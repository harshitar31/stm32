#include "stm32f4xx.h"  // Include STM32F4 header file for hardware register access

// Delay function: a simple delay loop
void delay(volatile uint32_t time){
    while(time--);  // Decrease the time variable until it reaches 0, creating a delay
}

int main(void){
    // Enable the clock for GPIOC (port C) and GPIOB (port B)
    RCC -> AHB1ENR |= (1<<2);  // Enable clock for GPIOC (bit 2 of AHB1ENR)
    GPIOC -> MODER |= (1<<26); // Set pin 13 of GPIOC as output (MODER register for pin 13)
    
    RCC -> AHB1ENR |= (1<<1);  // Enable clock for GPIOB (bit 1 of AHB1ENR)
    GPIOB -> MODER |= (1<<18); // Set pin 9 of GPIOB as output (MODER register for pin 9)
    
    while(1){  // Infinite loop to keep running the program
        GPIOC -> ODR &= ~(1<<13);  // Set GPIOC pin 13 low (turn off LED connected to pin 13)
        delay(200000);  // Delay to maintain LED state
        
        GPIOB -> ODR |= (1<<9);    // Set GPIOB pin 9 high (turn on LED connected to pin 9)
        delay(300000);  // Delay to maintain LED state
        
        GPIOB -> ODR &= ~(1<<9);   // Set GPIOB pin 9 low (turn off LED connected to pin 9)
        delay(300000);  // Delay to maintain LED state
        
        GPIOC -> ODR |= (1<<13);   // Set GPIOC pin 13 high (turn on LED connected to pin 13)
        delay(200000);  // Delay to maintain LED state
    }
}
