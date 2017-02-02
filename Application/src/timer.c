/**
 ******************************************************************************
 * @file    timer.c
 * @author  FARID
 * @version v1.0
 * @date    19-Jul-2013
 * @brief   Timer source file
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "timer.h"
#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_tim.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variable ----------------------------------------------------------*/
volatile uint32_t timer1ms;
/* Private function ----------------------------------------------------------*/
/**
 * @brief  TIMER Initialization of RCC
 * @input  None
 * @output None
 * @return None
 *
*/
void vTIMER_InitRCC(void)
{
	//SysTick_Config(SystemCoreClock/100);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

/**
 * @brief  TIMER General Initialization
 * @input  None
 * @output None
 * @return None
 *
*/
void vTIMER_InitGeneral(void)
{
 
	TIM_TimeBaseInitTypeDef  TimeBaseStructure;  
	
  /* Enable Timer 2   */
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //TIM2_CLK_ENABLE();
	
  /* Enable GPIOA clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	/* Time Base configuration 1ms based on HCLK 48MHz using HSI */
  TimeBaseStructure.TIM_Prescaler = 48000;
  TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TimeBaseStructure.TIM_Period = 1000;                                  /*Timer triggers every one second*/
  TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM2, &TimeBaseStructure);  
		
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);                  /* Enable the TIM Update Interrupt */
  TIM_Cmd(TIM2, ENABLE);                                      /* TIM counter enable */
  NVIC_SetPriority(TIM2_IRQn, 1); 
	NVIC_EnableIRQ(TIM2_IRQn); 
	
}
