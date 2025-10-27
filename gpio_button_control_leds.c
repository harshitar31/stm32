#include "stm32f4xx.h"

int main(void) {
    // 1. Enable clocks for GPIOA, GPIOB, and GPIOC
    RCC->AHB1ENR |= (1U << 0);  // Enable GPIOA clock
    RCC->AHB1ENR |= (1U << 1);  // Enable GPIOB clock
    RCC->AHB1ENR |= (1U << 2);  // Enable GPIOC clock

    // 2. Configure GPIOC pins 13 and 14 as output (LED control)
    GPIOC->MODER &= ~(3U << 26); // Set PC13 as output
    GPIOC->MODER &= ~(3U << 28); // Set PC14 as output

    // 3. Configure GPIOB pin 9 as output (LED control)
    GPIOB->MODER &= ~(3U << 18); // Set PB9 as output

    // 4. Configure GPIOA pins 0 and 6 as input with pull-up resistors
    GPIOA->PUPDR &= ~(3U << 0);   // Clear pull-up/down bits for PA0
    GPIOA->PUPDR &= ~(3U << 12);  // Clear pull-up/down bits for PA6
    GPIOB->PUPDR &= ~(3U << 20);  // Clear pull-up/down bits for PB10
    
    GPIOA->PUPDR |= (1U << 0);    // Enable pull-up on PA0
    GPIOA->PUPDR |= (1U << 12);   // Enable pull-up on PA6
    GPIOB->PUPDR |= (1U << 20);   // Enable pull-up on PB10

    // 5. Set GPIOC pins 13, 14 and GPIOB pin 9 as output
    GPIOC->MODER |= (1U << 26);   // Set PC13 as output
    GPIOC->MODER |= (1U << 28);   // Set PC14 as output
    GPIOB->MODER |= (1U << 18);   // Set PB9 as output

    while (1) {
        // 6. Condition for PA0 pressed, PA6 pressed, and PB10 pressed
        // Turn off PC13, PC14, and PB9 LEDs
        if (!(GPIOA->IDR & (1U << 0)) && (GPIOA->IDR & (1U << 6)) && (GPIOB->IDR & (1U << 10))) {
            GPIOC->ODR &= ~(1U << 13);   // Turn off PC13
            GPIOC->ODR &= ~(1U << 14);   // Turn off PC14
            GPIOB->ODR &= ~(1U << 9);    // Turn off PB9
        } 
        // 7. Condition for PA0 pressed, PA6 not pressed, and PB10 pressed
        // Turn on PC13 and PC14 LEDs, and turn off PB9 LED
        else if ((GPIOA->IDR & (1U << 0)) && !(GPIOA->IDR & (1U << 6)) && (GPIOB->IDR & (1U << 10))) {
            GPIOC->ODR |= (1U << 13);    // Turn on PC13
            GPIOC->ODR |= (1U << 14);    // Turn on PC14
            GPIOB->ODR &= ~(1U << 9);   // Turn off PB9
        }
        // 8. Condition for PA0 pressed, PA6 pressed, and PB10 not pressed
        // Turn on PC13, turn off PC14, and turn on PB9
        if ((GPIOA->IDR & (1U << 0)) && (GPIOA->IDR & (1U << 6)) && !(GPIOB->IDR & (1U << 10))) {
            GPIOC->ODR |= (1U << 13);   // Turn on PC13
            GPIOC->ODR &= ~(1U << 14);  // Turn off PC14
            GPIOB->ODR |= (1U << 9);    // Turn on PB9
        }
    }
    return 0;  // Never reached
}
