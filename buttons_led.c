/* 
  Program: External interrupts on PA6 and PB10 to control LED on PC13 (active-low)
*/

#include <stm32f4xx.h>

void delay(int s){
	SysTick->LOAD = 1600000*s-1;
	SysTick->VAL=0;
	SysTick->CTRL=1;
	while(!(SysTick->CTRL &(1U<<16)));
}

void EXTI9_5_IRQHandler(void)
{
    if (EXTI->PR & (1U << 6))
    {
        EXTI->PR |= (1U << 6); 
			GPIOC	->ODR |= (1u<<13);
    }
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR & (1U << 10)) 
    {
        EXTI->PR |= (1U << 10);

      GPIOC	->ODR &= ~ (1u<<13);
      delay(10);
			GPIOC	->ODR |= (1u<<13);
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
	NVIC_SetPriority(EXTI9_5_IRQn, 0);      
	NVIC_SetPriority(EXTI15_10_IRQn, 1);    

	
	while(1){}
}
