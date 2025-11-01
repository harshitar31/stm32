/* 
  Program: USART2 command "LEDON"/"LEDOFF" control PC14 LED
*/

#include "stm32f4xx.h"
#include "string.h"

volatile char buffer[10];
volatile int idx = 0;

void USART2_IRQHandler(void)
{
    if (USART2->SR & USART_SR_RXNE)
    {
        char data = USART2->DR;

        while(!(USART2->SR & USART_SR_TXE));
        USART2->DR = data;

        if (idx < sizeof(buffer) - 1) {
            buffer[idx++] = data;
            buffer[idx] = '\0';
        }

        if (idx == 5 && strcmp(buffer, "LEDON") == 0) {
            GPIOC->ODR |= (1<<14);
            idx = 0;
        }
        else if (idx == 6 && strcmp(buffer, "LEDOFF") == 0) {
            GPIOC->ODR &= ~(1<<14);
            idx = 0;
        }
        else if (idx >= 6) {
            idx = 0;
        }
    }
}

int main(void)
{
    RCC->AHB1ENR |= (1U << 2);
    GPIOC->MODER &= ~(3U<<28);
    GPIOC->MODER |= (1U<<28);

    RCC->AHB1ENR |= (1<<0);
    GPIOA->MODER |= (2<<4);
    GPIOA->MODER |= (2<<6);
    GPIOA->AFR[0] |= (7<<8);
    GPIOA->AFR[0] |= (7<<12);

    RCC->APB1ENR |= (1<<17);
    USART2->BRR = 0x0683;
    USART2->CR1 |= USART_CR1_RXNEIE;
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;
    USART2->CR1 |= USART_CR1_UE;

    NVIC_EnableIRQ(USART2_IRQn);

    while(1)
    {
    }
}
