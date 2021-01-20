/*
 * Digital_IO.c
 *
 *  Created on: 2016��6��3��
 *      Author: ZGH
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Digital_IO.h"

void AD2S1210_IO_Init(void)
{
	EALLOW;
    GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO48  = 1;//Sample low valid
    GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO49  = 1;//res0
    GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO50  = 1;//res1
	GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO51  = 1;//A0
    GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO52  = 1;//A1
    GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO55  = 1;//Reset
	EDIS;
}

void AD2S1210_Sample(Uint16 state)
{
    GpioDataRegs.GPBDAT.bit.GPIO48 = state;
}

void AD2S1210_Res0(Uint16 state)
{
    GpioDataRegs.GPBDAT.bit.GPIO49 = state;
}

void AD2S1210_Res1(Uint16 state)
{
    GpioDataRegs.GPBDAT.bit.GPIO50 = state;
}

void AD2S1210_Mode_A0(Uint16 state)
{
	GpioDataRegs.GPBDAT.bit.GPIO51 = state;
}

void AD2S1210_Mode_A1(Uint16 state)
{
	GpioDataRegs.GPBDAT.bit.GPIO52 = state;
}

void AD2S1210_Reset(Uint16 state)
{
    GpioDataRegs.GPBDAT.bit.GPIO55 = state;
}


void AD2S1210_Init(void)
{
    AD2S1210_IO_Init();
    AD2S1210_Res0(0);
    AD2S1210_Res1(1);

    AD2S1210_Reset(0);
    DELAY_US(1000);
    AD2S1210_Reset(1);
}

void AD2S1210_ConfigModeWrite(Uint16 add, Uint16 dat)
{
    AD2S1210_Mode_A0(1);
    AD2S1210_Mode_A1(1);
    DELAY_US(10);
	*(Uint16*)(0x200000) = add;
    DELAY_US(100);
	*(Uint16*)(0x200000) = dat;
}

Uint16 AD2S1210_ConfigModeRead(Uint16 add)
{
    AD2S1210_Mode_A0(1);
    AD2S1210_Mode_A1(1);
    DELAY_US(10);
    *(Uint16*)(0x200001) = add;
    DELAY_US(1);
    return *(Uint16*)(0x200001);
}

void AD2S1210_DataRead(Uint16* pos, Uint16* vel, Uint16* fault)
{
    AD2S1210_Sample(0);
    DELAY_US(10);
    AD2S1210_Sample(1);

    AD2S1210_Mode_A0(0);
    AD2S1210_Mode_A1(0);
    DELAY_US(10);
    *pos = *(Uint16*)(0x200000);
    DELAY_US(50);
    AD2S1210_Mode_A0(0);
    AD2S1210_Mode_A1(1);
    DELAY_US(10);
    *vel = *(Uint16*)(0x200000);
}
