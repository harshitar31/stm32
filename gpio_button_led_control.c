#include "stm32f4xx.h"

// Simple delay function to create a time delay
void delay(volatile uint32_t time){
    while(time--);  // Decrements the time variable until it reaches zero
}

int main(void) {
    // 1. Enable clocks for GPIOA, GPIOB, and GPIOC
    RCC->AHB1ENR |= (1U << 0);  // Enable GPIOA clock
    RCC->AHB1ENR |= (1U << 1);  // Enable GPIOB clock
    RCC->AHB1ENR |= (1U << 2);  // Enable GPIOC clock

    // 2. Configure GPIOC pins 13 and 14 as output
    GPIOC->MODER &= ~(3U << 26); // Set PC13 as output
    GPIOC->MODER &= ~(3U << 28); // Set PC14 as output

    // 3. Configure GPIOB pin 9 as output
    GPIOB->MODER &= ~(3U << 18); // Set PB9 as output

    // 4. Configure GPIOA and GPIOB pins as input with pull-up resistors
    GPIOA->PUPDR &= ~(3U << 0);   // Clear pull-up/down bits for PA0
    GPIOA->PUPDR &= ~(3U << 12);  // Clear pull-up/down bits for PA6
    GPIOB->PUPDR &= ~(3U << 20);  // Clear pull-up/down bits for PB10
    
    GPIOA->PUPDR |= (1U << 0);    // Enable pull-up on PA0
    GPIOA->PUPDR |= (1U << 12);   // Enable pull-up on PA6
    GPIOB->PUPDR |= (1U << 20);   // Enable pull-up on PB10

    // 5. Set GPIOC and GPIOB pins 13, 14, and 9 as output
    GPIOC->MODER |= (1U << 26);   // Set PC13 as output
    GPIOC->MODER |= (1U << 28);   // Set PC14 as output
    GPIOB->MODER |= (1U << 18);   // Set PB9 as output

    while (1) {
        // 6. Check if the button on PA0 is pressed (active low)
        if (!(GPIOA->IDR & (1U << 0))) {
            GPIOC->ODR &= ~(1U << 14);   // Turn off PC14 (LED)
            GPIOB->ODR &= ~(1U << 9);    // Turn off PB9 (LED)
            
            // 7. Blink PC13 (LED) until another button press is detected
            while (1) {
                GPIOC->ODR &= ~(1U << 13);  // Turn off PC13
                delay(500000);              // Delay
                GPIOC->ODR |= (1U << 13);   // Turn on PC13
                delay(500000);              // Delay
                
                // 8. Exit blinking loop if PA6 or PB10 is pressed (active low)
                if (!(GPIOA->IDR & (1U << 6)) || !(GPIOB->IDR & (1U << 10))) {
                    break;
                }
            }
        }
        // 9. Check if the button on PA6 is pressed (active low)
        else if (!(GPIOA->IDR & (1U << 6))) {
            GPIOC->ODR |= (1U << 13);    // Turn on PC13 (LED)
            GPIOB->ODR &= ~(1U << 9);    // Turn off PB9 (LED)
            
            // 10. Blink PC14 (LED) until another button press is detected
            while (1) {
                GPIOC->ODR |= (1U << 14);  // Turn on PC14
                delay(500000);              // Delay
                GPIOC->ODR &= ~(1U << 14);  // Turn off PC14
                delay(500000);              // Delay
                
                // 11. Exit blinking loop if PA0 or PB10 is pressed (active low)
                if (!(GPIOA->IDR & (1U << 0)) || !(GPIOB->IDR & (1U << 10))) {
                    break;
                }
            }
        }
        // 12. Check if the button on PB10 is pressed (active low)
        else if (!(GPIOB->IDR & (1U << 10))) {
            GPIOC->ODR |= (1U << 13);    // Turn on PC13 (LED)
            GPIOC->ODR &= ~(1U << 14);   // Turn off PC14 (LED)
            
            // 13. Blink PB9 (LED) until another button press is detected
            while (1) {
                GPIOB->ODR |= (1U << 9);   // Turn on PB9
                delay(500000);              // Delay
                GPIOB->ODR &= ~(1U << 9);   // Turn off PB9
                delay(500000);              // Delay
                
                // 14. Exit blinking loop if PA0 or PA6 is pressed (active low)
                if (!(GPIOA->IDR & (1U << 0)) || !(GPIOA->IDR & (1U << 6))) {
                    break;
                }
            }
        }
    }
    return 0;  // Never reached
}
