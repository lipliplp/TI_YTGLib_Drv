#include "Timer.h"
#include "GPIO_LED.h"
#include "USART.h"

uint16_t timer0A_cnt;

void Timer1AIntHandler(void)
{
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    UARTprintf("timer0A_cnt = %d\n",timer0A_cnt);
}
//中断服务函数 理论周期：0.001s
void Timer0AIntHandler(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_CAPA_MATCH);
    timer0A_cnt++;
}

void Timer_Init(void)
{
    // 启用Timer0模块
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0))
    {
    }

    // 启用GPIOB作为脉冲捕捉脚
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
    {
    }

    // 配置GPIO脚为使用Timer0捕捉模式
    GPIOPinConfigure(GPIO_PB6_T0CCP0);
    GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_6);

    // 为管脚配置弱上拉模式（捕获下降沿，配置为上拉）
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_6, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // 配置使用Timer0A模块配置为普通定时器
    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_COUNT_UP);

    // 使用下降沿触发
    TimerControlEvent(TIMER0_BASE, TIMER_A, TIMER_EVENT_NEG_EDGE);

    // 设置计数范围
    TimerMatchSet(TIMER0_BASE, TIMER_A, 50-1);

    // 注册中断处理函数以响应触发事件
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0AIntHandler);

    // 时钟中断允许，中断事件为Capture模式中边沿触发，计数到达预设值
    TimerIntEnable(TIMER0_BASE, TIMER_CAPA_MATCH);

    // 启动TIM0
    TimerEnable(TIMER0_BASE, TIMER_A);

    //使能Timer0A的中断
    IntEnable(INT_TIMER0A);

    // 启用Timer1模块
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1))
    {
    }
    // 配置使用Timer1的TimerA配置为普通定时器
    TimerConfigure(TIMER1_BASE, TIMER_CFG_A_PERIODIC);
    //一般来说定时器加载值为SysCtlClockGet()/N-1，定时时间为1/N秒
    TimerLoadSet(TIMER1_BASE, TIMER_A, (SysCtlClockGet()/1)-1);
    //为Timer1A注册中断处理函数
    TimerIntRegister(TIMER1_BASE, TIMER_A, Timer1AIntHandler);
    //定时器超时中断
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    // 启动TIM1
    TimerEnable(TIMER1_BASE, TIMER_A);
    //使能Timer1A的中断
    IntEnable(INT_TIMER1A);

    //使能对处理器的中断
    IntMasterEnable();
}

//void Timer_Init(void)
//{
//    //开启定时器时钟
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
//    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0))
//    {
//    }
//    //配置定时器
//    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);  //周期性计数模式  级联模式
//
//    //一般来说定时器加载值为SysCtlClockGet()/N-1，定时时间为1/N秒
//    TimerLoadSet(TIMER0_BASE, TIMER_A, (SysCtlClockGet()/1)-1);
//
//    //使能Timer0A的中断
//    IntEnable(INT_TIMER0A);
//
//    //配置中断源，配置为超时时产生中断
//    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
//
//    //使能对处理器的中断
//    IntMasterEnable();
//
//    //为Timer0A注册中断处理函数
//    TimerIntRegister(TIMER0_BASE,TIMER_A,Timer0IntHandler);
//
//    //使能TIMER0A
//    TimerEnable(TIMER0_BASE, TIMER_A);
//}

