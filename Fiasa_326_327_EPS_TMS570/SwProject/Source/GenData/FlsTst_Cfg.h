
/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : FlsTst_Cfg.h
* Module Description: Configuration file of FlsTst module
* Product           : Gen II Plus - EA3.0
* Generator         : artt 2.0.2.0
* Generation Time   : 20.10.2016 09:14:12
*****************************************************************************/
/* Version Control:
 * Date Created:      Fri Jul 13 18:34:17 2012
 * %version:          2 %
 * %date_modified:    Tue Jan 14 14:59:50 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 07/13/12   1       JJW       Initial template creation
 * 07/26/12   2       JJW       Generation of config set externs
 * 09/19/12   3       JJW       correction of blockDefine scope issue
 *            4                                                                                                6279
 * 10/10/13   5       KMC       change seclength element of FlsTst_MemBlockType to uint32 -- for fix of       10345
 *                              anomaly 5491
 */

#ifndef FLSTST_CFG_H
#define FLSTST_CFG_H


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*** Public Part (used by FlsTst API) *****************************************/
#include "Std_Types.h"                   /* Standard type definitions      */


/* Include definitions for Diagnostic Event API */
#include "Ap_DiagMgr.h"

#define FLSTST_E_FLSTST_FAILURE			NTC_Num_FlashCRCMemFault
#define FLSTST_E_SELFTEST_FAILURE		NTC_Num_CPU_CoreInitFlt
#define FLSTST_E_MPU_FAILURE			NTC_Num_PerDiag_DMAFlt
#define FLSTST_E_UNEXPECTEDIRQ_FAILURE	NTC_Num_FlashCRCMemFault

#define FLSTST_E_FLSTST_INFO			1u
#define FLSTST_E_SELFTEST_INFO			8u
#define FLSTST_E_MPU_INFO				128u
#define FLSTST_E_UNEXPECTEDIRQ_INFO		1u

#define FLSTST_REPORTERRORSTATUS(event, param, status)		NxtrDiagMgr10_ReportNTCStatus(event, param, status)
#define FLSTST_EVENT_PASSED				NTC_STATUS_PASSED
#define FLSTST_EVENT_FAILED				NTC_STATUS_FAILED


/*** Private Part (used by FlsTst.c only) *************************************/
#ifdef FLSTST_C


#endif /* FLSTST_C                                                            */


/*******************************************************************************
**                      Global Macros                                         **
*******************************************************************************/

/*** Public Part (FlsTst API) *****************************************/

/*
 * File version information
 */
#define FLSTST_CFG_H_MAJOR_VERSION   1u
#define FLSTST_CFG_H_MINOR_VERSION   0u
#define FLSTST_CFG_H_PATCH_VERSION   0u

/*
 * API enable settings
 */
#define FLSTST_GET_CURRENT_STATE_API					STD_OFF
#define FLSTST_GET_ERROR_DETAILS_API					STD_OFF
#define FLSTST_GET_TEST_RESULT_BGND_API					STD_OFF
#define FLSTST_GET_TEST_RESULT_FGND_API					STD_OFF
#define FLSTST_GET_TEST_SIGNATURE_BGND_API				STD_OFF
#define FLSTST_GET_TEST_SIGNATURE_FGND_API				STD_OFF
#define FLSTST_START_FGND_API							STD_OFF
#define FLSTST_SUSPEND_RESUME_API						STD_ON
#define FLSTST_TEST_ECC_API    							STD_OFF
#define FLSTST_TEST_COMPLETE_NOTIFICATION_SUPPORTED		STD_ON

#define FLSTST_TEST_INTERVAL_ID_END_VALUE	4294967295u

/* FlsTst Memory Block Configuration Definitions */
typedef struct {
	VAR(uint32, AUTOMATIC)	crcInitL;		/* CRC accumulator init value Low 32 bits */
	VAR(uint32, AUTOMATIC)	crcInitH;		/* CRC accumulator init value High 32 bits */
	P2CONST(uint64, AUTOMATIC, AUTOMATIC) crcPtr;
	P2CONST(uint64, AUTOMATIC, AUTOMATIC) startPtr;
	VAR(uint16, AUTOMATIC)	  secnum;			/* number of sectors, each having a unique CRC */
	VAR(uint32, AUTOMATIC)    seclength;		/* sector length in 64 bit words -- Max value is 1048575 (20 bit field in register) */
	VAR(uint16, AUTOMATIC)    dmaElementCnt;	/* DMA element count */
	VAR(uint16, AUTOMATIC)    dmaFrameCnt;	/* DMA frame count */
}FlsTst_MemBlockType;


#define FLSTST_BLOCK_NUMBER_BGND_RUNTIME  3u
#define FLSTST_BLOCK_NUMBER_FGND_RUNTIME  0u
extern CONST(FlsTst_MemBlockType, AUTOMATIC)	FlsTst_BlksRuntime[ 3u ];


typedef struct {
	VAR(uint8, AUTOMATIC)    numBgndBlks;
	VAR(uint8, AUTOMATIC)    numFgndBlks;
	/* All background blocks are defined first in the array. Any block defined only as a foreground test block is defined after background blocks */
	P2CONST(FlsTst_MemBlockType, AUTOMATIC, AUTOMATIC)	MemBlk;
	void (*notifFcn)();
}FlsTst_ConfigType;

/* Configuration Structures */
extern CONST(FlsTst_ConfigType, AUTOMATIC) FlsTst_Runtime;
   
#endif /* FLSTST_CFG_H */

/*** End of file **************************************************************/
