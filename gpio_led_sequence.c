/* 
 Program: Alternate blinking of LEDs on PC13 (active-low), PC14, and PB9 with delays.
 */

#include "stm32f4xx.h"

void delay(volatile uint32_t time){
    while(time--);
}

int main(void){
    RCC -> AHB1ENR |= (1<<2);
    GPIOC -> MODER |= (1<<26);
    
    RCC -> AHB1ENR |= (1<<2);
    GPIOC -> MODER |= (1<<28);

    RCC -> AHB1ENR |= (1<<1);
    GPIOB -> MODER |= (1<<18);
    
    while(1){
        GPIOC -> ODR &= ~(1<<13);
        GPIOC -> ODR |= (1<<14);
        
        GPIOB -> ODR |= (1<<9);
        
        delay(500000);

        GPIOB -> ODR &= ~(1<<9);
        
        GPIOC -> ODR &= ~(1<<14);
        GPIOC -> ODR |= (1<<13);
        
        delay(500000);
    }
}
