#include "ADC.h"
#include "USART.h"

void ADC_Init(void)
{
    P6SEL |= BIT0 + BIT1 + BIT2 + BIT3;
    ADC12CTL0 &= ~ADC12ENC;
    ADC12CTL0 |= ADC12ON + ADC12SHT03 + ADC12MSC;
    ADC12CTL1 |= ADC12SHP + 0x0006;  //多通道连续转换
    ADC12MCTL0 = ADC12INCH_0;
    ADC12MCTL1 = ADC12INCH_1;
    ADC12MCTL2 = ADC12INCH_2;
    ADC12MCTL3 = ADC12INCH_3+ADC12EOS;
    ADC12IE = 0x08;                             //开启ADC读取中断
    ADC12CTL0 |= ADC12ENC;
    ADC12CTL0 |= ADC12SC;                       //开始转换
    _EINT();                                    //开启全局中断
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
    char txt[20];
    unsigned int adc1,adc2,adc3,adc4;

//    sprintf(txt,"ADC=%d\n",value);
//    send_buf((unsigned char *)txt);
    switch(__even_in_range(ADC12IV,34))
    {
        case  0: break;                           // Vector  0:  No interrupt
        case  2: break;                           // Vector  2:  ADC overflow
        case  4: break;                           // Vector  4:  ADC timing overflow
        case  6: break;                           // Vector  6:  ADC12IFG0
        case  8: break;                           // Vector  8:  ADC12IFG1
        case 10: break;                           // Vector 10:  ADC12IFG2
        case 12:
          adc1 = ADC12MEM0;                       // Read ADC12MEM
          adc2 = ADC12MEM1;                       // Read ADC12MEM
          adc3 = ADC12MEM2;                       // Read ADC12MEM
          adc4 = ADC12MEM3;
          break;                           // Vector 12:  ADC12IFG3
        case 14: break;                           // Vector 14:  ADC12IFG4
        case 16: break;                           // Vector 16:  ADC12IFG5
        case 18: break;                           // Vector 18:  ADC12IFG6
        case 20: break;                           // Vector 20:  ADC12IFG7
        case 22: break;                           // Vector 22:  ADC12IFG8
        case 24: break;                           // Vector 24:  ADC12IFG9
        case 26: break;                           // Vector 26:  ADC12IFG10
        case 28: break;                           // Vector 28:  ADC12IFG11
        case 30: break;                           // Vector 30:  ADC12IFG12
        case 32: break;                           // Vector 32:  ADC12IFG13
        case 34: break;                           // Vector 34:  ADC12IFG14
        default: break;
    }
    sprintf(txt,"%d  %d  %d  %d\n",adc1,adc2,adc3,adc4);
    send_buf((unsigned char *)txt);
}
