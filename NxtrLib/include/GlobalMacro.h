/*****************************************************************************
* Copyright 2010 Nexteer, Inc., All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : GlobalMacro.h
* Module Description: This file contains global macros
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Wed Nov 24 19:06:38 2010
* %version:          6 %
* %derived_by:       qz0qz9 %
* %date_modified:    Thu Jan 19 14:04:53 2012 %
*---------------------------------------------------------------------------*/

#ifndef GLOBALMACRO_H
#define GLOBALMACRO_H

/* include standard math library to use those functions in the macros */
#include <math.h>

/* Inline function prototypes */
INLINE FUNC(float32, FILTERS_CODE) Blend_f32(VAR(float32, AUTOMATIC) In1_Uls_T_f32,
											 VAR(float32, AUTOMATIC) In2_Uls_T_f32,
											 VAR(float32, AUTOMATIC) Factor_Uls_T_f32);


/*****************************************************************************
*  Name:           Blend_f32()
*  Description:    Unity gain blend of two input signals
*  Inputs:         In1_Uls_T_f32 - first signal to be blended 
*				   In2_Uls_T_f32 - second signal to be blended
*				   Factor_Uls_T_f32 - contribution of the second signal
*  Outputs:        Blended signal result
*****************************************************************************/
INLINE FUNC(float32, FILTERS_CODE) Blend_f32(VAR(float32, AUTOMATIC) In1_Uls_T_f32,
											 VAR(float32, AUTOMATIC) In2_Uls_T_f32,
											 VAR(float32, AUTOMATIC) Factor_Uls_T_f32)
{
    return ((In1_Uls_T_f32 * (1.0 - Factor_Uls_T_f32) + (In2_Uls_T_f32 * Factor_Uls_T_f32)));
}

/*****************************************************************************
*  Name:           Redundant_Format_1_m(x)
*  Description:    Transforms the input parameter to be stored redundantly as
*                  1's complement
*  Inputs:         Any number 
*  Outputs:        1's complement
*****************************************************************************/
#define Redundant_Format_1_m(x)   (~(x))

/*****************************************************************************
*  Name:           TableSize_m(x)
*  Description:    Calculates the size of a passed table/array
*  Inputs:         Table/Array symbol
*  Outputs:        Size of table
*****************************************************************************/
#define TableSize_m(Tbl)   (sizeof(Tbl)/sizeof(Tbl[0]))

/*******************************************************************************
  * Name		:	Abs_s16_m(input)
  * Description	:	The absolute value of the input is generated.
  *  				Usage :- output = Abs_s16_m(input);
  * Inputs		:	Value of which the absolute value is to be generated.
  * Outputs		:	Absolute value
  *****************************************************************************/
#define Abs_s16_m(x) (((x)>=(0))?((uint16)(x)):(uint16)((x)*(-1)))

/*******************************************************************************
  * Name		:	Abs_s16_m(input)
  * Description	:	The absolute value of the input is generated.
  *  				Usage :- output = Abs_s16_m(input);
  * Inputs		:	Value of which the absolute value is to be generated.
  * Outputs		:	Absolute value
  *****************************************************************************/
#define Abs_s32_m(x) (((x)>=(0L))?((uint32)(x)):(uint32)((x)*(-1L)))

/*******************************************************************************
  * Name		:	Abs_f32_m(input)
  * Description	:	The absolute value of the input is generated.
  *  				Usage :- output = Abs_f32_m(input);
  * Inputs		:	Value of which the absolute value is to be generated.
  * Outputs		:	Absolute value
  *****************************************************************************/
#define Abs_f32_m(x) fabsf(x)

/*******************************************************************************
  * Name		:	Sign_s16_m(input)
  * Description	:	The sign of the input is generated.
  *  				Usage :- output = Sign_s16_m(input);
  * Inputs		:	Value of which the sign is to be generated.
  * Outputs		:	Returns 1 for positive input and -1 for negative inputs.
  *****************************************************************************/
#define Sign_s16_m(x) (((x)>=(0))?((1)):((-1)))

/*******************************************************************************
  * Name		:	Sign_s32_m(input)
  * Description	:	The sign of the input is generated.
  *  				Usage :- output = Sign_s32_m(input);
  * Inputs		:	Value of which the sign is to be generated.
  * Outputs		:	Returns 1 for positive input and -1 for negative inputs.
  *****************************************************************************/
#define Sign_s32_m(x) (((x)>=(sint32)(0))?((1)):((-1)))

/*******************************************************************************
  * Name		:	Sign_f32_m(input)
  * Description	:	The sign of the input is generated.
  *  				Usage :- output = Sign_f32_m(input);
  * Inputs		:	Value of which the sign is to be generated.
  * Outputs		:	Returns 1 for positive input and -1 for negative inputs.
  *****************************************************************************/
#define Sign_f32_m(x) (((x)>=(0.0f))?((1)):((-1)))

/*******************************************************************************
  * Name		:	Min_m(input1,input2)
  * Description	:	Minimum of two inputs is generated.
  *  				Usage :- output = Min_m(input1,input2);
  * Inputs		:	Two inputs of which minimum is to be generated.
  * Outputs		:	Minimum of the two inputs.
  *****************************************************************************/
#define Min_m(p,q) (((p)<=(q))?(p):(q))


/*******************************************************************************
  * Name		:	Max_m(input1,input2)
  * Description	:	Maximum of two inputs is generated.
  *  				Usage :- output = Max_m(input1,input2);
  * Inputs		:	Two inputs of which maximum is to be generated.
  * Outputs		:	Maximum of the two inputs.
  *****************************************************************************/
#define Max_m(p,q) (((p)>=(q))?(p):(q))


/*******************************************************************************
  * Name		:	Limit_m(value, low_limit, high_limit)
  * Description	:	This macro will will limit a variable 
  *					to the required range
  * Inputs		:	Input value, Lower Limit, Higher limit 
  * Outputs		:	Limited value (counts) 
  *****************************************************************************/
#define Limit_m(value, low_limit, high_limit)\
(  ((value) >= (high_limit)) ? (high_limit) :\
	( ((value) <= (low_limit)) ? (low_limit) :\
	(value) )  )

/*******************************************************************************
  * Name		:	DiagNStep_m(input1,input2)
  * Description	:	Reduces input1 by input2.NStep as long as input1 is large
  *                 enough, otherwise 0.
  *  				Usage :- output = DiagNStep_m(input1,input2);
  * Inputs		:	Fault Accumulator and Diag Settings.
  * Outputs		:	Modified accumulator value
  *****************************************************************************/
#define DiagNStep_m(Acc, Settings) \
(((Acc) > (Settings.NStep)) ? ((Acc) - (Settings.NStep)) : (0U))


/*******************************************************************************
  * Name		:	DiagPStep_m(input1,input2)
  * Description	:	Increment input1 by input2.PStep as long as input1 does
  *                 not exceed input2.Threshold, otherwise input2.Threshold.
  *  				Usage :- output = DiagPStep_m(input1,input2);
  * Inputs		:	Fault Accumulator and Diag Settings.
  * Outputs		:	Modified accumulator value
  *****************************************************************************/
#define DiagPStep_m(Acc, Settings) \
(((Acc) < ((Settings.Threshold) - (Settings.PStep)))? \
    ((Acc) + (Settings.PStep)) : (Settings.Threshold))


/*******************************************************************************
  * Name		:	DiagFailed_m(input1,input2)
  * Description	:	Determines if input1 is at or above the input2.Threshold
  *  				Usage :- output = DiagFailed_m(input1,input2);
  * Inputs		:	Fault Accumulator and Diag Settings.
  * Outputs		:	TRUE or FALSE
  *****************************************************************************/
#define DiagFailed_m(Acc, Settings) \
(((Acc) >= (Settings.Threshold)) ? (TRUE) : (FALSE))


#endif


/******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author 			Change Description              SCR #
 				  					 (MDD Rev & Date) 		
-------   -------   --------  -----------------------------------  ----------
11/24/2010	1.0	    JJW        Initial Version
11/28/2010  2.0     LWW        Added additional floating point macros
11/07/2011  3       JJW        Changed Abs_f32_m to use single precision compiler
                                absolute function fabsf
01/19/2012  5       SMW        Updated Blend_f32 to make the factor define the contribution
                               of the second passed parameter instead of the first.  
                               Anomaly 2825
01/19/2012  6       SMW        Updated for missing parenthesis
******************************************************************************/
