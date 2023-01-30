
/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_ApXcp_Cfg.h
* Module Description: Configuration file of Xcp module
* Product           : Gen II Plus - EA3.0
* Generator         : artt 2.0.2.0
* Generation Time   : 27.01.2014 14:17:13
*****************************************************************************/
/* Version Control:
 * Date Created:      Fri Jul 13 18:34:17 2012
 * %version:          3 %
 * %date_modified:    Mon Jan 27 15:51:16 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 01/07/13   1       LWW       Initial template creation
 * 10/28/13   4       KJS       Changed configuration to support new TOTF configuration layout for segments
 *								0, 1, 2, 3, 4, and 16. 
 */

#ifndef AP_XCP_CFG_H
#define AP_XCP_CFG_H

#include "Std_Types.h"                   /* Standard type definitions      */

/*** Private Part (used by Ap_ApXcp.c only) *************************************/
#ifdef APXCP_C

#define D_NUMOFOSAPPS_CNT_U8					4U

#define D_NUMOFVLDMEMRGNS_CNT_U08				2U

#define BC_XCP_EXTEEPACCESS	STD_OFF

/* Tune of the Fly Disabled */
#define BC_XCP_TUNEONFLY			STD_OFF

#endif

#endif /* AP_APXCP_CFG_H */

/*** End of file **************************************************************/
