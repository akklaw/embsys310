#ifndef __DELAY_H__
#define __DELAY_H__

#include "stm32l475xx.h"
#include "stm32l4xx_it.h"

volatile int counter=0;

void delay(uint32_t delayInMilliseconds);

#endif
