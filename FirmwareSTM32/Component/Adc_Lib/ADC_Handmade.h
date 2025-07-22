#ifndef ADC_HANDMADE_H
#define ADC_HANDMADE_H

#include "stdint.h"
#include "RCC_Handmade.h"
#include "GPIO_Handmade.h"

// ADC register structure for STM32F103
typedef struct {
    volatile uint32_t ADC_SR;
    volatile uint32_t ADC_CR1;
    volatile uint32_t ADC_CR2;
    volatile uint32_t ADC_SMPR1;
    volatile uint32_t ADC_SMPR2;
    volatile uint32_t ADC_JOFR1;
    volatile uint32_t ADC_JOFR2;
    volatile uint32_t ADC_JOFR3;
    volatile uint32_t ADC_JOFR4;
    volatile uint32_t ADC_HTR;
    volatile uint32_t ADC_LTR;
    volatile uint32_t ADC_SQR1;
    volatile uint32_t ADC_SQR2;
    volatile uint32_t ADC_SQR3;
    volatile uint32_t ADC_JSQR;
    volatile uint32_t ADC_JDR1;
    volatile uint32_t ADC_JDR2;
    volatile uint32_t ADC_JDR3;
    volatile uint32_t ADC_JDR4;
    volatile uint32_t ADC_DR;
} ADC_Handmade_t;

#define ADC1_BASE_ADDRESS 0x40012400UL
#define ADC1_HANDMADE ((volatile ADC_Handmade_t*)ADC1_BASE_ADDRESS)

// ADC channel enumeration
typedef enum {
    CUSTOM_ADC_CHANNEL_0 = 0,
    CUSTOM_ADC_CHANNEL_1,
    CUSTOM_ADC_CHANNEL_2,
    CUSTOM_ADC_CHANNEL_3,
    CUSTOM_ADC_CHANNEL_4,
    CUSTOM_ADC_CHANNEL_5,
    CUSTOM_ADC_CHANNEL_6,
    CUSTOM_ADC_CHANNEL_7,
    CUSTOM_ADC_CHANNEL_8,
    CUSTOM_ADC_CHANNEL_9,
    CUSTOM_ADC_CHANNEL_10,
    CUSTOM_ADC_CHANNEL_11,
    CUSTOM_ADC_CHANNEL_12,
    CUSTOM_ADC_CHANNEL_13,
    CUSTOM_ADC_CHANNEL_14,
    CUSTOM_ADC_CHANNEL_15,
    CUSTOM_ADC_CHANNEL_TEMP_SENSOR,
    CUSTOM_ADC_CHANNEL_VREFINT
} ADC_Channel_t;

// ADC sample time enumeration
typedef enum {
    SAMPLE_1_5_CYCLES = 0,
    SAMPLE_7_5_CYCLES,
    SAMPLE_13_5_CYCLES,
    SAMPLE_28_5_CYCLES,
    SAMPLE_41_5_CYCLES,
    SAMPLE_55_5_CYCLES,
    SAMPLE_71_5_CYCLES,
    SAMPLE_239_5_CYCLES
} ADC_SampleTime_t;

// ADC conversion mode enumeration
typedef enum {
    SINGLE_CONVERSION = 0,
    CONTINUOUS_CONVERSION
} ADC_ConversionMode_t;

// ADC scan mode enumeration
typedef enum {
    SCAN_DISABLE = 0,
    SCAN_ENABLE
} ADC_ScanMode_t;

// ADC DMA mode enumeration
typedef enum {
    DMA_DISABLE = 0,
    DMA_ENABLE
} ADC_DMA_Mode_t;

// ADC data alignment enumeration
typedef enum {
    DATAALIGN_RIGHT = 0,
    DATAALIGN_LEFT
} ADC_DataAlign_t;

// ADC external trigger enumeration
typedef enum {
    EXTERNAL_TRIGGER_DISABLE = 0,
    EXTERNAL_TRIGGER_ENABLE
} ADC_ExternalTrigger_t;

// ADC interrupt mode enumeration
typedef enum {
    INTERRUPT_DISABLE = 0,
    INTERRUPT_ENABLE
} ADC_InterruptMode_t;

// ADC clock prescaler enumeration
typedef enum {
    CLOCK_ADC_DIV_2 = 0,
    CLOCK_ADC_DIV_4,
    CLOCK_ADC_DIV_6,
    CLOCK_ADC_DIV_8
} ClockPrescaler_t;

// ADC configuration structure
typedef struct {
    ADC_ScanMode_t scan_mode;
    ADC_DMA_Mode_t dma_mode;
    ADC_ConversionMode_t conversion_mode;
    ADC_DataAlign_t data_align;
    ADC_ExternalTrigger_t external_trigger;
    ADC_InterruptMode_t interrupt_mode;
    ClockPrescaler_t clock_prescaler;
    ADC_Channel_t RegularSequence[16];
    uint8_t num_of_conversions;
    ADC_SampleTime_t sample_time;
    uint16_t Result_ADC[16];
} ADC_Config_t;

// ADC error codes
typedef enum {
    ADC_OK = 0,
    ADC_NOT_OK = 1,
    ADC_ERROR_INVALID_PARAM = 2,
    ADC_ERROR_TIMEOUT = 3,
    ADC_ERROR_NOT_INITIALIZED = 4
} ADC_Error_t;

// Bit manipulation macros for ADC registers
#define HM_ADC_CR1_SCAN_MODE_POS         (8U)
#define HM_ADC_CR1_SCAN_MODE_MASK        (0x1U << HM_ADC_CR1_SCAN_MODE_POS)

#define HM_ADC_CR2_ADON_POS              (0U)
#define HM_ADC_CR2_ADON_MASK             (0x1U << HM_ADC_CR2_ADON_POS)

#define HM_ADC_CR2_SWSTART_POS           (22U)
#define HM_ADC_CR2_SWSTART_MASK          (0x1U << HM_ADC_CR2_SWSTART_POS)

#define HM_ADC_CR2_CONT_POS              (1U)
#define HM_ADC_CR2_CONT_MASK             (0x1U << HM_ADC_CR2_CONT_POS)

#define HM_ADC_CR2_DMA_POS               (8U)
#define HM_ADC_CR2_DMA_MASK              (0x1U << HM_ADC_CR2_DMA_POS)

#define HM_ADC_CR2_ALIGN_POS             (11U)
#define HM_ADC_CR2_ALIGN_MASK            (0x1U << HM_ADC_CR2_ALIGN_POS)

#define HM_ADC_CR2_EXTERNAL_TRIGGER_POS  (20U)
#define HM_ADC_CR2_EXTERNAL_TRIGGER_MASK (0x1U << HM_ADC_CR2_EXTERNAL_TRIGGER_POS)

#define HM_ADC_CR1_EOC_INTERRUPT_POS     (5U)
#define HM_ADC_CR1_EOC_INTERRUPT_MASK    (0x1U << HM_ADC_CR1_EOC_INTERRUPT_POS)

#define HM_ADC_SQR1_NUM_CONVERSIONS_POS  (20U)
#define HM_ADC_SQR1_NUM_CONVERSIONS_MASK (0xFU << HM_ADC_SQR1_NUM_CONVERSIONS_POS)

#define HM_ADC_SQRx_CHANNEL_MASK(ch)     (0x1FU << ((ch) * 5U))
#define HM_ADC_SMPRx_SAMPLE_TIME_MASK(ch) (0x7U << ((ch) * 3U))

#define HM_ADC_SR_EOC_POS                (1U)
#define HM_ADC_SR_EOC_MASK               (0x1U << HM_ADC_SR_EOC_POS)

#define HM_ADC_DR_MASK                   (0xFFFFU)

// Function prototypes
ADC_Error_t ADC_EnableClock(ClockPrescaler_t prescaler);
ADC_Error_t ADC_Init(ADC_Config_t *adcConfig);
ADC_Error_t ADC_ReadMultiple(ADC_Config_t *adcConfig);
ADC_Error_t ADC_DMA_Start(void);

#endif // ADC_HANDMADE_H