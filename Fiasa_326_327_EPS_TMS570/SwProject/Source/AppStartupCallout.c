/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : AppStartupCallout.c
* Module Description: Application Startup Sequence Callout Functions
* Product           : Gen II Plus EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/* Version Control:
 * Date Created:      Wed Jul 17 11:00:00 2013
 * %version:          1 %
 * %derived_by:       nzx5jd %
 * %date_modified:    Fri Jul 19 13:23:29 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                               SCR #
 * --------  -------  --------  ------------------------------------------------------------------------------  -------
 * 07/17/13   1       OT        Initial Haitec version
 */


#include "Std_Types.h"
#include "Lnk_Symbols.h"


void AppStartupCallout1(void)
{
	/* Enable CPU ECC checking for ATCM (flash accesses) */
	asm("	mrc   p15, #0x00, r0,         c1, c0,  #0x01");
	asm("	orr   r0,  r0,    #0x1<<25");
	asm("	dmb");
	asm("	mcr   p15, #0x00, r0,         c1, c0,  #0x01");
	asm("	isb");
}

void AppStartupCallout2(void)
{
	uint32* Address;

	/* Initialize BSS section to 0 */
	for (Address = (uint32*)&Lnk_BSS_Start; Address <= (uint32*)&Lnk_BSS_End; Address++)
	{
		*Address = 0U;
	}
}
