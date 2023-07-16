#ifndef _MOTORandMOVE_H
#define _MOTORandMOVE_H
#include "stm32f10x.h"
#include "motor.h"
#include "PID.h"
#include "Delay.h"
#include "USART.h"
#include "stdlib.h"
#include "move.h"
// #include "OLED.h"
#include "math.h"
#include "string.h"
#include "stdio.h"
#include <stdint.h>
#include <stdarg.h>

#include "delay.h"
#include "IOI2C.h"
#include "UART1.h"
#include "misc.h"
#include "wit_c_sdk.h"
#define ACC_UPDATE   0x01
#define GYRO_UPDATE  0x02
#define ANGLE_UPDATE 0x04
#define MAG_UPDATE   0x08
#define READ_UPDATE  0x80
extern volatile char s_cDataUpdate, s_cCmd;
extern float fAcc[3], fGyro[3], fAngle[3];

#endif
