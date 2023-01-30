/*******************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : NtWrap_Cfg.h
* Module Description: Non-trusted function call wrapper configurable definitions
* Product           : Gen II Plus - EA3.0
* Author            : Owen Tosh
*******************************************************************************/
/*******************************************************************************
* Version Control:
* Date Created:      Tue Jan  7 15:00:00 2014
* %version:          1 %
* %derived_by:       nzx5jd %
* %date_modified:    Thu Jan  9 16:49:41 2014 %
*******************************************************************************/
/*******************************************************************************
* Change History:
* Date      Rev      Author    Change Description
* --------  -------  --------  ------------------------------------------------
* 01/07/14   1       OT        Initial version
*******************************************************************************/

#ifndef NTWRAP_CFG_H
#define NTWRAP_CFG_H

#include "Det.h"

#define		NTWRAP_DEV_ERROR_DETECT					STD_ON

#define 	NtWrap_ReportDet( errorId )				Det_ReportError( 0u /*ModuleId*/, 0u /*InstanceId*/, 0u /*ApiId*/, errorId )
#define		D_NTWRAPINVLDINDXDET_CNT_U08			0x00U

#endif
