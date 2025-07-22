#include "I2C_Handmade.h"

volatile I2C_Handmade_t *I2C_LIST[] = {I2C1_HANDMADE, I2C2_HANDMADE};

void initI2C(i2c_config_t *config)
{

    volatile I2C_Handmade_t *I2Cx = I2C_LIST[config->i2cType];
    Enable_Clock_RCC_APB1(config->i2cType == I2C_1 ? I2C1_EN_CLK : I2C2_EN_CLK);
    GPIO_config_t scl_gpio;
    GPIO_config_t sda_gpio;

    scl_gpio.port = Port_B;
    scl_gpio.pin = (config->i2cType == I2C_1) ? PIN_6 : PIN_10; // SCL pin for I2C1 and I2C2
    scl_gpio.cnf_mode = CNF_MODE_11;                            // Alternate function push-pull
    scl_gpio.mode = OUTPUT_MODE_50_MHZ;                         // 50 MHz output speed
    InitGPIO(&scl_gpio);

    sda_gpio.port = Port_B;
    sda_gpio.pin = (config->i2cType == I2C_1) ? PIN_7 : PIN_11; // SDA pin for I2C1 and I2C2
    sda_gpio.cnf_mode = CNF_MODE_11;                            // Alternate function push-pull
    sda_gpio.mode = OUTPUT_MODE_50_MHZ;                         // 50 MHz output speed
    InitGPIO(&sda_gpio);

    I2Cx->I2C_CR1 = 0; // Reset CR1
    I2Cx->I2C_CR2 = 0; // Reset CR2

    I2Cx->I2C_CR1 |= config->ackEnable << I2C_CR1_ACK_POS_hm;
    I2Cx->I2C_OAR1 |= config->addressingMode << I2C_OAR1_ADDMODE_POS_hm;

    I2Cx->I2C_CR2 |= (config->PeripheralSpeed & 0x3F) << I2C_CR2_FREQ_POS_hm; // Set frequency in CR2
    uint32_t ccr_val;
    if (config->mode_clock_scl == I2C_FS_STANDARD)
    {
        ccr_val = (config->PeripheralSpeed * 1000000) / (config->speedSCL * 2);
        if (ccr_val < 4)
            ccr_val = 4;                                 // CCR tối thiểu là 4
        I2Cx->I2C_CCR = (ccr_val << I2C_CCR_CCR_POS_hm); // Gán trực tiếp (xóa |=, tránh lỗi cấu hình chồng)
    }
    else
    {
        // I2Cx->I2C_CCR = (config->dutyCycle << I2C_CCR_DUTY_POS_hm) | (I2C_FS_FAST << I2C_CCR_FS_POS_hm);
        // Will continue ...
    }

    I2Cx->I2C_TRISE = (((config->mode_clock_scl == I2C_FS_STANDARD) ? 1000 : 300) / (config->PeripheralSpeed)) + 1;
    I2Cx->I2C_CR1 |= 1 << I2C_CR1_PE_POS_hm; // Enable I2C peripheral
}

static void enableACK(i2c_type_t I2C)
{
    volatile I2C_Handmade_t *I2Cx = I2C_LIST[I2C];
    I2Cx->I2C_CR1 |= I2C_ACK_ENABLE << I2C_CR1_ACK_POS_hm;
}

static void disableACK(i2c_type_t I2C)
{
    volatile I2C_Handmade_t *I2Cx = I2C_LIST[I2C];
    I2Cx->I2C_CR1 |= I2C_ACK_DISABLE << I2C_CR1_ACK_POS_hm;
}

void masterSendStart(i2c_type_t I2C)
{
    volatile I2C_Handmade_t *I2Cx = I2C_LIST[I2C];
    I2Cx->I2C_CR1 |= 1 << I2C_CR1_START_POS_hm;
    while (!(I2Cx->I2C_SR1 & I2C_SR1_SB_MASK_hm))
        ;
    volatile uint32_t temp = I2Cx->I2C_SR1;
    (void)temp;
}
void masterSendAddress(i2c_type_t I2C, readWriteBit_t readWriteBit, uint16_t SlaveAddress)
{
    volatile I2C_Handmade_t *I2Cx = I2C_LIST[I2C];
    I2Cx->I2C_DR = (SlaveAddress << 1) | readWriteBit;
    while (!(I2Cx->I2C_SR1 & I2C_SR1_ADDR_MASK_hm))
        ;
    volatile uint32_t temp = I2Cx->I2C_SR1;
    temp = I2Cx->I2C_SR2;
    (void)temp;
}
void masterSendData(i2c_type_t I2C, uint8_t data)
{
    volatile I2C_Handmade_t *I2Cx = I2C_LIST[I2C];
    while (!(I2Cx->I2C_SR1 & I2C_SR1_TXE_MASK_hm))
        ;
    I2Cx->I2C_DR = data;
    while (I2Cx->I2C_SR1 & I2C_SR1_AF_MASK_hm)
        ;
}

void masterSendStop(i2c_type_t I2C)
{
    volatile I2C_Handmade_t *I2Cx = I2C_LIST[I2C];
    while (!((I2Cx->I2C_SR1 & I2C_SR1_TXE_MASK_hm) && (I2Cx->I2C_SR1 & I2C_SR1_BTF_MASK_hm)))
        ;
    I2Cx->I2C_CR1 |= 1 << I2C_CR1_STOP_POS_hm;
}

// uint8_t masterRecieve_1_byte(i2c_type_t I2C){
//     volatile I2C_Handmade_t *I2Cx = I2C_LIST[I2C];
//     disableACK(I2C);
//     masterSendStop(I2C);
//     return (uint8_t)I2Cx->I2C_DR;
// }

void masterReceiveBuff(i2c_type_t I2C, uint8_t *buff, uint8_t length)
{
    volatile I2C_Handmade_t *I2Cx = I2C_LIST[I2C];

    if (length == 1)
    {
        // Chờ ADDR=1
        while (!(I2Cx->I2C_SR1 & I2C_SR1_ADDR_MASK_hm))
            ;
        // Tắt ACK
        disableACK(I2C);
        // Clear ADDR
        volatile uint32_t temp = I2Cx->I2C_SR1;
        temp = I2Cx->I2C_SR2;
        (void)temp;
        // Gửi STOP
        I2Cx->I2C_CR1 |= 1 << I2C_CR1_STOP_POS_hm;
        // Chờ RxNE
        while (!(I2Cx->I2C_SR1 & I2C_SR1_RXNE_MASK_hm))
            ;
        buff[0] = (uint8_t)I2Cx->I2C_DR;
    }
    else if (length == 2)
    {
        // Chờ ADDR=1
        while (!(I2Cx->I2C_SR1 & I2C_SR1_ADDR_MASK_hm))
            ;
        // Tắt ACK
        disableACK(I2C);
        // Set POS=1 (nếu dùng)
        // I2Cx->I2C_CR1 |= (1 << POS_BIT);
        // Clear ADDR
        volatile uint32_t temp = I2Cx->I2C_SR1;
        temp = I2Cx->I2C_SR2;
        (void)temp;
        // Chờ BTF=1 (cả 2 byte vào FIFO)
        while (!(I2Cx->I2C_SR1 & I2C_SR1_BTF_MASK_hm))
            ;
        // Gửi STOP
        I2Cx->I2C_CR1 |= 1 << I2C_CR1_STOP_POS_hm;
        // Đọc 2 byte liên tiếp
        buff[0] = (uint8_t)I2Cx->I2C_DR;
        buff[1] = (uint8_t)I2Cx->I2C_DR;
    }
    else if (length > 2)
    {
        // Chờ ADDR=1
        while (!(I2Cx->I2C_SR1 & I2C_SR1_ADDR_MASK_hm))
            ;
        // Để ACK=1
        // Clear ADDR
        volatile uint32_t temp = I2Cx->I2C_SR1;
        temp = I2Cx->I2C_SR2;
        (void)temp;

        uint8_t idx = 0;
        for (idx = 0; idx < length; idx++)
        {
            // Khi còn 3 byte cuối
            if (idx == length - 3)
            {
                // Đợi BTF
                while (!(I2Cx->I2C_SR1 & I2C_SR1_BTF_MASK_hm))
                    ;
                // Tắt ACK
                disableACK(I2C);
            }
            // Khi còn 2 byte cuối
            if (idx == length - 2)
            {
                // Đợi BTF
                while (!(I2Cx->I2C_SR1 & I2C_SR1_BTF_MASK_hm))
                    ;
                // Gửi STOP
                I2Cx->I2C_CR1 |= 1 << I2C_CR1_STOP_POS_hm;
            }
            // Đợi RxNE
            while (!(I2Cx->I2C_SR1 & I2C_SR1_RXNE_MASK_hm))
                ;
            buff[idx] = (uint8_t)I2Cx->I2C_DR;
        }
    }
    // Xong thì bật lại ACK nếu cần cho lần sau
    enableACK(I2C);
}