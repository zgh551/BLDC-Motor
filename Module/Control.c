/*
 * Control.c
 *
 *  Created on: 2021
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
#define POSITION_UPDATE_FREQ   10000
#define POSITION_UPDATE_DT     (float)(1.0/POSITION_UPDATE_FREQ)

#define CURRENT_UPDATE_FREQ   10000
#define CURRENT_UPDATE_DT     (float)(1.0f / CURRENT_UPDATE_FREQ)

#pragma CODE_SECTION(CurrentD_ControllerPID, "ramfuncs");
#pragma CODE_SECTION(CurrentQ_ControllerPID, "ramfuncs");
#pragma CODE_SECTION(SpeedControllerPID, "ramfuncs");
#pragma CODE_SECTION(PositionControllerPID, "ramfuncs");

#pragma DATA_SECTION(PID_Current_D, "DMARAML4");
#pragma DATA_SECTION(PID_Current_Q, "DMARAML4");
#pragma DATA_SECTION(PID_Speed, "DMARAML4");
#pragma DATA_SECTION(PID_Position, "DMARAML4");

PidObject PID_Current_Q, PID_Current_D;
PidObject PID_Speed, PID_Position;

void Control_Init(void)
{
	//Current D Control
	pidInit(&PID_Current_D, 0, PID_CURRENT_D_KP, PID_CURRENT_D_KI, PID_CURRENT_D_KD, CURRENT_UPDATE_DT);
	pidSetIntegralLimit(&PID_Current_D, PID_CURRENT_D_INTEGRATION_LIMIT);

    //Current Q Control
    pidInit(&PID_Current_Q, 0, PID_CURRENT_Q_KP, PID_CURRENT_Q_KI, PID_CURRENT_Q_KD, CURRENT_UPDATE_DT);
    pidSetIntegralLimit(&PID_Current_Q, PID_CURRENT_Q_INTEGRATION_LIMIT);

    // Speed control
    pidInit(&PID_Speed, 0, PID_SPEED_KP, PID_SPEED_KI, PID_SPEED_KD, CURRENT_UPDATE_DT);
    pidSetIntegralLimit(&PID_Speed, PID_SPEED_INTEGRATION_LIMIT);

    // Position control
    pidInit(&PID_Position, 0, PID_POSITION_KP, PID_POSITION_KI, PID_POSITION_KD, CURRENT_UPDATE_DT);
    pidSetIntegralLimit(&PID_Position, PID_POSITION_INTEGRATION_LIMIT);
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

void SpeedControllerPID(float i_desired, float i_actual, float *i_out)
{
    pidSetDesired(&PID_Speed, i_desired);
    *i_out = pidUpdate(&PID_Speed, i_actual, 1);
}

void PositionControllerPID(float i_desired, float i_actual, float *i_out)
{
    pidSetDesired(&PID_Position, i_desired);
    *i_out = pidUpdate(&PID_Position, i_actual, 1);
}

