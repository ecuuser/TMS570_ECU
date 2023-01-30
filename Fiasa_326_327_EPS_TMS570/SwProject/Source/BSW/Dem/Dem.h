/* Kernbauer Version: 1.15 Konfiguration: Diag_AsrDem_Vector Erzeugungsgangnummer: 1 */

/*********************************************************************************************************************/
/*!
 * \file     Dem.h
 * \brief    Interface of DEM
 * \par      copyright
 * \verbatim
 *  Copyright (c) 2015 by Vector Informatik GmbH. All rights reserved.
 *
 *  This software is copyright protected and proprietary to Vector Informatik GmbH.
 *  Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *  All other rights remain with Vector Informatik GmbH.
 *
 * \endverbatim
 */
/*  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Dem.h
 *      Project:  MICROSAR DEM
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  Interface of DEM
 *
 *  Manufacturer: Fiat
 *********************************************************************************************************************/

/******************************************************************************************************************//**
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 * \author                       Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Alexander Ditte              Ade           Vector Informatik GmbH
 *  Stefan Huebner               Hrs           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 * \version  Date        Author  Change Id      Description
 *  -------------------------------------------------------------------------------------------------------------------
 * 01.00.00  2010-11-02  Ade     -              Initial Version
 *                       Ade     ESCAN00044589  Sort list of API IDs
 *                       Ade     ESCAN00045948  Compiler error when using microcontroller with Paged RAM
 *                       Ade     ESCAN00046241  Adapt AUTOSAR version check
 *                       Ade     ESCAN00045037  Unify the call sequence of Dem_TriggerOnEvent() and DemCfg_GetInitMonitorFPtr()
 * 01.01.00  2010-12-01  Hrs     ESCAN00047310  Avoid nesting of Compiler Abstraction macros - P2VAR(P2CONST(...), ...)
 *                       Ade     ESCAN00047367  Remove NvM_GetErrorStatus() from Dem_Init()
 *                       Ade     ESCAN00047642  Modify status bits in their logic order
 *                       Ade     ESCAN00047934  Preprocessor error "#error "Dem: Incompatible AUTOSAR version of Fim!""
 *           2011-01-14  Ade     ESCAN00048024  Neg. Response ConditionNotCorrect in Diagnostic Services 19 0b, 19 0c, 19 0d, 19 0e
 * 01.02.00  2011-04-11  Ade     ESCAN00048454  Discarding of BSW events with status PASSED
 *                       Ade     ESCAN00049982  Change layout of the extended data record
 *                       Ade     ESCAN00049984  Change pending bit behavior
 *                       Ade     ESCAN00049986  Change the behavior of event aging
 *                       Ade     ESCAN00050014  Compiler error: "incompatible pointer types"
 *                       Ade     ESCAN00051170  Rename API ID defines for DET reporting
 *                       Ade     ESCAN00051171  Make the CurrentFailStatus configurable (DEM internal) if internal events shall be considered
 * 01.03.00  2011-06-30  Ade     ESCAN00051376  Remove unused code in Dem
 *                       Ade     ESCAN00051905  Time-based debouncing - DTC will not qualify
 *                       Ade     ESCAN00052128  Event displacement is not working correctly
 *                       Ade     ESCAN00052130  Remove DET check for a severity mask which is out of range
 * 01.04.00  2011-08-22  Ade     ESCAN00052916  The NVRAM block handling was reworked
 *           2011-08-29  Ade     ESCAN00051738  Remove the AUTOSAR Release Version Check
 *                       Ade     ESCAN00048943  Use standard include guard for Dem.h: #if defined (DEM_H)
 *                       Ade     ESCAN00052886  Replace internal error code "DEM_E_INV_SFN" with "DEM_E_PARAM_DATA"
 *           2011-09-19  Ade     ESCAN00053505  AR3-2069: Remove non-SchM code for critical section handling
 *           2011-10-18  Ade     ESCAN00051905  Time-based debouncing - DTC will not qualify
 * 01.04.01  2012-05-29  Ade     ESCAN00059173  Inconsistent usage of Dem_Cfg_AdminCycleStatePtr[]
 *           2013-01-25  Mhe     ESCAN00063880  Compiler error: 'DEM_IS_SET_WARNING_INDICATOR_REQ' undefined
 * 01.05.00  2013-04-11  Ade     -              Update to GENy version 3.12.00
 * 01.06.00  2013-10-18  Ade     -              Update to GENy version 3.13.00
 * 01.06.01	 2014-04-30  Ade     ESCAN00075163  Needless frequent NVRAM commit for pre-/Failed events
 * 01.06.02  2014-05-19  Ade     ESCAN00075717  DTC will not age 
 * 01.06.03  2015-01-15  Ade     ESCAN00080038  Snapshot record data is not persisted in NVRAM
 */                              
/******************************************************************************************************************/

#if !defined (DEM_H)
#define DEM_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "Std_Types.h"

#if (defined(STD_OFF) && defined(STD_ON))
#else
# error "Definition of STD_ON and/or STD_OFF is missing in Std_Types.h"
#endif

/* get GENy generated (CompileTime) configuration from file "Dem_Cfg.h" */
#include "Dem_Cfg.h"

/* -----------------------------------------------------------------------------
  Datatype definitions
 ----------------------------------------------------------------------------- */

#include "Dem_Types.h"

/* -----------------------------------------------------------------------------
  EventId definitions
 ----------------------------------------------------------------------------- */

/* PreConfig + PostBuild: #define  EVENT_CONFIG_NAME  DEM-internal-EventId */

/* BSW event Id symbols */
#include "Dem_IntErrId.h"
/* SW_C event Id symbols */
#include "Dem_IntEvtId.h"

/* -----------------------------------------------------------------------------
  Consistency check between generated code and static code/library
 ----------------------------------------------------------------------------- */

/* Check is not required for PRE-COMPILE variant */
#if (DEM_CONFIG_VARIANT != 1)
# define DEM_START_SEC_CONST_8BIT
# include "MemMap.h"                                                                              /* PRQA S 5087 *//* MD_MSR_19.1 */ 
extern CONST(uint8, DEM_CONST)  Dem_NeedDemLibVersion_SW_01_06_xx;                                /* PRQA S 0850 *//* MD_MSR_19.8 */
extern CONST(uint8, DEM_CONST)  Dem_NeedDemLibOem_DEM_FGA;                                        /* PRQA S 0850 *//* MD_MSR_19.8 */
# define DEM_STOP_SEC_CONST_8BIT
# include "MemMap.h"                                                                              /* PRQA S 5087 *//* MD_MSR_19.1 */ 
#endif

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Version - BCD coded version number - Main- and Sub-Version - Release-Version */
#define DIAG_ASRDEM_VERSION                     DIAG_ASRDEM_FIAT_VERSION
#define DIAG_ASRDEM_RELEASE_VERSION             DIAG_ASRDEM_FIAT_RELEASE_VERSION
/* ##V_CFG_MANAGEMENT ##CQProject : Diag_AsrDem_Fiat CQComponent : Implementation */
#define DIAG_ASRDEM_FIAT_VERSION                0x0106u
#define DIAG_ASRDEM_FIAT_RELEASE_VERSION        0x03u
/* ##V_CFG_MANAGEMENT ##CQProject : Diag_AsrDem__core CQComponent : Implementation */
#define DIAG_ASRDEM__CORE_VERSION               0x0300u
#define DIAG_ASRDEM__CORE_RELEASE_VERSION       0x01u

/* vendor and module identification */
#define DEM_VENDOR_ID                           30    /* Vector Informatik GmbH */
#define DEM_MODULE_ID                           54    /* DEM */
#define DEM_INSTANCE_ID                         0     /* always 1 instance */

/* AUTOSAR Software Specification Version Information (decimal coded) */
#define DEM_AR_MAJOR_VERSION                    2     /* Major version of AUTOSAR specification */
#define DEM_AR_MINOR_VERSION                    2     /* Minor version of AUTOSAR specification */
#define DEM_AR_PATCH_VERSION                    1     /* Patch version of AUTOSAR specification */
 
/* Component Version Information */
#define DEM_SW_MAJOR_VERSION                    (DIAG_ASRDEM_VERSION >> 8u)
#define DEM_SW_MINOR_VERSION                    (DIAG_ASRDEM_VERSION & 0x00FFu)
#define DEM_SW_PATCH_VERSION                    DIAG_ASRDEM_RELEASE_VERSION

/* error reporting with Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID, ApiId, ErrorId): */
/* API Service IDs for reporting errors to the DET */
#define DEM_GETVERSIONINFO_APIID                    0x00
#define DEM_PREINIT_APIID                           0x01
#define DEM_INIT_APIID                              0x02
#define DEM_SHUTDOWN_APIID                          0x03
#define DEM_SETEVENTSTATUS_APIID                    0x04
#define DEM_RESETEVENTSTATUS_APIID                  0x05
#define DEM_PRESTOREFREEZEFRAME_APIID               0x06
#define DEM_CLEARPRESTOREDFREEZEFRAME_APIID         0x07
#define DEM_SETOPERATIONCYCLESTATE_APIID            0x08
#define DEM_GETEVENTSTATUS_APIID                    0x0a
#define DEM_GETEVENTFAILED_APIID                    0x0b
#define DEM_GETEVENTTESTED_APIID                    0x0c
#define DEM_GETDTCOFEVENT_APIID                     0x0d
#define DEM_GETSEVERITYOFDTC_APIID                  0x0e
#define DEM_REPORTERRORSTATUS_APIID                 0x0f

#define DEM_SETDTCFILTER_APIID                      0x13
#define DEM_SETVIEWFILTER_APIID                     0x14
#define DEM_GETSTATUSOFDTC_APIID                    0x15
#define DEM_GETDTCSTATUSAVAILABILITYMASK_APIID      0x16
#define DEM_GETNUMBEROFFILTEREDDTC_APIID            0x17
#define DEM_GETNEXTFILTEREDDTC_APIID                0x18
#define DEM_GETDTCBYOCCURRENCETIME_APIID            0x19
#define DEM_DISABLEDTCRECORDUPDATE_APIID            0x1a
#define DEM_ENABLEDTCRECORDUPDATE_APIID             0x1b
#define DEM_GETDTCOFFREEZEFRAMERECORD_APIID         0x1c
#define DEM_GETFREEZEFRAMEDATABYDTC_APIID           0x1d
#define DEM_GETFREEZEFRAMEDATAIDENTIFIERBYDTC_APIID 0x1e
#define DEM_GETSIZEOFFREEZEFRAME_APIID              0x1f

#define DEM_GETEXTENDEDDATARECORDBYDTC_APIID        0x20
#define DEM_GETSIZEOFEXTENDEDDATARECORDBYDTC_APIID  0x21
#define DEM_CLEARDTC_APIID                          0x22
#define DEM_DISABLEDTCSETTING_APIID                 0x24
#define DEM_DISABLEDTCSTORAGE_APIID                 0x24    /* unused, kept for Compatibilty to ASR 3.0 */
#define DEM_ENABLEDTCSETTING_APIID                  0x25
#define DEM_ENABLEDTCSTORAGE_APIID                  0x25    /* unused, kept for Compatibilty to ASR 3.0 */

#define DEM_DISABLEEVENTSTATUSUPDATE_APIID          0x26    /* unused, kept for Compatibilty to ASR 3.0 */
#define DEM_ENABLEEVENTSTATUSUPDATE_APIID           0x27    /* unused, kept for Compatibilty to ASR 3.0 */
/* #define DEM_GETMILSTATUS_APIID                     40    no ServiceId in ASR 3.0 any more */
#define DEM_GETINDICATORSTATUS_APIID                0x29
/* #define DEM_GETOBDREADINESS_APIID                  42    no ServiceId in ASR 3.0 any more */
/* #define DEM_GETDISTANCEMIL_APIID                   43    no ServiceId in ASR 3.0 any more */
/* #define DEM_GETWARMUPCYCLEDTCCLEAR_APIID           44    no ServiceId in ASR 3.0 any more */
/* #define DEM_GETDISTANCEDTCCLEAR_APIID              45    no ServiceId in ASR 3.0 any more */
/* #define DEM_GETMONITORSTATUS_APIID                 46    no ServiceId in ASR 3.0 any more */
/* #define DEM_GETTIMEMILS_APIID                      47    no ServiceId in ASR 3.0 any more */
/* #define DEM_GETTIMEDTCCLEAR_APIID                  48    no ServiceId in ASR 3.0 any more */
/* #define DEM_XXX_DEMINITFUNCTION_APIID              50    no ServiceId in ASR 3.0 any more */
/* #define DEM_XXX_DEMTRIGGERONEVENTSTATUS_APIID      51    no ServiceId in ASR 3.0 any more */
/* #define DEM_XXX_DEMTRIGGERONDTCSTATUS_APIID        52    no ServiceId in ASR 3.0 any more */
#define DEM_XXX_GETDATAVALUEBYDATAIDENTIFIER_APIID  0x35    /* no ServiceId in ASR 3.0, number 53 (=0x35) is from ASR 2.1 */
#define DEM_GETVIEWIDOFDTC_APIID                    0x36
#define DEM_GETEXTENDEDDATARECORD_APIID             0x37    
#define DEM_SETVALUEBYOEMID_APIID                   0x38
#define DEM_SETENABLECONDITION_APIID                0x39

#define DEM_GETNEXTFILTEREDRECORD_APIID             0x3a
#define DEM_GETNEXTFILTEREDDTCANDFDC_APIID          0x3b
#define DEM_GETNEXTFILTEREDDTCANDSEVERITY_APIID     0x3d
#define DEM_GETTRANSLATIONTYPE_APIID                0x3c
#define DEM_GETFAULTDETECTIONCOUNTER_APIID          0x3e
#define DEM_SETDTCFILTERFORRECORDS_APIID            0x3f

#define DEM_MAINFUNCTION_APIID                      0x55
/* Additional ApiId for functions beyond AUTOSAR standard */
#define DEM_ADDON_APIID                             224 /* 0xE0 */
/* Additional ApiId for internal functions */
#define DEM_INTERNAL_APIID                           0xE7    /* 231 */
#define DEM_CALLEVENTINITMONITOR_APIID              (DEM_INTERNAL_APIID+0)  /* 0xE7: update status of an indicator */

#define DEM_UPDATESNAPSHOTRECORD_APIID              (DEM_INTERNAL_APIID+10) /* 0xF1 */
#define DEM_MEMMOVE_APIID                           (DEM_INTERNAL_APIID+11) /* 0xF2 */
#define DEM_UPDATEDTCINPRIM_NOTACT2ACT_APIID        (DEM_INTERNAL_APIID+12) /* 0xF3 */
#define DEM_MEMFREEPRIMARYENTRY                     (DEM_INTERNAL_APIID+13) /* 0xF4 */
#define DEM_GETOFFSETSNAPSHOTRECORDNTH_APIID        (DEM_INTERNAL_APIID+14) /* 0xF5 */
#define DEM_GETMOSTRECENTSNAPSHOTINDEX_APIID        (DEM_INTERNAL_APIID+15) /* 0xF6 */
#define DEM_CLEARSINGLEEVENT_APIID                  (DEM_INTERNAL_APIID+16) /* 0xF7 */
#define DEM_UPDATEDTCINPRIM_ACT2NOTACT_APIID        (DEM_INTERNAL_APIID+17) /* 0xF8 */
#define DEM_UPDATEUSERDATARECORD_APIID              (DEM_INTERNAL_APIID+18) /* 0xF9 */
#define DEM_ALLOCATEPRIMEMENTRY_APIID               (DEM_INTERNAL_APIID+19) /* 0xFA */
#define DEM_REALLOCATEPRIMEMENTRY_APIID             (DEM_INTERNAL_APIID+20) /* 0xFB */

#define DEM_CALCNEWDEBOUNCETIMERSLOTVAL_APIID       (DEM_INTERNAL_APIID+22) /* 0xFD */
#define DEM_INITDIAGNOSTICVARIANT_APIID             (DEM_INTERNAL_APIID+23) /* 0xFE */
#define DEM_AQPUSH_APIID                            (DEM_INTERNAL_APIID+24) /* 0xFF */  

/* Application ErrorIDs for RTE/API Application Errors in addition to E_OK and E_NOT_OK */
#define DEM_E_QUEUE_OVERFLOW                            0x0F

/* ErrorIDs for reporting errors to the DET */
/*      API service called with wrong parameter: */
#define DEM_E_PARAM_CONFIG                              0x10    /* using un-configured parameter */
#define DEM_E_PARAM_ADDRESS                             0x11    /* invalid address (NULL_PTR) */
#define DEM_E_PARAM_DATA                                0x12    /* data value out of range, incorrect data */
#define DEM_E_PARAM_LENGTH                              0x13    /* incorrect length of parameter */
/*      API service called before the DEM module has been initialized */
#define DEM_E_UNINIT                                    0x20
/*      No valid data available by the SW-C */
#define DEM_E_NODATAAVAILABLE                           0x30
/* range 0x80..0x9f is reserved for internal Debug codes that denote fatal errors */
#define DEM_E_DTC_NOT_FOUND                             0x82
#define DEM_E_ERASING_EMPTY_STACK                       0x83
#define DEM_E_INV_CSTACK_REF                            0x86
#define DEM_E_INV_SNAPSHOT_NUM                          0x8f
#define DEM_E_ZEROPTR_SOURCE                            0x90
#define DEM_E_ZEROPTR_TARGET                            0x91
#define DEM_E_TOO_MANY_DIDS_FOR_EVENT                   0x92
#define DEM_E_TOO_MANY_INDICATOR_IDS                    0x93
#define DEM_E_INVALIDSTATE                              0x94
#define DEM_E_INV_TIMER_SLOT_VAL                        0x95
#define DEM_E_NOT_IN_ACTIVE_VARIANT                     0x96

/* internal check for empty or uninitialized NVRAM (if NvM doesn't use the init-callback Dem_NvDataInit()) */
#define DEM_ENABLE_PATTERN_CHECK                        STD_ON

/* initial value used in Dem_NvDataInit() to initialize Dem_NvData buffer */ 
#define DEM_NVDATA_INIT_VALUE                           0xFFu

/* support for internal occurrence counter */
#if defined (DEM_SUPPORT_OCCURRENCE_COUNTER)
#else
# define DEM_SUPPORT_OCCURRENCE_COUNTER                 STD_OFF
#endif

/* value for invalid DTC number */
#define DEM_DTCNUMBER_INVALID                           0xFFFFFFFFuL

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/* Support of DET to handle assertions */
/* extern void Det_ReportError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId ); */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
# define Dem_DetReportError(ApiId, ErrorId)   Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID, (ApiId), (ErrorId))         /* PRQA S 3453 *//* MD_MSR_19.7 */
#else
# define Dem_DetReportError(ApiId, ErrorId)   do {/* no DET error reporting */} while(0)
#endif

/** Protection for critical areas against concurrent access */
# define Dem_EnterCritical_Large() SchM_Enter_Dem(DEM_EXCLUSIVE_AREA_0)
# define Dem_LeaveCritical_Large() SchM_Exit_Dem(DEM_EXCLUSIVE_AREA_0)
# define Dem_EnterCritical_PreInit() SchM_Enter_Dem(DEM_EXCLUSIVE_AREA_1)
# define Dem_LeaveCritical_PreInit() SchM_Exit_Dem(DEM_EXCLUSIVE_AREA_1)
# define Dem_EnterCritical_Short() SchM_Enter_Dem(DEM_EXCLUSIVE_AREA_2)
# define Dem_LeaveCritical_Short() SchM_Exit_Dem(DEM_EXCLUSIVE_AREA_2)

 /**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#if (DEM_SUPPORT_VARIANT_HANDLING == STD_ON) || (DEM_SUPPORT_MULTIPLE_CONFIG == STD_ON)
#define DEM_START_SEC_VAR_FAST_32BIT
#include "MemMap.h"                                                                               /* PRQA S 5087 *//* MD_MSR_19.1 */ 
extern VAR(uint32, DEM_VAR_NOINIT_FAST)  Dem_ActiveVariant;                                       /* PRQA S 0850 *//* MD_MSR_19.8 */
#define DEM_STOP_SEC_VAR_FAST_32BIT 
#include "MemMap.h"                                                                               /* PRQA S 5087 *//* MD_MSR_19.1 */ 
#endif  /* DEM_SUPPORT_VARIANT_HANDLING || DEM_SUPPORT_MULTIPLE_CONFIG */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define DEM_START_SEC_CODE 
#include "MemMap.h"                                                                               /* PRQA S 5087 *//* MD_MSR_19.1 */ 

/* Server PortInterface of the DEM (maybe defined in Rte_Dem.h too - depends on RTE/Application config) */
FUNC(void, DEM_CODE)                                                                              /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_ClientRunnable(                                                                               /* PRQA S 3451 *//* MD_DEM_8.8_3451 */
  void
  );  /* PRQA S 1503 */

/* Server PortInterface of the DEM (maybe defined in Rte_Dem.h too - depends on RTE/Application config) */
FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 */ /* MD_MSR_19.8 */
Dem_PostRunRequested(                                                                             /* PRQA S 3451 */ /* MD_DEM_8.8_3451 */
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  IsRequested                                           /* PRQA S 0850 */ /* MD_MSR_19.8 */
  );

FUNC(Dem_ReturnSetDTCFilterType, DEM_CODE)                                                        /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_SetDTCFilter(
  Dem_DTCStatusMaskType                   DTCStatusMask,
  Dem_DTCKindType                         DTCKind,
  Dem_DTCOriginType                       DTCOrigin,
  Dem_FilterWithSeverityType              FilterWithSeverity,
  Dem_DTCSeverityType                     DTCSeverity,
  Dem_FilterForFaultDetectionCounterType  FilterForFaultDetectionCounter
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnSetDTCFilterType, DEM_CODE)                                                        /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_SetDTCFilterForRecords(
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  NumberOfFilteredRecords                                /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnSetViewFilterType, DEM_CODE)                                                       /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_SetViewFilter(
  Dem_ViewIdType ViewId
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnGetStatusOfDTCType, DEM_CODE)                                                      /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetStatusOfDTC(
  Dem_DTCType                                             DTC,
  Dem_DTCKindType                                         DTCKind,
  Dem_DTCOriginType                                       DTCOrigin,
  P2VAR(Dem_DTCStatusMaskType, AUTOMATIC, DEM_APPL_DATA)  DTCStatus                               /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetDTCStatusAvailabilityMask(
  P2VAR(Dem_DTCStatusMaskType, AUTOMATIC, DEM_APPL_DATA)  DTCStatusMask                           /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnGetNumberOfFilteredDTCType, DEM_CODE)                                              /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetNumberOfFilteredDTC(
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  NumberOfFilteredDTC                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnGetNextFilteredDTCType, DEM_CODE)                                                  /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetNextFilteredDTC(
 P2VAR(Dem_DTCType,           AUTOMATIC, DEM_APPL_DATA)  DTC,                                     /* PRQA S 0850 *//* MD_MSR_19.8 */
 P2VAR(Dem_DTCStatusMaskType, AUTOMATIC, DEM_APPL_DATA)  DTCStatus                                /* PRQA S 0850 *//* MD_MSR_19.8 */
 );  /* PRQA S 1503 */

FUNC(Dem_ReturnGetNextFilteredDTCType, DEM_CODE)                                                  /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetNextFilteredRecord(
  P2VAR(Dem_DTCType, AUTOMATIC, DEM_APPL_DATA)  DTC,                                              /* PRQA S 0850 *//* MD_MSR_19.8 */
  P2VAR(uint8,       AUTOMATIC, DEM_APPL_DATA)  SnapshotRecord                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnGetNextFilteredDTCType, DEM_CODE)                                                  /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetNextFilteredDTCAndFDC(
 P2VAR(Dem_DTCType, AUTOMATIC, DEM_APPL_DATA)  DTC,                                               /* PRQA S 0850 *//* MD_MSR_19.8 */
 P2VAR(sint8,       AUTOMATIC, DEM_APPL_DATA)  DTCFaultDetectionCounter                           /* PRQA S 0850 *//* MD_MSR_19.8 */
 );  /* PRQA S 1503 */

FUNC(Dem_ReturnGetNextFilteredDTCType, DEM_CODE)                                                  /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetNextFilteredDTCAndSeverity(
 P2VAR(Dem_DTCType,           AUTOMATIC, DEM_APPL_DATA)  DTC,                                     /* PRQA S 0850 *//* MD_MSR_19.8 */
 P2VAR(Dem_DTCStatusMaskType, AUTOMATIC, DEM_APPL_DATA)  DTCStatus,                               /* PRQA S 0850 *//* MD_MSR_19.8 */
 P2VAR(Dem_DTCSeverityType,   AUTOMATIC, DEM_APPL_DATA)  DTCSeverity,                             /* PRQA S 0850 *//* MD_MSR_19.8 */
 P2VAR(uint8,                 AUTOMATIC, DEM_APPL_DATA)  DTCFunctionalUnit                        /* PRQA S 0850 *//* MD_MSR_19.8 */
 );  /* PRQA S 1503 */

FUNC(uint8, DEM_CODE)                                                                             /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetTranslationType(
  void
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnGetDTCByOccurrenceTimeType, DEM_CODE)                                              /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetDTCByOccurrenceTime(
  Dem_DTCRequestType                            DTCRequest,
  Dem_DTCKindType                               DTCKind,
  P2VAR(Dem_DTCType, AUTOMATIC, DEM_APPL_DATA)  DTC                                               /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_NvDataInit( 
  void
  );  /* PRQA S 1503 */

FUNC(void, DEM_CODE)                                                                              /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_MainFunction(
  void
  );  /* PRQA S 1503 */

FUNC(void, DEM_CODE)                                                                              /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_InitMemory(
  void
  );  /* PRQA S 1503 */

#if (DEM_SUPPORT_VARIANT_HANDLING == STD_ON)
FUNC(void, DEM_CODE)                                                                              /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_InitDiagnosticVariant(
  uint32 activeCfg
  );  /* PRQA S 1503 */
#endif  /* DEM_SUPPORT_VARIANT_HANDLING */

#if (DEM_SUPPORT_MULTIPLE_CONFIG == STD_ON) || (DEM_SUPPORT_VARIANT_HANDLING == STD_ON) || (DEM_PREINIT_HAS_CONFIG_PARAM == STD_ON)
FUNC(void, DEM_CODE)                                                                              /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_PreInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_CONST) activeCfg                                         /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */
#else
FUNC(void, DEM_CODE)                                                                              /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_PreInit(
  void
  );  /* PRQA S 1503 */
#endif

FUNC(void, DEM_CODE)                                                                              /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_Init(
  void
  );  /* PRQA S 1503 */

FUNC(void, DEM_CODE)                                                                              /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_Shutdown(
  void
  );  /* PRQA S 1503 */

#if (DEM_VERSION_INFO_API == STD_ON)
FUNC(void, DEM_CODE)                                                                              /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, DEM_APPL_DATA)  versioninfo                               /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */
#endif

/* Server PortInterface of the DEM (maybe defined in Rte_Dem.h too - depends on RTE/Application config) */
FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_ResetEventStatus(                                                                             /* PRQA S 3451 *//* MD_DEM_8.8_3451 */
  Dem_EventIdType   EventId
  );  /* PRQA S 1503 */

FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_PrestoreFreezeFrame(
  Dem_EventIdType   EventId
  );  /* PRQA S 1503 */

FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_ClearPrestoredFreezeFrame(
  Dem_EventIdType   EventId
  );  /* PRQA S 1503 */

/* Server PortInterface of the DEM (maybe defined in Rte_Dem.h too - depends on RTE/Application config) */
FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_SetOperationCycleState(                                                                       /* PRQA S 3451 *//* MD_DEM_8.8_3451 */
  Dem_OperationCycleIdType      OperationCycleId,
  Dem_OperationCycleStateType   CycleState
  );  /* PRQA S 1503 */

/* Server PortInterface of the DEM (maybe defined in Rte_Dem.h too - depends on RTE/Application config) */
FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_SetEventStatus(                                                                               /* PRQA S 3451 *//* MD_DEM_8.8_3451 */
  Dem_EventIdType       EventId,
  Dem_EventStatusType   EventStatus
  );  /* PRQA S 1503 */

/* Server PortInterface of the DEM (maybe defined in Rte_Dem.h too - depends on RTE/Application config) */
FUNC(void, DEM_CODE)                                                                              /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_ReportErrorStatus(                                                                            /* PRQA S 3451 *//* MD_DEM_8.8_3451 */
  Dem_EventIdType       EventId,
  Dem_EventStatusType   EventStatus
  );  /* PRQA S 1503 */

/* Server PortInterface of the DEM (maybe defined in Rte_Dem.h too - depends on RTE/Application config) */
FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetEventStatus(                                                                               /* PRQA S 3451 *//* MD_DEM_8.8_3451 */
  Dem_EventIdType                                               EventId,
  P2VAR(Dem_EventStatusExtendedType, AUTOMATIC, DEM_APPL_DATA)  EventStatusExtended               /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

/* Server PortInterface of the DEM (maybe defined in Rte_Dem.h too - depends on RTE/Application config) */
FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetEventFailed(                                                                               /* PRQA S 3451 *//* MD_DEM_8.8_3451 */
  Dem_EventIdType                           EventId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventFailed                                           /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

/* Server PortInterface of the DEM (maybe defined in Rte_Dem.h too - depends on RTE/Application config) */
FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetEventTested(                                                                               /* PRQA S 3451 *//* MD_DEM_8.8_3451 */
  Dem_EventIdType                           EventId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventTested                                           /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

/* Server PortInterface of the DEM (maybe defined in Rte_Dem.h too - depends on RTE/Application config) */
FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetDTCOfEvent(                                                                                /* PRQA S 3451 *//* MD_DEM_8.8_3451 */
  Dem_EventIdType                                               EventId,
  Dem_DTCKindType                                               DTCKind,
  P2VAR(Dem_DTCType,                 AUTOMATIC, DEM_APPL_DATA)  DTCOfEvent                        /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_SetValueByOemId(
  uint16                                  OemID,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DataValue,                                              /* PRQA S 0850 *//* MD_MSR_19.8 */
  uint8                                   BufferLength
  );  /* PRQA S 1503 */

FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_SetEnableCondition(
  uint8     EnableConditionID,
  boolean   ConditionFulfilled
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnGetSeverityOfDTCType, DEM_CODE)                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetSeverityOfDTC(
  Dem_DTCType                                                       DTC,
  P2VAR(Dem_DTCSeverityType,            AUTOMATIC, DEM_APPL_DATA)   DTCSeverity                   /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnControlDTCSettingType, DEM_CODE)                                                   /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_DisableDTCSetting(
  Dem_DTCGroupType  DTCGroup,
  Dem_DTCKindType   DTCKind
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnControlDTCSettingType, DEM_CODE)                                                   /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_EnableDTCSetting(
  Dem_DTCGroupType  DTCGroup,
  Dem_DTCKindType   DTCKind
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnControlDTCStorageType, DEM_CODE)                                                   /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_DisableDTCStorage(
  Dem_DTCGroupType  DTCGroup,
  Dem_DTCKindType   DTCKind
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnControlDTCStorageType, DEM_CODE)                                                   /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_EnableDTCStorage(
  Dem_DTCGroupType  DTCGroup,
  Dem_DTCKindType   DTCKind
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnControlEventUpdateType, DEM_CODE)                                                  /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_DisableEventStatusUpdate(
  Dem_DTCGroupType  DTCGroup,
  Dem_DTCKindType   DTCKind
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnControlEventUpdateType, DEM_CODE)                                                  /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_EnableEventStatusUpdate(
  Dem_DTCGroupType  DTCGroup,
  Dem_DTCKindType   DTCKind
  );  /* PRQA S 1503 */

FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetIndicatorStatus(
  Dem_IndicatorIdType                                       Dem_IndicatorId,
  P2VAR(Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA)  Dem_IndicatorStatus                   /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetFaultDetectionCounter(
  Dem_EventIdType                                                 EventId,
  P2VAR(Dem_FaultDetectionCounterType, AUTOMATIC, DEM_APPL_DATA)  EventIdFaultDetectionCounter    /* PRQA S 0850 *//* MD_MSR_19.8 */
);  /* PRQA S 1503 */

FUNC(Dem_ReturnGetDTCOfFreezeFrameRecordType, DEM_CODE)                                           /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetDTCOfFreezeFrameRecord(
  uint8                                         RecordNumber,
  Dem_DTCOriginType                             DTCOrigin,
  Dem_DTCKindType                               DTCKind,
  P2VAR(Dem_DTCType, AUTOMATIC, DEM_APPL_DATA)  DTC                                               /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnGetFreezeFrameDataIdentifierByDTCType, DEM_CODE)                                   /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetFreezeFrameDataIdentifierByDTC(
  Dem_DTCType                                             DTC,
  Dem_DTCKindType                                         DTCKind,
  Dem_DTCOriginType                                       DTCOrigin,
  uint8                                                   RecordNumber,
  P2VAR(uint8,                 AUTOMATIC, DEM_APPL_DATA)  ArraySize,                              /* PRQA S 0850 *//* MD_MSR_19.8 */
  P2VAR(Dem_RecordDIDAddrType, AUTOMATIC, DEM_APPL_DATA)  DataId  /* const uint16 **DataId */     /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnGetFreezeFrameDataByDTCType, DEM_CODE)                                             /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetFreezeFrameDataByDTC(
  Dem_DTCType                             DTC,
  Dem_DTCKindType                         DTCKind,
  Dem_DTCOriginType                       DTCOrigin,
  uint8                                   RecordNumber,
  uint16                                  DataId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,                                             /* PRQA S 0850 *//* MD_MSR_19.8 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  BufSize                                                 /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnGetSizeOfFreezeFrameType, DEM_CODE)                                                /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetSizeOfFreezeFrame(
  Dem_DTCType                               DTC,
  Dem_DTCKindType                           DTCKind,
  Dem_DTCOriginType                         DTCOrigin,
  uint8                                     RecordNumber,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)   SizeOfFreezeFrame                                     /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnGetExtendedDataRecordByDTCType, DEM_CODE)                                          /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetExtendedDataRecordByDTC(
  Dem_DTCType                             DTC,
  Dem_DTCKindType                         DTCKind,
  Dem_DTCOriginType                       DTCOrigin,
  uint8                                   ExtendedDataNumber,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,                                             /* PRQA S 0850 *//* MD_MSR_19.8 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  BufSize                                                 /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnGetSizeOfExtendedDataRecordByDTCType, DEM_CODE)                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetSizeOfExtendedDataRecordByDTC(
  Dem_DTCType                               DTC,
  Dem_DTCKindType                           DTCKind,
  Dem_DTCOriginType                         DTCOrigin,
  uint8                                     ExtendedDataNumber,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)   SizeOfExtendedDataRecord                              /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnClearDTCType, DEM_CODE)                                                            /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_ClearDTC(
  Dem_DTCType         DTC,
  Dem_DTCKindType     DTCKind,
  Dem_DTCOriginType   DTCOrigin
  );  /* PRQA S 1503 */

FUNC(Dem_ReturnGetViewIDOfDTCType, DEM_CODE)                                                      /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_GetViewIDOfDTC(
  Dem_DTCType                                       DTC,
  Dem_DTCKindType                                   DTCKind,
  P2VAR(Dem_ViewIdType, AUTOMATIC, DEM_APPL_DATA)   ViewId                                        /* PRQA S 0850 *//* MD_MSR_19.8 */
  );  /* PRQA S 1503 */

FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_DisableDTCRecordUpdate(
  void
  );  /* PRQA S 1503 */

FUNC(Std_ReturnType, DEM_CODE)                                                                    /* PRQA S 0850 *//* MD_MSR_19.8 */
Dem_EnableDTCRecordUpdate(
  void
  );  /* PRQA S 1503 */

#define DEM_STOP_SEC_CODE 
#include "MemMap.h"                                                                               /* PRQA S 5087 *//* MD_MSR_19.1 */ 

#define DEM_APPL_START_SEC_CODE 
#include "MemMap.h"                                                                               /* PRQA S 5087 *//* MD_MSR_19.1 */ 

#if ( DEM_ENABLE_FAIL_STATE_NOTIFICATION == STD_ON )
/* Support for FailState Notification APIs */
extern FUNC(void, DEM_APPL_CODE)                                                                  /* PRQA S 0850 *//* MD_MSR_19.8 */
Appl_Dem_GenericFailStateChangeNotification(
  boolean failState
  );
extern FUNC(void, DEM_APPL_CODE)                                                                  /* PRQA S 0850 *//* MD_MSR_19.8 */
Appl_Dem_CurrentFailStateChangeNotification(
  boolean failState
  );
#endif /* ( DEM_ENABLE_FAIL_STATE_NOTIFICATION == STD_ON ) */

#define DEM_APPL_STOP_SEC_CODE 
#include "MemMap.h"                                                                               /* PRQA S 5087 *//* MD_MSR_19.1 */ 

#endif /* DEM_H */

