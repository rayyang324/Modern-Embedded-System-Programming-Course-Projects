#ifndef BSP_H_
#define BSP_H_

#include <stdint.h>
#include "stm32h723xx.h"

/* System clock tick in Hz*/
#define BSP_TICKS_PER_SEC 1000U

/*Define our own delay function using interrupts*/
uint32_t BSP_tickCtr(void);
void BSP_delay(uint32_t);
#endif /*BSP_H_*/