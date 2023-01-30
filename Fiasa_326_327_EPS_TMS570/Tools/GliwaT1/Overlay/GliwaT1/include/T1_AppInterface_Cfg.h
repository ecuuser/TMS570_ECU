/***********************************************************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : T1_AppInterface_Cfg.h
* Module Description: GliwaT1 Application Interface
* Product           : Gen II Plus - EA3.0
* Author            : Owen Tosh
***********************************************************************************************************************/
/***********************************************************************************************************************
* Version Control:
* %version:          EA3#2 %
* %derived_by:       nzdx8v %
************************************************************************************************************************
* Change History:
* Date      Rev      Author    Change Description                                                                 CR#
* --------  -------  --------  ---------------------------------------------------------------------------------- -----
* 11/18/14   1       OT        Initial version
* 01/22/16   2       PS        Added D_I2CNXT_CNT_U08
***********************************************************************************************************************/

#ifndef T1_APPINTERFACE_CFG_H
#define T1_APPINTERFACE_CFG_H


#define D_SPINXT1_CNT_U08 0u
#define D_SPINXT2_CNT_U08 0u
#define D_I2CNXT_CNT_U08 T1_Isr_I2c_ID

#define PollT1HostToTarget() (void)0

#define D_GLIWAT1_SWITCHTOPRIVMODE_CNT_LGC STD_ON
#define D_GLIWAT1_SLOWWAITSTATES_CNT_LGC STD_ON /* slow here means 3dws 1aws. */


#endif
