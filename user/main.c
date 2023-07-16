#include "MOTORandMOVE.h"

// #include <string.h>
// #include <stdio.h>
// #include "stm32f10x.h"
// #include "stm32f10x_gpio.h"
// #include "stm32f10x_rcc.h"
// #include "misc.h"
// #include "wit_c_sdk.h"
// #include "UART1.h"
// #include "delay.h"
// #include "IOI2C.h"


volatile char s_cDataUpdate = 0, s_cCmd = 0xff;
float fAcc[3], fGyro[3], fAngle[3];
// void CmdProcess(void);
// void AutoScanSensor(void);
// void CopeSensorData(uint32_t uiReg, uint32_t uiRegNum);
// void Delayms(uint16_t ucMs);

int main(void)
{
    SysTick_Init();
    Usart1Init(115200);
    IIC_Init();
	WitInit(WIT_PROTOCOL_I2C, 0x50);
	WitI2cFuncRegister(IICwriteBytes, IICreadBytes);
	WitRegisterCallBack(CopeSensorData);
	WitDelayMsRegister(Delayms);
	WitInit(WIT_PROTOCOL_I2C, 0x50);
	s_cDataUpdate = 0;
	WitReadReg(AX, 3);
	motor_Init();
	pid_Init();
	TIM_Cmd(TIM6,DISABLE);
	Delay_ms(500);
    // electric_machinery_direction_control(Forward_direction,Forward_direction,Forward_direction,Forward_direction);
    // target_speed_all_set(0,0,0,0);
	Storage_Packet[0] = 1;
/*test*/
    while (1)
    {

		// Wit_Read_datapacket();
		Turn_degrees_anticlockwise(1,1000,90.0);
		// Turn_degrees_clockwise(1,1000,90.0);
		
    }

}


// void CopeCmdData(unsigned char ucData)
// {
// 	static unsigned char s_ucData[50], s_ucRxCnt = 0;

// 	s_ucData[s_ucRxCnt++] = ucData;
// 	if (s_ucRxCnt < 3)
// 		return; // Less than three data returned
// 	if (s_ucRxCnt >= 50)
// 		s_ucRxCnt = 0;
// 	if (s_ucRxCnt >= 3)
// 	{
// 		if ((s_ucData[1] == '\r') && (s_ucData[2] == '\n'))
// 		{
// 			s_cCmd = s_ucData[0];




			
// 			memset(s_ucData, 0, 50);
// 			s_ucRxCnt = 0;
// 		}
// 		else
// 		{
// 			s_ucData[0] = s_ucData[1];
// 			s_ucData[1] = s_ucData[2];
// 			s_ucRxCnt = 2;
// 		}
// 	}
// }
// static void ShowHelp(void)
// {
// 	UART1_Printf("\r\n************************	 WIT_SDK_DEMO	************************");
// 	UART1_Printf("\r\n************************          HELP           ************************\r\n");
// 	UART1_Printf("UART SEND:a\\r\\n   Acceleration calibration.\r\n");
// 	UART1_Printf("UART SEND:m\\r\\n   Magnetic field calibration,After calibration send:   e\\r\\n   to indicate the end\r\n");
// 	UART1_Printf("UART SEND:U\\r\\n   Bandwidth increase.\r\n");
// 	UART1_Printf("UART SEND:u\\r\\n   Bandwidth reduction.\r\n");
// 	UART1_Printf("UART SEND:B\\r\\n   Baud rate increased to 115200.\r\n");
// 	UART1_Printf("UART SEND:b\\r\\n   Baud rate reduction to 9600.\r\n");
// 	UART1_Printf("UART SEND:h\\r\\n   help.\r\n");
// 	UART1_Printf("******************************************************************************\r\n");
// }

//  void CmdProcess(void)
// {
// 	switch (s_cCmd)
// 	{
// 	case 'a':
// 		if (WitStartAccCali() != WIT_HAL_OK)
// 			UART1_Printf("\r\nSet AccCali Error\r\n");
// 		break;
// 	case 'm':
// 		if (WitStartMagCali() != WIT_HAL_OK)
// 			UART1_Printf("\r\nStart MagCali Error\r\n");
// 		break;
// 	case 'e':
// 		if (WitStopMagCali() != WIT_HAL_OK)
// 			UART1_Printf("\r\nEnd MagCali Error\r\n");
// 		break;
// 	case 'u':
// 		if (WitSetBandwidth(BANDWIDTH_5HZ) != WIT_HAL_OK)
// 			UART1_Printf("\r\nSet Bandwidth Error\r\n");
// 		break;
// 	case 'U':
// 		if (WitSetBandwidth(BANDWIDTH_256HZ) != WIT_HAL_OK)
// 			UART1_Printf("\r\nSet Bandwidth Error\r\n");
// 		break;
// 	case 'B':
// 		if (WitSetUartBaud(WIT_BAUD_115200) != WIT_HAL_OK)
// 			UART1_Printf("\r\nSet Baud Error\r\n");
// 		break;
// 	case 'b':
// 		if (WitSetUartBaud(WIT_BAUD_9600) != WIT_HAL_OK)
// 			UART1_Printf("\r\nSet Baud Error\r\n");
// 		break;
// 	case 'h':
// 		ShowHelp();
// 		break;
// 	default:
// 		return;
// 	}
// 	s_cCmd = 0xff;
// }

//  void CopeSensorData(uint32_t uiReg, uint32_t uiRegNum)
// {
// 	int i;
// 	for (i = 0; i < uiRegNum; i++)
// 	{
// 		switch (uiReg)
// 		{
// 			//            case AX:
// 			//            case AY:
// 		case AZ:
// 			s_cDataUpdate |= ACC_UPDATE;
// 			break;
// 			//            case GX:
// 			//            case GY:
// 		case GZ:
// 			s_cDataUpdate |= GYRO_UPDATE;
// 			break;
// 			//            case HX:
// 			//            case HY:
// 		case HZ:
// 			s_cDataUpdate |= MAG_UPDATE;
// 			break;
// 			//            case Roll:
// 			//            case Pitch:
// 		case Yaw:
// 			s_cDataUpdate |= ANGLE_UPDATE;
// 			break;
// 		default:
// 			s_cDataUpdate |= READ_UPDATE;
// 			break;
// 		}
// 		uiReg++;
// 	}
// }

//  void Delayms(uint16_t ucMs)
// {
// 	delay_ms(ucMs);
// }

//  void AutoScanSensor(void)
// {
// 	int i, iRetry;

// 	for (i = 0; i < 0x7F; i++)
// 	{
// 		WitInit(WIT_PROTOCOL_I2C, i);
// 		iRetry = 2;
// 		do
// 		{
// 			s_cDataUpdate = 0;
// 			WitReadReg(AX, 3);
// 			delay_ms(5);
// 			if (s_cDataUpdate != 0)
// 			{
// 				UART1_Printf("find %02X addr sensor\r\n", i);
// 				ShowHelp();
// 				return;
// 			}
// 			iRetry--;
// 		} while (iRetry);
// 	}
// 	UART1_Printf("can not find sensor\r\n");
// 	UART1_Printf("please check your connection\r\n");
// }


