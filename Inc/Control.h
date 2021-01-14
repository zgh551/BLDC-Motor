/*
 * Control.h
 *
 *  Created on: 2016Äê3ÔÂ1ÈÕ
 *      Author: ZGH
 */

#ifndef STEERINGENGINE_28335_V3_INC_CONTROL_H_
#define STEERINGENGINE_28335_V3_INC_CONTROL_H_

#include "include.h"

void Control_Init(void);
void controllerCorrectPositionPID(float PositionActual,float PositionDesired,int16 *PositionOutput);
//void controllerGetActuatorPositionOutput(int16 *Position);

void controllerCorrectCurrentPID(float CurrentActual,float CurrentDesired,int16 *CurrentOutput);
//void controllerGetActuatorCurrentOutput(int16 *Current);

#endif /* STEERINGENGINE_28335_V3_INC_CONTROL_H_ */
