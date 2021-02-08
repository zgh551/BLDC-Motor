/*
 * CRC.c
 *
 *  Created on: 2021
 *      Author: ZGH
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "CRC.h"

Uint16 crc_cal_by_bit(Uint16* message, Uint16 len)
{
    int32 i, j;
    Uint16 crc_reg = 0;
    Uint16 current;

    for (i = 0; i < len; i++)
    {
        current = message[i];
        for (j = 0; j < 8; j++)
        {
            if ((crc_reg ^ current) & 0x0001)
                crc_reg = (crc_reg >> 1) ^ 0x8408;
            else
                crc_reg >>= 1;
            current >>= 1;
        }
    }
    return crc_reg;
}
