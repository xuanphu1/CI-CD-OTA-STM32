#ifndef SPI_HANDMADE_H
#define SPI_HANDMADE_H

#include <stdint.h>
#include "GPIO_Handmade.h"

// SPI Base Addresses (for STM32F1)
#define SPI1_BASE_HANDMADE 0x40013000UL
#define SPI2_BASE_HANDMADE 0x40003800UL
#define SPI3_BASE_HANDMADE 0x40003C00UL


// SPI Register Structure
typedef struct {
    uint32_t SPI_CR1;      // Control Register 1, offset 0x00
    uint32_t SPI_CR2;      // Control Register 2, offset 0x04
    uint32_t SPI_SR;       // Status Register, offset 0x08
    uint32_t SPI_DR;       // Data Register, offset 0x0C
    uint32_t SPI_CRCPR;    // CRC Polynomial Register, offset 0x10
    uint32_t SPI_RXCRCR;   // RX CRC Register, offset 0x14
    uint32_t SPI_TXCRCR;   // TX CRC Register, offset 0x18
    uint32_t SPI_I2SCFGR;  // I2S Configuration Register, offset 0x1C
    uint32_t SPI_I2SPR;    // I2S Prescaler Register, offset 0x20
} SPI_Handmade_t;


#define SPI1_HANDMADE ((volatile SPI_Handmade_t*)SPI1_BASE_HANDMADE)
#define SPI2_HANDMADE ((volatile SPI_Handmade_t*)SPI2_BASE_HANDMADE)
#define SPI3_HANDMADE ((volatile SPI_Handmade_t*)SPI3_BASE_HANDMADE)


// SPI_CR1 Bit Definitions and Masks
#define SPI_CR1_BIDIMODE_POS        15
#define HM_SPI_CR1_BIDIMODE_MASK    (1U << 15)

#define SPI_CR1_BIDIOE_POS          14
#define HM_SPI_CR1_BIDIOE_MASK      (1U << 14)

#define SPI_CR1_CRCEN_POS           13
#define HM_SPI_CR1_CRCEN_MASK       (1U << 13)

#define SPI_CR1_CRCNEXT_POS         12
#define HM_SPI_CR1_CRCNEXT_MASK     (1U << 12)

#define SPI_CR1_DFF_POS             11
#define HM_SPI_CR1_DFF_MASK         (1U << 11)

#define SPI_CR1_RXONLY_POS          10
#define HM_SPI_CR1_RXONLY_MASK      (1U << 10)

#define SPI_CR1_SSM_POS             9
#define HM_SPI_CR1_SSM_MASK         (1U << 9)

#define SPI_CR1_SSI_POS             8
#define HM_SPI_CR1_SSI_MASK         (1U << 8)

#define SPI_CR1_LSBFIRST_POS        7
#define HM_SPI_CR1_LSBFIRST_MASK    (1U << 7)

#define SPI_CR1_SPE_POS             6
#define HM_SPI_CR1_SPE_MASK         (1U << 6)

#define SPI_CR1_BR_POS              3
#define HM_SPI_CR1_BR_MASK          (0x7U << 3)

#define SPI_CR1_MSTR_POS            2
#define HM_SPI_CR1_MSTR_MASK        (1U << 2)

#define SPI_CR1_CPOL_POS            1
#define HM_SPI_CR1_CPOL_MASK        (1U << 1)

#define SPI_CR1_CPHA_POS            0
#define HM_SPI_CR1_CPHA_MASK        (1U << 0)

// SPI_CR2 Bit Definitions and Masks
#define SPI_CR2_TXEIE_POS           7
#define HM_SPI_CR2_TXEIE_MASK       (1U << 7)

#define SPI_CR2_RXNEIE_POS          6
#define HM_SPI_CR2_RXNEIE_MASK      (1U << 6)

#define SPI_CR2_ERRIE_POS           5
#define HM_SPI_CR2_ERRIE_MASK       (1U << 5)

#define SPI_CR2_SSOE_POS            2
#define HM_SPI_CR2_SSOE_MASK        (1U << 2)

#define SPI_CR2_TXDMAEN_POS         1
#define HM_SPI_CR2_TXDMAEN_MASK     (1U << 1)

#define SPI_CR2_RXDMAEN_POS         0
#define HM_SPI_CR2_RXDMAEN_MASK     (1U << 0)

// SPI_SR Bit Definitions and W Masks
#define SPI_SR_BSY_POS              7
#define HM_SPI_SR_BSY_MASK          (1U << 7)

#define SPI_SR_OVR_POS              6
#define HM_SPI_SR_OVR_MASK          (1U << 6)

#define SPI_SR_MODF_POS             5
#define HM_SPI_SR_MODF_MASK         (1U << 5)

#define SPI_SR_CRCERR_POS           4
#define HM_SPI_SR_CRCERR_MASK       (1U << 4)

#define SPI_SR_UDR_POS              3
#define HM_SPI_SR_UDR_MASK          (1U << 3)

#define SPI_SR_CHSIDE_POS           2
#define HM_SPI_SR_CHSIDE_MASK       (1U << 2)

#define SPI_SR_TXE_POS              1
#define HM_SPI_SR_TXE_MASK          (1U << 1)

#define SPI_SR_RXNE_POS             0
#define HM_SPI_SR_RXNE_MASK         (1U << 0)

// SPI_DR Bit Definitions and Masks
#define SPI_DR_DR_POS               0
#define HM_SPI_DR_DR_MASK           (0xFFFFU << 0) // 16-bit data

// SPI_CRCPR Bit Definitions and Masks
#define SPI_CRCPR_CRCPOLY_POS       0
#define HM_SPI_CRCPR_CRCPOLY_MASK   (0xFFFFU << 0) // 16-bit polynomial

// SPI_RXCRCR Bit Definitions and Masks
#define SPI_RXCRCR_RXCRC_POS        0
#define HM_SPI_RXCRCR_RXCRC_MASK    (0xFFFFU << 0) // 16-bit RX CRC

// SPI_TXCRCR Bit Definitions and Masks
#define SPI_TXCRCR_TXCRC_POS        0
#define HM_SPI_TXCRCR_TXCRC_MASK    (0xFFFFU << 0) // 16-bit TX CRC

// SPI_I2SCFGR Bit Definitions and Masks
#define SPI_I2SCFGR_I2SMOD_POS      11
#define HM_SPI_I2SCFGR_I2SMOD_MASK  (1U << 11)

#define SPI_I2SCFGR_I2SE_POS        10
#define HM_SPI_I2SCFGR_I2SE_MASK    (1U << 10)

#define SPI_I2SCFGR_I2SCFG_POS      8
#define HM_SPI_I2SCFGR_I2SCFG_MASK  (0x3U << 8)

#define SPI_I2SCFGR_PCMSYNC_POS     7
#define HM_SPI_I2SCFGR_PCMSYNC_MASK (1U << 7)

#define SPI_I2SCFGR_I2SSTD_POS      4
#define HM_SPI_I2SCFGR_I2SSTD_MASK  (0x3U << 4)

#define SPI_I2SCFGR_CKPOL_POS       3
#define HM_SPI_I2SCFGR_CKPOL_MASK   (1U << 3)

#define SPI_I2SCFGR_DATLEN_POS      1
#define HM_SPI_I2SCFGR_DATLEN_MASK  (0x3U << 1)

#define SPI_I2SCFGR_CHLEN_POS       0
#define HM_SPI_I2SCFGR_CHLEN_MASK   (1U << 0)

// SPI_I2SPR Bit Definitions and Masks
#define SPI_I2SPR_MCKOE_POS         9
#define HM_SPI_I2SPR_MCKOE_MASK     (1U << 9)

#define SPI_I2SPR_ODD_POS           8
#define HM_SPI_I2SPR_ODD_MASK       (1U << 8)

#define SPI_I2SPR_I2SDIV_POS        0
#define HM_SPI_I2SPR_I2SDIV_MASK    (0xFFU << 0) // 8-bit prescaler

// SPI_CR1 Enums
typedef enum {
    SPI_CR1_BIDIMODE_2LINE = 0,
    SPI_CR1_BIDIMODE_1LINE = 1
} SPI_CR1_BIDIMODE_t;

typedef enum {
    SPI_CR1_BIDIOE_RX = 0,
    SPI_CR1_BIDIOE_TX = 1
} SPI_CR1_BIDIOE_t;

typedef enum {
    SPI_CR1_CRCEN_DISABLE = 0,
    SPI_CR1_CRCEN_ENABLE = 1
} SPI_CR1_CRCEN_t;

typedef enum {
    SPI_CR1_CRCNEXT_DATA = 0,
    SPI_CR1_CRCNEXT_CRC = 1
} SPI_CR1_CRCNEXT_t;

typedef enum {
    SPI_CR1_DFF_8BIT = 0,
    SPI_CR1_DFF_16BIT = 1
} SPI_CR1_DFF_t;

typedef enum {
    SPI_CR1_RXONLY_FULL = 0,
    SPI_CR1_RXONLY_RX = 1
} SPI_CR1_RXONLY_t;

typedef enum {
    SPI_CR1_SSM_DISABLE = 0,
    SPI_CR1_SSM_ENABLE = 1
} SPI_CR1_SSM_t;

typedef enum {
    SPI_CR1_SSI_LOW = 0,
    SPI_CR1_SSI_HIGH = 1
} SPI_CR1_SSI_t;

typedef enum {
    SPI_CR1_LSBFIRST_MSB = 0,
    SPI_CR1_LSBFIRST_LSB = 1
} SPI_CR1_LSBFIRST_t;

typedef enum {
    SPI_CR1_SPE_DISABLE = 0,
    SPI_CR1_SPE_ENABLE = 1
} SPI_CR1_SPE_t;

typedef enum {
    SPI_CR1_BR_DIV2 = 0,
    SPI_CR1_BR_DIV4 = 1,
    SPI_CR1_BR_DIV8 = 2,
    SPI_CR1_BR_DIV16 = 3,
    SPI_CR1_BR_DIV32 = 4,
    SPI_CR1_BR_DIV64 = 5,
    SPI_CR1_BR_DIV128 = 6,
    SPI_CR1_BR_DIV256 = 7
} SPI_CR1_BR_t;

typedef enum {
    SPI_CR1_MSTR_SLAVE = 0,
    SPI_CR1_MSTR_MASTER = 1
} SPI_CR1_MSTR_t;

// SPI_CR2 Enums
typedef enum {
    SPI_CR2_TXEIE_DISABLE = 0,
    SPI_CR2_TXEIE_ENABLE = 1
} SPI_CR2_TXEIE_t;

typedef enum {
    SPI_CR2_RXNEIE_DISABLE = 0,
    SPI_CR2_RXNEIE_ENABLE = 1
} SPI_CR2_RXNEIE_t;

typedef enum {
    SPI_CR2_ERRIE_DISABLE = 0,
    SPI_CR2_ERRIE_ENABLE = 1
} SPI_CR2_ERRIE_t;

typedef enum {
    SPI_CR2_SSOE_DISABLE = 0,
    SPI_CR2_SSOE_ENABLE = 1
} SPI_CR2_SSOE_t;

typedef enum {
    SPI_CR2_TXDMAEN_DISABLE = 0,
    SPI_CR2_TXDMAEN_ENABLE = 1
} SPI_CR2_TXDMAEN_t;

typedef enum {
    SPI_CR2_RXDMAEN_DISABLE = 0,
    SPI_CR2_RXDMAEN_ENABLE = 1
} SPI_CR2_RXDMAEN_t;

// SPI_SR Enums
typedef enum {
    SPI_SR_BSY_NOT_BUSY = 0,
    SPI_SR_BSY_BUSY = 1
} SPI_SR_BSY_t;

typedef enum {
    SPI_SR_OVR_NO = 0,
    SPI_SR_OVR_YES = 1
} SPI_SR_OVR_t;

typedef enum {
    SPI_SR_MODF_NO = 0,
    SPI_SR_MODF_YES = 1
} SPI_SR_MODF_t;

typedef enum {
    SPI_SR_CRCERR_NO = 0,
    SPI_SR_CRCERR_YES = 1
} SPI_SR_CRCERR_t;

typedef enum {
    SPI_SR_UDR_NO = 0,
    SPI_SR_UDR_YES = 1
} SPI_SR_UDR_t;

typedef enum {
    SPI_SR_CHSIDE_LEFT = 0,
    SPI_SR_CHSIDE_RIGHT = 1
} SPI_SR_CHSIDE_t;

typedef enum {
    SPI_SR_TXE_NOT_EMPTY = 0,
    SPI_SR_TXE_EMPTY = 1
} SPI_SR_TXE_t;

typedef enum {
    SPI_SR_RXNE_EMPTY = 0,
    SPI_SR_RXNE_NOT_EMPTY = 1
} SPI_SR_RXNE_t;

// SPI_I2SCFGR Enums
typedef enum {
    SPI_I2SCFGR_I2SMOD_SPI = 0,
    SPI_I2SCFGR_I2SMOD_I2S = 1
} SPI_I2SCFGR_I2SMOD_t;

typedef enum {
    SPI_I2SCFGR_I2SE_DISABLE = 0,
    SPI_I2SCFGR_I2SE_ENABLE = 1
} SPI_I2SCFGR_I2SE_t;

typedef enum {
    SPI_I2SCFGR_I2SCFG_SLAVE_TX = 0,
    SPI_I2SCFGR_I2SCFG_SLAVE_RX = 1,
    SPI_I2SCFGR_I2SCFG_MASTER_TX = 2,
    SPI_I2SCFGR_I2SCFG_MASTER_RX = 3
} SPI_I2SCFGR_I2SCFG_t;

typedef enum {
    SPI_I2SCFGR_PCMSYNC_SHORT = 0,
    SPI_I2SCFGR_PCMSYNC_LONG = 1
} SPI_I2SCFGR_PCMSYNC_t;

typedef enum {
    SPI_I2SCFGR_I2SSTD_PHILIPS = 0,
    SPI_I2SCFGR_I2SSTD_MSB = 1,
    SPI_I2SCFGR_I2SSTD_LSB = 2,
    SPI_I2SCFGR_I2SSTD_PCM = 3
} SPI_I2SCFGR_I2SSTD_t;

typedef enum {
    SPI_I2SCFGR_CKPOL_LOW = 0,
    SPI_I2SCFGR_CKPOL_HIGH = 1
} SPI_I2SCFGR_CKPOL_t;

typedef enum {
    SPI_I2SCFGR_DATLEN_16BIT = 0,
    SPI_I2SCFGR_DATLEN_24BIT = 1,
    SPI_I2SCFGR_DATLEN_32BIT = 2,
    SPI_I2SCFGR_DATLEN_NA = 3
} SPI_I2SCFGR_DATLEN_t;

typedef enum {
    SPI_I2SCFGR_CHLEN_16BIT = 0,
    SPI_I2SCFGR_CHLEN_32BIT = 1
} SPI_I2SCFGR_CHLEN_t;

// SPI_I2SPR Enums
typedef enum {
    SPI_I2SPR_MCKOE_DISABLE = 0,
    SPI_I2SPR_MCKOE_ENABLE = 1
} SPI_I2SPR_MCKOE_t;

typedef enum {
    SPI_I2SPR_ODD_EVEN = 0,
    SPI_I2SPR_ODD_ODD = 1
} SPI_I2SPR_ODD_t;


typedef enum {
    SPI_1 = 0,
    SPI_2 = 1,
    SPI_3 = 2
}SPI_Type_t;


typedef enum {
    SPI_OK = 0,
    SPI_ERROR = 1,
    SPI_NULL_PTR = 2,
    SPI_INVALID_PARAM = 3,
    SPI_NO_DATA = 4,
    SPI_NOT_READY = 5
    
}SPI_Error_t;

typedef enum {
    SPI_MODE_MASTER = 0,
    SPI_MODE_SLAVE = 1
}SPI_Mode_t;


typedef enum {
    FIRST_RISING   = 0,
    SECOND_FALLING = 1,
    FIRST_FALLING  = 2,
    SECOND_RISING  = 3
    
}Data_latch_t;
typedef struct {

    SPI_Type_t SPIx; // SPI selection (SPI_1, SPI_2, SPI_3)
    SPI_Mode_t Mode; // SPI mode (Master or Slave)
    SPI_CR1_BIDIMODE_t BIDIMODE;
    SPI_CR1_BIDIOE_t BIDIOE;
    SPI_CR1_CRCEN_t CRCEN;
    SPI_CR1_CRCNEXT_t CRCNEXT;
    SPI_CR1_DFF_t DFF;
    SPI_CR1_RXONLY_t RXONLY;
    SPI_CR1_SSM_t SSM;
    SPI_CR1_SSI_t SSI;
    SPI_CR1_LSBFIRST_t LSBFIRST;
    SPI_CR1_BR_t BR;
    Data_latch_t Data_latch;
    SPI_CR2_TXEIE_t TXEIE;
    SPI_CR2_RXNEIE_t RXNEIE;
    SPI_CR2_ERRIE_t ERRIE;
    SPI_CR2_SSOE_t SSOE;
    SPI_CR2_TXDMAEN_t TXDMAEN;
    SPI_CR2_RXDMAEN_t RXDMAEN;

} SPI_Config_t;


SPI_Error_t SPIInit(SPI_Config_t *SPI_Config);
SPI_Error_t SPITransmit(SPI_Config_t *SPI_Config, uint16_t *Data, uint16_t Size);
SPI_Error_t SPIReceive(SPI_Config_t *SPI_Config, uint16_t *Data, uint16_t Size);


#endif // SPI_HANDMADE_H