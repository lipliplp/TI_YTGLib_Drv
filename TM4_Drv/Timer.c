#include "Timer.h"
#include "GPIO_LED.h"
#include "USART.h"

uint16_t timer0A_cnt;

void Timer1AIntHandler(void)
{
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    UARTprintf("timer0A_cnt = %d\n",timer0A_cnt);
}
//�жϷ����� �������ڣ�0.001s
void Timer0AIntHandler(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_CAPA_MATCH);
    timer0A_cnt++;
}

void Timer_Init(void)
{
    // ����Timer0ģ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0))
    {
    }

    // ����GPIOB��Ϊ���岶׽��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
    {
    }

    // ����GPIO��Ϊʹ��Timer0��׽ģʽ
    GPIOPinConfigure(GPIO_PB6_T0CCP0);
    GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_6);

    // Ϊ�ܽ�����������ģʽ�������½��أ�����Ϊ������
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_6, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // ����ʹ��Timer0Aģ������Ϊ��ͨ��ʱ��
    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_COUNT_UP);

    // ʹ���½��ش���
    TimerControlEvent(TIMER0_BASE, TIMER_A, TIMER_EVENT_NEG_EDGE);

    // ���ü�����Χ
    TimerMatchSet(TIMER0_BASE, TIMER_A, 50-1);

    // ע���жϴ���������Ӧ�����¼�
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0AIntHandler);

    // ʱ���ж������ж��¼�ΪCaptureģʽ�б��ش�������������Ԥ��ֵ
    TimerIntEnable(TIMER0_BASE, TIMER_CAPA_MATCH);

    // ����TIM0
    TimerEnable(TIMER0_BASE, TIMER_A);

    //ʹ��Timer0A���ж�
    IntEnable(INT_TIMER0A);

    // ����Timer1ģ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1))
    {
    }
    // ����ʹ��Timer1��TimerA����Ϊ��ͨ��ʱ��
    TimerConfigure(TIMER1_BASE, TIMER_CFG_A_PERIODIC);
    //һ����˵��ʱ������ֵΪSysCtlClockGet()/N-1����ʱʱ��Ϊ1/N��
    TimerLoadSet(TIMER1_BASE, TIMER_A, (SysCtlClockGet()/1)-1);
    //ΪTimer1Aע���жϴ�����
    TimerIntRegister(TIMER1_BASE, TIMER_A, Timer1AIntHandler);
    //��ʱ����ʱ�ж�
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    // ����TIM1
    TimerEnable(TIMER1_BASE, TIMER_A);
    //ʹ��Timer1A���ж�
    IntEnable(INT_TIMER1A);

    //ʹ�ܶԴ��������ж�
    IntMasterEnable();
}

//void Timer_Init(void)
//{
//    //������ʱ��ʱ��
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
//    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0))
//    {
//    }
//    //���ö�ʱ��
//    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);  //�����Լ���ģʽ  ����ģʽ
//
//    //һ����˵��ʱ������ֵΪSysCtlClockGet()/N-1����ʱʱ��Ϊ1/N��
//    TimerLoadSet(TIMER0_BASE, TIMER_A, (SysCtlClockGet()/1)-1);
//
//    //ʹ��Timer0A���ж�
//    IntEnable(INT_TIMER0A);
//
//    //�����ж�Դ������Ϊ��ʱʱ�����ж�
//    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
//
//    //ʹ�ܶԴ��������ж�
//    IntMasterEnable();
//
//    //ΪTimer0Aע���жϴ�����
//    TimerIntRegister(TIMER0_BASE,TIMER_A,Timer0IntHandler);
//
//    //ʹ��TIMER0A
//    TimerEnable(TIMER0_BASE, TIMER_A);
//}

