/* Kernbauer Version: 1.16 Konfiguration: VStdLib Erzeugungsgangnummer: 1 */


/**********************************************************************************************************************
| Project Name: vstdlib library
|    File Name: vstdlib_ll.h
|
|  Description : Low level part of the implementation of standard Vector functions.
|                ARM core specific implementation.
|                               
|----------------------------------------------------------------------------------------------------------------------
|               C O P Y R I G H T
|----------------------------------------------------------------------------------------------------------------------
|   Copyright (c) by Vector Informatik GmbH.     All rights reserved.
|
|   This software is copyright protected and proprietary to 
|   Vector Informatik GmbH. Vector Informatik GmbH grants to you 
|   only those rights as set out in the license conditions. All 
|   other rights remain with Vector Informatik GmbH.
|
|----------------------------------------------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|----------------------------------------------------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ------------------------------------------------------------------------------
| Ml           Patrick Markl             Vector Informatik GmbH
| Fn           Matthias Fleischmann      Vector Informatik GmbH
| Ard          Thomas Arnold             Vector Informatik GmbH
| Hs           Hannes Haas               Vector Informatik GmbH
| Kk           Karol Kostolny            Vector Informatik GmbH
| Ces          Senol Cendere             Vector Informatik GmbH
| Pl           Georg Pfluegel            Vector Informatik GmbH
| Aj           Arthur Jendrusch          Vector Informatik GmbH
| Seg          Sebastian Gaertner        Vector Informatik GmbH
| Rna          Ruediger Naas             Vector Informatik GmbH
| Rse          Robert Schelkle           Vector Informatik GmbH
| Bmo          Bastian Molkenthin        Vector Informatik GmbH
|----------------------------------------------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|----------------------------------------------------------------------------------------------------------------------
| Date       Version   Author  Description
|----------  --------  ------  ----------------------------------------------------------------------------------------
| 2005-06-16  01.00.00    Ml     - Creation
| 2006-01-12  01.01.00    Ml     - no changes
| 2006-02-02  01.02.00    Fn     - added support for ARM7
| 2006-02-14  01.03.00    Ard    - add version history
| 2006-02-24  01.04.00    Ard    - add version scan comment
| 2006-03-06  01.05.00    Ard    - released HL version 2.05.00
| 2006-03-09  01.06.00    Ard    - remove unused prototypes (defaults from HL are used)
| 2006-03-23  01.07.00    Hs     - HL part updated
| 2006-06-26  01.08.00    Ard    - ESCAN00017417: Add IRQ functions for MAC7100
| 2006-07-31  01.09.00    Ard    - ESCAN00017420: Changes in vstdlib.kon
| 2006-08-23  01.10.00    Ard    - ESCAN00017421: Add IRQ functions for TMS470
| 2006-08-23  01.11.00    Ard    - ESCAN00017422: Support AVCCORE
| 2006-08-25  01.12.00    Ard    - ESCAN00017444: Support LPC2xxx
| 2006-10-30  01.13.00    Ard    - ESCAN00018191: Support MAC7100 GHS
| 2006-11-08  01.14.00    Ard    - ESCAN00018283: Support TMS470_DCAN
| 2007-01-15  01.15.00    Ard    - ESCAN00018932: Support new high level version (TMS470 - Texas Instruments/ARM)
| 2007-03-05  01.16.00    Ces    - ESCAN00019841: Support SAF7780_PELICAN with compiler Green Hills
| 2007-07-23  01.17.00    Ard    - ESCAN00021557: Interrupts won't be restored if compiler optimization is activated
| 2007-07-31  01.18.00    Ard    - ESCAN00021688: Modules using the macros defined by VStdLib to Restore/Disable IRQs 
|                                                   will not compile in THUMB mode
|                                - ESCAN00021915: Support GHS compiler for TMS470
| 2007-09-12  01.19.00    Ard    - ESCAN00022325: Save registers before using inline assembler (Texas Instruments)
|                                - ESCAN00022358: Fix interrupt handling for GHS compiler
| 2007-11-27  01.20.00    Ard    - ESCAN00023430: Add platform TMS320ARM
| 2008-07-10  01.21.00    Kk     - ESCAN00028311: Add platform Fujitsu MB86R0X for GNU compiler
|                         Ard    - ESCAN00030163: Support Omap derivative
| 2008-11-21  01.22.00    Ces    - ESCAN00031486: Support platform Freescale IMX
| 2009-01-28  01.23.00    Pl     - ESCAN00032648: Support ST30 GNU
| 2009-04-02  01.24.00    Fn     - ESCAN00034336: Support Mac7100 and ARM compiler
|                         Aj     - ESCAN00034775: Support TeleChips (TCC800x) and ARM compiler
| 2009-06-06  01.25.00    Seg    - ESCAN00036632: Support TI TMS470MSF542 derivative with ARM compiler
| 2009-10-23  01.26.00    Rna    - ESCAN00038742: Support STM32BXCAN derivative with ARM compiler
| 2010-07-13  01.27.00    Ces    - ESCAN00044028: Support IMX53 (Cortex A8) with GreenHills compiler
| 2010-08-27  01.28.00    Ht     - ESCAN00044915: Support Cortex M3 core with C_COMP_TMS470_DCAN
| 2011-03-04  01.29.00    Pl     - ESCAN00045901: Optimization of the different interrupt disable and restore functions
|                                - ESCAN00047518: Support AVNA with TI compiler
|                                - ESCAN00049098: Support TX03 with ARM compiler
|                                - ESCAN00045574: Processor mode is changed when function VStdSuspendAllInterrupts is called.
| 2011-07-13  01.30.00    Pl     - ESCAN00052181: Support global interrupt handling by application for the Tms320
| 2011-08-10  01.31.00    Pl     - ESCAN00052679: Support Fcr4 with GHS compiler
| 2011-09-01  01.32.00    Pl     - ESCAN00053194: Support LPC1768 with Keil compiler
| 2011-11-17  01.32.01    Pl     - ESCAN00054916: VStdLL_GlobalInterruptRestore with ARM compiler do not write the old
|                                                 saved value from localInterruptOldStatusPtr back
| 2012-01-30  01.33.00    Rse    - ESCAN00055780: Support IMX with QCC compiler (FlexCAN2 and FlexCAN3)
|                         Aj     - ESCAN00056135: Support Fujitsu Fm3 with Keil compiler
|                         Pl     - ESCAN00056477: Support LPC1768 with GHS Compiler
| 2012-03-14  01.33.01    Pl     - ESCAN00057576: in history there is the comment "Support Fujitsu Fm3 with Keil compiler"
|                                                 but C_COMP_KEIL_FM3_CCAN is missing in source
| 2012-05-02  01.34.00    Pl     - ESCAN00058670: Support for new platform ADUCM33x added
|                                                 Attention: release does not support disable / restore of global interrupt
| 2012-06-01  01.34.01    Pl     - ESCAN00058484: VStdLL_GlobalInterruptDisable override other RAM variables 
|                                                 (only if TI compiler is used with a Cortex M3 Prozessor)
| 2012-09-21  01.35.00    Pl     - ESCAN00061584: Add GNU compiler for IMX with FlexCAN3
|                                - ESCAN00062910: Add C_COMP_TI_TMS320ARM_DCAN
| 2012-12-06  01.36.00    Rna    - ESCAN00063573: Add support C_COMP_IAR_STM32_BXCAN
|                         Pl     - ESCAN00063681: Add support C_COMP_QCC_TMS320ARM_DCAN
| 2013-01-10  01.37.00    Bmo    - ESCAN00065147: Add C_COMP_KEIL_TLE986X
| 2013-02-28  02.00.00    Pl     - ESCAN00065474: Update to core version 03.07.00 (support of compiler abstraction and CFG5)
|                                - ESCAN00064251: Override other RAM variables and Interrupt locking doesn't work 
|                                                 (only if TI compiler and Cortex M3)
| 2013-08-20  02.01.00    Pl     - ESCAN00069915: Add C_COMP_ARM_STA8088_CCAN
| 2013-09-17  02.02.00    Rse    - ESCAN00070453: Support Vybrid with GNU compiler
| 2013-10-24  02.02.01    Pl     - ESCAN00071399: Add file vstdlib_lib.asm into content
|********************************************************************************************************************/

/**********************************************************************************************************************
|
| Project Name : vstdlib library
|    File Name : vstdlib_HL.h
|
|  Description : Highlevel part of the implementation of standard Vector functions
|                               
|----------------------------------------------------------------------------------------------------------------------
|               C O P Y R I G H T
|----------------------------------------------------------------------------------------------------------------------
|   Copyright (c) by Vector Informatik GmbH.     All rights reserved.
|
|   This software is copyright protected and proprietary to 
|   Vector Informatik GmbH. Vector Informatik GmbH grants to you 
|   only those rights as set out in the license conditions. All 
|   other rights remain with Vector Informatik GmbH.
|
|----------------------------------------------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|----------------------------------------------------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ------------------------------------------------------------------------------
| Ml           Patrick Markl             Vector Informatik GmbH
| HH           Hartmut Hoerner           Vector Informatik GmbH
| Ms           Gunnar Meiss              Vector Informatik GmbH
| Et           Thomas Ebert              Vector Informatik GmbH
| Bus          Sabine Buecherl           Vector Informatik GmbH
| Hs           Hannes Haas               Vector Informatik GmbH
| BWR          Brandon Root              Vector CANtech Inc.
| Ard          Thomas Arnold             Vector Informatik GmbH
| Tvi          Timo Vanoni               Vector Informatik GmbH
|----------------------------------------------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|----------------------------------------------------------------------------------------------------------------------
| Date       Version   Author  Description
|----------  --------  ------  ----------------------------------------------------------------------------------------
|2003-09-06  00.01.00    Ml     - Creation
|                        Ml     - Added HC12 Cosmic
|2003-10-07  00.02.00    Ml/HH  - v_lib input merged
|2004-04-10  00.03.00    Ml     - Added headerfile
|                        Ml     - Added HC08 Cosmic
|                        Ml     - removed channel dependence for assertions
|                        Ml     - Added function to retrieve the IRQ state
|                        Ml     - Added VSTD_FULL_LIB_SUPPORT switch
|2004-04-27  01.00.00    Ml     - resolved issues found in code inspection
|2004-05-17  01.01.00    Ml     - no changes
|                        Ml     - changed bugfix into releaseversion
|2004-05-18  01.02.00    Ms/HH  - changed memory qualifier concept
|2004-06-01  01.03.00    Ml     - no changes
|2004-08-06  01.04.00    Ml     - Added macros for local IRQ disable
|                               - Split of library into HL and LL
|2004-08-18  01.05.00    Ml     - Added function qualifier
|2004-09-06  01.06.00    Ml     - ESCAN00009316: fixed parameter type mismatch
|2004-09-27  01.07.00    Ml     - changed memcpy macros
|                        Ml     - changed namingconvention
|2004-09-29  01.08.00    Et     - ESCAN00009692: split VStdMemCpy in VStdRamMemCpy and VStdRomMemCpy   
|2004-10-01  01.09.00    Ml     - ESCAN00009731: usage of standard type qualifiers
|2004-10-26  01.10.00    Ml     - ESCAN00010000: LL parts are split into HW specific files
|2004-11-09  01.11.00    Ml     - no changes
|2004-11-15  01.12.00    Ml     - ESCAN00010533: Added optimized memory functions for HC08
|                        Ml     - ESCAN00010672: Added memory qualifier
|2005-01-24  01.13.00    Ml     - ESCAN00010670: Added memset
|2005-02-25  01.14.00    Ml     - ESCAN00011215  Added VStdInitPowerOn
|2005-04-26  01.15.00    Ml     - ESCAN00012047: Encapsulate VStdInitPowerOn
|            01.16.00    Ml     - ESCAN00012105: Change definition of VStdMemCpy
|2005-05-30  02.00.00    Ml     - ESCAN00013446: Development concept changed
|2005-09-12  02.01.00    Ml     - ESCAN00013512: Fixed Misra warnings
|2005-11-06  02.02.00    Ml     - ESCAN00014183: no changes
|2005-11-28  02.03.00    Ml     - Changed version defines
|                        Ml     - ESCAN00014428: VStdMemClr/Set are now internal functions
|                        Ml     - ESCAN00014409: Added casts for mem function defines
|2005-12-12  02.04.00    Ml/Bus - ESCAN00012774: insert comments for different resource categories
|2006-01-12  02.05.00    Ml     - ESCAN00014897: Changed interrupt handling
|2006-01-14  02.06.00    Ml     - ESCAN00014908: Adapted interrupt control handling for RI1.5
|2006-02-07  02.07.00    Ml     - Added VStdGetInterruptState
|                        Hs     - ESCAN00015802: compatibility defines added
|2006-05-09  02.08.00    Ces    - ESCAN00016289: Insert memory qualifier V_MEMROM3 to VStdRomMemCpy()
|2006-05-24  02.09.00    BWR    - ESCAN00016488: Compiler error in VStdSuspendAllInterrupts and VStdResumeAllInterrupts
|2006-07-16  02.10.00    Ml     - Changed return type of VStdGetInterruptState from uint8 to tVStdIrqStateType
|2006-07-31  02.11.00    Ml     - ESCAN00017133: Changed assertion handling
|2006-08-04  02.12.00    Ml     - ESCAN00017188: Added compatibility for older copy functions
|2006-11-20  02.13.00    Ml     - Removed VStdGetInterruptState
|2006-12-07  02.14.00    Ml     - Changed switch names
|                        Ml     - ESCAN00018889: Fixed code inspection report findings
|                               - ESCAN00018880: added casts to memXXX macros
|2007-01-27  02.15.00    Ml,Ard - ESCAN00019251: VStdLib HL usable for RI1.4 and RI1.5
|2007-02-19  02.16.00    Ml     - ESCAN00019672: no changes
|                        Ml     - ESCAN00019674: Changed names of interrupt lock macros
|2007-05-10  02.17.00    Ml     - ESCAN00020705: no changes
|                        Ml     - ESCAN00020241: Cast of length parameter
|2007-11-26  03.00.00    Ml     - ESCAN00024126: Support word and dword copy routines
|                        Ml     - ESCAN00024192: Default and specific implementations supported at the same time
|2008-06-25  03.01.00    Ml     - ESCAN00023334: Added u suffix to the version numbers
|                        Ml     - ESCAN00018659: No changes
|                        Ml     - ESCAN00015501: Added compatibility to older version defines   
|2008-07-17  03.01.01    Ml     - ESCAN00027617: Added library version check support
|2008-07-23  03.02.00    Ml     - ESCAN00028605: old interrupt status is initialized by low level token
|2008-07-27  03.02.01    Ml     - ESCAN00028752: Include of MSR header according to naming convention
|2008-08-13  03.03.00    Ml     - ESCAN00029196: Encapsulated AUTOSAR library version check
|2008-12-08  03.03.01    Ml     - ESCAN00031855: Additional memcpy interfaces
|2009-06-30  03.04.00    Ml     - ESCAN00036089: Application must care about nested calls in case of user handling of locks
|                        Ml     - ESCAN00035049: Resolved extended version check include
|2009-10-15  03.05.00    Ml     - ESCAN00038482: Added additional function qualifier (VSTD_API_2)
|                        Ml     - ESCAN00038485: Added general OS header include.
|2009-10-19  03.05.01    Ml     - ESCAN00038485: Renamed the OS header include according to osCAN
|2010-01-21  03.06.00    Tvi    - ESCAN00040103: [AUTOSAR] Add support for compiler abstraction
|2011-09-01  03.06.01    Tvi    - ESCAN00052664: [MSR only] "upper/lower case" issue @ #include compiler/memory abstraction
|2012-06-20  03.07.00    Tvi    - ESCAN00058623: AR4-170: support VStdLib with CFG5 MSR4 R5
|*********************************************************************************************************************/

#if !defined(_VSTDLIB_H_)
# define _VSTDLIB_H_

/* Include the configuration for vstdlib */
# include "v_cfg.h"


/* Encapsulation of AUTOSAR library check */
#if defined(VGEN_ENABLE_GW_ASRPDUR)
# define VSTD_ENABLE_MSR_LIB_VERSION_CHECK
# define VSTD_ENABLE_API_AUTOSAR
#endif

#if defined (VSTD_ENABLE_API_AUTOSAR)
/* If MICROSAR is used, several headers are needed */
# include "Std_Types.h"
# include "Compiler_Cfg.h"
# include "Compiler.h"
#else
# include "v_def.h"
#endif

/* Includes required in the header file */

/*********************************************************************************************************************/
/* Defines                                                                                                           */
/*********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : VStdLib_Arm7 CQComponent : Implementation */
#define VSTDLIB_ARM7_VERSION           0x0202u
#define VSTDLIB_ARM7_RELEASE_VERSION   0x01u

/* ##V_CFG_MANAGEMENT ##CQProject : VStdLib__coreHll CQComponent : Implementation */
# define VSTDLIB__COREHLL_VERSION         0x0307u
# define VSTDLIB__COREHLL_RELEASE_VERSION 0x00u

/* Introduced for comparibility with older VStdLib versions */
# define COMMON_VSTDLIB_VERSION             VSTDLIB__COREHLL_VERSION
# define COMMON_VSTDLIB_RELEASE_VERSION     VSTDLIB__COREHLL_RELEASE_VERSION

#if defined (V_COMP_GHS)
# if defined(VSTD_ENABLE_DEFAULT_INTCTRL)
#  include <arm_ghs.h>
# endif
#endif

#if defined (VSTD_ENABLE_FIQ_INTCTRL)
# define kIrqIbitMask  ((vuint32)0x000000C0)
#else    
# define kIrqIbitMask  ((vuint32)0x00000080)
#endif

#if defined (V_COMP_GNU_VYBRID)
# if !defined( VSTD_ENABLE_CLEAR_INSTRUCTION_PIPE ) && !defined( VSTD_DISABLE_CLEAR_INSTRUCTION_PIPE )
#  define VSTD_ENABLE_CLEAR_INSTRUCTION_PIPE
# endif
#endif


/* Compatibility defines */
# if !defined(VSTD_API_0)
#  define VSTD_API_0
# endif

# if !defined(VSTD_API_1)
#  define VSTD_API_1
# endif

# if !defined(VSTD_API_2)
#  define VSTD_API_2
# endif

# if !defined(VSTD_CALLBACK_0)
#  define VSTD_CALLBACK_0
# endif

# if !defined(VSTD_CALLBACK_1)
#  define VSTD_CALLBACK_1
# endif

# if !defined(VSTD_NONE)
#  define VSTD_NONE
# endif

/* MICROSAR compatibility */
# if defined(VSTD_ENABLE_API_AUTOSAR)

#  if !defined(VSTD_USE_MEMORY_MACROS)
#   define VSTD_USE_MEMORY_MACROS STD_OFF
#  endif

# endif


/* Memory abtraction layer */
# if defined(VSTD_ENABLE_API_AUTOSAR)
#  if !defined(VSTDLIB_AUTOMATIC)
#    define VSTDLIB_AUTOMATIC AUTOMATIC
#  endif
#  if !defined(V_NULL)
#   define V_NULL NULL_PTR
#  endif

#  define VSTD_DEF_VAR(storage, vartype, memclass)                    storage VAR(vartype, VSTDLIB_##memclass)
#  define VSTD_DEF_VAR_TYPE(storage, vartype)                         typedef storage VAR(vartype, TYPEDEF)
#  define VSTD_DEF_P2VAR(storage, ptrtype, memclass, ptrclass)        storage P2VAR(ptrtype, VSTDLIB_##memclass, VSTDLIB_##ptrclass)
#  define VSTD_DEF_P2VAR_TYPE(storage, ptrtype, ptrclass)             typedef storage P2VAR(ptrtype, TYPEDEF, VSTDLIB_##ptrclass)
#  define VSTD_DEF_P2VAR_PARA(storage, ptrtype, memclass, ptrclass)   storage P2VAR(ptrtype, VSTDLIB_##memclass, VSTDLIB_##ptrclass)
#  define VSTD_DEF_CONSTP2VAR(storage, ptrtype, memclass, ptrclass)   storage CONSTP2VAR(ptrtype, VSTDLIB_##memclass, VSTDLIB_##ptrclass)
#  define VSTD_DEF_CONST(storage, vartype, memclass)                  storage CONST(vartype, VSTDLIB_##memclass)
#  define VSTD_DEF_CONST_TYPE(storage, vartype)                       typedef storage CONST(vartype, TYPEDEF)
#  define VSTD_DEF_P2CONST(storage, ptrtype, memclass, ptrclass)      storage P2CONST(ptrtype, VSTDLIB_##memclass, VSTDLIB_##ptrclass)
#  define VSTD_DEF_P2CONST_TYPE(storage, ptrtype, ptrclass)           typedef storage P2CONST(ptrtype, TYPEDEF, VSTDLIB_##ptrclass)
#  define VSTD_DEF_P2CONST_PARA(storage, ptrtype, memclass, ptrclass) storage P2CONST(ptrtype, VSTDLIB_##memclass, VSTDLIB_##ptrclass)
#  define VSTD_DEF_CONSTP2CONST(storage, ptrtype, memclass, ptrclass) storage CONSTP2CONST(ptrtype, VSTDLIB_##memclass, VSTDLIB_##ptrclass)
#  define VSTD_DEF_FUNC(storage, rettype, memclass)                   storage FUNC(rettype, VSTDLIB_##memclass)
#  define VSTD_DEF_FUNC_API(storage, rettype, memclass)               storage FUNC(rettype, VSTDLIB_##memclass)
#  define VSTD_DEF_FUNC_CBK(storage, rettype, memclass)               storage FUNC(rettype, VSTDLIB_##memclass)

# else /* VSTD_ENABLE_API_AUTOSAR */

#  define VSTD_DEF_VAR(storage, vartype, memclass)                    V_MEMRAM0 storage V_MEMRAM1 vartype V_MEMRAM2
#  define VSTD_DEF_VAR_TYPE(storage, vartype)                         typedef storage V_MEMRAM1 vartype V_MEMRAM2
#  define VSTD_DEF_P2VAR(storage, ptrtype, memclass, ptrclass)        V_MEMRAM0 storage V_MEMRAM1 ptrtype V_MEMRAM2 *
#  define VSTD_DEF_P2VAR_TYPE(storage, ptrtype, ptrclass)             typedef storage V_MEMRAM1 ptrtype V_MEMRAM2 *
#  define VSTD_DEF_P2VAR_PARA(storage, ptrtype, memclass, ptrclass)   storage V_MEMRAM1 ptrtype V_MEMRAM2 *
#  define VSTD_DEF_CONSTP2VAR(storage, ptrtype, memclass, ptrclass)   V_MEMROM0 storage V_MEMRAM1 ptrtype V_MEMRAM2 V_MEMRAM3 * V_MEMROM1 V_MEMROM2
#  define VSTD_DEF_CONST(storage, vartype, memclass)                  V_MEMROM0 storage V_MEMROM1 vartype V_MEMROM2
#  define VSTD_DEF_CONST_TYPE(storage, vartype)                       typedef storage V_MEMROM1 vartype V_MEMROM2
#  define VSTD_DEF_P2CONST(storage, ptrtype, memclass, ptrclass)      V_MEMRAM0 storage V_MEMROM1 ptrtype V_MEMROM2 V_MEMROM3 * V_MEMRAM1 V_MEMRAM2
#  define VSTD_DEF_P2CONST_TYPE(storage, ptrtype, ptrclass)           typedef storage V_MEMROM1 ptrtype V_MEMROM2 V_MEMROM3 *
#  define VSTD_DEF_P2CONST_PARA(storage, ptrtype, memclass, ptrclass) storage V_MEMROM1 ptrtype V_MEMROM2 V_MEMROM3 * V_MEMRAM1 V_MEMRAM2
#  define VSTD_DEF_CONSTP2CONST(storage, ptrtype, memclass, ptrclass) V_MEMROM0 storage V_MEMROM1 ptrtype V_MEMROM2 V_MEMROM3 * V_MEMROM1 V_MEMROM2
#  define VSTD_DEF_FUNC(storage, rettype, memclass)                   storage rettype
#  define VSTD_DEF_FUNC_API(storage, rettype, memclass)               VSTD_API_0 storage VSTD_API_1 rettype
#  define VSTD_DEF_FUNC_CBK(storage, rettype, memclass)               storage VSTD_CALLBACK_0 rettype VSTD_CALLBACK_1

# endif


/* Types abstraction layer */
# if defined(VSTD_ENABLE_API_AUTOSAR) 
#  if !defined(vuint8)
#   define vuint8 uint8
#  endif
#  if !defined(vuint16)
#   define vuint16 uint16
#  endif
#  if !defined(vuint32)
#   define vuint32 uint32
#  endif
#  if !defined(vsint8)
#   define vsint8 sint8
#  endif
#  if !defined(vsint16)
#   define vsint16 sint16
#  endif
#  if !defined(vsint32)
#   define vsint32 sint32
#  endif
# endif



#  if defined(VSTD_ENABLE_DEFAULT_INTCTRL) || \
      defined(VSTD_ENABLE_OSEK_INTCTRL)    || \
      defined(VSTD_ENABLE_APPL_INTCTRL)
#   define VSTD_ENABLE_INTCTRL_HANDLING
#   define VSTD_HL_ENABLE_SUPPORT_IRQ_FCT  /* compatibility for Autosar */
#   define VSTD_ENABLE_SUPPORT_IRQ_FCT
#  else
#   define VSTD_DISABLE_INTCTRL_HANDLING
#   define VSTD_HL_DISABLE_SUPPORT_IRQ_FCT  /* compatibility for Autosar */
#   define VSTD_DISABLE_SUPPORT_IRQ_FCT
#  endif

# if !defined(VSTD_ENABLE_LIBRARY_FUNCTIONS) && !defined(VSTD_DISABLE_LIBRARY_FUNCTIONS)
#  define VSTD_ENABLE_LIBRARY_FUNCTIONS
# endif


/*********************************************************************************************************************/
/* Error codes for assertions                                                                                        */
/*********************************************************************************************************************/
# define kVStdErrorIntDisableTooOften        ((vuint8)0x01)
# define kVStdErrorIntRestoreTooOften        ((vuint8)0x02)
# define kVStdErrorMemClrInvalidParameter    ((vuint8)0x03)
# define kVStdErrorMemCpyInvalidParameter    ((vuint8)0x04)
# define kVStdErrorFunctionNotSupportedByHw  ((vuint8)0x05)
# define kVStdErrorMemSetInvalidParameter    ((vuint8)0x06)
# define kVStdErrorUnexpectedLockState       ((vuint8)0x07)


/*********************************************************************************************************************/
/* Plattforms with optimized VStdLib support                                                                         */
/*********************************************************************************************************************/
#define VSTD_HL_DISABLE_SUPPORT_MEM_FCT
#define VSTD_HL_DISABLE_MEM_FCT_MAPPING 

/* in case of the standard implementation enable all functions */
#if defined(VSTD_HL_ENABLE_MEM_FCT_MAPPING)
#else
# define VSTD_HL_USE_VSTD_MEMCLR
# define VSTD_HL_USE_VSTD_MEMSET
# define VSTD_HL_USE_VSTD_RAMMEMCPY
# define VSTD_HL_USE_VSTD_ROMMEMCPY
# define VSTD_HL_USE_VSTD_WORD_MEMCPY
# define VSTD_HL_USE_VSTD_DWORD_MEMCPY
#endif


/*********************************************************************************************************************/
/* Version check                                                                                                     */
/*********************************************************************************************************************/
# if defined(VSTD_ENABLE_API_AUTOSAR)
#  define VSTDLIB_START_SEC_CONST_UNSPECIFIED
#  include "MemMap.h"
# endif

/* ROM CATEGORY 4 START*/
VSTD_DEF_CONST(extern, vuint8, CONST) kVStdMainVersion;
VSTD_DEF_CONST(extern, vuint8, CONST) kVStdSubVersion;
VSTD_DEF_CONST(extern, vuint8, CONST) kVStdReleaseVersion;
/* ROM CATEGORY 4 END*/

# if defined(VSTD_ENABLE_API_AUTOSAR)
#  define VSTDLIB_STOP_SEC_CONST_UNSPECIFIED
#  include "MemMap.h"
# endif


/*********************************************************************************************************************/
/* Function like macros                                                                                              */
/*********************************************************************************************************************/
#if defined (V_COMP_ARM)
# if defined( VSTD_ENABLE_CLEAR_INSTRUCTION_PIPE )
#  define VSTD_CLEAR_INSTRUCTION_PIPE()  __asm {NOP                              \
                                                NOP                              \
                                                NOP                              \
                                                NOP                              \
                                                NOP                              \
                                                NOP                              \
                                                NOP}
# else
#  define VSTD_CLEAR_INSTRUCTION_PIPE()
# endif                                           
#endif                                           

#if defined (V_COMP_GHS)
# if !defined (__CortexM3)

#  if defined( VSTD_ENABLE_CLEAR_INSTRUCTION_PIPE )
#   define VStdLL_GlobalInterruptDisable(localInterruptOldStatusPtr)             \
{                                                                                \
  *(localInterruptOldStatusPtr) = __GETSR() & (vuint32)kIrqIbitMask;             \
  __SETSR(__GETSR() | kIrqIbitMask);                                             \
    __asm(" NOP ");                                                              \
    __asm(" NOP ");                                                              \
    __asm(" NOP ");                                                              \
    __asm(" NOP ");                                                              \
    __asm(" NOP ");                                                              \
    __asm(" NOP ");                                                              \
    __asm(" NOP ");                                                              \
}
#  else                                           
#   define VStdLL_GlobalInterruptDisable(localInterruptOldStatusPtr)             \
{                                                                                \
  *(localInterruptOldStatusPtr) = __GETSR() & (vuint32)kIrqIbitMask;             \
  __SETSR(__GETSR() | kIrqIbitMask);                                             \
}
#  endif

#  define VStdLL_GlobalInterruptRestore(localInterruptOldStatus)                 \
{                                                                                \
  __SETSR((__GETSR() & (vuint32)~kIrqIbitMask) | localInterruptOldStatus);       \
}

# endif
#endif

#if defined (V_COMP_TI) 
# if !defined (__TI_TMS470_V7M3__)

#  if defined( VSTD_ENABLE_CLEAR_INSTRUCTION_PIPE )
#   define VStdLL_GlobalInterruptDisable(localInterruptOldStatusPtr)             \
{                                                                                \
  *(localInterruptOldStatusPtr) = _get_CPSR() & kIrqIbitMask;                    \
  _set_CPSR(_get_CPSR() | kIrqIbitMask);                                         \
  __asm(" NOP");                                                                 \
  __asm(" NOP");                                                                 \
  __asm(" NOP");                                                                 \
  __asm(" NOP");                                                                 \
  __asm(" NOP");                                                                 \
  __asm(" NOP");                                                                 \
  __asm(" NOP");                                                                 \
}
#  else
#   define VStdLL_GlobalInterruptDisable(localInterruptOldStatusPtr)             \
{                                                                                \
  *(localInterruptOldStatusPtr) = _get_CPSR() & kIrqIbitMask;                    \
  _set_CPSR(_get_CPSR() | kIrqIbitMask);                                         \
}
#  endif

#  define VStdLL_GlobalInterruptRestore(localInterruptOldStatus)                 \
{                                                                                \
  _set_CPSR((_get_CPSR() & ~kIrqIbitMask) | localInterruptOldStatus);            \
}

# endif 
#endif

#if defined (V_COMP_IAR)
# if  ( ((__TID__ >> 4) & 0x0F) != 0x06 )

#  if defined( VSTD_ENABLE_CLEAR_INSTRUCTION_PIPE )
#   define VStdLL_GlobalInterruptDisable(localInterruptOldStatusPtr)             \
{                                                                                \
  *(localInterruptOldStatusPtr) = __get_CPSR() & (vuint32)kIrqIbitMask;          \
  __set_CPSR(__get_CPSR() | kIrqIbitMask);                                       \
  __asm(" nop");                                                                 \
  __asm(" nop");                                                                 \
  __asm(" nop");                                                                 \
  __asm(" nop");                                                                 \
  __asm(" nop");                                                                 \
  __asm(" nop");                                                                 \
  __asm(" nop");                                                                 \
}
#  else
#   define VStdLL_GlobalInterruptDisable(localInterruptOldStatusPtr)             \
{                                                                                \
  *(localInterruptOldStatusPtr) = __get_CPSR() & (vuint32)kIrqIbitMask;          \
  __set_CPSR(__get_CPSR() | kIrqIbitMask);                                       \
}
#  endif

#  define VStdLL_GlobalInterruptRestore(localInterruptOldStatus)                 \
{                                                                                \
  __set_CPSR((__get_CPSR() & (vuint32)~kIrqIbitMask) | localInterruptOldStatus); \
}

# endif
#endif

#if defined( V_COMP_GNU ) || defined ( V_COMP_QCC )
# if defined( VSTD_ENABLE_CLEAR_INSTRUCTION_PIPE )
#  define VSTD_CLEAR_INSTRUCTION_PIPE()  __asm volatile ("NOP; \n                \
                                                          NOP; \n                \
                                                          NOP; \n                \
                                                          NOP; \n                \
                                                          NOP; \n                \
                                                          NOP; \n                \
                                                          NOP")
# else
#  define VSTD_CLEAR_INSTRUCTION_PIPE()                                                           
# endif
#endif


/*********************************************************************************************************************/
/* Types                                                                                                             */
/*********************************************************************************************************************/
typedef volatile vuint32 tVStdIrqStateType;

/*********************************************************************************************************************/
/* Defines                                                                                                           */
/*********************************************************************************************************************/
#  if defined(VSTD_ENABLE_INTCTRL_HANDLING)
#   if defined(VSTD_ENABLE_DEFAULT_INTCTRL)
#    define VStdDeclareGlobalInterruptOldStatus     tVStdIrqStateType localInterruptOldStatus;
#    define VStdPutGlobalInterruptOldStatus(x)      (localInterruptOldStatus = (x))
#    define VStdGetGlobalInterruptOldStatus(x)      ((x) = localInterruptOldStatus)
#    define VStdGlobalInterruptDisable()            VStdLL_GlobalInterruptDisable(&localInterruptOldStatus)
#    define VStdGlobalInterruptRestore()            VStdLL_GlobalInterruptRestore(localInterruptOldStatus)
#   elif defined(VSTD_ENABLE_OSEK_INTCTRL)
#    define VStdDeclareGlobalInterruptOldStatus
#    define VStdPutGlobalInterruptOldStatus(x)
#    define VStdGetGlobalInterruptOldStatus(x)
#    if defined(osdOSEK2_1)
#     define VStdGlobalInterruptDisable()           OsSaveDisableGlobalNested()
#     define VStdGlobalInterruptRestore()           OsRestoreEnableGlobalNested()
#     define VStdSuspendAllInterrupts()             OsSaveDisableGlobalNested()
#     define VStdResumeAllInterrupts()              OsRestoreEnableGlobalNested()
#    else
#     define VStdGlobalInterruptDisable()           SuspendAllInterrupts()
#     define VStdGlobalInterruptRestore()           ResumeAllInterrupts()
#     define VStdSuspendAllInterrupts()             SuspendAllInterrupts()
#     define VStdResumeAllInterrupts()              ResumeAllInterrupts()
#    endif
#   elif defined(VSTD_ENABLE_APPL_INTCTRL)
#    define VStdDeclareGlobalInterruptOldStatus
#    define VStdPutGlobalInterruptOldStatus(x)
#    define VStdGetGlobalInterruptOldStatus(x)
#    define VStdGlobalInterruptDisable()           VStdUserNestedDisable()
#    define VStdGlobalInterruptRestore()           VStdUserNestedRestore()
#    define VStdSuspendAllInterrupts()             VStdUserNestedDisable()
#    define VStdResumeAllInterrupts()              VStdUserNestedRestore()
#   else
#    error "Please check VStdLib interrupt configuration!"
#   endif
#   define VStdNestedGlobalInterruptDisable() VStdGlobalInterruptDisable()
#   define VStdNestedGlobalInterruptRestore() VStdGlobalInterruptRestore()
#  endif

# if defined(VSTD_ENABLE_API_AUTOSAR)
/* For AUTOSAR, mem mapping has to be disabled */

/* Default implementaion of macros */
#  if !defined(VStdMemCpy_Macro)
#   define VStdMemCpy_Macro(dst, src, len)  { uint16_least __i; for ( __i = 0x00u; __i < (len); ++__i) { (dst)[__i] = (src)[__i]; } }
#  endif

#  if !defined(VStdMemSet_Macro)
#   define VStdMemSet_Macro(dst, val, len)  { uint16_least __i; for ( __i = 0x00u; __i < (len); ++__i) { (dst)[__i] = (val); } }
#  endif

#  if !defined(VStdMemClr_Macro)
#   define VStdMemClr_Macro(dst, len)       { uint16_least __i; for ( __i = 0x00u; __i < (len); ++__i) { (dst)[__i] = 0x00u; } }
#  endif

#  if !defined(VStdMemCpyRom_Macro)
#   define VStdMemCpyRom_Macro VStdMemCpy_Macro
#  endif

/* Set the default copy macros either to macros or to functions */
#  if (VSTD_USE_MEMORY_MACROS == STD_ON)
#   define VStdMemCpy(dst, src, len)            VStdMemCpy_Macro((dst), (src), (len))
#   define VStdMemCpy16(dst, src, len)          VStdMemCpy_Macro((dst), (src), (len))
#   define VStdMemCpy32(dst, src, len)          VStdMemCpy_Macro((dst), (src), (len))
#   define VStdMemSet(dst, val, len)            VStdMemSet_Macro((dst), (val), (len))
#   define VStdMemClr(dst, len)                 VStdMemClr_Macro((dst), (len))
#   define VStdMemCpyRom(dst, src, len)         VStdMemCpyRom_Macro((dst), (src), (len))
#  else
#   define VStdMemCpy(dst, src, len)            VStdMemCpy_Func(  (VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint8, AUTOMATIC, VAR_FAR))(dst), (VSTD_DEF_P2CONST_PARA(VSTD_NONE, vuint8, AUTOMATIC, VAR_FAR))(src), (len))
#   define VStdMemCpy16(dst, src, len)          VStdMemCpy16_Func((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint16, AUTOMATIC, VAR_FAR))(dst), (VSTD_DEF_P2CONST_PARA(VSTD_NONE, vuint16, AUTOMATIC, VAR_FAR))(src), (len))
#   define VStdMemCpy32(dst, src, len)          VStdMemCpy32_Func((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint32, AUTOMATIC, VAR_FAR))(dst), (VSTD_DEF_P2CONST_PARA(VSTD_NONE, vuint32, AUTOMATIC, VAR_FAR))(src), (len))
#   define VStdMemSet(dst, val, len)            VStdMemSet_Func(  (VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint8, AUTOMATIC, VAR_FAR))(dst), (val), (len))
#   define VStdMemClr(dst, len)                 VStdMemClr_Func(  (VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint8, AUTOMATIC, VAR_FAR))(dst), (len))   
#     define VStdMemCpyRom(dst, src, len)       VStdMemCpy_Func(  (VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint8, AUTOMATIC, VAR_FAR))(dst), (VSTD_DEF_P2CONST_PARA(VSTD_NONE, vuint8, AUTOMATIC, CONST_FAR))(src), (len))
#  endif /* VSTD_USE_MEMORY_MACROS */


/* Mapping for compatibility reasons */
/* memset abstraction */
#   define VStdMemNearSet(d, p, l)              VStdMemSet((d), (p), (l))
#   define VStdMemFarSet(d, p, l)               VStdMemSet((d), (p), (l))

/* memclr abstraction */
#   define VStdMemNearClr(d, l)                 VStdMemClr((d), (l))
#   define VStdMemFarClr(d, l)                  VStdMemClr((d), (l))

/* memcpy abstraction */
#   define VStdMemCpyRamToRam(d, s, l)          VStdMemCpy((d), (s), (l))
#   define VStdMemCpyRomToRam(d, s, l)          VStdMemCpyRom((d), (s), (l))
#   define VStdMemCpyRamToNearRam(d, s, l)      VStdMemCpy((d), (s), (l))
#   define VStdMemCpyRomToNearRam(d, s, l)      VStdMemCpyRom((d), (s), (l))
#   define VStdMemCpyRomToFarRam(d, s, l)       VStdMemCpyRom((d), (s), (l))
#   define VStdMemCpyRamToFarRam(d, s, l)       VStdMemCpy((d), (s), (l))
#   define VStdMemCpyFarRamToRam(d, s, l)       VStdMemCpy((d), (s), (l))
#   define VStdMemCpyFarRamToFarRam(d, s, l)    VStdMemCpy((d), (s), (l))
#   define VStdMemCpyFarRomToFarRam(d, s, l)    VStdMemCpyRom((d), (s), (l))

#    define VStdMemCpy16RamToRam(d, s, l)       VStdMemCpy16((d), (s), (l))
#    define VStdMemCpy16RamToFarRam(d, s, l)    VStdMemCpy16((d), (s), (l))
#    define VStdMemCpy16FarRamToRam(d, s, l)    VStdMemCpy16((d), (s), (l))

#    define VStdMemCpy32RamToRam(d, s, l)       VStdMemCpy32((d), (s), (l))
#    define VStdMemCpy32RamToFarRam(d, s, l)    VStdMemCpy32((d), (s), (l))
#    define VStdMemCpy32FarRamToRam(d, s, l)    VStdMemCpy32((d), (s), (l))




# else /* VSTD_ENABLE_API_AUTOSAR */
#  if defined(VSTD_HL_ENABLE_MEM_FCT_MAPPING)
/* define hardware specific mappings of memcpy etc. */
#  else /* VSTD_HL_ENABLE_MEM_FCT_MAPPING */

/* per default all memclr and memcpy functions are mapped on one routine which
   does not support different memory models */
/* memset abstraction */
#   define VStdMemSet(d, p, l)                 VStdMemSetInternal((void*)(d), (p), (vuint16)(l))
#   define VStdMemNearSet(d, p, l)             VStdMemSetInternal((void*)(d), (p), (vuint16)(l))
#   define VStdMemFarSet(d, p, l)              VStdMemSetInternal((void*)(d), (p), (vuint16)(l))

/* memclr abstraction */
#   define VStdMemClr(d, l)                    VStdMemClrInternal((void*)(d), (vuint16)(l))
#   define VStdMemNearClr(d, l)                VStdMemClrInternal((void*)(d), (vuint16)(l))
#   define VStdMemFarClr(d, l)                 VStdMemClrInternal((void*)(d), (vuint16)(l))

/* memcpy abstraction */
#   define VStdMemCpyRamToRam(d, s, l)         VStdRamMemCpy((void*)(d), (void*)(s), (vuint16)(l))
#   define VStdMemCpyRomToRam(d, s, l)         VStdRomMemCpy((void*)(d), (V_MEMROM1 void V_MEMROM2 V_MEMROM3 *)(s), (vuint16)(l))

#   define VStdMemCpyRamToNearRam(d, s, l)     VStdRamMemCpy((d), (void*)(s), (l))
#   define VStdMemCpyRomToNearRam(d, s, l)     VStdRomMemCpy((d), (V_MEMROM1 void V_MEMROM2 V_MEMROM3 *)(s), (vuint16)(l))

#   define VStdMemCpyRomToFarRam(d, s, l)      VStdRomMemCpy((d), (V_MEMROM1 void V_MEMROM2 V_MEMROM3 *)(s), (vuint16)(l))

#   define VStdMemCpyRamToFarRam(d, s, l)      VStdRamMemCpy((d), (s), (vuint16)(l))
#   define VStdMemCpyFarRamToRam(d, s, l)      VStdRamMemCpy((d), (s), (vuint16)(l))

#   define VStdMemCpyFarRamToFarRam(d, s, l)   VStdRamMemCpy((d), (s), (vuint16)(l))
#   define VStdMemCpyFarRomToFarRam(d, s, l)   VStdRomMemCpy((d), (s), (vuint16)(l))

#    define VStdMemCpy16RamToRam(d, s, l)      VStdRamMemCpy16((d), (s), (vuint16)(l))
#    define VStdMemCpy16RamToFarRam(d, s, l)   VStdRamMemCpy16((d), (s), (vuint16)(l))
#    define VStdMemCpy16FarRamToRam(d, s, l)   VStdRamMemCpy16((d), (s), (vuint16)(l))

#    define VStdMemCpy32RamToRam(d, s, l)      VStdRamMemCpy32((d), (s), (vuint16)(l))
#    define VStdMemCpy32RamToFarRam(d, s, l)   VStdRamMemCpy32((d), (s), (vuint16)(l))
#    define VStdMemCpy32FarRamToRam(d, s, l)   VStdRamMemCpy32((d), (s), (vuint16)(l))

#  endif /* VSTD_HL_ENABLE_MEM_FCT_MAPPING */
# endif
/*********************************************************************************************************************/
/* Compatibility                                                                                                     */
/*********************************************************************************************************************/
# if defined (VSTD_ENABLE_API_AUTOSAR)
# else
#  define VStdMemCpy(d,s,l)     VStdMemCpyRamToRam((d),(s),(l))
# endif

# if defined(VSTD_HL_USE_VSTD_RAMMEMCPY) && !defined(VSTD_ENABLE_API_AUTOSAR)
# else
#  define VStdRamMemCpy(d,s,l) VStdMemCpyRamToRam((d),(s),(l))
# endif

# if defined(VSTD_HL_USE_VSTD_ROMMEMCPY) && !defined(VSTD_ENABLE_API_AUTOSAR)
# else
#  define VStdRomMemCpy(d,s,l) VStdMemCpyRomToRam((d),(s),(l))
# endif

/*********************************************************************************************************************/
/* Prototypes of functions                                                                                           */
/*********************************************************************************************************************/

# if defined(VSTD_ENABLE_API_AUTOSAR)
#  define VSTDLIB_START_SEC_CODE
#  include "MemMap.h"
# endif

/* initialization */
/* CODE CATEGORY 4 START*/
VSTD_DEF_FUNC_API(VSTD_NONE, void, CODE) VStdInitPowerOn(void);
/* CODE CATEGORY 4 END*/


/* function for moving data */
# if defined(VSTD_ENABLE_API_AUTOSAR)
/* CODE CATEGORY 1 START */
VSTD_DEF_FUNC_API(VSTD_NONE, void, CODE) VStdMemClr_Func(VSTD_DEF_P2VAR_PARA(VSTD_NONE, uint8, AUTOMATIC, VAR_FAR) pDest, uint16_least nCnt);
VSTD_DEF_FUNC_API(VSTD_NONE, void, CODE) VStdMemSet_Func(VSTD_DEF_P2VAR_PARA(VSTD_NONE, uint8, AUTOMATIC, VAR_FAR) pDest, uint8 nPatter, uint16_least nCnt);
VSTD_DEF_FUNC_API(VSTD_NONE, void, CODE) VStdMemCpy_Func(VSTD_DEF_P2VAR_PARA(VSTD_NONE, uint8, AUTOMATIC, VAR_FAR) pDest, VSTD_DEF_P2CONST_PARA(VSTD_NONE, uint8, AUTOMATIC, VAR_FAR) pSrc, uint16_least nCnt);
VSTD_DEF_FUNC_API(VSTD_NONE, void, CODE) VStdMemCpy16_Func(VSTD_DEF_P2VAR_PARA(VSTD_NONE, uint16, AUTOMATIC, VAR_FAR) pDest, VSTD_DEF_P2CONST_PARA(VSTD_NONE, uint16, AUTOMATIC, VAR_FAR) pSrc, uint16_least nCnt);
VSTD_DEF_FUNC_API(VSTD_NONE, void, CODE) VStdMemCpy32_Func(VSTD_DEF_P2VAR_PARA(VSTD_NONE, uint32, AUTOMATIC, VAR_FAR) pDest, VSTD_DEF_P2CONST_PARA(VSTD_NONE, uint32, AUTOMATIC, VAR_FAR) pSrc, uint16_least nCnt);
/* CODE CATEGORY 1 END */
# else /* VSTD_ENABLE_API_AUTOSAR */
/* CODE CATEGORY 1 START*/
#  if defined(VSTD_HL_USE_VSTD_MEMCLR)
VSTD_API_0 void VSTD_API_1 VStdMemClrInternal(void *pDest, vuint16 nCnt) VSTD_API_2;
#  endif

#  if defined(VSTD_HL_USE_VSTD_MEMSET)
VSTD_API_0 void VSTD_API_1 VStdMemSetInternal(void *pDest, vuint8 nPattern, vuint16 nCnt) VSTD_API_2;
#  endif

#  if defined(VSTD_HL_USE_VSTD_RAMMEMCPY)
VSTD_API_0 void VSTD_API_1 VStdRamMemCpy(void *pDest, void *pSrc, vuint16 nCnt) VSTD_API_2;
#  endif

#  if defined(VSTD_HL_USE_VSTD_ROMMEMCPY)
VSTD_API_0 void VSTD_API_1 VStdRomMemCpy(void *pDest, V_MEMROM1 void V_MEMROM2 V_MEMROM3 *pSrc, vuint16 nCnt) VSTD_API_2;
# endif

#  if defined(VSTD_HL_USE_VSTD_WORD_MEMCPY)
VSTD_API_0 void VSTD_API_1 VStdRamMemCpy16(void *pDest, void *pSrc, vuint16 nWordCnt) VSTD_API_2;
# endif

#  if defined(VSTD_HL_USE_VSTD_DWORD_MEMCPY)
VSTD_API_0 void VSTD_API_1 VStdRamMemCpy32(void *pDest, void *pSrc, vuint16 nDWordCnt) VSTD_API_2;
#  endif
/* CODE CATEGORY 1 END*/

/* Declaration of additional memory manipulation functions */
# endif /* VSTD_ENABLE_API_AUTOSAR */

#  if defined(VSTD_ENABLE_INTCTRL_HANDLING)

/* interrupt control functions */
#   if defined(VSTD_ENABLE_DEFAULT_INTCTRL)

/* CODE CATEGORY 1 START*/
VSTD_DEF_FUNC_API(VSTD_NONE, void, CODE) VStdSuspendAllInterrupts(void) VSTD_API_2;
/* CODE CATEGORY 1 END*/

/* CODE CATEGORY 1 START*/
VSTD_DEF_FUNC_API(VSTD_NONE, void, CODE) VStdResumeAllInterrupts(void) VSTD_API_2;
/* CODE CATEGORY 1 END*/
#   endif

/* Declaration of additional Irq Support functions */
#if defined(VSTD_ENABLE_DEFAULT_INTCTRL)

# if (defined (V_COMP_TI)  &&  defined (__TI_TMS470_V7M3__))     || \
     (defined (V_COMP_ARM) && !defined (__TARGET_CPU_CORTEX_M3)) || \
      defined (V_COMP_GNU)                                       || \
      defined (V_COMP_QCC)
/* CODE CATEGORY 1 START */
  VSTD_API_0 void VSTD_API_1 VStdLL_GlobalInterruptDisable(tVStdIrqStateType* localInterruptOldStatusPtr);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
  VSTD_API_0 void VSTD_API_1 VStdLL_GlobalInterruptRestore(tVStdIrqStateType localInterruptOldStatus);
/* CODE CATEGORY 1 END */
# endif
  
# if (defined (V_COMP_ARM) || defined (V_COMP_KEIL))
#  if defined (__TARGET_CPU_CORTEX_M3)
  __asm void VStdLL_GlobalInterruptDisable(tVStdIrqStateType* localInterruptOldStatusPtr);
  __asm void VStdLL_GlobalInterruptRestore(tVStdIrqStateType localInterruptOldStatus);
#  endif
# endif


# if defined (V_COMP_IAR)
#  if ( ((__TID__ >> 4) & 0x0F) == 0x06 )
  void VStdLL_GlobalInterruptDisable(tVStdIrqStateType* localInterruptOldStatusPtr);
  void VStdLL_GlobalInterruptRestore(tVStdIrqStateType localInterruptOldStatus);
#  endif  
# endif 

# if defined (V_COMP_GHS)
#  if defined (__CortexM3)
  void VStdLL_GlobalInterruptDisable(tVStdIrqStateType* localInterruptOldStatusPtr);
  void VStdLL_GlobalInterruptRestore(tVStdIrqStateType localInterruptOldStatus);
#  endif  
# endif 

#endif /* if defined(VSTD_ENABLE_DEFAULT_INTCTRL) */
#  endif


/*********************************************************************************************************************/
/* Callback functions                                                                                                */
/*********************************************************************************************************************/
# if defined(VSTD_ENABLE_DEBUG_SUPPORT)
/* CODE CATEGORY 4 START*/
VSTD_DEF_FUNC_CBK(VSTD_NONE, void, CODE) ApplVStdFatalError(vuint8 nErrorNumber);
/* CODE CATEGORY 4 END*/
# endif

# if defined(VSTD_ENABLE_API_AUTOSAR)
#  define VSTDLIB_STOP_SEC_CODE
#  include "MemMap.h"
# endif


#endif
