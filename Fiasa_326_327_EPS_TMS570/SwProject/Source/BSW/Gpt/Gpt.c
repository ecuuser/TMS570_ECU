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
*         File:  Gpt.c
*      Project:  DrvGpt_Tms570Tirti01Asr
*       Module:  DrvGpt
*    Generator:  -
*
*  Description:  This file contains the module's implementation source.
*********************************************************************************************************************/


#define GPT_SOURCE

/**********************************************************************************************************************
*  INCLUDES
*********************************************************************************************************************/

#include "Std_Types.h"
#include "Gpt.h"
#include "Gpt_Irq.h"

/**********************************************************************************************************************
*  VERSION CHECK
*********************************************************************************************************************/

/* vendor specific version information is BCD coded */
#if (  (GPT_SW_MAJOR_VERSION != (0x01)) \
  || (GPT_SW_MINOR_VERSION != (0x00)) \
  || (GPT_SW_PATCH_VERSION != (0x06)) )
#error "Vendor specific version numbers of Gpt.c and Gpt.h are inconsistent"
#endif

/* AUTOSAR version information check has to match definition in header file */
#if (  (GPT_AR_MAJOR_VERSION != (0x02)) \
  || (GPT_AR_MINOR_VERSION != (0x02)) \
  || (GPT_AR_PATCH_VERSION != (0x00)) )
#error "AUTOSAR Specification Version numbers of Gpt.c and Gpt.h are inconsistent!"
#endif

/* versions of included header files shall be checked: configuration */
#if (  (GPT_CFG_MAJOR_VERSION != (0x01)) \
  || (GPT_CFG_MINOR_VERSION != (0x00)) )
#error "Version numbers of Gpt.c and Gpt_Cfg.h are inconsistent!"
#endif

/* versions of included header files shall be checked: interrupt interface */
#if (  (GPT_IRQ_MAJOR_VERSION != (0x01)) \
  || (GPT_IRQ_MINOR_VERSION != (0x00)) )
#error "Version numbers of Gpt.c and Gpt_Irq.h are inconsistent!"
#endif

/**********************************************************************************************************************
*  LOCAL CONSTANT MACROS
*********************************************************************************************************************/

/* Real Time Interrupt Module Registers */

#define GPT_REGISTER_BASE   (0xFFFFFC00u)


/* Global Registers */
/* RTI Global Control Register --> Start/Stop operations of the counter blocks and determines the external timebase */
#define GPT_RTIGCTRL       (GPT_REGISTER_ABS(0x00u))
/* RTI Timebase Control Register --> Selection of Free Running Counter behavior regarding clock source */
#define GPT_RTITBCTRL       (GPT_REGISTER_ABS(0x04u))
/* RTI Compare Control Register --> Setting dependencies of Free Running Counter instance to Compare instance */
#define GPT_RTICOMPCTRL     (GPT_REGISTER_ABS(0x0Cu))
/* RTI Clear/Status Interrupt Register --> Clears Free Running Counter Overflow and Compare Interrupts */
#define GPT_RTISETINT       (GPT_REGISTER_ABS(0x80u))
/* RTI Set/Status Interrupt Register --> Sets Free Running Counter Overflow and Compare Interrupts */
#define GPT_RTICLEARINT     (GPT_REGISTER_ABS(0x84u))
/* RTI Interrupt Flag Register -->  Determines pending interrupts */
#define GPT_RTIINTFLAG      (GPT_REGISTER_ABS(0x88u))

/* Counter block Registers */
/* RTI Free Running Counter 0 Register -->   Free Running Counter 0 */
#define GPT_FRC0            (GPT_REGISTER_ABS(0x10u))
/* RTI Up Counter 0 Register -->  Contains value of incrementation in frequency of RTI clock */
#define GPT_UC0             (GPT_REGISTER_ABS(0x14u))
/* RTI Compare Up Counter 0 Register -->   Prescales clock for incrementation of the Free Running Counter 0 */
#define GPT_CPUC0           (GPT_REGISTER_ABS(0x18u))

/* RTI Free Running Counter 1 Register -->   Free Running Counter 1 */
#define GPT_FRC1            (GPT_REGISTER_ABS(0x30u))
/* RTI Up Counter 1 Register -->  Contains value of incrementation in frequency of RTI clock */
#define GPT_UC1             (GPT_REGISTER_ABS(0x34u))
/* RTI Compare Up Counter 1 Register -->   Prescales clock for incrementation of the Free Running Counter 1 */
#define GPT_CPUC1           (GPT_REGISTER_ABS(0x38u))

/* Compare Registers to be mapped to timer channels*/
/* RTI Compare 0 Register -->  Contains value to be compared with Gpt_Counter0Register */
#define GPT_COMP0           (GPT_REGISTER_ABS(0x50u))
/* RTI Update Compare 0 Register -->  Contains value to be added to FRC0 to realize continuous timer mode  */
#define GPT_UDCP0           (GPT_REGISTER_ABS(0x54u))
/* RTI Compare 1 Register -->  Contains value to be compared with Gpt_Counter1Register */
#define GPT_COMP1           (GPT_REGISTER_ABS(0x58u))
/* RTI Update Compare 1 Register -->  Contains value to be added to FRC1 to realize continuous timer mode  */
#define GPT_UDCP1           (GPT_REGISTER_ABS(0x5Cu))
/* RTI Compare 2 Register -->  Contains value to be compared with Gpt_Counter2Register */
#define GPT_COMP2           (GPT_REGISTER_ABS(0x60u))
/* RTI Update Compare 2 Register -->  Contains value to be added to FRC2 to realize continuous timer mode  */
#define GPT_UDCP2           (GPT_REGISTER_ABS(0x64u))
/* RTI Compare 3 Register -->  Contains value to be compared with Gpt_Counter3Register */
#define GPT_COMP3           (GPT_REGISTER_ABS(0x68u))
/* RTI Update Compare 3 Register -->  Contains value to be added to FRC3 to realize continuous timer mode  */
#define GPT_UDCP3           (GPT_REGISTER_ABS(0x6Cu))

/* 
*  These masks are used for 32-bit write-access to registers, that influence behavior of the two counter blocks
*  and 4 compare blocks (currently used only 2 compare blocks connected to the two counter blocks) existing in
*  TMS570PSFC66; attended comments describe action for high bit; if necessary low bit action is described in
*  parenthesis (<--> ...)
*/

/* Assigned to RTIGCTRL-Register; Value after reset: 0x00000000 */
#define GPT_CNT0EN_MASK          (0x00000001u)  /* Enables operation of counter block 0: UC0, FRC0 */
#define GPT_CNT1EN_MASK          (0x00000002u)  /* Enables operation of counter block 1: UC1, FRC1 */

/* Assigned to RTITBCTRL-Register; Value after reset: 0x00000000 */
#define GPT_TBEXT_MASK           (0x00000001u)  /* Selects clock source of FRC0 from NTU (<--> UC0) */
#define GPT_INC_MASK             (0x00000002u)  /* Enables incrementation of FRC0 on failing NTU clock */

/* Assigned to RTICOMPCTRL-Register; Value after reset: 0x00000000 */
#define GPT_COMPSEL0_MASK        (0x00000001u)  /* Connects compare block 0 to counter block 1 = FRC1 (<--> FRC0) */
#define GPT_COMPSEL1_MASK        (0x00000010u)  /* Connects compare block 1 to counter block 1 = FRC1 (<--> FRC0) */
#define GPT_COMPSEL2_MASK        (0x00000100u)  /* Connects compare block 2 to counter block 1 = FRC1 (<--> FRC0) */
#define GPT_COMPSEL3_MASK        (0x00001000u)  /* Connects compare block 3 to counter block 1 = FRC1 (<--> FRC0) */

/* Assigned to RTICLEARINT-Register; Value after reset: 0x00000000 */
#define GPT_CLEARINT0_MASK       (0x00000001u)  /* Disables Clear Compare Interrupt 0 = INT0 (<--> bit unchanged) */
#define GPT_CLEARINT1_MASK       (0x00000002u)  /* Disables Clear Compare Interrupt 1 = INT1 (<--> bit unchanged) */
#define GPT_CLEARINT2_MASK       (0x00000004u)  /* Disables Clear Compare Interrupt 2 = INT1 (<--> bit unchanged) */
#define GPT_CLEARINT3_MASK       (0x00000008u)  /* Disables Clear Compare Interrupt 3 = INT1 (<--> bit unchanged) */
#define GPT_CLEARDMA0_MASK       (0x00000100u)  /* Disables Clear Compare DMA Request 0 = DMA0 (<--> bit unchanged) */
#define GPT_CLEARDMA1_MASK       (0x00000200u)  /* Disables Clear Compare DMA Request 1 = DMA1 (<--> bit unchanged) */
#define GPT_CLEARDMA2_MASK       (0x00000400u)  /* Disables Clear Compare DMA Request 2 = DMA2 (<--> bit unchanged) */
#define GPT_CLEARDMA3_MASK       (0x00000800u)  /* Disables Clear Compare DMA Request 3 = DMA3 (<--> bit unchanged) */
#define GPT_CLEARTBINT_MASK      (0x00010000u)  /* Disables Timebase Interrupt (<--> bit unchanged) */
#define GPT_CLEAROVL0INT_MASK    (0x00020000u)  /* Disables FRC0 Overflow Interrupt (<--> bit unchanged) */
#define GPT_CLEAROVL1INT_MASK    (0x00040000u)  /* Disables FRC1 Overflow Interrupt (<--> bit unchanged) */

/* Assigned to RTISETINT-Register; Value after reset: 0x00000000 */
#define GPT_SETINT0_MASK         (0x00000001u)  /* Enables Clear Compare Interrupt 0 = INT0 (<--> bit unchanged) */
#define GPT_SETINT1_MASK         (0x00000002u)  /* Enables Clear Compare Interrupt 1 = INT1 (<--> bit unchanged) */
#define GPT_SETINT2_MASK         (0x00000004u)  /* Enables Clear Compare Interrupt 2 = INT1 (<--> bit unchanged) */
#define GPT_SETINT3_MASK         (0x00000008u)  /* Enables Clear Compare Interrupt 3 = INT1 (<--> bit unchanged) */
#define GPT_SETDMA0_MASK         (0x00000100u)  /* Enables Clear Compare DMA Request 0 = DMA0 (<--> bit unchanged) */
#define GPT_SETDMA1_MASK         (0x00000200u)  /* Enables Clear Compare DMA Request 1 = DMA1 (<--> bit unchanged) */
#define GPT_SETDMA2_MASK         (0x00000400u)  /* Enables Clear Compare DMA Request 2 = DMA1 (<--> bit unchanged) */
#define GPT_SETDMA3_MASK         (0x00000800u)  /* Enables Clear Compare DMA Request 3 = DMA1 (<--> bit unchanged) */
#define GPT_SETTBINT_MASK        (0x00010000u)  /* Enables Timebase Interrupt (<--> bit unchanged) */
#define GPT_SETOVL0INT_MASK      (0x00020000u)  /* Enables FRC0 Overflow Interrupt (<--> bit unchanged) */
#define GPT_SETOVL1INT_MASK      (0x00040000u)  /* Enables FRC1 Overflow Interrupt (<--> bit unchanged) */

/* Assigned to RTIINTFLAG-Register; Value after reset: 0x00000000 */
#define GPT_INT0_MASK            (0x00000001u)  /* Sets Interrupt Flag 0 to 0 = no interrupt pending (<--> bit unchanged) */
#define GPT_INT1_MASK            (0x00000002u)  /* Sets Interrupt Flag 1 to 0 = no interrupt pending (<--> bit unchanged) */
#define GPT_INT2_MASK            (0x00000004u)  /* Sets Interrupt Flag 2 to 0 = no interrupt pending (<--> bit unchanged) */
#define GPT_INT3_MASK            (0x00000008u)  /* Sets Interrupt Flag 3 to 0 = no interrupt pending (<--> bit unchanged) */
#define GPT_TBINT_MASK           (0x00010000u)  /* Sets Timebase Interrupt Flag to 0 = no interrupt pending (<--> bit unchanged) */
#define GPT_OVL0INT_MASK         (0x00020000u)  /* Sets FRC0 Overflow Interrupt Flag to 0 = no interrupt pending (<--> bit unchanged) */
#define GPT_OVL1INT_MASK         (0x00040000u)  /* Sets FRC1 Overflow Interrupt Flag to 0 = no interrupt pending (<--> bit unchanged) */

#define GPT_COMPBYTE_MASK        (0x0000000Fu)  /* Masks higher Half-Byte of HWChannel_t (CountByte) to evaluate the Compare Block */
#define GPT_COUNTBYTE_MASK       (0x000000F0u)  /* Masks lower Half-Byte of HWChannel_t (CompByte) to evaluate the Counter Block */



/* Wrapper macros for register access. Used to redirect read/write operations on HW registers
 * to special Os services.
 */

#ifndef GPT_WRITE_PROTECTED_REGISTER_32BIT
# define GPT_WRITE_PROTECTED_REGISTER_32BIT(address, value, area)  (osWritePeripheral32((osuint16)(area), (osuint32)(address), (osuint32)(value))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#endif

#ifndef GPT_READ_PROTECTED_REGISTER_32BIT
# define GPT_READ_PROTECTED_REGISTER_32BIT(address, area)  (osReadPeripheral32((osuint16)(area), (osuint32)(address))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#endif

#ifndef GPT_MODIFY_PROTECTED_REGISTER_32BIT
# define GPT_MODIFY_PROTECTED_REGISTER_32BIT(address, clearmask, setmask, area) (osModifyPeripheral32((osuint16)(area), (osuint32)(address), (osuint32)(clearmask), (osuint32)(setmask))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#endif

#if (GPT_SPECIAL_REGISTER_ACCESS_ENABLED == STD_ON)
#  if(GPT_SPECIAL_REGISTER_ACCESS_NOT_IN_INIT == STD_ON)
#    if (GPT_SPECIAL_REGISTER_ACCESS_ONLY_FOR_PRIVILEGED_MODE_REGISTERS == STD_ON)
#      define GPT_WRITE_REGISTER_32BIT(address, value, area)                        (*((volatile uint32*)(address)) = (uint32)(value)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#    else
#      define GPT_WRITE_REGISTER_32BIT(address, value, area)                        (GPT_WRITE_PROTECTED_REGISTER_32BIT(address, value, area)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#    endif
#    define GPT_WRITE_REGISTER_32BIT_INIT(address, value, area)                     (*((volatile uint32*)(address)) = (uint32)(value)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#    define GPT_WRITE_REGISTER_32BIT_SUPERVISOR_INIT(address, value, area)          (*((volatile uint32*)(address)) = (uint32)(value)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#  else
#    if (GPT_SPECIAL_REGISTER_ACCESS_ONLY_FOR_PRIVILEGED_MODE_REGISTERS == STD_ON)
#      define GPT_WRITE_REGISTER_32BIT_INIT(address, value, area)                   (*((volatile uint32*)(address)) = (uint32)(value)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#      define GPT_WRITE_REGISTER_32BIT(address, value, area)                        (*((volatile uint32*)(address)) = (uint32)(value)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#    else
#      define GPT_WRITE_REGISTER_32BIT_INIT(address, value, area)                   (GPT_WRITE_PROTECTED_REGISTER_32BIT(address, value, area)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#      define GPT_WRITE_REGISTER_32BIT(address, value, area)                        (GPT_WRITE_PROTECTED_REGISTER_32BIT(address, value, area)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#    endif
#    define GPT_WRITE_REGISTER_32BIT_SUPERVISOR_INIT(address, value, area)          (GPT_WRITE_PROTECTED_REGISTER_32BIT(address, value, area)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#  endif
#  define GPT_WRITE_REGISTER_32BIT_SUPERVISOR(address, value, area)                 (GPT_WRITE_PROTECTED_REGISTER_32BIT(address, value, area)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#else
#  define GPT_WRITE_REGISTER_32BIT_INIT(address, value, area)                       (*((volatile uint32*)(address)) = (uint32)(value)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#  define GPT_WRITE_REGISTER_32BIT_SUPERVISOR_INIT(address, value, area)            (*((volatile uint32*)(address)) = (uint32)(value)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#  define GPT_WRITE_REGISTER_32BIT(address, value, area)                            (*((volatile uint32*)(address)) = (uint32)(value)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#  define GPT_WRITE_REGISTER_32BIT_SUPERVISOR(address, value, area)                 (*((volatile uint32*)(address)) = (uint32)(value)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#endif

#if (GPT_SPECIAL_REGISTER_ACCESS_ENABLED == STD_ON)
#  if(GPT_SPECIAL_REGISTER_ACCESS_ONLY_FOR_WRITE == STD_ON)
#    if(GPT_SPECIAL_REGISTER_ACCESS_NOT_IN_INIT == STD_ON)
#      define GPT_READ_REGISTER_32BIT_SUPERVISOR_INIT(address, area)                (*((uint32*)(address))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#    else
#      define GPT_READ_REGISTER_32BIT_SUPERVISOR_INIT(address, area)                (GPT_READ_PROTECTED_REGISTER_32BIT((address), (area))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#    endif
#    define GPT_READ_REGISTER_32BIT_INIT(address, area)                             (*((volatile uint32*)(address))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#    define GPT_READ_REGISTER_32BIT(address, area)                                  (*((volatile uint32*)(address))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#  else
#    if(GPT_SPECIAL_REGISTER_ACCESS_NOT_IN_INIT == STD_ON)
#      if (GPT_SPECIAL_REGISTER_ACCESS_ONLY_FOR_PRIVILEGED_MODE_REGISTERS == STD_ON)
#        define GPT_READ_REGISTER_32BIT(address, area)                               (*((volatile uint32*)(address))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#      else
#        define GPT_READ_REGISTER_32BIT(address, area)                               (GPT_READ_PROTECTED_REGISTER_32BIT(address, area)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#      endif
#      define GPT_READ_REGISTER_32BIT_INIT(address, area)                            (*((volatile uint32*)(address))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#      define GPT_READ_REGISTER_32BIT_SUPERVISOR_INIT(address, area)                 (*((volatile uint32*)(address))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#    else
#      if (GPT_SPECIAL_REGISTER_ACCESS_ONLY_FOR_PRIVILEGED_MODE_REGISTERS == STD_ON)
#        define GPT_READ_REGISTER_32BIT_INIT(address, area)                          (*((volatile uint32*)(address))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#        define GPT_READ_REGISTER_32BIT(address, area)                               (*((volatile uint32*)(address))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#      else
#        define GPT_READ_REGISTER_32BIT_INIT(address, area)                          (GPT_READ_PROTECTED_REGISTER_32BIT(address, area)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#        define GPT_READ_REGISTER_32BIT(address, area)                               (GPT_READ_PROTECTED_REGISTER_32BIT(address, area)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#      endif
#      define GPT_READ_REGISTER_32BIT_SUPERVISOR_INIT(address, area)                 (GPT_READ_PROTECTED_REGISTER_32BIT(address, area)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#    endif
#  endif
#  define GPT_READ_REGISTER_32BIT_SUPERVISOR(address, area)                          (GPT_READ_PROTECTED_REGISTER_32BIT(address, area)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#else
#  define GPT_READ_REGISTER_32BIT_INIT(address, area)                                (*((volatile uint32*)(address))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#  define GPT_READ_REGISTER_32BIT_SUPERVISOR_INIT(address, area)                     (*((volatile uint32*)(address))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#  define GPT_READ_REGISTER_32BIT(address, area)                                     (*((volatile uint32*)(address))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#  define GPT_READ_REGISTER_32BIT_SUPERVISOR(address, area)                          (*((volatile uint32*)(address))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#endif

#if (GPT_SPECIAL_REGISTER_ACCESS_ENABLED == STD_ON)
#  if(GPT_SPECIAL_REGISTER_ACCESS_NOT_IN_INIT == STD_ON)
#    if (GPT_SPECIAL_REGISTER_ACCESS_ONLY_FOR_PRIVILEGED_MODE_REGISTERS == STD_ON)
#      define GPT_MODIFY_REGISTER_32BIT(address, clearmask, setmask, area)                        ((*(volatile uint32*)(address)) = (*(volatile uint32*)(address)) & (clearmask) | (setmask)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#    else
#      define GPT_MODIFY_REGISTER_32BIT(address, clearmask, setmask, area)                        (GPT_MODIFY_PROTECTED_REGISTER_32BIT(address, clearmask, setmask, area))
#    endif
#    define GPT_MODIFY_REGISTER_32BIT_INIT(address, clearmask, setmask, area)                     ((*(volatile uint32*)(address)) = (*(volatile uint32*)(address)) & (clearmask) | (setmask)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#    define GPT_MODIFY_REGISTER_32BIT_SUPERVISOR_INIT(address, clearmask, setmask, area)          ((*(volatile uint32*)(address)) = (*(volatile uint32*)(address)) & (clearmask) | (setmask)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#  else
#    if (GPT_SPECIAL_REGISTER_ACCESS_ONLY_FOR_PRIVILEGED_MODE_REGISTERS == STD_ON)
#      define GPT_MODIFY_REGISTER_32BIT_INIT(address, clearmask, setmask, area)                   ((*(volatile uint32*)(address)) = (*(volatile uint32*)(address)) & (clearmask) | (setmask)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#      define GPT_MODIFY_REGISTER_32BIT(address, clearmask, setmask, area)                        ((*(volatile uint32*)(address)) = (*(volatile uint32*)(address)) & (clearmask) | (setmask)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#    else
#      define GPT_MODIFY_REGISTER_32BIT_INIT(address, clearmask, setmask, area)                   (GPT_MODIFY_PROTECTED_REGISTER_32BIT(address, clearmask, setmask, area)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#      define GPT_MODIFY_REGISTER_32BIT(address, clearmask, setmask, area)                        (GPT_MODIFY_PROTECTED_REGISTER_32BIT(address, clearmask, setmask, area)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#    endif
#    define GPT_MODIFY_REGISTER_32BIT_SUPERVISOR_INIT(address, clearmask, setmask, area)          (GPT_MODIFY_PROTECTED_REGISTER_32BIT(address, clearmask, setmask, area)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#  endif
#  define GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(address, clearmask, setmask, area)                 (GPT_MODIFY_PROTECTED_REGISTER_32BIT(address, clearmask, setmask, area)) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#else
#  define GPT_MODIFY_REGISTER_32BIT_INIT(address, clearmask, setmask, area)                       ((*(volatile uint32*)(address)) = (((*(volatile uint32*)(address)) & (clearmask)) | (setmask))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#  define GPT_MODIFY_REGISTER_32BIT_SUPERVISOR_INIT(address, clearmask, setmask, area)            ((*(volatile uint32*)(address)) = (((*(volatile uint32*)(address)) & (clearmask)) | (setmask))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#  define GPT_MODIFY_REGISTER_32BIT(address, clearmask, setmask, area)                            ((*(volatile uint32*)(address)) = (((*(volatile uint32*)(address)) & (clearmask)) | (setmask))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#  define GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(address, clearmask, setmask, area)                 ((*(volatile uint32*)(address)) = (((*(volatile uint32*)(address)) & (clearmask)) | (setmask))) /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */
#endif
/**********************************************************************************************************************
*  LOCAL FUNCTION MACROS
*********************************************************************************************************************/

#define GPT_REGISTER_ABS(x)     (GPT_REGISTER_BASE + (x))  /* PRQA S 3453 */ /* Macro is used for efficiency reasons. Type is ensured. */

/**********************************************************************************************************************
*  LOCAL DATA TYPES AND STRUCTURES
*********************************************************************************************************************/



/**********************************************************************************************************************
*  LOCAL DATA PROTOTYPES
*********************************************************************************************************************/

/**********************************************************************************************************************
*  GLOBAL DATA
*********************************************************************************************************************/

#define GPT_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */

static P2CONST(Gpt_ConfigType, GPT_DATA, GPT_CONST_PBCFG)
  Gpt_Config_pt = NULL_PTR;

#define GPT_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */


#define GPT_START_SEC_VAR_32BIT
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */

/* The Index for the ISR_Function Array*/
/* This Index is responsible for the Isr Function(Notification or Wakeup)
that has to be called in the ISR*/
VAR (uint32, GPT_DATA) Gpt_IsrIndex_u32[4];

/* Marker for active timer channels (bitwise) */
static VAR(uint32, GPT_DATA) Gpt_ActiveMap_u32;

#if (STD_ON == GPT_WAKEUP_FUNCTIONALITY_API)
/* To enable wakeup the assigned bit of this channel is set to 1 */
static VAR (uint32, GPT_DATA) Gpt_ChannelWakeupMatrix_u32;
/* Marker for operation mode */
static VAR (Gpt_ModeType, GPT_DATA) Gpt_SleepMode_t;
#endif /* (STD_ON == GPT_WAKEUP_FUNCTIONALITY_API) */

#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)
/* To enable notification the assigned bit of this channel is set to 1 */
static VAR (uint32, GPT_DATA) Gpt_ChannelNotifyMatrix_u32;
#endif /* (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API) */

#define GPT_STOP_SEC_VAR_32BIT
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */

#define GPT_START_SEC_CONST_32BIT
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */

/*The Array of pointers to the ISR_Functions */
CONST (Gpt_IsrRefType, GPT_CONST) Gpt_IsrFunction_ap[4]=
{
  &Gpt_NotifContIsr,
  &Gpt_NotifSingleIsr,
  &Gpt_WakeupContIsr,
  &Gpt_WakeupSingleIsr
};

#define GPT_STOP_SEC_CONST_32BIT
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */

/**********************************************************************************************************************
*  LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************************/

static FUNC(Gpt_HWChannelType, GPT_CODE) Gpt_GetHWChannel ( Gpt_ChannelType ChannelIdx );
static FUNC(Gpt_HWChannelType, GPT_CODE) Gpt_GetHWCountBlock ( Gpt_ChannelType ChannelIdx );
static FUNC(Gpt_ChannelType, GPT_CODE) Gpt_GetLogicalChannel ( Gpt_HWChannelType HWChannelIdx );

/**********************************************************************************************************************
*  LOCAL FUNCTIONS
*********************************************************************************************************************/


#define GPT_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 *//* MD_MSR_3.4  */

/**********************************************************************************************************************
Function name:  Gpt_GetHWChannel
**********************************************************************************************************************/

static FUNC(Gpt_HWChannelType, GPT_CODE) Gpt_GetHWChannel ( Gpt_ChannelType ChannelIdx )
{
  Gpt_HWChannelType HWCompBlockIdx;
  HWCompBlockIdx = Gpt_Config_pt -> ChannelConfig_pt [ChannelIdx].HWChannel_t;
  HWCompBlockIdx &= GPT_COMPBYTE_MASK;
  return HWCompBlockIdx;
}

/**********************************************************************************************************************
Function name:  Gpt_GetHWCountBlock
**********************************************************************************************************************/

static FUNC(Gpt_HWChannelType, GPT_CODE) Gpt_GetHWCountBlock ( Gpt_ChannelType ChannelIdx )
{
  Gpt_HWChannelType HWCountBlockIdx;
  HWCountBlockIdx = Gpt_Config_pt -> ChannelConfig_pt [ChannelIdx].HWChannel_t;
  HWCountBlockIdx &= GPT_COUNTBYTE_MASK;
  HWCountBlockIdx /= 0x10;
  return HWCountBlockIdx;
}

/**********************************************************************************************************************
Function name:  Gpt_GetLogicalChannel
**********************************************************************************************************************/

static FUNC(Gpt_ChannelType, GPT_CODE) Gpt_GetLogicalChannel ( Gpt_HWChannelType HWChannelIdx )
{
  Gpt_ChannelType ChannelIdx;
  Gpt_HWChannelType HWChlLoopIdx;
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONST_PBCFG) ChlConf_pt;

  /* -------------------- Loop over all channels ----------------------------------------
  * Check for channel number assigned to hardware channel
  */
  for ( ChannelIdx = 0; ChannelIdx < Gpt_Config_pt->ChannelCount_u32; ChannelIdx ++ )
  {
    ChlConf_pt = &(Gpt_Config_pt->ChannelConfig_pt[ChannelIdx]);
    HWChlLoopIdx = ChlConf_pt->HWChannel_t;
    HWChlLoopIdx &= GPT_COMPBYTE_MASK;
    if (HWChlLoopIdx == HWChannelIdx)
    {
      /* logical channel found */
      break;
    }
  }
  return ChannelIdx;
}
/**********************************************************************************************************************
*  GLOBAL FUNCTIONS
*********************************************************************************************************************/


/**********************************************************************************************************************
Function name:  Gpt_InitMemory
**********************************************************************************************************************/
FUNC(void, GPT_CODE) Gpt_InitMemory(void)
{
  Gpt_Config_pt = NULL_PTR;
}

#if (STD_ON == GPT_VERSION_INFO_API)
/**********************************************************************************************************************
Function name:  Gpt_GetVersionInfo
**********************************************************************************************************************/

FUNC(void, GPT_CODE) Gpt_GetVersionInfo
  (
  P2VAR(Std_VersionInfoType, AUTOMATIC, GPT_APPL_DATA) versioninfo
  )
{


#if (STD_ON == GPT_CFG_CHK_PARAM_VINFO)
  if (NULL_PTR == versioninfo)
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook(GPT_SID_GET_VERSION_INFO, GPT_E_PARAM_VINFO);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return;
  }
#endif  /* (STD_ON == GPT_CFG_CHK_PARAM_VINFO) */


  versioninfo->vendorID         = ( GPT_VENDOR_ID );
  versioninfo->moduleID         = ( GPT_MODULE_ID );
  versioninfo->instanceID       = ( GPT_INSTANCE_ID );
  versioninfo->sw_major_version = ( GPT_SW_MAJOR_VERSION );
  versioninfo->sw_minor_version = ( GPT_SW_MINOR_VERSION );
  versioninfo->sw_patch_version = ( GPT_SW_PATCH_VERSION );

}   /* Gpt_GetVersionInfo() */ /* PRQA S 2006 *//*  MD_MSR_14.7   */

#endif  /* (STD_ON == GPT_VERSION_INFO_API) */

/**********************************************************************************************************************
Function name:  Gpt_Init
**********************************************************************************************************************/

FUNC(void, GPT_CODE) Gpt_Init( P2CONST( Gpt_ConfigType, AUTOMATIC, GPT_CONST_PBCFG ) configPtr )
{
  /* variable for channel numbers used in the init loop */
  /* Numeric ID of the GPT channel */
  Gpt_ChannelType ChannelIdx;
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONST_PBCFG) ChlConf_pt;

  /* configPtr must not be NULL. In case it is NULL report an error and
  * return immediately.
  * this check can be disabled.
  */

#if (STD_ON == GPT_CFG_CHK_PARAM_CONFIG)
  if (NULL_PTR == configPtr)
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook(GPT_SID_INIT, GPT_E_PARAM_CONFIG);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return;
  }
#endif /* (STD_ON == GPT_CFG_CHK_PARAM_CONFIG) */

  /* Gpt module must not be initalized. Otherwise call the Det with GPT_E_ALREADY_INITIALIZED */
#if (STD_ON == GPT_CFG_CHK_ALREADY_INIT)
  if (NULL_PTR != Gpt_Config_pt)
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook(GPT_SID_INIT, GPT_E_ALREADY_INITIALIZED);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return;
  }
#endif  /* (STD_ON == GPT_CFG_CHK_ALREADY_INIT) */

  /* store config pointer (as a side effect this indicates correct
  * initialization in development mode [GPT050]).
  */
  Gpt_Config_pt = configPtr;

  /* Reset wakeup matrix */
#if (STD_ON == GPT_WAKEUP_FUNCTIONALITY_API)
  Gpt_ChannelWakeupMatrix_u32 = 0;
#endif  /* (STD_ON == GPT_WAKEUP_FUNCTIONALITY_API) */

  /* Reset the notification attributes */
#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)
  Gpt_ChannelNotifyMatrix_u32 = 0;
#endif  /* (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API) */

  /* no timer channel is active */
  Gpt_ActiveMap_u32 = 0;


  /* -------------------- Init loop ----------------------------------------
  * Only initialize configured resources, that means, only timers
  * listed in the channel configuration structure.
  */

  for ( ChannelIdx = 0; ChannelIdx < Gpt_Config_pt->ChannelCount_u32; ChannelIdx ++ )
  {
    Gpt_HWChannelType HWCompBlockIdx;
    Gpt_HWChannelType HWCountBlockIdx;

    ChlConf_pt = &(Gpt_Config_pt->ChannelConfig_pt[ChannelIdx]);

    /* Registers belonging to the CounterBlock */
    HWCountBlockIdx = Gpt_GetHWCountBlock (ChannelIdx);

    switch (HWCountBlockIdx)
    {    
    case 0:
      GPT_MODIFY_REGISTER_32BIT_SUPERVISOR_INIT(GPT_RTIGCTRL,(~GPT_CNT0EN_MASK),0,OS_MEM_AREA_RTI);             /* Operation of counter block */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR_INIT(GPT_UC0,0,OS_MEM_AREA_RTI);                                   /* RTI clock counter */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR_INIT(GPT_CPUC0,ChlConf_pt->ChannelPrescale_u32,OS_MEM_AREA_RTI);   /* Prescales clock */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR_INIT(GPT_FRC0,0,OS_MEM_AREA_RTI);                                  /* Free running counter */ /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    case 1:
      GPT_MODIFY_REGISTER_32BIT_SUPERVISOR_INIT(GPT_RTIGCTRL,(~GPT_CNT1EN_MASK),0,OS_MEM_AREA_RTI);             /* Operation of counter block */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR_INIT(GPT_UC1,0,OS_MEM_AREA_RTI);                                   /* RTI clock counter */  /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR_INIT(GPT_CPUC1,ChlConf_pt->ChannelPrescale_u32,OS_MEM_AREA_RTI);   /* Prescales clock */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR_INIT(GPT_FRC1,0,OS_MEM_AREA_RTI);                                  /* Free running counter */      /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    default:    /* for formal aspect */
      break;
    } /* End of switch */

    /* Registers belonging to the CompareBlock */
    HWCompBlockIdx = Gpt_GetHWChannel (ChannelIdx);

    switch (HWCompBlockIdx)
    {    
    case 0:
      if (0 == HWCountBlockIdx)
      {    
        GPT_MODIFY_REGISTER_32BIT_SUPERVISOR_INIT(GPT_RTICOMPCTRL,(~GPT_COMPSEL0_MASK),0,OS_MEM_AREA_RTI);    /* Connects compare block to counter block 0) */ /* PRQA S 303 */ /* MD_Gpt_303 */
      }
      else
      {
        GPT_MODIFY_REGISTER_32BIT_SUPERVISOR_INIT(GPT_RTICOMPCTRL,~0,GPT_COMPSEL0_MASK,OS_MEM_AREA_RTI);       /* Connects compare block to counter block 1) */ /* PRQA S 303 */ /* MD_Gpt_303 */
      }
      GPT_MODIFY_REGISTER_32BIT_SUPERVISOR_INIT(GPT_RTIINTFLAG,~0,GPT_INT0_MASK,OS_MEM_AREA_RTI);                /* Set back Interrupt Flag */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR_INIT(GPT_UDCP0,0,OS_MEM_AREA_RTI);                                  /* Register to realize continuous timer mode */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR_INIT(GPT_COMP0,0,OS_MEM_AREA_RTI);                                  /* Register holds compare value */ /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    case 1:
      if (0 == HWCountBlockIdx)
      {    
        GPT_MODIFY_REGISTER_32BIT_SUPERVISOR_INIT(GPT_RTICOMPCTRL,(~GPT_COMPSEL1_MASK),0,OS_MEM_AREA_RTI);    /* Connects compare block to counter block 0) */ /* PRQA S 303 */ /* MD_Gpt_303 */
      }
      else
      {
        GPT_MODIFY_REGISTER_32BIT_SUPERVISOR_INIT(GPT_RTICOMPCTRL,~0,GPT_COMPSEL1_MASK,OS_MEM_AREA_RTI);       /* Connects compare block to counter block 1) */ /* PRQA S 303 */ /* MD_Gpt_303 */
      }
      GPT_MODIFY_REGISTER_32BIT_SUPERVISOR_INIT(GPT_RTIINTFLAG,~0,GPT_INT1_MASK,OS_MEM_AREA_RTI);                /* Set back Interrupt Flag */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR_INIT(GPT_UDCP1,0,OS_MEM_AREA_RTI);                                  /* Register to realize continuous timer mode */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR_INIT(GPT_COMP1,0,OS_MEM_AREA_RTI);                                  /* Register holds compare value */ /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    case 2:
      if (0 == HWCountBlockIdx)
      {    
        GPT_MODIFY_REGISTER_32BIT_SUPERVISOR_INIT(GPT_RTICOMPCTRL,(~GPT_COMPSEL2_MASK),0,OS_MEM_AREA_RTI);    /* Connects compare block to counter block 0) */ /* PRQA S 303 */ /* MD_Gpt_303 */
      }
      else
      {
        GPT_MODIFY_REGISTER_32BIT_SUPERVISOR_INIT(GPT_RTICOMPCTRL,~0,GPT_COMPSEL2_MASK,OS_MEM_AREA_RTI);       /* Connects compare block to counter block 1) */ /* PRQA S 303 */ /* MD_Gpt_303 */
      }
      GPT_MODIFY_REGISTER_32BIT_SUPERVISOR_INIT(GPT_RTIINTFLAG,~0,GPT_INT2_MASK,OS_MEM_AREA_RTI);                /* Set back Interrupt Flag */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR_INIT(GPT_UDCP2,0,OS_MEM_AREA_RTI);                                  /* Register to realize continuous timer mode */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR_INIT(GPT_COMP2,0,OS_MEM_AREA_RTI);                                  /* Register holds compare value */ /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    case 3:
      if (0 == HWCountBlockIdx)
      {    
        GPT_MODIFY_REGISTER_32BIT_SUPERVISOR_INIT(GPT_RTICOMPCTRL,(~GPT_COMPSEL3_MASK),0,OS_MEM_AREA_RTI);    /* Connects compare block to counter block 0) */ /* PRQA S 303 */ /* MD_Gpt_303 */
      }
      else
      {
        GPT_MODIFY_REGISTER_32BIT_SUPERVISOR_INIT(GPT_RTICOMPCTRL,~0,GPT_COMPSEL3_MASK,OS_MEM_AREA_RTI);       /* Connects compare block to counter block 1) */ /* PRQA S 303 */ /* MD_Gpt_303 */
      }
      GPT_MODIFY_REGISTER_32BIT_SUPERVISOR_INIT(GPT_RTIINTFLAG,~0,GPT_INT3_MASK,OS_MEM_AREA_RTI);                /* Set back Interrupt Flag */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR_INIT(GPT_UDCP3,0,OS_MEM_AREA_RTI);                                  /* Register to realize continuous timer mode */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR_INIT(GPT_COMP3,0,OS_MEM_AREA_RTI);                                  /* Register holds compare value */ /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    default:    /* for formal aspect */
      break;
    } /* End of switch */
  } /* End of for */
  /* -------------------- End Init Loop ----------------------------------*/


  /* set normal mode */
#if (STD_ON == GPT_WAKEUP_FUNCTIONALITY_API)
  Gpt_SleepMode_t = GPT_MODE_NORMAL;
#endif  /* (STD_ON == GPT_WAKEUP_FUNCTIONALITY_API) */
  return;
} /* Gpt_Init */ /* Gpt_GetVersionInfo() */ /* PRQA S 2006 *//*  MD_MSR_14.7   */


#if (STD_ON == GPT_DEINIT_API)
/**********************************************************************************************************************
Function name:  Gpt_DeInit
**********************************************************************************************************************/

FUNC(void, GPT_CODE) Gpt_DeInit( void )
{
  /* variable for channel numbers used in the init loop */
  /* Numeric ID of the GPT channel */
  Gpt_ChannelType ChannelIdx;

  /* check if the driver has been successfully initialized. if the driver
  * has not been initialized, report an error and return immediately.
  */

#if (STD_ON == GPT_CFG_CHK_UNINIT)
  if (NULL_PTR == Gpt_Config_pt)
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook(GPT_SID_DEINIT, GPT_E_UNINIT);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return;
  }
#endif /* (STD_ON == GPT_CFG_CHK_UNINIT) */

  /* Check the running states */
#if (STD_ON == GPT_CFG_CHK_BUSY)
  {
    if ( Gpt_ActiveMap_u32 )
    {
      /* At least one of the channels is active */
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
      Gpt_Errorhook ( GPT_SID_DEINIT, GPT_E_BUSY );
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
      return;
    }
  }
#endif /* (STD_ON == GPT_CFG_CHK_BUSY) */ /* PRQA S 2006 *//*  MD_MSR_14.7   */

  /* -------------------- DeInit Loop ----------------------------------------
  * Only deinitialize configured resources, that means, only timers
  * listed in the channel configuration structure.
  */

  for ( ChannelIdx = 0; ChannelIdx < Gpt_Config_pt->ChannelCount_u32; ChannelIdx ++ )
  {
    Gpt_HWChannelType HWCompBlockIdx;
    Gpt_HWChannelType HWCountBlockIdx;

    /* Registers belonging to the CounterBlock */
    HWCountBlockIdx = Gpt_GetHWCountBlock (ChannelIdx);

    switch (HWCountBlockIdx)
    {    
    case 0:
      GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(GPT_RTIGCTRL,(~GPT_CNT0EN_MASK),0,OS_MEM_AREA_RTI);             /* Operation of counter block */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC0,0,OS_MEM_AREA_RTI);                                    /* RTI clock counter */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_CPUC0,0,OS_MEM_AREA_RTI);                                  /* Prescales clock */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC0,0,OS_MEM_AREA_RTI);                                   /* Free running counter */ /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    case 1:
      GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(GPT_RTIGCTRL,(~GPT_CNT1EN_MASK),0,OS_MEM_AREA_RTI);             /* Operation of counter block */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC1,0,OS_MEM_AREA_RTI);                                    /* RTI clock counter */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_CPUC1,0,OS_MEM_AREA_RTI);                                  /* Prescales clock */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC1,0,OS_MEM_AREA_RTI);                                   /* Free running counter */ /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    default:    /* for formal aspect */
      break;
    } /* End of switch */

    /* Registers belonging to the CompareBlock */
    HWCompBlockIdx = Gpt_GetHWChannel (ChannelIdx);

    switch (HWCompBlockIdx)
    {    
    case 0:
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP0,0,OS_MEM_AREA_RTI);                                  /* Register to realize continuous timer mode */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP0,0,OS_MEM_AREA_RTI);                                  /* Register holds compare value */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_RTICLEARINT,GPT_CLEARINT0_MASK,OS_MEM_AREA_RTI);            /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    case 1:
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP1,0,OS_MEM_AREA_RTI);                                  /* Register to realize continuous timer mode */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP1,0,OS_MEM_AREA_RTI);                                  /* Register holds compare value */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_RTICLEARINT,GPT_CLEARINT1_MASK,OS_MEM_AREA_RTI);           /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    case 2:
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP2,0,OS_MEM_AREA_RTI);                                  /* Register to realize continuous timer mode */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP2,0,OS_MEM_AREA_RTI);                                  /* Register holds compare value */ /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_RTICLEARINT,GPT_CLEARINT2_MASK,OS_MEM_AREA_RTI);           /* PRQA S 303 */ /* MD_Gpt_303 */
   break;
    case 3:
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP3,0,OS_MEM_AREA_RTI);                                  /* Register to realize continuous timer mode */  /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP3,0,OS_MEM_AREA_RTI);                                  /* Register holds compare value */  /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_RTICLEARINT,GPT_CLEARINT3_MASK,OS_MEM_AREA_RTI);           /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    default:    /* for formal aspect */
      break;
    } /* End of switch */
  } /* End of for */

  /* Reset the notification attributes */
#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)
  Gpt_ChannelNotifyMatrix_u32 = 0;
#endif /* (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API) */

  /* no timer channel is active */
  Gpt_ActiveMap_u32  = 0;

  /* Reset configuration pointer */
  Gpt_Config_pt = NULL_PTR;
  return;
} /* Gpt_DeInit */ /* PRQA S 2006 *//*  MD_MSR_14.7   */
#endif /* GPT_DEINIT_API */


#if (STD_ON == GPT_TIME_ELAPSED_API)
/**********************************************************************************************************************
Function name:  Gpt_GetTimeElapsed
**********************************************************************************************************************/

FUNC(Gpt_ValueType, GPT_CODE) Gpt_GetTimeElapsed( Gpt_ChannelType channel )
{
  /* local variables to store channel configuration pointer, timer value and counter value
  * of a timer  */
  Gpt_HWChannelType HWCompBlockIdx;
  Gpt_HWChannelType HWCountBlockIdx;
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONST_PBCFG) ChlConf_pt;
  Gpt_ValueType     UpdCompare_t = 0;
  Gpt_ValueType     Compare_t = 0;
  Gpt_ValueType     Counter_t = 0;
  /* Check if the driver has been successfully initialized. If the driver
  * has not been initialized, report an error and return immediately.
  */
#if (STD_ON == GPT_CFG_CHK_UNINIT )
  if (NULL_PTR == Gpt_Config_pt )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook(GPT_SID_GET_TIME_ELAPSED, GPT_E_UNINIT);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return 0;
  }
#endif /* (STD_ON == GPT_CFG_CHK_UNINIT) */

  /* Check if parameter channel is in valid range. If its value is out
  * of range report an error and return immediately.
  */
#if (  STD_ON == GPT_CFG_CHK_PARAM_CHL )
  if ( Gpt_Config_pt->ChannelCount_u32 <= channel )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook ( GPT_SID_GET_TIME_ELAPSED, GPT_E_PARAM_CHANNEL );
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return 0;
  }
#endif /* (STD_ON == GPT_CFG_CHK_PARAM_CHL) */

  /* Get the hardware channel */
  HWCompBlockIdx = Gpt_GetHWChannel ( channel );

  /* Make sure the timer is running now */
  if (0 == ( Gpt_ActiveMap_u32 & (1U << HWCompBlockIdx) ))
  {
#if (STD_ON == GPT_CFG_CHK_NOT_STARTED)
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook ( GPT_SID_GET_TIME_ELAPSED, GPT_E_NOT_STARTED );
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
#endif /* (STD_ON == GPT_CFG_CHK_NOT_STARTED) */
    /* The timer is not running, so return 0  */
    return 0;
  }

  /* Critical section, block the interrupts */
  Gpt_GlobalSuspend();


  HWCountBlockIdx = Gpt_GetHWCountBlock (channel);

  /* load current timer values to local variables */
  switch (HWCountBlockIdx)
  {    
  case 0:
    Counter_t = GPT_READ_REGISTER_32BIT(GPT_FRC0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  case 1:
    Counter_t = GPT_READ_REGISTER_32BIT(GPT_FRC1,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  default:    /* for formal aspect */
    break;
  } /* End of switch */

  switch (HWCompBlockIdx)
  {    
  case 0:
    UpdCompare_t = GPT_READ_REGISTER_32BIT(GPT_UDCP0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    Compare_t = GPT_READ_REGISTER_32BIT(GPT_COMP0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  case 1:
    UpdCompare_t = GPT_READ_REGISTER_32BIT(GPT_UDCP1,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    Compare_t = GPT_READ_REGISTER_32BIT(GPT_COMP1,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  case 2:
    UpdCompare_t = GPT_READ_REGISTER_32BIT(GPT_UDCP2,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    Compare_t = GPT_READ_REGISTER_32BIT(GPT_COMP2,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  case 3:
    UpdCompare_t = GPT_READ_REGISTER_32BIT(GPT_UDCP3,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    Compare_t = GPT_READ_REGISTER_32BIT(GPT_COMP3,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  default:    /* for formal aspect */
    break;
  } /* End of switch */

  /* Critical section, restore the interrupts */
  Gpt_GlobalRestore();

  /* prepare parameter for return value */
  ChlConf_pt = &(Gpt_Config_pt->ChannelConfig_pt[channel]);
  if (!(GPT_MODE_ONESHOT == ChlConf_pt->ChannelMode_u32))
  {
    Counter_t -= (Compare_t - UpdCompare_t);
  }
  return Counter_t;

} /* Gpt_GetTimeElapsed */  /* PRQA S 2006 *//*  MD_MSR_14.7   */
#endif /* (STD_ON == GPT_CFG_USE_GET_TIME_ELAPSED) */


#if (STD_ON == GPT_TIME_REMAINING_API)
/**********************************************************************************************************************
Function name:  Gpt_GetTimeRemaining
**********************************************************************************************************************/

FUNC(Gpt_ValueType, GPT_CODE) Gpt_GetTimeRemaining( Gpt_ChannelType channel )
{
  /* local variables to store activation, timer value and counter value
  * of a timer  */
  Gpt_HWChannelType HWCompBlockIdx;
  Gpt_HWChannelType HWCountBlockIdx;
  Gpt_ValueType     Compare_t = 0;
  Gpt_ValueType     Counter_t = 0;
  /* check if the driver has been successfully initialized. If the driver
  * has not been initialized, report an error and return immediately.
  */
#if (STD_ON == GPT_CFG_CHK_UNINIT )
  if (NULL_PTR == Gpt_Config_pt )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook(GPT_SID_GET_TIME_REMAINING, GPT_E_UNINIT);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return 0;
  }
#endif /* (STD_ON == GPT_CFG_CHK_UNINIT) */

  /* Check if parameter channel is in valid range. If its value is out
  * of range report an error and return immediately.
  */
#if (  STD_ON == GPT_CFG_CHK_PARAM_CHL )
  if ( Gpt_Config_pt->ChannelCount_u32 <= channel )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook ( GPT_SID_GET_TIME_REMAINING, GPT_E_PARAM_CHANNEL );
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return 0;
  }
#endif /* (STD_ON == GPT_CFG_CHK_PARAM_CHL) */

  /* Get the hardware channel */
  HWCompBlockIdx = Gpt_GetHWChannel ( channel );

  /* Make sure the timer is running now */
  if (0 == ( Gpt_ActiveMap_u32 & (1U << HWCompBlockIdx) ))
  {
#if (STD_ON == GPT_CFG_CHK_NOT_STARTED)
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook ( GPT_SID_GET_TIME_REMAINING, GPT_E_NOT_STARTED );
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
#endif /* (STD_ON == GPT_CFG_CHK_NOT_STARTED) */
    /* The timer is not running, so return 0  */
    return 0;
  }

  /* Critical section, block the interrupts */
  Gpt_GlobalSuspend();


  HWCountBlockIdx = Gpt_GetHWCountBlock (channel);

  /* load current timer values to local variables */
  switch (HWCountBlockIdx)
  {    
  case 0:
    Counter_t = GPT_READ_REGISTER_32BIT(GPT_FRC0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  case 1:
    Counter_t = GPT_READ_REGISTER_32BIT(GPT_FRC1,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  default:    /* for formal aspect */
    break;
  } /* End of switch */

  switch (HWCompBlockIdx)
  {    
  case 0:
    Compare_t = GPT_READ_REGISTER_32BIT(GPT_COMP0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  case 1:
    Compare_t = GPT_READ_REGISTER_32BIT(GPT_COMP1,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  case 2:
    Compare_t = GPT_READ_REGISTER_32BIT(GPT_COMP2,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  case 3:
    Compare_t = GPT_READ_REGISTER_32BIT(GPT_COMP3,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  default:    /* for formal aspect */
    break;
  } /* End of switch */


  /* Critical section, restore the interrupts */
  Gpt_GlobalRestore();

  /* prepare parameter for return value */
  Counter_t = Compare_t - Counter_t;
  return Counter_t;

} /* Gpt_GetTimeRemaining */ /* PRQA S 2006 *//*  MD_MSR_14.7   */
#endif /* (STD_ON == GPT_CFG_USE_GET_TIME_REMAINING) */


/**********************************************************************************************************************
Function name:  Gpt_StartTimer
**********************************************************************************************************************/

FUNC(void, GPT_CODE) Gpt_StartTimer (   Gpt_ChannelType channel,
  Gpt_ValueType value )
{
  Gpt_HWChannelType HWCompBlockIdx;
  Gpt_HWChannelType HWCountBlockIdx;
  uint32 HWChl_Mask_u32 ;
  uint32 HWCount_Mask_u32 ;
  uint32 Chl_Mode_u32 ;
  /* Check if the driver has been successfully initialized. If the driver
  * has not been initialized, report an error and return immediately.
  */
#if (STD_ON == GPT_CFG_CHK_UNINIT)
  if (NULL_PTR == Gpt_Config_pt)
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook(GPT_SID_START_TIMER, GPT_E_UNINIT);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return;
  }
#endif /* (STD_ON == GPT_CFG_CHK_UNINIT) */

  /* Check if parameter channel is in valid range. If its value is out
  * of range report an error and return immediately.
  */
#if (  STD_ON == GPT_CFG_CHK_PARAM_CHL )
  if ( Gpt_Config_pt->ChannelCount_u32 <= channel )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook ( GPT_SID_START_TIMER, GPT_E_PARAM_CHANNEL );
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return ;
  }
#endif /* (STD_ON == GPT_CFG_CHK_PARAM_CHL) */

  /* Check if parameter value is in valid range. If "0" is specified as
  * value, report an error and return immediately.
  */
#if (STD_ON == GPT_CFG_CHK_PARAM_VALUE)
  if ( 0 >= value )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook ( GPT_SID_START_TIMER, GPT_E_PARAM_VALUE );
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return;
  }
#endif /* GPT_CFG_CHK_PARAM_VALUE */

  /* Get the hardware channel reference */
  HWCompBlockIdx = Gpt_GetHWChannel ( channel );
  HWChl_Mask_u32 = (uint32)(1 << HWCompBlockIdx);
  Chl_Mode_u32 = Gpt_Config_pt->ChannelConfig_pt[channel].ChannelMode_u32;

  /* Critical section, block the interrupts */
  Gpt_GlobalSuspend();

  /* check if the selected timer channel is already active. in that
  * case report an error and return immediately.
  */
#if (STD_ON == GPT_CFG_CHK_BUSY)

  if ( Gpt_ActiveMap_u32 & HWChl_Mask_u32 )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook ( GPT_SID_START_TIMER, GPT_E_BUSY );
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */

    /* Critical section, restore the interrupts */
    Gpt_GlobalRestore();
    return ;
  }
#endif /* (STD_ON == GPT_CFG_CHK_BUSY) */

  /* Assign notification index for single or continuous timer channel */
  Gpt_IsrIndex_u32[HWCompBlockIdx] = Gpt_Config_pt->ChannelConfig_pt[channel].ChannelMode_u32;

  /* Mark the channel as active */
  Gpt_ActiveMap_u32 |= HWChl_Mask_u32 ;


  HWCountBlockIdx = Gpt_GetHWCountBlock (channel);
  HWCount_Mask_u32 = (uint32)(1 << HWCountBlockIdx);

  /* prepare registers */
  /* one shot timer */
  if (GPT_MODE_ONESHOT == Chl_Mode_u32)
  {
    /* enable interrupt for one shot timer (necessary to stop hardware after expire via ISR) */
    GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(GPT_RTISETINT,~0,(Gpt_ValueType)HWChl_Mask_u32,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */

    /* load register values */
    switch (HWCountBlockIdx)
    {    
    case 0:
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    case 1:
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    default:    /* for formal aspect */
      break;
    } /* End of switch */

    switch (HWCompBlockIdx)
    {    
    case 0:
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP0,value,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    case 1:
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP1,value,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    case 2:
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP2,value,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP2,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    case 3:
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP3,value,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP3,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    default:    /* for formal aspect */
      break;
    } /* End of switch */
  }
  /* continuous timer */
  else
  {
    /* load register values */
    switch (HWCountBlockIdx)
    {    
    case 0:
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    case 1:
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    default:    /* for formal aspect */
      break;
    } /* End of switch */

    switch (HWCompBlockIdx)
    {    
    case 0:
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP0,value,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP0,value,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    case 1:
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP1,value,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP1,value,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    case 2:
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP2,value,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP2,value,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    case 3:
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP3,value,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP3,value,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
      break;
    default:    /* for formal aspect */
      break;
    } /* End of switch */
  }

  /* enable channel */
  GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(GPT_RTIGCTRL,~0,(Gpt_ValueType)HWCount_Mask_u32,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */

  /* Critical section, restore the interrupts */
  Gpt_GlobalRestore();
  return;
} /* Gpt_StartTimer */ /* PRQA S 2006 *//*  MD_MSR_14.7   */


/**********************************************************************************************************************
Function name:  Gpt_StopTimer
**********************************************************************************************************************/

FUNC(void, GPT_CODE) Gpt_StopTimer ( Gpt_ChannelType channel )
{
  Gpt_HWChannelType HWCompBlockIdx;
  Gpt_HWChannelType HWCountBlockIdx;
  uint32 HWChl_Mask_u32;
  uint32 HWCount_Mask_u32;

  /* Check if the driver has been successfully initialized. If the driver
  * has not been initialized, report an error and return immediately.
  */
#if (STD_ON == GPT_CFG_CHK_UNINIT)
  if (NULL_PTR == Gpt_Config_pt)
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook(GPT_SID_STOP_TIMER, GPT_E_UNINIT);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return;
  }
#endif /* (STD_ON == GPT_CFG_CHK_UNINIT) */

  /* Check if parameter channel is in valid range. If its value is out
  * of range report an error and return immediately.
  */
#if (  STD_ON == GPT_CFG_CHK_PARAM_CHL )
  if ( Gpt_Config_pt->ChannelCount_u32 <= channel )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook ( GPT_SID_STOP_TIMER, GPT_E_PARAM_CHANNEL );
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return ;
  }
#endif /* (STD_ON == GPT_CFG_CHK_PARAM_CHL) */

  /* Get the hardware channel reference */
  HWCompBlockIdx = Gpt_GetHWChannel ( channel );
  HWChl_Mask_u32 = (uint32)(1 << HWCompBlockIdx);

  /* Critical section, block the interrupts */
  Gpt_GlobalSuspend();

  /* Mark the channel as inactive */
  Gpt_ActiveMap_u32 &= (~HWChl_Mask_u32);


  HWCountBlockIdx = Gpt_GetHWCountBlock (channel);
  HWCount_Mask_u32 = (uint32)(1 << HWCountBlockIdx);

  /* reset registers */
  GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(GPT_RTIGCTRL,(~(Gpt_ValueType)HWCount_Mask_u32),0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */

  switch (HWCountBlockIdx)
  {    
  case 0:
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  case 1:
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  default:    /* for formal aspect */
    break;
  } /* End of switch */


  /* Critical section, restore the interrupts */
  Gpt_GlobalRestore();
  return;
} /* Gpt_StopTimer */


#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)
/**********************************************************************************************************************
Function name:  Gpt_EnableNotification
**********************************************************************************************************************/

FUNC(void, GPT_CODE) Gpt_EnableNotification( Gpt_ChannelType channel )
{
  Gpt_HWChannelType HWCompBlockIdx;
  uint32 HWChl_Mask_u32 ;
#if (STD_ON == GPT_CFG_CHK_NOTIFPTR)
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONST_PBCFG) ChlConf_pt;
#endif
  /* Check if the driver has been successfully initialized. If the driver
  * has not been initialized, report an error and return immediately.
  */
#if (STD_ON == GPT_CFG_CHK_UNINIT)
  if ( NULL_PTR == Gpt_Config_pt )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook(GPT_SID_ENABLE_NOTIFY, GPT_E_UNINIT);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return;
  }
#endif /* (STD_ON == GPT_CFG_CHK_UNINIT) */

  /* Check if parameter channel is in valid range. If its value is out
  * of range report an error and return immediately.
  */
#if (STD_ON == GPT_CFG_CHK_PARAM_CHL)
  if ( Gpt_Config_pt->ChannelCount_u32 <= channel )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook ( GPT_SID_ENABLE_NOTIFY, GPT_E_PARAM_CHANNEL );
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return ;
  }
#endif /* (STD_ON == GPT_CFG_CHK_PARAM_CHL) */

  HWCompBlockIdx = Gpt_GetHWChannel ( channel );
  HWChl_Mask_u32 = (uint32)(1 << HWCompBlockIdx);

  /* Critical section, block the interrupts */
  Gpt_GlobalSuspend();

  /* Reset interrupt flag */
 GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(GPT_RTIINTFLAG,~0,(Gpt_ValueType)HWChl_Mask_u32,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */

#if (STD_ON == GPT_CFG_CHK_NOTIFPTR)
  ChlConf_pt = &(Gpt_Config_pt->ChannelConfig_pt[channel]);
  if (NULL_PTR == ChlConf_pt->Notification_pt)
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook(GPT_SID_ENABLE_NOTIFY, GPT_E_NOTIFY_NULL);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */

    /* Critical section, restore the interrupts */
    Gpt_GlobalRestore();
    return;
  }
#endif /* (STD_ON == GPT_CFG_CHK_NOTIFPTR) */        

  /* Mark the notification for this channel */
  Gpt_ChannelNotifyMatrix_u32 |= HWChl_Mask_u32;
  /* Enable interrupt */
 GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(GPT_RTISETINT,~0,(Gpt_ValueType)HWChl_Mask_u32,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */

  /* Critical section, restore the interrupts */
  Gpt_GlobalRestore();

  return;
} /* Gpt_EnableNotification */ /* PRQA S 2006 *//*  MD_MSR_14.7   */
#endif /* GPT_ENABLE_DISABLE_NOTIFICATION_API */


#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)
/**********************************************************************************************************************
Function name:  Gpt_DisableNotification
**********************************************************************************************************************/

FUNC(void, GPT_CODE) Gpt_DisableNotification( Gpt_ChannelType channel )
{
  Gpt_HWChannelType HWCompBlockIdx;
  uint32 HWChl_Mask_u32 ;
  uint32 Chl_Mode_u32 ;
  /* Check if the driver has been successfully initialized. If the driver
  * has not been initialized, report an error and return immediately.
  */
#if (STD_ON == GPT_CFG_CHK_UNINIT)
  if ( NULL_PTR == Gpt_Config_pt )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook(GPT_SID_DISABLE_NOTIFY, GPT_E_UNINIT);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return;
  }
#endif /* (STD_ON == GPT_CFG_CHK_UNINIT) */

  /* Check if parameter channel is in valid range. If its value is out
  * of range report an error and return immediately.
  */
#if (STD_ON == GPT_CFG_CHK_PARAM_CHL)
  if ( Gpt_Config_pt->ChannelCount_u32 <= channel )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook ( GPT_SID_DISABLE_NOTIFY, GPT_E_PARAM_CHANNEL );
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return ;
  }
#endif /* (STD_ON == GPT_CFG_CHK_PARAM_CHL) */

  HWCompBlockIdx = Gpt_GetHWChannel ( channel );
  HWChl_Mask_u32 = (uint32)(1 << HWCompBlockIdx) ;
  Chl_Mode_u32 = Gpt_Config_pt->ChannelConfig_pt[channel].ChannelMode_u32;

  /* Critical section, block the interrupts */
  Gpt_GlobalSuspend();

  /* Mark the notification for this channel */
  Gpt_ChannelNotifyMatrix_u32 &= (~HWChl_Mask_u32);

  /* Disable interrupt for one shot timer */
  if (GPT_MODE_ONESHOT != Chl_Mode_u32)
  {
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_RTICLEARINT,(Gpt_ValueType)HWChl_Mask_u32,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
  }

  /* Critical section, restore the interrupts */
  Gpt_GlobalRestore();
  return;
} /* Gpt_DisableNotification */ /* PRQA S 2006 *//*  MD_MSR_14.7   */
#endif /* GPT_ENABLE_DISABLE_NOTIFICATION_API */


#if (STD_ON == GPT_WAKEUP_FUNCTIONALITY_API)
/**********************************************************************************************************************
Function name:  Gpt_SetMode
**********************************************************************************************************************/

FUNC(void, GPT_CODE) Gpt_SetMode ( Gpt_ModeType mode )
{
  /* Check if the driver has been successfully initialized. If the driver
  * has not been initialized, report an error and return immediately.
  */
#if (STD_ON == GPT_CFG_CHK_UNINIT)
  if ( NULL_PTR == Gpt_Config_pt )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook(GPT_SID_SET_MODE, GPT_E_UNINIT);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return;
  }
#endif /* (STD_ON == GPT_CFG_CHK_UNINIT) */

  /* Check if the mode parameter is valid. If not report an error and return immediately */
#if (STD_ON == GPT_CFG_CHK_PARAM_MODE)
  if (( GPT_MODE_SLEEP != mode ) && ( GPT_MODE_NORMAL != mode )) /* PRQA S 3356 *//*  MISRA-C:2004 Rules applicable to message 3356: This value would be true in case of an illegal value  *//* PRQA S 3359 *//*  MISRA-C:2004 Rules applicable to message 3359: This if conditions checks for wrong mode parameters  */
  { /* PRQA S 3201 *//*  MISRA-C:2004 Rules applicable to message 3201: This code section will be used in case of wrong mode parameter  */
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook ( GPT_SID_SET_MODE, GPT_E_PARAM_MODE );
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return ;
  }
#endif

  if ( GPT_MODE_SLEEP == mode )
  {
    /* Setting to sleep mode already done before? */
    if ( GPT_MODE_SLEEP == Gpt_SleepMode_t )
    {
      return;
    }
    else
    {
      /* Perform the sleep sequence */
      Gpt_ChannelType ChannelIdx;

      for ( ChannelIdx = 0; ChannelIdx < Gpt_Config_pt->ChannelCount_u32; ChannelIdx ++ )
      {
        Gpt_HWChannelType HWCompBlockIdx;
        uint32 HWChl_Mask_u32;

        HWCompBlockIdx = Gpt_GetHWChannel ( ChannelIdx );
        HWChl_Mask_u32 = (uint32)(1 << HWCompBlockIdx);

        if ( Gpt_ChannelWakeupMatrix_u32 & HWChl_Mask_u32 )
        {
          /* This channel is configured as wakeup enabled */
          /* Assign wakeup index for this timer channel depending on channel mode */
          if (GPT_MODE_ONESHOT == Gpt_Config_pt->ChannelConfig_pt[ChannelIdx].ChannelMode_u32)
          {
            /* one shot timer channel */
            Gpt_IsrIndex_u32[HWCompBlockIdx] = GPT_MODE_ONESHOT_WAKEUP;
          }
          else
          {
            /* continuous timer channel */
            Gpt_IsrIndex_u32[HWCompBlockIdx] = GPT_MODE_CONT_WAKEUP;
          }
          /* Enable the Interrupt for this channel */

          /* Critical section, block the interrupts */   
          Gpt_GlobalSuspend();


          GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(GPT_RTISETINT,~0,(Gpt_ValueType)HWChl_Mask_u32,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */

          /* Critical section, restore the interrupts */
          Gpt_GlobalRestore();

        }
        else
        {
          Gpt_HWChannelType HWCountBlockIdx;
          uint32 HWCount_Mask_u32;

          /* Critical section, block the interrupts */ 
          Gpt_GlobalSuspend();

          /* Mark the channel as inactive */
          Gpt_ActiveMap_u32 &= (~HWChl_Mask_u32);

          /* Reset registers and interrupt */

          HWCountBlockIdx = Gpt_GetHWCountBlock (ChannelIdx);
          HWCount_Mask_u32 = (uint32)(1 << HWCountBlockIdx);

          GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(GPT_RTIGCTRL,(~(Gpt_ValueType)HWCount_Mask_u32),0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */

          switch (HWCountBlockIdx)
          {    
          case 0:
            GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
            GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
            break;
          case 1:
            GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
            GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
            break;
          default:    /* for formal aspect */
            break;
          } /* End of switch */

        GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_RTICLEARINT, (Gpt_ValueType)HWChl_Mask_u32,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */


          /* Critical section, restore the interrupts */
          Gpt_GlobalRestore();

        } /* End of if-else ( Gpt_ChannelWakeupMatrix_u32 & HWChl_Mask_u32 ) */
      } /* End of for */

      /* Set marker for sleep mode */
      Gpt_SleepMode_t = GPT_MODE_SLEEP;
    } /* End of if-else (GPT_MODE_SLEEP == Gpt_SleepMode_t) */
  } /* End of if (GPT_MODE_SLEEP == mode) */

  else /* Mode == GPT_MODE_NORMAL */
  {
    /* Setting to normal mode already done before? */
    if ( GPT_MODE_NORMAL == Gpt_SleepMode_t )
    {
      return;
    }
    else
    {
      /* Perform the wakeup sequence */
      Gpt_ChannelType ChannelIdx;

      for ( ChannelIdx = 0; ChannelIdx < Gpt_Config_pt->ChannelCount_u32; ChannelIdx ++ )
      {
        Gpt_HWChannelType HWCompBlockIdx ;
        uint32 HWChl_Mask_u32 ;

        HWCompBlockIdx = Gpt_GetHWChannel ( ChannelIdx );
        HWChl_Mask_u32 = (uint32)(1 << HWCompBlockIdx);

        /* Notification enabled for this channel? */
#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)/*ECO_IGNORE_LINE*/ 
        if ( Gpt_ChannelNotifyMatrix_u32 & HWChl_Mask_u32 )
        {
          Gpt_HWChannelType HWCountBlockIdx;
          uint32 HWCount_Mask_u32;

          /* Critical section, block the interrupts */
          Gpt_GlobalSuspend();


          /* Disable timer for the timers which were enabled at wakeup time */
          /* Mark the channel as inactive */
          Gpt_ActiveMap_u32 &= (~HWChl_Mask_u32);

          /* Reset registers*/


          HWCountBlockIdx = Gpt_GetHWCountBlock (ChannelIdx);
          HWCount_Mask_u32 = (uint32)(1 << HWCountBlockIdx);

          GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(GPT_RTIGCTRL,(~(Gpt_ValueType)HWCount_Mask_u32),0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */

          switch (HWCountBlockIdx)
          {    
          case 0:
            GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
            GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
            break;
          case 1:
            GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
            GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
            break;
          default:    /* for formal aspect */
            break;
          } /* End of switch */

          /* For this channel the notification is enabled */
          /* So enable the Interrupt for this channel */
          GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(GPT_RTISETINT,~0,(Gpt_ValueType)HWChl_Mask_u32,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */

          /* Critical section, restore the interrupts */
          Gpt_GlobalRestore();

        }
        else /* Notification is disabled for this channel */
#endif /* (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API) */ /*ECO_IGNORE_LINE*/ 
        {
          Gpt_HWChannelType HWCountBlockIdx;
          uint32 HWCount_Mask_u32;

          /* Critical section, block the interrupts */
          Gpt_GlobalSuspend();


          /* Mark the channel as inactive */
          Gpt_ActiveMap_u32 &= (~HWChl_Mask_u32);

          /* Reset registers */

          HWCountBlockIdx = Gpt_GetHWCountBlock (ChannelIdx);
          HWCount_Mask_u32 = (uint32)(1 << HWCountBlockIdx);

          GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(GPT_RTIGCTRL,(~(Gpt_ValueType)HWCount_Mask_u32),0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */

          switch (HWCountBlockIdx)
          {    
          case 0:
            GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
            GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
            break;
          case 1:
            GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
            GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
            break;
          default:    /* for formal aspect */
            break;
          } /* End of switch */

          /* Disable the Interrupt for this channel */
          GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_RTICLEARINT, (Gpt_ValueType)HWChl_Mask_u32,OS_MEM_AREA_RTI);

          /* Critical section, restore the interrupts */
          Gpt_GlobalRestore();
        } /* End of if-else ( Gpt_ChannelNotifyMatrix_u32 & HWChl_Mask_u32 ) */
      } /* End of for */

      /* Set marker for normal mode */
      Gpt_SleepMode_t = GPT_MODE_NORMAL;
    } /* End of if-else (GPT_MODE_NORMAL == Gpt_SleepMode_t) */
  } /* End of if-else (GPT_MODE_NORMAL == mode) */
  return;
} /* Gpt_SetMode */ /* PRQA S 2006 *//*  MD_MSR_14.7   */
#endif /* GPT_WAKEUP_FUNCTIONALITY_API */


#if (STD_ON == GPT_WAKEUP_FUNCTIONALITY_API)
/**********************************************************************************************************************
Function name:  Gpt_DisableWakeup
**********************************************************************************************************************/

FUNC(void, GPT_CODE) Gpt_DisableWakeup ( Gpt_ChannelType channel )
{
#if (STD_ON == GPT_CFG_CHK_PARAM_WAKEUPCHL)
  /* local variable to store channel configuration pointer */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONST_PBCFG) ChlConf_pt;
#endif
  /* Check if the driver has been successfully initialized. If the driver
  * has not been initialized, report an error and return immediately.
  */
#if (STD_ON == GPT_CFG_CHK_UNINIT)
  if ( NULL_PTR == Gpt_Config_pt )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook(GPT_SID_DISABLE_WAKEUP, GPT_E_UNINIT);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return;
  }
#endif /* (STD_ON == GPT_CFG_CHK_UNINIT) */

  /* Check if parameter channel is in valid range. If its value is out
  * of range report an error and return immediately.
  */
#if (STD_ON == GPT_CFG_CHK_PARAM_CHL)
  if ( Gpt_Config_pt->ChannelCount_u32 <= channel )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook ( GPT_SID_DISABLE_WAKEUP, GPT_E_PARAM_CHANNEL );
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return ;
  }
#endif /* (STD_ON == GPT_CFG_CHK_PARAM_CHL) */

  /* Check if channel is wakeup capable (reference ID != 0). If not report an error and return immediately. */
#if (STD_ON == GPT_CFG_CHK_PARAM_WAKEUPCHL)
  ChlConf_pt = &(Gpt_Config_pt->ChannelConfig_pt[channel]);
  if (0 == ChlConf_pt->WakeupSourceID)
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook ( GPT_SID_DISABLE_WAKEUP, GPT_E_PARAM_WAKEUPCHL );
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return ;
  }
#endif /* (STD_ON == GPT_CFG_CHK_PARAM_WAKEUPCHL) */

  /* Critical section, block the interrupts */
  Gpt_GlobalSuspend();


  /* Mark channel in wakeup matrix */
  Gpt_ChannelWakeupMatrix_u32 &= (~( 1u << Gpt_GetHWChannel (channel)));

  /* Critical section, restore the interrupts */
  Gpt_GlobalRestore();
  return ;
} /* Gpt_DisableWakeup */
#endif /* (STD_ON == GPT_WAKEUP_FUNCTIONALITY_API) */


#if (STD_ON == GPT_WAKEUP_FUNCTIONALITY_API)
/**********************************************************************************************************************
Function name:  Gpt_EnableWakeup
**********************************************************************************************************************/

FUNC(void, GPT_CODE) Gpt_EnableWakeup ( Gpt_ChannelType channel )
{
#if (STD_ON == GPT_CFG_CHK_PARAM_CHL)
  /* local variable to store channel configuration pointer */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONST_PBCFG) ChlConf_pt;
#endif
  /* Check if the driver has been successfully initialized. If the driver
  * has not been initialized, report an error and return immediately.
  */
#if (STD_ON == GPT_CFG_CHK_UNINIT)
  if ( NULL_PTR == Gpt_Config_pt )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook(GPT_SID_ENABLE_WAKEUP, GPT_E_UNINIT);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return;
  }
#endif /* (STD_ON == GPT_CFG_CHK_UNINIT) */

  /* Check if parameter channel is in valid range. If its value is out
  * of range report an error and return immediately.
  */
#if (STD_ON == GPT_CFG_CHK_PARAM_CHL)
  if ( Gpt_Config_pt->ChannelCount_u32 <= channel )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook ( GPT_SID_ENABLE_WAKEUP, GPT_E_PARAM_CHANNEL );
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return ;
  }
#endif /* (STD_ON == GPT_CFG_CHK_PARAM_CHL) */

  /* Check if channel is wakeup capable (reference ID != 0). If not report an error and return immediately. */
#if (STD_ON == GPT_CFG_CHK_PARAM_WAKEUPCHL)
  ChlConf_pt = &(Gpt_Config_pt->ChannelConfig_pt[channel]);
  if (0 == ChlConf_pt->WakeupSourceID)
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook ( GPT_SID_ENABLE_WAKEUP, GPT_E_PARAM_WAKEUPCHL );
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return ;
  }
#endif /* (STD_ON == GPT_CFG_CHK_PARAM_WAKEUPCHL) */

  /* Critical section, block the interrupts */
  Gpt_GlobalSuspend();

  /* Mark channel in wakeup matrix */
  Gpt_ChannelWakeupMatrix_u32 |= ( 1u << Gpt_GetHWChannel (channel));

  /* Critical section, restore the interrupts */
  Gpt_GlobalRestore();
  return ;
} /* Gpt_EnableWakeup */ /* PRQA S 2006 *//*  MD_MSR_14.7   */
#endif /* (STD_ON == GPT_WAKEUP_FUNCTIONALITY_API) */


#if (STD_ON == GPT_WAKEUP_FUNCTIONALITY_API)
/**********************************************************************************************************************
Function name:  Gpt_Cbk_CheckWakeup
**********************************************************************************************************************/

FUNC(void, GPT_CODE) Gpt_Cbk_CheckWakeup ( EcuM_WakeupSourceType wakeupSource )
{
  /* Variables for configured wakeup sources and channel configuration pointer and
  * numeric ID of the GPT channel
  */
  Gpt_HWChannelType HWCompBlockIdx ;
  uint32 HWChl_Mask_u32;
  Gpt_ChannelType ChannelIdx;
  EcuM_WakeupSourceType ChlWakeupID_t = 0;
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONST_PBCFG) ChlConf_pt;

  /* Check if the driver has been successfully initialized. If the driver
  * has not been initialized, report an error and return immediately.
  */
#if (STD_ON == GPT_CFG_CHK_UNINIT)
  if ( NULL_PTR == Gpt_Config_pt )
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook(GPT_SID_CBK_CHECK_WAKEUP, GPT_E_UNINIT);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return;
  }
#endif /* (STD_ON == GPT_CFG_CHK_UNINIT) */

  /* Check if wakeupSource is valid (reference ID != 0) */
  if (0 == wakeupSource)
  {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook(GPT_SID_CBK_CHECK_WAKEUP, GPT_E_WAKEUP_VALIDATION);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return;
  }

  /* -------------------- Loop over all channels ----------------------------------------
  * Check if delivered wakeupSource comes from configured wakeup capable timer channel
  */
  for ( ChannelIdx = 0; ChannelIdx < Gpt_Config_pt->ChannelCount_u32; ChannelIdx ++ )
  {
    ChlConf_pt = &(Gpt_Config_pt->ChannelConfig_pt[ChannelIdx]);
    ChlWakeupID_t = (EcuM_WakeupSourceType)(ChlConf_pt->WakeupSourceID);
    if (wakeupSource == ChlWakeupID_t)
    {
      /* configured wakeup capable timer found; leave loop */
      break;
    }
  } /* End of for */

  /* Check if configured wakeup capable timer was found */
  if ( Gpt_Config_pt->ChannelCount_u32 <= ChannelIdx )
  {
    /* no wakeup capable timer found */
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
    Gpt_Errorhook(GPT_SID_CBK_CHECK_WAKEUP, GPT_E_WAKEUP_VALIDATION);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
    return;
  }
  else
  {
    /* Check if delivered wakeupSource comes from wakeup enabled timer channel */
    HWCompBlockIdx = Gpt_GetHWChannel ( ChannelIdx );
    HWChl_Mask_u32 = (uint32)(1 << HWCompBlockIdx);

    if (0 == ( Gpt_ChannelWakeupMatrix_u32 & HWChl_Mask_u32 ))
    {
#if (STD_ON == GPT_CFG_DEBUG_REPORTING)
      Gpt_Errorhook(GPT_SID_CBK_CHECK_WAKEUP, GPT_E_WAKEUP_VALIDATION);
#endif  /* (STD_ON == GPT_CFG_DEBUG_REPORTING) */
      return;
    }
  }

  /* Check if valid wakeupSource was found */
  if (ChlWakeupID_t)
  {    
#if (STD_ON == GPT_REPORT_WAKEUP_SOURCE)
    EcuM_SetWakeupEvent (ChlWakeupID_t);
#endif /* (STD_ON == GPT_REPORT_WAKEUP_SOURCE) */
  }
  return;
} /* Gpt_Cbk_CheckWakeup */ /* PRQA S 2006 *//*  MD_MSR_14.7   */
#endif /* (STD_ON == GPT_WAKEUP_FUNCTIONALITY_API) */


/**********************************************************************************************************************
Function name:  Gpt_NotifContIsr
**********************************************************************************************************************/

FUNC(void, GPT_CODE) Gpt_NotifContIsr( Gpt_HWChannelType HWChannel_t )
{
  Gpt_ChannelType ChannelIdx;
  uint32 HWChl_Mask_u32;
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONST_PBCFG) ChlConf_pt;



  HWChl_Mask_u32 = (uint32)(1 << HWChannel_t);

  /* Critical section, block the interrupts */
  Gpt_GlobalSuspend();

GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(GPT_RTIINTFLAG,~0,(Gpt_ValueType)HWChl_Mask_u32,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */

  /* Critical section, restore the interrupts */
  Gpt_GlobalRestore();

  ChannelIdx = Gpt_GetLogicalChannel(HWChannel_t);
  ChlConf_pt = &(Gpt_Config_pt->ChannelConfig_pt[ChannelIdx]);

  if ( NULL_PTR != ( ChlConf_pt->Notification_pt ))
  {
    /* Call notification callback */
    ChlConf_pt->Notification_pt ();
  }
  return;

} /* Gpt_NotifContIsr */


/**********************************************************************************************************************
Function name:  Gpt_NotifSingleIsr
**********************************************************************************************************************/

FUNC(void, GPT_CODE) Gpt_NotifSingleIsr( Gpt_HWChannelType HWChannel_t )
{
  uint32 HWChl_Mask_u32;
  uint32 HWCount_Mask_u32;
  Gpt_ChannelType ChannelIdx;
  Gpt_HWChannelType HWCountBlockIdx;


  HWChl_Mask_u32 = (uint32)(1 << HWChannel_t);

  /* Critical section, block the interrupts */
  Gpt_GlobalSuspend();

  /* Mark the channel as inactive */
  Gpt_ActiveMap_u32 &= (~HWChl_Mask_u32);


  ChannelIdx = Gpt_GetLogicalChannel(HWChannel_t);
  HWCountBlockIdx = Gpt_GetHWCountBlock (ChannelIdx);
  HWCount_Mask_u32 = (uint32)(1 << HWCountBlockIdx);

  /* reset registers */
  GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(GPT_RTIGCTRL,(~(Gpt_ValueType)HWCount_Mask_u32),0,OS_MEM_AREA_RTI);

  switch (HWChannel_t)
  {    
  case 0:
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  case 1:
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  case 2:
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP2,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP2,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  case 3:
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP3,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP3,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  default:    /* for formal aspect */
    break;
  } /* End of switch */

  switch (HWCountBlockIdx)
  {    
  case 0:
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  case 1:
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  default:    /* for formal aspect */
    break;
  } /* End of switch */

  /* Clear interrupt flag as no notification shall arise */
#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API) /*ECO_IGNORE_LINE*/
  if (0 == ( Gpt_ChannelNotifyMatrix_u32 & HWChl_Mask_u32 ))
  {
  GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(GPT_RTIINTFLAG,~0,(Gpt_ValueType)HWChl_Mask_u32,OS_MEM_AREA_RTI);

    /* Critical section, restore the interrupts */
    Gpt_GlobalRestore();
  }
  /* Serve handler for notification function call */
  else
#endif /*ECO_IGNORE_LINE*/
  {
    /* Critical section, restore the interrupts */
    Gpt_GlobalRestore();

    Gpt_NotifContIsr ( HWChannel_t );
  }
  return;
} /* Gpt_NotifSingleIsr */


/**********************************************************************************************************************
Function name:  Gpt_WakeupContIsr
**********************************************************************************************************************/

FUNC(void, GPT_CODE) Gpt_WakeupContIsr( Gpt_HWChannelType HWChannel_t )
{
#if (STD_ON == GPT_REPORT_WAKEUP_SOURCE)
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONST_PBCFG) ChlConf_pt;
  Gpt_ChannelType ChannelIdx;
#endif
  uint32 HWChl_Mask_u32;

  HWChl_Mask_u32 = (uint32)(1 << HWChannel_t);

  /* Critical section, block the interrupts */
  Gpt_GlobalSuspend();

 GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(GPT_RTIINTFLAG,~0,(Gpt_ValueType)HWChl_Mask_u32,OS_MEM_AREA_RTI);

  /* Critical section, restore the interrupts */
  Gpt_GlobalRestore();

#if (STD_ON == GPT_REPORT_WAKEUP_SOURCE)
  ChannelIdx = Gpt_GetLogicalChannel(HWChannel_t);
  ChlConf_pt = &(Gpt_Config_pt->ChannelConfig_pt[ChannelIdx]);

  /* Inform EcuM about wakeup source */
  EcuM_CheckWakeup (ChlConf_pt->WakeupSourceID);
#endif /* (STD_ON == GPT_REPORT_WAKEUP_SOURCE) */
  return;
} /* Gpt_WakeupContIsr */


/**********************************************************************************************************************
Function name:  Gpt_WakeupSingleIsr
**********************************************************************************************************************/

FUNC(void, GPT_CODE) Gpt_WakeupSingleIsr( Gpt_HWChannelType HWChannel_t )
{
  uint32 HWChl_Mask_u32;
  uint32 HWCount_Mask_u32;
  Gpt_ChannelType ChannelIdx;
  Gpt_HWChannelType HWCountBlockIdx;
  HWChl_Mask_u32 = (uint32)(1 << HWChannel_t);

  /* Critical section, block the interrupts */
  Gpt_GlobalSuspend();

  /* Mark the channel as inactive */
  Gpt_ActiveMap_u32 &= (~HWChl_Mask_u32);


  ChannelIdx = Gpt_GetLogicalChannel(HWChannel_t);
  HWCountBlockIdx = Gpt_GetHWCountBlock (ChannelIdx);
  HWCount_Mask_u32 = (uint32)(1 << HWCountBlockIdx);

  /* reset registers */
  GPT_MODIFY_REGISTER_32BIT_SUPERVISOR(GPT_RTIGCTRL,(~(Gpt_ValueType)HWCount_Mask_u32),0,OS_MEM_AREA_RTI);

  switch (HWChannel_t)
  {    
  case 0:
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  case 1:
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  case 2:
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP2,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP2,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  case 3:
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UDCP3,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_COMP3,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  default:    /* for formal aspect */
    break;
  } /* End of switch */

  switch (HWCountBlockIdx)
  {    
  case 0:
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC0,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  case 1:
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_UC1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    GPT_WRITE_REGISTER_32BIT_SUPERVISOR(GPT_FRC1,0,OS_MEM_AREA_RTI); /* PRQA S 303 */ /* MD_Gpt_303 */
    break;
  default:    /* for formal aspect */
    break;
  } /* End of switch */

  /* Critical section, restore the interrupts */
  Gpt_GlobalRestore();

  Gpt_WakeupContIsr ( HWChannel_t );
  return;
} /* Gpt_WakeupSingleIsr */


#define GPT_STOP_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************
*  END OF FILE: Gpt.c
*********************************************************************************************************************/
