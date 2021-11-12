#include "Timer.h"

void Timer_Init(void)
{
    TA0CTL = TASSEL_2 + ID_0 + TACLR + MC_1 + TAIE;
    TA0CCR0 = 50000;
    TA0CCTL0 =CCIE;         //捕获/比较中断使能

    TA0CCR1 = 50000;
    TA0CCTL1 =CCIE;         //捕获/比较中断使能

//    P8DIR |= BIT1;

    _EINT();
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
    static unsigned int count;
    if(TAIFG)
    {
        count++;
        if(count >= 500)    // 1s延时
        {
            count = 0;
//            P4OUT ^= BIT7;
        }
        TA0CTL ^= TAIFG;       //TAIFG一定要手动清除，不然会卡在中断服务函数中跳不出去，导致绿灯常量
    }

}


#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer_A1(void)             // 100ms溢出中断
{
    static unsigned int count;
    switch(__even_in_range(TA0IV,14))// __even_in_range()本征函数，用于多源中断的查询。
    {
        //优先级从高到低，已经被硬件规定好了
        case 0: break; // No interrupt
        case 2:
        count ++;
        if(count >= 500)                // 1s延时
        {
            count = 0;
//            P4OUT ^= BIT7;
        }
        break; // TAxCCR1 CCIFG
        case 4: break; // TAxCCR2 CCIFG
        case 6: break; // TAxCCR3 CCIFG
        case 8: break; // TAxCCR4 CCIFG
        case 10: break; // TAxCCR5 CCIFG
        case 12: break; // TAxCCR6 CCIFG
        case 14: break; // TAxCTL TAIFG
        default: break;
    }
    TA0CTL ^= TAIFG;
}

