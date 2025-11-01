/* 
  Program: LED control sequence on PC13 (active-low), PC14, and PB9
 */

#include "stm32f4xx.h"

void delay(volatile uint32_t time){
    while(time--);
}

int main(void){
    int count = 0;
    
    RCC -> AHB1ENR |= (1 << 2);
    RCC -> AHB1ENR |= (1 << 1);

    GPIOC -> MODER |= (1 << 26);
    GPIOC -> MODER |= (1 << 28);

    GPIOB -> MODER |= (1 << 18);
    
    while(1){
        count = 23;

        GPIOC -> ODR &= ~(1 << 14);
        GPIOB -> ODR &= ~(1 << 9);
        GPIOC -> ODR |= (1 << 13);

        if(count % 2 == 0){
            GPIOC -> ODR &= ~(1 << 13);
        }
        else{
            GPIOB -> ODR |= (1 << 9);
            GPIOC -> ODR |= (1 << 14);
        }
    }
}
