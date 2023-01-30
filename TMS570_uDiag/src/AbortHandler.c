/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : AbortHandler.c
* Module Description: Data and Prefetch Abort Handler
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Fri Jun 29 10:22:39 2012
* %version:          1 %
* %derived_by:       czgng4 %
* %date_modified:    Fri Jun 29 10:22:39 2012 % 
*---------------------------------------------------------------------------*/

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"
#include "ResetCause.h"
#include "RednRpdShtdn.h"

/*****************************************************************************
* Local Functions
*****************************************************************************/
FUNC(void, ABORTHANDLER_CODE) AbortHandler(ENUM_ResetCause ResetCause_Cnt_T_Enum);

FUNC(void, ABORTHANDLER_CODE) AbortHandler(ENUM_ResetCause ResetCause_Cnt_T_Enum)
{
	RednRpdShtdn(ResetCause_Cnt_T_Enum);
}
/*****************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description              SCR #
                                    (MDD Rev & Date)
-------   -------  --------  -----------------------------------  ----------
06/29/12   1        LWW      Initial file creation
******************************************************************************/
