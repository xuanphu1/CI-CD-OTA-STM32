#ifndef I2C_HANDMADE_H
#define I2C_HANDMADE_H

#include <stdint.h>
#include "RCC_Handmade.h"
#include "GPIO_Handmade.h"
#include "math.h"

// I2C Base Address
#define I2C1_BASE_HANDMADE 0x40005400UL
#define I2C2_BASE_HANDMADE 0x40005800UL

typedef struct {
    uint32_t I2C_CR1;      // Control Register 1
    uint32_t I2C_CR2;      // Control Register 2
    uint32_t I2C_OAR1;     // Own Address Register 1
    uint32_t I2C_OAR2;     // Own Address Register 2
    uint32_t I2C_DR;       // Data Register
    uint32_t I2C_SR1;      // Status Register 1
    uint32_t I2C_SR2;      // Status Register 2
    uint32_t I2C_CCR;      // Clock Control Register
    uint32_t I2C_TRISE;    // TRISE Register
} I2C_Handmade_t;



#define I2C1_HANDMADE ((volatile I2C_Handmade_t*)I2C1_BASE_HANDMADE)
#define I2C2_HANDMADE ((volatile I2C_Handmade_t*)I2C2_BASE_HANDMADE)

/******************* I2C_CR1 (0x00) *******************/
#define I2C_CR1_PE_POS_hm            0
#define I2C_CR1_PE_MASK_hm           (1U << I2C_CR1_PE_POS_hm)
#define I2C_CR1_SMBUS_POS_hm         1
#define I2C_CR1_SMBUS_MASK_hm        (1U << I2C_CR1_SMBUS_POS_hm)
#define I2C_CR1_SMBTYPE_POS_hm       3
#define I2C_CR1_SMBTYPE_MASK_hm      (1U << I2C_CR1_SMBTYPE_POS_hm)
#define I2C_CR1_ENARP_POS_hm         4
#define I2C_CR1_ENARP_MASK_hm        (1U << I2C_CR1_ENARP_POS_hm)
#define I2C_CR1_ENPEC_POS_hm         5
#define I2C_CR1_ENPEC_MASK_hm        (1U << I2C_CR1_ENPEC_POS_hm)
#define I2C_CR1_ENGC_POS_hm          6
#define I2C_CR1_ENGC_MASK_hm         (1U << I2C_CR1_ENGC_POS_hm)
#define I2C_CR1_NOSTRETCH_POS_hm     7
#define I2C_CR1_NOSTRETCH_MASK_hm    (1U << I2C_CR1_NOSTRETCH_POS_hm)
#define I2C_CR1_START_POS_hm         8
#define I2C_CR1_START_MASK_hm        (1U << I2C_CR1_START_POS_hm)
#define I2C_CR1_STOP_POS_hm          9
#define I2C_CR1_STOP_MASK_hm         (1U << I2C_CR1_STOP_POS_hm)
#define I2C_CR1_ACK_POS_hm           10
#define I2C_CR1_ACK_MASK_hm          (1U << I2C_CR1_ACK_POS_hm)
#define I2C_CR1_POS_POS_hm           11
#define I2C_CR1_POS_MASK_hm          (1U << I2C_CR1_POS_POS_hm)
#define I2C_CR1_PEC_POS_hm           12
#define I2C_CR1_PEC_MASK_hm          (1U << I2C_CR1_PEC_POS_hm)
#define I2C_CR1_ALERT_POS_hm         13
#define I2C_CR1_ALERT_MASK_hm        (1U << I2C_CR1_ALERT_POS_hm)
#define I2C_CR1_SWRST_POS_hm         15
#define I2C_CR1_SWRST_MASK_hm        (1U << I2C_CR1_SWRST_POS_hm)

/******************* I2C_CR2 (0x04) *******************/
#define I2C_CR2_FREQ_POS_hm          0
#define I2C_CR2_FREQ_MASK_hm         (0x3F << I2C_CR2_FREQ_POS_hm)
#define I2C_CR2_ITERREN_POS_hm       8
#define I2C_CR2_ITERREN_MASK_hm      (1U << I2C_CR2_ITERREN_POS_hm)
#define I2C_CR2_ITEVTEN_POS_hm       9
#define I2C_CR2_ITEVTEN_MASK_hm      (1U << I2C_CR2_ITEVTEN_POS_hm)
#define I2C_CR2_ITBUFEN_POS_hm       10
#define I2C_CR2_ITBUFEN_MASK_hm      (1U << I2C_CR2_ITBUFEN_POS_hm)
#define I2C_CR2_DMAEN_POS_hm         11
#define I2C_CR2_DMAEN_MASK_hm        (1U << I2C_CR2_DMAEN_POS_hm)
#define I2C_CR2_LAST_POS_hm          12
#define I2C_CR2_LAST_MASK_hm         (1U << I2C_CR2_LAST_POS_hm)

/******************* I2C_OAR1 (0x08) *******************/
#define I2C_OAR1_ADD0_POS_hm         0
#define I2C_OAR1_ADD0_MASK_hm        (1U << I2C_OAR1_ADD0_POS_hm)
#define I2C_OAR1_ADD7_1_POS_hm       1
#define I2C_OAR1_ADD7_1_MASK_hm      (0x7F << I2C_OAR1_ADD7_1_POS_hm)
#define I2C_OAR1_ADD9_8_POS_hm       8
#define I2C_OAR1_ADD9_8_MASK_hm      (0x3 << I2C_OAR1_ADD9_8_POS_hm)
#define I2C_OAR1_ADDMODE_POS_hm      15
#define I2C_OAR1_ADDMODE_MASK_hm     (1U << I2C_OAR1_ADDMODE_POS_hm)

/******************* I2C_OAR2 (0x0C) *******************/
#define I2C_OAR2_ENDUAL_POS_hm       0
#define I2C_OAR2_ENDUAL_MASK_hm      (1U << I2C_OAR2_ENDUAL_POS_hm)
#define I2C_OAR2_ADD2_7_1_POS_hm     1
#define I2C_OAR2_ADD2_7_1_MASK_hm    (0x7F << I2C_OAR2_ADD2_7_1_POS_hm)

/******************* I2C_DR (0x10) *******************/
#define I2C_DR_DR_POS_hm             0
#define I2C_DR_DR_MASK_hm            (0xFF << I2C_DR_DR_POS_hm)

/******************* I2C_SR1 (0x14) *******************/
#define I2C_SR1_SB_POS_hm            0
#define I2C_SR1_SB_MASK_hm           (1U << I2C_SR1_SB_POS_hm)
#define I2C_SR1_ADDR_POS_hm          1
#define I2C_SR1_ADDR_MASK_hm         (1U << I2C_SR1_ADDR_POS_hm)
#define I2C_SR1_BTF_POS_hm           2
#define I2C_SR1_BTF_MASK_hm          (1U << I2C_SR1_BTF_POS_hm)
#define I2C_SR1_ADD10_POS_hm         3
#define I2C_SR1_ADD10_MASK_hm        (1U << I2C_SR1_ADD10_POS_hm)
#define I2C_SR1_STOPF_POS_hm         4
#define I2C_SR1_STOPF_MASK_hm        (1U << I2C_SR1_STOPF_POS_hm)
#define I2C_SR1_RXNE_POS_hm          6
#define I2C_SR1_RXNE_MASK_hm         (1U << I2C_SR1_RXNE_POS_hm)
#define I2C_SR1_TXE_POS_hm           7
#define I2C_SR1_TXE_MASK_hm          (1U << I2C_SR1_TXE_POS_hm)
#define I2C_SR1_BERR_POS_hm          8
#define I2C_SR1_BERR_MASK_hm         (1U << I2C_SR1_BERR_POS_hm)
#define I2C_SR1_ARLO_POS_hm          9
#define I2C_SR1_ARLO_MASK_hm         (1U << I2C_SR1_ARLO_POS_hm)
#define I2C_SR1_AF_POS_hm            10
#define I2C_SR1_AF_MASK_hm           (1U << I2C_SR1_AF_POS_hm)
#define I2C_SR1_OVR_POS_hm           11
#define I2C_SR1_OVR_MASK_hm          (1U << I2C_SR1_OVR_POS_hm)
#define I2C_SR1_PECERR_POS_hm        12
#define I2C_SR1_PECERR_MASK_hm       (1U << I2C_SR1_PECERR_POS_hm)
#define I2C_SR1_TIMEOUT_POS_hm       14
#define I2C_SR1_TIMEOUT_MASK_hm      (1U << I2C_SR1_TIMEOUT_POS_hm)
#define I2C_SR1_SMBALERT_POS_hm      15
#define I2C_SR1_SMBALERT_MASK_hm     (1U << I2C_SR1_SMBALERT_POS_hm)

/******************* I2C_SR2 (0x18) *******************/
#define I2C_SR2_MSL_POS_hm           0
#define I2C_SR2_MSL_MASK_hm          (1U << I2C_SR2_MSL_POS_hm)
#define I2C_SR2_BUSY_POS_hm          1
#define I2C_SR2_BUSY_MASK_hm         (1U << I2C_SR2_BUSY_POS_hm)
#define I2C_SR2_TRA_POS_hm           2
#define I2C_SR2_TRA_MASK_hm          (1U << I2C_SR2_TRA_POS_hm)
#define I2C_SR2_GENCALL_POS_hm       4
#define I2C_SR2_GENCALL_MASK_hm      (1U << I2C_SR2_GENCALL_POS_hm)
#define I2C_SR2_SMBDEFAULT_POS_hm    5
#define I2C_SR2_SMBDEFAULT_MASK_hm   (1U << I2C_SR2_SMBDEFAULT_POS_hm)
#define I2C_SR2_SMBHOST_POS_hm       6
#define I2C_SR2_SMBHOST_MASK_hm      (1U << I2C_SR2_SMBHOST_POS_hm)
#define I2C_SR2_DUALF_POS_hm         7
#define I2C_SR2_DUALF_MASK_hm        (1U << I2C_SR2_DUALF_POS_hm)
#define I2C_SR2_PEC_POS_hm           8
#define I2C_SR2_PEC_MASK_hm          (0xFF << I2C_SR2_PEC_POS_hm)

/******************* I2C_CCR (0x1C) *******************/
#define I2C_CCR_CCR_POS_hm           0
#define I2C_CCR_CCR_MASK_hm          (0xFFF << I2C_CCR_CCR_POS_hm)
#define I2C_CCR_DUTY_POS_hm          14
#define I2C_CCR_DUTY_MASK_hm         (1U << I2C_CCR_DUTY_POS_hm)
#define I2C_CCR_FS_POS_hm            15
#define I2C_CCR_FS_MASK_hm           (1U << I2C_CCR_FS_POS_hm)

/******************* I2C_TRISE (0x20) *******************/
#define I2C_TRISE_TRISE_POS_hm       0
#define I2C_TRISE_TRISE_MASK_hm      (0x3F << I2C_TRISE_TRISE_POS_hm)


/***************** I2C_CR1 *****************/
typedef enum {
    I2C_NOT_PE = 0,
    I2C_PE = 1
} CR1_PE_t;

typedef enum {
    I2C_NOT_SMBUS = 0,
    I2C_SMBUS = 1
} CR1_SMBUS_t;

typedef enum {
    I2C_NOT_SMBTYPE = 0,
    I2C_SMBTYPE = 1
} CR1_SMBTYPE_t;

typedef enum {
    I2C_ENARP_DISABLE = 0,
    I2C_ENARP_ENABLE = 1
} CR1_ENARP_t;

typedef enum {
    I2C_ENPEC_DISABLE = 0,
    I2C_ENPEC_ENABLE = 1
} CR1_ENPEC_t;

typedef enum {
    I2C_ENGC_DISABLE = 0,
    I2C_ENGC_ENABLE = 1
} CR1_ENGC_t;

typedef enum {
    I2C_NOSTRETCH_DISABLE = 0,
    I2C_NOSTRETCH_ENABLE = 1
} CR1_NOSTRETCH_t;

typedef enum {
    I2C_START_NOT_GENERATED = 0,
    I2C_START_GENERATED = 1
} CR1_START_t;

typedef enum {
    I2C_STOP_NOT_GENERATED = 0,
    I2C_STOP_GENERATED = 1
} CR1_STOP_t;

typedef enum {
    I2C_ACK_DISABLE = 0,
    I2C_ACK_ENABLE = 1
} CR1_ACK_t;

typedef enum {
    I2C_POS_DISABLE = 0,
    I2C_POS_ENABLE = 1
} CR1_POS_t;

typedef enum {
    I2C_PEC_DISABLE = 0,
    I2C_PEC_ENABLE = 1
} CR1_PEC_t;

typedef enum {
    I2C_ALERT_NOT_SET = 0,
    I2C_ALERT_SET = 1
} CR1_ALERT_t;

typedef enum {
    I2C_NOT_UNDER_RESET = 0,
    I2C_UNDER_RESET = 1
} CR1_SWRST_t;


/***************** I2C_CR2 *****************/
typedef enum {
    I2C_ITERREN_DISABLE = 0,
    I2C_ITERREN_ENABLE = 1
} CR2_ITERREN_t;

typedef enum {
    I2C_ITEVTEN_DISABLE = 0,
    I2C_ITEVTEN_ENABLE = 1
} CR2_ITEVTEN_t;

typedef enum {
    I2C_ITBUFEN_DISABLE = 0,
    I2C_ITBUFEN_ENABLE = 1
} CR2_ITBUFEN_t;

typedef enum {
    I2C_DMAEN_DISABLE = 0,
    I2C_DMAEN_ENABLE = 1
} CR2_DMAEN_t;

typedef enum {
    I2C_LAST_DISABLE = 0,
    I2C_LAST_ENABLE = 1
} CR2_LAST_t;


/***************** I2C_OAR1 *****************/
typedef enum {
    I2C_ADD0_RESET = 0,
    I2C_ADD0_SET = 1
} OAR1_ADD0_t;

typedef enum {
    I2C_7BIT_ADDRESS = 0,
    I2C_10BIT_ADDRESS = 1
} OAR1_ADDMODE_t;


/***************** I2C_OAR2 *****************/
typedef enum {
    I2C_ENDUAL_DISABLE = 0,
    I2C_ENDUAL_ENABLE = 1
} OAR2_ENDUAL_t;


/***************** I2C_SR1 *****************/
typedef enum {
    I2C_SB_NOT_SET = 0,
    I2C_SB_SET = 1
} SR1_SB_t;

typedef enum {
    I2C_ADDR_NOT_MATCHED = 0,
    I2C_ADDR_MATCHED = 1
} SR1_ADDR_t;

typedef enum {
    I2C_BTF_NOT_FINISHED = 0,
    I2C_BTF_FINISHED = 1
} SR1_BTF_t;

typedef enum {
    I2C_ADD10_NOT_SET = 0,
    I2C_ADD10_SET = 1
} SR1_ADD10_t;

typedef enum {
    I2C_STOPF_NOT_DETECTED = 0,
    I2C_STOPF_DETECTED = 1
} SR1_STOPF_t;

typedef enum {
    I2C_RXNE_EMPTY = 0,
    I2C_RXNE_NOT_EMPTY = 1
} SR1_RXNE_t;

typedef enum {
    I2C_TXE_NOT_EMPTY = 0,
    I2C_TXE_EMPTY = 1
} SR1_TXE_t;

typedef enum {
    I2C_BERR_NO_ERROR = 0,
    I2C_BERR_ERROR = 1
} SR1_BERR_t;

typedef enum {
    I2C_ARLO_NO_ERROR = 0,
    I2C_ARLO_ERROR = 1
} SR1_ARLO_t;

typedef enum {
    I2C_AF_NO_FAILURE = 0,
    I2C_AF_FAILURE = 1
} SR1_AF_t;

typedef enum {
    I2C_OVR_NO_OVERRUN = 0,
    I2C_OVR_OVERRUN = 1
} SR1_OVR_t;

typedef enum {
    I2C_PECERR_NO_ERROR = 0,
    I2C_PECERR_ERROR = 1
} SR1_PECERR_t;

typedef enum {
    I2C_TIMEOUT_NO_TIMEOUT = 0,
    I2C_TIMEOUT_TIMEOUT = 1
} SR1_TIMEOUT_t;

typedef enum {
    I2C_SMBALERT_NOT_ALERTED = 0,
    I2C_SMBALERT_ALERTED = 1
} SR1_SMBALERT_t;


/***************** I2C_SR2 *****************/
typedef enum {
    I2C_MSL_SLAVE = 0,
    I2C_MSL_MASTER = 1
} SR2_MSL_t;

typedef enum {
    I2C_BUSY_NOT_BUSY = 0,
    I2C_BUSY_BUSY = 1
} SR2_BUSY_t;

typedef enum {
    I2C_TRA_RECEIVER = 0,
    I2C_TRA_TRANSMITTER = 1
} SR2_TRA_t;

typedef enum {
    I2C_GENCALL_NOT_RECEIVED = 0,
    I2C_GENCALL_RECEIVED = 1
} SR2_GENCALL_t;

typedef enum {
    I2C_SMBDEFAULT_NOT_SET = 0,
    I2C_SMBDEFAULT_SET = 1
} SR2_SMBDEFAULT_t;

typedef enum {
    I2C_SMBHOST_NOT_SET = 0,
    I2C_SMBHOST_SET = 1
} SR2_SMBHOST_t;

typedef enum {
    I2C_DUALF_NOT_SELECTED = 0,
    I2C_DUALF_SELECTED = 1
} SR2_DUALF_t;


/***************** I2C_CCR *****************/
typedef enum {
    I2C_DUTY_2 = 0,    // T_low/T_high = 2
    I2C_DUTY_16_9 = 1  // T_low/T_high = 16/9
} CCR_DUTY_t;

typedef enum {
    I2C_FS_STANDARD = 0, // Standard mode
    I2C_FS_FAST = 1      // Fast mode
} CCR_FS_t;


typedef enum {
    I2C_1 = 0,
    I2C_2 = 1
} i2c_type_t;

typedef enum {
    WRITEDATA,
    READDATA
}readWriteBit_t;


typedef enum {
    I2C_FREQ_NOT_ALLOWED_0 = 0,
    I2C_FREQ_NOT_ALLOWED_1 = 1,
    I2C_FREQ_2MHZ  = 2,
    I2C_FREQ_3MHZ  = 3,
    I2C_FREQ_4MHZ  = 4,
    I2C_FREQ_5MHZ  = 5,
    I2C_FREQ_6MHZ  = 6,
    I2C_FREQ_7MHZ  = 7,
    I2C_FREQ_8MHZ  = 8,
    I2C_FREQ_9MHZ  = 9,
    I2C_FREQ_10MHZ = 10,
    I2C_FREQ_11MHZ = 11,
    I2C_FREQ_12MHZ = 12,
    I2C_FREQ_13MHZ = 13,
    I2C_FREQ_14MHZ = 14,
    I2C_FREQ_15MHZ = 15,
    I2C_FREQ_16MHZ = 16,
    I2C_FREQ_17MHZ = 17,
    I2C_FREQ_18MHZ = 18,
    I2C_FREQ_19MHZ = 19,
    I2C_FREQ_20MHZ = 20,
    I2C_FREQ_21MHZ = 21,
    I2C_FREQ_22MHZ = 22,
    I2C_FREQ_23MHZ = 23,
    I2C_FREQ_24MHZ = 24,
    I2C_FREQ_25MHZ = 25,
    I2C_FREQ_26MHZ = 26,
    I2C_FREQ_27MHZ = 27,
    I2C_FREQ_28MHZ = 28,
    I2C_FREQ_29MHZ = 29,
    I2C_FREQ_30MHZ = 30,
    I2C_FREQ_31MHZ = 31,
    I2C_FREQ_32MHZ = 32,
    I2C_FREQ_33MHZ = 33,
    I2C_FREQ_34MHZ = 34,
    I2C_FREQ_35MHZ = 35,
    I2C_FREQ_36MHZ = 36,
    I2C_FREQ_37MHZ = 37,
    I2C_FREQ_38MHZ = 38,
    I2C_FREQ_39MHZ = 39,
    I2C_FREQ_40MHZ = 40,
    I2C_FREQ_41MHZ = 41,
    I2C_FREQ_42MHZ = 42,
    I2C_FREQ_43MHZ = 43,
    I2C_FREQ_44MHZ = 44,
    I2C_FREQ_45MHZ = 45,
    I2C_FREQ_46MHZ = 46,
    I2C_FREQ_47MHZ = 47,
    I2C_FREQ_48MHZ = 48,
    I2C_FREQ_49MHZ = 49,
    I2C_FREQ_50MHZ = 50
} I2C_FREQ_CR2_t;




typedef struct  
{

    i2c_type_t i2cType;          // Loại I2C (1 hoặc 2)
    
    // --- Timing and clock configuration ---
    uint32_t speedSCL;       // Tốc độ SCL, Hz
    CCR_FS_t mode_clock_scl;          // Chế độ I2C (Standard hoặc Fast)
    I2C_FREQ_CR2_t PeripheralSpeed;        // Tốc độ I2C, Hz
    CCR_DUTY_t dutyCycle;       // CCR: Duty cycle (2 hoặc 16/9)
    uint32_t riseTime;          // TRISE, đơn vị ns hoặc raw

    // --- Main I2C function config ---
    CR1_ACK_t ackEnable;            // Enable/disable ACK
    CR1_ENPEC_t pecEnable;          // Enable/disable PEC
    CR1_ENARP_t arpEnable;          // Enable/disable ARP
    CR1_ENGC_t generalCallEnable;   // Enable/disable General Call
    CR1_NOSTRETCH_t noStretchEnable;// Enable/disable Clock Stretching
    CR1_POS_t posBitEnable;         // Enable/disable Acknowledge/PEC Position
    CR1_SMBUS_t smbusEnable;        // Enable/disable SMBus mode
    CR1_SMBTYPE_t smbusType;        // SMBus device type (Device/Host)
    CR1_ALERT_t alertEnable;        // Enable/disable SMBus alert

    // --- Address config ---
    OAR1_ADDMODE_t addressingMode;  // 7/10-bit addressing mode
    uint16_t ownAddress1;           // Địa chỉ chính
    OAR2_ENDUAL_t dualAddressEnable;// Enable/disable dual addressing
    uint16_t ownAddress2;           // Địa chỉ phụ

    // --- Interrupt, DMA config ---
    CR2_ITERREN_t errorInterruptEnable;   // Error interrupt
    CR2_ITEVTEN_t eventInterruptEnable;   // Event interrupt
    CR2_ITBUFEN_t bufferInterruptEnable;  // Buffer interrupt
    CR2_DMAEN_t dmaEnable;                // DMA enable
    CR2_LAST_t lastDmaTransfer;           // Last DMA transfer

    // --- Soft reset (ít khi dùng khi init, nhưng để đủ field) ---
    CR1_SWRST_t softwareReset;            // Software reset

} i2c_config_t;



void initI2C(i2c_config_t *config);
void masterSendStart(i2c_type_t I2C);
void masterSendAddress(i2c_type_t I2C,readWriteBit_t readWriteBit,uint16_t SlaveAddress);
void masterSendData(i2c_type_t I2C,uint8_t data); 
void masterSendStop(i2c_type_t I2C);
uint8_t masterRecieve_1_byte(i2c_type_t I2C);
#endif // I2C_HANDMADE_H