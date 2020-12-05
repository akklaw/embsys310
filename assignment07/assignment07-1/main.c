#include <stdint.h>
//#include "stm32f401xe.h"    // CMSIS - Device Specific File
#include "system_stm32l4xx.h"
#include "stm32l475xx.h"
#include "stm32l4xx_it.h"

// LD1 --> PA5 -- Homework

// forward declearation
void delay(uint32_t delayInMilliseconds);

// prototype
void SysTick_Initialize(void);

uint32_t SYS_CLOCK_HZ=0x003D0900; // 4,000,000 cycles per second which is 0x003D0900

void main(void)
{     
    // RCC AHB2 peripheral clock enable register (RCC_AHB2ENR)
    // RCC Base Address: 0x40021000
    // Address offset: 0x4C
    // Set bit[0] to 1
    // 1. Enable clock to Peripheral  
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    
    // GPIO port mode register (GPIOx_MODER) (x = A..E and H)
    // GPIOA Base Address: 0x48000000
    // Address offset: 0x00
    // Set bit[11:10] to 0x01 so 0x200  // To enable PA5 as output
    GPIOA->MODER &= ~GPIO_MODER_MODE5_1;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;
    
    // Initialize SysTick_Handler
    SysTick_Initialize();
    
    // GPIO port output data register (GPIOx_ODR) (x = A..E and H)
    // GPIOA Base Address: 0x48000000
    // Address offset: 0x5
    // Set bit[5] to 1 --> 0x20; // Turn LED ON
    // Set bit[5] to 0 --> 0x0; // Turn LED OFF
    
    while(1)
    {
        GPIOA->ODR |= GPIO_ODR_OD5;
        delay(500); // delay 500 milliseconds
        
        GPIOA->ODR &= ~GPIO_ODR_OD5;
        delay(500); // delay 500 milliseconds
    }    
}

// implementatio of SysTick_Handler Initialization
void SysTick_Initialize(void)
{
    SysTick->LOAD = (SYS_CLOCK_HZ/1000) - 1;    // 0xE000E014 - counts down to 0
    SysTick->VAL  = 0x0;                        // Clears initial value
    SysTick->CTRL = 0x7;                        // Enable interuupts
}