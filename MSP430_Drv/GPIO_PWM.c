#include "GPIO_PWM.h"

void GPIO_PWM_Init(void)
{
    TA0CTL = TASSEL_2 + ID_0 + MC_1;

    TA0CCTL1 = OUTMOD_7;
    P1SEL |= BIT2;          //从P1.2输出 (不同型号单片机可能不一样)
    P1DIR |= BIT2;          //从P1.2输出 (不同型号单片机可能不一样)

    TA0CCTL2 = OUTMOD_7;
    P1SEL |= BIT3;          //从P1.3输出 (不同型号单片机可能不一样)
    P1DIR |= BIT3;          //从P1.3输出 (不同型号单片机可能不一样)

    TA1CTL |= MC_1 + TASSEL_2 + TACLR + ID_3 ;    //时钟为SMCLK,比较模式，开始时清零计数器
    TA1CCTL1 = OUTMOD_7;                          //配置舵机PWM
    P2DIR |= BIT0;
    P2SEL |= BIT0;          //从P2.0输出
}

void PWM_State(unsigned int Period, unsigned int Duty)
{
    TA0CCR0 = Period;

    TA0CCR1 = Duty;
    TA0CCR2 = Duty;
}

void Servo_Pwm(unsigned int Period, unsigned int Duty)  //62500
{
    TA1CCR1 = Duty;   //舵机
    TA1CCR0 = Period;
}
