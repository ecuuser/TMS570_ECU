/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2009 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Gpt_Irq.h
 *    Component:  DrvGpt_Tms570Tirti01Asr
 *       Module:  DrvGpt
 *    Generator:  -
 *
 *  Description:  This file contains the module's interrupt interface.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Roland Süß                    Rsu           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2008-10-27  Rsu                   Initial release of Asr3.0 implementation
 *  01.00.01  2009-01-09  Rsu     ESCAN00032264 Removed BETA disclaimer
 *                                ESCAN00032268 Enhanced configuration of hardware resources
 *  01.00.02  2011-02-02  Lg      ESCAN00042829 Removing a bracket from a commend
 *  01.00.03  2011-08-24  Lg                    Adding time measurement tags and wakeup validation Det error report
 *  01.00.04  2012-01-16  Lg      ESCAN00054736 Adding register access feature via OS interface 
 *  01.00.05  2012-02-24  Lg                    Fixing error in macro
 *  01.00.06  2012-04-16  Lg      ESCAN00058371 Fixing Register access
 *********************************************************************************************************************/

#if !defined (GPT_IRQ_H)
#define GPT_IRQ_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Version identification */
#define GPT_IRQ_MAJOR_VERSION    (1)
#define GPT_IRQ_MINOR_VERSION    (0)
#define GPT_IRQ_PATCH_VERSION    (6)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* Typedef for the ISR Function Array */
typedef void (* Gpt_IsrRefType)(uint32);

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/* ---- Variable forward declarations ------------------------------------- */
/* external declarations of variables used for
 * addressing the correct interrupt handler 
 * function.
 */
 
#define GPT_START_SEC_VAR_32BIT
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */
    /* The Index for the ISR_Function Array*/
    /* This Index is responsible for the Isr Function(Notification or Wakeup)
        that has to be called in the ISR*/
    extern VAR (uint32, GPT_DATA) Gpt_IsrIndex_u32[4];
#define GPT_STOP_SEC_VAR_32BIT
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */

#define GPT_START_SEC_CONST_32BIT
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */
    extern CONST (Gpt_IsrRefType, GPT_CONST) Gpt_IsrFunction_ap[4];
#define GPT_STOP_SEC_CONST_32BIT
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/* Interrupt Functions */
#define GPT_START_SEC_CODE_ISR
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */

 #if (GPT_CFG_ISR_TYPE == GPT_ISR_CAT1)  /* PRQA S 0883 *//* MISRA-C:2004 Rules applicable to message 0883:  */
    /* The ISR Type_"Category 1" was selected in EAD */
    interrupt void Gpt_IsrInt0( void );
    interrupt void Gpt_IsrInt1( void );
    interrupt void Gpt_IsrInt2( void );
    interrupt void Gpt_IsrInt3( void );
        
 #elif (GPT_CFG_ISR_TYPE == GPT_ISR_CAT2)
    /* The ISR Type_"Category 2" was selected in EAD */
    ISR( Gpt_IsrInt0 );
    ISR( Gpt_IsrInt1 );
    ISR( Gpt_IsrInt2 );
    ISR( Gpt_IsrInt3 );
         
 #elif (GPT_CFG_ISR_TYPE == GPT_ISR_VOID)
    /* The ISR Type_"Void" was selected in EAD */
    void Gpt_IsrInt0( void );
    void Gpt_IsrInt1( void );
    void Gpt_IsrInt2( void );
    void Gpt_IsrInt3( void );

 #endif /* GPT_CFG_ISR_TYPE */
    
#define GPT_STOP_SEC_CODE_ISR
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */

#define GPT_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */

FUNC(void, GPT_CODE) Gpt_NotifContIsr( Gpt_HWChannelType HWChannel_t );
FUNC(void, GPT_CODE) Gpt_NotifSingleIsr( Gpt_HWChannelType HWChannel_t );
FUNC(void, GPT_CODE) Gpt_WakeupContIsr( Gpt_HWChannelType HWChannel_t );
FUNC(void, GPT_CODE) Gpt_WakeupSingleIsr( Gpt_HWChannelType HWChannel_t );

#define GPT_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */


#endif /* GPT_IRQ_H */

/**********************************************************************************************************************
 *  END OF FILE: Gpt_Irq.h
 *********************************************************************************************************************/
