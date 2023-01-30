/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : SystemTime_Cfg.h
* Module Description: Configuration file for Systemtime.c module
* Product           : Gen II Plus - EA3.0
* 
*****************************************************************************/
/* Version Control:
 * Date Created:      Fri Jul 26 12:37:17 2013
 * %version:          2 %
 * %date_modified:    Tue Oct  1 11:46:44 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 07/29/13   1       OT        Initial Haitec version
 * 10/01/13   2       OT        Changed to 2ms tick
 */

#ifndef SYSTEMTIME_CFG_H
#define SYSTEMTIME_CFG_H


/*******************************************************************************
**                      Define Section                                       **
*******************************************************************************/


/* Configure the system tick time */
#define D_TickRate_Cnt_u32	 2000UL
   
#endif /* SYSTEMTIME_CFG_H */

/*** End of file **************************************************************/