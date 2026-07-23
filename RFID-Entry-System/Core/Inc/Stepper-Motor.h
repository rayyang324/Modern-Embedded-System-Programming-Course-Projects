#ifndef STEPPER_MOTOR_H_
#define STEPPER_MOTOR_H_
#include <stdint.h>

#include "stm32h723xx.h"
#include "stm32h7xx_hal.h"
#include "bsp.h"
void OpenDoor(uint16_t angle);
void CloseDoor(uint16_t angle);
static void Stepper_Wave_Drive_CCW (uint16_t);
static void Stepper_Wave_Drive_CW (uint16_t);
static void Stepper_Full_Step_CCW (uint16_t);
static void Stepper_Full_Step_CW (uint16_t);
static void Stepper_Half_Step_CCW (uint16_t);
static void Stepper_Half_Step_CW (uint16_t);
static void Stepper_Half_Step_CCW (uint16_t);

#endif /*STEPPER_MOTOR_H_*/