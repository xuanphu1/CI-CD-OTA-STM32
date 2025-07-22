# STM32_Framework_Application_RTOS_CMSIS

## 📚 Overview

This project is a **modular STM32 firmware framework** designed for ARM Cortex-M3 microcontrollers, featuring a **handmade RTOS implementation** (CMSIS-compliant), complete with peripheral drivers and multitasking support.  
It is organized for clarity, portability, and ease of extension, making it suitable as a foundation for research, embedded education, and real-world firmware projects.

---

## 🗂️ Directory Structure

STM32_Framework_Application_RTOS_CMSIS/
├── .vscode/ # Editor configs (optional)
├── Component/ # Modular peripheral and RTOS libraries
│ ├── Adc_Lib/ # ADC driver (Handmade)
│ ├── Cortex_m3/ # ARM Cortex-M3 core helpers
│ ├── DMA_Lib/ # DMA driver (Handmade)
│ ├── Flash_Lib/ # FLASH memory operations
│ ├── FreeRTOS/ # Mini-RTOS: kernel, scheduler, context switch
│ ├── GPIO_Lib/ # GPIO driver
│ ├── InitSystemPeripheral/ # System initialization logic
│ ├── MutexRTOS/ # RTOS Mutex primitives
│ ├── Nvic_Lib/ # NVIC (interrupt controller) helpers
│ ├── QueueRTOS/ # RTOS Queue primitives
│ ├── RCC_Lib/ # Clock system (RCC) configuration
│ ├── SCB_Base/ # SCB (System Control Block) helpers
│ ├── SPI_Lib/ # SPI driver
│ ├── SysTick_Lib/ # SysTick timer functions
│ ├── Syscall/ # System call handlers
│ ├── Timer_Lib/ # Timer (TIM) driver
│ ├── UartDataManager/ # UART data management logic
│ └── Uart_Lib/ # UART driver
├── main/ # Application entry point and startup
│ ├── STM32_Startup.c # Reset handler, vector table, init code
│ ├── main.c # Main application code
│ ├── main.h
│ └── stm32f103xx_Linker.ld # Linker script for STM32F103 series
├── Output/ # Build artifacts (object files, .elf, .hex, map)
├── debug/ # Debug and ST-Link utility files
│ └── ST-LINKUtility/ # ST-Link loader and example projects
├── Makefile # Project build system (GNU Make)

---

## ✨ Main Features

- **CMSIS-based, modular STM32 firmware framework**
- **Custom RTOS kernel**: Cooperative/Preemptive scheduling, context switch via PendSV/SVC
- **Peripheral drivers** (ADC, DMA, GPIO, SPI, UART, Timer, RCC, NVIC, Flash, SysTick, etc.) – All written from scratch
- **RTOS Primitives**: Queues, Mutexes, System Calls, Task management
- **Application-ready**: Clean separation between hardware abstraction, kernel, and user code
- **Full build via Makefile**: Reproducible builds, easy debugging, portable to other toolchains

---

## ⚡️ Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/yourusername/STM32_Framework_Application_RTOS_CMSIS.git
cd STM32_Framework_Application_RTOS_CMSIS
2. Toolchain Requirements
ARM GCC Toolchain (arm-none-eabi-gcc, make)

(Optional) ST-Link Utility for flashing/debugging

STM32F103 (or compatible Cortex-M3) microcontroller

3. Build the Project
make
Build outputs (.elf, .hex, map file, logs, and object files) will be placed in Output/

4. Flash Firmware
Use ST-Link Utility or st-flash:
st-flash write Output/STM32_RUN.hex 0x08000000
Or use your preferred tool to program the device.

5. Debug
Connect via SWD/JTAG and debug with GDB, Keil, or STM32CubeIDE as needed.

RTOS context switch and debugging support is included.

🧩 Components and Key Modules
Module	Purpose
FreeRTOS/	Mini-RTOS kernel, task management, context switch (ASM)
MutexRTOS/	Mutex (mutual exclusion) primitives
QueueRTOS/	Queue/message passing primitives
Adc_Lib/	ADC peripheral driver (polling/interrupt)
DMA_Lib/	DMA controller driver
Timer_Lib/	Timer peripheral driver
GPIO_Lib/	General Purpose I/O driver
Uart_Lib/	UART/USART peripheral driver
UartDataManager/	UART data handler (buffers, callbacks)
SPI_Lib/	SPI protocol driver
RCC_Lib/	Clock setup and management
SysTick_Lib/	System timer handling
Nvic_Lib/	Nested vector interrupt controller helpers
SCB_Base/	System Control Block access
Syscall/	System call and privilege management
InitSystemPeripheral/	Startup, peripheral and system configuration

🔎 Example Usage
User application code goes in main/main.c

All hardware setup (clocks, GPIO, interrupts) can be performed using initialization libraries from Component/

To create new RTOS tasks, use the APIs provided in FreeRTOS_Handmade.h

Synchronize tasks with mutexes (MutexRTOS) and queues (QueueRTOS)

🛠 Build and Toolchain Notes
Makefile is provided for out-of-the-box builds using GCC/Make

Adjust MCU, linker script, and toolchain settings in Makefile and main/stm32f103xx_Linker.ld for your target device

All drivers are written for register-level access—no HAL/LL dependency

Assembly file switch.S is used for context switch (PendSV handler)

📝 Customization
Add new drivers or RTOS features by following the modular structure in Component/

Extend or replace main.c with your application logic

Support for new STM32 chips by updating the linker script and startup files

🧠 Learning & Research Value
This framework is ideal for:

Learning ARM Cortex-M3 programming

Studying how a real RTOS is implemented at low level

Experimenting with embedded systems, multitasking, and drivers

Using as a base for university, research, or hobbyist projects

🧪 Example: Creating a Task (in main.c)
#include "FreeRTOS_Handmade.h"

void MyTask(void* params) {
    while (1) {
        // Your task code
    }
}

int main(void) {
    SystemInit(); // From InitSystemPeripheral
    OS_TaskCreate(MyTask, NULL, ...);
    OS_StartScheduler();
    while (1);
}
📜 License
This project is open-source and provided for education and non-commercial use.

👨‍💻 Credits
Developed by [Your Name or Team]

Inspired by official STM32 reference manual, CMSIS, and open-source embedded communities.

---

**Instructions:**  
- Copy everything between the triple backticks into your README.md.  
- Replace `[Your Name or Team]` as appropriate.  
- You can further expand any section, add build badges, or insert diagrams as needed!