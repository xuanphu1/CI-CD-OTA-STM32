#include "SPI_Handmade.h"

volatile SPI_Handmade_t *SPI_List[] = {SPI1_HANDMADE, SPI2_HANDMADE, SPI3_HANDMADE};



SPI_Error_t SPIInit(SPI_Config_t *SPI_Config)
{
    volatile SPI_Handmade_t *SPIx = SPI_List[SPI_Config->SPIx];
    Enable_Clock_RCC_APB2(SPI1_EN_CLK);
    

    if (SPI_Config == NULL)
    {
        return SPI_NULL_PTR;
    }
    if (SPI_Config->SPIx < SPI_1 && SPI_Config->SPIx > SPI_3)
    {
        return SPI_INVALID_PARAM;
    }
    if (SPI_Config->Mode != SPI_MODE_MASTER && SPI_Config->Mode != SPI_MODE_SLAVE)
    {
        SPI_Config->Mode = SPI_MODE_MASTER;
    }

    GPIO_config_t Pin_Sck;
    GPIO_config_t Pin_Mosi;
    GPIO_config_t Pin_Miso;
    GPIO_config_t Pin_Nss;

    switch (SPI_Config->SPIx)
    {
    case SPI_1:
        // Chân SCK cho SPI1
        Pin_Sck.port = Port_A;
        Pin_Sck.pin = PIN_5; // SPI1 SCK

        // Chân MOSI cho SPI1
        Pin_Mosi.port = Port_A;
        Pin_Mosi.pin = PIN_7; // MOSI cho SPI1

        // Chân MISO cho SPI1
        Pin_Miso.port = Port_A;
        Pin_Miso.pin = PIN_6; // MISO cho SPI1

        // Chân NSS cho SPI1
        Pin_Nss.port = Port_A;
        Pin_Nss.pin = PIN_4; // NSS cho SPI1
        break;

    case SPI_2:
        // Chân SCK cho SPI2
        Pin_Sck.port = Port_B;
        Pin_Sck.pin = PIN_13; // SPI2 SCK

        // Chân MOSI cho SPI2
        Pin_Mosi.port = Port_B;
        Pin_Mosi.pin = PIN_15; // MOSI cho SPI2

        // Chân MISO cho SPI2
        Pin_Miso.port = Port_B;
        Pin_Miso.pin = PIN_14; // MISO cho SPI2

        // Chân NSS cho SPI2
        Pin_Nss.port = Port_B;
        Pin_Nss.pin = PIN_12; // NSS cho SPI2
        break;

    case SPI_3:
        // Chân SCK cho SPI3
        Pin_Sck.port = Port_B;
        Pin_Sck.pin = PIN_3; // SPI3 SCK

        // Chân MOSI cho SPI3
        Pin_Mosi.port = Port_B;
        Pin_Mosi.pin = PIN_5; // MOSI cho SPI3

        // Chân MISO cho SPI3
        Pin_Miso.port = Port_B;
        Pin_Miso.pin = PIN_4; // MISO cho SPI3

        // Chân NSS cho SPI3
        Pin_Nss.port = Port_B;
        Pin_Nss.pin = PIN_2; // NSS cho SPI3
        break;
    }

    if (SPI_Config->Mode == SPI_MODE_MASTER)
    {
        Pin_Sck.mode = OUTPUT_MODE_50_MHZ; // Chế độ Master, tốc độ cao
        Pin_Sck.cnf_mode = CNF_MODE_10;    // Alternate function push-pull

        Pin_Mosi.mode = OUTPUT_MODE_50_MHZ; // Chế độ Master, tốc độ cao
        Pin_Mosi.cnf_mode = CNF_MODE_10;    // Alternate function push-pull

        Pin_Miso.mode = INPUT_MODE;      // Chế độ Master
        Pin_Miso.cnf_mode = CNF_MODE_01; // Floating input

        Pin_Nss.mode = OUTPUT_MODE_50_MHZ; // Chế độ Master, tốc độ cao
        Pin_Nss.cnf_mode = CNF_MODE_10;    // Alternate function push-pull
    }
    else
    {
        Pin_Sck.mode = INPUT_MODE;      // Chế độ Slave
        Pin_Sck.cnf_mode = CNF_MODE_01; // Floating input

        Pin_Mosi.mode = INPUT_MODE;      // Chế độ Slave
        Pin_Mosi.cnf_mode = CNF_MODE_01; // Floating input

        Pin_Miso.mode = OUTPUT_MODE_50_MHZ; // Chế độ Slave, tốc độ cao
        Pin_Miso.cnf_mode = CNF_MODE_10;    // Alternate function push-pull

        Pin_Nss.mode = INPUT_MODE;      // Chế độ Slave
        Pin_Nss.cnf_mode = CNF_MODE_01; // Floating input
    }

    InitGPIO(&Pin_Sck);
    InitGPIO(&Pin_Mosi);
    InitGPIO(&Pin_Miso);
    InitGPIO(&Pin_Nss);

    
    SPIx->SPI_CR1 |= (SPI_Config->Data_latch << SPI_CR1_CPHA_POS) | ((SPI_Config->Data_latch >> 1) << SPI_CR1_CPOL_POS);
    SPIx->SPI_CR1 |= SPI_Config->DFF << SPI_CR1_DFF_POS;
    SPIx->SPI_CR1 |= SPI_Config->LSBFIRST << SPI_CR1_LSBFIRST_POS;
    SPIx->SPI_CR1 |= SPI_Config->SSM << SPI_CR1_SSM_POS;

    if (SPI_Config->Mode == SPI_MODE_MASTER)
    {
        SPIx->SPI_CR1 |= SPI_Config->BR << SPI_CR1_BR_POS;
        SPIx->SPI_CR2 |= SPI_Config->SSOE << SPI_CR2_SSOE_POS;
        SPIx->SPI_CR1 |= SPI_CR1_MSTR_MASTER << SPI_CR1_MSTR_POS;
    }
    else
    {
        SPIx->SPI_CR1 &= ~HM_SPI_CR1_MSTR_MASK;
        SPIx->SPI_CR1 |= SPI_CR1_MSTR_SLAVE << SPI_CR1_MSTR_POS;
    }
    SPIx->SPI_CR1 |= SPI_CR1_SPE_ENABLE << SPI_CR1_SPE_POS;

    return SPI_OK;
}

SPI_Error_t SPITransmit(SPI_Config_t *SPI_Config, uint16_t *Data, uint16_t Size)
{
    volatile SPI_Handmade_t *SPIx = SPI_List[SPI_Config->SPIx];
    uint8_t index;
    for (index = 0; index < Size; index++)
    {
        while (!(SPIx->SPI_SR & HM_SPI_SR_TXE_MASK))
            ;
        SPIx->SPI_DR = Data[index];
    }
    return SPI_OK;
}

SPI_Error_t SPIReceive(SPI_Config_t *SPI_Config, uint16_t *Data, uint16_t Size)
{
    volatile SPI_Handmade_t *SPIx = SPI_List[SPI_Config->SPIx];
    uint8_t index;
    for (index = 0; index < Size; index++)
    {
        while (!(SPIx->SPI_SR & HM_SPI_SR_RXNE_MASK))
            ;
        Data[index] = SPIx->SPI_DR;
    }
    return SPI_OK;
}