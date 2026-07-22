#include "Servo-Motor.h"
#include "stm32h723xx.h"

/*Moving the servo motor*/
void ServoRotate (uint16_t step) {
    GPIOC->BSRR = (GPIO_BSRR_BR9 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR12);
    for (uint16_t i = 0; i < step; i++) {
        GPIOC->BSRR = GPIO_BSRR_BS9;
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
        GPIOC->BSRR = GPIO_BSRR_BR12;
    }
    return;
}