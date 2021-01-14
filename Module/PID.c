/*
 * PID.c
 *
 *  Created on: 2016年3月1日
 *      Author: ZGH
 */
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "PID.h"

void pidInit(PidObject* pid, const float desired, const float kp,
             const float ki, const float kd, const float dt)
{
  pid->error     = 0;
  pid->prevError = 0;
  pid->integ     = 0;
  pid->deriv     = 0;
  pid->desired = desired;
  pid->kp = kp;
  pid->ki = ki;
  pid->kd = kd;
  pid->iLimit    = DEFAULT_PID_INTEGRATION_LIMIT;
  pid->iLimitLow = -DEFAULT_PID_INTEGRATION_LIMIT;
  pid->dt        = dt;
}

float pidUpdate(PidObject* pid, const float measured, const unsigned char updateError)
{
    float output;

    if (updateError)
    {
        pid->error = pid->desired - measured;//预期 - 实际
    }

    pid->integ += pid->error * pid->dt;
    if (pid->integ > pid->iLimit)
    {
        pid->integ = pid->iLimit;
    }
    else if (pid->integ < pid->iLimitLow)
    {
        pid->integ = pid->iLimitLow;
    }

    pid->deriv = (pid->error - pid->prevError) / pid->dt;

    pid->outP = pid->kp * pid->error;
    pid->outI = pid->ki * pid->integ;
    pid->outD = pid->kd * pid->deriv;

    output = pid->outP + pid->outI + pid->outD;

    pid->prevError = pid->error;

    return output;
}

//设置积分极限
void pidSetIntegralLimit(PidObject* pid, const float limit) {
    pid->iLimit = limit;
}

//设置积分最低值
void pidSetIntegralLimitLow(PidObject* pid, const float limitLow) {
    pid->iLimitLow = limitLow;
}

//pid参数初始化
void pidReset(PidObject* pid)
{
  pid->error     = 0;
  pid->prevError = 0;
  pid->integ     = 0;
  pid->deriv     = 0;
}

//设置PID误差
void pidSetError(PidObject* pid, const float error)
{
  pid->error = error;
}

//设置目标PID值
void pidSetDesired(PidObject* pid, const float desired)
{
  pid->desired = desired;
}

//获取目标PID值
float pidGetDesired(PidObject* pid)
{
  return pid->desired;
}

//判断PID是否激活
unsigned char pidIsActive(PidObject* pid)
{
	unsigned char isActive = 1;

  if (pid->kp < 0.0001 && pid->ki < 0.0001 && pid->kd < 0.0001)
  {
    isActive = 0;
  }

  return isActive;
}

void pidSetKp(PidObject* pid, const float kp)
{
  pid->kp = kp;
}

void pidSetKi(PidObject* pid, const float ki)
{
  pid->ki = ki;
}

void pidSetKd(PidObject* pid, const float kd)
{
  pid->kd = kd;
}
void pidSetDt(PidObject* pid, const float dt) {
    pid->dt = dt;
}
