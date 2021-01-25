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

void AD2S1210_IO_Init(void);

void AD2S1210_Sample(Uint16 state);
void AD2S1210_Res0(Uint16 state);
void AD2S1210_Res1(Uint16 state);
void AD2S1210_Reset(Uint16 state);

Uint16 AD2S1210_Dos(void);
Uint16 AD2S1210_Lot(void);
Uint16 AD2S1210_Dir(void);

void AD2S1210_SampleUpdate(void);

void AD2S1210_Init(void);

void AD2S1210_ConfigModeWrite(Uint16 add, Uint16 dat);

Uint16 AD2S1210_ConfigModeRead(Uint16 add);

Uint16 AD2S1210_DataRead(Uint16* pos, Uint16* vel);

Uint16 AD2S1210_ResultRead(float* pos, float* vel);
#endif /* STEERINGENGINE_28335_V4_INC_DIGITAL_IO_H_ */
