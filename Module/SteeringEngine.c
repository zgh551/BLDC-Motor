/*
 * TeeringEngine.c
 *
 *  Created on: 2016Äê3ÔÂ4ÈÕ
 *      Author: ZGH
 *      version:V1.0.0
 */

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "SteeringEngine.h"

void ePWM_Duty(Uint16 duty)
{
//	EPwm1Regs.CMPA.half.CMPA = duty; 	// Compare A = 350 TBCLK counts
	EPwm1Regs.CMPB = duty;
}

int16 limitPosition(int16 value)
{
	if(value > 1500)
	{
		value = 1500;
	}
	else if(value < -1499)
	{
		value = -1499;
	}
	return value;
}

void SteeringPowerOutput(int16 PositionPIDOutput)
{
	if(PositionPIDOutput < 0)
	{
		ePWM_Duty(1499 + limitPosition(PositionPIDOutput));
	}
	else if(0 == PositionPIDOutput)
	{
		ePWM_Duty(1499);
	}
	else
	{
		ePWM_Duty(1499 + limitPosition(PositionPIDOutput));
	}
}
