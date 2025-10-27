#include "stm32f4xx.h"   // Include header file for STM32F4xx device definitions

int main(void) {
    RCC -> AHB1ENR |= (1<<2);     // Enable clock for GPIOC by setting bit 2 in AHB1ENR register

    GPIOC -> MODER |= (1<<28);    // Set PC14 mode bit to output (bit 28 = 1, bit 29 = 0 → 01 = output mode)

    GPIOC -> ODR &= ~(1<<13);     // Clear bit 13 of output data register (set PC13 output to LOW)
}