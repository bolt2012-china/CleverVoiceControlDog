#include "stm32f10x.h"                  // Device header
#include "stdlib.h"
#include <stdio.h>
#include "LED.h"
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "PWM.h"
#include "Movement.h"
#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "Mode.h"


char RxData;			//用于接收串口数据的变量
char move_mode3 = '0';//用于接收语音识别串口数据的变量
char move_mode = '0';//决定状态变量
uint8_t previous_mode = '0';//用于保存上一次接收串口数据的变量
uint16_t T=100; // 记录距离 给初值大于10cm(不触发避障) 

uint16_t ff=0; //连续前进计数
uint16_t bb=0; //连续后退计数
uint16_t ll=0; //连续左转计数
uint16_t rr=0; //连续右转计数

int main(void)
{
	/*模块初始化*/
	LED_Init();			//LED初始化
	LED13_OFF();
	OLED_Init();		//OLED初始化
	OLED_Clear();

	USART1_Init();		//ASRPRO初始化
	USART2_Init();		//语音合成串口初始化
	Servo_Init();		//舵机初始化

	/*进入默认状态*/
	OLED_Clear();
	OLED_ShowImage(0, 0, 128, 64, BMP1); //立正
	mode_stand();

	while (1)
	{  

		RxData = USART1_GetRxData();		//获取语音识别串口接收的数据
		if(RxData != 0)
		{
				move_mode = RxData;
		}
		else
		{
				move_mode = move_mode;
		}
			
		//***互动设置***//
		if (move_mode == 0x32) { //前进
			mode_forward();
		}else if (move_mode == 0x31){
			mode_slowstand();
		}else if (move_mode == 0x33) { //后退
			mode_behind();
		} else if (move_mode ==0x34) { //左转
			mode_left();
		} else if (move_mode == 0x35) { //右转
			mode_right();
		} else if (move_mode == 0x36) { //前后摇摆
			mode_swing_qianhou();
		} else if (move_mode == 0x37) { //左右摇摆
			mode_swing_zuoyou();
		} else if (move_mode == 0x38) { //跳舞
			mode_dance();
		} else if (move_mode == 0x39) { //立正
			mode_stand();
		} else if (move_mode == 0x41) { //起身
			mode_slowstand();
		} else if (move_mode == 0x61) { //坐下
			mode_strech();
		} else if (move_mode == 0x62) { //打招呼
			mode_hello();
		} else if (move_mode == 0x63) { //伸懒腰
			mode_lanyao();
		} else if (move_mode == 0x64) { //抬头
			mode_headup();
		} else if (move_mode == 0x65) { //趴下睡觉
			mode_sleeppa();
		} else if (move_mode == 0x66) { //卧下睡觉
			mode_sleepwo();
		} else if (move_mode == 0x68) { //睡觉
			mode_sleepwo();
		} 
	}
}


