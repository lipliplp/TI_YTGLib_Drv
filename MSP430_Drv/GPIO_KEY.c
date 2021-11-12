#include "GPIO_KEY.h"
#include "GPIO_LED.h"
#include "USART.h"

void KEY0_GPIO_Config(void)
{
    P1DIR &= ~BIT1;
    P1REN |=  BIT1;
    P1OUT |=  BIT1;
}
void KEY1_GPIO_Config(void)
{
    P2DIR &=~ BIT1;
    P2REN |=  BIT1;
    P2OUT |=  BIT1;
}
int KEY0_STATE(void)
{
    char txt[20];
    if((P1IN & BIT1) == 0)
    {
      delay_ms(10);
      if((P1IN & BIT1) == 0)
      {
          LED_STATE(0);
//          return 0;
      }
      sprintf(txt,"%d\n",P1IN & BIT1);
      send_buf((unsigned char *)txt);
      while((P1IN & BIT1) == 0);
    }
    return 1;
}

int KEY1_STATE(void)
{
    if((P2IN & BIT1) == 0)
    {
      delay_ms(10);
      if((P2IN & BIT1) == 0)
      {
          LED_STATE(1);
//          return 0;
      }
      while((P2IN & BIT1) == 0);
    }
    return 1;
}

