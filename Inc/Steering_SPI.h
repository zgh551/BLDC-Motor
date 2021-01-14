/*
 * Steering_SPI.h
 *
 *  Created on: 2016Äê3ÔÂ7ÈÕ
 *      Author: ZGH
 */

#ifndef STEERINGENGINE_28335_V3_INC_STEERING_SPI_H_
#define STEERINGENGINE_28335_V3_INC_STEERING_SPI_H_

#include "include.h"

void Steering_Spi_Init(void);
void Steering_Spi_FIFO_Init(void);
void Steering_Spi_Send(Uint16 data);
Uint16 Steering_Spi_Reveive(void);

#endif /* STEERINGENGINE_28335_V3_INC_STEERING_SPI_H_ */
