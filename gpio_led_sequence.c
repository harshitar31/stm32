#include "stm32f4xx.h"  // Include STM32F4 header file for hardware register access

// Delay function: a simple delay loop
void delay(volatile uint32_t time){
    while(time--);  // Decrease the time variable until it reaches 0, creating a delay
}

int main(void){
    // Enable the clock for GPIOC and GPIOB
    RCC -> AHB1ENR |= (1<<2);  // Enable clock for GPIOC (bit 2 of AHB1ENR)
    GPIOC -> MODER |= (1<<26); // Set pin 13 of GPIOC as output (MODER register for pin 13)
    
    RCC -> AHB1ENR |= (1<<2);  // Redundant: GPIOC clock already enabled
    GPIOC -> MODER |= (1<<28); // Set pin 14 of GPIOC as output (MODER register for pin 14)

    RCC -> AHB1ENR |= (1<<1);  // Enable clock for GPIOB (bit 1 of AHB1ENR)
    GPIOB -> MODER |= (1<<18); // Set pin 9 of GPIOB as output (MODER register for pin 9)
    
    while(1){  // Infinite loop to keep running the program
        // Turn off LED on GPIOC pin 13, and turn on LED on GPIOC pin 14
        GPIOC -> ODR &= ~(1<<13);
        GPIOC -> ODR |= (1<<14);
        
        // Turn on LED on GPIOB pin 9
        GPIOB -> ODR |= (1<<9);
        
        delay(500000);  // Delay to maintain LED states

        // Turn off LED on GPIOB pin 9
        GPIOB -> ODR &= ~(1<<9);
        
        // Turn off LED on GPIOC pin 14, and turn on LED on GPIOC pin 13
        GPIOC -> ODR &= ~(1<<14);
        GPIOC -> ODR |= (1<<13);
        
        delay(500000);  // Delay to maintain LED states
    }
}
