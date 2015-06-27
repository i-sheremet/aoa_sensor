#ifndef _SEND_BUFFER_H
#define  _SEND_BUFFER_H

#define buf_start 0xAA

# include_next <stdint.h>


void _send_buffer_init(uint8_t temp);
void _compose_buffer_24(uint32_t* buffer);
void _compose_buffer_16(uint16_t* buffer);
void _compose_buffer_8(uint8_t* buffer);
void _send_buffer();
uint8_t _crc_ibutton_update(uint8_t crc, uint8_t data);

uint8_t buf_size, stack_position, sequence, data_buffer[20]; // 20 is the maximum for the buffer, can be extended


#endif
