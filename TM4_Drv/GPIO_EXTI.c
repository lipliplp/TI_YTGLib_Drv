#include "GPIO_EXTI.h"
#include "GPIO_LED.h"

void PortFIntHandler(void)
{
    static bool trigger=0;

    //��ȡ�ж�״̬
    uint32_t button = GPIOIntStatus(GPIO_PORTF_BASE, true);
    //����������жϱ�־
    GPIOIntClear(GPIO_PORTF_BASE, button);

    if((button&GPIO_PIN_4) == GPIO_PIN_4)
    {
        if(trigger == 0) LED_STATE(0);
        else LED_STATE(1);
        trigger = !trigger;
    }
}

void EXTI_Init(void)    //PF4<->SW1
{
    //ʹ��PFʱ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    //ע���жϺ���
    GPIOIntRegister(GPIO_PORTF_BASE, PortFIntHandler);

    //����PF4Ϊ����
    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);

    //2ma������� ��������
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    //PF4����Ϊ�½����ж�
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);

    //����PF4���ж�
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4);
}

