/*************************************************************************************
*   FILE:           T1_flexInterface.h
*
*   DESCRIPTION:    T1 flex interface
*
*   VISIBILITY:     extern
*
*   $Author: nick $
*
*   $Revision: 13931 $
*
*   $URL: https://gliwa.com/svn/repos/T1target/trunk/src/T1.flex/src/all/T1_flexInterface.h $
*
*   Copyright:      Gliwa GmbH | know- how in embedded software
*                   Weilheim i.OB.
*                   All rights reserved
*************************************************************************************/

#ifndef T1_FLEX_INTERFACE_H_
#define T1_FLEX_INTERFACE_H_ (1)

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include "T1_scopeInterface.h"

/*----------------------------------------------------------------------------------*/
/*--- type definitions -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if ! defined T1_TARGET_ADDRESS_TYPE
typedef T1_uint32_t T1_pFlexAddr_t;
#endif /* defined T1_TARGET_ADDRESS_TYPE */

typedef struct
{
    T1_pFlexAddr_t begin;
    T1_pFlexAddr_t end;
} const T1_flexRange_t;

/*----------------------------------------------------------------------------------*/
/*--- macros and inline functions --------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_FLEX_PLUGIN_ID               (2u)

#if defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX
#   define T1_flexPlugin                (&T1_flexPluginStruct)

#   define T1_START_SEC_CODE
#   include "T1_MemMap.h"
T1_status_t T1_CODE T1_FlexSelfTest( void );
T1_uint8Least_t T1_CODE T1_GetFlexTestCode( void );
#   define T1_STOP_SEC_CODE
#   include "T1_MemMap.h"

#else
#   define T1_flexPlugin                (T1_DISABLED_PLUGIN)
#   define T1_FlexSelfTest( )           (T1_NOTINITIALIZED)
#   define T1_GetFlexTestCode( )        (T1_FLEX_TEST_NOINIT)
#endif

#if defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX && defined T1_COUNT_PREEMPTION
/*
 * Increment and decrement are not atomic but it does not matter because interrupts
 * leave T1_preemptionCounter unchanged.
 */
#   if (defined T1_MULTICORE || defined T1_NOF_CORES) && !defined T1_MULTICORE_CLONE
#       define T1_INCR_PREEMPTIONS( te_ )                                       \
    ( ++T1_preemptionCounterPC[T1_GetCoreIdOffset( )], ( te_ ) )
#       define T1_DECR_PREEMPTIONS( te_ )                                       \
    ( ( te_ ), --T1_preemptionCounterPC[T1_GetCoreIdOffset( )] )
#   else /* single core or clone */
#       define T1_INCR_PREEMPTIONS( te_ )   ( ++T1_preemptionCounter, ( te_ ) )
#       define T1_DECR_PREEMPTIONS( te_ )   ( ( te_ ), --T1_preemptionCounter )
#   endif /* defined T1_MULTICORE && !defined T1_MULTICORE_CLONE */
#else
#       define T1_INCR_PREEMPTIONS( te_ )   ( te_ )
#       define T1_DECR_PREEMPTIONS( te_ )   ( te_ )
#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX && defined T1_COUNT_PREEMPTION */

enum {
    T1_FLEX_TEST_OK,
    T1_FLEX_TEST_NOINIT,
    T1_FLEX_UNEXPECTED_CODE_BP,
    T1_FLEX_FAILED_CODE_BP,
    T1_FLEX_FAILED_AFTER_CODE_BP,
    T1_FLEX_WRONG_PTR_CODE_BP,
    T1_FLEX_UNEXPECTED_WRITE_BP,
    T1_FLEX_FAILED_WRITE_BP,
    T1_FLEX_WRONG_PTR_WRITE_BP,
    T1_FLEX_UNEXPECTED_READ_BP,
    T1_FLEX_FAILED_READ_BP,
    T1_FLEX_WRONG_PTR_READ_BP,
    T1_FLEX_WRONG_INTERRUPT_ENABLE,
    T1_FLEX_TARGET_INIT_FAIL
};

/*----------------------------------------------------------------------------------*/
/*--- forward declaration of optional callback -------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_START_SEC_CODE
#include "T1_MemMap.h"
void T1_CODE T1_FlexUedMTriggerOnVal(   T1_nofEntries_t afterXevents,
                                        T1_uint32_t     writtenValue    );
#define T1_STOP_SEC_CODE
#include "T1_MemMap.h"

/*----------------------------------------------------------------------------------*/
/*--- external declarations for global variables -----------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_DeclarePlugin( T1_flexPluginStruct );
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_EXTERN T1_pFlexAddr_t        * const T1_addrsPC[] T1_SEC_CONST_32;
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_NO_INIT_32
#   include "T1_MemMap.h"
T1_EXTERN T1_pFlexAddr_t                T1_addrs[] T1_SEC_NO_INIT_32;
#   define T1_STOP_SEC_NO_INIT_32
#   include "T1_MemMap.h"

#   ifdef T1_MULTICORE_CLONE
#       define T1_START_SEC_NO_INIT_16_CLONE
#       include "T1_MemMap.h"
T1_EXTERN volatile T1_uint16_t          T1_preemptionCounter T1_SEC_NO_INIT_16_CLONE;
#       define T1_STOP_SEC_NO_INIT_16_CLONE
#       include "T1_MemMap.h"
#   else /* !T1_MULTICORE_CLONE */
#       define T1_START_SEC_NO_INIT_16
#       include "T1_MemMap.h"
T1_EXTERN volatile T1_uint16_t          T1_preemptionCounter T1_SEC_NO_INIT_16;
#       define T1_STOP_SEC_NO_INIT_16
#       include "T1_MemMap.h"
#   endif /* T1_MULTICORE_CLONE */

#   define T1_START_SEC_NO_INIT_16
#   include "T1_MemMap.h"
T1_EXTERN volatile T1_uint16_t          T1_preemptionCounterPC[] T1_SEC_NO_INIT_16;
#   define T1_STOP_SEC_NO_INIT_16
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_8
#   include "T1_MemMap.h"
T1_EXTERN T1_uint8_t const              T1_nofAddrs T1_SEC_CONST_8;
T1_EXTERN T1_uint8_t const              T1_nofAddrsPC[] T1_SEC_CONST_8;
T1_EXTERN T1_uint8_t const              T1_flexDisableWithDebugger T1_SEC_CONST_8;
#   define T1_STOP_SEC_CONST_8
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_8
#   include "T1_MemMap.h"
T1_EXTERN T1_uint8_t const              T1_32852 T1_SEC_CONST_8;
#   define T1_STOP_SEC_CONST_8
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_EXTERN T1_flexRange_t                T1_33108[] T1_SEC_CONST_32;
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX */

#endif /* T1_FLEX_INTERFACE_H_ */
