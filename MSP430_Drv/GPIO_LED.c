#include "GPIO_LED.h"

void LED_Init(void)
{
    P4DIR |= (1<<7);
    LED_STATE(0);
}

void LED_STATE(unsigned int state)
{
    switch(state)
    {
        case 0: P4OUT &= ~(1<<7); break;
        case 1: P4OUT |= (1<<7);  break;
        default: break;
    }
}

void LED_Test(void)
{
    while(1)
    {
        P4OUT &= ~(1<<7);
        delay_ms(1000);
        P4OUT |= (1<<7);
        delay_ms(1000);
    }
}
