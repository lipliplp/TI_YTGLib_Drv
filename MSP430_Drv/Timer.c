#include "Timer.h"

void Timer_Init(void)
{
    TA0CTL = TASSEL_2 + ID_0 + TACLR + MC_1 + TAIE;
    TA0CCR0 = 50000;
    TA0CCTL0 =CCIE;         //����/�Ƚ��ж�ʹ��

    TA0CCR1 = 50000;
    TA0CCTL1 =CCIE;         //����/�Ƚ��ж�ʹ��

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
        if(count >= 500)    // 1s��ʱ
        {
            count = 0;
//            P4OUT ^= BIT7;
        }
        TA0CTL ^= TAIFG;       //TAIFGһ��Ҫ�ֶ��������Ȼ�Ῠ���жϷ�������������ȥ�������̵Ƴ���
    }

}


#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer_A1(void)             // 100ms����ж�
{
    static unsigned int count;
    switch(__even_in_range(TA0IV,14))// __even_in_range()�������������ڶ�Դ�жϵĲ�ѯ��
    {
        //���ȼ��Ӹߵ��ͣ��Ѿ���Ӳ���涨����
        case 0: break; // No interrupt
        case 2:
        count ++;
        if(count >= 500)                // 1s��ʱ
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

