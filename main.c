#include <stdio.h> //maybe we don't need it (for printf)
#include <stdint.h>

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "misc.h"

#include "my_usart.h"
#include "my_i2c.h"
#include "my_tim.h"
#include "MS4525.h"
#include "ma3_encoder.h"
#include "send_buffer.h"


typedef signed char  int8_t;
typedef unsigned char  uint8_t;
typedef short  int16_t;
typedef unsigned short  uint16_t;

uint8_t buffer_number=10;

int main(void)
{
    TIM2_init();
    USART1_init();
    I2C1_init();
    _ma3_init();

    _send_buffer_init(buffer_number); // number is matrix dimension 3 bytes (start,seq,crc) + PAYLOAD
    printf("Init complete\n");

    _start_ms4525_trans();
    printf("Start complete\n");

    while(1)
      {

        _get_ms4525_data();
        _get_ma3_data();

      /*
       printf("status=%d\t", ms4525_status);
       printf("pressure=%d\t", ms4525_pressure);
       printf("temp=%d\t", ms4525_temp);
       printf("Value1=%d\t Value2=%d\t Capture=%d\n", IC3ReadValue1, IC3ReadValue2, ma3_capture);
      */
        _compose_buffer_8(&ms4525_status);
        _compose_buffer_16(&ms4525_pressure);
        _compose_buffer_16(&ms4525_temp);
        _compose_buffer_16(&ma3_capture);
        printf("\n");

       delay_ms(100);
      }
}



