/*********************************************************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Dma_Cfg.h
* Module Description: DMA Peripheral Configuration Header
* Product           : Gen II Plus - EA3.0
* Author            : Owen Tosh
*********************************************************************************************************************/
/***********************************************************************************************************************
* Version Control:
* Date Created:      Tue Mar 11 12:00:00 2014
* %version:          2 %
* %derived_by:       nzx5jd %
* %date_modified:    Wed Apr 30 12:00:00 2014 %
***********************************************************************************************************************/
/***********************************************************************************************************************
* Change History:
* Date      Rev      Author    Change Description                                                                CR#
* --------  -------  --------  --------------------------------------------------------------------------------- -----
* 04/08/14   1       OT        Initial version
* 04/29/14   2       OT        Added DiagMgr configuration                                                       11855
***********************************************************************************************************************/


#ifndef DMA_CFG_H
#define DMA_CFG_H


#include "Ap_DiagMgr.h"


#define D_DMAFLSTSTENABLED_CNT_ENUM			STD_ON	/* FlsTst Init Groups */
#define D_FASTSPIGROUPENABLED_CNT_ENUM		STD_ON	/* 50us SPI Group */
#define D_FASTADCGROUPENABLED_CNT_ENUM		STD_ON	/* 50us ADC Group */
#define D_FASTPWMGROUPENABLED_CNT_ENUM		STD_ON	/* 50us PWM Group */
#define D_SLOWADCGROUPENABLED_CNT_ENUM		STD_ON	/* 2ms ADC Group */

#define DMA_REPORTERRORSTATUS				NxtrDiagMgrX_ReportNTCStatus


#endif
