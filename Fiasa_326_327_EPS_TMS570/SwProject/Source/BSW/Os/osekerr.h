/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: osekerr.h
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.49
|
|  Description: definitions of all errors for assertions and OSError
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2012 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/

/* double include preventer */
#ifndef _OSEKERR_H
#define _OSEKERR_H

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
/* TR:SOSK22:0153 Start */
/* TR:SOSK22:0149 Start */
/* TR:SOSK22:0126 Start */
/* TR:SOSK22:0002 Start This is only a part of this informal specification, 
                        because it is of introductory character and specified 
                        in detail in following other SOSK22:xxxx numbers */
/* TR:SPMF10:0001 Start */
/* TR:SASR30:0350 Start Errors from OSEK spec */
/* All errors of API services (inherited from OSEK spec) */
/*      E_OK            0  now defined in osek.h */
#define E_OS_ACCESS     1
#define E_OS_CALLEVEL   2
#define E_OS_ID         3
#define E_OS_LIMIT      4
#define E_OS_NOFUNC     5
#define E_OS_RESOURCE   6
#define E_OS_STATE      7
#define E_OS_VALUE      8
/* TR:SASR30:0350 End */
/* TR:SOSK22:0153 End */

/* TR:SOSK22:0154 Start */
/* TR:SOSK22:0155 Start */
/* errors of API services (Autosar specification v3.0) */
/* TR:SASR30:0350 Start Errors from Autosar spec */
#define E_OS_SERVICEID            9
#define E_OS_ILLEGAL_ADDRESS      10
#define E_OS_MISSINGEND           11
#define E_OS_DISABLEDINT          12
#define E_OS_STACKFAULT           13
#define E_OS_PROTECTION_MEMORY    14
#define E_OS_PROTECTION_TIME      15
#define E_OS_PROTECTION_ARRIVAL   16
#define E_OS_PROTECTION_LOCKED    17
#define E_OS_PROTECTION_EXCEPTION 18
#define E_OS_PROTECTION_PERIPHERAL 19 /* TR:SPMF95:0012 */
#define E_OS_SYS_ASSERTION        20
#define E_OS_SYS_ABORT            21
/*E_OS_SYS_DIS_INT replaced by E_OS_DISABLEDINT, no No. 22*/
#define E_OS_SYS_API_ERROR        23
#define E_OS_SYS_ALARM_MANAGEMENT 24
#define E_OS_SYS_WARNING          25
/* TR:SASR30:0350 End */
/* TR:SOSK22:0154 End */
/* TR:SOSK22:0155 End */

/* TR:SPMF10:0002 Start */
/* TR:SPMF10:0003 Start */
/* TR:SPMF10:0004 Start */
/* TR:SPMF10:0005 Start */
/* TR:SPMF10:0006 Start */
/* TR:SPMF10:0007 Start */

/*
 * Syntax of errornumbers:
 * 0xgfee
 *   ||+--- consecutive error number
 *   |+---- number of function in the function group
 *   +----- number of function group
 */

/* Group: Task management 1 */
/*    function ActivateTask:           AT: 1 */
/*    function TerminateTask:          TT: 2 */
/*    function ChainTask:              HT: 3 */
/*    function Schedule:               SH: 4 */
/*    function GetTaskState:           GS: 5 */
/*    function GetTaskID:              GI: 6 */
/*    function osMissingTerminateError MT: 7 */

#define osdErrATWrongTaskID           0x1101U
#define osdErrATWrongTaskPrio         0x1102U
#define osdErrATMultipleActivation    0x1103U
#define osdErrATIntAPIDisabled        0x1104U
#define osdErrATAlarmMultipleActivation 0x1105U
#define osdErrATNoAccess              0x1106U
#define osdErrATCallContext           0x1107U

#define osdErrTTDisabledInterrupts    0x1201U
#define osdErrTTResourcesOccupied     0x1202U
#define osdErrTTNotActivated          0x1203U
#define osdErrTTOnInterruptLevel      0x1204U
#define osdErrTTNoImmediateTaskSwitch 0x1205U /* TR:SPMF12:0011*/
#define osdErrTTCallContext           0x1206U

#define osdErrHTInterruptsDisabled    0x1301U
#define osdErrHTResourcesOccupied     0x1302U
#define osdErrHTWrongTaskID           0x1303U
#define osdErrHTNotActivated          0x1304U
#define osdErrHTMultipleActivation    0x1305U
#define osdErrHTOnInterruptLevel      0x1306U
#define osdErrHTWrongTaskPrio         0x1307U
#define osdErrHTNoImmediateTaskSwitch 0x1308U /* TR:SPMF12:0012*/
#define osdErrHTCallContext           0x1309U
#define osdErrHTNoAccess              0x130AU

#define osdErrSHInterruptsDisabled    0x1401U
#define osdErrSHOnInterruptLevel      0x1402U
#define osdErrSHScheduleNotAllowed    0x1403U
#define osdErrSHResourcesOccupied     0x1405U
#define osdErrSHCallContext           0x1406U

#define osdErrGSWrongTaskID           0x1501U
#define osdErrGSIntAPIDisabled        0x1502U
#define osdErrGSIllegalAddr           0x1503U
#define osdErrGSCallContext           0x1504U
#define osdErrGSNoAccess              0x1505U

#define osdErrGIIntAPIDisabled        0x1601U
#define osdErrGIIllegalAddr           0x1602U
#define osdErrGICallContext           0x1603U

#define osdErrMTMissingTerminateTask  0x1701U


/* Group: Interrupt handling 2 */
/*    function EnableAllInterrupts         EA: 4 */
/*    function DisableAllInterrupts        DA: 5 */
/*    function ResumeOSInterrupts          RI: 6 */
/*    function SuspendOSInterrupts         SI: 7 */
/*    function osUnhandledException        UE: 8 */
/*    function osSaveDisableLevelNested    SD: 9 */
/*    function osRestoreEnableLevelNested  RE: A */
/*    function osSaveDisableGlobalNested   SG: B */
/*    function osRestoreEnableGlobalNested RG: C */
/*    function ResumeAllInterrupts         RA: D */
/*    function SuspendAllInterrupts        SA: E */

#define osdErrEAIntAPIWrongSequence   0x2401U
#define osdErrDAIntAPIDisabled        0x2501U

#define osdErrUEUnhandledException    0x2801U /* TR:SPMF78:0004 */

#define osdErrSDWrongCounter          0x2901U
#define osdErrREWrongCounter          0x2A01U

#define osdErrSGWrongCounter          0x2B01U
#define osdErrRGWrongCounter          0x2C01U


/* Group: Resource management 3 */
/*    function GetResource            GR:  1 */
/*    function ReleaseResource        RR:  2 */

#define osdErrGRWrongResourceID       0x3101U
#define osdErrGRPriorityOccupied      0x3102U
#define osdErrGRResourceOccupied      0x3103U
#define osdErrGRNoAccessRights        0x3104U /* TR:SPMF12:0009 */ /* TR:SPMF12:0010 */ 
#define osdErrGRWrongPrio             0x3105U
#define osdErrGRIntAPIDisabled        0x3106U
#define osdErrGRNoAccess              0x3107U
#define osdErrGRCallContext           0x3108U
#define osdErrGRISRNoAccessRights     0x3109U

#define osdErrRRWrongResourceID       0x3201U
#define osdErrRRCeilingPriorityNotSet 0x3202U
#define osdErrRRWrongTask             0x3203U
#define osdErrRRWrongPrio             0x3204U
#define osdErrRRNotOccupied           0x3206U
#define osdErrRRWrongSequence         0x3207U
#define osdErrRRIntAPIDisabled        0x3208U
#define osdErrRRNoAccess              0x3209U
#define osdErrRRCallContext           0x320AU
#define osdErrRRISRNoAccessRights     0x320BU
                                        

/* Group: Event control 4 */
/*    function SetEvent               SE:  1 */
/*    function ClearEvent             CE:  2 */
/*    function GetEvent               GE:  3 */
/*    function WaitEvent              WE:  4 */

#define osdErrSEWrongTaskID           0x4101U
#define osdErrSENotExtendedTask       0x4102U
#define osdErrSETaskSuspended         0x4103U
#define osdErrSEWrongTaskPrio         0x4104U
#define osdErrSEIntAPIDisabled        0x4105U
#define osdErrSECallContext           0x4106U
#define osdErrSENoAccess              0x4107U

#define osdErrCENotExtendedTask       0x4201U
#define osdErrCEOnInterruptLevel      0x4202U
#define osdErrCEIntAPIDisabled        0x4203U
#define osdErrCECallContext           0x4204U

#define osdErrGEWrongTaskID           0x4301U
#define osdErrGENotExtendedTask       0x4302U
#define osdErrGETaskSuspended         0x4303U
#define osdErrGEIntAPIDisabled        0x4304U
#define osdErrGEIllegalAddr           0x4305U
#define osdErrGECallContext           0x4306U
#define osdErrGENoAccess              0x4307U

#define osdErrWENotExtendedTask       0x4401U
#define osdErrWEResourcesOccupied     0x4402U
#define osdErrWEInterruptsDisabled    0x4403U
#define osdErrWEOnInterruptLevel      0x4404U
#define osdErrWECallContext           0x4405U

/* Group: Alarms 5 */
/*    function GetAlarmBase           GB:  1 */
/*    function GetAlarm               GA:  2 */
/*    function SetRelAlarm            SA:  3 */
/*    function SetAbsAlarm            SL:  4 */
/*    function CancelAlarm            CA:  5 */
/*    function osWorkAlarms           WA:  6 */

#define osdErrGBWrongAlarmID          0x5101U
#define osdErrGBIntAPIDisabled        0x5102U
#define osdErrGBIllegalAddr           0x5103U
#define osdErrGBCallContext           0x5104U
#define osdErrGBNoAccess              0x5105U

#define osdErrGAWrongAlarmID          0x5201U
#define osdErrGANotActive             0x5202U
#define osdErrGAIntAPIDisabled        0x5203U
#define osdErrGAIllegalAddr           0x5204U
#define osdErrGACallContext           0x5205U
#define osdErrGANoAccess              0x5206U

#define osdErrSAWrongAlarmID          0x5301U
#define osdErrSAAlreadyActive         0x5302U
#define osdErrSAWrongCycle            0x5303U
#define osdErrSAWrongDelta            0x5304U
#define osdErrSAIntAPIDisabled        0x5305U
#define osdErrSAZeroIncrement         0x5306U
#define osdErrSACallContext           0x5307U
#define osdErrSANoAccess              0x5308U

#define osdErrSLWrongAlarmID          0x5401U
#define osdErrSLAlreadyActive         0x5402U
#define osdErrSLWrongCycle            0x5403U
#define osdErrSLWrongStart            0x5404U
#define osdErrSLIntAPIDisabled        0x5405U
#define osdErrSLCallContext           0x5406U
#define osdErrSLNoAccess              0x5407U

#define osdErrCAWrongAlarmID          0x5501U
#define osdErrCANotActive             0x5502U
#define osdErrCAIntAPIDisabled        0x5503U
#define osdErrCAAlarmInternal         0x5504U /* TR:SPMF12:0008 */ 
#define osdErrCACallContext           0x5505U
#define osdErrCANoAccess              0x5506U


/* Group: Operating system execution control 6 */
/*    function osCheckStackOverflow   SO:  1 */
/*    function osSchedulePrio         SP:  2 */
/*    function osGetStackUsage        SU:  3 */
/*    function osCheckLibraryVers..   CL:  4 */
/*    function osErrorHook            EH:  5 */
/*    function StartOS                ST:  6 */

#define osdErrSOStackOverflow         0x6101U

#define osdErrSPInterruptsEnabled     0x6201U /* TR:SPMF12:0007 */ 

#define osdErrSUWrongTaskID           0x6301U

#define osdErrCLWrongLibrary          0x6401U

#define osdErrEHInterruptsEnabled     0x6501U

#define osdErrSTMemoryError           0x6601U /* TR:SPMF12:0006 */
#define osdErrSTNoImmediateTaskSwitch 0x6602U
#define osdErrSTWrongAppMode          0x6603U
#define osdErrSTConfigCRCError        0x6604U


/* Group: Schedule Table control 7 */
/*    function StartScheduleTableRel  SR:  1 */
/*    function StartScheduleTableAbs  SS:  2 */
/*    function StopScheduleTable      SP:  3 */
/*    function GetScheduleTableStatus SG:  4 */
/*    function NextScheduleTable      SN:  5 */
/*    function osWorkScheduleTables   WS:  6 */


#define osdErrSRWrongID                0x7101U
#define osdErrSRAlreadyRunningOrNext   0x7102U
#define osdErrSRZeroOffset             0x7103U
#define osdErrSROffsetTooBig           0x7104U
#define osdErrSRIntAPIDisabled         0x7105U
#define osdErrSRCallContext            0x7106U
#define osdErrSRNoAccess               0x7107U
#define osdErrSRImpliciteSync          0x7109U

#define osdErrSSWrongID                0x7201U
#define osdErrSSAlreadyRunningOrNext   0x7202U
#define osdErrSSTickvalueTooBig        0x7203U
#define osdErrSSIntAPIDisabled         0x7204U
#define osdErrSSCallContext            0x7205U
#define osdErrSSNoAccess               0x7206U

#define osdErrSPWrongID               0x7301U
#define osdErrSPNotRunning            0x7302U
#define osdErrSPIntAPIDisabled        0x7303U
#define osdErrSPCallContext           0x7304U
#define osdErrSPNoAccess              0x7305U
#define osdErrSPUnknownCase           0x7306U

#define osdErrSGWrongID               0x7401U
#define osdErrSGIntAPIDisabled        0x7402U
#define osdErrSGCallContext           0x7403U
#define osdErrSGNoAccess              0x7404U
#define osdErrSGIllegalAddr           0x7405U

#define osdErrSNWrongCurrentID        0x7501U
#define osdErrSNWrongNextID           0x7502U
#define osdErrSNNotRunning            0x7503U
#define osdErrSNAlreadyRunningOrNext  0x7504U
#define osdErrSNDifferentCounters     0x7505U
#define osdErrSNIntAPIDisabled        0x7506U
#define osdErrSNCallContext           0x7507U
#define osdErrSNNoAccess              0x7508U

#define osdErrWSUnknownAction         0x7601U
#define osdErrWSUnknownReaction       0x7602U

/* Group: other SC1 functions 8 */
/*    function IncrementCounter     IC:  1 */
/*    function GetISRID             II:  2 */

#define osdErrICWrongCounterID        0x8101U
#define osdErrICIntAPIDisabled        0x8102U
#define osdErrICCallContext           0x8103U
#define osdErrICNoAccess              0x8104U

#define osdErrIIIntAPIDisabled        0x8201U
#define osdErrIICallContext           0x8202U

/* Group: other SC2, SC3, SC4 functions 9 */
/*    function CallTrustedFunction        CT, NT:  3 */
/*    function TerminateApplication       TA:  4 */
/*    function SyncScheduleTable          SY:  5 */
/*    function SetScheduleTableAsync      AY:  6 */
/*    function BlockingTimeMonitoring     BM:  7 */
/*    function GetTaskMaxExecutionTime    TE:  8 */
/*    function GetISRMaxExecutionTime     IE:  9 */
/*    function GetTaskMaxBlockingTime     TB:  A */
/*    function GetISRMaxBlockingTime      IB:  B */
/*    function StartScheduleTableSynchron TS:  C */
/*    function ExecutionTimeMonitoring    ET:  D */
/*    function ISR exit                   IX:  E */
/*    function GetTaskMinInterArrivalTime    TM:  0 */
/*    function GetISRMinInterArrivalTime     MI:  F */

#define osdErrCTWrongFctIdx           0x9301U
#define osdErrCTCallContext           0x9302U
#define osdErrCTIntAPIDisabled        0x9303U
#define osdErrNTWrongFctIdx           0x9304U
#define osdErrNTCallContext           0x9305U
#define osdErrNTIntAPIDisabled        0x9306U

#define osdErrTAWrongRestartOption    0x9401U
#define osdErrTACallContext           0x9402U
#define osdErrTAIntAPIDisabled        0x9403U

#define osdErrSYCallContext           0x9501U
#define osdErrSYWrongID               0x9502U
#define osdErrSYNoAccess              0x9503U
#define osdErrSYIntAPIDisabled        0x9504U
#define osdErrSYSTNotRunning          0x9505U
#define osdErrSYGlobalTimeTooBig      0x9506U
#define osdErrSYSyncKindNotExplicit   0x9507U

#define osdErrAYCallContext           0x9601U
#define osdErrAYWrongID               0x9602U
#define osdErrAYNoAccess              0x9603U
#define osdErrAYIntAPIDisabled        0x9604U

#define osdErrBMResAlreadyMeasured    0x9702U
#define osdErrBMInvalidProcessInStart 0x9703U
#define osdErrBMInvalidProcessInStop  0x9704U

#define osdErrTEWrongTaskID           0x9801U
#define osdErrTENoAccess              0x9802U
#define osdErrTEIllegalAddr           0x9803U

#define osdErrIEWrongISRID            0x9901U
#define osdErrIENoAccess              0x9902U
#define osdErrIEIllegalAddr           0x9903U

#define osdErrTBWrongTaskID           0x9A01U
#define osdErrTBWrongBlockType        0x9A02U
#define osdErrTBWrongResourceID       0x9A03U
#define osdErrTBNoAccessToTask        0x9A04U
#define osdErrTBNoAccessToResource    0x9A05U
#define osdErrTBIllegalAddr           0x9A06U

#define osdErrIBWrongISRID            0x9B01U
#define osdErrIBWrongBlockType        0x9B02U
#define osdErrIBWrongResourceID       0x9B03U
#define osdErrIBNoAccessToISR         0x9B04U
#define osdErrIBNoAccessToResource    0x9B05U
#define osdErrIBIllegalAddr           0x9B06U

#define osdErrTSCallContext            0x9C01U
#define osdErrTSWrongID                0x9C02U
#define osdErrTSNoAccess               0x9C03U
#define osdErrTSIntAPIDisabled         0x9C04U
#define osdErrTSSTAlreadyRunning       0x9C05U
#define osdErrTSGlobalTimeTooBig       0x9C06U
#define osdErrTSSyncKindNotExplicit    0x9C08U

#define osdErrETNoCurrentProcess       0x9D01U

#define osdErrIXResourcesOccupied      0x9E01U
#define osdErrIXIntAPIDisabled         0x9E02U

#define osdErrTMWrongTaskID           0x9001U
#define osdErrTMNoAccess              0x9002U
#define osdErrTMIllegalAddr           0x9003U

#define osdErrMIWrongISRID            0x9F01U
#define osdErrMINoAccess              0x9F02U
#define osdErrMIIllegalAddr           0x9F03U

/* Group: Platform specific error codes A */
/* KB begin osekHwErrorCodes (overwritten) */
/*    function osSystemStackOverflow   YO:  1 */
/*    function osDefVectWarning        DV:  2 */
/*    function osIntNestingOverflow    NO:  3 */
/*    SafeContext                      CS:  4 */
/*    Dispatcher                       DP:  5 */

#define osdErrYOStackOverflow           0xA101U
#define osdErrYOIrqStackOverflow        0xA102U
#define osdErrYOIntHdlStackOverflow     0xA103U
#define osdErrDVDefVect                 0xA201U
#define osdErrNOIntNestingOverflow      0xA301U
#define osdErrDPStartValidContext       0xA401U
#define osdErrDPResumeInvalidContext    0xA402U
#define osdErrDPWrongHighReadyTaskIndex 0xA501U
/* KB end osekHwErrorCodes */

/* Group: messages B */
/*    function StartCOM               SC:  1 */
/*    function StopCOM                TC:  2 */
/*    function SendMessage            SM:  3 */
/*    function ReceiveMessage         RM:  4 */
/*    function GetMessageStatus       MS:  5 */
/*    function GetCOMApplicationMode  AM:  6 */
/*    function InitMessage            IM:  7 */
/*    function COMErrorHook           CR:  8 */

#define osdErrSCWrongModeID           0xB101U
#define osdErrSCCallContext           0xB102U

#define osdErrTCWrongModeID           0xB201U
#define osdErrTCCallContext           0xB202U

#define osdErrSMWrongID               0xB301U
#define osdErrSMNoAccess              0xB302U
#define osdErrSMCallContext           0xB303U

#define osdErrRMWrongID               0xB401U
#define osdErrRMLimit                 0xB402U
#define osdErrRMNoMessage             0xB403U
#define osdErrRMNoAccess              0xB404U
#define osdErrRMIllegalAddr           0xB405U
#define osdErrRMCallContext           0xB406U

#define osdErrMSWrongID               0xB501U
#define osdErrMSLimit                 0xB502U
#define osdErrMSNoMessage             0xB503U
#define osdErrMSNoAccess              0xB504U
#define osdErrMSCallContext           0xB505U

#define osdErrIMWrongID               0xB701U
#define osdErrIMNoAccess              0xB702U
#define osdErrIMCallContext           0xB703U

#define osdErrCRInterruptsEnabled     0xB801U /* TR:SPMF12:0007 */



/* TR:SPMF10:0001 End */
/* TR:SPMF10:0002 End */
/* TR:SPMF10:0003 End */
/* TR:SPMF10:0004 End */
/* TR:SPMF10:0005 End */
/* TR:SPMF10:0006 End */
/* TR:SPMF10:0007 End */
/* TR:SOSK22:0002 End */
/* TR:SOSK22:0126 End */
/* TR:SOSK22:0149 End */

/*lint -restore re-enable messages*/

#endif /* double include preventer */

/* END OF HEADER osekerr.h */
