#include "DMA_Handmade.h"

/**
 * @brief Initialize a DMA channel with provided configuration
 * @param dmaConfig: Pointer to DMA configuration structure
 * @return DMA_Error_t: Status of the operation
 */
DMA_Error_t DMA_Init(DMA_Config_t *dmaConfig) {
    if (dmaConfig == NULL                                           || 
        dmaConfig->Channel              > DMA_CHANNEL_7             ||
        dmaConfig->Priority             > DMA_VERY_HIGH_PRIORITY    ||
        dmaConfig->PeripheralIncrement  > ENABLE_DMA_PINC           ||
        dmaConfig->MemoryIncrement      > ENABLE_DMA_MINC           ||
        dmaConfig->PeripheralSize       > DMA_PSIZE_32BIT           ||
        dmaConfig->MemorySize           > DMA_MSIZE_32BIT           ||
        dmaConfig->CircularMode         > DMA_CIRC_ENABLE           ||
        dmaConfig->Direction            > DMA_DIR_MEM_TO_PERIPH     ||
        dmaConfig->TransferErrorInt     > DMA_TEIE_ENABLE           ||
        dmaConfig->HalfTransferInt      > DMA_HTIE_ENABLE           ||
        dmaConfig->TransferCompleteInt  > DMA_TCIE_ENABLE           ||
        dmaConfig->NumData              == 0                        ||
        dmaConfig->PeripheralAddress    == 0                        ||
        dmaConfig->MemoryAddress        == 0) {
        return DMA_ERROR_INVALID_PARAM;
    }

    // Enable DMA1 clock
    Enable_Clock_RCC_AHB(DMA1_EN_CLK);

    // Disable DMA channel before configuration
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CCR &= ~HM_DMA_CCR_EN_MASK;

    // Configure DMA channel parameters
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CCR &= ~(HM_DMA_CCR_PL_MASK      | 
                                                            HM_DMA_CCR_PINC_MASK    | 
                                                            HM_DMA_CCR_MINC_MASK    | 
                                                            HM_DMA_CCR_PSIZE_MASK   | 
                                                            HM_DMA_CCR_MSIZE_MASK   | 
                                                            HM_DMA_CCR_CIRC_MASK    | 
                                                        HM_DMA_CCR_DIR_MASK         | 
                                                            HM_DMA_CCR_TEIE_MASK    | 
                                                            HM_DMA_CCR_HTIE_MASK    | 
                                                            HM_DMA_CCR_TCIE_MASK);
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CCR |=   (dmaConfig->Priority << HM_DMA_CCR_PL_POS)              |
                                                            (dmaConfig->PeripheralIncrement << HM_DMA_CCR_PINC_POS) |
                                                            (dmaConfig->MemoryIncrement << HM_DMA_CCR_MINC_POS)     |
                                                            (dmaConfig->PeripheralSize << HM_DMA_CCR_PSIZE_POS)     |
                                                            (dmaConfig->MemorySize << HM_DMA_CCR_MSIZE_POS)         |
                                                            (dmaConfig->CircularMode << HM_DMA_CCR_CIRC_POS)        |
                                                            (dmaConfig->Direction << HM_DMA_CCR_DIR_POS)            |
                                                            (dmaConfig->TransferErrorInt << HM_DMA_CCR_TEIE_POS)    |
                                                            (dmaConfig->HalfTransferInt << HM_DMA_CCR_HTIE_POS)     |
                                                            (dmaConfig->TransferCompleteInt << HM_DMA_CCR_TCIE_POS);

    // Configure data transfer parameters
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CNDTR = dmaConfig->NumData;
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CPAR = dmaConfig->PeripheralAddress;
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CMAR = dmaConfig->MemoryAddress;

    return DMA_OK;
}

/**
 * @brief Start a configured DMA channel
 * @param channel: DMA channel to start (DMA_CHANNEL_1 to DMA_CHANNEL_7)
 * @return DMA_Error_t: Status of the operation
 */
DMA_Error_t DMA_Start(DMAChannel_t channel) {
    if (channel > DMA_CHANNEL_7) {
        return DMA_ERROR_INVALID_PARAM;
    }

    if (DMA1_HANDMADE->CHANNEL[channel].DMA_CNDTR == 0) {
        return DMA_ERROR_NOT_INITIALIZED;
    }

    // Clear interrupt flags
    DMA1_HANDMADE->DMA_IFCR |= HM_DMA_IFCR_CGIF_MASK(channel);

    // Enable DMA channel
    DMA1_HANDMADE->CHANNEL[channel].DMA_CCR |= HM_DMA_CCR_EN_MASK;

    return DMA_OK;
}

/**
 * @brief Set peripheral address for a DMA channel
 * @param channel: DMA channel (DMA_CHANNEL_1 to DMA_CHANNEL_7)
 * @param address: Peripheral address to set
 * @return DMA_Error_t: Status of the operation
 */
DMA_Error_t AddressPeripheral(DMAChannel_t channel, uint32_t address) {
    if (channel > DMA_CHANNEL_7 || address == 0) {
        return DMA_ERROR_INVALID_PARAM;
    }

    DMA1_HANDMADE->CHANNEL[channel].DMA_CPAR = address;
    return DMA_OK;
}

/**
 * @brief Set memory address for a DMA channel
 * @param channel: DMA channel (DMA_CHANNEL_1 to DMA_CHANNEL_7)
 * @param address: Memory address to set
 * @return DMA_Error_t: Status of the operation
 */
DMA_Error_t AddressMemory(DMAChannel_t channel, uint32_t address) {
    if (channel > DMA_CHANNEL_7 || address == 0) {
        return DMA_ERROR_INVALID_PARAM;
    }

    DMA1_HANDMADE->CHANNEL[channel].DMA_CMAR = address;
    return DMA_OK;
}