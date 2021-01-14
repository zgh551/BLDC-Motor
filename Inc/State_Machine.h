/*
 * State_Machine.h
 *
 *  Created on: 2016��4��23��
 *      Author: ZGH
 */

#ifndef STEERINGENGINE_28335_V3_INC_STATE_MACHINE_H_
#define STEERINGENGINE_28335_V3_INC_STATE_MACHINE_H_

#include "include.h"

//-------------- ����Э��------------------------//
//����װ�� ---> ����
#define F_LAUCH_MISSILE_A429_CONTROL      0x80	// �����֡�������ѯ��

//------����Э��-----------------------
//���� ---> ����װ��
#define MISSILE_LAUCH_A429_STATUS     	  0xA0   // ״̬�֡�����������
#define MISSILE_LAUCH_A429_AZIMUTH    	  0xA1   // ����ͷ��λ��
#define MISSILE_LAUCH_A429_PITCH      	  0xA2   // ����ͷ������
#define MISSILE_LAUCH_A429_POWER_1   	  0xA3   // ��ѹ1
#define MISSILE_LAUCH_A429_POWER_2   	  0xA4   // ��ѹ2
#define MISSILE_LAUCH_A429_POWER_3   	  0xA5   // ��ѹ3
#define MISSILE_LAUCH_A429_POWER_4   	  0xA6   // ��ѹ4

 //��Ӧ������λ����  ����װ�� ---> ����
 #define LM_COMMOND_BIT 					8
 #define LM_LOCK_BIT  						16
 #define LM_POWER_BIT 						17
 #define LM_LAUCH_BIT 						18

 #define LM_COMMOND_MASK 					0xff
 #define LM_LOCK_MASK  						0x01
 #define LM_LAUCH_MASK 						0x01
 #define LM_POWER_MASK 						0x01


 //��Ӧ������λ  ���� ---> ����װ��
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
	 Uint16 	Missile_Lock;       		 	// �����Ƿ����   1bit
	 Uint16 	Missile_Power;   	  		 	// ��������           1bit
	 Uint16 	Missile_Lauch;      		 	// ���������   1bit
	 Uint16 	Missile_Commond;				// ����������
 }Fly_To_Mis_Ctr_Info;						// �ɻ�����������Ϣ�ṹ��

 //���� -> ����װ�� ���ݽṹ
 //�ýṹ�����˴���������������Ϣ
 typedef struct Mis_To_Fly_Messege
 {
	 Uint32 Missile_Normal;						// �����Ƿ�����	1bit
	 Uint32 Missile_Capture;					// �����ػ� 	1bit
	 Uint32 Missile_Type;     					// ��������

	 Uint32 Fly_Control_Power;             		// �ɿ�ϵͳ��������
	 Uint32 RAM_Check;							// �ⲿRAM�Լ�����
	 Uint32 Guide_Check;						// �����Լ�����
	 Uint32 IMU_Check;							// IMU �Լ�����
	 Uint32 Steering_Check;          			// ����Լ�����
	 Uint32 Fly_Control_Batter;            		// �ɿ�ϵͳ�������
	 Uint32 Steering_Batter;          			// ����������
	 Uint32 Engine_Fire_Sigle;          		// ����������ź�

     int32  Seeker_Azimuth;						// ����ͷ��λ��
 	 int32  Seeker_Pitch;						// ����ͷ������

 	 Uint32 DJ_Batter_Voltage;       			//�����ص�ѹ
 	 Uint32 SYS_Batter_Voltage;      			//���ؼ������ص�ѹ
 	 Uint32 SYS_12_Voltage;         	 		//���ؼ����+12��ѹ
 	 Uint32 SYS_5_Voltage;      			 	//���ؼ����+5��ѹ
 	 Uint32 SYS_Negative_5_Voltage;      		//���ؼ����-5��ѹ
 	 Uint32 Position_Feedback_Voltage;   		//λ�÷�����ѹ
 	 Uint32 Current_Feedback_Voltage;    		//����������ѹ
  }Mis_To_Fly_Sta_Info;//�������ɻ�����Ϣ�ṹ��

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
