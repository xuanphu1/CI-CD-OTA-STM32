#include "Systick_Handmade.h"

volatile uint32_t SysTick_ms = 0;

/**
 * @brief Increment millisecond counter
 */
void SysTick_ms_inc(void) {
    SysTick_ms++;
}

/**
 * @brief Initialize SysTick with user configuration
 * @param systickConfig: Pointer to SysTick configuration structure
 * @return SysTick_Error_t: Status of the operation
 */
SysTick_Error_t SysTick_Init(SysTick_Config_t *systickConfig) {
    if (systickConfig == NULL ||
        systickConfig->SysTick_Source > SYST_CSR_CLKSOURCE_PROCESSOR ||
        systickConfig->Generate_interrupt > SYST_CSR_TICKINT_ENABLE ||
        systickConfig->EnableCounter > SYST_CSR_ENABLE_ENABLE ||
        systickConfig->ValueInitReload > 0xFFFFFF) {
        return SYSTICK_ERROR_INVALID_PARAM;
    }

    // Disable SysTick before configuration
    SYSTICK_HANDMADE->SYST_CSR = 0;

    // Configure clock source
    SYSTICK_HANDMADE->SYST_CSR |= (systickConfig->SysTick_Source << HM_SYST_CSR_CLKSOURCE_POS);

    // Configure interrupt
    SYSTICK_HANDMADE->SYST_CSR |= (systickConfig->Generate_interrupt << HM_SYST_CSR_TICKINT_POS);

    // Configure reload value
    uint32_t reload_value = systickConfig->ValueInitReload;
    if (reload_value == 0) {
        // Default: 1ms tick
        uint32_t clock_freq = getFrequencyRCC();
        if (systickConfig->SysTick_Source == SYST_CSR_CLKSOURCE_EXTERNAL) {
            clock_freq /= 8;
        }
        reload_value = (clock_freq / 1000) - 1;
        if (reload_value > 0xFFFFFF) {
            return SYSTICK_ERROR_INVALID_PARAM;
        }
    }
    SYSTICK_HANDMADE->SYST_RVR = reload_value;

    // Reset current counter
    SYSTICK_HANDMADE->SYST_CVR = 0;

    // Enable SysTick
    SYSTICK_HANDMADE->SYST_CSR |= (systickConfig->EnableCounter << HM_SYST_CSR_ENABLE_POS);

    return SYSTICK_OK;
}

/**
 * @brief Delay for specified milliseconds using SysTick
 * @param value_ms: Delay duration in milliseconds
 * @return SysTick_Error_t: Status of the operation
 */
SysTick_Error_t Delay_SysTick(uint32_t value_ms) {
    if (!(SYSTICK_HANDMADE->SYST_CSR & HM_SYST_CSR_ENABLE_MASK)) {
        return SYSTICK_ERROR_NOT_INITIALIZED;
    }

    if (value_ms == 0) {
        return SYSTICK_OK;
    }

    uint32_t start_ms = SysTick_ms;
    uint32_t elapsed_ms;

    do {
        elapsed_ms = SysTick_ms - start_ms;
        // Handle counter overflow
        if (SysTick_ms < start_ms) {
            elapsed_ms = (0xFFFFFFFF - start_ms) + SysTick_ms + 1;
        }
    } while (elapsed_ms < value_ms);

    return SYSTICK_OK;
}

/**
 * @brief Get current SysTick counter value
 * @param counter: Pointer to store current counter value
 * @return SysTick_Error_t: Status of the operation
 */
SysTick_Error_t SysTick_GetCounter(uint32_t *counter) {
    if (counter == NULL) {
        return SYSTICK_ERROR_INVALID_PARAM;
    }

    if (!(SYSTICK_HANDMADE->SYST_CSR & HM_SYST_CSR_ENABLE_MASK)) {
        return SYSTICK_ERROR_NOT_INITIALIZED;
    }

    *counter = SYSTICK_HANDMADE->SYST_CVR;
    return SYSTICK_OK;
}