/* -----------------------------------------------------------------------------
  Filename:    Dcm_Cbk.h
  Description: Interface towards the other components used by DCM.

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

#if !defined(__DCM_CBK_H__)
# define __DCM_CBK_H__

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

# include "Dcm_Types.h"



/* -----------------------------------------------------------------------------
    &&&~ Preprocessor constants (defines)
 ----------------------------------------------------------------------------- */

/* This magic number provides internal DCM generation process consistency check.All DCM files must have the same one. */
# define DCM_ADECL_MAGIC_NUMBER                                      32426


/* -----------------------------------------------------------------------------
    &&&~ Datatype definitions
 ----------------------------------------------------------------------------- */

# if (DCM_PDUROUTER_ENABLED == STD_ON)
typedef P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) DcmPduInfoTypePtr;
# endif /* (DCM_PDUROUTER_ENABLED == STD_ON) */


/* -----------------------------------------------------------------------------
    &&&~ Function prototypes
 ----------------------------------------------------------------------------- */

# define DCM_START_SEC_CODE
# include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* COM manager API */
extern FUNC(void, DCM_CODE) Dcm_ComM_NoComModeEntered(void);
extern FUNC(void, DCM_CODE) Dcm_ComM_SilentComModeEntered(void);
extern FUNC(void, DCM_CODE) Dcm_ComM_FullComModeEntered(void);

# if (DCM_PDUROUTER_ENABLED == STD_ON)
/* RX PDU_R API */
extern FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProvideRxBuffer(PduIdType DcmRxPduId, PduLengthType TpSduLength, P2VAR(DcmPduInfoTypePtr, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr);
extern FUNC(void, DCM_CODE) Dcm_RxIndication(PduIdType DcmRxPduId, NotifResultType Result);
/* TX PDU_R API */
extern FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProvideTxBuffer(PduIdType DcmTxPduId, P2VAR(DcmPduInfoTypePtr, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr, PduLengthType Length);
extern FUNC(void, DCM_CODE) Dcm_TxConfirmation(PduIdType DcmTxPduId, NotifResultType Result);

#  if (DCM_PDUR_PERIODIC_TX_TYPE2_ENABLED == STD_ON)
/* Flex Ray and LIN specific workaround */
extern FUNC(void, DCM_CODE) Dcm_TriggerTransmit(PduIdType FrTxPduId, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) FrSduPtr);
#  endif

#  if (DCM_CHANGE_TP_PARAM_ENABLED == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_ChangeParameterConfirmation(PduIdType DcmRxPduId, NotifResultType Result);
#  endif
# endif /* (DCM_PDUROUTER_ENABLED == STD_ON) */
# if (DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON)
extern FUNC(Dcm_StatusType, DCM_CODE) Dcm_ReadDid(uint16 did, Dcm_ApplDataPtrType resDataPtr, Dcm_ApplDataLenPtrType resDataLenPtr);
# endif

# define DCM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_19.1 */



#endif /* __DCM_CBK_H__ */
