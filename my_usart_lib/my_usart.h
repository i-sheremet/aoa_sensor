#ifndef _MY_USART_H
#define _MY_USART_H

#include <stm32f4xx_usart.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <misc.h>

#define USE_USART1


#ifdef USE_USART1
unsigned char U1_TxBuffer[128];
unsigned char U1_TxIndex;
unsigned char U1_TxLeft;
unsigned char U1_RxBuffer[128];
unsigned char U1_RxIndex;
volatile unsigned char U1_TxBusy;

void USART1_NVIC_conf(void);
void USART1_conf(void);
void USART1_Send(unsigned char *message, unsigned int bytes_to_send);
void USART1_IRQHandler(void);
void USART1_SetBaud(unsigned int NewBaud);
#endif

#ifdef USE_USART2
unsigned char U2_TxBuffer[128];
unsigned char U2_TxIndex;
unsigned char U2_TxLeft;
unsigned char U2_RxBuffer[128];
unsigned char U2_RxIndex;
volatile unsigned char U2_TxBusy;

void USART2_NVIC_conf(void);
void USART2_conf(void);
void USART2_Send(unsigned char *message, unsigned int bytes_to_send);
void USART2_IRQHandler(void);
void USART2_SetBaud(unsigned int NewBaud);
#endif

#ifdef USE_USART3
unsigned char U3_TxBuffer[128];
unsigned char U3_TxIndex;
unsigned char U3_TxLeft;
unsigned char U3_RxBuffer[128];
unsigned char U3_RxIndex;
volatile unsigned char U3_TxBusy;

void USART3_NVIC_conf(void);
void USART3_conf(void);
void USART3_Send(unsigned char *message, unsigned int bytes_to_send);
void USART3_IRQHandler(void);
void USART3_SetBaud(unsigned int NewBaud);
void USART3_ReadLast(unsigned char *data, int n);
#endif



#endif
