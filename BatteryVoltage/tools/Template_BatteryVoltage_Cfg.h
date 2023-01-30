/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Template_BatteryVoltage_Cfg.h
* Module Description: Battery Voltage configuration
* Product           : Gen II Plus - EA3.0
* Author            : Bobby O'Steen
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Wed Jan 01 18:03:04 2014
* %version:          1 %
* %derived_by:       wz7x3j %
* %date_modified:    Wed Jan  8 18:18:41 2014 %
*---------------------------------------------------------------------------*/

#ifndef BATTERYVOLTAGE_CFG_H
#define BATTERYVOLTAGE_CFG_H



/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#include "Ap_DiagMgr.h" /* add appropiate header to include */


#define BATTERYVOLTAGE_REPORTERRORSTATUS(event, param, status)		NxtrDiagMgr???_ReportNTCStatus(event, param, status) /* ??? = application, i.e. 8, 9, 10... */

#endif
