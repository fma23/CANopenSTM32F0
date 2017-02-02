/**
 ******************************************************************************
 * @file    common.h
 * @author  FARID
 * @version v1.0
 * @date    28-aug-2012
 * @brief   Common file header
 ******************************************************************************
 */

#ifndef __COMMON_H
#define __COMMON_H


/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
/* Define --------------------------------------------------------------------*/
/*#define FALSE      (0) */         /*defined in usb_type.h and below */
/*#define TRUE       (!FALSE) */    /*defined in usb_type.h and below */

/*#define DISABLE    (0) */         /*defined in stm32l1xx.h */
/*#define ENABLE     (!DISABLE) */  /*defined in stm32l1xx.h */

/*#define CLR        (0) */
/*#define SET        (!CLR) */   /*defined in stm32l1xx.h */

#define LOW        (0)
#define HIGH       (!LOW)

//#define NULL        (0)

#define false        FALSE
#define true         TRUE

#define FAIL       (0)
#define SUCCEED    (!FAIL)

#define	BIT0       0x01
#define	BIT1       0x02
#define	BIT2       0x04
#define	BIT3       0x08
#define	BIT4       0x10
#define	BIT5       0x20
#define	BIT6       0x40
#define	BIT7       0x80

#define	NBIT0       0xFE
#define	NBIT1       0xFD
#define	NBIT2       0xFB
#define	NBIT3       0xF7
#define	NBIT4       0xEF
#define	NBIT5       0xDF
#define	NBIT6       0xBF
#define	NbIT7       0x7F


/* Types ---------------------------------------------------------------------*/
typedef enum
{
  FALSE = 0, TRUE  = !FALSE
}bool;

typedef struct {
  unsigned char Bit0  :1;
  unsigned char Bit1  :1;
  unsigned char Bit2  :1;
  unsigned char Bit3  :1;
  unsigned char Bit4  :1;
  unsigned char Bit5  :1;
  unsigned char Bit6  :1;
  unsigned char Bit7  :1;
} BITS;

typedef union {
  BITS Bit;
  unsigned char ucByte;
} FLAGS;

#define PCB_A5_NEW_PIN  1   /* 0: PCB A5 new pin disabled; 1: PCB A5 new pin enabled */

#if !PCB_A5_NEW_PIN
#define DEBUG_PIN_PA9   0   /* 0: Not available; 1: Available */  /* LQFP64 Pin42 */
#endif

#endif  /* __COMMON_H */

