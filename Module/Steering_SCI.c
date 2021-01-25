/*
 * Steering_SCI.c
 *
 *  Created on: 2016��3��30��
 *      Author: ZGH
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
//user header file
#include "Steering_SCI.h"

#define CPU_FREQ 	 150000000
#define LSPCLK_FREQ  CPU_FREQ/4
#define SCI_FREQ 	 115200
#define SCI_PRD 	 (LSPCLK_FREQ/(SCI_FREQ*8))-1

//#define DSP28_SCIA 1
//Uint16 rdata[10];

// Prototype statements for functions found within this file.
//__interrupt void sciaRxFifoIsr(void);
__interrupt void scibRxFifoIsr(void);

//void Steering_SCI_Init(void)
//{
//// Interrupts that are used in this example are re-mapped to
//// ISR functions found within this file.
//	EALLOW;	// This is needed to write to EALLOW protected registers
//	PieVectTable.SCIRXINTA = &sciaRxFifoIsr;
////	PieVectTable.SCITXINTA = &sciaTxFifoIsr;
//	EDIS;   // This is needed to disable write to EALLOW protected registers
//
//	//BASE INIT
//	SciaRegs.SCICCR.all =0x0007;  // 1 stop bit,  No loopback
//								  // No parity,8 char bits,
//								  // async mode, idle-line protocol
//	SciaRegs.SCICTL1.all =0x0003; // enable TX, RX, internal SCICLK,
//								  // Disable RX ERR, SLEEP, TXWAKE
//	SciaRegs.SCICTL2.bit.TXINTENA =1;	// ENABLE THE TX INTERRUPT
//	SciaRegs.SCICTL2.bit.RXBKINTENA =1; // ENABLE THE RX INTERRUPT
//	SciaRegs.SCIHBAUD = 0x00;
//	SciaRegs.SCILBAUD = SCI_PRD;
//
////	ScibRegs.SCICCR.bit.LOOPBKENA =1; // Enable loop back
//
//	SciaRegs.SCIFFTX.all=0xE021;//ENABLE THE TX FIFO AND RESET LEVEL 8
//	SciaRegs.SCIFFRX.all=0x0021;//ENABLE RHE RX FIFO AND LEVEL 8
//	SciaRegs.SCIFFCT.all=0x00;
//
//	SciaRegs.SCICTL1.all =0x0023;     	// Relinquish SCI from Reset
//	SciaRegs.SCIFFTX.bit.TXFIFOXRESET=1;
//	SciaRegs.SCIFFRX.bit.RXFIFORESET =1;
//
//// Enable interrupts required for this example
//   IER |= M_INT9;	// Enable CPU INT9
//   PieCtrlRegs.PIEIER9.bit.INTx1=1;     // PIE Group 9, Int3
////   PieCtrlRegs.PIEIER9.bit.INTx2=1;     // PIE Group 9, INT4
//
//}
//
//void Steering_Send_Byte(Uint16 byte)
//{
//	while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}
//	SciaRegs.SCITXBUF=byte;
//}


void Steering_SCIB_Init(void)
{
    InitSciGpio();
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
	EALLOW;	// This is needed to write to EALLOW protected registers
	PieVectTable.SCIRXINTB = &scibRxFifoIsr;
	EDIS;   // This is needed to disable write to EALLOW protected registers

	//BASE INIT
	ScibRegs.SCICCR.all = 0x0007; // 1 stop bit,  No loopback
								  // No parity,8 char bits,
								  // async mode, idle-line protocol
	ScibRegs.SCICTL1.all = 0x0003; // enable TX, RX, internal SCICLK,
								   // Disable RX ERR, SLEEP, TXWAKE
	ScibRegs.SCICTL2.bit.TXINTENA   = 1; // ENABLE THE TX INTERRUPT
	ScibRegs.SCICTL2.bit.RXBKINTENA = 1; // ENABLE THE RX INTERRUPT
	ScibRegs.SCIHBAUD = 0x00;
	ScibRegs.SCILBAUD = SCI_PRD;

//	ScibRegs.SCICCR.bit.LOOPBKENA =1; // Enable loop back

	ScibRegs.SCIFFTX.all=0xE021;    //ENABLE THE TX FIFO AND RESET LEVEL 8
	ScibRegs.SCIFFRX.all=0x0021;    //ENABLE RHE RX FIFO AND LEVEL 8
	ScibRegs.SCIFFCT.all=0x00;

	ScibRegs.SCICTL1.all =0x0023;   // Relinquish SCI from Reset
	ScibRegs.SCIFFTX.bit.TXFIFOXRESET=1;
	ScibRegs.SCIFFRX.bit.RXFIFORESET =1;

// Enable interrupts required for this example
   IER |= M_INT9;	// Enable CPU INT9
   PieCtrlRegs.PIEIER9.bit.INTx3=1;     // PIE Group 9, Int3
//   PieCtrlRegs.PIEIER9.bit.INTx4=1;     // PIE Group 9, INT4

}

void Steering_Send_Byte_B(Uint16 byte)
{
	while (ScibRegs.SCIFFTX.bit.TXFFST != 0) {}
	ScibRegs.SCITXBUF = byte;
}


//__interrupt void sciaRxFifoIsr(void)
//{
//    Uint16 i;
//	for(i=0;i<8;i++)
//	{
//	   rdata[i]=SciaRegs.SCIRXBUF.all;	 // Read data
//	}
//
//	SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
//	SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag
//
//	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;       // Issue PIE ack
//}

__interrupt void scibRxFifoIsr(void)
{
	CommunicationStateMachine(ScibRegs.SCIRXBUF.all);

    ScibRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    ScibRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;       // Issue PIE ack
}
