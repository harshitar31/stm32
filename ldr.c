/* 
  Program: Read ADC on PA1 (LDR) and toggle PC14 and PB9 based on threshold
*/

#include "stm32f4xx.h"
int adcData;
int main(void) {

    RCC->AHB1ENR |= (1U << 0); 
		RCC->AHB1ENR |= (1U << 2); 
	RCC->AHB1ENR |= (1U << 1); 

    RCC->APB2ENR |= (1 << 8);

    GPIOA->MODER |= (1U << 2); 
	GPIOA->MODER |= (1U << 3); 
	
		GPIOC -> MODER &= ~ (1U<<29);
		GPIOC -> MODER |= (1U<<28);
		GPIOB -> MODER &= ~ (3U<<18);
		GPIOB -> MODER |= (1U<<18);

    ADC1->SMPR2 = 0;	

		ADC->CCR =0; 
	
    ADC1->CR1 = 0;
    ADC1->CR2 = 0;
	
	 
    ADC1->CR2 |= (1U << 1); 
    ADC1->SQR3 = 1; 
    ADC1->SQR1 = 0;
 
    ADC1->CR2 |= 1;
		
    while((ADC1->CR2 & 1) == 0) {}
		
       ADC1->CR2 |= (1 << 30);

    while (1) {
       
        while (!(ADC1->SR & (1 << 1))) {}

        adcData = ADC1->DR;
					
				if(adcData>2048){
					GPIOC->ODR 	&= ~(1U<<14);
					GPIOB->ODR |= (1U<<9);
				}
				else{
					GPIOC->ODR 	|= (1U<<14);
					GPIOB->ODR 	&= ~(1U<<9);
				}
    }
}
