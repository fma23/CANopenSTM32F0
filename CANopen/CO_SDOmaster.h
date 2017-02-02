/**
 * CANopen Service Data Object - client protocol.
 *
 * @file        CO_SDOmaster.h
 * @ingroup     CO_SDOmaster
 * @version     SVN: \$Id: CO_SDOmaster.h 39 2013-06-29 08:24:52Z jani22 $
 * @author      Janez Paternoster
 * @author      Matej Severkar
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
  * @defgroup CO_SDOmaster SDO client
  * @ingroup CO_CANopen
  * @{
  *
  * CANopen Service Data Object - client protocol.
  *
  * @see @ref CO_SDO
 */

#ifndef CO_SDO_CLIENT_H
#define CO_SDO_CLIENT_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported define -----------------------------------------------------------*/
/**
 * SDO Client Parameter. The same as record from Object dictionary (index 0x1280+).
 */
typedef struct{
    /** Equal to 3 */
    uint8_t             maxSubIndex;
    /** Communication object identifier for client transmission. Meaning of the specific bits:
        - Bit 0...10: 11-bit CAN identifier.
        - Bit 11..30: reserved, set to 0.
        - Bit 31: if 1, SDO client object is not used. */
    uint32_t            COB_IDClientToServer;
    /** Communication object identifier for message received from server. Meaning of the specific bits:
        - Bit 0...10: 11-bit CAN identifier.
        - Bit 11..30: reserved, set to 0.
        - Bit 31: if 1, SDO client object is not used. */
    uint32_t            COB_IDServerToClient;
    /** Node-ID of the SDO server */
    uint8_t             nodeIDOfTheSDOServer;
}CO_SDOclientPar_t;

/**
 * SDO client object
 */
typedef struct{
    /** From CO_SDOclient_init() */
    CO_SDOclientPar_t  *SDOClientPar;
    /** From CO_SDOclient_init() */
    CO_SDO_t           *SDO;
    /** Internal state of the SDO client */
    uint8_t             state;
    /** Pointer to data buffer supplied by user */
    uint8_t            *buffer;
    /** By download application indicates data size in buffer.
    By upload application indicates buffer size */
    uint32_t            bufferSize;
    /** Offset in buffer of next data segment being read/written */
    uint32_t            bufferOffset;
    /** Acknowledgement */
    uint32_t            bufferOffsetACK;
    /** data length to be uploaded in block transfer */
    uint32_t            dataSize;
    /** Data length transfered in block transfer */
    uint32_t            dataSizeTransfered;
    /** Timeout timer for SDO communication */
    uint16_t            timeoutTimer;
    /** Timeout timer for SDO block transfer */
    uint16_t            timeoutTimerBLOCK;
    /** Index of current object in Object Dictionary */
    uint16_t            index;
    /** Subindex of current object in Object Dictionary */
    uint8_t             subIndex;
    /** From CO_SDOclient_init() */
    CO_CANmodule_t     *CANdevRx;
    /** From CO_SDOclient_init() */
    uint16_t            CANdevRxIdx;
    /** Flag indicates, if new SDO message received from CAN bus.
    It is not cleared, until received message is completely processed. */
    uint16_t            CANrxNew;      /* must be 2-byte variable because of correct alignment of CANrxData */
    /** 8 data bytes of the received message */
    uint8_t             CANrxData[8];  /* take care for correct (word) alignment! */
    /** Pointer to optional external function. If defined, it is called from high
    priority interrupt after new CAN SDO response message is received. Function
    may wake up external task, which processes SDO client functions */
    void              (*pFunctSignal)(uint32_t arg);
    /** Optional argument, which is passed to above function */
    uint32_t            functArg;
    /** From CO_SDOclient_init() */
    CO_CANmodule_t     *CANdevTx;
    /** CAN transmit buffer inside CANdevTx for CAN tx message */
    CO_CANtx_t         *CANtxBuff;
    /** From CO_SDOclient_init() */
    uint16_t            CANdevTxIdx;
    /** Toggle bit toggled with each subsequent in segmented transfer */
    uint8_t             toggle;
    /** Server threshold for switch back to segmented transfer, if data size is small.
    Set in CO_SDOclient_init(). Can be changed by application. 0 Disables switching. */
    uint8_t             pst;
    /** Maximum number of segments in one block. Set in CO_SDOclient_init(). Can
    be changed by application to 2 .. 127. */
    uint8_t             block_size_max;
    /** Last sector number */
    uint8_t             block_seqno;
    /** Block size in current transfer */
    uint8_t             block_blksize;
    /** Number of bytes in last segment that do not contain data */
    uint8_t             block_noData;
    /** Server CRC support in block transfer */
    uint8_t             crcEnabled;

}CO_SDOclient_t;

/* Exported variables -----------------------------------------------------------*/

/* Exported functions -----------------------------------------------------------*/

int16_t CO_SDOclient_init(
        CO_SDOclient_t         *SDO_C,
        CO_SDO_t               *SDO,
        CO_SDOclientPar_t      *SDOClientPar,
        CO_CANmodule_t         *CANdevRx,
        uint16_t                CANdevRxIdx,
        CO_CANmodule_t         *CANdevTx,
        uint16_t                CANdevTxIdx);

int8_t CO_SDOclient_setup(
        CO_SDOclient_t         *SDO_C,
        uint32_t                COB_IDClientToServer,
        uint32_t                COB_IDServerToClient,
        uint8_t                 nodeIDOfTheSDOServer);

int8_t CO_SDOclientDownloadInitiate(
        CO_SDOclient_t         *SDO_C,
        uint16_t                index,
        uint8_t                 subIndex,
        uint8_t                *dataTx,
        uint32_t                dataSize,
        uint8_t                 blockEnable);

int8_t CO_SDOclientDownload(
        CO_SDOclient_t         *SDO_C,
        uint16_t                timeDifference_ms,
        uint16_t                SDOtimeoutTime,
        uint32_t               *pSDOabortCode);

int8_t CO_SDOclientUploadInitiate(
        CO_SDOclient_t         *SDO_C,
        uint16_t                index,
        uint8_t                 subIndex,
        uint8_t                *dataRx,
        uint32_t                dataRxSize,
        uint8_t                 blockEnable);

int8_t CO_SDOclientUpload(
        CO_SDOclient_t         *SDO_C,
        uint16_t                timeDifference_ms,
        uint16_t                SDOtimeoutTime,
        uint32_t               *pDataSize,
        uint32_t               *pSDOabortCode);

#endif    /* CO_SDO_CLIENT_H */
