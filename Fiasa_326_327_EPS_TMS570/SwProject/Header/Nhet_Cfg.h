/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Nhet_Cfg.h
* Module Description: Nhet Complex Driver configuration
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Sat Jul 28 18:03:04 2012
* %version:          1 %
* %derived_by:       jzh87w %
* %date_modified:    Fri Jul 19 13:22:32 2013 %
*---------------------------------------------------------------------------*/


#ifndef NHET_CFG_H
#define NHET_CFG_H

/* Include definitions for Diagnostic Event API */
#include "Ap_DiagMgr.h"

#define NHET_E_MPU_FAILURE			NTC_Num_RAMDiag_HETTU1RamFlt

#define NHET_E_MPU_INFO				0x80U

#define NHET_REPORTERRORSTATUS(event, param, status)		NxtrDiagMgrD_ReportNTCStatus(event, param, status)
#define NHET_EVENT_PASSED				NTC_STATUS_PASSED
#define NHET_EVENT_FAILED				NTC_STATUS_FAILED

#endif
