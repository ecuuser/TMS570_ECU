/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2007 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Compiler.h
 *    Component:  -
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  This file provides the AUTOSAR compiler abstraction for the TI TMS470 Code generation Tools (Compiler)
 *                   Supported compiler:           TMS470 Code generation Tools
 *                   Supported compiler version:   4.4.3 and 4.4.4
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  MISRA VIOLATIONS
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Joachim Kalmbach              Jk            Vector Informatik
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2007-08-09  Jk                    Initial creation
 *  01.00.01  2007-10-22  kbr                   customized for TI TMS570
 *  01.00.02  2007-11-27  Jk                    Version defines for CFG management added
 *  01.01.00  2009-05-19  Ht                    Support ASR 3.0
 *********************************************************************************************************************/

#ifndef COMPILER_H
#define COMPILER_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "Compiler_Cfg.h"



/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : CommonAsr_Tms470 CQComponent : Impl_CompAbstract_TexasInstruments */
#define COMMONASR_TMS470_IMPL_COMPABSTRACT_VERSION 0x0101
#define COMMONASR_TMS470_IMPL_COMPABSTRACT_RELEASE_VERSION 0x00

#define COMPILER_VENDOR_ID    30u

/* AUTOSAR Software Specification Version Information */
#define COMPILER_AR_MAJOR_VERSION       (2u)
#define COMPILER_AR_MINOR_VERSION       (0u)
#define COMPILER_AR_PATCH_VERSION       (1u)

/* Component Version Information */
#define COMPILER_SW_MAJOR_VERSION       (1u)
#define COMPILER_SW_MINOR_VERSION       (1u)
#define COMPILER_SW_PATCH_VERSION       (0u)


#define _TEXAS_INSTRUMENTS_C_TMS470_

/* AUTOMATIC used for the declaration of local pointers */
#define AUTOMATIC

/* TYPEDEF shall be used within type definitions, where no memory qualifier can be specified.*/
#define TYPEDEF
/*_STATIC_ define for abstraction of compiler keyword static*/
#define STATIC     static

/*NULL_PTR define with a void pointer to zero definition*/
#ifndef NULL_PTR
   #define NULL_PTR  ((void *)0)
#endif

/*_INLINE_ define for abstraction of the keyword inline*/
#define INLINE __inline


/* FUNC macro for the declaration and definition of functions, that ensures correct syntax of function declarations
   rettype     return type of the function
   memclass    classification of the function itself*/
#define FUNC(rettype, memclass) rettype

/* P2VAR macro for the declaration and definition of pointers in RAM, pointing to variables
   ptrtype     type of the referenced variable memclass
   memclass    classification of the pointer’s variable itself
   ptrclass    defines the classification of the pointer’s distance
 */
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype*

/* P2CONST macro for the declaration and definition of pointers in RAM pointing to constants
   ptrtype     type of the referenced data
   memclass    classification of the pointer's variable itself
   ptrclass    defines the classification of the pointer's distance
 */
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype*

/* CONSTP2VAR macro for the declaration and definition of constant pointers accessing variables
   ptrtype     type of the referenced data
   memclass    classification of the pointer's variable itself
   ptrclass    defines the classification of the pointer's distance
 */
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype *const

/* CONSTP2CONST macro for the declaration and definition of constant pointers accessing constants
   ptrtype     type of the referenced data
   memclass    classification of the pointer's variable itself
   ptrclass    defines the classification of the pointer's distance
 */
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype *const

/* P2FUNC macro for the type definition of pointers to functions
   rettype     return type of the function
   ptrclass    defines the classification of the pointer's distance
   fctname     function name respectivly name of the defined type
 */
#define P2FUNC(rettype, ptrclass, fctname) rettype (* fctname)

/* CONST macro for the declaration and definition of constants
   type        type of the constant
   memclass    classification of the constant itself
 */
#define CONST(type, memclass) const type

/* VAR macro for the declaration and definition of variables
   vartype        type of the variable
   memclass    classification of the variable itself
 */
#define VAR(vartype, memclass) vartype


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif  /* COMPILER_H */

/**********************************************************************************************************************
 *  END OF FILE: Compiler.h
 *********************************************************************************************************************/
/************   Organi, Version 3.9.0 Vector-Informatik GmbH  ************/
