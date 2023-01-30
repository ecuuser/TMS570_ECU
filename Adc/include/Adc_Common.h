/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Adc_Common.h
* Module Description: Adc device driver common functions (must be stateless to
*                      execute in all contexts)
* Product           : Gen II Plus - EA3.0
* Author            : Lonnie Newton
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Fri Nov 02 09:15:00 2012
* %version:          3 %
* %derived_by:       nzt9hv %
* %date_modified:    Mon Apr 29 09:29:24 2013 %
*---------------------------------------------------------------------------*/

#if !defined (ADC_COMMON_H)
#define ADC_COMMON_H

#include "adc_regs.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* Common defines for the operation of Adc and Adc2 BSW's */
#define D_MAXCONVERSIONVALUE_CNT_U16	0x0FFFU
#define D_GROUPEND_CNT_U32				0x00000001U
#define D_GROUPBUSY_CNT_U32				0x00000004U
#define D_GROUPMEMEMPTY_CNT_U32			0x00000008U

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"

FUNC(uint8, ADC_CODE) ADCOffsetCalibration( adcctrlregs_t *adcREG , P2VAR(uint16, AUTOMATIC,AUTOMATIC) ADCOffset_Cnt_T_u8p8);

#define ADC_STOP_SEC_CODE
#include "MemMap.h"

#endif  /* ADC_COMMON_H */
  
/*****************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description              SCR #
-------   -------  --------  -----------------------------------  ----------
01/16/13   1.0      JJW      	Initial file creation				CR6519
06/27/14   2        Selva       Updated for ADC offset compensation 
******************************************************************************/
