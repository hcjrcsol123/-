#include "MOTORandMOVE.h"
uint8_t RX_data;
uint8_t RX_datapacket[5] = {0};
uint8_t TX_datapacket[5] = {0};
uint8_t Storage_Packet[5] = {0};
// void USART3_Init(void)
// {
// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//串口外设时钟
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//GPIO外设时钟
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//复用时钟
// 	GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);


// 	GPIO_InitTypeDef GPIO_InitStructure;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
// 	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOC,&GPIO_InitStructure);

// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//上拉输入
// 	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOC,&GPIO_InitStructure);

// 	USART_InitTypeDef USART_InitStructure;//初始化USART3
// 	USART_InitStructure.USART_BaudRate=115200;//波特率.
// 	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//字长，这里选8位。
// 	USART_InitStructure.USART_StopBits=USART_StopBits_1;//停止位，这里选择一个
// 	USART_InitStructure.USART_Parity=USART_Parity_No;//校验位，这里选择无校验位。
// 	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;//串口模式，发送接收。
// 	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//指定了硬件流控制模式使能还是失能,这里选择失能。
// 	USART_Init(USART3,&USART_InitStructure);


// 	USART_ITConfig(USART3, USART_IT_TXE, DISABLE); 
// 	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//使能USART2,选择中断标志位，选择使能。
// 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//分组NVIC
// 	USART_ClearFlag(USART3,USART_FLAG_TC);

// 	NVIC_InitTypeDef NVIC_InitStructure;
// 	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;//选择USART2中断通道
// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//该参数设置了成员 NVIC_IRQChannel 中的先占优先级
// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//该参数设置了成员 NVIC_IRQChannel 中的从优先级
// 	NVIC_Init(&NVIC_InitStructure);
// 	USART_Cmd(USART3,ENABLE);

// }

// /// @brief 发送一字节
// /// @param data 一字节数据
// void USART3_SEND_data(uint8_t data)
// {
// 	USART_SendData(USART3,data);
// 	while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);//等待数据发送完成。该标志位置1之后，不需要手动清零。
// }
// /// @brief 发送数组
// /// @param arr 准备发送的数据，不包括包头和包尾
// /// @param length 发送长度
// void USART3_SENDArr(uint8_t *arr,uint16_t length)
// {
// 	uint16_t i;
// 	for(i=0;i<length;i++)
// 	{
// 		USART3_SEND_data(arr[i]);
// 	}
// }
// /// @brief 发送数据包
// /// @param data 数组首地址
// void USART3_SEND_data_packet(uint8_t *data,uint8_t length)
// {
// 	USART3_SEND_data(0xff);
// 	USART3_SENDArr(data,length);
// 	USART3_SEND_data(0xfe);
// }


// void USART3_SendString(char *String)
// {
// 	uint8_t i;
// 	for (i = 0; String[i] != '\0'; i ++)
// 	{
// 		USART3_SEND_data(String[i]);
// 	}
// }



// int fputc(int ch, FILE *file)
// {
// 	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
// 	USART_SendData(USART3,ch);
// 	return ch;
// }

// void USART3_Printf(char *format, ...)
// {
// 	char String[100];
// 	va_list arg;
// 	va_start(arg, format);
// 	vsprintf(String, format, arg);
// 	va_end(arg);
// 	USART3_SendString(String);
// }

// void CopeCmdData(unsigned char ucData);
// void USART3_IRQHandler(void)
// {
// 	// static uint8_t RX_State = 0;
// 	// static uint8_t i = 0;
// 	// if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
// 	// {
// 	// 	if(RX_State == 0)
// 	// 	{
// 	// 		if(RX_data==0xff)
// 	// 		{
// 	// 			RX_data = 1;
// 	// 			memset(RX_datapacket,0,(sizeof(uint8_t)*5));
// 	// 		}
// 	// 	}	
// 	// 	else if(RX_State == 1 )
// 	// 	{
// 	// 		RX_datapacket[i] = RX_data;
// 	// 		i++;
// 	// 		if(i>=5)
// 	// 		{
// 	// 			RX_State = 2;
// 	// 		}
// 	// 	}
// 	// 	else if(RX_State == 2)
// 	// 	{
// 	// 		i = 0;
// 	// 		strcpy(Storage_Packet,RX_datapacket);
// 	// 		RX_State = 0;
// 	// 		memset(RX_datapacket,0,(sizeof(uint8_t)*5));
// 	// 	}
// 	// 	USART_ClearITPendingBit(USART3,USART_IT_RXNE);
// 	// }

// 	unsigned char ucTemp;
// 	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
// 	{
// 		ucTemp = USART_ReceiveData(USART3);
// 		CopeCmdData(ucTemp);
// 		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
// 	}
// 	USART_ClearITPendingBit(USART3,USART_IT_ORE);

// }


uint8_t Serial_TxPacket[4];				//FF 01 02 03 04 FE
uint8_t Serial_RxPacket[4];
uint8_t Serial_RxFlag;
void Usart1Init(unsigned int uiBaud)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
	
	USART_InitStructure.USART_BaudRate = uiBaud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure); 
	USART_ITConfig(USART1, USART_IT_TXE, DISABLE); 
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ClearFlag(USART1,USART_FLAG_TC);
	USART_Cmd(USART1, ENABLE);	
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(String[i]);
	}
}




int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}


void Serial_SendPacket(void)
{
	Serial_SendByte(0xFF);
	Serial_SendArray(Serial_TxPacket, 4);
	Serial_SendByte(0xFE);
}

uint8_t Serial_GetRxFlag(void)
{
	if (Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

void USART1_IRQHandler(void)
{
	static uint8_t RxState = 0;
	static uint8_t pRxPacket = 0;
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		uint8_t RxData = USART_ReceiveData(USART1);
		
		if (RxState == 0)
		{
			if (RxData == 0xFF)
			{
				RxState = 1;
				pRxPacket = 0;
			}
		}
		else if (RxState == 1)
		{
			Serial_RxPacket[pRxPacket] = RxData;
			pRxPacket ++;
			if (pRxPacket >= 4)
			{
				RxState = 2;
			}
		}
		else if (RxState == 2)
		{
			if (RxData == 0xFE)
			{
				RxState = 0;
				Serial_RxFlag = 1;
			}
		}
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}



