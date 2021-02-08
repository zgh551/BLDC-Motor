/*
 * ExternalInterrupt.c
 *
 *  Created on: 2021
 *      Author: Zachary
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "ExternalInterrupt.h"

__interrupt void xint1_isr(void);

void ExternalInterruptInit(void)
{

//	   EALLOW;
//	   GpioCtrlRegs.GPAMUX1.bit.GPIO12=0;
//	   GpioCtrlRegs.GPADIR.bit.GPIO12=0;
//	   EDIS;

    // ISR functions found within this file.
       EALLOW;  // This is needed to write to EALLOW protected registers
       PieVectTable.XINT1 = &xint1_isr;
       EDIS;   // This is needed to disable write to EALLOW protected registers

	// GPIO0 and GPIO1 are inputs
	   EALLOW;
	   GpioCtrlRegs.GPAMUX1.bit.GPIO12  = 0;         // GPIO
	   GpioCtrlRegs.GPADIR.bit.GPIO12   = 0;         // input
	   GpioCtrlRegs.GPAPUD.bit.GPIO12   = 0;
	   GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 2;        // Xint1 Synch to SYSCLKOUT only
	   GpioCtrlRegs.GPACTRL.bit.QUALPRD1 = 0x0F;    // Each sampling window is 510*SYSCLKOUT
	   EDIS;

	// GPIO12 is XINT1
	   EALLOW;
	   GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 12;   // Xint1 is GPIO12
	   EDIS;

	// Configure XINT1
	   XIntruptRegs.XINT1CR.bit.POLARITY = 0;      // Falling edge interrupt

	// Enable XINT1
	   XIntruptRegs.XINT1CR.bit.ENABLE = 1;        // Enable Xint1
}

__interrupt void xint1_isr(void)
{
    // Insert ISR Code here
    BLDC_Stop();
    // To receive more interrupts from this PIE group, acknowledge this interrupt
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
