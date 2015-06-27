#include "send_buffer.h"


void _send_buffer_init(uint8_t temp) //uint8_t matrix_size
{
  buf_size=temp;
  stack_position=2; // 0 - buf_start, 1 - sequence
  sequence=0;
  data_buffer[0]=buf_start;
  data_buffer[1]=sequence;
}

void _send_buffer()
{
  uint8_t crc=0x00;
  data_buffer[1]=sequence;  //second matrix cell for sequence

  for(uint8_t i=0; i<buf_size; i++)
  {
      printf("%d ",data_buffer[i]);                            //SEND FUNCTION
      crc=_crc_ibutton_update(crc,data_buffer[i]);

      if(i==buf_size-2)  //the last cell before crc
        data_buffer[buf_size-1]=crc;
  }

  sequence++;
  stack_position=2;
}

void _compose_buffer_24(uint32_t* buffer)
{
    //transfer of 24 bit only, but not 32
    data_buffer[stack_position] = (*buffer >> 16) & 0xFF;
    data_buffer[stack_position+1] = (*buffer >> 8) & 0xFF;
    data_buffer[stack_position+2] = *buffer & 0xFF;

    stack_position=stack_position + sizeof(*buffer) - 1; // -1 for 24 bit of 32

    if (stack_position==buf_size-1)
        _send_buffer();
}

void _compose_buffer_8(uint8_t* buffer)
{
    //transfer of 24 bit only, but not 32
    data_buffer[stack_position] = *buffer;


    stack_position=stack_position + sizeof(*buffer);

    if (stack_position==buf_size-1)
        _send_buffer();
}

void _compose_buffer_16(uint16_t* buffer)
{
    data_buffer[stack_position] = (*buffer >> 8) & 0xFF;
    data_buffer[stack_position+1] = *buffer & 0xFF;

    stack_position=stack_position + sizeof(*buffer);

    if (stack_position==buf_size-1)
       _send_buffer();
}

uint8_t _crc_ibutton_update(uint8_t crc, uint8_t data)
{
    crc = crc ^ data;
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        if (crc & 0x01)
            crc = (crc >> 1) ^ 0x8C;
        else
            crc >>= 1;
    }
    return crc;
}
