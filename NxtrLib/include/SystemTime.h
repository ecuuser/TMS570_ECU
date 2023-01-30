/*****************************************************************************
* Copyright 2010 Nexteer, Inc., All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : SystemTime.h
* Module Description: This file contains the Nexteer System Time definition
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Mon Dec 06 15:06:38 2010
* %version:          2 %
* %derived_by:       czgng4 %
* %date_modified:    Thu Jan 13 11:36:28 2011 %
*---------------------------------------------------------------------------*/


#ifndef SYSTEMTIME_H
#define SYSTEMTIME_H

extern FUNC(void, SYSTEMTIME_CODE) DtrmnElapsedTime_uS_u16(uint32 InitialTime, P2VAR(uint16, AUTOMATIC, SYSTEMTIME_VAR) ElapsedTime);
extern FUNC(void, SYSTEMTIME_CODE) DtrmnElapsedTime_uS_u32(uint32 InitialTime, P2VAR(uint32, AUTOMATIC, SYSTEMTIME_VAR) ElapsedTime);
extern FUNC(void, SYSTEMTIME_CODE) DtrmnElapsedTime_mS_u16(uint32 InitialTime, P2VAR(uint16, AUTOMATIC, SYSTEMTIME_VAR) ElapsedTime);
extern FUNC(void, SYSTEMTIME_CODE) DtrmnElapsedTime_mS_u32(uint32 InitialTime, P2VAR(uint32, AUTOMATIC, SYSTEMTIME_VAR) ElapsedTime);
extern FUNC(void, SYSTEMTIME_CODE) GetSystemTime_uS_u32(P2VAR(uint32, AUTOMATIC, SYSTEMTIME_VAR) CurrentTime);
extern FUNC(void, SYSTEMTIME_CODE) GetSystemTime_mS_u32(P2VAR(uint32, AUTOMATIC, SYSTEMTIME_VAR) CurrentTime);
extern FUNC(void, SYSTEMTIME_CODE) SystemTime_Per1(void);
extern FUNC(void, SYSTEMTIME_CODE) SystemTime_Init(void);
#endif /*SYSTEMTIME_H*/

/******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author 			Change Description              SCR #
-------   -------   --------  -----------------------------------  ----------
12/06/2010  1       JJW        Initial version
01/13/2011  2       LWW        Fixed function name
******************************************************************************/
