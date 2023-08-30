#ifndef _MOVE_H
#define _MOVE_H
#include "MOTORandMOVE.h"



#define Pan_Over 0xfd//单次平移行为完成
#define Fine_tuning_stop 0xfc
#define Forward_direction_1 1
#define Reverse_1 2
#define low_speed 300
#define First_deceleration 150
#define Second_deceleration 90
#define max_speed 800

#define fine_tune_speed 100
#define Scan 0xfe
#define Single_fine_tune 0xfb
#define Pan_Grab 0xfa
#define Standby 0xf9

#define RED_1 0x01
#define GREEN_1 0x02
#define BLUE_1 0X03
#define RED_2 0x04
#define GREEN_2 0x05
#define BLUE_2 0X06

extern uint8_t fine_tune_Flag;
extern float lateral_movement_lenght;



//转过指定角度
void Turn_Angle(uint8_t order,int16_t speed,float angle);
//前进指定距离
void move_front_step(uint8_t order,uint16_t Input_length,int16_t speed,float Init_Angle,uint8_t instruction);
//后退指定距离
void move_back_step(uint8_t order,uint16_t Input_length,int16_t speed,float Init_Angle,uint8_t instruction);
//左移指定距离
void move_left_step(uint8_t order,uint16_t Input_length,int16_t speed,float Init_Angle);
//右移指定距离
void move_right_step(uint8_t order,uint16_t Input_length,int16_t speed,float Init_Angle);
//左移或右移串口接收到的指定距离
void fine_tune(uint8_t order,int16_t speed,uint8_t instruction);


#endif


