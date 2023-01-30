/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: Os.h
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.09
|
|  Description: standard header of the OS, to be included by the application
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2006-2012 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/

/* TR:SASR30:0287 Start */
/* double include preventer */
#ifndef _OS_H
#define _OS_H

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
/* TR:SASR30:0286 Start */
#if defined USE_QUOTE_INCLUDES
 #include "Os_Cfg.h"
#else
 #include <Os_Cfg.h>
#endif

#if (osdTypeHeaderInclude != 0)
 #if defined USE_QUOTE_INCLUDES
  #include "Std_Types.h"
 #else
  #include <Std_Types.h>
 #endif
/* there is no version check of this file since the OS is independent of these types */
#endif
/* TR:SASR30:0286 End */

#ifndef osdIncludeLibConfig
 #if (osdNumberOfTrustedFunctions > 0)
  #if defined USE_QUOTE_INCLUDES
   #include "usrostyp.h"
  #else
   #include <usrostyp.h>
  #endif
 #endif

 #if defined USE_QUOTE_INCLUDES
  #include "trustfct.h"
 #else
  #include <trustfct.h>
 #endif
#endif


#endif/* double include preventer */
/* TR:SASR30:0287 End */
/* END OF HEADER Os.h */

