/*************************************************************************************
*   FILE:           T1_baseConfig.h
*
*   DESCRIPTION:    T1 base configuration fragment
*
*   VISIBILITY:     extern
*
*   $Author: nick $
*
*   $Revision: 11277 $
*
*   $URL: https://gliwa.com/svn/repos/T1target/trunk/src/T1.base/src/all/T1_baseConfig.h $
*
*   Copyright:      Gliwa GmbH | know- how in embedded software
*                   Weilheim i.OB.
*                   All rights reserved
*************************************************************************************/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_BASE

#   define T1_START_SEC_CONST_8
#   include "T1_MemMap.h"
const T1_uint8_t        T1_CAT( T1_bid_, T1_BUILD_ID ) T1_SEC_CONST_8 = 0u;
#   if !defined T1_NOF_CORES
const T1_uint8_t        T1_32BitCoreWith16BitTimer T1_SEC_CONST_8 = T1_32BIT_CPU_SMALLER_TIMER_CORE0;
const T1_uint8_t        T1_traceTimerCountsDown T1_SEC_CONST_8 = T1_TRACE_TIMER_COUNTS_DOWN_CORE0;
#   elif 1 == T1_NOF_CORES
const T1_uint8_t        T1_32BitCoreWith16BitTimerPC[] T1_SEC_CONST_8 =
    { T1_32BIT_CPU_SMALLER_TIMER_CORE0 };
const T1_uint8_t        T1_traceTimerCountsDownPC[] T1_SEC_CONST_8 =
    { T1_TRACE_TIMER_COUNTS_DOWN_CORE0 };
#   elif 2 == T1_NOF_CORES
const T1_uint8_t        T1_32BitCoreWith16BitTimerPC[] T1_SEC_CONST_8 =
    { T1_32BIT_CPU_SMALLER_TIMER_CORE0, T1_32BIT_CPU_SMALLER_TIMER_CORE1 };
const T1_uint8_t        T1_traceTimerCountsDownPC[] T1_SEC_CONST_8 =
    { T1_TRACE_TIMER_COUNTS_DOWN_CORE0, T1_TRACE_TIMER_COUNTS_DOWN_CORE1 };
#   elif 3 == T1_NOF_CORES
const T1_uint8_t        T1_32BitCoreWith16BitTimerPC[] T1_SEC_CONST_8 =
    { T1_32BIT_CPU_SMALLER_TIMER_CORE0, T1_32BIT_CPU_SMALLER_TIMER_CORE1, T1_32BIT_CPU_SMALLER_TIMER_CORE2 };
const T1_uint8_t        T1_traceTimerCountsDownPC[] T1_SEC_CONST_8 =
    { T1_TRACE_TIMER_COUNTS_DOWN_CORE0, T1_TRACE_TIMER_COUNTS_DOWN_CORE1 , T1_TRACE_TIMER_COUNTS_DOWN_CORE2 };
#   else
#       error T1_NOF_CORES too large
#   endif /* T1_NOF_CORES */
const T1_uint8_t        T1_sid T1_SEC_CONST_8 = { T1_SID };
#   define T1_STOP_SEC_CONST_8
#   include "T1_MemMap.h"
#   define T1_START_SEC_CONST_16
#   include "T1_MemMap.h"
const T1_timeouts_t T1_timeouts T1_SEC_CONST_16 = { T1_TIMEOUT_RX, T1_TIMEOUT_TX, T1_TIMEOUT_RESPONSE };
#   define T1_STOP_SEC_CONST_16
#   include "T1_MemMap.h"
#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
const T1_uint32_t       T1_bid T1_SEC_CONST_32 = T1_CAT( T1_BUILD_ID , uL );
const T1_featureMask_t  T1_initFeatureMask T1_SEC_CONST_32 = T1_INIT_FEATURE_MASK;
T1_uint8_t const * const T1_pBid T1_SEC_CONST_32 = & T1_CAT( T1_bid_, T1_BUILD_ID );
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_BASE */
