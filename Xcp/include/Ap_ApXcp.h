/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_ApXcp.h
* Module Description: ApXcp Header File
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Thu Dec  6 16:25:00 2012 %
* %version:          4 %
* %derived_by:       czgng4 %
* %date_modified:    Mon Jul 22 13:38:26 2013 %
*---------------------------------------------------------------------------------------------------------------------
* Date      Rev      Author         Change Description                                                        SCR #
* -------   -------  --------  ---------------------------------------------------------------------------  ----------
* 12/06/12  1        LWW       Initial Version
* 01/14/13  2        JJW       Name change to provide uniquness wihtin the namespace with the AUTOSAR Xcp module 
* 07/25/13  4        LWW       Made external eeprom access configurable
*/

#ifndef AP_APXCP_H
#define AP_APXCP_H

#include "Std_Types.h"
#include "Ap_ApXcp_Cfg.h"
#include "XcpProf.h"


FUNC(void, XCP_CODE) ApXcp_Init(void);
FUNC(void, AP_XCP_CODE) ApXcpWriteCommon(void);

#ifdef APXCP_C
extern CONST(uint8, AUTOMATIC) T_AppIndex_Cnt_u08[D_NUMOFOSAPPS_CNT_U8];
extern CONST(uint8, AUTOMATIC) T_FunctionIndex_Cnt_u08[D_NUMOFOSAPPS_CNT_U8];
extern CONST(uint32, AUTOMATIC) T_AllowedMemRegion_Cnt_u32[D_NUMOFVLDMEMRGNS_CNT_U08][2];
#if (STD_ON == BC_XCP_EXTEEPACCESS)
extern CONST(uint32, AUTOMATIC) T_AllowedEEMemRegion_Cnt_u32[D_NUMOFVLDEEMEMRGNS_CNT_U08][2];
#endif
FUNC(void, AUTOMATIC) CopyCalsToRam(void);
#else
extern volatile CONST(boolean, AUTOMATIC) EnableTestMode_Cnt_lgc;
#endif

#endif  /* AP_XCP_H */
