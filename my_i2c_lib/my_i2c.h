/*Postal
*
* library that initialize I2C
*
*
*
*/

#ifndef _MY_i2c_H
#define _MY_i2c_H

#include "stm32f4xx_i2c.h"
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

void I2C1_init();
void I2C_start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction);
void I2C_write(I2C_TypeDef* I2Cx, uint8_t data);
uint8_t I2C_read_ack(I2C_TypeDef* I2Cx);
uint8_t I2C_read_nack(I2C_TypeDef* I2Cx);
void I2C_stop(I2C_TypeDef* I2Cx);


#endif
