#include "NVIC_Handmade.h"

/**
 * @brief Enable a specific NVIC interrupt
 * @param IRQ: Interrupt number (Custom_WWDG_IRQn to Custom_DMA2_Channel4_5_IRQn)
 * @return NVIC_Error_t: Status of the operation
 */
NVIC_Error_t Enable_Interrupt_NVIC(Custom_IRQn IRQ) {
    if (IRQ > Custom_DMA2_Channel4_5_IRQn) {
        return NVIC_ERROR_INVALID_PARAM;
    }

    NVIC_HANDMADE->ISER[IRQ / 32] |= HM_NVIC_ISER_BIT_MASK(IRQ);
    return NVIC_OK;
}

/**
 * @brief Disable a specific NVIC interrupt
 * @param IRQ: Interrupt number (Custom_WWDG_IRQn to Custom_DMA2_Channel4_5_IRQn)
 * @return NVIC_Error_t: Status of the operation
 */
NVIC_Error_t Disable_Interrupt_NVIC(Custom_IRQn IRQ) {
    if (IRQ > Custom_DMA2_Channel4_5_IRQn) {
        return NVIC_ERROR_INVALID_PARAM;
    }

    NVIC_HANDMADE->ICER[IRQ / 32] |= HM_NVIC_ICER_BIT_MASK(IRQ);
    return NVIC_OK;
}

/**
 * @brief Set priority for a specific NVIC interrupt
 * @param IRQ: Interrupt number (Custom_WWDG_IRQn to Custom_DMA2_Channel4_5_IRQn)
 * @param Priority: Priority level (0 to 15 for STM32F103)
 * @return NVIC_Error_t: Status of the operation
 */
NVIC_Error_t setPriorityInterrupt(Custom_IRQn IRQ, uint8_t Priority) {
    if (IRQ > Custom_DMA2_Channel4_5_IRQn || Priority > 15) {
        return NVIC_ERROR_INVALID_PARAM;
    }

    uint8_t IPRx = IRQ / 4;         // Find corresponding IPR register

    NVIC_HANDMADE->IPR[IPRx] &= ~HM_NVIC_IPR_BYTE_MASK(IRQ);
    NVIC_HANDMADE->IPR[IPRx] |= (Priority << HM_NVIC_IPR_BYTE_POS(IRQ));
    return NVIC_OK;
}

/**
 * @brief Disable all interrupts globally
 * @return NVIC_Error_t: Status of the operation
 */
NVIC_Error_t DisableAllInterrupt(void) {
    __asm__ volatile ("cpsid i" : : : "memory");
    return NVIC_OK;
}

/**
 * @brief Enable all interrupts globally
 * @return NVIC_Error_t: Status of the operation
 */
NVIC_Error_t EnableAllInterrupt(void) {
    __asm__ volatile ("cpsie i" : : : "memory");
    return NVIC_OK;
}