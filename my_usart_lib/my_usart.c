#include "my_usart.h"



#ifdef USE_USART1
void USART1_NVIC_conf(void)
{
	    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	    NVIC_InitTypeDef NVIC_InitStr;

	    NVIC_InitStr.NVIC_IRQChannel = USART1_IRQn;
	    NVIC_InitStr.NVIC_IRQChannelPreemptionPriority = 0;
	    NVIC_InitStr.NVIC_IRQChannelSubPriority = 2;
	    NVIC_InitStr.NVIC_IRQChannelCmd = ENABLE;
	    NVIC_Init(&NVIC_InitStr);
}

void USART1_init(void)
{
	//****************  USART 1  ********************//
	//************** pins - PB6,PB7 *****************//
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	U1_RxIndex =0;
	U1_TxIndex =0;
	U1_TxBusy = 0;
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

void USART1_Send(unsigned char *message, unsigned int bytes_to_send)
{
	if(U1_TxBusy == 1) return;
	U1_TxLeft = bytes_to_send;//set index for task
	U1_TxIndex = 0;
	int i;
	for(i=0; i<bytes_to_send; ++i)
	U1_TxBusy = 1;
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		//Interrupt routine upon recieving a message
		U1_RxBuffer[U1_RxIndex] = USART_ReceiveData(USART1);
		//USART_ClearITPendingBit(USART1, USART_FLAG_RXNE);

	//HMR_InterpretData(U1_RxBuffer[U1_RxIndex++]);
	if(U1_RxIndex==128) U1_RxIndex = 0 ;
	}
	if((USART_GetITStatus(USART1, USART_IT_TXE) == SET))
	{

		USART_SendData(USART1, U1_TxBuffer[U1_TxIndex++]);

		if(--U1_TxLeft == 0)
		{
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
			U1_TxIndex = 0;
			U1_TxBusy = 0;
		}
	}
}

void USART1_SetBaud(unsigned int NewBaud)
{	USART_Cmd(USART1, DISABLE);
	//USART_DeInit(USART1);
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = NewBaud;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_InitStructure);
		USART_Cmd(USART1, ENABLE);
}
#endif


#ifdef USE_USART2
void USART2_NVIC_conf(void)
{
	    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	    NVIC_InitTypeDef NVIC_InitStr;

	    NVIC_InitStr.NVIC_IRQChannel = USART2_IRQn;
	    NVIC_InitStr.NVIC_IRQChannelPreemptionPriority = 0;
	    NVIC_InitStr.NVIC_IRQChannelSubPriority = 2;
	    NVIC_InitStr.NVIC_IRQChannelCmd = ENABLE;
	    NVIC_Init(&NVIC_InitStr);
}
void USART2_conf(void)
{
	//****************  USART 2  ********************//

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate = 57600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE);
	U2_RxIndex =0;
	U2_TxIndex =0;
	U2_TxBusy = 0;
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

}
void USART2_Send(unsigned char *message, unsigned int bytes_to_send)
{
	U2_TxLeft = bytes_to_send;//set index 0
	U2_TxIndex = 0;
	int i;
	for(i=0; i<bytes_to_send; ++i) U2_TxBuffer[i] = message[i];//copy to buffer
	U2_TxBusy = 1;
	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		//Interrupt routine upon recieving a message
		U2_RxBuffer[U2_RxIndex++] = USART_ReceiveData(USART2);
		USART_ClearITPendingBit(USART2, USART_FLAG_RXNE);
		if(U2_RxIndex==128) U2_RxIndex = 0 ;
	}
	if((USART_GetITStatus(USART2, USART_IT_TXE) == SET))
	{
		USART_SendData(USART2, U2_TxBuffer[U2_TxIndex++]);

		if(--U2_TxLeft == 0)
		{
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
			U2_TxIndex = 0;
			U2_TxBusy = 0;
		}
	}
}

void USART2_SetBaud(unsigned int NewBaud)
{
	USART_Cmd(USART2, DISABLE);
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = NewBaud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE);
}

#endif

#ifdef USE_USART3
void USART3_NVIC_conf(void)
{
	    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	    NVIC_InitTypeDef NVIC_InitStr;

	    NVIC_InitStr.NVIC_IRQChannel = USART3_IRQn;
	    NVIC_InitStr.NVIC_IRQChannelPreemptionPriority = 0;
	    NVIC_InitStr.NVIC_IRQChannelSubPriority = 2;
	    NVIC_InitStr.NVIC_IRQChannelCmd = ENABLE;
	    NVIC_Init(&NVIC_InitStr);
}
void USART3_conf(void)
{
	//****************  USART 3  ********************//

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART3, &USART_InitStructure);
	USART_Cmd(USART3, ENABLE);
	U3_RxIndex =0;
	U3_TxIndex =0;
	U3_TxBusy = 0;
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
}
void USART3_Send(unsigned char *message, unsigned int bytes_to_send)
{
	U3_TxLeft = bytes_to_send;//set index for task
	U3_TxIndex = 0;
	int i;
	for(i=0; i<bytes_to_send; ++i) U3_TxBuffer[i] = message[i];//copy to buffer
	U3_TxBusy = 1;
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
}
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
	{
		//Interrupt routine upon recieving a message
		U3_RxBuffer[U3_RxIndex] = USART_ReceiveData(USART3);
		//USART_ClearITPendingBit(USART1, USART_FLAG_RXNE);

		//GX3_TakeData(U3_RxBuffer[U3_RxIndex++]);
		if(U3_RxIndex==128) U3_RxIndex = 0 ;
	}
	if((USART_GetITStatus(USART3, USART_IT_TXE) == SET))
	{

		USART_SendData(USART3, U3_TxBuffer[U3_TxIndex++]);

		if(--U3_TxLeft == 0)
		{
			USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
			U3_TxIndex = 0;
			U3_TxBusy = 0;
		}
	}
}
void USART3_SetBaud(unsigned int NewBaud)
{
	USART_Cmd(USART3, DISABLE);
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = NewBaud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	USART_Cmd(USART3, ENABLE);
}
void USART3_ReadLast(unsigned char *data, int n)
{
	int tmp = U3_RxIndex, i;
	if(tmp > 0) --tmp;
	else tmp = 127;//buffer end place
	for(i = n -1; i >=0; --i)
	{
		data[i] = U3_RxBuffer[tmp];
		if(tmp > 0) --tmp;
		else tmp = 127;//buffer end place
	}
}
#endif
