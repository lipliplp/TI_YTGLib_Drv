#include "ADC.h"
#include "USART.h"
#include "string.h"
#include "stdio.h"

void ADC_Init(void)
{
    //开启ADC0时钟
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0))
    {
    }
    //开启复位引脚时钟
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    //选择模拟ADC0引脚功能。
     GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_0);
    //配置ADC通道
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0);
    ADCSequenceEnable(ADC0_BASE, 0);
}

void ADC_Read(void)
{
    uint32_t ui32Value;
    char buf[20];

    ADCProcessorTrigger(ADC0_BASE, 0);
    while(!ADCIntStatus(ADC0_BASE, 0, false))   //等待读取完成
    {
    }

    ADCSequenceDataGet(ADC0_BASE, 0, &ui32Value);

    sprintf(buf,"ADC = %d\n",ui32Value);
    send_buf((unsigned char *)buf);

}
