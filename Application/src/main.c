/**
 ******************************************************************************
 * @file    main.c
 * @author  FARID
 * @version v1.0
 * @date    19-Jul-2013
 * @brief   Main source file
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "CANopen.h"
#include "application.h"
#include "timer.h"
#include "stm32f0xx.h"
#include "stm32f0xx_iwdg.h"


void ClearWDT()
{

    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);    /* Enable write access to IWDG_KR */
    IWDG_ReloadCounter();                            /* Set Reload value into IWDG_KR */
    while(IWDG_GetFlagStatus(IWDG_FLAG_RVU)); /* Wait till the Reload is written */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);    /* Enable write access to IWDG_KR */

}

/*******************************************************************************
* Function Name  : main.
* Description    : main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{
    uint32_t timer1msDiff;
    uint32_t t;
    CO_NMT_reset_cmd_t reset = CO_RESET_NOT;

    InitCanLeds();

    /* Configure Timer interrupt function for execution every 1 millisecond */
    vTIMER_InitRCC();
    vTIMER_InitGeneral();

    /* Program start - Application Call */
    programStart();


    while (reset != CO_RESET_APP) {
    /* CANopen communication reset - initialize CANopen objects *******************/
    static uint32_t timer1msPrevious;

    /* disable timer interrupts */
    NVIC_DisableIRQ(TIM2_IRQn);

    /* Communication Reset */
    communicationReset();

    /* start Timer interupts*/
    NVIC_EnableIRQ(TIM2_IRQn);

    reset = CO_RESET_NOT;
    timer1msPrevious = timer1ms;

    while (reset == CO_RESET_NOT) {
    /* loop for normal program execution ******************************************/

    timer1msDiff = timer1ms - timer1msPrevious;
    timer1msPrevious = timer1ms;

  //  ClearWDT();

    /* Program Async for SDO and NMT messages */
    reset = programAsync(timer1msDiff);

  //  ClearWDT();


    /* (not implemented) eeprom_process(&eeprom); */
    // t = getTime_us(&tprof);  
    t = 100;
    OD_performance[ODA_performance_mainCycleTime] = t;
    if (t > OD_performance[ODA_performance_mainCycleMaxTime])
    OD_performance[ODA_performance_mainCycleMaxTime] = t;

        } 
    } 
    /* program exit ***************************************************************/
    /* save variables to eeprom */
    CO_DISABLE_INTERRUPTS();

    CanLedsSet(eCoLed_None);
    /* (not implemented) eeprom_saveAll(&eeprom); */
    CanLedsSet(eCoLed_Red);
    /* delete CANopen object from memory */
    CO_delete();

    /* reset - by WD */
    return 0;
}


#ifdef USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
