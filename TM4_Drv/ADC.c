#include "ADC.h"
#include "USART.h"
#include "string.h"
#include "stdio.h"

void ADC_Init(void)
{
    //����ADC0ʱ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0))
    {
    }
    //������λ����ʱ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    //ѡ��ģ��ADC0���Ź��ܡ�
     GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_0);
    //����ADCͨ��
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0);
    ADCSequenceEnable(ADC0_BASE, 0);
}

void ADC_Read(void)
{
    uint32_t ui32Value;
    char buf[20];

    ADCProcessorTrigger(ADC0_BASE, 0);
    while(!ADCIntStatus(ADC0_BASE, 0, false))   //�ȴ���ȡ���
    {
    }

    ADCSequenceDataGet(ADC0_BASE, 0, &ui32Value);

    sprintf(buf,"ADC = %d\n",ui32Value);
    send_buf((unsigned char *)buf);

}
