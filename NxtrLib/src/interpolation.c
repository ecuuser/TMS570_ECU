/*****************************************************************************
* Copyright 2002 Delphi Technologies, Inc., All Rights Reserved.
* Delphi Confidential
*
* Module File Name  : interpolation.c
* Module Description: This file contains the interpolation library
*                      functions.
* Product           : Gen II Plus EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Thu Dec 16 11:37:41 2010
* %version:          11 %
* %derived_by:       cz7lt6 %
* %date_modified:    Thu Mar 21 09:39:20 2013 %
*---------------------------------------------------------------------------*/
#ifndef INTERPOLATION_C
#define INTERPOLATION_C

#include "fpmtype.h"
#include "fixmath.h"
#include <float.h>

sint16 BilinearXYM_s16_u16Xs16YM_Cnt(uint16 BS, uint16 input, const uint16* BSTbl, uint16 BSsize, const uint16* XTbl, const sint16* YMTbl, uint16 Xsize)
{
    uint16 BSindex;
    uint16 Xindex;
    uint16 ArrayIndex1;
    uint16 ArrayIndex2;
    uint16 ArrayIndex3;
    uint16 ArrayIndex4;
    sint32 BSInputDiff;
    sint32 XInputDiff;
    float32 Numerator_f32;
    float32 Denominator_f32;
    float32 Output_f32;
    sint16 Output_s16;

    /* Would binary search alg be better? */
    if (BS <= BSTbl[0])
    {
        BSindex = 0U;
        BS = BSTbl[0];
    }
    else if (BS >= BSTbl[BSsize-1U])
    {
        BSindex = BSsize-2U;
        BS = BSTbl[BSsize-1U];
        while ((BSTbl[BSindex] == BSTbl[BSindex+1U]) && (BSindex > 0U))
        {
            BSindex--;
        }
    }
    else
    {
        BSindex = 0U;
        while ( BSTbl[BSindex+1U] < BS )
        {
            BSindex++;
        }
    }

    if (input <= XTbl[0])
    {
        Xindex = 0U;
        input = XTbl[0];
    }
    else if (input >= XTbl[Xsize-1U])
    {
        Xindex = Xsize-2U;
        input = XTbl[Xsize-1U];
    }
    else
    {
        Xindex = 0U;
        while ( XTbl[Xindex+1U] < input )
        {
            Xindex++;
        }
    }

    ArrayIndex1 = (BSindex*Xsize)+Xindex;
    ArrayIndex2 = (BSindex*Xsize)+Xindex+1U;
    ArrayIndex3 = ((BSindex+1U)*Xsize)+Xindex;
    ArrayIndex4 = ((BSindex+1U)*Xsize)+Xindex+1U;

    BSInputDiff = (sint32)BS - (sint32)BSTbl[BSindex];
    XInputDiff = (sint32)input - (sint32)XTbl[Xindex];

    Numerator_f32 = ((float32)((sint32)YMTbl[ArrayIndex2] - (sint32)YMTbl[ArrayIndex1]) *
                    ((float32)((sint32)BSTbl[BSindex+1U] - (sint32)BSTbl[BSindex]) * 
                    (float32)XInputDiff)) +
                    ((float32)((sint32)YMTbl[ArrayIndex3] - (sint32)YMTbl[ArrayIndex1]) *
                    ((float32)BSInputDiff * (float32)((sint32)XTbl[Xindex+1U] - (sint32)XTbl[Xindex]))) +
                    (((float32)XInputDiff * (float32)BSInputDiff) *
                    (float32)(((sint32)YMTbl[ArrayIndex4])-((sint32)YMTbl[ArrayIndex3])-((sint32)YMTbl[ArrayIndex2] - (sint32)YMTbl[ArrayIndex1])));

    Denominator_f32 = (float32)((sint32)BSTbl[BSindex+1U] - (sint32)BSTbl[BSindex]) * ((sint32)XTbl[Xindex+1U] - (sint32)XTbl[Xindex]);

    if(Denominator_f32 <= FLT_EPSILON)
    {
        Output_f32 = (float32)YMTbl[ArrayIndex1];
    }
    else
    {
        Output_f32 = (float32)YMTbl[ArrayIndex1] + (Numerator_f32 / Denominator_f32);
    }

    Output_f32 = (Output_f32 >= 0.0F)?(Output_f32+0.5F):(Output_f32-0.5F);
    Output_s16 = (sint16)Output_f32;

    return (Output_s16);
}

uint16 BilinearXYM_u16_u16Xu16YM_Cnt(uint16 BS, uint16 input, const uint16* BSTbl, uint16 BSsize, const uint16* XTbl, const uint16* YMTbl, uint16 Xsize)
{
    uint16 BSindex;
    uint16 Xindex;
    uint16 ArrayIndex1;
    uint16 ArrayIndex2;
    uint16 ArrayIndex3;
    uint16 ArrayIndex4;
    sint32 BSInputDiff;
    sint32 XInputDiff;
    float32 Numerator_f32;
    float32 Denominator_f32;
    uint16 Output_u16;

    /* Would binary search alg be better? */
    if (BS <= BSTbl[0])
    {
        BSindex = 0U;
        BS = BSTbl[0];
    }
    else if (BS >= BSTbl[BSsize-1U])
    {
        BSindex = BSsize-2U;
        BS = BSTbl[BSsize-1U];
        while ((BSTbl[BSindex] == BSTbl[BSindex+1U]) && (BSindex > 0U))
        {
            BSindex--;
        }
    }
    else
    {
        BSindex = 0U;
        while ( BSTbl[BSindex+1U] < BS )
        {
            BSindex++;
        }
    }

    if (input <= XTbl[0])
    {
        Xindex = 0U;
        input = XTbl[0];
    }
    else if (input >= XTbl[Xsize-1U])
    {
        Xindex = Xsize-2U;
        input = XTbl[Xsize-1U];
    }
    else
    {
        Xindex = 0U;
        while ( XTbl[Xindex+1U] < input )
        {
            Xindex++;
        }
    }

    ArrayIndex1 = (BSindex*Xsize)+Xindex;
    ArrayIndex2 = (BSindex*Xsize)+Xindex+1U;
    ArrayIndex3 = ((BSindex+1U)*Xsize)+Xindex;
    ArrayIndex4 = ((BSindex+1U)*Xsize)+Xindex+1U;

    BSInputDiff = (sint32)BS - (sint32)BSTbl[BSindex];
    XInputDiff = (sint32)input - (sint32)XTbl[Xindex];

    Numerator_f32 = ((float32)((sint32)YMTbl[ArrayIndex2] - (sint32)YMTbl[ArrayIndex1]) *
                    ((float32)((sint32)BSTbl[BSindex+1U] - (sint32)BSTbl[BSindex]) * (float32)XInputDiff)) +
                    ((float32)((sint32)YMTbl[ArrayIndex3] - (sint32)YMTbl[ArrayIndex1]) *
                    ((float32)BSInputDiff * (float32)((sint32)XTbl[Xindex+1U] - (sint32)XTbl[Xindex]))) +
                    (((float32)XInputDiff * (float32)BSInputDiff) *
                    (float32)(((sint32)YMTbl[ArrayIndex4])-((sint32)YMTbl[ArrayIndex3])-((sint32)YMTbl[ArrayIndex2] - (sint32)YMTbl[ArrayIndex1])));

    Denominator_f32 = (float32)((sint32)BSTbl[BSindex+1U] - (sint32)BSTbl[BSindex]) * ((sint32)XTbl[Xindex+1U] - (sint32)XTbl[Xindex]);

    if(Denominator_f32 <= FLT_EPSILON)
    {
        Output_u16 = (uint16)((float32)YMTbl[ArrayIndex1] + 0.5f);
    }
    else
    {
        Output_u16 = (uint16)((float32)YMTbl[ArrayIndex1] + (Numerator_f32 / Denominator_f32) + 0.5f);
    }

    return (Output_u16);
}

sint16 BilinearXYM_s16_s16Xs16YM_Cnt(uint16 BS, sint16 input, const uint16* BSTbl, uint16 BSsize, const sint16* XTbl, const sint16* YMTbl, uint16 Xsize)
{
    uint16 BSindex;
    uint16 Xindex;
    uint16 ArrayIndex1;
    uint16 ArrayIndex2;
    uint16 ArrayIndex3;
    uint16 ArrayIndex4;
    sint32 BSInputDiff;
    sint32 XInputDiff;
    float32 Numerator_f32;
    float32 Denominator_f32;
    float32 Output_f32;
    sint16 Output_s16;

    /* Would binary search alg be better? */
    if (BS <= BSTbl[0])
    {
        BSindex = 0U;
        BS = BSTbl[0];
    }
    else if (BS >= BSTbl[BSsize-1U])
    {
        BSindex = BSsize-2U;
        BS = BSTbl[BSsize-1U];
        while ((BSTbl[BSindex] == BSTbl[BSindex+1U]) && (BSindex > 0U))
        {
            BSindex--;
        }
    }
    else
    {
        BSindex = 0U;
        while ( BSTbl[BSindex+1U] < BS )
        {
            BSindex++;
        }
    }

    if (input <= XTbl[0])
    {
        Xindex = 0U;
        input = XTbl[0];
    }
    else if (input >= XTbl[Xsize-1U])
    {
        Xindex = Xsize-2U;
        input = XTbl[Xsize-1U];
    }
    else
    {
        Xindex = 0U;
        while ( XTbl[Xindex+1U] < input )
        {
            Xindex++;
        }
    }

    ArrayIndex1 = (BSindex*Xsize)+Xindex;
    ArrayIndex2 = (BSindex*Xsize)+Xindex+1U;
    ArrayIndex3 = ((BSindex+1U)*Xsize)+Xindex;
    ArrayIndex4 = ((BSindex+1U)*Xsize)+Xindex+1U;

    BSInputDiff = (sint32)BS - (sint32)BSTbl[BSindex];
    XInputDiff = (sint32)input - (sint32)XTbl[Xindex];

    Numerator_f32 = ((float32)((sint32)YMTbl[ArrayIndex2] - (sint32)YMTbl[ArrayIndex1]) *
                    ((float32)((sint32)BSTbl[BSindex+1U] - (sint32)BSTbl[BSindex]) * (float32)XInputDiff)) +
                    ((float32)((sint32)YMTbl[ArrayIndex3] - (sint32)YMTbl[ArrayIndex1]) *
                    ((float32)BSInputDiff * (float32)((sint32)XTbl[Xindex+1U] - (sint32)XTbl[Xindex]))) +
                    (((float32)XInputDiff * (float32)BSInputDiff) *
                    (float32)(((sint32)YMTbl[ArrayIndex4])-((sint32)YMTbl[ArrayIndex3])-((sint32)YMTbl[ArrayIndex2] - (sint32)YMTbl[ArrayIndex1])));

    Denominator_f32 = (float32)((sint32)BSTbl[BSindex+1U] - (sint32)BSTbl[BSindex]) * ((sint32)XTbl[Xindex+1U] - (sint32)XTbl[Xindex]);

    if(Denominator_f32 <= FLT_EPSILON)
    {
        Output_f32 = (float32)YMTbl[ArrayIndex1];
    }
    else
    {
        Output_f32 = (float32)YMTbl[ArrayIndex1] + (Numerator_f32 / Denominator_f32);
    }

    Output_f32 = (Output_f32 >= 0.0F)?(Output_f32+0.5F):(Output_f32-0.5F);
    Output_s16 = (sint16)Output_f32;

    return (Output_s16);
}

uint16 BilinearXYM_u16_s16Xu16YM_Cnt(uint16 BS, sint16 input, const uint16* BSTbl, uint16 BSsize, const sint16* XTbl, const uint16* YMTbl, uint16 Xsize)
{
    uint16 BSindex;
    uint16 Xindex;
    uint16 ArrayIndex1;
    uint16 ArrayIndex2;
    uint16 ArrayIndex3;
    uint16 ArrayIndex4;
    sint32 BSInputDiff;
    sint32 XInputDiff;
    float32 Numerator_f32;
    float32 Denominator_f32;
    uint16 Output_u16;

    /* Would binary search alg be better? */
    if (BS <= BSTbl[0])
    {
        BSindex = 0U;
        BS = BSTbl[0];
    }
    else if (BS >= BSTbl[BSsize-1U])
    {
        BSindex = BSsize-2U;
        BS = BSTbl[BSsize-1U];
        while ((BSTbl[BSindex] == BSTbl[BSindex+1U]) && (BSindex > 0U))
        {
            BSindex--;
        }
    }
    else
    {
        BSindex = 0U;
        while ( BSTbl[BSindex+1U] < BS )
        {
            BSindex++;
        }
    }

    if (input <= XTbl[0])
    {
        Xindex = 0U;
        input = XTbl[0];
    }
    else if (input >= XTbl[Xsize-1U])
    {
        Xindex = Xsize-2U;
        input = XTbl[Xsize-1U];
    }
    else
    {
        Xindex = 0U;
        while ( XTbl[Xindex+1U] < input )
        {
            Xindex++;
        }
    }

    ArrayIndex1 = (BSindex*Xsize)+Xindex;
    ArrayIndex2 = (BSindex*Xsize)+Xindex+1U;
    ArrayIndex3 = ((BSindex+1U)*Xsize)+Xindex;
    ArrayIndex4 = ((BSindex+1U)*Xsize)+Xindex+1U;

    BSInputDiff = (sint32)BS - (sint32)BSTbl[BSindex];
    XInputDiff = (sint32)input - (sint32)XTbl[Xindex];

    Numerator_f32 = ((float32)((sint32)YMTbl[ArrayIndex2] - (sint32)YMTbl[ArrayIndex1]) *
                    ((float32)((sint32)BSTbl[BSindex+1U] - (sint32)BSTbl[BSindex]) * (float32)XInputDiff)) +
                    ((float32)((sint32)YMTbl[ArrayIndex3] - (sint32)YMTbl[ArrayIndex1]) *
                    ((float32)BSInputDiff * (float32)((sint32)XTbl[Xindex+1U] - (sint32)XTbl[Xindex]))) +
                    (((float32)XInputDiff * (float32)BSInputDiff) *
                    (float32)(((sint32)YMTbl[ArrayIndex4])-((sint32)YMTbl[ArrayIndex3])-((sint32)YMTbl[ArrayIndex2] - (sint32)YMTbl[ArrayIndex1])));

    Denominator_f32 = (float32)((sint32)BSTbl[BSindex+1U] - (sint32)BSTbl[BSindex]) * ((sint32)XTbl[Xindex+1U] - (sint32)XTbl[Xindex]);

    if(Denominator_f32 <= FLT_EPSILON)
    {
        Output_u16 = (uint16)((float32)YMTbl[ArrayIndex1] + 0.5f);
    }
    else
    {
        Output_u16 = (uint16)((float32)YMTbl[ArrayIndex1] + (Numerator_f32 / Denominator_f32) + 0.5f);
    }

    return (Output_u16);
}

uint16 BilinearXMYM_u16_u16XMu16YM_Cnt(uint16 BS, uint16 input, const uint16* BSTbl, uint16 BSsize, const uint16* XMTbl, const uint16* YMTbl, uint16 Xsize)
{
    uint16 BSindex;
    uint16 X1index;
    uint16 X2index;
    uint16 ArrayIndex1;
    uint16 ArrayIndex2;
    uint16 ArrayIndex3;
    uint16 ArrayIndex4;
    sint32 BSInputDiff;
    sint32 XInputDiff1;
    sint32 XInputDiff2;
    sint32 Mult1_s32;
    sint32 Mult2_s32;
    float32 Numerator_f32;
    float32 Denominator_f32;
    uint16 Output_u16;
    sint32 Den1_s32;
    sint32 Den2_s32;
    sint32 Den3_s32;
    uint16 input2 = input;

    /* Would binary search alg be better? */
    if (BS <= BSTbl[0])
    {
        BSindex = 0U;
        BS = BSTbl[0];
    }
    else if (BS >= BSTbl[BSsize-1U])
    {
        BSindex = BSsize-2U;
        BS = BSTbl[BSsize-1U];
        while ((BSTbl[BSindex] == BSTbl[BSindex+1U]) && (BSindex > 0U))
        {
            BSindex--;
        }
    }
    else
    {
        BSindex = 0U;
        while ( BSTbl[BSindex+1U] < BS )
        {
            BSindex++;
        }
    }

    if (input <= XMTbl[BSindex*Xsize])
    {
        X1index = 0U;
        input = XMTbl[BSindex*Xsize];
    }
    else if (input >= XMTbl[((BSindex*Xsize) + Xsize) - 1U])
    {
        X1index = Xsize-2U;
        input = XMTbl[((BSindex*Xsize)+Xsize)-1U];
        while ((XMTbl[(BSindex*Xsize)+X1index] == XMTbl[(BSindex*Xsize)+X1index+1U]) && (X1index > 0U))
        {
            X1index--;
        }
    }
    else
    {
        X1index = 0U;
        while ( XMTbl[(BSindex*Xsize)+X1index+1U] < input )
        {
            X1index++;
        }
    }

    if (input2 <= XMTbl[(BSindex+1U)*Xsize])
    {
        X2index = 0U;
        input2 = XMTbl[(BSindex+1U)*Xsize];
    }
    else if (input2 >= XMTbl[(((BSindex+1U)*Xsize)+Xsize)-1U])
    {
        X2index = Xsize-2U;
        input2 = XMTbl[(((BSindex+1U)*Xsize)+Xsize)-1U];
        while ((XMTbl[((BSindex+1U)*Xsize)+X2index] == XMTbl[((BSindex+1U)*Xsize)+X2index+1U]) && (X2index > 0U))
        {
            X2index--;
        }
    }
    else
    {
        X2index = 0U;
        while ( XMTbl[((BSindex+1U)*Xsize)+X2index+1U] < input2 )
        {
            X2index++;
        }
    }

    ArrayIndex1 = (BSindex*Xsize)+X1index;
    ArrayIndex2 = (BSindex*Xsize)+X1index+1U;
    ArrayIndex3 = ((BSindex+1U)*Xsize)+X2index;
    ArrayIndex4 = ((BSindex+1U)*Xsize)+X2index+1U;

    XInputDiff1 = (sint32)input - (sint32)XMTbl[ArrayIndex1];
    XInputDiff2 = (sint32)input2 - (sint32)XMTbl[ArrayIndex3];
    BSInputDiff = (sint32)BS - (sint32)BSTbl[BSindex];

    Mult1_s32 = XInputDiff1 * ((sint32)XMTbl[ArrayIndex4] - (sint32)XMTbl[ArrayIndex3]);
    Mult2_s32 = BSInputDiff * ((sint32)XMTbl[ArrayIndex2] - (sint32)XMTbl[ArrayIndex1]);
    Den1_s32 = ((sint32)XMTbl[ArrayIndex4] - (sint32)XMTbl[ArrayIndex3]);
    Den2_s32 = ((sint32)XMTbl[ArrayIndex2] - (sint32)XMTbl[ArrayIndex1]);
    Den3_s32 = ((sint32)BSTbl[BSindex+1U] - (sint32)BSTbl[BSindex]);

    Numerator_f32 = ((float32)Mult1_s32 *
                    (float32)((sint32)BSTbl[BSindex+1U] -(sint32)BS) *
                    (float32)(YMTbl[ArrayIndex2] - YMTbl[ArrayIndex1])) +
                    ((float32)Mult2_s32 *
                    (float32)((sint32)XMTbl[ArrayIndex4] - (sint32)XMTbl[ArrayIndex3]) *
                    (float32)((sint32)YMTbl[ArrayIndex3] - (sint32)YMTbl[ArrayIndex1])) +
                    ((float32)Mult2_s32 *
                    (float32)XInputDiff2 *
                    (float32)((sint32)YMTbl[ArrayIndex4] - (sint32)YMTbl[ArrayIndex3]));

    Denominator_f32 = (float32)(Den1_s32*Den2_s32)*(float32)Den3_s32;

    if(Denominator_f32 <= FLT_EPSILON)
    {
        Output_u16 = (uint16)((float32)YMTbl[ArrayIndex1] + 0.5f);
    }
    else
    {
        Output_u16 = (uint16)((float32)YMTbl[ArrayIndex1] + (Numerator_f32 / Denominator_f32) + 0.5f);
    }



    return (Output_u16);

}

sint16 BilinearXMYM_s16_u16XMs16YM_Cnt(uint16 BS, uint16 input, const uint16* BSTbl, uint16 BSsize, const uint16* XMTbl, const sint16* YMTbl, uint16 Xsize)
{
    uint16 BSindex;
    uint16 X1index;
    uint16 X2index;
    uint16 ArrayIndex1;
    uint16 ArrayIndex2;
    uint16 ArrayIndex3;
    uint16 ArrayIndex4;
    sint32 BSInputDiff;
    sint32 XInputDiff1;
    sint32 XInputDiff2;
    sint32 Mult1_s32;
    sint32 Mult2_s32;
    float32 Numerator_f32;
    float32 Denominator_f32;
    sint16 Output_s16;
    sint32 Den1_s32;
    sint32 Den2_s32;
    sint32 Den3_s32;
    uint16 input2 = input;
    float32 Output_f32;

    /* Would binary search alg be better? */
    if (BS <= BSTbl[0])
    {
        BSindex = 0U;
        BS = BSTbl[0];
    }
    else if (BS >= BSTbl[BSsize-1U])
    {
        BSindex = BSsize-2U;
        BS = BSTbl[BSsize-1U];
        while ((BSTbl[BSindex] == BSTbl[BSindex+1U]) && (BSindex > 0U))
        {
            BSindex--;
        }
    }
    else
    {
        BSindex = 0U;
        while ( BSTbl[BSindex+1U] < BS )
        {
            BSindex++;
        }
    }

    if (input <= XMTbl[BSindex*Xsize])
    {
        X1index = 0U;
        input = XMTbl[BSindex*Xsize];
    }
    else if (input >= XMTbl[((BSindex*Xsize) + Xsize) - 1U])
    {
        X1index = Xsize-2U;
        input = XMTbl[((BSindex*Xsize)+Xsize)-1U];
        while ((XMTbl[(BSindex*Xsize)+X1index] == XMTbl[(BSindex*Xsize)+X1index+1U]) && (X1index > 0U))
        {
            X1index--;
        }
    }
    else
    {
        X1index = 0U;
        while ( XMTbl[(BSindex*Xsize)+X1index+1U] < input )
        {
            X1index++;
        }
    }

    if (input2 <= XMTbl[(BSindex+1U)*Xsize])
    {
        X2index = 0U;
        input2 = XMTbl[(BSindex+1U)*Xsize];
    }
    else if (input2 >= XMTbl[(((BSindex+1U)*Xsize)+Xsize)-1U])
    {
        X2index = Xsize-2U;
        input2 = XMTbl[(((BSindex+1U)*Xsize)+Xsize)-1U];
        while ((XMTbl[((BSindex+1U)*Xsize)+X2index] == XMTbl[((BSindex+1U)*Xsize)+X2index+1U]) && (X2index > 0U))
        {
            X2index--;
        }
    }
    else
    {
        X2index = 0U;
        while ( XMTbl[((BSindex+1U)*Xsize)+X2index+1U] < input2 )
        {
            X2index++;
        }
    }

    ArrayIndex1 = (BSindex*Xsize)+X1index;
    ArrayIndex2 = (BSindex*Xsize)+X1index+1U;
    ArrayIndex3 = ((BSindex+1U)*Xsize)+X2index;
    ArrayIndex4 = ((BSindex+1U)*Xsize)+X2index+1U;

    XInputDiff1 = (sint32)input - (sint32)XMTbl[ArrayIndex1];
    XInputDiff2 = (sint32)input2 - (sint32)XMTbl[ArrayIndex3];
    BSInputDiff = (sint32)BS - (sint32)BSTbl[BSindex];

    Mult1_s32 = XInputDiff1 * ((sint32)XMTbl[ArrayIndex4] - (sint32)XMTbl[ArrayIndex3]);
    Mult2_s32 = BSInputDiff * ((sint32)XMTbl[ArrayIndex2] - (sint32)XMTbl[ArrayIndex1]);
    Den1_s32 = ((sint32)XMTbl[ArrayIndex4] - (sint32)XMTbl[ArrayIndex3]);
    Den2_s32 = ((sint32)XMTbl[ArrayIndex2] - (sint32)XMTbl[ArrayIndex1]);
    Den3_s32 = ((sint32)BSTbl[BSindex+1U] - (sint32)BSTbl[BSindex]);

    Numerator_f32 = ((float32)Mult1_s32 *
                    (float32)((sint32)BSTbl[BSindex+1U] -(sint32)BS) *
                    (float32)(YMTbl[ArrayIndex2] - YMTbl[ArrayIndex1])) +
                    ((float32)Mult2_s32 *
                    (float32)((sint32)XMTbl[ArrayIndex4] - (sint32)XMTbl[ArrayIndex3]) *
                    (float32)((sint32)YMTbl[ArrayIndex3] - (sint32)YMTbl[ArrayIndex1])) +
                    ((float32)Mult2_s32 *
                    (float32)XInputDiff2 *
                    (float32)((sint32)YMTbl[ArrayIndex4] - (sint32)YMTbl[ArrayIndex3]));

    Denominator_f32 = (float32)(Den1_s32*Den2_s32)*(float32)Den3_s32;

    if(Denominator_f32 <= FLT_EPSILON)
    {
            Output_f32 = (float32)YMTbl[ArrayIndex1];
    }
    else
    {
            Output_f32 = (float32)YMTbl[ArrayIndex1] + (Numerator_f32 / Denominator_f32);
    }


    Output_f32 = (Output_f32 >= 0.0F)?(Output_f32+0.5F):(Output_f32-0.5F);
    Output_s16 = (sint16)Output_f32;

    return (Output_s16);

}

sint16 BilinearXMYM_s16_s16XMs16YM_Cnt(uint16 BS, sint16 input, const uint16* BSTbl, uint16 BSsize, const sint16* XMTbl, const sint16* YMTbl, uint16 Xsize)
{
    uint16 BSindex;
    uint16 X1index;
    uint16 X2index;
    uint16 ArrayIndex1;
    uint16 ArrayIndex2;
    uint16 ArrayIndex3;
    uint16 ArrayIndex4;
    sint32 BSInputDiff;
    sint32 XInputDiff1;
    sint32 XInputDiff2;
    sint32 Mult1_s32;
    sint32 Mult2_s32;
    float32 Numerator_f32;
    float32 Denominator_f32;
    sint16 Output_s16;
    sint32 Den1_s32;
    sint32 Den2_s32;
    sint32 Den3_s32;
    sint16 input2 = input;
    float32 Output_f32;

    /* Would binary search alg be better? */
    if (BS <= BSTbl[0])
    {
        BSindex = 0U;
        BS = BSTbl[0];
    }
    else if (BS >= BSTbl[BSsize-1U])
    {
        BSindex = BSsize-2U;
        BS = BSTbl[BSsize-1U];
        while ((BSTbl[BSindex] == BSTbl[BSindex+1U]) && (BSindex > 0U))
        {
            BSindex--;
        }
    }
    else
    {
        BSindex = 0U;
        while ( BSTbl[BSindex+1U] < BS )
        {
            BSindex++;
        }
    }

    if (input <= XMTbl[BSindex*Xsize])
    {
        X1index = 0U;
        input = XMTbl[BSindex*Xsize];
    }
    else if (input >= XMTbl[((BSindex*Xsize) + Xsize) - 1U])
    {
        X1index = Xsize-2U;
        input = XMTbl[((BSindex*Xsize)+Xsize)-1U];
        while ((XMTbl[(BSindex*Xsize)+X1index] == XMTbl[(BSindex*Xsize)+X1index+1U]) && (X1index > 0U))
        {
            X1index--;
        }
    }
    else
    {
        X1index = 0U;
        while ( XMTbl[(BSindex*Xsize)+X1index+1U] < input )
        {
            X1index++;
        }
    }

    if (input2 <= XMTbl[(BSindex+1U)*Xsize])
    {
        X2index = 0U;
        input2 = XMTbl[(BSindex+1U)*Xsize];
    }
    else if (input2 >= XMTbl[(((BSindex+1U)*Xsize)+Xsize)-1U])
    {
        X2index = Xsize-2U;
        input2 = XMTbl[(((BSindex+1U)*Xsize)+Xsize)-1U];
        while ((XMTbl[((BSindex+1U)*Xsize)+X2index] == XMTbl[((BSindex+1U)*Xsize)+X2index+1U]) && (X2index > 0U))
        {
            X2index--;
        }
    }
    else
    {
        X2index = 0U;
        while ( XMTbl[((BSindex+1U)*Xsize)+X2index+1U] < input2 )
        {
            X2index++;
        }
    }

    ArrayIndex1 = (BSindex*Xsize)+X1index;
    ArrayIndex2 = (BSindex*Xsize)+X1index+1U;
    ArrayIndex3 = ((BSindex+1U)*Xsize)+X2index;
    ArrayIndex4 = ((BSindex+1U)*Xsize)+X2index+1U;

    XInputDiff1 = (sint32)input - (sint32)XMTbl[ArrayIndex1];
    XInputDiff2 = (sint32)input2 - (sint32)XMTbl[ArrayIndex3];
    BSInputDiff = (sint32)BS - (sint32)BSTbl[BSindex];

    Mult1_s32 = XInputDiff1 * ((sint32)XMTbl[ArrayIndex4] - (sint32)XMTbl[ArrayIndex3]);
    Mult2_s32 = BSInputDiff * ((sint32)XMTbl[ArrayIndex2] - (sint32)XMTbl[ArrayIndex1]);
    Den1_s32 = ((sint32)XMTbl[ArrayIndex4] - (sint32)XMTbl[ArrayIndex3]);
    Den2_s32 = ((sint32)XMTbl[ArrayIndex2] - (sint32)XMTbl[ArrayIndex1]);
    Den3_s32 = ((sint32)BSTbl[BSindex+1U] - (sint32)BSTbl[BSindex]);

    Numerator_f32 = ((float32)Mult1_s32 *
                    (float32)((sint32)BSTbl[BSindex+1U] -(sint32)BS) *
                    (float32)(YMTbl[ArrayIndex2] - YMTbl[ArrayIndex1])) +
                    ((float32)Mult2_s32 *
                    (float32)((sint32)XMTbl[ArrayIndex4] - (sint32)XMTbl[ArrayIndex3]) *
                    (float32)((sint32)YMTbl[ArrayIndex3] - (sint32)YMTbl[ArrayIndex1])) +
                    ((float32)Mult2_s32 *
                    (float32)XInputDiff2 *
                    (float32)((sint32)YMTbl[ArrayIndex4] - (sint32)YMTbl[ArrayIndex3]));

    Denominator_f32 = (float32)(Den1_s32*Den2_s32)*(float32)Den3_s32;

    if(Denominator_f32 <= FLT_EPSILON)
    {
        Output_f32 = (float32)YMTbl[ArrayIndex1];
    }
    else
    {
        Output_f32 = (float32)YMTbl[ArrayIndex1] + (Numerator_f32 / Denominator_f32);
    }


    Output_f32 = (Output_f32 >= 0.0F)?(Output_f32+0.5F):(Output_f32-0.5F);
    Output_s16 = (sint16)Output_f32;

    return (Output_s16);

}

uint16 BilinearXMYM_u16_s16XMu16YM_Cnt(uint16 BS, sint16 input, const uint16* BSTbl, uint16 BSsize, const sint16* XMTbl, const uint16* YMTbl, uint16 Xsize)
{
    uint16 BSindex;
    uint16 X1index;
    uint16 X2index;
    uint16 ArrayIndex1;
    uint16 ArrayIndex2;
    uint16 ArrayIndex3;
    uint16 ArrayIndex4;
    sint32 BSInputDiff;
    sint32 XInputDiff1;
    sint32 XInputDiff2;
    sint32 Mult1_s32;
    sint32 Mult2_s32;
    float32 Numerator_f32;
    float32 Denominator_f32;
    uint16 Output_u16;
    sint32 Den1_s32;
    sint32 Den2_s32;
    sint32 Den3_s32;
    sint16 input2 = input;

    /* Would binary search alg be better? */
    if (BS <= BSTbl[0])
    {
        BSindex = 0U;
        BS = BSTbl[0];
    }
    else if (BS >= BSTbl[BSsize-1U])
    {
        BSindex = BSsize-2U;
        BS = BSTbl[BSsize-1U];
        while ((BSTbl[BSindex] == BSTbl[BSindex+1U]) && (BSindex > 0U))
        {
            BSindex--;
        }
    }
    else
    {
        BSindex = 0U;
        while ( BSTbl[BSindex+1U] < BS )
        {
            BSindex++;
        }
    }

    if (input <= XMTbl[BSindex*Xsize])
    {
        X1index = 0U;
        input = XMTbl[BSindex*Xsize];
    }
    else if (input >= XMTbl[((BSindex*Xsize) + Xsize) - 1U])
    {
        X1index = Xsize-2U;
        input = XMTbl[((BSindex*Xsize)+Xsize)-1U];
        while ((XMTbl[(BSindex*Xsize)+X1index] == XMTbl[(BSindex*Xsize)+X1index+1U]) && (X1index > 0U))
        {
            X1index--;
        }
    }
    else
    {
        X1index = 0U;
        while ( XMTbl[(BSindex*Xsize)+X1index+1U] < input )
        {
            X1index++;
        }
    }

    if (input2 <= XMTbl[(BSindex+1U)*Xsize])
    {
        X2index = 0U;
        input2 = XMTbl[(BSindex+1U)*Xsize];
    }
    else if (input2 >= XMTbl[(((BSindex+1U)*Xsize)+Xsize)-1U])
    {
        X2index = Xsize-2U;
        input2 = XMTbl[(((BSindex+1U)*Xsize)+Xsize)-1U];
        while ((XMTbl[((BSindex+1U)*Xsize)+X2index] == XMTbl[((BSindex+1U)*Xsize)+X2index+1U]) && (X2index > 0U))
        {
            X2index--;
        }
    }
    else
    {
        X2index = 0U;
        while ( XMTbl[((BSindex+1U)*Xsize)+X2index+1U] < input2 )
        {
            X2index++;
        }
    }

    ArrayIndex1 = (BSindex*Xsize)+X1index;
    ArrayIndex2 = (BSindex*Xsize)+X1index+1U;
    ArrayIndex3 = ((BSindex+1U)*Xsize)+X2index;
    ArrayIndex4 = ((BSindex+1U)*Xsize)+X2index+1U;

    XInputDiff1 = (sint32)input - (sint32)XMTbl[ArrayIndex1];
    XInputDiff2 = (sint32)input2 - (sint32)XMTbl[ArrayIndex3];
    BSInputDiff = (sint32)BS - (sint32)BSTbl[BSindex];

    Mult1_s32 = XInputDiff1 * ((sint32)XMTbl[ArrayIndex4] - (sint32)XMTbl[ArrayIndex3]);
    Mult2_s32 = BSInputDiff * ((sint32)XMTbl[ArrayIndex2] - (sint32)XMTbl[ArrayIndex1]);
    Den1_s32 = ((sint32)XMTbl[ArrayIndex4] - (sint32)XMTbl[ArrayIndex3]);
    Den2_s32 = ((sint32)XMTbl[ArrayIndex2] - (sint32)XMTbl[ArrayIndex1]);
    Den3_s32 = ((sint32)BSTbl[BSindex+1U] - (sint32)BSTbl[BSindex]);

    Numerator_f32 = ((float32)Mult1_s32 *
                    (float32)((sint32)BSTbl[BSindex+1U] -(sint32)BS) *
                    (float32)(YMTbl[ArrayIndex2] - YMTbl[ArrayIndex1])) +
                    ((float32)Mult2_s32 *
                    (float32)((sint32)XMTbl[ArrayIndex4] - (sint32)XMTbl[ArrayIndex3]) *
                    (float32)((sint32)YMTbl[ArrayIndex3] - (sint32)YMTbl[ArrayIndex1])) +
                    ((float32)Mult2_s32 *
                    (float32)XInputDiff2 *
                    (float32)((sint32)YMTbl[ArrayIndex4] - (sint32)YMTbl[ArrayIndex3]));

    Denominator_f32 = (float32)(Den1_s32*Den2_s32)*(float32)Den3_s32;

    if(Denominator_f32 <= FLT_EPSILON)
    {
        Output_u16 = (uint16)((float32)YMTbl[ArrayIndex1] + 0.5f);
    }
    else
    {
        Output_u16 = (uint16)((float32)YMTbl[ArrayIndex1] + (Numerator_f32 / Denominator_f32) + 0.5f);
    }



    return (Output_u16);

}

/*******************************************************************************
  * Name        :    IntplVarXY_u16_u16Xu16Y_Cnt (TableX, TableY, Size, input)
  * Description :    Unsigned 16 bit Variable X Unsigned 16 bit Variable Y
  *                  2D Table Lookup function (with interpolation).
  *                  TableX is the independent axis and the TableY is
  *                  the dependent axis. The lookup function with
  *                  interpolation is used to interpolate the values of Y
  *                  corresponding to the input value for X.
  * Inputs      :    Name of TableX, Name of TableY, Table size, X input
  * Outputs     :    Y output
  *****************************************************************************/

uint16 IntplVarXY_u16_u16Xu16Y_Cnt (const uint16 *TableX, const uint16 *TableY, uint16 Size, uint16 input)
{
    uint16 output;
    uint16 index = 0U;
    sint16 tmpout2, sOutput;
    sint32 diffY, diffX, diffXinput, tmpout1;

    /* Check for Range */
    if ( input <= TableX[0] )
    {
        return TableY[0];
    }
    else if ( input >= TableX[Size-1U] )
    {
        return TableY[Size-1U];
    }

    /* In range. Get Index */
    while ( TableX[index+1U] < input )
    {
        index++;
    }

    /* Interpolate and get the output */
    diffY = (sint32)TableY[index+1U] - (sint32)TableY[index];
    diffX = (sint32)TableX[index+1U] - (sint32)TableX[index];
    diffXinput = (sint32)input - (sint32)TableX[index];
    tmpout1 = (sint32)diffY * (sint32)diffXinput;

    /* Check if Divide by zero */
    if (diffX == 0)
    {
        tmpout2 = 0;
    }
    else
    {
        tmpout2 = (sint16)(tmpout1 / (sint32)diffX);
    }

    sOutput = tmpout2 + FPM_Fix_m(TableY[index], u16p0_T, s15p0_T);
    output = FPM_Fix_m(sOutput, s15p0_T, u16p0_T);

    return output;
}


/*******************************************************************************
  * Name        :    IntplVarXY_u16_s16Xu16Y_Cnt (TableX, TableY, Size, input)
  * Description :    Signed 16 bit Variable X Unsigned 16 bit Variable Y
  *                  2D Table Lookup function (with interpolation).
  *                  TableX is the independent axis and the TableY is
  *                  the dependent axis.The lookup function with
  *                  interpolation is used to interpolate the values of Y
  *                  corresponding to the input value for X.
  * Inputs      :    Name of TableX, Name of TableY, Table size, X input
  * Outputs     :    Y output
  *****************************************************************************/

uint16 IntplVarXY_u16_s16Xu16Y_Cnt (const sint16 *TableX, const uint16 *TableY, uint16 Size, sint16 input)
{
    uint16 output;
    uint16 index = 0U;
    sint16 tmpout2, sOutput;
    sint32 diffY, diffX, diffXinput, tmpout1;

    /* Check for Range */
    if ( input <= TableX[0] )
    {
        return TableY[0];
    }
    else if ( input >= TableX[Size-1U] )
    {
        return TableY[Size-1U];
    }

    /* In range. Get Index */
    while ( TableX[index+1U] < input )
    {
        index++;
    }

    /* Interpolate and get the output */
    diffY = (sint32)TableY[index+1U] - (sint32)TableY[index];
    diffX = (sint32)TableX[index+1U] - (sint32)TableX[index];
    diffXinput = (sint32)input - (sint32)TableX[index];
    tmpout1 = (sint32)diffY * (sint32)diffXinput;

    /* Check if Divide by zero */
    if (diffX == 0)
    {
        tmpout2 = 0;
    }
    else
    {
        /* Here, the lower 16 bits are assigned to tmpout2 */
        tmpout2 = (sint16)(tmpout1 / (sint32)diffX);
    }

    sOutput = tmpout2 + FPM_Fix_m(TableY[index], u16p0_T, s15p0_T);
    output = FPM_Fix_m(sOutput, s15p0_T, u16p0_T);

    return output;
}


/*******************************************************************************
  * Name        :    IntplVarXY_s16_s16Xs16Y_Cnt (TableX, TableY, Size, input)
  * Description :    Signed 16 bit Variable X Signed 16 bit Variable Y
  *                  2D Table Lookup function (with interpolation).
  *                  TableX is the independent axis and the TableY is
  *                  the dependent axis.The lookup function with
  *                  interpolation is used to interpolate the values of Y
  *                  corresponding to the input value for X.
  * Inputs      :    Name of TableX, Name of TableY, Table size, X input
  * Outputs     :    Y output
  *****************************************************************************/
sint16 IntplVarXY_s16_s16Xs16Y_Cnt (const sint16 *TableX, const sint16 *TableY, uint16 Size, sint16 input)
{
    sint16 output;
    uint16 index = 0U;
    sint16 tmpout2;
    sint32 diffY, diffX, diffXinput, tmpout1;

    /* Check for Range */
    if ( input <= TableX[0] )
    {
        return TableY[0];
    }
    else if ( input >= TableX[Size-1U] )
    {
        return TableY[Size-1U];
    }

    /* In range. Get Index */
    while ( TableX[index+1U] < input )
    {
        index++;
    }

    /* Interpolate and get the output */
    diffY = (sint32)TableY[index+1U] - (sint32)TableY[index];
    diffX = (sint32)TableX[index+1U] - (sint32)TableX[index];
    diffXinput = (sint32)input - (sint32)TableX[index];
    tmpout1 = (sint32)diffY * (sint32)diffXinput;

    /* Check if Divide by zero */
    if (diffX == 0)
    {
        tmpout2 = 0;
    }
    else
    {
        /* Here, the lower 16 bits are assigned to tmpout2 */
        tmpout2 = (sint16)(tmpout1 / (sint32)diffX);
    }

    output = tmpout2 + TableY[index];

    return output;
}

/*******************************************************************************
  * Name        :    IntplVarXY_s16_u16Xs16Y_Cnt (TableX, TableY, Size, input)
  * Description :    Unsigned 16 bit Variable X Signed 16 bit Variable Y
  *                  2D Table Lookup function (with interpolation).
  *                  TableX is the independent axis and the TableY is
  *                  the dependent axis.The lookup function with
  *                  interpolation is used to interpolate the values of Y
  *                  corresponding to the input value for X.
  * Inputs      :    Name of TableX, Name of TableY, Table size, X input
  * Outputs     :    Y output
  *****************************************************************************/
sint16 IntplVarXY_s16_u16Xs16Y_Cnt (const uint16 *TableX, const sint16 *TableY, uint16 Size, uint16 input)
{
    sint16  output;
    uint16  index = 0U;
    sint16  tmpout2;
    sint32  diffY, diffX, diffXinput, tmpout1;

    /* Check for Range */
    if ( input <= TableX[0] )
    {
        return TableY[0];
    }
    else if ( input >= TableX[Size-1U] )
    {
        return TableY[Size-1U];
    }

    /* In range. Get Index */
    while ( TableX[index+1U] < input )
    {
        index++;
    }

    /* Interpolate and get the output */
    diffY = (sint32)TableY[index+1U] - (sint32)TableY[index];
    diffX = (sint32)TableX[index+1U] - (sint32)TableX[index];
    diffXinput = (sint32)input - (sint32)TableX[index];
    tmpout1 = (sint32)diffY * (sint32)diffXinput;

    /* Check if Divide by zero */
    if (diffX == 0)
    {
        tmpout2 = 0;
    }
    else
    {
        /* Here, the lower 16 bits are assigned to tmpout2 */
        tmpout2 = (sint16)(tmpout1 / (sint32)diffX);
    }

    output = tmpout2 + TableY[index];

    return output;
}

/*******************************************************************************
  * Name        :    IntplFxdX_u16_u16Xu16Y_Cnt (DeltaX, TableY, Size, input)
  * Description :    Unsigned 16 bit Fixed X Unsigned 16 bit Variable Y
  *                  2D Table Lookup function (with interpolation).
  *                  DeltaX is the fixed interval in the independent axis
  *                  and the TableY is the dependent axis.The lookup function
  *                  with interpolation is used to interpolate the values
  *                  of Y corresponding to the input value for X.
  * Inputs      :    DeltaX, Name of TableY, Table size, X input
  * Outputs     :    Y output
  *****************************************************************************/
uint16 IntplFxdX_u16_u16Xu16Y_Cnt (uint16 DeltaX, const uint16 *TableY, uint16 Size, uint16 input)
{
    uint16  output;
    uint16  index = 0U;
    sint16  tmpout2, sOutput;
    sint32  diffY, diffXinput, tmpout1;

    if (DeltaX == 0U)
    {
        /* Cannot do interpolation. Return Y0 */
        return TableY[0];
    }

    /* Check for Range. Low limit of input is 0 */
    if ( input <= 0U )
    {
        return TableY[0];
    }
    else if ( input >= (DeltaX * (Size-1U)) )
    {
        return TableY[Size-1U];
    }

    /* In range. Get Index. Assume only positive values for input
    and the output table has the first element as 0 */
    index = input / DeltaX;

    /* Interpolate and get the output */
    diffY = (sint32)TableY[index + 1U] - (sint32)TableY[index];
    diffXinput = (sint32)input - ((sint32)DeltaX * (sint32)index);
    tmpout1 = (sint32)diffY * (sint32)diffXinput;
    tmpout2 = (sint16)(tmpout1 / (sint32)DeltaX);

    sOutput = tmpout2 + FPM_Fix_m(TableY[index], u16p0_T, s15p0_T);
    output = FPM_Fix_m(sOutput, s15p0_T, u16p0_T);

    return output;
}


/*******************************************************************************
  * Name        :    IntplFxdX_u16_s16Xu16Y_Cnt (DeltaX, TableY, Size, input)
  * Description :    Signed 16 bit Fixed X Unsigned 16 bit Variable Y
  *                  2D Table Lookup function (with interpolation).
  *                  DeltaX is the fixed interval in the independent axis
  *                  and the TableY is the dependent axis.The lookup function
  *                  with interpolation is used to interpolate the values
  *                  of Y corresponding to the input value for X.
  * Inputs      :    DeltaX, Name of TableY, Table size, X input
  * Outputs     :    Y output
  *****************************************************************************/
uint16 IntplFxdX_u16_s16Xu16Y_Cnt (sint16 DeltaX, const uint16 *TableY, uint16 Size, sint16 input)
{
    uint16  output;
    uint16  index = 0U;
    sint16  tmpout2, sOutput;
    sint32  diffY, diffXinput, tmpout1;

    if (DeltaX == 0)
    {
        /* Cannot do interpolation. Return Y0 */
        return TableY[0];
    }

    /* Check for Range. Low limit of input is 0 */
    if ( input <= 0 )
    {
        return TableY[0];
    }
    else if ( input >= (DeltaX * (Size-1U)) )
    {
        return TableY[Size-1U];
    }

    /* In range. Get Index. Assume only positive values for input
    and the output table has the first element as 0 */
    index = (uint16)(input / DeltaX);

    /* Interpolate and get the output */
    diffY = (sint32)TableY[index + 1U] - (sint32)TableY[index];
    diffXinput = (sint32)input - ((sint32)DeltaX * (sint32)index);
    tmpout1 = (sint32)diffY * (sint32)diffXinput;
    /* Here, the lower 16 bits are assigned to tmpout2 */
    tmpout2 = (sint16)(tmpout1 / (sint32)DeltaX);

    sOutput = tmpout2 + FPM_Fix_m (TableY[index], u16p0_T, s15p0_T);
    output = FPM_Fix_m(sOutput, s15p0_T, u16p0_T);

    return output;
}



/*******************************************************************************
  * Name        :    IntplFxdX_s16_s16Xs16Y_Cnt (DeltaX, TableY, Size, input)
  * Description :    Signed 16 bit Fixed X Signed 16 bit Variable Y
  *                  2D Table Lookup function (with interpolation).
  *                  DeltaX is the fixed interval in the independent axis
  *                  and the TableY is the dependent axis.The lookup function
  *                  with interpolation is used to interpolate the values
  *                  of Y corresponding to the input value for X.
  * Inputs      :    DeltaX, Name of TableY, Table size, X input
  * Outputs     :    Y output
  *****************************************************************************/
sint16 IntplFxdX_s16_s16Xs16Y_Cnt (sint16 DeltaX, const sint16 *TableY, uint16 Size, sint16 input)
{
    sint16  output;
    uint16  index = 0U;
    sint16  tmpout2;
    sint32  diffY, diffXinput, tmpout1;

    if (DeltaX == 0)
    {
        /* Cannot do interpolation. Return Y0 */
        return TableY[0];
    }

    /* Check for Range. Low limit of input is 0 */
    if ( input <= 0 )
    {
        return TableY[0];
    }
    else if ( input >= (DeltaX * (Size-1U)) )
    {
        return TableY[Size-1U];
    }

    /* In range. Get Index. Assume only positive values for input
    and the output table has the first element as 0 */
    index = (uint16)(input / DeltaX);

    /* Interpolate and get the output */
    diffY = (sint32)TableY[index + 1U] - (sint32)TableY[index];
    diffXinput = (sint32)input - ((sint32)DeltaX * (sint32)index);
    tmpout1 = (sint32)diffY * (sint32)diffXinput;
    /* Here, the lower 16 bits are assigned to tmpout2 */
    tmpout2 = (sint16)(tmpout1 / (sint32)DeltaX);

    output = tmpout2 + TableY[index];

    return output;
}



/*******************************************************************************
  * Name        :    IntplFxdX_s16_u16Xs16Y_Cnt (DeltaX, TableY, Size, input)
  * Description :    Unigned 16 bit Fixed X Signed 16 bit Variable Y
  *                  2D Table Lookup function (with interpolation).
  *                  DeltaX is the fixed interval in the independent axis
  *                  and the TableY is the dependent axis.The lookup function
  *                  with interpolation is used to interpolate the values
  *                  of Y corresponding to the input value for X.
  * Inputs      :    DeltaX, Name of TableY, Table size, X input
  * Outputs     :    Y output
  *****************************************************************************/
sint16 IntplFxdX_s16_u16Xs16Y_Cnt (uint16 DeltaX, const sint16 *TableY, uint16 Size, uint16 input)
{
    sint16  output;
    uint16  index = 0U;
    sint16  tmpout2;
    sint32  diffY, diffXinput, tmpout1;

    if (DeltaX == 0U)
    {
        /* Cannot do interpolation. Return Y0 */
        return TableY[0];
    }

    /* Check for Range. Low limit of input is 0 */
    if ( input <= 0U )
    {
        return TableY[0];
    }
    else if ( input >= (DeltaX * (Size-1U)) )
    {
        return TableY[Size-1U];
    }

    /* In range. Get Index. Assume only positive values for input
    and the output table has the first element as 0 */
    index = input / DeltaX;

    /* Interpolate and get the output */
    diffY = (sint32)TableY[index + 1U] - (sint32)TableY[index];
    diffXinput = (sint32)input - ((sint32)DeltaX * (sint32)index);
    tmpout1 = diffY * diffXinput;
    /* Here, the lower 16 bits are assigned to tmpout2 */
    tmpout2 = (sint16)(tmpout1 / (sint32)DeltaX);

    output = (sint16)(tmpout2 + (sint32)TableY[index]);

    return output;
}

#endif


/******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author             Change Description              SCR #
                                       (MDD Rev & Date)
-------   -------  --------  -----------------------------------  ----------
12/16/10   1.0      LWW       Temporary file for interpolation and new 
                              bilinear interpolation
05/18/11   2.0      LWW       Underflow anomaly fix  
07/13/11   3.0      LWW       Added BilinearXMYM_s16_u16XMs16YM_Cnt
08/09/11   4.0      LWW       Fixed typecast anomaly, fixed rounding
                              logic on BilinearXMYM_s16_u16XMs16YM_Cnt
09/29/11   5.0      LWW       Added BilinearXMYM_s16_s16XMs16YM_Cnt
11/23/11   6.0      LWW       Added BilinearXYM_s16_u16Xs16YM_Cnt
12/14/11   7.0      NRAR      Divide by Zero fixed in BilinearIntpl
04/13/12   8.0      NRAR      Anom 3161 Fix for Numerator calculation of SingleXMultipleY BilinearIntpl
09/28/12   9.0      OT        Added BilinearXMYM_u16_s16XMu16YM_Cnt,
                              BilinearXYM_s16_s16Xs16YM_Cnt, and
                              BilinearXYM_u16_s16Xu16YM_Cnt
05/06/15   10.0     KJS       Corrected anomalies 947 to 959, EA3#530, and EA3#191 and some QAC corrections
******************************************************************************/
