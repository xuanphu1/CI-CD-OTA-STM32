#include "GPIO_Handmade.h"

static volatile GPIO_Handmade_t *GPIO_List[] = {
    GPIOA_HANDMADE, GPIOB_HANDMADE, GPIOC_HANDMADE, 
    GPIOD_HANDMADE, GPIOE_HANDMADE, GPIOF_HANDMADE, GPIOG_HANDMADE
};

static const uint32_t GPIO_CRL_MODE_POS[] = {
    GPIO_CRL_MODE0_POS, GPIO_CRL_MODE1_POS, GPIO_CRL_MODE2_POS, GPIO_CRL_MODE3_POS,
    GPIO_CRL_MODE4_POS, GPIO_CRL_MODE5_POS, GPIO_CRL_MODE6_POS, GPIO_CRL_MODE7_POS
};

static const uint32_t GPIO_CRL_CNF_POS[] = {
    GPIO_CRL_CNF0_POS, GPIO_CRL_CNF1_POS, GPIO_CRL_CNF2_POS, GPIO_CRL_CNF3_POS,
    GPIO_CRL_CNF4_POS, GPIO_CRL_CNF5_POS, GPIO_CRL_CNF6_POS, GPIO_CRL_CNF7_POS
};

static const uint32_t GPIO_CRH_MODE_POS[] = {
    GPIO_CRH_MODE8_POS, GPIO_CRH_MODE9_POS, GPIO_CRH_MODE10_POS, GPIO_CRH_MODE11_POS,
    GPIO_CRH_MODE12_POS, GPIO_CRH_MODE13_POS, GPIO_CRH_MODE14_POS, GPIO_CRH_MODE15_POS
};

static const uint32_t GPIO_CRH_CNF_POS[] = {
    GPIO_CRH_CNF8_POS, GPIO_CRH_CNF9_POS, GPIO_CRH_CNF10_POS, GPIO_CRH_CNF11_POS,
    GPIO_CRH_CNF12_POS, GPIO_CRH_CNF13_POS, GPIO_CRH_CNF14_POS, GPIO_CRH_CNF15_POS
};

static const uint32_t GPIO_MODE_MASKS[] = {
    HM_GPIO_CRL_MODE0_MASK, HM_GPIO_CRL_MODE1_MASK, HM_GPIO_CRL_MODE2_MASK, HM_GPIO_CRL_MODE3_MASK,
    HM_GPIO_CRL_MODE4_MASK, HM_GPIO_CRL_MODE5_MASK, HM_GPIO_CRL_MODE6_MASK, HM_GPIO_CRL_MODE7_MASK,
    HM_GPIO_CRH_MODE8_MASK, HM_GPIO_CRH_MODE9_MASK, HM_GPIO_CRH_MODE10_MASK, HM_GPIO_CRH_MODE11_MASK,
    HM_GPIO_CRH_MODE12_MASK, HM_GPIO_CRH_MODE13_MASK, HM_GPIO_CRH_MODE14_MASK, HM_GPIO_CRH_MODE15_MASK
};

static const uint32_t GPIO_CNF_MASKS[] = {
    HM_GPIO_CRL_CNF0_MASK, HM_GPIO_CRL_CNF1_MASK, HM_GPIO_CRL_CNF2_MASK, HM_GPIO_CRL_CNF3_MASK,
    HM_GPIO_CRL_CNF4_MASK, HM_GPIO_CRL_CNF5_MASK, HM_GPIO_CRL_CNF6_MASK, HM_GPIO_CRL_CNF7_MASK,
    HM_GPIO_CRH_CNF8_MASK, HM_GPIO_CRH_CNF9_MASK, HM_GPIO_CRH_CNF10_MASK, HM_GPIO_CRH_CNF11_MASK,
    HM_GPIO_CRH_CNF12_MASK, HM_GPIO_CRH_CNF13_MASK, HM_GPIO_CRH_CNF14_MASK, HM_GPIO_CRH_CNF15_MASK
};

static const uint32_t GPIO_BSRR_SET_MASKS[] = {
    HM_GPIO_BSRR_PIN0_SET, HM_GPIO_BSRR_PIN1_SET, HM_GPIO_BSRR_PIN2_SET, HM_GPIO_BSRR_PIN3_SET,
    HM_GPIO_BSRR_PIN4_SET, HM_GPIO_BSRR_PIN5_SET, HM_GPIO_BSRR_PIN6_SET, HM_GPIO_BSRR_PIN7_SET,
    HM_GPIO_BSRR_PIN8_SET, HM_GPIO_BSRR_PIN9_SET, HM_GPIO_BSRR_PIN10_SET, HM_GPIO_BSRR_PIN11_SET,
    HM_GPIO_BSRR_PIN12_SET, HM_GPIO_BSRR_PIN13_SET, HM_GPIO_BSRR_PIN14_SET, HM_GPIO_BSRR_PIN15_SET
};

static const uint32_t GPIO_BRR_MASKS[] = {
    HM_GPIO_BRR_PIN0_MASK, HM_GPIO_BRR_PIN1_MASK, HM_GPIO_BRR_PIN2_MASK, HM_GPIO_BRR_PIN3_MASK,
    HM_GPIO_BRR_PIN4_MASK, HM_GPIO_BRR_PIN5_MASK, HM_GPIO_BRR_PIN6_MASK, HM_GPIO_BRR_PIN7_MASK,
    HM_GPIO_BRR_PIN8_MASK, HM_GPIO_BRR_PIN9_MASK, HM_GPIO_BRR_PIN10_MASK, HM_GPIO_BRR_PIN11_MASK,
    HM_GPIO_BRR_PIN12_MASK, HM_GPIO_BRR_PIN13_MASK, HM_GPIO_BRR_PIN14_MASK, HM_GPIO_BRR_PIN15_MASK
};

/**
 * @brief Initialize GPIO with the provided configuration
 * @param config_gpio: Pointer to the GPIO configuration (port, pin, cnf_mode, mode)
 * @return GPIO_Error_t: Execution status (GPIO_OK, GPIO_ERROR_INVALID_PARAM)
 */
GPIO_Error_t InitGPIO(GPIO_config_t *config_gpio) {
    if (config_gpio == NULL || 
        config_gpio->port > Port_G || 
        config_gpio->pin > PIN_15 || 
        config_gpio->cnf_mode > CNF_MODE_11 || 
        config_gpio->mode > OUTPUT_MODE_50_MHZ) {
        return GPIO_ERROR_INVALID_PARAM;
    }

    volatile GPIO_Handmade_t *GPIOx = GPIO_List[config_gpio->port];

    Enable_Clock_RCC_APB2((APB2_Peripheral_Clock)(config_gpio->port + IOPA_EN_CLK)); // Enable clock for port A, B, C, D, E, F, G
    
    if (config_gpio->pin < PIN_8) {
        // Clear MODE and CNF bits
        GPIOx->GPIO_CRL &= ~(GPIO_MODE_MASKS[config_gpio->pin] | GPIO_CNF_MASKS[config_gpio->pin]);
        // Set new MODE and CNF bits
        GPIOx->GPIO_CRL |= ((config_gpio->mode << GPIO_CRL_MODE_POS[config_gpio->pin]) |
                           (config_gpio->cnf_mode << GPIO_CRL_CNF_POS[config_gpio->pin]));
    } else {
        // Clear MODE and CNF bits
        GPIOx->GPIO_CRH &= ~(GPIO_MODE_MASKS[config_gpio->pin] | GPIO_CNF_MASKS[config_gpio->pin]);
        // Set new MODE and CNF bits
        GPIOx->GPIO_CRH |= ((config_gpio->mode << GPIO_CRH_MODE_POS[config_gpio->pin - 8]) |
                           (config_gpio->cnf_mode << GPIO_CRH_CNF_POS[config_gpio->pin - 8]));
    }
    return GPIO_OK;
}

/**
 * @brief Read the state of a GPIO pin
 * @param port: GPIO port (Port_A, Port_B, ...)
 * @param Pin: GPIO pin (PIN_0, PIN_1, ...)
 * @return uint32_t: Pin value (0 or 1), or GPIO_ERROR_INVALID_PARAM if the parameters are invalid
 */
uint32_t ReadPin(Port_t port, Pin_gpio_t Pin) {
    if (port > Port_G || Pin > PIN_15) return GPIO_ERROR_INVALID_PARAM;
    volatile GPIO_Handmade_t *GPIOx = GPIO_List[port];
    return (GPIOx->GPIO_IDR & (1U << Pin)) ? 1 : 0;
}

/**
 * @brief Write a value to a GPIO pin
 * @param port: GPIO port (Port_A, Port_B, ...)
 * @param Pin: GPIO pin (PIN_0, PIN_1, ...)
 * @param value: Value to write (GPIO_LOW or GPIO_HIGH)
 * @return GPIO_Error_t: Execution status (GPIO_OK, GPIO_ERROR_INVALID_PARAM, GPIO_ERROR_NOT_INITIALIZED)
 */
GPIO_Error_t WritePin(Port_t port, Pin_gpio_t Pin, uint32_t value) {
    if (port > Port_G || Pin > PIN_15 || (value != GPIO_LOW && value != GPIO_HIGH)) {
        return GPIO_ERROR_INVALID_PARAM;
    }
    volatile GPIO_Handmade_t *GPIOx = GPIO_List[port];
    uint32_t mode_bits = (Pin < PIN_8) ? 
        ((GPIOx->GPIO_CRL & GPIO_MODE_MASKS[Pin]) >> GPIO_CRL_MODE_POS[Pin]) : 
        ((GPIOx->GPIO_CRH & GPIO_MODE_MASKS[Pin]) >> GPIO_CRH_MODE_POS[Pin - 8]);

    if (mode_bits == INPUT_MODE) {
        return GPIO_ERROR_NOT_INITIALIZED; // Pin not configured as output
    }
    
    if (value == GPIO_LOW) {
        GPIOx->GPIO_BRR = GPIO_BRR_MASKS[Pin];
    } else {
        GPIOx->GPIO_BSRR = GPIO_BSRR_SET_MASKS[Pin];
    }
    return GPIO_OK;
}

/**
 * @brief Toggle the state of a GPIO pin
 * @param port: GPIO port (Port_A, Port_B, ...)
 * @param Pin: GPIO pin (PIN_0, PIN_1, ...)
 * @return GPIO_Error_t: Execution status (GPIO_OK, GPIO_ERROR_INVALID_PARAM)
 */
GPIO_Error_t TogglePin(Port_t port, Pin_gpio_t Pin) {
    if (port > Port_G || Pin > PIN_15) return GPIO_ERROR_INVALID_PARAM;

    volatile GPIO_Handmade_t *GPIOx = GPIO_List[port];

    if ((GPIOx->GPIO_ODR & (1U << Pin)) == 0) {
        GPIOx->GPIO_BSRR = GPIO_BSRR_SET_MASKS[Pin];
    } else {
        GPIOx->GPIO_BRR = GPIO_BRR_MASKS[Pin];
    }
    return GPIO_OK;
}

/**
 * @brief Write values to multiple GPIO pins at once
 * @param port: GPIO port (Port_A, Port_B, ...)
 * @param pin_mask: Pin mask (bits 1: selected pin)
 * @param value: Value to write (bits 1: HIGH, bits 0: LOW)
 * @return GPIO_Error_t: Execution status (GPIO_OK, GPIO_ERROR_INVALID_PARAM)
 */
GPIO_Error_t WriteMultiPins(Port_t port, uint32_t pin_mask, uint32_t value) {
    if (port > Port_G) {
        return GPIO_ERROR_INVALID_PARAM;
    }

    volatile GPIO_Handmade_t *GPIOx = GPIO_List[port];
    GPIOx->GPIO_BSRR = (pin_mask & value);    // Set HIGH bits
    GPIOx->GPIO_BRR = (pin_mask & ~value);    // Set LOW bits
    return GPIO_OK;
}

/**
 * @brief Read values from multiple GPIO pins
 * @param port: GPIO port (Port_A, Port_B, ...)
 * @param pins: Array of GPIO pins to read (PIN_0, PIN_1, ...)
 * @param output_array: Array to store the read results (0 or 1 for each pin)
 * @param pin_count: Number of pins to read (up to 16)
 * @return GPIO_Error_t: Execution status (GPIO_OK, GPIO_ERROR_INVALID_PARAM, GPIO_ERROR_NOT_INITIALIZED)
 */
GPIO_Error_t ReadMultiPins(Port_t port, Pin_gpio_t *pins, uint8_t *output_array, uint8_t pin_count) {
    if (port > Port_G || pins == NULL || output_array == NULL || pin_count == 0 || pin_count > 16) {
        return GPIO_ERROR_INVALID_PARAM;
    }

    volatile GPIO_Handmade_t *GPIOx = GPIO_List[port];
    uint32_t idr_value = GPIOx->GPIO_IDR;

    for (uint32_t i = 0; i < pin_count; i++) {
        if (pins[i] > PIN_15) {
            return GPIO_ERROR_INVALID_PARAM; // Invalid pin
        }

        uint32_t mode_bits = (pins[i] < PIN_8) ? 
            ((GPIOx->GPIO_CRL & GPIO_MODE_MASKS[pins[i]]) >> GPIO_CRL_MODE_POS[pins[i]]) : 
            ((GPIOx->GPIO_CRH & GPIO_MODE_MASKS[pins[i]]) >> GPIO_CRH_MODE_POS[pins[i] - 8]);

        if (mode_bits != INPUT_MODE) {
            return GPIO_ERROR_NOT_INITIALIZED; // Pin not configured as input
        }

        output_array[i] = (idr_value & (1U << pins[i])) ? 1 : 0;
    }

    return GPIO_OK;
}

/**
 * @brief Turn ON the LED on pin PC13 (active-low)
 */
void ON_Led_Hardware(void) {
    WritePin(Port_C, PIN_13, GPIO_LOW);
}

/**
 * @brief Turn OFF the LED on pin PC13 (active-low)
 */
void OFF_Led_Hardware(void) {
    WritePin(Port_C, PIN_13, GPIO_HIGH);
}
