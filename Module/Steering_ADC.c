/*
 * Steering_ADC.c
 *
 *  Created on: 2021
 *      Author: ZGH
 *      Version:V1.0.0
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Steering_ADC.h"

// ADC start parameters
#if (CPU_FRQ_150MHZ)     // Default - 150 MHz SYSCLKOUT
  #define ADC_MODCLK 0x3 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3)   = 25.0 MHz
  #define CPU_FRQ    150000000
#endif
#if (CPU_FRQ_100MHZ)
  #define ADC_MODCLK 0x2 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 100/(2*2)   = 25.0 MHz
#endif
#define ADC_CKPS   0x1   // ADC module clock = HSPCLK/2*ADC_CKPS   = 25.0MHz/(1*2) = 12.5MHz
#define ADC_SHCLK  0xF   // S/H width in ADC module periods                        = 16 ADC clocks
#define AVG        1000  // Average sample limit
#define ZOFFSET    0x00  // Average Zero offset
#define BUF_SIZE   4    // Sample buffer size
#define Sample_Fre 1000

//#define ADC_MaxValue	4095
//#define ADC_MinValue	200

#define ADC_MaxValue	3580
#define ADC_MinValue	0

#define Current_Max_Value	4095
#define Current_Min_Value   200

//#define Ratio_Factor
//#pragma DATA_SECTION(DMABuf1,"DMARAML4");
//extern volatile Uint16 DMABuf1[BUF_SIZE];

// Prototype statements for functions found within this file.
__interrupt void adc_isr(void);

volatile Uint16 *DMADest;
volatile Uint16 *DMASource;

//static float rate_temp = 0.0f;
//static float last_angle;
//static Uint16 first_enter;
//static Uint16 angle_rate_cnt;

//float CurrentA[500];
//float CurrentB[500];
//float CurrentC[500];
Uint16 index_count;
Uint16 update_flag;

//static float pid_output;

void Steering_ADC_Init(void)
{

// Specific clock setting for this example:
   EALLOW;
   SysCtrlRegs.HISPCP.all = ADC_MODCLK;	// HSPCLK = SYSCLKOUT / ADC_MODCLK
   EDIS;

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
   EALLOW;  // This is needed to write to EALLOW protected register
   PieVectTable.ADCINT = &adc_isr;
   EDIS;    // This is needed to disable write to EALLOW protected registers

// InitPeripherals(); // Not required for this example
   InitAdc();  // For this example, init the ADC

// Specific ADC setup for this example:
   AdcRegs.ADCTRL1.bit.ACQ_PS         = ADC_SHCLK;// 16 ADC clocks
   AdcRegs.ADCTRL3.bit.ADCCLKPS       = ADC_CKPS; // HCLK 12.5Mhz
   AdcRegs.ADCTRL1.bit.SEQ_CASC       = 0;        // 0 Non-Cascaded Mode
   AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1   = 0x1;  // Interrupt request by INT_SEQ1 is enabled.
   AdcRegs.ADCTRL2.bit.RST_SEQ1       = 0x1;  // Immediately reset sequencer to state CONV00
   AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 0x1;  // Enable SOCA from ePWM to start SEQ1

   AdcRegs.ADCCHSELSEQ1.bit.CONV00    = 0x5;  // Setup ADCINA5 as 1st SEQ1 conv.
   AdcRegs.ADCCHSELSEQ1.bit.CONV01    = 0x6;  // Setup ADCINA6 as 2nd SEQ1 conv.
   AdcRegs.ADCCHSELSEQ1.bit.CONV02    = 0x7;  // Setup ADCINA7 as 3td SEQ1 conv.
   AdcRegs.ADCCHSELSEQ1.bit.CONV03    = 0x4;  // Setup ADCINA4 as 4fr SEQ1 conv.

   AdcRegs.ADCMAXCONV.bit.MAX_CONV1   = 3;      // Set up ADC to perform 1 conversions for every SOC

//   AdcRegs.ADCREFSEL.bit.REF_SEL = 0 ;          // Internal reference selected
//   AdcRegs.ADCTRL1.bit.CONT_RUN = 0;          // Setup continuous run

//   first_enter = 0xABCD;
//   angle_rate_cnt = 0;
   update_flag = 0xABCD;
}

void Steering_ADC_EPwm(void)
{
// Assumes ePWM1 clock is already enabled in InitSysCtrl();
	EPwm1Regs.ETSEL.bit.SOCAEN  = 1;        				  // Enable SOC on A group
	EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD;     		      // Select SOC from from CTR_PRD on updown_count
	EPwm1Regs.ETPS.bit.SOCAPRD  = ET_1ST;        			  // Generate pulse on 1st event
//	EPwm1Regs.CMPA.half.CMPA    = 0x0080; // CPU_FRQ/Sample_Fre/4;	  	  // Set compare A value
//	EPwm1Regs.TBPRD             = 0xffff; //(CPU_FRQ/Sample_Fre/2 - 1); // Set period for ePWM1; CPU_FRQ/2/5000 - 1;
//	EPwm1Regs.TBCTL.bit.CTRMODE   = TB_COUNT_UP;			  // count up and start
//	EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV2;     			  // TBCLK = SYSCLK/2
//	EPwm1Regs.TBCTL.bit.CLKDIV    = TB_DIV1;
}

void Steering_ADC_Start(void)
{
   // Start SEQ1
   AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0x1;
}

void Steerint_ADC_DMA_Init(void)
{
// Initialize DMA
   DMAInitialize();

// Configure DMA Channel
//   DMADest   = &DMABuf1[0];              //Point DMA destination to the beginning of the array
//   DMASource = &AdcMirror.ADCRESULT0;    //Point DMA source to ADC result register base

   DMACH1AddrConfig(DMADest, DMASource);

   // Bsize：         每一个脉冲传递的字的个数，实际脉冲数为bsize+1
   // Srcbstep：每传递一个字后，源地址A增量
   // Desbstep：每传递一个字后，目的地址A增量
   DMACH1BurstConfig(0,1,1);

   // Tsize：每一帧的脉冲个数，脉冲递减到0时（即一帧传递完成，也是DMA传递完成），产生DMA中断。实际帧数为tsize+1
   // Srctstep：每个脉冲的最后一个字传递结束后，源地址A增量
   // Deststep：每个脉冲的最后一个字传递结束后，目的地址A增量
   DMACH1TransferConfig(3,0,0); //帧结束后，重新加载地址ַ

   // 每一帧后绕回，偏离0 all
   DMACH1WrapConfig(3, 0, 3, 0);

   DMACH1ModeConfig(DMA_SEQ1INT,PERINT_ENABLE,ONESHOT_ENABLE,CONT_ENABLE,SYNC_DISABLE,SYNC_SRC,
		 OVRFLOW_DISABLE,SIXTEEN_BIT,CHINT_END,CHINT_ENABLE);

   StartDMACH1();
}

Uint16 Position_Value_Progress(Uint16 ADC_value)
{
	Uint16 ADC_temp;
	if(ADC_value <= ADC_MinValue)
	{
		ADC_temp = ADC_MinValue;
	}
	else if(ADC_value > ADC_MaxValue)
	{
		ADC_temp =  ADC_MaxValue;
	}
	else
	{
		ADC_temp = ADC_value;
	}
	return (Uint16)((ADC_temp-ADC_MinValue)*0.25);//1000 / 3580
}

Uint16 Current_Value_Progress(Uint16 ADC_value)
{
	Uint16 ADC_temp;
	if(ADC_value <= Current_Min_Value)
	{
		ADC_temp = Current_Min_Value;
	}
	else if(ADC_value > Current_Max_Value)
	{
		ADC_temp =  Current_Max_Value;
	}
	else
	{
		ADC_temp = ADC_value;
	}
	return (Uint16)((ADC_temp-Current_Min_Value)*0.25);
}

__interrupt void  adc_isr(void)
{
    d2m_Messege.MotorDriver_IA = (int16)(AdcMirror.ADCRESULT0 - 223) * 3.32919e-3; // (adc * 3.0 / 4096)  * (15 / 3.3) [A]
    d2m_Messege.MotorDriver_IB = (int16)(AdcMirror.ADCRESULT1 - 223) * 3.32919e-3; // (adc * 3.0 / 4096)  * (15 / 3.3) [A]
    d2m_Messege.MotorDriver_IC = (int16)(AdcMirror.ADCRESULT2 - 223) * 3.32919e-3; // (adc * 3.0 / 4096)  * (15 / 3.3) [A]

    // update the voltage and current
    d2m_Messege.MotorDriverVoltage = AdcMirror.ADCRESULT3 * 0.0076171875; // adc / 4096 * 3 * 10.4



    // read the position and velocity information
    d2m_Messege.FaultState = AD2S1210_ResultRead(&d2m_Messege.AngularPosition, &d2m_Messege.AngularVelocity);

    InverseParkTransform(d2m_Messege.V_d, d2m_Messege.V_q, d2m_Messege.AngularPosition,
                         &d2m_Messege.V_alpha, &d2m_Messege.V_beta);

    d2m_Messege.ControlPhaseState = SVPWM(d2m_Messege.V_alpha, d2m_Messege.V_beta);

//    last_angle = d2m_Messege.AngularPosition;
//    BLDC_RotateTurnControl(d2m_Messege.ControlPhaseState);
    BLDC_RotateTurnControlPro(d2m_Messege.ControlPhaseState);
    // Reinitialize for next ADC sequence
    AdcRegs.ADCTRL2.bit.RST_SEQ1   = 1;         // Reset SEQ1
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE
}

// Current Translate
//    CurrentProcess(&d2m_Messege.MotorDriver_IA, &d2m_Messege.MotorDriver_IB, &d2m_Messege.MotorDriver_IC, d2m_Messege.ControlPhaseState);
//    ClarkTransform(d2m_Messege.MotorDriver_IA, d2m_Messege.MotorDriver_IB, d2m_Messege.MotorDriver_IC,
//                   &d2m_Messege.I_alpha, &d2m_Messege.I_beta);
//    ParkTransform(d2m_Messege.I_alpha, d2m_Messege.I_beta, d2m_Messege.AngularPosition,
//                  &d2m_Messege.I_d, &d2m_Messege.I_q);

//    if (update_flag == 0xABCD)
//    {
//        CurrentA[index_count] = d2m_Messege.MotorDriver_IA;
//        CurrentB[index_count] = d2m_Messege.MotorDriver_IB;
//        CurrentC[index_count] = d2m_Messege.MotorDriver_IC;
//        index_count = (index_count + 1) % 500;
//        if (index_count == 0)
//        {
//            update_flag = 0x1234;
//        }
//    }

// 位置控制
//    PositionControllerPID(m2d_Messege.TargetPosition, d2m_Messege.AngularPosition, &m2d_Messege.TargetAngleVelocity);
// 速度控制
//    SpeedControllerPID(m2d_Messege.TargetAngleVelocity, d2m_Messege.AngularVelocity, &m2d_Messege.TargetVq);//&pid_output

// 电流控制
//    CurrentD_ControllerPID(m2d_Messege.TargetVd, d2m_Messege.I_d, &d2m_Messege.V_d);
//    CurrentQ_ControllerPID(m2d_Messege.TargetVq, d2m_Messege.I_q, &d2m_Messege.V_q);

//    d2m_Messege.V_d = m2d_Messege.TargetVd;
//    d2m_Messege.V_q = m2d_Messege.TargetVq;

//    d2m_Messege.V_d = 0;
//    d2m_Messege.V_q = 6;

// 角速度计算
//    if (0xABCD == first_enter)
//    {
//        last_angle = d2m_Messege.AngularPosition;
//        d2m_Messege.AngularVelocity = 0;
//        first_enter = 0x1234;
//    }
//    else if (0x1234 == first_enter)
//    {
//        last_angle = d2m_Messege.AngularPosition;
//        d2m_Messege.AngularVelocity = 0;
//        first_enter = 0;
//    }
//    else
//    {
//        angle_rate_cnt++;
//        if (fabs(d2m_Messege.AngularPosition - last_angle) > 0.03f)
//        {
//            if (angle_rate_cnt > 0)
//            {
//                d2m_Messege.AngularVelocity = (((d2m_Messege.AngularPosition - last_angle) < -3.5f) ?  6.28f :
//                                               ((d2m_Messege.AngularPosition - last_angle) >  3.5f) ? -6.28f : 0
//                                            +   (d2m_Messege.AngularPosition - last_angle)) * 1591.54f /  angle_rate_cnt;
//                angle_rate_cnt = 0;
//
//            }
//            else
//            {
//                d2m_Messege.AngularVelocity = 0;
//            }
//        }

//        rate_temp = ((((d2m_Messege.AngularPosition - last_angle) < -5.5f) ?  6.28f :
//                      ((d2m_Messege.AngularPosition - last_angle) >  5.5f) ? -6.28f : 0)
//                  +    (d2m_Messege.AngularPosition - last_angle)) * 1591.54f;
//
//        if ((fabs(d2m_Messege.AngularVelocity - rate_temp) < 15) || (fabs(rate_temp) > 6))
//        {
//            d2m_Messege.AngularVelocity = rate_temp;
//        }


//        if (d2m_Messege.AngularVelocity < -1000)
//        {
//            d2m_Messege.AngularVelocity = 0;
//        }
//    }
