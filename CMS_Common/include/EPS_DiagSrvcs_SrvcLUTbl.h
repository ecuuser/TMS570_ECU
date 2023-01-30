/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : EPS_DiagSrvcs_SrvcLUTbl.h file
* Module Description: Common Manufacturing Program Interface for XCP and ISO services
* Product           : Gen II Plus - EA3.0
* Author            : Kevin Smith
*
* Notes:
* This file contains format of the lookup tables.
*
*****************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Apr 12 10:20:00 2012
 * %version:          17 %
 * %derived_by:       kzdyfh %
 * %date_modified:    Mon Jan 27 16:14:01 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 06/06/12     1       KS      Initial Component Release
 * 09/26/12     2       Jared   Updated PIDTBLSIZE for addition of DiagMgr & AvgFricLrn PIDs
 * 10/29/12     3       Jared   Added defeat clear on session change variable for anomaly 3677 correction       6344
 * 01/14/13     4       LN      Updated PIDTBLSIZE for addition of new XCP services.                            6916
 * 01/28/13     5       Jared   Added F0FF from PSR485                                                          7190
 * 03/11/13     6       Jared   Update to spec 04A and generation tool 2.0                                      7225
 * 03/16/13     7       Jared   Updated LUT definition to include checks entry for common NRC check config      7628
 * 08/29/13     8       Jared   Modified table structure type to reflect shared usage of lenStop/NvM block      9996
 * 09/19/13     9       Jared   Added 2 new services: FD30 & FD31                                               9610
 * 09/27/13     10      LWW     Updated per integration issues of 06A version
 * 10/16/13     11      Jared   Removed Var Table definitions to support Var table removal                      10467
 * 01/29/14		14		LK		Updated table size for new PID FD17												11298
 * 04/09/14     15      SP		Updated per the new XCP 0x0C requirements										11736
 * 08/29/14		16		KJS		Incorrect file was baselined, same change request as revision 14				12406
 * 11/12/14     17      JWJ     Added new XCP PIDs and DAQs                                                     12664
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include area >>                        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include"EPS_DiagSrvcs_CommonData.h"

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include area >>                          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#ifndef EPS_DIAGSRVCS_PIDTBLINTERFACE_H
#define EPS_DIAGSRVCS_PIDTBLINTERFACE_H

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of custom include area >>                 DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "EPS_DiagSrvcs_ISO.h"              /* required for typedefs for lookup table */
#include "EPS_DiagSrvcs_ISO.Customer.h"     /* Required for PID table size */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of custom include area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of custom define area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* Variables owned by the diagnostic service functions */
extern VAR(boolean, EPSDIAGSRVCS_VAR) MfgDiagInhibit_Uls_G_lgc;
extern VAR(ManufModeType, EPSDIAGSRVCS_VAR) NxtrMEC_Uls_G_enum;

extern VAR(uint8, NVM_APPL_DATA) Nvm_NMEC_Cnt_u8;
extern VAR(uint8, NVM_APPL_DATA) Nvm_EcuSrlNum_Cnt_u8[4];
extern VAR(uint8, NVM_APPL_DATA) Nvm_EpsSrlNum_Cnt_u8[4];
extern VAR(uint8, NVM_APPL_DATA) Nvm_EcuHwPn_Cnt_u8[12];
extern VAR(uint8, NVM_APPL_DATA) Nvm_NxtrManfScrpd_Cnt_u8[64];
extern VAR(uint16, NVM_APPL_DATA) Nvm_IgnCntr_Cnt_u16;

/* XCP and ISO services and variables PID Table */
#define	D_DIAGSRCVS_COMPIDTBLSIZE_CNT_U16	178U
#define D_PIDTBL_NULLPTRADDR_ULS_U32 	t_DiagSrv_PIDtbl[0].address
#define D_PIDTBL_INVLDPID_ULS_U16		t_DiagSrv_PIDtbl[0].PID

/* PID Table definition */
typedef struct EPS_DiagSrv_PIDtbl {
    uint16      PID;
    union {
        void*       var;
        DiagFuncRef func;
    }address;
    uint8       type;
    uint16      length;
    union {
        uint16      lenStop;
        uint16      block;
    }length2;
    uint16      lenStatus;
    uint16      checks;
    uint8       access;
    uint8       active;
} EPS_DiagSrv_PIDtbl;
extern const struct EPS_DiagSrv_PIDtbl t_DiagSrv_PIDtbl[D_DIAGSRCVS_COMPIDTBLSIZE_CNT_U16 + D_DIAGSRCVS_PROGPIDTBLSIZE_CNT_U16];

/* Table defines */
#define D_PIDTBL_READONLY 	0x00u
#define D_PIDTBL_READWRITE	0x01u
#define D_PIDTBL_DISABLED	0x00u
#define D_PIDTBL_ENABLED	0x01u

#define D_PIDTBL_VARTYPE	0x00u
#define D_PIDTBL_PIDTYPE	0x01u
#define D_PIDTBL_RIDTYPE	0x02u
#define D_PIDTBL_RESETTYPE	0x03u
#define D_PIDTBL_IOCTYPE	0x04u

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of custom define area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#endif /* EPS_DIAGSRVCS_PIDTBLINTERFACE_H */