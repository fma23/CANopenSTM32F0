/**
 ******************************************************************************
 * @file    CO_common.c
 * @author  FARID
 * @version v1.0
 * @date
 * @brief   CAN Open common function source file
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "CO_driver.h"
#include "CO_common.h"
/* Private macro -------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variable ----------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/


/* Helper functions. **********************************************************/
void CO_memcpy(uint8_t dest[], const uint8_t src[], const uint16_t size)
{
    uint16_t i;
    for(i = 0; i < size; i++)
    {
        dest[i] = src[i];
    }
}

uint16_t CO_getUint16(const uint8_t data[])
{
    CO_bytes_t b;
    b.u8[0] = data[0];
    b.u8[1] = data[1];
    return b.u16[0];
}

uint32_t CO_getUint32(const uint8_t data[])
{
    CO_bytes_t b;
    b.u8[0] = data[0];
    b.u8[1] = data[1];
    b.u8[2] = data[2];
    b.u8[3] = data[3];
    return b.u32[0];
}

void CO_setUint16(uint8_t data[], const uint16_t value)
{
    CO_bytes_t b;
    b.u16[0] = value;
    data[0] = b.u8[0];
    data[1] = b.u8[1];
}

void CO_setUint32(uint8_t data[], const uint32_t value)
{
    CO_bytes_t b;
    b.u32[0] = value;
    data[0] = b.u8[0];
    data[1] = b.u8[1];
    data[2] = b.u8[2];
    data[3] = b.u8[3];
}

#ifdef BIG_ENDIAN
void CO_memcpySwap2(uint8_t dest[], const uint8_t src[])
{
    dest[0] = src[1];
    dest[1] = src[0];
}

void CO_memcpySwap4(uint8_t dest[], const uint8_t src[])
{
    dest[0] = src[3];
    dest[1] = src[2];
    dest[2] = src[1];
    dest[3] = src[0];
}
#else
void CO_memcpySwap2(uint8_t dest[], const uint8_t src[])
{
    dest[0] = src[0];
    dest[1] = src[1];
}

void CO_memcpySwap4(uint8_t dest[], const uint8_t src[])
{
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    dest[3] = src[3];
}
#endif
