/*
 * FOC.c
 *
 *  Created on: 2021年1月23日
 *      Author: Zachary
 */

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "FOC.h"

#pragma CODE_SECTION(SVPWM, "ramfuncs");

#define INVER_SQRT_TREE (0.57735026918962576450914878050196) // 1/sqrt(3)
#define TWO_SQRT_TREE   (0.86602540378443864676372317075294) // sqrt(3)/2
#define SQRT_TREE       (1.7320508075688772935274463415059)  // sqrt(3)

#define T_SAMPLE        (100) // us
#define V_DC            (0.03571428571428571428571428571429) // 1 / U_dc = 1 / 28 (V)

#define K_SVPWM         (SQRT_TREE * T_SAMPLE * V_DC)        // sqrt(3) * T_s / U_dc


void InverseParkTransform(float v_d, float v_q, float theta, float* v_alpha, float* v_beta)
{
    *v_alpha = v_d * cos(theta) - v_q * sin(theta);
    *v_beta  = v_d * sin(theta) + v_q * cos(theta);
}

Uint16 SVPWM(float v_alpha, float v_beta)
{
    float v1, v2, v3;
    float t1, t2, t3, t4, t5, t6;
    float ta, tb, tc;
    Uint16 A, B, C, State_N;
    Uint16 PhaseState = 0;

    v1 = v_beta;
    v2 =  TWO_SQRT_TREE * v_alpha - 0.5f * v_beta;
    v3 = -TWO_SQRT_TREE * v_alpha - 0.5f * v_beta;

    A = v1 > 0.0f ? 1 : 0;
    B = v2 > 0.0f ? 1 : 0;
    C = v3 > 0.0f ? 1 : 0;

    State_N = A + 2 * B + 4 * C;

    switch(State_N)
    {
        case 3: // 区域1 I
            t4 = K_SVPWM * v2; // v2 > 0
            t6 = K_SVPWM * v1; // v1 > 0

            ta = (T_SAMPLE - t4 - t6) * 0.5f;
            tb = ta + t4;
            tc = tb + t6;

            PhaseState = 1;
            break;

        case 1: // 区域2 II
            t2 = K_SVPWM * v2; // v2 < 0
            t6 = K_SVPWM * v3; // v3 < 0

            tb = (T_SAMPLE + t2 + t6) * 0.5f;
            ta = tb - t2;
            tc = ta - t6;

            PhaseState = 2;
            break;

        case 5: // 区域3 III
            t2 = K_SVPWM * v1; // v1 > 0
            t3 = K_SVPWM * v3; // v3 > 0

            tb = (T_SAMPLE - t2 - t3) * 0.5f;
            tc = tb + t2;
            ta = tc + t3;

            PhaseState = 3;
            break;

        case 4: // 区域4 IV
            t1 = K_SVPWM * v1; // v1 < 0
            t3 = K_SVPWM * v2; // v2 < 0

            tc = (T_SAMPLE + t1 + t3) * 0.5f;
            tb = tc - t1;
            ta = tb - t3;

            PhaseState = 4;
            break;

        case 6: // 区域5 V
            t1 = K_SVPWM * v3; // v3 > 0
            t5 = K_SVPWM * v2; // v2 > 0

            tc = (T_SAMPLE - t1 - t5) * 0.5f;
            ta = tc + t1;
            tb = ta + t5;

            PhaseState = 5;
            break;

        case 2: // 区域6 VI
            t4 = K_SVPWM * v3; // v3 < 0
            t5 = K_SVPWM * v1; // v1 < 0

            ta = (T_SAMPLE + t4 + t5) * 0.5f;
            tc = ta - t4;
            tb = tc - t5;

            PhaseState = 6;
            break;

        default:
            PhaseState = 0;
            break;
    }

    ePWM1_LowLevelDutyTime(ta); // us
    ePWM2_LowLevelDutyTime(tb); // us
    ePWM3_LowLevelDutyTime(tc); // us

    return PhaseState;
}




