/*
 * SteeringEngine.h
 *
 *  Created on: 2016Äê3ÔÂ4ÈÕ
 *      Author: ZGH
 */

#ifndef STEERINGENGINE_28335_V3_INC_STEERINGENGINE_H_
#define STEERINGENGINE_28335_V3_INC_STEERINGENGINE_H_

#include "include.h"

void ePWM_Duty(Uint16 duty);
int16 limitPosition(int16 value);
void SteeringPowerOutput(int16 PositionPIDOutput);

#endif /* STEERINGENGINE_28335_V3_INC_STEERINGENGINE_H_ */
