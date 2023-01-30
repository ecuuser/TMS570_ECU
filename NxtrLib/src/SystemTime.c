/*****************************************************************************
* Copyright 2010 Nexteer, Inc., All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : SystemTime.c
* Module Description: This file contains the System Time library
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Wed Nov 24 19:06:38 2010
* %version:          5 %
* %derived_by:       jzh87w %
* %date_modified:    Fri Jul 26 12:49:07 2013 %
*---------------------------------------------------------------------------*/

#include "Rte_NexteerLibs.h"
#include "SystemTime.h"
#include "GlobalMacro.h"
#include "Gpt.h"
#include "Gpt_Cfg.h"
#include "SystemTime_Cfg.h"


#define d_MIN_u16  0U
#define d_MAX_u16  65535U
#define d_MIN_u32  0U
#define d_MAX_u32  4294967295L
#define d_MAXSYSTEMTIME_uS_u32   4294967295L 


#define START_SEC_SYSTEMTIME_CODE
//#include "MemMap.h"

/*.***************************************************************************
*. Name: DtrmnElapsedTime_uS_u16 PROCEDURE
*.   This function shall get the current system time and find the difference 
*.	 between it and the given input argument in microseconds.   
*.   Arguments : InitialTime:  calculate time elapsed since this time.
*.	 Outputs : Elapsed time between input argument and current time. (16 bit)
*.
******************************************************************************/
FUNC(void, SYSTEMTIME_CODE) DtrmnElapsedTime_uS_u16 (uint32 InitialTime, P2VAR(uint16, AUTOMATIC, SYSTEMTIME_VAR) ElapsedTime)
{
uint32  Temp_ElapsedTime;

DtrmnElapsedTime_uS_u32(InitialTime, &Temp_ElapsedTime);

/* clip and clamp result for correct output type */
*ElapsedTime = (uint16)(Limit_m(Temp_ElapsedTime, d_MIN_u16, d_MAX_u16));

}

/*.***************************************************************************
*. Name: DtrmnElapsedTime_uS_u32 PROCEDURE
*.   This function shall get the current system time and find the difference 
*.	 between it and the given input argument in microseconds.   
*.   Arguments : InitialTime:  calculate time elapsed since this time.
*.	 Outputs : Elapsed time between input argument and current time. (32 bit)
*.
******************************************************************************/
FUNC(void, SYSTEMTIME_CODE) DtrmnElapsedTime_uS_u32(uint32 InitialTime, P2VAR(uint32, AUTOMATIC, SYSTEMTIME_VAR) ElapsedTime)
{
	uint32  CurrentTime = 0;
	uint32  Temp_ElapsedTime = 0;

	CurrentTime = *(uint32*)(0xFFFFFC10u);
	if ( InitialTime > CurrentTime )   /* handle system time roll-over */
	{
        Temp_ElapsedTime = ((d_MAXSYSTEMTIME_uS_u32 - InitialTime) + CurrentTime + 1);
	}
	else
	{
        Temp_ElapsedTime = (CurrentTime - InitialTime);
	}

	/* No limiting possible on output because performing unsigned 32 bit math and */
	/* Returning a value that is full 32 bit range.                               */
*ElapsedTime = Temp_ElapsedTime;
}

/*****************************************************************************
  * Name:        DtrmnElapsedTime_mS_u16
  * Description: Service to calculate the time elapsed since the given initial
  *               time.   
  * Inputs:      uint32 InitialTime 
  * Outputs:     uint16 ElapsedTime
  *
*****************************************************************************/
FUNC(void, SYSTEMTIME_CODE) DtrmnElapsedTime_mS_u16(uint32 InitialTime, P2VAR(uint16, AUTOMATIC, SYSTEMTIME_VAR) ElapsedTime)
{
uint32  Temp_ElapsedTime;

DtrmnElapsedTime_mS_u32(InitialTime, &Temp_ElapsedTime);

/* clip and clamp result for correct output type */
*ElapsedTime = (uint16)(Limit_m(Temp_ElapsedTime, d_MIN_u16, d_MAX_u16));

}

/*****************************************************************************
  * Name:        DtrmnElapsedTime_mS_u32
  * Description: Service to calculate the time elapsed since the given initial
  *               time.   
  * Inputs:      uint32 InitialTime 
  * Outputs:     uint32 ElapsedTime
  *
*****************************************************************************/
FUNC(void, SYSTEMTIME_CODE) DtrmnElapsedTime_mS_u32(uint32 InitialTime, P2VAR(uint32, AUTOMATIC, SYSTEMTIME_VAR) ElapsedTime)
{
uint32  CurrentTime;
uint32  Temp_ElapsedTime;

CurrentTime = Rte_IrvRead_DtrmnElapsedTime_mS_u16_Time_mS_u32();
if (InitialTime > CurrentTime)   /* handle system time roll-over */
{
    Temp_ElapsedTime = ((d_MAXSYSTEMTIME_uS_u32 - InitialTime) + CurrentTime + 1);
}
else
{
    Temp_ElapsedTime = (CurrentTime - InitialTime);
}

/* No limiting possible on output because performing unsigned 32 bit math and */
/* Returning a value that is full 32 bit range.                               */
*ElapsedTime = Temp_ElapsedTime;

}

/*.***************************************************************************
*. Name: GetSystemTime_u32_uS PROCEDURE
*.   Return the system time in units of microseconds.  
*.   Arguments : None
*.	 Outputs : System time in units of microseconds.
*.
******************************************************************************/
FUNC(void, SYSTEMTIME_CODE) GetSystemTime_uS_u32(P2VAR(uint32, AUTOMATIC, SYSTEMTIME_VAR) CurrentTime)
{
	/* Since the system time in this implementation is already in units of 
	microseconds, simply get and return the system time. */
	*CurrentTime = *(uint32*)(0xFFFFFC10u);
}

/*****************************************************************************
  * Name:        GetSystemTime_mS_u32
  * Description: Service to return the current system time value   
  * Inputs:      None 
  * Outputs:     uint16 CurrentTime
  *
*****************************************************************************/
FUNC(void, SYSTEMTIME_CODE) GetSystemTime_mS_u32(P2VAR(uint32, AUTOMATIC, SYSTEMTIME_VAR) CurrentTime)
{

*CurrentTime = Rte_IrvRead_GetSystemTime_mS_u32_Time_mS_u32();

}

/*****************************************************************************
  * Name:        SystemTime_Init
  * Description: Init function to initial   
  * Inputs:      None 
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, SYSTEMTIME_CODE) SystemTime_Init(void)
{

/*TODO: Replace magic number 1000U with a constant definition froom a configuration file */
/* Generating a 1mS notification function to maintain the tick API for the Os and WdgM   */
Gpt_StartTimer(SystemTime_uS, D_TickRate_Cnt_u32);

}

/*****************************************************************************
  * Name:        SystemTime_Per1
  * Description: Periodicly scheduled function to maintain the mS counter   
  * Inputs:      None 
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, SYSTEMTIME_CODE) SystemTime_Per1(void)
{

Rte_IrvWrite_SystemTime_Per1_Time_mS_u32((Rte_IrvRead_SystemTime_Per1_Time_mS_u32() + 2));

}




#define STOP_SEC_SYSTEMTIME_CODE
//#include "MemMap.h"

/******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author 			Change Description              SCR #
 				  					 (MDD Rev & Date) 		
-------   -------   --------  -----------------------------------  ----------
11/24/2010	1.0	    JJW        Initial Version
12/06/2010  2.0     JJW        Added uS timer functions
01/13/2011  3.0     LWW        Fixed name, direct register access of uS Timer
09/19/2011  4.0     JJW        Changed notification time to 1000 uS so that the 
                                Os and WdgM tick API's can be properly called.
07/26/2013  5.0     SAH		   Changed system time to a configurable value 
								defined in header file(D_TickRate_Cnt_u32).
******************************************************************************/
