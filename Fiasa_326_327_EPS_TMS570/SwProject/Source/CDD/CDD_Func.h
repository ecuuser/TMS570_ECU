/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : CDD_Func.h
* Module Description: Header file for functions communicated between Nexteer
*                      Complex Device Drivers (CDD)
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/* Version Control:
 * Date Created:      Wed Jul 17 10:00:00 2013
 * %version:          2 %
 * %derived_by:       nzx5jd %
 * %date_modified:    Wed Jul 31 08:47:46 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                               SCR #
 * --------  -------  --------  ------------------------------------------------------------------------------  -------
 * 07/17/13   1       OT        Initial Haitec version
 * 07/30/13   2       OT        Removed MtrPos_Per1
 * 11/16/15   3       PS        Updated SF99B (MtrCtrl_CM) to ver 17				 	 						EA3#4579
 */

#ifndef CDD_FUNC_H
#define CDD_FUNC_H

#include "Std_Types.h"

extern FUNC(void, RTE_AP_MICRODIAG_APPL_CODE) MicroDiag_Per1(void);

/* TODO: Determine if the  CalRamInit really needs to execute as a CDD early in init */
/*        if it is determined that RAM cals are only used after RTE Start, then this */
/*        function can be removed from here and scheduled in Developer               */
extern FUNC(void, XCP_CODE) Xcp_CalRamInit(void);

extern FUNC(void, CDDInterface_CODE) CDDInterface_Per5(void);

#endif
