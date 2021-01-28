/*
 * SteeringEngine.h
 *
 *  Created on: 2016��3��4��
 *      Author: ZGH
 */

#ifndef STEERINGENGINE_28335_V3_INC_STEERINGENGINE_H_
#define STEERINGENGINE_28335_V3_INC_STEERINGENGINE_H_

#include "include.h"

void BLDC_IO_Init(void);

void InitEPwmBLDC(void);

void BLDC_ShutDown(Uint16 state);

void ePWM1_LowLevelDutyTime(float time); // us

void ePWM2_LowLevelDutyTime(float time); // us

void ePWM3_LowLevelDutyTime(float time); // us

void BLDC_Start();

void BLDC_Stop();

#endif /* STEERINGENGINE_28335_V3_INC_STEERINGENGINE_H_ */
