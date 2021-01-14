/*
 * Digital_IO.c
 *
 *  Created on: 2016Äê6ÔÂ3ÈÕ
 *      Author: ZGH
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Digital_IO.h"
void Digital_IO_Init(void)
{
	EALLOW;
	GpioCtrlRegs.GPBMUX2.bit.GPIO50=0;
	GpioCtrlRegs.GPBDIR.bit.GPIO50 =1;//Missle Ready Sigle
	GpioCtrlRegs.GPBMUX2.bit.GPIO51=0;
	GpioCtrlRegs.GPBDIR.bit.GPIO51 =1;//Missle Normal Sigle
	EDIS;
}

void Missle_Ready(Uint16 state)
{
	GpioDataRegs.GPBDAT.bit.GPIO50 = state;
}

void Missle_Normal(Uint16 state)
{
	GpioDataRegs.GPBDAT.bit.GPIO51 = state;
}

void Missle_K2(Uint16 state)
{
	*(Uint16*)(0x100006) = state;
}


Uint16 Missle_SA(void)
{
	Uint16 temp;
	temp = *(Uint16*)(0x100006);
	return (temp>>2)&0x0001;
}

Uint16 Missle_DY_Capture(void)
{
	Uint16 temp;
	temp = *(Uint16*)(0x100006);
	return (temp>>1)&0x0001;
}

Uint16 Missle_Leave(void)
{
	Uint16 temp;
	temp = *(Uint16*)(0x100006);
	return (temp)&0x0001;
}
