#include "MS4525.h"


const  float P_min = 0x0666f; //from datasheet A-type measurement
const  float P_max = 0x399Af; //from datasheet A-type measurement
const float PSI_to_Pa = 6894.757f; //coefficient



int _start_ms4525_trans(void)
{
    while(timer_ms(10))
      {
        I2C_start(I2C1, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
        I2C_write(I2C1, 0x01); // write one byte to the slave
        I2C_stop(I2C1); // stop the transmission
      }
 }

int _get_ms4525_data()
{
  I2C_start(I2C1, SLAVE_ADDRESS << 1, I2C_Direction_Receiver);

  // receive packet
  received_data[0] = I2C_read_ack(I2C1);
  received_data[1] = I2C_read_ack(I2C1);
  received_data[2] = I2C_read_nack(I2C1);

  //convert data
  ms4525_status = received_data[0] >> 6;

  ms4525_pressure = (received_data[0] << 8)+received_data[1];
  ms4525_pressure = 0x3FFF & ms4525_pressure;

  ms4525_temp = ((received_data[2 ]<< 3 | 0x0000) | received_data[3] >> 5);
  ms4525_temp = ((200.0f * ms4525_temp) / 2047) - 50;

  //convert to PSI and PASCAL
  ms4525_press_PSI = - (P_min + (((ms4525_pressure - 0.1f*16383) * (P_max-P_min))) / (0.8f*16383)); //minus here defines the pitot tube connection
  ms4525_pressure_PAS=ms4525_press_PSI * PSI_to_Pa;

}


