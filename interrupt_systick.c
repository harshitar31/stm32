/* 
  Program: External interrupts on PA0, PA6, PB10 to control LEDs on PC13 (active-low), PC14, PB9
*/

#include <stm32f4xx.h>

void delay(int s){
	SysTick->LOAD = 16000000*s-1;
	SysTick->VAL=0;
	SysTick->CTRL=5;
	while(!(SysTick->CTRL &(1U<<16)));
}
void EXTI0_IRQHandler(void)
{
    if (EXTI->PR & (1U << 0))
    {
        EXTI->PR |= (1U << 0); 
			
      GPIOC->ODR &=~ (1U << 14);
			GPIOB->ODR &=~ (1U<<9);
			while(1){
				GPIOC	->ODR &=~ (1u<<13);
				for(int i=0;i<1200000;i++);
				GPIOC	->ODR |= (1u<<13);
				for(int i=0;i<1200000;i++);
			}
    }
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR & (1U << 10)) 
    {
        EXTI->PR |= (1U << 10);

      GPIOC	->ODR |= (1u<<13);
      
			GPIOB->ODR &=~(1U<<9);
			while(1){
				GPIOC->ODR |= (1U << 14);
				for(int i=0;i<800000;i++);
				GPIOC->ODR &=~ (1U << 14);
				for(int i=0;i<600000;i++);
			}
    }
}

void EXTI9_5_IRQHandler(void)
{
    if (EXTI->PR & (1U << 6))
    {
        EXTI->PR |= (1U << 6); 
			
			GPIOC	->ODR |= (1u<<13);
      GPIOC->ODR &=~ (1U << 14);
			
			while(1){
				GPIOB->ODR |= (1U<<9);
				for(int i=0;i<300000;i++);
				GPIOB->ODR &=~ (1U<<9);
				for(int i=0;i<300000;i++);
			}
    }
}

int main(void){
	RCC->AHB1ENR |= (1U << 0); 
	RCC->AHB1ENR |= (1U << 2); 
	RCC->AHB1ENR |= (1U << 1); 
	
	RCC->APB2ENR |= (1U << 14);
	
	GPIOC -> MODER &= ~ (3U<<28);
	GPIOC -> MODER |= (1U<<28);
	GPIOC -> MODER &= ~ (3U<<26);
	GPIOC -> MODER |= (1U<<26);
	GPIOB -> MODER &= ~ (3U<<18);
	GPIOB -> MODER |= (1U<<18);
	
	GPIOC	->ODR |= (1u<<13);
	
	GPIOC->MODER &= ~(3U << 0); 
  GPIOC->MODER &= ~(3U << 12);
  GPIOB->MODER &= ~(3U << 20); 	
  GPIOA->PUPDR &= ~(3U << 0);
  GPIOA->PUPDR &= ~(3U << 12);  
  GPIOB->PUPDR &= ~(3U << 20);    
	GPIOA->PUPDR|=(1U<<0);
	GPIOA->PUPDR|=(1U<<12);
	GPIOB->PUPDR|=(1U<<20);
	
	SYSCFG->EXTICR[0] &=~(15U<<0);
	SYSCFG->EXTICR[0] |= (0U << 0);  
	
	SYSCFG->EXTICR[1] &= ~(15U << 8);
  SYSCFG->EXTICR[1] |= (0U << 8);  

  SYSCFG->EXTICR[2] &= ~(15U << 8); 
  SYSCFG->EXTICR[2] |= (1U << 8);  
	
	EXTI->IMR |= (1<<0);
	EXTI->IMR |= (1 << 6);   
  EXTI->IMR |= (1 << 10);  
	
	EXTI->FTSR |= (1 << 0); 
	EXTI->FTSR |= (1 << 6);  
  EXTI->FTSR |= (1 << 10); 
	
	NVIC_EnableIRQ(EXTI9_5_IRQn);  
  NVIC_EnableIRQ(EXTI15_10_IRQn);
	NVIC_EnableIRQ(EXTI0_IRQn);
	
  
	NVIC_SetPriority(EXTI0_IRQn, 2);      
	NVIC_SetPriority(EXTI15_10_IRQn, 1); 
	NVIC_SetPriority(EXTI9_5_IRQn, 0);   	

	
	while(1){}
}
