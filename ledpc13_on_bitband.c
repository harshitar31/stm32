#include <stdint.h>

// ------------------ Base Addresses ------------------
#define PERIPH_BASE       0x40000000    // Base address for peripheral registers
#define PERIPH_BB_BASE    0x42000000    // Base address for peripheral bit-band region

// ------------------ Peripheral Addresses ------------------
#define RCC_AHB1ENR       0x40023830    // RCC AHB1 peripheral clock enable register
#define GPIOC_MODER       0x40020800    // GPIOC mode register
#define GPIOC_ODR         0x40020814    // GPIOC output data register

// ------------------ Bit Positions ------------------
#define RCC_IOPC_EN_BIT   2             // Bit 2 enables clock for GPIOC
#define GPIOC_MODER13_0   26            // Bit 26 -> MODER13[0]
#define GPIOC_MODER13_1   27            // Bit 27 -> MODER13[1]
#define GPIOC_ODR13_BIT   13            // Bit 13 -> PC13 output data bit

// ------------------ Bit-Band Alias Macro ------------------
#define BITBAND_PERI(addr, bit) \
  ((volatile uint32_t *)(PERIPH_BB_BASE + (((addr) - PERIPH_BASE) * 32) + ((bit) * 4)))

// ------------------ Simple Delay Function ------------------
void delay(volatile uint32_t time) {
    while (time--);   // Simple busy-wait loop
}

// ------------------ Main Program ------------------
int main(void) {

    // Enable GPIOC clock by setting bit 2 of RCC_AHB1ENR
    *BITBAND_PERI(RCC_AHB1ENR, RCC_IOPC_EN_BIT) = 1;

    // Configure PC13 as output mode:
    // MODER13 = 01 (output)
    *BITBAND_PERI(GPIOC_MODER, GPIOC_MODER13_0) = 1;
    *BITBAND_PERI(GPIOC_MODER, GPIOC_MODER13_1) = 0;

    // Infinite loop: Toggle PC13 (LED)
    while (1) {
        *BITBAND_PERI(GPIOC_ODR, GPIOC_ODR13_BIT) = 0;  // LED OFF (PC13 = LOW)
        delay(800000);

        *BITBAND_PERI(GPIOC_ODR, GPIOC_ODR13_BIT) = 1;  // LED ON (PC13 = HIGH)
        delay(800000);
    }
}
