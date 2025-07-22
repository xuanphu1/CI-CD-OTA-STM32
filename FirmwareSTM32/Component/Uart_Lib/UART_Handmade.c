#include "UART_Handmade.h"

static uint16_t USART_CalculateBRR(uint32_t PCLK, uint32_t BaudRate) {
    float USARTDIV = (float)PCLK / (16 * BaudRate);
    uint16_t mantissa = (uint16_t)USARTDIV;
    uint8_t fraction = (USARTDIV - mantissa) * 16;
    return ((mantissa << UART_BRR_DIV_MANTISSA_POS) | (fraction & HM_UART_BRR_DIV_FRACTION_MASK));
}

volatile UART_Handmade_t *UART_List[] = {USART1_HANDMADE, USART2_HANDMADE, USART3_HANDMADE};

Error_UART_t UARTInit(USART_Config_t *uartConfig) {
    // Kiểm tra con trỏ NULL
    if (uartConfig == NULL) {
        return UART_NULL_PTR;
    }
    volatile UART_Handmade_t *UARTx = UART_List[uartConfig->USARTx];

    // Kiểm tra con trỏ UARTx hợp lệ
    if (UARTx == NULL) {
        return UART_ERROR;
    }

    if (uartConfig->USARTx == UART_1) Enable_Clock_RCC_APB2(USART1_EN_CLK);
    else Enable_Clock_RCC_APB1((uartConfig->USARTx == UART_2) ? USART2_EN_CLK : USART3_EN_CLK);

    // 1️⃣ Bật clock GPIO trước khi bật UART
    if (uartConfig->USARTx == UART_1) {
        Enable_Clock_RCC_APB2(USART1_EN_CLK);
        Enable_Clock_RCC_APB2(IOPA_EN_CLK);
    } else if (uartConfig->USARTx == UART_2) {
        Enable_Clock_RCC_APB1(USART2_EN_CLK);
        Enable_Clock_RCC_APB2(IOPA_EN_CLK);
    } else {
        Enable_Clock_RCC_APB1(USART3_EN_CLK);
        Enable_Clock_RCC_APB2(IOPB_EN_CLK);
    }

    // 2️⃣ Cấu hình GPIO TX và RX theo UART đã chọn
    GPIO_config_t gpio_tx, gpio_rx;
    if (uartConfig->USARTx == UART_1) {
        gpio_tx.port = Port_A; gpio_tx.pin = PIN_9;
        gpio_rx.port = Port_A; gpio_rx.pin = PIN_10;
    } else if (uartConfig->USARTx == UART_2) {
        gpio_tx.port = Port_A; gpio_tx.pin = PIN_2;
        gpio_rx.port = Port_A; gpio_rx.pin = PIN_3;
    } else {
        gpio_tx.port = Port_B; gpio_tx.pin = PIN_10;
        gpio_rx.port = Port_B; gpio_rx.pin = PIN_11;
    }

    gpio_tx.mode = OUTPUT_MODE_50_MHZ;
    gpio_tx.cnf_mode = CNF_MODE_10; // Alternate Function Push-Pull
    InitGPIO(&gpio_tx);

    gpio_rx.mode = INPUT_MODE;
    gpio_rx.cnf_mode = CNF_MODE_01; // Input Floating
    InitGPIO(&gpio_rx);

    // Xóa các thanh ghi trước khi cấu hình để tránh giá trị thừa
    UARTx->UART_CR1 = 0;
    UARTx->UART_CR2 = 0;
    UARTx->UART_CR3 = 0;
    UARTx->UART_BRR = 0;
    UARTx->UART_GTPR = 0;

    // Cấu hình thanh ghi UART_CR1
    UARTx->UART_CR1 |= (uartConfig->usartEnable << UART_CR1_UE_POS) |
                       (uartConfig->wordLength << UART_CR1_M_POS) |
                       (uartConfig->wakeupMethod << UART_CR1_WAKE_POS) |
                       (uartConfig->parityControl << UART_CR1_PCE_POS) |
                       (uartConfig->paritySelection << UART_CR1_PS_POS) |
                       (uartConfig->peInterrupt << UART_CR1_PEIE_POS) |
                       (uartConfig->txeInterrupt << UART_CR1_TXEIE_POS) |
                       (uartConfig->tcInterrupt << UART_CR1_TCIE_POS) |
                       (uartConfig->rxneInterrupt << UART_CR1_RXNEIE_POS) |
                       (uartConfig->idleInterrupt << UART_CR1_IDLEIE_POS) |
                       (uartConfig->transmitterEnable << UART_CR1_TE_POS) |
                       (uartConfig->receiverEnable << UART_CR1_RE_POS) |
                       (uartConfig->receiverWakeup << UART_CR1_RWU_POS) |
                       (uartConfig->sendBreak << UART_CR1_SBK_POS);

    // Cấu hình thanh ghi UART_CR2
    UARTx->UART_CR2 |= (uartConfig->linMode << UART_CR2_LINEN_POS) |
                       (uartConfig->stopBits << UART_CR2_STOP_POS) |
                       (uartConfig->clockEnable << UART_CR2_CLKEN_POS) |
                       (uartConfig->clockPolarity << UART_CR2_CPOL_POS) |
                       (uartConfig->clockPhase << UART_CR2_CPHA_POS) |
                       (uartConfig->lastBitClock << UART_CR2_LBCL_POS) |
                       (uartConfig->linBreakInterrupt << UART_CR2_LBDIE_POS) |
                       (uartConfig->linBreakLength << UART_CR2_LBDL_POS) |
                       (uartConfig->nodeAddress & HM_UART_CR2_ADD_MASK);

    // Cấu hình thanh ghi UART_CR3
    UARTx->UART_CR3 |= (uartConfig->ctsInterrupt << UART_CR3_CTSIE_POS) |
                       (uartConfig->ctsEnable << UART_CR3_CTSE_POS) |
                       (uartConfig->rtsEnable << UART_CR3_RTSE_POS) |
                       (uartConfig->dmaTransmitter << UART_CR3_DMAT_POS) |
                       (uartConfig->dmaReceiver << UART_CR3_DMAR_POS) |
                       (uartConfig->smartcardMode << UART_CR3_SCEN_POS) |
                       (uartConfig->smartcardNack << UART_CR3_NACK_POS) |
                       (uartConfig->halfDuplex << UART_CR3_HDSEL_POS) |
                       (uartConfig->irdaLowPower << UART_CR3_IRLP_POS) |
                       (uartConfig->irdaMode << UART_CR3_IREN_POS) |
                       (uartConfig->errorInterrupt << UART_CR3_EIE_POS);

    // Cấu hình thanh ghi UART_BRR (Baud rate)
    UARTx->UART_BRR = USART_CalculateBRR((uartConfig->USARTx == UART_1 ? (uint32_t)getFrequencyAPB2() : (uint32_t)getFrequencyAPB1()),
                                         uartConfig->baudUART);

    // Cấu hình thanh ghi UART_GTPR (Guard time and prescaler)
    UARTx->UART_GTPR = (uartConfig->guardTime << UART_GTPR_GT_POS) |
                       (uartConfig->prescalerValue & HM_UART_GTPR_PSC_MASK);

    // Kiểm tra trạng thái ban đầu (tùy chọn)
    if (UARTx->UART_SR & HM_UART_SR_ORE_MASK) { // Kiểm tra ORE (Overrun error)
        return UART_ERROR; // Báo lỗi nếu có overrun ngay sau khi khởi tạo
    }
    UARTx->UART_CR1 |= HM_UART_CR1_TE_MASK; // Bật bộ truyền (TE)
    UARTx->UART_CR1 |= HM_UART_CR1_RE_MASK; // Bật bộ nhận (RE)
    return UART_OK; // Trả về thành công
}

Error_UART_t TransmitDataUART(UART_Type_t uartx, uint8_t *Data, uint8_t lengthData) {
    volatile UART_Handmade_t *UARTx = UART_List[uartx];
    if (UARTx == NULL || Data == NULL) {
        return UART_ERROR;
    }

    // Kiểm tra UART có sẵn sàng để gửi không (TE phải bật)
    if (!(UARTx->UART_CR1 & HM_UART_CR1_TE_MASK)) {
        return UART_NOT_READY; // UART chưa sẵn sàng để truyền
    }

    // Gửi dữ liệu qua UART
    for (uint8_t idx = 0; idx < lengthData; idx++) {
        while (!(UARTx->UART_SR & HM_UART_SR_TXE_MASK)); // Chờ TXE = 1
        UARTx->UART_DR = Data[idx]; // Gửi dữ liệu
    }

    // Chờ cho đến khi truyền xong toàn bộ dữ liệu (TC = 1)
    while (!(UARTx->UART_SR & HM_UART_SR_TC_MASK));

    return UART_OK;
}

Error_UART_t ReceiveDataUART(UART_Type_t uartx, uint8_t *Data, uint8_t lengthData) {
    volatile UART_Handmade_t *UARTx = UART_List[uartx];
    if (UARTx == NULL || Data == NULL) {
        return UART_ERROR;
    }

    // Kiểm tra xem có dữ liệu trong UART không (RXNE = 1)
    if (!(UARTx->UART_SR & HM_UART_SR_RXNE_MASK)) {
        return UART_NO_DATA; // Không có dữ liệu
    }

    // Đọc dữ liệu khi có dữ liệu sẵn sàng
    for (uint8_t idx = 0; idx < lengthData; idx++) {
        while (!(UARTx->UART_SR & HM_UART_SR_RXNE_MASK)); // Chờ RXNE = 1
        Data[idx] = UARTx->UART_DR; // Lưu dữ liệu nhận được

        // Kiểm tra nếu không còn dữ liệu nữa thì thoát
        if (!(UARTx->UART_SR & HM_UART_SR_RXNE_MASK)) {
            break;
        }
    }

    return UART_OK;
}

Error_UART_t EnableInterrupt_RX_UARTx(UART_Type_t uartx) {
    if (uartx < UART_1 || uartx > UART_3) return UART_ERROR; // Kiểm tra hợp lệ
    
    volatile UART_Handmade_t *UARTx = UART_List[uartx];
    if (UARTx == NULL) return UART_ERROR; // Kiểm tra con trỏ null
    
    Enable_Interrupt_NVIC((Custom_IRQn)(uartx + Custom_USART1_IRQn)); // Bật NVIC
    
    UARTx->UART_CR1 |= HM_UART_CR1_RXNEIE_MASK; // Bật ngắt RXNE
    
    return UART_OK; // Trả về thành công
}

void interruptEnable(UART_Type_t uartx) {
    volatile UART_Handmade_t *UARTx = UART_List[uartx];
    UARTx->UART_CR1 |= HM_UART_CR1_RXNEIE_MASK; // Bật RXNEIE
}

void interruptDisable(UART_Type_t uartx) {
    volatile UART_Handmade_t *UARTx = UART_List[uartx];
    UARTx->UART_CR1 &= ~HM_UART_CR1_RXNEIE_MASK; // Tắt RXNEIE
}

Error_UART_t ReceiveDataUART_IT(UART_Type_t uartx, uint8_t *Buffer_output, uint8_t length) {
    if (uartx < UART_1 || uartx > UART_3 || Buffer_output == NULL || length == 0) {
        return UART_ERROR;
    }

    volatile UART_Handmade_t *UARTx = UART_List[uartx];
    static volatile uint8_t idx = 0; // Biến giữ trạng thái

    // Kiểm tra nếu có dữ liệu đến (RXNE = 1)
    if (UARTx->UART_SR & HM_UART_SR_RXNE_MASK) {
        uint8_t Data = UARTx->UART_DR; // Đọc dữ liệu từ UART

        if (idx < length) { // Chưa nhận đủ dữ liệu
            Buffer_output[idx++] = Data;
        }
        if (idx >= length) {
            idx = 0; // Reset index để nhận dữ liệu mới
            return UART_OK;
        }
    }
    return UART_NO_DATA;
}