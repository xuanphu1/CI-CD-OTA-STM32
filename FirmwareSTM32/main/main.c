#include "main.h"
#include "I2C_Handmade.h"

void SysTick_Handler()
{
    SysTick_ms_inc();
    // TriggerSV_Call_Interrupt();
}

SysTick_Config_t SysTickConfig = {
    .EnableCounter = SYST_CSR_COUNTFLAG_YES,
    .Generate_interrupt = SYST_CSR_TICKINT_ENABLE,
    .SysTick_Source = SYST_CSR_CLKSOURCE_EXTERNAL,
    .ValueInitReload = 0};

RCC_config_t rccconfig = {
    .source_clock = HSE_CLOCK,
    .frequency = FREQ_72MHZ};

i2c_config_t i2cconfig = {
    .i2cType = I2C_1,
    .ackEnable = I2C_ACK_ENABLE,
    .addressingMode = I2C_7BIT_ADDRESS,
    .mode_clock_scl = I2C_FS_STANDARD,
    .PeripheralSpeed = I2C_FREQ_8MHZ,
    .speedSCL = 100000};

#define SSD1306_I2C_ADDRESS 0x3C
const uint8_t font_A_5x7[5] = {
    0x7C, // 0b01111100
    0x12, // 0b00010010
    0x11, // 0b00010001
    0x12, // 0b00010010
    0x7C  // 0b01111100
};
void SSD1306_WriteCommand(uint8_t cmd)
{
    masterSendStart(I2C_1);
    masterSendAddress(I2C_1, WRITEDATA, SSD1306_I2C_ADDRESS);
    masterSendData(I2C_1, 0x00); // Control byte: Co=0, D/C#=0 (lệnh)
    masterSendData(I2C_1, cmd);  // Byte lệnh
    masterSendStop(I2C_1);
}
void SSD1306_SetCursor(uint8_t col, uint8_t page)
{
    SSD1306_WriteCommand(0xB0 | page);                // Page Address (0..7)
    SSD1306_WriteCommand(0x00 | (col & 0x0F));        // Lower nibble column
    SSD1306_WriteCommand(0x10 | ((col >> 4) & 0x0F)); // Upper nibble column
}
void SSD1306_DrawCharA(uint8_t col, uint8_t page)
{
    SSD1306_SetCursor(col, page);
    // Gửi control byte (0x40) rồi gửi từng byte của ký tự A
    masterSendStart(I2C_1);
    masterSendAddress(I2C_1, WRITEDATA, SSD1306_I2C_ADDRESS);
    masterSendData(I2C_1, 0x40); // Control byte: data
    for (uint8_t i = 0; i < 5; i++)
    {
        masterSendData(I2C_1, font_A_5x7[i]);
    }
    masterSendData(I2C_1, 0x00); // Ký tự cách/thêm 1 cột trắng
    masterSendStop(I2C_1);
}

void SSD1306_Init(void)
{
    SSD1306_WriteCommand(0xAE); // Display OFF
    SSD1306_WriteCommand(0x20); // Set Memory Addressing Mode
    SSD1306_WriteCommand(0x10); // 00,Horizontal Addressing Mode; 01,Vertical Addressing Mode;
                                // 10,Page Addressing Mode (RESET); 11,Invalid
    SSD1306_WriteCommand(0xB0); // Set Page Start Address for Page Addressing Mode,0-7
    SSD1306_WriteCommand(0xC8); // Set COM Output Scan Direction
    SSD1306_WriteCommand(0x00); // ---set low column address
    SSD1306_WriteCommand(0x10); // ---set high column address
    SSD1306_WriteCommand(0x40); // ---set start line address
    SSD1306_WriteCommand(0x81); // Set contrast control register
    SSD1306_WriteCommand(0xFF); // Max contrast
    SSD1306_WriteCommand(0xA1); // Set segment re-map 0 to 127
    SSD1306_WriteCommand(0xA6); // Set normal display
    SSD1306_WriteCommand(0xA8); // Set multiplex ratio(1 to 64)
    SSD1306_WriteCommand(0x3F); //
    SSD1306_WriteCommand(0xA4); // 0xA4=>Output follows RAM content; 0xA5=>Output ignores RAM content
    SSD1306_WriteCommand(0xD3); // Set display offset
    SSD1306_WriteCommand(0x00); // No offset
    SSD1306_WriteCommand(0xD5); // Set display clock divide ratio/oscillator frequency
    SSD1306_WriteCommand(0xF0); // Set divide ratio
    SSD1306_WriteCommand(0xD9); // Set pre-charge period
    SSD1306_WriteCommand(0x22);
    SSD1306_WriteCommand(0xDA); // Set com pins hardware configuration
    SSD1306_WriteCommand(0x12);
    SSD1306_WriteCommand(0xDB); // Set vcomh
    SSD1306_WriteCommand(0x20); // 0x20,0.77xVcc
    SSD1306_WriteCommand(0x8D); // Set DC-DC enable
    SSD1306_WriteCommand(0x14);
    SSD1306_WriteCommand(0xAF); // Display ON
}
void SSD1306_Clear(void) {
    for (uint8_t page = 0; page < 8; page++) {
        SSD1306_SetCursor(0, page);
        masterSendStart(I2C_1);
        masterSendAddress(I2C_1, WRITEDATA, SSD1306_I2C_ADDRESS);
        masterSendData(I2C_1, 0x40); // Data
        for (uint8_t col = 0; col < 128; col++)
            masterSendData(I2C_1, 0x00); // Pixel off
        masterSendStop(I2C_1);
    }
}
int main(void)
{

    init_RCC(&rccconfig);
    SysTick_Init(&SysTickConfig);
    initI2C(&i2cconfig);
    SSD1306_Init();
    SSD1306_Clear();
    SSD1306_DrawCharA(0, 0); // Hiển thị 'A' ở góc trên cùng bên trái
    while (1)
    {
        
    }
}
