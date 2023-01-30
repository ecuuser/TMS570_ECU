/*****************************************************************************
* Copyright 2011 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : RednRpdShtdn.h
* Module Description: Redundant Rapid Shutdown function
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue May 31 09:10:19 2011
* %version:          4 %
* %derived_by:       nz63rn %
* %date_modified:    Wed Jan  8 14:56:14 2014 % 
*---------------------------------------------------------------------------*/

#ifndef REDNRPDSHTDN_H_
#define REDNRPDSHTDN_H_

#include "ResetCause.h"

extern FUNC(void, REDNRPDSHTDN_CODE) RednRpdShtdn(ENUM_ResetCause ResetCause_Cnt_T_Enum);

#endif /*REDNRPDSHTDN_H_*/

/***********************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description              	 	        SCR #
-------   -------  --------  -----------------------------------  		      ----------
05/31/11   1.0      LWW      Initial Creation
07/11/12   2.0      LWW      Updated to use standard register definitions
10/11/13   3/0      KMC      Updated to force error pin low instead of          10406
                             other shutdown mechanisms - fixes anomaly 5403
01/08/14	4.0		KMC		 Removed INLINE keyword; moved function from .h     11158
                             file to .c file
************************************************************************************/
