#include "GPIO_PWM.h"

void GPIO_PWM_Init(void)
{
    //����PWM0  ע:TM4������PWMģ�飬����PWM1������PWM0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1))
    {
    }

    //����GPIOʱ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    //GPIO���Ÿ���
    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    GPIOPinConfigure(GPIO_PF3_M1PWM7);
    GPIOPinTypePWM(GPIO_PORTF_BASE,GPIO_PIN_2);
    GPIOPinTypePWM(GPIO_PORTF_BASE,GPIO_PIN_3);

    //����PWM�Ĵ���          ���¼��� | ��ͬ��ģʽ
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    //����PWMʱ��Ƶ��         50KHz
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 800);

    //����PWM1-Aռ�ձ�   ռ�ձ�25%
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, 200);
    //����PWM1-Bռ�ձ�   ռ�ձ�75%
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, 600);

    //PWM generatorʹ��
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);

    //ʹ��PWM���
    PWMOutputState(PWM1_BASE, (PWM_OUT_6_BIT | PWM_OUT_7_BIT), true);
}

void SetDuty(uint8_t duty)
{
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, duty);
    PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);
    //ʹ�ܷ�����ģ��
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);
}
