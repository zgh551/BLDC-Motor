#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "include.h"
// These are defined by the linker (see F28335.cmd)
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;
extern Uint16 RamfuncsLoadSize;

//static Uint32 ARINC_Dat_H,ARINC_Dat_L;
//static Uint32 ARINC_Data;
//static Uint16 IMU_Dat=0,Power_Dat;

int main(void) {
// Step 1. Initialize System Control:

    InitSysCtrl();

// Step 2. Initialize GPIO:
//   Realy_Init();
//   FIFO_state();
   Digital_IO_Init();
   LedInit();
   InitSciGpio();
//   InitEQepGpio();
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2833x_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2833x_DefaultIsr.c.
// This function is found in DSP2833x_PieVect.c.
   InitPieVectTable();

#ifdef _FLASH
// Copy time critical code and Flash setup code to RAM
// This includes the following ISR functions: epwm1_timer_isr(), epwm2_timer_isr()
// epwm3_timer_isr and and InitFlash();
// The  RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
// symbols are created by the linker. Refer to the F28335.cmd file.

   memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (Uint32)&RamfuncsLoadSize);

// Call Flash Initialization to setup flash waitstates
// This function must reside in RAM

   InitFlash();
#endif
// Step 4. Initialize the Device Peripheral.
//-Timer1 initialize
   InitCpuTimers();
//-Configure CPU-Timer 0, 1, and 2 to interrupt every second:
//-100MHz CPU Freq, 1 second Period (in uSeconds)
   ConfigCpuTimer(&CpuTimer0, 150, 5000);//5ms

//-XINTF Module Initialize for AD2S1210
   Init_Zone();

//-ADC Module Init
//   Steering_ADC_Init();
//   Steering_ADC_EPwm();

//-Init the ePWM
//   InitEPwmBLDC();

//   DRV8432_Init();

//-SCI Module Initialize for 422
   Steering_SCIB_Init();

// Step 5. User specific code, enable interrupts:
//-Initialize the variable
//   StateMachine_Init(); // state machine initial
//   FK_Init();           // this buf used for telemetry
//   Control_Init();

//-System Check
//   SelfCheck();
//   IMU_Init();
//   qep_posspeed.init(&qep_posspeed);
// To ensure precise timing, use write-only instructions to write to the entire register. Therefore, if any
// of the configuration bits are changed in ConfigCpuTimer and InitCpuTimers (in DSP2833x_CpuTimers.h), the
// below settings must also be updated.
   CpuTimer0Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0

// Enable CPU int1 which is connected to CPU-Timer 0
   IER |= M_INT1;
// Enable ADCINT in PIE
   PieCtrlRegs.PIEIER1.bit.INTx6 = 1;
// Enable TINT0 in the PIE: Group 1 interrupt 7
   PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

   EnableInterrupts();
// Enable global Interrupts and higher priority real-time debug events:
   EINT;   // Enable Global interrupt INTM
   ERTM;   // Enable Global realtime interrupt DBGM

// Step 6. IDLE loop. Just sit and loop forever (optional):
   while(1)
   {
      if (SELFCHECK == m2d_Messege.Commond)
      {
         BLDC_SelfCheck();
         m2d_Messege.Commond = 0;
      }
      else if (DELIVERRY == m2d_Messege.Commond)
      {
         CommandResponse(DELIVERRY_REACT);
         m2d_Messege.Commond = 0;
      }
      else if (RESET == m2d_Messege.Commond)
      {
         CommandResponse(RESET_REACT);
         m2d_Messege.Commond = 0;
      }
      else if (APROXMT_ZERO == m2d_Messege.Commond)
      {
         CommandResponse(APROXMT_ZERO_REACT);
         m2d_Messege.Commond = 0;
      }
      else
      {
         // do nothing
      }

      if (0xAABB = TelemetrySendFlag)
      {
         BLDC_TelemetrySend();
      }
   }
}
