#include "GPIO_EXTI.h"
#include "GPIO_LED.h"

void EXTI_Init(void)
{
    P2IE |= BIT1; //P2.1中断
    P2DIR &= ~BIT1;//P2.1 输入
    P2REN |= BIT1;//使能上下拉电阻
    P2OUT |= BIT1;//选择使用上拉电阻
    P2IFG &= ~ BIT1;//清除标志位
    P2IES |= BIT1; //下降沿触发

    P2IE |= BIT0; //P2.0中断
    P2DIR &= ~BIT0;//P2.0 输入
    P2REN |= BIT0;//使能上下拉电阻
    P2OUT |= BIT0;//选择使用上拉电阻
    P2IFG &= ~ BIT0;//清除标志位
    P2IES |= BIT0; //下降沿触发

    P1IE |= BIT1; //P1.1中断
    P1DIR &= ~BIT1;//P1.1 输入
    P1REN |= BIT1;//使能上下拉电阻
    P1OUT |= BIT1;//选择使用上拉电阻
    P1IES |= BIT1; //下降沿触发

    _EINT();        //开启总中断
}

//#pragma vector=PORT1_VECTOR
//__interrupt void p1Interrupt()
//{
//    static unsigned int i;
//    if(P1IFG & BIT1)        //判断是中断由P2.0引起
//    {
//        if(i == 0)
//        {
//            P4OUT &= ~(1<<7);
//            i = 1;
//        }
//        else
//        {
//            i = 0;
//            P4OUT |= (1<<7);
//        }
//        P1IFG &= ~BIT1; //清除中断标志
//    }
//}
//
//#pragma vector=PORT2_VECTOR
//__interrupt void p2Interrupt()
//{
//    static unsigned int i;
//    if(P2IFG & BIT1)        //判断是中断由P2.1引起
//    {
//        if(i == 0)
//        {
//            P4OUT &= ~(1<<7);
//            i = 1;
//        }
//        else
//        {
//            i = 0;
//            P4OUT |= (1<<7);
//        }
//        P2IFG &= ~BIT1; //清除中断标志
//    }
//    if(P2IFG & BIT0)        //判断是中断由P2.0引起
//    {
//        if(i == 0)
//        {
//            P4OUT &= ~(1<<7);
//            i = 1;
//        }
//        else
//        {
//            i = 0;
//            P4OUT |= (1<<7);
//        }
//        P2IFG &= ~BIT0; //清除中断标志
//    }
//}
