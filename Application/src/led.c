/**
 ******************************************************************************
 * @file    led.c
 * @author  FARID
 * @version v1.0
 * @date    06-Aug-2013
 * @brief   led source file
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "led.h"
//#include "stm32f0xx_rcc.h"

/* Private macro -------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variable ----------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/**
 * @brief  LED Initialize RCC
 * @input  None
 * @output None
 * @return None
 *
*/
void vLED_InitRCC(void)
{
//  RCC_APB2PeriphClockCmd(RCC_AHBENR_GPIOBEN, ENABLE);        /*!< GPIOB clock enable */
//	RCC_APB2PeriphClockCmd(RCC_AHBENR_GPIOAEN , ENABLE);       /*!< GPIOA clock enable */
//	RCC_APB2PeriphClockCmd(RCC_AHBENR_GPIOCEN , ENABLE);       /*!< GPIOC clock enable */
}

/**
 * @brief  LED Initialize Port
 * @input  None
 * @output None
 * @return None
 *
*/
void vLED_InitPort(void)
{

	  /* Enable the peripheral clock of GPIOC */
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    
  /* Select output mode (01) on PC8 and PC9 */
  GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODER5 ))| (GPIO_MODER_MODER5_0);
}

 /**
 * @brief  turn off PB14 led
 * @input  None
 * @output None
 * @return None
 *
*/
void vLED_OffPB14Led(void)
{
  //GPIO_ResetBits(LED_1_PORT, LED_1_PIN);
	GPIOA->ODR &= ~GPIO_ODR_5;
}
 /**
 * @brief  turn off PB15 led
 * @input  None
 * @output None
 * @return None
 *
*/
void vLED_OffPB15Led(void)
{
  //GPIO_ResetBits(LED_2_PORT, LED_2_PIN);
   GPIOA->ODR &= ~GPIO_ODR_5;
}

/**
 * @brief  turn On PB14 led
 * @input  None
 * @output None
 * @return None
 *
*/
void vLED_OnPB14Led(void)
{
  //GPIO_SetBits(LED_1_PORT, LED_1_PIN);
	GPIOA->ODR |= GPIO_ODR_5;
}

/**
 * @brief  turn On PB14 led
 * @input  None
 * @output None
 * @return None
 *
*/
void vLED_OnPB15Led(void)
{
 // GPIO_SetBits(LED_2_PORT, LED_2_PIN);
	GPIOA->ODR |= GPIO_ODR_5;
}

