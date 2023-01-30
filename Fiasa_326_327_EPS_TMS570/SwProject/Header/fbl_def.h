/***********************************************************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief        Main definitions for the Flash Boot Loader
 *
 *  --------------------------------------------------------------------------------------------------------------------
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \par Copyright
 *  \verbatim
 *  Copyright (c) 2014 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  --------------------------------------------------------------------------------------------------------------------
 *  Christian Baeuerle            CB            Vector Informatik GmbH
 *  Ralf Fritz                    Fz            Vector Informatik GmbH
 *  Armin Happel                  Hp            Vector Informatik GmbH
 *  Konrad Lazarus                Ls            Vector Informatik GmbH
 *  Thomas Sommer                 ThS           Vector Informatik GmbH
 *  Marco Wierer                  WM            Vector Informatik GmbH
 *  Alexandre C. Plombin          ACP           Vector CANtech, Inc.
 *  Ahmad Nasser                  An            Vector CANtech, Inc.
 *  Robert Schaeffner             Rr            Vector Informatik GmbH
 *  Andreas Pick                  Ap            Vector Informatik GmbH
 *  Michael Radwick               MFR           Vector CANtech, Inc.
 *  Thomas Ebert                  Et            Vector Informatik GmbH
 *  Ben Erickson                  BJE           Vector CANtech, Inc.
 *  Quetty Palacios               QPs           Vector Informatik GmbH
 *  Florian Hees                  FHe           Vector Informatik GmbH
 *  Slawomir Wilk                 SWk           Vector Informatik GmbH
 *  Andre Caspari                 Ci            Vector Informatik GmbH
 *  Andreas Wenckebach            AWh           Vector Informatik GmbH
 *  Joern Herwig                  JHg           Vector Informatik GmbH
 *  Keith Kalski                  Kak           Vector CANtech, Inc.
 *  Phil Lapczynski               Pal           Vector CANtech, Inc.
 *  Achim Strobelt                Ach           Vector Informatik GmbH
 *  Thomas Bezold                 TBe           Vector Informatik GmbH
 *  Marcel Viole                  MVi           Vector Informatik GmbH
 *  Ron Brockmiller               RLB           Vector CANtech, Inc.
 *  Dennis O'Donnell              DJO           Vector CANtech, Inc.
 *  Ralf Haegenlaeuer             HRf           Vector Informatik GmbH
 *  Alexander Starke              ASe           Vector Informatik GmbH
 *  Anuj Rawat                    AR            Vector CANtech, Inc.
 *  Heath Smith                   HSm           Vector CANtech, Inc.
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  02.00.00   2009-10-29  AWh     ESCAN00038531    Added compiler pragmas for C_COMP_GHS_SH4_RCAN2
 *                                 ESCAN00038824    Corrected definitions for Oem Claas
 *  02.01.00   2009-10-29  MVi     ESCAN00038952    Encapsulated pSecTaskFct by FBL_ENABLE_SECM_TASK for VAG SLP3
 *                         Ci      ESCAN00038916    Added support for Ford SLP6
 *                         TBe     ESCAN00039364    Adaptions for +strict option in Cosmic compiler
 *  02.02.00   2010-01-29  Ci      ESCAN00040275    Added support for AVR32/IAR
 *  02.03.00   2010-02-25  Ci      ESCAN00040658    Ford: Enhanced block descriptor
 *                                 ESCAN00040665    Added dedicated return type for
 *                                                  flash erased detection
 *                                 ESCAN00040853    Replaced decryption interface by
 *                                                  data processing API
 *                         AWh     ESCAN00040940    Define common reprogramming magic pattern,
 *                                                  replaced ~-operator in kNoProgRequest macro
 *  02.04.00   2010-04-22  CB      ESCAN00042462    New OEM
 *  02.05.00   2010-07-15  MVi     ESCAN00042953    Changed VAG/PAG BlockDescriptor typedef
 *                         AWh     ESCAN00043586    Gm only: Added CanInitTableStruct definitions for
 *                                                  C_COMP_METROWERKS_MPC55XX_COMMENT, added tDecParam
 *                         CB      ESCAN00043653    Encapsulation of export pointer pSecTaskFct
 *                         SWk     ESCAN00043683    Add support for C_COMP_IAR_78K0R. Adapt
 *                                                  kLbtAddress and pFlashDrvBlk for newest memory qualifier.
 *                         RLB     ESCAN00044112    Added support for C_COMP_IAR_SH2_RCAN
 *  02.06.00   2010-10-04  DJO     ESCAN00044750    Add CanInit registers to CanInitTable for GHS MPC55XX
 *                         SWk     ESCAN00044973    Adapt flashSegmentSize and  CallFblStart() for
 *                                                  C_COMP_MICROCHIP_DSPIC33_COMMENT
 *  02.07.00   2010-11-29  AWh     ESCAN00045586    OEM Fisker: Added support for FBL_ENABLE_EEPMGR configuration
 *                         TBe     ESCAN00047086    Adaptions for 78K0R
 *  02.08.00   2011-01-11  Ach     ESCAN00047946    Use explicit __far qualifiers to access constants from FblHeader/GM SLP2
 *  02.09.00   2011-02-10  TBe     ESCAN00048403    Adaptions for 78K0R NEC compiler
 *                         AWh     ESCAN00048547    Reorganization of CanInitTableStrct bus timing registers
 *  02.10.00   2011-04-13  JHg     ESCAN00046553    Split version check of HIS Security Module specification
 *                         SWk     ESCAN00048877    Removed unused code: FblStackInit(), add FBL_CLIENT_VAG_COMMENT
 *                         Ach     ESCAN00050048    OEM independent extern declaration for FblHeader
 *                                 ESCAN00049189    Change GetFblBuildVersion() for some OEMs
 *  02.11.00   2011-04-13  Kak     ESCAN00050905    Removed ApplFblStart for GM SLP2 to avoid
 *                                                  compiler errors.  Function is not needed.
 *                                 ESCAN00051409    Fix Compiler error caused by tFblStrtFct typedef for XC16X/Keil
 *  02.12.00   2011-07-22  SWk                      Add new states for ApplFblErrorNotification (FBL_CLIENT_VAG_COMMENT)
 *                         SWk     ESCAN00052407    Corrected memory qualifier for FlashEraseTable
 *  02.13.00   2011-08-01  HRf     ESCAN00052264    Add Metrowerks pragmas for data structure FblHeader
 *  02.14.00   2011-08-10  ASe     ESCAN00052558    Encapsulated pSecTaskFct by FBL_ENABLE_SECM_TASK for PAG SLP3
 *  02.15.00   2011-09-07  Hp      ESCAN00052873    Support fbl-start with magic-flag in RAM for Vector-FBL and others
 *                         Ach     ESCAN00052928    Rework memory qualifiers in tFblHeader definitions
 *                         TBe     ESCAN00053207    Added support for new OEM
 *                         ASe     ESCAN00053224    Corrected memory qualifier for kLbtAddress pointer for XC2000
 *  02.16.00   2011-09-20  MVi     ESCAN00053710    Added check if SEC_SECURITY_CLASS is defined
 *                         HRf     ESCAN00053850    Remove structure member CanInitMCR in structure CanInitTableStrct for Mpc5500.
 *  02.17.00   2011-10-07  AR      ESCAN00052873    Support fbl-start with magic-flag in RAM for Vector-FBL and others
 *  02.18.00   2011-11-11  Ach     ESCAN00054551    OEM independent tProcParam definition
 *                                 ESCAN00054665    Ensure FblHeader is placed in data section (GHS, PPC)
 *                         AWh     ESCAN00054600    Added Toyota
 *                         HRf     ESCAN00054710    Macros tFblAddress and tFblLength not accessible for GM SLP2
 *                                 ESCAN00054754    Function like macro CallFblStart(pParam) is compiled incorrectly
 *                                 ESCAN00054760    Extern declaration of FblHeader requires far qualifier for Fj16lx
 *  02.19.00   2012-01-27  Ach     ESCAN00056033    Support XCP transition from Appl to FBL
 *                         JHg     ESCAN00056332    Added configurable checksum/signature verification routines
 *                                                  to logical block descriptor (FBL_ENABLE_USER_VERIFICATION)
 *  02.20.00   2012-02-15  Rr      ESCAN00051367    Add Renault SLP5
 *                         MVi     ESCAN00056844    Removed unused defines (HMC)
 *  02.21.00   2012-03-23  MVi     ESCAN00057460    Misra improvement
 *                         Ach     ESCAN00057601    Common data structure for Daimler SLP10
 *  02.22.00   2012-02-23  Hp      ESCAN00057837    Add support for XCP bootloader
 *  02.23.00   2012-06-22  Ci      ESCAN00058434    Added support for OEM VolvoCar
 *  02.24.00   2012-07-30  HRf     ESCAN00060457    Add support for Renesas compiler on 78K0R.
 *  02.25.00   2012-08-10  Ci      ESCAN00060466    Extended FblStart magic pattern
 *  02.26.00   2012-08-24  TBe     ESCAN00060888    Added support for Renesas CX compiler
 *  02.27.00   2012-09-10  AWh     ESCAN00058069    Added support for Gm SLP4
 *                         Rr      ESCAN00061289    Make fblStartMagicFlag volatile
 *  02.28.00   2012-09-18  Ach     ESCAN00061507    Remove direct access to fblStartMagicFlag from application
 *  02.29.00   2012-10-08  DJO     ESCAN00061845    Add support for C_COMP_FUJITSU_FR81_CCAN
 *                         HSm     ESCAN00061957    Added support for XC2000 with Keil toolchain
 *                         QPs     ESCAN00061963    Add support for C_COMP_RENESAS_RL78_AFCAN
 *  02.30.00   2012-11-20  Ach     ESCAN00062912    Adapted comments to use Doxygen
 *                         HRf     ESCAN00063129    Define the macro #define FBL_CALL_TYPE to an empty macro
 *  02.31.00   2013-02-22  CB      ESCAN00063421    Missing closing comment sign leads to compiler error
 *                         CB      ESCAN00065346    Support for Fiat SLP4
 *  02.32.00   2013-05-15  HRf     ESCAN00066604    Add support for Fujitsu FM3 (MB9BF406RA)
 *                         AWh     ESCAN00067339    Harmonize fblStartMagicFlag extern declaration
 *  02.33.00   2013-08-01  AWh     ESCAN00066859    Compiler warning:fbl_mtab.c W1992B extra braces are nonstandard
 *                         TBe     ESCAN00068061    Reworked memory qualifier for FblHeader access
 *                         AWh     ESCAN00069169    Added Gm SLP5, prepared GM SLP6, removed GM SLP1
 *                         HRf     ESCAN00069556    Renesas Compiler for 78k0r V1.50 is not able to use the memmap approach
 *  02.34.00   2013-08-14  MVi     ESCAN00069804    Add support for RL78
 *  02.35.00   2013-11-15  Ach     ESCAN00071683    Support GM with MPC57xx
 *  02.36.00   2013-12-13  AWh     ESCAN00072086    Gm Secure: tBlockDescriptor Map PartId instead of Mid to Block Index
 *                         JHg     ESCAN00072604    Renamed BIT0, BIT1, ... defines to FBL_BIT0, FBL_BIT1, ...
 *  02.37.00   2014-02-11  Ci      ESCAN00073368    Added support for Ford SLP7
 *                         Ach     ESCAN00073428    Use fbl_mtab.h on Daimler SLP9/10, VAG SLP3 and Vector SLP3
 *                         AWh     ESCAN00073336    GM SLP5 and SLP6: Removed elements that are generated to fbl_mtab.h
 **********************************************************************************************************************/

#ifndef __FBL_DEF_H__
#define __FBL_DEF_H__

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/

/* Basic configurations */
#include "v_cfg.h"

#if defined( VGEN_GENY ) && !defined( VGEN_ENABLE_CANFBL )
/* this file was obviously not included in FBL, so it's used in user application
   check if MAGIC_NUMBER was generated. In this case we have to remove the check for the
   following include because FBL generation use different number than application */
# if defined( MAGIC_NUMBER )
#  undef MAGIC_NUMBER
# endif
#endif
/* Configuration file for flash boot loader */
#include "fbl_cfg.h"
#if defined( VGEN_GENY ) && !defined( VGEN_ENABLE_CANFBL )
/* the last include redefine MAGIC_NUMBER, which is not relevant for application so
   invalidate it */
# if defined( MAGIC_NUMBER )
#  undef MAGIC_NUMBER
# endif
#endif

/* Basic type definitions */
#include "v_def.h"

#if defined( FBL_ENABLE_SECMOD_VECTOR )
# include "SecM_cfg.h"
#endif

/* PRQA S 3453 EOF */ /* MD_CBD_19.7 */
/* PRQA S 3458 EOF */ /* MD_CBD_19.4 */

/***********************************************************************************************************************
 *  VERSION
 **********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : FblDef CQComponent : Implementation */
#define FBLDEF_VERSION          0x0237u
#define FBLDEF_RELEASE_VERSION  0x00u

#ifndef NULL
# define NULL ((void *)0)
#endif

# define assertFbl(p, e)
# define assertFblUser(p, e)
# define assertFblGen(p, e)
# define assertFblInternal(p, e)

/*-- End of assertion definition --------------------------------------------*/


#ifndef SWM_DATA_ALIGN
# define SWM_DATA_ALIGN 0
#endif

/* CanTransmit return values */
# ifndef kCanTxOk
#  define kCanTxOk             0/* Msg transmitted                        */
# endif
# ifndef kCanTxFailed
#  define kCanTxFailed         1/* Tx path switched off                   */
# endif
# define kCanTxInProcess       2

/* Define return code of several functions   */
#define kFblOk                0
#define kFblFailed            1

/* Parameters for ApplFblStartup() */
#define kStartupPreInit       0
#define kStartupPostInit      1
#define kStartupStayInBoot    2

/* Programming request flag */
#define kProgRequest         (tFblProgStatus)0x01u
#define kNoProgRequest       FblInvertBits(kProgRequest,tFblProgStatus)

/* Application validation  */
# define kApplValid            1 /* Application is fully programmed */
# define kApplInvalid          0 /* Operational software is missing */




/* Define to access the FBL header structure */
# define FblHeaderTable ((V_MEMROM1_FAR tFblHeader V_MEMROM2_FAR V_MEMROM3 *)(FBL_HEADER_ADDRESS))

/* Position of boot block: */
/* FBL_TOP_BOOT_BLOCK: The boot block is mapped to the high addresses */
/* FBL_BOTTOM_BOOT_BLOCK: The boot block is mapped to the low addresses */

#if !defined( FBL_REPEAT_CALL_CYCLE )
/* Set default to 1ms for repeat time of main loop */
# define FBL_REPEAT_CALL_CYCLE 1
#endif

# define FBL_CALL_TYPE

#ifndef V_CALLBACK_NEAR
# define V_CALLBACK_NEAR
#endif
#ifndef V_API_NEAR
# define V_API_NEAR
#endif


#if defined( FBL_ENABLE_FBL_START )
/*============ Declarations for FBL start over RAM pattern ===============*/
typedef void tCanInitTable;
void FblStart(tCanInitTable *pCanInitTable);
/* Define pattern for magic flags used for reprogramming indication */
# define kFblStartMagicByte0   0x50u /* 'P' */
# define kFblStartMagicByte1   0x72u /* 'r' */
# define kFblStartMagicByte2   0x6Fu /* 'o' */
# define kFblStartMagicByte3   0x67u /* 'g' */
# define kFblStartMagicByte4   0x53u /* 'S' */
# define kFblStartMagicByte5   0x69u /* 'i' */
# define kFblStartMagicByte6   0x67u /* 'g' */
# define kFblStartMagicByte7   0x6Eu /* 'n' */
# define kFblNoOfMagicBytes    8u

# define FblSetFblStartMagicFlag() \
{ \
   fblStartMagicFlag[0] = kFblStartMagicByte0; \
   fblStartMagicFlag[1] = kFblStartMagicByte1; \
   fblStartMagicFlag[2] = kFblStartMagicByte2; \
   fblStartMagicFlag[3] = kFblStartMagicByte3; \
   fblStartMagicFlag[4] = kFblStartMagicByte4; \
   fblStartMagicFlag[5] = kFblStartMagicByte5; \
   fblStartMagicFlag[6] = kFblStartMagicByte6; \
   fblStartMagicFlag[7] = kFblStartMagicByte7; \
}

# define FblChkFblStartMagicFlag() \
   ((    (fblStartMagicFlag[0] == kFblStartMagicByte0) \
      && (fblStartMagicFlag[1] == kFblStartMagicByte1) \
      && (fblStartMagicFlag[2] == kFblStartMagicByte2) \
      && (fblStartMagicFlag[3] == kFblStartMagicByte3) \
      && (fblStartMagicFlag[4] == kFblStartMagicByte4) \
      && (fblStartMagicFlag[5] == kFblStartMagicByte5) \
      && (fblStartMagicFlag[6] == kFblStartMagicByte6) \
      && (fblStartMagicFlag[7] == kFblStartMagicByte7)) ? 1u : 0u)

# define FblClrFblStartMagicFlag() \
{ \
   vuint8 byteIndex; \
   for (byteIndex = 0; byteIndex < kFblNoOfMagicBytes; byteIndex++) \
   { \
      fblStartMagicFlag[byteIndex] = 0x00u; \
   } \
}
#endif /* #if defined( FBL_ENABLE_FBL_START ) */

/* Defines to convert BigEndian bytes into short or long values ********************/
# ifdef C_CPUTYPE_BIGENDIAN
#  ifdef C_CPUTYPE_32BIT
#   define FblBytesToShort(hi,lo)            (((vuint16)(hi) << 8) | ((vuint16)(lo) ))
#  else
#   define FblBytesToShort(hi,lo)            (vuint16)*(V_MEMRAM0 V_MEMRAM1_FAR vuint16 V_MEMRAM2_FAR *)(&(hi))
#  endif
# endif
# ifdef C_CPUTYPE_LITTLEENDIAN
#  define FblBytesToShort(hi,lo)              (((vuint16)(hi) << 8) | ((vuint16)(lo) ))
# endif

# ifdef C_CPUTYPE_BIGENDIAN
#  ifdef C_CPUTYPE_32BIT
#   define FblBytesToLong(hiWrd_hiByt,hiWrd_loByt,loWrd_hiByt,loWrd_loByt)  \
                                         (((vuint32)(hiWrd_hiByt) << 24) |  \
                                          ((vuint32)(hiWrd_loByt) << 16) |  \
                                          ((vuint32)(loWrd_hiByt) <<  8) |  \
                                          ((vuint32)(loWrd_loByt)      )  )
#  else
#   define FblBytesToLong(hiWrd_hiByt,hiWrd_loByt,loWrd_hiByt, loWrd_loByt)  \
            (vuint32)*(V_MEMRAM0 V_MEMRAM1_FAR vuint32 V_MEMRAM2_FAR *)(&(hiWrd_hiByt))
#  endif
# endif
# ifdef C_CPUTYPE_LITTLEENDIAN
#  define FblBytesToLong(hiWrd_hiByt,hiWrd_loByt,loWrd_hiByt,loWrd_loByt)  \
                                        (((vuint32)(hiWrd_hiByt) << 24) |  \
                                         ((vuint32)(hiWrd_loByt) << 16) |  \
                                         ((vuint32)(loWrd_hiByt) <<  8) |  \
                                         ((vuint32)(loWrd_loByt)      )  )
# endif

#define FBL_BIT0   0x01u
#define FBL_BIT1   0x02u
#define FBL_BIT2   0x04u
#define FBL_BIT3   0x08u
#define FBL_BIT4   0x10u
#define FBL_BIT5   0x20u
#define FBL_BIT6   0x40u
#define FBL_BIT7   0x80u

/* Macros and values for fblMode */
#define START_FROM_APPL          FBL_BIT0
#define START_FROM_RESET         FBL_BIT1
#define APPL_CORRUPT             FBL_BIT2
#define STAY_IN_FLASHER          FBL_BIT3
#define FBL_RESET_REQUEST        FBL_BIT4
#define WAIT_FOR_PING            FBL_BIT5
#define FBL_START_WITH_RESP      FBL_BIT6
#define FBL_START_WITH_PING      FBL_BIT7
#define SetFblMode(state)        (fblMode = (vuint8)((fblMode & 0xF0u) | (state)))
#define GetFblMode()             ((vuint8)(fblMode & 0x0Fu))
#define FblSetShutdownRequest()  SetFblMode(FBL_RESET_REQUEST)
extern MEMORY_NEAR vuint8 fblMode;

/* Defines for response after reset */
#  define RESET_RESPONSE_NOT_REQUIRED         ((vuint8)0x00)
#  define RESET_RESPONSE_SDS_REQUIRED         ((vuint8)0x01)
#  define RESET_RESPONSE_ECURESET_REQUIRED    ((vuint8)0x02)
#  define RESET_RESPONSE_KEYOFFON_REQUIRED    ((vuint8)0x03)


/* Access macros for FblHeader elements for application */
# define GetFblMainVersion()     (FblHeaderTable->kFblMainVersion)
# define GetFblSubVersion()      (FblHeaderTable->kFblSubVersion)
# define GetFblReleaseVersion()  (FblHeaderTable->kFblBugFixVersion)
# if defined( FBL_ENABLE_COMMON_DATA )
#  define GetFblCommonDataPtr()  (FblHeaderTable->pFblCommonData)
# endif

#  define FBL_START_PARAM       ((void *)0)
#   define CallFblStart(pParam)  (FblHeaderTable->FblStartFct)((pParam))

/* macros to harmonize type casts for inverting bits */
#define FblInvertBits(x,type)  ( (type)  ~((type) (x))      )
#define FblInvert8Bit(x)       ( FblInvertBits((x),vuint8)  )
#define FblInvert16Bit(x)      ( FblInvertBits((x),vuint16) )
#define FblInvert32Bit(x)      ( FblInvertBits((x),vuint32) )

/* Always use table for physical flash pages */
# define FBL_FLASHBLOCK_TABLE




/***********************************************************************************************************************
 *  TYPEDEFS
 **********************************************************************************************************************/

typedef vuint8 tFblResult;                    /**< FBL result codes */
typedef vuint8 tFblProgStatus;                /**< Status of reprogramming flag */
typedef vuint8 tApplStatus;                   /**< Application valid status */
typedef vuint8 tMagicFlag;                    /**< Application valid flag */

# ifdef C_CPUTYPE_8BIT
typedef vuint16 FBL_ADDR_TYPE;
typedef vuint16 FBL_MEMSIZE_TYPE;
#  define MEMSIZE_OK
# endif /* C_CPUTYPE_8BIT */
# ifdef C_CPUTYPE_16BIT
typedef vuint16 FBL_ADDR_TYPE;
typedef vuint16 FBL_MEMSIZE_TYPE;
#  define MEMSIZE_OK
# endif /* C_CPUTYPE_16BIT */
# ifdef C_CPUTYPE_32BIT
typedef vuint32 FBL_ADDR_TYPE;
typedef vuint32 FBL_MEMSIZE_TYPE;
#  define MEMSIZE_OK
# endif /* C_CPUTYPE_32BIT */

#define tFblAddress    FBL_ADDR_TYPE
#define tFblLength     FBL_MEMSIZE_TYPE

typedef vuint8 FBL_MEMID_TYPE;

#ifdef MEMSIZE_OK
#else
# error "Error in FBL_DEF.H: C_CPUTYPE_ not defined."
#endif




#if defined( FBL_ENABLE_FBL_START )                   
typedef MEMORY_HUGE MEMORY_FAR void (*tFblStrtFct)( tCanInitTable* );
#endif

#if defined( FBL_ENABLE_COMMON_DATA )
/* Pointer to shared ROM constants */
typedef V_MEMROM1_FAR void V_MEMROM2_FAR V_MEMROM3 * tFblCommonDataPtr;
#endif

/***********************************************************************************************************************
 *  DEFINES
 **********************************************************************************************************************/

# define kFblDiagTimeP2             FBL_DIAG_TIME_P2MAX
# define kFblDiagTimeP2Star         FBL_DIAG_TIME_P3MAX




/* Function pointer for FBL-exported functions */
typedef MEMORY_FAR void (*tExportFct)(void);

/*-------- Note: big section starts here ---------------*/

# define kBlockTypeCode    0x9Au
# define kBlockTypeData    0x9Bu
# define kBlockTypeBoot    0x9Fu
# define kBlockTypeExt     0x9Cu


# ifdef FBL_MTAB_NO_OF_BLOCKS
# else
/* Within the FBL, the size of the logical block table is determined */
/* by the size value in the logical block table.                     */
#  define FBL_MTAB_NO_OF_BLOCKS  1
# endif



#  define kEepFblReprogram       0xB5u

# define kEepWriteData           1
# define kEepReadData            2

/* Error code defines for ApplFblErrorNotification */
# define kFblErrTypeAppl         0x10u
# define kFblErrTypeFlash        0x20u
# define kFblErrTypeEeprom       0x30u
# define kFblErrTypeSec          0x40u
# define kFblErrTypeVectorTPMC   0x50u

typedef vuint8  *tCRCValue;
typedef vuint8  tFblData;
typedef vuint8  tFblErrorType;
typedef vuint16 tFblErrorCode;

/* The address types of the module definition table always use logical addresses.   */
/* This is important for those platforms which provide a paged physical memory      */
/* address space. For those platforms with linear physical address space, logical   */
/* and physical addresses are identical.                                            */
typedef FBL_ADDR_TYPE       tMtabAddress;
typedef FBL_MEMSIZE_TYPE    tMtabLength;
typedef FBL_MEMID_TYPE      tMtabMemId;


/* Forward delaration - struct is declared in fbl_mtab.h */
struct tLogicalBlockTableTag;
typedef V_MEMROM1_FAR struct tLogicalBlockTableTag V_MEMROM2_FAR V_MEMROM3 * tpLogicalBlockTable;


/* Header of the FBL */
typedef struct tagFblHeader
{
   vuint8    kFblMainVersion;
   vuint8    kFblSubVersion;
   vuint8    kFblBugFixVersion;
   vuint8    FblHeaderAlign1;            /**< Alignment to even addresses */
   tpLogicalBlockTable kLbtAddress;
# if defined( FBL_ENABLE_COMMON_DATA )
   tFblCommonDataPtr pFblCommonData;
# endif
# if defined( FBL_ENABLE_EEPMGR )
   /* Extension for VPM with EEPMGR */
   V_MEMROM1_FAR vuint8 V_MEMROM2_FAR V_MEMROM3 * pFlashDrvBlk;
# endif
# ifdef FBL_ENABLE_FBL_START
   tFblStrtFct FblStartFct;            /**< Pointer to FblStart-function */
# endif
} tFblHeader;


/***********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

/* Definition of the logical block table */
/* The FBL provides a logical block table even on an unprogrammed ECU. This table   */
/* is erases and replaced by the one of the application during the first download.  */
# if !defined(FBL_DISABLE_REPROGRAMMABLE_LBT)
#  define FBL_ENABLE_REPROGRAMMABLE_LBT
# endif

/*-------- Note: big section ends here ---------------*/

typedef FBL_CALL_TYPE vuint8 (*tFblRealtimeFct)(void);

/** Function pointer to read memory */
typedef FBL_CALL_TYPE FBL_MEMSIZE_TYPE (*tReadMemoryFct)(FBL_ADDR_TYPE address, vuint8 *buffer, FBL_MEMSIZE_TYPE length);


/** Structure for address and length information of segments */
typedef struct tagSegmentInfo
{
   FBL_ADDR_TYPE     targetAddress;
   FBL_MEMSIZE_TYPE  length;
} tSegmentInfo;

/** Segment data structure */
typedef struct tagSegmentList
{
   vuint8         nrOfSegments;
   tSegmentInfo   segmentInfo[SWM_DATA_MAX_NOAR];
} tSegmentList;


typedef vuint16 tChecksum;












/* OEM independent type definitions ******************************************/
#if defined( FBL_ENABLE_DATA_PROCESSING )
typedef struct tagProcParam
{
   vuint8*        dataBuffer;
   vuint16        dataLength;
   vuint8*        dataOutBuffer;
   vuint16        dataOutLength;
   vuint16        dataOutMaxLength;
   vuint8         (* wdTriggerFct)(void);
   vuint8         mode;
} tProcParam;
#endif

/* OEM independent global data ***********************************************/
//# define FBLHEADER_START_SEC_CONST_EXPORT
//# include "memmap.h"
V_MEMROM0 extern V_MEMROM1 tFblHeader V_MEMROM2 FblHeader;
//# define FBLHEADER_STOP_SEC_CONST_EXPORT
//# include "memmap.h"

//#if defined( FBL_ENABLE_FBL_START )
//#  define MAGICFLAG_START_SEC_DATA_EXPORT
//#  include "memmap.h"
/* Entering bootloader with 8 byte special ('FBLSTARTMAGIC') values */
 extern volatile vuint8 fblStartMagicFlag[kFblNoOfMagicBytes];
//#  define MAGICFLAG_STOP_SEC_DATA_EXPORT
//#  include "memmap.h"
//#endif /* FBL_ENABLE_FBL_START */

#endif /* __FBL_DEF_H__ */

/***********************************************************************************************************************
 *  END OF FILE: FBL_DEF.H
 **********************************************************************************************************************/
