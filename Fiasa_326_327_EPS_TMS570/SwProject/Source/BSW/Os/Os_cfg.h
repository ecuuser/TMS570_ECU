/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: Os_Cfg.h
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.03
|
|  Description: Included by the OS standard header Os.h
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2008-2010 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/

/* double include preventer */
#ifndef _OS_CFG_H
#define _OS_CFG_H

/* Vector release management */
#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <vrm.h>
#endif
/* KB begin vrmReleaseNumber (overwritten) */
/* TR:SPMF36:0002 Start */
/* Source release number */
#define osdVrmMajRelNum 5
#define osdVrmMinRelNum 6
/* TR:SPMF36:0002 End */
/* KB end vrmReleaseNumber */
#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <vrm.h>
#endif

#if defined USE_QUOTE_INCLUDES
 #include "osek.h"
#else
 #include <osek.h>
#endif

#endif/* double include preventer */

/* END OF HEADER Os_cfg.h */

