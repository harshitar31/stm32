#include "stm32f4xx.h"

int main(void) {

    // Enable clock for GPIOB (port B) and GPIOC (port C)
    RCC->AHB1ENR |= (1U << 1);  // Enable GPIOB clock
    RCC->AHB1ENR |= (1U << 2);  // Enable GPIOC clock

    // Configure GPIOB pin 10 as input (button)
    GPIOB->MODER &= ~(1U << 20);  // Clear bits for pin 10 to set as input
    
    // Configure GPIOC pin 14 as output (LED)
    GPIOC->MODER |= (1U << 28);   // Set pin 14 as output
    GPIOC->MODER &= ~(1U << 29);  // Clear bit for pin 14 to ensure output mode
    
    // Configure GPIOB pin 10 pull-up resistor
    GPIOB->PUPDR &= ~(3U << 20);  // Clear previous pull-up/pull-down setting
    GPIOB->PUPDR |= (1U << 20);   // Enable pull-up on pin 10

    // Infinite loop to check button state and control LED
    while (1) {

        // Check if button on GPIOB pin 10 is pressed
        if (GPIOB->IDR & (1U << 10)) {
            // If button is pressed, turn off LED (GPIOC pin 14)
            GPIOC->ODR &= ~(1U << 14);
        } else {
            // If button is not pressed, turn on LED (GPIOC pin 14)
            GPIOC->ODR |= (1U << 14);
        }
    }
}
