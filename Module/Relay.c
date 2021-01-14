/*
 * Relay.c
 *
 *  Created on: 2016Äê4ÔÂ24ÈÕ
 *      Author: ZGH
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Relay.h"

void Realy_Init(void)
{
	EALLOW;

	GpioDataRegs.GPBCLEAR.bit.GPIO52=1;
	GpioDataRegs.GPBCLEAR.bit.GPIO53=1;

	GpioCtrlRegs.GPBMUX2.bit.GPIO52=0;
	GpioCtrlRegs.GPBDIR.bit.GPIO52=1;

	GpioCtrlRegs.GPBMUX2.bit.GPIO53=0;
	GpioCtrlRegs.GPBDIR.bit.GPIO53=1;

   EDIS;
}


void Fire_Ready_ON(void)
{
	GpioDataRegs.GPBSET.bit.GPIO52=1;
}

void Fire_Ready_OFF(void)
{
	GpioDataRegs.GPBCLEAR.bit.GPIO52=1;
}


void Fire_ON(void)
{
	GpioDataRegs.GPBSET.bit.GPIO53=1;
}

void Fire_OFF(void)
{
	GpioDataRegs.GPBCLEAR.bit.GPIO53=1;
}
