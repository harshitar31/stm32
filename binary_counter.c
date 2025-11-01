/* 
 Program: Binary Counter with LEDs on PC13 (active-low), PC14, and PB9
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
        for(int i = 0; i <= 1; i++){
            if(i == 0) 
                GPIOC -> ODR |= (1<<13);
            else 
                GPIOC -> ODR &= ~(1<<13);
            
            for(int j = 0; j <= 1; j++){
                if(j == 0) 
                    GPIOC -> ODR &= ~(1<<14);
                else 
                    GPIOC -> ODR |= (1<<14);
                
                for(int k = 0; k <= 1; k++){
                    if(k == 0) 
                        GPIOB -> ODR &= ~(1<<9);
                    else 
                        GPIOB -> ODR |= (1<<9);
                    
                    delay(2000000);
                }
                delay(1000000);
            }
            delay(900000);
        }
    }
}
