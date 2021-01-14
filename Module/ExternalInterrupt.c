/*
 * ExternalInterrupt.c
 *
 *  Created on: 2016Äê4ÔÂ20ÈÕ
 *      Author: ZGH
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "ExternalInterrupt.h"

void Steering_External_Interrupt(void)
{

	   EALLOW;
	   GpioCtrlRegs.GPBMUX2.bit.GPIO60=0;
	   GpioCtrlRegs.GPBMUX2.bit.GPIO61=0;
	   GpioCtrlRegs.GPBMUX2.bit.GPIO62=0;

	   GpioCtrlRegs.GPBDIR.bit.GPIO60=0;
	   GpioCtrlRegs.GPBDIR.bit.GPIO61=0;
	   GpioCtrlRegs.GPBDIR.bit.GPIO62=0;
	   EDIS;

	// GPIO0 and GPIO1 are inputs
	   EALLOW;
	   GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 0;         // GPIO
	   GpioCtrlRegs.GPBDIR.bit.GPIO63= 0;           // input
	   GpioCtrlRegs.GPBQSEL2.bit.GPIO63 = 0;        // Xint1 Synch to SYSCLKOUT only
	   GpioCtrlRegs.GPBCTRL.bit.QUALPRD3 = 0x00;   // Each sampling window is 510*SYSCLKOUT
	   EDIS;

	// GPIO63 is XINT3
	   EALLOW;
	   GpioIntRegs.GPIOXINT3SEL.bit.GPIOSEL = 31;   // Xint3 is GPIO63
	   EDIS;

	// Configure XINT1
	   XIntruptRegs.XINT3CR.bit.POLARITY = 1;      // Rising edge interrupt

	// Enable XINT3
	   XIntruptRegs.XINT3CR.bit.ENABLE = 1;        // Enable Xint3
}
