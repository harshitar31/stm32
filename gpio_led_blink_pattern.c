#include "stm32f4xx.h"

// Simple delay function to create a time delay
void delay(volatile uint32_t time){
    while(time--);  // Decrements the time variable until it reaches zero
}

int main(void){
    // 1. Enable clock for GPIOC (for LED control) and GPIOB (for another LED control)
    RCC -> AHB1ENR |= (1 << 2);  // Enable GPIOC clock
    RCC -> AHB1ENR |= (1 << 1);  // Enable GPIOB clock

    // 2. Set PC13 and PC14 as output (LED control)
    GPIOC -> MODER |= (1 << 26); // Set PC13 as output
    GPIOC -> MODER |= (1 << 28); // Set PC14 as output

    // 3. Set PB9 as output (LED control)
    GPIOB -> MODER |= (1 << 18); // Set PB9 as output

    while(1){
        // 4. Turn off all LEDs to start with
        GPIOC -> ODR &= ~(1 << 13);  // Turn off PC13 LED
        GPIOB -> ODR &= ~(1 << 9);   // Turn off PB9 LED
        GPIOC -> ODR &= ~(1 << 14);  // Turn off PC14 LED
        delay(1000000);              // Delay to observe the state
        
        // 5. Blink PC13 LED 3 times (on/off) with delay in between
        for(int i = 0; i < 3; i++){
            GPIOC -> ODR &= ~(1 << 13);  // Turn off PC13 LED
            delay(300000);               // Delay
            GPIOC -> ODR |= (1 << 13);   // Turn on PC13 LED
            delay(300000);               // Delay
        }

        // 6. Turn on PC13 and PB9 LEDs, and turn off PC14 LED
        GPIOC -> ODR |= (1 << 13);   // Turn on PC13 LED
        GPIOB -> ODR |= (1 << 9);    // Turn on PB9 LED
        GPIOC -> ODR &= ~(1 << 14);  // Turn off PC14 LED
        delay(1000000);              // Delay to observe the state

        // 7. Blink PB9 LED 3 times (on/off) with delay in between
        for(int i = 0; i < 3; i++){
            GPIOB -> ODR |= (1 << 9);    // Turn on PB9 LED
            delay(300000);               // Delay
            GPIOB -> ODR &= ~(1 << 9);   // Turn off PB9 LED
            delay(300000);               // Delay
        }

        // 8. Turn on PC13 and turn off PB9, then turn on PC14
        GPIOC -> ODR |= (1 << 13);   // Turn on PC13 LED
        GPIOB -> ODR &= ~(1 << 9);   // Turn off PB9 LED
        GPIOC -> ODR |= (1 << 14);   // Turn on PC14 LED
        delay(1000000);              // Delay to observe the state

        // 9. Blink PC14 LED 3 times (on/off) with delay in between
        for(int i = 0; i < 3; i++){
            GPIOC -> ODR |= (1 << 14);  // Turn on PC14 LED
            delay(300000);              // Delay
            GPIOC -> ODR &= ~(1 << 14); // Turn off PC14 LED
            delay(300000);              // Delay
        }
    }
}
