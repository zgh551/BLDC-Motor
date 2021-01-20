/*
 * State_Machine.c
 *
 *  Created on: 2016��4��23��
 *      Author: ZGH
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "State_Machine.h"

#define ARINC429_Send   10

#define FirstCheckChar  0x55
#define SecondCheckChar 0x77

//define the Power RX state
typedef enum {
HeadFirst = 0,
HeadSecond,
Length,
Commond,
ReceiveData,
CheckSum
} CommunicationState;
CommunicationState Com422_State = HeadFirst;

//422 Communication
typedef struct _RxData{
	Uint16  len;
	Uint16  cmd;
	Uint16  data[100];
	Uint16  checksum;
}RxData;
RxData Rdata;

typedef struct _TxData{
	Uint16  len;
	Uint16  data[96];
	Uint16  checksum;
}TxData;
TxData Tdata;

Uint16 dat_cnt = 0;

Master2DriverMessege m2d_Messege;
Driver2MasterMessege d2m_Messege;

void StateMachine_Init(void)
{
	//communication state machine
	Com422_State 	= HeadFirst;
	Rdata.header 	= 0;
	Rdata.len    	= 0;
	Rdata.checksum	= 0;
	for(i=0; i < 240; i++)
	{
		Rdata.data[i] = 0;
	}
	dat_cnt=0;
}

void BLDC_SelfCheck(void)
{
	Uint16 i = 0, check_sum = 0;

	Tdata.len = 8;
	Tdata.data[0] = SELFCHECK_REACT;
	Tdata.data[1] = Driver2MasterMessege.DriverBoardCheck; // 驱动板自检故障码		
	Tdata.data[2] = Driver2MasterMessege.MotorCheck;	   // 电机自检故障码
	Tdata.data[3] = Driver2MasterMessege.SoftwareVersion_L;  // 驱动板软件版本号 低
	Tdata.data[4] = Driver2MasterMessege.SoftwareVersion_H;  // 驱动板软件版本号 高
	Tdata.data[5] = 0;
	Tdata.data[6] = 0;
	Tdata.data[7] = 0;

	Steering_Send_Byte_B(0x55);
	Steering_Send_Byte_B(0x77);
	Steering_Send_Byte_B(Tdata.len);
	check_sum = 0;
	for (i = 0; i < Tdata.len; i++)
	{
		check_sum += Tdata.data[i];
		Steering_Send_Byte_B(Tdata.data[i]);
	}
	Steering_Send_Byte_B(check_sum & 0x00ff);
}

void CommandResponse(Uint16 rsp)
{
	Uint16 i = 0, check_sum = 0;
	Tdata.len = 8;
	Tdata.data[0] = rsp;
	Tdata.data[1] = 3;	
	Tdata.data[2] = 0;
	Tdata.data[3] = 0;  
	Tdata.data[4] = 0;
	Tdata.data[5] = 0;
	Tdata.data[6] = 0;
	Tdata.data[7] = 0;

	Steering_Send_Byte_B(0x55);
	Steering_Send_Byte_B(0x77);
	Steering_Send_Byte_B(Tdata.len);
	check_sum = 0;
	for (i = 0; i < Tdata.len; i++)
	{
		check_sum += Tdata.data[i];
		Steering_Send_Byte_B(Tdata.data[i]);
	}
	Steering_Send_Byte_B(check_sum & 0x00ff);
}

void BLDC_Delivery(void)
{
	Uint16 i = 0, check_sum = 0;

	Tdata.len = 8;
	Tdata.data[0] = 0x82;
	Tdata.data[1] = 3;	
	Tdata.data[2] = 0;
	Tdata.data[3] = 0;  
	Tdata.data[4] = 0;
	Tdata.data[5] = 0;
	Tdata.data[6] = 0;
	Tdata.data[7] = 0;

	Steering_Send_Byte_B(0x55);
	Steering_Send_Byte_B(0x77);
	Steering_Send_Byte_B(Tdata.len);
	check_sum = 0;
	for (i = 0; i < Tdata.len; i++)
	{
		check_sum += Tdata.data[i];
		Steering_Send_Byte_B(Tdata.data[i]);
	}
	Steering_Send_Byte_B(check_sum & 0x00ff);
}

void BLDC_Reset(void)
{
	Uint16 i = 0, check_sum = 0;

	Tdata.len = 8;
	Tdata.data[0] = 0x83;
	Tdata.data[1] = 3;	
	Tdata.data[2] = 0;
	Tdata.data[3] = 0;  
	Tdata.data[4] = 0;
	Tdata.data[5] = 0;
	Tdata.data[6] = 0;
	Tdata.data[7] = 0;

	Steering_Send_Byte_B(0x55);
	Steering_Send_Byte_B(0x77);
	Steering_Send_Byte_B(Tdata.len);
	check_sum = 0;
	for (i = 0; i < Tdata.len; i++)
	{
		check_sum += Tdata.data[i];
		Steering_Send_Byte_B(Tdata.data[i]);
	}
	Steering_Send_Byte_B(check_sum & 0x00ff);
}


void CommunicationStateMachine(Uint16 Receive_Data)
{
	switch(Com422_State)
	{
		case HeadFirst:
				Com422_State = (Receive_Data == FirstCheckChar) 
							 ? HeadSecond : HeadFirst;
		break;

		case HeadSecond:
			Com422_State = (Receive_Data == SecondCheckChar) 
						 ? Length : HeadFirst;
		break;

		case Length:
			Rdata.len      = Receive_Data;
			Rdata.checksum = 0;
			Com422_State   = Commond;
		break;

		case Commond:
			dat_cnt         = 0;
			Rdata.cmd       = Receive_Data;
			Rdata.checksum += Receive_Data;
			Com422_State    = ReceiveData;
		break;

		case ReceiveData:
			if(dat_cnt >= Rdata.len)
			{
				Com422_State = CheckSum;
			}
			else
			{
				Rdata.data[dat_cnt] = Receive_Data;
				Rdata.checksum     += Receive_Data;
				dat_cnt++;
			}
		break;

		case CheckSum:
			Rdata.checksum = Rdata.checksum & 0x00ff;
			if(Receive_Data == Rdata.checksum)//check sum
			{
				if(SELFCHECK == Rdata.cmd) // self check
				{
					m2d_Messege.Commond = SELFCHECK;
				}
				else if(DELIVERRY == Rdata.cmd) // 投放
				{
					m2d_Messege.Commond = DELIVERRY;
					m2d_Messege.DeliveryStrategyNumber = Rdata.data[0]; // 投放策略编号
					m2d_Messege.MotorRotateCount       = Rdata.data[1]; // 电机旋转次数
					for (Uint16 i = 0; i < m2d_Messege.MotorRotateCount; i++)
					{
						m2d_Messege.RotateTurns[i]  = Rdata.data[2 + 3 * i]; // 旋转圈数
						m2d_Messege.RotateTimes[i]  = Rdata.data[3 + 3 * i]; // 旋转总运行时间
						m2d_Messege.TimeInterval[i] = Rdata.data[4 + 3 * i]; // 两次的时间间隔
					}
				}
				else if(RESET == Rdata.cmd) //Reset
				{
					m2d_Messege.Commond = RESET;
					m2d_Messege.HighSpeedReverseNumber = Rdata.data[0]; // 高速反转圈数
					m2d_Messege.LowSpeedReverseNumber  = Rdata.data[1]; // 低速反转圈数
				}
				else if(APROXMT_ZERO == Rdata.cmd) //近似零位
				{
					m2d_Messege.Commond = APROXMT_ZERO;
				}
				else
				{
					// invalid commond
				}
			}
			else//data receive err
			{

			}
			Com422_State = HeadFirst;
		break;

		default :
			Com422_State = HeadFirst;
		break;
	}
}

//Uint16 temp1,temp2,j,x_data[14];
//void IMU_State_Machine(Uint16 Receive_Data)
//{
//
//	switch(IMU_State)
//	{
//		case IMU_HeadFirst:
//			if(Receive_Data == 0x7f)
//			{
//				IMU_State = IMU_HeadSecond;
//			}
//			else
//			{
//				IMU_State = IMU_HeadFirst;
//			}
//			break;
//		case IMU_HeadSecond:
//			if(Receive_Data == 0x80)
//			{
//				IMU_State = IMU_ReceiveData;
//				IMU_cnt = 0;
//			}
//			else
//			{
//				IMU_State = IMU_HeadFirst;
//			}
//			break;
//		case IMU_ReceiveData:
//			IMU_Buffer.Dat[IMU_cnt+2] = Receive_Data;
//			IMU_cnt++;
//			if(IMU_cnt == 12)
//			{
//				IMU_cnt = 0;
//				IMU_State = IMU_CRC_Check;
//			}
//			break;
//		case IMU_CRC_Check:
//			IMU_Buffer.CRC16_Check[IMU_cnt] = Receive_Data;
//			IMU_cnt++;
//			if(IMU_cnt == 2)
//			{
////				temp1 = crc2(IMU_Buffer.Dat,14);
////				temp2 = usMBCRC16(IMU_Buffer.Dat,14);
////				IMU_cnt = 0;
////				Steering_Send_Byte(0xaa);
//				IMU_State = IMU_HeadFirst;
//			}
//			break;
//		default:
//			IMU_cnt = 0;
//			IMU_State = IMU_HeadFirst;
//			break;
//	}
//}


//void Self_Check_State_Machine(Uint16 *Tartget_Position,Uint16 Feedback_Position)
//{
//	switch(Self_check_state)
//	{
//	case Voltage_Check:
//		*Tartget_Position = 500;
//		if(0x5AA5 == Voltage_Check_Finish)
//		{
//			if(m_mis_fly_Messege.Guide_Check && m_mis_fly_Messege.IMU_Check &&
//			m_mis_fly_Messege.RAM_Check && m_mis_fly_Messege.Fly_Control_Power)
//			{
//				Missle_Ready(1);
//				m_mis_fly_Messege.Missile_Normal = 1;
//				Time_ms_cnt = 0;
//				#if Rocket_Bomb
//					Self_check_state = Batter_Check;
//					Steering_Send_Byte(Batter_Check);
//				#else
//					Self_check_state = Steering_SlefCheck;
//					Steering_Send_Byte(Steering_SlefCheck);
//				#endif
//				ARINC_Encode(&m_mis_fly_Messege);
//				ARINC_Encode(&m_mis_fly_Messege);
//				ARINC_Encode(&m_mis_fly_Messege);
//			}
//			else
//			{
//				Missle_Ready(0);
//				m_mis_fly_Messege.Missile_Normal = 0;
//				Self_check_state = Err;
//				Steering_Send_Byte(Err);
//			}
//		}
//		break;
//	case Steering_SlefCheck:
//		*Tartget_Position = 500;
//		if(0x5C == m_fly_mis_Messege.Missile_Commond)//Wait for the Steering SelfCheck
//		{
//			Time_ms_cnt = 0;
//			Steering_Check_cnt = 0;
//			Self_check_state = Steering_Check_Position_one;
//			Steering_Send_Byte(Steering_Check_Position_one);
//		}
//		break;
//	case Steering_Check_Position_one:
//		Time_ms_cnt++;
//		//200 -> 1022
//		*Tartget_Position = 200;
//		if(Feedback_Position < 1500)
//		{
//			Steering_Check_cnt++;
//		}
//		if(Steering_Check_cnt > 100)
//		{
//			Time_ms_cnt = 0;
//			Steering_Check_cnt=0;
//			Self_check_state = Steering_Check_Position_two;
//			Steering_Send_Byte(Steering_Check_Position_two);
//		}
//		if(Time_ms_cnt >= 600)
//		{
//			m_mis_fly_Messege.Steering_Check = 0;
//			Self_check_state = Err;
//			Steering_Send_Byte(Err);
//		}
//		break;
//	case Steering_Check_Position_two:
//		Time_ms_cnt++;
//		// 800 -> 3520
//		*Tartget_Position = 800;
//		if(Feedback_Position > 3000)
//		{
//			Steering_Check_cnt++;
//		}
//		if(Steering_Check_cnt > 100)
//		{
//			m_mis_fly_Messege.Steering_Check = 1;
//			Self_check_state = Batter_Check;//Batter_Check
//			Steering_Send_Byte(Batter_Check);
//			Time_ms_cnt = 0;
//			Steering_Check_cnt = 0;
//			ARINC_Encode(&m_mis_fly_Messege);
//			ARINC_Encode(&m_mis_fly_Messege);
//			ARINC_Encode(&m_mis_fly_Messege);
//		}
//		if(Time_ms_cnt >= 600)
//		{
//			m_mis_fly_Messege.Steering_Check = 0;
//			Self_check_state = Err;
//			Steering_Send_Byte(Err);
//		}
//		break;
//	case Batter_Check:
//		*Tartget_Position = 500;
//		if((0x5D == m_fly_mis_Messege.Missile_Commond) && (m_fly_mis_Messege.Missile_Lauch))
//		{
//			Model_Type = 0x1234;
//			if(0xABCD == Batter_Check_Flag)
//			{
//				Time_ms_cnt = 0;
//				ARINC_Encode(&m_mis_fly_Messege);
//				ARINC_Encode(&m_mis_fly_Messege);
//				ARINC_Encode(&m_mis_fly_Messege);
//				Self_check_state = Fire;
//				Steering_Send_Byte(Fire);
//			}
//			Time_ms_cnt++;
//			if(Time_ms_cnt >= 3000)
//			{
//				Self_check_state = Err;//�޸�
//				Time_ms_cnt = 0;
//			}
//		}
//		break;
//	case Fire:
//		*Tartget_Position = 500;
//		if(Time_ms_cnt >= 200)
//		{
//			Time_ms_cnt = 200;
//		}
//		if(Time_ms_cnt > 0 && Time_ms_cnt < 100)
//		{
//			Fire_Ready_ON();
//			Fire_OFF();
//		}
//		if(Time_ms_cnt >= 100 && Time_ms_cnt < 200)
//		{
//			Fire_Ready_ON();
//			Fire_ON();
//			m_mis_fly_Messege.Engine_Fire_Sigle = 1;
//			ARINC_Encode(&m_mis_fly_Messege);
//			ARINC_Encode(&m_mis_fly_Messege);
//			ARINC_Encode(&m_mis_fly_Messege);
//		}
//		if(Time_ms_cnt >= 200)
//		{
//			Fire_Ready_OFF();
//			Fire_OFF();
//			Self_check_state = Idle;
//			Steering_Send_Byte(Idle);
//			Time_ms_cnt=0;
//		}
//		Time_ms_cnt++;
//		break;
//	case Idle:
//		Model_Type = 0xA5A5;
//		*Tartget_Position = 500;
//		break;
//	case Err:
//		Time_ms_cnt = (Time_ms_cnt + 1)%40;
//		if(Time_ms_cnt == 0)
//		{
//			if(Steering_StateFlag)
//			{
//				Steering_StateFlag = 0;
//			}
//			else
//			{
//				Steering_StateFlag = 1;
//			}
//
//			if(Steering_StateFlag)
//			{
//				*Tartget_Position = 700;
//			}
//			else
//			{
//				*Tartget_Position = 300;
//			}
//		}
//		break;
//	default:
//		Self_check_state = Idle;
//		break;
//	}
//}
//
//void ARINC_Decode(Uint32 Dat,Fly_To_Mis_Ctr_Info *Control_Information)
//{
//	switch(Dat & 0x00ff)
//	{
//		case F_LAUCH_MISSILE_A429_CONTROL: // �����֡�������ѯ��
//			Control_Information->Missile_Commond        =   (Dat >> LM_COMMOND_BIT) & LM_COMMOND_MASK;
//			Control_Information->Missile_Lock			=	(Dat >> LM_LOCK_BIT   ) & LM_LOCK_MASK ;
//			Control_Information->Missile_Power			=	(Dat >> LM_POWER_BIT  ) & LM_POWER_MASK;
//			Control_Information->Missile_Lauch 			=   (Dat >> LM_LAUCH_BIT  ) & LM_LAUCH_MASK;
//		break;
//		default:
//			Control_Information->Missile_Lauch 				= 0;
//			Control_Information->Missile_Lock				= 0;
//			Control_Information->Missile_Power				= 0;
//			Control_Information->Missile_Commond            = 0;
//		break;
//	}
//}

//void ARINC_Encode(Mis_To_Fly_Sta_Info *Status_Information)
//{
//	Uint32  ARINC_Dat;
//	ARINC_Dat = (Status_Information->Missile_Normal  	   << ML_NORMAL_BIT)   			|// �����Ƿ�����
//				(Status_Information->Missile_Capture       << ML_CAPTURE_BIT)  			|// �����ػ�
//				(Status_Information->Missile_Type    	   << ML_TYPE_BIT)     			|// ��������
//				(Status_Information->Fly_Control_Power     << ML_FLY_CONTROL_POWER_BIT) |// �ɿع���״̬
//				(Status_Information->RAM_Check    	   	   << ML_RAM_CHECK_BIT)     	|// �ⲿRAM�Լ�״̬
//				(Status_Information->Guide_Check     	   << ML_GUIDE_CHECK_BIT) 		|// �����Լ�״̬
//				(Status_Information->IMU_Check    	       << ML_IMU_CHECK_BIT)     	|// IMU�Լ�״̬
//				(Status_Information->Steering_Check    	   << ML_STEERING_CHECK_BIT)    |// ����Լ�״̬
//				(Status_Information->Fly_Control_Batter    << ML_FLY_CONTROL_BATTER_BIT)|// �ɿص��״̬
//				(Status_Information->Steering_Batter   	   << ML_STEERING_BATTER_BIT)   |// ������״̬
//				(Status_Information->Engine_Fire_Sigle     << ML_ENGINE_FIRE_SIGLE_BIT) |// ����������ź�״̬
//				MISSILE_LAUCH_A429_STATUS;												 // ��ǩ
//
//   *(Uint16*)(0x100004) = (Uint16)((ARINC_Dat>>16)&0xffff);
//   	DELAY_US(ARINC429_Send);
//   *(Uint16*)(0x100005) = (Uint16)(ARINC_Dat&0xffff);
//    DELAY_US(3000);
////    Steering_Send_Byte((ARINC_Dat >> 24 )&0xff);
////    Steering_Send_Byte((ARINC_Dat >> 16 )&0xff);
////    Steering_Send_Byte((ARINC_Dat >> 8 )&0xff);
////    Steering_Send_Byte(ARINC_Dat&0xff);
//}
