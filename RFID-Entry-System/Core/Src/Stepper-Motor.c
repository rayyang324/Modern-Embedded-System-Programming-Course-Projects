#include "Stepper-Motor.h"
#include "stm32h723xx.h"
#include <stdint.h>
/*Generic Open/Close Door Function*/

void OpenDoor(uint16_t angle) {
    /*angle to step conversion
    Since 512 is a full 360 deg
    */
    uint32_t step = (uint32_t)angle * 512 / 360; // should somehow round to about the same
    Stepper_Half_Step_CW(step);
    return;

}
void CloseDoor(uint16_t angle) {
    uint32_t step = (uint32_t)angle * 512 / 360;
    Stepper_Half_Step_CCW(step);
    return;
}

// Some tof the drive functions are not used but displayed. In reality
// the half drive should be the smoothest of all and Wave is just generally faster.
// Full step has more torque compared to wave drive.

/*Moving the Stepper motor -> Wave Drive*/
static void Stepper_Wave_Drive_CCW(uint16_t step) {
  if (!step)
    return;
  GPIOC->BSRR =
      (GPIO_BSRR_BR9 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR12);
  for (uint16_t i = 0; i < step; i++) {
    GPIOC->BSRR = GPIO_BSRR_BS9;
    GPIOC->BSRR = GPIO_BSRR_BR12;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR9;
    GPIOC->BSRR = GPIO_BSRR_BS10;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR10;
    GPIOC->BSRR = GPIO_BSRR_BS11;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR11;
    GPIOC->BSRR = GPIO_BSRR_BS12;
    BSP_delay(2U);
  }
  return;
}
static void Stepper_Wave_Drive_CW(uint16_t step) {
  if (!step)
    return;
  GPIOC->BSRR =
      (GPIO_BSRR_BR9 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR12);
  for (uint16_t i = 0; i < step; i++) {
    GPIOC->BSRR = GPIO_BSRR_BS12;
    GPIOC->BSRR = GPIO_BSRR_BR9;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR12;
    GPIOC->BSRR = GPIO_BSRR_BS11;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR11;
    GPIOC->BSRR = GPIO_BSRR_BS10;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR10;
    GPIOC->BSRR = GPIO_BSRR_BS9;
    BSP_delay(2U);
  }
  return;
}

/* Moving via Full Step configuration*/
static void Stepper_Full_Step_CCW(uint16_t step) {
  if (!step)
    return;
  GPIOC->BSRR =
      (GPIO_BSRR_BR9 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR12);
  /* The Starting State*/
  GPIOC->BSRR = GPIO_BSRR_BS9;
  GPIOC->BSRR = GPIO_BSRR_BS10;
  for (uint16_t i = 0; i < step; i++) {
    GPIOC->BSRR = GPIO_BSRR_BR9;
    GPIOC->BSRR = GPIO_BSRR_BS11;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR10;
    GPIOC->BSRR = GPIO_BSRR_BS12;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR11;
    GPIOC->BSRR = GPIO_BSRR_BS9;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR12;
    GPIOC->BSRR = GPIO_BSRR_BS10;
    BSP_delay(2U);
  }
  return;
}
static void Stepper_Full_Step_CW(uint16_t step) {
  if (!step)
    return;
  GPIOC->BSRR =
      (GPIO_BSRR_BR9 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR12);
  /* The Starting State*/
  GPIOC->BSRR = GPIO_BSRR_BS9;
  GPIOC->BSRR = GPIO_BSRR_BS10;
  for (uint16_t i = 0; i < step; i++) {
    GPIOC->BSRR = GPIO_BSRR_BR10;
    GPIOC->BSRR = GPIO_BSRR_BS12;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR9;
    GPIOC->BSRR = GPIO_BSRR_BS11;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR12;
    GPIOC->BSRR = GPIO_BSRR_BS10;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR11;
    GPIOC->BSRR = GPIO_BSRR_BS9;
    BSP_delay(2U);
  }
  return;
}

/* Moving via Half Step configuration*/
static void Stepper_Half_Step_CCW(uint16_t step) {
  if (!step)
    return;
  GPIOC->BSRR =
      (GPIO_BSRR_BR9 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR12);

  GPIOC->BSRR = GPIO_BSRR_BS9;
  for (int i = 0; i < step; i++) {
    GPIOC->BSRR = GPIO_BSRR_BS10;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR9;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BS11;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR10;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BS12;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR11;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BS9;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR12;
    BSP_delay(2U);
  }
}
static void Stepper_Half_Step_CW(uint16_t step) {
  if (!step)
    return;
  GPIOC->BSRR =
      (GPIO_BSRR_BR9 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR12);

  GPIOC->BSRR = GPIO_BSRR_BS9;
  for (int i = 0; i < step; i++) {
    GPIOC->BSRR = GPIO_BSRR_BS12;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR9;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BS11;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR12;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BS10;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR11;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BS9;
    BSP_delay(2U);
    GPIOC->BSRR = GPIO_BSRR_BR10;
    BSP_delay(2U);
  }
}