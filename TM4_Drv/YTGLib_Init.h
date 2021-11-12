#ifndef __YTGLIB_INIT_H__
#define __YTGLIB_INIT_H__
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "driverlib/adc.h"
#include "driverlib/pwm.h"
#include "utils/uartstdio.h"
#include "driverlib/qei.h"
#include "driverlib/eeprom.h"
#include "driverlib/flash.h"

#define delay_ms(n); SysCtlDelay(n*(SysCtlClockGet()/3000));
#define delay_us(n); SysCtlDelay(n*(SysCtlClockGet()/3000000));
#endif
