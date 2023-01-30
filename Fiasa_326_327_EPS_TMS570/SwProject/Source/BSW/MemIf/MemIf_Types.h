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
 *         File:  MemIf.h
 *    Component:  If_AsrIfMem
 *       Module:  MemIf
 *    Generator:  -  
 *
 *  Description:  The Memory Abstraction Interface provides uniform access to services of underlying
 *                Memory Hardware abstraction (MemHwA) modules, i.e. EEPROM Abstraction (EA) and
 *                Flash EEPROM Emulation (FEE). The appropriate MemHwA module is selected by a device index.
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Tobias Schmid                 Tsd           Vector Informatik GmbH
 *  Manfred Duschinger            Du            Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.02.00  -           Tsd     -             first production release
 *  01.02.01              Du      ESCAN00042276 Support of MEMIF_JOB_CANCELED and MEMIF_JOB_CANCELLED
 *********************************************************************************************************************/

/*---- Protection against multiple inclusion -------------------------------*/
#if !defined _MEMIF_TYPES_H_
#define _MEMIF_TYPES_H_

/*---- Version identification ---------------*/
#define MEMIF_TYPES_MAJOR_VERSION      (1U)
#define MEMIF_TYPES_MINOR_VERSION      (2U)
#define MEMIF_TYPES_PATCH_VERSION      (1U)

/*---- API Defines ---------------------------------------------------------*/
/* error value for calling MemIf's API with an invalid device index */
#define MEMIF_E_PARAM_DEVICE (0x01u)
/* error value for calling MemIf_GetVersionInfo with NULL_PTR as parameter */
#define MEMIF_E_PARAM_VINFO  (0x02u)

/*---- API Type definitions ------------------------------------------------*/

/* A memory hardware abstraction module's state is denoted in 
 * this type. Mainly used in MemIf_GetStatus and related 
 * APIs of memory hardware abstraction modules.
 */
typedef enum
{
    MEMIF_UNINIT = 0,
    MEMIF_IDLE,
    MEMIF_BUSY,
    MEMIF_BUSY_INTERNAL
} MemIf_StatusType;

/* A requested job can have one these values after it has been
 * processed. Use in MemIf_GetJobResult and related memory 
 * hardware abstraction module APIs. 
 */
typedef enum
{
    MEMIF_JOB_OK = 0,
    MEMIF_JOB_FAILED,
    MEMIF_JOB_PENDING,
    MEMIF_JOB_CANCELLED,
    MEMIF_BLOCK_INCONSISTENT,
    MEMIF_BLOCK_INVALID
} MemIf_JobResultType;


/* Specifies the processing speed of requested jobs. The exact 
 * processing duration in the different modes depends on 
 * configuration of the underlying memory hardware abstraction 
 * modules.   
 */
typedef enum
{
    MEMIF_MODE_SLOW = 0,
    MEMIF_MODE_FAST
} MemIf_ModeType;

/* data pointer for API */
typedef P2VAR(uint8, AUTOMATIC, MEMIF_APPL_DATA) MemIf_DataPtr_pu8;

/* Workaround for AUTOSAR Release 2.0 Flash Drivers:
 * 
 * Fls assumes, that MemIf provides MemIf_AddressType and MemIf_LenghthType.
 * Eep assumes, that it should define its address types on its own.
 * MemIf assumes, that Eep is right and hence does NOT provide these 
 * types. However, there are some implementations, that did not recognise 
 * this inconsistency, so we have to provide these types in order to
 * get Flash drivers and Flash Eeprom Emultation integrated with the 
 * other BSW Modules. In order to minimize the risk of limitting the 
 * address range of underlying flash drivers, both types are based 
 * on 32bit-address range (allowing 4GB of data, which should be 
 * considerably adequate). This might not be the optimum data type 
 * on all platforms, but it's the safest.
 */
typedef uint32 MemIf_AddressType;
typedef uint32 MemIf_LengthType;

/* 
 * Because of different typings in the different AUTOSAR specs for compatibility
 * either MEMIF_JOB_CANCELLED and MEMIF_JOB_CANCELED must be useable. 
 */
#define MEMIF_JOB_CANCELED     MEMIF_JOB_CANCELLED

/*--------------------------------------------------------------------------*/
#endif /* _MEMIF_TYPES_H_ */
/*---- End of File ---------------------------------------------------------*/
