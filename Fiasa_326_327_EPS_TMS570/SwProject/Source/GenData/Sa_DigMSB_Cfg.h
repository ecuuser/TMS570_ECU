
/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Sa_DigMSB_Cfg.h
* Module Description: Configuration file of DiagMgr module
* Product           : Gen II Plus - EA3.0
* Generator         : artt 2.0.2.0
* Generation Time   : 02.12.2013 12:45:46
*****************************************************************************/
/* Version Control:
 * Date Created:      Fri Jul 13 18:34:17 2012
 * %version:          3 %
 * %date_modified:    Tue Dec  3 15:47:48 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 09/20/12   1       ssk       Initial template creation
 * 12/02/13   2       OT        Update for removal of periodic
 * 	 	
 */

#ifndef SA_DIGMSB_CFG_H
#define SA_DIGMSB_CFG_H


/*******************************************************************************
**                      Define Section                                       **
*******************************************************************************/


/* Disable all checkpoints that are not enabled */
#define Rte_Call_DigMSB_Per2_CP0_CheckpointReached()		(void)0 /* Checkpoint disabled */	 
#define Rte_Call_DigMSB_Per2_CP1_CheckpointReached()		(void)0 /* Checkpoint disabled */	 
   
#endif /* DIGMSB_CFG_H */

/*** End of file **************************************************************/
