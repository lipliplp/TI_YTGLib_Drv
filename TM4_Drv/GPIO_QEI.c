#include "GPIO_QEI.h"

uint32_t QEIvget, QEIpget;

void QEIHandler()
{
    static unsigned char i = 0;
    uint32_t status = QEIIntStatus(QEI1_BASE, true);
    i++;
    if(status == QEI_INTTIMER){
        QEIvget = QEIVelocityGet(QEI1_BASE);
        UARTprintf("Vel = %d\n",QEIvget);                               //输出读取的脉冲值
        QEIpget = QEIPositionGet(QEI1_BASE);                         //输出读取的位置值
        UARTprintf("pos = %d\n",QEIpget);
    }
    QEIIntClear(QEI1_BASE, status);
}

void QEI_Init(void)
{
    //使能编码器1时钟
    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_QEI1))
    {
    }

    //使能编码器1所需要用到的GPIO的时钟
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
    {
    }

    //复用GPIO时钟为编码器模式
    GPIOPinConfigure(GPIO_PC5_PHA1);
    GPIOPinConfigure(GPIO_PC6_PHB1);
    GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_5);
    GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_6);

    //配置编码器1            AB通道双边缘采集，AB通道正交采集，计数到4000则编码器复位
    QEIConfigure(QEI1_BASE, QEI_CONFIG_CAPTURE_A_B|QEI_CONFIG_NO_RESET|QEI_CONFIG_QUADRATURE|QEI_CONFIG_NO_SWAP, 390);

    //QEI速度检测配置,1ms触发一次中断
    QEIVelocityConfigure(QEI1_BASE, QEI_VELDIV_1, 20000);

    //配置编码器1滤波
    QEIFilterConfigure(QEI1_BASE,QEI_FILTCNT_2);

    //QEI中断配置
    QEIIntRegister(QEI1_BASE, QEIHandler);
    QEIIntEnable(QEI1_BASE, QEI_INTTIMER);

    //使能编码器1
    QEIEnable(QEI1_BASE);
    QEIFilterEnable(QEI1_BASE);
    QEIVelocityEnable(QEI1_BASE);

}
