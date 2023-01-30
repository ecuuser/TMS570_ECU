/*****************************************************************************
* Copyright 2010 Nexteer, Inc., All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : CheckSums.c
* Module Description: This file contains the checksum functions
* Product           : Gen II Plus - EA3.0
* Author            : Bobby OSteen
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Mon Feb 04 19:06:38 2010
* %version:          1 %
* %derived_by:       wz7x3j %
* %date_modified:    Fri Feb 11 18:02:03 2011 %
*---------------------------------------------------------------------------*/

#ifndef CHECKSUMS_H_
#define CHECKSUMS_H_

#include "Rte_Type.h"
#include "fpmtype.h"
#include "fixmath.h"

extern CONST(uint8, CHECKSUM_CONST) CrcTable[256];

extern FUNC(uint8, CHECKSUM_CODE) BMW_CRC(	VAR(uint16, AUTOMATIC) id,
											CONSTP2CONST(uint8, CHECKSUM_CONST, CHECKSUM_CONST) MsgData, 
											VAR(uint8, AUTOMATIC) MsgLength);

#endif /*CHECKSUMS_H_*/

/******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author 			Change Description              SCR #
 				 					 (MDD Rev & Date) 		
-------   -------  --------  -----------------------------------  ----------
02/04/11   1.0      OSteen    Initial version 

******************************************************************************/
