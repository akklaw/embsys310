#include "delay.h"

void delay(uint32_t delayInMilliseconds)
{
    while(1)
    {
        // check to see the global counter is greater than
        // the delay in milliseconds, the counter will be 
        // increment by 1 every millisecond
        // if the time is up, it would break this while loop
        // and reset the counter to 0 before exiting this function.
        if(delayInMilliseconds < counter)
            break;
    }
    // reset it before exit
    counter = 0;
}

// SysTick_Handler to increment the counter by 1 every millisecond
void SysTick_Handler(void)
{
   counter++;
}