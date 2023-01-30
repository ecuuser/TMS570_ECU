
/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_ApXcp_Cfg.c
* Module Description: Configuration file of Xcp module
* Product           : Gen II Plus - EA3.0
* Generator         : artt 2.0.2.0
* Generation Time   : 27.01.2014 14:17:14
*****************************************************************************/
/* Version Control:
 * Date Created:      Fri Jul 13 18:34:17 2012
 * %version:          3 %
 * %date_modified:    Mon Jan 27 15:51:14 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 01/07/13   1       LWW       Initial template creation
 * 06/26/13   3       KJS       Added preprocessor statements to control memcpy statements
 * 07/09/13   4       JJW       Added generation of Rte runnalbes for the configured Rte mapped Xcp Events
 */


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#define APXCP_C /* Enable visibility to Module internal definitions in Ap_ApXcp.h*/
#include "Ap_ApXcp.h"
#include "NtWrap.h"

/*******************************************************************************
**                      Public Data                                           **
*******************************************************************************/
CONST(uint32, AUTOMATIC) T_AllowedMemRegion_Cnt_u32[D_NUMOFVLDMEMRGNS_CNT_U08][2] =
{ 
	{ 0x00000000UL, 0x000BFFFFUL },
	{ 0x08000000UL, 0x0801FFFFUL },
};


CONST(uint8, AUTOMATIC) T_AppIndex_Cnt_u08[D_NUMOFOSAPPS_CNT_U8] =
{ 0U, 8U, 9U, 10U, };

CONST(uint8, AUTOMATIC) T_FunctionIndex_Cnt_u08[D_NUMOFOSAPPS_CNT_U8] =
{ TWrapS_XcpWriteAp0, NtWrapS_XcpWriteAp8, NtWrapS_XcpWriteAp9, NtWrapS_XcpWriteAp10,};

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DAQ_2msTL
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2
 *
 *********************************************************************************************************************/
FUNC(void, AUTOMATIC) DAQ_2msTL(void)
{
	XcpEvent(XcpEventChannel_2ms_DAQ_2);
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: CopyCalsToRam
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * SWC internal function executed by ApXcp_Init()
 *
 *********************************************************************************************************************/
FUNC(void, AUTOMATIC) CopyCalsToRam(void)
{
#if( (D_ENABLEMETRICS_CNT_LGC != STD_ON) && (BC_TUNINGSETINRAM == 1U) )
#endif
}
