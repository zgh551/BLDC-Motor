/*
 * Steering_ADC.c
 *
 *  Created on: 2016年3月3日
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
#define ADC_SHCLK  0xf   // S/H width in ADC module periods                        = 16 ADC clocks
#define AVG        1000  // Average sample limit
#define ZOFFSET    0x00  // Average Zero offset
#define BUF_SIZE   5    // Sample buffer size
#define Sample_Fre 5000

//#define ADC_MaxValue	4095
//#define ADC_MinValue	200

#define ADC_MaxValue	3580
#define ADC_MinValue	0

#define Current_Max_Value	4095
#define Current_Min_Value   200

//#define Ratio_Factor
//#pragma DATA_SECTION(DMABuf1,"DMARAML4");
extern volatile Uint16 DMABuf1[BUF_SIZE];


volatile Uint16 *DMADest;
volatile Uint16 *DMASource;

void Steering_ADC_Init(void)
{
// InitPeripherals(); // Not required for this example
   InitAdc();  // For this example, init the ADC
// Specific clock setting for this example:
   EALLOW;
   SysCtrlRegs.HISPCP.all = ADC_MODCLK;	// HSPCLK = SYSCLKOUT/ADC_MODCLK
   EDIS;

// Specific ADC setup for this example:
   AdcRegs.ADCTRL1.bit.ACQ_PS         = ADC_SHCLK;// 采样保持周期
   AdcRegs.ADCTRL3.bit.ADCCLKPS       = ADC_CKPS; // HCLK时钟分频
   AdcRegs.ADCTRL1.bit.SEQ_CASC       = 0;        // 0 Non-Cascaded Mode 不级联
   AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1   = 0x1;  // Interrupt request by INT_SEQ1 is enabled.
   AdcRegs.ADCTRL2.bit.RST_SEQ1       = 0x1;  // Immediately reset sequencer to state CONV00
   AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 0x1; // Enable SOCA from ePWM to start SEQ1
   AdcRegs.ADCCHSELSEQ1.bit.CONV00    = 0x0;  // Setup ADCINA0 as 1st SEQ1 conv.
   AdcRegs.ADCCHSELSEQ1.bit.CONV01    = 0x1;  // Setup ADCINA1 as 2nd SEQ1 conv.
   AdcRegs.ADCMAXCONV.bit.MAX_CONV1   = 1;   // Set up ADC to perform 1 conversions for every SOC

//   AdcRegs.ADCTRL1.bit.CONT_RUN = 0;       // Setup continuous run
}

void Steering_ADC_EPwm(void)
{
// Assumes ePWM1 clock is already enabled in InitSysCtrl();
	EPwm2Regs.ETSEL.bit.SOCAEN  = 1;        				  // Enable SOC on A group
	EPwm2Regs.ETSEL.bit.SOCASEL = ET_CTRU_CMPA;     		  // Select SOC from from CPMA on upcount
	EPwm2Regs.ETPS.bit.SOCAPRD  = ET_1ST;        			  // Generate pulse on 1st event
	EPwm2Regs.CMPA.half.CMPA    =  CPU_FRQ/Sample_Fre/4;	  	  // Set compare A value
	EPwm2Regs.TBPRD             = (CPU_FRQ/Sample_Fre/2 - 1); // Set period for ePWM1; CPU_FRQ/2/5000 - 1;
	EPwm2Regs.TBCTL.bit.CTRMODE   = TB_COUNT_UP;			  // count up and start
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV2;     			  // TBCLK = SYSCLK/2
	EPwm2Regs.TBCTL.bit.CLKDIV    = TB_DIV1;
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
   DMADest   = &DMABuf1[0];              //Point DMA destination to the beginning of the array
   DMASource = &AdcMirror.ADCRESULT0;    //Point DMA source to ADC result register base

   DMACH1AddrConfig(DMADest,DMASource);

// 脉冲结束
// Bsize：         每一个脉冲传递的字的个数，实际脉冲数为bsize+1
// Srcbstep：每传递一个字后，源地址A增量
// Desbstep：每传递一个字后，目的地址A增量
   DMACH1BurstConfig(0,0,1);

// 帧结束
// Tsize：每一帧的脉冲个数，脉冲递减到0时（即一帧传递完成，也是DMA传递完成），产生DMA中断。实际帧数为tsize+1
// Srctstep：每个脉冲的最后一个字传递结束后，源地址A增量
// Deststep：每个脉冲的最后一个字传递结束后，目的地址A增量
   DMACH1TransferConfig(4,0,1);//帧结束后，重新加载地址

// 脉冲循环
// Srcwsize：当已经传递的脉冲数为srcwsize+1的整数倍时，源地址（B）增加srcwstep（常为0），并装载入源地址A
// Deswsize：当已经传递的脉冲数为deswsize+1的整数倍时，目的地址（B）增加deswstep（常为0），并装载入目的地址A
   DMACH1WrapConfig(0xFFFF,0,0xFFFF,0);

// 工作模式配置
// Persel：选择触发DMA的外设中断源
// Perinte：外设中断使能，
// Oneshot：使能时，外设产生一次中断，就能够把一帧传递完。禁止，外设产生一次中断，只能传递一个脉冲
// Cont：使能时，每次DMA结束后，需要再次启动DMA时，就不需要调用void StartDMACH1(void)。禁止时，重启DMA，需要调用void StartDMACH1(void)
// Datasize:设置每个字是16位或者32位
// Chintmode：设置DMA中断是在DMA启动或者结束时产生
// Chinte：DMA相应通道的中断使能（外设级）。
// 注：Perinte和Chinte同时使能时，才能进入DMA通道中断
// 仅Perinte使能，可以传输数据，但是不进入通道的中断程序
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
