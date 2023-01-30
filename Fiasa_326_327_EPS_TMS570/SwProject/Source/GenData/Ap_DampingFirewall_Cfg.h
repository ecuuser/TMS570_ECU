
/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_DampingFirewall_Cfg.h
* Module Description: Configuration file of DiagMgr module
* Product           : Gen II Plus - EA3.0
* Generator         : artt 2.0.2.0
* Generation Time   : 05.07.2013 13:37:28
*****************************************************************************/
/* Version Control:
 * Date Created:      Fri Jul 13 18:34:17 2012
 * %version:          1 %
 * %date_modified:    Fri Jul 19 13:30:43 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 07/13/12   1       JJW       Initial template creation
 */

#ifndef AP_DAMPINGFIREWALL_CFG_H
#define AP_DAMPINGFIREWALL_CFG_H


/*******************************************************************************
**                      Define Section                                       **
*******************************************************************************/


/* Disable all checkpoints that are not enabled */
#define Rte_Call_DampingFirewall_Per1_CP0_CheckpointReached()		(void)0 /* Checkpoint disabled */	 
#define Rte_Call_DampingFirewall_Per1_CP1_CheckpointReached()		(void)0 /* Checkpoint disabled */	 
   
#endif /* DAMPINGFIREWALL_CFG_H */

/*** End of file **************************************************************/
