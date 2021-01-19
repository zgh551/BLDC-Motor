/*
 * Digital_IO.h
 *
 *  Created on: 2016��6��3��
 *      Author: ZGH
 */

#ifndef STEERINGENGINE_28335_V4_INC_DIGITAL_IO_H_
#define STEERINGENGINE_28335_V4_INC_DIGITAL_IO_H_
#include "include.h"

#define POSITION_H              (0x80)
#define POSITION_L              (0x81)
#define VELOCITY_H              (0x82)
#define VELOCITY_L              (0x83)
#define LOS_THRESHOLD           (0x88)
#define DOS_OVER_THRESHOLD      (0x89)
#define DOS_MISM_THRESHOLD      (0x8A)
#define DOS_REST_MAX_THRESHOLD  (0x8B)
#define DOS_REST_MIN_THRESHOLD  (0x8C)
#define LOT_HIGH_THRESHOLD      (0x8D)
#define LOT_LOW_THRESHOLD       (0x8E)
#define EXCITATION_FREQUENCY    (0x91)
#define CONTROL                 (0x92)
#define SOFT_RESET              (0xF0)
#define FAULT                   (0xFF)

void Digital_IO_Init(void);

void Missle_Ready(Uint16 state);
void Missle_Normal(Uint16 state);
void Missle_K2(Uint16 state);

Uint16 Missle_SA(void);
Uint16 Missle_DY_Capture(void);
Uint16 Missle_Leave(void);

#endif /* STEERINGENGINE_28335_V4_INC_DIGITAL_IO_H_ */
