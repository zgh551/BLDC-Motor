/*
 * State_Machine.h
 *
 *  Created on: 2021
 *      Author: ZGH
 */

#ifndef _INC_STATE_MACHINE_H_
#define _INC_STATE_MACHINE_H_

#include "include.h"

 #define LM_COMMOND_BIT 					8
 #define LM_LOCK_BIT  						16
 #define LM_POWER_BIT 						17
 #define LM_LAUCH_BIT 						18

 #define LM_COMMOND_MASK 					0xff
 #define LM_LOCK_MASK  						0x01
 #define LM_LAUCH_MASK 						0x01
 #define LM_POWER_MASK 						0x01

#define SELFCHECK 		(1) // 自检
#define DELIVERRY 		(2) // 投放
#define RESET     		(3) // 复位
#define APROXMT_ZERO 	(4) // 近似零位

// user test interface
#define TARGET_DQ       (5) // 目标DQ
#define TARGET_SPEED    (6) // 目标目标速度

#define SELFCHECK_REACT 		(0x81) // 自检应答
#define DELIVERRY_REACT 		(0x82) // 投放应答
#define RESET_REACT     		(0x83) // 复位应答
#define APROXMT_ZERO_REACT 		(0x84) // 近似零位应答
#define DRIVER_BOARD_CYCLE_SEND (0x85) // 驱动板周期发送
#define TELEMETRY_SEND 			(0x86) // 遥测数据发送
// user define commond
#define TREE_PHASE_CURRENT      (0x91) // 三相电流发送
#define FEEDBACK_CURRENT        (0x92) // 反馈DQ电流

typedef struct _Master2DriverMessege
{
	Uint16 Commond;							// 命令字 1：自检；2：投放； 3：复位 4：近似零位

	Uint16 DeliveryStrategyNumber;			// 投放策略编号
	Uint16 MotorRotateCount;				// 电机旋转次数
	Uint16 RotateTurns[32];					// 旋转圈数
	Uint16 RotateTimes[32];					// 旋转总运行时间
	Uint16 TimeInterval[32];				// 两次的时间间隔

	Uint16 HighSpeedReverseNumber; 			// 高速反转圈数
	Uint16 LowSpeedReverseNumber; 			// 低速反转圈数

    float TargetVd;                         // VD
    float TargetVq;                         // VQ

    float TargetAngleVelocity;              // 目标角速度
    float TargetPosition;                   // 目标位置

} Master2DriverMessege; //


typedef struct _Driver2MasterMessege
{
	Uint16 DriverBoardCheck;		// 驱动板自检故障码
	Uint16 MotorCheck;				// 电机自检故障码
	Uint16 SoftwareVersion_L;		// 驱动板软件版本号 low
	Uint16 SoftwareVersion_H;		// 驱动板软件版本号 high
    union{
        Uint16 all;
        struct{
            Uint16 revert1 : 5;
            Uint16 MotorDirection : 2;// 电机方向状态参数
            Uint16 WorkStatus : 1;// 电机工作状态参数
            Uint16 revert2 : 8;
        }bit;
    }MotorStatus;// 电机状态参数
	float MotorDriverVoltage;     	// 电机驱动电压
	float MotorDriverCurrent;    	// 电机驱动电流

	// 遥测上报数据包
	float MotorTargetPosition;		// 电机目标位置
	float MotorActualPosition;		// 电机实际转动位置
	Uint16 ActualRotationRings;		// 本组电机实际旋转圈数
	Uint16 ThrowStatus;        		// 投放状态

	// User test data
	Uint16 TargetRotateTurns;       // 目标旋转圈数
	// Motor current
	float MotorDriver_IA;           // 电机驱动A相电流
	float MotorDriver_IB;           // 电机驱动B相电流
	float MotorDriver_IC;           // 电机驱动C相电流

	// the clark tranisform current
	float I_alpha;                  // alpha 电流
	float I_beta;                   // beta  电流

	float I_d;                      //
	float I_q;

    float V_d;                      //
    float V_q;

    float V_alpha;                      //
    float V_beta;
	// AD2S1210
    float TotalAngularPosition;     // 角度位置 累计和信息 [0, 360]deg
	float AngularPosition;          // 角度位置 信息 [0, 360]deg
	float AngularVelocity;          // 角速度信息 rps
	Uint16 FaultState;              // AD2S1210错误状态

	Uint16 ControlPhaseState;       // 控制相位状态
}Driver2MasterMessege;

extern Master2DriverMessege m2d_Messege;
extern Driver2MasterMessege d2m_Messege;

extern Uint16 TelemetrySendFlag;
extern Uint16 Time5msSendFlag;
extern Uint16 TimeDQCurrentSendFlag;

extern Uint16 rx_commond;
/**
 * @brief the state machine initialize
 */
void StateMachine_Init(void);


void CommandResponse(Uint16 rsp);
/**
 * @brief self check feedback function
 */
void BLDC_SelfCheck(void);

/**
 * @brief the deliver feedback function
 */
void BLDC_Delivery(void);

/**
 * @brief the reset commond feedback function
 */
void BLDC_Reset(void);

/**
 * @brief the 500ms cycle send
 */
void BLDC_CycleSend500ms(void);

/**
 * @brief the Telemetry send
 */
void BLDC_TelemetrySend(void);

/*
 * @brief the tree phase current send
 */
void BLDC_TreePhaseCurrent(void);
void BLDC_TreePhaseCurrentTest(float a, float b, float c);

/*
 * @brief the current feedback
 */
void BLDC_FeedbackCurrent(void);


/**
 * @brief the 422 communication receive function
 */
void CommunicationStateMachine(Uint16 Receive_Data);

void BLDC_RotateTurnControl(Uint16 phase);

//基于圈数支持多包
void BLDC_RotateTurnControlPro(Uint16 phase);

// 基于位置控制旋转圈数
void BLDC_RotateTurnControlPosition(Uint16 phase);

#endif /* STEERINGENGINE_28335_V3_INC_STATE_MACHINE_H_ */
