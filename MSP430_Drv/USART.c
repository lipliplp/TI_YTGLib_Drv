#include "USART.h"

void send_buf(unsigned char *ptr)    //发送字符串
{
    while(*ptr != '\0')
    {
        while(!(UCA1IFG & UCTXIFG));
        UCA1TXBUF = *ptr;
        ptr++;
    }
}

void USART_Init(void)
{
    //串口初始化
//    P4SEL    |=  BIT4+BIT5 ;                        // P4.4,5 = USCI_A1 TXD/RXD
//    UCA1CTL1 |=  UCSWRST;                      // **Put state machine in reset**
//    UCA1CTL1 |=  UCSSEL_1;                     // ACLK
//    UCA1BR0   =  0x03;                         // 32768Hz 9600 波特率为9600
//    UCA1BR1   =  0x00;                             // 32768Hz 9600
//    UCA1MCTL |=  UCBRS_3 + UCBRF_0;           // Modulation UCBRSx=1, UCBRFx=0
//    UCA1CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
//    UCA1IE   |=  UCRXIE;                       // Enable USCI_A1 RX interrupt 使能中断

    P4SEL    |=  BIT4+BIT5 ;                        // P4.4,5 = USCI_A1 TXD/RXD
    UCA1CTL1 |=  UCSWRST;                      // **Put state machine in reset**
    UCA1CTL1 |=  UCSSEL_2;                     // MCLK
    UCA1BR0   =  0xD8;                         // 25MHz 11500 波特率为115200
    UCA1BR1   =  0x00;                             // 25MHz 115200
    UCA1MCTL |=  UCBRS_6 + UCBRF_0;           // Modulation UCBRSx=1, UCBRFx=0
    UCA1CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
    UCA1IE   |=  UCRXIE;                       // Enable USCI_A1 RX interrupt 使能中断

//    P3SEL |= BIT3+BIT4;                       // P3.3,4使用外设功能 = UCA1 TXD/RXD
//    UCA0CTL1 |= UCSWRST;                      // 复位USCI
//    UCA0CTL1 |= UCSSEL_2;                     // 设置SMCLK时钟，用于发生特定波特率
//    UCA0BR0 = 0xD8;                              // 设置波特率， 25MHz 波特率= 115200
//    UCA0BR1 = 0x00;
//    UCA0MCTL |= UCBRS_6 + UCBRF_0;
//    UCA0CTL1 &= ~UCSWRST;                     // 结束复位
//    UCA0IE |= UCRXIE;                         // 使能UCA0接受中断

    _EINT();
}

void uart_putchar(unsigned char dat)
{
    while(!(UCA1IFG & UCTXIFG));
    UCA1TXBUF = dat;
}

//#pragma vector=USCI_A0_VECTOR
//__interrupt void USCI_A0_ISR(void)
//{
//    switch(__even_in_range(UCA0IV,4))
//    {
//        case 0:break;                             // Vector 0 - no interrupt
//        case 2:break;
//        case 4:break;                             // Vector 4 - TXIFG
//        default: break;
//    }
//}

/*************  串口P44-TXD P45-RXD (UCA1)  *************(USB选择M11)*/
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
    switch(__even_in_range(UCA1IV,4))
    {
        case 0:break;
        case 2:                         //串口接收中断
        while(!(UCA1IFG & UCTXIFG));
        UCA1TXBUF = UCA1RXBUF;
        break;
        case 4:break;
        default: break;
    }
}

//
///*************  重定向printf到串口UCA1  **************/
//int fputc(int ch, FILE *stream)
//{
//    uart_putchar((char)ch);
//    return(ch);
//}
