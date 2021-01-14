/*
 * State_Machine.h
 *
 *  Created on: 2016年4月23日
 *      Author: ZGH
 */

#ifndef STEERINGENGINE_28335_V3_INC_STATE_MACHINE_H_
#define STEERINGENGINE_28335_V3_INC_STATE_MACHINE_H_

#include "include.h"

//-------------- 接收协议------------------------//
//发控装置 ---> 导弹
#define F_LAUCH_MISSILE_A429_CONTROL      0x80	// 控制字、导弹查询字

//------发送协议-----------------------
//导弹 ---> 发射装置
#define MISSILE_LAUCH_A429_STATUS     	  0xA0   // 状态字、导弹类型字
#define MISSILE_LAUCH_A429_AZIMUTH    	  0xA1   // 导引头方位角
#define MISSILE_LAUCH_A429_PITCH      	  0xA2   // 导引头俯仰角
#define MISSILE_LAUCH_A429_POWER_1   	  0xA3   // 电压1
#define MISSILE_LAUCH_A429_POWER_2   	  0xA4   // 电压2
#define MISSILE_LAUCH_A429_POWER_3   	  0xA5   // 电压3
#define MISSILE_LAUCH_A429_POWER_4   	  0xA6   // 电压4

 //相应的数据位定义  发射装置 ---> 导弹
 #define LM_COMMOND_BIT 					8
 #define LM_LOCK_BIT  						16
 #define LM_POWER_BIT 						17
 #define LM_LAUCH_BIT 						18

 #define LM_COMMOND_MASK 					0xff
 #define LM_LOCK_MASK  						0x01
 #define LM_LAUCH_MASK 						0x01
 #define LM_POWER_MASK 						0x01


 //相应的数据位  导弹 ---> 发射装置
 #define ML_NORMAL_BIT  					8
 #define ML_CAPTURE_BIT 					9
 #define ML_TYPE_BIT						10

 #define ML_FLY_CONTROL_POWER_BIT    		12
 #define ML_RAM_CHECK_BIT  					13
 #define ML_GUIDE_CHECK_BIT      			14
 #define ML_IMU_CHECK_BIT 					15
 #define ML_STEERING_CHECK_BIT 				16
 #define ML_FLY_CONTROL_BATTER_BIT  		17
 #define ML_STEERING_BATTER_BIT				18
 #define ML_ENGINE_FIRE_SIGLE_BIT			19

 typedef struct Fly_To_Mis_Messege
 {
	 Uint16 	Missile_Lock;       		 	// 导弹是否解锁   1bit
	 Uint16 	Missile_Power;   	  		 	// 导弹供电           1bit
	 Uint16 	Missile_Lauch;      		 	// 导弹会否发射   1bit
	 Uint16 	Missile_Commond;				// 导弹命令字
 }Fly_To_Mis_Ctr_Info;						// 飞机到导弹的信息结构体

 //导弹 -> 发射装置 数据结构
 //该结构包含了传输过程中所需的信息
 typedef struct Mis_To_Fly_Messege
 {
	 Uint32 Missile_Normal;						// 导弹是否正常	1bit
	 Uint32 Missile_Capture;					// 导弹截获 	1bit
	 Uint32 Missile_Type;     					// 导弹类型

	 Uint32 Fly_Control_Power;             		// 飞控系统供电正常
	 Uint32 RAM_Check;							// 外部RAM自检正常
	 Uint32 Guide_Check;						// 导引自检正常
	 Uint32 IMU_Check;							// IMU 自检正常
	 Uint32 Steering_Check;          			// 舵机自检正常
	 Uint32 Fly_Control_Batter;            		// 飞控系统电池正常
	 Uint32 Steering_Batter;          			// 舵机电池正常
	 Uint32 Engine_Fire_Sigle;          		// 发动机点火信号

     int32  Seeker_Azimuth;						// 导引头方位角
 	 int32  Seeker_Pitch;						// 导引头俯仰角

 	 Uint32 DJ_Batter_Voltage;       			//舵机电池电压
 	 Uint32 SYS_Batter_Voltage;      			//弹载计算机电池电压
 	 Uint32 SYS_12_Voltage;         	 		//弹载计算机+12电压
 	 Uint32 SYS_5_Voltage;      			 	//弹载计算机+5电压
 	 Uint32 SYS_Negative_5_Voltage;      		//弹载计算机-5电压
 	 Uint32 Position_Feedback_Voltage;   		//位置反馈电压
 	 Uint32 Current_Feedback_Voltage;    		//电流反馈电压
  }Mis_To_Fly_Sta_Info;//导弹到飞机的信息结构体

extern Mis_To_Fly_Sta_Info m_mis_fly_Messege;
extern Fly_To_Mis_Ctr_Info m_fly_mis_Messege;

void StateMachine_Init(void);
void Power_State_Machine(Uint16 Receive_Data);
void IMU_State_Machine(Uint16 Receive_Data);

void ARINC_Decode(Uint32 Dat,Fly_To_Mis_Ctr_Info *Control_Information);
void ARINC_Encode(Mis_To_Fly_Sta_Info *Status_Information);
Uint16 Fly_Control_Voltage_Check(void);
void Self_Check_State_Machine(Uint16 *Tartget_Position,Uint16 Feedback_Position);
#endif /* STEERINGENGINE_28335_V3_INC_STATE_MACHINE_H_ */
