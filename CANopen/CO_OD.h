/*******************************************************************************

   File: CO_OD.h
   CANopen Object Dictionary.

   Copyright (C) 2004-2008 Janez Paternoster

   License: GNU Lesser General Public License (LGPL).

   <http://canopennode.sourceforge.net>

   (For more information see <CO_SDO.h>.)
*/
/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.


   Author: Janez Paternoster


   This file was automatically generated with CANopenNode Object
   Dictionary Editor. DON'T EDIT THIS FILE MANUALLY !!!!

*******************************************************************************/

#ifndef CO_OD_H
#define CO_OD_H


/*******************************************************************************
   CANopen DATA DYPES
*******************************************************************************/
   typedef uint8_t      UNSIGNED8;
   typedef uint16_t     UNSIGNED16;
   typedef uint32_t     UNSIGNED32;
   typedef uint64_t     UNSIGNED64;
   typedef int8_t       INTEGER8;
   typedef int16_t      INTEGER16;
   typedef int32_t      INTEGER32;
   typedef int64_t      INTEGER64;
   typedef float32_t    REAL32;
   typedef float64_t    REAL64;
   typedef char_t       VISIBLE_STRING;
   typedef oChar_t      OCTET_STRING;
   typedef domain_t     DOMAIN;


/*******************************************************************************
   FILE INFO:
      FileName:     IO
      FileVersion:  3.0
      CreationTime: 15:22:45
      CreationDate: 2013-08-14
      CreatedBy:    -
*******************************************************************************/


/*******************************************************************************
   DEVICE INFO:
      VendorName:     Paternoster
      VendorNumber:   0
      ProductName:    CANopenNode
      ProductNumber:  0
*******************************************************************************/


/*******************************************************************************
   FEATURES
*******************************************************************************/
   #define CO_NO_SYNC                     1   //Associated objects: 1005, 1006, 1007, 2103, 2104
   #define CO_NO_EMERGENCY                1   //Associated objects: 1014, 1015
   #define CO_NO_SDO_SERVER               1   //Associated objects: 1200
   #define CO_NO_SDO_CLIENT               0
   #define CO_NO_RPDO                     4   //Associated objects: 1400, 1401, 1402, 1403, 1600, 1601, 1602, 1603
   #define CO_NO_TPDO                     4   //Associated objects: 1800, 1801, 1802, 1803, 1A00, 1A01, 1A02, 1A03
   #define CO_NO_NMT_MASTER               0


/*******************************************************************************
   OBJECT DICTIONARY
*******************************************************************************/
   #define CO_OD_NoOfElements             61


/*******************************************************************************
   TYPE DEFINITIONS FOR RECORDS
*******************************************************************************/
/*1018      */ typedef struct{
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     vendorID;
               UNSIGNED32     productCode;
               UNSIGNED32     revisionNumber;
               UNSIGNED32     serialNumber;
               }              OD_identity_t;

/*1200[1]   */ typedef struct{
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDClientToServer;
               UNSIGNED32     COB_IDServerToClient;
               }              OD_SDOServerParameter_t;

/*1400[4]   */ typedef struct{
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDUsedByRPDO;
               UNSIGNED8      transmissionType;
               }              OD_RPDOCommunicationParameter_t;

/*1600[4]   */ typedef struct{
               UNSIGNED8      numberOfMappedObjects;
               UNSIGNED32     mappedObject1;
               UNSIGNED32     mappedObject2;
               UNSIGNED32     mappedObject3;
               UNSIGNED32     mappedObject4;
               UNSIGNED32     mappedObject5;
               UNSIGNED32     mappedObject6;
               UNSIGNED32     mappedObject7;
               UNSIGNED32     mappedObject8;
               }              OD_RPDOMappingParameter_t;

/*1800[4]   */ typedef struct{
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDUsedByTPDO;
               UNSIGNED8      transmissionType;
               UNSIGNED16     inhibitTime;
               UNSIGNED8      compatibilityEntry;
               UNSIGNED16     eventTimer;
               UNSIGNED8      SYNCStartValue;
               }              OD_TPDOCommunicationParameter_t;

/*1A00[4]   */ typedef struct{
               UNSIGNED8      numberOfMappedObjects;
               UNSIGNED32     mappedObject1;
               UNSIGNED32     mappedObject2;
               UNSIGNED32     mappedObject3;
               UNSIGNED32     mappedObject4;
               UNSIGNED32     mappedObject5;
               UNSIGNED32     mappedObject6;
               UNSIGNED32     mappedObject7;
               UNSIGNED32     mappedObject8;
               }              OD_TPDOMappingParameter_t;

/*2120      */ typedef struct{
               UNSIGNED8      maxSubIndex;
               INTEGER64      I64;
               UNSIGNED64     U64;
               REAL32         R32;
               REAL64         R64;
               DOMAIN         domain;
               }              OD_testVar_t;

/*6020      */ typedef struct{
               UNSIGNED8      maxSubIndex;
               UNSIGNED8      batteryType;
               UNSIGNED16     ahCapacity;
               UNSIGNED16     maximumChargeCurrent;
               UNSIGNED16     numberOfCells;
               }              OD_batteryParameters_t;


/*******************************************************************************
   STRUCTURES FOR VARIABLES IN DIFFERENT MEMORY LOCATIONS
*******************************************************************************/
#define  CO_OD_FIRST_LAST_WORD     0x55 //Any value from 0x01 to 0xFE. If changed, EEPROM will be reinitialized.

/***** Structure for RAM variables ********************************************/
struct sCO_OD_RAM{
               UNSIGNED32     FirstWord;

/*1001      */ UNSIGNED8      errorRegister;
/*1003      */ UNSIGNED32     preDefinedErrorField[8];
/*2100      */ OCTET_STRING   errorStatusBits[10];
/*2103      */ UNSIGNED16     SYNCCounter;
/*2104      */ UNSIGNED16     SYNCTime;
/*2107      */ UNSIGNED16     performance[5];
/*2109      */ INTEGER16      voltage[1];
/*2110      */ INTEGER32      variableInt32[16];
/*2120      */ OD_testVar_t   testVar;
/*6000      */ UNSIGNED8      batteryStatus;
/*6001      */ UNSIGNED8      chargeStatus;
/*6010      */ INTEGER16      temperature;
/*6050      */ UNSIGNED32     cumulativeTotalAhCharge;
/*6051      */ UNSIGNED16     ahExpendedSinceLastCharge;
/*6052      */ UNSIGNED16     ahReturnedDuringLastCharge;
/*6053      */ UNSIGNED16     ahSinceLastEqualization;
/*6054      */ UNSIGNED16     dateOfLastEqualization[2];
/*6060      */ UNSIGNED32     batteryVoltage;
/*6070      */ UNSIGNED16     chargeCurrentRequested;
/*6080      */ UNSIGNED8      chargerStateOfCharge;
/*6081      */ UNSIGNED8      batteryStateOfCharge;
/*6090      */ UNSIGNED8      waterLevelStatus;

               UNSIGNED32     LastWord;
};

/***** Structure for EEPROM variables *****************************************/
struct sCO_OD_EEPROM{
               UNSIGNED32     FirstWord;

/*2106      */ UNSIGNED32     powerOnCounter;
/*2112      */ INTEGER32      variableNVInt32[16];

               UNSIGNED32     LastWord;
};


/***** Structure for ROM variables ********************************************/
struct sCO_OD_ROM{
               UNSIGNED32     FirstWord;

/*1000      */ UNSIGNED32     deviceType;
/*1005      */ UNSIGNED32     COB_ID_SYNCMessage;
/*1006      */ UNSIGNED32     communicationCyclePeriod;
/*1007      */ UNSIGNED32     synchronousWindowLength;
/*1014      */ UNSIGNED32     COB_ID_EMCY;
/*1015      */ UNSIGNED16     inhibitTimeEMCY;
/*1016      */ UNSIGNED32     consumerHeartbeatTime[4];
/*1017      */ UNSIGNED16     producerHeartbeatTime;
/*1018      */ OD_identity_t  identity;
/*1019      */ UNSIGNED8      synchronousCounterOverflowValue;
/*1029      */ UNSIGNED8      errorBehavior[6];
/*1200[1]   */ OD_SDOServerParameter_t SDOServerParameter[1];
/*1400[4]   */ OD_RPDOCommunicationParameter_t RPDOCommunicationParameter[4];
/*1600[4]   */ OD_RPDOMappingParameter_t RPDOMappingParameter[4];
/*1800[4]   */ OD_TPDOCommunicationParameter_t TPDOCommunicationParameter[4];
/*1A00[4]   */ OD_TPDOMappingParameter_t TPDOMappingParameter[4];
/*1F80      */ UNSIGNED32     NMTStartup;
/*2101      */ UNSIGNED8      CANNodeID;
/*2102      */ UNSIGNED16     CANBitRate;
/*2111      */ INTEGER32      variableROMInt32[16];
/*6020      */ OD_batteryParameters_t batteryParameters;
/*6030      */ UNSIGNED32     batterySerialNumber[3];
/*6031      */ UNSIGNED32     batteryID[5];
/*6040      */ UNSIGNED32     vehicleSerialNumber[5];
/*6041      */ UNSIGNED32     vehicleID[5];

               UNSIGNED32     LastWord;
};


/***** Declaration of Object Dictionary variables *****************************/
extern struct sCO_OD_RAM CO_OD_RAM;

extern struct sCO_OD_EEPROM CO_OD_EEPROM;

extern struct sCO_OD_ROM CO_OD_ROM;


/*******************************************************************************
   ALIASES FOR OBJECT DICTIONARY VARIABLES
*******************************************************************************/
/*1000, Data Type: UNSIGNED32 */
      #define OD_deviceType                              CO_OD_ROM.deviceType

/*1001, Data Type: UNSIGNED8 */
      #define OD_errorRegister                           CO_OD_RAM.errorRegister

/*1003, Data Type: UNSIGNED32, Array[8] */
      #define OD_preDefinedErrorField                    CO_OD_RAM.preDefinedErrorField
      #define ODL_preDefinedErrorField_arrayLength       8

/*1005, Data Type: UNSIGNED32 */
      #define OD_COB_ID_SYNCMessage                      CO_OD_ROM.COB_ID_SYNCMessage

/*1006, Data Type: UNSIGNED32 */
      #define OD_communicationCyclePeriod                CO_OD_ROM.communicationCyclePeriod

/*1007, Data Type: UNSIGNED32 */
      #define OD_synchronousWindowLength                 CO_OD_ROM.synchronousWindowLength

/*1014, Data Type: UNSIGNED32 */
      #define OD_COB_ID_EMCY                             CO_OD_ROM.COB_ID_EMCY

/*1015, Data Type: UNSIGNED16 */
      #define OD_inhibitTimeEMCY                         CO_OD_ROM.inhibitTimeEMCY

/*1016, Data Type: UNSIGNED32, Array[4] */
      #define OD_consumerHeartbeatTime                   CO_OD_ROM.consumerHeartbeatTime
      #define ODL_consumerHeartbeatTime_arrayLength      4

/*1017, Data Type: UNSIGNED16 */
      #define OD_producerHeartbeatTime                   CO_OD_ROM.producerHeartbeatTime

/*1018, Data Type: OD_identity_t */
      #define OD_identity                                CO_OD_ROM.identity

/*1019, Data Type: UNSIGNED8 */
      #define OD_synchronousCounterOverflowValue         CO_OD_ROM.synchronousCounterOverflowValue

/*1029, Data Type: UNSIGNED8, Array[6] */
      #define OD_errorBehavior                           CO_OD_ROM.errorBehavior
      #define ODL_errorBehavior_arrayLength              6
      #define ODA_errorBehavior_communication            0
      #define ODA_errorBehavior_communicationOther       1
      #define ODA_errorBehavior_communicationPassive     2
      #define ODA_errorBehavior_generic                  3
      #define ODA_errorBehavior_deviceProfile            4
      #define ODA_errorBehavior_manufacturerSpecific     5

/*1200[1], Data Type: OD_SDOServerParameter_t, Array[1] */
      #define OD_SDOServerParameter                      CO_OD_ROM.SDOServerParameter

/*1400[4], Data Type: OD_RPDOCommunicationParameter_t, Array[4] */
      #define OD_RPDOCommunicationParameter              CO_OD_ROM.RPDOCommunicationParameter

/*1600[4], Data Type: OD_RPDOMappingParameter_t, Array[4] */
      #define OD_RPDOMappingParameter                    CO_OD_ROM.RPDOMappingParameter

/*1800[4], Data Type: OD_TPDOCommunicationParameter_t, Array[4] */
      #define OD_TPDOCommunicationParameter              CO_OD_ROM.TPDOCommunicationParameter

/*1A00[4], Data Type: OD_TPDOMappingParameter_t, Array[4] */
      #define OD_TPDOMappingParameter                    CO_OD_ROM.TPDOMappingParameter

/*1F80, Data Type: UNSIGNED32 */
      #define OD_NMTStartup                              CO_OD_ROM.NMTStartup

/*2100, Data Type: OCTET_STRING, Array[10] */
      #define OD_errorStatusBits                         CO_OD_RAM.errorStatusBits
      #define ODL_errorStatusBits_stringLength           10

/*2101, Data Type: UNSIGNED8 */
      #define OD_CANNodeID                               CO_OD_ROM.CANNodeID

/*2102, Data Type: UNSIGNED16 */
      #define OD_CANBitRate                              CO_OD_ROM.CANBitRate

/*2103, Data Type: UNSIGNED16 */
      #define OD_SYNCCounter                             CO_OD_RAM.SYNCCounter

/*2104, Data Type: UNSIGNED16 */
      #define OD_SYNCTime                                CO_OD_RAM.SYNCTime

/*2106, Data Type: UNSIGNED32 */
      #define OD_powerOnCounter                          CO_OD_EEPROM.powerOnCounter

/*2107, Data Type: UNSIGNED16, Array[5] */
      #define OD_performance                             CO_OD_RAM.performance
      #define ODL_performance_arrayLength                5
      #define ODA_performance_cyclesPerSecond            0
      #define ODA_performance_timerCycleTime             1
      #define ODA_performance_timerCycleMaxTime          2
      #define ODA_performance_mainCycleTime              3
      #define ODA_performance_mainCycleMaxTime           4

/*2109, Data Type: INTEGER16, Array[1] */
      #define OD_voltage                                 CO_OD_RAM.voltage
      #define ODL_voltage_arrayLength                    1
      #define ODA_voltage_mainPCBSupply                  0

/*2110, Data Type: INTEGER32, Array[16] */
      #define OD_variableInt32                           CO_OD_RAM.variableInt32
      #define ODL_variableInt32_arrayLength              16

/*2111, Data Type: INTEGER32, Array[16] */
      #define OD_variableROMInt32                        CO_OD_ROM.variableROMInt32
      #define ODL_variableROMInt32_arrayLength           16

/*2112, Data Type: INTEGER32, Array[16] */
      #define OD_variableNVInt32                         CO_OD_EEPROM.variableNVInt32
      #define ODL_variableNVInt32_arrayLength            16

/*2120, Data Type: OD_testVar_t */
      #define OD_testVar                                 CO_OD_RAM.testVar

/*6000, Data Type: UNSIGNED8 */
      #define OD_batteryStatus                           CO_OD_RAM.batteryStatus

/*6001, Data Type: UNSIGNED8 */
      #define OD_chargeStatus                            CO_OD_RAM.chargeStatus

/*6010, Data Type: INTEGER16 */
      #define OD_temperature                             CO_OD_RAM.temperature

/*6020, Data Type: OD_batteryParameters_t */
      #define OD_batteryParameters                       CO_OD_ROM.batteryParameters

/*6030, Data Type: UNSIGNED32, Array[3] */
      #define OD_batterySerialNumber                     CO_OD_ROM.batterySerialNumber
      #define ODL_batterySerialNumber_arrayLength        3
      #define ODA_batterySerialNumber_ASCIICharacters1To4 0
      #define ODA_batterySerialNumber_ASCIICharacters5To8 1
      #define ODA_batterySerialNumber_ASCIICharacters9To10 2

/*6031, Data Type: UNSIGNED32, Array[5] */
      #define OD_batteryID                               CO_OD_ROM.batteryID
      #define ODL_batteryID_arrayLength                  5
      #define ODA_batteryID_ASCIICharacters1To4          0
      #define ODA_batteryID_ASCIICharacters5To8          1
      #define ODA_batteryID_ASCIICharacters9To12         2
      #define ODA_batteryID_ASCIICharacters13To16        3
      #define ODA_batteryID_ASCIICharacters17To20        4

/*6040, Data Type: UNSIGNED32, Array[5] */
      #define OD_vehicleSerialNumber                     CO_OD_ROM.vehicleSerialNumber
      #define ODL_vehicleSerialNumber_arrayLength        5
      #define ODA_vehicleSerialNumber_ASCIICharacters1To4 0
      #define ODA_vehicleSerialNumber_ASCIICharacters5To8 1
      #define ODA_vehicleSerialNumber_ASCIICharacters9To12 2
      #define ODA_vehicleSerialNumber_ASCIICharacters13To16 3
      #define ODA_vehicleSerialNumber_ASCIICharacters17To20 4

/*6041, Data Type: UNSIGNED32, Array[5] */
      #define OD_vehicleID                               CO_OD_ROM.vehicleID
      #define ODL_vehicleID_arrayLength                  5
      #define ODA_vehicleID_ASCIICharacters1To4          0
      #define ODA_vehicleID_ASCIICharacters5To8          1
      #define ODA_vehicleID_ASCIICharacters9To12         2
      #define ODA_vehicleID_ASCIICharacters13To16        3
      #define ODA_vehicleID_ASCIICharacters17To20        4

/*6050, Data Type: UNSIGNED32 */
      #define OD_cumulativeTotalAhCharge                 CO_OD_RAM.cumulativeTotalAhCharge

/*6051, Data Type: UNSIGNED16 */
      #define OD_ahExpendedSinceLastCharge               CO_OD_RAM.ahExpendedSinceLastCharge

/*6052, Data Type: UNSIGNED16 */
      #define OD_ahReturnedDuringLastCharge              CO_OD_RAM.ahReturnedDuringLastCharge

/*6053, Data Type: UNSIGNED16 */
      #define OD_ahSinceLastEqualization                 CO_OD_RAM.ahSinceLastEqualization

/*6054, Data Type: UNSIGNED16, Array[2] */
      #define OD_dateOfLastEqualization                  CO_OD_RAM.dateOfLastEqualization
      #define ODL_dateOfLastEqualization_arrayLength     2
      #define ODA_dateOfLastEqualization_numberOfMinutes 0
      #define ODA_dateOfLastEqualization_numberOfDays    1

/*6060, Data Type: UNSIGNED32 */
      #define OD_batteryVoltage                          CO_OD_RAM.batteryVoltage

/*6070, Data Type: UNSIGNED16 */
      #define OD_chargeCurrentRequested                  CO_OD_RAM.chargeCurrentRequested

/*6080, Data Type: UNSIGNED8 */
      #define OD_chargerStateOfCharge                    CO_OD_RAM.chargerStateOfCharge

/*6081, Data Type: UNSIGNED8 */
      #define OD_batteryStateOfCharge                    CO_OD_RAM.batteryStateOfCharge

/*6090, Data Type: UNSIGNED8 */
      #define OD_waterLevelStatus                        CO_OD_RAM.waterLevelStatus


#endif

