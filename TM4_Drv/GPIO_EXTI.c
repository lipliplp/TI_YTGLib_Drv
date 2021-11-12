#include "GPIO_EXTI.h"
#include "GPIO_LED.h"

void PortFIntHandler(void)
{
    static bool trigger=0;

    //获取中断状态
    uint32_t button = GPIOIntStatus(GPIO_PORTF_BASE, true);
    //清除发生的中断标志
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
    //使能PF时钟
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    //注册中断函数
    GPIOIntRegister(GPIO_PORTF_BASE, PortFIntHandler);

    //设置PF4为输入
    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);

    //2ma输出能力 推挽上拉
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    //PF4配置为下降沿中断
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);

    //开启PF4的中断
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4);
}

