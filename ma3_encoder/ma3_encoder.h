#ifndef _MA3_ENCODER_H
#define  _MA3_ENCODER_H

#include <stm32f4xx_gpio.h>
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"

volatile int16_t IC3ReadValue1, IC3ReadValue2, CaptureNumber, dataCaptureReady, ma3_capture;
float ma3_capture_angle;


void _get_ma3_data(void);
void _ma3_init(void);
void tim3ConfigRising(void);
void tim3ConfigFalling(void);
void initTimers(void);
void initGpio(void);
void TIM3_IRQHandler(void);



#endif
