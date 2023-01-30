/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : EPS_DiagSrvcs_XCP.h file
* Module Description: Common Manufacturing Program Interface for XCP and ISO services
* Product           : Gen II Plus - EA3.0
* Author            : Kevin Smith
*
* Notes:
* This file contains configurations for the XCP services.
*
*****************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Apr 12 10:20:00 2012
 * %version:          12 %
 * %derived_by:       lz4p8n %
 * %date_modified:    Thu Aug 29 16:55:37 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 06/06/12     1       KS      Initial Component Release
 * 09/28/12     2       Jared   Updates for changes to RID function structure
 * 01/14/13     3       LN      Added Static DAQ 0107                                                           6931
 * 03/16/13     4       VK      Added Static DAQ 0108, 0109                                                     7625
 * 03/16/13     5       VK      Added Static DAQ 010A, 010B                                                     7625
 * 03/18/13     6       Jared   Added function prototypes for new DAQs                                          7628
 * 05/23/13     7       KJS     Anomaly correction for limiting DAQ ODT lengths and QAC corrections
 * 08/29/13     8       JWJ     Added XCP write function and code to handle calling write block after download  9610
 * 04/10/14		9		SP		Added Static DAQ 0x0C															11736
 * 08/29/14		10		KJS		Added static DAQ 0x0D															12406
 * 11/12/14     11      JWJ     Added static DAQs 0x10E and 0x10F                                               12664
 * 11/19/14		13		SP		Corrected static DAQ 0x0D													  	12733
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include area >>		                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "EPS_DiagSrvcs_SrvcLUTbl.h"
#include "EPS_DiagSrvcs_XCP.Interface.h"
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include area >>   		      		    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#ifndef EPS_DIAGSRVCS_XCP_H
#define EPS_DIAGSRVCS_XCP_H

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of custom include area >>	                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of custom include area >>	                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of custom define area >>   		  	    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* XCP User Command Valid Responses */
#define D_XCP_NOERROR				0x00U
#define D_XCP_USRCMDRESP_OK			XCP_CMD_OK
#define D_XCP_USRCMDRESP_PENDING	XCP_CMD_PENDING
#define D_XCP_USRCMDRESP_ERR		XCP_CMD_SYNTAX
#define XCP_UserCmd_RespLen_m(x) 	xcp.CrmLen = x
#define XCP_UserCmd_RespByte_m(x)	CRM_BYTE(x)

/* XCP User Command Ranges
 * Valid Ranges
 * 0x0000 - 0x01FF -> DAQ Operations
 * 0x0200 - 0xEFFF -> Reserved
 * 0xF000 - 0xFCFF -> System Commands
 * 0xFD00 - 0xFEFF -> Reserved (ISO PID Range)...XCP not supported in this range
 * 0xFF00 - 0xFFFF -> Read/Write XCP PIDs
 */
#define D_XCP_USERCMD_DAQCMD_USER			0x00U
#define D_XCP_USERCMD_DAQCMD_PREDEFINED		0x01U
#define D_XCP_USERCMD_SYSCMD_LOLMT			0xF0U
#define D_XCP_USERCMD_SYSCMD_HILMT			0xFCU
#define D_XCP_USERCMD_PIDCMD				0xFFU

/* DAQ  */
#define D_XCP_DAQ_USERDEFTYPE		D_XCP_USERCMD_DAQCMD_USER
#define D_XCP_DAQ_PREDEFINEDTYPE	D_XCP_USERCMD_DAQCMD_PREDEFINED
#define D_XCP_DAQ_MAXEVENT			kXcpMaxEvent
#define D_XCP_USRDEFDAQ_BUFFLEN		(D_XCP_TL_MAXREQLEN - 4)
#define D_XCP_DAQRESP_FULLLEN		(D_XCP_TL_MAXCTO - 0x01)
#define D_XCP_MAX_ODT_ENTRY_SIZE	XCP_MAX_ODT_ENTRY_SIZE
#define D_XCP_USRDEFDAQ_LISTMODE	0x10U /* Enables time stamp */
#define D_XCP_USRDEFDAQ_DAQNUM		0x00U
#define D_XCP_PREDEFDAQ_DAQNUM		0x00U

/* Pre build DAQ PID numbers */
#define D_STATICDAQ_MANUFSRVC_MTRLEARNING 						0x0101U
#define D_STATICDAQ_MANUFSRVC_TRQRATIO							0x0102U
#define D_STATICDAQ_MANUFSRVC_TRQSWEEP							0x0103U
#define D_STATICDAQ_MANUFSRVC_STATICEFFNLONGSWEEP				0x0104U
#define D_STATICDAQ_MANUFSRVC_ROTORSTIFFNESS					0x0105U
#define D_STATICDAQ_MANUFSRVC_NOISE								0x0106U
#define D_STATICDAQ_MANUFSRVC_POSITION							0x0107U
#define D_STATICDAQ_MANUFSRVC_TURNSCNTRSPIDATA					0x0108U
#define D_STATICDAQ_MANUFSRVC_MOTORCURRENT						0x0109U
#define D_STATICDAQ_MANUFSRVC_ANLGTRQSNSRINFO					0x010AU
#define D_STATICDAQ_MANUFSRVC_STATICEFFNLONGSWEEPANALOG			0x010BU
#define D_STATICDAQ_MANUFSRVC_DIGTRQANDHWPOS					0x010CU
#define D_STATICDAQ_MANUFSRVC_VERNERR							0x010DU
#define D_STATICDAQ_MANUFSRVC_POSITION2							0x010EU
#define D_STATICDAQ_MANUFSRVC_TORQUE							0x010FU


/* PID */
#define D_XCP_PID_READSRV				0u
#define D_XCP_PID_WRITESRV				1u
#define D_XCP_PID_SNGLFRM_RESP			0u
#define D_XCP_PID_MULTIFRM_RESP			1u
#define D_XCP_PID_SNGLFRM_RESPLEN		4u
#define D_XCP_PID_SNGLFRM_WRITELMT		4u
#define D_XCP_PID_BYTELEN				1u
#define D_XCP_PID_WORDLEN				2u
#define D_XCP_PID_FLOATLEN				4u
#define D_XCP_PID_READRESP_BASELEN 		2u

#define XCP_PID_RESPTYPE_m(x)			CRM_BYTE(1) = x
#define XCP_PID_SINGLEFRAMELEN_m(x)		CRM_BYTE(2) = x
#define XCP_PID_MULTIFRAMELENHI_m(x)	CRM_BYTE(2) = x
#define XCP_PID_MULTIFRAMELENLO_m(x)	CRM_BYTE(3) = x
#define XCP_PID_WRITEMULTIFRMLENHI_m(x)	CRM_BYTE(1) = x
#define XCP_PID_WRITEMULTIFRMLENLO_m(x)	CRM_BYTE(2) = x
#define XCP_PID_SINGLEFRAMEDATA_m(x)	CRM_BYTE((3+x))

/* Error Codes */
#define D_XCP_ERR_INVLDSRVID		0x01U
#define D_XCP_ERR_SRVIDRESRVD		0x02U
#define D_XCP_ERR_INACTIVESRV		0x03U
#define D_XCP_ERR_CONFIGERR			0x04U
#define D_XCP_ERR_MEMALLOCERR		0x05U
#define D_XCP_ERR_INVLDARG			0x06U
#define D_XCP_ERR_SRVREADONLY		0x07U
#define D_XCP_ERR_INVLDDAQ			0x08U
#define D_XCP_ERR_NOVLDDAQPID		0x09U
#define D_XCP_ERR_INVLDPREDEFDAQ	0x0AU
#define D_XCP_ERR_INVLDPRESACLE		0x0BU
#define D_XCP_ERR_INVLDEVENT		0x0CU
#define D_XCP_ERR_UNKOWNERR			0x0DU
#define D_XCP_ERR_FUNCNOTSUPP		0x0EU	/* Equiv to ISO error code 0x12 */
#define D_XCP_ERR_INVLFORMAT		0x0FU	/* Equiv to ISO error code 0x13 */
#define D_XCP_ERR_CONDNOTCORRECT	0x10U	/* Equiv to ISO error code 0x22 */
#define D_XCP_ERR_REQOUTOFRANGE		0x11U	/* Equiv to ISO error code 0x31 */


#define D_XCP_ERR_BYTEOFFSET		2
#define XCP_ERR_UpperByte_m(x)		XCP_UserCmd_RespByte_m(D_XCP_ERR_BYTEOFFSET) = x	
#define XCP_ERR_LowerByte_m(x)		XCP_UserCmd_RespByte_m((D_XCP_ERR_BYTEOFFSET + 1)) = x
#define XCP_ERR_ErrorCode_m(x)		XCP_UserCmd_RespByte_m((D_XCP_ERR_BYTEOFFSET + 2)) = x
#define XCP_ERR_Determine_m(x)		(((uint8)x > D_ZERO_CNT_U8)?(TRUE):(FALSE))
#define XCP_Error_SetRespLen_m()	XCP_UserCmd_RespLen_m(5U)


/* TODO: Correct these indexes */
/* Static DAQ indexes -- The following PIDs are used in the static built DAQs */
#define D_XCP_PIDID_T1_ANALOG_CNTS			0x0003U
#define D_XCP_PIDID_T1_ANALOG_VOLTS			0x0004U
#define D_XCP_PIDID_T2_ANALOG_CNTS			0x0005U
#define D_XCP_PIDID_T2_ANALOG_VOLTS			0x0006U
#define D_XCP_PIDID_ABSHWPOSSCOM			0x0008U
#define D_XCP_PIDID_KEFBCKTYH				0x000AU
#define D_XCP_PIDID_RFBCKTYH				0x000BU
#define D_XCP_PIDID_SIN1MAXTYH				0x000CU
#define D_XCP_PIDID_SIN1MINTYH				0x000DU
#define D_XCP_PIDID_COS1MAXTYH				0x000EU
#define D_XCP_PIDID_COS1MINTYH				0x000FU
#define D_XCP_PIDID_MRFMTRTRQCMD			0x0010U
#define D_XCP_PIDID_MRFCUMMTRPOS			0x0011U
#define D_XCP_PIDID_MRFMTRVEL				0x0012U
#define D_XCP_PIDID_T1_DIGITAL_DUTY			0x0014U
#define D_XCP_PIDID_T1_DIGITAL_VOLTS		0x0015U
#define D_XCP_PIDID_T2_DIGITAL_DUTY			0x0016U
#define D_XCP_PIDID_T2_DIGITAL_VOLTS		0x0017U
#define D_XCP_PIDID_P1_ANALOG_CNTS			0x002CU
#define D_XCP_PIDID_P2_ANALOG_CNTS			0x002DU
#define D_XCP_PIDID_RELPOS					0x002EU
#define D_XCP_PIDID_RAWCURR1				0x0037U
#define D_XCP_PIDID_RAWCURR2				0x0038U
#define D_XCP_PIDID_MTRCURRQAX				0x0039U
#define D_XCP_PIDID_MTRCURRDAX				0x003AU
#define D_XCP_PIDID_VALIDCURRSAMPLE			0x003BU
#define D_XCP_PIDID_TURNSCNTRSPIDATA		0x003CU
#define D_XCP_PIDID_T1_SENT_HWNM			0x0041U
#define D_XCP_PIDID_T2_SENT_HWNM			0x0042U
#define D_XCP_PIDID_I2CHWCOLPOS_HWDEG		0x0043U
#define D_XCP_PIDID_I2CHWSPURPOS_HWDEG		0x0044U
#define D_XCP_PIDID_I2CABSHWPOS_HWDEG		0x0045U
#define D_XCP_PIDID_VERNDIAGERROR_DEG		0x0046U
#define D_XCP_PIDID_DIGHWTRQT1_HWNM			0x0047U
#define D_XCP_PIDID_DIGHWTRQT2_HWNM			0x0048U
#define D_XCP_PIDID_I2CABSHWPOS_HWDEG_F32	0x0049U

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of custom define area >>	                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, EPSXCPDIAGSRVCS_CODE) ProcessXCPPID(VAR(uint8, EPSDIAGSRVCS_VAR) Size_Cnt_T_u08);

/* Function Prototypes */

/* User XCP Services */
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) XcpUserDynamicDaqSetup( VAR(uint8, EPSDIAGSRVCS_VAR) Prescale_Uls_T_u08,
																 VAR(uint8, EPSDIAGSRVCS_VAR) Event_Cnt_T_u08,
																 P2CONST(uint8, EPSDIAGSRVCS_VAR, EPSDIAGSRVCS_VAR) t_Param_Uls_T_u08);

STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) XcpUserStaticDaqSetup( VAR(uint8, EPSDIAGSRVCS_VAR) Prescale_Uls_T_u08,
																 VAR(uint8, EPSDIAGSRVCS_VAR) Event_Cnt_T_u08,
																 VAR(uint8, EPSDIAGSRVCS_VAR) PreBltDaqNum_T_Cnt_u08);

STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) XcpUserRoutineCmd(VAR(uint16, EPSDIAGSRVCS_VAR) SysCmdID_Cnt_T_u16,
														 P2VAR(uint8, EPSDIAGSRVCS_VAR, EPSDIAGSRVCS_VAR) t_Param_Uls_T_u08);

STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) XcpUserPIDSrvc(VAR(uint16, EPSDIAGSRVCS_VAR) PID_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) SrvcType_Cnt_T_u08,
														 P2CONST(uint8, EPSDIAGSRVCS_VAR, EPSDIAGSRVCS_VAR) t_Param_Uls_T_u08);

/* User XCP Services Supporting Functions */
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) XcpPIDReadResp(VAR(uint16, EPSDIAGSRVCS_VAR) PIDSize_Cnt_T_u16, P2CONST(uint32, EPSDIAGSRVCS_VAR, EPSDIAGSRVCS_VAR) ReadValue_Cnt_T_ptr,
														VAR(uint8, EPSDIAGSRVCS_VAR) Type_Cnt_T_u08);

STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) XcpErrorHandler(VAR(uint8, EPSDIAGSRVCS_VAR) ErrorCode_Uls_T_u08);
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) XcpODTEntrySetup(	P2CONST(uint16, EPSDIAGSRVCS_VAR, EPSDIAGSRVCS_VAR) t_PIDs_Uls_T_u16,
															VAR(uint16, EPSDIAGSRVCS_VAR) PIDCount_Cnt_T_u08,
															VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08);

STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) XcpISOErrorConverter(VAR(uint8, EPSDIAGSRVCS_VAR) ErrorCode_Cnt_T_u08);

/* Static DAQ functions */
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_MtrLearning(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08);
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_TrqRatio(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08);
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_TrqSweep(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08);
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_StaticEffnLongSweep(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08);
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_RotorStiffness(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08);
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_Noise(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08);
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_Position(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08);
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_TurnsCounterSPIData(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08);
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_MotorCurrent(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08);
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_AnlgTrqSnsrInfo(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08);
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_StaticEffnLongSweepAnalog(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08);
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_DigTrqAndPosition(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08);
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_VernErrAndPositionAndTrq(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08);
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_Position2(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08);
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_Torque(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08);

#endif /*EPS_DIAGSRVCS_XCP_H*/
