/* Copyright (C) 2010-2012 TTTech Automotive GmbH. All rights reserved
 * Schoenbrunnerstrasse 7, A-1040 Wien, Austria. office(at)tttech-automotive.com
 *
 * Name:
 *   WdgIf.c
 *
 * Purpose: Platform independent implementation of the Safe Watchdog Interface
 *          part of the Modular Safety Platform.
 *
 */

/* ------------------------------------------------------------------------- */
/*                        SUPRESSED MISRA VIOLATONS                          */
/* ------------------------------------------------------------------------- */
/* Error Message : Msg(4:1503) The function 'WdgIf_SetMode' /
                   'WdgIf_SetTriggerCondition' / 'WdgIf_SetTriggerWindow' /
                   'WdgIf_GetTickCounter'
                   is defined but is not used within this project.
 * Justification : The function is a library-API-function used by
 *                 the application.                                          */
/* Error Message : Msg(4:5087) #include statements in a file should only be
   preceded by other preprocessor directives or comments.
 * Justification : MemMap-pragmas must be included here. See AUTOSAR
 *                 requirement MEMMAP003.                                    */

/* ***************************************************************************
** Includes
******************************************************************************/
#include "WdgIf.h"
#if (WDGIF_DEV_ERROR_DETECT == STD_ON)
  #include "Appl_Det.h"
#endif

/* ***************************************************************************
** Source version
******************************************************************************/
#define WDGIF_SW_MAJOR_VERSION_SOURCE 2
#define WDGIF_SW_MINOR_VERSION_SOURCE 0
#define WDGIF_SW_PATCH_VERSION_SOURCE 2

/* Protection against incorrect include file version */
#if !(  (WDGIF_SW_MAJOR_VERSION ==     \
         WDGIF_SW_MAJOR_VERSION_SOURCE \
        )                              \
     && (WDGIF_SW_MINOR_VERSION ==     \
         WDGIF_SW_MINOR_VERSION_SOURCE \
        )                              \
     && (WDGIF_SW_PATCH_VERSION ==     \
         WDGIF_SW_PATCH_VERSION_SOURCE \
        )                              \
     )
  #error "Version mismatch! Incorrect version of WdgIf.h"
#endif

/* ***************************************************************************
** Module functions
******************************************************************************/
#define WDGIF_START_SEC_CODE
#include "MemMap.h"

/* PRQA S 1503 1 */
FUNC (Std_ReturnType, WDGIF_CODE) WdgIf_SetMode
    ( VAR (uint8, AUTOMATIC) DeviceIndex
    , VAR (WdgIf_ModeType, AUTOMATIC) WdgMode
    )
{
    VAR (uint8, AUTOMATIC) wdg_instance;
    VAR (Std_ReturnType, AUTOMATIC) ret;

    /* Check DeviceIndex and report to DET if necessary and enabled */
    if (  (WdgIf_Interface.WdgFunctionsPerDevice == NULL_PTR)
       || (DeviceIndex >= WdgIf_Interface.NumOfWdgs)
       || (WdgIf_Interface.WdgFunctionsPerDevice[DeviceIndex].WdgFunctions == NULL_PTR)
       )
    {
      #if (WDGIF_DEV_ERROR_DETECT == STD_ON)
        Appl_Det_ReportError(WDGIF_MODULE_ID,WDGIF_VENDOR_ID,API_ID_WdgIf_SetMode,WDGIF_E_PARAM_DEVICE);
      #endif /* WDGIF_DEV_ERROR_DETECT == STD_ON */
        ret = E_NOT_OK;
    }
    /* If DET checks were successful */
    else
    {
        /* Identify watchdog instance, if more than one of the same type */
        wdg_instance = WdgIf_Interface.WdgFunctionsPerDevice [DeviceIndex].WdgInstance;

        /* Call corresponding platform-specific implementation */
        ret = WdgIf_Interface.WdgFunctionsPerDevice [DeviceIndex].WdgFunctions->
            Wdg_SetMode (wdg_instance, WdgMode);
    }

    return ret;
}

/* PRQA S 1503 1 */
FUNC (Std_ReturnType, WDGIF_CODE) WdgIf_SetTriggerCondition
    ( VAR (uint8, AUTOMATIC) DeviceIndex
    , VAR (uint16, AUTOMATIC) Timeout
    )
{
    VAR (uint8, AUTOMATIC) wdg_instance;
    VAR (Std_ReturnType, AUTOMATIC) ret;

    /* Check DeviceIndex and report to DET if necessary and enabled */
    if (  (WdgIf_Interface.WdgFunctionsPerDevice == NULL_PTR)
       || (DeviceIndex >= WdgIf_Interface.NumOfWdgs)
       || (WdgIf_Interface.WdgFunctionsPerDevice[DeviceIndex].WdgFunctions == NULL_PTR)
       )
    {
      #if (WDGIF_DEV_ERROR_DETECT == STD_ON)
        Appl_Det_ReportError(WDGIF_MODULE_ID,WDGIF_VENDOR_ID,API_ID_WdgIf_SetTriggerCondition,WDGIF_E_PARAM_DEVICE);
      #endif /* WDGIF_DEV_ERROR_DETECT == STD_ON */
        ret = E_NOT_OK;
    }
    /* If DET checks were successful */
    else
    {
        /* Identify watchdog instance, if more than one of the same type */
        wdg_instance = WdgIf_Interface.WdgFunctionsPerDevice [DeviceIndex].WdgInstance;

        /* Call corresponding platform-specific implementation */
        ret = WdgIf_Interface.WdgFunctionsPerDevice [DeviceIndex].WdgFunctions->
            Wdg_SetTriggerWindow (wdg_instance, 0, Timeout);
    }

    return ret;
}

/* PRQA S 1503 1 */
FUNC (Std_ReturnType, WDGIF_CODE) WdgIf_SetTriggerWindow
    ( VAR (uint8, AUTOMATIC) DeviceIndex
    , VAR (uint16, AUTOMATIC) WindowStart
    , VAR (uint16, AUTOMATIC) Timeout
    )
{
    VAR (uint8, AUTOMATIC) wdg_instance;
    VAR (Std_ReturnType, AUTOMATIC) ret;

    /* Check DeviceIndex and report to DET if necessary and enabled */
    if (  (WdgIf_Interface.WdgFunctionsPerDevice == NULL_PTR)
       || (DeviceIndex >= WdgIf_Interface.NumOfWdgs)
       || (WdgIf_Interface.WdgFunctionsPerDevice[DeviceIndex].WdgFunctions == NULL_PTR)
       )
    {
      #if (WDGIF_DEV_ERROR_DETECT == STD_ON)
        Appl_Det_ReportError(WDGIF_MODULE_ID,WDGIF_VENDOR_ID,API_ID_WdgIf_SetTriggerWindow,WDGIF_E_PARAM_DEVICE);
      #endif /* WDGIF_DEV_ERROR_DETECT == STD_ON */
        ret = E_NOT_OK;
    }
    /* If DET checks were successful */
    else
    {
        /* Identify watchdog instance, if more than one of the same type */
        wdg_instance = WdgIf_Interface.WdgFunctionsPerDevice [DeviceIndex].WdgInstance;

        /* Call corresponding platform-specific implementation */
        ret = WdgIf_Interface.WdgFunctionsPerDevice [DeviceIndex].WdgFunctions->
            Wdg_SetTriggerWindow (wdg_instance, WindowStart, Timeout);
    }

    return ret;
}

#if (WDGIF_INTERNAL_TICK_COUNTER == STD_ON)
/* PRQA S 1503 1 */
FUNC (void, WDGIF_CODE) WdgIf_GetTickCounter
    (P2VAR (uint32, AUTOMATIC, WDGIF_APPL_DATA) TickCounter)
{
    if (TickCounter== NULL_PTR)
    {
      #if (WDGIF_DEV_ERROR_DETECT == STD_ON)
        Appl_Det_ReportError ( WDGIF_MODULE_ID
                             , WDGIF_VENDOR_ID
                             , API_ID_WdgIf_GetVersionInfo
                             , WDGIF_E_PARAM_PTR
                             );
      #endif /* WDGIF_DEV_ERROR_DETECT == STD_ON */
    }
    else
    {
        /* Write in the output parameter the counter value provided from the watchdog driver*/
        *TickCounter = WdgIf_Interface.Wdg_GetTickCounter();
    }
}
#endif /* WDGIF_INTERNAL_TICK_COUNTER == STD_ON */

#if (WDGIF_VERSION_INFO_API == STD_ON)
/* PRQA S 1503 1 */
FUNC (void, WDGIF_CODE) WdgIf_GetVersionInfo
    (P2VAR (Std_VersionInfoType, AUTOMATIC, WDGIF_APPL_DATA) VersionInfoPtr)
{
    if (VersionInfoPtr == NULL_PTR)
    {
      #if (WDGIF_DEV_ERROR_DETECT == STD_ON)
        Appl_Det_ReportError ( WDGIF_MODULE_ID
                             , WDGIF_VENDOR_ID
                             , API_ID_WdgIf_GetVersionInfo
                             , WDGIF_E_PARAM_PTR
                             );
      #endif /* WDGIF_DEV_ERROR_DETECT == STD_ON */
    }
    else
    {
        VersionInfoPtr->vendorID         = WDGIF_VENDOR_ID;
        VersionInfoPtr->moduleID         = WDGIF_MODULE_ID;
        VersionInfoPtr->sw_major_version = WDGIF_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = WDGIF_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = WDGIF_SW_PATCH_VERSION;
    }
}
#endif /* WDGIF_VERSION_INFO_API == STD_ON */

#define WDGIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */
