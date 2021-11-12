#include "GPIO_QEI.h"

uint32_t QEIvget, QEIpget;

void QEIHandler()
{
    static unsigned char i = 0;
    uint32_t status = QEIIntStatus(QEI1_BASE, true);
    i++;
    if(status == QEI_INTTIMER){
        QEIvget = QEIVelocityGet(QEI1_BASE);
        UARTprintf("Vel = %d\n",QEIvget);                               //�����ȡ������ֵ
        QEIpget = QEIPositionGet(QEI1_BASE);                         //�����ȡ��λ��ֵ
        UARTprintf("pos = %d\n",QEIpget);
    }
    QEIIntClear(QEI1_BASE, status);
}

void QEI_Init(void)
{
    //ʹ�ܱ�����1ʱ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_QEI1))
    {
    }

    //ʹ�ܱ�����1����Ҫ�õ���GPIO��ʱ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
    {
    }

    //����GPIOʱ��Ϊ������ģʽ
    GPIOPinConfigure(GPIO_PC5_PHA1);
    GPIOPinConfigure(GPIO_PC6_PHB1);
    GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_5);
    GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_6);

    //���ñ�����1            ABͨ��˫��Ե�ɼ���ABͨ�������ɼ���������4000���������λ
    QEIConfigure(QEI1_BASE, QEI_CONFIG_CAPTURE_A_B|QEI_CONFIG_NO_RESET|QEI_CONFIG_QUADRATURE|QEI_CONFIG_NO_SWAP, 390);

    //QEI�ٶȼ������,1ms����һ���ж�
    QEIVelocityConfigure(QEI1_BASE, QEI_VELDIV_1, 20000);

    //���ñ�����1�˲�
    QEIFilterConfigure(QEI1_BASE,QEI_FILTCNT_2);

    //QEI�ж�����
    QEIIntRegister(QEI1_BASE, QEIHandler);
    QEIIntEnable(QEI1_BASE, QEI_INTTIMER);

    //ʹ�ܱ�����1
    QEIEnable(QEI1_BASE);
    QEIFilterEnable(QEI1_BASE);
    QEIVelocityEnable(QEI1_BASE);

}
