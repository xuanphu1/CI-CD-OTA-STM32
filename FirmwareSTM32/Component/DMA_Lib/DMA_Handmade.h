#ifndef DMA_HANDMADE_H
#define DMA_HANDMADE_H

#include "stdint.h"
#include "RCC_Handmade.h"

// DMA channel register structure
typedef struct {
    volatile uint32_t DMA_CCR;      // Channel Configuration Register
    volatile uint32_t DMA_CNDTR;    // Number of Data Register
    volatile uint32_t DMA_CPAR;     // Peripheral Address Register
    volatile uint32_t DMA_CMAR;     // Memory Address Register
    volatile uint32_t RESERVED;     // Reserved
} DMA_Channel_t;

// DMA controller structure
typedef struct {
    volatile uint32_t DMA_ISR;       // Interrupt Status Register
    volatile uint32_t DMA_IFCR;      // Interrupt Flag Clear Register
    DMA_Channel_t CHANNEL[7];        // 7 DMA channels
} DMA_Handmade_t;

#define DMA1_BASE_ADDRESS 0x40020000UL
#define DMA1_HANDMADE ((volatile DMA_Handmade_t*)DMA1_BASE_ADDRESS)

// DMA channel enumeration
typedef enum {
    DMA_CHANNEL_1 = 0,
    DMA_CHANNEL_2,
    DMA_CHANNEL_3,
    DMA_CHANNEL_4,
    DMA_CHANNEL_5,
    DMA_CHANNEL_6,
    DMA_CHANNEL_7
} DMAChannel_t;

// DMA priority enumeration
typedef enum {
    DMA_LOW_PRIORITY = 0,
    DMA_MEDIUM_PRIORITY,
    DMA_HIGH_PRIORITY,
    DMA_VERY_HIGH_PRIORITY
} DMA_Priority_t;

// DMA peripheral increment enumeration
typedef enum {
    DISABLE_DMA_PINC = 0,
    ENABLE_DMA_PINC
} DMA_PeripheralInc_t;

// DMA memory increment enumeration
typedef enum {
    DISABLE_DMA_MINC = 0,
    ENABLE_DMA_MINC
} DMA_MemoryInc_t;

// DMA peripheral size enumeration
typedef enum {
    DMA_PSIZE_8BIT = 0,
    DMA_PSIZE_16BIT,
    DMA_PSIZE_32BIT
} DMA_PeripheralSize_t;

// DMA memory size enumeration
typedef enum {
    DMA_MSIZE_8BIT = 0,
    DMA_MSIZE_16BIT,
    DMA_MSIZE_32BIT
} DMA_MemorySize_t;

// DMA circular mode enumeration
typedef enum {
    DMA_CIRC_DISABLE = 0,
    DMA_CIRC_ENABLE
} DMA_CircularMode_t;

// DMA direction enumeration
typedef enum {
    DMA_DIR_PERIPH_TO_MEM = 0,
    DMA_DIR_MEM_TO_PERIPH
} DMA_Direction_t;

// DMA transfer error interrupt enumeration
typedef enum {
    DMA_TEIE_DISABLE = 0,
    DMA_TEIE_ENABLE
} DMA_TransferErrorInt_t;

// DMA half-transfer interrupt enumeration
typedef enum {
    DMA_HTIE_DISABLE = 0,
    DMA_HTIE_ENABLE
} DMA_HalfTransferInt_t;

// DMA transfer complete interrupt enumeration
typedef enum {
    DMA_TCIE_DISABLE = 0,
    DMA_TCIE_ENABLE
} DMA_TransferCompleteInt_t;

// DMA configuration structure
typedef struct {
    DMAChannel_t Channel;
    DMA_Priority_t Priority;
    DMA_PeripheralInc_t PeripheralIncrement;
    DMA_MemoryInc_t MemoryIncrement;
    DMA_PeripheralSize_t PeripheralSize;
    DMA_MemorySize_t MemorySize;
    DMA_CircularMode_t CircularMode;
    DMA_Direction_t Direction;
    DMA_TransferErrorInt_t TransferErrorInt;
    DMA_HalfTransferInt_t HalfTransferInt;
    DMA_TransferCompleteInt_t TransferCompleteInt;
    uint32_t PeripheralAddress;
    uint32_t MemoryAddress;
    uint32_t NumData;
} DMA_Config_t;

// DMA error codes
typedef enum {
    DMA_OK = 0,
    DMA_ERROR_INVALID_PARAM = 1,
    DMA_ERROR_NOT_INITIALIZED = 2
} DMA_Error_t;

// Bit manipulation macros for DMA registers
#define HM_DMA_CCR_EN_POS           (0U)
#define HM_DMA_CCR_EN_MASK          (0x1U << HM_DMA_CCR_EN_POS)

#define HM_DMA_CCR_TCIE_POS         (1U)
#define HM_DMA_CCR_TCIE_MASK        (0x1U << HM_DMA_CCR_TCIE_POS)

#define HM_DMA_CCR_HTIE_POS         (2U)
#define HM_DMA_CCR_HTIE_MASK        (0x1U << HM_DMA_CCR_HTIE_POS)

#define HM_DMA_CCR_TEIE_POS         (3U)
#define HM_DMA_CCR_TEIE_MASK        (0x1U << HM_DMA_CCR_TEIE_POS)

#define HM_DMA_CCR_DIR_POS          (4U)
#define HM_DMA_CCR_DIR_MASK         (0x1U << HM_DMA_CCR_DIR_POS)

#define HM_DMA_CCR_CIRC_POS         (5U)
#define HM_DMA_CCR_CIRC_MASK        (0x1U << HM_DMA_CCR_CIRC_POS)

#define HM_DMA_CCR_PINC_POS         (6U)
#define HM_DMA_CCR_PINC_MASK        (0x1U << HM_DMA_CCR_PINC_POS)

#define HM_DMA_CCR_MINC_POS         (7U)
#define HM_DMA_CCR_MINC_MASK        (0x1U << HM_DMA_CCR_MINC_POS)

#define HM_DMA_CCR_PSIZE_POS        (8U)
#define HM_DMA_CCR_PSIZE_MASK       (0x3U << HM_DMA_CCR_PSIZE_POS)

#define HM_DMA_CCR_MSIZE_POS        (10U)
#define HM_DMA_CCR_MSIZE_MASK       (0x3U << HM_DMA_CCR_MSIZE_POS)

#define HM_DMA_CCR_PL_POS           (12U)
#define HM_DMA_CCR_PL_MASK          (0x3U << HM_DMA_CCR_PL_POS)

#define HM_DMA_IFCR_CGIF_POS(ch)    (0U + (ch * 4U))
#define HM_DMA_IFCR_CGIF_MASK(ch)   (0xFU << HM_DMA_IFCR_CGIF_POS(ch))

// Function prototypes
DMA_Error_t DMA_Init(DMA_Config_t *dmaConfig);
DMA_Error_t DMA_Start(DMAChannel_t channel);
DMA_Error_t AddressPeripheral(DMAChannel_t channel, uint32_t address);
DMA_Error_t AddressMemory(DMAChannel_t channel, uint32_t address);

#endif // DMA_HANDMADE_H