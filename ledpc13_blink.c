/* 
  Program: Blink LED on PC13 (active-low) with simple delay loop.
 */

#include "stm32f4xx.h"

void delay(volatile uint32_t time){
    while(time--);
}

int main(void) {
    RCC -> AHB1ENR |= (1<<2);
    GPIOC -> MODER |= (1<<26);

    while(1) {
        GPIOC -> ODR &= ~(1<<13);
        delay(200000);
        GPIOC -> ODR |= (1<<13);
        delay(200000);
    }
}
