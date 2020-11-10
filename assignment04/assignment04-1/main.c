// Blinky_LED1 using Bit-Banding method

// GPIOA Base address: 0x48000000
#define GPIOA_BASE       0x48000000
#define GPIOA_MODER (*((unsigned int*)(GPIOA_BASE + 0x0 )))
#define GPIOA_ODR   (*((unsigned int*)(GPIOA_BASE + 0x14)))

#define BIT_BANDING_BASE 0x42000000
#define BYTE_OFFSET      0x2104C
#define BIT_NUMBER       0

//(PA5)
#define ORD5        (1 << 5) 

void delay(void)
{
    volatile int  counter = 0;
    while (counter < 100000)
    {
        counter++;
    }
}

int main()
{     
    // RCC_AHB2ENR: Enable clock to GPIOA using bit-banding method
    *((unsigned int*)((BIT_BANDING_BASE) + (BYTE_OFFSET * 32) + ( BIT_NUMBER * 4))) = 0x1;
    
    GPIOA_MODER &= 0xFFFFF7FF; // GPIOA_MODER: Set GPIOA to output
    
    while (1)
    {
        delay();
        
        GPIOA_ODR |= ORD5;      // GPIOB_ODR: Turn LED1 (PA5) on
       
        delay();
        
        GPIOA_ODR &= ~ORD5;      // GPIOB_ODR: Turn LED2 (PA5) off
    }
}
