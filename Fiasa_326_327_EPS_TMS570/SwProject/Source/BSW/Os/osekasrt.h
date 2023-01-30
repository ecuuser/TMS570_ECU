/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: osekasrt.h
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.23
|
|  Description: different assertions for error detection
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2012 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/

/* double include preventer */
#ifndef _OSEKASRT_H
#define _OSEKASRT_H

/*lint -save Messages inhibited in this file, will be re-enabled at the end of file */
/*lint -e539 Did not expect positive indentation */

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

/* KB begin osekHw_FILE_Cast (default) */
#define osd_FILE_Cast
/* KB end osekHw_FILE_Cast */


/* TR:SPMF12:0004 Start */
#define osAssertFailed_(x) osLastError = (osuint16) (x); osAssertFailed()  /* TR:SPMF10:0010 */


#define osSysErrAssertFailed(x)  {\
                                    osDisableGlobal();\
                                    osAssertFailed_(x);\
                                 }

#define osSysErrAssert(p, x) if ((p) == 0)\
                                 {\
                                    osSysErrAssertFailed(x)\
                                 }
/* TR:SPMF12:0004 End */
#define osAPIError(x, y)      osLastError = (osuint16) (y); osErrorHook((StatusType) (x)) /* TR:SPMF10:0008 */ /* TR:SOSK22:0124 */ /* TR:SOSK22:0127 */

#define osCOMAPIError(x, y) /* TR:SPMF10:0009 */

/*lint -restore re-enable messages*/

#endif /* double include preventer */

/* END OF HEADER osekasrt.h */
