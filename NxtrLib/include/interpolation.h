/*****************************************************************************
* Copyright 2002 Delphi Technologies, Inc., All Rights Reserved.
* Delphi Confidential
*
* Module File Name  : interpolation.h
* Module Description: Header file for interpolation functions. To be
*					  included for using interpolation functions.
* Product           : Gen II Plus EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Thu Dec 16 11:37:42 2010
* %version:          5 %
* %derived_by:       nzx5jd %
* %date_modified:    Fri Sep 28 14:18:09 2012 %
*---------------------------------------------------------------------------*/

#ifndef INTERPOLATION_H
#define INTERPOLATION_H

extern sint16 BilinearXYM_s16_u16Xs16YM_Cnt(uint16 BS, uint16 input, const uint16* BSTbl, uint16 BSsize, const uint16* XTbl, const sint16* YMTbl, uint16 Xsize);
extern uint16 BilinearXYM_u16_u16Xu16YM_Cnt(uint16 BS, uint16 input, const uint16* BSTbl, uint16 BSsize, const uint16* XTbl, const uint16* YMTbl, uint16 Xsize);
extern sint16 BilinearXYM_s16_s16Xs16YM_Cnt(uint16 BS, sint16 input, const uint16* BSTbl, uint16 BSsize, const sint16* XTbl, const sint16* YMTbl, uint16 Xsize);
extern uint16 BilinearXYM_u16_s16Xu16YM_Cnt(uint16 BS, sint16 input, const uint16* BSTbl, uint16 BSsize, const sint16* XTbl, const uint16* YMTbl, uint16 Xsize);
extern uint16 BilinearXMYM_u16_u16XMu16YM_Cnt(uint16 BS, uint16 input, const uint16* BSTbl, uint16 BSsize, const uint16* XMTbl, const uint16* YMTbl, uint16 Xsize);
extern sint16 BilinearXMYM_s16_u16XMs16YM_Cnt(uint16 BS, uint16 input, const uint16* BSTbl, uint16 BSsize, const uint16* XMTbl, const sint16* YMTbl, uint16 Xsize);
extern sint16 BilinearXMYM_s16_s16XMs16YM_Cnt(uint16 BS, sint16 input, const uint16* BSTbl, uint16 BSsize, const sint16* XMTbl, const sint16* YMTbl, uint16 Xsize);
extern uint16 BilinearXMYM_u16_s16XMu16YM_Cnt(uint16 BS, sint16 input, const uint16* BSTbl, uint16 BSsize, const sint16* XMTbl, const uint16* YMTbl, uint16 Xsize);

extern uint16 IntplVarXY_u16_u16Xu16Y_Cnt (const uint16*, const uint16*, 
						uint16, uint16);
extern uint16 IntplVarXY_u16_s16Xu16Y_Cnt (const sint16*, const uint16*, 
						uint16, sint16);
extern sint16 IntplVarXY_s16_s16Xs16Y_Cnt (const sint16*, const sint16*, 
						uint16, sint16);
extern sint16 IntplVarXY_s16_u16Xs16Y_Cnt (const uint16*, const sint16*, 
						uint16, uint16);
extern uint16 IntplFxdX_u16_u16Xu16Y_Cnt (uint16, const uint16*, 
						uint16, uint16);
extern uint16 IntplFxdX_u16_s16Xu16Y_Cnt (sint16, const uint16*, 
						uint16, sint16);
extern sint16 IntplFxdX_s16_s16Xs16Y_Cnt (sint16, const sint16*, 
						uint16, sint16);
extern sint16 IntplFxdX_s16_u16Xs16Y_Cnt (uint16, const sint16*, 
						uint16, uint16);

#endif


/******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author 			Change Description              SCR #
 				 					 (MDD Rev & Date) 		
-------   -------  --------  -----------------------------------  ----------
12/16/10   1.0      LWW       Temporary file for interpolation and new 
                              bilinear interpolation
07/14/11   2.0      LWW       Added BilinearXMYM_s16_u16XMs16YM_Cnt
09/29/11   3.0      LWW       Added BilinearXMYM_s16_s16XMs16YM_Cnt
11/23/11   4.0      LWW       Added BilinearXYM_s16_u16Xs16YM_Cnt
09/28/12   5.0      OT        Added BilinearXMYM_u16_s16XMu16YM_Cnt,
                              BilinearXYM_s16_s16Xs16YM_Cnt, and
							  BilinearXYM_u16_s16Xu16YM_Cnt
******************************************************************************/
