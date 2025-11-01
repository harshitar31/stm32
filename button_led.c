/* 
  Program: Read push-button on PA6 to control LEDs on PC14 and PB9
*/

#include "stm32f4xx.h"

int main(void) {

		RCC->AHB1ENR |= (1U<<0); 
    RCC->AHB1ENR |= (1U<<1);  
    RCC->AHB1ENR |= (1U<<2);  

    GPIOB->MODER &= ~(3U << 18); 
		GPIOC->MODER &= ~(3U << 28); 
		GPIOA->PUPDR &= ~(3U << 12);  
	
		GPIOA->PUPDR|=(1U<<12);
		GPIOB->MODER|=(1U<<18);
		GPIOC->MODER|=(1U<<28);
	
    while (1) {
       
        if (GPIOA->IDR & (1U << 6)) {
            GPIOC->ODR &= ~ (1U << 14);
						GPIOB->ODR|=(1U<<9);
        } else {
            GPIOC->ODR |=  (1U << 14); 
					GPIOB->ODR&=~(1U<<9);
        }
    }
		return 0;
}
