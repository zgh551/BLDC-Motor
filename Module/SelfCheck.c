/*
 * SelfCheck.c
 *
 *  Created on: 2021
 *      Author: ZGH
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "SelfCheck.h"


void SelfCheck()
{
    d2m_Messege.DriverBoardCheck = 0; // 驱动板自检故障码
    d2m_Messege.MotorCheck       = 0; // 电机自检故障码
    d2m_Messege.SoftwareVersion_L = 2;  // 驱动板软件版本号 低
    d2m_Messege.SoftwareVersion_H = 1;  // 驱动板软件版本号 高

}

