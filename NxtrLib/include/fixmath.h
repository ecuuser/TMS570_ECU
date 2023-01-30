/*****************************************************************************
* Copyright 2010 Nexteer, Inc., All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : fixmath.h
* Module Description: This file contains fixed point macro definitions
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Sun Nov 28 13:37:12 2010
* %version:          3 %
* %derived_by:       czgng4 %
* %date_modified:    Wed Nov 23 14:05:28 2011 %
*---------------------------------------------------------------------------*/

#ifndef FIXMATH_H
#define FIXMATH_H

#include "fpmtype.h"

/* Macros added to limit MISRA code violations*/
#define Sign2_m(x) (((sint32)(x)>=(sint32)(0))?((1)):((-1)))
#define Abs2_m(x) (((sint32)(x)>=(sint32)(0))?((sint32)(x)):((sint32)(x)*(-1L)))
#define Diff_m(from_type, to_type)\
(\
	 ((totype(from_type)) > (totype(to_type))) ?\
	(((totype(from_type)) - (totype(to_type)))):\
	(((totype(to_type)) - (totype(from_type))))\
)	
#define totype(to_type) ((BPP_##to_type))
#define ShiftVal(from,to) ((from - to))
#define ShiftVal2(from,to) ((from - to - 1))
#define ShiftVal3(to_type) \
( \
	( (totype(to_type)) >= 0 ) ? \
	(totype(to_type)) : (-1 * totype(to_type)) \
)

#define FPM_FloatToFixed_m(value, to_type)\
( \
(to_type)(value * FLOATTOFIXED_##to_type) \
)

#define FPM_FloatToFixedWithRound_m(value, to_type)\
( \
((value < 0.0f)? ((to_type)((value * FLOATTOFIXED_##to_type) - 0.5F)): ((to_type)((value * FLOATTOFIXED_##to_type) + 0.5F))) \
)

#define FPM_FixedToFloat_m(value, from_type)\
( \
((float)value * FIXEDTOFLOAT_##from_type) \
)
  
/*******************************************************************************
  * Name		:	FPM_InitFixedPoint_m(value, to_type)
  * Description	:	The Initialization routine shall scale the engineering value
  *					and return computer value(Counts) in required fixed-point 
  *					math type  
  * Inputs		:	Engineering value, Required Fixed-point data type
  * Outputs		:	Computer value (counts) in fixed-point type
  *****************************************************************************/

#define FPM_InitFixedPoint_m(value,to_type) \
( \
	( (totype(to_type)) >= 0 ) ? \
	        ( ( (value) >= 0.0 ) ? \
             /* If the value is positive, add 0.5 for rounding. */ \
             ((to_type)((((float64)(value)) * (float64)(1ul << (ShiftVal3(to_type)))) + 0.5)) : \
             /* Else for negative values, subtract 0.5 for rounding. */ \
             ((to_type)((((float64)(value)) * (float64)(1ul << (ShiftVal3(to_type)))) - 0.5)) \
        ) : \
        /* Else for negative BPP, divide by 2^BPP.*/ \
        ( ( (value) >= 0.0 ) ? \
             /* If the value is positive, add 0.5 for rounding. */ \
             ((to_type)((((float64)(value)) / (float64)(1ul << (ShiftVal3(to_type)))) + 0.5)) : \
             /* Else for negative values, subtract 0.5 for rounding. */ \
             ((to_type)((((float64)(value)) / (float64)(1ul << (ShiftVal3(to_type)))) - 0.5)) \
        ) \
)


/*******************************************************************************
  * Name		:	FPM_Fix_m(value, to_type)
  * Description	:	The FPM_Fix_m macro will scale the data and return the same 
  *					in the required Fixed-point math type.
  * Inputs		:	Input value, Current Fixed-point data type, 
  *					Required Fixed-point data type
  * Outputs		:	Computer value (counts) in  the Required fixed-point type
  *****************************************************************************/
#define FPM_Fix_m(value, from_type, to_type)\
(\
	((TRUE) == (SIGNED_##from_type)) ?\
		(FPM_Fix_sIn_m(value, from_type, to_type)) :\
		(FPM_Fix_uIn_m(value, from_type, to_type)) \
)
	
#define FPM_Fix_sIn_m(value, from_type, to_type)\
(\
  		((totype(from_type)) > (totype(to_type))) ?\
       		(to_type)((sint32)(Sign2_m(value))*(sint32)(((uint32)(Abs2_m(value)) >> (Diff_m(from_type, to_type))))) :\
       		(to_type)((sint32)(Sign2_m(value))*(sint32)(((uint32)(Abs2_m(value)) << (Diff_m(from_type, to_type)))))  \
)

#define FPM_Fix_uIn_m(value, from_type, to_type)\
(\
   ( ( sizeof(from_type) < sizeof(to_type) ) ?\
     (to_type)Change_TypeA( value, totype(from_type), totype(to_type),from_type ,to_type) :\
\
     /* Otherwise,  cast after. */\
     (to_type)Change_TypeA( value, totype(from_type), totype(to_type),from_type ,to_type) )\
\
)

/* PRIVATE: Use Fix above. */
#define Change_TypeA(value,from_type_bpp,to_type_bpp,from_type,to_type)\
(  ( (from_type_bpp) > (to_type_bpp) ) ?\
       ( (value) >> ( Diff_m(from_type, to_type) ) ) :\
       ( (value) << ( Diff_m(from_type, to_type) ) )  )


/*******************************************************************************
  * Name		:	FPM_FixWithRound_m(value, to_type)
  * Description	:	This macro will scale the data such that the fraction is 
  * 				rounded to the closest magnitude.  
  * Inputs		:	Input value, Current Fixed-point data type, 
  *					Required Fixed-point data type
  * Outputs		:	Computer value (counts) in  the Required fixed-point type
  *****************************************************************************/
  
#define FPM_FixWithRound_m(value, from_type, to_type)\
(\
	((TRUE) == (SIGNED_##from_type)) ?\
		(FPM_FixWithRound_sIn_m(value, from_type, to_type)) :\
		(FPM_FixWithRound_uIn_m(value, from_type, to_type)) \
)
  
#define FPM_FixWithRound_sIn_m(value, from_type, to_type)\
(  ( (totype(from_type)) < (totype(to_type)) ) ?\
  (to_type)(0):\
  (Change_Type2( value, totype(from_type), totype(to_type), to_type, from_type )) \
)

/* PRIVATE: Use Fix above. */
#define Change_Type2(value,from_type_bpp,to_type_bpp, to_type, from_type) \
	(((uint32)Abs2_m(value))  >  (uint32)(MAX_##from_type##to_type)) ?\
  	(FPM_Fix_sIn_m(value, from_type, to_type)) :\
	(to_type)((sint32)(Sign2_m(value)) * \
    	((sint32)((((uint32)Abs2_m(value) + ((uint32)1 << (ShiftVal2(from_type_bpp,to_type_bpp))))/  \
	((uint32)1 << (ShiftVal(from_type_bpp,to_type_bpp)))))))	
	
#define FPM_FixWithRound_uIn_m(value, from_type, to_type)\
(  ( (totype(from_type)) < (totype(to_type)) ) ?\
  (to_type)(0):\
  \
  ((((uint32)value)  >  (uint32)(MAX_##from_type##to_type)) ?\
  (FPM_Fix_uIn_m(value, from_type, to_type)):\
  \
  ((to_type)Change_Type8( value, totype(from_type), totype(to_type), to_type, from_type ))))

/* PRIVATE: Use Fix above. */
#define Change_Type8(value,from_type_bpp,to_type_bpp, to_type, from_type)\
  ( \
    (( ((uint32)value) + ((uint32)1 << ( ShiftVal2(from_type_bpp,to_type_bpp)))) / \
	((uint32)1 << (ShiftVal(from_type_bpp,to_type_bpp))) )	) 
#endif



/******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author 			Change Description              SCR #
 				  					 (MDD Rev & Date) 		
-------   -------   --------  -----------------------------------  ----------
11/28/2010	1.0	    LWW       Initial Version
12/20/2010  2.0     LWW       Fixed FloatToFixed with round, removed
                              FPM_Limit_m
11/23/2011  3.0     LWW       Fixed QAC errors on FPM_FloatToFixedWithRound_m
******************************************************************************/
