/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2009 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Gpt.h
 *    Component:  DrvGpt_Tms570Tirti01Asr
 *       Module:  DrvGpt
 *    Generator:  -
 *
 *  Description:  This module implements a driver to provide services for starting and stopping a functional timer
 *                instance (channel) within the hardware timer module. Individual timeout periods (single shot mode) as
 *                well as repeating timeout periods (continuous mode) can be generated. The user can configure, if a
 *                notification shall be invoked, when the requested timeout period has expired. Notifications can be
 *                enabled and disabled at runtime. Both, the relative time elapsed since the last notification occurred
 *                (respectively the channel has been started) and the time remaining until the next notification will
 *                occur, can be queried. The GPT Driver can be used to wakeup the ECU, whenever a predefined timeout
 *                period has expired. A mode switching service is provided to switch the GPT Driver between normal
 *                operation and sleep mode.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Roland Süß                    Rsu           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2008-10-24  Rsu                   Initial release of Asr3.0 implementation
 *  01.00.01  2009-01-09  Rsu     ESCAN00032264 Removed BETA disclaimer
 *  01.00.02  2011-02-02  Lg      ESCAN00042829 Removing a bracket from a commend
 *  01.00.03  2011-08-24  Lg                    Adding time measurement tags and wakeup validation Det error report
 *  01.00.04  2012-01-16  Lg      ESCAN00054736 Adding register access feature via OS interface 
 *  01.00.05  2012-02-24  Lg                    Fixing error in macro
 *  01.00.06  2012-04-16  Lg      ESCAN00058371 Fixing Register access
 *********************************************************************************************************************/

#if !defined (GPT_H)
#define GPT_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "Gpt_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : DrvGpt_Tms570Tirti01Asr CQComponent : <Implementation> */
/* Version - BCD coded version number - Main- and Sub-Version - Release-Version */
#define DRVGPT_TMS570TIRTI01ASR_VERSION          (0x0100u)
#define DRVGPT_TMS570TIRTI01ASR_RELEASE_VERSION  (0x06u)

/* vendor and module identification */
#define GPT_VENDOR_ID               (30u)
#define GPT_MODULE_ID               (100u)
#define GPT_INSTANCE_ID             (0u)

/* AUTOSAR Software Specification Version Information */
#define GPT_AR_MAJOR_VERSION        (0x02)
#define GPT_AR_MINOR_VERSION        (0x02)
#define GPT_AR_PATCH_VERSION        (0x00)

/* Component Version Information */
#define GPT_SW_MAJOR_VERSION        (DRVGPT_TMS570TIRTI01ASR_VERSION >> 8u)
#define GPT_SW_MINOR_VERSION        (DRVGPT_TMS570TIRTI01ASR_VERSION & 0x00FF)
#define GPT_SW_PATCH_VERSION        DRVGPT_TMS570TIRTI01ASR_RELEASE_VERSION

/* Error codes */
#define GPT_E_UNINIT                (0x0Au)   /* API service used without init */
#define GPT_E_BUSY                  (0x0Bu)   /* Timer is already running */
#define GPT_E_NOT_STARTED           (0x0Cu)   /* Timer has not been started yet */
#define GPT_E_ALREADY_INITIALIZED   (0x0Du)   /* Gpt_Init is called but the module is already initialized */
#define GPT_E_PARAM_CHANNEL         (0x14u)   /* API called with invalid channel */
#define GPT_E_PARAM_VALUE           (0x15u)   /* Invalid start timer parameter */
#define GPT_E_PARAM_WAKEUPCHL       (0x16u)   /* API called with not wakeup-capable channel */
#define GPT_E_PARAM_CONFIG          (0x1Eu)   /* Gpt_Init called with NULL_PTR param */
#define GPT_E_PARAM_MODE            (0x1Fu)   /* Gpt_SetMode is called with wrong mode parameter */
#define GPT_E_PARAM_VINFO           (0x20u)   /* Gpt_GetVersionInfo is called with NULL_PTR param */
#define GPT_E_NOTIFY_NULL           (0x21u)   /* Gpt_Notification function is NULL_PTR configured */
#define GPT_E_WAKEUP_VALIDATION     (0x22u)   /*Wakeup validation fails*/

/* Service Id's */
#define GPT_SID_GET_VERSION_INFO    (0x00u)   /* Service Id of Gpt_GetVersionInfo() */
#define GPT_SID_INIT                (0x01u)   /* Service Id of Gpt_Init() */
#define GPT_SID_DEINIT              (0x02u)   /* Service Id of Gpt_DeInit() */
#define GPT_SID_GET_TIME_ELAPSED    (0x03u)   /* Service Id of Gpt_GetTimeElapsed() */
#define GPT_SID_GET_TIME_REMAINING  (0x04u)   /* Service Id of Gpt_GetTimeRemaining() */
#define GPT_SID_START_TIMER         (0x05u)   /* Service Id of Gpt_StartTimer() */
#define GPT_SID_STOP_TIMER          (0x06u)   /* Service Id of Gpt_StopTimer() */
#define GPT_SID_ENABLE_NOTIFY       (0x07u)   /* Service Id of Gpt_EnableNotification() */
#define GPT_SID_DISABLE_NOTIFY      (0x08u)   /* Service Id of Gpt_DisableNotification() */
#define GPT_SID_SET_MODE            (0x09u)   /* Service Id of Gpt_SetMode() */
#define GPT_SID_DISABLE_WAKEUP      (0x0Au)   /* Service Id of Gpt_DisableWakeup() */
#define GPT_SID_ENABLE_WAKEUP       (0x0Bu)   /* Service Id of Gpt_EnableWakeup() */
#define GPT_SID_CBK_CHECK_WAKEUP    (0x0Cu)   /* Service Id of Gpt_Cbk_CheckWakeup() */

/* Defines for channel mode and the ISR_Function Array Indices */
#define GPT_MODE_CONTINUOUS     (0u)
#define GPT_MODE_ONESHOT        (1u)
#define GPT_MODE_CONT_WAKEUP    (2u)
#define GPT_MODE_ONESHOT_WAKEUP (3u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* type describing the timeout value */
typedef uint32 Gpt_ValueType;
/* type describing the ID of configured channels */
typedef uint32 Gpt_ChannelType;

/* List of process modes */
typedef enum {
    GPT_MODE_NORMAL  = 0,
    GPT_MODE_SLEEP
} Gpt_ModeType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define GPT_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */

FUNC(void, GPT_CODE) Gpt_InitMemory(void);

#if (STD_ON == GPT_VERSION_INFO_API)
FUNC(void, GPT_CODE) Gpt_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, GPT_APPL_DATA) versioninfo );
#endif /*(STD_ON == GPT_VERSION_INFO_API)*/

FUNC(void, GPT_CODE) Gpt_Init( P2CONST( Gpt_ConfigType, AUTOMATIC, GPT_CONST_PBCFG) configPtr );

#if (STD_ON == GPT_DEINIT_API)
FUNC(void, GPT_CODE) Gpt_DeInit( void );
#endif /*(STD_ON == GPT_DEINIT_API)*/

#if (STD_ON == GPT_TIME_ELAPSED_API)
FUNC(Gpt_ValueType, GPT_CODE) Gpt_GetTimeElapsed( Gpt_ChannelType channel );
#endif /*(STD_ON == GPT_TIME_ELAPSED_API)*/

#if (STD_ON == GPT_TIME_REMAINING_API)
FUNC(Gpt_ValueType, GPT_CODE) Gpt_GetTimeRemaining( Gpt_ChannelType channel );
#endif /*(STD_ON == GPT_TIME_REMAINING_API)*/

FUNC(void, GPT_CODE) Gpt_StartTimer( Gpt_ChannelType channel, Gpt_ValueType value );

FUNC(void, GPT_CODE) Gpt_StopTimer( Gpt_ChannelType channel );

#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)
FUNC(void, GPT_CODE) Gpt_EnableNotification( Gpt_ChannelType channel );
#endif /*(STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)*/

#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)
FUNC(void, GPT_CODE) Gpt_DisableNotification( Gpt_ChannelType channel );
#endif /*(STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)*/

#if (STD_ON == GPT_WAKEUP_FUNCTIONALITY_API)
FUNC(void, GPT_CODE) Gpt_SetMode( Gpt_ModeType mode );
#endif /*(STD_ON == GPT_WAKEUP_FUNCTIONALITY_API)*/

#if (STD_ON == GPT_WAKEUP_FUNCTIONALITY_API)
FUNC(void, GPT_CODE) Gpt_DisableWakeup( Gpt_ChannelType channel );
#endif /*(STD_ON == GPT_WAKEUP_FUNCTIONALITY_API)*/

#if (STD_ON == GPT_WAKEUP_FUNCTIONALITY_API)
FUNC(void, GPT_CODE) Gpt_EnableWakeup( Gpt_ChannelType channel );
#endif /*(STD_ON == GPT_WAKEUP_FUNCTIONALITY_API)*/

#if (STD_ON == GPT_WAKEUP_FUNCTIONALITY_API)
FUNC(void, GPT_CODE) Gpt_Cbk_CheckWakeup( EcuM_WakeupSourceType wakeupSource );
#endif /*(STD_ON == GPT_WAKEUP_FUNCTIONALITY_API)*/

#define GPT_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */


#endif  /* GPT_H */

/**********************************************************************************************************************
 *  END OF FILE: Gpt.h
 *********************************************************************************************************************/
