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
 *         File:  Crc.h
 *    Component:  SysService_AsrCrc
 *       Module:  Crc
 *    Generator:  MICROSAR EAD
 *
 *  Description:  Crc module is used to calculate CRC values for data to
 *                ensure data integrity.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Tobias Schmid                 Tsd           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  03.00.00  2007-11-29  Tsd     -             Updated component to AUTOSAR Release 2.1
 *  04.00.00  2008-05-07  Mz      -             Add Crc8 calculation AUTOSAR Release 3.0
 *                                ESCAN00026229 Add Extension for MSR3.0 LinkTime checks
 *  04.00.01  2009-02-13  Mz      ESCAN00031923 Resolved the inconsistency between Compiler Abstraction keywords
 *
 **********************************************************************************************************************/

/* multiple inclusion potection */
#if !defined (CRC_H)
#define CRC_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Crc_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : SysService_AsrCrc CQComponent : Implementation */
/* Version - BCD coded version number - Main- and Sub-Version - Release-Version */
#define SYSSERVICE_ASRCRC_VERSION         (0x0400u)
#define SYSSERVICE_ASRCRC_RELEASE_VERSION (0x01u)

/* Version and module identification */
#define CRC_VENDOR_ID               (30u)
#define CRC_MODULE_ID               (201u)
#define CRC_INSTANCE_ID             (0u)
/* AUTOSAR Software Specification Version Information */
#define CRC_AR_MAJOR_VERSION        (3u)
#define CRC_AR_MINOR_VERSION        (0u)
#define CRC_AR_PATCH_VERSION        (0u)

/* Component Version Information */
#define CRC_SW_MAJOR_VERSION        (SYSSERVICE_ASRCRC_VERSION >> 8u)
#define CRC_SW_MINOR_VERSION        (SYSSERVICE_ASRCRC_VERSION & 0x00FF)
#define CRC_SW_PATCH_VERSION        SYSSERVICE_ASRCRC_RELEASE_VERSION

/* These value shall be used as start value when CRC is calculated */
#define CRC_INITIAL_VALUE8          (0x0)
#define CRC_INITIAL_VALUE16         (0xFFFF)
#define CRC_INITIAL_VALUE32         (0xFFFFFFFFL)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*!
 * \brief   pointer type for pointers to data buffers, from which the
 *          CRC value is to be calculated.
 */
typedef P2CONST(uint8, AUTOMATIC, CRC_APPL_DATA) Crc_DataRefType;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define CRC_START_SEC_CODE
#include "MemMap.h"

FUNC(uint16, CRC_CODE) Crc_CalculateCRC16
                (
                     Crc_DataRefType Crc_DataPtr,
                     uint32 Crc_Length,
                     uint16 Crc_StartValue16
                );

FUNC(uint32, CRC_CODE) Crc_CalculateCRC32
                (
                     Crc_DataRefType Crc_DataPtr,
                     uint32 Crc_Length,
                     uint32 Crc_StartValue32
                );

FUNC(uint8, CRC_CODE) Crc_CalculateCRC8
                (
                     Crc_DataRefType Crc_DataPtr,
                     uint32 Crc_Length,
                     uint8 Crc_StartValue8
                );

#if (CRC_VERSION_INFO_API == STD_ON)
    FUNC(void, CRC_CODE) Crc_GetVersionInfo
                (
                     P2VAR(Std_VersionInfoType, AUTOMATIC, CRC_APPL_DATA) versioninfo
                );
#endif

#define CRC_STOP_SEC_CODE
#include "MemMap.h"

#endif  /* CRC_H */

/**********************************************************************************************************************
 *  END OF FILE: Crc.h
 *********************************************************************************************************************/
