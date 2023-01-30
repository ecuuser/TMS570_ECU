/* -----------------------------------------------------------------------------
  Filename:    Dcm.h
  Description: Interface of DCM visible to any application.

 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2008-2013 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

#if !defined(__DCM_H__)
# define __DCM_H__

/* -----------------------------------------------------------------------------
    &&&~ History
 ----------------------------------------------------------------------------- */

/* 
------------------------------------------------------------------------------------------------------------------------
                                             A U T H O R   I D E N T I T Y                                              
------------------------------------------------------------------------------------------------------------------------
Initials   Name                  Company                                                                                
---------- --------------------- ---------------------------------------------------------------------------------------
Ktw        Katrin Thurow         Vector Informatik GmbH                                                                 
Sa         Mishel Shishmanyan    Vector Informatik GmbH                                                                 
------------------------------------------------------------------------------------------------------------------------
                                            R E V I S I O N   H I S T O R Y                                             
------------------------------------------------------------------------------------------------------------------------
Date       Version  Author Modification type Issue Id      Affects                        Description                    
---------- -------- ------ ----------------- ------------- ------------------------------ -------------------------------
2010-10-27  4.04.00
                    Sa     Modified          ESCAN00044821 Fiat(UDS)                      Optimize periodic connection owner check on single connection configurations
                    Sa     Added             ESCAN00046468 Fiat(UDS)                      Support OEM FIAT               
                    Sa     Fixed             ESCAN00045900 All                            Compiler warning: Useless assignment to variable
                    Sa     Fixed             ESCAN00044898 All                            Compile error for missing data type definitions Dcm_ReturnReadMemoryType and Dcm_ReturnWriteMemoryType
                    Sa     Modified          ESCAN00046464 All                            Changed DEM AR version check   
                    Sa     Modified          ESCAN00046467 All                            Optimized DSL transport object management
2010-11-30  4.05.00
                    Sa     Fixed             ESCAN00047626 Fiat(UDS)                      Compile error for missing DEM OBD API prototype
                    Sa     Added             ESCAN00046808 Fiat(UDS)                      DCM shall interact with BswM   
                    Sa     Fixed             ESCAN00044108 All                            DCM does not fully support split task concept with different task priorities for the timer and state tasks
                    Sa     Fixed             ESCAN00047989 All                            Functional request causes Physical Request to be discontinued
                    Sa     Fixed             ESCAN00048294 All                            Wrong NRC handling on requests's minimum length check
                    Sa     Modified          ESCAN00045441 All                            Improvement of MISRA compliance (AR3-962)
                    Sa     Modified          ESCAN00048097 All                            Pre-compile time code optimization if no hard reset functionality is needed
                    Sa     Modified          ESCAN00048237 All                            Improved memory mapping on external callbacks
                    Sa     Added             ESCAN00046237 All                            Adapt AUTOSAR version check    
2011-04-30  4.06.00
                    Sa     Fixed             ESCAN00050421 Fiat(UDS)                      Service 0x2A might not accept request from another tester in a multi client environment
                    Sa     Added             ESCAN00050351 Fiat(UDS)                      OBD2(WWHOBD) PIDs 0x90-0x94 (0xF490-0xF494) access calls redirected to DEM
                    Sa     Fixed             ESCAN00050420 All                            Service 0x2C can not append multiple address definitions in a single request
                    Sa     Fixed             ESCAN00049069 All                            Possibly incorrect library file, due to compiler optimizations over arrays with declarations of single element size
                    Sa     Modified          ESCAN00050348 All                            Improved reliability of SID 0x2F and 0x31 processors
                    Sa     Modified          ESCAN00049673 All                            Improve robustness by initializing all local variables
                    Sa     Modified          ESCAN00050349 All                            Minor run time and code optimizations
                    Sa     Modified          ESCAN00050434 All                            Make number of identities link-time capable
                    Sa     Added             ESCAN00050425 All                            Service 0x19 with SPRMIB=1 will first send RCR-RP response, then final positive response
                    Sa     Added             ESCAN00050426 All                            General services NRC handling update to match ISO 14229-1 2010
2011-05-05  4.07.00
                    Sa     Fixed             ESCAN00050877 Fiat(UDS)                      Compile error on MCS12 COSMIC if OBD2 support enabled
                    Sa     Fixed             ESCAN00050932 Fiat(UDS)                      Link time error for missing function Dcm_CopyRam2Ram in Dcm.c
                    Sa     Fixed             ESCAN00050940 All                            Dcm accepts a 'send key' request after a zero seed positive response on an already unlocked security level
2011-05-17  4.08.00
                    Sa     Fixed             ESCAN00052267 Fiat(UDS)                      OBD(UDS) requests from a UDS(OBD) client shall result in NRC 0x11
                    Sa     Fixed             ESCAN00052160 All                            Compiler warning: "condition is always false"
                    Sa     Fixed             ESCAN00052270 All                            Unspecified OBD service call-outs report wrong SID
                    Sa     Modified          ESCAN00050743 All                            AR3-1330: Remove E_PENDING for ASR3
                    Sa     Modified          ESCAN00051176 All                            Possibly incorrect library file, due to compiler optimizations over RAM arrays with declarations of single element size
                    Sa     Modified          ESCAN00052079 All                            Return NRC 0x72 instead of 0x22 for AR 4.0 Dcm_WriteMemory operation
                    Sa     Added             ESCAN00050195 All                            Support of state group definitions beyond session and security
                    Sa     Added             ESCAN00051269 All                            Provide means for suppressing included BSW file version checks
2011-08-19  4.08.01
                    Sa     Modified          ESCAN00051736 All                            Remove the AUTOSAR Release Version Check
2011-09-14  4.09.00
                    Sa     Fixed             ESCAN00054517 Fiat(UDS)                      Memory overwritten if SID 0x2A is not supported in a DCM library configuration
                    Sa     Added             ESCAN00053549 Fiat(UDS)                      AR3-1803 Generate DID callback automatically and return 10 byte delivery ID
                    Sa     Fixed             ESCAN00054517 All                            Dcm sends NRC 0x13 instead of NRC 0x12 for SIDs 0x10, 0x11 and 0x3E
                    Sa     Fixed             ESCAN00048470 All                            Change ESCAN00035661 "Comments of kind '*C++-comment*' replaced by '*/ /*'" text not to contain any C comments
                    Sa     Fixed             ESCAN00054863 All                            SID 0x28 sub-functions state filter evaluated before sub-function specific length
                    Sa     Modified          ESCAN00053504 All                            AR3-2069: Remove non-SchM code for critical section handling
2012-06-14  4.10.00
                    Ktw    Fixed             ESCAN00057142 Fiat(UDS)                      Service 0x11 rapid shutdown will report the correct power down time
                    Ktw    Fixed             ESCAN00057782 Fiat(UDS)                      DCM generates RTE SWC ports resp. callback function declarations for OBD2 DEM data that will never be called
                    Ktw    Fixed             ESCAN00057992 Fiat(UDS)                      Service ports for OBD DIDs  0xF41D and 0xF41E are directed to the DEM and not to RTE
                    Ktw    Fixed             ESCAN00058541 Fiat(UDS)                      Service port for OBD DIDs 0xF431 is directed to the RTE and not to DEM
                    Ktw    Fixed             ESCAN00057141 All                            Compiler error: Undefined constant DCM_11_PWRDWN_TIME_ENABLED 
                    Ktw    Fixed             ESCAN00055917 All                            Compiler warning: character constant too big to fit in a byte
                    Ktw    Fixed             ESCAN00055990 All                            DCM does not support more than 16 session/security access states
                    Ktw    Modified          ESCAN00059142 All                            AR3-2416: Treat OBD DIDs and RIDs as normal application identifier if no OBD is licensed
                    Ktw    Added             ESCAN00057821 All                            AR3-2405: Service 0x22 with limited paged buffer support
2012-12-03  4.10.01
                    Sa     Added             ESCAN00061996 Fiat(UDS)                      AR3-2463: The services ReadDataByAddress and WriteDataByAddress shall be supported
2013-03-11  4.11.00
                    Sa     Modified          ESCAN00064963 Fiat(UDS)                      Remove limitation of 16 PDIDs simultaneously readable via SID 0x2A
                    Sa     Fixed             ESCAN00065849 All                            The ECU rejects a valid diagnostic request of service 0x2C (DynamicallDefineDataIdentifier) with NRC 0x31
                    Sa     Fixed             ESCAN00064949 All                            Dcm sends incomplete response for OBD SID 0x06
                    Sa     Fixed             ESCAN00064564 All                            Compiler error: Dem_En-/DisableDTCRecordUpdate declared implicitly
                    Sa     Fixed             ESCAN00054077 All                            DCM supports only TID and not OBDMID-TID specific application calls and UASIDs
                    Sa     Modified          ESCAN00065779 All                            New bit operation unifications 
                    Sa     Modified          ESCAN00067394 All                            The paged buffer update function call is now synchronized with any failed response transmission confirmation event
                    Sa     Added             ESCAN00065297 All                            AR3-2477: Implement instrumentation for time measurement
2013-09-12  4.12.00
                    Sa     Added             ESCAN00068549 Fiat(UDS)                      AR3-2433: Implement ROE according to Fiat norms
                    Sa     Fixed             ESCAN00067972 All                            Dcm does not call the Dcm_RequestIndicationSys application callback
                    Sa     Fixed             ESCAN00067737 All                            Compiler warning: dead assignment to "resultDtcSetting" eliminated
                    Sa     Fixed             ESCAN00071076 All                            Dcm executes the post-handler of the last request if OemIndication call rejects the service execution
                    Sa     Modified          ESCAN00071075 All                            Improved internal DCM task event management stability
                    Sa     Modified          ESCAN00071074 All                            Reduced disabled interrupt run time
                    Sa     Added             ESCAN00066866 All                            Provide means for generic diagnostic service confirmation notification
------------------------------------------------------------------------------------------------------------------------
 */


/* -----------------------------------------------------------------------------
    &&&~ Includes
 ----------------------------------------------------------------------------- */

# include "Dcm_Cbk.h"
# include "Dcm_Lcfg.h"



/* -----------------------------------------------------------------------------
    &&&~ Preprocessor constants (defines)
 ----------------------------------------------------------------------------- */

# define DCM_SW_MAJOR_VERSION                                        0x04u
# define DCM_SW_MINOR_VERSION                                        0x12u
# define DCM_SW_PATCH_VERSION                                        0x00u
# define DCM_AR_MAJOR_VERSION                                        0x03u
# define DCM_AR_MINOR_VERSION                                        0x00u
# define DCM_AR_PATCH_VERSION                                        0x00u
/* ##V_CFG_MANAGEMENT ##CQProject : Diag_AsrDcm CQComponent : Implementation */
# define DIAG_ASRDCM_VERSION                                         0x0412u
# define DIAG_ASRDCM_RELEASE_VERSION                                 0x00u
/* Module identifier */
# define DCM_MODULE_ID                                               0x35u
/* Vendor ID */
# define DCM_VENDOR_ID                                               30
/* This magic number provides internal DCM generation process consistency check.All DCM files must have the same one. */
# define DCM_XDECL_INTERFACE_MAGIC_NUMBER                            32426
/*-----------------------------------------------*/
/*                Global DCM API                 */
/*-----------------------------------------------*/
/* ApiIds for DET */
# define DcmServiceId_Init                                           (uint8)0x01

# define DcmServiceId_ProvideRxBuffer                                (uint8)0x02
# define DcmServiceId_RxIndication                                   (uint8)0x03
# define DcmServiceId_ProvideTxBuffer                                (uint8)0x04
# define DcmServiceId_TxConfirmation                                 (uint8)0x05

# define DcmServiceId_GetSesCtrlType                                 (uint8)0x06
# define DcmServiceId_SetSesCtrlType                                 (uint8)0x07

# define DcmServiceId_GetSesChgPermission                            (uint8)0x08
# define DcmServiceId_SesCtrlChgIndication                           (uint8)0x09

# define DcmServiceId_GetSesTimingValues                             (uint8)0x0A
# define DcmServiceId_PrepareSesTimingValue                          (uint8)0x0B
# define DcmServiceId_SetSesTimingValues                             (uint8)0x0C

# define DcmServiceId_GetSecurityLevel                               (uint8)0x0D
# define DcmServiceId_SetSecurityLevel                               (uint8)0x0E
# define DcmServiceId_GetActiveProtocol                              (uint8)0x0F

# define DcmServiceId_ResponseOnEvent                                (uint8)0x10
# define DcmServiceId_ResponseOnOneDataByPeriodicId                  (uint8)0x11

# define DcmServiceId_DiagnosticService                              (uint8)0x12
# define DcmServiceId_SetNegResponse                                 (uint8)0x13
# define DcmServiceId_ProcessingDone                                 (uint8)0x14

# define DcmServiceId_DspConfirmation                                (uint8)0x15
# define DcmServiceId_RteConfirmation                                (uint8)0x16
# define DcmServiceId_RteIndication                                  (uint8)0x17

# define DcmServiceId_StartPagedProcessing                           (uint8)0x18
# define DcmServiceId_UpdatePage                                     (uint8)0x19
# define DcmServiceId_ProcessPage                                    (uint8)0x1A
# define DcmServiceId_CancelPagedBufferProcessing                    (uint8)0x1B

# define DcmServiceId_GetActiveServiceTable                          (uint8)0x1C

# define DcmServiceId_GetSeed                                        (uint8)0x1D
# define DcmServiceId_CompareKey                                     (uint8)0x1E

# define DcmServiceId_ComMNoComModeEntered                           (uint8)0x21
# define DcmServiceId_ComMSilentComModeEntered                       (uint8)0x22
# define DcmServiceId_ComMFullComModeEntered                         (uint8)0x23
# define DcmServiceId_GetVersionInfo                                 (uint8)0x24
# define DcmServiceId_MainFunction                                   (uint8)0x25

# define DcmServiceId_StartProtocol                                  (uint8)0x1F
# define DcmServiceId_StopProtocol                                   (uint8)0x20

/* DCM implementation custom codes */
# define DcmServiceId_DsdDispatcher                                  (uint8)0x50
# define DcmServiceId_SendResponsePending                            (uint8)0x51
# define DcmServiceId_ProcessActivity                                (uint8)0x52
# define DcmServiceId_TriggerTransmit                                (uint8)0x53
# define DcmServiceId_SendResponse                                   (uint8)0x54
# define DcmServiceId_SendSpontaneousResponse                        (uint8)0x55
# define DcmServiceId_ReleaseResource                                (uint8)0x56
# define DcmServiceId_AllocateResource                               (uint8)0x57
# define DcmServiceId_LockDcm                                        (uint8)0x58
# define DcmServiceId_UnLockDcm                                      (uint8)0x59
# define DcmServiceId_GetProgConditions                              (uint8)0x5A
# define DcmServiceId_SetProgConditions                              (uint8)0x5B
# define DcmServiceId_InternalRoutine                                (uint8)0x5C
# define DcmServiceId_GetActiveRxPduId                               (uint8)0x5D



/* Error classification */
# define DCM_E_INTERFACE_VALUE_OUT_OF_RANGE                          (Dcm_DevErrorType)0x02
# define DCM_E_UNINIT                                                (Dcm_DevErrorType)0x05
# define DCM_E_PARAM                                                 (Dcm_DevErrorType)0x06

/* Custom types*/
# define DCM_E_ILLEGAL_STATE_REACHED                                 (Dcm_DevErrorType)0x80
# define DCM_E_INTERFACE_ILLEGALLY_USED                              (Dcm_DevErrorType)0x81
# define DCM_E_LIB_CONFIG_MISMATCH                                   (Dcm_DevErrorType)0x82




/* -----------------------------------------------------------------------------
    &&&~ Function prototypes
 ----------------------------------------------------------------------------- */

# define DCM_START_SEC_CODE
# include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if (DCM_EXT_CRITICAL_SEC_MGR_ENABLED == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_EnterCriticalSection(void);
extern FUNC(void, DCM_CODE) Dcm_LeaveCriticalSection(void);
# endif

# if (DCM_COPY_RAM2RAM_ENABLED == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_CopyRam2Ram(Dcm_ApplDataPtrType tgtAddr, Dcm_ApplDataPtrType      srcAddr, uint16_least len);
# endif

# if (DCM_COPY_ROM2RAM_ENABLED == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_CopyRom2Ram(Dcm_ApplDataPtrType tgtAddr, Dcm_ApplConstDataPtrType srcAddr, uint16_least len);
# endif

# if (DCM_VERSION_INFO_API == STD_ON)
/* Version info report */
extern FUNC(void, DCM_CODE) Dcm_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, DCM_APPL_DATA) versioninfo);
# endif

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSesCtrlType( P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) SessionCtrlType);
# if (DCM_EXT_ROE_TRIGGER_ENABLED == STD_ON)
extern FUNC(Dcm_StatusType, DCM_CODE) Dcm_ResponseOnOneEvent( Dcm_MsgType MsgPtr, Dcm_MsgLenType MsgLen, PduIdType DcmRxPduId);
# endif

# if (DCM_SERVICE_27_ENABLED == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSecurityLevel( P2VAR(Dcm_SecLevelType, AUTOMATIC, DCM_APPL_DATA) SecLevel);
# endif /* (DCM_SERVICE_27_ENABLED == STD_ON) */
# if (DCM_API_GET_RXPDUID_ENABLED == STD_ON)
extern FUNC(PduIdType, DCM_CODE) Dcm_GetActiveRxPduId(void);
# endif

/* Administrative functions */
# if (DCM_CFG_MULTI_ID_INC_ENABLED == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_InitDiagnosticVariant(Dcm_CfgVariantMaskType VariantMask);
# endif
# if (DCM_MULTI_ID_ENABLED == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_Init(P2CONST(Dcm_ConfigType, AUTOMATIC, DCM_CONST) DcmConfigPtr);
# else
extern FUNC(void, DCM_CODE) Dcm_Init(void);
# endif
extern FUNC(void, DCM_CODE) Dcm_MainFunction(void);
extern FUNC(void, DCM_CODE) Dcm_TimerTask(void);
extern FUNC(void, DCM_CODE) Dcm_StateTask(void);

# define DCM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_19.1 */



/* -----------------------------------------------------------------------------
    &&&~ External function prototypes
 ----------------------------------------------------------------------------- */

# define DCM_APPL_START_SEC_CODE
# include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if (DCM_DSD_OEM_INDICATION_ENABLED == STD_ON)
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_RequestIndicationOem(uint8                           Sid,
                                                                    Dcm_MsgType                     ReqData,
                                                                    uint16                          ReqDataLen,
                                                                    uint8                           ReqType,
                                                                    uint16                          TesterAddress,
                                                                    Dcm_NegativeResponseCodePtrType ErrorPtr);
extern FUNC(void, DCM_APPL_CODE) Dcm_RequestConfirmationOem(uint8                      Sid,
                                                            uint8                      ReqType,
                                                            uint16                     TesterAddress,
                                                            Dcm_ConfirmationStatusType status);
# endif
# if (DCM_DSD_SYS_INDICATION_ENABLED == STD_ON)
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_RequestIndicationSys(uint8                           Sid,
                                                                    Dcm_MsgType                     ReqData,
                                                                    uint16                          ReqDataLen,
                                                                    uint8                           ReqType,
                                                                    uint16                          TesterAddress,
                                                                    Dcm_NegativeResponseCodePtrType ErrorPtr);
extern FUNC(void, DCM_APPL_CODE) Dcm_RequestConfirmationSys(uint8                      Sid,
                                                            uint8                      ReqType,
                                                            uint16                     TesterAddress,
                                                            Dcm_ConfirmationStatusType status);
# endif

# if ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON))
#  if (DCM_MEMMGR_PARAM_CHECK_ENABLED == STD_OFF)
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_CheckMemory(Dcm_MemMgrOpType MemAccOp,
                                                           uint8            MemoryIdentifier,
                                                           uint32           MemoryAddress,
                                                           uint32           MemorySize,
                                                           Dcm_NegativeResponseCodePtrType ErrorPtr);
#  endif
# endif /* ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON)) */
# if (DCM_SERVICE_22_ENABLED == STD_ON)
#  if (DCM_22_USR_PB_USAGE_ENABLED == STD_ON)
extern FUNC(void, DCM_APPL_CODE) Dcm_PBDidUpdatePage(uint16 did, Dcm_MsgType dataPtr, Dcm_MsgLenPtrType pageSize);
extern FUNC(void, DCM_APPL_CODE) Dcm_PBDidPostHandler(uint16 did, Dcm_ConfirmationStatusType status);
#  endif
# endif /* (DCM_SERVICE_22_ENABLED == STD_ON) */
# if ((DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON) && ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF)))
extern FUNC(Dcm_ReturnReadMemoryType, DCM_APPL_CODE) Dcm_ReadMemory(uint8 MemoryIdentifier, uint32 MemoryAddress,uint32 MemorySize, Dcm_MsgType MemoryData);
# endif /* ((DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON) && ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF))) */
# if (DCM_SERVICE_28_ENABLED == STD_ON)
#  if (DCM_28_ENHANCED_ADDR_INFO_ENABLED == STD_ON)
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ComControlEnhParamsCheck(uint16  nodeIdNumber
                                                                       ,uint8   subNetId
                                                                       ,uint8   msgType
                                                                       ,boolean rxState
                                                                       ,boolean txState);
extern FUNC(void, DCM_APPL_CODE) Dcm_ComControlEnhParamsExecute(uint16  nodeIdNumber
                                                               ,uint8   subNetId
                                                               ,uint8   msgType
                                                               ,boolean rxState
                                                               ,boolean txState);

#  endif
# endif /* (DCM_SERVICE_28_ENABLED == STD_ON) */
# if ((DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON) && ((DCM_SERVICE_3D_ENABLED == STD_ON) || (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF)))
extern FUNC(Dcm_ReturnWriteMemoryType, DCM_APPL_CODE) Dcm_WriteMemory(uint8 MemoryIdentifier, uint32 MemoryAddress, uint32 MemorySize, Dcm_MsgType MemoryData);
# endif /* ((DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON) && ((DCM_SERVICE_3D_ENABLED == STD_ON) || (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF))) */
# if (DCM_UNSPEC_SERVICE_SUPPORT_ENABLED == STD_ON)
/* Application callouts */
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_CheckUnspecifiedService(uint8 sid, P2VAR(boolean,AUTOMATIC,DCM_VAR_NOINIT) hasSprmib);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_HandleUnspecifiedService(uint8                           sid
                                                                       ,Dcm_MsgType                     requestPtr
                                                                       ,Dcm_MsgLenType                  reqDataLen
                                                                       ,Dcm_MsgType                     responsePtr
                                                                       ,Dcm_MsgLenPtrType               resDataLenPtr
                                                                       ,Dcm_NegativeResponseCodePtrType errorPtr);

extern FUNC(void, DCM_APPL_CODE) Dcm_PostHandleUnspecifiedService(uint8 sid, Dcm_ConfirmationStatusType status);
# endif /* (DCM_UNSPEC_SERVICE_SUPPORT_ENABLED == STD_ON) */
# if (DCM_FBL_POS_RES_ENABLED == STD_ON)
extern FUNC(void, DCM_APPL_CODE) Dcm_SetProgConditions(Dcm_ProgConditionsPtrType ProgConditions);
extern FUNC(void, DCM_APPL_CODE) Dcm_GetProgConditions(Dcm_ProgConditionsPtrType ProgConditions);
# endif /* (DCM_FBL_POS_RES_ENABLED == STD_ON) */
# define DCM_APPL_STOP_SEC_CODE
# include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_19.1 */



/* -----------------------------------------------------------------------------
    &&&~ ROM 32Bit definitions
 ----------------------------------------------------------------------------- */

# define DCM_START_SEC_CONST_32BIT
# include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if !defined ( V_SUPPRESS_EXTENDED_VERSION_CHECK )
extern CONST(uint32, DCM_CONST) Dcm_GeneratorVersion;
# endif

# define DCM_STOP_SEC_CONST_32BIT
# include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_19.1 */



/* -----------------------------------------------------------------------------
    &&&~ Macro definitions
 ----------------------------------------------------------------------------- */

/* Avoid compiler warnings on unused local variables or function parameters */
# define DCM_IGNORE_UNREF_PARAM(paramName)                           ((void)paramName)


/*-----------------------------------------------*/
/*                 GlobalUtils                   */
/*-----------------------------------------------*/
/* Data assemble/disassemble macros */
/* compose from byte stream a 16 bit data */
# define Dcm_Make16Bit(hiByte,loByte)                                ((uint16)((((uint16)(hiByte))<<8)| \
                                                                     ((uint16)(loByte))))                                                             /* PRQA S 3453 */ /* MISRA-C:2004 Rule 19.7: A function should be used in preference to a function-like macro. */
/* compose from byte stream a 32 bit data */
# define Dcm_Make32Bit(hiHiByte,hiLoByte,loHiByte,loLoByte)          ((uint32)((((uint32)(hiHiByte))<<24)| \
                                                                     (((uint32)(hiLoByte))<<16)| \
                                                                     (((uint32)(loHiByte))<<8) | \
                                                                     ((uint32)(loLoByte))))                                                           /* PRQA S 3453 */ /* MISRA-C:2004 Rule 19.7: A function should be used in preference to a function-like macro. */
/* decompose 16 bit data in byte stream */
# define Dcm_GetHiByte(data)                                         ((uint8)(((uint16)(data))>>8))                                                   /* PRQA S 3453 */ /* MISRA-C:2004 Rule 19.7: A function should be used in preference to a function-like macro. */
# define Dcm_GetLoByte(data)                                         ((uint8)(data))                                                                  /* PRQA S 3453 */ /* MISRA-C:2004 Rule 19.7: A function should be used in preference to a function-like macro. */

/* decompose 32 bit data in byte stream */
# define Dcm_GetHiHiByte(data)                                       ((uint8)(((uint32)(data))>>24))                                                  /* PRQA S 3453 */ /* MISRA-C:2004 Rule 19.7: A function should be used in preference to a function-like macro. */
# define Dcm_GetHiLoByte(data)                                       ((uint8)(((uint32)(data))>>16))                                                  /* PRQA S 3453 */ /* MISRA-C:2004 Rule 19.7: A function should be used in preference to a function-like macro. */
# define Dcm_GetLoHiByte(data)                                       ((uint8)(((uint32)(data))>>8))                                                   /* PRQA S 3453 */ /* MISRA-C:2004 Rule 19.7: A function should be used in preference to a function-like macro. */
# define Dcm_GetLoLoByte(data)                                       ((uint8)(data))                                                                  /* PRQA S 3453 */ /* MISRA-C:2004 Rule 19.7: A function should be used in preference to a function-like macro. */



#endif /* __DCM_H__ */
