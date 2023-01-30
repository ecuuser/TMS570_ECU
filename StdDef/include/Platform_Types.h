/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2007 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Platform_Types.h
 *    Component:  -
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  Provision of Platform Types for TI TMS570
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  MISRA VIOLATIONS
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Joachim Kalmbach              Jk            Vector Informatik
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2007-08-09  Jk                    Initial creation
 *  01.00.01  2007-10-24 Kbr                    changed for TMS570
 *  01.00.02  2007-11-27  Jk                    Defines for CFG management added
 *  01.01.00  2009-05-19  Ht                    Suppport ASR 3.0
 *  2.0       02/10/11    JJW                   Added unit64 type for TMS570 architecture
 *********************************************************************************************************************/

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : CommonAsr_Tms470 CQComponent : Impl_PlatformTypes */
#define COMMONASR_TMS470_IMPL_PLATFORMTYPES_VERSION 0x0101
#define COMMONASR_TMS470_IMPL_PLATFORMTYPES_RELEASE_VERSION 0x00

#define PLATFORM_VENDOR_ID    30u

/* AUTOSAR Software Specification Document Version Information */
/*           part of AUTOSAR Release 3.0                       */
#define PLATFORM_AR_MAJOR_VERSION       (2u)
#define PLATFORM_AR_MINOR_VERSION       (2u)
#define PLATFORM_AR_PATCH_VERSION       (1u)

/* Component Version Information */
#define PLATFORM_SW_MAJOR_VERSION       (1u)
#define PLATFORM_SW_MINOR_VERSION       (1u)
#define PLATFORM_SW_PATCH_VERSION       (0u) 


#define CPU_TYPE_8       8
#define CPU_TYPE_16      16
#define CPU_TYPE_32      32


#define MSB_FIRST         0                 /* Big endian bit ordering        */
#define LSB_FIRST         1                 /* Little endian bit ordering     */


#define HIGH_BYTE_FIRST   0                 /* Big endian byte ordering       */
#define LOW_BYTE_FIRST    1                 /* Little endian byte ordering    */


#ifndef TRUE
   #define TRUE   ((boolean) 1)
#endif

#ifndef FALSE
   #define FALSE  ((boolean) 0)
#endif


#define CPU_TYPE            CPU_TYPE_32
#define CPU_BIT_ORDER       MSB_FIRST
#define CPU_BYTE_ORDER      HIGH_BYTE_FIRST

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 
typedef unsigned char       boolean;        /* for use with TRUE/FALSE                      */

typedef signed char         sint8;          /*                 -128 .. +127                 */
typedef unsigned char       uint8;          /*                    0 .. 255                  */
typedef signed short        sint16;         /*               -32768 .. +32767               */
typedef unsigned short      uint16;         /*                    0 .. 65535                */
typedef signed long         sint32;         /*          -2147483648 .. +2147483647          */
typedef unsigned long       uint32;         /*                    0 .. 4294967295           */
typedef signed long long    sint64;         /* -9223372036854775808 .. +9223372036854775807 */
typedef unsigned long long  uint64;         /*           0 .. 18446744073709551615          */

typedef unsigned long       uint8_least;    /* At least 8 bit                 */
typedef unsigned long       uint16_least;   /* At least 16 bit                */
typedef unsigned long       uint32_least;   /* At least 32 bit                */
typedef unsigned long long  uint64_least;   /* At least 64 bit                */
typedef signed long         sint8_least;    /* At least 7 bit + 1 bit sign    */
typedef signed long         sint16_least;   /* At least 15 bit + 1 bit sign   */
typedef signed long         sint32_least;   /* At least 31 bit + 1 bit sign   */
typedef signed long long    sint64_least;   /* At least 63 bit + 1 bit sign   */


typedef float               float32;
typedef double              float64;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/


/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/


#endif /* PLATFORM_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Platform_Types.h
 *********************************************************************************************************************/
