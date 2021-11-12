#ifndef __GPIO_PWM_H__
#define __GPIO_PWM_H__

#include "msp430.h"

void GPIO_PWM_Init(void);
void PWM_State(unsigned int Period, unsigned int Duty);
void Servo_Pwm(unsigned int Period, unsigned int Duty);

#endif
