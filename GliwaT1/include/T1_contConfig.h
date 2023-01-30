/*************************************************************************************
*   FILE:           T1_contConfig.h
*
*   DESCRIPTION:    T1.cont configuration fragment
*
*   VISIBILITY:     extern
*
*   $Author: nick $
*
*   $Revision: 14701 $
*
*   $URL: https://gliwa.com/svn/repos/T1target/trunk/release/ti-arm7r/interface/T1_contConfig.h $
*
*   Copyright:      Gliwa GmbH | know- how in embedded software
*                   Weilheim i.OB.
*                   All rights reserved
*************************************************************************************/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_CONT

#       define T1_START_SEC_CODE
#       include "T1_MemMap.h"
extern void T1_CODE T1_CPULOAD_CALLBACK_CORE0( T1_uint16Least_t to, T1_uint16Least_t te );
#       if defined T1_NOF_CORES
#           if 1 < T1_NOF_CORES
extern void T1_CODE T1_CPULOAD_CALLBACK_CORE1( T1_uint16Least_t to, T1_uint16Least_t te );
#           endif
#           if 2 < T1_NOF_CORES
extern void T1_CODE T1_CPULOAD_CALLBACK_CORE2( T1_uint16Least_t to, T1_uint16Least_t te );
#           endif
#       endif
#       define T1_STOP_SEC_CODE
#       include "T1_MemMap.h"

#       ifndef T1_OVERHEAD_CORE0_NS
#           error T1_OVERHEAD_CORE0_NS not defined
#       endif /* T1_OVERHEAD_CORE0_NS */
#       ifndef T1_FLEX_OVERHEAD_CORE0_NS
#           error T1_FLEX_OVERHEAD_CORE0_NS not defined
#       endif /* T1_FLEX_OVERHEAD_CORE0_NS */
#       ifndef T1_CPULOAD_TX_PERIOD_CORE0
#           error T1_CPULOAD_TX_PERIOD_CORE0 not defined
#       endif /* T1_CPULOAD_TX_PERIOD_CORE0 */
#       ifndef T1_CPULOAD_SAMPLES_CORE0
#           error T1_CPULOAD_SAMPLES_CORE0 not defined
#       endif /* T1_CPULOAD_SAMPLES_CORE0 */
#       ifndef T1_NOF_TASKS_CORE0
#           error T1_NOF_TASKS_CORE0 not defined
#       endif /* T1_NOF_TASKS_CORE0 */
#       ifndef T1_NOF_USER_STPWS_CORE0
#           error T1_NOF_USER_STPWS_CORE0 not defined
#       endif /* T1_NOF_USER_STPWS_CORE0 */
#       ifndef T1_NOF_FLEX_STPWS_CORE0
#           error T1_NOF_FLEX_STPWS_CORE0 not defined
#       endif /* T1_NOF_FLEX_STPWS_CORE0 */
#       ifndef T1_NOF_CSRNS_CORE0
#           error T1_NOF_CSRNS_CORE0 not defined
#       endif /* T1_NOF_CSRNS_CORE0 */
#   if !defined T1_NOF_CORES
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
void (* const T1_pCpuLoadCallback)( T1_uint16Least_t to, T1_uint16Least_t te ) T1_SEC_CONST_32 =
((0.0 <= T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 ) && T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 ) < 256.0)
    ? (T1_CPULOAD_CALLBACK_CORE0)
    : T1_NULL );
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#       if defined T1_32BIT_TRACE_TIME
#           define T1_START_SEC_CONST_32
#           include "T1_MemMap.h"
const T1_tick_t         T1_overhead T1_SEC_CONST_32     = (T1_tick_t)T1_NS_TO_TICKS( T1_OVERHEAD_CORE0_NS );
const T1_tick_t         T1_flexOverhead T1_SEC_CONST_32 = (T1_tick_t)T1_NS_TO_TICKS( T1_FLEX_OVERHEAD_CORE0_NS );
#           define T1_STOP_SEC_CONST_32
#           include "T1_MemMap.h"
#       else /* 16 bit trace time */
#           define T1_START_SEC_CONST_16
#           include "T1_MemMap.h"
const T1_tick_t         T1_overhead T1_SEC_CONST_16     = (T1_tick_t)T1_NS_TO_TICKS( T1_OVERHEAD_CORE0_NS );
const T1_tick_t         T1_flexOverhead T1_SEC_CONST_16 = (T1_tick_t)T1_NS_TO_TICKS( T1_FLEX_OVERHEAD_CORE0_NS );
#           define T1_STOP_SEC_CONST_16
#           include "T1_MemMap.h"
#       endif /* defined T1_32BIT_TRACE_TIME */
#       define T1_START_SEC_CONST_16
#       include "T1_MemMap.h"
const T1_uint16_t       T1_cpuLoadTxPeriod T1_SEC_CONST_16 = T1_CPULOAD_TX_PERIOD_CORE0;
const T1_resultsIdx_t   T1_nofResults T1_SEC_CONST_16   = T1_NOF_TASKS_CORE0 + 2*(T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS) + 3;
const T1_uint16_t       T1_startOfFrameEvent T1_SEC_CONST_16 = T1_COMBINE_EVENT_INFO( T1_BSF_EVENT_ID_CORE0, T1_BSF_EVENT_INFO_CORE0);
const T1_anaCapa_t      T1_defaultAnalysisCapacity T1_SEC_CONST_16 = T1_CONT_ANALYSIS_CAPACITY_CORE0;
#       define T1_STOP_SEC_CONST_16
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_8
#       include "T1_MemMap.h"
const T1_uint8_t        T1_avgCPULoadSamples T1_SEC_CONST_8 = T1_CPULOAD_SAMPLES_CORE0;
const T1_taskIdx_t      T1_nofTasks T1_SEC_CONST_8      = T1_NOF_TASKS_CORE0;
const T1_stpwIdx_t      T1_nofStpws T1_SEC_CONST_8      = T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS;
const T1_stpwIdx_t      T1_nofUserStpws T1_SEC_CONST_8  = T1_NOF_USER_STPWS_CORE0;
const T1_csrnIdx_t      T1_nofCsrns T1_SEC_CONST_8      = T1_NOF_CSRNS_CORE0;
const T1_uint8_t        T1_nofPreemptions T1_SEC_CONST_8 = T1_MAX_TASK_PREEMPTIONS_CORE0;
const T1_uint8_t        T1_cpuLoadThreshold T1_SEC_CONST_8 =
((0.0 <= T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 ) && T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 ) < 256.0)
    ? (T1_uint8_t)T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 )
    : 0u);
const T1_taskIdx_t      T1_bgTaskIdx T1_SEC_CONST_8    = T1_BACKGROUND_TASK_ID_CORE0;
#       define T1_STOP_SEC_CONST_8
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32
#       include "T1_MemMap.h"
T1_stpwData_t           T1_stpwData[T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS] T1_SEC_NO_INIT_32;
T1_csrnData_t           T1_csrnData[T1_NOF_CSRNS_CORE0] T1_SEC_NO_INIT_32;
T1_resultTime_t         T1_resultBuffer[T1_NOF_TASKS_CORE0 + 2*(T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS) + 3] T1_SEC_NO_INIT_32;
T1_taskStackElem_t      T1_taskStack[T1_MAX_TASK_PREEMPTIONS_CORE0+T1_TASK_STACK_OVERRUNS] T1_SEC_NO_INIT_32;
#       define T1_STOP_SEC_NO_INIT_32
#       include "T1_MemMap.h"
#       if defined T1_CONT_TASK_CONSTRAINTS && ! defined T1_CONT_TERMINATING_ECC
#           define T1_START_SEC_NO_INIT_8
#           include "T1_MemMap.h"
T1_taskData_t           T1_taskData[T1_NOF_TASKS_CORE0] T1_SEC_NO_INIT_8;
#           define T1_STOP_SEC_NO_INIT_8
#          include "T1_MemMap.h"
#       endif /* defined T1_CONT_TASK_CONSTRAINTS && ! defined T1_CONT_TERMINATING_ECC */
#   elif 1 == T1_NOF_CORES
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
void (* const T1_pCpuLoadCallbackPC[])( T1_uint16Least_t to, T1_uint16Least_t te ) T1_SEC_CONST_32 =
{
    ((0.0 <= T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 ) && T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 ) < 256.0)
        ? (T1_CPULOAD_CALLBACK_CORE0)
        : T1_NULL )
};
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#       if defined T1_32BIT_TRACE_TIME
#           define T1_START_SEC_CONST_32
#           include "T1_MemMap.h"
const T1_tick_t         T1_overheadPC[] T1_SEC_CONST_32     = { (T1_tick_t)T1_NS_TO_TICKS_CORE0( T1_OVERHEAD_CORE0_NS ) };
const T1_tick_t         T1_flexOverheadPC[] T1_SEC_CONST_32 = { (T1_tick_t)T1_NS_TO_TICKS_CORE0( T1_FLEX_OVERHEAD_CORE0_NS ) };
#           define T1_STOP_SEC_CONST_32
#           include "T1_MemMap.h"
#       else /* 16 bit trace time */
#           define T1_START_SEC_CONST_16
#           include "T1_MemMap.h"
const T1_tick_t         T1_overheadPC[] T1_SEC_CONST_32     = { (T1_tick_t)T1_NS_TO_TICKS_CORE0( T1_OVERHEAD_CORE0_NS ) };
const T1_tick_t         T1_flexOverheadPC[] T1_SEC_CONST_32 = { (T1_tick_t)T1_NS_TO_TICKS_CORE0( T1_FLEX_OVERHEAD_CORE0_NS ) };
#           define T1_STOP_SEC_CONST_16
#           include "T1_MemMap.h"
#       endif /* defined T1_STOP_SEC_CONST_32 */
#       define T1_START_SEC_CONST_16
#       include "T1_MemMap.h"
const T1_uint16_t       T1_cpuLoadTxPeriodPC[] T1_SEC_CONST_16 = { T1_CPULOAD_TX_PERIOD_CORE0 };
const T1_resultsIdx_t   T1_nofResultsPC[] T1_SEC_CONST_16   = { T1_NOF_TASKS_CORE0 + 2*(T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS) + 3 };
const T1_uint16_t       T1_startOfFrameEventPC[] T1_SEC_CONST_16 = { T1_COMBINE_EVENT_INFO( T1_BSF_EVENT_ID_CORE0, T1_BSF_EVENT_INFO_CORE0) };
const T1_anaCapa_t      T1_defaultAnalysisCapacityPC[] T1_SEC_CONST_16 = { T1_CONT_ANALYSIS_CAPACITY_CORE0 };
#       define T1_STOP_SEC_CONST_16
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_8
#       include "T1_MemMap.h"
const T1_uint8_t        T1_avgCPULoadSamplesPC[] T1_SEC_CONST_8 = { T1_CPULOAD_SAMPLES_CORE0 };
const T1_taskIdx_t      T1_nofTasksPC[] T1_SEC_CONST_8      = { T1_NOF_TASKS_CORE0 };
const T1_stpwIdx_t      T1_nofStpwsPC[] T1_SEC_CONST_8      = { T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS };
const T1_stpwIdx_t      T1_nofUserStpwsPC[] T1_SEC_CONST_8  = { T1_NOF_USER_STPWS_CORE0 };
const T1_csrnIdx_t      T1_nofCsrnsPC[] T1_SEC_CONST_8      = { T1_NOF_CSRNS_CORE0 };
const T1_uint8_t        T1_nofPreemptionsPC[] T1_SEC_CONST_8 = { T1_MAX_TASK_PREEMPTIONS_CORE0 };
const T1_uint8_t        T1_cpuLoadThresholdPC[] T1_SEC_CONST_8 =
{
    ((0.0 <= T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 ) && T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 ) < 256.0)
        ? (T1_uint8_t)T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 )
        : 0u)
};
const T1_taskIdx_t      T1_bgTaskIdxPC[] T1_SEC_CONST_8 = { T1_BACKGROUND_TASK_ID_CORE0 };
#       define T1_STOP_SEC_CONST_8
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE0
#       include "T1_MemMap.h"
T1_stpwData_t           T1_stpwData0[T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS] T1_SEC_NO_INIT_32_CORE0;
T1_csrnData_t           T1_csrnData0[T1_NOF_CSRNS_CORE0] T1_SEC_NO_INIT_32_CORE0;
T1_resultTime_t         T1_resultBuffer0[T1_NOF_TASKS_CORE0 + 2*(T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS) + 3] T1_SEC_NO_INIT_32_CORE0;
T1_taskStackElem_t      T1_taskStack0[T1_MAX_TASK_PREEMPTIONS_CORE0+T1_TASK_STACK_OVERRUNS] T1_SEC_NO_INIT_32_CORE0;
#       define T1_STOP_SEC_NO_INIT_32_CORE0
#       include "T1_MemMap.h"
#       if defined T1_CONT_TASK_CONSTRAINTS && ! defined T1_CONT_TERMINATING_ECC
#           define T1_START_SEC_NO_INIT_8_CORE0
#           include "T1_MemMap.h"
T1_taskData_t           T1_taskData0[T1_NOF_TASKS_CORE0] T1_SEC_NO_INIT_8_CORE0;
#           define T1_STOP_SEC_NO_INIT_8_CORE0
#          include "T1_MemMap.h"
#       endif /* defined T1_CONT_TASK_CONSTRAINTS && ! defined T1_CONT_TERMINATING_ECC */
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_stpwData_t   * const T1_stpwDataPC[] T1_SEC_CONST_32     = { T1_stpwData0 };
T1_csrnData_t   * const T1_csrnDataPC[] T1_SEC_CONST_32     = { T1_csrnData0 };
T1_resultTime_t * const T1_resultBufferPC[] T1_SEC_CONST_32 = { T1_resultBuffer0 };
T1_taskStackElem_t * const T1_taskStackPC[] T1_SEC_CONST_32 = { T1_taskStack0 };
#       if defined T1_CONT_TASK_CONSTRAINTS || defined T1_CONT_TERMINATING_ECC
T1_taskData_t * const T1_taskDataPC[] T1_SEC_CONST_32       = { T1_taskData0 };
#       endif /* defined T1_CONT_TASK_CONSTRAINTS || defined T1_CONT_TERMINATING_ECC */
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#   elif 2 == T1_NOF_CORES
#       ifndef T1_OVERHEAD_CORE0_NS
#           error T1_OVERHEAD_CORE0_NS not defined
#       endif /* T1_OVERHEAD_CORE0_NS */
#       ifndef T1_FLEX_OVERHEAD_CORE0_NS
#           error T1_FLEX_OVERHEAD_CORE0_NS not defined
#       endif /* T1_FLEX_OVERHEAD_CORE0_NS */
#       ifndef T1_CPULOAD_TX_PERIOD_CORE0
#           error T1_CPULOAD_TX_PERIOD_CORE0 not defined
#       endif /* T1_CPULOAD_TX_PERIOD_CORE0 */
#       ifndef T1_CPULOAD_SAMPLES_CORE0
#           error T1_CPULOAD_SAMPLES_CORE0 not defined
#       endif /* T1_CPULOAD_SAMPLES_CORE0 */
#       ifndef T1_NOF_TASKS_CORE0
#           error T1_NOF_TASKS_CORE0 not defined
#       endif /* T1_NOF_TASKS_CORE0 */
#       ifndef T1_NOF_USER_STPWS_CORE0
#           error T1_NOF_USER_STPWS_CORE0 not defined
#       endif /* T1_NOF_USER_STPWS_CORE0 */
#       ifndef T1_NOF_FLEX_STPWS_CORE0
#           error T1_NOF_FLEX_STPWS_CORE0 not defined
#       endif /* T1_NOF_FLEX_STPWS_CORE0 */
#       ifndef T1_NOF_CSRNS_CORE0
#           error T1_NOF_CSRNS_CORE0 not defined
#       endif /* T1_NOF_CSRNS_CORE0 */
#       ifndef T1_OVERHEAD_CORE1_NS
#           error T1_OVERHEAD_CORE1_NS not defined
#       endif /* T1_OVERHEAD_CORE1_NS */
#       ifndef T1_FLEX_OVERHEAD_CORE1_NS
#           error T1_FLEX_OVERHEAD_CORE1_NS not defined
#       endif /* T1_FLEX_OVERHEAD_CORE1_NS */
#       ifndef T1_CPULOAD_TX_PERIOD_CORE1
#           error T1_CPULOAD_TX_PERIOD_CORE1 not defined
#       endif /* T1_CPULOAD_TX_PERIOD_CORE1 */
#       ifndef T1_CPULOAD_SAMPLES_CORE1
#           error T1_CPULOAD_SAMPLES_CORE1 not defined
#       endif /* T1_CPULOAD_SAMPLES_CORE1 */
#       ifndef T1_NOF_TASKS_CORE1
#           error T1_NOF_TASKS_CORE1 not defined
#       endif /* T1_NOF_TASKS_CORE1 */
#       ifndef T1_NOF_USER_STPWS_CORE1
#           error T1_NOF_USER_STPWS_CORE1 not defined
#       endif /* T1_NOF_USER_STPWS_CORE1 */
#       ifndef T1_NOF_FLEX_STPWS_CORE1
#           error T1_NOF_FLEX_STPWS_CORE1 not defined
#       endif /* T1_NOF_FLEX_STPWS_CORE1 */
#       ifndef T1_NOF_CSRNS_CORE1
#           error T1_NOF_CSRNS_CORE1 not defined
#       endif /* T1_NOF_CSRNS_CORE1 */
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
void (* const T1_pCpuLoadCallbackPC[])( T1_uint16Least_t to, T1_uint16Least_t te ) T1_SEC_CONST_32 =
{
    ((0.0 <= T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 ) && T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 ) < 256.0)
        ? (T1_CPULOAD_CALLBACK_CORE0)
        : T1_NULL ),
    ((0.0 <= T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE1 ) && T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE1 ) < 256.0)
        ? (T1_CPULOAD_CALLBACK_CORE1)
        : T1_NULL )
};

#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_16
#       include "T1_MemMap.h"
const T1_tick_t         T1_overheadPC[] T1_SEC_CONST_16     = { (T1_tick_t)T1_NS_TO_TICKS_CORE0( T1_OVERHEAD_CORE0_NS ), (T1_tick_t)T1_NS_TO_TICKS_CORE1( T1_OVERHEAD_CORE1_NS ) };
const T1_tick_t         T1_flexOverheadPC[] T1_SEC_CONST_16 = { (T1_tick_t)T1_NS_TO_TICKS_CORE0( T1_FLEX_OVERHEAD_CORE0_NS ), (T1_tick_t)T1_NS_TO_TICKS_CORE1( T1_FLEX_OVERHEAD_CORE1_NS ) };
const T1_uint16_t       T1_cpuLoadTxPeriodPC[] T1_SEC_CONST_16 = { T1_CPULOAD_TX_PERIOD_CORE0, T1_CPULOAD_TX_PERIOD_CORE1 };
const T1_resultsIdx_t   T1_nofResultsPC[] T1_SEC_CONST_16   = { T1_NOF_TASKS_CORE0 + 2*(T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS) + 3, T1_NOF_TASKS_CORE1 + 2*(T1_NOF_USER_STPWS_CORE1 + T1_NOF_FLEX_STPWS_CORE1 + T1_CONT_NOF_VRTL_STPWS) + 3 };
const T1_uint16_t       T1_startOfFrameEventPC[] T1_SEC_CONST_16 = { T1_COMBINE_EVENT_INFO( T1_BSF_EVENT_ID_CORE0, T1_BSF_EVENT_INFO_CORE0), T1_COMBINE_EVENT_INFO( T1_BSF_EVENT_ID_CORE1, T1_BSF_EVENT_INFO_CORE1) };
const T1_anaCapa_t      T1_defaultAnalysisCapacityPC[] T1_SEC_CONST_16 = { T1_CONT_ANALYSIS_CAPACITY_CORE0, T1_CONT_ANALYSIS_CAPACITY_CORE1 };
#       define T1_STOP_SEC_CONST_16
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_8
#       include "T1_MemMap.h"
const T1_uint8_t        T1_avgCPULoadSamplesPC[] T1_SEC_CONST_8 = { T1_CPULOAD_SAMPLES_CORE0, T1_CPULOAD_SAMPLES_CORE1 };
const T1_taskIdx_t      T1_nofTasksPC[] T1_SEC_CONST_8      = { T1_NOF_TASKS_CORE0, T1_NOF_TASKS_CORE1 };
const T1_stpwIdx_t      T1_nofStpwsPC[] T1_SEC_CONST_8      = { T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS, T1_NOF_USER_STPWS_CORE1 + T1_NOF_FLEX_STPWS_CORE1 + T1_CONT_NOF_VRTL_STPWS };
const T1_stpwIdx_t      T1_nofUserStpwsPC[] T1_SEC_CONST_8  = { T1_NOF_USER_STPWS_CORE0, T1_NOF_USER_STPWS_CORE1 };
const T1_csrnIdx_t      T1_nofCsrnsPC[] T1_SEC_CONST_8      = { T1_NOF_CSRNS_CORE0, T1_NOF_CSRNS_CORE1 };
const T1_uint8_t        T1_nofPreemptionsPC[] T1_SEC_CONST_8 = { T1_MAX_TASK_PREEMPTIONS_CORE0, T1_MAX_TASK_PREEMPTIONS_CORE1 };
const T1_uint8_t        T1_cpuLoadThresholdPC[] T1_SEC_CONST_8 =
{
    ((0.0 <= T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 ) && T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 ) < 256.0)
        ? (T1_uint8_t)T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 )
        : 0u),
    ((0.0 <= T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE1 ) && T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE1 ) < 256.0)
        ? (T1_uint8_t)T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE1 )
        : 0u)
};
const T1_taskIdx_t      T1_bgTaskIdxPC[] T1_SEC_CONST_8 = { T1_BACKGROUND_TASK_ID_CORE0, T1_BACKGROUND_TASK_ID_CORE1 };
#       define T1_STOP_SEC_CONST_8
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE0
#       include "T1_MemMap.h"
T1_stpwData_t           T1_stpwData0[T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS] T1_SEC_NO_INIT_32_CORE0;
T1_csrnData_t           T1_csrnData0[T1_NOF_CSRNS_CORE0] T1_SEC_NO_INIT_32_CORE0;
T1_resultTime_t         T1_resultBuffer0[T1_NOF_TASKS_CORE0 + 2*(T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS) + 3] T1_SEC_NO_INIT_32_CORE0;
T1_taskStackElem_t      T1_taskStack0[T1_MAX_TASK_PREEMPTIONS_CORE0+T1_TASK_STACK_OVERRUNS] T1_SEC_NO_INIT_32_CORE0;
#       define T1_STOP_SEC_NO_INIT_32_CORE0
#       include "T1_MemMap.h"
#       if defined T1_CONT_TASK_CONSTRAINTS && ! defined T1_CONT_TERMINATING_ECC
#           define T1_START_SEC_NO_INIT_8_CORE0
#           include "T1_MemMap.h"
T1_taskData_t           T1_taskData0[T1_NOF_TASKS_CORE0] T1_SEC_NO_INIT_8_CORE0;
#           define T1_STOP_SEC_NO_INIT_8_CORE0
#          include "T1_MemMap.h"
#       endif /* defined T1_CONT_TASK_CONSTRAINTS && ! defined T1_CONT_TERMINATING_ECC */
#       define T1_START_SEC_NO_INIT_32_CORE1
#       include "T1_MemMap.h"
T1_stpwData_t           T1_stpwData1[T1_NOF_USER_STPWS_CORE1 + T1_NOF_FLEX_STPWS_CORE1 + T1_CONT_NOF_VRTL_STPWS] T1_SEC_NO_INIT_32_CORE1;
T1_csrnData_t           T1_csrnData1[T1_NOF_CSRNS_CORE1] T1_SEC_NO_INIT_32_CORE1;
T1_resultTime_t         T1_resultBuffer1[T1_NOF_TASKS_CORE1 + 2*(T1_NOF_USER_STPWS_CORE1 + T1_NOF_FLEX_STPWS_CORE1 + T1_CONT_NOF_VRTL_STPWS) + 3] T1_SEC_NO_INIT_32_CORE1;
T1_taskStackElem_t      T1_taskStack1[T1_MAX_TASK_PREEMPTIONS_CORE1+T1_TASK_STACK_OVERRUNS] T1_SEC_NO_INIT_32_CORE1;
#       define T1_STOP_SEC_NO_INIT_32_CORE1
#       include "T1_MemMap.h"
#       if defined T1_CONT_TASK_CONSTRAINTS && ! defined T1_CONT_TERMINATING_ECC
#           define T1_START_SEC_NO_INIT_8_CORE1
#           include "T1_MemMap.h"
T1_taskData_t           T1_taskData1[T1_NOF_TASKS_CORE1] T1_SEC_NO_INIT_8_CORE1;
#           define T1_STOP_SEC_NO_INIT_8_CORE1
#          include "T1_MemMap.h"
#       endif /* defined T1_CONT_TASK_CONSTRAINTS && ! defined T1_CONT_TERMINATING_ECC */
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_stpwData_t   * const T1_stpwDataPC[2] T1_SEC_CONST_32 = { T1_stpwData0, T1_stpwData1 };
T1_csrnData_t   * const T1_csrnDataPC[2] T1_SEC_CONST_32 = { T1_csrnData0, T1_csrnData1 };
T1_resultTime_t * const T1_resultBufferPC[2] T1_SEC_CONST_32 = { T1_resultBuffer0, T1_resultBuffer1 };
T1_taskStackElem_t * const T1_taskStackPC[2] T1_SEC_CONST_32 = { T1_taskStack0, T1_taskStack1 };
#       if defined T1_CONT_TASK_CONSTRAINTS || defined T1_CONT_TERMINATING_ECC
T1_taskData_t * const T1_taskDataPC[2] T1_SEC_CONST_32       = { T1_taskData0, T1_taskData1 };
#       endif /* defined T1_CONT_TASK_CONSTRAINTS || defined T1_CONT_TERMINATING_ECC */
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#   elif 3 == T1_NOF_CORES
#       ifndef T1_OVERHEAD_CORE0_NS
#           error T1_OVERHEAD_CORE0_NS not defined
#       endif /* T1_OVERHEAD_CORE0_NS */
#       ifndef T1_FLEX_OVERHEAD_CORE0_NS
#           error T1_FLEX_OVERHEAD_CORE0_NS not defined
#       endif /* T1_FLEX_OVERHEAD_CORE0_NS */
#       ifndef T1_CPULOAD_TX_PERIOD_CORE0
#           error T1_CPULOAD_TX_PERIOD_CORE0 not defined
#       endif /* T1_CPULOAD_TX_PERIOD_CORE0 */
#       ifndef T1_CPULOAD_SAMPLES_CORE0
#           error T1_CPULOAD_SAMPLES_CORE0 not defined
#       endif /* T1_CPULOAD_SAMPLES_CORE0 */
#       ifndef T1_NOF_TASKS_CORE0
#           error T1_NOF_TASKS_CORE0 not defined
#       endif /* T1_NOF_TASKS_CORE0 */
#       ifndef T1_NOF_USER_STPWS_CORE0
#           error T1_NOF_USER_STPWS_CORE0 not defined
#       endif /* T1_NOF_USER_STPWS_CORE0 */
#       ifndef T1_NOF_FLEX_STPWS_CORE0
#           error T1_NOF_FLEX_STPWS_CORE0 not defined
#       endif /* T1_NOF_FLEX_STPWS_CORE0 */
#       ifndef T1_NOF_CSRNS_CORE0
#           error T1_NOF_CSRNS_CORE0 not defined
#       endif /* T1_NOF_CSRNS_CORE0 */
#       ifndef T1_OVERHEAD_CORE1_NS
#           error T1_OVERHEAD_CORE1_NS not defined
#       endif /* T1_OVERHEAD_CORE1_NS */
#       ifndef T1_FLEX_OVERHEAD_CORE1_NS
#           error T1_FLEX_OVERHEAD_CORE1_NS not defined
#       endif /* T1_FLEX_OVERHEAD_CORE1_NS */
#       ifndef T1_CPULOAD_TX_PERIOD_CORE1
#           error T1_CPULOAD_TX_PERIOD_CORE1 not defined
#       endif /* T1_CPULOAD_TX_PERIOD_CORE1 */
#       ifndef T1_CPULOAD_SAMPLES_CORE1
#           error T1_CPULOAD_SAMPLES_CORE1 not defined
#       endif /* T1_CPULOAD_SAMPLES_CORE1 */
#       ifndef T1_NOF_TASKS_CORE1
#           error T1_NOF_TASKS_CORE1 not defined
#       endif /* T1_NOF_TASKS_CORE1 */
#       ifndef T1_NOF_USER_STPWS_CORE1
#           error T1_NOF_USER_STPWS_CORE1 not defined
#       endif /* T1_NOF_USER_STPWS_CORE1 */
#       ifndef T1_NOF_FLEX_STPWS_CORE1
#           error T1_NOF_FLEX_STPWS_CORE1 not defined
#       endif /* T1_NOF_FLEX_STPWS_CORE1 */
#       ifndef T1_NOF_CSRNS_CORE1
#           error T1_NOF_CSRNS_CORE1 not defined
#       endif /* T1_NOF_CSRNS_CORE1 */
#       ifndef T1_OVERHEAD_CORE2_NS
#           error T1_OVERHEAD_CORE2_NS not defined
#       endif /* T1_OVERHEAD_CORE2_NS */
#       ifndef T1_FLEX_OVERHEAD_CORE2_NS
#           error T1_FLEX_OVERHEAD_CORE2_NS not defined
#       endif /* T1_FLEX_OVERHEAD_CORE2_NS */
#       ifndef T1_CPULOAD_TX_PERIOD_CORE2
#           error T1_CPULOAD_TX_PERIOD_CORE2 not defined
#       endif /* T1_CPULOAD_TX_PERIOD_CORE2 */
#       ifndef T1_CPULOAD_SAMPLES_CORE2
#           error T1_CPULOAD_SAMPLES_CORE2 not defined
#       endif /* T1_CPULOAD_SAMPLES_CORE2 */
#       ifndef T1_NOF_TASKS_CORE2
#           error T1_NOF_TASKS_CORE2 not defined
#       endif /* T1_NOF_TASKS_CORE2 */
#       ifndef T1_NOF_USER_STPWS_CORE2
#           error T1_NOF_USER_STPWS_CORE2 not defined
#       endif /* T1_NOF_USER_STPWS_CORE2 */
#       ifndef T1_NOF_FLEX_STPWS_CORE2
#           error T1_NOF_FLEX_STPWS_CORE2 not defined
#       endif /* T1_NOF_FLEX_STPWS_CORE2 */
#       ifndef T1_NOF_CSRNS_CORE2
#           error T1_NOF_CSRNS_CORE2 not defined
#       endif /* T1_NOF_CSRNS_CORE2 */
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
void (* const T1_pCpuLoadCallbackPC[])( T1_uint16Least_t to, T1_uint16Least_t te ) T1_SEC_CONST_32 =
{
    ((0.0 <= T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 ) && T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 ) < 256.0)
        ? (T1_CPULOAD_CALLBACK_CORE0)
        : T1_NULL ),
    ((0.0 <= T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE1 ) && T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE1 ) < 256.0)
        ? (T1_CPULOAD_CALLBACK_CORE1)
        : T1_NULL ),
    ((0.0 <= T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE2 ) && T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE2 ) < 256.0)
        ? (T1_CPULOAD_CALLBACK_CORE2)
        : T1_NULL )
};
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_16
#       include "T1_MemMap.h"
const T1_tick_t         T1_overheadPC[] T1_SEC_CONST_16     = { (T1_tick_t)T1_NS_TO_TICKS_CORE0( T1_OVERHEAD_CORE0_NS ), (T1_tick_t)T1_NS_TO_TICKS_CORE1( T1_OVERHEAD_CORE1_NS ), (T1_tick_t)T1_NS_TO_TICKS_CORE2( T1_OVERHEAD_CORE2_NS ) };
const T1_tick_t         T1_flexOverheadPC[] T1_SEC_CONST_16 = { (T1_tick_t)T1_NS_TO_TICKS_CORE0( T1_FLEX_OVERHEAD_CORE0_NS ), (T1_tick_t)T1_NS_TO_TICKS_CORE1( T1_FLEX_OVERHEAD_CORE1_NS ), (T1_tick_t)T1_NS_TO_TICKS_CORE2( T1_FLEX_OVERHEAD_CORE2_NS ) };
const T1_uint16_t       T1_cpuLoadTxPeriodPC[] T1_SEC_CONST_16 = { T1_CPULOAD_TX_PERIOD_CORE0, T1_CPULOAD_TX_PERIOD_CORE1, T1_CPULOAD_TX_PERIOD_CORE2 };
const T1_resultsIdx_t   T1_nofResultsPC[] T1_SEC_CONST_16   = { T1_NOF_TASKS_CORE0 + 2*(T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS) + 3, T1_NOF_TASKS_CORE1 + 2*(T1_NOF_USER_STPWS_CORE1 + T1_NOF_FLEX_STPWS_CORE1 + T1_CONT_NOF_VRTL_STPWS) + 3, T1_NOF_TASKS_CORE2 + 2*(T1_NOF_USER_STPWS_CORE2 + T1_NOF_FLEX_STPWS_CORE2 + T1_CONT_NOF_VRTL_STPWS) + 3 };
const T1_uint16_t       T1_startOfFrameEventPC[] T1_SEC_CONST_16 = { T1_COMBINE_EVENT_INFO( T1_BSF_EVENT_ID_CORE0, T1_BSF_EVENT_INFO_CORE0), T1_COMBINE_EVENT_INFO( T1_BSF_EVENT_ID_CORE1, T1_BSF_EVENT_INFO_CORE1), T1_COMBINE_EVENT_INFO( T1_BSF_EVENT_ID_CORE2, T1_BSF_EVENT_INFO_CORE2) };
const T1_anaCapa_t      T1_defaultAnalysisCapacityPC[] T1_SEC_CONST_16 = { T1_CONT_ANALYSIS_CAPACITY_CORE0, T1_CONT_ANALYSIS_CAPACITY_CORE1, T1_CONT_ANALYSIS_CAPACITY_CORE2 };
#       define T1_STOP_SEC_CONST_16
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_8
#       include "T1_MemMap.h"
const T1_uint8_t        T1_avgCPULoadSamplesPC[] T1_SEC_CONST_8 = { T1_CPULOAD_SAMPLES_CORE0, T1_CPULOAD_SAMPLES_CORE1, T1_CPULOAD_SAMPLES_CORE2 };
const T1_taskIdx_t      T1_nofTasksPC[] T1_SEC_CONST_8      = { T1_NOF_TASKS_CORE0, T1_NOF_TASKS_CORE1, T1_NOF_TASKS_CORE2 };
const T1_stpwIdx_t      T1_nofStpwsPC[] T1_SEC_CONST_8      = { T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS, T1_NOF_USER_STPWS_CORE1 + T1_NOF_FLEX_STPWS_CORE1 + T1_CONT_NOF_VRTL_STPWS, T1_NOF_USER_STPWS_CORE2 + T1_NOF_FLEX_STPWS_CORE2 + T1_CONT_NOF_VRTL_STPWS };
const T1_stpwIdx_t      T1_nofUserStpwsPC[] T1_SEC_CONST_8  = { T1_NOF_USER_STPWS_CORE0, T1_NOF_USER_STPWS_CORE1, T1_NOF_USER_STPWS_CORE2 };
const T1_csrnIdx_t      T1_nofCsrnsPC[] T1_SEC_CONST_8      = { T1_NOF_CSRNS_CORE0, T1_NOF_CSRNS_CORE1, T1_NOF_CSRNS_CORE2 };
const T1_uint8_t        T1_nofPreemptionsPC[] T1_SEC_CONST_8 = { T1_MAX_TASK_PREEMPTIONS_CORE0, T1_MAX_TASK_PREEMPTIONS_CORE1, T1_MAX_TASK_PREEMPTIONS_CORE2 };
T1_uint8_t const T1_cpuLoadThresholdPC[] T1_SEC_CONST_8 =
{
    ((0.0 <= T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 ) && T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 ) < 256.0)
        ? (T1_uint8_t)T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE0 )
        : 0u),
    ((0.0 <= T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE1 ) && T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE1 ) < 256.0)
        ? (T1_uint8_t)T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE1 )
        : 0u),
    ((0.0 <= T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE2 ) && T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE2 ) < 256.0)
        ? (T1_uint8_t)T1_PERCENT_TO_256THS( T1_CPULOAD_THRESHOLD_PERCENT_CORE2 )
        : 0u)
};
const T1_taskIdx_t      T1_bgTaskIdxPC[] T1_SEC_CONST_8 = { T1_BACKGROUND_TASK_ID_CORE0, T1_BACKGROUND_TASK_ID_CORE1, T1_BACKGROUND_TASK_ID_CORE2 };
#       define T1_STOP_SEC_CONST_8
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE0
#       include "T1_MemMap.h"
T1_stpwData_t           T1_stpwData0[T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS] T1_SEC_NO_INIT_32_CORE0;
T1_csrnData_t           T1_csrnData0[T1_NOF_CSRNS_CORE0] T1_SEC_NO_INIT_32_CORE0;
T1_resultTime_t         T1_resultBuffer0[T1_NOF_TASKS_CORE0 + 2*(T1_NOF_USER_STPWS_CORE0 + T1_NOF_FLEX_STPWS_CORE0 + T1_CONT_NOF_VRTL_STPWS) + 3] T1_SEC_NO_INIT_32_CORE0;
T1_taskStackElem_t      T1_taskStack0[T1_MAX_TASK_PREEMPTIONS_CORE0+T1_TASK_STACK_OVERRUNS] T1_SEC_NO_INIT_32_CORE0;
#       define T1_STOP_SEC_NO_INIT_32_CORE0
#       include "T1_MemMap.h"
#       if defined T1_CONT_TASK_CONSTRAINTS && ! defined T1_CONT_TERMINATING_ECC
#           define T1_START_SEC_NO_INIT_8_CORE0
#           include "T1_MemMap.h"
T1_taskData_t           T1_taskData0[T1_NOF_TASKS_CORE0] T1_SEC_NO_INIT_8_CORE0;
#           define T1_STOP_SEC_NO_INIT_8_CORE0
#          include "T1_MemMap.h"
#       endif /* defined T1_CONT_TASK_CONSTRAINTS && ! defined T1_CONT_TERMINATING_ECC */
#       define T1_START_SEC_NO_INIT_32_CORE1
#       include "T1_MemMap.h"
T1_stpwData_t           T1_stpwData1[T1_NOF_USER_STPWS_CORE1 + T1_NOF_FLEX_STPWS_CORE1 + T1_CONT_NOF_VRTL_STPWS] T1_SEC_NO_INIT_32_CORE1;
T1_csrnData_t           T1_csrnData1[T1_NOF_CSRNS_CORE1] T1_SEC_NO_INIT_32_CORE1;
T1_resultTime_t         T1_resultBuffer1[T1_NOF_TASKS_CORE1 + 2*(T1_NOF_USER_STPWS_CORE1 + T1_NOF_FLEX_STPWS_CORE1 + T1_CONT_NOF_VRTL_STPWS) + 3] T1_SEC_NO_INIT_32_CORE1;
T1_taskStackElem_t      T1_taskStack1[T1_MAX_TASK_PREEMPTIONS_CORE1+T1_TASK_STACK_OVERRUNS] T1_SEC_NO_INIT_32_CORE1;
#       define T1_STOP_SEC_NO_INIT_32_CORE1
#       include "T1_MemMap.h"
#       if defined T1_CONT_TASK_CONSTRAINTS && ! defined T1_CONT_TERMINATING_ECC
#           define T1_START_SEC_NO_INIT_8_CORE1
#           include "T1_MemMap.h"
T1_taskData_t           T1_taskData1[T1_NOF_TASKS_CORE1] T1_SEC_NO_INIT_8_CORE1;
#           define T1_STOP_SEC_NO_INIT_8_CORE1
#          include "T1_MemMap.h"
#       endif /* defined T1_CONT_TASK_CONSTRAINTS && ! defined T1_CONT_TERMINATING_ECC */
#       define T1_START_SEC_NO_INIT_32_CORE2
#       include "T1_MemMap.h"
T1_stpwData_t           T1_stpwData2[T1_NOF_USER_STPWS_CORE2 + T1_NOF_FLEX_STPWS_CORE2 + T1_CONT_NOF_VRTL_STPWS] T1_SEC_NO_INIT_32_CORE2;
T1_csrnData_t           T1_csrnData2[T1_NOF_CSRNS_CORE2] T1_SEC_NO_INIT_32_CORE2;
T1_resultTime_t         T1_resultBuffer2[T1_NOF_TASKS_CORE2 + 2*(T1_NOF_USER_STPWS_CORE2 + T1_NOF_FLEX_STPWS_CORE2 + T1_CONT_NOF_VRTL_STPWS) + 3] T1_SEC_NO_INIT_32_CORE2;
T1_taskStackElem_t      T1_taskStack2[T1_MAX_TASK_PREEMPTIONS_CORE2+T1_TASK_STACK_OVERRUNS] T1_SEC_NO_INIT_32_CORE2;
#       define T1_STOP_SEC_NO_INIT_32_CORE2
#       include "T1_MemMap.h"
#       if defined T1_CONT_TASK_CONSTRAINTS && ! defined T1_CONT_TERMINATING_ECC
#           define T1_START_SEC_NO_INIT_8_CORE2
#           include "T1_MemMap.h"
T1_taskData_t           T1_taskData2[T1_NOF_TASKS_CORE2] T1_SEC_NO_INIT_8_CORE2;
#           define T1_STOP_SEC_NO_INIT_8_CORE2
#          include "T1_MemMap.h"
#       endif /* defined T1_CONT_TASK_CONSTRAINTS && ! defined T1_CONT_TERMINATING_ECC */
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_stpwData_t   * const T1_stpwDataPC[3] T1_SEC_CONST_32 = { T1_stpwData0, T1_stpwData1, T1_stpwData2 };
T1_csrnData_t   * const T1_csrnDataPC[3] T1_SEC_CONST_32 = { T1_csrnData0, T1_csrnData1, T1_csrnData2 };
T1_resultTime_t * const T1_resultBufferPC[3] T1_SEC_CONST_32 = { T1_resultBuffer0, T1_resultBuffer1, T1_resultBuffer2 };
T1_taskStackElem_t * const T1_taskStackPC[3] T1_SEC_CONST_32 = { T1_taskStack0, T1_taskStack1, T1_taskStack2 };
#       if defined T1_CONT_TASK_CONSTRAINTS || defined T1_CONT_TERMINATING_ECC
T1_taskData_t * const T1_taskDataPC[3] T1_SEC_CONST_32       = { T1_taskData0, T1_taskData1, T1_taskData2 };
#       endif /* defined T1_CONT_TASK_CONSTRAINTS || defined T1_CONT_TERMINATING_ECC */
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#   else
#       error T1_NOF_CORES too large
#   endif
#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_CONT */
