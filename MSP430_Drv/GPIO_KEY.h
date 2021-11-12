#ifndef __GPIO_KEY_H_
#define __GPIO_KEY_H_

#include <msp430.h>
#include "delay.h"

void KEY0_GPIO_Config(void);
void KEY1_GPIO_Config(void);
int KEY0_STATE(void);
int KEY1_STATE(void);
#endif /* GO_BLACK_KEY_H_ */
