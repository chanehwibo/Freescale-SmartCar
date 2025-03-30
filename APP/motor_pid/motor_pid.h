#ifndef _MOTOR_PID_H
#define _MOTOR_PID_H
#include "k60_dma.h"
#include "mk60_ftm.h"

//电机Pid参数结构体
struct MotorPid
{
	float Kp;
	float Ki;
	float Kd;
	float Pout;
	float Iout;
	float Dout;
	u32 Speed;
	u32 Pluse;
	int Error[3];
  int Out;
	int LastOut;
};

extern struct MotorPid Left;
extern struct MotorPid Right;

void LeftMotorPID(void);
void RightMotorPID(void);

#endif
