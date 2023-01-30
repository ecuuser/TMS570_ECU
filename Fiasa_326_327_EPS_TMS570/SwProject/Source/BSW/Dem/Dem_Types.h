/* Kernbauer Version: 1.15 Konfiguration: Diag_AsrDem_Vector Erzeugungsgangnummer: 1 */

/*********************************************************************************************************************/
/*!
 * \file     Dem_Types.h
 * \brief    Typedefs for DEM
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
 *         File:  Dem_Types.h
 *      Project:  MICROSAR DEM
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  Typedefs of DEM
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

#if defined(DEM_TYPES_H)
#else
#define DEM_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* for typedef Dem_DtcStatusByteType  we require  #include "Dem_Cfg.h" */
#if defined(DEM_CFG_H) || defined(__DEM_CFG_H__)
#else
#error "Wrong #include sequence: Please include \"Dem_Cfg.h\" before including file \"Dem_Types.h\""
#endif

/**
 * File Rte_Type.h contains the typedefs and defines which are required as PortInterface argument
 * and also used in the DEM. If we are not using the RTE, the types will be defined by ourself below
 */
#if (DEM_USE_RTE == STD_ON)
#include "Rte_Type.h"
#endif

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define DEM_NVDATA_PATTERN_SIZE                         4

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*
 * If we don't have RTE, that defines PortInterface typedefs and defines, we will do it ourself here:
 * With RTE, these definitions are imported above via  #include "Rte_Type.h".
 * The Vector RTE (RTE_VENDOR_ID==0x1Eu) will suppress (optimize) some defines/typedefs, if a port is not configured.
 * In this case we define the types here to avoid compile errors.
 * For NON-Vector RTE, we cannot detect the suppression of the definition, so such RTE must always generate 
 * all required datatype definitions.
 */
#if defined(RTE_VENDOR_ID)
# if (RTE_VENDOR_ID == 0x1Eu)
#   define DEM_USE_RTE_FROM_VECTOR  STD_ON
# else
#   define DEM_USE_RTE_FROM_VECTOR  STD_OFF
# endif
#else
#  define DEM_USE_RTE_FROM_VECTOR  STD_OFF
#endif

/* StatusMaskType is used in DCM-API: SetDTCFilter, GetStatusOfDTC, GetDTCStatusAvailabilityMask and GetNextFilteredDTC
 *  and SW-C/FIM API TriggerOnDTCStatus. It contains status bits (typically) masked with the status availability mask.
 * This is one of the external status types, /see Dem_EventStatusExtendedType                                            */
#if (DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_DTCStatusMaskType)))
typedef uint8 Dem_DTCStatusMaskType;                            /* DTCStatusMask as defined in ISO14229-1 */
#endif

#if (DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_DTCType)))
typedef uint32 Dem_DTCType;
#endif

#if (DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_DTCKindType)))
typedef uint8 Dem_DTCKindType;
#define DEM_DTC_KIND_ALL_DTCS                             0x01  /* Select all DTCs */
#define DEM_DTC_KIND_EMISSION_REL_DTCS                    0x02  /* Select OBD-relevant DTCs */
#endif

/* DTC number type (Dem_EventIdType) is dependent on pre-configured, maximum possible DTC count (+1). */
#if (DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_EventIdType)))
# if (DEM_MAX_NUMBER_OF_EVENTS <= 255)
typedef uint8  Dem_EventIdType;
# else
typedef uint16 Dem_EventIdType;
# endif
#endif

/* EventStatusExtendedType is used in SWC-API: ResetEventStatus, GetEventStatus, GetEventFailed and GetEventTested
 *  and SW-C/FIM API TriggerOnEventStatus. It contains the full set of status bits (unmasked).
 * This is one of the external status types, /see Dem_DTCStatusMaskType
 */
#if (DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_EventStatusExtendedType)))
typedef uint8 Dem_EventStatusExtendedType;                /* DEM definition, currently(!) identical to Status bits of ISO 14229-1 */
#endif

#if (DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_FaultDetectionCounterType)))
typedef sint8 Dem_FaultDetectionCounterType;
#endif

/* typedef uint8 Dem_DTCTranslationFormatType;                     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */
/* #define DEM_DTC_TRANSLATION_ISO15031_6                 0x01     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */
/* #define DEM_DTC_TRANSLATION_ISO14229_1                 0x02     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */
/* #define DEM_DTC_TRANSLATION_CUSTOMER                   0x03     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */
/* #define DEM_DTC_TRANSLATION_INTERNAL                   0x04     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */

#if (DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_EventStatusType)))
typedef uint8 Dem_EventStatusType;
#define DEM_EVENT_STATUS_PASSED                           0x00  /* Event debouncing by Monitor Function - result is testPassed */
#define DEM_EVENT_STATUS_FAILED                           0x01  /* Event debouncing by Monitor Function - result is testFailed */
#define DEM_EVENT_STATUS_PREPASSED                        0x02  /* Event debouncing by DEM module - Monitor Function reports testPassed */
#define DEM_EVENT_STATUS_PREFAILED                        0x03  /* Event debouncing by DEM module - Monitor Function reports testFailed */
#endif

#if (DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_IndicatorStatusType)))
typedef uint8 Dem_IndicatorStatusType;
#define DEM_INDICATOR_OFF                                 0x00  /* Indicator off */
#define DEM_INDICATOR_CONTINUOUS                          0x01  /* Continuous on */
#define DEM_INDICATOR_BLINKING                            0x02  /* blinking mode */
#define DEM_INDICATOR_BLINK_CONT                          0x03  /* Continuous and blinking mode */
#endif

#if (DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_InitMonitorKindType)))
typedef uint8 Dem_InitMonitorKindType;
#define DEM_INIT_MONITOR_CLEAR                            0x01  /* Monitor Function of the EventId is cleared and all internal values and states are reset. */
#define DEM_INIT_MONITOR_RESTART                          0x02  /* Monitor Function of the EventId is requested to restart. */
#endif

#if (DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_OperationCycleIdType)))
typedef uint8 Dem_OperationCycleIdType;
#endif

#if (DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_OperationCycleStateType)))
typedef uint8 Dem_OperationCycleStateType;
#define DEM_CYCLE_STATE_START                             0x01  /* Start of operation cycle */
#define DEM_CYCLE_STATE_END                               0x02  /* End of operation cycle */
#endif

/*
 * The maximum buffer sizes for Snapshot-DID records resp. Ext.Data records are set by configuration.
 * Dem_MaxDataValueType          is the largest defined DID record
 * Dem_MaxExtendedDataRecordType is the largest defined ExtendedData record
 * For the API Argument definition we may use the unspecified size of the arrays instead:
 */
#if (DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_MaxDataValueType)))
typedef uint8 Dem_MaxDataValueType[];                                                             /* PRQA S 3650 *//* The size of the array is undetermined - according AUTOSAR it is always accessed via pointer and the user magically knows its size. */
#endif
#if (DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_MaxExtendedDataRecordType)))
typedef uint8 Dem_MaxExtendedDataRecordType[];                                                    /* PRQA S 3650 *//* The size of the array is undetermined - according AUTOSAR it is always accessed via pointer and the user magically knows its size. */
#endif

typedef uint8 Dem_DTCOriginType;
#define DEM_DTC_ORIGIN_PRIMARY_MEMORY                     0x01  /* Event information located in the primary memory. */
#define DEM_DTC_ORIGIN_MIRROR_MEMORY                      0x02  /* Event information located in the mirror memory. */
#define DEM_DTC_ORIGIN_PERMANENT                          0x03  /* not supported yet */
#define DEM_DTC_ORIGIN_SECONDARY_MEMORY                   0x04  /* Event information located in the secondary memory. */

/*
 * These Dem_OperationCycle/AgingCycle IDs are predefined. 
 * Further defined cycles are simply mapped to these cycles.
 */
#define DEM_IGNITION                                      0
#define DEM_OBD_DCY                                       1
#define DEM_WARMUP                                        2
#define DEM_POWER                                         3

typedef uint8 Dem_ViewIdType;

/* internal DTC status info stored in NVRAM */
/* with R3.0 this definition is now identical to Dem_EventStatusExtendedType */
typedef uint8 Dem_DtcStatusByteType;
/*
(1u << 0) = 0x01 testFailed
(1u << 1) = 0x02 testFailedThisOperationCycle
(1u << 2) = 0x04 pendingDTC
(1u << 3) = 0x08 confirmedDTC
(1u << 4) = 0x10 testNotCompletedSinceLastClear
(1u << 5) = 0x20 testFailedSinceLastClear
(1u << 6) = 0x40 testNotCompletedThisOperationCycle
(1u << 7) = 0x80 warningIndicatorRequested
*/

#define DEM_EVENTSTATUSEXT_CLEARED_DTC                    0x50  /* ISO 14229-1 status of a cleared DTC */

/* internal DTC status info in RAM (never saved to NVRAM) */
typedef uint8 Dem_DtcInternalStatusType;
/*
 (1u << 0) = 0x01 filteredDTC
 (1u << 1) = 0x02 prestoredEvent
 (1u << 2) = 0x04 storedDTC, only if (DEM_CONFIRMEDDTC_MEANS_STOREDDTC == STD_OFF)
*/

#define DEM_GET_FFDATA_ID_ALL                             0xffffu           /* API Dem_GetFreezeFrameDataByDTC(): request ALL DIDs */

typedef uint32 Dem_DTCGroupType;
#define DEM_DTC_GROUP_EMISSION_REL_DTCS                   0x000000uL        /* ISO 14229-1 Annex D.1: groupOfDTC parameter, Emission-related systems */
/* other DEM_DTC_GROUP_xxx_DTCS are defined in Dem_Cfg.h (if necessary) */
#define DEM_DTC_GROUP_ALL_DTCS                            0xffffffuL        /* ISO 14229-1 Annex D.1: groupOfDTC parameter, All Groups (all DTCs) */

typedef uint8 Dem_DTCGroupKindType;         /* Bit coded DTCGroup */
#define DEM_DTC_GROUPKIND_EMISSION_REL                    (uint8)(1u<<0)
#define DEM_DTC_GROUPKIND_POWERTRAIN                      (uint8)(1u<<1)
#define DEM_DTC_GROUPKIND_CHASSIS                         (uint8)(1u<<2)
#define DEM_DTC_GROUPKIND_BODY                            (uint8)(1u<<3)
#define DEM_DTC_GROUPKIND_NETWORK_COM                     (uint8)(1u<<4)
#define DEM_DTC_GROUPKIND_ALL_DTCS                        (uint8)(0xffu)

typedef struct Dem_DTCGroupMappingTypeTag
{
  Dem_DTCGroupKindType  GroupKind;
  Dem_DTCType           DTCnumber;
} Dem_DTCGroupMappingType;

typedef uint8 Dem_DTCRequestType;
#define DEM_FIRST_FAILED_DTC                              0x01  /* first failed DTC requested */
#define DEM_MOST_RECENT_FAILED_DTC                        0x02  /* most recent failed DTC requested */
#define DEM_FIRST_DET_CONFIRMED_DTC                       0x03  /* first detected confirmed DTC requested */
#define DEM_MOST_REC_DET_CONFIRMED_DTC                    0x04  /* most recently detected confirmed DTC requested */

typedef uint8 Dem_EventPriorityType;
typedef uint8 Dem_DataByteType;
typedef uint8 Dem_IndicatorIdType;

typedef uint16 Dem_NvMBlockIdType;

typedef uint8 Dem_FilterWithSeverityType;
#define DEM_FILTER_WITH_SEVERITY_YES                      0x00  /* Severity information used */
#define DEM_FILTER_WITH_SEVERITY_NO                       0x01  /* Severity information not used */

typedef uint8 Dem_DTCSeverityType;
#define DEM_SEVERITY_NO_SEVERITY                          0x00  /* No severity information available */
#define DEM_SEVERITY_MAINTENANCE_ONLY                     0x20  /* maintenance required */
#define DEM_SEVERITY_CHECK_AT_NEXT_HALT                   0x40  /* check at next halt */
#define DEM_SEVERITY_CHECK_IMMEDIATELY                    0x80  /* Check immediately */

/* Return values */
typedef uint8 Dem_ReturnSetDTCFilterType;
#define DEM_FILTER_ACCEPTED                               0x00  /* Filter was accepted */
#define DEM_WRONG_FILTER                                  0x01  /* Wrong filter selected */

typedef uint8 Dem_FilterForFaultDetectionCounterType;
#define DEM_FILTER_FOR_FDC_YES                            0x00  /* Fault Detection Counter information used */
#define DEM_FILTER_FOR_FDC_NO                             0x01  /* Fault Detection Counter information not used */
/* #define DEM_FILTER_FOR_FAULTDETECTIONCOUNTER_YES       0x00     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */
/* #define DEM_FILTER_FOR_FAULTDETECTIONCOUNTER_NO        0x01     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */

typedef uint8 Dem_ReturnSetViewFilterType;
#define DEM_VIEW_ID_ACCEPTED                              0x00  /* View ID was accepted */
#define DEM_WRONG_ID                                      0x01  /* Wrong View ID selected */

typedef uint8 Dem_ReturnGetStatusOfDTCType;
#define DEM_STATUS_OK                                     0x00  /* Status of DTC is OK */
#define DEM_STATUS_WRONG_DTC                              0x01  /* Wrong DTC */
#define DEM_STATUS_WRONG_DTCORIGIN                        0x02  /* Wrong DTC origin */
#define DEM_STATUS_WRONG_DTCKIND                          0x03  /* DTC kind wrong */
#define DEM_STATUS_FAILED                                 0x04  /* DTC failed */

typedef uint8 Dem_ReturnGetNextFilteredDTCType;
#define DEM_FILTERED_OK                                   0x00  /* Returned next filtered DTC */
#define DEM_FILTERED_NO_MATCHING_DTC                      0x01  /* No DTC matched */
#define DEM_FILTERED_WRONG_DTCKIND                        0x02  /* DTC kind wrong */

typedef uint8 Dem_ReturnGetNumberOfFilteredDTCType;
#define DEM_NUMBER_OK                                     0x00  /* get of number of DTC was successful */
#define DEM_NUMBER_FAILED                                 0x01  /* get of number of DTC failed */
#define DEM_NUMBER_PENDING                                0x02  /* get of number of DTC is pending */

typedef uint8 Dem_ReturnClearDTCType;
#define DEM_CLEAR_OK                                      0x00  /* DTC successfully cleared */
#define DEM_CLEAR_WRONG_DTC                               0x01  /* Wrong DTC */
#define DEM_CLEAR_WRONG_DTCORIGIN                         0x02  /* Wrong DTC origin */
#define DEM_CLEAR_WRONG_DTCKIND                           0x03  /* DTC kind wrong */
#define DEM_CLEAR_FAILED                                  0x04  /* DTC not cleared */
#define DEM_DTC_PENDING                                   0x05  /* Clearing of DTC is pending */

typedef uint8 Dem_ReturnControlDTCStorageType;
#define DEM_CONTROL_DTC_STORAGE_OK                        0x00  /* DTC storage control successful */
#define DEM_CONTROL_DTC_STORAGE_N_OK                      0x01  /* DTC storage control not successful */
#define DEM_CONTROL_DTC_WRONG_DTCGROUP                    0x02  /* DTC storage control not successful because group of DTC was wrong */

typedef Dem_ReturnControlDTCStorageType Dem_ReturnControlDTCSettingType;                  /* AUTOSAR 4 API for Service 85 */
# define DEM_CONTROL_DTC_SETTING_OK                       DEM_CONTROL_DTC_STORAGE_OK      /* DTC setting control successful */
# define DEM_CONTROL_DTC_SETTING_N_OK                     DEM_CONTROL_DTC_STORAGE_N_OK    /* DTC setting control not successful */

typedef uint8 Dem_ReturnControlEventUpdateType;
#define DEM_CONTROL_EVENT_UPDATE_OK                       0x00  /* Event storage control successful */
#define DEM_CONTROL_EVENT_UPDATE_N_OK                     0x01  /* Event storage control not successful */
#define DEM_CONTROL_EVENT_WRONG_DTCGROUP                  0x02  /* Event storage control not successful because group of DTC was wrong */

typedef uint8 Dem_ReturnGetDTCOfFreezeFrameRecordType;
#define DEM_GET_DTCOFFF_OK                                0x00  /* DTC successfully returned */
#define DEM_GET_DTCOFFF_WRONG_RECORD                      0x01  /* Wrong record */
#define DEM_GET_DTCOFFF_NO_DTC_FOR_RECORD                 0x02  /* No DTC for record available */
#define DEM_GET_DTCOFFF_WRONG_DTCKIND                     0x03  /* DTC kind wrong */

typedef uint8 Dem_ReturnGetFreezeFrameDataIdentifierByDTCType;
#define DEM_GET_ID_OK                                     0x00  /* FreezeFrame data identifier successfully returned */
#define DEM_GET_ID_WRONG_DTC                              0x01  /* Wrong DTC */
#define DEM_GET_ID_WRONG_DTCORIGIN                        0x02  /* Wrong DTC origin */
#define DEM_GET_ID_WRONG_DTCKIND                          0x03  /* DTC kind wrong */
#define DEM_GET_ID_WRONG_FF_TYPE                          0x04  /* FreezeFrame type wrong */

typedef uint8 Dem_ReturnGetExtendedDataRecordByDTCType;
#define DEM_RECORD_OK                                     0x00  /* Extended data record successfully returned */
#define DEM_RECORD_WRONG_DTC                              0x01  /* Wrong DTC */
#define DEM_RECORD_WRONG_DTCORIGIN                        0x02  /* Origin wrong */
#define DEM_RECORD_WRONG_DTCKIND                          0x03  /* DTC kind wrong */
#define DEM_RECORD_WRONG_NUMBER                           0x04  /* Record number wrong */
#define DEM_RECORD_WRONG_BUFFERSIZE                       0x05  /* Provided buffer to small */

/* typedef uint8 Dem_ReturnGetDTCOfEventType;                      not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */
/* #define DEM_GET_DTCOFEVENT_OK                          0x00     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */
/* #define DEM_GET_DTCOFEVENT_WRONG_EVENTID               0x01     wrong definition by ch 11.3 in  DEM Spec V2.2.1 (R3.0 Rev 0002), see below */
/* #define DEM_GET_DTCOFEVENT_WRONG_TRANSLATION           0x02     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */
#define DEM_GET_DTCOFEVENT_WRONG_EVENTID                  0x05  /* Wrong EventId (see Dem198) */
#define DEM_GET_DTCOFEVENT_WRONG_DTCKIND                  0x04  /* DTC kind wrong (see Dem198) */

typedef uint8 Dem_ReturnGetDTCByOccurrenceTimeType;
#define DEM_OCCURR_OK                                     0x00  /* Status of DTC was OK */
#define DEM_OCCURR_WRONG_DTCKIND                          0x01  /* DTC kind wrong */
#define DEM_OCCURR_FAILED                                 0x02  /* DTC failed */

typedef uint8 Dem_ReturnGetFreezeFrameDataByDTCType;
#define DEM_GET_FFDATABYDTC_OK                            0x00  /* Size successfully returned */
#define DEM_GET_FFDATABYDTC_WRONG_DTC                     0x01  /* Wrong DTC */
#define DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN               0x02  /* Wrong DTC origin */
#define DEM_GET_FFDATABYDTC_WRONG_DTCKIND                 0x03  /* DTC kind wrong */
#define DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER            0x04  /* Wrong Record Number */
#define DEM_GET_FFDATABYDTC_WRONG_DATAID                  0x05  /* Wrong DataID */
#define DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE              0x06  /* provided buffer size to small */

typedef uint8 Dem_ReturnGetSizeOfExtendedDataRecordByDTCType;
#define DEM_GET_SIZEOFEDRBYDTC_OK                         0x00  /* Size successfully returned */
#define DEM_GET_SIZEOFEDRBYDTC_W_DTC                      0x01  /* Wrong DTC */
#define DEM_GET_SIZEOFEDRBYDTC_W_DTCOR                    0x02  /* Wrong DTC origin */
#define DEM_GET_SIZEOFEDRBYDTC_W_DTCKI                    0x03  /* DTC kind wrong */
#define DEM_GET_SIZEOFEDRBYDTC_W_RNUM                     0x04  /* Wrong Record Number */
/* #define DEM_GET_SIZEOFEDRBYDTCTYPE_OK                  0x00     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */
/* #define DEM_GET_SIZEOFEDRBYDTCTYPE_WRONG_DTC           0x01     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */
/* #define DEM_GET_SIZEOFEDRBYDTCTYPE_WRONG_DTCORIGIN     0x02     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */
/* #define DEM_GET_SIZEOFEDRBYDTCTYPE_WRONG_DTCKIND       0x03     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */
/* #define DEM_GET_SIZEOFEDRBYDTCTYPE_WRONG_RECORDNUMBER  0x04     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */
  
typedef uint8 Dem_ReturnGetSizeOfFreezeFrameType;
#define DEM_GET_SIZEOFFF_OK                               0x00  /* Size successfully returned. */
#define DEM_GET_SIZEOFFF_WRONG_DTC                        0x01  /* Wrong DTC */
#define DEM_GET_SIZEOFFF_WRONG_DTCOR                      0x02  /* Wrong DTC origin */
#define DEM_GET_SIZEOFFF_WRONG_DTCKIND                    0x03  /* DTC kind wrong */
#define DEM_GET_SIZEOFFF_WRONG_RNUM                       0x04  /* Wrong Record Number */
/* #define DEM_GET_SIZEOFFREEZEFRAMETYPE_OK               0x00     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */
/* #define DEM_GET_SIZEOFFREEZEFRAMETYPE_WRONG_DTC        0x01     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */
/* #define DEM_GET_SIZEOFFREEZEFRAMETYPE_WRONG_DTCORIGIN  0x02     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */
/* #define DEM_GET_SIZEOFFREEZEFRAMETYPE_WRONG_DTCKIND    0x03     not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */
/* #define DEM_GET_SIZEOFFREEZEFRAMETYPE_WRONG_RECORDNUMBER  0x04  not used any more in  DEM Spec V2.2.1 (R3.0 Rev 0002) */

typedef uint8 Dem_ReturnGetViewIDOfDTCType;
#define DEM_VIEWID_OK                                     0x00  /* Status of ViewId is OK */
#define DEM_VIEWID_WRONG_DTC                              0x01  /* Wrong DTC */
#define DEM_VIEWID_WRONG_DTCKIND                          0x02  /* DTC kind wrong */

typedef uint8 Dem_ReturnGetSeverityOfDTCType;
#define DEM_GET_SEVERITYOFDTC_OK                          0x00  /* Severity successfully returned.  */
#define DEM_GET_SEVERITYOFDTC_WRONG_DTC                   0x01  /* Wrong DTC */
#define DEM_GET_SEVERITYOFDTC_WRONG_DTCORIGIN             0x02  /* Wrong DTC origin  (unused) */ 
#define DEM_GET_SEVERITYOFDTC_NOSEVERITY                  0x03  /* Severity information is not available */

typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_InitMonitorFPtrType) (Dem_InitMonitorKindType InitMonitorKind); /* PRQA S 0850 *//* MD_MSR_19.8 */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_ClearAllowedFPtrType)(P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) Allowed); /* PRQA S 0850 *//* MD_MSR_19.8 */

typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_GetDataValueByDataIdentifierType) (P2VAR(Dem_MaxDataValueType, AUTOMATIC, DEM_APPL_DATA) /* DataValueByDataIDBuffer */);   /* buffer argument's type is (uint8 *[]) see Bugzillas #22258 and #22401 */ /* PRQA S 0850, 3651 *//* MD_MSR_19.8, MD_DEM_3651 */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_GetExtDataRecordFPtrType) (P2VAR(Dem_MaxExtendedDataRecordType, AUTOMATIC, DEM_APPL_DATA) /* ExtendedDataRecordBuffer */); /* buffer argument's type is (uint8 *[]) see Bugzillas #22258 and #22401 */ /* PRQA S 0850, 3651 *//* MD_MSR_19.8, MD_DEM_3651 */

typedef uint16 Dem_TriggerOnEventIndexType;
typedef uint16 Dem_TriggerOnDTCIndexType;

typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_TriggerFunctionType) (Dem_EventStatusExtendedType EventStatusOld, Dem_EventStatusExtendedType EventStatusNew);        /* PRQA S 0850 *//* MD_MSR_19.8 */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_TriggerDTCFunctionType) (Dem_DTCType DTC, Dem_DTCKindType DTCKind, Dem_DTCStatusMaskType DTCStatusOld, Dem_DTCStatusMaskType DTCStatusNew);        /* PRQA S 0850 *//* MD_MSR_19.8 */

typedef P2CONST(uint16, TYPEDEF, DEM_PBCFG) Dem_RecordDIDAddrType;                            /* PRQA S 0850 *//* MD_MSR_19.8 */

/* Action queue for storing API call triggers. Queue is drained in Dem_MainFunction() */
typedef struct
{
  union
  {                                                                                           /* PRQA S 0750 */ /* MD_MSR_18.4 */
    Dem_EventIdType           EventIdentifier;  /* uint8/uint16 */
    Dem_OperationCycleIdType  CycleId;          /* uint8 */
    struct
    {
      Dem_DTCGroupKindType  BitcodedDtcGroup;   /* uint8 */
      Dem_DTCKindType       DTCKind;            /* 2 bit */
      Dem_DTCOriginType     DTCOrigin;          /* 2 bit */
    } dtc;
  } arg;
  uint8 Action; 
} Dem_AQElementType;

/*
typedef struct Dem_NonVolatileDataTypeTag {...} Dem_NonVolatileDataType;
  is in file Dem_Lcfg.h, as the size of Dem_NonVolatileDataType is dependent on
  the (PostBuild) selectable number of events, ...
  Someone might think the size is constant, when the typedef is written here together
  with other constant types.
*/

#if (DEM_SUPPORT_MULTIPLE_CONFIG == STD_ON) || (DEM_SUPPORT_VARIANT_HANDLING == STD_ON) || (DEM_PREINIT_HAS_CONFIG_PARAM == STD_ON)
/* Support of configuration parameter with Dem_PreInit(), used with multiple configuration and variant handling */
typedef struct
{
  uint32 ConfigurationMask;   /* this parameter is a bitfield */
} Dem_ConfigType;
#endif /* DEM_SUPPORT_MULTIPLE_CONFIG || DEM_SUPPORT_VARIANT_HANDLING || DEM_PREINIT_HAS_CONFIG_PARAM */

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif /* DEM_TYPES_H */
