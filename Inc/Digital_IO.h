/*
 * Digital_IO.h
 *
 *  Created on: 2016Äê6ÔÂ3ÈÕ
 *      Author: ZGH
 */

#ifndef STEERINGENGINE_28335_V4_INC_DIGITAL_IO_H_
#define STEERINGENGINE_28335_V4_INC_DIGITAL_IO_H_
#include "include.h"

void Digital_IO_Init(void);

void Missle_Ready(Uint16 state);
void Missle_Normal(Uint16 state);
void Missle_K2(Uint16 state);

Uint16 Missle_SA(void);
Uint16 Missle_DY_Capture(void);
Uint16 Missle_Leave(void);

#endif /* STEERINGENGINE_28335_V4_INC_DIGITAL_IO_H_ */
