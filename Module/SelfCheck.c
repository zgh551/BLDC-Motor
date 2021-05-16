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
    // 驱动板自检故障码
    d2m_Messege.DriverBoardCheck.bit.Voltage12V = 0;
    d2m_Messege.DriverBoardCheck.bit.Voltage28V = 0;
    d2m_Messege.DriverBoardCheck.bit.CommunicationState = 0;

    // 电机自检故障码
    d2m_Messege.MotorCheck.bit.Converter = 0;
    d2m_Messege.MotorCheck.bit.MotorAngle = 0;
    d2m_Messege.MotorCheck.bit.MotorAngleRate = 0;
    d2m_Messege.MotorCheck.bit.CurrentOverload = 0;

    d2m_Messege.SoftwareVersion_L = 4;  // 驱动板软件版本号 低
    d2m_Messege.SoftwareVersion_H = 2;  // 驱动板软件版本号 高

    d2m_Messege.MotorStatus.bit.Voltage12V = 0; // 12正常
    d2m_Messege.MotorStatus.bit.Voltage28V = 0; // 28正常
    d2m_Messege.MotorStatus.bit.CommunicationState = 1; // 正常

}

