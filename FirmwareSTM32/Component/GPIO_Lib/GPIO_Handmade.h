#ifndef GPIO_HANDMADE_H
#define GPIO_HANDMADE_H

#include <stdint.h>
#include "RCC_Handmade.h"

// GPIO Base Addresses
#define GPIOA_BASE_HANDMADE 0x40010800UL
#define GPIOB_BASE_HANDMADE 0x40010C00UL
#define GPIOC_BASE_HANDMADE 0x40011000UL
#define GPIOD_BASE_HANDMADE 0x40011400UL
#define GPIOE_BASE_HANDMADE 0x40011800UL
#define GPIOF_BASE_HANDMADE 0x40011C00UL
#define GPIOG_BASE_HANDMADE 0x40012000UL

#define GPIOA_HANDMADE ((volatile GPIO_Handmade_t*)GPIOA_BASE_HANDMADE)
#define GPIOB_HANDMADE ((volatile GPIO_Handmade_t*)GPIOB_BASE_HANDMADE)
#define GPIOC_HANDMADE ((volatile GPIO_Handmade_t*)GPIOC_BASE_HANDMADE)
#define GPIOD_HANDMADE ((volatile GPIO_Handmade_t*)GPIOD_BASE_HANDMADE)
#define GPIOE_HANDMADE ((volatile GPIO_Handmade_t*)GPIOE_BASE_HANDMADE)
#define GPIOF_HANDMADE ((volatile GPIO_Handmade_t*)GPIOF_BASE_HANDMADE)
#define GPIOG_HANDMADE ((volatile GPIO_Handmade_t*)GPIOG_BASE_HANDMADE)

// AFIO Base Address
#define AFIO_BASE_HANDMADE 0x40010000UL
#define AFIO_HANDMADE ((volatile AFIO_Handmade_t*)AFIO_BASE_HANDMADE)

// GPIO Register Structure
typedef struct {
    uint32_t GPIO_CRL;
    uint32_t GPIO_CRH;
    uint32_t GPIO_IDR;
    uint32_t GPIO_ODR;
    uint32_t GPIO_BSRR;
    uint32_t GPIO_BRR;
    uint32_t GPIO_LCKR;
} GPIO_Handmade_t;

// AFIO Register Structure
typedef struct {
    uint32_t EVCR;
    uint32_t MAPR;
    uint32_t EXTICR1;
    uint32_t EXTICR2;
    uint32_t EXTICR3;
    uint32_t EXTICR4;
    uint32_t MAPR2;
} AFIO_Handmade_t;

// GPIO_CRL/CRH Bit Definitions and Masks
// For each pin (0-7 in CRL, 8-15 in CRH)
#define GPIO_CRL_MODE0_POS          0           // MODE0[1:0] position
#define HM_GPIO_CRL_MODE0_MASK      (0x3U << 0) // MODE0[1:0] mask
#define GPIO_CRL_CNF0_POS           2           // CNF0[1:0] position
#define HM_GPIO_CRL_CNF0_MASK       (0x3U << 2) // CNF0[1:0] mask
#define GPIO_CRL_MODE1_POS          4
#define HM_GPIO_CRL_MODE1_MASK      (0x3U << 4)
#define GPIO_CRL_CNF1_POS           6
#define HM_GPIO_CRL_CNF1_MASK       (0x3U << 6)
#define GPIO_CRL_MODE2_POS          8
#define HM_GPIO_CRL_MODE2_MASK      (0x3U << 8)
#define GPIO_CRL_CNF2_POS           10
#define HM_GPIO_CRL_CNF2_MASK       (0x3U << 10)
#define GPIO_CRL_MODE3_POS          12
#define HM_GPIO_CRL_MODE3_MASK      (0x3U << 12)
#define GPIO_CRL_CNF3_POS           14
#define HM_GPIO_CRL_CNF3_MASK       (0x3U << 14)
#define GPIO_CRL_MODE4_POS          16
#define HM_GPIO_CRL_MODE4_MASK      (0x3U << 16)
#define GPIO_CRL_CNF4_POS           18
#define HM_GPIO_CRL_CNF4_MASK       (0x3U << 18)
#define GPIO_CRL_MODE5_POS          20
#define HM_GPIO_CRL_MODE5_MASK      (0x3U << 20)
#define GPIO_CRL_CNF5_POS           22
#define HM_GPIO_CRL_CNF5_MASK       (0x3U << 22)
#define GPIO_CRL_MODE6_POS          24
#define HM_GPIO_CRL_MODE6_MASK      (0x3U << 24)
#define GPIO_CRL_CNF6_POS           26
#define HM_GPIO_CRL_CNF6_MASK       (0x3U << 26)
#define GPIO_CRL_MODE7_POS          28
#define HM_GPIO_CRL_MODE7_MASK      (0x3U << 28)
#define GPIO_CRL_CNF7_POS           30
#define HM_GPIO_CRL_CNF7_MASK       (0x3U << 30)

#define GPIO_CRH_MODE8_POS          0
#define HM_GPIO_CRH_MODE8_MASK      (0x3U << 0)
#define GPIO_CRH_CNF8_POS           2
#define HM_GPIO_CRH_CNF8_MASK       (0x3U << 2)
#define GPIO_CRH_MODE9_POS          4
#define HM_GPIO_CRH_MODE9_MASK      (0x3U << 4)
#define GPIO_CRH_CNF9_POS           6
#define HM_GPIO_CRH_CNF9_MASK       (0x3U << 6)
#define GPIO_CRH_MODE10_POS         8
#define HM_GPIO_CRH_MODE10_MASK     (0x3U << 8)
#define GPIO_CRH_CNF10_POS          10
#define HM_GPIO_CRH_CNF10_MASK      (0x3U << 10)
#define GPIO_CRH_MODE11_POS         12
#define HM_GPIO_CRH_MODE11_MASK     (0x3U << 12)
#define GPIO_CRH_CNF11_POS          14
#define HM_GPIO_CRH_CNF11_MASK      (0x3U << 14)
#define GPIO_CRH_MODE12_POS         16
#define HM_GPIO_CRH_MODE12_MASK     (0x3U << 16)
#define GPIO_CRH_CNF12_POS          18
#define HM_GPIO_CRH_CNF12_MASK      (0x3U << 18)
#define GPIO_CRH_MODE13_POS         20
#define HM_GPIO_CRH_MODE13_MASK     (0x3U << 20)
#define GPIO_CRH_CNF13_POS          22
#define HM_GPIO_CRH_CNF13_MASK      (0x3U << 22)
#define GPIO_CRH_MODE14_POS         24
#define HM_GPIO_CRH_MODE14_MASK     (0x3U << 24)
#define GPIO_CRH_CNF14_POS          26
#define HM_GPIO_CRH_CNF14_MASK      (0x3U << 26) // Sửa từ HM_GPIO_CRH_CNF14_POS
#define GPIO_CRH_MODE15_POS         28
#define HM_GPIO_CRH_MODE15_MASK     (0x3U << 28)
#define GPIO_CRH_CNF15_POS          30
#define HM_GPIO_CRH_CNF15_MASK      (0x3U << 30)

// GPIO_IDR/ODR/BSRR/BRR Bit Definitions and Masks
#define HM_GPIO_IDR_PIN0_MASK       (1U << 0)
#define HM_GPIO_IDR_PIN1_MASK       (1U << 1)
#define HM_GPIO_IDR_PIN2_MASK       (1U << 2)
#define HM_GPIO_IDR_PIN3_MASK       (1U << 3)
#define HM_GPIO_IDR_PIN4_MASK       (1U << 4)
#define HM_GPIO_IDR_PIN5_MASK       (1U << 5)
#define HM_GPIO_IDR_PIN6_MASK       (1U << 6)
#define HM_GPIO_IDR_PIN7_MASK       (1U << 7)
#define HM_GPIO_IDR_PIN8_MASK       (1U << 8)
#define HM_GPIO_IDR_PIN9_MASK       (1U << 9)
#define HM_GPIO_IDR_PIN10_MASK      (1U << 10)
#define HM_GPIO_IDR_PIN11_MASK      (1U << 11)
#define HM_GPIO_IDR_PIN12_MASK      (1U << 12)
#define HM_GPIO_IDR_PIN13_MASK      (1U << 13)
#define HM_GPIO_IDR_PIN14_MASK      (1U << 14)
#define HM_GPIO_IDR_PIN15_MASK      (1U << 15)

// ODR, BSRR, BRR use same bit positions as IDR
#define HM_GPIO_ODR_PIN0_MASK       HM_GPIO_IDR_PIN0_MASK
#define HM_GPIO_ODR_PIN1_MASK       HM_GPIO_IDR_PIN1_MASK
#define HM_GPIO_ODR_PIN2_MASK       HM_GPIO_IDR_PIN2_MASK
#define HM_GPIO_ODR_PIN3_MASK       HM_GPIO_IDR_PIN3_MASK
#define HM_GPIO_ODR_PIN4_MASK       HM_GPIO_IDR_PIN4_MASK
#define HM_GPIO_ODR_PIN5_MASK       HM_GPIO_IDR_PIN5_MASK
#define HM_GPIO_ODR_PIN6_MASK       HM_GPIO_IDR_PIN6_MASK
#define HM_GPIO_ODR_PIN7_MASK       HM_GPIO_IDR_PIN7_MASK
#define HM_GPIO_ODR_PIN8_MASK       HM_GPIO_IDR_PIN8_MASK
#define HM_GPIO_ODR_PIN9_MASK       HM_GPIO_IDR_PIN9_MASK
#define HM_GPIO_ODR_PIN10_MASK      HM_GPIO_IDR_PIN10_MASK
#define HM_GPIO_ODR_PIN11_MASK      HM_GPIO_IDR_PIN11_MASK
#define HM_GPIO_ODR_PIN12_MASK      HM_GPIO_IDR_PIN12_MASK
#define HM_GPIO_ODR_PIN13_MASK      HM_GPIO_IDR_PIN13_MASK
#define HM_GPIO_ODR_PIN14_MASK      HM_GPIO_IDR_PIN14_MASK
#define HM_GPIO_ODR_PIN15_MASK      HM_GPIO_IDR_PIN15_MASK

#define HM_GPIO_BSRR_PIN0_SET       (1U << 0)
#define HM_GPIO_BSRR_PIN1_SET       (1U << 1)
#define HM_GPIO_BSRR_PIN2_SET       (1U << 2)
#define HM_GPIO_BSRR_PIN3_SET       (1U << 3)
#define HM_GPIO_BSRR_PIN4_SET       (1U << 4)
#define HM_GPIO_BSRR_PIN5_SET       (1U << 5)
#define HM_GPIO_BSRR_PIN6_SET       (1U << 6)
#define HM_GPIO_BSRR_PIN7_SET       (1U << 7)
#define HM_GPIO_BSRR_PIN8_SET       (1U << 8)
#define HM_GPIO_BSRR_PIN9_SET       (1U << 9)
#define HM_GPIO_BSRR_PIN10_SET      (1U << 10)
#define HM_GPIO_BSRR_PIN11_SET      (1U << 11)
#define HM_GPIO_BSRR_PIN12_SET      (1U << 12)
#define HM_GPIO_BSRR_PIN13_SET      (1U << 13)
#define HM_GPIO_BSRR_PIN14_SET      (1U << 14)
#define HM_GPIO_BSRR_PIN15_SET      (1U << 15)
#define HM_GPIO_BSRR_PIN0_RESET     (1U << 16)
#define HM_GPIO_BSRR_PIN1_RESET     (1U << 17)
#define HM_GPIO_BSRR_PIN2_RESET     (1U << 18)
#define HM_GPIO_BSRR_PIN3_RESET     (1U << 19)
#define HM_GPIO_BSRR_PIN4_RESET     (1U << 20)
#define HM_GPIO_BSRR_PIN5_RESET     (1U << 21)
#define HM_GPIO_BSRR_PIN6_RESET     (1U << 22)
#define HM_GPIO_BSRR_PIN7_RESET     (1U << 23)
#define HM_GPIO_BSRR_PIN8_RESET     (1U << 24)
#define HM_GPIO_BSRR_PIN9_RESET     (1U << 25)
#define HM_GPIO_BSRR_PIN10_RESET    (1U << 26)
#define HM_GPIO_BSRR_PIN11_RESET    (1U << 27)
#define HM_GPIO_BSRR_PIN12_RESET    (1U << 28)
#define HM_GPIO_BSRR_PIN13_RESET    (1U << 29)
#define HM_GPIO_BSRR_PIN14_RESET    (1U << 30)
#define HM_GPIO_BSRR_PIN15_RESET    (1U << 31)

#define HM_GPIO_BRR_PIN0_MASK       (1U << 0)
#define HM_GPIO_BRR_PIN1_MASK       (1U << 1)
#define HM_GPIO_BRR_PIN2_MASK       (1U << 2)
#define HM_GPIO_BRR_PIN3_MASK       (1U << 3)
#define HM_GPIO_BRR_PIN4_MASK       (1U << 4)
#define HM_GPIO_BRR_PIN5_MASK       (1U << 5)
#define HM_GPIO_BRR_PIN6_MASK       (1U << 6)
#define HM_GPIO_BRR_PIN7_MASK       (1U << 7)
#define HM_GPIO_BRR_PIN8_MASK       (1U << 8)
#define HM_GPIO_BRR_PIN9_MASK       (1U << 9)
#define HM_GPIO_BRR_PIN10_MASK      (1U << 10)
#define HM_GPIO_BRR_PIN11_MASK      (1U << 11)
#define HM_GPIO_BRR_PIN12_MASK      (1U << 12)
#define HM_GPIO_BRR_PIN13_MASK      (1U << 13)
#define HM_GPIO_BRR_PIN14_MASK      (1U << 14)
#define HM_GPIO_BRR_PIN15_MASK      (1U << 15)

// AFIO_MAPR Bit Definitions and Masks
#define AFIO_MAPR_SWJ_CFG_POS       24          // SWJ_CFG[2:0] position
#define HM_AFIO_MAPR_SWJ_CFG_MASK   (0x7U << 24) // SWJ_CFG[2:0] mask
#define HM_AFIO_MAPR_SWJ_CFG_FULL   (0x0U << 24) // Full SWJ (JTAG-DP + SW-DP)
#define HM_AFIO_MAPR_SWJ_CFG_NO_JTAG (0x1U << 24) // JTAG-DP disabled, SW-DP enabled
#define HM_AFIO_MAPR_SWJ_CFG_SWD    (0x2U << 24) // JTAG-DP disabled, SW-DP enabled (SWD only)
#define HM_AFIO_MAPR_SWJ_CFG_NONE   (0x4U << 24) // Both JTAG-DP and SW-DP disabled

// Port Enum
typedef enum {
    Port_A = 0,
    Port_B,
    Port_C,
    Port_D,
    Port_E,
    Port_F,
    Port_G
} Port_t;

// CNF Mode Enum
typedef enum {
    CNF_MODE_00 = 0,
    CNF_MODE_01,
    CNF_MODE_10,
    CNF_MODE_11
} CNF_Mode_t;

// Mode Pin Enum
typedef enum {
    INPUT_MODE = 0,
    OUTPUT_MODE_10_MHZ,
    OUTPUT_MODE_2_MHZ,
    OUTPUT_MODE_50_MHZ
} Mode_Pin_t;

// Pin Enum
typedef enum {
    PIN_0 = 0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7,
    PIN_8,
    PIN_9,
    PIN_10,
    PIN_11,
    PIN_12,
    PIN_13,
    PIN_14,
    PIN_15
} Pin_gpio_t;

// State Pin Enum
typedef enum {
    GPIO_LOW = 0,
    GPIO_HIGH
} State_Pin_t;

// GPIO Configuration Structure
typedef struct {
    Port_t port;
    Pin_gpio_t pin;
    CNF_Mode_t cnf_mode;
    Mode_Pin_t mode;
} GPIO_config_t;

// Error Codes
typedef enum {
    GPIO_OK = 0,
    GPIO_NOT_OK = 1,
    GPIO_ERROR_INVALID_PARAM = 2,
    GPIO_ERROR_NOT_INITIALIZED = 3
} GPIO_Error_t;

// Function Prototypes
GPIO_Error_t InitGPIO(GPIO_config_t *config_gpio);
uint32_t ReadPin(Port_t port, Pin_gpio_t Pin);
GPIO_Error_t WritePin(Port_t port, Pin_gpio_t Pin, uint32_t value);
GPIO_Error_t TogglePin(Port_t port, Pin_gpio_t Pin);
GPIO_Error_t WriteMultiPins(Port_t port, uint32_t pin_mask, uint32_t value);
GPIO_Error_t ReadMultiPins(Port_t port, Pin_gpio_t *pins, uint8_t *output_array, uint8_t pin_count);
void ON_Led_Hardware(void);
void OFF_Led_Hardware(void);

#endif // GPIO_HANDMADE_H