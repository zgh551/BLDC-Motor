/*
 * Steering_SPI.c
 *
 *  Created on: 2016Äê3ÔÂ5ÈÕ
 *      Author: ZGH
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Steering_SPI.h"

void Steering_Spi_Init(void)
{

//	SpiaRegs.SPICCR.all =0x000F;	             // Reset on, rising edge, 16-bit char bits
	SpiaRegs.SPICCR.bit.SPISWRESET  = 0x0 ;		 // Reset on,enter into reset
	SpiaRegs.SPICCR.bit.CLKPOLARITY = 0x0 ;		 // rising edge
	SpiaRegs.SPICCR.bit.SPILBK      = 0x0 ;      // disable the lookback
	SpiaRegs.SPICCR.bit.SPICHAR     = 0xf ;		 // 16-bit char bits

//	SpiaRegs.SPICTL.all =0x0006;    		     // Enable master mode, normal phase,
												 // enable talk, and SPI int disabled.
	SpiaRegs.SPICTL.bit.MASTER_SLAVE  = 1;		 // Enable master mode
	SpiaRegs.SPICTL.bit.CLK_PHASE     = 0;		 // Normal phase
	SpiaRegs.SPICTL.bit.TALK          = 1;		 // enable Transmission
	SpiaRegs.SPICTL.bit.SPIINTENA     = 0;		 // No SPI - Interrupts

	SpiaRegs.SPIBRR =124;                        // Baud Rate Register LCLK = 37.5MHZ
												 // baudrate = LCLK/125 = 300kHZ

    SpiaRegs.SPICCR.bit.SPISWRESET = 1;		     // Relinquish SPI from Reset

    SpiaRegs.SPIPRI.bit.FREE = 1;                // Set so breakpoints don't disturb xmission
}


void Steering_Spi_FIFO_Init(void)
{
// Initialize SPI FIFO registers
    SpiaRegs.SPIFFTX.all=0xE040;				// resume fifo,enhence fifo,Re-enable FIFO Operation
    											// clear TXFFINT flag,disable the fifo interupte
    SpiaRegs.SPIFFRX.all=0x204f;				// clear RXFFOVF flag,Re-enable receive FIFO operation
    											// clear RXFFINT flag,interrupt based on RXFFIL match
    SpiaRegs.SPIFFCT.all=0x0;
}

void Steering_Spi_Send(Uint16 data)
{
    SpiaRegs.SPITXBUF=data;
    while(SpiaRegs.SPISTS.bit.INT_FLAG != 1){} // Wait until the data is sent
}

Uint16 Steering_Spi_Reveive(void)
{
	Uint16 rdata;  // received data

    // Wait until data is received
//    while(SpiaRegs.SPIFFRX.bit.RXFFST !=1) { }
    // Check against sent data
    rdata = SpiaRegs.SPIRXBUF;

    return rdata;
}
