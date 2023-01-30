/*****************************************************************************
* Copyright 2015 Nexteer 
* Nexteer Confidential
*
* Module File Name  : Nhet.h
* Module Description: NHET data structure definition
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/* Version Control:
 * Date Created:      Wed Apr 13 12:17:00 2011
 * %version:          4 %
 * %derived_by:       nz63rn %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 04/13/11  1        LWW       Initial K2xx Synergy Version
 * 10/13/11  2        LWW       Added NHET1 in addition to NHET0
 * 12/12/11	 3		  KJS		Added function prototype for NHET2
 * 01/27/12	 4		  JJW       Consolidated NHET1 and NHET2 initializations
 * 01/27/12	 5		  JJW       std_nhet.h name replaced std_het.h to match new TI header naming
 *                              Nhet2_Prog.h added
 * 01/31/12	 6		  JJW       Updated NHET Reg struct to contain reg defs based on TI Data sheet SPNU499-September 2011
 * 07/27/12	 7		  JJW       Removed NHET reg struct and instead included n2het_regs.h
 *                              Created buffered control structure type that mirrors the Nhet Prog structure to support HTU use
 *								Added API for setting pwm edges to abstract the user from the underlying
 *								structure names (macro access used for efficient use in mtr ctrl ISR)
 * 02/01/13  8		  OT		Updates for ePWM
 * 06/19/13  9		  OT		Updates for FDD 34B v003 (added NHET0 program)
 * 04/07/14  10        Selva    Implemented  FDD34B v 005														CR11062
 * 01/26/15  11       KMC       Added extern declaration for Nhet_Htu1RstFail_Cnt_G_lgc for ES-34B v008         CR12869
 */


#ifndef NHET_H
#define NHET_H

#include "Std_Types.h"
#include "n2het_regs.h"
#include "std_nhet.h"
#include "Nhet_SENT_Prog.h"
#include "Nhet2_ePWM_Prog.h"
#include "htu_regs.h"


						

#if defined(HTUDATATRQ)|| defined(UDIAG_C)

	#define D_CBUFLEN_CNT_U16		8U	
	/* # of time stamps for rising and falling edges stored in main system RAM*/
	typedef struct{

			uint32 HtuDataTrq1_Cnt_u32[D_CBUFLEN_CNT_U16]; /* Main input capture circular buffer (for HTU transfers from HET RAM to main CPU RAM */
			uint32 HtuDataTrq2_Cnt_u32[D_CBUFLEN_CNT_U16]; /* Main input capture circular buffer (for HTU transfers from HET RAM to main CPU RAM*/

	}HtuDataTrq_Str;
										
	extern volatile VAR(HtuDataTrq_Str, AUTOMATIC)  Nhet_HtuDataTrq_Cnt_G_str; 			
	extern VAR(boolean, AUTOMATIC) Nhet_Htu1RstFail_Cnt_G_lgc;														
										
#endif

/* Global NHET Functions */
FUNC(void, NHET_CODE) Nhet_Init1(void);
FUNC(void, NHET_CODE) Nhet1_Per3(void);

#endif
