#include "MOTORandMOVE.h"
void Turn_degrees_anticlockwise(uint8_t order,int16_t speed,float angle)
{
    if(Storage_Packet[0] == order)
    {        
        float Last_Angle = 0;
        float count_angle = 0;
        Storage_Packet[0] = 0;
        TIM_Cmd(TIM6,ENABLE);//打开定时器
        target_speed_all_set(speed,speed,speed,speed);
        electric_machinery_direction_control(Reverse,Forward_direction,Reverse,Forward_direction);//逆时针方向
        Last_Angle = Wit_Read_datapacket();
        while(count_angle<=angle)
        {
            Wit_Read_datapacket();
            if((int16_t)fAngle[2]==(0))
            {
                Last_Angle = fAngle[2];
            }
            count_angle = count_angle+(fAngle[2]-Last_Angle);
            motor_control_all(speed,speed,speed,speed);//不断刷新最新输入速度
            Last_Angle = fAngle[2];
            UART1_Printf("%.3f , %.3f\r\n",fAngle[2],count_angle);
            
        }
        UART1_Printf("Steering completed\r\n");
        target_speed_all_set(0,0,0,0);
        Delay_ms(500);
        TIM_Cmd(TIM6, DISABLE);
        UART1_SendByte(Pan_Over);
    }   
}


void Turn_degrees_clockwise(uint8_t order,int16_t speed,float angle)
{
    if(Storage_Packet[0] == order)
    {        
        float Last_Angle = 0;
        float count_angle = 0;
        Storage_Packet[0]=0;
        TIM_Cmd(TIM6,ENABLE);//打开定时器
        target_speed_all_set(speed,speed,speed,speed);
        electric_machinery_direction_control(Forward_direction,Reverse,Forward_direction,Reverse);//逆时针方向
        Last_Angle = Wit_Read_datapacket();
        while(count_angle<=angle)
        {
            Wit_Read_datapacket();
            if((int16_t)fAngle[2]==(360))
            {
                Last_Angle =fAngle[2];
            }
            count_angle = count_angle+(Last_Angle-fAngle[2]);
            motor_control_all(speed,speed,speed,speed);//不断刷新最新输入速度
            Last_Angle = fAngle[2];
            UART1_Printf("%.3f , %.3f\r\n",fAngle[2],count_angle);
            
        }
        target_speed_all_set(0,0,0,0);
        Delay_ms(500);
        TIM_Cmd(TIM6, DISABLE);
        UART1_SendByte(Pan_Over);
    }   
}


void move_front_step(uint8_t order,uint8_t Input_length,int16_t speed)
{
    if(Storage_Packet[0] == order)
    {
        TIM_Cmd(TIM6,ENABLE);//打开定时器
        RX_data = 0;
        uint8_t i = 0;
        int16_t length = 0;
        uint8_t A = 0;
        length = Pulse_Distance_conversion(Input_length);
        electric_machinery_direction_control(Forward_direction,Forward_direction,Forward_direction,Forward_direction);//所有电机正转
        target_speed_all_set(speed,speed,speed,speed);
        while(average_count_pulse<length)
        {
            motor_control_all(speed,speed,speed,speed);//不断刷新最新输入度
            if((average_count_pulse>(length-5000))&&(i==0))
            {
                speed = speed-jia_su_can_su;
                target_speed_all_set(speed,speed,speed,speed);
                i = 1;
            }

            if((average_count_pulse>(length-2500))&&(A==0))
            {
                speed = speed-jia_su_can_su;
                target_speed_all_set(speed,speed,speed,speed);
                A = 1;
            }
        }
        target_speed_all_set(0,0,0,0);//达到指定距离，停止.
        Delay_s(1);
        TIM_Cmd(TIM6,DISABLE);//关闭定时器6
        memset(Storage_Packet,0,(sizeof(uint8_t)*5));
        
    }
}




void move_rear_step(uint8_t order,uint8_t Input_length,int16_t speed)
{
    if(Storage_Packet[0] == order)
    {
        TIM_Cmd(TIM6,ENABLE);//打开定时器
        RX_data = 0;
        uint8_t i = 0;
        int16_t length = 0;
        uint8_t A = 0;
        length = Pulse_Distance_conversion(Input_length);
        electric_machinery_direction_control(Reverse,Reverse,Reverse,Reverse);//所有电机正转
        target_speed_all_set(speed,speed,speed,speed);
        while(average_count_pulse<length)
        {
            motor_control_all(speed,speed,speed,speed);//不断刷新最新输入度
            if((average_count_pulse>(length-5000))&&(i==0))
            {
                speed = speed-jia_su_can_su;
                target_speed_all_set(speed,speed,speed,speed);
                i = 1;
            }
            
            if((average_count_pulse>(length-2500))&&(A==0))
            {
                speed = speed-jia_su_can_su;
                target_speed_all_set(speed,speed,speed,speed);
                A = 1;
            }
        }
        target_speed_all_set(0,0,0,0);//达到指定距离，停止.
        Delay_s(1);
        TIM_Cmd(TIM6,DISABLE);//关闭定时器6
        memset(Storage_Packet,0,(sizeof(uint8_t)*5));
        
    }
}


