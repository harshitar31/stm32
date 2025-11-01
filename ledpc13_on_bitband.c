/* 
  Program: Blink LED on PC13 (active-low) using bit-banding technique
*/

#include <stdint.h>

#define PERIPH_BASE       0x40000000
#define PERIPH_BB_BASE    0x42000000

#define RCC_AHB1ENR       0x40023830
#define GPIOC_MODER       0x40020800
#define GPIOC_ODR         0x40020814

#define RCC_IOPC_EN_BIT   2
#define GPIOC_MODER13_0   26
#define GPIOC_MODER13_1   27
#define GPIOC_ODR13_BIT   13

#define BITBAND_PERI(addr, bit) \
  ((volatile uint32_t *)(PERIPH_BB_BASE + (((addr) - PERIPH_BASE) * 32) + ((bit) * 4)))

void delay(volatile uint32_t time) {
    while (time--);
}

int main(void) {
    *BITBAND_PERI(RCC_AHB1ENR, RCC_IOPC_EN_BIT) = 1;
    *BITBAND_PERI(GPIOC_MODER, GPIOC_MODER13_0) = 1;
    *BITBAND_PERI(GPIOC_MODER, GPIOC_MODER13_1) = 0;

    while (1) {
        *BITBAND_PERI(GPIOC_ODR, GPIOC_ODR13_BIT) = 0;
        delay(800000);

        *BITBAND_PERI(GPIOC_ODR, GPIOC_ODR13_BIT) = 1;
        delay(800000);
    }
}
