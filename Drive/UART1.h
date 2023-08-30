#ifndef __UART1_H
#define __UART1_H



extern uint8_t TX_datapacket[5];
extern uint8_t RX_datapacket[5];
extern uint8_t RX_data;
extern uint8_t Storage_Packet[5];
void Usart1Init(unsigned int uiBaud);
void UART1_SendByte(uint8_t Byte);
void UART1_SendArray(uint8_t *Array, uint16_t Length);
void UART1_SendString(char *String);
void UART1_Printf(char *format, ...);
void UART1_send_datapacket(void);
void TX_datapacket_assignment(uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4,uint8_t data5);






#endif



