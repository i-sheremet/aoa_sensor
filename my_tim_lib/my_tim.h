/*Postal
*
* library that has TIM_2 configured
* as well as two different delay_ms functions
*
*
*/

#ifndef _MY_TIM_H
#define _MY_TIM_H

#include "stm32f4xx_tim.h"
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

int TIM2_init(void);
void delay_ms_timer(uint32_t ms);
int timer_ms(uint32_t ms);
void delay_ms(uint32_t ms);

#endif
