/* 
  Program: Read push-button on PB10 to control LED on PC14
*/

#include "stm32f4xx.h"

int main(void) {
    RCC->AHB1ENR |= (1U << 1);
    RCC->AHB1ENR |= (1U << 2);

    GPIOB->MODER &= ~(1U << 20);
    GPIOC->MODER |= (1U << 28);
    GPIOC->MODER &= ~(1U << 29);

    GPIOB->PUPDR &= ~(3U << 20);
    GPIOB->PUPDR |= (1U << 20);

    while (1) {
        if (GPIOB->IDR & (1U << 10)) {
            GPIOC->ODR &= ~(1U << 14);
        } else {
            GPIOC->ODR |= (1U << 14);
        }
    }
}
