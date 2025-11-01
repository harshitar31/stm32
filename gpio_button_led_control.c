/* 
 * Program: Control LEDs on PC13 (active-low), PC14, and PB9 using push-buttons on PA0, PA6, and PB10.
 * Each button triggers a blinking pattern on its respective LED until another button is pressed.
 */

#include "stm32f4xx.h"

void delay(volatile uint32_t time){
    while(time--);
}

int main(void) {
    RCC->AHB1ENR |= (1U << 0);
    RCC->AHB1ENR |= (1U << 1);
    RCC->AHB1ENR |= (1U << 2);

    GPIOC->MODER &= ~(3U << 26);
    GPIOC->MODER &= ~(3U << 28);
    GPIOB->MODER &= ~(3U << 18);

    GPIOA->PUPDR &= ~(3U << 0);
    GPIOA->PUPDR &= ~(3U << 12);
    GPIOB->PUPDR &= ~(3U << 20);
    
    GPIOA->PUPDR |= (1U << 0);
    GPIOA->PUPDR |= (1U << 12);
    GPIOB->PUPDR |= (1U << 20);

    GPIOC->MODER |= (1U << 26);
    GPIOC->MODER |= (1U << 28);
    GPIOB->MODER |= (1U << 18);

    while (1) {
        if (!(GPIOA->IDR & (1U << 0))) {
            GPIOC->ODR &= ~(1U << 14);
            GPIOB->ODR &= ~(1U << 9);
            while (1) {
                GPIOC->ODR &= ~(1U << 13);
                delay(500000);
                GPIOC->ODR |= (1U << 13);
                delay(500000);
                if (!(GPIOA->IDR & (1U << 6)) || !(GPIOB->IDR & (1U << 10))) {
                    break;
                }
            }
        }
        else if (!(GPIOA->IDR & (1U << 6))) {
            GPIOC->ODR |= (1U << 13);
            GPIOB->ODR &= ~(1U << 9);
            while (1) {
                GPIOC->ODR |= (1U << 14);
                delay(500000);
                GPIOC->ODR &= ~(1U << 14);
                delay(500000);
                if (!(GPIOA->IDR & (1U << 0)) || !(GPIOB->IDR & (1U << 10))) {
                    break;
                }
            }
        }
        else if (!(GPIOB->IDR & (1U << 10))) {
            GPIOC->ODR |= (1U << 13);
            GPIOC->ODR &= ~(1U << 14);
            while (1) {
                GPIOB->ODR |= (1U << 9);
                delay(500000);
                GPIOB->ODR &= ~(1U << 9);
                delay(500000);
                if (!(GPIOA->IDR & (1U << 0)) || !(GPIOA->IDR & (1U << 6))) {
                    break;
                }
            }
        }
    }
    return 0;
}
