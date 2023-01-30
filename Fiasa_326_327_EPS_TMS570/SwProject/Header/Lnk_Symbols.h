/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Lnk_Symbols.h
* Module Description: This file contains the declarations of Link Time Symbols
*                     used in the application.
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/* Version Control:
 * Date Created:      Wed Jul 11 11:30:00 2013
 * %version:          EA3#2 %
 * %derived_by:       nzdx8v %
 * %date_modified:    Mon Jan 27 15:51:00 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                               SCR #
 * --------  -------  --------  ------------------------------------------------------------------------------  -------
 * 07/11/13   1       OT        Initial Haitec version
 * 12/01/15   2      PS         Implemented software according to SCIR 5A and DSR 6A	 						 EA3#4681, EA3#4686
 */

#ifndef LNK_SYMBOLS_H
#define LNK_SYMBOLS_H

#include "Std_Types.h"

extern VAR(uint8, AUTOMATIC) Lnk_BootRelNum_Addr;
extern VAR(uint8, AUTOMATIC) Lnk_BootSwIdentificationDIDF180_Addr;

extern CONSTP2VAR(void, AUTOMATIC, AUTOMATIC) Lnk_BSS_Start;
extern CONSTP2VAR(void, AUTOMATIC, AUTOMATIC) Lnk_BSS_End;

extern CONSTP2VAR(void, AUTOMATIC, AUTOMATIC) Lnk_AppBlock_Start;
extern CONSTP2VAR(void, AUTOMATIC, AUTOMATIC) Lnk_AppBlock_Length;
extern CONSTP2VAR(void, AUTOMATIC, AUTOMATIC) Lnk_CalBlock_Start;
extern CONSTP2VAR(void, AUTOMATIC, AUTOMATIC) Lnk_CalBlock_Length;

#endif

