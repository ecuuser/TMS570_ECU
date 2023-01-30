/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : BootStartup.c
* Module Description: Boot Startup Sequence
* Product           : Gen II Plus EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/* Version Control:
 * Date Created:      Fri May 11 12:17:00 2012
 * %version:          1 %
 * %derived_by:       czgng4 %
 * %date_modified:    Fri Jun  8 09:31:02 2012 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 06/09/12  1        LWW       Initial Version
 */

#include "Platform_Types.h"
#include "Compiler.h"

typedef void (*handler_fptr)(const unsigned char *in, unsigned char *out);

#pragma WEAK(__TI_Handler_Table_Base)
#pragma WEAK(__TI_Handler_Table_Limit)
#pragma WEAK(__TI_CINIT_Base)
#pragma WEAK(__TI_CINIT_Limit)

extern unsigned   __TI_Handler_Table_Base;
extern unsigned   __TI_Handler_Table_Limit;
extern unsigned   __TI_CINIT_Base;
extern unsigned   __TI_CINIT_Limit;
extern unsigned   __TI_PINIT_Base;
extern unsigned   __TI_PINIT_Limit;
extern unsigned * __binit__;

extern void main(void);
extern void BootStartupCallout1(void);
extern void BootStartupCallout2(void);

void BootStartup(void)
{
	/* Callout for Application Specific processing */
	BootStartupCallout1();

/***************************** INITIALIZATION STEP 43 ****************************/
	/* initialize copy table */
	if ((uint32 *)&__binit__ != (uint32 *)0xFFFFFFFFU)
	{
		extern void copy_in(void *binit);
		copy_in((void *)&__binit__);
	}

	/* initialize the C global variables */
	if (&__TI_Handler_Table_Base < &__TI_Handler_Table_Limit)
	{
		uint8 **tablePtr   = (uint8 **)&__TI_CINIT_Base;
		uint8 **tableLimit = (uint8 **)&__TI_CINIT_Limit;

		while (tablePtr < tableLimit)
		{
			uint8 *loadAdr = *tablePtr++;
			uint8 *runAdr  = *tablePtr++;
			uint8  idx     = *loadAdr++;
			handler_fptr   handler = (handler_fptr)(&__TI_Handler_Table_Base)[idx];

			(*handler)((const uint8 *)loadAdr, runAdr);
		}
	}

	/* Initialize constructors */
	if (__TI_PINIT_Base < __TI_PINIT_Limit)
	{
		void (**p0)() = (void *)__TI_PINIT_Base;

		while ((uint32)p0 < __TI_PINIT_Limit)
		{
			void (*p)() = *p0++;
			p();
		}
	}

	/* Callout for Application Specific processing */
	BootStartupCallout2();

	main();
}


