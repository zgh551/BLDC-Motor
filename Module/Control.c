/*
 * Control.c
 *
 *  Created on: 2016Äê3ÔÂ1ÈÕ
 *      Author: ZGH
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Control.h"

#define INT16_MIN	-32768
#define INT16_MAX	32767
//Fancier version
#define TRUNCATE_SINT16(out, in) (out = (in<INT16_MIN)?INT16_MIN:((in>INT16_MAX)?INT16_MAX:in) )

//Better semantic
#define SATURATE_SINT16(in) ( (in<INT16_MIN)?INT16_MIN:((in>INT16_MAX)?INT16_MAX:in) )

/**
 * Position update frequency dictates the overall update frequency.
 */
#define POSITION_UPDATE_FREQ   5000
#define POSITION_UPDATE_DT     (float)(1.0/POSITION_UPDATE_FREQ)

#define CURRENT_UPDATE_FREQ   5000
#define CURRENT_UPDATE_DT     (float)(1.0/CURRENT_UPDATE_FREQ)

PidObject PID_Position,PID_Current;
int16 PositionOutput,CurrentOutput;

void Control_Init(void)
{
	//Position Control
	pidInit(&PID_Position, 0, PID_POSITION_KP, PID_POSITION_KI, PID_POSITION_KD, POSITION_UPDATE_DT);
	pidSetIntegralLimit(&PID_Position, PID_POSITION_INTEGRATION_LIMIT);
	//Current Control
//	pidInit(&PID_Current, 0, PID_CURRENT_KP, PID_CURRENT_KI, PID_CURRENT_KD, POSITION_UPDATE_DT);
//	pidSetIntegralLimit(&PID_Current, PID_CURRENT_INTEGRATION_LIMIT);
}

/******Position function*********/
void controllerCorrectPositionPID(float PositionActual,float PositionDesired,int16 *PositionOutput)
{
	pidSetDesired(&PID_Position, PositionDesired);
	TRUNCATE_SINT16(*PositionOutput, pidUpdate(&PID_Position, PositionActual, 1));
}

//Get the position PID output
//void controllerGetActuatorPositionOutput(int16 *Position)
//{
//	*Position = PositionOutput;
//}

//void controllerCorrectCurrentPID(float CurrentActual,float CurrentDesired,int16 *CurrentOutput)
//{
//	pidSetDesired(&PID_Current, CurrentDesired);
//	TRUNCATE_SINT16(*CurrentOutput, pidUpdate(&PID_Current, CurrentActual, 1));
//}

//Get the Current PID output
//void controllerGetActuatorCurrentOutput(int16 *Current)
//{
//	*Current = CurrentOutput;
//}
