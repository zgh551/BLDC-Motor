/*
 * Control.h
 *
 *  Created on: 2016��3��1��
 *      Author: ZGH
 */

#ifndef STEERINGENGINE_28335_V3_INC_CONTROL_H_
#define STEERINGENGINE_28335_V3_INC_CONTROL_H_

#include "include.h"

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

#endif /* STEERINGENGINE_28335_V3_INC_CONTROL_H_ */
