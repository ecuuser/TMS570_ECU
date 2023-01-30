/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Adc_Common.c
* Module Description: Adc device driver common functions (must be stateless to
*                      execute in all application contexts)
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Fri Nov 02 09:15:00 2012
* %version:          4 %
* %derived_by:       nzt9hv %
* %date_modified:    Thu May 30 16:52:39 2013 %
*---------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "Adc_Common.h"
#include "Adc.h"
#include "adc_regs.h"
#include "CalConstants.h"
#include "SystemTime.h"
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
#define D_NUMOFADCCALREADS_CNT_U8		128U

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/


#define ADC_START_SEC_CODE
#include "MemMap.h"


/*****************************************************************************
  * Name:        ADCOffsetCalibration
  * Description: Perform the ADC Calibration and Storing of offset
  * Inputs:      None
  * Outputs:     ADC Calibration and Error Offset Correction Register (CALR)
*****************************************************************************/
FUNC(uint8, ADC_CODE) ADCOffsetCalibration( adcctrlregs_t *adcREG, P2VAR(uint16, AUTOMATIC,AUTOMATIC) ADCOffset_Cnt_T_u8p8)
{
	VAR(boolean, AUTOMATIC) ConvTimeOut_Cnt_T_lgc = D_FALSE_CNT_LGC;
	VAR(uint32, AUTOMATIC) StartTime_uS_T_u32;
	VAR(uint16, AUTOMATIC) ElapsedTime_uS_T_u16;
	VAR(uint32, AUTOMATIC) ReadResults_Cnt_T_u32 = 0U;
	VAR(uint8, AUTOMATIC) NumOfReads_Cnt_T_u8;
	VAR(uint8, AUTOMATIC) Status_Cnt_T_u08 = ADC_EVENT_FAILED; /* Init to FAILED, only the success path's will change this to PASSED */


	/* Enable the Calibration Mode */
	adcREG->CALCR = 0x00000001U;
	
	NumOfReads_Cnt_T_u8 = 0u;
	while(NumOfReads_Cnt_T_u8 < D_NUMOFADCCALREADS_CNT_U8) 
	{
		/* Start the ADC conversion with HILO bit set to 0 */
		adcREG->CALCR |= 0x00010000U;

		/* Get start time for wait period */
		GetSystemTime_uS_u32(&StartTime_uS_T_u32);

		/* Wait for ADC conversion to complete */
		while((0U != (adcREG->CALCR & 0x00010000U)) && (ConvTimeOut_Cnt_T_lgc == D_FALSE_CNT_LGC))
		{
			DtrmnElapsedTime_uS_u16(StartTime_uS_T_u32, &ElapsedTime_uS_T_u16);

			if( ElapsedTime_uS_T_u16 >= k_MaxADCConvTime_uS_u16 )
			{
				ConvTimeOut_Cnt_T_lgc = D_TRUE_CNT_LGC;
				NumOfReads_Cnt_T_u8 = D_NUMOFADCCALREADS_CNT_U8;
			}
		}
		
		/* Read Results */
		ReadResults_Cnt_T_u32 += adcREG->CALR;
		NumOfReads_Cnt_T_u8++;
	}

	if(ConvTimeOut_Cnt_T_lgc == D_FALSE_CNT_LGC)
	{
		/* Set HILO bit */
		adcREG->CALCR |= 0x00000100U;
		NumOfReads_Cnt_T_u8 = 0u;
		while(NumOfReads_Cnt_T_u8 < D_NUMOFADCCALREADS_CNT_U8) 
		{
			/* Start the ADC conversion */
			adcREG->CALCR |= 0x00010000U;

			/* Get start time for wait period */
			GetSystemTime_uS_u32(&StartTime_uS_T_u32);

			/* Wait for ADC conversion to complete */
			while((0U != (adcREG->CALCR & 0x00010000U)) && (ConvTimeOut_Cnt_T_lgc == D_FALSE_CNT_LGC))
			{
				DtrmnElapsedTime_uS_u16(StartTime_uS_T_u32, &ElapsedTime_uS_T_u16);

				if( ElapsedTime_uS_T_u16 >= k_MaxADCConvTime_uS_u16 )
				{
					ConvTimeOut_Cnt_T_lgc = D_TRUE_CNT_LGC;
					NumOfReads_Cnt_T_u8 = D_NUMOFADCCALREADS_CNT_U8;
				}
			}

			/* Read Results */
			ReadResults_Cnt_T_u32 += adcREG->CALR;
			NumOfReads_Cnt_T_u8++;
		}

		if(ConvTimeOut_Cnt_T_lgc == D_FALSE_CNT_LGC)
		{
			/* Each End of Conversion completed within allowed time, assign E_OK to return */
			Status_Cnt_T_u08 = ADC_EVENT_PASSED;

			/* Load the ADCALR register with the 2s complement of the computed error correction value */
			adcREG->CALR = (uint32)((sint32)((sint32)0x07FF - ((sint32)ReadResults_Cnt_T_u32/((sint32)D_NUMOFADCCALREADS_CNT_U8 * 2))));
		}
	}

	*ADCOffset_Cnt_T_u8p8 = (uint16) (ReadResults_Cnt_T_u32 & (uint32)  ((D_NUMOFADCCALREADS_CNT_U8*2u)-1u));
	/* Disable the Calibration Mode */
	adcREG->CALCR = 0x00000000U;

	return(Status_Cnt_T_u08);
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */

/*****************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description              SCR #
-------   -------  --------  -----------------------------------  ----------
01/16/13   1.0      JJW      	Initial Component Creation			CR6519
04/28/13   2      	Selva       QAC fixes added.
05/29/13   3		SP			QAC fixes							8394
06/27/14   4        Selva       Updated for ADC offset compensation 
                                
******************************************************************************/
