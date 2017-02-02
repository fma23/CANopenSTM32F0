/**
 ******************************************************************************
 * @file    led.h
 * @author  FARID
 * @version v1.0
 * @date    21-Nov-2012
 * @brief   led file header
 ******************************************************************************
 */

#ifndef __LED_H
#define __LED_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "stm32f0xx.h"
#include "stdint.h"

/* Exported define -----------------------------------------------------------*/


#define LED_1_PORT     GPIOA
#define LED_1_PIN      GPIO_Pin_5

#define LED_2_PORT     GPIOA
#define LED_2_PIN      GPIO_Pin_6





/* Exported variables -----------------------------------------------------------*/

/* Exported functions -----------------------------------------------------------*/
void vLED_InitRCC(void);
void vLED_InitPort(void);
void vLED_OffPB14Led(void);
void vLED_OnPB14Led(void);
void vLED_OffPB15Led(void);
void vLED_OnPB15Led(void);

#endif /* __LED_H */




