/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2009 by Vector Informatik GmbH.                                                  All rights reserved.
 * 
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Gpt_Irq.c
 *      Project:  DrvGpt_Tms570Tirti01Asr
 *       Module:  DrvGpt
 *    Generator:  -
 *
 *  Description:  This file contains the module's interrupt implementation.
 *********************************************************************************************************************/


#define GPT_IRQ_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Std_Types.h"
#include "Gpt.h"
#include "Gpt_Irq.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

#if (   (GPT_IRQ_MAJOR_VERSION != (1)) \
     || (GPT_IRQ_MINOR_VERSION != (0)))
  #error "Version numbers of Gpt_Irq.c and Gpt_Irq.h are inconsistent!"
#endif

#define GPT_START_SEC_CODE_ISR
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */


/**********************************************************************************************************************
    Function name:  Gpt_IsrIntX
**********************************************************************************************************************/

#if (GPT_CFG_ISR_TYPE == GPT_ISR_CAT1)
    interrupt void Gpt_IsrInt0( void )
#elif (GPT_CFG_ISR_TYPE == GPT_ISR_CAT2)
    ISR( Gpt_IsrInt0 )
#elif (GPT_CFG_ISR_TYPE == GPT_ISR_VOID)
    void Gpt_IsrInt0 ( void )
#endif
{
    /* ------------------------------------------------------------ */
    /* add pre-ISR code here:                                       */


    /* ------------------------------------------------------------ */

    /* implementation of ISR Frame, DO NOT MODIFY!! */
    Gpt_GlobalReEnable();
    Gpt_IsrFunction_ap[Gpt_IsrIndex_u32[0]]( 0 );

    /* ------------------------------------------------------------ */
    /* add post-ISR code here:                                      */


    /* ------------------------------------------------------------ */
    return;
}

#if (GPT_CFG_ISR_TYPE == GPT_ISR_CAT1)
    interrupt void Gpt_IsrInt1( void )
#elif (GPT_CFG_ISR_TYPE == GPT_ISR_CAT2)
    ISR( Gpt_IsrInt1 )
#elif (GPT_CFG_ISR_TYPE == GPT_ISR_VOID)
    void Gpt_IsrInt1 ( void )
#endif
{
    /* ------------------------------------------------------------ */
    /* add pre-ISR code here:                                       */


    /* ------------------------------------------------------------ */

    /* implementation of ISR Frame, DO NOT MODIFY!! */
    Gpt_GlobalReEnable();
    Gpt_IsrFunction_ap[Gpt_IsrIndex_u32[1]]( 1 );

    /* ------------------------------------------------------------ */
    /* add post-ISR code here:                                      */


    /* ------------------------------------------------------------ */
    return;
}

#if (GPT_CFG_ISR_TYPE == GPT_ISR_CAT1)
    interrupt void Gpt_IsrInt2( void )
#elif (GPT_CFG_ISR_TYPE == GPT_ISR_CAT2)
    ISR( Gpt_IsrInt2 )
#elif (GPT_CFG_ISR_TYPE == GPT_ISR_VOID)
    void Gpt_IsrInt2 ( void )
#endif
{
    /* ------------------------------------------------------------ */
    /* add pre-ISR code here:                                       */


    /* ------------------------------------------------------------ */

    /* implementation of ISR Frame, DO NOT MODIFY!! */
    Gpt_GlobalReEnable();
    Gpt_IsrFunction_ap[Gpt_IsrIndex_u32[2]]( 2 );

    /* ------------------------------------------------------------ */
    /* add post-ISR code here:                                      */


    /* ------------------------------------------------------------ */
    return;
}

#if (GPT_CFG_ISR_TYPE == GPT_ISR_CAT1)
    interrupt void Gpt_IsrInt3( void )
#elif (GPT_CFG_ISR_TYPE == GPT_ISR_CAT2)
    ISR( Gpt_IsrInt3 )
#elif (GPT_CFG_ISR_TYPE == GPT_ISR_VOID)
    void Gpt_IsrInt3 ( void )
#endif
{
    /* ------------------------------------------------------------ */
    /* add pre-ISR code here:                                       */


    /* ------------------------------------------------------------ */

    /* implementation of ISR Frame, DO NOT MODIFY!! */
    Gpt_GlobalReEnable();
    Gpt_IsrFunction_ap[Gpt_IsrIndex_u32[3]]( 3 );

    /* ------------------------------------------------------------ */
    /* add post-ISR code here:                                      */


    /* ------------------------------------------------------------ */
    return;
}


#define GPT_STOP_SEC_CODE_ISR
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */

/**********************************************************************************************************************
 *  END OF FILE: Gpt_Irq.c
 *********************************************************************************************************************/
