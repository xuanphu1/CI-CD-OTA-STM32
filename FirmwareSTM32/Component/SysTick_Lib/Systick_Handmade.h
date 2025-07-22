#ifndef SYSTICK_HANDMADE_H
#define SYSTICK_HANDMADE_H

#include "stdint.h"
#include "RCC_Handmade.h"

// SysTick register structure for Cortex-M3 (STM32F103)
typedef struct {
    volatile uint32_t SYST_CSR;   // 0xE000E010 - Control and Status Register (RW)
    volatile uint32_t SYST_RVR;   // 0xE000E014 - Reload Value Register (RW)
    volatile uint32_t SYST_CVR;   // 0xE000E018 - Current Value Register (RW)
    volatile uint32_t SYST_CALIB; // 0xE000E01C - Calibration Value Register (RO)
} SysTick_Handmade_t;

// Base address of SysTick in Cortex-M3
#define SYSTICK_BASE_ADDRESS 0xE000E010UL
#define SYSTICK_HANDMADE ((volatile SysTick_Handmade_t*)SYSTICK_BASE_ADDRESS)

// SysTick counter enable (ENABLE, bit 0, SYST_CSR)
typedef enum {
    SYST_CSR_ENABLE_DISABLE = 0x00, // Counter disabled
    SYST_CSR_ENABLE_ENABLE = 0x01   // Counter enabled
} SysTick_CSR_Enable_t;

// SysTick interrupt enable (TICKINT, bit 1, SYST_CSR)
typedef enum {
    SYST_CSR_TICKINT_DISABLE = 0x00, // No interrupt on count to 0
    SYST_CSR_TICKINT_ENABLE = 0x01   // Interrupt on count to 0
} SysTick_CSR_TickInt_t;

// SysTick clock source (CLKSOURCE, bit 2, SYST_CSR)
typedef enum {
    SYST_CSR_CLKSOURCE_EXTERNAL = 0x00, // External clock (HCLK/8)
    SYST_CSR_CLKSOURCE_PROCESSOR = 0x01 // Processor clock (HCLK)
} SysTick_CSR_ClockSource_t;

// SysTick count flag (COUNTFLAG, bit 16, SYST_CSR, read-only)
typedef enum {
    SYST_CSR_COUNTFLAG_NO = 0x00,  // Timer has not counted to 0
    SYST_CSR_COUNTFLAG_YES = 0x01  // Timer has counted to 0
} SysTick_CSR_CountFlag_t;

// SysTick error codes
typedef enum {
    SYSTICK_OK = 0,
    SYSTICK_ERROR_INVALID_PARAM = 1,
    SYSTICK_ERROR_NOT_INITIALIZED = 2
} SysTick_Error_t;

// SysTick configuration structure
typedef struct {
    SysTick_CSR_ClockSource_t SysTick_Source; // Clock source (HCLK or HCLK/8)
    SysTick_CSR_TickInt_t Generate_interrupt; // Interrupt enable
    SysTick_CSR_Enable_t EnableCounter;       // Counter enable
    uint32_t ValueInitReload;                 // Reload value (0 to 0xFFFFFF)
} SysTick_Config_t;

// Bit manipulation macros for SYST_CSR
#define HM_SYST_CSR_ENABLE_POS      (0U)
#define HM_SYST_CSR_ENABLE_MASK     (0x1U << HM_SYST_CSR_ENABLE_POS)
#define HM_SYST_CSR_TICKINT_POS     (1U)
#define HM_SYST_CSR_TICKINT_MASK    (0x1U << HM_SYST_CSR_TICKINT_POS)
#define HM_SYST_CSR_CLKSOURCE_POS   (2U)
#define HM_SYST_CSR_CLKSOURCE_MASK  (0x1U << HM_SYST_CSR_CLKSOURCE_POS)
#define HM_SYST_CSR_COUNTFLAG_POS   (16U)
#define HM_SYST_CSR_COUNTFLAG_MASK  (0x1U << HM_SYST_CSR_COUNTFLAG_POS)
#define HM_SYST_CSR_COUNTFLAG_GET   ((SYSTICK_HANDMADE->SYST_CSR & HM_SYST_CSR_COUNTFLAG_MASK) >> HM_SYST_CSR_COUNTFLAG_POS)

// External millisecond counter
extern volatile uint32_t SysTick_ms;

// Function prototypes
void SysTick_ms_inc(void);
SysTick_Error_t SysTick_Init(SysTick_Config_t *systickConfig);
SysTick_Error_t Delay_SysTick(uint32_t value_ms);
SysTick_Error_t SysTick_GetCounter(uint32_t *counter);

#endif // SYSTICK_HANDMADE_H