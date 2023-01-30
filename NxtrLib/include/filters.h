/*****************************************************************************
* Copyright 2010 Nexteer, Inc., All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : filters.h
* Module Description: This file contains filter macro definitions
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Sun Nov 28 13:46:22 2010
* %version:          8 %
* %derived_by:       bz1q07 %
* %date_modified:    Thu Dec  5 16:30:19 2013 %
*---------------------------------------------------------------------------*/
#ifndef FILTERS_H
#define FILTERS_H

#include <math.h>
#include "Std_Types.h" 
#include "GlobalMacro.h"
#include "Filter_Types.h"


#define D_PI 3.141592653589793f
#define D_2PI 6.283185307179586f


/* External Declarations for filter functions */
extern FUNC(void, FILTERS_CODE) NF_Init_f32(VAR(float32, AUTOMATIC) In_Uls_T_f32, 
                                            P2VAR(NotchFiltSV_Str, AUTOMATIC, AUTOMATIC) SVPtr_Cnt_T_Str, 
                                            P2CONST(NotchFiltK_Str, AUTOMATIC, AUTOMATIC) FiltK_Cnt_T_Str);

INLINE FUNC(void, FILTERS_CODE) NF_SvUpdate_f32(VAR(float32, AUTOMATIC) In_Uls_T_f32, 
                                                         P2VAR(NotchFiltSV_Str, AUTOMATIC, AUTOMATIC) SVPtr_T_Cnt_Str,
														 P2CONST(NotchFiltK_Str, AUTOMATIC, AUTOMATIC) FiltK_Cnt_T_Str);
														 
INLINE FUNC(float32, FILTERS_CODE) NF_OpUpdate_f32(VAR(float32, AUTOMATIC) In_Uls_T_f32, 
                                                        P2VAR(NotchFiltSV_Str, AUTOMATIC, AUTOMATIC) SVPtr_T_Cnt_Str);
														
INLINE FUNC(float32, FILTERS_CODE) NF_FullUpdate_f32(VAR(float32, AUTOMATIC) In_Uls_T_f32, 
                                                        P2VAR(NotchFiltSV_Str, AUTOMATIC, AUTOMATIC) SVPtr_Cnt_T_Str,
														P2CONST(NotchFiltK_Str, AUTOMATIC, AUTOMATIC) FiltK_Cnt_T_Str);
														
/*############################# Notch Filter #####################################*/
/*******************************************************************************
  * Name		:	NF_SvUpdate_f32
  * Description	:	Partial Notch filter implementation to be called before
  *             :    NF_OpUpdate_f32. A partial filter implementation is
  *             :    provided to satisfy cases where short run-time is required. 
  * Inputs		:	In_Uls_T_f32: Input to the Low Pass Filter
  *             :   SVPtr_Cnt_T_Str: Pointer to the State Variable Structure
  *				:	FiltK_Cnt_T_Str: Pointer to the Filter Constant Data Structure
  * Outputs		:	SV structure updated
  *****************************************************************************/
INLINE FUNC(void, FILTERS_CODE) NF_SvUpdate_f32(VAR(float32, AUTOMATIC) In_Uls_T_f32, 
                                                         P2VAR(NotchFiltSV_Str, AUTOMATIC, AUTOMATIC) SVPtr_Cnt_T_Str,
														 P2CONST(NotchFiltK_Str, AUTOMATIC, AUTOMATIC) FiltK_Cnt_T_Str)
{
	SVPtr_Cnt_T_Str->KPtr_Cnt_Str = FiltK_Cnt_T_Str;
	
    SVPtr_Cnt_T_Str->SV1_Uls_f32 = (SVPtr_Cnt_T_Str->SV2_Uls_f32 + (In_Uls_T_f32 * SVPtr_Cnt_T_Str->KPtr_Cnt_Str->B1_Uls_f32)) -
                            (SVPtr_Cnt_T_Str->Out_Uls_f32 * SVPtr_Cnt_T_Str->KPtr_Cnt_Str->A1_Uls_f32);

    SVPtr_Cnt_T_Str->SV2_Uls_f32 = (SVPtr_Cnt_T_Str->KPtr_Cnt_Str->B2_Uls_f32 * In_Uls_T_f32) -
                             (SVPtr_Cnt_T_Str->Out_Uls_f32 * SVPtr_Cnt_T_Str->KPtr_Cnt_Str->A2_Uls_f32);
    
    return;
}

/*******************************************************************************
  * Name		:	NF_OpUpdate_f32
  * Description	:	Partial Notch filter implementation to be called after
  *             :    NF_SvUpdate_f32. A partial filter implementation is
  *             :    provided to satisfy cases where short run-time is required. 
  * Inputs		:	In_Uls_T_f32: Input to the Low Pass Filter
  *             :   SVPtr_Cnt_T_Str: Pointer to the State Variable Data Type
  *             :   FiltK_Cnt_T_Str: Pointer to the Filter Constant Data Type  
  * Outputs		:	Filtered Output, SV Structure Updated
  *****************************************************************************/
INLINE FUNC(float32, FILTERS_CODE) NF_OpUpdate_f32(VAR(float32, AUTOMATIC) In_Uls_T_f32, 
                                                        P2VAR(NotchFiltSV_Str, AUTOMATIC, AUTOMATIC) SVPtr_Cnt_T_Str)
{
    SVPtr_Cnt_T_Str->Out_Uls_f32 = SVPtr_Cnt_T_Str->SV1_Uls_f32 + (SVPtr_Cnt_T_Str->KPtr_Cnt_Str->B0_Uls_f32 * In_Uls_T_f32);

    return (SVPtr_Cnt_T_Str->Out_Uls_f32);
}

/*******************************************************************************
  * Name		:	NF_FullUpdate_f32
  * Description	:	Full Notch filter execution
  * Inputs		:	In_Uls_T_f32: Input to the Low Pass Filter
  *             :   SVPtr_Cnt_T_Str: Pointer to the State Variable Data Type
  *             :   FiltK_Cnt_T_Str: Pointer to the Filter Constant Data Type  
  * Outputs		:	Filtered Output
  *****************************************************************************/
INLINE FUNC(float32, FILTERS_CODE) NF_FullUpdate_f32(VAR(float32, AUTOMATIC) In_Uls_T_f32, 
                                                        P2VAR(NotchFiltSV_Str, AUTOMATIC, AUTOMATIC) SVPtr_Cnt_T_Str,
														P2CONST(NotchFiltK_Str, AUTOMATIC, AUTOMATIC) FiltK_Cnt_T_Str)
{
    /* OpUpdate must be executed prior to the SvUpdate to use the z-1 value of SV1 for the output computation */
	NF_OpUpdate_f32(In_Uls_T_f32, SVPtr_Cnt_T_Str);
    NF_SvUpdate_f32(In_Uls_T_f32, SVPtr_Cnt_T_Str, FiltK_Cnt_T_Str);
    return (SVPtr_Cnt_T_Str->Out_Uls_f32);
}

/*############################# 1 LP1-C #####################################*/
/****** UNSIGNED INPUT FILTER *******/  
/*******************************************************************************
  * Name		:	LPF_SvInit_u16InFixKTrunc_m(input)
  * Description	:	The equation to initialize the state variable, (Node e)
  *				:	is filt_SV = Input * Kd. For a 16 bit filter coefficient,
  *				:   the value of Kd is 65536.
  * Inputs		:	Input :- Input to the Low Pass Filter
  * Outputs		:	Initialized value of Node e
  *****************************************************************************/

#define LPF_SvInit_u16InFixKTrunc_m(input) (((uint32)input)<<(16))

/*******************************************************************************
  * Name		:	LPF_SvUpdate_u16InFixKTrunc_m(input,filt_SV,Kn)
  * Description	:	The equation to update the state variable, (Node e)
  *				:	is filt_SV = ( ( Input - (filt_SV / Kd) ) * Kn ) + filt_SV. 
  *				:   For a 16 bit filter coefficient, the value of Kd is 65536.
  * Inputs		:	filt_SV	:- Calculated Value of Filter output
  * Outputs		:	Value of Node e (filt_SV)
  *****************************************************************************/

#define LPF_SvUpdate_u16InFixKTrunc_m(input,filt_SV,Kn) (\
((((uint32)input)-((filt_SV)>>(16)))*((uint32)Kn))+(filt_SV))

/*******************************************************************************
  * Name		:	LPF_OpInit_u16InFixKTrunc_m(input,filt_SV,Kn)
  * Description	:	The equation to initialize the output (Node O) is :
  *				:	filt_O = [((Input-(filt_SV/Kd))*Kn)+filt_SV]/Kd
  * Inputs		:	Input 	:- Input to the Low Pass Filter
  *				:	filt_SV :- Initialized value of the State variable
  *				:	Kn 		:- Numerator of the Filter Coefficient, K.
  *				:   For a 16 bit filter coefficient, the value of Kd is 65536.  
  * Outputs		:	Value of filt_O
  *****************************************************************************/

#define LPF_OpInit_u16InFixKTrunc_m(input,filt_SV,Kn) (\
(((((uint32)input)-((filt_SV)>>(16)))*((uint32)Kn))+\
(filt_SV))>>(16))

/*******************************************************************************
  * Name		:	LPF_OpUpdate_u16InFixKTrunc_m(filt_SV)
  * Description	:	The equation to initialize the output (Node O) is :
  *				:	filt_O = filt_SV/Kd
  * Inputs		:	filt_SV :- State variable value as calculated by State
  *				:	Variable Update macro
  *				:   For a 16 bit filter coefficient, the value of Kd is 65536.  
  * Outputs		:	Value of filt_O
  *****************************************************************************/

#define LPF_OpUpdate_u16InFixKTrunc_m(filt_SV) ((filt_SV)>>(16))

/****** SIGNED INPUT FILTER *******/
/*******************************************************************************
  * Name		:	LPF_SvInit_s16InFixKTrunc_m(input)
  * Description	:	The equation to initialize the state variable, (Node e)
  *				:	is filt_SV = Input * Kd. For a 16 bit filter coefficient,
  *				:   the value of Kd is 65536.
  * Inputs		:	Input :- Input to the Low Pass Filter
  * Outputs		:	Initialized value of Node e
  *****************************************************************************/

#define LPF_SvInit_s16InFixKTrunc_m(input) ((sint32)(((uint32)(input))<<(16)))

/*******************************************************************************
  * Name		:	LPF_SvUpdate_s16InFixKTrunc_m(input,filt_SV,Kn)
  * Description	:	The equation to update the state variable, (Node e)
  *				:	is filt_SV = ( ( Input - (filt_SV / Kd) ) * Kn ) + filt_SV. 
  *				:   For a 16 bit filter coefficient, the value of Kd is 65536.
  * Inputs		:	filt_SV	:- Calculated Value of Filter output
  * Outputs		:	Value of Node e (filt_SV)
  *****************************************************************************/

#define LPF_SvUpdate_s16InFixKTrunc_m(input,filt_SV,Kn) (((filt_SV) >= (0L)) ?\
(((((sint32)(input)-(sint32)((uint32)(filt_SV)>>(16))))*(sint32)(Kn)) + (filt_SV)):\
((((((sint32)(input)-(sint32)((0xFFFF0000ul)|((uint32)(filt_SV)>>(16))))*(sint32)(Kn)) + (filt_SV)))))

/*******************************************************************************
  * Name		:	LPF_OpInit_s16InFixKTrunc_m(input,filt_SV,Kn)
  * Description	:	The equation to initialize the output (Node O) is :
  *				:	filt_O = [((Input-(filt_SV/Kd))*Kn)+filt_SV]/Kd
  * Inputs		:	Input 	:- Input to the Low Pass Filter
  *				:	filt_SV :- Initialized value of the State variable
  *				:	Kn 		:- Numerator of the Filter Coefficient, K.
  *				:   For a 16 bit filter coefficient, the value of Kd is 65536.  
  * Outputs		:	Value of filt_O
  *****************************************************************************/

#define LPF_OpInit_s16InFixKTrunc_m(input,filt_SV,Kn) ( ((filt_SV) >= (0L)) ?\
(sint32)((0xFFFF0000ul)|((uint32)((((((sint32)(input) - (sint32)((uint32)(filt_SV)>>(16)))) * (sint32)(Kn)) + (filt_SV)))>>(16))):\
(sint32)((0xFFFF0000ul)|((uint32)((((((sint32)(input) - (sint32)((0xFFFF0000ul)|((uint32)(filt_SV)>>(16))))) * (sint32)(Kn)) + (filt_SV)))>>(16))))

/*******************************************************************************
  * Name		:	LPF_OpUpdate_s16InFixKTrunc_m(filt_SV)
  * Description	:	The equation to initialize the output (Node O) is :
  *				:	filt_O = filt_SV/Kd
  * Inputs		:	filt_SV :- State variable value as calculated by State
  *				:	Variable Update macro
  *				:   For a 16 bit filter coefficient, the value of Kd is 65536.  
  * Outputs		:	Value of filt_O
  *****************************************************************************/
  
#define LPF_OpUpdate_s16InFixKTrunc_m(filt_SV) ((sint16)((uint32)(filt_SV)>>(16)))

/*############################### 1 LP1-B ####################################*/
/****** UNSIGNED INPUT FILTER *******/  
/*******************************************************************************
  * Name		:	LPF_SvInit_u16InVarKTrunc_m(input,Kd,Ddb)
  * Description	:	The equation to initialize the state variable, (Node e)
  *				:	is filt_SV = Input*Kd*Ddb 
  * Inputs		:	Input 	:- Input to the Low Pass Filter
  *				:	Kd 		:- Denominator bits of filter coeff K
  *				:	Ddb 	:- Deadband factor in bits
  * Outputs		:	Initialized value of Node e
  *****************************************************************************/

#define LPF_SvInit_u16InVarKTrunc_m(input,Kd,Ddb) (\
((Ddb) != (0)) ? \
((((uint32)input)<<(Kd))<<(Ddb)): \
(((uint32)input)<<(Kd)))

/*******************************************************************************
  * Name		:	LPF_SvUpdate_u16InVarKTrunc_m(input,filt_SV,Kn,Kd,Ddb)
  * Description	:	The equation to update the state variable, (Node e)
  *				:	is filt_SV = (((Input*Ddb)-(filt_SV/Kd))*Kn)+filt_SV  
  * Inputs		:	Input	:- Input to the Low Pass Filter
  *				:	filt_SV :- Initialized value of the State variable
  *				:	Kd 		:- Denominator bits of filter coeff K
  *				:	Ddb 	:- Deadband factor in bits
  *				:	Kn 		:- numerator of filter coeff K
  * Outputs		:	Value of Node e (filt_SV)
  *****************************************************************************/

#define LPF_SvUpdate_u16InVarKTrunc_m(input,filt_SV,Kn,Kd,Ddb) (\
((Ddb) != (0)) ?\
((((((uint32)input)<<(Ddb))-((filt_SV)>>(Kd)))*((uint32)Kn))+(filt_SV)):\
(((((uint32)input)-((filt_SV)>>(Kd)))*((uint32)Kn))+(filt_SV)))

/*******************************************************************************
  * Name		:	LPF_OpInit_u16InVarKTrunc_m(Input,filt_SV,Kn,Kd,Ddb)
  * Description	:	The equation to initialize the output (Node O) is :
  *				:	filt_O = [(((Input*Ddb)-(filt_SV/Kd))*Kn)+filt_SV]/(Kd*Ddb)  
  * Inputs		:	Input 	:- Input to the Low Pass Filter
  *				:	filt_SV :- State variable value as calculated by State
  *				:	Variable Update macro
  *				:	Kn 		:- Numerator of the Filter Coefficient, K.
  * Outputs		:	Value of filt_O
  *****************************************************************************/

#define LPF_OpInit_u16InVarKTrunc_m(Input,filt_SV,Kn,Kd,Ddb) (\
((Ddb) != (0)) ?\
((((((((uint32)Input)<<(Ddb))-((filt_SV)>>(Kd)))*((uint32)Kn))+\
(filt_SV))>>(Kd))>>(Ddb)):\
((((((uint32)Input)-((filt_SV)>>(Kd)))*((uint32)Kn))+\
(filt_SV))>>(Kd)))

/*******************************************************************************
  * Name		:	LPF_OpUpdate_u16InVarKTrunc_m(filt_SV,Kd,Ddb)
  * Description	:	The equation to initialize the output (Node O) is :
  *				:	filt_O = filt_SV/(Kd*Ddb)
  * Inputs		:	filt_SV :- State variable value as calculated by State
  *				:	Variable Update macro
  *				:	Kd 		:- Numerator of the Filter Coefficient, K.
  *				:	Ddb 	:- Deadband factor in bits
  * Outputs		:	Value of filt_O
  *****************************************************************************/

#define LPF_OpUpdate_u16InVarKTrunc_m(filt_SV,Kd,Ddb) (\
((Ddb) != (0)) ?\
(((filt_SV)>>(Kd))>>(Ddb)):((filt_SV)>>(Kd)))

/****** SIGNED INPUT FILTER *******/
/*******************************************************************************
  * Name		:	LPF_SvInit_s16InVarKTrunc_m(input,Kd,Ddb)
  * Description	:	The equation to initialize the state variable, (Node e)
  *				:	is filt_SV = Input*Kd*Ddb 
  * Inputs		:	Input 	:- Input to the Low Pass Filter
  *				:	Kd 		:- Denominator bits of filter coeff K
  *				:	Ddb 	:- Deadband factor in bits
  * Outputs		:	Initialized value of Node e
  *****************************************************************************/

#define LPF_SvInit_s16InVarKTrunc_m(input,Kd,Ddb) (\
((Ddb) != (uint16)(0)) ? \
((sint32)((((uint32)input)<<(Kd))<<(Ddb))): \
((sint32)(((uint32)input)<<(Kd))))
/*******************************************************************************
  * Name		:	LPF_SvUpdate_s16InVarKTrunc_m(input,filt_SV,Kn,Kd,Ddb)
  * Description	:	The equation to update the state variable, (Node e)
  *				:	is filt_SV = (((Input*Ddb)-(filt_SV/Kd))*Kn)+filt_SV  
  * Inputs		:	Input	:- Input to the Low Pass Filter
  *				:	filt_SV :- Initialized value of the State variable
  *				:	Kd 		:- Denominator bits of filter coeff K
  *				:	Ddb 	:- Deadband factor in bits
  *				:	Kn 		:- numerator of filter coeff K
  * Outputs		:	Value of Node e (filt_SV)
  *****************************************************************************/

#define LPF_SvUpdate_s16InVarKTrunc_m(input,filt_SV,Kn,Kd,Ddb) (\
((filt_SV) >= (sint32)0) ?\
(posIn(input,filt_SV,Kn,Kd,Ddb)) :\
(negIn(input,filt_SV,Kn,Kd,Ddb)))

#define posIn(input,filt_SV,Kn,Kd,Ddb) (\
((Ddb) != (uint16)(0)) ?\
((((sint32)((uint32)(input)<<(Ddb))-(sint32)((Abs_s32_m(filt_SV))>>(Kd)))*((sint32)Kn))+(filt_SV)):\
((((sint32)(input)-(sint32)((Abs_s32_m(filt_SV))>>(Kd)))*((sint32)Kn))+(filt_SV)))

#define negIn(input,filt_SV,Kn,Kd,Ddb) (\
((Ddb) != (uint16)(0)) ?\
((((((sint32)((uint32)(input)<<(Ddb)))-((((-1L)*((sint32)(Abs_s32_m(filt_SV)>>(Kd)))))))*(sint32)(Kn)))+(filt_SV)):\
((((((sint32)input)-((((-1L)*((sint32)(Abs_s32_m(filt_SV)>>(Kd)))))))*(sint32)(Kn)))+(filt_SV)))

/*******************************************************************************
  * Name		:	LPF_OpInit_s16InVarKTrunc_m(input,filt_SV,Kn,Kd,Ddb)
  * Description	:	The equation to initialize the output (Node O) is :
  *				:	filt_O = [(((Input*Ddb)-(filt_SV/Kd))*Kn)+filt_SV]/(Kd*Ddb)  
  * Inputs		:	Input 	:- Input to the Low Pass Filter
  *				:	filt_SV :- State variable value as calculated by State
  *				:	Variable Update macro
  *				:	Kn 		:- Numerator of the Filter Coefficient, K.
  * Outputs		:	Value of filt_O
  *****************************************************************************/

#define LPF_OpInit_s16InVarKTrunc_m(input,filt_SV,Kn,Kd,Ddb) (\
((filt_SV) >= (sint32)0) ?\
(pos2In(input,filt_SV,Kn,Kd,Ddb)) :\
(neg2In(input,filt_SV,Kn,Kd,Ddb)))

#define pos2In(input,filt_SV,Kn,Kd,Ddb) (\
((Ddb) != (uint16)(0)) ?\
((sint32)(((((uint32)((((sint32)((uint32)(input)<<(Ddb))-(sint32)((Abs_s32_m(filt_SV))>>(Kd)))*((SINT32)Kn))+(filt_SV)))) >> (Kd)) >> (Ddb))):\
((sint32)((((uint32)((((sint32)(input)-(sint32)((Abs_s32_m(filt_SV))>>(Kd)))*((sint32)Kn))+(filt_SV)))) >> (Kd))))

#define neg2In(input,filt_SV,Kn,Kd,Ddb) (\
((Ddb) != (uint16)(0)) ?\
((-1L)*(sint32)(((Abs_s32_m((((((sint32)((uint32)(input)<<(Ddb)))-((((-1L)*((sint32)(Abs_s32_m(filt_SV)>>(Kd)))))))*(sint32)(Kn)))+(filt_SV))) >> (Kd)) >> (Ddb))):\
((-1L)*(sint32)(((Abs_s32_m((((((sint32)((uint32)(input)))-((((-1L)*((sint32)(Abs_s32_m(filt_SV)>>(Kd)))))))*(sint32)(Kn)))+(filt_SV)))) >> (Kd))))

/*******************************************************************************
  * Name		:	LPF_OpUpdate_s16InVarKTrunc_m(filt_SV,Kd,Ddb)
  * Description	:	The equation to initialize the output (Node O) is :
  *				:	filt_O = filt_SV/(Kd*Ddb)
  * Inputs		:	filt_SV :- State variable value as calculated by State
  *				:	Variable Update macro
  *				:	Kd 		:- Numerator of the Filter Coefficient, K.
  *				:	Ddb 	:- Deadband factor in bits
  * Outputs		:	Value of filt_O
  *****************************************************************************/

#define LPF_OpUpdate_s16InVarKTrunc_m(filt_SV,Kd,Ddb) (\
((filt_SV) >= 0L) ?\
(pos3In(filt_SV,Kd,Ddb)) :\
(neg3In(filt_SV,Kd,Ddb)))

#define pos3In(filt_SV,Kd,Ddb) (\
((Ddb) != (uint16)(0L)) ?\
(sint32)(((((((Abs_s32_m(filt_SV)>>(Kd))))))) >> (Ddb)):(LONG)(((((Abs_s32_m(filt_SV)>>(Kd)))))))

#define neg3In(filt_SV,Kd,Ddb) (\
((Ddb) != (uint16)(0L)) ?\
(sint32)(((uint32)(((-1L)*((sint32)(Abs_s32_m(filt_SV)>>(Kd)))))) >> (Ddb)):((((-1L)*((sint32)(Abs_s32_m(filt_SV)>>(Kd)))))))



/*############################### 1 LP1-CF ###################################*/
/*******************************************************************************
  * Name		:	LPF_KUpdate_f32_m
  * Description	:	The equation to calculate coefficient K is:
  *				:	K = 1 - exp(-2PI * Fp * T)
  * Inputs		:   Fp_f32       :- Pole Cutoff Frequency (Hz)
  *             :   T_f32        :- Filter sampling interval (sec)
  *             :   LPF32KSV_Ptr :- Pointer to the state variable structure
  * Outputs		:	Assignment returns coefficient K
  *****************************************************************************/
#define LPF_KUpdate_f32_m(Fp_f32, T_f32, LPF32KSV_Ptr) \
    ((LPF32KSV_Ptr)->K_Uls_f32 = (1.0f - expf(-D_2PI * (Fp_f32) * (T_f32))))


/*******************************************************************************
  * Name		:	LPF_OpUpdate_f32_m
  * Description	:	The equation to calculate the output (Node O) is :
  *				:	filt_O = ((Input - prev_Out) * K) + prev_Out
  * Inputs		:	input_f32    :- Input to the Low Pass Filter
  *				:	LPF32KSV_Ptr :- Pointer to the state variable structure
  * Outputs		:	Assignment returns filter output (filt_O)
  *****************************************************************************/
#define LPF_OpUpdate_f32_m(input_f32, LPF32KSV_Ptr) \
	((LPF32KSV_Ptr)->SV_Uls_f32 = ((((input_f32) - (LPF32KSV_Ptr)->SV_Uls_f32) * (LPF32KSV_Ptr)->K_Uls_f32) + (LPF32KSV_Ptr)->SV_Uls_f32))


/*******************************************************************************
  * Name		:	LPF_Init_f32_m
  * Description	:	The equation to init coefficient K is:
  *				:	K = 1 - exp(-2PI * Fp * T)
  * Inputs		:	input_f32    :- Initial input to the filter
  *             :   Fp_f32       :- Pole Cutoff Frequency (Hz)
  *             :   T_f32        :- Filter sampling interval (sec)
  *             :   LPF32KSV_Ptr :- Pointer to the state variable structure
  * Outputs		:	Assignment returns initial output (filt_O)
  *****************************************************************************/
#define LPF_Init_f32_m(input_f32, Fp_f32, T_f32, LPF32KSV_Ptr) \
	((LPF32KSV_Ptr)->SV_Uls_f32 = (input_f32)); \
	LPF_KUpdate_f32_m(Fp_f32, T_f32, LPF32KSV_Ptr)



/*############################### 1 HP-CF ####################################*/
/*******************************************************************************
  * Name		:	HPF_KUpdate_f32_m
  * Description	:	The equation to calculate the correction factor is:
  *				:	CF = (1 + exp(2PI * Fp * T)) / (2 * sqrt(1 + ((2 * Fp * T)^2)))
  * Inputs		:   Fp_f32       :- Pole Cutoff Frequency (Hz)
  *             :   T_f32        :- Filter sampling interval (sec)
  *             :   HPF32KSV_Ptr :- Pointer to the state variable structure
  * Outputs		:	Assignment returns correction factor
  *****************************************************************************/
#define HPF_KUpdate_f32_m(Fp_f32, T_f32, HPF32KSV_Ptr) \
    (HPF32KSV_Ptr)->CF_Uls_f32 = (1.0f + expf(D_2PI * (Fp_f32) * (T_f32))) / (2 * sqrtf(1 + ((2.0f * Fp_f32 * T_f32) * (2.0f * Fp_f32 * T_f32)))); \
	LPF_KUpdate_f32_m((Fp_f32), (T_f32), &((HPF32KSV_Ptr)->LPF_Str))



/*******************************************************************************
  * Name		:	HPF_OpUpdate_f32_m
  * Description	:	The equation to calculate the output (Node O) is :
  *				:	filt_O = (prev_Out + Input - prev_In) * K
  * Inputs		:	input_f32    :- Input to the High Pass Filter
  *				:	HPF32KSV_Ptr :- Pointer to the state variable structure
  * Outputs		:	Assignment returns filter output (filt_O)
  *****************************************************************************/
#define HPF_OpUpdate_f32_m(input_f32, HPF32KSV_Ptr) \
	(((input_f32) - LPF_OpUpdate_f32_m((input_f32), &((HPF32KSV_Ptr)->LPF_Str))) * (HPF32KSV_Ptr)->CF_Uls_f32)


/*******************************************************************************
  * Name		:	HPF_Init_f32_m
  * Description	:	The equation to init coefficient K is:
  *				:	K = exp(-2PI * Fp * T)
  * Inputs		:	input_f32    :- Initial input to the filter
  *             :   Fp_f32       :- Pole Cutoff Frequency (Hz)
  *             :   T_f32        :- Filter sampling interval (sec)
  *             :   HPF32KSV_Ptr :- Pointer to the state variable structure
  * Outputs		:	Assignment returns initial output
  *****************************************************************************/
#define HPF_Init_f32_m(input_f32, Fp_f32, T_f32, HPF32KSV_Ptr) \
	LPF_Init_f32_m((input_f32), (Fp_f32), (T_f32), &((HPF32KSV_Ptr)->LPF_Str)); \
	HPF_KUpdate_f32_m(Fp_f32, T_f32, HPF32KSV_Ptr)



#endif /* end of ifndef FILTERS_H */


/******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author 			Change Description              SCR #
 				  					 (MDD Rev & Date) 		
-------   -------   --------  -----------------------------------  ----------
11/28/2010	1.0	    LWW       Initial Version
12/19/2010  2.0     JJW       Updated usage of Abs_m to use type 
                                specific macro
11/19/2011  3.0     JJW       Added Notch Filter
11/22/2011  4.0     JJW       Corrected order of execution for
                                NF_FullUpdate_f32
12/15/2011  5.0     JJW       ???
02/07/2012  6.0     JWJ       Added floating point low pass         4845
                                filter support
04/26/2012  7.0     OT        Added floating point high pass        5302
                                filter support
12/05/2013  8.0     VT        Added new parameter to functions     11008
								NF_FullUpdate_f32 and NF_SvUpdate_f32
******************************************************************************/
