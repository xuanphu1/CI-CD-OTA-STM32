#ifndef RCC_HANDMADE_H
#define RCC_HANDMADE_H

#include <stdint.h>
#include <stddef.h>
#include "Flash_Handmade.h"

// RCC Base Address
#define RCC_BASE_HANDMADE 0x40021000UL
#define RCC_HANDMADE ((volatile RCC_Handmade_t*)RCC_BASE_HANDMADE)


// RCC Register Structure
typedef struct {
    uint32_t RCC_CR;
    uint32_t RCC_CFGR;
    uint32_t RCC_CIR;
    uint32_t RCC_APB2RSTR;
    uint32_t RCC_APB1RSTR;
    uint32_t RCC_AHBENR;
    uint32_t RCC_APB2ENR;
    uint32_t RCC_APB1ENR;
    uint32_t RCC_BDCR;
    uint32_t RCC_CSR;
} RCC_Handmade_t;

// RCC_CR Bit Definitions and Masks
#define RCC_CR_HSION                (1U << 0)  // HSI oscillator enable
#define HM_RCC_CR_HSION_MASK        (1U << 0)
#define RCC_CR_HSIRDY               (1U << 1)  // HSI oscillator ready
#define HM_RCC_CR_HSIRDY_MASK       (1U << 1)
#define RCC_CR_HSEON                (1U << 16) // HSE oscillator enable
#define HM_RCC_CR_HSEON_MASK        (1U << 16)
#define RCC_CR_HSERDY               (1U << 17) // HSE oscillator ready
#define HM_RCC_CR_HSERDY_MASK       (1U << 17)
#define RCC_CR_PLLON                (1U << 24) // PLL enable
#define HM_RCC_CR_PLLON_MASK        (1U << 24)
#define RCC_CR_PLLRDY               (1U << 25) // PLL ready
#define HM_RCC_CR_PLLRDY_MASK       (1U << 25)

// RCC_CFGR Bit Definitions and Masks
#define RCC_CFGR_SW_POS             0           // System clock switch position
#define HM_RCC_CFGR_SW_MASK         (0x3U << 0) // System clock switch mask
#define HM_RCC_CFGR_SW_HSI          (0x0U << 0) // HSI as system clock
#define HM_RCC_CFGR_SW_HSE          (0x1U << 0) // HSE as system clock
#define HM_RCC_CFGR_SW_PLL          (0x2U << 0) // PLL as system clock
#define RCC_CFGR_SWS_POS            2           // System clock switch status position
#define HM_RCC_CFGR_SWS_MASK        (0x3U << 2) // System clock switch status mask
#define RCC_CFGR_HPRE_POS           4           // AHB prescaler position
#define HM_RCC_CFGR_HPRE_MASK       (0xFU << 4) // AHB prescaler mask
#define RCC_CFGR_PPRE1_POS          8           // APB1 prescaler position
#define HM_RCC_CFGR_PPRE1_MASK      (0x7U << 8) // APB1 prescaler mask
#define RCC_CFGR_PPRE2_POS          11          // APB2 prescaler position
#define HM_RCC_CFGR_PPRE2_MASK      (0x7U << 11) // APB2 prescaler mask
#define RCC_CFGR_ADCPRE_POS         14          // ADC prescaler position
#define HM_RCC_CFGR_ADCPRE_MASK     (0x3U << 14) // ADC prescaler mask
#define RCC_CFGR_PLLSRC             (1U << 16)  // PLL clock source
#define HM_RCC_CFGR_PLLSRC_MASK     (1U << 16)
#define RCC_CFGR_PLLMUL_POS         18          // PLL multiplication factor position
#define HM_RCC_CFGR_PLLMUL_MASK     (0xFU << 18) // PLL multiplication factor mask

// RCC_APB2ENR Bit Definitions and Masks
#define RCC_APB2ENR_AFIOEN          (1U << 0)  // Alternate Function I/O clock enable
#define HM_RCC_APB2ENR_AFIOEN_MASK  (1U << 0)
// Bit 1 is reserved (not used)
#define RCC_APB2ENR_IOPAEN          (1U << 2)  // GPIOA clock enable
#define HM_RCC_APB2ENR_IOPAEN_MASK  (1U << 2)
#define RCC_APB2ENR_IOPBEN          (1U << 3)  // GPIOB clock enable
#define HM_RCC_APB2ENR_IOPBEN_MASK  (1U << 3)
#define RCC_APB2ENR_IOPCEN          (1U << 4)  // GPIOC clock enable
#define HM_RCC_APB2ENR_IOPCEN_MASK  (1U << 4)
#define RCC_APB2ENR_IOPDEN          (1U << 5)  // GPIOD clock enable
#define HM_RCC_APB2ENR_IOPDEN_MASK  (1U << 5)
#define RCC_APB2ENR_IOPEEN          (1U << 6)  // GPIOE clock enable
#define HM_RCC_APB2ENR_IOPEEN_MASK  (1U << 6)
#define RCC_APB2ENR_IOPFEN          (1U << 7)  // GPIOF clock enable
#define HM_RCC_APB2ENR_IOPFEN_MASK  (1U << 7)
#define RCC_APB2ENR_IOPGEN          (1U << 8)  // GPIOG clock enable
#define HM_RCC_APB2ENR_IOPGEN_MASK  (1U << 8)
#define RCC_APB2ENR_ADC1EN          (1U << 9)  // ADC1 clock enable
#define HM_RCC_APB2ENR_ADC1EN_MASK  (1U << 9)
#define RCC_APB2ENR_ADC2EN          (1U << 10) // ADC2 clock enable
#define HM_RCC_APB2ENR_ADC2EN_MASK  (1U << 10)
#define RCC_APB2ENR_TIM1EN          (1U << 11) // TIM1 clock enable
#define HM_RCC_APB2ENR_TIM1EN_MASK  (1U << 11)
#define RCC_APB2ENR_SPI1EN          (1U << 12) // SPI1 clock enable
#define HM_RCC_APB2ENR_SPI1EN_MASK  (1U << 12)
#define RCC_APB2ENR_TIM8EN          (1U << 13) // TIM8 clock enable
#define HM_RCC_APB2ENR_TIM8EN_MASK  (1U << 13)
#define RCC_APB2ENR_USART1EN        (1U << 14) // USART1 clock enable
#define HM_RCC_APB2ENR_USART1EN_MASK (1U << 14)
#define RCC_APB2ENR_ADC3EN          (1U << 15) // ADC3 clock enable
#define HM_RCC_APB2ENR_ADC3EN_MASK  (1U << 15)
#define RCC_APB2ENR_TIM9EN          (1U << 19) // TIM9 clock enable
#define HM_RCC_APB2ENR_TIM9EN_MASK  (1U << 19)
#define RCC_APB2ENR_TIM10EN         (1U << 20) // TIM10 clock enable
#define HM_RCC_APB2ENR_TIM10EN_MASK (1U << 20)
#define RCC_APB2ENR_TIM11EN         (1U << 21) // TIM11 clock enable
#define HM_RCC_APB2ENR_TIM11EN_MASK (1U << 21)

// RCC_APB1ENR Bit Definitions and Masks
#define RCC_APB1ENR_TIM2EN          (1U << 0)  // TIM2 clock enable
#define HM_RCC_APB1ENR_TIM2EN_MASK  (1U << 0)
#define RCC_APB1ENR_TIM3EN          (1U << 1)  // TIM3 clock enable
#define HM_RCC_APB1ENR_TIM3EN_MASK  (1U << 1)
#define RCC_APB1ENR_TIM4EN          (1U << 2)  // TIM4 clock enable
#define HM_RCC_APB1ENR_TIM4EN_MASK  (1U << 2)
#define RCC_APB1ENR_TIM5EN          (1U << 3)  // TIM5 clock enable
#define HM_RCC_APB1ENR_TIM5EN_MASK  (1U << 3)
#define RCC_APB1ENR_TIM6EN          (1U << 4)  // TIM6 clock enable
#define HM_RCC_APB1ENR_TIM6EN_MASK  (1U << 4)
#define RCC_APB1ENR_TIM7EN          (1U << 5)  // TIM7 clock enable
#define HM_RCC_APB1ENR_TIM7EN_MASK  (1U << 5)
#define RCC_APB1ENR_TIM12EN         (1U << 6)  // TIM12 clock enable
#define HM_RCC_APB1ENR_TIM12EN_MASK (1U << 6)
#define RCC_APB1ENR_TIM13EN         (1U << 7)  // TIM13 clock enable
#define HM_RCC_APB1ENR_TIM13EN_MASK (1U << 7)
#define RCC_APB1ENR_TIM14EN         (1U << 8)  // TIM14 clock enable
#define HM_RCC_APB1ENR_TIM14EN_MASK (1U << 8)
#define RCC_APB1ENR_WWDGEN          (1U << 11) // Window Watchdog clock enable
#define HM_RCC_APB1ENR_WWDGEN_MASK  (1U << 11)
#define RCC_APB1ENR_SPI2EN          (1U << 14) // SPI2 clock enable
#define HM_RCC_APB1ENR_SPI2EN_MASK  (1U << 14)
#define RCC_APB1ENR_SPI3EN          (1U << 15) // SPI3 clock enable
#define HM_RCC_APB1ENR_SPI3EN_MASK  (1U << 15)
#define RCC_APB1ENR_USART2EN        (1U << 17) // USART2 clock enable
#define HM_RCC_APB1ENR_USART2EN_MASK (1U << 17)
#define RCC_APB1ENR_USART3EN        (1U << 18) // USART3 clock enable
#define HM_RCC_APB1ENR_USART3EN_MASK (1U << 18)
#define RCC_APB1ENR_UART4EN         (1U << 19) // UART4 clock enable
#define HM_RCC_APB1ENR_UART4EN_MASK (1U << 19)
#define RCC_APB1ENR_UART5EN         (1U << 20) // UART5 clock enable
#define HM_RCC_APB1ENR_UART5EN_MASK (1U << 20)
#define RCC_APB1ENR_I2C1EN          (1U << 21) // I2C1 clock enable
#define HM_RCC_APB1ENR_I2C1EN_MASK  (1U << 21)
#define RCC_APB1ENR_I2C2EN          (1U << 22) // I2C2 clock enable
#define HM_RCC_APB1ENR_I2C2EN_MASK  (1U << 22)
#define RCC_APB1ENR_USBEN           (1U << 23) // USB clock enable
#define HM_RCC_APB1ENR_USBEN_MASK   (1U << 23)
#define RCC_APB1ENR_CAN1EN          (1U << 25) // CAN1 clock enable
#define HM_RCC_APB1ENR_CAN1EN_MASK  (1U << 25)
#define RCC_APB1ENR_BKPEN           (1U << 27) // Backup interface clock enable
#define HM_RCC_APB1ENR_BKPEN_MASK   (1U << 27)
#define RCC_APB1ENR_PWREN           (1U << 28) // Power interface clock enable
#define HM_RCC_APB1ENR_PWREN_MASK   (1U << 28)
#define RCC_APB1ENR_DACEN           (1U << 29) // DAC clock enable
#define HM_RCC_APB1ENR_DACEN_MASK   (1U << 29)

// RCC_AHBENR Bit Definitions and Masks
#define RCC_AHBENR_DMA1EN           (1U << 0)  // DMA1 clock enable
#define HM_RCC_AHBENR_DMA1EN_MASK   (1U << 0)
#define RCC_AHBENR_DMA2EN           (1U << 1)  // DMA2 clock enable
#define HM_RCC_AHBENR_DMA2EN_MASK   (1U << 1)
#define RCC_AHBENR_SRAMEN           (1U << 2)  // SRAM clock enable
#define HM_RCC_AHBENR_SRAMEN_MASK   (1U << 2)
#define RCC_AHBENR_FLITFEN          (1U << 4)  // FLITF clock enable
#define HM_RCC_AHBENR_FLITFEN_MASK  (1U << 4)
#define RCC_AHBENR_CRCEN            (1U << 6)  // CRC clock enable
#define HM_RCC_AHBENR_CRCEN_MASK    (1U << 6)
#define RCC_AHBENR_FSMCEN           (1U << 8)  // FSMC clock enable
#define HM_RCC_AHBENR_FSMCEN_MASK   (1U << 8)
#define RCC_AHBENR_SDIOEN           (1U << 10) // SDIO clock enable
#define HM_RCC_AHBENR_SDIOEN_MASK   (1U << 10)

// Peripheral Clock Enums
typedef enum {
    AFIO_EN_CLK       = 0,  // Alternate Function I/O clock enable
    Reserved_0        = 1,  // (Không sử dụng)
    IOPA_EN_CLK       = 2,  // GPIOA clock enable
    IOPB_EN_CLK       = 3,  // GPIOB clock enable
    IOPC_EN_CLK       = 4,  // GPIOC clock enable
    IOPD_EN_CLK       = 5,  // GPIOD clock enable
    IOPE_EN_CLK       = 6,  // GPIOE clock enable
    IOPF_EN_CLK       = 7,  // GPIOF clock enable
    IOPG_EN_CLK       = 8,  // GPIOG clock enable
    ADC1_EN_CLK       = 9,  // ADC1 clock enable
    ADC2_EN_CLK       = 10, // ADC2 clock enable
    TIM1_EN_CLK       = 11, // TIM1 clock enable
    SPI1_EN_CLK       = 12, // SPI1 clock enable
    TIM8_EN_CLK       = 13, // TIM8 clock enable
    USART1_EN_CLK     = 14, // USART1 clock enable
    ADC3_EN_CLK       = 15, // ADC3 clock enable
    TIM9_EN_CLK       = 19, // TIM9 clock enable
    TIM10_EN_CLK      = 20, // TIM10 clock enable
    TIM11_EN_CLK      = 21  // TIM11 clock enable
} APB2_Peripheral_Clock;

typedef enum {
    TIM2_EN_CLK       = 0,  // TIM2 clock enable
    TIM3_EN_CLK       = 1,  // TIM3 clock enable
    TIM4_EN_CLK       = 2,  // TIM4 clock enable
    TIM5_EN_CLK       = 3,  // TIM5 clock enable
    TIM6_EN_CLK       = 4,  // TIM6 clock enable
    TIM7_EN_CLK       = 5,  // TIM7 clock enable
    TIM12_EN_CLK      = 6,  // TIM12 clock enable
    TIM13_EN_CLK      = 7,  // TIM13 clock enable
    TIM14_EN_CLK      = 8,  // TIM14 clock enable
    WWDG_EN_CLK       = 11, // Window Watchdog clock enable
    SPI2_EN_CLK       = 14, // SPI2 clock enable
    SPI3_EN_CLK       = 15, // SPI3 clock enable
    USART2_EN_CLK     = 17, // USART2 clock enable
    USART3_EN_CLK     = 18, // USART3 clock enable
    UART4_EN_CLK      = 19, // UART4 clock enable
    UART5_EN_CLK      = 20, // UART5 clock enable
    I2C1_EN_CLK       = 21, // I2C1 clock enable
    I2C2_EN_CLK       = 22, // I2C2 clock enable
    USB_EN_CLK        = 23, // USB clock enable
    CAN1_EN_CLK       = 25, // CAN1 clock enable
    BKP_EN_CLK        = 27, // Backup interface clock enable
    PWR_EN_CLK        = 28, // Power interface clock enable
    DAC_EN_CLK        = 29  // DAC clock enable
} APB1_Peripheral_Clock;

typedef enum {
    DMA1_EN_CLK       = 0,  // DMA1 clock enable
    DMA2_EN_CLK       = 1,  // DMA2 clock enable
    SRAM_EN_CLK       = 2,  // SRAM clock enable
    FLITF_EN_CLK      = 4,  // FLITF clock enable (Flash interface)
    CRC_EN_CLK        = 6,  // CRC clock enable
    FSMC_EN_CLK       = 8,  // FSMC clock enable
    SDIO_EN_CLK       = 10  // SDIO clock enable
} AHB_Peripheral_Clock;

typedef enum {
    HSI_CLOCK = 0, // High-speed internal clock
    HSE_CLOCK = 1, // High-speed external clock
} Source_Clock_t;

enum {
    DISABLE_RCC = 0,
    ENABLE_RCC = 1
};

typedef enum {
    FREQ_8MHZ    = 8000000,   // PLL x2
    FREQ_12MHZ   = 12000000,  // PLL x3
    FREQ_16MHZ   = 16000000,  // PLL x4
    FREQ_20MHZ   = 20000000,  // PLL x5
    FREQ_24MHZ   = 24000000,  // PLL x6
    FREQ_28MHZ   = 28000000,  // PLL x7
    FREQ_32MHZ   = 32000000,  // PLL x8
    FREQ_36MHZ   = 36000000,  // PLL x9
    FREQ_40MHZ   = 40000000,  // PLL x10
    FREQ_44MHZ   = 44000000,  // PLL x11
    FREQ_48MHZ   = 48000000,  // PLL x12
    FREQ_52MHZ   = 52000000,  // PLL x13
    FREQ_56MHZ   = 56000000,  // PLL x14
    FREQ_60MHZ   = 60000000,  // PLL x15
    FREQ_64MHZ   = 64000000,   // PLL x16 (Tối đa của HSI)
    FREQ_72MHZ   = 72000000   // PLL x18 (Tối đa của HSE)
} FREQ_Frequency_t;

typedef enum {
    ADC_CLOCK_DIV_2 = 0,
    ADC_CLOCK_DIV_4,
    ADC_CLOCK_DIV_6,
    ADC_CLOCK_DIV_8
} ADC_ClockPrescaler_t;

typedef enum {
    PPRE_CLOCK_DIV_1 = 0,
    PPRE_CLOCK_DIV_2 = 4,
    PPRE_CLOCK_DIV_4,
    PPRE_CLOCK_DIV_8,
    PPRE_CLOCK_DIV_16
} PPRE_Prescaler_t;

typedef enum {
    HPRE_CLOCK_DIV_1 = 0,
    HPRE_CLOCK_DIV_2 = 8,
    HPRE_CLOCK_DIV_4,
    HPRE_CLOCK_DIV_8,
    HPRE_CLOCK_DIV_16,
    HPRE_CLOCK_DIV_64,
    HPRE_CLOCK_DIV_128,
    HPRE_CLOCK_DIV_256,
    HPRE_CLOCK_DIV_512
} HPRE_Prescaler_t;

typedef struct {
    ADC_ClockPrescaler_t ADC_Prescaler;
    PPRE_Prescaler_t PPRE1_Prescaler;
    PPRE_Prescaler_t PPRE2_Prescaler;
    HPRE_Prescaler_t HPRE_Prescaler;
} RCC_ClockPrescaler_t;

typedef enum {
    AHB_Prescaler = 0,
    APB1_Prescaler,
    APB2_Prescaler,
    ADC_Prescaler
} RCC_Prescaler_t;

typedef struct {
    Source_Clock_t source_clock;
    FREQ_Frequency_t frequency;
} RCC_config_t;

typedef enum {
    RCC_OK = 0,
    RCC_NOT_OK = 1,
    RCC_ERROR_INVALID_PARAM = 2,
    RCCError_tIMEOUT = 3
} RCCError_t;

// Function Prototypes
RCCError_t init_RCC(RCC_config_t *RCC_config);
RCCError_t Select_Frequency_CLK(FREQ_Frequency_t Frequency_clk);
RCCError_t Select_Sources_Clock(Source_Clock_t Source_Clock);
RCCError_t Enable_Clock_RCC_APB2(APB2_Peripheral_Clock Peripheral_CLK);
RCCError_t Enable_Clock_RCC_APB1(APB1_Peripheral_Clock Peripheral_CLK);
RCCError_t Enable_Clock_RCC_AHB(AHB_Peripheral_Clock Peripheral_CLK);
RCCError_t Select_Prescaler_RCC(RCC_ClockPrescaler_t *Prescaler, RCC_Prescaler_t Prescaler_type);
FREQ_Frequency_t getFrequencyAPB1(void);
FREQ_Frequency_t getFrequencyAPB2(void);
FREQ_Frequency_t getFrequencyAHB(void);
FREQ_Frequency_t getFrequencyRCC(void);

#endif // RCC_HANDMADE_H