// Blinky_LED1 using XOR bit wise operator

// RCC Base address: 0x40021000
#define RCC_BASE     0x40021000

// GPIOA Base address: 0x48000000
#define GPIOA_BASE   0x48000000

#define RCC_AHB2ENR (*((unsigned int*)(RCC_BASE   + 0x4c)))
#define GPIOA_MODER (*((unsigned int*)(GPIOA_BASE + 0x0 )))
#define GPIOA_ODR   (*((unsigned int*)(GPIOA_BASE + 0x14)))

//(PA5)
#define ORD5        (1 << 5) 

volatile int counter = 0;

int main()
{    
    RCC_AHB2ENR |= 0x1;  // RCC_AHB2ENR: Enable clock to GPIOA
    
    GPIOA_MODER &= 0xFFFFF7FF; // GPIOA_MODER: Set GPIOA to output
    
    while (1)
    {
        counter = 0;
        while (counter < 100000)
        {
            counter++;
        }
        GPIOA_ODR ^= ORD5;      // GPIOB_ODR: Turn LED1 (PA5) toggle on and off   
    }
}
