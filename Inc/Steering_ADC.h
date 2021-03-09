/*
 * Steering_ADC.h
 *
 *  Created on: 2021
 *      Author: ZGH
 */

#ifndef _INC_STEERING_ADC_H_
#define _STEERING_ADC_H_

#include "include.h"

void Steering_ADC_Init(void);
void Steering_ADC_EPwm(void);
void Steering_ADC_Start(void);
void Steerint_ADC_DMA_Init(void);
Uint16 Position_Value_Progress(Uint16 ADC_value);
Uint16 Current_Value_Progress(Uint16 ADC_value);
#endif /* STEERINGENGINE_28335_V3_INC_STEERING_ADC_H_ */
