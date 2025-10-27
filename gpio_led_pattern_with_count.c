#include "stm32f4xx.h"

// Simple delay function to create a time delay
void delay(volatile uint32_t time){
    while(time--);  // Decrements the time variable until it reaches zero
}

int main(void){
    int count = 0;
    
    // 1. Enable clock for GPIOC (for LED control) and GPIOB (for another LED control)
    RCC -> AHB1ENR |= (1 << 2);  // Enable GPIOC clock
    RCC -> AHB1ENR |= (1 << 1);  // Enable GPIOB clock

    // 2. Set PC13 and PC14 as output (LED control)
    GPIOC -> MODER |= (1 << 26); // Set PC13 as output
    GPIOC -> MODER |= (1 << 28); // Set PC14 as output

    // 3. Set PB9 as output (LED control)
    GPIOB -> MODER |= (1 << 18); // Set PB9 as output
    
    while(1){
        // 4. Reset count value periodically (counts from 0 to 99999)
        count = count % 100000;
        
        // 5. Turn off PC13 and turn on PB9, then turn on PC14
        GPIOC -> ODR &= ~(1 << 13); // Turn off PC13 LED
        GPIOB -> ODR |= (1 << 9);   // Turn on PB9 LED
        GPIOC -> ODR |= (1 << 14);  // Turn on PC14 LED

        // 6. If count reaches 75000, turn off PC14 and create a delay
        if (count == 75000) {
            GPIOC -> ODR &= ~(1 << 14); // Turn off PC14 LED
            delay(500000);              // Delay for a noticeable effect
        }

        // 7. If count reaches 50000, turn off PB9 and create a delay
        if (count == 50000) {
            GPIOB -> ODR &= ~(1 << 9);  // Turn off PB9 LED
            delay(500000);              // Delay for a noticeable effect
        }

        // 8. If count reaches 10000, turn on PC13 and create a delay
        if (count == 10000) {
            GPIOC -> ODR |= (1 << 13);  // Turn on PC13 LED
            delay(500000);              // Delay for a noticeable effect
        }

        // 9. Increment the count value
        count++;
    }
}
