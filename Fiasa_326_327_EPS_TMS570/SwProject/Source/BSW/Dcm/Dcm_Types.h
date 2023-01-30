/* -----------------------------------------------------------------------------
  Filename:    Dcm_Types.h
  Description: Interface for publishing DCM common datatypes.

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

#if !defined(__DCM_TYPES_H__)
# define __DCM_TYPES_H__

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

/* Communication Stack Datatypes */
# include "ComStack_Types.h"
# include "Dcm_Cfg.h"



/* -----------------------------------------------------------------------------
    &&&~ Configuration switches
 ----------------------------------------------------------------------------- */

# if (DCM_DSD_OEM_INDICATION_ENABLED == STD_ON) || \
     (DCM_DSD_SYS_INDICATION_ENABLED == STD_ON)
#  define DCM_DSD_ANY_INDICATION_ENABLED                             STD_ON
# else
#  define DCM_DSD_ANY_INDICATION_ENABLED                             STD_OFF
# endif

# if (DCM_SERVICE_22_ENABLED == STD_ON)
/* Compatibility */
#  if !defined(DCM_22_USR_PB_USAGE_ENABLED)
#   define DCM_22_USR_PB_USAGE_ENABLED                               STD_OFF
#  endif

#  if (DCM_22_INT_PB_USAGE_ENABLED == STD_ON) || \
      (DCM_22_USR_PB_USAGE_ENABLED == STD_ON)
#   define DCM_22_PB_USAGE_ENABLED                                   STD_ON
#  else
#   define DCM_22_PB_USAGE_ENABLED                                   STD_OFF
#  endif
# endif /* (DCM_SERVICE_22_ENABLED == STD_ON) */


/* -----------------------------------------------------------------------------
    &&&~ Preprocessor constants (defines)
 ----------------------------------------------------------------------------- */

/* DCM status type values */
# define DCM_E_OK                                                    (Dcm_StatusType)E_OK
# define DCM_E_NOT_OK                                                (Dcm_StatusType)E_NOT_OK
# define DCM_E_TI_PREPARE_LIMITS                                     (Dcm_StatusType)2
# define DCM_E_TI_PREPARE_INCONSTENT                                 (Dcm_StatusType)3
# define DCM_E_SESSION_NOT_ALLOWED                                   (Dcm_StatusType)4
# define DCM_E_PROTOCOL_NOT_ALLOWED                                  (Dcm_StatusType)5
# define DCM_E_ROE_NOT_ACCEPTED                                      (Dcm_StatusType)6
# define DCM_E_PERIODICID_NOT_ACCEPTED                               (Dcm_StatusType)7
# define DCM_E_REQUEST_NOT_ACCEPTED                                  (Dcm_StatusType)8
# define DCM_E_REQUEST_ENV_NOK                                       (Dcm_StatusType)9
# define DCM_E_PENDING                                               (Dcm_StatusType)10
# define DCM_E_COMPARE_KEY_FAILED                                    (Dcm_StatusType)11
# define DCM_E_FORCE_RCRRP                                           (Dcm_StatusType)12
/* Vendor specific return codes */
# define DCM_E_BUFFER_TOO_SMALL                                      (Dcm_StatusType)42
# define DCM_E_COM_CTRL_NOT_ACCEPTED                                 (Dcm_StatusType)40
# define DCM_E_DID_NOT_FOUND                                         (Dcm_StatusType)41
# define DCM_E_DID_BUFFER_TOO_SMALL                                  DCM_E_BUFFER_TOO_SMALL
/* BEGIN special return values
 * Only for DCM internal purpose!
 * Must not be used by any application callback!!!
 */
# define DCM_E_PAGED_DATA_OK                                         (Dcm_StatusType)43
# define DCM_E_PROCESSINGDONE                                        (Dcm_StatusType)50

/* END special return values
 */
/*Check for LOCAL_INLINE availability in compiler.h*/
# if defined (LOCAL_INLINE)
/* newer version of compiler.h -> move on */
# else
/*LOCAL_INLINE not available in compiler.h – reduce define to be INLINE only*/
/*If INLINE is also not supported for the target compiler, INLINE is defined to nothing*/
#  define LOCAL_INLINE                                               INLINE
# endif

/* This magic number provides internal DCM generation process consistency check.All DCM files must have the same one. */
# define DCM_TDECL_MAGIC_NUMBER                                      32426
# if ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON))
#  if (DCM_MEMMGR_PARAM_CHECK_ENABLED == STD_OFF)
/* Memory access operation types */
#   define DCM_MEM_OP_READ                                           (Dcm_MemMgrOpType)0
#   define DCM_MEM_OP_WRITE                                          (Dcm_MemMgrOpType)1
#  endif
# endif /* ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON)) */
# define DCM_NO_RESET                                                (Dcm_ResetModeType)0x00
# define DCM_HARD_RESET                                              (Dcm_ResetModeType)0x01
# define DCM_KEY_ON_OFF_RESET                                        (Dcm_ResetModeType)0x02
# define DCM_SOFT_RESET                                              (Dcm_ResetModeType)0x03
# define DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET                       (Dcm_ResetModeType)0x04
# define DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET                      (Dcm_ResetModeType)0x05
# define DCM_BOOTLOADER_RESET                                        (Dcm_ResetModeType)0x06
/* Currently not supported!
#define DCM_SS_BOOTLOADER_RESET  (Dcm_ResetModeType)0x07;
*/
# define DCM_RESET_EXECUTION                                         (Dcm_ResetModeType)0x08

# if ((DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON) && ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF)))
#  define DCM_READ_OK                                                (Dcm_ReturnReadMemoryType)DCM_E_OK
#  define DCM_READ_PENDING                                           (Dcm_ReturnReadMemoryType)DCM_E_PENDING
#  define DCM_READ_FAILED                                            (Dcm_ReturnReadMemoryType)DCM_E_NOT_OK
# endif /* ((DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON) && ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF))) */
# define DCM_ENABLE_RX_TX_NORM                                       (Dcm_CommunicationModeType)0x00
# define DCM_ENABLE_RX_DISABLE_TX_NORM                               (Dcm_CommunicationModeType)0x01
# define DCM_DISABLE_RX_ENABLE_TX_NORM                               (Dcm_CommunicationModeType)0x02
# define DCM_DISABLE_RX_TX_NORMAL                                    (Dcm_CommunicationModeType)0x03

# define DCM_ENABLE_RX_TX_NM                                         (Dcm_CommunicationModeType)0x04
# define DCM_ENABLE_RX_DISABLE_TX_NM                                 (Dcm_CommunicationModeType)0x05
# define DCM_DISABLE_RX_ENABLE_TX_NM                                 (Dcm_CommunicationModeType)0x06
# define DCM_DISABLE_RX_TX_NM                                        (Dcm_CommunicationModeType)0x07

# define DCM_ENABLE_RX_TX_NORM_NM                                    (Dcm_CommunicationModeType)0x08
# define DCM_ENABLE_RX_DISABLE_TX_NORM_NM                            (Dcm_CommunicationModeType)0x09
# define DCM_DISABLE_RX_ENABLE_TX_NORM_NM                            (Dcm_CommunicationModeType)0x0A
# define DCM_DISABLE_RX_TX_NORM_NM                                   (Dcm_CommunicationModeType)0x0B

# if ((DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON) && ((DCM_SERVICE_3D_ENABLED == STD_ON) || (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF)))
#  define DCM_WRITE_OK                                               (Dcm_ReturnWriteMemoryType)DCM_E_OK
#  define DCM_WRITE_PENDING                                          (Dcm_ReturnWriteMemoryType)DCM_E_PENDING
#  define DCM_WRITE_FAILED                                           (Dcm_ReturnWriteMemoryType)DCM_E_NOT_OK
# endif /* ((DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON) && ((DCM_SERVICE_3D_ENABLED == STD_ON) || (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF))) */
# if (DCM_SERVICE_86_ENABLED == STD_ON)
/* --- parameters which can be overwritten by --- */
/* max Service to respond to length; may be overwritten by user config file */
#  if !defined(DCM_SVC_86_STRT_MAX_LENGTH)
#   define DCM_SVC_86_STRT_MAX_LENGTH                                5
#  endif
#  if (DCM_SVC_86_STRT_MAX_LENGTH > 255)
#   error "Maximum length of service to respond to have been configured out of range!"
#  endif
# endif /* (DCM_SERVICE_86_ENABLED == STD_ON) */
# if (DCM_FBL_POS_RES_ENABLED == STD_ON)
#  define DCM_COLD_START                                             (Dcm_EcuStartModeType)0x00
#  define DCM_WARM_START                                             (Dcm_EcuStartModeType)0x01
# endif /* (DCM_FBL_POS_RES_ENABLED == STD_ON) */


/* -----------------------------------------------------------------------------
    &&&~ Datatype definitions
 ----------------------------------------------------------------------------- */

typedef uint8                                               Dcm_ContextIdType;
typedef uint8                                               Dcm_StatusType;
typedef P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST)           Dcm_ApplConstDataPtrType;
typedef uint16                                              Dcm_MsgLenType;
typedef unsigned int                                        Dcm_BitType;
typedef uint8                                               Dcm_MsgItemType;

typedef P2VAR(Dcm_MsgItemType, AUTOMATIC, DCM_VAR_NOINIT)   Dcm_MsgType;
typedef P2VAR(Dcm_MsgLenType, AUTOMATIC, DCM_VAR_NOINIT)    Dcm_MsgLenPtrType;

typedef uint8 Dcm_RteDataType[];                                                                                                                      /* PRQA S 3650 */ /* QAC 7.0: General typedef for the port-interfaces */
typedef P2VAR(Dcm_RteDataType, AUTOMATIC, DCM_VAR_NOINIT)   Dcm_RteDataPtrType;                                                                       /* PRQA S 3651 */ /* QAC 7.0: General typedef for the port-interfaces */

/* Generic data type pointers */
typedef P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT)             Dcm_Uint8DataPtrType;
typedef P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT)            Dcm_Uint16DataPtrType;
typedef P2CONST(uint8, AUTOMATIC, DCM_CONST)                Dcm_Uint8ConstDataPtrType;
typedef P2CONST(uint16, AUTOMATIC, DCM_CONST)               Dcm_Uint16ConstDataPtrType;
typedef P2CONST(uint32, AUTOMATIC, DCM_CONST)               Dcm_Uint32ConstDataPtrType;
typedef P2CONST(uint32, AUTOMATIC, DCM_CAL_PRM)             Dcm_Uint32CalibDataPtrType;

typedef CONSTP2CONST(uint8, AUTOMATIC, DCM_CONST)           Dcm_Uint8ConstDataConstPtrType;
typedef CONSTP2CONST(uint16, AUTOMATIC, DCM_CONST)          Dcm_Uint16ConstDataConstPtrType;
typedef CONSTP2CONST(uint32, AUTOMATIC, DCM_CONST)          Dcm_Uint32ConstDataConstPtrType;
typedef CONSTP2CONST(uint32, AUTOMATIC, DCM_CAL_PRM)        Dcm_Uint32CalibDataConstPtrType;

# if (DCM_OBD_CALIBRATION_ENABLED == STD_ON)
typedef Dcm_Uint32CalibDataConstPtrType Dcm_ObdMaskConstDataPtrType;
# else
typedef Dcm_Uint32ConstDataConstPtrType Dcm_ObdMaskConstDataPtrType;
# endif

typedef struct
{
  uint16 timeOutP2;
  uint16 timeOutP2Ex;
}Dcm_TimerSettingType;

/* Appl pointer types */
typedef P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)              Dcm_ApplDataPtrType;
typedef P2VAR(Dcm_MsgLenType, AUTOMATIC, DCM_APPL_DATA)     Dcm_ApplDataLenPtrType;


/* Common service port/call-back data types
 * Do not use directly the Dcm_MsgLenType to avoid indirect changes of the service-port prototype on any DCM optimization/extension.*/
typedef uint16                                               Dcm_RteDataLenType;
typedef P2VAR(Dcm_RteDataLenType, AUTOMATIC, DCM_VAR_NOINIT) Dcm_RteDataLenPtrType;

typedef uint8 Dcm_DevErrorType;

# if ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON))
#  if (DCM_MEMMGR_PARAM_CHECK_ENABLED == STD_OFF)
typedef uint8 Dcm_MemMgrOpType;
#  endif
# endif /* ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON)) */
typedef uint8 Dcm_ResetModeType;

# if ((DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON) && ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF)))
typedef uint8 Dcm_ReturnReadMemoryType;
# endif /* ((DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON) && ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF))) */
typedef uint8 Dcm_CommunicationModeType;

# if ((DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON) && ((DCM_SERVICE_3D_ENABLED == STD_ON) || (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF)))
typedef uint8 Dcm_ReturnWriteMemoryType;
# endif /* ((DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON) && ((DCM_SERVICE_3D_ENABLED == STD_ON) || (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF))) */
# if (DCM_SERVICE_86_ENABLED == STD_ON)
typedef uint8  Dcm_86_RoeStateType;
typedef uint8  Dcm_86_STRTLengthType;

typedef struct
{
  uint16                  numMatchingDTCs;              /* while RoE is active: current number of DTCs matching the status mask */
  uint8                   dtcStatusMask;                /* configured status mask for RoE */
  uint8                   isSessionControlDisabled;     /* when set to '1', session control will have no effect on RoE (DID 0x0106) */
  PduIdType               rxPduId;                      /* RxPduId of request, which started RoE */
  Dcm_86_RoeStateType     handlerState;                 /* state of the internal RoE state machine */
  Dcm_86_STRTLengthType   STRTLength;                   /* length of service to respond to */
  Dcm_MsgItemType         STRT[DCM_SVC_86_STRT_MAX_LENGTH];   /* service to respond to */
} Dcm_86_NvMStateDataType;

typedef P2VAR(Dcm_86_NvMStateDataType, AUTOMATIC, DCM_VAR_NOINIT)   Dcm_86_StateDataPtrType;
# endif /* (DCM_SERVICE_86_ENABLED == STD_ON) */
# if (DCM_FBL_POS_RES_ENABLED == STD_ON)
typedef uint8 Dcm_EcuStartModeType;

typedef struct
{
  /* uint8 ProtocolID; - not used since single protocol DCM only! */
  uint8                 TesterSourceAddr;
  uint8                 Sid;
  uint8                 SubFncId;
  Dcm_EcuStartModeType  EcuStartMode;
}Dcm_ProgConditionsType;

typedef P2VAR(Dcm_ProgConditionsType, AUTOMATIC, DCM_VAR_NOINIT) Dcm_ProgConditionsPtrType;
# endif /* (DCM_FBL_POS_RES_ENABLED == STD_ON) */
typedef P2FUNC (Std_ReturnType, DCM_CODE, Dcm_RepeaterProxyFuncType) (void);



#endif /* __DCM_TYPES_H__ */
