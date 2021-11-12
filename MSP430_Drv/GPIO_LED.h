#ifndef __GPIO_LED_H__
#define __GPIO_LED_H__

#include "msp430.h"
#include "delay.h"

void LED_Init(void);
void LED_Test(void);
void LED_STATE(unsigned int);

#endif
