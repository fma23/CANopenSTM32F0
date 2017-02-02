/**
 ******************************************************************************
 * @file    isr.c
 * @author  FARID
 * @version v1.0
 * @date    19-Jul-2013
 * @brief   Interrupt Service Routine source file
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "isr.h"
#include "timer.h"
#include "stm32f0xx.h"
#include "CANopen.h"
#include "application.h"
#include "stm32f0xx_tim.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variable ----------------------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M Processor Exceptions Handlers                          */
/******************************************************************************/

/**
 * @brief  Description
 * @input  None
 * @output None
 * @return None
*/
void NMI_Handler(void)
{
}

/**
 * @brief  Description
 * @input  None
 * @output None
 * @return None
*/
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
 * @brief  Description
 * @input  None
 * @output None
 * @return None
*/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
 * @brief  Description
 * @input  None
 * @output None
 * @return None
*/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
 * @brief  Description
 * @input  None
 * @output None
 * @return None
*/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
 * @brief  Description
 * @input  None
 * @output None
 * @return None
*/
void SVC_Handler(void)
{
}

/**
 * @brief  Description
 * @input  None
 * @output None
 * @return None
*/
void DebugMon_Handler(void)
{
}

/**
 * @brief  Description
 * @input  None
 * @output None
 * @return None
*/
void PendSV_Handler(void)
{
}

/**
 * @brief  Description
 * @input  None
 * @output None
 * @return None
*/
void SysTick_Handler(void)
{

  static uint16_t tick = 0;

  switch (tick++) {
  	case 100:
  		tick = 0;
  		//GPIOC->ODR ^= (1 << 8);
  		break;
}

}

/******************************************************************************/
/*            Peripherals Interrupt Handlers                                  */
/******************************************************************************/

/**
 * @brief  ISR for USB Low Priority Interrupt
 * @input  None
 * @output None
 * @return None
*/
void USB_LP_IRQHandler(void)
{
  //USB_Istr();
}

/**
 * @brief  ISR for CAN RX Interrupt
 * @input  None
 * @output None
 * @return None
*/
//void USB_LP_CAN1_RX0_IRQHandler(void)
//{
//    CO_CANinterrupt_Rx(CO->CANmodule[0]);
//}

///**
// * @brief  ISR for CAN TX Interrupt
// * @input  None
// * @output None
// * @return None
//*/
//void USB_HP_CAN1_TX_IRQHandler(void)
//{
//    CO_CANinterrupt_Tx(CO->CANmodule[0]);
//}



void CEC_CAN_IRQHandler(void){
	
	 if((CAN->RF0R & CAN_RF0R_FMP0)!=0)/* check if a message is filtered and received by FIFO 0 */
  {
		CO_CANinterrupt_Rx(CO->CANmodule[0]);//CAN_RX_int();
    CAN->RF0R |= CAN_RF0R_RFOM0; /* release FIFO */
	} 
   else
	 {
			CO_CANinterrupt_Tx(CO->CANmodule[0]);//CAN_TX_int(); 
   }
}


/**
  * @brief  This function handles TIM2 overflow and update interrupt request.
            This is 1ms periodic interrupt.
  * @param  None
  * @retval None
 */
void TIM2_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);      /* Clear the Update pending bit */
  timer1ms++;
  /* Periodic cyclic function call */
  if(timer1ms % 50 == 0)
  {
		GPIOA->ODR |= GPIO_ODR_5;  //PA5
    program1ms();
  }

}

