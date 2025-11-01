# STM32F401CCU6 Firmware Collection

This repository contains example codes and firmware modules for the **STM32F401CCU6** microcontroller.  
The project includes code for working with **LEDs, push buttons, ADC (potentiometer and LDR), SysTick, interrupts, and UART communication**.

---

## Overview

These example programs demonstrate basic peripheral interfacing on the STM32F401CCU6, including:

- LED control (GPIO output)
- Push button input handling (GPIO + EXTI)
- Analog-to-Digital Conversion (ADC)
- UART communication (TX/RX)
- SysTick timer
- Interrupt-based event handling
  
---

## Pin Configuration

| Function | Pin  | Port | Notes |
|-----------|------|------|-------|
| **LED 1** | PC13 | GPIOC | Active **LOW** |
| **LED 2** | PC14 | GPIOC | Active **HIGH** |
| **LED 3** | PB9  | GPIOB | Active **HIGH** |
| **Push Button 1** | PA0 | GPIOA | **Also used as Potentiometer input when jumper is connected** |
| **Push Button 2** | PA6 | GPIOA | – |
| **Push Button 3** | PB10 | GPIOB | – |
| **Potentiometer (ADC)** | PA0 | GPIOA | Enabled **only when jumper near pot sensor is connected** |
| **LDR Sensor (ADC)** | PA1 | GPIOA | – |
| **UART TX** | PA2 | GPIOA | UART Transmit |
| **UART RX** | PA3 | GPIOA | UART Receive |

---

