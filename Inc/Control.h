/*
 * Control.h
 *
 *  Created on: 2021
 *      Author: ZGH
 */

#ifndef _INC_CONTROL_H_
#define _INC_CONTROL_H_

#include "include.h"

#define POSITION_UPDATE_FREQ   10000
#define POSITION_UPDATE_DT     (float)(1.0/POSITION_UPDATE_FREQ)

#define CURRENT_UPDATE_FREQ   10000
#define CURRENT_UPDATE_DT     (float)(1.0f / CURRENT_UPDATE_FREQ)

//position control pid
#define PID_POSITION_KP  10.0 //12位置满足，但声音大
#define PID_POSITION_KI  0.02
#define PID_POSITION_KD  0.04 //0.12
#define PID_POSITION_INTEGRATION_LIMIT    20.0

#define PID_SPEED_KP  1.2 //3.5
#define PID_SPEED_KI  0.0 //0.01
#define PID_SPEED_KD  0.0 //0.12
#define PID_SPEED_INTEGRATION_LIMIT    20.0

#define PID_CURRENT_D_KP  2.0 //3.5
#define PID_CURRENT_D_KI  0.0
#define PID_CURRENT_D_KD  0.0 //0.12
#define PID_CURRENT_D_INTEGRATION_LIMIT    20.0

#define PID_CURRENT_Q_KP  0.0 //3.5
#define PID_CURRENT_Q_KI  0.0
#define PID_CURRENT_Q_KD  0.0 //0.12
#define PID_CURRENT_Q_INTEGRATION_LIMIT    20.0

#define _constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
//#define DEFAULT_PID_INTEGRATION_LIMIT    5000.0
/*
 * @brief the pid initialize
 */
void Control_Init(void);

/*
 * @brief the current d control pid
 */
void CurrentD_ControllerPID(float i_desired, float i_actual, float *i_out);

/*
 * @brief the current q control pid
 */
void CurrentQ_ControllerPID(float i_desired, float i_actual, float *i_out);

/*
 * @brief the speed control pid
 */
void SpeedControllerPID(float i_desired, float i_actual, float *i_out);

/*
 * @brief the position control pid
 */
void PositionControllerPID(float i_desired, float i_actual, float *i_out);

void SpeedControllerPIDParameterSet(float p, float i);
void PositionControllerPIDParameterSet(float p, float i,  float d);

#endif /* STEERINGENGINE_28335_V3_INC_CONTROL_H_ */
