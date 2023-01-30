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
 *         File:  Port.h
 *      Project:  DrvPort_Tms570Tigio01Asr
 *       Module:  DrvPort
 *    Generator:  -
 *
 *  Description:  This module implements a driver in ANSI C programming language to centralize the
 *                configuration of ports and pins which are used by more than one driver module.
 *                With this driver you can:
 *                - Configure all port pins
 *                - Initialize the configuration
 *                - Refresh the configuration (EMC purposes)
 *                - Switch the port pin configuration during runtime
 *
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Martin Froschhammer           Mfr           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2008-09-08  Mfr     -             Initial release
 *  01.00.01  2009-03-30  Mfr     -             Patch version updated due to changes of memory mapping
 *  01.00.02  2010-04-29  Mfr     ESCAN00035117 PBCFG_ROOT section added to Port_MemMap.inc
 *  01.01.00  2011-08-18  Mfr     -             Markers for runtime measurement added
 *                                ESCAN00050869 Software qualified for serial release
 *                                ESCAN00053350 Port_InitMemory added
 *                                ESCAN00053313 MISRA justifications added to the code
 *            2011-11-04  Mfr     -             Implementation of safety SFR access
 *********************************************************************************************************************/


#if (!defined PORT_H)
#define PORT_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Port_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : DrvPort_Tms570Tigio01Asr CQComponent : <Implementation> */
/* Version - BCD coded version number - Main- and Sub-Version - Release-Version */
#define DRVPORT_TMS570TIGIO01ASR_VERSION          (0x0101u)
#define DRVPORT_TMS570TIGIO01ASR_RELEASE_VERSION  (0x00u)

/* vendor and module identification */
#define PORT_VENDOR_ID              (30u)
#define PORT_MODULE_ID              (124u)
#define PORT_INSTANCE_ID            (0u)

/* AUTOSAR Software Specification Version Information */
#define PORT_AR_MAJOR_VERSION       (0x03)
#define PORT_AR_MINOR_VERSION       (0x00)
#define PORT_AR_PATCH_VERSION       (0x01)

/* Component Version Information */
#define PORT_SW_MAJOR_VERSION       (DRVPORT_TMS570TIGIO01ASR_VERSION >> 8u)
#define PORT_SW_MINOR_VERSION       (DRVPORT_TMS570TIGIO01ASR_VERSION & 0x00FF)
#define PORT_SW_PATCH_VERSION       DRVPORT_TMS570TIGIO01ASR_RELEASE_VERSION

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/****** Error Codes in Development-Mode  ********/

/*  Invalid Port Pin ID requested  */
#define PORT_E_PARAM_PIN                    (0xAu)

/*  Port Pin not configured as changeable  */
#define PORT_E_DIRECTION_UNCHANGEABLE       (0xBu)

/*  Init service called with wrong parameter  */
#define PORT_E_PARAM_CONFIG                 (0xCu)

/*  Module not initialized  */
#define PORT_E_UNINIT                       (0xFu)

/* GetVersionInfo called with wrong parameter */
#define PORT_E_PARAM_VINFO                  (0x20u)

/* Api is called which is not supported */
#define PORT_E_FEATURE_NOT_SUPPORTED        (0x21u)


/****** Port Service Identification  ************/
#define PORT_SID_INIT                       (0x0u)
#define PORT_SID_SET_PIN_DIR                (0x1u)
#define PORT_SID_REFRESH_PORT_DIR           (0x2u)
#define PORT_SID_GET_VERSION_INFO           (0x3u)
#define PORT_SID_SET_PIN_MODE               (0x4u)


/*  Type for symbolic name of Port pins  */
typedef uint8 Port_PinType;


/*  Type of direction of Port pin  */
typedef enum
{
    PORT_PIN_IN = 0,
    PORT_PIN_OUT
}Port_PinDirectionType;



/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define PORT_START_SEC_CODE
#include "MemMap.h"


/*  Service Functions  */
FUNC(void, PORT_CODE) Port_InitMemory( void );

FUNC(void, PORT_CODE) Port_Init( P2CONST( Port_ConfigType, AUTOMATIC, PORT_PBCFG) ConfigPtr );

#if ( STD_ON == PORT_SET_PIN_DIRECTION_API )
FUNC(void, PORT_CODE)Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
#endif /*( STD_ON == PORT_SET_PIN_DIRECTION_API )*/

#if ( STD_ON == PORT_REFRESH_PORT_DIRECTION_API )
FUNC(void, PORT_CODE) Port_RefreshPortDirection(void);
#endif /*( STD_ON == PORT_REFRESH_PORT_DIRECTION_API )*/

#if ( STD_ON == PORT_SET_PIN_MODE_API )
FUNC(void, PORT_CODE) Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
#endif /*( STD_ON == PORT_SET_PIN_MODE_API )*/


#if (STD_ON == PORT_VERSION_INFO_API)
FUNC(void, PORT_CODE) Port_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, PORT_APPL_DATA) versioninfo );
#endif /*(STD_ON == PORT_VERSION_INFO_API)*/

#define PORT_STOP_SEC_CODE
#include "MemMap.h"


#endif  /* PORT_H */

/**********************************************************************************************************************
 *  END OF FILE: Port.h
 *********************************************************************************************************************/
