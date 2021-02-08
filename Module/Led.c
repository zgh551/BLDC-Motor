/*
 * Led.c
 *
 *  Created on: 2021
 *      Author: ZGH
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Led.h"

void LedInit(void)
{
	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO9  = 1;

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO10  = 1;

    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO11  = 1;
	EDIS;
}


void LedRunning(void)
{
	GpioDataRegs.GPATOGGLE.bit.GPIO10 = 1;
}

void LedErr(void)
{
    GpioDataRegs.GPATOGGLE.bit.GPIO11 = 1;
}

void LedTx(void)
{
    GpioDataRegs.GPATOGGLE.bit.GPIO9 = 1;
}
