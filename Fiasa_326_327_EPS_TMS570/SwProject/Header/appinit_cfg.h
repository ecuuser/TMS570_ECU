/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : appinit_cfg.h
* Module Description: This file contains the configuration of the applicaiton init sequence
* Product           : Gen II Plus EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/* Version Control:
 * Date Created:      Fri May 11 12:17:00 2012
 * %version:          2 %
 * %derived_by:       jzh87w %
 * %date_modified:    Fri Jul 19 13:23:15 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 03/15/13		2		SAH		Enabled MIBSPI3
 */
 
#ifndef APPINIT_CFG_H_
#define APPINIT_CFG_H_

#include "Std_Types.h"

/* Peripheral Enables */
#define MIBSPI1_ENABLE  			STD_OFF
#define MIBSPI3_ENABLE  			STD_ON
#define MIBSPI5_ENABLE  			STD_ON
#define GIO_ENABLE  				STD_ON

/* Peripheral RAM Parity Test Enables */
#define MIBSPI1_PARITY_ENABLE  		STD_OFF
#define MIBSPI3_PARITY_ENABLE  		STD_OFF
#define MIBSPI5_PARITY_ENABLE  		STD_OFF
#define N2HET1_PARITY_ENABLE  		STD_ON
#define N2HET2_PARITY_ENABLE  		STD_ON
#define N2HET1TU_PARITY_ENABLE  	STD_ON
#define N2HET2TU_PARITY_ENABLE  	STD_ON
#define MIBADC1_PARITY_ENABLE  		STD_ON
#define MIBADC2_PARITY_ENABLE  		STD_ON
#define DCAN1_PARITY_ENABLE  		STD_ON
#define DCAN2_PARITY_ENABLE  		STD_OFF
#define DCAN3_PARITY_ENABLE  		STD_OFF
#define VIM_PARITY_ENABLE  			STD_ON
#define DMA_PARITY_ENABLE  			STD_ON
#define DMA_MPU_ENABLE 				STD_ON
#define N2HET1TU_MPU_ENABLE  		STD_ON
#define N2HET2TU_MPU_ENABLE  		STD_OFF

#endif /* APPINIT_CFG_H_ */
