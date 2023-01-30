/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : EPS_DiagSrvcs_ISO.Customer.h file
* Module Description: Common Manufacturing Program Interface for XCP and ISO services
* Product           : Gen II Plus - EA3.0
* Author            : Jared Julien
*
* Notes:
* This file contains configurations for ISO services.
*
*****************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Wed Jul 17 11:00:00 2013
 * %version:          3 %
 * %derived_by:       nzx5jd %
 * %date_modified:    Mon Sep 30 14:35:43 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                               SCR #
 * --------  -------  --------  ------------------------------------------------------------------------------  -------
 * 07/17/13   1       OT        Initial Haitec version
 * 09/30/13   2       OT        Added 00FF as XCP customer service
 * 12/15/14   3       PS        Added XCP DAQ 0xF0 and 0xF1.
 * 								Enabled XCP DAQ 0x010E, 0x010F
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include area >>                        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "EPS_DiagSrvcs_CommonData.h"
#include "EPS_DiagSrvcs_SrvcLUTbl.h"
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include area >>                          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#ifndef EPS_DIAGSRVCS_ISO_CUSTOMER_H
#define EPS_DIAGSRVCS_ISO_CUSTOMER_H

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of custom include area >>                 DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "EPS_DiagSrvcs_ISO.Interface.h"

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of custom include area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of custom define area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* This is the number of Program Specific PIDs in the LUT */
#define	D_DIAGSRCVS_PROGPIDTBLSIZE_CNT_U16	2U

/****************************** BEGIN CMS GENERATION - DO NOT CHANGE/REMOVE THIS COMMENT ******************************/
/******************************* END CMS GENERATION - DO NOT CHANGE/REMOVE THIS COMMENT *******************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of custom define area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#endif /* EPS_DIAGSRVCS_ISO_CUSTOMER_H */
