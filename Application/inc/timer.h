/**
 ******************************************************************************
 * @file    timer.h
 * @author  FARID
 * @version v1.0
 * @date    2-Nov-2012
 * @brief   Timer file header
 ******************************************************************************
 */

#ifndef __TIMER_H
#define __TIMER_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "co_driver.h"
#include <stdint.h>


/* Exported define -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported variable ---------------------------------------------------------*/
extern volatile uint32_t timer1ms;
/* Exported function -------------------------------------------------------- */
void vTIMER_InitRCC(void);
void vTIMER_InitGeneral(void);

typedef unsigned int (*pf_getTimerVal_us)();

typedef struct {
	uint32_t savedTime;
} ttimer;

int initTimer(pf_getTimerVal_us gett);
void saveTime(ttimer *tim);
uint32_t getTime_ms(ttimer *tim);
uint32_t getTime_us(ttimer *tim);

#endif  /* __TEMPLATE_H*/


