/*
 * Steering_SCI.h
 *
 *  Created on: 2016��3��30��
 *      Author: ZGH
 */

#ifndef STEERINGENGINE_28335_V3_INC_STEERING_SCI_H_
#define STEERINGENGINE_28335_V3_INC_STEERING_SCI_H_

#include "include.h"

void Steering_SCI_Init(void);
void Steering_Send_Byte(Uint16 byte);

void Steering_SCI_Test_Init(void);
void Steering_Send_Byte_Test(Uint16 byte);
#endif /* STEERINGENGINE_28335_V3_INC_STEERING_SCI_H_ */
