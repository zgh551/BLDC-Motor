/*
 * State_Machine.c
 *
 *  Created on: 2021
 *      Author: ZGH
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "State_Machine.h"

#pragma DATA_SECTION(Rdata, "DMARAML5");
#pragma DATA_SECTION(Tdata, "DMARAML5");
#pragma DATA_SECTION(m2d_Messege, "DMARAML7");
#pragma DATA_SECTION(d2m_Messege, "DMARAML7");

#pragma CODE_SECTION(BLDC_SelfCheck, "ramfuncs");
#pragma CODE_SECTION(CommandResponse, "ramfuncs");

#define FirstCheckChar  0x55
#define SecondCheckChar 0x77

#define TWO_PI_INV      (0.15915494309189533576888376337251)
#define TWO_PI          (6.283185307179586476925286766559)
#define ONE_PI          (3.1415926535897932384626433832795)

#define MAX_VQ          (14.0f)
#define ACC_RESEET      (-600.0f)
#define ACC_DELIVERRY   (4800.0f)

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

typedef enum {
WaitStart = 0,
TotalTurns,
HightReset,
LowReset,
LowResetUniformPhase,
LowResetStop,
WaitLowResetStop,
WaitRun,
Running,
WaitPositionRun,
PositionControl,
AcceleratePhase,
UniformPhase,
DeceleratePhase,
SmallTurnDeceleratePhase,
SmallTurnLastPhase,
DecelerateStopPhase,
WaitTime,
WaitStop
} RotateControlState;
RotateControlState BLDC_RotateState = WaitStart;
static Uint16 deliverry_rotate_turn_cnt = 0, rotate_turn_cnt = 0, last_phase = 0;
//static Uint16 total_turns = 0;

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
Uint16 TimeDQCurrentSendFlag;

Uint16 rx_commond = 0;

static int16 total_sum_rotate_turn_cnt = 0;
static Uint16 TotalTurnCount = 0, CurrentTurnIndex = 0, CurrentTurnCount = 0;
static Uint16 hight_turn_count = 0, lower_turn_count = 0;
static float reset_target_angle_position, reset_total_turn_count;

static float current_angle_rate = 0.0f, current_angle = 0.0f;
static float rote_time_count = 0.0f, wait_time_count = 0.0f;

// 复位相关
static Uint16 reset_current_turn_cnt = 0;
static float high_speed_end_position = 0.0f;

// 投放相关
static float current_turn_count = 0.0f; // 当前投放圈数
static float target_rote_time = 0.0f;   // 该投放阶段所需总的时间
static float current_turn_angle_rate = 0.0f;    // 当前投放的角速度
static float update_current_turn_angle_rate = 0.0f;// 更新角速度

static float max_turn_angle_rate = 0.0f;  // 最大角速度
static float target_wait_time = 0.0f;   // 两段投放间隔时间
static float update_delta_target_position = 0.0f;
static float bound_turn_count = 0.0f; //满足时间的圈数边界值
static float target_turn_count = 0.0f; // 投放的目标圈数
static float total_turn_time = 0.0f; // 投放总时间
static float delta_acc_time = 0.0f; // 加速段时间
static float ahead_stop_distance = 0.0f; // 提前减速度距离

static float origin_init_angle_position = 0, init_angle_position,target_angle_position, total_turn_count_sum;
static float last_angle;

static Uint16 delta_angle_update_flag = 0;

int16 turn_direction_symbol = 0;

//static float temp_angle[100];
//Uint16  temp_angle_count = 0;

static float stage_phase = 0.0f;

void StateMachine_Init(void)
{
    Uint16 i;
	//communication state machine
	Com422_State 	= HeadFirst;
	Rdata.cmd 	    = 0;
	Rdata.len    	= 0;
	Rdata.checksum	= 0;
	for(i = 0; i < 100; i++)
	{
		Rdata.data[i] = 0;
	}
	dat_cnt=0;

	m2d_Messege.Commond = 0;

	m2d_Messege.TargetVd = 0;
	m2d_Messege.TargetVq = 0;

    d2m_Messege.V_d = 0;
    d2m_Messege.V_q = 0;

    d2m_Messege.MotorStatus.bit.revert1 = 0;
    d2m_Messege.MotorStatus.bit.revert2 = 0;

    d2m_Messege.DriverBoardCheck.bit.revert1 = 0;
    d2m_Messege.DriverBoardCheck.bit.revert2 = 0;

    d2m_Messege.MotorCheck.bit.revert1 = 0;
    d2m_Messege.MotorCheck.bit.revert2 = 0;

    d2m_Messege.MotorTargetPosition = 0.0f;
    d2m_Messege.MotorActualPosition = 0.0f;
    for(i = 0; i < 30; i++)
    {
        m2d_Messege.RotateTurns[i]  = 0; // 旋转圈数
        m2d_Messege.RotateTimes[i]  = 0; // 旋转总运行时间
        m2d_Messege.TimeInterval[i] = 0; // 两次的时间间隔
    }

    total_sum_rotate_turn_cnt = 0;
    wait_time_count = 0;
    last_angle = 0;
    delta_angle_update_flag = 0xABCD;
    max_turn_angle_rate = 0.0f;
    update_current_turn_angle_rate = 0.0f;
    CurrentTurnIndex = 0;
}

void BLDC_SelfCheck(void)
{
	Uint16 i = 0, check_sum = 0;

	Tdata.len = 8;
	Tdata.data[0] = SELFCHECK_REACT;
	Tdata.data[1] = d2m_Messege.DriverBoardCheck.all; // 驱动板自检故障码
	Tdata.data[2] = d2m_Messege.MotorCheck.all;	   // 电机自检故障码
	Tdata.data[3] = d2m_Messege.SoftwareVersion_L;  // 驱动板软件版本号 低
	Tdata.data[4] = d2m_Messege.SoftwareVersion_H;  // 驱动板软件版本号 高
	Tdata.data[5] = 0;
	Tdata.data[6] = 0;
	Tdata.data[7] = 0;

	Steering_Send_Byte_B(0x55);
	Steering_Send_Byte_B(0x77);
	Steering_Send_Byte_B(Tdata.len);
	check_sum = Tdata.len;
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
	check_sum = Tdata.len;
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
	check_sum = Tdata.len;
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
	check_sum = Tdata.len;
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
#ifdef TERMINAL_DEBUG
	int16 temp_data_i16 = 0;
#endif

	Tdata.len = 8;
	Tdata.data[0] = DRIVER_BOARD_CYCLE_SEND;
	Tdata.data[1] = d2m_Messege.MotorDriverVoltage * 5 ; // 电机驱动电压
	d2m_Messege.MotorDriverCurrent = d2m_Messege.MotorDriver_IA + d2m_Messege.MotorDriver_IB + d2m_Messege.MotorDriver_IC;
	Tdata.data[2] = d2m_Messege.MotorDriverCurrent * 10; // 电机驱动电流
    #ifdef TERMINAL_DEBUG
	temp_data = (Uint16)(d2m_Messege.MotorActualPosition * 0.5f); // 电机旋转位置 rad
//	temp_data = (Uint16)(d2m_Messege.AngularPosition * 100); // 电机旋转位置 rad
    #else
	temp_data = (Uint16)(d2m_Messege.MotorActualPosition * 0.5f * 57.3f); // 电机旋转位置 deg
    #endif
	Tdata.data[3] =  temp_data & 0x00ff; 
	Tdata.data[4] = (temp_data >> 8) & 0x00ff; 

    #ifdef TERMINAL_DEBUG
	temp_data_i16 = (int16)(d2m_Messege.AngularVelocity * 10);
	Tdata.data[5] =  temp_data_i16 & 0x00ff;
	Tdata.data[6] = (temp_data_i16 >> 8) & 0x00ff; // [-150 - 150] r/s
    #else
	temp_data =  fabsf(d2m_Messege.AngularVelocity) * 57.3;// 电机角速度 [0 - 54000] deg/s
	Tdata.data[5] =  temp_data & 0x00ff;
	Tdata.data[6] = (temp_data >> 8) & 0x00ff; //
    #endif

    #ifdef TERMINAL_DEBUG
	Tdata.data[7] = d2m_Messege.FaultState;
    #else
	d2m_Messege.MotorStatus.bit.MotorDirection = d2m_Messege.AngularVelocity > 1.0e-2f ? 1 : d2m_Messege.AngularVelocity < -1.0e-2f ? 2 : 0;
	Tdata.data[7] = d2m_Messege.MotorStatus.all; // 电机状态参数
    #endif

	Steering_Send_Byte_B(0x55);
	Steering_Send_Byte_B(0x77);
	Steering_Send_Byte_B(Tdata.len);
	check_sum = Tdata.len;
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

	temp_data = (Uint16)d2m_Messege.MotorTargetPosition * 0.5 * 57.3; // 电机目标位置
	Tdata.data[1] =  temp_data & 0x00ff;  	
	Tdata.data[2] = (temp_data >> 8) & 0x00ff;

	temp_data = (Uint16)d2m_Messege.MotorActualPosition * 0.5 * 57.3; // 电机实际转动位置
	Tdata.data[3] =  temp_data & 0x00ff; 
	Tdata.data[4] = (temp_data >> 8) & 0x00ff; 

	d2m_Messege.TargetRotationRings = (Uint16)(d2m_Messege.MotorTargetPosition/TWO_PI);
	d2m_Messege.ActualRotationRings = (Uint16)(d2m_Messege.MotorActualPosition/TWO_PI);
	Tdata.data[5] = d2m_Messege.TargetRotationRings; // 目标
	Tdata.data[6] = d2m_Messege.ActualRotationRings; // 本组电机实际旋转圈数

	if(d2m_Messege.TargetRotationRings == d2m_Messege.ActualRotationRings)
	{
	    Tdata.data[7] = 0xBB;//d2m_Messege.ThrowStatus;         // 投放状态
	}
	else
	{
	    Tdata.data[7] = 0xCC;
	}

	Steering_Send_Byte_B(0x55);
	Steering_Send_Byte_B(0x77);
	Steering_Send_Byte_B(Tdata.len);
	check_sum = Tdata.len;
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
    int16 temp_data = 0;
    Tdata.len = 8;
    Tdata.data[0] = TREE_PHASE_CURRENT;
    temp_data = (int16)(d2m_Messege.MotorDriver_IA * 1000); // A相电流
    Tdata.data[1] =  temp_data & 0x00ff;
    Tdata.data[2] = (temp_data >> 8) & 0x00ff;
    temp_data = (int16)(d2m_Messege.MotorDriver_IB * 1000); // B相电流
    Tdata.data[3] =  temp_data & 0x00ff;
    Tdata.data[4] = (temp_data >> 8) & 0x00ff;
    temp_data = (int16)(d2m_Messege.MotorDriver_IC * 1000); // C相电流
    Tdata.data[5] =  temp_data & 0x00ff;
    Tdata.data[6] = (temp_data >> 8) & 0x00ff;
    Tdata.data[7] = d2m_Messege.FaultState & 0x00ff;

    Steering_Send_Byte_B(0x55);
    Steering_Send_Byte_B(0x77);
    Steering_Send_Byte_B(Tdata.len);
    check_sum = Tdata.len;
    for (i = 0; i < Tdata.len; i++)
    {
        check_sum += Tdata.data[i];
        Steering_Send_Byte_B(Tdata.data[i]);
    }
    Steering_Send_Byte_B(check_sum & 0x00ff);
}

void BLDC_TreePhaseCurrentTest(float a, float b, float c)
{
    Uint16 i = 0, check_sum = 0;
    int16 temp_data = 0;
    Tdata.len = 8;
    Tdata.data[0] = TREE_PHASE_CURRENT;
    temp_data = (int16)(a * 1000); // A相电流
    Tdata.data[1] =  temp_data & 0x00ff;
    Tdata.data[2] = (temp_data >> 8) & 0x00ff;
    temp_data = (int16)(b * 1000); // B相电流
    Tdata.data[3] =  temp_data & 0x00ff;
    Tdata.data[4] = (temp_data >> 8) & 0x00ff;
    temp_data = (int16)(c * 1000); // C相电流
    Tdata.data[5] =  temp_data & 0x00ff;
    Tdata.data[6] = (temp_data >> 8) & 0x00ff;
    Tdata.data[7] = d2m_Messege.FaultState & 0x00ff;

    Steering_Send_Byte_B(0x55);
    Steering_Send_Byte_B(0x77);
    Steering_Send_Byte_B(Tdata.len);
    check_sum = Tdata.len;
    for (i = 0; i < Tdata.len; i++)
    {
        check_sum += Tdata.data[i];
        Steering_Send_Byte_B(Tdata.data[i]);
    }
    Steering_Send_Byte_B(check_sum & 0x00ff);
}

void BLDC_FeedbackCurrent(void)
{
    Uint16 i = 0, check_sum = 0;
    int16 temp_data = 0;
    Tdata.len = 8;
    Tdata.data[0] = FEEDBACK_CURRENT;
    temp_data = (int16)(d2m_Messege.I_d * 1000); // D电流
    Tdata.data[1] =  temp_data       & 0x00ff;
    Tdata.data[2] = (temp_data >> 8) & 0x00ff;
    temp_data = (int16)(d2m_Messege.I_q * 1000); // Q电流
//    temp_data = (int16)(m2d_Messege.TargetVq * 1000); // Q电流

    Tdata.data[3] =  temp_data       & 0x00ff;
    Tdata.data[4] = (temp_data >> 8) & 0x00ff;

    Tdata.data[5] = 0;
    Tdata.data[6] = 0;
    Tdata.data[7] = 0;

    Steering_Send_Byte_B(0x55);
    Steering_Send_Byte_B(0x77);
    Steering_Send_Byte_B(Tdata.len);
    check_sum = Tdata.len;
    for (i = 0; i < Tdata.len; i++)
    {
        check_sum += Tdata.data[i];
        Steering_Send_Byte_B(Tdata.data[i]);
    }
    Steering_Send_Byte_B(check_sum & 0x00ff);
}


void BLDC_FeedbackCurrentTest(float d, float q)
{
    Uint16 i = 0, check_sum = 0;
    int16 temp_data = 0;
    Tdata.len = 8;
    Tdata.data[0] = FEEDBACK_CURRENT;
    temp_data = (int16)(d * 1000); // D电流
    Tdata.data[1] =  temp_data       & 0x00ff;
    Tdata.data[2] = (temp_data >> 8) & 0x00ff;
    temp_data = (int16)(q * 1000); // Q电流
    Tdata.data[3] =  temp_data       & 0x00ff;
    Tdata.data[4] = (temp_data >> 8) & 0x00ff;

    Tdata.data[5] = 0;
    Tdata.data[6] = 0;
    Tdata.data[7] = 0;

    Steering_Send_Byte_B(0x55);
    Steering_Send_Byte_B(0x77);
    Steering_Send_Byte_B(Tdata.len);
    check_sum = Tdata.len;
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
			Rdata.checksum = Receive_Data;
			Com422_State   = Commond;
		break;

		case Commond:
			dat_cnt         = 1;
			Rdata.data[0]   = Receive_Data;
			Rdata.cmd       = Receive_Data;
			Rdata.checksum += Receive_Data;
			Com422_State    = ReceiveData;
		break;

		case ReceiveData:
            Rdata.data[dat_cnt] = Receive_Data;
            Rdata.checksum     += Receive_Data;
            dat_cnt++;
            if(dat_cnt >= Rdata.len)
            {
                Com422_State = CheckSum;
            }
		break;

		case CheckSum:
			Rdata.checksum = Rdata.checksum & 0x00ff;
			if(Receive_Data == Rdata.checksum)//check sum
			{
				if(SELFCHECK == Rdata.cmd) // self check
				{
					m2d_Messege.Commond = Rdata.data[0];
				}
				else if(DELIVERRY == Rdata.cmd) // 投放
				{
					m2d_Messege.Commond                 = Rdata.data[0];
					m2d_Messege.DeliveryStrategyNumber  = Rdata.data[1]; // 投放策略编号
					m2d_Messege.MotorRotateCount        = Rdata.data[2]; // 电机旋转次数
					for (i = 0; i < m2d_Messege.MotorRotateCount; i++)
					{
						m2d_Messege.RotateTurns[i]  = Rdata.data[3 + 3 * i]; // 旋转圈数
						m2d_Messege.RotateTimes[i]  = Rdata.data[4 + 3 * i]; // 旋转总运行时间
						m2d_Messege.TimeInterval[i] = Rdata.data[5 + 3 * i]; // 两次的时间间隔
					}
				}
				else if(RESET == Rdata.cmd) //Reset
				{
					m2d_Messege.Commond = Rdata.data[0];
					m2d_Messege.HighSpeedReverseNumber = Rdata.data[1]; // 高速反转圈数
					m2d_Messege.LowSpeedReverseNumber  = Rdata.data[2]; // 低速反转圈数
				}
				else if(APROXMT_ZERO == Rdata.cmd) //近似零位
				{
					m2d_Messege.Commond = Rdata.data[0];
				}
                else if(TARGET_DQ == Rdata.cmd) //目标DQ值
                {
                    m2d_Messege.Commond = Rdata.data[0];
                    m2d_Messege.TargetVd = ((int16)((Rdata.data[2] << 8) | Rdata.data[1])) * 0.01f; //D
                    m2d_Messege.TargetVq = ((int16)((Rdata.data[4] << 8) | Rdata.data[3])) * 0.01f; //Q
                }
                else if (TARGET_SPEED == Rdata.cmd) // 目标速度和目标角度
                {
                    m2d_Messege.TargetAngleVelocity = ((int16)((Rdata.data[2] << 8) | Rdata.data[1])) * 0.01f; // 目标角速度
                    m2d_Messege.TargetPosition      = ((int16)((Rdata.data[4] << 8) | Rdata.data[3])) * 0.01f; // 目标位置
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

		default:
			Com422_State = HeadFirst;
		break;
	}
}

void BLDC_RotateTurnControl(Uint16 phase)
{
    switch(BLDC_RotateState)
    {
        case WaitStart:
            if (m2d_Messege.Commond == DELIVERRY)
            {
                BLDC_Start();
                rotate_turn_cnt = 0;
                m2d_Messege.Commond = 0;
                BLDC_RotateState = Running;
            }
            else if (m2d_Messege.Commond == RESET)
            {
                BLDC_Start();
                rotate_turn_cnt = 0;
                m2d_Messege.Commond = 0;
                d2m_Messege.V_q = 4;
                BLDC_RotateState = HightReset;
            }
            else
            {
                BLDC_Stop();
            }
            break;

        case Running:
            if (rotate_turn_cnt >= m2d_Messege.RotateTurns[0])
            {
                d2m_Messege.V_q = 0;
                BLDC_RotateState = WaitStop;
            }
            else
            {
                if((last_phase != phase) && (phase == 1))
                {
                    rotate_turn_cnt++;
                }
                d2m_Messege.V_q = 5;
            }
            break;

        case HightReset:
            if (rotate_turn_cnt >= m2d_Messege.HighSpeedReverseNumber)
            {
                rotate_turn_cnt = 0;
                BLDC_RotateState = LowReset;
            }
            else
            {
                if((last_phase != phase) && (phase == 1))
                {
                    rotate_turn_cnt++;
                    if(d2m_Messege.V_q > 8.0f)
                    {
                        d2m_Messege.V_q = 8.0f;
                    }
                    else
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 0.5f;
                    }
                }
            }
            break;

        case LowReset:
            if (rotate_turn_cnt >= m2d_Messege.LowSpeedReverseNumber)
            {
                d2m_Messege.V_q = 0;
                BLDC_RotateState = WaitStop;
            }
            else
            {
                if((last_phase != phase) && (phase == 1))
                {
                    rotate_turn_cnt++;
                }
                d2m_Messege.V_q = 4;
            }
            break;

        case WaitStop:
            BLDC_Stop();
            BLDC_RotateState = WaitStart;
            break;

        default:

            break;
    }
    last_phase = phase;
}

//基于圈数
void BLDC_RotateTurnControlPro(Uint16 phase)
{
    int16 i;
    switch(BLDC_RotateState)
    {
        case WaitStart:
            if (m2d_Messege.Commond == DELIVERRY)
            {
                TotalTurnCount      = m2d_Messege.MotorRotateCount;
                init_angle_position = d2m_Messege.AngularPosition;
                CurrentTurnIndex = 0;
                total_sum_rotate_turn_cnt = 0;
                turn_direction_symbol = 1;
                m2d_Messege.Commond = 0;
                d2m_Messege.MotorStatus.bit.WorkStatus = 1;
                d2m_Messege.MotorTargetPosition = 0.0f;
                for (i = 0; i < TotalTurnCount; i++)
                {
                    d2m_Messege.MotorTargetPosition += m2d_Messege.RotateTurns[i] * 1.875f * 360.0f;
                }
                BLDC_RotateState = TotalTurns;
            }
            else if (m2d_Messege.Commond == RESET)
            {
                BLDC_Start();
                total_sum_rotate_turn_cnt = 0;
                turn_direction_symbol = -1;
                m2d_Messege.Commond = 0;
                d2m_Messege.V_q = -5.0f;
                init_angle_position = d2m_Messege.AngularPosition;
                hight_turn_count = floorf(m2d_Messege.HighSpeedReverseNumber * 1.875f);
                reset_target_angle_position = modff((m2d_Messege.LowSpeedReverseNumber + m2d_Messege.HighSpeedReverseNumber) * 1.875f
                                                   + (1.0f - init_angle_position * TWO_PI_INV), &reset_total_turn_count) * TWO_PI;

                reset_target_angle_position = TWO_PI - reset_target_angle_position;
                lower_turn_count = (Uint16)reset_total_turn_count;

                d2m_Messege.MotorTargetPosition = (m2d_Messege.LowSpeedReverseNumber + m2d_Messege.HighSpeedReverseNumber) * 1.875f * 360.0f;

                BLDC_RotateState = HightReset;
            }
            else
            {
                d2m_Messege.MotorStatus.bit.WorkStatus = 0;
                BLDC_Stop();
            }
            break;

        case TotalTurns:
            if (CurrentTurnIndex < TotalTurnCount)
            {
//                target_rote_time   = m2d_Messege.RotateTimes [CurrentTurnIndex] * 0.01; // 旋转总运行时间(s)
                target_wait_time   = m2d_Messege.TimeInterval[CurrentTurnIndex] * 0.05; // 两次的时间间隔 (s)
//                CurrentTurnCount   = m2d_Messege.RotateTurns [CurrentTurnIndex];// r/s 旋转圈数/s
                current_turn_count = m2d_Messege.RotateTurns[CurrentTurnIndex] * 1.875f;// r/s 旋转圈数/s
                target_angle_position = modff(current_turn_count + init_angle_position * TWO_PI_INV, &total_turn_count_sum) * TWO_PI;
                CurrentTurnCount = (Uint16)total_turn_count_sum;
                rotate_turn_cnt    = 0;
                d2m_Messege.V_d    = 0;
                d2m_Messege.V_q    = 5.0;
                BLDC_Start();
                BLDC_RotateState   = AcceleratePhase;//Running;
            }
            else
            {
                BLDC_RotateState = WaitStop;
            }
            break;

        case AcceleratePhase:
            if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
            {
                rotate_turn_cnt++;
                total_sum_rotate_turn_cnt++;
                if ((CurrentTurnCount - rotate_turn_cnt) <= 4)
                {
                    if (1 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 2.0f;
                        BLDC_RotateState = DeceleratePhase;
                    }
                    else if (2 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 2.0f;
                        BLDC_RotateState = SmallTurnDeceleratePhase;
                    }
                    else
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 2.0f;
                        BLDC_RotateState = SmallTurnDeceleratePhase;
                    }
                }
                else
                {
                    if(d2m_Messege.V_q > MAX_VQ)
                    {
                        d2m_Messege.V_q = MAX_VQ;
                        BLDC_RotateState = UniformPhase;
                    }
                    else
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 1.0f;
                    }
                }
            }
            break;

        case SmallTurnDeceleratePhase:
            if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
            {
                rotate_turn_cnt++;
                total_sum_rotate_turn_cnt++;
                if (rotate_turn_cnt >= CurrentTurnCount)
                {
                    BLDC_RotateState = DeceleratePhase;
                }
                else
                {
                    if (CurrentTurnCount == 7) // 4
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 3.5f;
                    }
                    else if (CurrentTurnCount == 6) // 3
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 2.0f;
                    }
                    else if (CurrentTurnCount == 5) // 3
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 1.0f;
                    }
                    else if (CurrentTurnCount == 4)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 3.0f;
                    }
                    else if (CurrentTurnCount == 3) // 2
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 4.5f;
                    }
                    else if (CurrentTurnCount == 2)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 4.0f;
                    }
                }
            }
            break;

        case UniformPhase:
            if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
            {
                rotate_turn_cnt++;
                total_sum_rotate_turn_cnt++;
                if (rotate_turn_cnt >= CurrentTurnCount)
                {
                    d2m_Messege.V_q = 0.0f;
                    BLDC_RotateState = DeceleratePhase;
                }
                else
                {
                    if ((CurrentTurnCount - rotate_turn_cnt) <= 4)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 2.0f;
                    }
                    else
                    {
                        d2m_Messege.V_q = MAX_VQ;
                    }
                }
            }
            break;

        case DeceleratePhase:
            if (d2m_Messege.AngularPosition > target_angle_position)
            {
                d2m_Messege.V_q = 0.0f;
                BLDC_RotateState = DecelerateStopPhase;
            }
            else
            {
                if (d2m_Messege.AngularVelocity < 1.0e-3f)
                {
                    d2m_Messege.V_q =  0.0f;
                    BLDC_RotateState = DecelerateStopPhase;
                }
                else
                {
//                    d2m_Messege.V_q =  0.0f;
                    stage_phase = fmodf(TWO_PI + d2m_Messege.AngularPosition - target_angle_position, 1.02f);
                    if (stage_phase > 5.0f)
                    {
                        d2m_Messege.V_q =  0.0f;
                    }
                    else if(stage_phase > 4.0f)
                    {
                        d2m_Messege.V_q =  0.5f;
                    }
                    else if(stage_phase > 3.0f)
                    {
                        d2m_Messege.V_q =  1.0f;
                    }
                    else
                    {
                        d2m_Messege.V_q =  2.0f;
                    }
                }
            }
            if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
            {
                rotate_turn_cnt++;
                total_sum_rotate_turn_cnt++;
                d2m_Messege.V_q = 0.0f;
                BLDC_RotateState = DecelerateStopPhase;
            }
            break;

        case DecelerateStopPhase:
            if (d2m_Messege.AngularVelocity > 2.0f)
            {
                d2m_Messege.V_d = 0;
                d2m_Messege.V_q = -1.0f;
            }
            else
            {
                d2m_Messege.V_d = 0;
                d2m_Messege.V_q = 0;
                if (d2m_Messege.AngularVelocity < 1.0e-3f)
                {
                    CurrentTurnIndex++;
                    wait_time_count = 0;
                    TelemetrySendFlag = 0xAABB;
                    if(CurrentTurnIndex >= TotalTurnCount)
                    {
                        BLDC_RotateState = WaitStop;
                    }
                    else
                    {
                        BLDC_RotateState = WaitTime;
                    }

                }
            }
            if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
            {
                rotate_turn_cnt++;
                total_sum_rotate_turn_cnt++;
            }
            break;

        case WaitTime:
            if (wait_time_count > target_wait_time)
            {
                BLDC_RotateState = TotalTurns;
            }
            else
            {
                wait_time_count += 0.0001f;
            }
            break;

        case HightReset:
            if (total_sum_rotate_turn_cnt >= hight_turn_count)
            {
                BLDC_RotateState = LowReset;
            }
            else
            {
                if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
                {
                    total_sum_rotate_turn_cnt++;
                    if(d2m_Messege.V_q < -(MAX_VQ - 1.0e-6f))
                    {
                        d2m_Messege.V_q = -MAX_VQ;
                    }
                    else
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 1.0f;
                    }
                }
            }
            break;

        case LowReset:
            if (total_sum_rotate_turn_cnt >= lower_turn_count)
            {
                BLDC_RotateState = LowResetStop;
            }
            else
            {
                if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
                {
                    total_sum_rotate_turn_cnt++;
                    if(d2m_Messege.V_q > -(4.0f + 1.0e-6f))
                    {
                        d2m_Messege.V_q = -4.0f;
                        BLDC_RotateState = LowResetUniformPhase;
                    }
                    else
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 1.0f;
                    }
                }
            }
            break;

        case LowResetUniformPhase:
            if (total_sum_rotate_turn_cnt >= lower_turn_count)
            {
                BLDC_RotateState = LowResetStop;
            }
            else
            {
                if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
                {
                    total_sum_rotate_turn_cnt++;
                    d2m_Messege.V_q = -4.0f;
                }
            }
            break;

        case LowResetStop:
            if (d2m_Messege.AngularPosition < reset_target_angle_position)  // before 30 deg
            {
                d2m_Messege.V_q = 0.0f;
                BLDC_RotateState = WaitLowResetStop;
            }
            else
            {
                stage_phase = fmodf(TWO_PI + d2m_Messege.AngularPosition - reset_target_angle_position, 1.02f);
                if (stage_phase < 2.0f)
                {
                    d2m_Messege.V_q =  -2.5f;
                }
                else
                {
                    d2m_Messege.V_q =  -3.5f;
                }
            }
            if (d2m_Messege.AngularVelocity > -0.1f)
            {
                d2m_Messege.V_d = 0;
                d2m_Messege.V_q = 0;
                TelemetrySendFlag = 0xAABB;
                BLDC_RotateState = WaitStop;
            }
            if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
            {
                total_sum_rotate_turn_cnt++;
            }
            break;

        case WaitLowResetStop:
            if ((d2m_Messege.AngularVelocity < -1.0f)  && (d2m_Messege.AngularPosition > reset_target_angle_position))
            {
                d2m_Messege.V_d =  0;
                d2m_Messege.V_q =  1;
            }
            else
            {
                d2m_Messege.V_d = 0;
                d2m_Messege.V_q = 0;
                TelemetrySendFlag = 0xAABB;
                BLDC_RotateState = WaitStop;
            }
            if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
            {
                total_sum_rotate_turn_cnt++;
            }
            break;

        case WaitStop:
            BLDC_Stop();
            BLDC_RotateState = WaitStart;
            break;

        default:

            break;
    }
    d2m_Messege.MotorActualPosition = (total_sum_rotate_turn_cnt * TWO_PI + turn_direction_symbol * (d2m_Messege.AngularPosition - init_angle_position)) * 57.3f;
    last_angle = d2m_Messege.AngularPosition;
}

//基于圈数
void BLDC_RotateTurnControlProMax(Uint16 phase)
{
    int16 i;
    switch(BLDC_RotateState)
    {
        case WaitStart:
            if (m2d_Messege.Commond == DELIVERRY)
            {
                TotalTurnCount      = m2d_Messege.MotorRotateCount;
                origin_init_angle_position = d2m_Messege.AngularPosition;
                CurrentTurnIndex = 0;
                total_sum_rotate_turn_cnt = 0;
                turn_direction_symbol = 1;
                m2d_Messege.Commond = 0;
                d2m_Messege.MotorStatus.bit.WorkStatus = 1;
                d2m_Messege.MotorTargetPosition = 0.0f;
                for (i = 0; i < TotalTurnCount; i++)
                {
                    d2m_Messege.MotorTargetPosition += m2d_Messege.RotateTurns[i] * 1.875f * 360.0f;
                }
                BLDC_RotateState = TotalTurns;
            }
            else if (m2d_Messege.Commond == RESET)
            {
                BLDC_Start();
                total_sum_rotate_turn_cnt = 0;
                turn_direction_symbol = -1;
                m2d_Messege.Commond = 0;
                d2m_Messege.V_q = -5.0f;
                origin_init_angle_position = d2m_Messege.AngularPosition;
                hight_turn_count = floorf(m2d_Messege.HighSpeedReverseNumber * 1.875f);
                reset_target_angle_position = modff((m2d_Messege.LowSpeedReverseNumber + m2d_Messege.HighSpeedReverseNumber) * 1.875f
                                                   + (1.0f - origin_init_angle_position * TWO_PI_INV), &reset_total_turn_count) * TWO_PI;

                reset_target_angle_position = TWO_PI - reset_target_angle_position;
                lower_turn_count = (Uint16)reset_total_turn_count;

                d2m_Messege.MotorTargetPosition = (m2d_Messege.LowSpeedReverseNumber + m2d_Messege.HighSpeedReverseNumber) * 1.875f * 360.0f;

                BLDC_RotateState = HightReset;
            }
            else
            {
                d2m_Messege.MotorStatus.bit.WorkStatus = 0;
                BLDC_Stop();
            }
            break;

        case TotalTurns:
            if (CurrentTurnIndex < TotalTurnCount)
            {
//                target_rote_time   = m2d_Messege.RotateTimes [CurrentTurnIndex] * 0.01; // 旋转总运行时间(s)
                target_wait_time   = m2d_Messege.TimeInterval[CurrentTurnIndex] * 0.05; // 两次的时间间隔 (s)
//                CurrentTurnCount   = m2d_Messege.RotateTurns [CurrentTurnIndex];// r/s 旋转圈数/s
                current_turn_count = m2d_Messege.RotateTurns[CurrentTurnIndex] * 1.875f;// r/s 旋转圈数/s
                init_angle_position = d2m_Messege.AngularPosition;
                target_angle_position = modff(current_turn_count + init_angle_position * TWO_PI_INV, &total_turn_count_sum) * TWO_PI;
                CurrentTurnCount = (Uint16)total_turn_count_sum;
                rotate_turn_cnt    = 0;
                d2m_Messege.V_d    = 0;
                d2m_Messege.V_q    = 6.0;//5
                BLDC_Start();
                BLDC_RotateState   = AcceleratePhase;//Running;
            }
            else
            {
                BLDC_RotateState = WaitStop;
            }
            break;

        case AcceleratePhase:
            if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
            {
                rotate_turn_cnt++;
                total_sum_rotate_turn_cnt++;
                if ((CurrentTurnCount - rotate_turn_cnt) <= 4)
                {
                    if (1 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 4.0f;
                        BLDC_RotateState = DeceleratePhase;
                    }
                    else if (2 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 1.0f;
                        BLDC_RotateState = SmallTurnDeceleratePhase;
                    }
                    else if (3 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 4.5f;
                        BLDC_RotateState = SmallTurnDeceleratePhase;
                    }
                    else if (5 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 3.5f;
                        BLDC_RotateState = SmallTurnDeceleratePhase;
                    }
                    else if (8 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 2.0f;
                        BLDC_RotateState = SmallTurnDeceleratePhase;
                    }
                    else if (9 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 3.5f;
                        BLDC_RotateState = SmallTurnDeceleratePhase;
                    }
                    else
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 2.0f;
                        BLDC_RotateState = SmallTurnDeceleratePhase;
                    }
                }
                else
                {
                    if(d2m_Messege.V_q > (MAX_VQ - 1.0e-6f))
                    {
                        d2m_Messege.V_q = MAX_VQ;
                        BLDC_RotateState = UniformPhase;
                    }
                    else
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 2.0f;
                    }
                }
            }
            break;

        case SmallTurnDeceleratePhase:
            if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
            {
                rotate_turn_cnt++;
                total_sum_rotate_turn_cnt++;
                if (rotate_turn_cnt >= CurrentTurnCount)
                {
                    if (CurrentTurnCount == 2)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 2.0f;
                    }
                    BLDC_RotateState = DeceleratePhase;
                }
                else
                {
                    if (CurrentTurnCount == 9) // 5
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 2.5f;
                    }
                    else if (CurrentTurnCount == 8) // 4
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 2.3f;
                    }
                    else if (CurrentTurnCount == 7) // 4
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 2.0f;
                    }
                    else if (CurrentTurnCount == 6) // 3
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 1.75f;
                    }
                    else if (CurrentTurnCount == 5) // 3
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 0.75f;
                    }
                    else if (CurrentTurnCount == 4) // 2
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 1.5f;
                    }
                    else if (CurrentTurnCount == 3) // 2
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 3.5f;
                    }
                    else if (CurrentTurnCount == 2)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 2.0f;
                    }
                    else
                    {

                    }
                }
            }
            break;

        case UniformPhase:
            if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
            {
                rotate_turn_cnt++;
                total_sum_rotate_turn_cnt++;
                if (rotate_turn_cnt >= CurrentTurnCount)
                {
                    d2m_Messege.V_q = 5.5f;
                    BLDC_RotateState = DeceleratePhase;
                }
                else
                {
                    if (CurrentTurnCount >= 20)
                    {
                        if ((CurrentTurnCount - rotate_turn_cnt) <= 5)
                        {
                            d2m_Messege.V_q = d2m_Messege.V_q - 2.25f;
                        }
                        else
                        {
                            d2m_Messege.V_q = MAX_VQ;
                        }
                    }
                    else
                    {
                        if ((CurrentTurnCount - rotate_turn_cnt) <= 4)
                        {
                            d2m_Messege.V_q = d2m_Messege.V_q - 3.0f;
                        }
                        else
                        {
                            d2m_Messege.V_q = MAX_VQ;
                        }
                    }

                }
            }
            break;

        case DeceleratePhase:
            if (d2m_Messege.AngularPosition > target_angle_position)
            {
                d2m_Messege.V_q = 0.0f;
                BLDC_RotateState = DecelerateStopPhase;
            }
            else
            {
                if (d2m_Messege.AngularVelocity < 1.0e-3f)
                {
                    d2m_Messege.V_q =  0.0f;
                    BLDC_RotateState = DecelerateStopPhase;
                }
                else
                {
//                    d2m_Messege.V_q =  0.0f;
                    stage_phase = fmodf(TWO_PI + d2m_Messege.AngularPosition - target_angle_position, 1.02f);
//                    if (CurrentTurnCount >= 20)
//                    {
//                        if (stage_phase > 5.0f)
//                        {
//                            d2m_Messege.V_q =  5.5f;
//                        }
//                        else if(stage_phase > 4.0f)
//                        {
//                            d2m_Messege.V_q =  5.5f;
//                        }
//                        else if(stage_phase > 3.0f)
//                        {
//                            d2m_Messege.V_q =  4.0f;
//                        }
//                        else
//                        {
//                            d2m_Messege.V_q =  3.0f;
//                        }
//                    }
//                    else
                    {
                        if (stage_phase > 5.0f)
                        {
                            d2m_Messege.V_q =  5.5f;
                        }
                        else if(stage_phase > 4.0f)
                        {
                            d2m_Messege.V_q =  5.5f;
                        }
                        else if(stage_phase > 3.0f)
                        {
                            d2m_Messege.V_q =  4.0f;
                        }
                        else
                        {
                            d2m_Messege.V_q =  3.0f;
                        }
                    }
//                    if (stage_phase > 5.0f)
//                    {
//                        d2m_Messege.V_q =  4.0f;
//                    }
//                    else if(stage_phase > 4.0f)
//                    {
//                        d2m_Messege.V_q =  3.5f;
//                    }
//                    else if(stage_phase > 3.0f)
//                    {
//                        d2m_Messege.V_q =  3.0f;
//                    }
//                    else
//                    {
//                        d2m_Messege.V_q =  2.0f;
//                    }
                }
            }
            if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
            {
                rotate_turn_cnt++;
                total_sum_rotate_turn_cnt++;
                d2m_Messege.V_q = 0.0f;
                BLDC_RotateState = DecelerateStopPhase;
            }
            break;

        case DecelerateStopPhase:
            if (d2m_Messege.AngularVelocity > 2.0f)
            {
                d2m_Messege.V_d = 0;
                d2m_Messege.V_q = 0.0f;
            }
            else
            {
                d2m_Messege.V_d = 0;
                d2m_Messege.V_q = 0;
                if (d2m_Messege.AngularVelocity < 1.0e-3f)
                {
                    CurrentTurnIndex++;
                    wait_time_count = 0;
                    TelemetrySendFlag = 0xAABB;
                    if(CurrentTurnIndex >= TotalTurnCount)
                    {
                        BLDC_RotateState = WaitStop;
                    }
                    else
                    {
                        BLDC_RotateState = WaitTime;
                    }
                }
            }
            if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
            {
                rotate_turn_cnt++;
                total_sum_rotate_turn_cnt++;
            }
            break;

        case WaitTime:
            if (wait_time_count > target_wait_time)
            {
                BLDC_RotateState = TotalTurns;
            }
            else
            {
                BLDC_Stop();
                wait_time_count += 0.0001f;
            }
            break;

        case HightReset:
            if (total_sum_rotate_turn_cnt >= hight_turn_count)
            {
                BLDC_RotateState = LowReset;
            }
            else
            {
                if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
                {
                    total_sum_rotate_turn_cnt++;
                    if(d2m_Messege.V_q < -(MAX_VQ - 1.0e-6f))
                    {
                        d2m_Messege.V_q = -MAX_VQ;
                    }
                    else
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 2.0f;
                    }
                }
            }
            break;

        case LowReset:
            if (total_sum_rotate_turn_cnt >= lower_turn_count)
            {
                BLDC_RotateState = LowResetStop;
            }
            else
            {
                if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
                {
                    total_sum_rotate_turn_cnt++;
                    if(d2m_Messege.V_q > -(5.0f + 1.0e-6f))
                    {
                        d2m_Messege.V_q = -5.0f;
                        BLDC_RotateState = LowResetUniformPhase;
                    }
                    else
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 2.0f;
                    }
                }
            }
            break;

        case LowResetUniformPhase:
            if (total_sum_rotate_turn_cnt >= lower_turn_count)
            {
                BLDC_RotateState = LowResetStop;
            }
            else
            {
                if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
                {
                    total_sum_rotate_turn_cnt++;
                    d2m_Messege.V_q = -5.0f;
                }
            }
            break;

        case LowResetStop:
            if (d2m_Messege.AngularPosition < reset_target_angle_position)  // before 30 deg
            {
                d2m_Messege.V_q = 0.0f;
                BLDC_RotateState = WaitLowResetStop;
            }
            else
            {
                d2m_Messege.V_q = -5.0f;
//                stage_phase = fmodf(TWO_PI + d2m_Messege.AngularPosition - reset_target_angle_position, 1.02f);
//                if (stage_phase < 2.0f)
//                {
//                    d2m_Messege.V_q =  -5.0f;
//                }
//                else
//                {
//                    d2m_Messege.V_q =  -4.8f;
//                }
            }
            if (d2m_Messege.AngularVelocity > -0.1f)
            {
                d2m_Messege.V_d = 0;
                d2m_Messege.V_q = 0;
                TelemetrySendFlag = 0xAABB;
                BLDC_RotateState = WaitStop;
            }
            if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
            {
                total_sum_rotate_turn_cnt++;
            }
            break;

        case WaitLowResetStop:
            if ((d2m_Messege.AngularVelocity < -1.0f)  && (d2m_Messege.AngularPosition > reset_target_angle_position))
            {
                d2m_Messege.V_d =  0;
                d2m_Messege.V_q =  1;
            }
            else
            {
                d2m_Messege.V_d = 0;
                d2m_Messege.V_q = 0;
                TelemetrySendFlag = 0xAABB;
                BLDC_RotateState = WaitStop;
            }
            if (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
            {
                total_sum_rotate_turn_cnt++;
            }
            break;

        case WaitStop:
            BLDC_Stop();
            BLDC_RotateState = WaitStart;
            break;

        default:

            break;
    }
    d2m_Messege.MotorActualPosition = (total_sum_rotate_turn_cnt * TWO_PI + turn_direction_symbol * (d2m_Messege.AngularPosition - origin_init_angle_position)) * 57.3f;
    last_angle = d2m_Messege.AngularPosition;
}


//基于圈数,绝对位置以复位后为零位
void BLDC_RotateTurnControlProMaxReset(Uint16 phase)
{ 
    switch(BLDC_RotateState)
    {
        case WaitStart:
            if (m2d_Messege.Commond == DELIVERRY)
            {
                CurrentTurnIndex = 0;
                TotalTurnCount   = m2d_Messege.MotorRotateCount;
                turn_direction_symbol = 1;
                d2m_Messege.MotorStatus.bit.WorkStatus = 1;
                m2d_Messege.Commond = 0;
                BLDC_RotateState = TotalTurns;
            }
            else if (m2d_Messege.Commond == RESET)
            {
                BLDC_Start();
                reset_current_turn_cnt =  0;
                turn_direction_symbol  = -1;
                origin_init_angle_position = d2m_Messege.AngularPosition;
                hight_turn_count = floorf(m2d_Messege.HighSpeedReverseNumber * 1.875f);
                reset_target_angle_position = modff((m2d_Messege.LowSpeedReverseNumber + m2d_Messege.HighSpeedReverseNumber) * 1.875f
                                                   + (1.0f - origin_init_angle_position * TWO_PI_INV), &reset_total_turn_count) * TWO_PI;
                reset_target_angle_position = TWO_PI - reset_target_angle_position;
                lower_turn_count = (Uint16)reset_total_turn_count;
                d2m_Messege.MotorTargetPosition = 0.0f;//(m2d_Messege.LowSpeedReverseNumber + m2d_Messege.HighSpeedReverseNumber) * 1.875f * 360.0f;
                d2m_Messege.V_q = -5.0f;
                m2d_Messege.Commond = 0;
                BLDC_RotateState = HightReset;
            }
            else if (m2d_Messege.Commond == APROXMT_ZERO)
            {
                total_sum_rotate_turn_cnt = 0;
                origin_init_angle_position = d2m_Messege.AngularPosition;
                d2m_Messege.MotorTargetPosition = 0.0f;
                m2d_Messege.Commond = 0;
            }
            else
            {
                d2m_Messege.MotorStatus.bit.WorkStatus = 0;
                BLDC_Stop();
            }
            break;

        case TotalTurns:
            if (CurrentTurnIndex < TotalTurnCount)
            {
                target_wait_time   = m2d_Messege.TimeInterval[CurrentTurnIndex] * 0.05; // 两次的时间间隔 (s)
                // current_turn_count = m2d_Messege.RotateTurns[CurrentTurnIndex] * 1.875f;// r/s 旋转圈数/s
                d2m_Messege.MotorTargetPosition += m2d_Messege.RotateTurns[CurrentTurnIndex] * 1.875f * 360.0f;
                if (d2m_Messege.MotorTargetPosition > d2m_Messege.MotorActualPosition)
                {
                    CurrentTurnCount = (Uint16)((d2m_Messege.MotorTargetPosition - d2m_Messege.MotorActualPosition) / 360.f);
                    deliverry_rotate_turn_cnt = 0;
                    d2m_Messege.V_d = 0;
                    BLDC_Start();
                    if (0 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = 7.0;//5
                        BLDC_RotateState = DeceleratePhase;
                    }
                    else
                    {
                        d2m_Messege.V_q = 6.0;//5
                        BLDC_RotateState = AcceleratePhase;//Running;
                    }
                }
                else
                {
                    CurrentTurnCount = 0;
                    deliverry_rotate_turn_cnt = 0;
                    d2m_Messege.V_d = 0;
                    d2m_Messege.V_q = 7.0;//5
                    BLDC_Start();
                    BLDC_RotateState = DeceleratePhase;
                }
            }
            else
            {
                BLDC_RotateState = WaitStop;
            }
            break;

        case AcceleratePhase:
            if ((last_angle < (origin_init_angle_position - 1.0e-6f))
            &&  (d2m_Messege.AngularPosition > (origin_init_angle_position + 1.0e-6f)))
            {
                deliverry_rotate_turn_cnt++;
                total_sum_rotate_turn_cnt++;
                if ((CurrentTurnCount - deliverry_rotate_turn_cnt) <= 4)
                {
                    if (1 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 2.0f;
                        BLDC_RotateState = DeceleratePhase;
                    }
                    else if (2 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 2.0f;// 6 + 2.0 == 8
                        BLDC_RotateState = SmallTurnDeceleratePhase;
                    }
                    else if (3 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 4.0f;// 6 + 4.0 == 10
                        BLDC_RotateState = SmallTurnDeceleratePhase;
                    }
                    else if (4 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 4.0f;// 6 + 4.0 == 10
                        BLDC_RotateState = SmallTurnDeceleratePhase;
                    }
                    else if (5 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 4.0f;// 6 + 4 == 10
                        BLDC_RotateState = SmallTurnDeceleratePhase;
                    }
                    else if (6 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 2.0f; // 8 + 2 == 11
                        BLDC_RotateState = SmallTurnDeceleratePhase;
                    }
                    else if (7 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 1.0f; // 10 + 1 == 11
                        BLDC_RotateState = SmallTurnDeceleratePhase;
                    }
                    else if (8 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 2.0f; // 12 - 2.0 = 10
                        BLDC_RotateState = SmallTurnDeceleratePhase;
                    }
                    else if (9 == CurrentTurnCount)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 3.2f;// 14 - 3.0 = 11
                        BLDC_RotateState = SmallTurnDeceleratePhase;
                    }
                    else
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 2.0f;
                        BLDC_RotateState = SmallTurnDeceleratePhase;
                    }
                }
                else
                {
                    if(d2m_Messege.V_q > (MAX_VQ - 1.0e-6f))
                    {
                        d2m_Messege.V_q = MAX_VQ;
                        BLDC_RotateState = UniformPhase;
                    }
                    else
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 2.0f;
                    }
                }
            }
            if (fabsf(d2m_Messege.MotorTargetPosition - d2m_Messege.MotorActualPosition) < 360)
            {
                d2m_Messege.V_q = 5.2f;
                BLDC_RotateState = DeceleratePhase;
            }
            break;

        case SmallTurnDeceleratePhase:
            if ((last_angle < (origin_init_angle_position - 1.0e-6f))
            &&  (d2m_Messege.AngularPosition > (origin_init_angle_position + 1.0e-6f)))
            {
                deliverry_rotate_turn_cnt++;
                total_sum_rotate_turn_cnt++;
                if (deliverry_rotate_turn_cnt >= CurrentTurnCount)
                {
                    if (CurrentTurnCount == 2)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 2.0f;
                    }
                    BLDC_RotateState = DeceleratePhase;
                }
                else
                {
                    if (CurrentTurnCount == 9) // 5
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 2.0f;
                    }
                    else if (CurrentTurnCount == 8) // 4
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 1.5f;
                    }
                    else if (CurrentTurnCount == 7) // 4
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 1.2f;
                    }
                    else if (CurrentTurnCount == 6) // 3
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 1.20f;
                    }
                    else if (CurrentTurnCount == 5) // 3
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 1.20f;
                    }
                    else if (CurrentTurnCount == 4) // 2
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 2.4f;
                    }
                    else if (CurrentTurnCount == 3) // 2
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 3.0f;
                    }
                    else if (CurrentTurnCount == 2)
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 2.0f;
                    }
                    else
                    {

                    }
                }
            }
            if (fabsf(d2m_Messege.MotorTargetPosition - d2m_Messege.MotorActualPosition) < 360)
            {
                d2m_Messege.V_q = 5.2f;
                BLDC_RotateState = DeceleratePhase;
            }
            break;

        case UniformPhase:
            if ((last_angle < (origin_init_angle_position - 1.0e-6f))
            &&  (d2m_Messege.AngularPosition > (origin_init_angle_position + 1.0e-6f)))
            {
                deliverry_rotate_turn_cnt++;
                total_sum_rotate_turn_cnt++;
                if (deliverry_rotate_turn_cnt >= CurrentTurnCount)
                {
                    d2m_Messege.V_q = 5.2f;
                    BLDC_RotateState = DeceleratePhase;
                }
                else
                {
                    if (CurrentTurnCount >= 20)
                    {
                        if ((CurrentTurnCount - deliverry_rotate_turn_cnt) <= 5)
                        {
                            d2m_Messege.V_q = d2m_Messege.V_q - 1.8f;// 2.25 -> 2.5
                        }
                        else
                        {
                            d2m_Messege.V_q = MAX_VQ;
                        }
                    }
                    else
                    {
                        if ((CurrentTurnCount - deliverry_rotate_turn_cnt) <= 4)
                        {
                            d2m_Messege.V_q = d2m_Messege.V_q - 2.4f;
                        }
                        else
                        {
                            d2m_Messege.V_q = MAX_VQ;
                        }
                    }
                }
            }
            break;

        case DeceleratePhase:
            // if (d2m_Messege.AngularPosition > target_angle_position)
            if (d2m_Messege.MotorActualPosition > d2m_Messege.MotorTargetPosition)
            {
                d2m_Messege.V_q = 0.0f;
                BLDC_RotateState = DecelerateStopPhase;
            }
            else
            {
                if (d2m_Messege.AngularVelocity < 1.0e-3f)
                {
                    d2m_Messege.V_q =  0.0f;
                    BLDC_RotateState = DecelerateStopPhase;
                }
                else
                {
                    stage_phase = fabsf(d2m_Messege.MotorTargetPosition - d2m_Messege.MotorActualPosition);
                    if (stage_phase > 300.0f)
                    {
                        d2m_Messege.V_q =  5.5f;
                    }
                    else if(stage_phase > 240.0f)
                    {
                        d2m_Messege.V_q =  4.5f;
                    }
                    else if(stage_phase > 180.0f)
                    {
                        d2m_Messege.V_q =  4.0f;
                    }
                    else
                    {
                        d2m_Messege.V_q =  3.0f;
                    }
                }
            }

            if ((last_angle < (origin_init_angle_position - 1.0e-6f))
            &&  (d2m_Messege.AngularPosition > (origin_init_angle_position + 1.0e-6f)))
            {
                deliverry_rotate_turn_cnt++;
                total_sum_rotate_turn_cnt++;
                d2m_Messege.V_q = 0.0f;
                BLDC_RotateState = DecelerateStopPhase;
            }
            break;

        case DecelerateStopPhase:
            if (d2m_Messege.AngularVelocity > 1.0f)
            {
                d2m_Messege.V_d = 0;
                d2m_Messege.V_q = -1.0f;
            }
            else
            {
                d2m_Messege.V_d = 0;
                d2m_Messege.V_q = 0;
                if (d2m_Messege.AngularVelocity < 1.0e-3f)
                {
                    CurrentTurnIndex++;
                    wait_time_count = 0;
                    TelemetrySendFlag = 0xAABB;
                    if(CurrentTurnIndex >= TotalTurnCount)
                    {
                        BLDC_Stop();
                        BLDC_RotateState = WaitStop;
                    }
                    else
                    {
                        BLDC_RotateState = WaitTime;
                    }
                }
            }

            if ((last_angle < (origin_init_angle_position - 1.0e-6f))
            &&  (d2m_Messege.AngularPosition > (origin_init_angle_position + 1.0e-6f)))
            {
                deliverry_rotate_turn_cnt++;
                total_sum_rotate_turn_cnt++;
            }
            break;

        case WaitTime:
            if (wait_time_count > target_wait_time)
            {
                BLDC_RotateState = TotalTurns;
            }
            else
            {
                BLDC_Stop();
                wait_time_count += 0.0001f;
            }
            break;

        case HightReset:
            if (reset_current_turn_cnt >= hight_turn_count)
            {
                BLDC_RotateState = LowReset;
            }
            else
            {
                if ((last_angle > (origin_init_angle_position + 1.0e-6f))
                &&  (d2m_Messege.AngularPosition < (origin_init_angle_position - 1.0e-6f)))
                {
                    ++reset_current_turn_cnt;
                    --total_sum_rotate_turn_cnt;
                    if(d2m_Messege.V_q < -(MAX_VQ - 1.0e-6f))
                    {
                        d2m_Messege.V_q = -MAX_VQ;
                    }
                    else
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q - 2.0f;
                    }
                }
            }
            break;

        case LowReset:
            if (reset_current_turn_cnt >= lower_turn_count)
            {
                BLDC_RotateState = LowResetStop;
            }
            else
            {
                if ((last_angle > (origin_init_angle_position + 1.0e-6f))
                &&  (d2m_Messege.AngularPosition < (origin_init_angle_position - 1.0e-6f)))
                {
                    ++reset_current_turn_cnt;
                    --total_sum_rotate_turn_cnt;
                    if(d2m_Messege.V_q > -(5.0f + 1.0e-6f))
                    {
                        d2m_Messege.V_q = -5.0f;
                        BLDC_RotateState = LowResetUniformPhase;
                    }
                    else
                    {
                        d2m_Messege.V_q = d2m_Messege.V_q + 2.0f;
                    }
                }
            }
            if (m2d_Messege.Commond == APROXMT_ZERO)
            {
                total_sum_rotate_turn_cnt = 0;
                origin_init_angle_position = d2m_Messege.AngularPosition;
                m2d_Messege.Commond = 0;
                d2m_Messege.MotorTargetPosition = 0.0f;
                BLDC_RotateState = WaitLowResetStop;
            }
            break;

        case LowResetUniformPhase:
            if (reset_current_turn_cnt >= lower_turn_count)
            {
                BLDC_RotateState = LowResetStop;
            }
            else
            {
                if ((last_angle > (origin_init_angle_position + 1.0e-6f))
                &&  (d2m_Messege.AngularPosition < (origin_init_angle_position - 1.0e-6f)))
                {
                    ++reset_current_turn_cnt;
                    --total_sum_rotate_turn_cnt;
                    d2m_Messege.V_q = -5.0f;
                }
            }
            if (m2d_Messege.Commond == APROXMT_ZERO)
            {
                total_sum_rotate_turn_cnt = 0;
                origin_init_angle_position = d2m_Messege.AngularPosition;
                m2d_Messege.Commond = 0;
                d2m_Messege.MotorTargetPosition = 0.0f;
                BLDC_RotateState = WaitLowResetStop;
            }
            break;

        case LowResetStop:
            if ((d2m_Messege.AngularPosition < reset_target_angle_position)
            ||  (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI)
            ||  (reset_current_turn_cnt > lower_turn_count))  // before 30 deg
            {
                d2m_Messege.V_q = 0.0f;
                BLDC_RotateState = WaitLowResetStop;
            }
            else
            {
                d2m_Messege.V_q = -5.0f;
            }
            if (d2m_Messege.AngularVelocity > -0.1f)
            {
                d2m_Messege.V_d = 0;
                d2m_Messege.V_q = 0;
                total_sum_rotate_turn_cnt  = 0;
                origin_init_angle_position = d2m_Messege.AngularPosition;
                d2m_Messege.MotorTargetPosition = 0.0f;
                TelemetrySendFlag = 0xAABB;
                BLDC_RotateState = WaitStop;
            }
            if ((last_angle > (origin_init_angle_position + 1.0e-6f))
            &&  (d2m_Messege.AngularPosition < (origin_init_angle_position - 1.0e-6f)))
            {
                ++reset_current_turn_cnt;
                --total_sum_rotate_turn_cnt;
            }
            if (m2d_Messege.Commond == APROXMT_ZERO)
            {
                total_sum_rotate_turn_cnt = 0;
                origin_init_angle_position = d2m_Messege.AngularPosition;
                m2d_Messege.Commond = 0;
                d2m_Messege.MotorTargetPosition = 0.0f;
                BLDC_RotateState = WaitLowResetStop;
            }
            break;

        case WaitLowResetStop:
            if (d2m_Messege.AngularVelocity < -0.2f)
            {
                d2m_Messege.V_d =  0;
                d2m_Messege.V_q =  1;
            }
            else
            {
                d2m_Messege.V_d = 0;
                d2m_Messege.V_q = 0;
                total_sum_rotate_turn_cnt  = 0;
                origin_init_angle_position = d2m_Messege.AngularPosition;
                d2m_Messege.MotorTargetPosition = 0.0f;
                TelemetrySendFlag = 0xAABB;
                BLDC_RotateState = WaitStop;
            }
            if ((last_angle > (origin_init_angle_position + 1.0e-6f))
            && (d2m_Messege.AngularPosition < (origin_init_angle_position - 1.0e-6f)))
            {
                ++reset_current_turn_cnt;
                --total_sum_rotate_turn_cnt;
            }
            if (m2d_Messege.Commond == APROXMT_ZERO)
            {
                total_sum_rotate_turn_cnt = 0;
                origin_init_angle_position = d2m_Messege.AngularPosition;
                d2m_Messege.MotorTargetPosition = 0.0f;
                m2d_Messege.Commond = 0;
            }
            break;

        case WaitStop:
            BLDC_Stop();
            BLDC_RotateState = WaitStart;
            break;

        default:

            break;
    }
    
    d2m_Messege.MotorActualPosition = (total_sum_rotate_turn_cnt * TWO_PI
                                    + ( d2m_Messege.AngularPosition - origin_init_angle_position)
                                    + (fabs(d2m_Messege.AngularPosition - last_angle) > ONE_PI ? TWO_PI : 0)
                                    * turn_direction_symbol) * 57.3f;
    last_angle = d2m_Messege.AngularPosition;
}


void BLDC_RotateTurnControlVelocity(Uint16 phase)
{
    float delta_theta;
    if (0xABCD != delta_angle_update_flag)
    {
        delta_theta = d2m_Messege.AngularPosition - last_angle;
        delta_theta = (delta_theta < -ONE_PI) ? (delta_theta + TWO_PI)
                    : (delta_theta >  ONE_PI) ? (delta_theta - TWO_PI)
                    :  delta_theta;
    }
    else
    {
        delta_theta = 0;
        delta_angle_update_flag = 0;
    }
    d2m_Messege.MotorActualPosition += delta_theta;

    switch(BLDC_RotateState)
    {
        case WaitStart:
            if (m2d_Messege.Commond == DELIVERRY)
            {
                CurrentTurnIndex = 0;
                TotalTurnCount   = m2d_Messege.MotorRotateCount;
                d2m_Messege.MotorStatus.bit.WorkStatus = 1;
                m2d_Messege.Commond = 0;
                BLDC_RotateState = TotalTurns;
            }
            else if (m2d_Messege.Commond == RESET)
            {
                d2m_Messege.MotorTargetPosition = 0.0f;
                d2m_Messege.MotorActualPosition = (m2d_Messege.LowSpeedReverseNumber + m2d_Messege.HighSpeedReverseNumber) * 1.875f * TWO_PI;//更新实际位置
                high_speed_end_position         =  m2d_Messege.LowSpeedReverseNumber * 1.875f * TWO_PI;//更新高速结束段位置
                m2d_Messege.Commond = 0;
                m2d_Messege.TargetAngleVelocity = 0;
                BLDC_Start();
                BLDC_RotateState = HightReset;
            }
            else if (m2d_Messege.Commond == APROXMT_ZERO)
            {
                m2d_Messege.Commond = 0;
            }
            else
            {
                d2m_Messege.MotorStatus.bit.WorkStatus = 0;
                BLDC_Stop();
            }
            break;

        case TotalTurns:
            if (CurrentTurnIndex < TotalTurnCount)
            {
                target_rote_time   = m2d_Messege.RotateTimes [CurrentTurnIndex] * 0.01;     // 旋转总运行时间(s)
                target_wait_time   = m2d_Messege.TimeInterval[CurrentTurnIndex] * 0.05;     // 两次的时间间隔 (s)
                target_turn_count  = m2d_Messege.RotateTurns [CurrentTurnIndex];            // 投放旋转圈数(r)
                current_turn_count = target_turn_count * 1.875f;                            // 电机旋转圈数(r)
                total_turn_time = target_rote_time * target_turn_count;                     // 投放规定的总时间
//                update_delta_target_position = d2m_Messege.MotorTargetPosition;
                d2m_Messege.MotorTargetPosition += current_turn_count * TWO_PI;

                if (m2d_Messege.RotateTimes [CurrentTurnIndex] < 2)
                {
                    current_turn_angle_rate = 187.5f;// 93.75f;// 旋转圈数/s
                    PositionControllerPIDParameterSet(PID_POSITION_KP, PID_POSITION_KI, PID_POSITION_KD);
                    BLDC_RotateState = WaitRun;
                }
                else if (m2d_Messege.RotateTimes [CurrentTurnIndex] < 20)
                {
                    bound_turn_count = 7.5f / (target_rote_time * target_rote_time * ACC_DELIVERRY);
                    if(target_turn_count > bound_turn_count)
                    {
                        delta_acc_time = 0.5f * (total_turn_time
                                       - sqrtf(total_turn_time * total_turn_time
                                       - 7.5f * target_turn_count / ACC_DELIVERRY));
                        current_turn_angle_rate = ACC_DELIVERRY * delta_acc_time;
                    }
                    else
                    {
                        delta_acc_time = total_turn_time * 0.5f;
                        current_turn_angle_rate = 187.5f;// 93.75f;// 旋转圈数/s
                    }
                    ahead_stop_distance = 0.5f * ACC_DELIVERRY * delta_acc_time * delta_acc_time * TWO_PI;
                    PositionControllerPIDParameterSet(15, PID_POSITION_KI, PID_POSITION_KD);
                    BLDC_RotateState = WaitRun;
                }
                else // 采用位置控制方式 速度太低
                {
                    max_turn_angle_rate = 187.5f / m2d_Messege.RotateTimes [CurrentTurnIndex];// 旋转圈数/s
                    current_turn_angle_rate = TWO_PI * max_turn_angle_rate;// rad/s
                    max_turn_angle_rate = max_turn_angle_rate < 9.375f ? 9.375f : max_turn_angle_rate;
                    PositionControllerPIDParameterSet(5.0, PID_POSITION_KI, PID_POSITION_KD);
                    BLDC_RotateState = WaitPositionRun;
                }
#ifdef TERMINAL_DEBUG
                TelemetrySendFlag = 0xAABB;
#endif
                BLDC_Start();
            }
            else
            {
                BLDC_RotateState = WaitStop;
            }
            break;

        case WaitRun:
            if (fabs(d2m_Messege.AngularVelocity) > 1.0f)
            {
                BLDC_RotateState = Running;
            }
            else
            {
                m2d_Messege.TargetAngleVelocity = update_current_turn_angle_rate = 7.0f;
            }
            break;

        case Running:
            if ((d2m_Messege.MotorActualPosition < (d2m_Messege.MotorTargetPosition - ahead_stop_distance))
            && (fabs(d2m_Messege.AngularVelocity) > 0.5f))
            {
                if (update_current_turn_angle_rate > (current_turn_angle_rate - 1.0e-5f))
                {
                    update_current_turn_angle_rate = current_turn_angle_rate;
                }
                else
                {
                    update_current_turn_angle_rate += ACC_DELIVERRY * 0.0001f;
                }
                if (m2d_Messege.RotateTimes [CurrentTurnIndex] < 10)
                {
                    //位置控制方式
                    PositionControllerPID(d2m_Messege.MotorTargetPosition, d2m_Messege.MotorActualPosition, &m2d_Messege.TargetAngleVelocity);
                    m2d_Messege.TargetAngleVelocity = _constrain(m2d_Messege.TargetAngleVelocity, -update_current_turn_angle_rate, update_current_turn_angle_rate);
                }
                else
                {
                    // 速度控制方式
                    m2d_Messege.TargetAngleVelocity = update_current_turn_angle_rate;
                }
            }
            else
            {
                if(fabs(d2m_Messege.AngularVelocity) > 0.5f)
                {
                    if (update_current_turn_angle_rate < 1.0e-3f)
                    {
                        update_current_turn_angle_rate = 0.0f;
                    }
                    else
                    {
                        update_current_turn_angle_rate -= ACC_DELIVERRY * 0.0001f;
                    }
                    m2d_Messege.TargetAngleVelocity = update_current_turn_angle_rate;
                }
                else
                {
                    m2d_Messege.TargetAngleVelocity = 0.0f;
                    CurrentTurnIndex++;
                    if(CurrentTurnIndex >= TotalTurnCount)
                    {
                        BLDC_Stop();
                        BLDC_RotateState = WaitStop;
                    }
                    else
                    {
                        #ifdef TERMINAL_DEBUG
                        TelemetrySendFlag = 0xAABB;
                        #endif
                        wait_time_count = 0;
                        BLDC_RotateState = WaitTime;
                    }
                }
            }
            break;

        case WaitPositionRun:
            if (update_delta_target_position < (d2m_Messege.MotorTargetPosition - 1.0e-5f))
            {
                update_delta_target_position += current_turn_angle_rate * 0.0001f;
            }
            else
            {
                update_delta_target_position = d2m_Messege.MotorTargetPosition;
            }

            if (fabs(d2m_Messege.AngularVelocity) > 0.5f)
            {
                BLDC_RotateState = PositionControl;
            }
            else
            {
                PositionControllerPID(update_delta_target_position, d2m_Messege.MotorActualPosition, &m2d_Messege.TargetAngleVelocity);
                m2d_Messege.TargetAngleVelocity = _constrain(m2d_Messege.TargetAngleVelocity, -max_turn_angle_rate, max_turn_angle_rate);
            }
            break;

        case PositionControl:
            if (update_delta_target_position < (d2m_Messege.MotorTargetPosition - 1.0e-5f))
            {
                update_delta_target_position += current_turn_angle_rate * 0.0001f;
            }
            else
            {
                update_delta_target_position = d2m_Messege.MotorTargetPosition;
            }

            if ((d2m_Messege.MotorActualPosition > (d2m_Messege.MotorTargetPosition - 0.5f))
            &&  (fabs(d2m_Messege.AngularVelocity) < 1.0e-3f))
            {
                m2d_Messege.TargetAngleVelocity = 0;
                CurrentTurnIndex++;
                if(CurrentTurnIndex >= TotalTurnCount)
                {
                    BLDC_Stop();
                    BLDC_RotateState = WaitStop;
                }
                else
                {
                    #ifdef TERMINAL_DEBUG
                    TelemetrySendFlag = 0xAABB;
                    #endif
                    wait_time_count = 0;
                    BLDC_RotateState = WaitTime;
                }
            }
            else
            {
                PositionControllerPID(update_delta_target_position, d2m_Messege.MotorActualPosition, &m2d_Messege.TargetAngleVelocity);
                m2d_Messege.TargetAngleVelocity = _constrain(m2d_Messege.TargetAngleVelocity, -max_turn_angle_rate, max_turn_angle_rate);
            }
            break;

        case WaitTime:
            if (wait_time_count > target_wait_time)
            {
                BLDC_RotateState = TotalTurns;
            }
            else
            {
                BLDC_Stop();
                wait_time_count += 0.0001f;
            }
            break;

        case HightReset:
            if (d2m_Messege.MotorActualPosition < high_speed_end_position)
            {
                BLDC_RotateState = LowReset;
            }
            else
            {
                if (m2d_Messege.TargetAngleVelocity < (-50.0f + 1.0e-5f))
                {
                    m2d_Messege.TargetAngleVelocity = -50.0f;
                }
                else
                {
                    m2d_Messege.TargetAngleVelocity += ACC_RESEET * 0.0001f;
                }
            }
            // 近似零位处理
            if (m2d_Messege.Commond == APROXMT_ZERO)
            {
                m2d_Messege.TargetAngleVelocity = 0;
                BLDC_RotateState = WaitLowResetStop;
                m2d_Messege.Commond = 0;
            }
            break;

        case LowReset:
            if (d2m_Messege.MotorActualPosition < 0)
            {
                m2d_Messege.TargetAngleVelocity = 0;
                BLDC_RotateState = WaitLowResetStop;
            }
            else
            {
                if (m2d_Messege.TargetAngleVelocity > (-10.0f - 1.0e-5f))
                {
                    m2d_Messege.TargetAngleVelocity = -10.0f;
                }
                else
                {
                    m2d_Messege.TargetAngleVelocity -= ACC_RESEET * 0.0001f;
                }
            }
            // 近似零位处理
            if (m2d_Messege.Commond == APROXMT_ZERO)
            {
                d2m_Messege.MotorTargetPosition = 0.0f;
                m2d_Messege.TargetAngleVelocity = 0;
                BLDC_RotateState = WaitLowResetStop;
                m2d_Messege.Commond = 0;
            }
            break;

        case WaitLowResetStop:
            if (fabs(d2m_Messege.AngularVelocity) > 1.0e-3f)
            {
//                PositionControllerPID(d2m_Messege.MotorTargetPosition, d2m_Messege.MotorActualPosition, &m2d_Messege.TargetAngleVelocity);
//                m2d_Messege.TargetAngleVelocity = _constrain(m2d_Messege.TargetAngleVelocity, -10, 10);
                m2d_Messege.TargetAngleVelocity = 0;
            }
            else
            {
                d2m_Messege.MotorTargetPosition = 0.0f;
                m2d_Messege.TargetAngleVelocity = 0;
                d2m_Messege.MotorTargetPosition = 0.0f;
                BLDC_RotateState = WaitStop;
            }
            if (m2d_Messege.Commond == APROXMT_ZERO)
            {
                d2m_Messege.MotorTargetPosition = 0.0f;
                m2d_Messege.Commond = 0;
            }
            break;

        case WaitStop:
            TelemetrySendFlag = 0xAABB;
            BLDC_Stop();
            BLDC_RotateState = WaitStart;
            break;

        default:

            break;
    }
    last_angle = d2m_Messege.AngularPosition;
}
// 基于位置控制旋转圈数
void BLDC_RotateTurnControlPosition(Uint16 phase)
{
    switch(BLDC_RotateState)
    {
        case WaitStart:
            if (m2d_Messege.Commond == DELIVERRY)
            {
                BLDC_Start();
                m2d_Messege.Commond = 0;
                TotalTurnCount = m2d_Messege.MotorRotateCount;
                CurrentTurnIndex = 0;
                BLDC_RotateState = TotalTurns;
            }
            else
            {
                BLDC_Stop();
            }
            break;

        case TotalTurns:
            if (CurrentTurnIndex < TotalTurnCount)
            {
                target_rote_time   = m2d_Messege.RotateTimes [CurrentTurnIndex] * 0.01; // 旋转总运行时间(s)
                target_wait_time   = m2d_Messege.TimeInterval[CurrentTurnIndex] * 0.05; // 两次的时间间隔 (s)
                current_angle_rate = m2d_Messege.RotateTurns [CurrentTurnIndex] / target_rote_time;// r/s 旋转圈数/s
                rote_time_count    = 0.0f;
                current_angle      = 0.0f;
                BLDC_RotateState   = Running;
            }
            else
            {
                BLDC_RotateState = WaitStop;
            }
            break;

        case Running:
            if (rote_time_count > target_rote_time)
            {
                CurrentTurnIndex++;
                wait_time_count = 0;
                BLDC_RotateState = WaitTime;
            }
            else
            {
                current_angle   += current_angle_rate * rote_time_count;
                m2d_Messege.TargetPosition = fmodf(current_angle, 360.0f);
                rote_time_count += 0.005f;
            }
            break;

        case WaitTime:
            if (wait_time_count > target_wait_time)
            {
                BLDC_RotateState = TotalTurns;
            }
            else
            {
                wait_time_count += 0.005f;
            }
            break;

        case WaitStop:
            BLDC_Stop();
            BLDC_RotateState = WaitStart;
            break;

        default:
            break;
    }
}
