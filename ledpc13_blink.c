#include "stm32f4xx.h"   // Include the STM32F4xx device-specific header for peripheral and register definitions

// Simple delay function (busy-wait)
void delay(volatile uint32_t time){
    while(time--);    // Decrement 'time' until it reaches 0, creating a delay
}

int main(void) {
    // Enable clock for GPIOC by setting bit 2 in the AHB1ENR register
    RCC -> AHB1ENR |= (1<<2);

    // Set PC13 as output mode (bits 26-27 control pin mode for PC13)
    GPIOC -> MODER |= (1<<26);  // Set PC13 as output (binary 01 for output mode)

    // Infinite loop to toggle PC13 (used for blinking an LED or output toggling)
    while(1) {
        // Set PC13 to LOW (turn off LED or set output to LOW)
        GPIOC -> ODR &= ~(1<<13);

        // Call delay function with a time value for visible blinking (busy-wait)
        delay(200000);  // Wait for a while (adjust for blink rate)

        // Set PC13 to HIGH (turn on LED or set output to HIGH)
        GPIOC -> ODR |= (1<<13);

        // Call delay function again to keep LED on for a while
        delay(200000);  // Wait for a while
    }
}
