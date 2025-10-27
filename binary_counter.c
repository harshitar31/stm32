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
        // Outer loop to toggle LED on GPIOC pin 13
        for(int i = 0; i <= 1; i++){
            if(i == 0) 
                GPIOC -> ODR |= (1<<13);  // Turn on LED on GPIOC pin 13
            else 
                GPIOC -> ODR &= ~(1<<13); // Turn off LED on GPIOC pin 13
            
            // Middle loop to toggle LED on GPIOC pin 14
            for(int j = 0; j <= 1; j++){
                if(j == 0) 
                    GPIOC -> ODR &= ~(1<<14); // Turn off LED on GPIOC pin 14
                else 
                    GPIOC -> ODR |= (1<<14);  // Turn on LED on GPIOC pin 14
                
                // Inner loop to toggle LED on GPIOB pin 9
                for(int k = 0; k <= 1; k++){
                    if(k == 0) 
                        GPIOB -> ODR &= ~(1<<9);  // Turn off LED on GPIOB pin 9
                    else 
                        GPIOB -> ODR |= (1<<9);   // Turn on LED on GPIOB pin 9
                    
                    delay(2000000);  // Delay to maintain LED states
                }
                delay(1000000);  // Delay to maintain LED state for pin 14
            }
            delay(900000);  // Delay to maintain LED state for pin 13
        }
    }
}
