/*
 * Control.c
 *
 *  Created on: 2016��3��1��
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

#define CURRENT_UPDATE_FREQ   10000
#define CURRENT_UPDATE_DT     (float)(1.0f / CURRENT_UPDATE_FREQ)

#pragma CODE_SECTION(CurrentD_ControllerPID, "ramfuncs");
#pragma CODE_SECTION(CurrentQ_ControllerPID, "ramfuncs");

#pragma DATA_SECTION(PID_Current_D, "DMARAML4");
#pragma DATA_SECTION(PID_Current_Q, "DMARAML4");

PidObject PID_Current_Q, PID_Current_D;

void Control_Init(void)
{
	//Current D Control
	pidInit(&PID_Current_D, 0, PID_CURRENT_D_KP, PID_CURRENT_D_KI, PID_CURRENT_D_KD, CURRENT_UPDATE_DT);
	pidSetIntegralLimit(&PID_Current_D, PID_CURRENT_D_INTEGRATION_LIMIT);

    //Current Q Control
    pidInit(&PID_Current_Q, 0, PID_CURRENT_Q_KP, PID_CURRENT_Q_KI, PID_CURRENT_Q_KD, CURRENT_UPDATE_DT);
    pidSetIntegralLimit(&PID_Current_Q, PID_CURRENT_Q_INTEGRATION_LIMIT);
}

/******Position function*********/
void CurrentD_ControllerPID(float i_desired, float i_actual, float *i_out)
{
	pidSetDesired(&PID_Current_D, i_desired);
	*i_out = pidUpdate(&PID_Current_D, i_actual, 1);
}

void CurrentQ_ControllerPID(float i_desired, float i_actual, float *i_out)
{
    pidSetDesired(&PID_Current_Q, i_desired);
    *i_out = pidUpdate(&PID_Current_Q, i_actual, 1);
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
