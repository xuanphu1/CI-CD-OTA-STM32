#include "RCC_Handmade.h"

FREQ_Frequency_t Frequency_RCC;
PPRE_Prescaler_t PPRE1_Prescaler;
PPRE_Prescaler_t PPRE2_Prescaler;
HPRE_Prescaler_t HPRE_Prescaler;

RCCError_t Enable_Clock_RCC_APB2(APB2_Peripheral_Clock Peripheral_CLK) {
    // Prevent enabling reserved bit
    if (Peripheral_CLK == Reserved_0) {
        return RCC_ERROR_INVALID_PARAM;
    }
    // Check if clock is already enabled
    uint32_t mask = (1U << Peripheral_CLK);
    if (!(RCC_HANDMADE->RCC_APB2ENR & mask)) {
        RCC_HANDMADE->RCC_APB2ENR |= mask;
    }
    return RCC_OK;
}

RCCError_t Enable_Clock_RCC_APB1(APB1_Peripheral_Clock Peripheral_CLK) {
    // Check if clock is already enabled
    uint32_t mask = (1U << Peripheral_CLK);
    if (!(RCC_HANDMADE->RCC_APB1ENR & mask)) {
        RCC_HANDMADE->RCC_APB1ENR |= mask;
    }
    return RCC_OK;
}

RCCError_t Enable_Clock_RCC_AHB(AHB_Peripheral_Clock Peripheral_CLK) {
    // Check if clock is already enabled
    uint32_t mask = (1U << Peripheral_CLK);
    if (!(RCC_HANDMADE->RCC_AHBENR & mask)) {
        RCC_HANDMADE->RCC_AHBENR |= mask;
    }
    return RCC_OK;
}

RCCError_t Select_Prescaler_RCC(RCC_ClockPrescaler_t *Prescaler, RCC_Prescaler_t Prescaler_type) {
    if (!Prescaler) return RCC_ERROR_INVALID_PARAM; // Check for null pointer

    switch (Prescaler_type) {
        case AHB_Prescaler:
            if (Prescaler->HPRE_Prescaler > HPRE_CLOCK_DIV_512) return RCC_ERROR_INVALID_PARAM;
            RCC_HANDMADE->RCC_CFGR &= ~HM_RCC_CFGR_HPRE_MASK; // Clear HPRE
            RCC_HANDMADE->RCC_CFGR |= (Prescaler->HPRE_Prescaler << RCC_CFGR_HPRE_POS); // Configure prescaler
            HPRE_Prescaler = Prescaler->HPRE_Prescaler;
            break;

        case APB1_Prescaler:
            if (Prescaler->PPRE1_Prescaler > PPRE_CLOCK_DIV_16) return RCC_ERROR_INVALID_PARAM;
            RCC_HANDMADE->RCC_CFGR &= ~HM_RCC_CFGR_PPRE1_MASK; // Clear PPRE1
            RCC_HANDMADE->RCC_CFGR |= (Prescaler->PPRE1_Prescaler << RCC_CFGR_PPRE1_POS); // Configure prescaler
            PPRE1_Prescaler = Prescaler->PPRE1_Prescaler;
            break;

        case APB2_Prescaler:
            if (Prescaler->PPRE2_Prescaler > PPRE_CLOCK_DIV_16) return RCC_ERROR_INVALID_PARAM;
            RCC_HANDMADE->RCC_CFGR &= ~HM_RCC_CFGR_PPRE2_MASK; // Clear PPRE2
            RCC_HANDMADE->RCC_CFGR |= (Prescaler->PPRE2_Prescaler << RCC_CFGR_PPRE2_POS); // Configure prescaler
            PPRE2_Prescaler = Prescaler->PPRE2_Prescaler;
            break;

        case ADC_Prescaler:
            if (Prescaler->ADC_Prescaler > ADC_CLOCK_DIV_8) return RCC_ERROR_INVALID_PARAM;
            RCC_HANDMADE->RCC_CFGR &= ~HM_RCC_CFGR_ADCPRE_MASK; // Clear ADCPRE
            RCC_HANDMADE->RCC_CFGR |= (Prescaler->ADC_Prescaler << RCC_CFGR_ADCPRE_POS); // Configure prescaler
            break;

        default:
            return RCC_ERROR_INVALID_PARAM; // Invalid case
    }
    
    return RCC_OK;
}

RCCError_t Select_Sources_Clock(Source_Clock_t Source_Clock) {
    if (Source_Clock != HSI_CLOCK && Source_Clock != HSE_CLOCK) {
        return RCC_ERROR_INVALID_PARAM; // Invalid clock source
    }

    if (Source_Clock == HSI_CLOCK) {
        RCC_HANDMADE->RCC_CR |= RCC_CR_HSION; // Enable HSI
        while (!(RCC_HANDMADE->RCC_CR & HM_RCC_CR_HSIRDY_MASK)); // Wait for HSI ready
    } else if (Source_Clock == HSE_CLOCK) {
        Enable_Clock_RCC_APB2(IOPD_EN_CLK);
        RCC_HANDMADE->RCC_CR |= RCC_CR_HSEON; // Enable HSE
        while (!(RCC_HANDMADE->RCC_CR & HM_RCC_CR_HSERDY_MASK)); // Wait for HSE ready
    }
    return RCC_OK;
}

RCCError_t Select_Frequency_CLK(FREQ_Frequency_t Frequency_clk) {
    if (Frequency_clk > FREQ_72MHZ) {
        return RCC_ERROR_INVALID_PARAM; // Exceeds maximum frequency
    }

    uint32_t pll_input_freq;

    // Check current clock source
    if (RCC_HANDMADE->RCC_CR & HM_RCC_CR_HSERDY_MASK) {
        pll_input_freq = 8000000; // HSE is 8MHz
        RCC_HANDMADE->RCC_CFGR |= RCC_CFGR_PLLSRC; // PLLSRC = HSE
    } else if (RCC_HANDMADE->RCC_CR & HM_RCC_CR_HSIRDY_MASK) {
        pll_input_freq = 4000000; // HSI is 8MHz divided by 2
        RCC_HANDMADE->RCC_CFGR &= ~HM_RCC_CFGR_PLLSRC_MASK; // PLLSRC = HSI/2
    } else {
        return RCC_ERROR_INVALID_PARAM; // No valid clock source
    }

    // Configure bus prescalers similar to HAL
    RCC_ClockPrescaler_t Clock_persaler = {
        .ADC_Prescaler = ADC_CLOCK_DIV_2,
        .PPRE1_Prescaler = PPRE_CLOCK_DIV_1,
        .PPRE2_Prescaler = PPRE_CLOCK_DIV_1,
        .HPRE_Prescaler = HPRE_CLOCK_DIV_1
    };

    if (Frequency_clk > FREQ_36MHZ) Clock_persaler.PPRE1_Prescaler = PPRE_CLOCK_DIV_2; // AHB = SYSCLK/2
    if (Frequency_clk > FREQ_12MHZ) Clock_persaler.ADC_Prescaler = ADC_CLOCK_DIV_6; // ADC = PCLK2/6
        
    Select_Prescaler_RCC(&Clock_persaler, APB1_Prescaler);
    Select_Prescaler_RCC(&Clock_persaler, ADC_Prescaler);
    // Calculate PLL multiplier
    uint32_t pllmul = Frequency_clk / pll_input_freq;
    if (pllmul < 2 || pllmul > 16) return RCC_ERROR_INVALID_PARAM; // PLL multiplier must be 2-16

    // Configure PLL multiplier
    RCC_HANDMADE->RCC_CFGR &= ~HM_RCC_CFGR_PLLMUL_MASK; // Clear PLLMUL
    RCC_HANDMADE->RCC_CFGR |= ((pllmul - 2) << RCC_CFGR_PLLMUL_POS); // Set PLLMUL

    // Enable PLL and wait for PLL ready
    RCC_HANDMADE->RCC_CR |= RCC_CR_PLLON; // PLLON = 1   
    uint32_t timeout = 10000;
    while (!(RCC_HANDMADE->RCC_CR & HM_RCC_CR_PLLRDY_MASK) && timeout--) { // Wait for PLLRDY
        if (timeout == 0) return RCCError_tIMEOUT; // PLL not ready
    }
    // Select PLL as SYSCLK
    RCC_HANDMADE->RCC_CFGR &= ~HM_RCC_CFGR_SW_MASK; // Clear SW bits
    RCC_HANDMADE->RCC_CFGR |= HM_RCC_CFGR_SW_PLL; // SW = PLL

    // Wait until PLL is selected as SYSCLK
    timeout = 10000;
    while (((RCC_HANDMADE->RCC_CFGR & HM_RCC_CFGR_SWS_MASK) >> RCC_CFGR_SWS_POS) != 0x2 && timeout--) {
        if (timeout == 0) return RCCError_tIMEOUT; // SYSCLK not switched to PLL
    }

    PPRE1_Prescaler = Clock_persaler.PPRE1_Prescaler;
    PPRE2_Prescaler = Clock_persaler.PPRE2_Prescaler;
    HPRE_Prescaler = Clock_persaler.HPRE_Prescaler;
    return RCC_OK;
}

RCCError_t init_RCC(RCC_config_t *RCC_config) {
    if (RCC_config == NULL) return RCC_ERROR_INVALID_PARAM;

    RCCError_t status;
    status = (RCCError_t)Flash_AdjustForCLK(RCC_config->frequency);
    if (status != RCC_OK) goto fallback;

    status = Select_Sources_Clock(RCC_config->source_clock);
    if (status != RCC_OK) goto fallback;

    status = Select_Frequency_CLK(RCC_config->frequency);
    Frequency_RCC = RCC_config->frequency;
    if (status != RCC_OK) goto fallback;

    return RCC_OK;

fallback:
    // Restore to default HSI (8MHz)
    RCC_HANDMADE->RCC_CR |= RCC_CR_HSION;
    uint32_t timeout = 10000;
    while (!(RCC_HANDMADE->RCC_CR & HM_RCC_CR_HSIRDY_MASK) && timeout--);
    RCC_HANDMADE->RCC_CFGR &= ~HM_RCC_CFGR_SW_MASK; // Select HSI as SYSCLK
    RCC_HANDMADE->RCC_CFGR |= HM_RCC_CFGR_SW_HSI;
    return RCCError_tIMEOUT;
}

FREQ_Frequency_t getFrequencyAHB(void) {
    uint8_t hpre_divider = (HPRE_Prescaler < 8) ? 1 : (2 << (HPRE_Prescaler - 8));
    return (FREQ_Frequency_t)(Frequency_RCC / hpre_divider);
}

FREQ_Frequency_t getFrequencyAPB1(void) {
    uint8_t ppre1_divider = (PPRE1_Prescaler < 4) ? 1 : (2 << (PPRE1_Prescaler - 4));
    return (FREQ_Frequency_t)(Frequency_RCC / ppre1_divider);
}

FREQ_Frequency_t getFrequencyAPB2(void) {
    uint8_t ppre2_divider = (PPRE2_Prescaler < 4) ? 1 : (2 << (PPRE2_Prescaler - 4));
    return (FREQ_Frequency_t)(Frequency_RCC / ppre2_divider);
}

FREQ_Frequency_t getFrequencyRCC(void) {
    return (FREQ_Frequency_t)(Frequency_RCC);
}