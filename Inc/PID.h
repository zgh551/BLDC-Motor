/*
 * PID.h
 *
 *  Created on: 2016��3��1��
 *      Author: ZGH
 */

#ifndef STEERINGENGINE_28335_V3_INC_PID_H_
#define STEERINGENGINE_28335_V3_INC_PID_H_

#include "include.h"

//                             ƽ��
#define PID_POSITION_KP  4.2 //3.5
#define PID_POSITION_KI  0.05
#define PID_POSITION_KD  0.12 //0.12
#define PID_POSITION_INTEGRATION_LIMIT    100.0

#define PID_CURRENT_KP  3.5 //3.5
#define PID_CURRENT_KI  0.0
#define PID_CURRENT_KD  0.12 //0.12
#define PID_CURRENT_INTEGRATION_LIMIT    100.0

#define PID_CURRENT_D_KP  3.5 //3.5
#define PID_CURRENT_D_KI  0.0
#define PID_CURRENT_D_KD  0.12 //0.12
#define PID_CURRENT_D_INTEGRATION_LIMIT    100.0

#define PID_CURRENT_Q_KP  3.5 //3.5
#define PID_CURRENT_Q_KI  0.0
#define PID_CURRENT_Q_KD  0.12 //0.12
#define PID_CURRENT_Q_INTEGRATION_LIMIT    100.0

#define DEFAULT_PID_INTEGRATION_LIMIT  	 5000.0

typedef struct
{
  float desired;     //< set point
  float error;        //< error
  float prevError;    //< previous error
  float integ;        //< integral
  float deriv;        //< derivative
  float kp;           //< proportional gain
  float ki;           //< integral gain
  float kd;           //< derivative gain
  float outP;         //< proportional output (debugging)
  float outI;         //< integral output (debugging)
  float outD;         //< derivative output (debugging)
  float iLimit;       //< integral limit
  float iLimitLow;    //< integral limit
  float dt;           //< delta-time dt
} PidObject;

/**
 * PID object initialization.
 *
 * @param[out] pid   A pointer to the pid object to initialize.
 * @param[in] desired  The initial set point.
 * @param[in] kp        The proportional gain
 * @param[in] ki        The integral gain
 * @param[in] kd        The derivative gain
 */
void pidInit(PidObject* pid, const float desired, const float kp,
             const float ki, const float kd, const float dt);

/**
 * Set the integral limit for this PID in deg.
 *
 * @param[in] pid   A pointer to the pid object.
 * @param[in] limit Pid integral swing limit.
 */
void pidSetIntegralLimit(PidObject* pid, const float limit);

/**
 * Reset the PID error values
 *
 * @param[in] pid   A pointer to the pid object.
 * @param[in] limit Pid integral swing limit.
 */
void pidReset(PidObject* pid);

/**
 * Update the PID parameters.
 *
 * @param[in] pid         A pointer to the pid object.
 * @param[in] measured    The measured value
 * @param[in] updateError Set to TRUE if error should be calculated.
 *                        Set to False if pidSetError() has been used.
 * @return PID algorithm output
 */
float pidUpdate(PidObject* pid, const float measured, const unsigned char updateError);

/**
 * Set a new set point for the PID to track.
 *
 * @param[in] pid   A pointer to the pid object.
 * @param[in] angle The new set point
 */
void pidSetDesired(PidObject* pid, const float desired);

/**
 * Set a new set point for the PID to track.
 * @return The set point
 */
float pidGetDesired(PidObject* pid);

/**
 * Find out if PID is active
 * @return TRUE if active, FALSE otherwise
 */
unsigned char pidIsActive(PidObject* pid);

/**
 * Set a new error. Use if a special error calculation is needed.
 *
 * @param[in] pid   A pointer to the pid object.
 * @param[in] error The new error
 */
void pidSetError(PidObject* pid, const float error);

/**
 * Set a new proportional gain for the PID.
 *
 * @param[in] pid   A pointer to the pid object.
 * @param[in] kp    The new proportional gain
 */
void pidSetKp(PidObject* pid, const float kp);

/**
 * Set a new integral gain for the PID.
 *
 * @param[in] pid   A pointer to the pid object.
 * @param[in] ki    The new integral gain
 */
void pidSetKi(PidObject* pid, const float ki);

/**
 * Set a new derivative gain for the PID.
 *
 * @param[in] pid   A pointer to the pid object.
 * @param[in] kd    The derivative gain
 */
void pidSetKd(PidObject* pid, const float kd);

/**
 * Set a new dt gain for the PID. Defaults to IMU_UPDATE_DT upon construction
 *
 * @param[in] pid   A pointer to the pid object.
 * @param[in] dt    Delta time
 */
void pidSetDt(PidObject* pid, const float dt);
#endif /* STEERINGENGINE_28335_V3_INC_PID_H_ */
