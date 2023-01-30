/* Copyright (C) 2011-2012 TTTech Automotive GmbH. All rights reserved
** Schoenbrunnerstrasse 7, A-1040 Wien, Austria. office(at)tttech-automotive.com
**
** Name:
**   Wdg_TMS570LS3x.c
**
** Purpose: Platform specific implementation (TMS570LS3x) of the Safe Watchdog
**          Driver part of the Modular Safety Platform.
**
*/

/* ***************************************************************************
** Includes
******************************************************************************/
#include "Wdg_TMS570LS3x.h"
#include "Wdg_TMS570LS3x_reg_defs.h"
#if (WDG_DEM_REPORT == STD_ON)
    #include "Appl_Dem.h"
#endif
#if (WDG_DEV_ERROR_DETECT == STD_ON)
  #include "Appl_Det.h"
#endif

#if ((defined(__CANTATA__)) || (defined(PC_TEST)))
  #if ((__CANTATA__ == 1) || (defined(PC_TEST)))
    #include "tms570ls3x_wdg_emulation.h"
  #endif
#endif

/* ***************************************************************************
** Source version
******************************************************************************/
#define WDG_TMS570LS3x_SW_MAJOR_VERSION_SOURCE 2
#define WDG_TMS570LS3x_SW_MINOR_VERSION_SOURCE 0
#define WDG_TMS570LS3x_SW_PATCH_VERSION_SOURCE 3

/* defines for expected Wdg.h Version */
#define EXPECTED_WDG_SW_MAJOR_VERSION       2
#define EXPECTED_WDG_SW_MINOR_VERSION       0
/* defines for expected Wdg_Cfg.h Version */
#define EXPECTED_WDG_CFG_SW_MAJOR_VERSION   2
#define EXPECTED_WDG_CFG_SW_MINOR_VERSION   0

/* Protection against incorrect include file version */
#if !(  (WDG_TMS570LS3x_SW_MAJOR_VERSION ==     \
         WDG_TMS570LS3x_SW_MAJOR_VERSION_SOURCE \
        )                                       \
     && (WDG_TMS570LS3x_SW_MINOR_VERSION ==     \
         WDG_TMS570LS3x_SW_MINOR_VERSION_SOURCE \
        )                                       \
     && (WDG_TMS570LS3x_SW_PATCH_VERSION ==     \
         WDG_TMS570LS3x_SW_PATCH_VERSION_SOURCE \
        )                                       \
     )
  #error "Version mismatch! Incorrect version of Wdg_TMS570LS3x.h"
#endif

/* Protection against incorrect Wdg_TMS570LS3x_Cfg.h include file version */
#if !(  (WDG_TMS570LS3x_CFG_SW_MAJOR_VERSION == \
         WDG_TMS570LS3x_SW_MAJOR_VERSION_SOURCE \
        )                                       \
     && (WDG_TMS570LS3x_CFG_SW_MINOR_VERSION == \
         WDG_TMS570LS3x_SW_MINOR_VERSION_SOURCE \
        )                                       \
     && (WDG_TMS570LS3x_CFG_SW_PATCH_VERSION == \
         WDG_TMS570LS3x_SW_PATCH_VERSION_SOURCE \
        )                                       \
     )
  #error "Version mismatch! Incorrect version of Wdg_TMS570LS3x_Cfg.h"
#endif

/* Protection against incorrect Wdg_TMS570LS3x_reg_defs.h include file version */
#if !(  (WDG_TMS570LS3x_REG_DEFS_SW_MAJOR_VERSION == \
         WDG_TMS570LS3x_SW_MAJOR_VERSION_SOURCE      \
        )                                            \
     && (WDG_TMS570LS3x_REG_DEFS_SW_MINOR_VERSION == \
         WDG_TMS570LS3x_SW_MINOR_VERSION_SOURCE      \
        )                                            \
     && (WDG_TMS570LS3x_REG_DEFS_SW_PATCH_VERSION == \
         WDG_TMS570LS3x_SW_PATCH_VERSION_SOURCE      \
        )                                            \
     )
  #error "Version mismatch! Incorrect version of Wdg_TMS570LS3x_reg_defs.h"
#endif

/* Protection against incorrect Wdg.h include file version */
#if !(  (WDG_SW_MAJOR_VERSION ==                 \
         EXPECTED_WDG_SW_MAJOR_VERSION           \
        )                                        \
     && (WDG_SW_MINOR_VERSION ==                 \
         EXPECTED_WDG_SW_MINOR_VERSION           \
        )                                        \
     )
  #error "Version mismatch! Incorrect version of Wdg.h"
#endif

/* Protection against incorrect Wdg_Cfg.h include file version */
#if !(  (WDG_CFG_SW_MAJOR_VERSION ==             \
         EXPECTED_WDG_CFG_SW_MAJOR_VERSION       \
        )                                        \
     && (WDG_CFG_SW_MINOR_VERSION ==             \
         EXPECTED_WDG_CFG_SW_MINOR_VERSION       \
        )                                        \
     )
  #error "Version mismatch! Incorrect version of Wdg_Cfg.h"
#endif

/* ------------------------------------------------------------------------- */
/*                        SUPRESSED MISRA VIOLATONS                          */
/* ------------------------------------------------------------------------- */
/* Error Message : Msg(4:1503) The function 'Wdg_TMS570LS3x_Init' /
                   'Wdg_TMS570LS3x_SetMode' /
                   'Wdg_TMS570LS3x_SetTriggerWindow' /
                   'Wdg_TMS570LS3x_GetVersionInfo'
                   is defined but is not used within this project.
 * Justification : The function is an interface of this SW module to the upper
                   SW layers, such as WdgIf.                                 */

/* Error Message : Msg(4:5087) #include statements in a file should only be
                   preceded by other preprocessor directives or comments.
 * Justification : MemMap-pragmas must be included here. See AUTOSAR
 *                 requirement MEMMAP003.                                    */

/* Error Message : Msg(4:0303) [I] Cast between a pointer to object and an
                   integral type.
 * Justification : RTIDWDCTRL, RTIDWDPRLD, RTIWDKEY and RTIDWDCNTR are
                   TMS570LS3x specific registers, which are situated at fixed
                   addresses in the memory.                                  */

/* Error Message : Msg(4:3335) No function declaration. Implicit declaration
                   inserted: 'extern int GlobalSuspendInterrupts();' /
                   'extern int GlobalRestoreInterrupts();'.
 * Justification : These are compiler intrinsic function.                    */

/* Error Message : Msg(4:3356) The result of this logical operation is always
                   'false'.
                   Msg(4:3359) The value of this control expression is always
                   'false'.
 * Justification : According to AUTOSAR a DET check for this parameter is
                   necessary. Furthermore, it is possible that the caller
                   function passes a wrong value for the parameter of the enum
                   type WdgIf_ModeType, e.g. via a unit8 variable.           */

/* Error Message : Msg(4:1317) Value not in the enumeration type.
 * Justification : Inverted value of the variabled is stored here for memory
                   check, it is intended that the value is out of bounds.     */

/* Error Message : Msg(6:0306) [I] Cast between a pointer to object and an
                   integral type.
 * Justification : Inverted value of the pointer is stored in the variable on
                   purpose in order to check for memory corruption.           */

/* Error Message : Msg(6:0277) [I] An integer constant expression with negative
                   value is being converted to an unsigned type.
 * Justification : Inverted value of the integer constant is stored in the
                   variable on purpose in order to check for memory
                   corruption.                                                */

/* Error Message : Msg(4:3355) The result of this logical operation is always
                   'true'.
 * Justification : The inverted value of a variable and the variable itself
                   differ if some other software module overwrites the memory.
                   That this logical operation may become false is proven within
                   the unit tests.                                            */

/* Error Message : Msg(4:3358) The value of this 'if' control expression is
                   always 'true'.
 * Justification : The inverted value of a variable and the variable itself
                   differ if some other software module overwrites the memory.
                   that this logical operation may become false is proven within
                   the unit tests.                                            */

/* Error Message : Msg(4:3201) This statement is unreachable.
 * Justification : The statement is indeed reachable: it is possible that the
                   caller function passes a wrong value for the parameter of
                   the enum type WdgIf_ModeType, e.g. via a unit8 variable.  */

/* Error Message : Msg(4:3453) A function could probably be used instead of this
                   function-like macro.
 * Justification : This simple computation is used only once in the code and is
                   realized as a macro in the beginnig of the file together with
                   other computations for a better code readybility. A function
                   would be very inefficient. */

/* ***************************************************************************
** Globals
******************************************************************************/
#define WDG_START_SEC_VAR_8BIT
#include "MemMap.h"
STATIC VAR(WdgIf_ModeType, WDG_VAR) g_wdg_tms570ls3x_current_mode = WDGIF_OFF_MODE;
/* PRQA S 1317 2 */
STATIC VAR(WdgIf_ModeType, WDG_VAR) g_wdg_tms570ls3x_current_mode_INV =
    (WdgIf_ModeType)~WDGIF_OFF_MODE;
#define WDG_STOP_SEC_VAR_8BIT
#include "MemMap.h" /* PRQA S 5087 */

#define WDG_START_SEC_VAR_32BIT
#include "MemMap.h" /* PRQA S 5087 */
/* global variable to save the current Configuration Pointer of the Watchdog */
STATIC P2CONST(Wdg_TMS570LS3x_ConfigType, WDG_VAR, WDG_CONST) g_wdg_tms570ls3x_cfg_ptr = NULL_PTR;
/* global variable to save the inverted value of the current Configuration Pointer */
/* PRQA S 0306 2 */
STATIC P2CONST(Wdg_TMS570LS3x_ConfigType, WDG_VAR, WDG_CONST) g_wdg_tms570ls3x_cfg_ptr_INV =
    (const Wdg_TMS570LS3x_ConfigType *)(~(uint32)NULL_PTR);
#define WDG_STOP_SEC_VAR_32BIT
#include "MemMap.h" /* PRQA S 5087 */

#define WDG_START_SEC_VAR_16BIT
#include "MemMap.h" /* PRQA S 5087 */
/* global variable to save the current Window of the Watchdog */
STATIC VAR(uint16, WDG_VAR) g_wdg_tms570ls3x_window_start = 0u; /* in ms */
/* global variable to save the inverted value of the current Window of the Watchdog */
/* PRQA S 0277 1 */
STATIC VAR(uint16, WDG_VAR) g_wdg_tms570ls3x_window_start_INV = (uint16)~0u;
/* global variable to save the current Timeout of the Watchdog */
STATIC VAR(uint16, WDG_VAR) g_wdg_tms570ls3x_last_timeout = 0u; /* in ms */
/* global variable to save the inverted value of the current Timeout of the Watchdog */
/* PRQA S 0277 1 */
STATIC VAR(uint16, WDG_VAR) g_wdg_tms570ls3x_last_timeout_INV = (uint16)~0u;
#define WDG_STOP_SEC_VAR_16BIT
#include "MemMap.h" /* PRQA S 5087 */


/* ***************************************************************************
** Macros
******************************************************************************/

#define READ_RTIDWDPRLD (*RTIDWDPRLD)
#define READ_RTIDWDCNTR (*RTIDWDCNTR)
#define READ_RTIWDKEY   (*RTIWDKEY)
#define READ_RTIDWDCTRL (*RTIDWDCTRL)
#define READ_RTIFRC1    (*RTIFRC1)
#define READ_RTICPUC1   (*RTICPUC1)
#define READ_RTIGCTRL   (*RTIGCTRL)

#if ((!defined(__CANTATA__)) && (!defined(PC_TEST)))
    #define WRITE_RTIDWDPRLD (*RTIDWDPRLD) =
    #define WRITE_RTIDWDCNTR (*RTIDWDCNTR) =
    #define WRITE_RTIWDKEY   (*RTIWDKEY)   =
    #define WRITE_RTIDWDCTRL (*RTIDWDCTRL) =
  #if (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON)
    #define WRITE_RTICPUC1   (*RTICPUC1) =
    #define WRITE_RTIGCTRL   (*RTIGCTRL) =
  #endif /* (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON) */
#else
    #define WRITE_RTIDWDPRLD pc_write_RTIDWDPRLD
    #define WRITE_RTIDWDCNTR pc_write_RTIDWDCNTR
    #define WRITE_RTIWDKEY   pc_write_RTIWDKEY
    #define WRITE_RTIDWDCTRL pc_write_RTIDWDCTRL
  #if (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON)
    #define WRITE_RTICPUC1   pc_write_RTICPUC1
    #define WRITE_RTIGCTRL   pc_write_RTIGTRL
  #endif /* (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON) */
#endif

/* PRQA S 3453 2 */
#define WDG_TMS570LS3x_MS_TO_PRLD(_ms,_RTICLK_khz) \
    ((((uint32)(_ms) * (_RTICLK_khz)) / (1u << 13u)) - 1u)

/* PRQA S 3453 2 */
#define WDG_TMS570LS3x_WDTICKS_TO_MS(_wdticks,_RTICLK_khz) \
    ((_wdticks) / (_RTICLK_khz))

/* PRQA S 3453 2 */
#define WDG_TMS570LS3x_MS_TO_WDTICKS(_ms,_RTICLK_khz) \
    ((uint32)(_ms) * (_RTICLK_khz))

#if (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON)
/* PRQA S 3453 2 */
#define WDG_TMS570LS3x_TICKS_TO_CPUC(_ticks,_RTICLK_khz) \
    ((((_RTICLK_khz) * 1000u) / (_ticks)) - 1u)
#endif /* (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON) */


/* ***************************************************************************
** Module internal functions
******************************************************************************/

/* Internal functions' prototypes */
STATIC FUNC (void, WDG_CODE) wdg_tms570ls3x_reset (void);
STATIC FUNC (Std_ReturnType, WDG_CODE) wdg_tms570ls3x_check_window_start
    ( VAR (uint16, AUTOMATIC) window_start
    , VAR (uint16, AUTOMATIC) last_timeout
    , VAR (uint32, AUTOMATIC) rtickl_khz
    );
STATIC FUNC (Wdg_TMS570LS3x_ConfigChecksumType, WDG_CODE) wdg_tms570ls3x_checksum
    (P2CONST (Wdg_TMS570LS3x_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr);

#define WDG_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */

STATIC FUNC (void, WDG_CODE) wdg_tms570ls3x_reset (void)
{
    (void) Wdg_GlobalSuspendInterrupts(); /* PRQA S 3335 */
    /* Prepare the KEY register and then write a wrong value */
    WRITE_RTIWDKEY (RTIWDKEY_PREPARE); /* PRQA S 0303 */
    /* Now write a wrong value, RTIWDKEY_TRIGGER expected */
    WRITE_RTIWDKEY (RTIWDKEY_WRONG_VAL); /* PRQA S 0303 */
    /* Not reached, if HW is working correctly */
    (void) Wdg_GlobalRestoreInterrupts(); /* PRQA S 3335 */
}

STATIC FUNC (Std_ReturnType, WDG_CODE) wdg_tms570ls3x_check_window_start
    ( VAR (uint16, AUTOMATIC) window_start
    , VAR (uint16, AUTOMATIC) last_timeout
    , VAR (uint32, AUTOMATIC) rtickl_khz
    )
{
    VAR (uint32, AUTOMATIC) elapsed_time_wdticks;   /* since last watchdog service in wdticks */
    VAR (uint32, AUTOMATIC) remaining_time_wdticks; /* until watchdog overflow in wdticks */
    VAR (uint32, AUTOMATIC) last_timeout_wdticks;   /* last set timeout in wdticks */
    VAR (uint32, AUTOMATIC) last_window_wdticks;    /* last set window in wdticks */
    VAR (Std_ReturnType, AUTOMATIC) ret = E_OK;

    /* Perform check only if a window is set */
    if (window_start > 0u)
    {
        remaining_time_wdticks = READ_RTIDWDCNTR; /* PRQA S 0303 */
        last_timeout_wdticks = WDG_TMS570LS3x_MS_TO_WDTICKS
                                (last_timeout, rtickl_khz);
        last_window_wdticks  = WDG_TMS570LS3x_MS_TO_WDTICKS
                                (window_start, rtickl_khz);

        /* Remaining time cannot be greater than last set timeout - otherwise a watchdog */
        /* timeout would already have occurred.                                          */
        elapsed_time_wdticks = last_timeout_wdticks - remaining_time_wdticks;

        /* Is this an attempt to trigger the watchdog earlier than the set window? */
        if (elapsed_time_wdticks < last_window_wdticks)
        {
            /* Start Window violation! Perform Watchdog reset! */
            ret = E_NOT_OK;
            wdg_tms570ls3x_reset ();
        }
    }

    return ret;
}

STATIC FUNC (Wdg_TMS570LS3x_ConfigChecksumType, WDG_CODE) wdg_tms570ls3x_checksum
    (P2CONST (Wdg_TMS570LS3x_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr)
{
    VAR (Wdg_TMS570LS3x_ConfigChecksumType, AUTOMATIC) cs = 0u;

    /* Basic configuration */
    cs += ((Wdg_TMS570LS3x_ConfigChecksumType) ConfigPtr->BasicCfgPtr->InitialMode)           << 0u;
    cs += ((Wdg_TMS570LS3x_ConfigChecksumType) ConfigPtr->BasicCfgPtr->InitialTimeout_ms)     << 1u;
    cs += ((Wdg_TMS570LS3x_ConfigChecksumType) ConfigPtr->BasicCfgPtr->InitialWindowStart_ms) << 0u;
    cs += ((Wdg_TMS570LS3x_ConfigChecksumType) ConfigPtr->BasicCfgPtr->SlowModeMax_ms)        << 1u;
    cs += ((Wdg_TMS570LS3x_ConfigChecksumType) ConfigPtr->BasicCfgPtr->FastModeMax_ms)        << 0u;

    /* Module version */
    cs += ((Wdg_TMS570LS3x_ConfigChecksumType) ConfigPtr->BasicCfgPtr->WdgConfigMajorVersion) << 1u;
    cs += ((Wdg_TMS570LS3x_ConfigChecksumType) ConfigPtr->BasicCfgPtr->WdgConfigMinorVersion) << 0u;

    /* TMS570LS3x specific configuration parameters */
    cs += ((Wdg_TMS570LS3x_ConfigChecksumType) ConfigPtr->RTICLK_khz)  << 0u;
    #if (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON)
    cs += ((Wdg_TMS570LS3x_ConfigChecksumType) ConfigPtr->TickFreq_hz) << 1u;
    #endif /* (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON) */

    return cs;
}

#define WDG_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */

/* ***************************************************************************
** Module functions
******************************************************************************/
#define WDG_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */

/* PRQA S 1503 1 */
FUNC(Std_ReturnType, WDG_CODE) Wdg_TMS570LS3x_Init
    (P2CONST(Wdg_TMS570LS3x_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr)
{
    VAR (Std_ReturnType, AUTOMATIC) ret = E_NOT_OK;
    VAR(uint16, AUTOMATIC) window_start;
    VAR(uint16, AUTOMATIC) last_timeout;
    VAR(WdgIf_ModeType, AUTOMATIC) current_mode;
    P2CONST (Wdg_BasicConfigurationType, AUTOMATIC, WDG_APPL_CONST) basic_cfg_ptr;
    P2CONST (Wdg_TMS570LS3x_ConfigType, AUTOMATIC, WDG_APPL_CONST) config_ptr;
    VAR (uint32, AUTOMATIC) reg_prld;
    VAR (uint32, AUTOMATIC) reg_ctrl;
    VAR (uint32, AUTOMATIC) rtidwdprld_value;
  #if (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON)
    VAR (uint32, AUTOMATIC) reg_gctrl;
    VAR (uint32, AUTOMATIC) reg_cpuc1;
    VAR (uint32, AUTOMATIC) rtigctrl_value;
    VAR (uint32, AUTOMATIC) rticpuc1_value;
  #endif /* (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON) */

    /* check global variables for consistency */
    window_start = g_wdg_tms570ls3x_window_start;
    last_timeout = g_wdg_tms570ls3x_last_timeout;
    current_mode = g_wdg_tms570ls3x_current_mode;
    config_ptr   = g_wdg_tms570ls3x_cfg_ptr;
    /* PRQA S 3355 5 */ /* PRQA S 3358 5 */
    if ( ((uint16)~window_start != g_wdg_tms570ls3x_window_start_INV)
      || ((uint16)~last_timeout != g_wdg_tms570ls3x_last_timeout_INV)
      || ((WdgIf_ModeType)~current_mode != g_wdg_tms570ls3x_current_mode_INV)
      || ((uint32)~(uint32)config_ptr != (uint32)g_wdg_tms570ls3x_cfg_ptr_INV) /* PRQA S 0306 */
       )
    {
        /* Memory courruption detected! Perform a RESET */
        ret = E_NOT_OK;
        wdg_tms570ls3x_reset ();
    }

    /* Development error detect */
    /* PRQA S 3201 1 */
    else if (ConfigPtr == NULL_PTR)
    {
        #if (WDG_DEV_ERROR_DETECT == STD_ON)
        Appl_Det_ReportError ( WDG_TMS570LS3x_MODULE_ID
                             , WDG_TMS570LS3x_VENDOR_ID
                             , API_ID_Wdg_Init
                             , WDG_E_PARAM_CONFIG
                             );
        #endif
    }
    else if (ConfigPtr->BasicCfgPtr == NULL_PTR)
    {
        #if (WDG_DEV_ERROR_DETECT == STD_ON)
        Appl_Det_ReportError ( WDG_TMS570LS3x_MODULE_ID
                             , WDG_TMS570LS3x_VENDOR_ID
                             , API_ID_Wdg_Init
                             , WDG_E_PARAM_CONFIG
                             );
        #endif
    }
    /* PRQA S 3359 1 */ /* PRQA S 3356 1 */
    else if (ConfigPtr->BasicCfgPtr->InitialMode > WDGIF_FAST_MODE)
    /* PRQA S 3201 1 */
    {
        #if (WDG_DEV_ERROR_DETECT == STD_ON)
        Appl_Det_ReportError ( WDG_TMS570LS3x_MODULE_ID
                             , WDG_TMS570LS3x_VENDOR_ID
                             , API_ID_Wdg_Init
                             , WDG_E_PARAM_CONFIG
                             );
        #endif
    }
    else if ( (ConfigPtr->BasicCfgPtr->WdgConfigMajorVersion != WDG_TMS570LS3x_SW_MAJOR_VERSION_SOURCE)
           || (ConfigPtr->BasicCfgPtr->WdgConfigMinorVersion != WDG_TMS570LS3x_SW_MINOR_VERSION_SOURCE)
            )
    {
        #if (WDG_DEV_ERROR_DETECT == STD_ON)
        Appl_Det_ReportError ( WDG_TMS570LS3x_MODULE_ID
                             , WDG_TMS570LS3x_VENDOR_ID
                             , API_ID_Wdg_Init
                             , WDG_E_PARAM_CONFIG
                             );
        #endif
    }
    else if (wdg_tms570ls3x_checksum (ConfigPtr) != ConfigPtr->ConfigChecksum)
    {
        #if (WDG_DEV_ERROR_DETECT == STD_ON)
        Appl_Det_ReportError ( WDG_TMS570LS3x_MODULE_ID
                             , WDG_TMS570LS3x_VENDOR_ID
                             , API_ID_Wdg_Init
                             , WDG_E_PARAM_CONFIG
                             );
        #endif
    }
    else
    /* If DET checks were successful */
    {
        #if (WDG_DISABLE_ALLOWED == STD_OFF)
        if (ConfigPtr->BasicCfgPtr->InitialMode == WDGIF_OFF_MODE)
        {
            #if (WDG_DEM_REPORT == STD_ON)
            /* If not allowed report failure */
            Appl_Dem_ReportErrorStatus ( WDG_E_DISABLE_REJECTED
                                       , DEM_EVENT_STATUS_FAILED
                                       );
            #endif
        }
        else
        {
        #endif /* WDG_DISABLE_ALLOWED == STD_OFF */

            /* Perform init */
            basic_cfg_ptr = ConfigPtr->BasicCfgPtr;

            /* Check if already initialized and if so - check timeout value */
            if (config_ptr != NULL_PTR)
            {
                /* Check window start, if already initialized
                   (and therefore running) */
                /* If first call of Init then window start is 0 and the check
                   cannot lead to reset. */
                ret = wdg_tms570ls3x_check_window_start
                    (window_start, last_timeout, config_ptr->RTICLK_khz);

                /* ret is here E_NOT_OK only if the window was violated but no
                   reset occurred. This could happen if the HW is not working
                   properly. */
                if (ret == E_OK)
                {
                    if (basic_cfg_ptr->InitialTimeout_ms == last_timeout)
                    {
                        /* Copy configuration pointer */
                        g_wdg_tms570ls3x_cfg_ptr     = ConfigPtr;
                        g_wdg_tms570ls3x_cfg_ptr_INV =
                            (const Wdg_TMS570LS3x_ConfigType *)(~(uint32)ConfigPtr); /* PRQA S 0306 */

                        /* Update g_wdg_tms570ls3x_current_mode */
                        g_wdg_tms570ls3x_current_mode     = basic_cfg_ptr->InitialMode;
                        g_wdg_tms570ls3x_current_mode_INV =
                            (WdgIf_ModeType)~(basic_cfg_ptr->InitialMode);

                        /* Update g_wdg_tms570ls3x_window_start */
                        g_wdg_tms570ls3x_window_start     = basic_cfg_ptr->InitialWindowStart_ms;
                        g_wdg_tms570ls3x_window_start_INV =
                            (uint16)~(basic_cfg_ptr->InitialWindowStart_ms);

                        /* g_wdg_tms570ls3x_last_timeout already set */
                    }
                    else
                    {
                        /* TMS570LS3x's watchdog can be set only once! */
                        #if (WDG_DEV_ERROR_DETECT == STD_ON)
                        Appl_Det_ReportError ( WDG_TMS570LS3x_MODULE_ID
                                             , WDG_TMS570LS3x_VENDOR_ID
                                             , API_ID_Wdg_Init
                                             , WDG_E_PARAM_TIMEOUT
                                             );
                        #endif /* (WDG_DEV_ERROR_DETECT == STD_ON) */

                        ret = E_NOT_OK;
                    }
                }
            }
            else
            {
                /* ---------------------- */
                /* Init RTIDWDPRLD and activate watchdog only once */
                rtidwdprld_value = WDG_TMS570LS3x_MS_TO_PRLD
                    (basic_cfg_ptr->InitialTimeout_ms, ConfigPtr->RTICLK_khz);
              #if (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON)
                rticpuc1_value = WDG_TMS570LS3x_TICKS_TO_CPUC
                    (ConfigPtr->TickFreq_hz, ConfigPtr->RTICLK_khz);
              #endif /* (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON) */
                /* Disable interrupts */
                (void) Wdg_GlobalSuspendInterrupts(); /* PRQA S 3335 */
                /* Compute and set reload value */
                WRITE_RTIDWDPRLD (rtidwdprld_value); /* PRQA S 0303 */
                reg_prld = READ_RTIDWDPRLD; /* PRQA S 0303 */
                /* Enable Watchdog */
                WRITE_RTIDWDCTRL (RTIDWDCTRL_ENABLED); /* PRQA S 0303 */
                reg_ctrl = READ_RTIDWDCTRL; /* PRQA S 0303 */
              #if (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON)
                /* Write to Compare Up Counter register the value calculated
                   according to definition:
                   fRTIFRCx = fRTICLK / (RTICPUC+1) */
                WRITE_RTICPUC1 (rticpuc1_value); /* PRQA S 0303 */
                /* Read back the RTICPUC1 register */
                reg_cpuc1 = READ_RTICPUC1; /* PRQA S 0303 */
                /* Read global control register value */
                reg_gctrl = READ_RTIGCTRL; /* PRQA S 0303 */
                /* Enable counter block 1 - set bit1 to 1, other bits remain unchanged
                   RTIGCTRL_ENABLED = 00....010*/
                rtigctrl_value = reg_gctrl | RTIGCTRL_ENABLED; /* PRQA S 0303 */
                /* Write new value to global control register*/
                WRITE_RTIGCTRL (rtigctrl_value); /* PRQA S 0303 */
                /* Read back the global control register value */
                reg_gctrl = READ_RTIGCTRL; /* PRQA S 0303 */
              #endif /* (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON) */
                /* Restore interrupts */
                (void) Wdg_GlobalRestoreInterrupts(); /* PRQA S 3335 */
                /* ---------------------- */

                /* Read back and check register contents */
                if ( (reg_prld  != rtidwdprld_value)
                  || (reg_ctrl  != RTIDWDCTRL_ENABLED)
                #if (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON)
                  || (reg_cpuc1 != rticpuc1_value)
                  || (reg_gctrl != rtigctrl_value)
                #endif /* (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON) */
                   )
                {
                    ret = E_NOT_OK;
                }
                else
                {
                    /* Copy configuration pointer */
                    g_wdg_tms570ls3x_cfg_ptr     = ConfigPtr;
                    g_wdg_tms570ls3x_cfg_ptr_INV =
                        (const Wdg_TMS570LS3x_ConfigType *)(~(uint32)ConfigPtr); /* PRQA S 0306 */

                    /* Update g_wdg_tms570ls3x_current_mode */
                    g_wdg_tms570ls3x_current_mode     = basic_cfg_ptr->InitialMode;
                    g_wdg_tms570ls3x_current_mode_INV =
                        (WdgIf_ModeType)~(basic_cfg_ptr->InitialMode);

                    /* Update g_wdg_tms570ls3x_window_start */
                    g_wdg_tms570ls3x_window_start     = basic_cfg_ptr->InitialWindowStart_ms;
                    g_wdg_tms570ls3x_window_start_INV =
                        (uint16)~(basic_cfg_ptr->InitialWindowStart_ms);

                    /* Update g_wdg_tms570ls3x_last_timeout */
                    g_wdg_tms570ls3x_last_timeout     = basic_cfg_ptr->InitialTimeout_ms;
                    g_wdg_tms570ls3x_last_timeout_INV =
                        (uint16)~(basic_cfg_ptr->InitialTimeout_ms);

                    ret = E_OK;
                }
            }
        #if (WDG_DISABLE_ALLOWED == STD_OFF)
        }
        #endif /* WDG_DISABLE_ALLOWED == STD_OFF */
    }

    return ret;
}

/* PRQA S 1503 1 */
FUNC(Std_ReturnType, WDG_CODE) Wdg_TMS570LS3x_SetMode
    (VAR (uint8, AUTOMATIC) WdgInstance, VAR (WdgIf_ModeType, AUTOMATIC) WdgMode)
{
    VAR (Std_ReturnType, AUTOMATIC) ret;
    VAR (WdgIf_ModeType, AUTOMATIC) current_mode;
    VAR(uint16, AUTOMATIC) window_start;
    VAR(uint16, AUTOMATIC) last_timeout;
    P2CONST (Wdg_TMS570LS3x_ConfigType, AUTOMATIC, WDG_APPL_CONST) config_ptr;

    /* Check global variables for consistency */
    window_start = g_wdg_tms570ls3x_window_start;
    last_timeout = g_wdg_tms570ls3x_last_timeout;
    current_mode = g_wdg_tms570ls3x_current_mode;
    config_ptr   = g_wdg_tms570ls3x_cfg_ptr;
    /* PRQA S 3355 5 */ /* PRQA S 3358 5 */
    if ( ((uint16)~window_start != g_wdg_tms570ls3x_window_start_INV)
      || ((uint16)~last_timeout != g_wdg_tms570ls3x_last_timeout_INV)
      || ((WdgIf_ModeType)~current_mode != g_wdg_tms570ls3x_current_mode_INV)
      || ((uint32)~(uint32)config_ptr != (uint32)g_wdg_tms570ls3x_cfg_ptr_INV) /* PRQA S 0306 */
       )
    {
        /* Memory courruption detected! Perform a RESET */
        ret = E_NOT_OK;
        wdg_tms570ls3x_reset ();
    }

    /* Development error detect */
    /* PRQA S 3201 1 */
    else if (g_wdg_tms570ls3x_cfg_ptr == NULL_PTR)
    {
        #if (WDG_DEV_ERROR_DETECT == STD_ON)
        Appl_Det_ReportError ( WDG_TMS570LS3x_MODULE_ID
                             , WDG_TMS570LS3x_VENDOR_ID
                             , API_ID_Wdg_SetMode
                             , WDG_E_DRIVER_STATE
                             );
        #endif
        ret = E_NOT_OK;
    }
    else if (WdgInstance > 0u)
    {
        #if (WDG_DEV_ERROR_DETECT == STD_ON)
        Appl_Det_ReportError ( WDG_TMS570LS3x_MODULE_ID
                             , WDG_TMS570LS3x_VENDOR_ID
                             , API_ID_Wdg_SetMode
                             , WDG_E_PARAM_CONFIG
                             );
        #endif
        ret = E_NOT_OK;
    }
    /* PRQA S 3356 1 */ /* PRQA S 3359 1 */
    else if (WdgMode > WDGIF_FAST_MODE)
    /* PRQA S 3201 1 */
    {
        #if (WDG_DEV_ERROR_DETECT == STD_ON)
        Appl_Det_ReportError ( WDG_TMS570LS3x_MODULE_ID
                             , WDG_TMS570LS3x_VENDOR_ID
                             , API_ID_Wdg_SetMode
                             , WDG_E_PARAM_MODE
                             );
        #endif
        ret = E_NOT_OK;
    }
    else
    /* If DET checks were successful */
    {
    #if (WDG_DISABLE_ALLOWED == STD_OFF)
        if (WdgMode == WDGIF_OFF_MODE)
        {
            #if (WDG_DEM_REPORT == STD_ON)
            /* If not allowed report failure */
            Appl_Dem_ReportErrorStatus ( WDG_E_DISABLE_REJECTED
                                       , DEM_EVENT_STATUS_FAILED
                                       );
            #endif
            ret = E_NOT_OK;
        }
        else
        {
    #endif /* WDG_DISABLE_ALLOWED == STD_OFF */
            /* Check window start */
            ret = wdg_tms570ls3x_check_window_start (window_start, last_timeout, config_ptr->RTICLK_khz);

            /* ret is here E_NOT_OK only if the window was violated but no
               reset occurred. This could happen if the HW is not working
               properly. */
            if (ret == E_OK)
            {
                /* Nothing to do here, only one mode is supported */
                g_wdg_tms570ls3x_current_mode     = WdgMode;
                g_wdg_tms570ls3x_current_mode_INV = (WdgIf_ModeType)~WdgMode;
            }
    #if (WDG_DISABLE_ALLOWED == STD_OFF)
        }
    #endif /* WDG_DISABLE_ALLOWED == STD_OFF */
    }

    return ret;
}

/* PRQA S 1503 1 */
FUNC(Std_ReturnType, WDG_CODE) Wdg_TMS570LS3x_SetTriggerWindow
    ( VAR (uint8, AUTOMATIC) WdgInstance
    , VAR (uint16, AUTOMATIC) WindowStart
    , VAR (uint16, AUTOMATIC) Timeout
    )
{
    VAR (Std_ReturnType, AUTOMATIC) ret = E_OK;
    VAR (uint16, AUTOMATIC) det_max_ms;
    VAR (uint32, AUTOMATIC) check_ms;
    VAR (uint32, AUTOMATIC) wd_cntr_old;
    VAR (uint32, AUTOMATIC) wd_cntr;
    VAR (uint16, AUTOMATIC) window_start;
    VAR (uint16, AUTOMATIC) last_timeout;
    VAR (WdgIf_ModeType, AUTOMATIC) current_mode;
    P2CONST (Wdg_TMS570LS3x_ConfigType, AUTOMATIC, WDG_APPL_CONST) config_ptr;

    /* Check global variables for consistency */
    window_start = g_wdg_tms570ls3x_window_start;
    last_timeout = g_wdg_tms570ls3x_last_timeout;
    current_mode = g_wdg_tms570ls3x_current_mode;
    config_ptr   = g_wdg_tms570ls3x_cfg_ptr;
    /* PRQA S 0306 4 */ /* PRQA S 3355 4 */ /* PRQA S 3358 4 */
    if ( ((uint16)~window_start != g_wdg_tms570ls3x_window_start_INV)
      || ((uint16)~last_timeout != g_wdg_tms570ls3x_last_timeout_INV)
      || ((WdgIf_ModeType)~current_mode != g_wdg_tms570ls3x_current_mode_INV)
      || ((uint32)~(uint32)config_ptr != (uint32)g_wdg_tms570ls3x_cfg_ptr_INV)
       )
    {
        /* Memory courruption detected! Perform a RESET */
        ret = E_NOT_OK;
        wdg_tms570ls3x_reset ();
    }

    /* Development error detect */
    else if (g_wdg_tms570ls3x_cfg_ptr == NULL_PTR) /* PRQA S 3201 */
    {
        #if (WDG_DEV_ERROR_DETECT == STD_ON)
        Appl_Det_ReportError ( WDG_TMS570LS3x_MODULE_ID
                             , WDG_TMS570LS3x_VENDOR_ID
                             , API_ID_Wdg_SetTriggerWindow
                             , WDG_E_DRIVER_STATE
                             );
        #endif
        ret = E_NOT_OK;
    }
    else if (WdgInstance > 0u)
    {
        #if (WDG_DEV_ERROR_DETECT == STD_ON)
        Appl_Det_ReportError ( WDG_TMS570LS3x_MODULE_ID
                             , WDG_TMS570LS3x_VENDOR_ID
                             , API_ID_Wdg_SetMode
                             , WDG_E_PARAM_CONFIG
                             );
        #endif
        ret = E_NOT_OK;
    }
    else
    {
        /* Get the maximum settable milliseconds for this mode */
        if (current_mode == WDGIF_FAST_MODE)
        {
            det_max_ms = g_wdg_tms570ls3x_cfg_ptr->BasicCfgPtr->FastModeMax_ms;
        }
        else
        {
            det_max_ms = g_wdg_tms570ls3x_cfg_ptr->BasicCfgPtr->SlowModeMax_ms;
        }

        if (  (WindowStart > det_max_ms)
           || (Timeout     > det_max_ms)
           || (WindowStart > Timeout)
           )
        {
            #if (WDG_DEV_ERROR_DETECT == STD_ON)
            Appl_Det_ReportError ( WDG_TMS570LS3x_MODULE_ID
                                 , WDG_TMS570LS3x_VENDOR_ID
                                 , API_ID_Wdg_SetTriggerWindow
                                 , WDG_E_PARAM_TIMEOUT
                                 );
            #endif
            ret = E_NOT_OK;
        }
    }

    /* If DET checks were successful */
    if (ret == E_OK) /* PRQA S 3356 */ /* PRQA S 3359 */
    { /* PRQA S 3201 */
        if (Timeout == 0u)
        {
            ret = E_NOT_OK;
            wdg_tms570ls3x_reset ();
        }
        else if (Timeout != g_wdg_tms570ls3x_cfg_ptr->BasicCfgPtr->InitialTimeout_ms)
        {
            /* TMS570LS3x's watchdog can be set only once! */
            #if (WDG_DEV_ERROR_DETECT == STD_ON)
            Appl_Det_ReportError ( WDG_TMS570LS3x_MODULE_ID
                                 , WDG_TMS570LS3x_VENDOR_ID
                                 , API_ID_Wdg_SetTriggerWindow
                                 , WDG_E_PARAM_TIMEOUT
                                 );
            #endif
            ret = E_NOT_OK;
        }
        else
        {

            /* Check window start */
            ret = wdg_tms570ls3x_check_window_start
                (window_start, last_timeout, config_ptr->RTICLK_khz);

            /* ret is here E_NOT_OK only if the window was violated but no
               reset occurred. This could happen if the HW is not working
               properly. */
            if (ret == E_OK)
            {
                g_wdg_tms570ls3x_window_start     = WindowStart;
                g_wdg_tms570ls3x_window_start_INV = (uint16)~WindowStart;

                /* No need to set g_wdg_tms570ls3x_last_timeout again */

                /* Disable interrupts */
                (void) Wdg_GlobalSuspendInterrupts(); /* PRQA S 3335 */
                wd_cntr_old = READ_RTIDWDCNTR; /* PRQA S 0303 */
                /* Service watchdog */
                WRITE_RTIWDKEY (RTIWDKEY_PREPARE); /* PRQA S 0303 */
                WRITE_RTIWDKEY (RTIWDKEY_TRIGGER); /* PRQA S 0303 */
                wd_cntr = READ_RTIDWDCNTR; /* PRQA S 0303 */
                /* Restore interrupts */
                (void) Wdg_GlobalRestoreInterrupts(); /* PRQA S 3335 */

                /* Check if wdg timer value is as expected */
                check_ms = WDG_TMS570LS3x_WDTICKS_TO_MS (wd_cntr, config_ptr->RTICLK_khz);

                /* If watchdog not running or not enabled - assume an error */
                if (  ( !(wd_cntr > wd_cntr_old))
                   /* If wdg timer value is not as expected - assume an error */
                   || (check_ms > Timeout)
                   || (check_ms < (Timeout - 1u))
                   )
                {
                    ret = E_NOT_OK;
                }
            }
        }
    }

    return ret;
}

#if (WDG_VERSION_INFO_API == STD_ON)
/* PRQA S 1503 1 */
FUNC(void, WDG_CODE) Wdg_TMS570LS3x_GetVersionInfo
    (P2VAR (Std_VersionInfoType, AUTOMATIC, WDG_APPL_DATA) VersionInfoPtr)
{
    if (VersionInfoPtr == NULL_PTR)
    {
        #if (WDG_DEV_ERROR_DETECT == STD_ON)
        Appl_Det_ReportError ( WDG_TMS570LS3x_MODULE_ID
                             , WDG_TMS570LS3x_VENDOR_ID
                             , API_ID_Wdg_GetVersionInfo
                             , WDG_E_PARAM_CONFIG
                             );
        #endif
    }
    else
    {
        VersionInfoPtr->vendorID         = WDG_VENDOR_ID;
        VersionInfoPtr->moduleID         = WDG_MODULE_ID;
        VersionInfoPtr->sw_major_version = WDG_TMS570LS3x_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = WDG_TMS570LS3x_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = WDG_TMS570LS3x_SW_PATCH_VERSION;
    }
}
#endif /* WDG_VERSION_INFO_API == STD_ON */

#if (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON)
/* PRQA S 1503 1 */
FUNC(uint32, WDG_CODE) Wdg_TMS570LS3x_GetTickCounter (void)
{
    return READ_RTIFRC1; /* PRQA S 0303 */
}
#endif /* WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON */

#if defined(WDG_UNIT_TESTS)
  #if (WDG_UNIT_TESTS == 1)
    #if (defined(__CANTATA__))
    #if (__CANTATA__ == 1)
    /* Do not instrument in Cantata++ - these functions are part of the test
       cases and not of the module's functionality. */
    #pragma ipl cantata++ ci instr all off
    #endif
    #endif

    /* grant access to internal static resources for the unit tests */
    const Wdg_TMS570LS3x_ConfigType* tc_wdg_get_cfg_ptr(void)
    {
        return g_wdg_tms570ls3x_cfg_ptr;
    }
    void tc_wdg_deinit_wdg (void)
    {
        g_wdg_tms570ls3x_window_start     = 0;
        g_wdg_tms570ls3x_window_start_INV = (uint16)~0;
        g_wdg_tms570ls3x_last_timeout     = 0;
        g_wdg_tms570ls3x_last_timeout_INV = (uint16)~0;
        g_wdg_tms570ls3x_cfg_ptr          = NULL_PTR;
        g_wdg_tms570ls3x_cfg_ptr_INV      =
            (const Wdg_TMS570LS3x_ConfigType *)(~(uint32)NULL_PTR);
        g_wdg_tms570ls3x_current_mode     = WDGIF_OFF_MODE;
        g_wdg_tms570ls3x_current_mode_INV = (WdgIf_ModeType)~WDGIF_OFF_MODE;
    }
    WdgIf_ModeType tc_get_g_wdg_tms570ls3x_current_mode (void)
    {
        return g_wdg_tms570ls3x_current_mode;
    }
    uint16 tc_get_g_wdg_tms570ls3x_window_start (void)
    {
        return g_wdg_tms570ls3x_window_start;
    }
    uint16 tc_get_g_wdg_tms570ls3x_last_timeout (void)
    {
        return g_wdg_tms570ls3x_last_timeout;
    }

    uint32 tc_wdg_tms570ls3x_convert_ms_to_wdticks (uint16 ms)
    {
        return WDG_TMS570LS3x_MS_TO_WDTICKS (ms, g_wdg_tms570ls3x_cfg_ptr->RTICLK_khz);
    }

    /* access functions to manipulate the module internal variables */
    void tc_write_g_wdg_tms570ls3x_cfg_ptr (const Wdg_TMS570LS3x_ConfigType* x)
    {
        g_wdg_tms570ls3x_cfg_ptr = x;
    }
    void tc_write_g_wdg_tms570ls3x_cfg_ptr_INV (const Wdg_TMS570LS3x_ConfigType* x)
    {
        g_wdg_tms570ls3x_cfg_ptr_INV = x;
    }
    void tc_write_g_wdg_tms570ls3x_last_timeout (uint16 x)
    {
        g_wdg_tms570ls3x_last_timeout = x;
    }
    void tc_write_g_wdg_tms570ls3x_last_timeout_INV (uint16 x)
    {
        g_wdg_tms570ls3x_last_timeout_INV = x;
    }
    void tc_write_g_wdg_tms570ls3x_window_start (uint16 x)
    {
        g_wdg_tms570ls3x_window_start = x;
    }
    void tc_write_g_wdg_tms570ls3x_window_start_INV (uint16 x)
    {
        g_wdg_tms570ls3x_window_start_INV = x;
    }
    void tc_write_g_wdg_tms570ls3x_current_mode (uint16 x)
    {
        g_wdg_tms570ls3x_current_mode = x;
    }
    void tc_write_g_wdg_tms570ls3x_current_mode_INV (uint16 x)
    {
        g_wdg_tms570ls3x_current_mode_INV = x;
    }
    #if (defined(__CANTATA__))
    #if (__CANTATA__ == 1)
    #pragma ipl cantata++ ci instr all default
    #endif
    #endif
  #endif
#endif



#define WDG_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */
