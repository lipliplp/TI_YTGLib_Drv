#include "GPIO_PWM.h"

void GPIO_PWM_Init(void)
{
    TA0CTL = TASSEL_2 + ID_0 + MC_1;

    TA0CCTL1 = OUTMOD_7;
    P1SEL |= BIT2;          //��P1.2��� (��ͬ�ͺŵ�Ƭ�����ܲ�һ��)
    P1DIR |= BIT2;          //��P1.2��� (��ͬ�ͺŵ�Ƭ�����ܲ�һ��)

    TA0CCTL2 = OUTMOD_7;
    P1SEL |= BIT3;          //��P1.3��� (��ͬ�ͺŵ�Ƭ�����ܲ�һ��)
    P1DIR |= BIT3;          //��P1.3��� (��ͬ�ͺŵ�Ƭ�����ܲ�һ��)

    TA1CTL |= MC_1 + TASSEL_2 + TACLR + ID_3 ;    //ʱ��ΪSMCLK,�Ƚ�ģʽ����ʼʱ���������
    TA1CCTL1 = OUTMOD_7;                          //���ö��PWM
    P2DIR |= BIT0;
    P2SEL |= BIT0;          //��P2.0���
}

void PWM_State(unsigned int Period, unsigned int Duty)
{
    TA0CCR0 = Period;

    TA0CCR1 = Duty;
    TA0CCR2 = Duty;
}

void Servo_Pwm(unsigned int Period, unsigned int Duty)  //62500
{
    TA1CCR1 = Duty;   //���
    TA1CCR0 = Period;
}
