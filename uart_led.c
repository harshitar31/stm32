/* 
  Program: USART2 RX (PA3) controls PC14 LED; 'A' turns LED on, 'B' turns it off
*/

#include "stm32f4xx.h"
#include "string.h"
uint8_t data;
int main()
{		
	RCC->AHB1ENR |= (1U << 2); 
	
	GPIOC -> MODER &= ~ (3U<<28);
	GPIOC -> MODER |= (1U<<28);

    RCC->AHB1ENR |= (1<<0);
    GPIOA->MODER |= (1<<5);
    GPIOA->MODER |= (1<<7);
	GPIOA->AFR[0] &= (~(1<<15));
    GPIOA->AFR[0] |= (1<<14) | (1<<13) | (1<<12);
	GPIOA->AFR[0] &= (~(1<<11));
    GPIOA->AFR[0] |= (1<<10) | (1<<9) | (1<<8);

    RCC->APB1ENR |= (1<<17);
    USART2->BRR = 0x0683;
    USART2->CR1 |= (1<<2);
	USART2->CR1 |= (1<<3);
    USART2->CR1 |= (1<<13);
    while(1)
    {
		while(!(USART2->SR & (1U<<5))) {};
        data = USART2->DR;  
		int a = 'A';
		int b = 'B';
				
		if (data==a){
			GPIOC->ODR |=(1U<<14);
		}
		else if (data==b){
			GPIOC->ODR &=~(1U<<14);
		}
    }
}
