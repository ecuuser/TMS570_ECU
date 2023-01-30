/*****************************************************************************
* Copyright 2011 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : RednRpdShtdn.c
* Module Description: Redundant Rapid Shutdown function
* Product           : Gen II Plus - EA3.0
* Author            : Kathleen Creager
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Thu Jan  9 10:58:17 2014
* %version:          1 %
* %derived_by:       nz63rn %
* %date_modified:    Thu Jan  9 10:58:17 2014 % 
*---------------------------------------------------------------------------*/

#include "RednRpdShtdn.h"
#include "ResetCause.h"
#include "system_regs.h"
#include "esm_regs.h"

FUNC(void, REDNRPDSHTDN_CODE) RednRpdShtdn(ENUM_ResetCause ResetCause_Cnt_T_Enum)
{
	/* TODO: See if we want to disable MPU here */
	
	/* Force error pin low */
	ESMREGS->ESMEKR = 0xAU;  	

	/* Write Pattern To RAM Address */
	ResetCause_Cnt_Enum = ResetCause_Cnt_T_Enum;
	
	/* Perform Software Reset */
	systemREG1->SYSECR |= ((uint32)0x00008000u);
	
	for(;;){}
}


/***********************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description              	 	        SCR #
-------   -------  --------  -----------------------------------  		      ----------
01/08/14	1.0		KMC		 Initial creation - from RednRpdShtdn.h ver 3       11158
************************************************************************************/
