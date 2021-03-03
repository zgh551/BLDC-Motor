/*
 * Digital_IO.c
 *
 *  Created on: 2021
 *      Author: ZGH
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Digital_IO.h"

#define WR_DELAY_TIME   (1) // define the wait time
#define DEG2RAD         (0.01745329251994329576923690768489)    // deg -> rad

void AD2S1210_IO_Init(void)
{
	EALLOW;

    GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO63  = 1;//Sample low valid

    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO28  = 1;//res0 Pin 141

    GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO36  = 1;//res1 Pin 145

    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO57  = 1;//Reset Pin 99

    /*
     * the input pin configure
     */
    GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO55  = 0;//Dos Pin 97

    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO56  = 0;//Lot Pin 98

    GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO58  = 0;//Dir Pin 100

	EDIS;
}

/*
 * @brief the output single
 */
void AD2S1210_Sample(Uint16 state)
{
    GpioDataRegs.GPBDAT.bit.GPIO63 = state;
}

void AD2S1210_Res0(Uint16 state)
{
    GpioDataRegs.GPADAT.bit.GPIO28 = state;
}

void AD2S1210_Res1(Uint16 state)
{
    GpioDataRegs.GPBDAT.bit.GPIO36 = state;
}

void AD2S1210_Reset(Uint16 state)
{
    GpioDataRegs.GPBDAT.bit.GPIO57 = state;
}

/*
 * @brief the input pin read
 */
Uint16 AD2S1210_Dos(void)
{
	return GpioDataRegs.GPBDAT.bit.GPIO55;
}

Uint16 AD2S1210_Lot(void)
{
	return GpioDataRegs.GPBDAT.bit.GPIO56;
}

Uint16 AD2S1210_Dir(void)
{
    return GpioDataRegs.GPBDAT.bit.GPIO58;
}

void AD2S1210_SampleUpdate(void)
{
    AD2S1210_Sample(1);
    AD2S1210_Sample(0);
    DELAY_US(WR_DELAY_TIME);
    AD2S1210_Sample(1);
    DELAY_US(WR_DELAY_TIME);
}

void AD2S1210_Init(void)
{
    // the relation pin initialize
    AD2S1210_IO_Init();

    // Hardware reset
    AD2S1210_Reset(0);
    DELAY_US(1000);
    AD2S1210_Reset(1);

    // the software reset
    *(Uint16*)(0x200003) = SOFT_RESET;

    DELAY_US(1000);

    // update the sample single to clear the fault register
    AD2S1210_SampleUpdate();

    // set the resolution in the pin of chip
    AD2S1210_Res0(1);
    AD2S1210_Res1(1);
    // register set
    // res: 12bit
    // enres: 16bit
    AD2S1210_ConfigModeWrite(CONTROL, 0x7F);

    // configure the EXCITATION FREQUENCY register
//    AD2S1210_ConfigModeWrite(EXCITATION_FREQUENCY, 0x18); // 6khz

    // LOS Threshold
//    AD2S1210_ConfigModeWrite(LOS_THRESHOLD, 0x34); // 1.1 v

    // DOS mism Threshold
//    AD2S1210_ConfigModeWrite(DOS_MISM_THRESHOLD, 0x12); // 0.684 v

    // LOT high threshold
//    AD2S1210_ConfigModeWrite(LOT_HIGH_THRESHOLD, 0x23); // 10 deg

    // LOT low threshold
//    AD2S1210_ConfigModeWrite(LOT_LOW_THRESHOLD, 0x08); // 5 deg

    DELAY_US(WR_DELAY_TIME);
    *(Uint16*)(0x200003) = FAULT;
    // set the sample single to high
    AD2S1210_Sample(1);
}

void AD2S1210_ConfigModeWrite(Uint16 add, Uint16 dat)
{
    DELAY_US(WR_DELAY_TIME);
	*(Uint16*)(0x200003) = add;
    DELAY_US(WR_DELAY_TIME);
	*(Uint16*)(0x200003) = dat;
}

Uint16 AD2S1210_ConfigModeRead(Uint16 add)
{
    DELAY_US(WR_DELAY_TIME);
    *(Uint16*)(0x200003) = add;
    DELAY_US(WR_DELAY_TIME);
    return *(Uint16*)(0x200003);
}

Uint16 AD2S1210_DataReadSpeed(Uint16* vel)
{
    Uint16 temp_h;
    AD2S1210_SampleUpdate();

    temp_h = AD2S1210_ConfigModeRead(VELOCITY_H);
    *vel  = (temp_h << 8) | (AD2S1210_ConfigModeRead(VELOCITY_L) & 0xff);
    DELAY_US(WR_DELAY_TIME);

    DELAY_US(WR_DELAY_TIME);
    *(Uint16*)(0x200003) = FAULT;
    return *(Uint16*)(0x200003);
}

Uint16 AD2S1210_DataRead(Uint16* pos, Uint16* vel)
{
    AD2S1210_SampleUpdate();

    *pos  = *(Uint16*)(0x200000);
    DELAY_US(WR_DELAY_TIME);

    *vel  = *(Uint16*)(0x200002);
    DELAY_US(WR_DELAY_TIME);

    return *(Uint16*)(0x200003);
}

Uint16 AD2S1210_ResultRead(float* pos, float* vel)
{
    Uint16 temp_data_u16 = 0;
    int16  temp_data_i16 = 0;

    AD2S1210_SampleUpdate();

    temp_data_u16 = *(Uint16*)(0x200000);
//    *pos  = (temp_data_u16 >> 4) * 0.08833 * DEG2RAD; // 5.3 / 60 [deg: 0 - 360] 12bit
    *pos  = temp_data_u16 * 0.005 * DEG2RAD; // 0.3 / 60 [deg: 0 - 360] 16bit

    DELAY_US(WR_DELAY_TIME);

    temp_data_i16 = *(int16*)(0x200001);
//    *vel  = (temp_data_i16 >> 4) * 0.488; //rps 12bit
    *vel  = temp_data_i16 * 0.004; //rps 16bit

    DELAY_US(WR_DELAY_TIME);

    return *(Uint16*)(0x200003); // return the fault status
}
