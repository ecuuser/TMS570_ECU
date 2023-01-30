/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : OsErrCallouts.c
* Module Description: Callout functions for OS errors
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue Nov 13 10:22:39 2012
* %version:          2 %
* %derived_by:       nz63rn %
* %date_modified:    Tue Jun 25 14:38:08 2013 % 
*---------------------------------------------------------------------------*/

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"
#include "ResetCause.h"
#include "RednRpdShtdn.h"
#include "Os.h"

/*****************************************************************************
  * Name:        ErrorHook
  * Description: Required OSEK Hook function, functionality currently only 
  *              looks for unhandled exception fault and calls 
  *              Redundant Rapid Shutdown function
  * Called by:   OS (On Error)
  * Inputs:      None 
  * Outputs:     None
*****************************************************************************/
FUNC(void, APPLCB_CODE) ErrorHook(StatusType Error)
{	
  switch ( OSErrorGetosCANError() )
   	{  		
		case osdErrUEUnhandledException:
      		RednRpdShtdn(UNUSEDINTERRUPT);
         break;
        default:
         break;
   }
  
}

/*****************************************************************************
  * Name:        ProtectionHook
  * Description: OS MPU Protection Error Hook --  functionality currently  
  *              calls Redundant Rapid Shutdown function with reset cause 
  *              STACKOVERWRITE for stack faults and MPUVIOLATION for any other 
  *              protection violation
  * Called by:   OS (On Protection Violation)
  * Inputs:      None 
  * Outputs:     None
*****************************************************************************/
FUNC(ProtectionReturnType, APPLCB_CODE) ProtectionHook(StatusType Fatalerror)
{
  switch ( OSErrorGetosCANError() )
   	{  		
   		case osdErrSOStackOverflow:			/* Task Stacks */
    	case osdErrYOStackOverflow:			/* System Stack */
    		RednRpdShtdn(STACKOVERWRITE);
         break;
        default:
			RednRpdShtdn(MPUVIOLATION);
         break;
   }

	return(PRO_SHUTDOWN);
}

/*****************************************************************************
  *
  * CHANGE HISTORY:
  *
  * Date      Rev      Author         Change Description 											SCR #
  *                                    (MDD Rev & Date)
  * -------   -------  --------  -----------------------------------  							----------
  * 11/13/12   1        LWW      Initial file creation
  * 06/25/13   2        KMC      Move stack fault handling from ErrorHook to ProtectionHook         7139
*****************************************************************************/
