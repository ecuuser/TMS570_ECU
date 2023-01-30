
/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : SpiNxt_Cfg.h
* Module Description: SpiNxt Configuration
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Fri Nov 5 16:33:22 2010
* %version:          4 %
* %derived_by:       nz63rn %
* %date_modified:    Wed Apr 02 10:35:04 2014 % 
*---------------------------------------------------------------------------*/
/*****************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description                                 SCR #
-------   -------  --------  ------------------------------------------------------  ----------
08/02/13   3.0      KMC       Changes to make SpiNxt configurable for Turns Counter  
                              or Digital MSB (CR 8834) 
04/01/13   4.0		KMC		  Changes to make configurable to use/not use DMA         11435
                              as part of changes for ES-50A ver 005.      
******************************************************************************/

#ifndef SPINXT_CFG_H 
#define SPINXT_CFG_H  

/***************************************************************************************************
* Include files
***************************************************************************************************/

/* Spi used with */
#define D_SPINXT_USEWITHTC 		0U
#define D_SPINXT_USEWITHDIGMSB 	1U

/* SpiNxt used with Turns Counter or Digital MSB. */
#define D_SPINXTUSEWITH_CNT_ENUM			D_SPINXT_USEWITHDIGMSB

/* SpiNxt use DMA */
#define BC_SPINXT_USEDMA    				STD_ON

#endif /*SPINXT_CFG_H*/
