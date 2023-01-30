/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : PwmCdd.h
* Module Description: Pwm Complex Driver external definitions
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue Dec  7 20:09:21 2010
* %version:          4 %
* %derived_by:       nzx5jd %
* %date_modified:    Fri Aug 30 08:41:38 2013 % 
*---------------------------------------------------------------------------*/


#ifndef PWMCDD_H
#define PWMCDD_H

extern FUNC(void, PWMCDD_CODE) PwmCdd_Init(void);
extern FUNC(void, PWMCDD_CODE) PwmCdd_Per1(void);

#endif

/*****************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description              SCR #
-------   -------  --------  -----------------------------------  ----------
12/16/10   1.0      JJW      Initial Creation
12/21/10   2.0      LWW      Added Init
07/28/12   3        JJW      Added config header include
08/30/13   4        OT       Removed config header include
******************************************************************************/
