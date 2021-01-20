/*
 * State_Machine.h
 *
 *  Created on: 2016��4��23��
 *      Author: ZGH
 */

#ifndef STEERINGENGINE_28335_V3_INC_STATE_MACHINE_H_
#define STEERINGENGINE_28335_V3_INC_STATE_MACHINE_H_

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

#define SELFCHECK_REACT 		(0x81) // 自检应答
#define DELIVERRY_REACT 		(0x82) // 投放应答
#define RESET_REACT     		(0x83) // 复位应答
#define APROXMT_ZERO_REACT 		(0x84) // 近似零位应答
#define DRIVER_BOARD_CYCLE_SEND (0x85) // 驱动板周期发送
#define TELEMETRY_SEND 			(0x85) // 遥测数据发送

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
} Master2DriverMessege; //


typedef struct _Driver2MasterMessege
{
	Uint16 DriverBoardCheck;		// 驱动板自检故障码
	Uint16 MotorCheck;				// 电机自检故障码
	Uint16 SoftwareVersion_L;		// 驱动板软件版本号 low
	Uint16 SoftwareVersion_H;		// 驱动板软件版本号 high

	Uint16 MotorDriverVoltage;     	// 电机驱动电压
	Uint16 MotorDriverCurrent;    	// 电机驱动电流
	Uint16 MotorRotatePosition; 	// 电机旋转位置
	Uint16 MotorAngularVelocity;	// 电机角速度
	Uint16 MotorStatus;      		// 电机状态参数

	// 遥测上报数据包
	Uint16 MotorTargetPosition;		// 电机目标位置
	Uint16 MotorActualPosition;		// 电机实际转动位置
	Uint16 ActualRotationRings;		// 本组电机实际旋转圈数
	Uint16 ThrowStatus;        		// 投放状态
}Driver2MasterMessege;

extern Master2DriverMessege m2d_Messege;
extern Driver2MasterMessege d2m_Messege;

extern Uint16 TelemetrySendFlag;

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

void BLDC_TelemetrySend(void);
/**
 * @brief the 422 communication receive function
 */
void CommunicationStateMachine(Uint16 Receive_Data);

#endif /* STEERINGENGINE_28335_V3_INC_STATE_MACHINE_H_ */
