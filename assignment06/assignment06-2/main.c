#include <stdint.h>

// LD1 --> PA5 -- Homework
// LD2 --> PB14 -- In Class

#define RCC_BASE 0x40021000
#define RCC_AHB2ENR (*((unsigned int*)(RCC_BASE + 0x4C)))

#define GPIOB_BASE 0x48000400
#define GPIOB_MODER (*((unsigned int*)(GPIOB_BASE + 0x00)))
#define GPIOB_ODR (*((unsigned int*)(GPIOB_BASE + 0x14)))

#define GPIOA_BASE 0x48000000
#define GPIOA_MODER (*((unsigned int*)(GPIOA_BASE + 0x00)))
#define GPIOA_ODR (*((unsigned int*)(GPIOA_BASE + 0x14)))

#define ORD14   (1<<14)
#define ORD5    (1<<5)

#define LED_ON 1
#define LED_OFF 0
#define DELAY_DURATION 100000

void delay(uint32_t iteration);
void control_user_led1(uint8_t state, uint32_t duration);
void enable_rcc(uint32_t port);

// Debug helper code
#if 0

void delay_in_c(uint32_t iteration);
void control_user_led1_in_c(uint8_t state, uint32_t duration);
void enable_rcc_in_c(int bit);

void control_user_led1_in_c(uint8_t state, uint32_t duration)
{
    if(state)        
        GPIOA_ODR |= ORD5;      // GPIOB_ODR: Turn LED1 (PA5) on       
    else
        GPIOA_ODR &= ~ORD5;      // GPIOB_ODR: Turn LED2 (PA5) off

#if 1
    delay_in_c(duration);
#else    
    delay(duration);
#endif
    
}

void delay_in_c(uint32_t iteration)
{
   int counter = 0;
   while (counter < iteration)
       counter++;  
}

void enable_rcc_in_c(int bit)
{
    *((unsigned int*)((0x42000000) + (0x2104C * 32) + ( bit * 4))) = 0x1;
}
#endif

void main(void)
{    
    // RCC AHB2 peripheral clock enable register (RCC_AHB2ENR)
    // RCC Base Address: 0x40021000
    // Address offset: 0x4C
    // Set bit[1] to 1 to enable clock to PortB
    // Set bit[0] to 1 to enable clock to PortA
    // 1. Enable clock to Peripheral

#if 1    
    RCC_AHB2ENR |= 0x1;    
#else    
    
    // Replace above statement with function call below    
 #if 1    
    enable_rcc(0);
 #else    
    // debug code
    enable_rcc_in_c(0);
 #endif    
    
#endif  
    // GPIO port mode register (GPIOx_MODER) (x = A..E and H)
    // GPIOA Base Address: 0x48000000
    // Address offset: 0x00
    // Set bit[11:10] to 0x01  so --> 0x200 // To enable PA5 as output
    // Note: GPIOA_MODER reset value = 0xABFFFFFF
    //       So will only need to clear bit 11
    GPIOA_MODER &= 0xFFFFF7FF;

    // GPIO port output data register (GPIOx_ODR) (x = A..E and H)
    // GPIOA Base Address: 0x48000000
    // Address offset: 0x14
    // Set bit[5] to 1 --> 0x20; // Turn LED ON
    // Set bit[5] to 0 --> 0x0; // Turn LED OFF
     
    while(1)
    {
#if 1 
        control_user_led1(LED_ON, DELAY_DURATION);
        control_user_led1(LED_OFF, DELAY_DURATION);
#else        
        control_user_led1_in_c(LED_ON, DELAY_DURATION);
        control_user_led1_in_c(LED_OFF, DELAY_DURATION);
#endif        
    }
}
