/*
 * Control.h
 *
 *  Created on: 2021
 *      Author: ZGH
 */

#ifndef _INC_CONTROL_H_
#define _INC_CONTROL_H_

#include "include.h"

//position control pid
#define PID_POSITION_KP  4.0 //3.5
#define PID_POSITION_KI  0.05
#define PID_POSITION_KD  0.0 //0.12
#define PID_POSITION_INTEGRATION_LIMIT    20.0

#define PID_SPEED_KP  2.0 //3.5
#define PID_SPEED_KI  0.06
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

#endif /* STEERINGENGINE_28335_V3_INC_CONTROL_H_ */
