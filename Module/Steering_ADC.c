/*
 * Steering_ADC.c
 *
 *  Created on: 2016��3��3��
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
   AdcRegs.ADCTRL1.bit.ACQ_PS         = ADC_SHCLK;// ������������
   AdcRegs.ADCTRL3.bit.ADCCLKPS       = ADC_CKPS; // HCLKʱ�ӷ�Ƶ
   AdcRegs.ADCTRL1.bit.SEQ_CASC       = 0;        // 0 Non-Cascaded Mode ������
   AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1   = 0x1;  // Interrupt request by INT_SEQ1 is enabled.
   AdcRegs.ADCTRL2.bit.RST_SEQ1       = 0x1;  // Immediately reset sequencer to state CONV00
   AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 0x1; // Enable SOCA from ePWM to start SEQ1
   AdcRegs.ADCCHSELSEQ1.bit.CONV00    = 0x0;  // Setup ADCINA0 as 1st SEQ1 conv.
   AdcRegs.ADCCHSELSEQ1.bit.CONV01    = 0x1;  // Setup ADCINA1 as 2nd SEQ1 conv.

   AdcRegs.ADCCHSELSEQ2.bit.CONV04    = 0x0;  // Setup ADCINA4 as 1st SEQ2 conv.
   AdcRegs.ADCCHSELSEQ2.bit.CONV05    = 0x1;  // Setup ADCINA5 as 2nd SEQ2 conv.
   AdcRegs.ADCCHSELSEQ2.bit.CONV06    = 0x2;  // Setup ADCINA6 as 3td SEQ2 conv.
   AdcRegs.ADCCHSELSEQ2.bit.CONV07    = 0x3;  // Setup ADCINA7 as 4fr SEQ2 conv.

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

// �������
// Bsize��         ÿһ�����崫�ݵ��ֵĸ�����ʵ��������Ϊbsize+1
// Srcbstep��ÿ����һ���ֺ�Դ��ַA����
// Desbstep��ÿ����һ���ֺ�Ŀ�ĵ�ַA����
   DMACH1BurstConfig(0,0,1);

// ֡����
// Tsize��ÿһ֡���������������ݼ���0ʱ����һ֡������ɣ�Ҳ��DMA������ɣ�������DMA�жϡ�ʵ��֡��Ϊtsize+1
// Srctstep��ÿ����������һ���ִ��ݽ�����Դ��ַA����
// Deststep��ÿ����������һ���ִ��ݽ�����Ŀ�ĵ�ַA����
   DMACH1TransferConfig(4,0,1);//֡���������¼��ص�ַ

// ����ѭ��
// Srcwsize�����Ѿ����ݵ�������Ϊsrcwsize+1��������ʱ��Դ��ַ��B������srcwstep����Ϊ0������װ����Դ��ַA
// Deswsize�����Ѿ����ݵ�������Ϊdeswsize+1��������ʱ��Ŀ�ĵ�ַ��B������deswstep����Ϊ0������װ����Ŀ�ĵ�ַA
   DMACH1WrapConfig(0xFFFF,0,0xFFFF,0);

// ����ģʽ����
// Persel��ѡ�񴥷�DMA�������ж�Դ
// Perinte�������ж�ʹ�ܣ�
// Oneshot��ʹ��ʱ���������һ���жϣ����ܹ���һ֡�����ꡣ��ֹ���������һ���жϣ�ֻ�ܴ���һ������
// Cont��ʹ��ʱ��ÿ��DMA��������Ҫ�ٴ�����DMAʱ���Ͳ���Ҫ����void StartDMACH1(void)����ֹʱ������DMA����Ҫ����void StartDMACH1(void)
// Datasize:����ÿ������16λ����32λ
// Chintmode������DMA�ж�����DMA�������߽���ʱ����
// Chinte��DMA��Ӧͨ�����ж�ʹ�ܣ����輶����
// ע��Perinte��Chinteͬʱʹ��ʱ�����ܽ���DMAͨ���ж�
// ��Perinteʹ�ܣ����Դ������ݣ����ǲ�����ͨ�����жϳ���
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
