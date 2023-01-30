/* STARTSINGLE_OF_MULTIPLE */


/*****************************************************************************
 * Project Name: AUTOSAR Demonstrator
 *    File Name: Det.c
 *
 *  Description: Implementation of Development Error Tracer
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
 * 2005-09-05  0.01.00  Om      Creation
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

#include "Det.h"

#if defined( DET_GENERATOR_CFG5 )
#  include "Compiler.h"
#  if defined( _MICROSOFT_C_CANOE_ )
#    define DET_COMP_ANSI_CANOE
#  endif
#else
#  include "v_cfg.h" /* needed for C_COMP_... switch */
#endif

#if defined( DET_COMP_ANSI_CANOE )
#  include <stdio.h> /* PRQA S 5124 */  /* MD_DET_5124 */ /* simulation environment, no production code */
#  include "os.h"
#  include "CANoeApi.h"
# if(_MSC_VER >= 1400)
#  include <string.h>
#  include <time.h> /* PRQA S 5127 */  /* MD_DET_5127 */ /* simulation environment, no production code */
# endif
#endif /* DET_COMP_ANSI_CANOE */

#if defined( DET_DEBUG_ENABLED )
#  include "SchM_Det.h"
#endif

#if (DET_FORWARD_TO_DLT == STD_ON)
# include "Dlt.h"
#endif

/**
 * Version check for source and header file consistency
 */
#if (DET_SW_MAJOR_VERSION != 6)
#  error "Source and Header file are inconsistent!"
#endif

#if (DET_SW_MINOR_VERSION != 0)
#  error "Source and Header file are inconsistent!"
#endif

#if (DET_SW_PATCH_VERSION != 1)
#  error "Source and Header file are inconsistent!"
#endif

/**
 * Version check for GENy generator DLL consistency
 */

#if (!defined(DET_GENERATOR_CFG5))

# if (!defined(V_SUPPRESS_EXTENDED_VERSION_CHECK))

#  if (SYSSERVICE_ASRDET_GENTOOL_GENY_MAJOR_VERSION != 0x02u)
#   error "GENy DLL is inconsistent!"
#  endif

#  if (SYSSERVICE_ASRDET_GENTOOL_GENY_MINOR_VERSION != 0x00u)
#   error "GENy DLL is inconsistent!"
#  endif

# endif

#endif

#if defined( DET_ENABLED )

# if DET_AUTOSARVERSION == 4
#  define DET_START_SEC_VAR_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_DET_5087 */
DET_STATIC volatile VAR(uint8,DET_VAR) detModuleInit = STD_OFF; /* PRQA S 1504, 850 */ /* MD_DET_1504, MD_DET_0850 */
#  define DET_STOP_SEC_VAR_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_DET_5087 */
# endif

# if defined( DET_DEBUG_ENABLED )

#   if DET_AUTOSARVERSION == 4
#    define Det_EnterCritical() SchM_Enter_Det_DET_EXCLUSIVE_AREA_0()
#    define Det_LeaveCritical() SchM_Exit_Det_DET_EXCLUSIVE_AREA_0()
#   else
#    define Det_EnterCritical() SchM_Enter_Det(DET_EXCLUSIVE_AREA_0)
#    define Det_LeaveCritical() SchM_Exit_Det(DET_EXCLUSIVE_AREA_0)
#   endif

# define DET_START_SEC_VAR_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */  /* MD_DET_5087 */

/* global variables, should be put in a watch window */
# if DET_GLOBALFILTERSIZE > 0
volatile VAR(DetInfoType,DET_VAR) detGlobalFilter[DET_GLOBALFILTERSIZE]; /* ##### use this variable to configure global filters */ /* PRQA S 1504, 850 */ /* MD_DET_1504, MD_DET_0850 */
# endif
# if DET_BREAKFILTERSIZE > 0
volatile VAR(DetInfoType,DET_VAR) detBreakFilter[DET_BREAKFILTERSIZE];   /* ##### use this variable to configure break filters */ /* PRQA S 1504, 850 */ /* MD_DET_1504, MD_DET_0850 */
# endif
# if DET_LOGBUFFERSIZE > 0
volatile VAR(DetInfoType,DET_VAR) detLogBuffer[DET_LOGBUFFERSIZE];       /* ##### use this variable to view log buffer */ /* PRQA S 1504, 850 */ /* MD_DET_1504, MD_DET_0850 */
DET_STATIC volatile VAR(uint8,DET_VAR) detLock1;                                     /* used to resolve ESCAN00029923 */ /* PRQA S 1504, 850 */ /* MD_DET_1504, MD_DET_0850 */
# endif
volatile VAR(DetStatusType,DET_VAR) detStatus;                           /* ##### use this variable to configure DET debug operation */ /* PRQA S 1504, 850 */ /* MD_DET_1504, MD_DET_0850 */

# define DET_STOP_SEC_VAR_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */  /* MD_DET_5087 */

# endif /* DET_DEBUG_ENABLED */

#if defined( DET_ENTRY_CALLOUT_ENABLED )
# define DET_START_SEC_VAR_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */  /* MD_DET_5087 */
DET_STATIC volatile VAR(uint8,DET_VAR) detLock2;                                     /* used to resolve ESCAN00029923 */ /* PRQA S 1504, 850 */ /* MD_DET_1504, MD_DET_0850 */
# define DET_STOP_SEC_VAR_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */  /* MD_DET_5087 */
#endif


#define DET_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_DET_5087 */

/*******************************************************************************
 * Global functions as an interface from EcuM to DET for initialization
 * and start
 *******************************************************************************/

FUNC(void, DET_CODE) Det_Init( void ) /* PRQA S 1503, 850 */ /* MD_DET_1503, MD_DET_0850 */
{
#if defined( DET_DEBUG_ENABLED )
# if (DET_GLOBALFILTERSIZE > 0) || (DET_BREAKFILTERSIZE > 0) || (DET_LOGBUFFERSIZE > 0)
  VAR(uint8,AUTOMATIC) i; /* PRQA S 850 */ /* MD_DET_0850 */
# endif
  detStatus.globalFilterActive=0;
  detStatus.logActive=0;
  detStatus.logIndex=0;
  detStatus.breakOnLogOverrun=0;
  detStatus.breakFilterActive=0;
  detStatus.unlockBreak=0;
# if DET_GLOBALFILTERSIZE > 0
  for(i=0;i<DET_GLOBALFILTERSIZE;i++)
  {
    detGlobalFilter[i].moduleId=0;
    detGlobalFilter[i].instanceId=0;
    detGlobalFilter[i].apiId=0;
    detGlobalFilter[i].errorId=0;
  }
# endif
# if DET_BREAKFILTERSIZE > 0
  for(i=0;i<DET_BREAKFILTERSIZE;i++)
  {
    detBreakFilter[i].moduleId=0;
    detBreakFilter[i].instanceId=0;
    detBreakFilter[i].apiId=0;
    detBreakFilter[i].errorId=0;
  }
# endif
# if DET_LOGBUFFERSIZE > 0
  for(i=0;i<DET_LOGBUFFERSIZE;i++)
  {
    detLogBuffer[i].moduleId=0;
    detLogBuffer[i].instanceId=0;
    detLogBuffer[i].apiId=0;
    detLogBuffer[i].errorId=0;
  }
  detLock1=0;
# endif
#endif
#if defined( DET_ENTRY_CALLOUT_ENABLED )
  detLock2=0;
#endif
#if DET_AUTOSARVERSION == 4
  detModuleInit = STD_ON;
#endif
}

FUNC(void, DET_CODE) Det_Start( void ) /* PRQA S 1503, 850 */ /* MD_DET_1503, MD_DET_0850 */
{
}

#if DET_AUTOSARVERSION == 4
FUNC(void, DET_CODE) Det_InitMemory(void) /* PRQA S 1503, 850 */ /* MD_DET_1503, MD_DET_0850 */
{
  detModuleInit = STD_OFF;
}                               /* End of Det_InitMemory() */
#endif

/*******************************************************************************
 * Global function for BSW-Modules to report errors to the DET
 *******************************************************************************/
#if DET_AUTOSARVERSION == 4
FUNC(Std_ReturnType, DET_CODE) Det_ReportError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId ) /* PRQA S 1503, 850 */ /* MD_DET_1503, MD_DET_0850 */
#else
FUNC(void, DET_CODE) Det_ReportError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId ) /* PRQA S 1503, 850 */ /* MD_DET_1503, MD_DET_0850 */
#endif
{
#if defined( DET_DEBUG_ENABLED )
# if (DET_GLOBALFILTERSIZE > 0) || (DET_BREAKFILTERSIZE > 0)
  VAR(uint8,AUTOMATIC) i; /* PRQA S 850 */ /* MD_DET_0850 */
# endif
# if DET_LOGBUFFERSIZE > 0
  VAR(uint8,AUTOMATIC) forceBreakHandler=0; /* PRQA S 850 */ /* MD_DET_0850 */
# endif
#endif

#if defined( DET_COMP_ANSI_CANOE )
  char str[255]; /* PRQA S 5013 */ /* MD_DET_5013 */

# if(_MSC_VER >= 1400)
  time_t timeVal;
  struct tm timeS;

  (void) time(&timeVal); /* PRQA S 5127 */  /* MD_DET_5127 */ /* simulation environment, no production code */
  (void) localtime_s(&timeS, &timeVal); /* PRQA S 5127 */  /* MD_DET_5127 */ /* simulation environment, no production code */

  (void) strftime(str, sizeof(str), "%H:%M:%S", &timeS); /* PRQA S 5127 */  /* MD_DET_5127 */ /* simulation environment, no production code */

  (void) sprintf_s(str + strlen(str), sizeof(str) - strlen(str), " DET Error: ModuleId 0x%x, InstanceId 0x%x, ApiId 0x%x, ErrorId 0x%x", /* PRQA S 0488 */  /* MD_DET_0488 */ /* simulation environment, no production code */
     ModuleId, InstanceId, ApiId, ErrorId); 
# else
  (void) sprintf(str, "DET Error: ModuleId 0x%x, InstanceId 0x%x, ApiId 0x%x, ErrorId 0x%x",
     ModuleId, InstanceId, ApiId, ErrorId);
# endif
  CANoeAPI_WriteString((const char *)str);  /* PRQA S 5013 */ /* MD_DET_5013 */
#else
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
#  if ! defined( DET_ENTRY_CALLOUT_ENABLED ) && ((!defined(DET_DEBUG_ENABLED) || \
   (defined(DET_DEBUG_ENABLED) && (DET_GLOBALFILTERSIZE==0) && (DET_LOGBUFFERSIZE==0) && (DET_BREAKFILTERSIZE==0))))
  ModuleId = ModuleId;
  InstanceId = InstanceId;
  ApiId = ApiId; 
  ErrorId = ErrorId;
#  endif
# endif
#endif

#if DET_AUTOSARVERSION == 4
  if(detModuleInit == STD_OFF)
  {
    return E_OK; /* in case of call to uninitialized DET return */
  }
#endif

#if (DET_FORWARD_TO_DLT == STD_ON)
  Dlt_DetForwardErrorTrace(ModuleId, InstanceId, ApiId, ErrorId);
#endif

#if defined( DET_ENTRY_CALLOUT_ENABLED )
  if(detLock2==0) /* avoid recursion by potential DET calls in the callout */
  {
    detLock2=1;
    if(Appl_DetEntryCallout(ModuleId, InstanceId, ApiId, ErrorId)!=0)
    {
      detLock2=0;
# if DET_AUTOSARVERSION == 4
      return E_OK; /* handling is completely done in callout, abandon further processing */
# else
      return; /* handling is completely done in callout, abandon further processing */
# endif
    }
    detLock2=0;
  }
#endif

#if defined( DET_DEBUG_ENABLED )
  /* check for global filter match, in case of match discard error */
#if DET_GLOBALFILTERSIZE > 0
  if(detStatus.globalFilterActive!=0)
  {
    for(i=0;i<DET_GLOBALFILTERSIZE;i++)
    {
      if(
        ((detGlobalFilter[i].moduleId==ModuleId) || (detGlobalFilter[i].moduleId==0xffffu)) &&
        ((detGlobalFilter[i].instanceId==InstanceId) || (detGlobalFilter[i].instanceId==0xff)) &&
        ((detGlobalFilter[i].apiId==ApiId) || (detGlobalFilter[i].apiId==0xff)) &&
        ((detGlobalFilter[i].errorId==ErrorId) || (detGlobalFilter[i].errorId==0xff))
        )
      {
# if DET_AUTOSARVERSION == 4
        return E_OK;
# else
        return;
# endif
      }
    }
  }
#endif
#if DET_LOGBUFFERSIZE > 0
  if(detStatus.logActive!=0)
  {
    if(detLock1==0) /* avoid recursion by potential DET calls in enter / leave critical calls */
    {
      detLock1=1;
      Det_EnterCritical();
      detStatus.logIndex++;
      if(detStatus.logIndex>=DET_LOGBUFFERSIZE)
      {
        detStatus.logIndex=0;
        if(detStatus.breakOnLogOverrun!=0)
        {
          forceBreakHandler=1;
        }
      }
      detLogBuffer[detStatus.logIndex].moduleId=ModuleId;
      detLogBuffer[detStatus.logIndex].instanceId=InstanceId;
      detLogBuffer[detStatus.logIndex].apiId=ApiId;
      detLogBuffer[detStatus.logIndex].errorId=ErrorId;
      Det_LeaveCritical();
      detLock1=0;
    }
  }
#endif
  /* check for break filter match, in case of match discard error */
#if DET_BREAKFILTERSIZE > 0
# if DET_LOGBUFFERSIZE > 0
  if(forceBreakHandler==0)
  {
# endif
    if(detStatus.breakFilterActive!=0)
    {
      for(i=0;i<DET_BREAKFILTERSIZE;i++)
      {
        if(
          ((detBreakFilter[i].moduleId==ModuleId) || (detBreakFilter[i].moduleId==0xffffu)) &&
          ((detBreakFilter[i].instanceId==InstanceId) || (detBreakFilter[i].instanceId==0xff)) &&
          ((detBreakFilter[i].apiId==ApiId) || (detBreakFilter[i].apiId==0xff)) &&
          ((detBreakFilter[i].errorId==ErrorId) || (detBreakFilter[i].errorId==0xff))
          )
        {
#  if DET_AUTOSARVERSION == 4
          return E_OK;
#  else
          return;
#  endif
        }
      }
    }
# if DET_LOGBUFFERSIZE > 0
  }
# endif
#endif
# if ! defined( DET_COMP_ANSI_CANOE )
  while(detStatus.unlockBreak==0) /* set this variable to 0 to unlock breakpoint */
  {
    ; /* ##### typical place for a breakpoint if extended debugging support is enabled*/
  }
  detStatus.unlockBreak=0; /* PRQA S 3201 */ /* MD_DET_3201 */
# endif /* DET_COMP_ANSI_CANOE */
#else /* DET_DEBUG_ENABLED */
# if ! defined( DET_COMP_ANSI_CANOE )
  /* Endless loop for breakpoint in case of development error */
  while(1) 
  {
    ; /* ##### typical place for a breakpoint if extended debugging support is disabled*/
  }
# endif /* DET_COMP_ANSI_CANOE */
#endif /* DET_DEBUG_ENABLED */

#if DET_AUTOSARVERSION == 4
  return E_OK;
#endif
} /* PRQA S 2006, 6010, 6030 */ /* MD_DET_2006, MD_MSR_STPTH, MD_MSR_STCYC */ 

/*******************************************************************************
 * Global function for BSW-Modules to get the Version of Det
 *******************************************************************************/
#if (DET_VERSION_INFO_API == STD_ON)
FUNC(void, DET_CODE) Det_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, DET_APPL_DATA ) versioninfo ) /* PRQA S 1503, 850 */ /* MD_DET_1503, MD_DET_0850 */
{
  if(versioninfo!=((void*)0))
  {
    versioninfo->vendorID           = DET_VENDOR_ID;
    versioninfo->moduleID           = DET_MODULE_ID;
    versioninfo->sw_major_version   = DET_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version   = DET_SW_MINOR_VERSION;
    versioninfo->sw_patch_version   = DET_SW_PATCH_VERSION;
  }
}
#endif

#define DET_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_DET_5087 */

#endif /* DET_ENABLED */

/* module specific MISRA deviations:
   MD_DET_5013:
     Reason:     Usage of "char" data type is necessary if error messages are output in the CANoe write window because the CANoe API requires this. 
     Risk:       Potentially unknown size and signedness of data type.
     Prevention: The affected code part is only active in a PC simulation environment and does not run on an embedded target. Therefore this deviation is not critical. No change planned.
   MD_DET_1504:
     Reason:     The global variables could be used by the application for testing and debugging purposes, therefore they have been made global. The MISRA test configuration does not reference these variables.
     Risk:       These variables could be used by the application for unrelated purposes.
     Prevention: This deviation is not critical, no change planned.
   MD_DET_1503:
     Reason:     The API provided by the DET is not used in the test configuration for MISRA checking.
     Risk:       None.
     Prevention: This is not critical, no change planned.
   MD_DET_2006:
     Reason:     The function Det_ReportError has multiple return paths and a complex structure. 
     Risk:       Violation of ISO multiple return path requirement.
     Prevention: This will not be changed for the following reasons: - efficiency problem due to additional control variables (stack!) and additional conditions in the code - the structure of the code would become more complex which increases the risk of introducing errors.
   MD_DET_5087:
     Reason:     Violation caused by AUTOSAR memory mapping concept which requires the inclusion of the header MemMap.h.
     Risk:       None.
     Prevention: No workaround or change possible.
   MD_DET_0850:
     Reason:     Violation caused by AUTOSAR compiler abstraction concept can lead to empty macro parameters.
     Risk:       None.
     Prevention: No workaround or change possible.
   MD_DET_0883:
     Reason:     No violation - tool issue in QAC (empty #ifdef block with comments only not detected correctly)
     Risk:       None.
     Prevention: no risk and no change planned.
   MD_DET_5124:
     Reason:     Standard library functionality is only used in the CANoe simulation environemnt for debug purposes, not included in production code.
     Risk:       None.
     Prevention: No change planned.
   MD_DET_5127:
     Reason:     Standard library functionality is only used in the CANoe simulation environemnt for debug purposes, not included in production code.
     Risk:       None.
     Prevention: No change planned.
   MD_DET_0488:
     Reason:     Pointer arithmetic is only used in the CANoe simulation environemnt for debug purposes, not included in production code.
     Risk:       None.
     Prevention: No change planned.
   MD_DET_3201:
     Reason:     No violation - tool issue in QAC (it is not detected that loop can be left due to intended debug concept via manipulation of control variable).
     Risk:       None.
     Prevention: No change planned.
*/

/* STOPSINGLE_OF_MULTIPLE */
