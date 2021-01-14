/*
 * CRC.h
 *
 *  Created on: 2016Äê5ÔÂ31ÈÕ
 *      Author: ZGH
 */

#ifndef STEERINGENGINE_28335_V4_INC_CRC_H_
#define STEERINGENGINE_28335_V4_INC_CRC_H_

#include "include.h"

Uint16 CRC16_1(Uint16* pchMsg, Uint16 wDataLen);
unsigned short crc_ccitt(unsigned char *q, int len);
Uint16 crc16(unsigned char *buf,unsigned short length);
unsigned int crc2(unsigned char *ptr, unsigned char count);
Uint16 usMBCRC16( unsigned char * pucFrame, Uint16 usLen );
//Uint16 CRC16_2(Uint16* pchMsg, Uint16 wDataLen);
//Uint16 CRC16_3(Uint16* pchMsg, Uint16 wDataLen);

#endif /* STEERINGENGINE_28335_V4_INC_CRC_H_ */
