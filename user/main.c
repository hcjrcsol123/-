#include "MOTORandMOVE.h"
volatile char s_cDataUpdate = 0, s_cCmd = 0xff;
float fAcc[3], fGyro[3], fAngle[3];
float Init_angle = 0.0;//最初始方向角
uint8_t colour_Flag = 0;
int main(void)
{
	int step_auto_flag = step_auto_start;//step_auto_start;
    SysTick_Init();
    Usart1Init(9600);
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
	TIM_Cmd(TIM6,ENABLE);
	Delay_ms(600);
	motor_control_all(0,0,0,0);
	electric_machinery_direction_control(0,0,0,0);
	Init_angle = Wit_Read_datapacket();//读取初始方向角
/*test*/
RX_datapacket[0] = Forward_auto_0 ;
Storage_Packet[0] = Forward_auto_0 ;
Delay_ms(600);
		if(step_auto_flag<step_auto_Boundary)
		{
			
			move_left_step(Forward_auto_0,160,200);
			// Turn_Angle_Delay_time(Forward_auto_2,660,negative_direction,300);
			// move_front_step(Forward_auto_0,90,150,Wit_Read_datapacket(),0xff);
			// RX_datapacket[0] = Forward_auto_1;
			// Storage_Packet[0] = Forward_auto_1;
			// Turn_Angle_gyro(Forward_auto_1,120,-82.0);
			// RX_datapacket[0] = Forward_auto_2;
			// Storage_Packet[0] = Forward_auto_2;
			RX_datapacket[0] = Forward_auto_3;
			Storage_Packet[0] = Forward_auto_3;
			move_front_step(Forward_auto_3,585,300,Wit_Read_datapacket(),0xff);
			RX_datapacket[0] = Forward_auto_4;
			Storage_Packet[0] = Forward_auto_4;
			Turn_Angle_gyro(Forward_auto_4,120,-82.0);
			// RX_datapacket[0] = Forward_auto_5;
			// Storage_Packet[0] = Forward_auto_5;
			// move_back_step(Forward_auto_5,5,90,Wit_Read_datapacket(),0xff);
			TX_datapacket_assignment(Pan_Over,0xff,0xff,0x02,Scan);
			UART1_send_datapacket();
			step_auto_flag = step_auto_stop;
			memset(TX_datapacket,0xff,(sizeof(uint8_t)*5));
		}
// electric_machinery_direction_control(Reverse,Reverse,Reverse,Reverse);
    while (1)
	{
		//Delay_ms(500);
		//下限14，上限18cm //横向极限 7.5cm
		
		//motor_control_all(400,400,400,400);
		// target_speed_all_set(150,150,150,150);
		// Delay_ms(500);
		// for(int i = 0;i<6;i++)
		// {
		// 	target_speed1=100*i;
		// 	target_speed2=100*i;
		// 	target_speed3=100*i;
		// 	target_speed4=100*i;
		// 	Delay_ms(500);
		// }
		// target_speed1=0;
		// target_speed2=0;
		// target_speed3=0;
		// target_speed4=0;
		// Delay_ms(1000);
		// electric_machinery_direction_control(Reverse,Reverse,Reverse,Reverse);
		// for(int i = 0;i<6;i++)
		// {
		// 	target_speed1=100*i;
		// 	target_speed2=100*i;
		// 	target_speed3=100*i;
		// 	target_speed4=100*i;
		// 	Delay_ms(500);
		// }
		// target_speed1=0;
		// target_speed2=0;
		// target_speed3=0;
		// target_speed4=0;
		// Delay_ms(1000);
		// while(1);
		// move_front_step(2,5,90,Wit_Read_datapacket(),0xff);
		//  Storage_Packet[0] = 3;
		//  RX_datapacket[0] = 3;
		Turn_Angle_gyro(3,120,83.0);
		//  Storage_Packet[0] = 4;
		//  RX_datapacket[0] = 4;
		move_front_step(4,810,450,Wit_Read_datapacket(),0xff);
		// Storage_Packet[0] = 5;
		// RX_datapacket[0] = 5;
		Turn_Angle_gyro(5,120,-82.0);
		//  Storage_Packet[0] = 6;
		//  RX_datapacket[0] = 6;
		Turn_Angle_gyro(6,120,83.0);
		//  Storage_Packet[0] = 7;
		// RX_datapacket[0] = 7;
		move_front_step(7,420,230,Wit_Read_datapacket(),0xff);
		// Storage_Packet[0] = 8;
		//  RX_datapacket[0] = 8;
		Turn_Angle_gyro(8,120,90.5);
		//  Storage_Packet[0] = 9;
		// RX_datapacket[0] = 9;
		// RX_datapacket[3] = RED_1;
		// Storage_Packet[3] = RED_1;
		//if(RX_datapacket[3] == RED_1||Storage_Packet[3] == RED_1){//粗加工红
			move_front_step_colour(9,RED_1,650,350,Wit_Read_datapacket(),0xff);
			// colour_Flag = RED_1;
		// }
		//else if (RX_datapacket[3] == GREEN_1||Storage_Packet[3] == GREEN_1){//绿
			move_front_step_colour(9,GREEN_1,840,350,Wit_Read_datapacket(),0xff);
			// colour_Flag = GREEN_1;
		//}
		//else if (RX_datapacket[3] == BLUE_1||Storage_Packet[3] == BLUE_1){//蓝
			move_front_step_colour(9,BLUE_1,1030,350,Wit_Read_datapacket(),0xff);
			// colour_Flag = BLUE_1;
		//}
		//  Storage_Packet[0] = 10;
		//  RX_datapacket[0] = 10;
		// if(colour_Flag==RED_1){Turn_Angle_gyro(10,120,-81.5);}
		// else if(colour_Flag==GREEN_1){Turn_Angle_gyro(10,120,-81.5);}
		// else if(colour_Flag==BLUE_1){Turn_Angle_gyro(10,120,-81.5);}
		Turn_Angle_gyro_colour(10,120,-81.0,RED_1);
		Turn_Angle_gyro_colour(10,120,-81.5,GREEN_1);
		Turn_Angle_gyro_colour(10,120,-80.0,BLUE_1);

		// Storage_Packet[0] = 11;
		// RX_datapacket[0] = 11;
		Turn_Angle_gyro(11,120,84.5);
		// Storage_Packet[0] = 12;
		// RX_datapacket[0] = 12;
		// RX_datapacket[3] = RED_1;
		// Storage_Packet[3] = RED_1;
		// if(RX_datapacket[3] == RED_1||Storage_Packet[3] == RED_1)//精加工红
		// {
			move_front_step_colour(12,RED_2,650,350,Wit_Read_datapacket(),0xff);
		// 	colour_Flag = RED_1;
		// }
		// else if (RX_datapacket[3] == GREEN_1||Storage_Packet[3] == GREEN_1)//绿
		// {
			move_front_step_colour(12,GREEN_2,650,300,Wit_Read_datapacket(),0xff);
		// 	colour_Flag = GREEN_1;
		// }
		// else if (RX_datapacket[3] == BLUE_1||Storage_Packet[3] == BLUE_1)//蓝
		// {
			move_front_step_colour(12,BLUE_2,520,300,Wit_Read_datapacket(),0xff);
		// 	colour_Flag = BLUE_1;
		// }
		// Storage_Packet[0] = 13;
		// RX_datapacket[0] = 13;
		Turn_Angle_gyro_colour(13,120,86.5,RED_2);
		Turn_Angle_gyro_colour(13,120,86.5,GREEN_2);
		Turn_Angle_gyro_colour(13,120,86.5,BLUE_2);
		// if(colour_Flag==RED_1){Turn_Angle_gyro(13,120,86.5);}
		// else if(colour_Flag==GREEN_1){Turn_Angle_gyro(13,120,85.0);}
		// else if(colour_Flag==BLUE_1){Turn_Angle_gyro(13,120,85.0);}
		// Storage_Packet[0] = 15;
		// RX_datapacket[0] = 15;
		// RX_datapacket[3] = RED_2;
		// Storage_Packet[3] = RED_2;
		// if(RX_datapacket[3] == RED_2||Storage_Packet[3] == RED_2)//精加工红到达
		// {
			move_front_step_colour(14,RED_2,570,350,Wit_Read_datapacket(),0xff);

		// }
		// else if(RX_datapacket[3] == GREEN_2||Storage_Packet[3] == GREEN_2)//绿
		// {
			move_front_step_colour(14,GREEN_2,690,300,Wit_Read_datapacket(),0xff);
		// }
		// else if(RX_datapacket[3] == BLUE_2||Storage_Packet[3] == BLUE_2)//蓝
		// {
			move_front_step_colour(14,BLUE_2,1000,300,Wit_Read_datapacket(),0xff);
		// }
		// }
		// Storage_Packet[0] = 16;
		// RX_datapacket[0] = 16;
		Turn_Angle_gyro_colour(15,120,-81.0,RED_2);
		Turn_Angle_gyro_colour(15,120,-81.0,GREEN_2);
		Turn_Angle_gyro_colour(15,120,-81.0,BLUE_2);
		// Storage_Packet[0] = 17;
		// RX_datapacket[0] = 17;
		// move_front_step(16,90,90,Wit_Read_datapacket(),0xff);
		// // Storage_Packet[0] = 18;
		// // RX_datapacket[0] = 18;
		// move_back_step(17,90,90,Wit_Read_datapacket(),0xff);
		// Storage_Packet[0] = 19;
		// RX_datapacket[0] = 19;
		Turn_Angle_gyro(16,120,84.0);
		// Storage_Packet[0] = 20;
		// RX_datapacket[0] = 20;
		move_front_step_colour(17,RED_2,1030,350,Wit_Read_datapacket(),0xff);
		move_front_step_colour(17,GREEN_2,850,350,Wit_Read_datapacket(),0xff);
		move_front_step_colour(17,BLUE_2,800,350,Wit_Read_datapacket(),0xff);
		Turn_Angle_gyro_colour(18,120,88.5,RED_2);
		Turn_Angle_gyro_colour(18,120,89.5,GREEN_2);
		Turn_Angle_gyro_colour(18,120,89.5,BLUE_2);
		move_front_step(19,1000,350,Wit_Read_datapacket(),0xff);

		// while (1)
		// {
		
		// }

    
	}
}




