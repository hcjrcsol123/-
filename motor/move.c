#include "MOTORandMOVE.h"
uint8_t fine_tune_Flag = 0;
float lateral_movement_lenght = 0.0;

void Turn_Angle_gyro(uint8_t order,int16_t speed,float angle)
{
    if((Storage_Packet[0] == order)||(RX_datapacket[0]==order))
    {   
        uint8_t fangxiang = 0;
        float Now_Relative_angle = 0;
        float Init_Angle = 0;
        // float last_Relative_angle = 0.0;
        // float last_last_Relative_angle = 0.0;
        memset(RX_datapacket,0,(sizeof(uint8_t)*5));
        memset(Storage_Packet,0,(sizeof(uint8_t)*5));
        if(angle>=0.0)
        {
            electric_machinery_direction_control(Reverse,Forward_direction,Forward_direction,Reverse);//逆时针方向
            fangxiang = 0;
            angle*=1.0;
            //0.799
        }
        else if(angle<0.0)
        {
            electric_machinery_direction_control(Forward_direction,Reverse,Reverse,Forward_direction);//顺时针方向
            fangxiang = 1;
            angle*=1.0;
            //angle*=0.847;
        }
        WitInit(WIT_PROTOCOL_I2C, 0x50);
        WitI2cFuncRegister(IICwriteBytes, IICreadBytes);
        WitRegisterCallBack(CopeSensorData);
        WitDelayMsRegister(Delayms);
        s_cDataUpdate = 0;
        delay_ms(200);
        delay_ms(5);
        TIM_Cmd(TIM6,ENABLE);//打开定时器
        
        target_speed_all_set(speed,speed,speed,speed);
        Init_Angle = Wit_Read_datapacket();
        //Now_Relative_angle
        switch (fangxiang)
        {
        case 0:
            while(Now_Relative_angle<=angle)
            {
                Now_Relative_angle = Wit_Read_datapacket()-Init_Angle;
                
                if((Now_Relative_angle>=(-Init_Angle))&&(Now_Relative_angle<0.0))
                {
                    Now_Relative_angle = Now_Relative_angle+359.0;
                }
                if(Now_Relative_angle>350.0)
                {
                    Now_Relative_angle=Now_Relative_angle-359.0;
                }
                // else if((Now_Relative_angle>=180.0)&&(Now_Relative_angle>0.0))
                // {
                //     Now_Relative_angle = Now_Relative_angle-359.0;
                // }
                //UART1_Printf("%.2f %.2f\r\n",Now_Relative_angle,Init_Angle);
                // last_last_Relative_angle = last_Relative_angle;
                // last_Relative_angle = Now_Relative_angle;
            }
            break;
        case 1:
            while(Now_Relative_angle>=angle)
            {
                Now_Relative_angle = Wit_Read_datapacket()-Init_Angle;
                if((Now_Relative_angle>Init_Angle)&&(Now_Relative_angle>0.0))
                {
                    Now_Relative_angle = Now_Relative_angle-359.0;
                }
                if(Now_Relative_angle<(-350.0))
                {
                    Now_Relative_angle = 359.0-Now_Relative_angle;
                }
                //UART1_Printf("%.2f %.2f\r\n",Now_Relative_angle,Init_Angle);
                // last_last_Relative_angle = last_Relative_angle;
                // last_Relative_angle = Now_Relative_angle;
            }
            break;
        default:
            break;
        }

        target_speed_all_set(0,0,0,0);
        motor_control_all(0,0,0,0);
        Delay_ms(600);
        motor_control_all(0,0,0,0);
        electric_machinery_direction_control(0,0,0,0);
        TIM_Cmd(TIM6, DISABLE);
        TX_datapacket_assignment(Pan_Over,0xff,0xff,order,0xff);
        UART1_send_datapacket();
        memset(TX_datapacket,0xff,(sizeof(uint8_t)*5));
        count_pulse1 = 0;
        count_pulse2 = 0;
        count_pulse3 = 0;
        count_pulse4 = 0;
        average_count_pulse = 0;
        // target_speed_all_set(0,0,0,0);
        // TX_datapacket_assignment(0xfd,0xff,0xff,order,0xff);
        // UART1_send_datapacket();
        // memset(Storage_Packet,0,(sizeof(uint8_t)*5));
        // memset(TX_datapacket,0xff,(sizeof(uint8_t)*5));
        // Delay_ms(600);
        // motor_control_all(0,0,0,0);
        // electric_machinery_direction_control(0,0,0,0);
        // TIM_Cmd(TIM6, DISABLE);
        // count_pulse1 = 0;
        // count_pulse2 = 0;
        // count_pulse3 = 0;
        // count_pulse4 = 0;
        // average_count_pulse = 0;
    }   
}

void Turn_Angle(uint8_t order,int16_t speed,float angle)
{
    if((Storage_Packet[0] == order)||(RX_datapacket[0]==order))
    {
        float target_angle = 0;
        target_angle = Angle_conversion(angle);
        target_angle = abs(target_angle);
        memset(RX_datapacket,0,(sizeof(uint8_t)*5));
        memset(Storage_Packet,0,(sizeof(uint8_t)*5));
        if(angle>=0.0)
        {
            electric_machinery_direction_control(Reverse,Forward_direction,Forward_direction,Reverse);//逆时针方向
        }
        else if(angle<0.0)
        {
            electric_machinery_direction_control(Forward_direction,Reverse,Reverse,Forward_direction);//顺时针方向
        }
        TIM_Cmd(TIM6,ENABLE);//打开定时器
        delay_ms(50);
        while(average_count_pulse<target_angle)
        {
            target_speed_all_set(speed,speed,speed,speed);
        }
        target_speed_all_set(0,0,0,0);
        motor_control_all(0,0,0,0);
        Delay_ms(600);
        motor_control_all(0,0,0,0);
        electric_machinery_direction_control(0,0,0,0);
        TIM_Cmd(TIM6, DISABLE);
        TX_datapacket_assignment(Pan_Over,0xff,0xff,order,0xff);
        UART1_send_datapacket();
        memset(TX_datapacket,0xff,(sizeof(uint8_t)*5));
        count_pulse1 = 0;
        count_pulse2 = 0;
        count_pulse3 = 0;
        count_pulse4 = 0;
        average_count_pulse = 0;
    }
}

void Turn_Angle_Delay_time(uint8_t order,int16_t speed,float dir,uint16_t time)
{
    if((Storage_Packet[0] == order)||(RX_datapacket[0]==order))
    {
        memset(RX_datapacket,0,(sizeof(uint8_t)*5));
        memset(Storage_Packet,0,(sizeof(uint8_t)*5));
        if(dir>=0.0)
        {
            electric_machinery_direction_control(Reverse,Forward_direction,Forward_direction,Reverse);//逆时针方向
        }
        else if(dir<0.0)
        {
            electric_machinery_direction_control(Forward_direction,Reverse,Reverse,Forward_direction);//顺时针方向
        }
        TIM_Cmd(TIM6,DISABLE);//打开定时器
        delay_ms(50);
        motor_control_all(speed,speed,speed,speed);
        Delay_ms(time);
        motor_control_all(0,0,0,0);
        Delay_ms(600);
        electric_machinery_direction_control(0,0,0,0);
        TIM_Cmd(TIM6, DISABLE);
        TX_datapacket_assignment(Pan_Over,0xff,0xff,order,0xff);
        UART1_send_datapacket();
        memset(TX_datapacket,0xff,(sizeof(uint8_t)*5));
        count_pulse1 = 0;
        count_pulse2 = 0;
        count_pulse3 = 0;
        count_pulse4 = 0;
        average_count_pulse = 0;
    }
}

void move_front_step(uint8_t order,uint16_t Input_length,int16_t speed,float Init_Angle,uint8_t instruction)
{
    if((Storage_Packet[0] == order)||(RX_datapacket[0]==order))
    {
        uint8_t i = 0;//一级减速标志位
        float length = 0;//目标距离
        uint8_t A = 0;//二级减速标志位
        // int16_t turn_speed = 0;
        memset(RX_datapacket,0,(sizeof(uint8_t)*5));
        memset(Storage_Packet,0,(sizeof(uint8_t)*5));
        float Now_Relative_angle = 0;
        length = Pulse_Distance_conversion(Input_length);//目标距离转换函数
        //电机方向初始化
        electric_machinery_direction_control(Forward_direction,Forward_direction,Forward_direction,Forward_direction);//所有电机正转
        target_speed_all_set(speed,speed,speed,speed);//初始化小车速度
		Init_Angle = Wit_Read_datapacket();//姿态角初始化
        Delayms(50);
		TIM_Cmd(TIM6,ENABLE);//打开定时器
        //count_pulse1<length ((count_pulse3+count_pulse4)/2.0)
        while(count_pulse1<length)
        {
            Now_Relative_angle = Wit_Read_datapacket()-Init_Angle;
            //解决角度的过零问题
            if((Now_Relative_angle>180)&&(Now_Relative_angle>0))
            {
                Now_Relative_angle = Now_Relative_angle-360.0;
            }
            else if((Now_Relative_angle<(-180))&&(Now_Relative_angle<0))
            {
                Now_Relative_angle = Now_Relative_angle+360.0;
            }
            //判断距离，预先减速。
            if((count_pulse1>(length*0.5))&&(i==0))
            {
                speed = speed*0.6;
                target_speed_all_set(speed,speed,speed,speed);
                i = 1;
            }
            else if((count_pulse1>(length*0.7))&&(A==0)&&(speed>100||Init_Angle>600))
            {
                speed = Second_deceleration;
                target_speed_all_set(speed,speed,speed,speed);
                A = 1;
            }
            //判断方向
			// if(Now_Relative_angle>0.5)//车往逆时针方向偏
            // {
            //     turn_speed = ((speed-abs(Now_Relative_angle)*3));
            //     if (turn_speed<0)
            //     {
            //         turn_speed=0;
            //     }
                
            //     target_speed_all_set(speed,turn_speed,speed,speed);
            //     UART1_Printf("turn_right\r\n");
                
            // }
            // else if(Now_Relative_angle<(-0.5))//车往顺时针方向偏
            // {
            //     turn_speed = ((speed-abs(Now_Relative_angle)*3));
            //     if (turn_speed<0)
            //     {
            //         turn_speed=0;
            //     }
            //     target_speed_all_set(turn_speed,speed,speed,speed);
            //     UART1_Printf("turn_left\r\n");
            // }
            // else
            // {
            //     target_speed_all_set(speed,speed,speed,speed);
            //     UART1_Printf("front\r\n");
            // }
        }
        target_speed_all_set(0,0,0,0);//达到指定距离，停止.
        Delay_ms(600);
        motor_control_all(0,0,0,0);
        electric_machinery_direction_control(0,0,0,0);
        TIM_Cmd(TIM6, DISABLE);
        TX_datapacket_assignment(Pan_Over,0xff,0xff,order,instruction);
        UART1_send_datapacket();
        memset(TX_datapacket,0xff,(sizeof(uint8_t)*5));
        count_pulse1 = 0;
        count_pulse2 = 0;
        count_pulse3 = 0;
        count_pulse4 = 0;
        average_count_pulse = 0;
    }
}

void move_back_step(uint8_t order,uint16_t Input_length,int16_t speed,float Init_Angle,uint8_t instruction)
{
    if((Storage_Packet[0] == order)||(RX_datapacket[0]==order))
    {
        uint8_t i = 0;//一级减速标志位
        float length = 0;//目标距离
        uint8_t A = 0;//二级减速标志位
        // int16_t turn_speed = 0;
        float Now_Relative_angle = 0;
        memset(RX_datapacket,0,(sizeof(uint8_t)*5));
        memset(Storage_Packet,0,(sizeof(uint8_t)*5));
        length = Pulse_Distance_conversion(Input_length);
        electric_machinery_direction_control(Reverse,Reverse,Reverse,Reverse);//所有电机反转
        target_speed_all_set(speed,speed,speed,speed);
		Init_Angle = Wit_Read_datapacket();
		TIM_Cmd(TIM6,ENABLE);//打开定时器
        //count_pulse1<length
        while(count_pulse1<(length))
        {
            Now_Relative_angle = Wit_Read_datapacket()-Init_Angle;
            //解决角度的过零问题
            if((Now_Relative_angle>180)&&(Now_Relative_angle>0))
            {
                Now_Relative_angle = Now_Relative_angle-360.0;
            }
            else if((Now_Relative_angle<(-180))&&(Now_Relative_angle<0))
            {
                Now_Relative_angle = Now_Relative_angle+360.0;
            }
            //判断距离，预先减速。
            if((count_pulse1>(length*0.5))&&(i==0))
            {
                speed = speed*0.6;
                target_speed_all_set(speed,speed,speed,speed);
                i = 1;
            }
            else if((count_pulse1>(length*0.7))&&(A==0)&&(speed>100||Init_Angle>600))
            {
                speed = Second_deceleration;
                target_speed_all_set(speed,speed,speed,speed);
                A = 1;
            }
            // //判断方向
			// if(Now_Relative_angle>0.5)//车往逆时针方向偏
            // {
            //     turn_speed = ((speed-abs(Now_Relative_angle)*3));
            //     if(turn_speed<0){turn_speed=0;}
            //     target_speed_all_set(speed,speed,speed,turn_speed);
            //     UART1_Printf("turn_right\r\n");
                
            // }
            // else if(Now_Relative_angle<(-0.5))//车往顺时针时针方向偏
            // {
            //     turn_speed = ((speed-abs(Now_Relative_angle)*3));
            //     if(turn_speed<0)
            //     {
            //         turn_speed = 0;
            //     }
            //     target_speed_all_set(speed,speed,turn_speed,speed);
            //     UART1_Printf("turn_left\r\n");
            // }
            // else
            // {
            //     target_speed_all_set(speed,speed,speed,speed);
            //     UART1_Printf("front\r\n");
            // }
        }
        target_speed_all_set(0,0,0,0);//达到指定距离，停止.
        Delay_ms(600);
        motor_control_all(0,0,0,0);
        electric_machinery_direction_control(0,0,0,0);
        TIM_Cmd(TIM6, DISABLE);
        TX_datapacket_assignment(Pan_Over,0xff,0xff,order,0xff);
        UART1_send_datapacket();
        memset(TX_datapacket,0xff,(sizeof(uint8_t)*5));
        count_pulse1 = 0;
        count_pulse2 = 0;
        count_pulse3 = 0;
        count_pulse4 = 0;
        average_count_pulse = 0;
    }
}

void move_left_step(uint8_t order,uint16_t Input_length,int16_t speed)//,float Init_Angle
{
if((Storage_Packet[0] == order)||(RX_datapacket[0]==order))
    {
        float length = 0;//目标距离
        // int16_t turn_speed = 0;
        // float Now_Relative_angle = 0;
        memset(RX_datapacket,0,(sizeof(uint8_t)*5));
        memset(Storage_Packet,0,(sizeof(uint8_t)*5));
        length = Pulse_Distance_conversion(Input_length);
        electric_machinery_direction_control(Reverse,Forward_direction,Reverse,Forward_direction);
        target_speed_all_set(speed,speed,speed,speed);
		//Init_Angle = Wit_Read_datapacket();
		TIM_Cmd(TIM6,ENABLE);//打开定时器
        //count_pulse1<length
        while(count_pulse1<length)
        {
            // Now_Relative_angle = Wit_Read_datapacket()-Init_Angle;
            // //解决角度的过零问题
            // if((Now_Relative_angle>180)&&(Now_Relative_angle>0))
            // {
            //     Now_Relative_angle = Now_Relative_angle-360.0;
            // }
            // else if((Now_Relative_angle<(-180))&&(Now_Relative_angle<0))
            // {
            //     Now_Relative_angle = Now_Relative_angle+360.0;
            // }
            // //判断方向
			// if(Now_Relative_angle>(0.5))//车往逆时针方向偏
            // {
            //     turn_speed = ((speed-abs(Now_Relative_angle)*5));
            //     if(turn_speed<0)
            //     {
            //         turn_speed = 0;
            //     }
            //     target_speed_all_set(turn_speed,speed,speed,speed);
                
                
            // }
            // else if(Now_Relative_angle<(-0.5))//车往顺时针方向偏
            // {
            //     turn_speed = ((speed-abs(Now_Relative_angle)*5));
            //     if(turn_speed<0)
            //     {
            //         turn_speed = 0;
            //     }
            //     target_speed_all_set(speed,speed,speed,turn_speed);
                
            // }
            // else
            // {
            //     target_speed_all_set(speed,speed,speed,speed);
                
            // }
        }
        target_speed_all_set(0,0,0,0);//达到指定距离，停止.
        Delay_ms(600);
        motor_control_all(0,0,0,0);
        electric_machinery_direction_control(0,0,0,0);
        TIM_Cmd(TIM6, DISABLE);
        TX_datapacket_assignment(Pan_Over,0xff,0xff,order,0xff);
        UART1_send_datapacket();
        memset(TX_datapacket,0xff,(sizeof(uint8_t)*5));
        count_pulse1 = 0;
        count_pulse2 = 0;
        count_pulse3 = 0;
        count_pulse4 = 0;
        average_count_pulse = 0;
    }
}

void move_right_step(uint8_t order,uint16_t Input_length,int16_t speed,float Init_Angle)
{
    if((Storage_Packet[0] == order)||(RX_datapacket[0]==order))
    {
        float length = 0;//目标距离
        int16_t turn_speed = 0;
        float Now_Relative_angle = 0;
        length = Pulse_Distance_conversion(Input_length);
        memset(RX_datapacket,0,(sizeof(uint8_t)*5));
        memset(Storage_Packet,0,(sizeof(uint8_t)*5));
        electric_machinery_direction_control(Forward_direction,Reverse,Forward_direction,Reverse);
        target_speed_all_set(speed,speed,speed,speed);
		Init_Angle = Wit_Read_datapacket();
		TIM_Cmd(TIM6,ENABLE);//打开定时器
        //count_pulse1<length
        while(count_pulse1<length)
        {
            UART1_Printf("Temp1=%d Temp2=%d Temp3=%d Temp4=%d angle=%.1f ",Temp1,Temp2,Temp3,Temp4,Now_Relative_angle);
            Now_Relative_angle = Wit_Read_datapacket()-Init_Angle;
            //解决角度的过零问题
            if((Now_Relative_angle>180)&&(Now_Relative_angle>0))
            {
                Now_Relative_angle = Now_Relative_angle-360.0;
            }
            else if((Now_Relative_angle<(-180))&&(Now_Relative_angle<0))
            {
                Now_Relative_angle = Now_Relative_angle+360.0;
            }
            //判断方向
			if(Now_Relative_angle>(0.5))//车往逆时针方向偏
            {
                turn_speed = ((speed-abs(Now_Relative_angle)*5));
                if(turn_speed<0)
                {
                    turn_speed = 0;
                }
                target_speed_all_set(speed,speed,turn_speed,speed);
                UART1_Printf("turn_right\r\n");
            }
            else if(Now_Relative_angle<(-0.5))//车往顺时针方向偏
            {
                turn_speed = ((speed-abs(Now_Relative_angle)*5));
                if(turn_speed<0)
                {
                    turn_speed = 0;
                }
                target_speed_all_set(speed,turn_speed,speed,speed);
                UART1_Printf("turn_left\r\n");
            }
            else
            {
                target_speed_all_set(speed,speed,speed,speed);
                UART1_Printf("front\r\n");
            }
        }
        target_speed_all_set(0,0,0,0);//达到指定距离，停止.
        Delay_ms(600);
        motor_control_all(0,0,0,0);
        electric_machinery_direction_control(0,0,0,0);
        TIM_Cmd(TIM6, DISABLE);
        TX_datapacket_assignment(Pan_Over,0xff,0xff,order,0xff);
        UART1_send_datapacket();
        memset(TX_datapacket,0xff,(sizeof(uint8_t)*5));
        count_pulse1 = 0;
        count_pulse2 = 0;
        count_pulse3 = 0;
        count_pulse4 = 0;
        average_count_pulse = 0;
    }
}

void fine_tune(uint8_t order,int16_t speed,uint8_t instruction)
{
    if((Storage_Packet[0] == order)||(RX_datapacket[0] == order))
    {
        memset(RX_datapacket,0,(sizeof(uint8_t)*5));
        memset(Storage_Packet,0,(sizeof(uint8_t)*5));
        target_speed_all_set(0,0,0,0);
        TIM_Cmd(TIM6,ENABLE);
        while(Storage_Packet[4]!=Fine_tuning_stop)
        {
            while((lateral_movement_lenght-(average_count_pulse))>5&&(fine_tune_Flag==1))
            {                
                if(Storage_Packet[1]==Forward_direction_1)//车头朝向物块，向前是左，向后是右
                {
                    electric_machinery_direction_control(Reverse,Forward_direction,Reverse,Forward_direction);
                    target_speed_all_set(speed,speed,speed,speed);
                }
                else if(Storage_Packet[1]==Reverse_1)
                {
                    electric_machinery_direction_control(Forward_direction,Reverse,Forward_direction,Reverse);
                    target_speed_all_set(speed,speed,speed,speed);
                }
                if(lateral_movement_lenght-average_count_pulse<5||(Storage_Packet[4]==Standby))
                {
                    fine_tune_Flag = 0;
                    target_speed_all_set(0,0,0,0);
                    motor_control_all(0,0,0,0);
                    Delay_ms(200);
                    lateral_movement_lenght = 0.0;
                    count_pulse1 = 0;count_pulse2 = 0;count_pulse3 = 0;count_pulse4 = 0;
                    TX_datapacket_assignment(Pan_Over,0xff,0xff,order,instruction);
                    UART1_send_datapacket();
                    memset(TX_datapacket,0xff,(sizeof(uint8_t)*5));
                    break;
                }
            }
            count_pulse1 = 0;count_pulse2 = 0;count_pulse3 = 0;count_pulse4 = 0;
            average_count_pulse = 0;
            motor_control_all(0,0,0,0);
            
        }
        Delay_ms(300);
        motor_control_all(0,0,0,0);
        electric_machinery_direction_control(0,0,0,0);
        TIM_Cmd(TIM6,DISABLE);
        TX_datapacket_assignment(Pan_Over,0xff,0xff,order+1,0xff);
        UART1_send_datapacket();
        memset(TX_datapacket,0xff,(sizeof(uint8_t)*5));
        count_pulse1 = 0;
        count_pulse2 = 0;
        count_pulse3 = 0;
        count_pulse4 = 0;
        average_count_pulse = 0;
    }
}

void move_front_step_colour(uint8_t order,uint8_t colour,uint16_t Input_length,int16_t speed,float Init_Angle,uint8_t instruction)
{
    if(((Storage_Packet[0] == order)||(RX_datapacket[0]==order))&&((Storage_Packet[3] == colour)||(RX_datapacket[3]==colour)))
    {
        uint8_t i = 0;//一级减速标志位
        float length = 0;//目标距离
        uint8_t A = 0;//二级减速标志位
        // int16_t turn_speed = 0;
        colour_Flag = colour;
        memset(RX_datapacket,0,(sizeof(uint8_t)*5));
        memset(Storage_Packet,0,(sizeof(uint8_t)*5));
        float Now_Relative_angle = 0;
        length = Pulse_Distance_conversion(Input_length);//目标距离转换函数
        //电机方向初始化
        electric_machinery_direction_control(Forward_direction,Forward_direction,Forward_direction,Forward_direction);//所有电机正转
        target_speed_all_set(speed,speed,speed,speed);//初始化小车速度
		Init_Angle = Wit_Read_datapacket();//姿态角初始化
        Delayms(50);
		TIM_Cmd(TIM6,ENABLE);//打开定时器
        //count_pulse1<length ((count_pulse3+count_pulse4)/2.0)
        while(count_pulse1<length)
        {
            Now_Relative_angle = Wit_Read_datapacket()-Init_Angle;
            //解决角度的过零问题
            if((Now_Relative_angle>180)&&(Now_Relative_angle>0))
            {
                Now_Relative_angle = Now_Relative_angle-360.0;
            }
            else if((Now_Relative_angle<(-180))&&(Now_Relative_angle<0))
            {
                Now_Relative_angle = Now_Relative_angle+360.0;
            }
            //判断距离，预先减速。
            if((count_pulse1>(length*0.5))&&(i==0))
            {
                speed = speed*0.6;
                target_speed_all_set(speed,speed,speed,speed);
                i = 1;
            }
            else if((count_pulse1>(length*0.7))&&(A==0)&&(speed>100||Init_Angle>600))
            {
                speed = Second_deceleration;
                target_speed_all_set(speed,speed,speed,speed);
                A = 1;
            }
            //判断方向
			// if(Now_Relative_angle>0.5)//车往逆时针方向偏
            // {
            //     turn_speed = ((speed-abs(Now_Relative_angle)*3));
            //     if (turn_speed<0)
            //     {
            //         turn_speed=0;
            //     }
                
            //     target_speed_all_set(speed,turn_speed,speed,speed);
            //     UART1_Printf("turn_right\r\n");
                
            // }
            // else if(Now_Relative_angle<(-0.5))//车往顺时针方向偏
            // {
            //     turn_speed = ((speed-abs(Now_Relative_angle)*3));
            //     if (turn_speed<0)
            //     {
            //         turn_speed=0;
            //     }
            //     target_speed_all_set(turn_speed,speed,speed,speed);
            //     UART1_Printf("turn_left\r\n");
            // }
            // else
            // {
            //     target_speed_all_set(speed,speed,speed,speed);
            //     UART1_Printf("front\r\n");
            // }
        }
        target_speed_all_set(0,0,0,0);//达到指定距离，停止.
        Delay_ms(600);
        motor_control_all(0,0,0,0);
        electric_machinery_direction_control(0,0,0,0);
        TIM_Cmd(TIM6, DISABLE);
        TX_datapacket_assignment(Pan_Over,0xff,0xff,order,instruction);
        UART1_send_datapacket();
        memset(TX_datapacket,0xff,(sizeof(uint8_t)*5));
        count_pulse1 = 0;
        count_pulse2 = 0;
        count_pulse3 = 0;
        count_pulse4 = 0;
        average_count_pulse = 0;
    }
}

void Turn_Angle_gyro_colour(uint8_t order,int16_t speed,float angle,uint8_t colour)
{
    if((Storage_Packet[0] == order)||(RX_datapacket[0]==order)&&((colour_Flag == colour)||(colour_Flag==colour)))
    {   
        uint8_t fangxiang = 0;
        float Now_Relative_angle = 0;
        float Init_Angle = 0;
        // float last_Relative_angle = 0.0;
        // float last_last_Relative_angle = 0.0;
        memset(RX_datapacket,0,(sizeof(uint8_t)*5));
        memset(Storage_Packet,0,(sizeof(uint8_t)*5));
        if(angle>=0.0)
        {
            electric_machinery_direction_control(Reverse,Forward_direction,Forward_direction,Reverse);//逆时针方向
            fangxiang = 0;
            angle*=1.0;
            //0.799
        }
        else if(angle<0.0)
        {
            electric_machinery_direction_control(Forward_direction,Reverse,Reverse,Forward_direction);//顺时针方向
            fangxiang = 1;
            angle*=1.0;
            //angle*=0.847;
        }
        WitInit(WIT_PROTOCOL_I2C, 0x50);
        WitI2cFuncRegister(IICwriteBytes, IICreadBytes);
        WitRegisterCallBack(CopeSensorData);
        WitDelayMsRegister(Delayms);
        s_cDataUpdate = 0;
        delay_ms(200);
        delay_ms(5);
        TIM_Cmd(TIM6,ENABLE);//打开定时器
        
        target_speed_all_set(speed,speed,speed,speed);
        Init_Angle = Wit_Read_datapacket();
        //Now_Relative_angle
        switch (fangxiang)
        {
        case 0:
            while(Now_Relative_angle<=angle)
            {
                Now_Relative_angle = Wit_Read_datapacket()-Init_Angle;
                
                if((Now_Relative_angle>=(-Init_Angle))&&(Now_Relative_angle<0.0))
                {
                    Now_Relative_angle = Now_Relative_angle+359.0;
                }
                if(Now_Relative_angle>350.0)
                {
                    Now_Relative_angle=Now_Relative_angle-359.0;
                }
                // else if((Now_Relative_angle>=180.0)&&(Now_Relative_angle>0.0))
                // {
                //     Now_Relative_angle = Now_Relative_angle-359.0;
                // }
                //UART1_Printf("%.2f %.2f\r\n",Now_Relative_angle,Init_Angle);
                // last_last_Relative_angle = last_Relative_angle;
                // last_Relative_angle = Now_Relative_angle;
            }
            break;
        case 1:
            while(Now_Relative_angle>=angle)
            {
                Now_Relative_angle = Wit_Read_datapacket()-Init_Angle;
                if((Now_Relative_angle>Init_Angle)&&(Now_Relative_angle>0.0))
                {
                    Now_Relative_angle = Now_Relative_angle-359.0;
                }
                if(Now_Relative_angle<(-350.0))
                {
                    Now_Relative_angle = 359.0-Now_Relative_angle;
                }
                //UART1_Printf("%.2f %.2f\r\n",Now_Relative_angle,Init_Angle);
                // last_last_Relative_angle = last_Relative_angle;
                // last_Relative_angle = Now_Relative_angle;
            }
            break;
        default:
            break;
        }

        target_speed_all_set(0,0,0,0);
        motor_control_all(0,0,0,0);
        Delay_ms(600);
        motor_control_all(0,0,0,0);
        electric_machinery_direction_control(0,0,0,0);
        TIM_Cmd(TIM6, DISABLE);
        TX_datapacket_assignment(Pan_Over,0xff,0xff,order,0xff);
        UART1_send_datapacket();
        memset(TX_datapacket,0xff,(sizeof(uint8_t)*5));
        count_pulse1 = 0;
        count_pulse2 = 0;
        count_pulse3 = 0;
        count_pulse4 = 0;
        average_count_pulse = 0;
        // target_speed_all_set(0,0,0,0);
        // TX_datapacket_assignment(0xfd,0xff,0xff,order,0xff);
        // UART1_send_datapacket();
        // memset(Storage_Packet,0,(sizeof(uint8_t)*5));
        // memset(TX_datapacket,0xff,(sizeof(uint8_t)*5));
        // Delay_ms(600);
        // motor_control_all(0,0,0,0);
        // electric_machinery_direction_control(0,0,0,0);
        // TIM_Cmd(TIM6, DISABLE);
        // count_pulse1 = 0;
        // count_pulse2 = 0;
        // count_pulse3 = 0;
        // count_pulse4 = 0;
        // average_count_pulse = 0;
    }   
}
