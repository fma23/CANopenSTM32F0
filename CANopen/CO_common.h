/**
 ******************************************************************************
 * @file    CO_common.h
 * @author
 * @version v1.0
 * @date
 * @brief   CAN Open common function file header
 ******************************************************************************
 */

#ifndef CO_COMMON_H
#define CO_COMMON_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported define -----------------------------------------------------------*/
/**
 * Helper union for manipulating data bytes.
 */
typedef union{
    uint8_t  u8[8];  /**< 8 bytes */
    uint16_t u16[4]; /**< 4 words */
    uint32_t u32[2]; /**< 2 double words */
}CO_bytes_t;

/**
 * Helper function like memcpy.
 *
 * Function copies n data bytes from source to destination.
 *
 * @param dest Destination location.
 * @param src Source location.
 * @param size Number of data bytes to be copied (max 0xFFFF).
 */
void CO_memcpy(uint8_t dest[], const uint8_t src[], const uint16_t size);

/**
 * Helper function returns uint16 from byte array.
 *
 * @param data Location of source data.
 * @return Variable of type uint16_t.
 */
uint16_t CO_getUint16(const uint8_t data[]);

/**
 * Helper function returns uint32 from byte array.
 *
 * @param data Location of source data.
 * @return Variable of type uint32_t.
 */
uint32_t CO_getUint32(const uint8_t data[]);

/**
 * Helper function writes uint16 to byte array.
 *
 * @param data Location of destionation data.
 * @param value Variable of type uint16_t to be written into data.
 */
void CO_setUint16(uint8_t data[], const uint16_t value);

/**
 * Helper function writes uint32 to byte array.
 *
 * @param data Location of destionation data.
 * @param value Variable of type uint32_t to be written into data.
 */
void CO_setUint32(uint8_t data[], const uint32_t value);

void CO_memcpySwap2(uint8_t dest[], const uint8_t src[]);
void CO_memcpySwap4(uint8_t dest[], const uint8_t src[]);



#endif    /* CO_COMMON_H */
