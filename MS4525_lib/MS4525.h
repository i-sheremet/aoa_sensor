#ifndef _MS4525_H
#define _MS4525_H

#include "my_i2c.h"
#include "my_tim.h"

#define SLAVE_ADDRESS	0x28

/*
extern const  float P_min = 0x0666f; //from datasheet A-type measurement
extern const  float P_max = 0x399Af; //from datasheet A-type measurement
extern const float PSI_to_Pa = 6894.757f; //coeficient
*/

uint8_t ms4525_status, received_data[4];
int16_t  ms4525_pressure, ms4525_temp;
float ms4525_press_PSI, ms4525_pressure_PAS;

int _start_ms4525_trans(void);
int _get_ms4525_data(void);

#endif
