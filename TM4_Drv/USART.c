#include "USART.h"

void UART0IntHandler(void)
{
    uint32_t ui32Status;

    ui32Status = UARTIntStatus(UART0_BASE, true);

    UARTIntClear(UART0_BASE, ui32Status);

    while(UARTCharsAvail(UART0_BASE))   //ȷ������FIFO���Ƿ����κ��ַ�
    {
        UARTCharPutNonBlocking(UART0_BASE, UARTCharGetNonBlocking(UART0_BASE));
    }
}

void send_buf(unsigned char *ptr)    //�����ַ���
{
    while(*ptr != '\0')
    {
        UARTCharPutNonBlocking(UART0_BASE, *ptr);   //�������������
        ptr++;
    }
}

void USART_Init(void)
{
    //�������ڼĴ���
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
    {
    }

    //�������ڶ�Ӧ��GPIO�ļĴ���
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
    {
    }

    //����GPIO��Ӧ���ڵĹ��ܸ���
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //���ô��ڲ���
//    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UARTStdioConfig(0,115200,SysCtlClockGet());
    //ʹ�ܴ��ڽ����ж�
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    //ע������жϺ���
    UARTIntRegister(UART0_BASE, UART0IntHandler);
}
