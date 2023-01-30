/* STARTSINGLE_OF_MULTIPLE */


/*****************************************************************************
 * Project Name: AUTOSAR Demonstrator
 *    File Name: Det.h
 *
 *  Description: Header of Development Error Tracer
 *
 ******************************************************************************
 *               C O P Y R I G H T
 ******************************************************************************
 * Copyright (c) 2005-2013 by Vector Informatik GmbH.      All rights reserved.
 *
 *       This software is copyright protected and 
 *       proporietary to Vector Informatik GmbH.
 *       Vector Informatik GmbH grants to you only
 *       those rights as set out in the license conditions.
 *       All other rights remain with Vector Informatik GmbH.
 * 
 *       Diese Software ist urheberrechtlich geschuetzt. 
 *       Vector Informatik GmbH raeumt Ihnen an dieser Software nur 
 *       die in den Lizenzbedingungen ausdruecklich genannten Rechte ein.
 *       Alle anderen Rechte verbleiben bei Vector Informatik GmbH.
 *
 ******************************************************************************
 *               A U T H O R   I D E N T I T Y
 ******************************************************************************
 * Initials     Name                      Company
 * ********     *********************     *************************************
 * Om           Oliver Meili              Vector Informatik GmbH
 * Jk           Joachim Kalmbach          Vector Informatik GmbH
 * HH           Hartmut Hoerner           Vector Informatik GmbH
 ******************************************************************************
 *               R E V I S I O N   H I S T O R Y
 ******************************************************************************
 * Date        Version  Author  Description
 * **********  *******  ******  ***********************************************
 * 2005-08-18  0.01.00  Om      Creation
 * 2006-05-18  2.00.00  Om      Update for AUTOSAR Release 2.0
 * 2007-08-08  3.00.00  Jk      Update for AUTOSAR Release 2.1 
 * 2007-09-17  3.01.00  Jk      GetVersionInfo API added 
 * 2007-11-28  3.02.00  HH      Extended debug features added 
 * 2008-01-02  4.00.00  HH      Update for AUTOSAR Release 3.0 
 *                              compiler abstraction and memmap added
 * 2008-09-12  4.01.00  HH      ESCAN00023736: DET entry callout
 *                              ESCAN00029923: DET could be called recursively
 * 2008-12-09  4.02.00  HH      ESCAN00030591: compile error if extended version check is disabled
 *                              ESCAN00031617: Compiler warning about sprintf on CANoe emulation platform
 * 2008-12-09  4.03.00  HH      ESCAN00033897: case-sensitive issue: #include "VStdLib.h" instead of "#include "vstdlib.h" in Det.c
 * 2009-05-20  4.03.01  HH      ESCAN00034249: DET entry callout Appl_DetEntryCallout is only called once
 *                              ESCAN00034566: Compiler warnings because of unused parameters in Det_ReportError
 * 2010-07-27  4.03.02  HH      ESCAN00039898: Endless loop on CANoe platform
 *                              ESCAN00042300: support time-stamp for write window messages on CANoe platform
 * 2011-01-13  5.00.00  HH      ESCAN00048023: Update for AUTOSAR Release 4.0
 * 2011-10-27  5.01.00  HH      ESCAN00054556: AR3-1698 support CDK MISRA report
 * 2012-06-25  5.02.00  HH      ESCAN00060956: do not use v_cfg.h for Cfg5
 * 2013-01-18  5.03.00  HH      ESCAN00064266: AR4-220: Compiler error: Different errors due to unknown STATIC
 * 2013-08-22  6.00.00  HH      ESCAN00068394: AR4-292: Reporting of DET and DEM errors via DLT
 * 2013-12-17  6.00.01  HH      ESCAN00072683: version consistency checking is too strict
*****************************************************************************/

#ifndef DET_H
#define DET_H

#include "Std_Types.h"
#include "Det_Cfg.h"


/* AUTOSAR Development Error Tracer version */
/* ##V_CFG_MANAGEMENT ##CQProject : SysService_AsrDet CQComponent : Implementation     */
#define SYSSERVICE_ASRDET_VERSION          0x0600u /* BCD coded version number         */
#define SYSSERVICE_ASRDET_RELEASE_VERSION  0x01u   /* BCD coded release version number */

/**
 * Define vendor and module ID
 */
#define DET_VENDOR_ID         30 /* HIS Vendor ID for Vector               */
#define DET_MODULE_ID         15 /* Det Module ID according to BSW Modules */

/* if new source code is used with older generator dll default to AUTOSAR 3 mode */
#if !defined(DET_AUTOSARVERSION)
#define DET_AUTOSARVERSION                   3
#endif

/**
 * Define AUTOSAR specification version if not already externally specified (ESCAN00072683)
 */
#if !defined(DET_AR_MAJOR_VERSION) 
# if (DET_AUTOSARVERSION == 4)
#  define DET_AR_MAJOR_VERSION  3
#  define DET_AR_MINOR_VERSION  0
#  define DET_AR_PATCH_VERSION  0
# else
#  define DET_AR_MAJOR_VERSION  2
#  define DET_AR_MINOR_VERSION  2
#  define DET_AR_PATCH_VERSION  0
# endif
#endif

/**
 * Define AUTOSAR release version  if not already externally specified (ESCAN00072683)
 */
#if !defined(DET_AR_RELEASE_MAJOR_VERSION) 
# if (DET_AUTOSARVERSION == 4)
#  if defined(DET_GENERATOR_CFG5)
#   define DET_AR_RELEASE_MAJOR_VERSION  4
#   define DET_AR_RELEASE_MINOR_VERSION  0
#   define DET_AR_RELEASE_PATCH_VERSION  3
#  else
#   define DET_AR_RELEASE_MAJOR_VERSION  4
#   define DET_AR_RELEASE_MINOR_VERSION  0
#   define DET_AR_RELEASE_PATCH_VERSION  1
#  endif
# endif
# define DET_AR_RELEASE_REVISION_VERSION  DET_AR_RELEASE_PATCH_VERSION
#endif

/**
 * Define version for header and source file consistency
 */
#define DET_SW_MAJOR_VERSION  ((SYSSERVICE_ASRDET_VERSION & 0xFF00u) >> 8)
#define DET_SW_MINOR_VERSION  (SYSSERVICE_ASRDET_VERSION & 0x00FFu)
#define DET_SW_PATCH_VERSION  SYSSERVICE_ASRDET_RELEASE_VERSION

/********************** compiler abstraction *******************************/
#if !defined(DET_STATIC)
# if defined(STATIC)
#  define DET_STATIC  STATIC   /* standard by AutoSar 3.x */
# else
#  define DET_STATIC  static   /* standard AutoSar 4.x define */
# endif
#endif

/* for backwards compatibility to old generators */
#if !defined(DET_FORWARD_TO_DLT)
#define DET_FORWARD_TO_DLT                   STD_OFF    
#endif

# if defined( DET_ENABLED )

#  if defined( DET_DEBUG_ENABLED )
/* strucure used to configure filters and store log data, using 0xff for a filter item means don't care */
typedef struct
{
  uint16 moduleId;
  uint8 instanceId;
  uint8 apiId;
  uint8 errorId;
} DetInfoType;
/* structure to control the operation of DET debug extension */
typedef struct
{
  uint8 globalFilterActive; /* 0: global filters disabled, 1: global filters enabled */
  uint8 logActive;          /* 0: logging disabled, 1: logging enabled */
  uint8 logIndex;           /* do not modify: last index in array where data was logged */
  uint8 breakOnLogOverrun;  /* 0: break on log buffer overrun disabled, 1: break on log buffer overrun enabled */
  uint8 breakFilterActive;  /* 0: break filters disabled, 1: break filters enabled */
  uint8 unlockBreak;        /* 0: break, 1: unlock break, can be used to unlock endless loop */
} DetStatusType;

#define DET_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */  /* MD_DET_5087 */
/* global variables, should be put in a watch window */
#if DET_GLOBALFILTERSIZE > 0
extern volatile VAR(DetInfoType,DET_VAR) detGlobalFilter[DET_GLOBALFILTERSIZE]; /* ##### use this variable to configure global filters */ /* PRQA S 850 */ /* MD_DET_0850 */
#endif
#if DET_BREAKFILTERSIZE > 0
extern volatile VAR(DetInfoType,DET_VAR) detBreakFilter[DET_BREAKFILTERSIZE];   /* ##### use this variable to configure break filters */ /* PRQA S 850 */ /* MD_DET_0850 */
#endif
#if DET_LOGBUFFERSIZE > 0
extern volatile VAR(DetInfoType,DET_VAR) detLogBuffer[DET_LOGBUFFERSIZE];       /* ##### use this variable to view log buffer */ /* PRQA S 850 */ /* MD_DET_0850 */
#endif
extern volatile VAR(DetStatusType,DET_VAR) detStatus;                           /* ##### use this variable to configure DET debug operation */ /* PRQA S 850 */ /* MD_DET_0850 */
#define DET_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */  /* MD_DET_5087 */

#  endif /* DET_DEBUG_ENABLED */  /* MD_DET_5087 */

#define DET_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_DET_5087 */
/*******************************************************************************
 * Global functions as an interface from EcuM to DET for initialization
 * and start
 *******************************************************************************/
FUNC(void, DET_CODE) Det_Init( void ); /* PRQA S 850 */ /* MD_DET_0850 */

FUNC(void, DET_CODE) Det_Start( void ); /* PRQA S 850 */ /* MD_DET_0850 */

#   if DET_AUTOSARVERSION == 4
FUNC(void, DET_CODE) Det_InitMemory( void ); /* PRQA S 850 */ /* MD_DET_0850 */
#   endif

/*******************************************************************************
 * Global function for BSW-Modules to report errors to the DET
 *******************************************************************************/
#   if DET_AUTOSARVERSION == 4
FUNC(Std_ReturnType, DET_CODE) Det_ReportError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId ); /* PRQA S 850 */ /* MD_DET_0850 */
#   else
FUNC(void, DET_CODE) Det_ReportError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId ); /* PRQA S 850 */ /* MD_DET_0850 */
#   endif

/*******************************************************************************
 * Global function for BSW-Modules to get the Version of Det
 *******************************************************************************/
#   if (DET_VERSION_INFO_API == STD_ON)
FUNC(void, DET_CODE) Det_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, DET_APPL_DATA ) versioninfo ); /* PRQA S 850 */ /* MD_DET_0850 */
#   endif

/*******************************************************************************
 * Callouts which have to be provided by the application
 *******************************************************************************/
#if defined( DET_ENTRY_CALLOUT_ENABLED )
FUNC(uint8, DET_APPL_CODE) Appl_DetEntryCallout( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId ); /* PRQA S 850 */ /* MD_DET_0850 */
#endif

#define DET_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */  /* MD_DET_5087 */

# endif /* DET_ENABLED */
#endif /* DET_H */

/* STOPSINGLE_OF_MULTIPLE */
