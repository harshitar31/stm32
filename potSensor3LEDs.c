/* 
  Program: Read ADC on PA0 (pot) and control PC13 (active-low), PC14, and PB9 based on ADC thresholds
*/

#include "stm32f4xx.h"
int adcData;
int main(void) {
    RCC->AHB1ENR |= (1U << 0); 
		RCC->AHB1ENR |= (1U << 2); 
	RCC->AHB1ENR |= (1U << 1); 
    
    RCC->APB2ENR |= (1 << 8);
    
    GPIOA->MODER |= (3U << 0); 
	
		GPIOC -> MODER &= ~ (3U<<28);
		GPIOC -> MODER |= (1U<<28);
	GPIOC -> MODER &= ~ (3U<<26);
		GPIOC -> MODER |= (1U<<26);
	GPIOB -> MODER &= ~ (3U<<18);
		GPIOB -> MODER |= (1U<<18);
	
    ADC1->SMPR2 = 0;	

		ADC->CCR &= ~(3 << 16); 
		ADC->CCR |= (1 << 16);

    ADC1->CR1 = 0;
    ADC1->CR2 = 0;
	
    ADC1->CR2 |= (1U << 1); 
    ADC1->SQR3 = 0; 
    ADC1->SQR1 = 0;
    
    ADC1->CR2 |= 1;
		
    while((ADC1->CR2 & 1) == 0) {}
			   
    ADC1->CR2 |= (1 << 30);

    while (1) {
        while (!(ADC1->SR & (1 << 1))) {}
        adcData = ADC1->DR;
					
				if(adcData<1365){
					GPIOC->ODR &= ~ (1U<<13);
					GPIOC->ODR 	&= ~(1U<<14);
					GPIOB->ODR &= ~(1U<<9);
				}
				else if(adcData>1366 && adcData < 2370) {
					GPIOC->ODR |= (1U<<13);
					GPIOC->ODR 	|=(1U<<14);
					GPIOB->ODR &= ~(1U<<9);
				}
				else{
					GPIOC->ODR |= (1U<<13);
					GPIOC->ODR 	&= ~(1U<<14);
					GPIOB->ODR |=(1U<<9);
				}
    }
}
