/**
 * CANopen Process Data Object protocol.
 *
 * @file        CO_PDO.h
 * @ingroup     CO_PDO
 * @version     SVN: \$Id: CO_PDO.h 46 2013-08-24 09:18:16Z jani22 $
 * @author      Janez Paternoster
 * @copyright   2004 - 2013 Janez Paternoster
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
/**
 * @defgroup CO_PDO PDO
 * @ingroup CO_CANopen
 * @{
 *
 * CANopen Process Data Object protocol.
 *
 * Process data objects are used for real-time data transfer with no protocol
 * overhead.
 *
 * TPDO with specific identifier is transmitted by one device and recieved by
 * zero or more devices as RPDO. PDO communication parameters(COB-ID,
 * transmission type, etc.) are in Object Dictionary at index 0x1400+ and
 * 0x1800+. PDO mapping parameters (size and contents of the PDO) are in Object
 * Dictionary at index 0x1600+ and 0x1A00+.
 *
 * Features of the PDO as implemented here, in CANopenNode:
 *  - Dynamic PDO mapping.
 *  - Map granularity of one byte.
 *  - After RPDO is received from CAN bus, its data are copied to buffer.
 *    Function CO_RPDO_process() (called by application) copies data to
 *    mapped objects in Object Dictionary.
 *  - Function CO_TPDO_process() (called by application) sends TPDO if
 *    necessary. There are possible different transmission types, including
 *    automatic detection of Change of State of specific variable.
 */

#ifndef CO_PDO_H
#define CO_PDO_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported define -----------------------------------------------------------*/
/**
 * RPDO communication parameter. The same as record from Object dictionary (index 0x1400+).
 */
typedef struct{
    uint8_t             maxSubIndex;    /**< Equal to 2 */
    /** Communication object identifier for message received. Meaning of the specific bits:
        - Bit  0-10: COB-ID for PDO, to change it bit 31 must be set.
        - Bit 11-29: set to 0 for 11 bit COB-ID.
        - Bit 30:    If true, rtr are NOT allowed for PDO.
        - Bit 31:    If true, node does NOT use the PDO. */
    uint32_t            COB_IDUsedByRPDO;
    /** Transmission type. Values:
        - 0-240:   Reciving is synchronous, process after next reception of the SYNC object.
        - 241-253: Not used.
        - 254:     Manufacturer specific.
        - 255:     Asynchronous. */
    uint8_t             transmissionType;
}CO_RPDOCommPar_t;

/**
 * RPDO mapping parameter. The same as record from Object dictionary (index 0x1600+).
 */
typedef struct{
    /** Actual number of mapped objects from 0 to 8. To change mapped object,
    this value must be 0. */
    uint8_t             numberOfMappedObjects;
    /** Location and size of the mapped object. Bit meanings `0xIIIISSLL`:
        - Bit  0-7:  Data Length in bits.
        - Bit 8-15:  Subindex from object distionary.
        - Bit 16-31: Index from object distionary. */
    uint32_t            mappedObject1;
    uint32_t            mappedObject2;  /**< Same */
    uint32_t            mappedObject3;  /**< Same */
    uint32_t            mappedObject4;  /**< Same */
    uint32_t            mappedObject5;  /**< Same */
    uint32_t            mappedObject6;  /**< Same */
    uint32_t            mappedObject7;  /**< Same */
    uint32_t            mappedObject8;  /**< Same */
}CO_RPDOMapPar_t;

/**
 * TPDO communication parameter. The same as record from Object dictionary (index 0x1800+).
 */
typedef struct{
    uint8_t             maxSubIndex;    /**< Equal to 6 */
    /** Communication object identifier for transmitting message. Meaning of the specific bits:
        - Bit  0-10: COB-ID for PDO, to change it bit 31 must be set.
        - Bit 11-29: set to 0 for 11 bit COB-ID.
        - Bit 30:    If true, rtr are NOT allowed for PDO.
        - Bit 31:    If true, node does NOT use the PDO. */
    uint32_t            COB_IDUsedByTPDO;
    /** Transmission type. Values:
        - 0:       Transmiting is synchronous, specification in device profile.
        - 1-240:   Transmiting is synchronous after every N-th SYNC object.
        - 241-251: Not used.
        - 252-253: Transmited only on reception of Remote Transmission Request.
        - 254:     Manufacturer specific.
        - 255:     Asinchronous, specification in device profile. */
    uint8_t             transmissionType;
    /** Minimum time between transmissions of the PDO in 100micro seconds.
    Zero disables functionality. */
    uint16_t            inhibitTime;
    /** Not used */
    uint8_t             compatibilityEntry;
    /** Time between periodic transmissions of the PDO in milliseconds.
    Zero disables functionality. */
    uint16_t            eventTimer;
    /** Used with numbered SYNC messages. Values:
        - 0:       Counter of the SYNC message shall not be processed.
        - 1-240:   The SYNC message with the counter value equal to this value
                   shall be regarded as the first received SYNC message. */
    uint8_t             SYNCStartValue;
}CO_TPDOCommPar_t;

/**
 * TPDO mapping parameter. The same as record from Object dictionary (index 0x1A00+).
 */
typedef struct{
    /** Actual number of mapped objects from 0 to 8. To change mapped object,
    this value must be 0. */
    uint8_t             numberOfMappedObjects;
    /** Location and size of the mapped object. Bit meanings `0xIIIISSLL`:
        - Bit  0-7:  Data Length in bits.
        - Bit 8-15:  Subindex from object distionary.
        - Bit 16-31: Index from object distionary. */
    uint32_t            mappedObject1;
    uint32_t            mappedObject2;  /**< Same */
    uint32_t            mappedObject3;  /**< Same */
    uint32_t            mappedObject4;  /**< Same */
    uint32_t            mappedObject5;  /**< Same */
    uint32_t            mappedObject6;  /**< Same */
    uint32_t            mappedObject7;  /**< Same */
    uint32_t            mappedObject8;  /**< Same */
}CO_TPDOMapPar_t;

/**
 * RPDO object.
 */
typedef struct{
    CO_EM_t            *em;             /**< From CO_RPDO_init() */
    CO_SDO_t           *SDO;            /**< From CO_RPDO_init() */
    const CO_RPDOCommPar_t *RPDOCommPar;/**< From CO_RPDO_init() */
    const CO_RPDOMapPar_t  *RPDOMapPar; /**< From CO_RPDO_init() */
    uint8_t            *operatingState; /**< From CO_RPDO_init() */
    uint8_t             nodeId;         /**< From CO_RPDO_init() */
    uint16_t            defaultCOB_ID;  /**< From CO_RPDO_init() */
    uint8_t             restrictionFlags;/**< From CO_RPDO_init() */
    /** True, if PDO is enabled and valid */
    bool                valid;
    /** Data length of the received PDO message. Calculated from mapping */
    uint8_t             dataLength;
    /** Pointers to 8 data objects, where PDO will be copied */
    uint8_t            *mapPointer[8];
    /** Variable indicates, if new PDO message received from CAN bus.
    Must be 2-byte variable because of correct alignment of CANrxData. */
    uint16_t            CANrxNew;
    /** 8 data bytes of the received message. Take care for correct (word) alignment!*/
    uint8_t             CANrxData[8];
    CO_CANmodule_t     *CANdevRx;       /**< From CO_RPDO_init() */
    uint16_t            CANdevRxIdx;    /**< From CO_RPDO_init() */
}CO_RPDO_t;

/**
 * TPDO object.
 */
typedef struct{
    CO_EM_t            *em;             /**< From CO_TPDO_init() */
    CO_SDO_t           *SDO;            /**< From CO_TPDO_init() */
    const CO_TPDOCommPar_t *TPDOCommPar;/**< From CO_TPDO_init() */
    const CO_TPDOMapPar_t  *TPDOMapPar; /**< From CO_TPDO_init() */
    uint8_t            *operatingState; /**< From CO_TPDO_init() */
    uint8_t             nodeId;         /**< From CO_TPDO_init() */
    uint16_t            defaultCOB_ID;  /**< From CO_TPDO_init() */
    uint8_t             restrictionFlags;/**< From CO_TPDO_init() */
    bool                valid;          /**< True, if PDO is enabled and valid */
    /** Data length of the transmitting PDO message. Calculated from mapping */
    uint8_t             dataLength;
    /** If application set this flag, PDO will be later sent by
    function CO_TPDO_process(). Depends on transmission type. */
    uint8_t             sendRequest;
    /** Pointers to 8 data objects, where PDO will be copied */
    uint8_t            *mapPointer[8];
    /** Each flag bit is connected with one mapPointer. If flag bit
    is true, CO_TPDO_process() functiuon will send PDO if
    Change of State is detected on value pointed by that mapPointer */
    uint8_t             sendIfCOSFlags;
    /** SYNC counter used for PDO sending */
    uint8_t             syncCounter;
    /** Previous timer from CO_SYNC_t */
    uint32_t            SYNCtimerPrevious;
    /** Inhibit timer used for inhibit PDO sending */
    uint16_t            inhibitTimer;
    /** Event timer used for PDO sending */
    uint16_t            eventTimer;
    CO_CANmodule_t     *CANdevTx;       /**< From CO_TPDO_init() */
    CO_CANtx_t         *CANtxBuff;      /**< CAN transmit buffer inside CANdev */
    uint16_t            CANdevTxIdx;    /**< From CO_TPDO_init() */
}CO_TPDO_t;

/* Exported variables -----------------------------------------------------------*/

/* Exported functions -----------------------------------------------------------*/
CO_ReturnError_t CO_RPDO_init(
        CO_RPDO_t              *RPDO,
        CO_EM_t                *em,
        CO_SDO_t               *SDO,
        uint8_t                *operatingState,
        uint8_t                 nodeId,
        uint16_t                defaultCOB_ID,
        uint8_t                 restrictionFlags,
        const CO_RPDOCommPar_t *RPDOCommPar,
        const CO_RPDOMapPar_t  *RPDOMapPar,
        uint16_t                idx_RPDOCommPar,
        uint16_t                idx_RPDOMapPar,
        CO_CANmodule_t         *CANdevRx,
        uint16_t                CANdevRxIdx);

CO_ReturnError_t CO_TPDO_init(
        CO_TPDO_t              *TPDO,
        CO_EM_t                *em,
        CO_SDO_t               *SDO,
        uint8_t                *operatingState,
        uint8_t                 nodeId,
        uint16_t                defaultCOB_ID,
        uint8_t                 restrictionFlags,
        const CO_TPDOCommPar_t *TPDOCommPar,
        const CO_TPDOMapPar_t  *TPDOMapPar,
        uint16_t                idx_TPDOCommPar,
        uint16_t                idx_TPDOMapPar,
        CO_CANmodule_t         *CANdevTx,
        uint16_t                CANdevTxIdx);

uint8_t CO_TPDOisCOS(CO_TPDO_t *TPDO);
void CO_RPDO_process(CO_RPDO_t *RPDO);
void CO_TPDO_process(
        CO_TPDO_t              *TPDO,
        CO_SYNC_t              *SYNC,
        uint16_t                timeDifference_100us,
        uint16_t                timeDifference_ms);

#endif    /* CO_PDO_H */
