#ifndef TIM_HANDMADE_H
#define TIM_HANDMADE_H

#include "stdint.h"
#include "RCC_Handmade.h"

// Timer register structure for STM32F103
typedef struct {
    volatile uint32_t TIM_CR1;      // 0x00 - Control Register 1
    volatile uint32_t TIM_CR2;      // 0x04 - Control Register 2
    volatile uint32_t TIM_SMCR;     // 0x08 - Slave Mode Control Register
    volatile uint32_t TIM_DIER;     // 0x0C - DMA/Interrupt Enable Register
    volatile uint32_t TIM_SR;       // 0x10 - Status Register
    volatile uint32_t TIM_EGR;      // 0x14 - Event Generation Register
    volatile uint32_t TIM_CCMR1;    // 0x18 - Capture/Compare Mode Register 1
    volatile uint32_t TIM_CCMR2;    // 0x1C - Capture/Compare Mode Register 2
    volatile uint32_t TIM_CCER;     // 0x20 - Capture/Compare Enable Register
    volatile uint32_t TIM_CNT;      // 0x24 - Counter Register
    volatile uint32_t TIM_PSC;      // 0x28 - Prescaler Register
    volatile uint32_t TIM_ARR;      // 0x2C - Auto-Reload Register
    volatile uint32_t RESERVED1;    // 0x30 - Reserved
    volatile uint32_t TIM_CCR1;     // 0x34 - Capture/Compare Register 1
    volatile uint32_t TIM_CCR2;     // 0x38 - Capture/Compare Register 2
    volatile uint32_t TIM_CCR3;     // 0x3C - Capture/Compare Register 3
    volatile uint32_t TIM_CCR4;     // 0x40 - Capture/Compare Register 4
    volatile uint32_t RESERVED2;    // 0x44 - Reserved
    volatile uint32_t TIM_DCR;      // 0x48 - DMA Control Register
    volatile uint32_t TIM_DMAR;     // 0x4C - DMA Address for full transfer
} TIM_Handmade_t;

// Base addresses for TIMx in STM32F103
#define TIM2_BASE_ADDRESS 0x40000000UL
#define TIM3_BASE_ADDRESS 0x40000400UL
#define TIM4_BASE_ADDRESS 0x40000800UL
#define TIM5_BASE_ADDRESS 0x40000C00UL

// Pointers to timer registers
#define TIM2_HANDMADE ((volatile TIM_Handmade_t*)TIM2_BASE_ADDRESS)
#define TIM3_HANDMADE ((volatile TIM_Handmade_t*)TIM3_BASE_ADDRESS)
#define TIM4_HANDMADE ((volatile TIM_Handmade_t*)TIM4_BASE_ADDRESS)
#define TIM5_HANDMADE ((volatile TIM_Handmade_t*)TIM5_BASE_ADDRESS)

// Timer selection enumeration
typedef enum {
    TIMER_2 = 0,
    TIMER_3 = 1,
    TIMER_4 = 2,
    TIMER_5 = 3
} Timer_t;

// Timer channel enumeration
typedef enum {
    CHANNEL_TIMER_1 = 0,
    CHANNEL_TIMER_2,
    CHANNEL_TIMER_3,
    CHANNEL_TIMER_4
} Channel_timer_t;

// Clock division (CKD[1:0])
typedef enum {
    Custom_CKD_NO_DIV = 0x00, // tDTS = tCK_INT
    Custom_CKD_DIV_BY_2 = 0x01, // tDTS = 2 × tCK_INT
    Custom_CKD_DIV_BY_4 = 0x02, // tDTS = 4 × tCK_INT
    Custom_CKD_INVALID = 0x03 // Reserved
} Custom_TIMx_CR1_CKD;

// Center-aligned mode selection (CMS[1:0])
typedef enum {
    Custom_CMS_EDGE = 0x00, // Edge-aligned mode
    Custom_CMS_CENTER_DOWN = 0x01, // Center-aligned mode 1 (flag set when counting down)
    Custom_CMS_CENTER_UP = 0x02, // Center-aligned mode 2 (flag set when counting up)
    Custom_CMS_CENTER_BOTH = 0x03 // Center-aligned mode 3 (flag set when counting up or down)
} Custom_TIMx_CR1_CMS;

// Direction (DIR)
typedef enum {
    Custom_DIR_INCREMENT = 0x00, // Counter used as upcounter
    Custom_DIR_DECREMENT = 0x01 // Counter used as downcounter
} Custom_TIMx_CR1_DIR;

// One-pulse mode (OPM)
typedef enum {
    Custom_OPM_CONTINUOUS = 0x00, // Counter not stopped at update event
    Custom_OPM_SINGLE = 0x01 // Counter stops at next update event
} Custom_TIMx_CR1_OPM;

// Update request source (URS)
typedef enum {
    Custom_URS_ALL_EVENTS = 0x00, // Any event generates update interrupt/DMA request
    Custom_URS_OVERFLOW_ONLY = 0x01 // Only overflow/underflow generates update interrupt/DMA request
} Custom_TIMx_CR1_URS;

// Update disable (UDIS)
typedef enum {
    Custom_UDIS_ACTIVE = 0x00, // UEV enabled
    Custom_UDIS_INACTIVE = 0x01 // UEV disabled
} Custom_TIMx_CR1_UDIS;

// Counter enable (CEN)
typedef enum {
    Custom_CEN_OFF = 0x00, // Counter disabled
    Custom_CEN_ON = 0x01 // Counter enabled
} Custom_TIMx_CR1_CEN;

// Auto-reload preload enable (ARPE)
typedef enum {
    Custom_ARPE_DIRECT = 0x00, // TIMx_ARR register is not buffered
    Custom_ARPE_BUFFERED = 0x01 // TIMx_ARR register is buffered
} Custom_TIMx_CR1_ARPE;

// TI1 selection (TI1S)
typedef enum {
    Custom_TI1S_SINGLE_CH1 = 0x00, // TIMx_CH1 pin connected to TI1 input
    Custom_TI1S_XOR_CH123 = 0x01 // TIMx_CH1, CH2, CH3 pins connected to TI1 input (XOR)
} Custom_TIMx_CR2_TI1S;

// Master mode selection (MMS[2:0])
typedef enum {
    Custom_MMS_RESET_TRIG = 0x00, // UG bit from TIMx_EGR as TRGO
    Custom_MMS_ENABLE_TRIG = 0x01, // Counter enable signal (CNT_EN) as TRGO
    Custom_MMS_UPDATE_TRIG = 0x02, // Update event as TRGO
    Custom_MMS_PULSE_TRIG = 0x03, // Compare pulse (CC1IF) as TRGO
    Custom_MMS_OC1_TRIG = 0x04, // OC1REF signal as TRGO
    Custom_MMS_OC2_TRIG = 0x05, // OC2REF signal as TRGO
    Custom_MMS_OC3_TRIG = 0x06, // OC3REF signal as TRGO
    Custom_MMS_OC4_TRIG = 0x07 // OC4REF signal as TRGO
} Custom_TIMx_CR2_MMS;

// Capture/compare DMA selection (CCDS)
typedef enum {
    Custom_CCDS_ON_CC = 0x00, // CCx DMA request sent when CCx event occurs
    Custom_CCDS_ON_UPDATE = 0x01 // CCx DMA request sent when update event occurs
} Custom_TIMx_CR2_CCDS;

// External trigger polarity (ETP)
typedef enum {
    Custom_ETP_POSITIVE = 0x00, // ETR active at high level or rising edge
    Custom_ETP_NEGATIVE = 0x01 // ETR active at low level or falling edge
} Custom_TIMx_SMCR_ETP;

// External clock enable (ECE)
typedef enum {
    Custom_ECE_OFF = 0x00, // External clock mode 2 disabled
    Custom_ECE_ON = 0x01 // External clock mode 2 enabled
} Custom_TIMx_SMCR_ECE;

// External trigger prescaler (ETPS[1:0])
typedef enum {
    Custom_ETPS_NO_SCALE = 0x00, // Prescaler OFF
    Custom_ETPS_SCALE_2 = 0x01, // ETRP frequency divided by 2
    Custom_ETPS_SCALE_4 = 0x02, // ETRP frequency divided by 4
    Custom_ETPS_SCALE_8 = 0x03 // ETRP frequency divided by 8
} Custom_TIMx_SMCR_ETPS;

// External trigger filter (ETF[3:0])
typedef enum {
    Custom_ETF_NONE = 0x00, // No filter, sampling at fDTS
    Custom_ETF_CK_INT_2 = 0x01, // fSAMPLING=fCK_INT, N=2
    Custom_ETF_CK_INT_4 = 0x02, // fSAMPLING=fCK_INT, N=4
    Custom_ETF_CK_INT_8 = 0x03, // fSAMPLING=fCK_INT, N=8
    Custom_ETF_DTS_2_6 = 0x04, // fSAMPLING=fDTS/2, N=6
    Custom_ETF_DTS_2_8 = 0x05, // fSAMPLING=fDTS/2, N=8
    Custom_ETF_DTS_4_6 = 0x06, // fSAMPLING=fDTS/4, N=6
    Custom_ETF_DTS_4_8 = 0x07, // fSAMPLING=fDTS/4, N=8
    Custom_ETF_DTS_8_6 = 0x08, // fSAMPLING=fDTS/8, N=6
    Custom_ETF_DTS_8_8 = 0x09, // fSAMPLING=fDTS/8, N=8
    Custom_ETF_DTS_16_5 = 0x0A, // fSAMPLING=fDTS/16, N=5
    Custom_ETF_DTS_16_6 = 0x0B, // fSAMPLING=fDTS/16, N=6
    Custom_ETF_DTS_16_8 = 0x0C, // fSAMPLING=fDTS/16, N=8
    Custom_ETF_DTS_32_5 = 0x0D, // fSAMPLING=fDTS/32, N=5
    Custom_ETF_DTS_32_6 = 0x0E, // fSAMPLING=fDTS/32, N=6
    Custom_ETF_DTS_32_8 = 0x0F // fSAMPLING=fDTS/32, N=8
} Custom_TIMx_SMCR_ETF;

// Master/Slave mode (MSM)
typedef enum {
    Custom_MSM_INDEPENDENT = 0x00, // No action
    Custom_MSM_SYNC_DELAYED = 0x01 // Delay TRGI effect for synchronization
} Custom_TIMx_SMCR_MSM;

// Trigger selection (TS[2:0])
typedef enum {
    Custom_TS_INT_TRIG0 = 0x00, // Internal Trigger 0
    Custom_TS_INT_TRIG1 = 0x01, // Internal Trigger 1
    Custom_TS_INT_TRIG2 = 0x02, // Internal Trigger 2
    Custom_TS_INT_TRIG3 = 0x03, // Internal Trigger 3
    Custom_TS_TI1_EDGE = 0x04, // TI1 Edge Detector
    Custom_TS_TI1_FILT = 0x05, // Filtered Timer Input 1
    Custom_TS_TI2_FILT = 0x06, // Filtered Timer Input 2
    Custom_TS_EXT_TRIG = 0x07 // External Trigger input
} Custom_TIMx_SMCR_TS;

// Slave mode selection (SMS[2:0])
typedef enum {
    Custom_SMS_OFF = 0x00, // Slave mode disabled
    Custom_SMS_ENC_MODE1 = 0x01, // Encoder mode 1
    Custom_SMS_ENC_MODE2 = 0x02, // Encoder mode 2
    Custom_SMS_ENC_MODE3 = 0x03, // Encoder mode 3
    Custom_SMS_RESET = 0x04, // Reset mode
    Custom_SMS_GATED = 0x05, // Gated mode
    Custom_SMS_TRIGGER = 0x06, // Trigger mode
    Custom_SMS_EXT_CLK = 0x07 // External Clock mode 1
} Custom_TIMx_SMCR_SMS;

// Output compare mode
typedef enum {
    TIM_OC_MODE_FROZEN     = 0x0, // Frozen
    TIM_OC_MODE_ACTIVE     = 0x1, // Set active level on match
    TIM_OC_MODE_INACTIVE   = 0x2, // Set inactive level on match
    TIM_OC_MODE_TOGGLE     = 0x3, // Toggle on match
    TIM_OC_MODE_FORCE_LOW  = 0x4, // Force low
    TIM_OC_MODE_FORCE_HIGH = 0x5, // Force high
    TIM_OC_MODE_PWM1       = 0x6, // PWM mode 1
    TIM_OC_MODE_PWM2       = 0x7  // PWM mode 2
} TIM_OutputCompareMode_t;

// Timer error codes
typedef enum {
    TIM_OK = 0,
    TIM_ERROR_INVALID_PARAM = 1,
    TIM_ERROR_NOT_INITIALIZED = 2
} TIM_Error_t;

// Bit manipulation macros for TIM registers
#define HM_TIM_CR1_CKD_POS       (8U)
#define HM_TIM_CR1_CKD_MASK      (0x3U << HM_TIM_CR1_CKD_POS)
#define HM_TIM_CR1_CMS_POS       (5U)
#define HM_TIM_CR1_CMS_MASK      (0x3U << HM_TIM_CR1_CMS_POS)
#define HM_TIM_CR1_DIR_POS       (4U)
#define HM_TIM_CR1_DIR_MASK      (0x1U << HM_TIM_CR1_DIR_POS)
#define HM_TIM_CR1_OPM_POS       (3U)
#define HM_TIM_CR1_OPM_MASK      (0x1U << HM_TIM_CR1_OPM_POS)
#define HM_TIM_CR1_URS_POS       (2U)
#define HM_TIM_CR1_URS_MASK      (0x1U << HM_TIM_CR1_URS_POS)
#define HM_TIM_CR1_UDIS_POS      (1U)
#define HM_TIM_CR1_UDIS_MASK     (0x1U << HM_TIM_CR1_UDIS_POS)
#define HM_TIM_CR1_CEN_POS       (0U)
#define HM_TIM_CR1_CEN_MASK      (0x1U << HM_TIM_CR1_CEN_POS)
#define HM_TIM_CR1_ARPE_POS      (7U)
#define HM_TIM_CR1_ARPE_MASK     (0x1U << HM_TIM_CR1_ARPE_POS)

#define HM_TIM_CR2_TI1S_POS      (7U)
#define HM_TIM_CR2_TI1S_MASK     (0x1U << HM_TIM_CR2_TI1S_POS)
#define HM_TIM_CR2_MMS_POS       (4U)
#define HM_TIM_CR2_MMS_MASK      (0x7U << HM_TIM_CR2_MMS_POS)
#define HM_TIM_CR2_CCDS_POS      (3U)
#define HM_TIM_CR2_CCDS_MASK     (0x1U << HM_TIM_CR2_CCDS_POS)

#define HM_TIM_SMCR_ETP_POS      (15U)
#define HM_TIM_SMCR_ETP_MASK     (0x1U << HM_TIM_SMCR_ETP_POS)
#define HM_TIM_SMCR_ECE_POS      (14U)
#define HM_TIM_SMCR_ECE_MASK     (0x1U << HM_TIM_SMCR_ECE_POS)
#define HM_TIM_SMCR_ETPS_POS     (12U)
#define HM_TIM_SMCR_ETPS_MASK    (0x3U << HM_TIM_SMCR_ETPS_POS)
#define HM_TIM_SMCR_ETF_POS      (8U)
#define HM_TIM_SMCR_ETF_MASK     (0xFU << HM_TIM_SMCR_ETF_POS)
#define HM_TIM_SMCR_MSM_POS      (7U)
#define HM_TIM_SMCR_MSM_MASK     (0x1U << HM_TIM_SMCR_MSM_POS)
#define HM_TIM_SMCR_TS_POS       (4U)
#define HM_TIM_SMCR_TS_MASK      (0x7U << HM_TIM_SMCR_TS_POS)
#define HM_TIM_SMCR_SMS_POS      (0U)
#define HM_TIM_SMCR_SMS_MASK     (0x7U << HM_TIM_SMCR_SMS_POS)

#define HM_TIM_CCMR1_OC1M_POS    (4U)
#define HM_TIM_CCMR1_OC1M_MASK   (0x7U << HM_TIM_CCMR1_OC1M_POS)
#define HM_TIM_CCMR1_OC2M_POS    (12U)
#define HM_TIM_CCMR1_OC2M_MASK   (0x7U << HM_TIM_CCMR1_OC2M_POS)
#define HM_TIM_CCMR2_OC3M_POS    (4U)
#define HM_TIM_CCMR2_OC3M_MASK   (0x7U << HM_TIM_CCMR2_OC3M_POS)
#define HM_TIM_CCMR2_OC4M_POS    (12U)
#define HM_TIM_CCMR2_OC4M_MASK   (0x7U << HM_TIM_CCMR2_OC4M_POS)

#define HM_TIM_CCER_CC1E_POS     (0U)
#define HM_TIM_CCER_CC1E_MASK    (0x1U << HM_TIM_CCER_CC1E_POS)
#define HM_TIM_CCER_CC2E_POS     (4U)
#define HM_TIM_CCER_CC2E_MASK    (0x1U << HM_TIM_CCER_CC2E_POS)
#define HM_TIM_CCER_CC3E_POS     (8U)
#define HM_TIM_CCER_CC3E_MASK    (0x1U << HM_TIM_CCER_CC3E_POS)
#define HM_TIM_CCER_CC4E_POS     (12U)
#define HM_TIM_CCER_CC4E_MASK    (0x1U << HM_TIM_CCER_CC4E_POS)

// Timer configuration structure
typedef struct {
    Timer_t Timer; // Timer selection
    // TIMx_CR1 fields
    Custom_TIMx_CR1_CKD clockDivision; // Clock division (CKD)
    Custom_TIMx_CR1_CMS aligned_mode;  // Center-aligned mode (CMS)
    Custom_TIMx_CR1_DIR Direction_count; // Counting direction (DIR)
    Custom_TIMx_CR1_OPM onePulseMode;  // One-pulse mode (OPM)
    Custom_TIMx_CR1_URS updateSource;  // Update request source (URS)
    Custom_TIMx_CR1_UDIS updateDisable; // Update disable (UDIS)
    Custom_TIMx_CR1_CEN counterEnable; // Counter enable (CEN)
    Custom_TIMx_CR1_ARPE autoReloadPreload; // Auto-reload preload (ARPE)
    // TIMx_CR2 fields
    Custom_TIMx_CR2_TI1S ti1Selection; // TI1 selection (TI1S)
    Custom_TIMx_CR2_MMS masterMode;    // Master mode (MMS)
    Custom_TIMx_CR2_CCDS dmaSelection; // Capture/compare DMA selection (CCDS)
    // TIMx_SMCR fields
    Custom_TIMx_SMCR_ETP extTriggerPolarity; // External trigger polarity (ETP)
    Custom_TIMx_SMCR_ECE extClockEnable;     // External clock enable (ECE)
    Custom_TIMx_SMCR_ETPS extTriggerPrescaler; // External trigger prescaler (ETPS)
    Custom_TIMx_SMCR_ETF extTriggerFilter;    // External trigger filter (ETF)
    Custom_TIMx_SMCR_MSM masterSlaveMode;     // Master/Slave mode (MSM)
    Custom_TIMx_SMCR_TS triggerSelection;     // Trigger selection (TS)
    Custom_TIMx_SMCR_SMS slaveMode;           // Slave mode selection (SMS)
    uint32_t DesiredFrequency; // Desired timer frequency
    uint16_t ValueAutoReload; // Auto-reload value
    uint8_t DutyCycle; // PWM duty cycle
    uint16_t ValueCount; // Initial counter value
} TIM_Config_t;

// Function prototypes
TIM_Error_t InitTimer(TIM_Config_t *TimerConfig);
TIM_Error_t StartPWMNormal(Timer_t timer, Channel_timer_t channel);
TIM_Error_t SetDutyCycle(Timer_t timer, Channel_timer_t channel, uint8_t dutyCycle);

#endif // TIM_HANDMADE_H