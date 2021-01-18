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
header,
Length,
ReceiveData,
CheckSum
}PowerState;
PowerState Power_State = HeadFirst;

//422 Communication
typedef struct PowerData{
	Uint16  len ;
	Uint16  header;
	Uint32  dat[12];
	Uint16  checksum;
}RxData;
RxData Rdat;

//define the zgh Check state
typedef enum {
Voltage_Check = 0,
Steering_SlefCheck,
Steering_Check_Position_one,
Steering_Check_Position_two,
Batter_Check,
Fire,
Idle,
Err
}CheckState;
CheckState Self_check_state = Voltage_Check;


typedef enum {
IMU_HeadFirst = 0,
IMU_HeadSecond,
IMU_ReceiveData,
IMU_CRC_Check
}IMUState;
IMUState IMU_State= IMU_HeadFirst;
//IMU �������ݵĽṹ��
typedef struct IMUData{
	unsigned char  Dat[14];
	unsigned char  CRC16_Check[2];
}IMUData;
IMUData IMU_Buffer;

Uint16 IMU_cnt=0;
Uint16 c_sum;
Uint16 dat_cnt=0;
Uint16 Voltage_Check_Cnt=0,Voltage_Check_Finish=0,Power_cnt=0,Model_Type=0X7F80;
Uint16 Batter_Check_Flag=0,Batter_cnt=0;
volatile Uint16 Time_ms_cnt,Steering_StateFlag,Steering_Check_cnt;

Mis_To_Fly_Sta_Info m_mis_fly_Messege;
Fly_To_Mis_Ctr_Info m_fly_mis_Messege;



void ARINC_Encode(Mis_To_Fly_Sta_Info *Status_Information);


void StateMachine_Init(void)
{
	Uint16 i;
	//power state machine
	Power_State 	= HeadFirst;
	Rdat.header 	= 0;
	Rdat.len    	= 0;
	Rdat.checksum	= 0;
	for(i=0;i<12;i++)
	{
		Rdat.dat[i] = 0;
	}
	c_sum  =0;
	dat_cnt=0;
	Voltage_Check_Cnt    =0;
	Voltage_Check_Finish =0;
	Power_cnt  =0;
	Model_Type =0X7F80;
	Batter_cnt = 0;
	//imu state machine
	IMU_State = IMU_HeadFirst;
	for(i=0;i<14;i++)
	{
		IMU_Buffer.Dat[i] = 0;
	}
	for(i=0;i<2;i++)
	{
		IMU_Buffer.CRC16_Check[i]=0;
	}
	IMU_cnt = 0;

	//selfcheck
	Self_check_state 	= Voltage_Check;
	Time_ms_cnt      	= 0;
	Steering_StateFlag 	= 0;
	Steering_Check_cnt  = 0;
	Batter_Check_Flag	= 0;

	m_mis_fly_Messege.Current_Feedback_Voltage=0;
	m_mis_fly_Messege.DJ_Batter_Voltage=0;
	m_mis_fly_Messege.Fly_Control_Batter=0;
	m_mis_fly_Messege.Fly_Control_Power=0;
	m_mis_fly_Messege.Guide_Check=0;
	m_mis_fly_Messege.IMU_Check=0;
	m_mis_fly_Messege.Missile_Capture=0;
	m_mis_fly_Messege.Missile_Normal=0;
	m_mis_fly_Messege.Missile_Type=0;
	m_mis_fly_Messege.Position_Feedback_Voltage=0;
	m_mis_fly_Messege.RAM_Check=0;
	m_mis_fly_Messege.SYS_12_Voltage=0;
	m_mis_fly_Messege.SYS_5_Voltage=0;
	m_mis_fly_Messege.SYS_Batter_Voltage=0;
	m_mis_fly_Messege.SYS_Negative_5_Voltage=0;
	m_mis_fly_Messege.Seeker_Azimuth=0;
	m_mis_fly_Messege.Seeker_Pitch=0;
	m_mis_fly_Messege.Steering_Batter=0;
	m_mis_fly_Messege.Steering_Check=0;
	m_mis_fly_Messege.Engine_Fire_Sigle=0;

	m_fly_mis_Messege.Missile_Commond=0;
	m_fly_mis_Messege.Missile_Lauch=0;
	m_fly_mis_Messege.Missile_Lock=0;
	m_fly_mis_Messege.Missile_Power=0;
}


Uint16 Fly_Control_Voltage_Check(void)
{
	Uint16 Voltage_val[3];
	Uint16 Status=0;
	Status = 0;
	Voltage_val[0] = (Rdat.dat[2]<<8) | Rdat.dat[3];
	Voltage_val[1] = (Rdat.dat[4]<<8) | Rdat.dat[5];
	Voltage_val[2] = (Rdat.dat[8]<<8) | Rdat.dat[9];

	if(Voltage_val[0]>2400 && Voltage_val[0]<3000)
	{
		Status = 0x07;
	}

	if(Voltage_val[1]>2400 && Voltage_val[1]<3000)
	{
		Status |= 0x18;
	}

	if(Voltage_val[2]>2400 && Voltage_val[2]<3000)
	{
		Status |= 0xE0;
	}

	return Status;
}

//FK -> 24V -> 2736
//DJ -> 24V -> 1458
Uint16 Batter_Voltage_Check(void)
{
	Uint16 Voltage_val[2];
	Uint16 Status=0;
	Status = 0;
	Voltage_val[0] = (Rdat.dat[0]<<8) | Rdat.dat[1];//DJ
	Voltage_val[1] = (Rdat.dat[6]<<8) | Rdat.dat[7];//FK

	if(Voltage_val[0]>1458 && Voltage_val[0]<1800)//1620
	{
		Status |= 0x00ff;
		m_mis_fly_Messege.Steering_Batter=1;
	}
	else
	{
		Status &= 0xff00;
		m_mis_fly_Messege.Steering_Batter=0;
	}

	if(Voltage_val[1]>2736)//3096
	{
		Status |= 0xff00;
		m_mis_fly_Messege.Fly_Control_Batter=1;
	}
	else
	{
		Status &= 0x00ff;
		m_mis_fly_Messege.Fly_Control_Batter=0;
	}
	return Status;
}

void Power_State_Machine(Uint16 Receive_Data)
{
	switch(Power_State)
	{
		case HeadFirst:
			if(Receive_Data == FirstCheckChar)
			{
				Power_State = HeadSecond;
			}
			else
			{
				Power_State = HeadFirst;
			}
		break;

		case HeadSecond:
			if(Receive_Data == SecondCheckChar)
			{
				Power_State = header;
			}
			else
			{
				Power_State = HeadFirst;
			}
			c_sum = 0;
		break;

		case header:
			if(Receive_Data == 0xA5)//c28
			{
				Power_State = Length;
				Rdat.header = Receive_Data;
				c_sum  =(c_sum + Receive_Data);
			}
			else
			{
				Power_State = HeadFirst;
			}

		break;

		case Length:
			Rdat.len = Receive_Data;
			c_sum  =(c_sum + Receive_Data);
			dat_cnt = 0;
			Power_State = ReceiveData;
		break;

		case ReceiveData:
			Rdat.dat[dat_cnt] = Receive_Data;
			c_sum  =(c_sum + Receive_Data);
			dat_cnt++;
			if(dat_cnt >= Rdat.len)
			{
				Power_State = CheckSum;
				dat_cnt = 0;
			}
		break;
		case CheckSum:
			Rdat.checksum = c_sum&0xff;
			Power_State = HeadFirst;
			if(Receive_Data == Rdat.checksum)//���յ�����������ȷ��
			{
				if(Rdat.header == 0xA5)
				{
					if(0xA5A5 == Model_Type)
					{
					   *(Uint16*)(0x100004) = (Uint16)(((Rdat.dat[0]&0x0f)<<12)|((Rdat.dat[1]&0xff)<<4)|(Rdat.dat[6]&0x0f));
					   DELAY_US(ARINC429_Send);
					   *(Uint16*)(0x100005) = (Uint16)(((Rdat.dat[7]&0xff)<<8)|MISSILE_LAUCH_A429_POWER_1);
					   DELAY_US(3000);

					   *(Uint16*)(0x100004) = (Uint16)(((Rdat.dat[2]&0x0f)<<12)|((Rdat.dat[3]&0xff)<<4)|(Rdat.dat[4]&0x0f));
					   DELAY_US(ARINC429_Send);
					   *(Uint16*)(0x100005) = (Uint16)(((Rdat.dat[5]&0xff)<<8)|MISSILE_LAUCH_A429_POWER_2);
					   DELAY_US(3000);

					   *(Uint16*)(0x100004) = (Uint16)(((Rdat.dat[8]&0x0f)<<12)|((Rdat.dat[9]&0xff)<<4));
					   DELAY_US(ARINC429_Send);
					   *(Uint16*)(0x100005) = MISSILE_LAUCH_A429_POWER_3;
					   DELAY_US(3000);

					   *(Uint16*)(0x100004) = (Uint16)((FW<<4)|((FI>>8)&0xf));
					   DELAY_US(ARINC429_Send);
					   *(Uint16*)(0x100005) = (Uint16)(((FI<<8)&0xff00)|MISSILE_LAUCH_A429_POWER_4);
					   DELAY_US(3000);

					}
					else if(0x7F80 == Model_Type) // Fly Control Power Check
					{
						Power_cnt++;
						if(0xff == Fly_Control_Voltage_Check())
						{
							Voltage_Check_Cnt++;
						}
						if(Voltage_Check_Cnt >= 100)
						{
							Voltage_Check_Cnt = 0;
							Voltage_Check_Finish = 0x5AA5;
							Model_Type = 0;
							m_mis_fly_Messege.Fly_Control_Power=1;
							Missle_Normal(1);
						}
						if(Power_cnt >= 200)
						{
							Voltage_Check_Finish = 0;
							Model_Type = 0;
							m_mis_fly_Messege.Fly_Control_Power=0;
							Missle_Normal(0);
						}
					}
					else if(0x1234 == Model_Type)//Batter Voltage Check
					{
						if(0xFFFF == Batter_Voltage_Check())
						{
							Batter_cnt++;
						}
						if(Batter_cnt > 20)
						{
							Model_Type = 0;
							Batter_Check_Flag = 0xABCD;
						}
					   *(Uint16*)(0x100004) = (Uint16)(((Rdat.dat[0]&0x0f)<<12)|((Rdat.dat[1]&0xff)<<4)|(Rdat.dat[6]&0x0f));
					   DELAY_US(ARINC429_Send);
					   *(Uint16*)(0x100005) = (Uint16)(((Rdat.dat[7]&0xff)<<8)|MISSILE_LAUCH_A429_POWER_1);
					   DELAY_US(3000);

					   *(Uint16*)(0x100004) = (Uint16)(((Rdat.dat[2]&0x0f)<<12)|((Rdat.dat[3]&0xff)<<4)|(Rdat.dat[4]&0x0f));
					   DELAY_US(ARINC429_Send);
					   *(Uint16*)(0x100005) = (Uint16)(((Rdat.dat[5]&0xff)<<8)|MISSILE_LAUCH_A429_POWER_2);
					   DELAY_US(3000);

					   *(Uint16*)(0x100004) = (Uint16)(((Rdat.dat[8]&0x0f)<<12)|((Rdat.dat[9]&0xff)<<4));
					   DELAY_US(ARINC429_Send);
					   *(Uint16*)(0x100005) = MISSILE_LAUCH_A429_POWER_3;
					   DELAY_US(3000);

//					   *(Uint16*)(0x100004) = (Uint16)((FW<<4)|((FI>>8)&0xf));
//					   DELAY_US(100);
//					   *(Uint16*)(0x100005) = (Uint16)(((FI<<8)&0xff00)|MISSILE_LAUCH_A429_POWER_4);
//					   DELAY_US(3000);
					}
				}
			}
			else//data receive err
			{

			}
		break;
		default :
			Power_State = HeadFirst;
		break;
	}
}

Uint16 temp1,temp2,j,x_data[14];
void IMU_State_Machine(Uint16 Receive_Data)
{

	switch(IMU_State)
	{
		case IMU_HeadFirst:
			if(Receive_Data == 0x7f)
			{
				IMU_State = IMU_HeadSecond;
			}
			else
			{
				IMU_State = IMU_HeadFirst;
			}
			break;
		case IMU_HeadSecond:
			if(Receive_Data == 0x80)
			{
				IMU_State = IMU_ReceiveData;
				IMU_cnt = 0;
			}
			else
			{
				IMU_State = IMU_HeadFirst;
			}
			break;
		case IMU_ReceiveData:
			IMU_Buffer.Dat[IMU_cnt+2] = Receive_Data;
			IMU_cnt++;
			if(IMU_cnt == 12)
			{
				IMU_cnt = 0;
				IMU_State = IMU_CRC_Check;
			}
			break;
		case IMU_CRC_Check:
			IMU_Buffer.CRC16_Check[IMU_cnt] = Receive_Data;
			IMU_cnt++;
			if(IMU_cnt == 2)
			{
//				temp1 = crc2(IMU_Buffer.Dat,14);
//				temp2 = usMBCRC16(IMU_Buffer.Dat,14);
//				IMU_cnt = 0;
//				Steering_Send_Byte(0xaa);
				IMU_State = IMU_HeadFirst;
			}
			break;
		default:
			IMU_cnt = 0;
			IMU_State = IMU_HeadFirst;
			break;
	}
}


void Self_Check_State_Machine(Uint16 *Tartget_Position,Uint16 Feedback_Position)
{
	switch(Self_check_state)
	{
	case Voltage_Check:
		*Tartget_Position = 500;
		if(0x5AA5 == Voltage_Check_Finish)
		{
			if(m_mis_fly_Messege.Guide_Check && m_mis_fly_Messege.IMU_Check &&
			m_mis_fly_Messege.RAM_Check && m_mis_fly_Messege.Fly_Control_Power)
			{
				Missle_Ready(1);
				m_mis_fly_Messege.Missile_Normal = 1;
				Time_ms_cnt = 0;
				#if Rocket_Bomb
					Self_check_state = Batter_Check;
					Steering_Send_Byte(Batter_Check);
				#else
					Self_check_state = Steering_SlefCheck;
					Steering_Send_Byte(Steering_SlefCheck);
				#endif
				ARINC_Encode(&m_mis_fly_Messege);
				ARINC_Encode(&m_mis_fly_Messege);
				ARINC_Encode(&m_mis_fly_Messege);
			}
			else
			{
				Missle_Ready(0);
				m_mis_fly_Messege.Missile_Normal = 0;
				Self_check_state = Err;
				Steering_Send_Byte(Err);
			}
		}
		break;
	case Steering_SlefCheck:
		*Tartget_Position = 500;
		if(0x5C == m_fly_mis_Messege.Missile_Commond)//Wait for the Steering SelfCheck
		{
			Time_ms_cnt = 0;
			Steering_Check_cnt = 0;
			Self_check_state = Steering_Check_Position_one;
			Steering_Send_Byte(Steering_Check_Position_one);
		}
		break;
	case Steering_Check_Position_one:
		Time_ms_cnt++;
		//200 -> 1022
		*Tartget_Position = 200;
		if(Feedback_Position < 1500)
		{
			Steering_Check_cnt++;
		}
		if(Steering_Check_cnt > 100)
		{
			Time_ms_cnt = 0;
			Steering_Check_cnt=0;
			Self_check_state = Steering_Check_Position_two;
			Steering_Send_Byte(Steering_Check_Position_two);
		}
		if(Time_ms_cnt >= 600)
		{
			m_mis_fly_Messege.Steering_Check = 0;
			Self_check_state = Err;
			Steering_Send_Byte(Err);
		}
		break;
	case Steering_Check_Position_two:
		Time_ms_cnt++;
		// 800 -> 3520
		*Tartget_Position = 800;
		if(Feedback_Position > 3000)
		{
			Steering_Check_cnt++;
		}
		if(Steering_Check_cnt > 100)
		{
			m_mis_fly_Messege.Steering_Check = 1;
			Self_check_state = Batter_Check;//Batter_Check
			Steering_Send_Byte(Batter_Check);
			Time_ms_cnt = 0;
			Steering_Check_cnt = 0;
			ARINC_Encode(&m_mis_fly_Messege);
			ARINC_Encode(&m_mis_fly_Messege);
			ARINC_Encode(&m_mis_fly_Messege);
		}
		if(Time_ms_cnt >= 600)
		{
			m_mis_fly_Messege.Steering_Check = 0;
			Self_check_state = Err;
			Steering_Send_Byte(Err);
		}
		break;
	case Batter_Check:
		*Tartget_Position = 500;
		if((0x5D == m_fly_mis_Messege.Missile_Commond) && (m_fly_mis_Messege.Missile_Lauch))
		{
			Model_Type = 0x1234;
			if(0xABCD == Batter_Check_Flag)
			{
				Time_ms_cnt = 0;
				ARINC_Encode(&m_mis_fly_Messege);
				ARINC_Encode(&m_mis_fly_Messege);
				ARINC_Encode(&m_mis_fly_Messege);
				Self_check_state = Fire;
				Steering_Send_Byte(Fire);
			}
			Time_ms_cnt++;
			if(Time_ms_cnt >= 3000)
			{
				Self_check_state = Err;//�޸�
				Time_ms_cnt = 0;
			}
		}
		break;
	case Fire:
		*Tartget_Position = 500;
		if(Time_ms_cnt >= 200)
		{
			Time_ms_cnt = 200;
		}
		if(Time_ms_cnt > 0 && Time_ms_cnt < 100)
		{
			Fire_Ready_ON();
			Fire_OFF();
		}
		if(Time_ms_cnt >= 100 && Time_ms_cnt < 200)
		{
			Fire_Ready_ON();
			Fire_ON();
			m_mis_fly_Messege.Engine_Fire_Sigle = 1;
			ARINC_Encode(&m_mis_fly_Messege);
			ARINC_Encode(&m_mis_fly_Messege);
			ARINC_Encode(&m_mis_fly_Messege);
		}
		if(Time_ms_cnt >= 200)
		{
			Fire_Ready_OFF();
			Fire_OFF();
			Self_check_state = Idle;
			Steering_Send_Byte(Idle);
			Time_ms_cnt=0;
		}
		Time_ms_cnt++;
		break;
	case Idle:
		Model_Type = 0xA5A5;
		*Tartget_Position = 500;
		break;
	case Err:
		Time_ms_cnt = (Time_ms_cnt + 1)%40;
		if(Time_ms_cnt == 0)
		{
			if(Steering_StateFlag)
			{
				Steering_StateFlag = 0;
			}
			else
			{
				Steering_StateFlag = 1;
			}

			if(Steering_StateFlag)
			{
				*Tartget_Position = 700;
			}
			else
			{
				*Tartget_Position = 300;
			}
		}
		break;
	default:
		Self_check_state = Idle;
		break;
	}
}

void ARINC_Decode(Uint32 Dat,Fly_To_Mis_Ctr_Info *Control_Information)
{
	switch(Dat & 0x00ff)
	{
		case F_LAUCH_MISSILE_A429_CONTROL: // �����֡�������ѯ��
			Control_Information->Missile_Commond        =   (Dat >> LM_COMMOND_BIT) & LM_COMMOND_MASK;
			Control_Information->Missile_Lock			=	(Dat >> LM_LOCK_BIT   ) & LM_LOCK_MASK ;
			Control_Information->Missile_Power			=	(Dat >> LM_POWER_BIT  ) & LM_POWER_MASK;
			Control_Information->Missile_Lauch 			=   (Dat >> LM_LAUCH_BIT  ) & LM_LAUCH_MASK;
		break;
		default:
			Control_Information->Missile_Lauch 				= 0;
			Control_Information->Missile_Lock				= 0;
			Control_Information->Missile_Power				= 0;
			Control_Information->Missile_Commond            = 0;
		break;
	}
}

void ARINC_Encode(Mis_To_Fly_Sta_Info *Status_Information)
{
	Uint32  ARINC_Dat;
	ARINC_Dat = (Status_Information->Missile_Normal  	   << ML_NORMAL_BIT)   			|// �����Ƿ�����
				(Status_Information->Missile_Capture       << ML_CAPTURE_BIT)  			|// �����ػ�
				(Status_Information->Missile_Type    	   << ML_TYPE_BIT)     			|// ��������
				(Status_Information->Fly_Control_Power     << ML_FLY_CONTROL_POWER_BIT) |// �ɿع���״̬
				(Status_Information->RAM_Check    	   	   << ML_RAM_CHECK_BIT)     	|// �ⲿRAM�Լ�״̬
				(Status_Information->Guide_Check     	   << ML_GUIDE_CHECK_BIT) 		|// �����Լ�״̬
				(Status_Information->IMU_Check    	       << ML_IMU_CHECK_BIT)     	|// IMU�Լ�״̬
				(Status_Information->Steering_Check    	   << ML_STEERING_CHECK_BIT)    |// ����Լ�״̬
				(Status_Information->Fly_Control_Batter    << ML_FLY_CONTROL_BATTER_BIT)|// �ɿص��״̬
				(Status_Information->Steering_Batter   	   << ML_STEERING_BATTER_BIT)   |// ������״̬
				(Status_Information->Engine_Fire_Sigle     << ML_ENGINE_FIRE_SIGLE_BIT) |// ����������ź�״̬
				MISSILE_LAUCH_A429_STATUS;												 // ��ǩ

   *(Uint16*)(0x100004) = (Uint16)((ARINC_Dat>>16)&0xffff);
   	DELAY_US(ARINC429_Send);
   *(Uint16*)(0x100005) = (Uint16)(ARINC_Dat&0xffff);
    DELAY_US(3000);
//    Steering_Send_Byte((ARINC_Dat >> 24 )&0xff);
//    Steering_Send_Byte((ARINC_Dat >> 16 )&0xff);
//    Steering_Send_Byte((ARINC_Dat >> 8 )&0xff);
//    Steering_Send_Byte(ARINC_Dat&0xff);
}
