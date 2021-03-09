/*
 * TeeringEngine.c
 *
 *  Created on: 2021
 *      Author: ZGH
 *      version:V1.0.0
 */

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "SteeringEngine.h"

#define CPU_FRQ_OUT     (150000000) // TBCLK = SYSCLKOUT
#define FREQUENCY_PWM   (10000)     // PWM_Frequency
#define PWM_COUNT       (7500)     // TBCLK / PWM_Frequency / 2  [ the preiod = 100 us -> 1us(150 count) ]


void BLDC_IO_Init(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO17  = 1;//Shunt down low valid
    EDIS;
}

void BLDC_ShutDown(Uint16 state)
{
    GpioDataRegs.GPADAT.bit.GPIO17 = state;
}

void InitEPwmBLDC(void)
{
   // Initialize ePWM1/2/3/4/5/6 GPIO
    InitEPwmGpio();

    //=====================================================================
    // Config
    // Initialization Time
    //========================
    // EPWM Module 1 config
    EPwm1Regs.TBPRD                 = PWM_COUNT;         // Period = 900 TBCLK counts
    EPwm1Regs.TBPHS.half.TBPHS      = 0;                // Set Phase register to zero
    EPwm1Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV1;          // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV      = TB_DIV1;
    EPwm1Regs.TBCTL.bit.CTRMODE     = TB_COUNT_UPDOWN;  // Symmetrical mode
    EPwm1Regs.TBCTL.bit.PHSEN       = TB_DISABLE;       // Master module
    EPwm1Regs.TBCTL.bit.PRDLD       = TB_SHADOW;
    EPwm1Regs.TBCTL.bit.SYNCOSEL    = TB_CTR_ZERO;      // Sync down-stream module
    EPwm1Regs.CMPCTL.bit.SHDWAMODE  = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE  = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;      // load on CTR=Zero
    EPwm1Regs.CMPCTL.bit.LOADBMODE  = CC_CTR_ZERO;      // load on CTR=Zero
    EPwm1Regs.AQCTLA.bit.CAU        = AQ_SET;           // set actions for EPWM1A
    EPwm1Regs.AQCTLA.bit.CAD        = AQ_CLEAR;         // clear actions for EPWM1A
    EPwm1Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;   // enable Dead-band module
    EPwm1Regs.DBCTL.bit.POLSEL      = DB_ACTV_HIC;      // Active Hi complementary
    EPwm1Regs.DBFED                 = 50;               // FED = 50 TBCLKs
    EPwm1Regs.DBRED                 = 50;               // RED = 50 TBCLKs

    // EPWM Module 2 config
    EPwm2Regs.TBPRD                 = PWM_COUNT;        // Period = 900 TBCLK counts
    EPwm2Regs.TBPHS.half.TBPHS      = 0;                // Set Phase register to zero
    EPwm2Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV1;          // Clock ratio to SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV      = TB_DIV1;
    EPwm2Regs.TBCTL.bit.CTRMODE     = TB_COUNT_UPDOWN;  // Symmetrical mode
    EPwm2Regs.TBCTL.bit.PHSEN       = TB_ENABLE;        // Slave module
    EPwm2Regs.TBCTL.bit.PRDLD       = TB_SHADOW;
    EPwm2Regs.TBCTL.bit.SYNCOSEL    = TB_SYNC_IN;       // sync flow-through
    EPwm2Regs.CMPCTL.bit.SHDWAMODE  = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE  = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;      // load on CTR=Zero
    EPwm2Regs.CMPCTL.bit.LOADBMODE  = CC_CTR_ZERO;      // load on CTR=Zero
    EPwm2Regs.AQCTLA.bit.CAU        = AQ_SET;           // set actions for EPWM2A
    EPwm2Regs.AQCTLA.bit.CAD        = AQ_CLEAR;         // clear actions for EPWM2A
    EPwm2Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;   // enable Dead-band module
    EPwm2Regs.DBCTL.bit.POLSEL      = DB_ACTV_HIC;      // Active Hi Complementary
    EPwm2Regs.DBFED                 = 50;               // FED = 50 TBCLKs
    EPwm2Regs.DBRED                 = 50;               // RED = 50 TBCLKs

    // EPWM Module 3 config
    EPwm3Regs.TBPRD                 = PWM_COUNT;        // Period = 900 TBCLK counts
    EPwm3Regs.TBPHS.half.TBPHS      = 0;                // Phase = 0 deg
    EPwm3Regs.TBCTL.bit.HSPCLKDIV   = TB_DIV1;          // Clock ratio to SYSCLKOUT
    EPwm3Regs.TBCTL.bit.CLKDIV      = TB_DIV1;
    EPwm3Regs.TBCTL.bit.CTRMODE     = TB_COUNT_UPDOWN;  // Symmetrical mode
    EPwm3Regs.TBCTL.bit.PHSEN       = TB_ENABLE;        // Slave module
    EPwm3Regs.TBCTL.bit.PRDLD       = TB_SHADOW;
    EPwm3Regs.TBCTL.bit.SYNCOSEL    = TB_SYNC_IN;       // sync flow-through
    EPwm3Regs.CMPCTL.bit.SHDWAMODE  = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.SHDWBMODE  = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE  = CC_CTR_ZERO;      // load on CTR=Zero
    EPwm3Regs.CMPCTL.bit.LOADBMODE  = CC_CTR_ZERO;      // load on CTR=Zero
    EPwm3Regs.AQCTLA.bit.CAU        = AQ_SET;           // set actions for EPWM3A
    EPwm3Regs.AQCTLA.bit.CAD        = AQ_CLEAR;         // clear actions for EPWM3A
    EPwm3Regs.DBCTL.bit.OUT_MODE    = DB_FULL_ENABLE;   // enable Dead-band module
    EPwm3Regs.DBCTL.bit.POLSEL      = DB_ACTV_HIC;      // Active Hi complementary
    EPwm3Regs.DBFED                 = 50;               // FED = 50 TBCLKs
    EPwm3Regs.DBRED                 = 50;               // RED = 50 TBCLKs

    // Run Time (Note: Example execution of one run-time instant)
    //===========================================================
    EPwm1Regs.CMPA.half.CMPA        = PWM_COUNT;        // adjust duty for output EPWM1A
    EPwm2Regs.CMPA.half.CMPA        = PWM_COUNT;        // adjust duty for output EPWM2A
    EPwm3Regs.CMPA.half.CMPA        = PWM_COUNT;        // adjust duty for output EPWM3A

    BLDC_ShutDown(0);// stop
}

void ePWM1_LowLevelDutyTime(float time) // us
{
    EPwm1Regs.CMPA.half.CMPA = (Uint16)(time * 75); // adjust duty for output EPWM1A
}

void ePWM2_LowLevelDutyTime(float time) // us
{
    EPwm2Regs.CMPA.half.CMPA = (Uint16)(time * 75); // adjust duty for output EPWM1A
}

void ePWM3_LowLevelDutyTime(float time) // us
{
    EPwm3Regs.CMPA.half.CMPA = (Uint16)(time * 75); // adjust duty for output EPWM1A
}


void BLDC_Start()
{
    BLDC_ShutDown(1);
}

void BLDC_Stop()
{
    BLDC_ShutDown(0);
}
