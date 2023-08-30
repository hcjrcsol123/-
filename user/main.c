#include "MOTORandMOVE.h"
volatile char s_cDataUpdate = 0, s_cCmd = 0xff;
float fAcc[3], fGyro[3], fAngle[3];
float Init_angle = 0.0;//最初始方向角
int main(void)
{
    SysTick_Init();
    Usart1Init(115200);
    IIC_Init();
	WitInit(WIT_PROTOCOL_I2C, 0x50);
	WitI2cFuncRegister(IICwriteBytes, IICreadBytes);
	WitRegisterCallBack(CopeSensorData);
	WitDelayMsRegister(Delayms);
	s_cDataUpdate = 0;
	// WitReadReg(AX, 3);
	delay_ms(5);
	motor_Init();
	pid_Init();
	TIM_Cmd(TIM6,DISABLE);
	Delay_ms(600);
	motor_control_all(0,0,0,0);
	electric_machinery_direction_control(0,0,0,0);
	Init_angle = Wit_Read_datapacket();//读取初始方向角
/*test*/
RX_datapacket[0] = 1 ;
Storage_Packet[0] = 1;
Delay_ms(600);
    while (1)
    {
		//fine_tune(0,100,Pan_Grab);
		move_left_step(1,150,150,Wit_Read_datapacket());
		// Storage_Packet[0] = 2;
		// RX_datapacket[0] = 2;
		move_front_step(2,630,310,Wit_Read_datapacket(),Scan);
		// Storage_Packet[0] = 3;
		// RX_datapacket[0] = 3;
		Turn_Angle(3,90,-90.0);
		// Storage_Packet[0] = 4;
		// RX_datapacket[0] = 4;
		Turn_Angle(4,90,90.0);
		// Storage_Packet[0] = 5;
		// RX_datapacket[0] = 5;
		move_front_step(5,800,350,Wit_Read_datapacket(),Scan);
		// Storage_Packet[0] = 6;
		// RX_datapacket[0] = 6;
		Turn_Angle(6,90,-90);
		// Storage_Packet[0] = 7;
		// RX_datapacket[0] = 7;
		Turn_Angle(7,90,90);
		// Storage_Packet[0] = 8;
		// RX_datapacket[0] = 8;
		move_front_step(8,400,230,Wit_Read_datapacket(),Scan);
		// Storage_Packet[0] = 9;
		// RX_datapacket[0] = 9;
		Turn_Angle(9,90,90);
		// Storage_Packet[0] = 10;
		// RX_datapacket[0] = 10;
		move_front_step(10,1060,350,Wit_Read_datapacket(),Scan);
		// Storage_Packet[0] = 11;
		// RX_datapacket[0] = 11;
		Turn_Angle(11,90,-90);
		Storage_Packet[0] = 12;
		RX_datapacket[0] = 12;
		move_front_step(12,20,100,Wit_Read_datapacket(),Scan);
		Storage_Packet[0] = 13;
		RX_datapacket[0] = 13;
		fine_tune(13,100,Single_fine_tune);
		Storage_Packet[0] = 14;
		RX_datapacket[0] = 14;
		move_back_step(14,100,100,Wit_Read_datapacket(),Scan);
		Storage_Packet[0] = 15;
		RX_datapacket[0] = 15;
		Turn_Angle(15,90,90);
		Storage_Packet[0] = 16;
		RX_datapacket[0] = 16;
		RX_datapacket[3] = BLUE_1;
		Storage_Packet[3] = BLUE_1;
		if(RX_datapacket[3] == RED_1||Storage_Packet[3] == RED_1)
		{
			move_front_step(16,800,350,Wit_Read_datapacket(),0xaa);
		}
		else if (RX_datapacket[3] == GREEN_1||Storage_Packet[3] == GREEN_1)
		{
			move_front_step(16,650,300,Wit_Read_datapacket(),0xaa);
		}
		else if (RX_datapacket[3] == BLUE_1||Storage_Packet[3] == BLUE_1)
		{
			move_front_step(16,500,300,Wit_Read_datapacket(),0xaa);
		}
	
		Storage_Packet[0] = 17;
		RX_datapacket[0] = 17;
		Turn_Angle(17,90,70);
		Storage_Packet[0] = 18;
		RX_datapacket[0] = 18;
		Turn_Angle(18,55,22);
		Storage_Packet[0] = 19;
		RX_datapacket[0] = 19;
		move_front_step(19,1030,350,Wit_Read_datapacket(),0xaa);
		Storage_Packet[0] = 20;
		RX_datapacket[0] = 20;
		Turn_Angle(20,90,-90);
		Storage_Packet[0] = 21;
		RX_datapacket[0] = 21;
		move_front_step(21,240,100,Wit_Read_datapacket(),0xaa);
		Storage_Packet[0] = 22;
		RX_datapacket[0]  = 22;
		fine_tune(22,100,Single_fine_tune);
		Storage_Packet[0] = 23;
		RX_datapacket[0]  = 23;
		move_back_step(23,240,100,Wit_Read_datapacket(),0xaa);
		Storage_Packet[0] = 24;
		RX_datapacket[0]  = 24;
		Turn_Angle(24,90,90);






		
		

		

		



while (1)
{
	/* code */
}
		count_pulse1=0;
		count_pulse2=0;
		count_pulse3=0;
		count_pulse4=0;
		average_count_pulse=0;
    }
}




