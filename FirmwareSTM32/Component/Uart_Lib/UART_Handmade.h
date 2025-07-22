#ifndef UART_HANDMADE_H
#define UART_HANDMADE_H
#include "stdint.h"
#include "RCC_Handmade.h"
#include "GPIO_Handmade.h"
#include "NVIC_Handmade.h"

// Cấu trúc ánh xạ thanh ghi UART (USART)
typedef struct {
    volatile uint32_t UART_SR;   // 0x00 - Status Register (SR)
    volatile uint32_t UART_DR;   // 0x04 - Data Register (DR)
    volatile uint32_t UART_BRR;  // 0x08 - Baud Rate Register (BRR)
    volatile uint32_t UART_CR1;  // 0x0C - Control Register 1 (CR1)
    volatile uint32_t UART_CR2;  // 0x10 - Control Register 2 (CR2)
    volatile uint32_t UART_CR3;  // 0x14 - Control Register 3 (CR3)
    volatile uint32_t UART_GTPR; // 0x18 - Guard Time and Prescaler Register (GTPR)
} UART_Handmade_t;

// Base address của các USART trên STM32F103
#define USART1_BASE_ADDRESS  0x40013800UL
#define USART2_BASE_ADDRESS  0x40004400UL
#define USART3_BASE_ADDRESS  0x40004800UL

// Con trỏ ánh xạ đến thanh ghi của từng USART
#define USART1_HANDMADE  ((volatile UART_Handmade_t*)USART1_BASE_ADDRESS)
#define USART2_HANDMADE  ((volatile UART_Handmade_t*)USART2_BASE_ADDRESS)
#define USART3_HANDMADE  ((volatile UART_Handmade_t*)USART3_BASE_ADDRESS)

// UART_SR Bit Definitions and Masks
#define UART_SR_CTS_POS             9
#define HM_UART_SR_CTS_MASK         (1U << 9)

#define UART_SR_LBD_POS             8
#define HM_UART_SR_LBD_MASK         (1U << 8)

#define UART_SR_TXE_POS             7
#define HM_UART_SR_TXE_MASK         (1U << 7)

#define UART_SR_TC_POS              6
#define HM_UART_SR_TC_MASK          (1U << 6)

#define UART_SR_RXNE_POS            5
#define HM_UART_SR_RXNE_MASK        (1U << 5)

#define UART_SR_IDLE_POS            4
#define HM_UART_SR_IDLE_MASK        (1U << 4)

#define UART_SR_ORE_POS             3
#define HM_UART_SR_ORE_MASK         (1U << 3)

#define UART_SR_NE_POS              2
#define HM_UART_SR_NE_MASK          (1U << 2)

#define UART_SR_FE_POS              1
#define HM_UART_SR_FE_MASK          (1U << 1)

#define UART_SR_PE_POS              0
#define HM_UART_SR_PE_MASK          (1U << 0)

// UART_DR Bit Definitions and Masks
#define UART_DR_DR_POS              0
#define HM_UART_DR_DR_MASK          (0x1FFU << 0) // 9-bit data

// UART_BRR Bit Definitions and Masks
#define UART_BRR_DIV_MANTISSA_POS   4
#define HM_UART_BRR_DIV_MANTISSA_MASK (0xFFFU << 4)

#define UART_BRR_DIV_FRACTION_POS   0
#define HM_UART_BRR_DIV_FRACTION_MASK (0xFU << 0)

// UART_CR1 Bit Definitions and Masks
#define UART_CR1_UE_POS             13
#define HM_UART_CR1_UE_MASK         (1U << 13)

#define UART_CR1_M_POS              12
#define HM_UART_CR1_M_MASK          (1U << 12)

#define UART_CR1_WAKE_POS           11
#define HM_UART_CR1_WAKE_MASK       (1U << 11)

#define UART_CR1_PCE_POS            10
#define HM_UART_CR1_PCE_MASK        (1U << 10)

#define UART_CR1_PS_POS             9
#define HM_UART_CR1_PS_MASK         (1U << 9)

#define UART_CR1_PEIE_POS           8
#define HM_UART_CR1_PEIE_MASK       (1U << 8)

#define UART_CR1_TXEIE_POS          7
#define HM_UART_CR1_TXEIE_MASK      (1U << 7)

#define UART_CR1_TCIE_POS           6
#define HM_UART_CR1_TCIE_MASK       (1U << 6)

#define UART_CR1_RXNEIE_POS         5
#define HM_UART_CR1_RXNEIE_MASK     (1U << 5)

#define UART_CR1_IDLEIE_POS         4
#define HM_UART_CR1_IDLEIE_MASK     (1U << 4)

#define UART_CR1_TE_POS             3
#define HM_UART_CR1_TE_MASK         (1U << 3)

#define UART_CR1_RE_POS             2
#define HM_UART_CR1_RE_MASK         (1U << 2)

#define UART_CR1_RWU_POS            1
#define HM_UART_CR1_RWU_MASK        (1U << 1)

#define UART_CR1_SBK_POS            0
#define HM_UART_CR1_SBK_MASK        (1U << 0)

// UART_CR2 Bit Definitions and Masks
#define UART_CR2_LINEN_POS          14
#define HM_UART_CR2_LINEN_MASK      (1U << 14)

#define UART_CR2_STOP_POS           12
#define HM_UART_CR2_STOP_MASK       (0x3U << 12)

#define UART_CR2_CLKEN_POS          11
#define HM_UART_CR2_CLKEN_MASK      (1U << 11)

#define UART_CR2_CPOL_POS           10
#define HM_UART_CR2_CPOL_MASK       (1U << 10)

#define UART_CR2_CPHA_POS           9
#define HM_UART_CR2_CPHA_MASK       (1U << 9)

#define UART_CR2_LBCL_POS           8
#define HM_UART_CR2_LBCL_MASK       (1U << 8)

#define UART_CR2_LBDIE_POS          6
#define HM_UART_CR2_LBDIE_MASK      (1U << 6)

#define UART_CR2_LBDL_POS           5
#define HM_UART_CR2_LBDL_MASK       (1U << 5)

#define UART_CR2_ADD_POS            0
#define HM_UART_CR2_ADD_MASK        (0xFU << 0)

// UART_CR3 Bit Definitions and Masks
#define UART_CR3_CTSIE_POS          10
#define HM_UART_CR3_CTSIE_MASK      (1U << 10)

#define UART_CR3_CTSE_POS           9
#define HM_UART_CR3_CTSE_MASK       (1U << 9)

#define UART_CR3_RTSE_POS           8
#define HM_UART_CR3_RTSE_MASK       (1U << 8)

#define UART_CR3_DMAT_POS           7
#define HM_UART_CR3_DMAT_MASK       (1U << 7)

#define UART_CR3_DMAR_POS           6
#define HM_UART_CR3_DMAR_MASK       (1U << 6)

#define UART_CR3_SCEN_POS           5
#define HM_UART_CR3_SCEN_MASK       (1U << 5)

#define UART_CR3_NACK_POS           4
#define HM_UART_CR3_NACK_MASK       (1U << 4)

#define UART_CR3_HDSEL_POS          3
#define HM_UART_CR3_HDSEL_MASK      (1U << 3)

#define UART_CR3_IRLP_POS           2
#define HM_UART_CR3_IRLP_MASK       (1U << 2)

#define UART_CR3_IREN_POS           1
#define HM_UART_CR3_IREN_MASK       (1U << 1)

#define UART_CR3_EIE_POS            0
#define HM_UART_CR3_EIE_MASK        (1U << 0)

// UART_GTPR Bit Definitions and Masks
#define UART_GTPR_GT_POS            8
#define HM_UART_GTPR_GT_MASK        (0xFFU << 8)

#define UART_GTPR_PSC_POS           0
#define HM_UART_GTPR_PSC_MASK       (0xFFU << 0)

typedef enum {
    UART_1 = 0,
    UART_2,
    UART_3
} UART_Type_t;

typedef enum {
    Custom_Baud_300 = 300,
    Custom_Baud_600 = 600,
    Custom_Baud_1200 = 1200,
    Custom_Baud_2400 = 2400,
    Custom_Baud_4800 = 4800,
    Custom_Baud_9600 = 9600,
    Custom_Baud_14400 = 14400,
    Custom_Baud_19200 = 19200,
    Custom_Baud_38400 = 38400,
    Custom_Baud_57600 = 57600,
    Custom_Baud_115200 = 115200,
    Custom_Baud_230400 = 230400,
    Custom_Baud_460800 = 460800,
    Custom_Baud_921600 = 921600
} Custom_UART_BaudRate;

// CTS flag (Bit 9)
typedef enum {
    Custom_CTS_NO_CHANGE = 0x00,
    Custom_CTS_CHANGED = 0x01
} Custom_USART_SR_CTS;

// LIN break detection flag (Bit 8)
typedef enum {
    Custom_LBD_NO_BREAK = 0x00,
    Custom_LBD_BREAK = 0x01
} Custom_USART_SR_LBD;

// Transmit data register empty (Bit 7)
typedef enum {
    Custom_TXE_NOT_EMPTY = 0x00,
    Custom_TXE_EMPTY = 0x01
} Custom_USART_SR_TXE;

// Transmission complete (Bit 6)
typedef enum {
    Custom_TC_NOT_COMPLETE = 0x00,
    Custom_TC_COMPLETE = 0x01
} Custom_USART_SR_TC;

// Read data register not empty (Bit 5)
typedef enum {
    Custom_RXNE_EMPTY = 0x00,
    Custom_RXNE_NOT_EMPTY = 0x01
} Custom_USART_SR_RXNE;

// IDLE line detected (Bit 4)
typedef enum {
    Custom_IDLE_NOT_DETECTED = 0x00,
    Custom_IDLE_DETECTED = 0x01
} Custom_USART_SR_IDLE;

// Overrun error (Bit 3)
typedef enum {
    Custom_ORE_NO_ERROR = 0x00,
    Custom_ORE_ERROR = 0x01
} Custom_USART_SR_ORE;

// Noise error flag (Bit 2)
typedef enum {
    Custom_NE_NO_NOISE = 0x00,
    Custom_NE_NOISE = 0x01
} Custom_USART_SR_NE;

// Framing error (Bit 1)
typedef enum {
    Custom_FE_NO_ERROR = 0x00,
    Custom_FE_ERROR = 0x01
} Custom_USART_SR_FE;

// Parity error (Bit 0)
typedef enum {
    Custom_PE_NO_ERROR = 0x00,
    Custom_PE_ERROR = 0x01
} Custom_USART_SR_PE;

// Prescaler value for USART_GTPR (PSC[7:0])
typedef enum {
    Custom_PSC_DIV_1 = 0x01,
    Custom_PSC_DIV_2 = 0x02,
    Custom_PSC_DIV_4 = 0x04,
    Custom_PSC_DIV_6 = 0x06,
    Custom_PSC_DIV_8 = 0x08,
    Custom_PSC_DIV_10 = 0x0A,
    Custom_PSC_DIV_12 = 0x0C,
    Custom_PSC_DIV_16 = 0x10,
    Custom_PSC_DIV_20 = 0x14
} Custom_USART_GTPR_PSC;

// Parameter of CR1 register
// USART enable (UE)
typedef enum {
    Custom_UE_DISABLE = 0x00,
    Custom_UE_ENABLE = 0x01
} Custom_USART_CR1_UE;

// Word length (M)
typedef enum {
    Custom_M_8BIT = 0x00,
    Custom_M_9BIT = 0x01
} Custom_USART_CR1_M;

// Wakeup method (WAKE)
typedef enum {
    Custom_WAKE_IDLE = 0x00,
    Custom_WAKE_ADDRESS = 0x01
} Custom_USART_CR1_WAKE;

// Parity control enable (PCE)
typedef enum {
    Custom_PCE_DISABLE = 0x00,
    Custom_PCE_ENABLE = 0x01
} Custom_USART_CR1_PCE;

// Parity selection (PS)
typedef enum {
    Custom_PS_EVEN = 0x00,
    Custom_PS_ODD = 0x01
} Custom_USART_CR1_PS;

// Interrupt enables (PEIE, TXEIE, TCIE, RXNEIE, IDLEIE)
typedef enum {
    Custom_INT_DISABLE = 0x00,
    Custom_INT_ENABLE = 0x01
} Custom_USART_CR1_INT;

// Transmitter enable (TE)
typedef enum {
    Custom_TE_DISABLE = 0x00,
    Custom_TE_ENABLE = 0x01
} Custom_USART_CR1_TE;

// Receiver enable (RE)
typedef enum {
    Custom_RE_DISABLE = 0x00,
    Custom_RE_ENABLE = 0x01
} Custom_USART_CR1_RE;

// Receiver wakeup (RWU)
typedef enum {
    Custom_RWU_ACTIVE = 0x00,
    Custom_RWU_MUTE = 0x01
} Custom_USART_CR1_RWU;

// Send break (SBK)
typedef enum {
    Custom_SBK_NO_BREAK = 0x00,
    Custom_SBK_BREAK = 0x01
} Custom_USART_CR1_SBK;

// Parameter of CR2 register
// LIN mode enable (LINEN)
typedef enum {
    Custom_LINEN_DISABLE = 0x00,
    Custom_LINEN_ENABLE = 0x01
} Custom_USART_CR2_LINEN;

// Stop bits (STOP[1:0])
typedef enum {
    Custom_STOP_1 = 0x00,
    Custom_STOP_0_5 = 0x01,
    Custom_STOP_2 = 0x02,
    Custom_STOP_1_5 = 0x03
} Custom_USART_CR2_STOP;

// Clock enable (CLKEN)
typedef enum {
    Custom_CLKEN_DISABLE = 0x00,
    Custom_CLKEN_ENABLE = 0x01
} Custom_USART_CR2_CLKEN;

// Clock polarity (CPOL)
typedef enum {
    Custom_CPOL_LOW = 0x00,
    Custom_CPOL_HIGH = 0x01
} Custom_USART_CR2_CPOL;

// Clock phase (CPHA)
typedef enum {
    Custom_CPHA_FIRST = 0x00,
    Custom_CPHA_SECOND = 0x01
} Custom_USART_CR2_CPHA;

// Last bit clock pulse (LBCL)
typedef enum {
    Custom_LBCL_NO_PULSE = 0x00,
    Custom_LBCL_PULSE = 0x01
} Custom_USART_CR2_LBCL;

// LIN break detection interrupt enable (LBDIE)
typedef enum {
    Custom_LBDIE_DISABLE = 0x00,
    Custom_LBDIE_ENABLE = 0x01
} Custom_USART_CR2_LBDIE;

// LIN break detection length (LBDL)
typedef enum {
    Custom_LBDL_10BIT = 0x00,
    Custom_LBDL_11BIT = 0x01
} Custom_USART_CR2_LBDL;

// Parameter of CR3 register
// CTS interrupt enable (CTSIE)
typedef enum {
    Custom_CTSIE_DISABLE = 0x00,
    Custom_CTSIE_ENABLE = 0x01
} Custom_USART_CR3_CTSIE;

// CTS enable (CTSE)
typedef enum {
    Custom_CTSE_DISABLE = 0x00,
    Custom_CTSE_ENABLE = 0x01
} Custom_USART_CR3_CTSE;

// RTS enable (RTSE)
typedef enum {
    Custom_RTSE_DISABLE = 0x00,
    Custom_RTSE_ENABLE = 0x01
} Custom_USART_CR3_RTSE;

// DMA enable transmitter (DMAT)
typedef enum {
    Custom_DMAT_DISABLE = 0x00,
    Custom_DMAT_ENABLE = 0x01
} Custom_USART_CR3_DMAT;

// DMA enable receiver (DMAR)
typedef enum {
    Custom_DMAR_DISABLE = 0x00,
    Custom_DMAR_ENABLE = 0x01
} Custom_USART_CR3_DMAR;

// Smartcard mode enable (SCEN)
typedef enum {
    Custom_SCEN_DISABLE = 0x00,
    Custom_SCEN_ENABLE = 0x01
} Custom_USART_CR3_SCEN;

// Smartcard NACK enable (NACK)
typedef enum {
    Custom_NACK_DISABLE = 0x00,
    Custom_NACK_ENABLE = 0x01
} Custom_USART_CR3_NACK;

// Half-duplex selection (HDSEL)
typedef enum {
    Custom_HDSEL_DISABLE = 0x00,
    Custom_HDSEL_ENABLE = 0x01
} Custom_USART_CR3_HDSEL;

// IrDA low-power (IRLP)
typedef enum {
    Custom_IRLP_NORMAL = 0x00,
    Custom_IRLP_LOW_POWER = 0x01
} Custom_USART_CR3_IRLP;

// IrDA mode enable (IREN)
typedef enum {
    Custom_IREN_DISABLE = 0x00,
    Custom_IREN_ENABLE = 0x01
} Custom_USART_CR3_IREN;

// Error interrupt enable (EIE)
typedef enum {
    Custom_EIE_DISABLE = 0x00,
    Custom_EIE_ENABLE = 0x01
} Custom_USART_CR3_EIE;

typedef enum {
    UART_OK = 0,
    UART_ERROR = 1,
    UART_NULL_PTR = 2,
    UART_INVALID_PARAM = 3,
    UART_NO_DATA,
    UART_NOT_READY
} Error_UART_t;

typedef struct {
    UART_Type_t USARTx;

    // USART_CR1
    Custom_USART_CR1_UE usartEnable;
    Custom_USART_CR1_M wordLength;
    Custom_USART_CR1_WAKE wakeupMethod;
    Custom_USART_CR1_PCE parityControl;
    Custom_USART_CR1_PS paritySelection;
    Custom_USART_CR1_INT peInterrupt;
    Custom_USART_CR1_INT txeInterrupt;
    Custom_USART_CR1_INT tcInterrupt;
    Custom_USART_CR1_INT rxneInterrupt;
    Custom_USART_CR1_INT idleInterrupt;
    Custom_USART_CR1_TE transmitterEnable;
    Custom_USART_CR1_RE receiverEnable;
    Custom_USART_CR1_RWU receiverWakeup;
    Custom_USART_CR1_SBK sendBreak;

    // USART_CR2
    Custom_USART_CR2_LINEN linMode;
    Custom_USART_CR2_STOP stopBits;
    Custom_USART_CR2_CLKEN clockEnable;
    Custom_USART_CR2_CPOL clockPolarity;
    Custom_USART_CR2_CPHA clockPhase;
    Custom_USART_CR2_LBCL lastBitClock;
    Custom_USART_CR2_LBDIE linBreakInterrupt;
    Custom_USART_CR2_LBDL linBreakLength;
    uint8_t nodeAddress;

    // USART_CR3
    Custom_USART_CR3_CTSIE ctsInterrupt;
    Custom_USART_CR3_CTSE ctsEnable;
    Custom_USART_CR3_RTSE rtsEnable;
    Custom_USART_CR3_DMAT dmaTransmitter;
    Custom_USART_CR3_DMAR dmaReceiver;
    Custom_USART_CR3_SCEN smartcardMode;
    Custom_USART_CR3_NACK smartcardNack;
    Custom_USART_CR3_HDSEL halfDuplex;
    Custom_USART_CR3_IRLP irdaLowPower;
    Custom_USART_CR3_IREN irdaMode;
    Custom_USART_CR3_EIE errorInterrupt;

    // USART_BRR
    Custom_UART_BaudRate baudUART;

    // USART_GTPR
    uint8_t guardTime;
    Custom_USART_GTPR_PSC prescalerValue;

    // USART_SR
    Custom_USART_SR_CTS ctsStatus;
    Custom_USART_SR_LBD linBreakStatus;
    Custom_USART_SR_TXE transmitEmpty;
    Custom_USART_SR_TC transmitComplete;
    Custom_USART_SR_RXNE receiveNotEmpty;
    Custom_USART_SR_IDLE idleDetected;
    Custom_USART_SR_ORE overrunError;
    Custom_USART_SR_NE noiseError;
    Custom_USART_SR_FE framingError;
    Custom_USART_SR_PE parityError;
} USART_Config_t;

Error_UART_t UARTInit(USART_Config_t *uartConfig);
Error_UART_t TransmitDataUART(UART_Type_t UARTx, uint8_t *Data, uint8_t lengthData);
Error_UART_t ReceiveDataUART(UART_Type_t UARTx, uint8_t *Data, uint8_t lengthData);
Error_UART_t EnableInterrupt_RX_UARTx(UART_Type_t uartx);
Error_UART_t ReceiveDataUART_IT(UART_Type_t uartx, uint8_t *Buffer, uint8_t length);
void interruptEnable(UART_Type_t uartx);
void interruptDisable(UART_Type_t uartx);

#endif // UART_HANDMADE_H