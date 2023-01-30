/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2011 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Dio.h
 *    Component:  DrvDio_Tms570Tigio01Asr
 *       Module:  Dio
 *    Generator:  -
 *
 *  Description:  This is the header file of MICROSAR CAL module Dio. This DIO Driver provides services for 
 *                reading and writing to/from
 *                        -   DIO Channels (Pins)
 *                        -   DIO Ports
 *                        -   DIO Channel Groups
 * 
 *                This module works on pins and ports which are configured by the PORT driver for this purpose. 
 *                For this reason there is no configuration and initialization of this port structure in the DIO 
 *                Driver.
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Tobias Schmid                 Tsd           Vector Informatik GmbH
 *  Martin Froschhammer           Mfr           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2008-10-10  Tsd     -             First release
 *  01.00.01  2009-03-31  Tsd     -             Updated driver for use in serial production environments
 *  01.01.00  2011-08-12  Mfr    ESCAN00050900  Immediate return of Dio_GetVersionInfo in case of a DET error added
 *                               ESCAN00052737  Dio_WriteChannel - Access for CAN IO pins corrected
 *                               ESCAN00053617  Dio_WritePort - Access for CAN IO pins corrected
 *                                -             Support of Dio_MaskedWritePort added
 *                               ESCAN00050870  State of component changed to serial qualified
 *                               ESCAN00053298  MISRA justifications added to source code 
 *            2012-03-06  Mfr    ESCAN00054735  Support of HW register access via Safety OS functions  
 *********************************************************************************************************************/


#if !defined (DIO_H)
#define DIO_H

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : DrvDio_Tms570Tigio01Asr CQComponent : Implementation */
/* Version - BCD coded version number - Main- and Sub-Version - Release-Version */
#define DRVDIO_TMS570TIGIO01ASR_VERSION          (0x0101u)
#define DRVDIO_TMS570TIGIO01ASR_RELEASE_VERSION  (0x00u)

/* vendor and module identification */
#define DIO_VENDOR_ID              (30u)
#define DIO_MODULE_ID              (120u)

/* AUTOSAR Software Specification Version Information */
#define DIO_AR_MAJOR_VERSION       (0x02)
#define DIO_AR_MINOR_VERSION       (0x03)
#define DIO_AR_PATCH_VERSION       (0x00)

/* Component Version Information */
#define DIO_SW_MAJOR_VERSION       (DRVDIO_TMS570TIGIO01ASR_VERSION >> 8u)
#define DIO_SW_MINOR_VERSION       (DRVDIO_TMS570TIGIO01ASR_VERSION & 0x00FFu)
#define DIO_SW_PATCH_VERSION       DRVDIO_TMS570TIGIO01ASR_RELEASE_VERSION


/* DIO error codes: */
#define DIO_E_PARAM_INVALID_CHANNEL_ID      (10u)   /* API service called with invalid channel ID               */
#define DIO_E_PARAM_INVALID_PORT_ID         (20u)   /* API service called with invalid port ID                  */
#define DIO_E_PARAM_INVALID_GROUP_ID        (31u)   /* API service called with invalid channel group ID         */
#define DIO_E_PARAM_VINFO                   (32u)   /* Dio_GetVersionInfo() called with NULL_PTR as parameter   */

/* DIO API service identification */
#define DIO_SID_READ_CHANNEL                ( 0u)
#define DIO_SID_WRITE_CHANNEL               ( 1u)
#define DIO_SID_READ_PORT                   ( 2u)
#define DIO_SID_WRITE_PORT                  ( 3u)
#define DIO_SID_READ_CHL_GROUP              ( 4u)
#define DIO_SID_WRITE_CHL_GROUP             ( 5u)
#define DIO_SID_GET_VERSION_INFO            (18u)
#define DIO_SID_MASKED_WRITE_PORT           (19u)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/* type definition for identifying DIO channels (meaning single port pins) */
typedef uint32 Dio_ChannelType;

/* type definition for identifying ports */
typedef uint32 Dio_PortType;

/* type defintion for setting port level values (this is a bitmask, where each bit with value '1' sets the 
 * corresponding port pin to HIGH and '0' sets the pin to LOW)
 */
typedef uint32 Dio_PortLevelType;

/* type definition for setting DIO channnel level values (allowed values: STD_HIGH and STD_LOW) */
typedef uint8  Dio_LevelType;

/* type definition for identifying channel groups (meaning a set of pins in one port) */
typedef struct {
  Dio_PortType      port;       /* port ID of a channel group                                           */
  Dio_PortLevelType mask;       /* bitmask where a '1' represents a pin handled by this channel group   */
  uint8             offset;     /* shifts channel group values, so it is always "right" aligned.        */
} Dio_ChannelGroupType;

/* type definition for referencing channel group structures */
typedef P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_DATA) Dio_ChannelGroupRefType;

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Dio_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"

FUNC(Dio_LevelType, DIO_CODE) Dio_ReadChannel
(
  Dio_ChannelType ChannelId
);

FUNC(void, DIO_CODE) Dio_WriteChannel
(
  Dio_ChannelType ChannelId,
  Dio_LevelType   Level
);


FUNC(Dio_PortLevelType, DIO_CODE) Dio_ReadPort
(
  Dio_PortType PortId
);

FUNC(void, DIO_CODE) Dio_WritePort
(
  Dio_PortType      PortId,
  Dio_PortLevelType Level
);


FUNC(Dio_PortLevelType, DIO_CODE) Dio_ReadChannelGroup
(
  Dio_ChannelGroupRefType ChannelGroupIdPtr
);

FUNC(void, DIO_CODE) Dio_WriteChannelGroup
(
  Dio_ChannelGroupRefType ChannelGroupIdPtr,
  Dio_PortLevelType       Level
);

#if(DIO_MASKED_WRITE_PORT_API == STD_ON)
FUNC(void, DIO_CODE) Dio_MaskedWritePort
( 
    Dio_PortType PortId, 
    Dio_PortLevelType Level, 
    Dio_PortLevelType Mask
);
#endif


#if (DIO_VERSION_INFO_API == STD_ON)
  FUNC(void, DIO_CODE) Dio_GetVersionInfo
  (
    P2VAR(Std_VersionInfoType, AUTOMATIC, DIO_APPL_DATA) VersionInfo
  );
#endif

#define DIO_STOP_SEC_CODE
#include "MemMap.h"


#endif  /* DIO_H */

/**********************************************************************************************************************
 *  END OF FILE: Dio.h
 *********************************************************************************************************************/
