#include "Clock.h"

void set_clock(void)
{
    /* MOSCƵ��16M��SYSDIV5��Ƶ��ϵͳʱ��Դ��PLL���໷��Ƶ��ʱ��Դʹ��MOSC */
    /* ϵͳʱ��Ƶ��400M/2/5=40M */
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);

//    /* MOSCƵ��16M��SYSDIV2.5��Ƶ��ϵͳʱ��Դ��PLL���໷��Ƶ��ʱ��Դʹ��MOSC */
//    /* ϵͳʱ��Ƶ��400M/2/2.5=80M , ע������������*/
//    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
//
//    /* MOSCƵ��16M��SYSDIV����Ƶ��ϵͳʱ������ʱ��Դ��ʱ��Դʹ��MOSC */
//    /* ϵͳʱ��Ƶ��16M/1=16M */
//    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
//
//    //
//    // Configure the device to run at 20 MHz from the PLL using a 4 MHz crystal
//    // as the input.
//    //
//    SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_XTAL_4MHZ | SYSCTL_OSC_MAIN);   //20Mhz���
}
