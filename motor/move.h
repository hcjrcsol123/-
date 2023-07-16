#ifndef _MOVE_H
#define _MOVE_H
#include "MOTORandMOVE.h"
#define FL1 GPIO_Pin_2
#define FL2 GPIO_Pin_3
#define FR1 GPIO_Pin_4
#define FR2 GPIO_Pin_5

#define LL1 GPIO_Pin_0
#define LL2 GPIO_Pin_1
#define LR1 GPIO_Pin_2
#define LR2 GPIO_Pin_3

#define RL1 GPIO_Pin_9
#define RL2 GPIO_Pin_10
#define RR1 GPIO_Pin_11
#define RR2 GPIO_Pin_12

#define BL1 GPIO_Pin_11
#define BL2 GPIO_Pin_12
#define BR1 GPIO_Pin_13
#define BR2 GPIO_Pin_14

#define motor1_positive_electrode GPIO_Pin_3
#define motor1_negative_electrode GPIO_Pin_4
#define motor2_positive_electrode GPIO_Pin_4
#define motor2_negative_electrode GPIO_Pin_5
#define motor3_positive_electrode GPIO_Pin_0
#define motor3_negative_electrode GPIO_Pin_1
#define motor4_positive_electrode GPIO_Pin_14
#define motor4_negative_electrode GPIO_Pin_15
#define motor1_pwm_GPIO GPIOA
#define motor2_pwm_GPIO GPIOC
#define motor3_pwm_GPIO GPIOB
#define motor4_pwm_GPIO GPIOB


#define Front_grayscale GPIOG
#define Left_grayscale GPIOF
#define Right_grayscale GPIOG
#define Rear_grayscale GPIOF

#define zhuan_wan_zeng_liang 150//目标速度减去该增量
#define jia_su_can_su 150
#define Pan_Over 0xfd//单次平移行为完成
#define Turning_speed 300
void Turn_degrees_clockwise(uint8_t order,int16_t speed,float angle);
void Turn_degrees_anticlockwise(uint8_t order,int16_t speed,float angle);
void move_front_step(uint8_t order,uint8_t Input_length,int16_t speed);//向前移动，行动序号，目标长度，本次行动最高速度。
void move_rear_step(uint8_t order,uint8_t Input_length,int16_t speed);//向后移动，行动序号，目标长度，本次行动最高速度。

#endif


