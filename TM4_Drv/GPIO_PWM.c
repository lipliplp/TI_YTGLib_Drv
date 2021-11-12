#include "GPIO_PWM.h"

void GPIO_PWM_Init(void)
{
    //配置PWM0  注:TM4有两个PWM模块，这是PWM1，还有PWM0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1))
    {
    }

    //复用GPIO时钟
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    //GPIO引脚复用
    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    GPIOPinConfigure(GPIO_PF3_M1PWM7);
    GPIOPinTypePWM(GPIO_PORTF_BASE,GPIO_PIN_2);
    GPIOPinTypePWM(GPIO_PORTF_BASE,GPIO_PIN_3);

    //配置PWM寄存器          向下计数 | 非同步模式
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    //配置PWM时钟频率         50KHz
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 800);

    //设置PWM1-A占空比   占空比25%
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, 200);
    //设置PWM1-B占空比   占空比75%
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, 600);

    //PWM generator使能
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);

    //使能PWM输出
    PWMOutputState(PWM1_BASE, (PWM_OUT_6_BIT | PWM_OUT_7_BIT), true);
}

void SetDuty(uint8_t duty)
{
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, duty);
    PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);
    //使能发生器模块
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);
}
