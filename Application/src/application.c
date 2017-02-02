/*
 * Header for application interface for CANopenNode stack.
 *
 * @file        application.c
 * @ingroup     application
 * @version     SVN: \$Id: application.c 31 2013-03-08 17:57:40Z jani22 $
 * @author      Janez Paternoster
 * @copyright   2012 - 2013 Janez Paternoster
 *
 * This file is part of CANopenNode, an opensource CANopen Stack.
 * Project home page is <http://canopennode.sourceforge.net>.
 * For more information on CANopen see <http://www.can-cia.org/>.
 *
 * CANopenNode is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* Includes ------------------------------------------------------------------*/
#include "CANopen.h"
#include "application.h"





void programStart(void)
{

    /* Verify, if OD structures have proper alignment of initial values */
    if (CO_OD_RAM.FirstWord != CO_OD_RAM.LastWord)
        {
            while(1){}
        }
    if (CO_OD_EEPROM.FirstWord != CO_OD_EEPROM.LastWord)
        {
            while(1){}
        }
    if (CO_OD_ROM.FirstWord != CO_OD_ROM.LastWord)
        {
            while(1){}
        }
    /* increase variable each startup. Variable is stored in eeprom. */
    OD_powerOnCounter++;

}

/*******************************************************************************/
void communicationReset(void)
{
    CO_ReturnError_t err;

    /* turn on red LED */
    CanLedsSet(eCoLed_Red);

    /* initialize CANopen */
    err = CO_init();
    if (err)
    {
      CO_errorReport(CO->em, CO_EM_MEMORY_ALLOCATION_ERROR, CO_EMC_SOFTWARE_INTERNAL, err);
    }

}

/*******************************************************************************/
void programEnd(void)
{

}


/*******************************************************************************/
 CO_NMT_reset_cmd_t programAsync(uint16_t timer1msDiff)
{
    CO_NMT_reset_cmd_t reset = CO_RESET_NOT;

    /* CANopen process */
    reset = CO_process(CO, timer1msDiff);

    CanLedsSet((LED_GREEN_RUN(CO->NMT)>0 ? eCoLed_Green : 0) | (LED_RED_ERROR(CO->NMT)>0 ? eCoLed_Red : 0));

    return reset;
}


/*******************************************************************************/
void program1ms(void)
{

    CO_process_RPDO(CO);
    CO_process_TPDO(CO);

}
