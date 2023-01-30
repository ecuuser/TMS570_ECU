/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_StaMd.h
* Module Description: AUTOSAR Startup Sequence
* Product           : Gen II Plus - EA3.0
* Author            : Bobby O'Steen
*****************************************************************************/
/* Version Control:
 * Date Created:      Wed Apr 13 12:17:00 2011
 * %version:          2 %
 * %derived_by:       wz7x3j %
 * %date_modified:    Fri Dec 20 13:37:44 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 12/12/13  1        BDO       Initial Version
 * 12/20/13  2        BDO       Changed prototype and removed comments from StaMd_Init0
 */

#ifndef AP_STAMD_H
#define AP_STAMD_H

/***************************************************************************************************
* Include files
***************************************************************************************************/
#include "Std_Types.h"
#include "Rte_Type.h"

/**************************************************************************************************
* Defines / Constants
**************************************************************************************************/


/**************************************************************************************************
* Function Prototypes
**************************************************************************************************/
/* Prototypes */
extern FUNC(void, AP_STAMD_CODE) StaMd_Init0(void);


#endif /* AP_STAMD_H */
