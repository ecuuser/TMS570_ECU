/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : EPS_DiagSrvcs_XCP.c file
* Module Description: Common Manufacturing Program Interface for XCP and ISO services
* Product           : Gen II Plus - EA3.0
* Author            : Kevin Smith
*
* Notes:
* This file contains the source of functions that are used for XCP services.
*
*****************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Apr 12 10:20:00 2012
 * %version:          20 %
 * %derived_by:       kzdyfh %
 * %date_modified:    Thu Sep 19 12:35:01 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 06/06/12     1       KS      Initial Component Release
 * 08/13/12     2       KS      Incorrect pointer refernces correction for DAQ lists (A3630)                    6004
 * 09/28/12     3       Jared   Update for changes to RID function type
 * 10/18/12     4       Jared   Corrected anom 3645 for NRC compliance with spec v02A                           6401
 * 01/14/13     5       LN      Added Static DAQ 0107                                                           6931
 * 03/15/13     6       Jared   Updated NRC defines for Conversion Function                                     7225
 * 03/16/13     7       VK      Added Static DAQ 0108, 0109                                                     7625
 * 03/16/13     7       VK      Added Static DAQ 010A, 010B, corrected anomaly 4625                             7625
 * 03/18/13     9       Jared   Updates to support changes made to CMS function structure                       7628
 * 05/23/13     10      KJS     Anomaly correction for DAQs larger then the ODT limit and multi-frame response
 *                              service reads and QAC corrections.
 * 08/29/13     11      Jared   Added XCP write function and code to handle calling write block after download  9996
 * 09/19/13     12      Jared   Added CLEARED to module variable segment definitions                            9610
 * 04/10/14		13		SP		Added Static DAQ 0x0C															11736
 * 08/29/14		14		KJS		Added static DAQ 0x0D															12406
 * 08/29/14		15		KJS		Incorrect file was baselined, same change request as revision 14				12406
 * 11/12/14     16      JWJ     Added static DAQs 0x10E and 0x10F                                               12664
 * 11/19/14		18		SP		Corrected static DAQ 0x0D														12733
 * 11/20/14     19      JWJ     Corrected static DAQs 0x0E and 0x0F to use proper floating point signals        12661
 * 12/12/14     20      JWJ     A7733: Corrected PID active checks to lookup index of entry rather than assume  12810
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "EPS_DiagSrvcs_SrvcLUTbl.h"
#include "EPS_DiagSrvcs_ISO.h"
#include "EPS_DiagSrvcs_XCP.h"


#define EPSXCPSRVC_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint16, EPSXCPDIAGSRVCS_VAR) EpsXcpSrvc_XCPPIDDataToProcess_Cnt_M_u16;
STATIC VAR(uint16, EPSXCPDIAGSRVCS_VAR) EpsXcpSrvc_XCPPIDActive_Cnt_M_u16;
#define EPSXCPSRVC_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* Source */
/*****************************************************************************
 *
 *	Function Name: 	   ApplXcpUserService
 *
 *	Description:       Handling function for XCP user commands (0xF1)
 *
 *	Inputs:		       pCmd: Command input pCmd[0] = 0xF1, 
 * 							 pCmd[1]-pCmd[2] = User Command, 
 * 							 pCmd[3]-pCmd[7] = Command Parameters
 *
 *	Outputs:	       UserCmdResp_T_Uls_u08: Command response
 *
 *****************************************************************************/
vuint8 ApplXcpUserService( MEMORY_ROM BYTEPTR pCmd )
{
	/* Known deivation of MISRA rule 492. Since the function prototype is not in our control, 
	 * the exception to this rule is used within this function. */

	/* Outputs */
	VAR(uint8, EPSDIAGSRVCS_VAR) UserCmdResp_Uls_T_u08;
	
	/* Local variables */
	VAR(vuint8, EPSDIAGSRVCS_VAR) UserCmdUpperByte_Uls_T_u08;
	VAR(uint16, EPSDIAGSRVCS_VAR) UserCmd_Uls_T_u16;
	
	UserCmdUpperByte_Uls_T_u08 = pCmd[1]; /* PRQA S 492 */
	UserCmd_Uls_T_u16 = bytesToWord_m(pCmd[1], pCmd[2]); /* PRQA S 492 */
	UserCmdResp_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;
	
	if ( UserCmdUpperByte_Uls_T_u08 == D_XCP_USERCMD_DAQCMD_USER )
	{
		/* Dynamic DAQ Request */
		UserCmdResp_Uls_T_u08 = XcpUserDynamicDaqSetup( pCmd[2], pCmd[3], &pCmd[4] ); /* PRQA S 492 */
	}
	else if( UserCmdUpperByte_Uls_T_u08 == D_XCP_USERCMD_DAQCMD_PREDEFINED )
	{
		/* Static Defined DAQ */
		UserCmdResp_Uls_T_u08 = XcpUserStaticDaqSetup( pCmd[2], pCmd[3], pCmd[4] ); /* PRQA S 492 */
	}
	else if( (UserCmdUpperByte_Uls_T_u08 >= D_XCP_USERCMD_SYSCMD_LOLMT) && (UserCmdUpperByte_Uls_T_u08 <= D_XCP_USERCMD_SYSCMD_HILMT) )
	{
		/* System Command */
		UserCmdResp_Uls_T_u08 = XcpUserRoutineCmd( UserCmd_Uls_T_u16, (vuint8 *)&pCmd[3]); /* PRQA S 492 */
	}
	else if( UserCmdUpperByte_Uls_T_u08 == D_XCP_USERCMD_PIDCMD )
	{
		/* PID Command */
		UserCmd_Uls_T_u16 = 0x00FFU & UserCmd_Uls_T_u16;
		UserCmdResp_Uls_T_u08 = XcpUserPIDSrvc( UserCmd_Uls_T_u16, pCmd[3], &pCmd[4]); /* PRQA S 492 */
	}
	else
	{
		/* Out of range error */
		UserCmdResp_Uls_T_u08 = XcpErrorHandler(D_XCP_ERR_INVLDSRVID);
	}

	/* Append error information */
	if(UserCmdResp_Uls_T_u08 == (uint8)D_XCP_USRCMDRESP_ERR)
	{
		XCP_ERR_UpperByte_m(pCmd[1]); /* PRQA S 492 */
		XCP_ERR_LowerByte_m(pCmd[2]); /* PRQA S 492 */
	}
		
	return UserCmdResp_Uls_T_u08;	
}

/*****************************************************************************
 *
 *	Function Name: 	   XcpUserDynamicDaqSetup
 *
 *	Description:       Prepare a DAQ list with user defined PIDs
 *
 *	Inputs:		       Prescale_Uls_T_u08: Prescaler for the DAQ list
 * 					   Event_Cnt_T_u08: Event entry for DAQ
 * 					   t_Param_Uls_T_u08: Parameters for user def daqs 
 *
 *	Outputs:	       Resp_T_Uls_u08: Positive or Negative response. 
 * 			
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) XcpUserDynamicDaqSetup( VAR(uint8, EPSDIAGSRVCS_VAR) Prescale_Uls_T_u08, VAR(uint8, EPSDIAGSRVCS_VAR) Event_Cnt_T_u08, P2CONST(uint8, EPSDIAGSRVCS_VAR, EPSDIAGSRVCS_VAR) t_Param_Uls_T_u08)
{
	/* outputs */
	VAR(uint8, EPSDIAGSRVCS_VAR) Resp_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;
	
	/* locals */
	VAR(uint8, EPSDIAGSRVCS_VAR) TempPIDBufferCnt_Cnt_T_u08;
	VAR(uint16, EPSDIAGSRVCS_VAR) TempPIDBuffer_Uls_T_u16[D_XCP_USRDEFDAQ_BUFFLEN];
	VAR(uint8, EPSDIAGSRVCS_VAR) ErrorFlag_Cnt_T_lgc;
	VAR(uint16, AUTOMATIC) PIDidx_Cnt_T_u16;
	
	/* For-loop variables */
	VAR(uint8, EPSDIAGSRVCS_VAR) I_Cnt_T_u08;
	
	/* Set the response to zero, errors are non-zero */
	Resp_Uls_T_u08 = D_XCP_NOERROR;

	/* Prep variables for function run */
	for (I_Cnt_T_u08 = 0U; I_Cnt_T_u08 < D_XCP_USRDEFDAQ_BUFFLEN; I_Cnt_T_u08++)
	{
		TempPIDBuffer_Uls_T_u16[I_Cnt_T_u08] = 0U;
	}
	TempPIDBufferCnt_Cnt_T_u08 = 0U;
	ErrorFlag_Cnt_T_lgc = FALSE;
	
	/* Start DAQ setup - Clear any existing settings and allocate DAQ in memory */
	XcpUserFreeDaq();
	Resp_Uls_T_u08 = XcpUserAllocDaq(D_ONE_CNT_U8);
	
	if(Resp_Uls_T_u08 != D_XCP_NOERROR)
	{
		Resp_Uls_T_u08 = XcpErrorHandler(D_XCP_ERR_MEMALLOCERR);
	}
	else
	{
		/* Validate event selection */
		if(Event_Cnt_T_u08 >= (uint8)D_XCP_DAQ_MAXEVENT)
		{
			Resp_Uls_T_u08 = XcpErrorHandler(D_XCP_ERR_INVLDEVENT);
		}
		else
		{
			/* Store user params into temp buffer for processing and get total number of bytes to generate ODTs*/
			for(I_Cnt_T_u08 = 0U; I_Cnt_T_u08 < D_XCP_USRDEFDAQ_BUFFLEN; I_Cnt_T_u08++)
			{
				if(t_Param_Uls_T_u08[I_Cnt_T_u08] != D_PIDTBL_INVLDPID_ULS_U16) /* PRQA S 492 */
				{
					PIDidx_Cnt_T_u16 = DiagSrvcs_PIDIdxSearch(t_Param_Uls_T_u08[I_Cnt_T_u08]); /* PRQA S 492 */
					if(t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].active == TRUE) /* PRQA S 492 */
					{
						TempPIDBuffer_Uls_T_u16[TempPIDBufferCnt_Cnt_T_u08] = bytesToWord_m(D_XCP_DAQ_USERDEFTYPE,t_Param_Uls_T_u08[I_Cnt_T_u08]); /* PRQA S 492 */
						TempPIDBufferCnt_Cnt_T_u08++;
					}
					else
					{
						ErrorFlag_Cnt_T_lgc = TRUE;
						Resp_Uls_T_u08 = XcpErrorHandler(D_XCP_ERR_INACTIVESRV);
						break;
					}	
				}
			}
	
			if( (TempPIDBufferCnt_Cnt_T_u08 > 0U) && (ErrorFlag_Cnt_T_lgc == FALSE) )
			{
				Resp_Uls_T_u08 = XcpODTEntrySetup((uint16 *)&TempPIDBuffer_Uls_T_u16[0], (uint16)TempPIDBufferCnt_Cnt_T_u08, D_XCP_USRDEFDAQ_DAQNUM);
				ErrorFlag_Cnt_T_lgc |= XCP_ERR_Determine_m(Resp_Uls_T_u08);
				
				/* Select DAQ and set event */
				if(ErrorFlag_Cnt_T_lgc == FALSE)
				{
					Resp_Uls_T_u08 = XcpUserSetDaqListMode(  D_XCP_USRDEFDAQ_LISTMODE, D_XCP_USRDEFDAQ_DAQNUM, Event_Cnt_T_u08, Prescale_Uls_T_u08 );
				}
			}
			else
			{
				XcpUserFreeDaq(); /* Clear all DAQ settings due to error */
				Resp_Uls_T_u08 = XcpErrorHandler(D_XCP_ERR_NOVLDDAQPID);
			}
		}
	}
	
	if ((Resp_Uls_T_u08 != D_XCP_NOERROR) || (ErrorFlag_Cnt_T_lgc == TRUE))
	{
		XcpUserFreeDaq(); /* Clear all DAQ settings due to error */
	}
	
	return Resp_Uls_T_u08;
}


/*****************************************************************************
 *
 *	Function Name: 	   XcpUserStaticDaqSetup
 *
 *	Description:       DAQs that are predefined. Commonly used by manufacturing 
 *
 *	Inputs:		       Prescale_Uls_T_u08 - Event  		
 * 					   Event_Cnt_T_u08 - Event to assign the selected DAQ
 * 					   PreBltDaqNum_T_Cnt_u08 - prebuilt DAQ selected by the user.
 *
 *	Outputs:	       UserCmdResp_T_Uls_u08: Command response
 *
 * 
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) XcpUserStaticDaqSetup( VAR(uint8, EPSDIAGSRVCS_VAR) Prescale_Uls_T_u08, VAR(uint8, EPSDIAGSRVCS_VAR) Event_Cnt_T_u08,  VAR(uint8, EPSDIAGSRVCS_VAR) PreBltDaqNum_T_Cnt_u08)
{
	/* outputs */
	VAR(uint8, EPSDIAGSRVCS_VAR) Resp_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;
	
	/* locals */
	VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16;
	VAR(uint16, EPSDIAGSRVCS_VAR) DAQSelection_Cnt_T_u16;
	VAR(uint8, EPSDIAGSRVCS_VAR) ErrorFlag_Cnt_T_lgc;
	
	Resp_Uls_T_u08 = 0U;
	ErrorFlag_Cnt_T_lgc = 0U;
	DAQSelection_Cnt_T_u16 = 0U;
	
	/* Validate event selection */
	if(Event_Cnt_T_u08 >= (uint8)D_XCP_DAQ_MAXEVENT)
	{
		XcpUserFreeDaq(); /* Clear all DAQ settings due to error */
		Resp_Uls_T_u08 = XcpErrorHandler(D_XCP_ERR_UNKOWNERR);
	}
	else
	{
		/* Allocate DAQ */
		XcpUserFreeDaq();
		Resp_Uls_T_u08 = XcpUserAllocDaq(1U);
		ErrorFlag_Cnt_T_lgc |= XCP_ERR_Determine_m(Resp_Uls_T_u08);
		
		if(ErrorFlag_Cnt_T_lgc == D_XCP_NOERROR)
		{
			DAQSelection_Cnt_T_u16 = bytesToWord_m(D_XCP_USERCMD_DAQCMD_PREDEFINED, PreBltDaqNum_T_Cnt_u08);
			PIDidx_Cnt_T_u16 = DiagSrvcs_PIDIdxSearch(DAQSelection_Cnt_T_u16);
			
			if(PIDidx_Cnt_T_u16 == D_PIDTBL_INVLDPID_ULS_U16)
			{
				Resp_Uls_T_u08 = XcpErrorHandler(D_XCP_ERR_INVLDPREDEFDAQ);
			}
			else
			{
				if(t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].active == TRUE)
				{
					switch(DAQSelection_Cnt_T_u16)
					{
						case D_STATICDAQ_MANUFSRVC_MTRLEARNING:
							Resp_Uls_T_u08 = StaticDAQ_ManufSrvc_MtrLearning(PIDidx_Cnt_T_u16, D_XCP_PREDEFDAQ_DAQNUM);
						break; 
						case D_STATICDAQ_MANUFSRVC_TRQRATIO:
							Resp_Uls_T_u08 = StaticDAQ_ManufSrvc_TrqRatio(PIDidx_Cnt_T_u16, D_XCP_PREDEFDAQ_DAQNUM);
						break; 
						case D_STATICDAQ_MANUFSRVC_TRQSWEEP:
							Resp_Uls_T_u08 = StaticDAQ_ManufSrvc_TrqSweep(PIDidx_Cnt_T_u16, D_XCP_PREDEFDAQ_DAQNUM);
						break; 
						case D_STATICDAQ_MANUFSRVC_STATICEFFNLONGSWEEP:
							Resp_Uls_T_u08 = StaticDAQ_ManufSrvc_StaticEffnLongSweep(PIDidx_Cnt_T_u16, D_XCP_PREDEFDAQ_DAQNUM);
						break; 
						case D_STATICDAQ_MANUFSRVC_ROTORSTIFFNESS:
							Resp_Uls_T_u08 = StaticDAQ_ManufSrvc_RotorStiffness(PIDidx_Cnt_T_u16, D_XCP_PREDEFDAQ_DAQNUM);
						break; 
						case D_STATICDAQ_MANUFSRVC_NOISE:
							Resp_Uls_T_u08 = StaticDAQ_ManufSrvc_Noise(PIDidx_Cnt_T_u16, D_XCP_PREDEFDAQ_DAQNUM);
						break;
						case D_STATICDAQ_MANUFSRVC_POSITION:
							Resp_Uls_T_u08 = StaticDAQ_ManufSrvc_Position(PIDidx_Cnt_T_u16, D_XCP_PREDEFDAQ_DAQNUM);
						break;
						case D_STATICDAQ_MANUFSRVC_TURNSCNTRSPIDATA:
							Resp_Uls_T_u08 = StaticDAQ_ManufSrvc_TurnsCounterSPIData(PIDidx_Cnt_T_u16, D_XCP_PREDEFDAQ_DAQNUM);
						break;
						case D_STATICDAQ_MANUFSRVC_MOTORCURRENT:
							Resp_Uls_T_u08 = StaticDAQ_ManufSrvc_MotorCurrent(PIDidx_Cnt_T_u16, D_XCP_PREDEFDAQ_DAQNUM);
						break;
						case D_STATICDAQ_MANUFSRVC_ANLGTRQSNSRINFO:
							Resp_Uls_T_u08 = StaticDAQ_ManufSrvc_AnlgTrqSnsrInfo(PIDidx_Cnt_T_u16, D_XCP_PREDEFDAQ_DAQNUM);
						break;
						case D_STATICDAQ_MANUFSRVC_STATICEFFNLONGSWEEPANALOG:
							Resp_Uls_T_u08 = StaticDAQ_ManufSrvc_StaticEffnLongSweepAnalog(PIDidx_Cnt_T_u16, D_XCP_PREDEFDAQ_DAQNUM);
						break;
						case D_STATICDAQ_MANUFSRVC_DIGTRQANDHWPOS:
							Resp_Uls_T_u08 = StaticDAQ_ManufSrvc_DigTrqAndPosition(PIDidx_Cnt_T_u16, D_XCP_PREDEFDAQ_DAQNUM);
						break;
						case D_STATICDAQ_MANUFSRVC_VERNERR:
							Resp_Uls_T_u08 = StaticDAQ_ManufSrvc_VernErrAndPositionAndTrq(PIDidx_Cnt_T_u16, D_XCP_PREDEFDAQ_DAQNUM);
						break;
						case D_STATICDAQ_MANUFSRVC_POSITION2:
							Resp_Uls_T_u08 = StaticDAQ_ManufSrvc_Position2(PIDidx_Cnt_T_u16, D_XCP_PREDEFDAQ_DAQNUM);
						break;
						case D_STATICDAQ_MANUFSRVC_TORQUE:
							Resp_Uls_T_u08 = StaticDAQ_ManufSrvc_Torque(PIDidx_Cnt_T_u16, D_XCP_PREDEFDAQ_DAQNUM);
						break;
						default:
							XcpUserFreeDaq(); /* Clear all DAQ settings due to error */
							Resp_Uls_T_u08 = XcpErrorHandler(D_XCP_ERR_INVLDPREDEFDAQ);
						break;
					}
					
					if(Resp_Uls_T_u08 == D_XCP_NOERROR)
					{
						Resp_Uls_T_u08 = XcpUserSetDaqListMode(  D_XCP_USRDEFDAQ_LISTMODE, D_XCP_USRDEFDAQ_DAQNUM, Event_Cnt_T_u08, Prescale_Uls_T_u08);	
					}
				}
				else
				{
					Resp_Uls_T_u08 = XcpErrorHandler(D_XCP_ERR_INACTIVESRV);
				}
			}
		}
		else
		{
			Resp_Uls_T_u08 = XcpErrorHandler(D_XCP_ERR_INVLDEVENT);
		}
	}
	
	return Resp_Uls_T_u08;
}

/*****************************************************************************
 *
 *	Function Name: 	   XcpUserRoutineCmd
 *
 *	Description:       Handling function for XCP system commands (User command 0x00)
 *
 *	Inputs:		       SysCmdID_Cnt_T_u16 - System Command to execute
 * 					   t_Param_Uls_T_u08 - Control bytes for sys command
 *
 *	Outputs:	       Resp_T_Uls_u08: Command response
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) XcpUserRoutineCmd(VAR(uint16, EPSDIAGSRVCS_VAR) SysCmdID_Cnt_T_u16,
														P2VAR(uint8, EPSDIAGSRVCS_VAR, EPSDIAGSRVCS_VAR) t_Param_Uls_T_u08)
{
	VAR(uint8, EPSDIAGSRVCS_VAR) Resp_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;
	VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16;
	VAR(uint16, EPSDIAGSRVCS_VAR) CtrlByteLen_Cnt_T_u16;
	VAR(uint16, EPSDIAGSRVCS_VAR) RespLen_Cnt_T_u16;
	VAR(uint8, EPSDIAGSRVCS_VAR) ActiveSrv_Cnt_T_u08;
	VAR(uint8, EPSDIAGSRVCS_VAR) PIDType_Cnt_T_u08;
	VAR(DiagFuncRef, EPSDIAGSRVCS_VAR) DiagFuncPtr;
	
	Resp_Uls_T_u08 = 0U;
	PIDidx_Cnt_T_u16 = DiagSrvcs_PIDIdxSearch(SysCmdID_Cnt_T_u16);
	ActiveSrv_Cnt_T_u08 = t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].active;
	PIDType_Cnt_T_u08 = t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].type;
	
	if ((PIDidx_Cnt_T_u16 != D_PIDTBL_INVLDPID_ULS_U16) && (ActiveSrv_Cnt_T_u08 != (uint8)D_PID_NOTACTIVE_CNT_U8) && (PIDType_Cnt_T_u08 == D_PIDTBL_RIDTYPE))
	{
		CtrlByteLen_Cnt_T_u16 = t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length;

		DiagFuncPtr = t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].address.func;
		Resp_Uls_T_u08 = DiagFuncPtr(1U, t_Param_Uls_T_u08, CtrlByteLen_Cnt_T_u16, &RespLen_Cnt_T_u16);

		if(Resp_Uls_T_u08 != D_XCP_NOERROR)
		{
			Resp_Uls_T_u08 = XcpISOErrorConverter(Resp_Uls_T_u08);
			Resp_Uls_T_u08 = XcpErrorHandler(Resp_Uls_T_u08);
		}
	}
	else
	{
		Resp_Uls_T_u08 = XcpErrorHandler(D_XCP_ERR_INACTIVESRV);
	}
	
	return(Resp_Uls_T_u08);
}

/*****************************************************************************
 *
 *	Function Name: 	   XcpUserPIDSrvc
 *
 *	Description:       Handling function for PID commands 
 *
 *	Inputs:		       PID_Cnt_T_u16 - PID to execute
 * 					   t_Param_Uls_T_u08 - Data passed by the user
 *
 *	Outputs:	       Resp_T_Uls_u08: Command response
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) XcpUserPIDSrvc(VAR(uint16, EPSDIAGSRVCS_VAR) PID_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) SrvcType_Cnt_T_u08,
														 P2CONST(uint8, EPSDIAGSRVCS_VAR, EPSDIAGSRVCS_VAR) t_Param_Uls_T_u08)
{
	/* Outputs */
	VAR(uint8, EPSDIAGSRVCS_VAR) Resp_T_Uls_u08 = (uint8)D_XCP_USRCMDRESP_OK;
	
	/* Locals */
	VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16;
	VAR(uint32, EPSDIAGSRVCS_VAR) SelectedValue_Cnt_T_u32 = 0u;
	
	
	Resp_T_Uls_u08 = D_ZERO_CNT_U8;
	
	PIDidx_Cnt_T_u16 = DiagSrvcs_PIDIdxSearch(PID_Cnt_T_u16);
	
	if((PIDidx_Cnt_T_u16 != D_PIDTBL_INVLDPID_ULS_U16) && (t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].active == TRUE) && (t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].type == D_PIDTBL_VARTYPE))
	{
		switch(SrvcType_Cnt_T_u08)
		{
			case D_XCP_PID_READSRV:
				if(t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length <= D_XCP_PID_SNGLFRM_RESPLEN)
				{
					Resp_T_Uls_u08 = XcpPIDReadResp(t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length, (uint32 *)t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].address.var, D_XCP_PID_SNGLFRM_RESP);
				}
				else
				{
					/* multi frame response */
					Resp_T_Uls_u08 = XcpPIDReadResp(t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length, (uint32 *)t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].address.var, D_XCP_PID_MULTIFRM_RESP);
				}			
			break;
			case D_XCP_PID_WRITESRV:
				if(t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].access == (uint8)D_PID_READWRITE_CNT_U8)
				{
					if(t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length <= D_XCP_PID_SNGLFRM_WRITELMT)
					{
						/* single frame */
						switch(t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length)
						{
							case D_XCP_PID_BYTELEN:
								SelectedValue_Cnt_T_u32 = (uint8)t_Param_Uls_T_u08[0]; /* PRQA S 492 */
							break;
							case D_XCP_PID_WORDLEN:
								SelectedValue_Cnt_T_u32 = (uint16)bytesToWord_m(t_Param_Uls_T_u08[0u], t_Param_Uls_T_u08[1u]); /* PRQA S 492 */
							break;
							case D_XCP_PID_FLOATLEN:
								SelectedValue_Cnt_T_u32 = uint8LeftShftuint32_m(t_Param_Uls_T_u08[0u], D_MSBYTESHIFT_CNT_U16); /* PRQA S 492 */
								SelectedValue_Cnt_T_u32 |= uint8LeftShftuint32_m(t_Param_Uls_T_u08[1u], D_WORDSHIFT_CNT_U16); /* PRQA S 492 */
								SelectedValue_Cnt_T_u32 |= uint8LeftShftuint32_m(t_Param_Uls_T_u08[2u], D_BYTESHIFT_CNT_U16); /* PRQA S 492 */
								SelectedValue_Cnt_T_u32 |= uint8LeftShftuint32_m(t_Param_Uls_T_u08[3u], D_ZERO_CNT_U8); /* PRQA S 492 */
							break;
							default:
								Resp_T_Uls_u08 = XcpErrorHandler(D_XCP_ERR_CONFIGERR);
							break;
						}
						
						/* write value to memory location */
						*(uint32 *)t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].address.var = SelectedValue_Cnt_T_u32;

						/* If the PID has an NvM Block associated with it, call writeblock once PID is completed writing */
						if (t_DiagSrv_PIDtbl[EpsXcpSrvc_XCPPIDActive_Cnt_M_u16].length2.block != 0)
						{
							(void)NvM_WriteBlock(t_DiagSrv_PIDtbl[EpsXcpSrvc_XCPPIDActive_Cnt_M_u16].length2.block, NULL_PTR);
						}
					}
					else
					{
						/* multi frame */
						XCP_UserCmd_RespLen_m(3U);
						XCP_PID_WRITEMULTIFRMLENHI_m(MSB(t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length));
						XCP_PID_WRITEMULTIFRMLENLO_m(LSB(t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length));
						XcpUserSetMta(ApplXcpGetPointer(0, (uint32)t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].address.var), 0xFFU);
						EpsXcpSrvc_XCPPIDDataToProcess_Cnt_M_u16 = t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length; /* Capture amount of data to be downloaded */
						EpsXcpSrvc_XCPPIDActive_Cnt_M_u16 = PIDidx_Cnt_T_u16; /* Capture XCP PID Index Requested */
					}
				}
				else
				{
					Resp_T_Uls_u08 = XcpErrorHandler(D_XCP_ERR_SRVREADONLY);
				}
			break;
			default:
				Resp_T_Uls_u08 = XcpErrorHandler(D_XCP_ERR_CONFIGERR);
			break;
		}
	}
	else
	{
		if(PIDidx_Cnt_T_u16 == D_PIDTBL_INVLDPID_ULS_U16)
		{
			Resp_T_Uls_u08 = XcpErrorHandler(D_XCP_ERR_INVLDSRVID);
		}
		else
		{
			Resp_T_Uls_u08 = XcpErrorHandler(D_XCP_ERR_INACTIVESRV);
		}
	}

	return (Resp_T_Uls_u08);
}

/*****************************************************************************
 *
 *	Function Name: 	   ProcessXCPPID
 *
 *	Description:       PID reading response
 *
 *	Inputs:		       PIDSize_Cnt_T_u16 - Number of bytes to
 * 					   ReadValue_Cnt_T_u32 - Value of the PID
 * 					   Type_Cnt_T_u08 - Single or multi frame response type
 *
 *	Outputs:	       Resp_T_Uls_u08: Command response
 *
 *****************************************************************************/
FUNC(void, EPSXCPDIAGSRVCS_CODE) ProcessXCPPID(VAR(uint8, EPSDIAGSRVCS_VAR) Size_Cnt_T_u08)
{
	if ((EpsXcpSrvc_XCPPIDDataToProcess_Cnt_M_u16 != 0U) && (EpsXcpSrvc_XCPPIDActive_Cnt_M_u16 != 0U))
	{
		if (EpsXcpSrvc_XCPPIDDataToProcess_Cnt_M_u16 > Size_Cnt_T_u08)
		{
			EpsXcpSrvc_XCPPIDDataToProcess_Cnt_M_u16 -= Size_Cnt_T_u08;
		}
		else
		{
			/* If the PID has an NvM Block associated with it, call writeblock once PID is completed writing */
			if (t_DiagSrv_PIDtbl[EpsXcpSrvc_XCPPIDActive_Cnt_M_u16].length2.block != 0U)
			{
				(void)NvM_WriteBlock(t_DiagSrv_PIDtbl[EpsXcpSrvc_XCPPIDActive_Cnt_M_u16].length2.block, NULL_PTR);
			}
			EpsXcpSrvc_XCPPIDDataToProcess_Cnt_M_u16 = 0U;
			EpsXcpSrvc_XCPPIDActive_Cnt_M_u16 = 0U;
		}
	}
}

/*****************************************************************************
 *
 *	Function Name: 	   XcpPIDReadResp
 *
 *	Description:       PID reading response
 *
 *	Inputs:		       PIDSize_Cnt_T_u16 - Number of bytes to 
 * 					   ReadValue_Cnt_T_u32 - Value of the PID
 * 					   Type_Cnt_T_u08 - Single or multi frame response type
 *
 *	Outputs:	       Resp_T_Uls_u08: Command response
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) XcpPIDReadResp(VAR(uint16, EPSDIAGSRVCS_VAR) PIDSize_Cnt_T_u16, P2CONST(uint32, EPSDIAGSRVCS_VAR, EPSDIAGSRVCS_VAR) ReadValue_Cnt_T_ptr,
														VAR(uint8, EPSDIAGSRVCS_VAR) Type_Cnt_T_u08)
{
	/* outputs */
	
	/* locals */
	VAR(uint8, EPSDIAGSRVCS_VAR) Resp_T_Uls_u08 = (uint8)D_XCP_USRCMDRESP_OK;
	VAR(uint8, EPSDIAGSRVCS_VAR) I_Cnt_T_u08;
	
	VAR(boolean, EPSDIAGSRVCS_VAR) ValidEntry_Cnt_T_lgc;
	VAR(uint8, EPSDIAGSRVCS_VAR) ByteOffset_Cnt_T_u08 = 0u;
	VAR(uint8, EPSDIAGSRVCS_VAR) ByteShift_Cnt_T_u08 = 0u;
	VAR(uint8, EPSDIAGSRVCS_VAR) LoopLimit_Cnt_T_u08 = 0u;
	
	
	ValidEntry_Cnt_T_lgc = FALSE;	
	switch(Type_Cnt_T_u08)
	{
		case D_XCP_PID_SNGLFRM_RESP:
			
			XCP_UserCmd_RespLen_m((uint8)(D_XCP_PID_READRESP_BASELEN + PIDSize_Cnt_T_u16));
			XCP_PID_RESPTYPE_m(D_XCP_PID_SNGLFRM_RESP);
			XCP_PID_SINGLEFRAMELEN_m((uint8)PIDSize_Cnt_T_u16);
			switch(PIDSize_Cnt_T_u16)
			{
				case D_XCP_PID_BYTELEN:
					ValidEntry_Cnt_T_lgc = TRUE;
					ByteOffset_Cnt_T_u08 = 0U;
					ByteShift_Cnt_T_u08 = 0U;
					LoopLimit_Cnt_T_u08 = D_XCP_PID_BYTELEN;
				break;
				case D_XCP_PID_WORDLEN:
					ValidEntry_Cnt_T_lgc = TRUE;
					ByteOffset_Cnt_T_u08 = D_ONE_CNT_U8;
					ByteShift_Cnt_T_u08 = D_BYTESHIFT_CNT_U8;
					LoopLimit_Cnt_T_u08 = D_XCP_PID_WORDLEN;
				break;
				case D_XCP_PID_FLOATLEN:
					ValidEntry_Cnt_T_lgc = TRUE;
					ByteOffset_Cnt_T_u08 = 3U;
					ByteShift_Cnt_T_u08 = D_BYTESHIFT_CNT_U8;
					LoopLimit_Cnt_T_u08 = D_XCP_PID_FLOATLEN;
				break;
				default:
					ValidEntry_Cnt_T_lgc = FALSE;
					Resp_T_Uls_u08 = XcpErrorHandler(D_XCP_ERR_CONFIGERR);
				break;
			}
			
			/* Process data */
			if(ValidEntry_Cnt_T_lgc == TRUE)
			{
				for ( I_Cnt_T_u08 = 0U; I_Cnt_T_u08 < LoopLimit_Cnt_T_u08; I_Cnt_T_u08++)
				{
					XCP_PID_SINGLEFRAMEDATA_m(I_Cnt_T_u08) = (uint8)((*ReadValue_Cnt_T_ptr >> (ByteShift_Cnt_T_u08 * (ByteOffset_Cnt_T_u08 - I_Cnt_T_u08))) & D_BYTEMASK_ULS_U8);
				}	
			}
		break;
		case D_XCP_PID_MULTIFRM_RESP:
			XCP_UserCmd_RespLen_m((uint8)(D_XCP_PID_READRESP_BASELEN + PIDSize_Cnt_T_u16));
			XCP_PID_RESPTYPE_m(D_XCP_PID_MULTIFRM_RESP);
			XCP_PID_MULTIFRAMELENHI_m(MSB(PIDSize_Cnt_T_u16));
			XCP_PID_MULTIFRAMELENLO_m(LSB(PIDSize_Cnt_T_u16));
			/* Note: ApplXcpGetPointer expects the address as a uint32 value, which it will turn into the correct
			 * pointer for the SetMta command, this will cause a MISRA warning */
			XcpUserSetMta(ApplXcpGetPointer(0U, (uint32)ReadValue_Cnt_T_ptr), 0xFFU); /* PRQA S 306 */
		break;
		default:
			Resp_T_Uls_u08 = XcpErrorHandler(D_XCP_ERR_CONFIGERR);
		break;
	}
	
	return(Resp_T_Uls_u08);
}

/*****************************************************************************
 *
 *	User XCP Service Supporting Functions
 *
 *****************************************************************************/

/*****************************************************************************
 *
 *	Function Name: 	   XcpErrorHandler
 *
 *	Description:       Error handler for xcp user information. Sets proper
 * 					   response length and data bytes.   
 *
 *	Inputs:		       ErrorCode_Uls_T_u08: Error code to place into return
 * 						message. 
 *
 *	Outputs:	       Error_Uls_T_u08: Error condition for response. 
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) XcpErrorHandler( VAR(uint8, EPSDIAGSRVCS_VAR) ErrorCode_Uls_T_u08)
{
	XCP_Error_SetRespLen_m();
	XCP_ERR_ErrorCode_m(ErrorCode_Uls_T_u08);
	
	return ((uint8)D_XCP_USRCMDRESP_ERR);
}

/*****************************************************************************
 *
 *	Function Name: 	   XcpODTEntrySetup
 *
 *	Description:       Takes a valid list of PIDs and fills in ODTs for a DAQ
 *
 *	Inputs:		       t_PIDs_Uls_T_u16 - Table of PIDs
 * 					   PIDCount_Cnt_T_u08 - DAQ Number
 * 					   DAQNum_Cnt_T_u08 - Number of DAQ entry 
 *
 *	Outputs:	       Resp_Uls_T_u08: Report errors if any. 
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) XcpODTEntrySetup(	P2CONST(uint16, EPSDIAGSRVCS_VAR, EPSDIAGSRVCS_VAR) t_PIDs_Uls_T_u16,
															VAR(uint16, EPSDIAGSRVCS_VAR) PIDCount_Cnt_T_u08,
															VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08)
{
	/* output */
	VAR(uint8, EPSDIAGSRVCS_VAR) Resp_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;
	
	/* locals */
	VAR(uint8, EPSDIAGSRVCS_VAR) ErrorFlag_Uls_T_u08;
	VAR(uint8, EPSDIAGSRVCS_VAR) FirstODTByteLmt_Cnt_T_u08;
	VAR(float32, EPSDIAGSRVCS_VAR) NumOfODTReq_Cnt_T_f32;
	VAR(uint8, EPSDIAGSRVCS_VAR) NumOfODTReq_Cnt_T_u08;
	VAR(uint8, EPSDIAGSRVCS_VAR) ODTByteCntr_Cnt_T_u08;
	VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Uls_T_u16;
	VAR(uint16, EPSDIAGSRVCS_VAR) Size_Uls_T_u16;
	VAR(uint8, EPSDIAGSRVCS_VAR) ODTEntry_Cnt_T_u08;
	VAR(uint8, EPSDIAGSRVCS_VAR) ODTEntryCntr_Cnt_T_u08;
	VAR(uint8, EPSDIAGSRVCS_VAR) ODTEntryLimit_Cnt_T_u08;
	VAR(uint8, EPSDIAGSRVCS_VAR) TotalPIDBytes_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) PIDidx_Cnt_T_u16;

	/* loop vars */
	VAR(uint8, EPSDIAGSRVCS_VAR) I_Cnt_T_u08, X_Cnt_T_u08;
	
	Resp_Uls_T_u08 = 0U;
	ErrorFlag_Uls_T_u08 = 0U;	
	TotalPIDBytes_Cnt_T_u08 = 0U;
	
	/* Check all PIDs to make sure they are active */
	for (I_Cnt_T_u08 = 0U; I_Cnt_T_u08 < PIDCount_Cnt_T_u08; I_Cnt_T_u08++)
	{
		PIDidx_Cnt_T_u16 = DiagSrvcs_PIDIdxSearch(t_PIDs_Uls_T_u16[I_Cnt_T_u08]); /* PRQA S 492 */
		if((t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].active == TRUE) && (t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].type == D_PIDTBL_VARTYPE)) /* PRQA S 492 */
		{
			TotalPIDBytes_Cnt_T_u08 += (uint8)t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length; /* PRQA S 492 */
		}
		else
		{
			Resp_Uls_T_u08 = XcpErrorHandler(D_XCP_ERR_INACTIVESRV);
		}
	}
	
	/* Adjust first ODT for timestamp, if required */
	#if defined ( XCP_ENABLE_DAQ_TIMESTAMP )
		FirstODTByteLmt_Cnt_T_u08 = (uint8)D_XCP_MAX_ODT_ENTRY_SIZE - (uint8)sizeof(XcpDaqTimestampType);
	#else
		FirstODTByteLmt_Cnt_T_u08 = (uint8)D_XCP_MAX_ODT_ENTRY_SIZE - D_ONE_CNT_U8;
	#endif
	
	/* Determine number of ODTs to use */
	NumOfODTReq_Cnt_T_u08 = D_ONE_CNT_U8;
	if((TotalPIDBytes_Cnt_T_u08 > FirstODTByteLmt_Cnt_T_u08) && (Resp_Uls_T_u08 == D_ZERO_CNT_U8))
	{
		/* More than one ODT required, determine the number by the number of bytes in the variables passed via the DAQ request */
		NumOfODTReq_Cnt_T_f32 = ((float32)((((float32)TotalPIDBytes_Cnt_T_u08 - (float32)FirstODTByteLmt_Cnt_T_u08) / (float32)D_XCP_DAQRESP_FULLLEN) + 0.5F));
		
		if((NumOfODTReq_Cnt_T_f32 > D_ZERO_ULS_F32) && (NumOfODTReq_Cnt_T_f32 < D_ONE_ULS_F32))
		{
			 NumOfODTReq_Cnt_T_u08++;
		}
		
		NumOfODTReq_Cnt_T_u08 += (uint8)NumOfODTReq_Cnt_T_f32;
	}		

	if(Resp_Uls_T_u08 == D_XCP_NOERROR)
	{
		/* Allocate ODTs required */
		Resp_Uls_T_u08 = XcpUserAllocOdt( DAQNum_Cnt_T_u08, NumOfODTReq_Cnt_T_u08 );
		ErrorFlag_Uls_T_u08 |= XCP_ERR_Determine_m(Resp_Uls_T_u08);
		
		if(ErrorFlag_Uls_T_u08 == D_ZERO_CNT_U8)
		{
			ODTByteCntr_Cnt_T_u08 = TotalPIDBytes_Cnt_T_u08;
			for (I_Cnt_T_u08 = 0U; I_Cnt_T_u08 < NumOfODTReq_Cnt_T_u08; I_Cnt_T_u08++)
			{
				if ( I_Cnt_T_u08 == 0U )
				{
					if(ODTByteCntr_Cnt_T_u08 < FirstODTByteLmt_Cnt_T_u08)
					{
						Resp_Uls_T_u08 = XcpUserAllocOdtEntry( DAQNum_Cnt_T_u08, I_Cnt_T_u08, ODTByteCntr_Cnt_T_u08 );
						ErrorFlag_Uls_T_u08 |= XCP_ERR_Determine_m(Resp_Uls_T_u08);
						
						ODTByteCntr_Cnt_T_u08 -= ODTByteCntr_Cnt_T_u08;
					}
					else
					{
						Resp_Uls_T_u08 = XcpUserAllocOdtEntry( DAQNum_Cnt_T_u08, I_Cnt_T_u08, FirstODTByteLmt_Cnt_T_u08 );
						ErrorFlag_Uls_T_u08 |= XCP_ERR_Determine_m(Resp_Uls_T_u08);

						ODTByteCntr_Cnt_T_u08 -= FirstODTByteLmt_Cnt_T_u08;
					}
				}
				else
				{
					if( ODTByteCntr_Cnt_T_u08 >= (uint8)D_XCP_DAQRESP_FULLLEN )
					{
						Resp_Uls_T_u08 = XcpUserAllocOdtEntry( DAQNum_Cnt_T_u08, I_Cnt_T_u08, (uint8)D_XCP_DAQRESP_FULLLEN );
						ErrorFlag_Uls_T_u08 |= XCP_ERR_Determine_m(Resp_Uls_T_u08);

						ODTByteCntr_Cnt_T_u08 -= D_XCP_DAQRESP_FULLLEN;
					}
					else
					{
						/* Last run of the FOR loop */
						Resp_Uls_T_u08 = XcpUserAllocOdtEntry( DAQNum_Cnt_T_u08, I_Cnt_T_u08, ODTByteCntr_Cnt_T_u08 );
						ErrorFlag_Uls_T_u08 |= XCP_ERR_Determine_m(Resp_Uls_T_u08);
					}	
				}
			}
		
			/* process valid parameters */
			ODTEntry_Cnt_T_u08 = 0U;
			ODTEntryCntr_Cnt_T_u08 = 0U;
			ODTEntryLimit_Cnt_T_u08 = FirstODTByteLmt_Cnt_T_u08;
			Resp_Uls_T_u08 = XcpUserSetDaqPtr(DAQNum_Cnt_T_u08, ODTEntry_Cnt_T_u08, D_ZERO_CNT_U8);
			ErrorFlag_Uls_T_u08 |= XCP_ERR_Determine_m(Resp_Uls_T_u08);
		
			for (I_Cnt_T_u08 = 0U; I_Cnt_T_u08 < PIDCount_Cnt_T_u08; I_Cnt_T_u08++)
			{
				PIDidx_Uls_T_u16 = DiagSrvcs_PIDIdxSearch(t_PIDs_Uls_T_u16[I_Cnt_T_u08]); /* PRQA S 492 */
				if( PIDidx_Uls_T_u16 == D_PIDTBL_INVLDPID_ULS_U16 )
				{
					XcpUserFreeDaq(); /* Clear all DAQ settings due to error */
					ErrorFlag_Uls_T_u08 = TRUE;
					Resp_Uls_T_u08 = XcpErrorHandler(D_XCP_ERR_NOVLDDAQPID);
					break; /* end the loop since there is an error */
				}
				else
				{
					Size_Uls_T_u16 = t_DiagSrv_PIDtbl[PIDidx_Uls_T_u16].length;
					for (X_Cnt_T_u08 = 0U; X_Cnt_T_u08 < Size_Uls_T_u16; X_Cnt_T_u08++)
					{
						if (ODTEntryCntr_Cnt_T_u08 < ODTEntryLimit_Cnt_T_u08)
						{
							Resp_Uls_T_u08 = XcpUserWriteDaq(0xFFU, D_ONE_CNT_U8, D_ZERO_CNT_U8, (vuint32)&((uint8 *)t_DiagSrv_PIDtbl[PIDidx_Uls_T_u16].address.var)[X_Cnt_T_u08]);
							ErrorFlag_Uls_T_u08 |= XCP_ERR_Determine_m(Resp_Uls_T_u08);
						}
						else
						{
							ODTEntryCntr_Cnt_T_u08 = 0U;
							ODTEntry_Cnt_T_u08++;
							ODTEntryLimit_Cnt_T_u08 = (uint8)D_XCP_DAQRESP_FULLLEN;
							
							Resp_Uls_T_u08 = XcpUserSetDaqPtr(D_XCP_USRDEFDAQ_DAQNUM, ODTEntry_Cnt_T_u08, D_ZERO_CNT_U8);
							ErrorFlag_Uls_T_u08 |= XCP_ERR_Determine_m(Resp_Uls_T_u08);
							
							Resp_Uls_T_u08 = XcpUserWriteDaq(0xFFU, D_ONE_CNT_U8, D_ZERO_CNT_U8, (vuint32)&((uint8 *)t_DiagSrv_PIDtbl[PIDidx_Uls_T_u16].address.var)[X_Cnt_T_u08]);
							ErrorFlag_Uls_T_u08 |= XCP_ERR_Determine_m(Resp_Uls_T_u08);
						}
						ODTEntryCntr_Cnt_T_u08++;
					}
				}
			}
		}
		else
		{
			Resp_Uls_T_u08 = XcpErrorHandler(D_XCP_ERR_MEMALLOCERR);		
		}
	}
	
	return (Resp_Uls_T_u08);
}


/*****************************************************************************
 *
 *	Function Name: 	   XcpISOErrorConverter
 *
 *	Description:       This function converts an ISO error into an XCP error
 *					   code.
 *
 *	Inputs:		       ErrorCode_Cnt_T_u08 - ISO error
 *
 *	Outputs:	       Resp_Uls_T_u08: Converted XCP error code.
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) XcpISOErrorConverter(VAR(uint8, EPSDIAGSRVCS_VAR) ErrorCode_Cnt_T_u08)
{
	VAR(uint8, EPSDIAGSRVCS_VAR) Resp_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;

	switch(ErrorCode_Cnt_T_u08)
	{
		case D_EPSNRCSUBFUNCNOTSUPP_CNT_U08:
			Resp_Uls_T_u08 = D_XCP_ERR_FUNCNOTSUPP;
		break;
		case D_EPSNRCINVALIDFORMAT_CNT_U08:
			Resp_Uls_T_u08 = D_XCP_ERR_INVLFORMAT;
		break;
		case D_EPSNRCCONDNOTCORRECT_CNT_U08:
			Resp_Uls_T_u08 = D_XCP_ERR_CONDNOTCORRECT;
		break;
		case D_EPSNRCREQOUTOFRANGE_CNT_U08:
			Resp_Uls_T_u08 = D_XCP_ERR_REQOUTOFRANGE;
		break;
		default:
			Resp_Uls_T_u08 = D_XCP_ERR_UNKOWNERR;
		break;
	}

	return Resp_Uls_T_u08;
}

/*****************************************************************************
 *
 *	Pre built DAQ Services 
 *
 *****************************************************************************/

/*****************************************************************************
 *
 *	Function Name: 	   StaticDAQ_ManufSrvc_MtrLearning
 *
 *	Description:       Manufacturing Service DAQ for Motor Learning
 *
 *	Inputs:		       PIDidx_Cnt_T_u16 - Index of the PID entry
 * 					   DAQNum_Cnt_T_u08 - DAQ list number. (Typically 0)
 *
 *	Outputs:	       Result_Uls_T_u08 - Command response. 
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_MtrLearning(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08)
{
	/* output */
	VAR(uint8, EPSDIAGSRVCS_VAR) Result_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;
	
	/* local */
	VAR(uint16, EPSDIAGSRVCS_VAR) t_PIDlist_Cnt_T_u16[] = {D_XCP_PIDID_KEFBCKTYH, D_XCP_PIDID_RFBCKTYH, D_XCP_PIDID_SIN1MAXTYH,
													D_XCP_PIDID_SIN1MINTYH, D_XCP_PIDID_COS1MAXTYH, D_XCP_PIDID_COS1MINTYH};
	
	Result_Uls_T_u08 = XcpODTEntrySetup((uint16 *)&t_PIDlist_Cnt_T_u16[0], t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length, DAQNum_Cnt_T_u08);
	
	return Result_Uls_T_u08;
}


/*****************************************************************************
 *
 *	Function Name: 	   StaticDAQ_ManufSrvc_TrqRatio
 *
 *	Description:       Manufacturing Service DAQ for Torque Ratio
 *
 *	Inputs:		       PIDidx_Cnt_T_u16 - Index of the PID entry
 * 					   DAQNum_Cnt_T_u08 - DAQ list number. (Typically 0)
 *
 *	Outputs:	       Result_Uls_T_u08 - Command response. 
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_TrqRatio(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08)
{
	/* output */
	VAR(uint8, EPSDIAGSRVCS_VAR) Result_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;
	
	/* local */
	VAR(uint16, EPSDIAGSRVCS_VAR) t_PIDlist_Cnt_T_u16[] = {D_XCP_PIDID_MRFMTRTRQCMD};
	
	Result_Uls_T_u08 = XcpODTEntrySetup((uint16 *)&t_PIDlist_Cnt_T_u16[0], t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length, DAQNum_Cnt_T_u08);
	
	return Result_Uls_T_u08;
}

/*****************************************************************************
 *
 *	Function Name: 	   StaticDAQ_ManufSrvc_TrqSweep
 *
 *	Description:       Manufacturing Service DAQ for Torque Sweep
 *
 *	Inputs:		       PIDidx_Cnt_T_u16 - Index of the PID entry
 * 					   DAQNum_Cnt_T_u08 - DAQ list number. (Typically 0)
 *
 *	Outputs:	       Result_Uls_T_u08 - Command response. 
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_TrqSweep(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08)
{
	/* output */
	VAR(uint8, EPSDIAGSRVCS_VAR) Result_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;
	
	/* local */
	VAR(uint16, EPSDIAGSRVCS_VAR) t_PIDlist_Cnt_T_u16[] = {D_XCP_PIDID_T1_ANALOG_CNTS, D_XCP_PIDID_T2_ANALOG_CNTS,
															D_XCP_PIDID_T1_DIGITAL_DUTY, D_XCP_PIDID_T2_DIGITAL_DUTY};
	
	Result_Uls_T_u08 = XcpODTEntrySetup((uint16 *)&t_PIDlist_Cnt_T_u16[0], t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length, DAQNum_Cnt_T_u08);
	
	return Result_Uls_T_u08;
}

/*****************************************************************************
 *
 *	Function Name: 	   StaticDAQ_ManufSrvc_StaticEffnLongSweep
 *
 *	Description:       Manufacturing Service DAQ for Static Effort and Long Sweep
 *
 *	Inputs:		       PIDidx_Cnt_T_u16 - Index of the PID entry
 * 					   DAQNum_Cnt_T_u08 - DAQ list number. (Typically 0)
 *
 *	Outputs:	       Result_Uls_T_u08 - Command response. 
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_StaticEffnLongSweep(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08)
{
	/* output */
	VAR(uint8, EPSDIAGSRVCS_VAR) Result_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;
	
	/* local */
	VAR(uint16, EPSDIAGSRVCS_VAR) t_PIDlist_Cnt_T_u16[] = {D_XCP_PIDID_T1_ANALOG_CNTS, D_XCP_PIDID_T2_ANALOG_CNTS,
														D_XCP_PIDID_T1_DIGITAL_VOLTS, D_XCP_PIDID_T2_DIGITAL_VOLTS, D_XCP_PIDID_MRFCUMMTRPOS};
	
	Result_Uls_T_u08 = XcpODTEntrySetup((uint16 *)&t_PIDlist_Cnt_T_u16[0], t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length, DAQNum_Cnt_T_u08);
	
	return Result_Uls_T_u08;
	
}

/*****************************************************************************
 *
 *	Function Name: 	   StaticDAQ_ManufSrvc_RotorStiffness
 *
 *	Description:       Manufacturing Service DAQ for Rotor Stiffness
 *
 *	Inputs:		       PIDidx_Cnt_T_u16 - Index of the PID entry
 * 					   DAQNum_Cnt_T_u08 - DAQ list number. (Typically 0)
 *
 *	Outputs:	       Result_Uls_T_u08 - Command response. 
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_RotorStiffness(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08)
{
	/* output */
	VAR(uint8, EPSDIAGSRVCS_VAR) Result_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;
	
	/* local */
	VAR(uint16, EPSDIAGSRVCS_VAR) t_PIDlist_Cnt_T_u16[] = {D_XCP_PIDID_MRFCUMMTRPOS, D_XCP_PIDID_MRFMTRTRQCMD};
	
	Result_Uls_T_u08 = XcpODTEntrySetup((uint16 *)&t_PIDlist_Cnt_T_u16[0], t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length, DAQNum_Cnt_T_u08);
	
	return Result_Uls_T_u08;
}

/*****************************************************************************
 *
 *	Function Name: 	   StaticDAQ_ManufSrvc_Noise
 *
 *	Description:       Manufacturing Service DAQ for Noist testing. 
 *
 *	Inputs:		       PIDidx_Cnt_T_u16 - Index of the PID entry
 * 					   DAQNum_Cnt_T_u08 - DAQ list number. (Typically 0)
 *
 *	Outputs:	       Result_Uls_T_u08 - Command response. 
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_Noise(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08)
{
	/* output */
	VAR(uint8, EPSDIAGSRVCS_VAR) Result_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;
	
	/* local */
	VAR(uint16, EPSDIAGSRVCS_VAR) t_PIDlist_Cnt_T_u16[] = {D_XCP_PIDID_ABSHWPOSSCOM, D_XCP_PIDID_MRFMTRVEL};
	
	Result_Uls_T_u08 = XcpODTEntrySetup((uint16 *)&t_PIDlist_Cnt_T_u16[0], t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length, DAQNum_Cnt_T_u08);
	
	return Result_Uls_T_u08;
}

/*****************************************************************************
 *
 *	Function Name: 	   StaticDAQ_ManufSrvc_Position
 *
 *	Description:       Manufacturing Service DAQ for Position
 *
 *	Inputs:		       PIDidx_Cnt_T_u16 - Index of the PID entry
 * 					   DAQNum_Cnt_T_u08 - DAQ list number. (Typically 0)
 *
 *	Outputs:	       Result_Uls_T_u08 - Command response.
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_Position(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08)
{
	/* output */
	VAR(uint8, EPSDIAGSRVCS_VAR) Result_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;

	/* local */
	VAR(uint16, EPSDIAGSRVCS_VAR) t_PIDlist_Cnt_T_u16[] = {D_XCP_PIDID_T1_ANALOG_CNTS, D_XCP_PIDID_T2_ANALOG_CNTS,
															D_XCP_PIDID_P1_ANALOG_CNTS, D_XCP_PIDID_P2_ANALOG_CNTS, D_XCP_PIDID_RELPOS};

	Result_Uls_T_u08 = XcpODTEntrySetup((uint16 *)&t_PIDlist_Cnt_T_u16[0], t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length, DAQNum_Cnt_T_u08);

	return Result_Uls_T_u08;
}

/*****************************************************************************
 *
 *	Function Name: 	   StaticDAQ_ManufSrvc_TurnsCounterSPIData
 *
 *	Description:       Manufacturing Service DAQ for Turns Counter SPI Data
 *
 *	Inputs:		       PIDidx_Cnt_T_u16 - Index of the PID entry
 * 					   DAQNum_Cnt_T_u08 - DAQ list number. (Typically 0)
 *
 *	Outputs:	       Result_Uls_T_u08 - Command response.
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_TurnsCounterSPIData(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08)
{
	/* output */
	VAR(uint8, EPSDIAGSRVCS_VAR) Result_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;

	/* local */
	VAR(uint16, EPSDIAGSRVCS_VAR) t_PIDlist_Cnt_T_u16[] = {D_XCP_PIDID_TURNSCNTRSPIDATA};

	Result_Uls_T_u08 = XcpODTEntrySetup((uint16 *)&t_PIDlist_Cnt_T_u16[0], t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length, DAQNum_Cnt_T_u08);

	return Result_Uls_T_u08;
}

/*****************************************************************************
 *
 *	Function Name: 	   StaticDAQ_ManufSrvc_MotorCurrent
 *
 *	Description:       Manufacturing Service DAQ for Motor Current
 *
 *	Inputs:		       PIDidx_Cnt_T_u16 - Index of the PID entry
 * 					   DAQNum_Cnt_T_u08 - DAQ list number. (Typically 0)
 *
 *	Outputs:	       Result_Uls_T_u08 - Command response.
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_MotorCurrent(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08)
{
	/* output */
	VAR(uint8, EPSDIAGSRVCS_VAR) Result_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;

	/* local */
	VAR(uint16, EPSDIAGSRVCS_VAR) t_PIDlist_Cnt_T_u16[] = {D_XCP_PIDID_RAWCURR1, D_XCP_PIDID_RAWCURR2,
															D_XCP_PIDID_MTRCURRQAX, D_XCP_PIDID_MTRCURRDAX, D_XCP_PIDID_VALIDCURRSAMPLE};

	Result_Uls_T_u08 = XcpODTEntrySetup((uint16 *)&t_PIDlist_Cnt_T_u16[0], t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length, DAQNum_Cnt_T_u08);

	return Result_Uls_T_u08;
}

/*****************************************************************************
 *
 *	Function Name: 	   StaticDAQ_ManufSrvc_AnalogTorqueSensor Information
 *
 *	Description:       Manufacturing Service DAQ for AnalogTorque sensor only
 *
 *	Inputs:		       PIDidx_Cnt_T_u16 - Index of the PID entry
 * 					   DAQNum_Cnt_T_u08 - DAQ list number. (Typically 0)
 *
 *	Outputs:	       Result_Uls_T_u08 - Command response.
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_AnlgTrqSnsrInfo(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08)
{
	/* output */
	VAR(uint8, EPSDIAGSRVCS_VAR) Result_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;

	/* local */
	VAR(uint16, EPSDIAGSRVCS_VAR) t_PIDlist_Cnt_T_u16[] = {D_XCP_PIDID_T1_ANALOG_CNTS, D_XCP_PIDID_T2_ANALOG_CNTS};

	Result_Uls_T_u08 = XcpODTEntrySetup((uint16 *)&t_PIDlist_Cnt_T_u16[0], t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length, DAQNum_Cnt_T_u08);

	return Result_Uls_T_u08;
}

/*****************************************************************************
 *
 *	Function Name: 	   StaticDAQ_ManufSrvc_StaticEffnLongSweepAnalog
 *
 *	Description:       Manufacturing Service DAQ for Static Effort and Long Sweep
 *
 *	Inputs:		       PIDidx_Cnt_T_u16 - Index of the PID entry
 * 					   DAQNum_Cnt_T_u08 - DAQ list number. (Typically 0)
 *
 *	Outputs:	       Result_Uls_T_u08 - Command response. 
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_StaticEffnLongSweepAnalog(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08)
{
	/* output */
	VAR(uint8, EPSDIAGSRVCS_VAR) Result_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;
	
	/* local */
	VAR(uint16, EPSDIAGSRVCS_VAR) t_PIDlist_Cnt_T_u16[] = {D_XCP_PIDID_T1_ANALOG_CNTS, D_XCP_PIDID_T2_ANALOG_CNTS, D_XCP_PIDID_MRFCUMMTRPOS};
	
	Result_Uls_T_u08 = XcpODTEntrySetup((uint16 *)&t_PIDlist_Cnt_T_u16[0], t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length, DAQNum_Cnt_T_u08);
	
	return Result_Uls_T_u08;
	
}


/*****************************************************************************
 *
 *	Function Name: 	   StaticDAQ_ManufSrvc_DigTrqAndPosition
 *
 *	Description:       Manufacturing Service DAQ for Static Effort and Long Sweep
 *
 *	Inputs:		       PIDidx_Cnt_T_u16 - Index of the PID entry
 * 					   DAQNum_Cnt_T_u08 - DAQ list number. (Typically 0)
 *
 *	Outputs:	       Result_Uls_T_u08 - Command response.
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_DigTrqAndPosition(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08)
{
	/* output */
	VAR(uint8, EPSDIAGSRVCS_VAR) Result_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;

	/* local */
	VAR(uint16, EPSDIAGSRVCS_VAR) t_PIDlist_Cnt_T_u16[] = {D_XCP_PIDID_T1_SENT_HWNM, D_XCP_PIDID_T2_SENT_HWNM,
														   D_XCP_PIDID_I2CHWCOLPOS_HWDEG, D_XCP_PIDID_I2CHWSPURPOS_HWDEG,D_XCP_PIDID_I2CABSHWPOS_HWDEG};

	Result_Uls_T_u08 = XcpODTEntrySetup((uint16 *)&t_PIDlist_Cnt_T_u16[0], t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length, DAQNum_Cnt_T_u08);

	return Result_Uls_T_u08;

}

/*****************************************************************************
 *
 *	Function Name: 	   StaticDAQ_ManufSrvc_VernErrAndPositionAndTrq
 *
 *	Description:       Manufacturing Service DAQ for Vernier Error, position, and torque
 *
 *	Inputs:		       PIDidx_Cnt_T_u16 - Index of the PID entry
 * 					   DAQNum_Cnt_T_u08 - DAQ list number. (Typically 0)
 *
 *	Outputs:	       Result_Uls_T_u08 - Command response.
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_VernErrAndPositionAndTrq(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08)
{
	/* output */
	VAR(uint8, EPSDIAGSRVCS_VAR) Result_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;

	/* local */
	VAR(uint16, EPSDIAGSRVCS_VAR) t_PIDlist_Cnt_T_u16[] = {D_XCP_PIDID_DIGHWTRQT1_HWNM, D_XCP_PIDID_DIGHWTRQT2_HWNM,
															D_XCP_PIDID_I2CABSHWPOS_HWDEG_F32, D_XCP_PIDID_VERNDIAGERROR_DEG};

	Result_Uls_T_u08 = XcpODTEntrySetup((uint16 *)&t_PIDlist_Cnt_T_u16[0], t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length, DAQNum_Cnt_T_u08);

	return Result_Uls_T_u08;

}

/*****************************************************************************
 *
 *	Function Name: 	   StaticDAQ_ManufSrvc_Position2
 *
 *	Description:       Manufacturing Service DAQ for Digital T1, T2, AbsHwPOs, MRGMtrTrqCmd, VernierError
 *
 *	Inputs:		       PIDidx_Cnt_T_u16 - Index of the PID entry
 * 					   DAQNum_Cnt_T_u08 - DAQ list number. (Typically 0)
 *
 *	Outputs:	       Result_Uls_T_u08 - Command response.
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_Position2(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08)
{
	/* output */
	VAR(uint8, EPSDIAGSRVCS_VAR) Result_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;

	/* local */
	VAR(uint16, EPSDIAGSRVCS_VAR) t_PIDlist_Cnt_T_u16[] = {
			D_XCP_PIDID_DIGHWTRQT1_HWNM,
			D_XCP_PIDID_DIGHWTRQT2_HWNM,
			D_XCP_PIDID_I2CABSHWPOS_HWDEG_F32,
			D_XCP_PIDID_VERNDIAGERROR_DEG,
			D_XCP_PIDID_MRFCUMMTRPOS
	};

	Result_Uls_T_u08 = XcpODTEntrySetup((uint16 *)&t_PIDlist_Cnt_T_u16[0], t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length, DAQNum_Cnt_T_u08);

	return Result_Uls_T_u08;

}

/*****************************************************************************
 *
 *	Function Name: 	   StaticDAQ_ManufSrvc_Torque
 *
 *	Description:       Manufacturing Service DAQ for T1 and T2 (Digital) Only
 *
 *	Inputs:		       PIDidx_Cnt_T_u16 - Index of the PID entry
 * 					   DAQNum_Cnt_T_u08 - DAQ list number. (Typically 0)
 *
 *	Outputs:	       Result_Uls_T_u08 - Command response.
 *
 *****************************************************************************/
STATIC FUNC(uint8, EPSXCPDIAGSRVCS_CODE) StaticDAQ_ManufSrvc_Torque(VAR(uint16, EPSDIAGSRVCS_VAR) PIDidx_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) DAQNum_Cnt_T_u08)
{
	/* output */
	VAR(uint8, EPSDIAGSRVCS_VAR) Result_Uls_T_u08 = (uint8)D_XCP_USRCMDRESP_OK;

	/* local */
	VAR(uint16, EPSDIAGSRVCS_VAR) t_PIDlist_Cnt_T_u16[] = {
			D_XCP_PIDID_DIGHWTRQT1_HWNM,
			D_XCP_PIDID_DIGHWTRQT2_HWNM
	};

	Result_Uls_T_u08 = XcpODTEntrySetup((uint16 *)&t_PIDlist_Cnt_T_u16[0], t_DiagSrv_PIDtbl[PIDidx_Cnt_T_u16].length, DAQNum_Cnt_T_u08);

	return Result_Uls_T_u08;

}
