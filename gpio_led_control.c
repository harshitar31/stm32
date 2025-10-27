#include "stm32f4xx.h"

// Simple delay function to create a time delay
void delay(volatile uint32_t time){
    while(time--);  // Loop to create delay by decrementing time
}

int main(void){
    int count = 0;
    
    // 1. Enable clock for GPIOC (for LED control) and GPIOB (for another LED control)
    RCC -> AHB1ENR |= (1 << 2);  // Enable GPIOC clock
    RCC -> AHB1ENR |= (1 << 1);  // Enable GPIOB clock

    // 2. Set PC13 and PC14 as output (for controlling LEDs)
    GPIOC -> MODER |= (1 << 26); // Set PC13 as output
    GPIOC -> MODER |= (1 << 28); // Set PC14 as output

    // 3. Set PB9 as output (for controlling LED)
    GPIOB -> MODER |= (1 << 18); // Set PB9 as output
    
    while(1){
        count = 23;  // Initialize count variable

        // 4. Turn off LEDs (initial state)
        GPIOC -> ODR &= ~(1 << 14);  // Turn off PC14 LED
        GPIOB -> ODR &= ~(1 << 9);   // Turn off PB9 LED
        GPIOC -> ODR |= (1 << 13);   // Turn on PC13 LED

        // 5. Toggle behavior based on count (odd/even)
        if(count % 2 == 0){
            // If count is even, turn off PC13 LED
            GPIOC -> ODR &= ~(1 << 13);  // Turn off PC13 LED
        }
        else{
            // If count is odd, turn on PB9 LED and PC14 LED
            GPIOB -> ODR |= (1 << 9);    // Turn on PB9 LED
            GPIOC -> ODR |= (1 << 14);   // Turn on PC14 LED
        }

        // Optionally, a delay can be added here to observe LED behavior
        // delay(1000000);  // Uncomment for delay between toggles (optional)
    }
}
