/* 
  Program: Configure PC13 as output and set PC13 to low (active-low LED control)
*/

#include "stm32f4xx.h"

int main(void) {
    RCC -> AHB1ENR |= (1<<2);
    GPIOC -> MODER |= (1<<26);
    GPIOC -> ODR &= ~(1<<13);
}
