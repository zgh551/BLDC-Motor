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
	GpioCtrlRegs.GPBMUX2.bit.GPIO56=0;
	GpioCtrlRegs.GPBDIR.bit.GPIO56 =1;

    GpioCtrlRegs.GPBMUX2.bit.GPIO57=0;
    GpioCtrlRegs.GPBDIR.bit.GPIO57 =1;

//    GpioCtrlRegs.GPAMUX2.bit.GPIO17=0;
//    GpioCtrlRegs.GPADIR.bit.GPIO17 =1;
	EDIS;
}


void LedRunning(void)
{
	GpioDataRegs.GPBTOGGLE.bit.GPIO56=1;
}

void LedErr(void)
{
    GpioDataRegs.GPBTOGGLE.bit.GPIO57=1;
}

//void LedTx(void)
//{
//    GpioDataRegs.GPATOGGLE.bit.GPIO17=1;
//}
