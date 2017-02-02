/**
 * Main CANopen stack file.
 *
 * It combines Object dictionary (CO_OD) and all other CANopen source files.
 * Configuration information are read from CO_OD.h file. This file may be
 * customized for different CANopen configuration. (One or multiple CANopen
 * device on one or multiple CAN modules.)
 *
 * @file        CANopen.h
 * @ingroup     CO_CANopen
 * @version     SVN: \$Id: CANopen.h 46 2013-08-24 09:18:16Z jani22 $
 * @author      Janez Paternoster
 * @author      Uwe Kindler
 * @copyright   2010 - 2013 Janez Paternoster
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

#ifndef CANopen_H
#define CANopen_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "CO_driver.h"
#include "CO_common.h"
#include "CO_OD.h"
#include "CO_SDO.h"
#include "CO_Emergency.h"
#include "CO_NMT_Heartbeat.h"
#include "CO_SYNC.h"
#include "CO_PDO.h"
#include "CO_HBconsumer.h"
 #if CO_NO_SDO_CLIENT == 1
  #include "CO_SDOmaster.h"
 #endif

/* Exported define -----------------------------------------------------------*/
/**
 * Default CANopen identifiers.
 *
 * Default CANopen identifiers for CANopen communication objects. Same as
 * 11-bit addresses of CAN messages. These are default identifiers and
 * can be changed in CANopen. Especially PDO identifiers are confgured
 * in PDO linking phase of the CANopen network configuration.
 */
typedef enum{
     CO_CAN_ID_NMT_SERVICE       = 0x000,   /**< 0x000, Network management */
     CO_CAN_ID_SYNC              = 0x080,   /**< 0x080, Synchronous message */
     CO_CAN_ID_EMERGENCY         = 0x080,   /**< 0x080, Emergency messages (+nodeID) */
     CO_CAN_ID_TIME_STAMP        = 0x100,   /**< 0x100, Time stamp message */
     CO_CAN_ID_TPDO_1            = 0x180,   /**< 0x180, Default TPDO1 (+nodeID) */
     CO_CAN_ID_RPDO_1            = 0x200,   /**< 0x200, Default RPDO1 (+nodeID) */
     CO_CAN_ID_TPDO_2            = 0x280,   /**< 0x280, Default TPDO2 (+nodeID) */
     CO_CAN_ID_RPDO_2            = 0x300,   /**< 0x300, Default RPDO2 (+nodeID) */
     CO_CAN_ID_TPDO_3            = 0x380,   /**< 0x380, Default TPDO3 (+nodeID) */
     CO_CAN_ID_RPDO_3            = 0x400,   /**< 0x400, Default RPDO3 (+nodeID) */
     CO_CAN_ID_TPDO_4            = 0x480,   /**< 0x480, Default TPDO4 (+nodeID) */
     CO_CAN_ID_RPDO_4            = 0x500,   /**< 0x500, Default RPDO5 (+nodeID) */
     CO_CAN_ID_TSDO              = 0x580,   /**< 0x580, SDO response from server (+nodeID) */
     CO_CAN_ID_RSDO              = 0x600,   /**< 0x600, SDO request from client (+nodeID) */
     CO_CAN_ID_HEARTBEAT         = 0x700    /**< 0x700, Heartbeat message */
}CO_Default_CAN_ID_t;

/**
 * Number of CAN modules in use.
*/
#ifndef CO_NO_CAN_MODULES
    #define CO_NO_CAN_MODULES 1
#endif

/**
 * CANopen stack object combines pointers to all CANopen objects.
 */
typedef struct{
    CO_CANmodule_t     *CANmodule[CO_NO_CAN_MODULES];/**< CAN module objects */
    CO_SDO_t           *SDO;            /**< SDO object */
    CO_EM_t            *em;             /**< Emergency report object */
    CO_EMpr_t          *emPr;           /**< Emergency process object */
    CO_NMT_t           *NMT;            /**< NMT object */
    CO_SYNC_t          *SYNC;           /**< SYNC object */
    CO_RPDO_t          *RPDO[CO_NO_RPDO];/**< RPDO objects */
    CO_TPDO_t          *TPDO[CO_NO_TPDO];/**< TPDO objects */
    CO_HBconsumer_t    *HBcons;         /**<  Heartbeat consumer object*/
#if CO_NO_SDO_CLIENT == 1
    CO_SDOclient_t     *SDOclient;      /**< SDO client object */
#endif
}CO_t;

/** CANopen object */
    extern CO_t *CO;

/* Exported variables -----------------------------------------------------------*/

/* Exported functions -----------------------------------------------------------*/

#if CO_NO_NMT_MASTER == 1
    uint8_t CO_sendNMTcommand(CO_t *CO, uint8_t command, uint8_t nodeID);
#endif

CO_ReturnError_t CO_init(void);
void CO_delete(void);
CO_NMT_reset_cmd_t CO_process(CO_t *CO, uint16_t timeDifference_ms);
void CO_process_RPDO(CO_t *CO);
void CO_process_TPDO(CO_t *CO);

#endif    /* CANopen_H */
