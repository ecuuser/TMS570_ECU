/*****************************************************************************
* Copyright 2010 Nexteer, Inc., All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Filter_Type.h
* Module Description: This file contains filter type definitions
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Sun Nov 28 13:46:22 2010
* %version:          3 %
* %derived_by:       nzx5jd %
* %date_modified:    Tue Apr 24 09:03:08 2012 %
*---------------------------------------------------------------------------*/
#ifndef FILTER_TYPES_H
#define FILTER_TYPES_H

#include "Std_Types.h" 

/* Type Defines for Filter Data Structures */
typedef struct {
	VAR(float32, AUTOMATIC)  A1_Uls_f32;
	VAR(float32, AUTOMATIC)  A2_Uls_f32;
	VAR(float32, AUTOMATIC)  B0_Uls_f32;
	VAR(float32, AUTOMATIC)  B1_Uls_f32;
	VAR(float32, AUTOMATIC)  B2_Uls_f32;
}NotchFiltK_Str;

typedef struct {
	VAR(float32, AUTOMATIC)					  		SV1_Uls_f32;
	VAR(float32, AUTOMATIC)  						SV2_Uls_f32;
	VAR(float32, AUTOMATIC)  						Out_Uls_f32;
	P2CONST(NotchFiltK_Str, AUTOMATIC, AUTOMATIC)   KPtr_Cnt_Str;
}NotchFiltSV_Str;

/* NOTE: the filter macros assume that the names of elements between these
		 structures are the same (SV_Uls_f32 and K_Uls_f32) */
typedef struct {
    VAR(float32, AUTOMATIC) SV_Uls_f32;
    VAR(float32, AUTOMATIC) K_Uls_f32;
}LPF32KSV_Str;

typedef struct {
    VAR(LPF32KSV_Str, AUTOMATIC) LPF_Str;
    VAR(float32, AUTOMATIC)      CF_Uls_f32;
}HPF32KSV_Str;

#endif


/******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author 			Change Description              SCR #
 				  					 (MDD Rev & Date) 		
-------   -------   --------  -----------------------------------  ----------
11/28/2011	1	    JJW       Initial Version
02/02/2012  2       JWJ       Added floating point filt structure    4845
04/26/2012  3       OT        Added HP floating point filt structure 5302
******************************************************************************/
