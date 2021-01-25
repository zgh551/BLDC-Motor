/*
 * Steering_Xintf.c
 *
 *  Created on: 2016��3��30��
 *      Author: ZGH
 */

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
// User Header File
#include "Steering_XINTF.h"

void Init_Zone(void)
{
    // Configure the GPIO for XINTF with a 16-bit data bus
    // This function is in DSP2833x_Xintf.c
    InitXintf16Gpio();

    EALLOW;
    // All Zones---------------------------------
    // Timing for all zones based on XTIMCLK = SYSCLKOUT
    XintfRegs.XINTCNF2.bit.XTIMCLK = 1;
    // Buffer up to 3 writes
    XintfRegs.XINTCNF2.bit.WRBUFF  = 3;
    // XCLKOUT is disabled
    XintfRegs.XINTCNF2.bit.CLKOFF  = 1;
    // XCLKOUT = XTIMCLK
    XintfRegs.XINTCNF2.bit.CLKMODE = 1;
    // Disable XHOLD to prevent XINTF bus from going into high impedance state
    // whenever TZ3 signal goes low. This occurs because TZ3 on GPIO14 is
    // shared with HOLD of XINTF
    XintfRegs.XINTCNF2.bit.HOLD    = 1;

    // Zone 7------------------------------------
    // When using ready, ACTIVE must be 1 or greater
    // Lead must always be 1 or greater
    // Zone write timing
    XintfRegs.XTIMING7.bit.XWRLEAD   = 3;
    XintfRegs.XTIMING7.bit.XWRACTIVE = 7;
    XintfRegs.XTIMING7.bit.XWRTRAIL  = 3;
    // Zone read timing
    XintfRegs.XTIMING7.bit.XRDLEAD   = 3;
    XintfRegs.XTIMING7.bit.XRDACTIVE = 7;
    XintfRegs.XTIMING7.bit.XRDTRAIL  = 3;

    // don't double all Zone read/write lead/active/trail timing
    XintfRegs.XTIMING7.bit.X2TIMING  = 1;

    // Zone will not sample XREADY signal
    XintfRegs.XTIMING7.bit.USEREADY  = 0;
    XintfRegs.XTIMING7.bit.READYMODE = 0;

    // 1,1 = x16 data bus
    // 0,1 = x32 data bus
    // other values are reserved
    XintfRegs.XTIMING7.bit.XSIZE = 3;

    // Zone 6------------------------------------
	// When using ready, ACTIVE must be 1 or greater
	// Lead must always be 1 or greater
	// Zone write timing
	XintfRegs.XTIMING6.bit.XWRLEAD   = 3;
	XintfRegs.XTIMING6.bit.XWRACTIVE = 7;
	XintfRegs.XTIMING6.bit.XWRTRAIL  = 3;
	// Zone read timing
	XintfRegs.XTIMING6.bit.XRDLEAD   = 3;
	XintfRegs.XTIMING6.bit.XRDACTIVE = 7;
	XintfRegs.XTIMING6.bit.XRDTRAIL  = 3;

	// don't double all Zone read/write lead/active/trail timing
	XintfRegs.XTIMING6.bit.X2TIMING  = 1;

	// Zone will not sample XREADY signal
	XintfRegs.XTIMING6.bit.USEREADY  = 0;
	XintfRegs.XTIMING6.bit.READYMODE = 0;

	// 1,1 = x16 data bus
	// 0,1 = x32 data bus
	// other values are reserved
	XintfRegs.XTIMING6.bit.XSIZE = 3;

    // Bank switching
    // Assume Zone 7 is slow, so add additional BCYC cycles
    // when ever switching from Zone 7 to another Zone.
    // This will help avoid bus contention.
    XintfRegs.XBANK.bit.BANK = 7;
    XintfRegs.XBANK.bit.BCYC = 7;

    EDIS;

   //Force a pipeline flush to ensure that the write to
   //the last register configured occurs before returning.
   __asm(" RPT #7 || NOP");
}
