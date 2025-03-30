#ifndef _SERVO_PD_H
#define _SERVO_PD_H
#include "control.h"
#include "mk60_ftm.h"

#define SERVO_MID  1840
#define SERVO_LEFT_MAX 2020
#define SERVO_RIGHT_MAX  1650

void ServoPD(void);

#endif
