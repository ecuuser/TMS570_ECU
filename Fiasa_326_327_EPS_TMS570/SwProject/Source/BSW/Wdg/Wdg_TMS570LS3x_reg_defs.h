/* Copyright (C) 2011-2012 TTTech Automotive GmbH. All rights reserved
** Schoenbrunnerstrasse 7, A-1040 Wien, Austria. office(at)tttech-automotive.com
**
** Name:
**   Wdg_TMS570LS3x_reg_defs.h
**
** Purpose: Header file for the TMS570LS3x specific registers which are used by
**          the Safe Watchdog Driver of the Modular Safety Platform.
**
*/

#ifndef WDG_TMS570LS3x_REG_DEFS_H_
#define WDG_TMS570LS3x_REG_DEFS_H_

/* ------------------------------------------------------------------------- */
/*                        SUPRESSED MISRA VIOLATONS                          */
/* ------------------------------------------------------------------------- */
/* Error Message : Msg(4:3332) The macro 'WDG_TMS570LS3x_INTERNAL_TICK_COUNTER'
                   used in this '#if...' test is not defined.
                   Msg(4:3332) The macro 'STD_ON' used in this '#if...' test is
                   not defined.
 * Justification : This file 'Wdg_TMS570LS3x_reg_defs.h' is included in the
                   source file 'Wdg_TMS570LS3x.c' after implicitly including
                   'Wdg_TMS570LS3x_Cfg_Features.h' which defines
                   'WDG_TMS570LS3x_INTERNAL_TICK_COUNTER' and 'Std_Types.h'
                   which defines 'STD_ON'. Furthermore there is an explicit
                   check (in 'Wdg_TMS570LS3x_Cfg.h') whether
                   'WDG_TMS570LS3x_INTERNAL_TICK_COUNTER' is defined at all. */


/* Module version */
#define WDG_TMS570LS3x_REG_DEFS_SW_MAJOR_VERSION  2
#define WDG_TMS570LS3x_REG_DEFS_SW_MINOR_VERSION  0
#define WDG_TMS570LS3x_REG_DEFS_SW_PATCH_VERSION  3


/* ***************************************************************************
** Register definitions
******************************************************************************/

#define TMS570_RTI_REG_BASE 0xFFFFFC00u

#define RTIDWDCTRL  ((volatile uint32 *) (TMS570_RTI_REG_BASE + 0x00000090u))
#define RTIDWDPRLD  ((volatile uint32 *) (TMS570_RTI_REG_BASE + 0x00000094u))
#define RTIWDSTATUS ((volatile uint32 *) (TMS570_RTI_REG_BASE + 0x00000098u))
#define RTIWDKEY    ((volatile uint32 *) (TMS570_RTI_REG_BASE + 0x0000009Cu))
#define RTIDWDCNTR  ((volatile uint32 *) (TMS570_RTI_REG_BASE + 0x000000A0u))
/* PRQA S 3332 1 */
#if (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON)
/* free running counter 1 */
#define RTIFRC1     ((volatile uint32 *) (TMS570_RTI_REG_BASE + 0x00000030u))
/* compare up counter */
#define RTICPUC1    ((volatile uint32 *) (TMS570_RTI_REG_BASE + 0x00000038u))
/* global control register */
#define RTIGCTRL    ((volatile uint32 *) (TMS570_RTI_REG_BASE + 0x00000000u))
#endif /* WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON */

#define SYSESR      ((volatile uint32 *) (0xFFFFFF00u + 0x000000E4u))

#define RTIDWDCTRL_DISABLED 0x5312ACEDu
#define RTIDWDCTRL_ENABLED  0xA98559DAu
#define RTIWDKEY_PREPARE    0x0000E51Au
#define RTIWDKEY_TRIGGER    0x0000A35Cu
#define RTIWDKEY_WRONG_VAL  0x0000F0F0u
/* PRQA S 3332 1 */
#if (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON)
#define RTIGCTRL_ENABLED    0x00000002u /* mask to enable counter block 1. bit 1
                                           needs to be set to 1, the others
                                           should remain unchanged maks will be
                                           or-ed with the current register value
                                        */
#endif /* WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON */

#endif /* WDG_TMS570LS3x_REG_DEFS_H_ */
