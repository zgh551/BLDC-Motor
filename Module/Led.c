/*
 * Led.c
 *
 *  Created on: 2016Äê4ÔÂ24ÈÕ
 *      Author: ZGH
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Led.h"

void Led_Init(void)
{
	EALLOW;
	GpioCtrlRegs.GPBMUX2.bit.GPIO59=0;
	GpioCtrlRegs.GPBDIR.bit.GPIO59 =1;
	EDIS;
}


void Led_Toggle(void)
{
	GpioDataRegs.GPBTOGGLE.bit.GPIO59=1;
}
