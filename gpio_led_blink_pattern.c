/* 
 Program: LED blinking sequence on PC13 (active-low), PC14, and PB9 with timed patterns and loops.
 */

#include "stm32f4xx.h"

void delay(volatile uint32_t time){
    while(time--);
}

int main(void){
    RCC -> AHB1ENR |= (1 << 2);
    RCC -> AHB1ENR |= (1 << 1);

    GPIOC -> MODER |= (1 << 26);
    GPIOC -> MODER |= (1 << 28);
    GPIOB -> MODER |= (1 << 18);

    while(1){
        GPIOC -> ODR &= ~(1 << 13);
        GPIOB -> ODR &= ~(1 << 9);
        GPIOC -> ODR &= ~(1 << 14);
        delay(1000000);
        
        for(int i = 0; i < 3; i++){
            GPIOC -> ODR &= ~(1 << 13);
            delay(300000);
            GPIOC -> ODR |= (1 << 13);
            delay(300000);
        }

        GPIOC -> ODR |= (1 << 13);
        GPIOB -> ODR |= (1 << 9);
        GPIOC -> ODR &= ~(1 << 14);
        delay(1000000);

        for(int i = 0; i < 3; i++){
            GPIOB -> ODR |= (1 << 9);
            delay(300000);
            GPIOB -> ODR &= ~(1 << 9);
            delay(300000);
        }

        GPIOC -> ODR |= (1 << 13);
        GPIOB -> ODR &= ~(1 << 9);
        GPIOC -> ODR |= (1 << 14);
        delay(1000000);

        for(int i = 0; i < 3; i++){
            GPIOC -> ODR |= (1 << 14);
            delay(300000);
            GPIOC -> ODR &= ~(1 << 14);
            delay(300000);
        }
    }
}
