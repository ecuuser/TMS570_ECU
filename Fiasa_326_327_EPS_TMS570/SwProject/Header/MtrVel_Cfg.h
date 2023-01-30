/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : MtrVel_Cfg.h
* Module Description: Configuration file of MtrVel module
* Product           : Gen II Plus - EA3.0
* Author            : Selva Sengottaiyan
*****************************************************************************/
/* Version Control:
 * Date Created:      Tue Jul 30 10:00:00 2013
 * %version:          2 %
 * %date_modified:    Tue Sep  3 15:15:42 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 07/30/13   1       OT        Initial Haitec version
 * 09/03/13   2       OT        Updated interfaces for latest version of MtrVel
 */

#ifndef MTRVEL_CFG_H
#define MTRVEL_CFG_H


#include "CDD_Data.h"


#define MtrVel_Read_MechMtrPos1_Rev_u0p16(ptr)			*(ptr) = CDD_MechMtrPos1_Rev_G_u0p16[CDD_CDDDataAccessBfr_Cnt_G_u16]
#define MtrVel_Read_MechMtrPos1TimeStamp_uS_u32(ptr)	*(ptr) = CDD_MechMtrPos1TimeStamp_uSec_G_u32[CDD_CDDDataAccessBfr_Cnt_G_u16]

#define D_MTRVELOSBUFSZ_CNT_U08    				8u


#endif /* MTRVEL_CFG_H */
