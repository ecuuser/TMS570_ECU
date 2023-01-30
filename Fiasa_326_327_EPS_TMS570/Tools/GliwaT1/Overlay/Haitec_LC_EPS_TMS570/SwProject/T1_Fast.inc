/*******************************************************************************
* Copyright 2014 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : T1_Fast.inc
* Module Description: GliwaT1 conditional include file
* Product           : Gen II Plus - EA3.0
* Author            : Owen Tosh
*******************************************************************************/
/*******************************************************************************
* Version Control:
* %version:          1 %
* %derived_by:       nzx5jd %
*******************************************************************************/
/*******************************************************************************
* Change History:
* Date      Rev      Author    Change Description
* --------  -------  --------  ------------------------------------------------
* 12/18/14   1       OT        Initial version
*******************************************************************************/

/*
*  This file is intended to be used for GliwaT1 builds.  The elements here are
*  only included during a special GliwaT1 build - otherwise they will cause
*  compiler warnings.
*/

.T1_aligned	:	{
					. = align(16);
					*(.T1_codeFast:T1_TraceEvent_)
					. = align(16);
					*(.T1_codeFast:T1_TraceEventFast_)
					. = align(16);
					*(.T1_codeFast:T1_TraceEventNoSusp_)
					. = align(16);
					*(.T1_codeFast)
				} > APP_FLASH
