/* Copyright (C) 2010-2012 TTTech Automotive GmbH. All rights reserved
 * Schoenbrunnerstrasse 7, A-1040 Wien, Austria. office(at)tttech-automotive.com
 *
 * Name:
 *   WdgIf.h
 *
 * Purpose: Common include file for the Safe Watchdog Manager.
 *
 */

/* ------------------------------------------------------------------------- */
/*                        SUPRESSED MISRA VIOLATONS                          */
/* ------------------------------------------------------------------------- */
/* Error Message : Msg(3:3210) The global identifier 'WdgIf_Interface' /
                   'WdgIf_SetMode' / 'WdgIf_SetTriggerCondition' /
                   'WdgIf_SetTriggerWindow' / 'WdgIf_GetTickCounter'
                   is declared but is not used.
 * Justification : The function is the interface of this SW module to the upper
                   SW layers.                                                */
/* Error Message : Msg(4:3408) 'WdgIf_SetMode' / 'WdgIf_SetTriggerCondition' /
                   'WdgIf_SetTriggerWindow' / 'WdgIf_GetTickCounter'
                   has external linkage but is being defined without any
                   previous declaration.
 * Justification : The function is the interface of this SW module to the upper
                   SW layers and is declared in this header file.            */
/* Error Message : Msg(4:3447) 'WdgIf_Interface' has external linkage but this
                   declaration is not in a header file.
 * Justification : The declaration is in a header file - this file.          */
/* Error Message : Msg(6:0288) [I] Source file 'WdgIf.h' has comments containing
                   characters which are not members of the basic source
                   character set.
 * Justification : The (at) character is needed for doxygen comments.         */
/* PRQA S 0288 EOF */

#ifndef _WDGIF_H_
#define _WDGIF_H_

/* ***************************************************************************
** Includes
******************************************************************************/
#include "WdgIf_Cfg.h"

/* ***************************************************************************
** Macros
******************************************************************************/

/* Published information */
#define WDGIF_VENDOR_ID  46
#define WDGIF_MODULE_ID  43

/* Version information */
#define WDGIF_SW_MAJOR_VERSION  2
#define WDGIF_SW_MINOR_VERSION  0
#define WDGIF_SW_PATCH_VERSION  2

/* AUTOSAR release version */
#define WDGIF_AR_MAJOR_VERSION  4
#define WDGIF_AR_MINOR_VERSION  0
#define WDGIF_AR_PATCH_VERSION  1

/** API Service ID for WdgIf_SetMode */
#define API_ID_WdgIf_SetMode             0x01u

/** API Service ID for WdgIf_SetTriggerCondition */
#define API_ID_WdgIf_SetTriggerCondition 0x02u

/** API Service ID for WdgIf_GetVersionInfo */
#define API_ID_WdgIf_GetVersionInfo      0x03u

/** API Service ID for WdgIf_SetTriggerWindow */
#define API_ID_WdgIf_SetTriggerWindow    0x04u

/* DET codes */
#define WDGIF_E_PARAM_DEVICE 0x01u
#define WDGIF_E_PARAM_PTR    0x02u

/* ***************************************************************************
** Externals
******************************************************************************/
/* Define the external variable WdgIf_Interface as const, if unit tests are
   compiled - define it as non const. */
#ifndef WDGIF_UNIT_TESTS
    #define WDGIF_CONST_FOR_CONFIG_PTR const
#else
  #if (WDGIF_UNIT_TESTS == 1u)
    #define WDGIF_CONST_FOR_CONFIG_PTR
  #else
    #define WDGIF_CONST_FOR_CONFIG_PTR const
  #endif /* (WDGIF_UNIT_TESTS == 1) */
#endif
/* PRQA S 3210 1 */ /* PRQA S 3447 1 */
extern WDGIF_CONST_FOR_CONFIG_PTR WdgIf_InterfaceType WdgIf_Interface;

/* ***************************************************************************
** Prototypes
******************************************************************************/

/**
 *  Function selects a Watchdog Mode.
 *
 *  @param DeviceIndex (in)      index of the Watchdog device
 *  @param WdgMode (in)          new mode to be set
 *
 * @return an error-code
 *  @retval E_OK                 new mode selected successfully
 *  @retval E_NOT_OK             an error occurred
 */
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC (Std_ReturnType, WDGIF_CODE) WdgIf_SetMode
    ( VAR (uint8, AUTOMATIC) DeviceIndex
    , VAR (WdgIf_ModeType, AUTOMATIC) WdgMode
    );

/**
 *  Function triggers the Watchdog and set a new timeout.
 *
 *  @param DeviceIndex (in)      index of the Watchdog device
 *  @param Timeout (in)          new timeout to be set
 *
 * @return an error-code
 *  @retval E_OK                 the trigger and timeout set was successfull
 *  @retval E_NOT_OK             an error occurred
 */
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC (Std_ReturnType, WDGIF_CODE) WdgIf_SetTriggerCondition
    ( VAR (uint8, AUTOMATIC) DeviceIndex
    , VAR (uint16, AUTOMATIC) Timeout
    );

/**
 *  Function triggers the Watchdog and set a new window start and timeout.
 *
 *  @param DeviceIndex (in)      index of the Watchdog device
 *  @param WindowStart (in)      new window start time to be set
 *  @param Timeout (in)          new timeout to be set
 *
 * @return an error-code
 *  @retval E_OK                 the trigger, window start and timeout set was successfull
 *  @retval E_NOT_OK             an error occurred
 */
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC (Std_ReturnType, WDGIF_CODE) WdgIf_SetTriggerWindow
    ( VAR (uint8, AUTOMATIC) DeviceIndex
    , VAR (uint16, AUTOMATIC) WindowStart
    , VAR (uint16, AUTOMATIC) Timeout
    );

/**
 *  Function returns the module version.
 *
 *  @param VersionInfoPtr (in)   pointer to where to store the version info
 *
 * @return void
 */
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC (void, WDGIF_CODE) WdgIf_GetVersionInfo
    (P2VAR (Std_VersionInfoType, AUTOMATIC, WDGIF_APPL_DATA) VersionInfoPtr);

#if (WDGIF_INTERNAL_TICK_COUNTER == STD_ON)
/**
 *  Function reads the hardware Tick counter.
 *
 *  @param TickCounter (in)      pointer to where the Tick counter to store
 *
 * @return  void
 */
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC (void, WDGIF_CODE) WdgIf_GetTickCounter
    (P2VAR (uint32, AUTOMATIC, WDGIF_APPL_DATA) TickCounter);
#endif /* (WDGIF_INTERNAL_TICK_COUNTER == STD_ON) */

#endif /* _WDGIF_H_ */
