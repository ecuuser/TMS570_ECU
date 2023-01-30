/*****************************************************************************
* Copyright 2010 Nexteer, Inc., All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : filters.c
* Module Description: This file contains filter function definitions
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Sun Nov 28 13:46:22 2010
* %version:          1 %
* %derived_by:       xz0btk %
* %date_modified:    Tue Nov 29 13:31:19 2011 %
*---------------------------------------------------------------------------*/

#include "filters.h"

														
/*******************************************************************************
  * Name		:	NF_Init_f32
  * Description	:	Floating point notch filter init to be called before
  *             :    all other notch filter functions. This initialization function
  *             :    sets the initial state variable values and captures the filter
  *             :    tuning reference.
  * Inputs		:	In_Uls_T_f32: Input to the Low Pass Filter
  *             :   SVPtr_Cnt_T_Str: Pointer to the State Variable Data Type
  *             :   FiltK_Cnt_T_Str: Pointer to the Filter Constant Data Type  
  * Outputs		:	SV structure updated
  *****************************************************************************/
FUNC(void, FILTERS_CODE) NF_Init_f32(VAR(float32, AUTOMATIC) In_Uls_T_f32, 
                                     P2VAR(NotchFiltSV_Str, AUTOMATIC, AUTOMATIC) SVPtr_Cnt_T_Str, 
                                     P2CONST(NotchFiltK_Str, AUTOMATIC, AUTOMATIC) FiltK_Cnt_T_Str)
{
	
	SVPtr_Cnt_T_Str->KPtr_Cnt_Str = FiltK_Cnt_T_Str;
	
	/* This Initialization assumes unity gain tuning */
    SVPtr_Cnt_T_Str->Out_Uls_f32 = In_Uls_T_f32;

	/* SV1 initialization for unity gain filter */
	SVPtr_Cnt_T_Str->SV1_Uls_f32 = In_Uls_T_f32 * (FiltK_Cnt_T_Str->B1_Uls_f32 + FiltK_Cnt_T_Str->B2_Uls_f32 -
												   FiltK_Cnt_T_Str->A1_Uls_f32 - FiltK_Cnt_T_Str->A2_Uls_f32);

	/* SV2 initialization for unity gain filter */
	SVPtr_Cnt_T_Str->SV2_Uls_f32 = In_Uls_T_f32 * (FiltK_Cnt_T_Str->B2_Uls_f32  - FiltK_Cnt_T_Str->A2_Uls_f32);
    
    return;
}



/******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author 			Change Description              SCR #
 				  					 (MDD Rev & Date) 		
-------   -------   --------  -----------------------------------  ----------
11/28/2011	1	    JJW       Initial Version
******************************************************************************/
