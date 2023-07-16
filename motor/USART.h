#ifndef _USART_H
#define _USART_H
#include "MOTORandMOVE.h"
extern uint8_t RX_data;
extern uint8_t RX_datapacket[5];
extern uint8_t TX_datapacket[5];
extern uint8_t Storage_Packet[5];
void Usart1Init(unsigned int uiBaud);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_Printf(char *format, ...);
void Serial_SendPacket(void);
uint8_t Serial_GetRxFlag(void);






// void USART3_Init(void);
// void USART3_SEND_data(uint8_t data);
// void USART3_SEND_data_packet(uint8_t *data,uint8_t length);
// void USART3_SENDArr(uint8_t *arr,uint16_t length);
// void USART3_SendString(char *String);
// void USART3_Printf(char *format, ...);


#endif
