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
    d2m_Messege.SoftwareVersion_L = 0;  // 驱动板软件版本号 低
    d2m_Messege.SoftwareVersion_H = 2;  // 驱动板软件版本号 高

}


void send_test1()
{
    d2m_Messege.AngularVelocity = 1234.0 / 57.3f;
    d2m_Messege.MotorTargetPosition = 12.34f / 57.3f;
    d2m_Messege.MotorActualPosition = 56.78f / 57.3f;
}

