/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Adc2.h
* Module Description: ADC Unit 2 Complex Device Driver
* Product           : Gen II Plus - EA3.0
* Author            : Lonnie Newton
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Fri Nov 02 09:15:00 2012
* %version:          3 %
* %derived_by:       nzt9hv %
* %date_modified:    Tue Apr 30 11:03:16 2013 %
*---------------------------------------------------------------------------*/
#ifndef ADC2_H
#define ADC2_H

#include "Std_Types.h"
#include "CDD_Const.h"
#include "adc_regs.h"
#include "Adc2_Cfg.h"
#include "Adc_Common.h"

/* The following defines allow access directly to the ADC2 Result */
/*  RAM (i.e. non-fifo mode.                                      */
#define D_ADC2RSLTBASEADR_CNT_U32      (0xFF3A0000U)

/* The following inline function is designed to grant access to the motor Isr adc results
 *  At the moment, for efficiency, they allow direct access to the ADC results.
 *  The 12bit mask is used to mask out the Channel ID appended to the conversion result.
 *  Function access is used instead of direct memory access to facilitate UTP.  Inline is
 *  is specified to reduce the execution time for the Mtr Ctrl Isr accesses.
 * NOTE: This API is an extension to the AUTOSAR Adc API.
 */

/* User function prototypes */
inline uint16 Adc2_ReadConversion(uint16);

/* User function definitions */
inline uint16 Adc2_ReadConversion(uint16 ConvId)
{
	return((uint16)(D_MAXCONVERSIONVALUE_CNT_U16 & ((uint32*)D_ADC2RSLTBASEADR_CNT_U32)[ConvId]));
}

/* ADC Interface Functions */
void Adc2_Init1(void);
void Adc2_StartGroupConversion(uint8 group);
void Adc2_EnableGroupNotification(uint8 group);


 
#endif

/*****************************************************************************
CHANGE HISTORY:

 Date      Rev      Author         Change Description              SCR #
-------   -------  --------  -----------------------------------  ----------
11/02/12   1.0      LN      	Initial Component Creation			CR6519
01/18/13   2      	JJW      	Updates per peer review
******************************************************************************/
