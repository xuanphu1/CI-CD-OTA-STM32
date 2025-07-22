#include "ADC_Handmade.h"

/**
 * @brief Enable clock for ADC1 and configure the prescaler
 * @

param prescaler: ADC prescaler (CLOCK_ADC_DIV_2, CLOCK_ADC_DIV_4, ...)
 * @return ADC_Error_t: Execution status
 */
ADC_Error_t ADC_EnableClock(ClockPrescaler_t prescaler) {
    if (prescaler > CLOCK_ADC_DIV_8) {
        return ADC_ERROR_INVALID_PARAM;
    }

    Enable_Clock_RCC_APB2(ADC1_EN_CLK);
    RCC_ClockPrescaler_t Prescaler_RCC = {
        .ADC_Prescaler = prescaler,
    };
    Select_Prescaler_RCC(&Prescaler_RCC, ADC_Prescaler);

    return ADC_OK;
}

/**
 * @brief Initialize ADC1 with user configuration
 * @param adcConfig: Pointer to ADC configuration
 * @return ADC_Error_t: Execution status
 */
ADC_Error_t ADC_Init(ADC_Config_t *adcConfig) {
    if (adcConfig == NULL || 
        adcConfig->num_of_conversions       == 0                        || 
        adcConfig->num_of_conversions       > 16                        ||
        adcConfig->scan_mode                > SCAN_ENABLE               ||
        adcConfig->dma_mode                 > DMA_ENABLE                ||
        adcConfig->conversion_mode          > CONTINUOUS_CONVERSION     ||
        adcConfig->data_align               > DATAALIGN_LEFT            ||
        adcConfig->external_trigger         > EXTERNAL_TRIGGER_ENABLE   ||
        adcConfig->interrupt_mode           > INTERRUPT_ENABLE          ||
        adcConfig->sample_time              > SAMPLE_239_5_CYCLES       ||
        adcConfig->clock_prescaler          > CLOCK_ADC_DIV_8) {
        return ADC_ERROR_INVALID_PARAM;
    }

    // Configure GPIO for ADC channels
    for (uint8_t i = 0; i < adcConfig->num_of_conversions; i++) {
        if (adcConfig->RegularSequence[i] > CUSTOM_ADC_CHANNEL_VREFINT) {
            return ADC_ERROR_INVALID_PARAM;
        }

        Port_t port_adc;
        Pin_gpio_t pin_adc;

        if (adcConfig->RegularSequence[i] <= CUSTOM_ADC_CHANNEL_7) {
            port_adc = Port_A;
            pin_adc = (Pin_gpio_t)adcConfig->RegularSequence[i];
        } else if (adcConfig->RegularSequence[i] <= CUSTOM_ADC_CHANNEL_9) {
            port_adc = Port_B;
            pin_adc = (Pin_gpio_t)(adcConfig->RegularSequence[i] - 8);
        } else if (adcConfig->RegularSequence[i] <= CUSTOM_ADC_CHANNEL_15) {
            port_adc = Port_C;
            pin_adc = (Pin_gpio_t)(adcConfig->RegularSequence[i] - 10);
        } else {
            continue; // Skip TEMP_SENSOR and VREFINT
        }

        GPIO_config_t config_GPIO = {
            .port = port_adc,
            .pin = pin_adc,
            .mode = INPUT_MODE,
            .cnf_mode = CNF_MODE_00 // Analog mode
        };
        if (InitGPIO(&config_GPIO) != GPIO_OK) {
            return ADC_ERROR_INVALID_PARAM;
        }
    }

    // Enable ADC clock
    if (ADC_EnableClock(adcConfig->clock_prescaler) != ADC_OK) {
        return ADC_ERROR_INVALID_PARAM;
    }

    // Disable ADC before configuration
    ADC1_HANDMADE->ADC_CR2 &= ~HM_ADC_CR2_ADON_MASK;

    // Configure ADC parameters
    ADC1_HANDMADE->ADC_CR1  &= ~HM_ADC_CR1_SCAN_MODE_MASK;
    ADC1_HANDMADE->ADC_CR1  |= (adcConfig->scan_mode << HM_ADC_CR1_SCAN_MODE_POS);
    
    ADC1_HANDMADE->ADC_CR2  &= ~HM_ADC_CR2_CONT_MASK;
    ADC1_HANDMADE->ADC_CR2  |= (adcConfig->conversion_mode << HM_ADC_CR2_CONT_POS);
    
    ADC1_HANDMADE->ADC_CR2  &= ~HM_ADC_CR2_DMA_MASK;
    ADC1_HANDMADE->ADC_CR2  |= (adcConfig->dma_mode << HM_ADC_CR2_DMA_POS);
    
    ADC1_HANDMADE->ADC_CR2  &= ~HM_ADC_CR2_ALIGN_MASK;
    ADC1_HANDMADE->ADC_CR2  |= (adcConfig->data_align << HM_ADC_CR2_ALIGN_POS);
    
    ADC1_HANDMADE->ADC_CR2  &= ~HM_ADC_CR2_EXTERNAL_TRIGGER_MASK;
    ADC1_HANDMADE->ADC_CR2  |= (adcConfig->external_trigger << HM_ADC_CR2_EXTERNAL_TRIGGER_POS);
    
    ADC1_HANDMADE->ADC_CR1  &= ~HM_ADC_CR1_EOC_INTERRUPT_MASK;
    ADC1_HANDMADE->ADC_CR1  |= (adcConfig->interrupt_mode << HM_ADC_CR1_EOC_INTERRUPT_POS);

    // Configure number of conversions
    ADC1_HANDMADE->ADC_SQR1 &= ~HM_ADC_SQR1_NUM_CONVERSIONS_MASK;
    ADC1_HANDMADE->ADC_SQR1 |= ((adcConfig->num_of_conversions - 1) << HM_ADC_SQR1_NUM_CONVERSIONS_POS);

    // Configure regular sequence and sample times
    for (uint8_t i = 0; i < adcConfig->num_of_conversions; i++) {
        if (i < 6) {
            ADC1_HANDMADE->ADC_SQR3 &= ~HM_ADC_SQRx_CHANNEL_MASK(i);
            ADC1_HANDMADE->ADC_SQR3 |= (adcConfig->RegularSequence[i] << (i * 5U));
        } else if (i < 12) {
            ADC1_HANDMADE->ADC_SQR2 &= ~HM_ADC_SQRx_CHANNEL_MASK(i - 6);
            ADC1_HANDMADE->ADC_SQR2 |= (adcConfig->RegularSequence[i] << ((i - 6) * 5U));
        } else {
            ADC1_HANDMADE->ADC_SQR1 &= ~HM_ADC_SQRx_CHANNEL_MASK(i - 12);
            ADC1_HANDMADE->ADC_SQR1 |= (adcConfig->RegularSequence[i] << ((i - 12) * 5U));
        }

        if (adcConfig->RegularSequence[i] <= CUSTOM_ADC_CHANNEL_9) {
            ADC1_HANDMADE->ADC_SMPR2 &= ~HM_ADC_SMPRx_SAMPLE_TIME_MASK(adcConfig->RegularSequence[i]);
            ADC1_HANDMADE->ADC_SMPR2 |= (adcConfig->sample_time << (adcConfig->RegularSequence[i] * 3U));
        } else {
            uint8_t offset = adcConfig->RegularSequence[i] - 10;
            ADC1_HANDMADE->ADC_SMPR1 &= ~HM_ADC_SMPRx_SAMPLE_TIME_MASK(offset);
            ADC1_HANDMADE->ADC_SMPR1 |= (adcConfig->sample_time << (offset * 3U));
        }
    }

    // Enable and calibrate ADC
    ADC1_HANDMADE->ADC_CR2 |= HM_ADC_CR2_ADON_MASK;
    for (volatile uint32_t i = 0; i < 1000; i++); // Stabilization delay
    
    ADC1_HANDMADE->ADC_CR2 |= HM_ADC_CR2_ADON_MASK;
    ADC1_HANDMADE->ADC_CR2 |= (1U << 2); // Start calibration

    uint32_t timeout = 10000;
    while ((ADC1_HANDMADE->ADC_CR2 & (1U << 2)) && timeout--) {
        if (timeout == 0) {
            return ADC_ERROR_TIMEOUT;
        }
    }

    return ADC_OK;
}

/**
 * @brief Read multiple ADC channels without DMA
 * @param adcConfig: Pointer to ADC configuration containing results
 * @return ADC_Error_t: Execution status
 */
ADC_Error_t ADC_ReadMultiple(ADC_Config_t *adcConfig) {
    if (adcConfig == NULL || 
        adcConfig->num_of_conversions == 0 || 
        adcConfig->dma_mode == DMA_ENABLE) {
        return ADC_ERROR_INVALID_PARAM;
    }

    if (!(ADC1_HANDMADE->ADC_CR2 & HM_ADC_CR2_ADON_MASK)) {
        return ADC_ERROR_NOT_INITIALIZED;
    }

    ADC1_HANDMADE->ADC_CR2 |= HM_ADC_CR2_SWSTART_MASK;

    for (uint8_t i = 0; i < adcConfig->num_of_conversions; i++) {
        uint32_t timeout = 10000;
        while (!(ADC1_HANDMADE->ADC_SR & HM_ADC_SR_EOC_MASK) && timeout--) {
            if (timeout == 0) {
                return ADC_ERROR_TIMEOUT;
            }
        }
        adcConfig->Result_ADC[i] = ADC1_HANDMADE->ADC_DR & HM_ADC_DR_MASK;
    }

    return ADC_OK;
}

/**
 * @brief Start ADC conversion with DMA
 * @return ADC_Error_t: Execution status
 */
ADC_Error_t ADC_DMA_Start(void) {
    if (!(ADC1_HANDMADE->ADC_CR2 & HM_ADC_CR2_ADON_MASK) || 
        !(ADC1_HANDMADE->ADC_CR2 & HM_ADC_CR2_DMA_MASK)) {
        return ADC_ERROR_NOT_INITIALIZED;
    }

    ADC1_HANDMADE->ADC_CR2 |= HM_ADC_CR2_SWSTART_MASK;
    return ADC_OK;
}