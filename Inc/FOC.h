/*
 * FOC.h
 *
 *  Created on: 2021年1月23日
 *      Author: Zachary
 */

#ifndef INC_FOC_H_
#define INC_FOC_H_

#include "include.h"

void ClarkTransform(float ia, float ib, float ic, float* i_alpha, float* i_beta);

void ParkTransform(float i_alpha, float i_beta, float theta, float* i_d, float* i_q);

void InverseParkTransform(float v_d, float v_q, float theta, float* v_alpha, float* v_beta);

Uint16 SVPWM(float v_alpha, float v_beta);

#endif /* INC_FOC_H_ */
