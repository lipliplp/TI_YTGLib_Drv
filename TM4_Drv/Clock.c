#include "Clock.h"

void set_clock(void)
{
    /* MOSC频率16M，SYSDIV5分频，系统时钟源自PLL锁相环倍频，时钟源使用MOSC */
    /* 系统时钟频率400M/2/5=40M */
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);

//    /* MOSC频率16M，SYSDIV2.5分频，系统时钟源自PLL锁相环倍频，时钟源使用MOSC */
//    /* 系统时钟频率400M/2/2.5=80M , 注意这是上限了*/
//    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
//
//    /* MOSC频率16M，SYSDIV不分频，系统时钟来自时钟源，时钟源使用MOSC */
//    /* 系统时钟频率16M/1=16M */
//    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
//
//    //
//    // Configure the device to run at 20 MHz from the PLL using a 4 MHz crystal
//    // as the input.
//    //
//    SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_XTAL_4MHZ | SYSCTL_OSC_MAIN);   //20Mhz输出
}
