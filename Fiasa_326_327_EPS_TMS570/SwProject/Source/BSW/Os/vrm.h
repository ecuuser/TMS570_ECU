/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: Vector Release Management (VRM)
|    File Name: vrm.h
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.04
|
|  Description: header file for release management
|               (The current number of the newest release is stored in this
|               file)
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2012 Vector Informatik GmbH               All rights reserved.
|****************************************************************************/

/* TR:SPMF89:0038 Start */

/* MISRA RULE 19.15 VIOLATION: This file performs a version check for all source- 
 * and header files of the OS. Therefore it needs to be included multiple times.
 * Special care has been taken that the multiple inclusion has no negative 
 * effect on the software. */
/* PRQA S 0883 EOF */

/* double include preventer */
#ifndef __VRM__1__
#define __VRM__1__
 
/* KB begin vrmReleaseNumberReference (overwritten) */
/* TR:SPMF36:0001 Start */
/* source VRM check               */
#define osdVrmMajRelNumRef 5
#define osdVrmMinRelNumRef 6

/* generator VRM check            */
#define osdVrmGenMajRelNumRef 5
#define osdVrmGenMinRelNumRef 6
/* TR:SPMF36:0001 End */
/* KB end vrmReleaseNumberReference */


#else /* __VRM__1__ */

#ifndef __VRM__2__
#define __VRM__2__

/* TR:SPMF36:0004 Start */
/* source VRM checks */
#if defined osdVrmMajRelNum && defined osdVrmMinRelNum

#if osdVrmMajRelNum!=osdVrmMajRelNumRef
#error "VRM: major release number mismatch (Source)"
#endif

#if osdVrmMinRelNum!=osdVrmMinRelNumRef
#error "VRM: minor release number mismatch (Source)"
#endif

#endif /* osdVrmMajRelNum && osdVrmMinRelNum */


/* generator VRM checks */
#if defined osdVrmGenMajRelNum && defined osdVrmGenMinRelNum

#if osdVrmGenMajRelNum!=osdVrmGenMajRelNumRef
#error "VRM: major release number mismatch (Generator)"
#endif

#if osdVrmGenMinRelNum!=osdVrmGenMinRelNumRef
#error "VRM: minor release number mismatch (Generator)"
#endif

#endif /* osdVrmGenMajRelNum && osdVrmGenMinRelNum */
/* TR:SPMF36:0004 End */

#ifdef osdVrmMajRelNum
#undef osdVrmMajRelNum
#endif

#ifdef osdVrmMinRelNum
#undef osdVrmMinRelNum
#endif

#ifdef osdVrmGenMajRelNum
#undef osdVrmGenMajRelNum
#endif

#ifdef osdVrmGenMinRelNum
#undef osdVrmGenMinRelNum
#endif

#endif /* __VRM__2__ */
#undef  __VRM__2__

#endif /* __VRM__1__ */
/* TR:SPMF89:0038 End */

