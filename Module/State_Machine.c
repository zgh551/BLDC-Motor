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
Uint16 TelemetrySendFlag;
Uint16 Time5msSendFlag;

void StateMachine_Init(void)
{
    Uint16 i;
	//communication state machine
	Com422_State 	= HeadFirst;
	Rdata.cmd 	    = 0;
	Rdata.len    	= 0;
	Rdata.checksum	= 0;
	for(i = 0; i < 240; i++)
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
	Tdata.data[1] = d2m_Messege.DriverBoardCheck; // 驱动板自检故障码
	Tdata.data[2] = d2m_Messege.MotorCheck;	   // 电机自检故障码
	Tdata.data[3] = d2m_Messege.SoftwareVersion_L;  // 驱动板软件版本号 低
	Tdata.data[4] = d2m_Messege.SoftwareVersion_H;  // 驱动板软件版本号 高
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

void BLDC_CycleSend500ms(void)
{
	Uint16 i = 0, check_sum = 0;
	Uint16 temp_data = 0;
//	int16 temp_data_i16 = 0;
	Tdata.len = 8;
	Tdata.data[0] = DRIVER_BOARD_CYCLE_SEND;
	Tdata.data[1] = d2m_Messege.MotorDriverVoltage * 5 ; // 电机驱动电压
	Tdata.data[2] = d2m_Messege.MotorDriverCurrent * 10; // 电机驱动电流
	temp_data = (Uint16)(d2m_Messege.AngularPosition * 100 * 57.3); // 电机旋转位置
	Tdata.data[3] =  temp_data & 0x00ff; 
	Tdata.data[4] = (temp_data >> 8) & 0x00ff; 

	temp_data =  d2m_Messege.AngularVelocity < 0.0
	          ? -d2m_Messege.AngularVelocity * 100
	          :  d2m_Messege.AngularVelocity * 100; // 电机角速度
	Tdata.data[5] =  temp_data & 0x00ff;
	Tdata.data[6] = (temp_data >> 8) & 0x00ff; // [0 - 54000] deg
	Tdata.data[7] = d2m_Messege.MotorStatus; // 电机状态参数

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

void BLDC_TelemetrySend(void)
{
	Uint16 i = 0, check_sum = 0;
	Uint16 temp_data = 0;
	Tdata.len = 8;
	Tdata.data[0] = TELEMETRY_SEND;
	temp_data = (Uint16)d2m_Messege.MotorTargetPosition * 0.5; // 电机目标位置
	Tdata.data[1] =  temp_data & 0x00ff;  	
	Tdata.data[2] = (temp_data >> 8) & 0x00ff;
	temp_data = (Uint16)d2m_Messege.MotorActualPosition * 0.5; // 电机实际转动位置
	Tdata.data[3] =  temp_data & 0x00ff; 
	Tdata.data[4] = (temp_data >> 8) & 0x00ff; 
	Tdata.data[5] = d2m_Messege.ActualRotationRings; // 本组电机实际旋转圈数
	Tdata.data[6] = d2m_Messege.ThrowStatus;         // 投放状态
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

void BLDC_TreePhaseCurrent(void)
{
    Uint16 i = 0, check_sum = 0;
    Uint16 temp_data = 0;
    Tdata.len = 8;
    Tdata.data[0] = TREE_PHASE_CURRENT;
    temp_data = (Uint16)(d2m_Messege.MotorDriver_IA * 1000); // A相电流
    Tdata.data[1] =  temp_data & 0x00ff;
    Tdata.data[2] = (temp_data >> 8) & 0x00ff;
    temp_data = (Uint16)(d2m_Messege.MotorDriver_IB * 1000); // B相电流
    Tdata.data[3] =  temp_data & 0x00ff;
    Tdata.data[4] = (temp_data >> 8) & 0x00ff;
    temp_data = (Uint16)(d2m_Messege.MotorDriver_IC * 1000); // C相电流
    Tdata.data[5] =  temp_data & 0x00ff;
    Tdata.data[6] = (temp_data >> 8) & 0x00ff;
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
    Uint16 i;
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
					for (i = 0; i < m2d_Messege.MotorRotateCount; i++)
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
