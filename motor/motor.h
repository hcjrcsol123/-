#ifndef _MOTOR_H
#define _MOTOR_H
#include "MOTORandMOVE.h"
//定时中断采用tim6进行中断
//TIM2、3、4、5测速
//TIM2的、TIM5
#define Forward_direction 0//正转
#define Reverse 1//反转
#define pwm_Speed_proportion 2.8169//每50ms355次脉冲，pwm占空电机空载每周期输出脉冲比（需要修改，未调试）
#define Pwm_Parameter 1000
#define Pulse_conversion_coefficient 0.1446//0.196373（实测比例）//0.044328（已作废）//距离转换脉冲比例
#define Angle_conversion_parameters 21.89
#define Centimeter_conversion_parameter_transverse 71.1118//标准62.1118
#define wheel_D 58.85//轮子直径mm

extern int16_t Temp1,Temp2,Temp3,Temp4;//接收编码器的计数值
extern int16_t speed1,speed2,speed3,speed4;//电机pwm目标值
extern int16_t target_speed1,target_speed2,target_speed3,target_speed4;//电机pwm目标值
extern float count_pulse1,count_pulse2,count_pulse3,count_pulse4;//脉冲数累加
extern float Last_count_pulse1,Last_count_pulse2,Last_count_pulse3,Last_count_pulse4;
extern float average_count_pulse;
extern uint8_t Init_motor1_direction_flag,Init_motor2_direction_flag,Init_motor3_direction_flag,Init_motor4_direction_flag;



void timer6(void);//初始化基本定时器
void Encoder1(void);//TIM3，编码器1
void Encoder2(void);//用TIM8
void Encoder3(void);//用TIM1
void Encoder4(void);//用TIM4
int16_t Encoder1_Get(void);
int16_t Encoder2_Get(void);
int16_t Encoder3_Get(void);
int16_t Encoder4_Get(void);
void pwm_TIM5(int16_t PwmParameter);//1KHZ占空比100%
void pwm_TIM2(int16_t PwmParameter);
void PWM_Init(int16_t PwmParameter);
void motor_Init(void);
void motor1_direction_control(uint8_t direction);
void motor2_direction_control(uint8_t direction);
void motor3_direction_control(uint8_t direction);
void motor4_direction_control(uint8_t direction);
void electric_machinery_direction_control(uint8_t motor1,uint8_t motor2,uint8_t motor3,uint8_t motor4);//电机转向调节，0正转，1反转
void motor_Direction_GPIO_Init(void);
void target_speed_all_set(int16_t s1,int16_t s2,int16_t s3,int16_t s4);//同时设置4个目标速度
void motor1_pwm_contorl(int16_t speed);
void motor2_pwm_contorl(int16_t speed);
void motor3_pwm_contorl(int16_t speed);
void motor4_pwm_contorl(int16_t speed);
void motor_control_all(int16_t speed_all_1,int16_t speed_all_2,int16_t speed_all_3,int16_t speed_all_4);
float Pulse_Distance_conversion(float mm);//换算长度为总脉冲数
float Angle_conversion(float angle);
float Centimeter_conversion_transverse(float cm);
float Wit_Read_datapacket(void);

//例程的代码
void CopeCmdData(unsigned char ucData);
void ShowHelp(void);
void CmdProcess(void);
void CopeSensorData(uint32_t uiReg, uint32_t uiRegNum);
void Delayms(uint16_t ucMs);
void AutoScanSensor(void);






#endif
