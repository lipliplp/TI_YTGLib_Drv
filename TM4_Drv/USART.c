#include "USART.h"

void UART0IntHandler(void)
{
    uint32_t ui32Status;

    ui32Status = UARTIntStatus(UART0_BASE, true);

    UARTIntClear(UART0_BASE, ui32Status);

    while(UARTCharsAvail(UART0_BASE))   //确定接收FIFO中是否有任何字符
    {
        UARTCharPutNonBlocking(UART0_BASE, UARTCharGetNonBlocking(UART0_BASE));
    }
}

void send_buf(unsigned char *ptr)    //发送字符串
{
    while(*ptr != '\0')
    {
        UARTCharPutNonBlocking(UART0_BASE, *ptr);   //无阻塞串口输出
        ptr++;
    }
}

void USART_Init(void)
{
    //启动串口寄存器
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
    {
    }

    //启动串口对应的GPIO的寄存器
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
    {
    }

    //设置GPIO对应串口的功能复用
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //配置串口参数
//    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UARTStdioConfig(0,115200,SysCtlClockGet());
    //使能串口接收中断
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    //注册接收中断函数
    UARTIntRegister(UART0_BASE, UART0IntHandler);
}
