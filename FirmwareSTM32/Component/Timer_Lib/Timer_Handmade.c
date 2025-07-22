#include "Timer_Handmade.h"

static volatile TIM_Handmade_t *TIMx[4] = { TIM2_HANDMADE, TIM3_HANDMADE, TIM4_HANDMADE, TIM5_HANDMADE };

/**
 * @brief Calculate prescaler value based on desired frequency
 * @param RCC_Clock: Input clock frequency (Hz)
 * @param Desired_Timer_Freq: Desired timer frequency (Hz)
 * @return uint32_t: Prescaler value or 0xFFFF if invalid
 */
static uint32_t calculateFrequency(uint32_t RCC_Clock, uint32_t Desired_Timer_Freq) {
    if (Desired_Timer_Freq == 0 || Desired_Timer_Freq > RCC_Clock) {
        return 0xFFFF;
    }
    return ((RCC_Clock / Desired_Timer_Freq) - 1);
}

/**
 * @brief Calculate duty cycle value based on auto-reload value
 * @param AutoReload: Auto-reload value
 * @param DutyCycle: Duty cycle percentage (0-100)
 * @return uint32_t: Calculated compare value
 */
static uint32_t calculateDutyCycle(uint32_t AutoReload, uint8_t DutyCycle) {
    if (DutyCycle > 100) {
        return AutoReload;
    }
    return ((AutoReload * DutyCycle) / 100);
}

/**
 * @brief Initialize timer with user configuration
 * @param TimerConfig: Pointer to timer configuration structure
 * @return TIM_Error_t: Status of the operation
 */
TIM_Error_t InitTimer(TIM_Config_t *TimerConfig) {
    if (TimerConfig == NULL ||
        TimerConfig->Timer > TIMER_5 ||
        TimerConfig->clockDivision > Custom_CKD_DIV_BY_4 ||
        TimerConfig->aligned_mode > Custom_CMS_CENTER_BOTH ||
        TimerConfig->Direction_count > Custom_DIR_DECREMENT ||
        TimerConfig->onePulseMode > Custom_OPM_SINGLE ||
        TimerConfig->updateSource > Custom_URS_OVERFLOW_ONLY ||
        TimerConfig->updateDisable > Custom_UDIS_INACTIVE ||
        TimerConfig->counterEnable > Custom_CEN_ON ||
        TimerConfig->autoReloadPreload > Custom_ARPE_BUFFERED ||
        TimerConfig->ti1Selection > Custom_TI1S_XOR_CH123 ||
        TimerConfig->masterMode > Custom_MMS_OC4_TRIG ||
        TimerConfig->dmaSelection > Custom_CCDS_ON_UPDATE ||
        TimerConfig->extTriggerPolarity > Custom_ETP_NEGATIVE ||
        TimerConfig->extClockEnable > Custom_ECE_ON ||
        TimerConfig->extTriggerPrescaler > Custom_ETPS_SCALE_8 ||
        TimerConfig->extTriggerFilter > Custom_ETF_DTS_32_8 ||
        TimerConfig->masterSlaveMode > Custom_MSM_SYNC_DELAYED ||
        TimerConfig->triggerSelection > Custom_TS_EXT_TRIG ||
        TimerConfig->slaveMode > Custom_SMS_EXT_CLK ||
        TimerConfig->DesiredFrequency == 0 ||
        TimerConfig->ValueAutoReload == 0 ||
        TimerConfig->DutyCycle > 100) {
        return TIM_ERROR_INVALID_PARAM;
    }

    // Enable clock for the selected timer
    switch (TimerConfig->Timer) {
        case TIMER_2: Enable_Clock_RCC_APB1(TIM2_EN_CLK); break;
        case TIMER_3: Enable_Clock_RCC_APB1(TIM3_EN_CLK); break;
        case TIMER_4: Enable_Clock_RCC_APB1(TIM4_EN_CLK); break;
        case TIMER_5: Enable_Clock_RCC_APB1(TIM5_EN_CLK); break;
        default: return TIM_ERROR_INVALID_PARAM;
    }

    volatile TIM_Handmade_t *TIMER = TIMx[TimerConfig->Timer];

    // Configure prescaler
    uint32_t apb1_freq = getFrequencyAPB1();
    uint32_t timer_clock = ((apb1_freq < FREQ_36MHZ) && (getFrequencyRCC() != FREQ_36MHZ)) ? apb1_freq * 2 : apb1_freq;
    uint32_t prescaler = calculateFrequency(timer_clock, TimerConfig->DesiredFrequency);
    if (prescaler > 0xFFFF) {
        return TIM_ERROR_INVALID_PARAM;
    }
    TIMER->TIM_PSC = prescaler;

    // Configure auto-reload and duty cycle
    TIMER->TIM_ARR = TimerConfig->ValueAutoReload;
    TIMER->TIM_CCR1 = calculateDutyCycle(TimerConfig->ValueAutoReload, TimerConfig->DutyCycle);

    // Configure initial counter value
    TIMER->TIM_CNT = TimerConfig->ValueCount;

    // Configure TIM_CR1
    TIMER->TIM_CR1 = 0;
    TIMER->TIM_CR1 |= (TimerConfig->clockDivision << HM_TIM_CR1_CKD_POS);
    TIMER->TIM_CR1 |= (TimerConfig->aligned_mode << HM_TIM_CR1_CMS_POS);
    TIMER->TIM_CR1 |= (TimerConfig->Direction_count << HM_TIM_CR1_DIR_POS);
    TIMER->TIM_CR1 |= (TimerConfig->onePulseMode << HM_TIM_CR1_OPM_POS);
    TIMER->TIM_CR1 |= (TimerConfig->updateSource << HM_TIM_CR1_URS_POS);
    TIMER->TIM_CR1 |= (TimerConfig->updateDisable << HM_TIM_CR1_UDIS_POS);
    TIMER->TIM_CR1 |= (TimerConfig->counterEnable << HM_TIM_CR1_CEN_POS);
    TIMER->TIM_CR1 |= (TimerConfig->autoReloadPreload << HM_TIM_CR1_ARPE_POS);

    // Configure TIM_CR2
    TIMER->TIM_CR2 = 0;
    TIMER->TIM_CR2 |= (TimerConfig->ti1Selection << HM_TIM_CR2_TI1S_POS);
    TIMER->TIM_CR2 |= (TimerConfig->masterMode << HM_TIM_CR2_MMS_POS);
    TIMER->TIM_CR2 |= (TimerConfig->dmaSelection << HM_TIM_CR2_CCDS_POS);

    // Configure TIM_SMCR
    TIMER->TIM_SMCR = 0;
    TIMER->TIM_SMCR |= (TimerConfig->extTriggerPolarity << HM_TIM_SMCR_ETP_POS);
    TIMER->TIM_SMCR |= (TimerConfig->extClockEnable << HM_TIM_SMCR_ECE_POS);
    TIMER->TIM_SMCR |= (TimerConfig->extTriggerPrescaler << HM_TIM_SMCR_ETPS_POS);
    TIMER->TIM_SMCR |= (TimerConfig->extTriggerFilter << HM_TIM_SMCR_ETF_POS);
    TIMER->TIM_SMCR |= (TimerConfig->masterSlaveMode << HM_TIM_SMCR_MSM_POS);
    TIMER->TIM_SMCR |= (TimerConfig->triggerSelection << HM_TIM_SMCR_TS_POS);
    TIMER->TIM_SMCR |= (TimerConfig->slaveMode << HM_TIM_SMCR_SMS_POS);

    return TIM_OK;
}

/**
 * @brief Start PWM output on a specific timer channel
 * @param timer: Timer selection (TIMER_2 to TIMER_5)
 * @param channel: Channel selection (CHANNEL_TIMER_1 to CHANNEL_TIMER_4)
 * @return TIM_Error_t: Status of the operation
 */
TIM_Error_t StartPWMNormal(Timer_t timer, Channel_timer_t channel) {
    if (timer > TIMER_5 || channel > CHANNEL_TIMER_4) {
        return TIM_ERROR_INVALID_PARAM;
    }

    volatile TIM_Handmade_t *TIMER = TIMx[timer];

    if (!(TIMER->TIM_CR1 & HM_TIM_CR1_CEN_MASK)) {
        return TIM_ERROR_NOT_INITIALIZED;
    }

    switch (channel) {
        case CHANNEL_TIMER_1:
            TIMER->TIM_CCMR1 &= ~HM_TIM_CCMR1_OC1M_MASK;
            TIMER->TIM_CCMR1 |= (TIM_OC_MODE_PWM1 << HM_TIM_CCMR1_OC1M_POS);
            TIMER->TIM_CCER |= HM_TIM_CCER_CC1E_MASK;
            break;
        case CHANNEL_TIMER_2:
            TIMER->TIM_CCMR1 &= ~HM_TIM_CCMR1_OC2M_MASK;
            TIMER->TIM_CCMR1 |= (TIM_OC_MODE_PWM1 << HM_TIM_CCMR1_OC2M_POS);
            TIMER->TIM_CCER |= HM_TIM_CCER_CC2E_MASK;
            break;
        case CHANNEL_TIMER_3:
            TIMER->TIM_CCMR2 &= ~HM_TIM_CCMR2_OC3M_MASK;
            TIMER->TIM_CCMR2 |= (TIM_OC_MODE_PWM1 << HM_TIM_CCMR2_OC3M_POS);
            TIMER->TIM_CCER |= HM_TIM_CCER_CC3E_MASK;
            break;
        case CHANNEL_TIMER_4:
            TIMER->TIM_CCMR2 &= ~HM_TIM_CCMR2_OC4M_MASK;
            TIMER->TIM_CCMR2 |= (TIM_OC_MODE_PWM1 << HM_TIM_CCMR2_OC4M_POS);
            TIMER->TIM_CCER |= HM_TIM_CCER_CC4E_MASK;
            break;
        default:
            return TIM_ERROR_INVALID_PARAM;
    }

    return TIM_OK;
}

/**
 * @brief Set duty cycle for a specific PWM channel
 * @param timer: Timer selection (TIMER_2 to TIMER_5)
 * @param channel: Channel selection (CHANNEL_TIMER_1 to CHANNEL_TIMER_4)
 * @param dutyCycle: Duty cycle percentage (0-100)
 * @return TIM_Error_t: Status of the operation
 */
TIM_Error_t SetDutyCycle(Timer_t timer, Channel_timer_t channel, uint8_t dutyCycle) {
    if (timer > TIMER_5 || channel > CHANNEL_TIMER_4 || dutyCycle > 100) {
        return TIM_ERROR_INVALID_PARAM;
    }

    volatile TIM_Handmade_t *TIMER = TIMx[timer];

    if (!(TIMER->TIM_CR1 & HM_TIM_CR1_CEN_MASK)) {
        return TIM_ERROR_NOT_INITIALIZED;
    }

    uint32_t ccr_value = calculateDutyCycle(TIMER->TIM_ARR, dutyCycle);
    switch (channel) {
        case CHANNEL_TIMER_1:
            TIMER->TIM_CCR1 = ccr_value;
            break;
        case CHANNEL_TIMER_2:
            TIMER->TIM_CCR2 = ccr_value;
            break;
        case CHANNEL_TIMER_3:
            TIMER->TIM_CCR3 = ccr_value;
            break;
        case CHANNEL_TIMER_4:
            TIMER->TIM_CCR4 = ccr_value;
            break;
        default:
            return TIM_ERROR_INVALID_PARAM;
    }

    return TIM_OK;
}