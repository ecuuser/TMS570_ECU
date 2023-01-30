/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: osek.h
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=2.08
|
|  Description: contains osek prototypes and declarations, declares parts
|               of the safe context implementation to be used in safety
|               related code and QM code.
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2012 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/

/* MISRA RULE 19.15 VIOLATION: The QAC-Tool states a violation of rule 19.15 with 
 * message 0883 below. Anyhow, there is a double include prevention and therefore,
 * the message is considered to be wrong. */
/* double include preventer */
#ifndef _OSEKSCTX_H      /* PRQA S 0883 EOF */ /* see MISRA comment above */
#define _OSEKSCTX_H

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

#if defined USE_QUOTE_INCLUDES
 #include "osektype.h"
 #include "osekasrt.h"
#else
 #include <osektype.h>
 #include <osekasrt.h>
#endif


#define osdIntAPIDisableAll 0x80U
/* KB begin osekHwSctxConstants (overwritten) */
#define osGetLevel osCheckInterruptsDisabled

#define osdREQMSKCLR0 0xFFFFfe40UL
#define osdREQMSKCLR1 0xFFFFfe44UL

#define osdMPURegionNr_DEFAULT            0
#define osdMPURegionNr_CODE               1
#define osdMPURegionNr_STACK              2
#define osdMPURegionNr_APPLDATA_NOINIT    3
#define osdMPURegionNr_AREA4              4
#define osdMPURegionNr_APPLDATA_INIT      5
#define osdMPURegionNr_AREA6              6
#define osdMPURegionNr_SHAREDGLOBAL       7
#define osdMPURegionNr_AREA8              8
#define osdMPURegionNr_AREA9              9
#define osdMPURegionNr_AREA10            10
#define osdMPURegionNr_AREA11            11

#define osdSpecialStack_AbortStack        0
#define osdSpecialStack_IRQStack          1
#define osdSpecialStack_StartupStack      2
#define osdSpecialStack_SupervisorStack   3
#define osdSpecialStack_APIStack          4

#define osdNumberOfMPUAreas 12
#define OSCFGBLOCK (&osConfigBlock)
/* KB end osekHwSctxConstants */

/* KB begin osekHwSctxTypes (overwritten) */
typedef struct
{
   osuint32 aulMPUSectionStartAddress[osdNumberOfMPUAreas];
   osuint32 aulMPUSectionSize[osdNumberOfMPUAreas];       
   osuint32 aulMPUSectionAccess[osdNumberOfMPUAreas];       
} tsMPUSetting;

typedef struct
{
   osuint32 aulMPUSectionStartAddress;
   osuint32 aulMPUSectionSize;       
   osuint32 aulMPUSectionAccess;       
} tsSingleMPUSetting;
/* KB end osekHwSctxTypes */

/* KB begin osekHWConfigBlockFixedLengthPartStruct (overwritten) */
typedef struct {

   /* Frame */
   osuint8 aucMagicNumber[4]; /* 130 42 12 196  = 0x82 2A 0C C4 */ 
   osuint16 uiLength;                                              
   osuint16 uiHardwareID;     /* Hardware Identification */        
   osuint8 ucMajorVersion;                                         
   osuint8 ucMinorVersion;                                         
   osuint16 uiConfigBlockVersion;   /* configuration block format version */        
   osuint16 uiUserConfigurationVersion;   /* user configuration version */        

   /* cargo --------------------------------------------------------------- */

   /* start addresses of sub-containers (fixed number) */
   osuint32 uiStartAddressConfigBlock;
   osuint32 uiStartAddressSubCont0;   /* absolute */ 
   osuint32 uiStartAddressTaskStartAddress;                                           
   osuint32 uiStartAddressTaskPreemptive;                                           
   osuint32 uiStartAddressTaskTrusted;                                           
   osuint32 uiStartAddressTaskStackStartAddress;                                           
   osuint32 uiStartAddressTaskStackEndAddress;                                           
   osuint32 uiStartAddressTaskMPUSettings;                                           
   osuint32 uiStartAddressTaskToAppl;         
   osuint32 uiStartAddressNTFTaskStackMPUSetting;         
   osuint32 uiStartAddressNTFTaskStackStartAddress;         
   osuint32 uiStartAddressNTFTaskStackEndAddress;         
   osuint32 uiStartAddressISRMPUSettings;                                           
   osuint32 uiStartAddressISRToAppl;                                           
   osuint32 uiStartAddressISRTrusted;  
   osuint32 uiStartAddressNTFISRStackMPUSetting;  
   osuint32 uiStartAddressNTFISRStackStartAddress;         
   osuint32 uiStartAddressNTFISRStackEndAddress;         
   osuint32 uiStartAddressISRStackStart;                                           
   osuint32 uiStartAddressISRStackEnd;                                           
   osuint32 uiStartAddressTrustedFct;                                           
   osuint32 uiStartAddressTrustedFctToAppl;                                           
   osuint32 uiStartAddressNonTrustedFct;                                           
   osuint32 uiStartAddressNonTrustedFctToAppl;                                           
   osuint32 uiStartAddressSpecStackStart;                                           
   osuint32 uiStartAddressSpecStackEnd;                                           
   osuint32 uiStartAddressOSMPUSettings;                                           
   osuint32 uiStartAddressApplMPUSettings;      
   osuint32 uiStartAddressPeripheralRegionStart;      
   osuint32 uiStartAddressPeripheralRegionEnd;        
   osuint32 uiStartAddressPeripheralRegionAccess;     
   osuint32 uiStartAddressInterruptPrios;      
   osuint32 uiStartAddressIntNestingEnabled;      
   osuint32 uiStartAddressIRQFIQSetting;      
   osuint32 uiStartAddressINTChannelMap;      

   /* Sub-Container 0 = General (fixed number) */
   osuint16 uiNumberOfTasks;            /* = osdNumberOfAllTasks */          
   osuint16 uiNumberOfCat2ISRs;             /* = osdNumberOfISRs */              
   osuint16 uiNumberOfTrustedFunctions; /* = osdNumberOfTrustedFunctions */
   osuint16 uiNumberOfNonTrustedFunctions; /* = osdNumberOfNonTrustedFunctions */
   osuint16 uiNumberOfIRQNestings;      /* = osdIRQMaxNesting */  
   osuint16 uiNumberOfApplications;        /* = osdNumberOfApplications */              
   osuint16 uiNumberOfSpecStacks;        /* = osdNumberOfSpecStacks */              
   osuint16 uiNumberOfPeripheralRegions;      /* = osdNumberOfPeripheralRegions */ 
   osuint8  ucStackUsageMeasurement;    /* = osdStackUsageMeasurement */   
} tsConfigBlockFixedLengthPart;
/* KB end osekHWConfigBlockFixedLengthPartStruct */

/* Save Context Variables */
osqScRAM0 extern osqScRAM1          osqScRAM2 osuint8     osqScRAM3 osaIntNestingDepth            ;
osqScRAM0 extern osqScRAM1          osqScRAM2 TaskType    osqScRAM3 osaActiveTaskIndex            ;
osqScRAM0 extern osqScRAM1 volatile osqScRAM2 ISRType     osqScRAM3 osaActiveISRID                ;
osqScRAM0 extern osqScRAM1          osqScRAM2 osuint8     osqScRAM3 osaIntSaveDisableCounter      ;
osqScRAM0 extern osqScRAM1          osqScRAM2 osuint8     osqScRAM3 osaIntSaveDisableCounterGlobal;
osqScRAM0 extern osqScRAM1 volatile osqScRAM2 osuint8     osqScRAM3 osaSavedIntGlobal             ;
osqScRAM0 extern osqScRAM1 volatile osqScRAM2 osuint8     osqScRAM3 osaSavedIntGlobalNested       ;
osqScRAM0 extern osqScRAM1 volatile osqScRAM2 osuint8     osqScRAM3 osaIntAPIStatus               ; /* TR:SOSK22:0254 */
osqScRAM0 extern osqScRAM1          osqScRAM2 osIntLevelType osqScRAM3 osaSavedIntLevelNested     ;
osqScRAM0 extern osqScRAM1          osqScRAM2 ApplicationType osqScRAM3 osaActiveApplicationID;


extern const tsConfigBlockFixedLengthPart osConfigBlock;

/* KB begin osekHwSctxExternalDeclarations (overwritten) */
extern osuint8 osaOnAPIStack;
extern osuint32 osaIRQTable[96];

/* KB end osekHwSctxExternalDeclarations */
/* TR:SOSK22:0254 Start */
#define osSetIntAPIStatus(x) (osaIntAPIStatus = (x))
#define osIncIntAPIStatus()  (osaIntAPIStatus++    )
#define osDecIntAPIStatus()  (osaIntAPIStatus--    )
/* TR:SOSK22:0254 End */
/* Init-function for save context variables*/
osqFunc1 void osqFunc2 osInitSctx(void);

osqFunc1 void osqFunc2 osFillTaskStacks(void);
osqFunc1 void osqFunc2 osInitTaskStacks(void);
osqFunc1 osbool osqFunc2 osCheckInterruptsEnabled(void);
osqFunc1 osbool osqFunc2 osCheckInterruptsDisabled(void);
void osDisableGlobal(void);                 /* disable all interrupts, no nesting */
void osEnableGlobal(void);                  /* enable all interrupts, no nesting */
ProtectionReturnType ProtectionHook(StatusType Fatalerror); /* TR:SASR30:0387 */

extern void osDispatch(void);
void osSwitchToUserMode(void);
osuint16 osGetConfigBlockVersion(void);


/*-------------------------------------------------------------------------------*/
/* functions and macros for modifying the global interrupt flag of the used core */
/*-------------------------------------------------------------------------------*/
/* We support two levels here: 1 means interrupts globally enabled, 0 means globally disabled */
/* TR: SPMF89:0014 Start */ /* TR: SPMF89:0027 Start */
#define osDisableLevel()              osDisableGlobal()   
#define osEnableLevel()               osEnableGlobal()
/* TR: SPMF89:0014 End */ /* TR: SPMF89:0027 End */

/* KB begin osekHwSctxPrototypes (overwritten) */
extern void osSetupMPURegion(osuint8 regionNr, osuint32 baseAddr, osuint32 sizeCnf, osuint32 accessCtrl); /* implemented in asm */
extern void osStoreRegionSettings(osuint8 regionNr, osuint32 *baseAddr, osuint32 *sizeCnf, osuint32 *accessCnf); /* implemented in asm */
extern void osMPUDisable(void); /* implemented in asm */
extern void osMPUEnable(void); /* implemented in asm */
extern void osEnableHWVector(void);
extern void osDisableHWVector(void);
extern void osEnterSafeState(StatusType ErrorCode, osuint16 OSErrorCode);

/* The use of an unknown function pointer is intended here. */
extern void osCallNTF(NonTrustedFunctionIndexType FunctionIndex, NonTrustedFunctionParameterRefType FunctionParams, NonTrustedFunctionType fctAddr, osuint32 stackAddr); /* PRQA S 3672 */ /* implemented in asm */


extern void osAsmAssertFailed(osuint16 err);
extern void osSetMPUForOS(void);
extern void osSetMPUForTask(void);
extern void osSaveTaskMPUSettings(void);
extern void osRestoreTaskMPUSettings(void);
extern void osLeaveProtectedISR(void);
extern void osSystemStackOverflow(osuint16 cause);
extern void osPeripheralError(void);
extern void osIntNestingOverflow(void);
extern void osFillSystemStack(void);
extern void osInitSystemStack(void);
extern osStackUsageType osGetSupervisorStackUsage(void);
extern osStackUsageType osGetAPIStackUsage(void);

extern void osDisableGslobal(void);
extern void osInitISRs(void);

#pragma SWI_ALIAS(osSwitchToPrivMode, 0x83);
osuint32 osSwitchToPrivMode(void);
/* This macro defines the previously declared identifier and doesn't hide it. */
#define osSwitchToUserMode() __asm("   cps #010000b") /* PRQA S 3436 */

/* KB end osekHwSctxPrototypes */
extern osqFunc1 ProtectionReturnType osqFunc2 osProtectionHookWrapper(StatusType argErr);
extern osqFunc1 void osqFunc2 osHandleProtectionErrors(ProtectionReturnType proRet, StatusType Fatalerror);
extern osqFunc1 void osqFunc2 osStackOverflow(void);
extern osqFunc1 void osqFunc2 osShutdownHookWrapper(StatusType ErrorCode);
extern osqFunc1 void osqFunc2 osErrorHookWrapper(StatusType ErrorCode);
extern osqFunc1 void osqFunc2 osStartupHookWrapper(void);
extern osuint32 osEnterProtectedISR(osuint32 sp, osuint32 nestDepth);
extern osuint8 osCheckMPUAccess(osuint8* DestinationAddress);
extern ApplicationType osGetApplicationID(void);
extern osqFunc1 void osqFunc2 osInitialize(void); /* TR:SPMF05:0001 */

/*lint -restore re-enable messages*/

#endif/* double include preventer */

/* END OF HEADER osektype.h */

