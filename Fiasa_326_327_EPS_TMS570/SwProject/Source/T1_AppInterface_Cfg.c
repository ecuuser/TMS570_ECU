/***********************************************************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : T1_AppInterface_Cfg.c
* Module Description: GliwaT1 Application Interface
* Product           : Gen II Plus - EA3.0
* Author            : Owen Tosh
***********************************************************************************************************************/
/***********************************************************************************************************************
* Version Control:
* %version:          1 %
* %derived_by:       nzx5jd %
************************************************************************************************************************
* Change History:
* Date      Rev      Author    Change Description                                                                 CR#
* --------  -------  --------  ---------------------------------------------------------------------------------- -----
* 11/18/14   1       OT        Initial version
***********************************************************************************************************************/

#include "T1_AppInterface.h"
#include "T1_AppInterface_Cfg.h"
#include "Std_Types.h"
#include "CanIf.h"

#ifdef T1_ENABLE


#define T1_START_SEC_NO_INIT_8
#include "T1_MemMap.h"
static uint8 Buffer_Cnt_M_u08[8u];
#define T1_STOP_SEC_NO_INIT_8
#include "T1_MemMap.h"

#define T1_START_SEC_CODE
#include "T1_MemMap.h"

/* Message reception handler. Pass all data back to T1 */
void GliwaT1_MsgProcess_RxT1HostToTarget(PduIdType CanRxPduId, const uint8 * CanSduPtr)
{
	VAR(uint32, AUTOMATIC) CallerIsTrusted_Cnt_T_u32;
	
	CallerIsTrusted_Cnt_T_u32 = osSwitchToPrivMode();
	
	Buffer_Cnt_M_u08[0u] = CanSduPtr[0u];
	Buffer_Cnt_M_u08[1u] = CanSduPtr[1u];
	Buffer_Cnt_M_u08[2u] = CanSduPtr[2u];
	Buffer_Cnt_M_u08[3u] = CanSduPtr[3u];
	Buffer_Cnt_M_u08[4u] = CanSduPtr[4u];
	Buffer_Cnt_M_u08[5u] = CanSduPtr[5u];
	Buffer_Cnt_M_u08[6u] = CanSduPtr[6u];
	Buffer_Cnt_M_u08[7u] = CanSduPtr[7u];
	
	(void)T1_RxCallback((T1_rawData_t*)Buffer_Cnt_M_u08);
	
	if( 0ul == CallerIsTrusted_Cnt_T_u32 )
	{
		osSwitchToUserMode();
	}
}

/* Called by T1 when it has data it wants to put on the bus */
T1_status_t T1_Transmit(T1_rawData_t const * pRawData)
{
	VAR(T1_status_t, AUTOMATIC) RetVal_Cnt_T_enum;
	VAR(PduInfoType, AUTOMATIC) PduInfo_Cnt_T_str;
	
	PduInfo_Cnt_T_str.SduDataPtr = (SduDataPtrType)(&(pRawData->d.u8[0]));
	PduInfo_Cnt_T_str.SduLength = 8u;
	
	if( E_OK == CanIf_Transmit(0u, &PduInfo_Cnt_T_str) )
	{
		RetVal_Cnt_T_enum = T1_OK;
	}
	else
	{
		RetVal_Cnt_T_enum = T1_FAILED;
	}
	
	return RetVal_Cnt_T_enum;
}

#define T1_STOP_SEC_CODE
#include "T1_MemMap.h"


#else


void GliwaT1_MsgProcess_RxT1HostToTarget(PduIdType CanRxPduId, const uint8 * CanSduPtr)
{
	/* Do nothing. */
}


#endif
