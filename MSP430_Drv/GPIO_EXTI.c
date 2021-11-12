#include "GPIO_EXTI.h"
#include "GPIO_LED.h"

void EXTI_Init(void)
{
    P2IE |= BIT1; //P2.1�ж�
    P2DIR &= ~BIT1;//P2.1 ����
    P2REN |= BIT1;//ʹ������������
    P2OUT |= BIT1;//ѡ��ʹ����������
    P2IFG &= ~ BIT1;//�����־λ
    P2IES |= BIT1; //�½��ش���

    P2IE |= BIT0; //P2.0�ж�
    P2DIR &= ~BIT0;//P2.0 ����
    P2REN |= BIT0;//ʹ������������
    P2OUT |= BIT0;//ѡ��ʹ����������
    P2IFG &= ~ BIT0;//�����־λ
    P2IES |= BIT0; //�½��ش���

    P1IE |= BIT1; //P1.1�ж�
    P1DIR &= ~BIT1;//P1.1 ����
    P1REN |= BIT1;//ʹ������������
    P1OUT |= BIT1;//ѡ��ʹ����������
    P1IES |= BIT1; //�½��ش���

    _EINT();        //�������ж�
}

//#pragma vector=PORT1_VECTOR
//__interrupt void p1Interrupt()
//{
//    static unsigned int i;
//    if(P1IFG & BIT1)        //�ж����ж���P2.0����
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
//        P1IFG &= ~BIT1; //����жϱ�־
//    }
//}
//
//#pragma vector=PORT2_VECTOR
//__interrupt void p2Interrupt()
//{
//    static unsigned int i;
//    if(P2IFG & BIT1)        //�ж����ж���P2.1����
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
//        P2IFG &= ~BIT1; //����жϱ�־
//    }
//    if(P2IFG & BIT0)        //�ж����ж���P2.0����
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
//        P2IFG &= ~BIT0; //����жϱ�־
//    }
//}
