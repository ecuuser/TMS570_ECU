/*************************************************************************************
*   FILE:           T1_scopeInterface.h
*
*   DESCRIPTION:    T1 scope interface
*
*   VISIBILITY:     extern
*
*   $Author: nick $
*
*   $Revision: 14625 $
*
*   $URL: https://gliwa.com/svn/repos/T1target/trunk/src/T1.scope/src/all/T1_scopeInterface.h $
*
*   Copyright:      Gliwa GmbH | know- how in embedded software
*                   Weilheim i.OB.
*                   All rights reserved
*************************************************************************************/

#ifndef T1_SCOPE_INTERFACE_H_
#define T1_SCOPE_INTERFACE_H_ (1)

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include "T1_baseInterface.h"

/*----------------------------------------------------------------------------------*/
/*--- type definitions -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/
/* The following type defines the structure of a single trace-entry  */
/* The array T1_traceBuffer of entries of this type define the trace buffer */
#if defined T1_32BIT_TRACE_TIME
typedef struct
{
    T1_uint16_t         timeLow;    /* 32 bit time field split for alignment */
    T1_uint16_t         timeHigh;
    T1_uint16_t         eventInfo;
}
T1_traceEntry_t;
#else /* !defined T1_32BIT_TRACE_TIME */
typedef T1_uint32_t T1_traceEntry_t;
#endif /* defined T1_32BIT_TRACE_ENTRY */
/*----------------------------------------------------------------------------------*/
/* When using a logic analyzer instead of the trace buffer, the event and the       */
/* info is written to a single cell which is traced. Instead of the target's        */
/* internal time, the logic analyzer's time stamp is used.                          */
typedef T1_uint16_t         T1_traceCell_t;
/*----------------------------------------------------------------------------------*/
typedef T1_uint16Least_t    T1_nofEntries_t; /* number of trace-buffer entries */

/*----------------------------------------------------------------------------------*/
/*--- macros, inline functions and forward declarations ----------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_SCOPE_PLUGIN_ID          (1u)

#define T1_EMPTY                    0x00u   /* empty (no entry, initialized) */
#define T1_START                    0x01u   /* start of a task or ISR */
#define T1_STOP                     0x02u   /* end of a task or ISR */
#define T1_START_STOP               0x03u   /* start and end of a short task or ISR */
#define T1_STOP_START               0x04u   /* end of one task and start of a 2nd */
#define T1_STOPWATCH_START          0x05u   /* start stopwatch */
#define T1_STOPWATCH_STOP           0x06u   /* stop stopwatch */
#define T1_STOPWATCH_STOP_START     0x07u   /* stop stopwatch n, start n */
#define T1_STOPWATCH_STOP_START_INC 0x08u   /* stop stopwatch n-1, start n */
#define T1_FLEX_UEC                 0x09u   /* T1.flex code event */
#define T1_FLEX_UED                 0x0Au   /* T1.flex data event */
#define T1_FLEX_USERDATA_START      0x0Bu   /* T1.flex data event with data */
#define T1_ACTIVATION               0x0Cu   /* successful task activation */
#define T1_WAIT                     0x0Du   /* task called WaitEvent */
#define T1_RESUME                   0x0Eu   /* task returned from WaitEvent */
#define T1_DISCONTINUITY            0x0Fu   /* resume after stop trace */
#define T1_ACTIVATION_FAILED        0x10u   /* failed task activation (E_OS_LIMIT) */
#define T1_RELEASE                  0x11u   /* task had a waiting event set */
#define T1_SYNCDATA_START           0x12u   /* synchronisation timestamp data */
#define T1_USERDATA_START           0x13u   /* user data */
#define T1_USERDATA_MID             0x14u   /* user data with no timestamp */
#define T1_USERDATA_STOP            0x15u   /* user data */
#define T1_RUNNABLE_START           0x16u   /* start of a runnable */
#define T1_RUNNABLE_STOP            0x17u   /* end of a runnable */
#define T1_TRIGGER_SYNC0            0x18u   /* .. 0x1Fu, low 3 bits are time */

#if defined T1_ENABLE && !defined T1_DISABLE_T1_SCOPE

#define T1_COMBINE_EVENT_INFO( event_, info_ )                                  \
( (((T1_uint16Least_t)(event_) << 10) & 0xFC00u) | ((T1_uint16Least_t)(info_) & 0x03FFu) )
#define T1_COMBINE_EVENT_INFO2( event_, info1_, info2_ )                        \
( (((T1_uint16Least_t)(event_) << 10) & 0xFC00u) | (((T1_uint16Least_t)(info1_) << 5) & 0x03E0u)  | ((T1_uint16Least_t)(info2_) & 0x001Fu) )

#define T1_TRACEDATA_UINT8          0x0u
#define T1_TRACEDATA_SINT8          0x1u
#define T1_TRACEDATA_UINT16         0x2u
#define T1_TRACEDATA_SINT16         0x3u
#define T1_TRACEDATA_UINT32         0x4u
#define T1_TRACEDATA_SINT32         0x5u
#define T1_TRACEDATA_UINT64         0x6u
#define T1_TRACEDATA_SINT64         0x7u
#define T1_TRACEDATA_FLOAT          0x8u
#define T1_TRACEDATA_ADDRESS        0x9u
#if defined T1_32BIT_TRACE_TIME
#   define T1_TRACEDATA_STR_REST0   0x200u
#   define T1_TRACEDATA_STR_REST1   0x201u
#   define T1_TRACEDATA_STR_REST2   0x202u
#   define T1_TRACEDATA_STR_REST3   0x203u
#   define T1_TRACEDATA_STR_REST4   0x204u
#   define T1_TRACEDATA_BIN_REST0   0x205u
#   define T1_TRACEDATA_BIN_REST1   0x206u
#   define T1_TRACEDATA_BIN_REST2   0x207u
#   define T1_TRACEDATA_BIN_REST3   0x208u
#   define T1_TRACEDATA_BIN_REST4   0x209u
#else /* 16 bit trace time */
#   define T1_TRACEDATA_STR_REST0   0xAu
#   define T1_TRACEDATA_STR_REST1   0xBu
#   define T1_TRACEDATA_STR_REST2   0xCu
#   define T1_TRACEDATA_BIN_REST0   0xDu
#   define T1_TRACEDATA_BIN_REST1   0xEu
#   define T1_TRACEDATA_BIN_REST2   0xFu
#endif /* defined T1_32BIT_TRACE_TIME */

#define T1_TRACEDATA( kind_, info_, pData_, len_ )                                  \
( T1_TraceData##kind_( T1_COMBINE_EVENT_INFO( T1_USERDATA_START, info_ ),           \
                       (pData_),                                                    \
                       (len_) ) )

#   if defined T1_USE_LOGIC
    /*------------------------------------------------------------------------------*/
    /*--- use logic analyser interface ---------------------------------------------*/
    /*------------------------------------------------------------------------------*/

#       define T1_START_SEC_CODE_FAST
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_LogicTraceEventNoSusp( T1_uint16Least_t eventInfo );
T1_EXTERN T1_status_t T1_CODE_FAST T1_NoTrigger( T1_nofEntries_t afterXevents );
#       define T1_STOP_SEC_CODE_FAST
#       include "T1_MemMap.h"

#       define T1_TraceEvent( a_, b_ )                                          \
    (T1_logicTraceEvent( T1_COMBINE_EVENT_INFO( a_, b_ ) ))
#       define T1_TraceEventFast( a_, b_ )                                      \
    (T1_logicTraceEvent( T1_COMBINE_EVENT_INFO( a_, b_ ) ))
#       define T1_TraceEventNoSusp( a_, b_ )                                    \
    (T1_logicTraceEvent( T1_COMBINE_EVENT_INFO( a_, b_ ) ))
#       define T1_TraceStart( taskId_ )                                         \
    ( T1_INCR_PREEMPTIONS( T1_TraceEvent( T1_START, taskId_ ) ) )
#       define T1_TraceStartFast( taskId_ )                                     \
    ( T1_INCR_PREEMPTIONS( T1_TraceEventFast( T1_START, taskId_ ) ) )
#       define T1_TraceStartNoSusp( taskId_ )                                   \
    ( T1_INCR_PREEMPTIONS( T1_TraceEventNoSusp( T1_START, taskId_ ) ) )
#       define T1_TraceStop( taskId_ )                                          \
    ( T1_DECR_PREEMPTIONS( T1_TraceEvent( T1_STOP, taskId_ ) ) )
#       define T1_TraceStopFast( taskId_ )                                      \
    ( T1_DECR_PREEMPTIONS( T1_TraceEventFast( T1_STOP, taskId_ ) ) )
#       define T1_TraceStopNoSusp( taskId_ )                                    \
    ( T1_DECR_PREEMPTIONS( T1_TraceEventNoSusp( T1_STOP, taskId_ ) ) )
#       define T1_TraceStopStart( stopTaskId_, startTaskId_ )                   \
    (T1_logicTraceEvent(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )))
#       define T1_TraceStopStartFast( stopTaskId_, startTaskId_ )               \
    (T1_logicTraceEvent(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )))
#       define T1_TraceStopStartNoSusp( stopTaskId_, startTaskId_ )             \
    (T1_logicTraceEvent(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )))

#       define T1_InitTraceBuffer( )
#       define T1_SetStopTrigger(afterXevents)          ((T1_status_t)T1_NOFUNC)
#       define T1_SetStopTriggerFast(afterXevents)      ((T1_status_t)T1_NOFUNC)
#       define T1_SetStopTriggerNoSusp(afterXevents)    ((T1_status_t)T1_NOFUNC)
#       define T1_RestartScope( )                       ((T1_status_t)T1_NOFUNC)

#       define T1_scopePlugin                           (&T1_scopeLogicPluginStruct)

#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_DeclarePlugin( T1_scopeLogicPluginStruct );
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_16
#       include "T1_MemMap.h"
T1_EXTERN volatile T1_traceCell_t T1_traceCell T1_SEC_NO_INIT_16;
#       define T1_STOP_SEC_NO_INIT_16
#       include "T1_MemMap.h"

#       define T1_logicTraceEvent( eventInfo_ )         \
                ( (void)(T1_traceCell = (T1_traceCell_t)eventInfo_) )

#   else /* !defined T1_USE_LOGIC */

#       define T1_scopePlugin       (&T1_scopePluginStruct)
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_DeclarePlugin( T1_scopePluginStruct );
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE
#       include "T1_MemMap.h"
T1_EXTERN void        T1_CODE T1_InitTraceBuffer( void );
T1_EXTERN void        T1_CODE T1_RestartScope( void );
#       define T1_SetStopTriggerFast( afterXevents_ ) T1_SetStopTrigger( afterXevents_ )
T1_EXTERN T1_status_t T1_CODE T1_SetStopTrigger( T1_nofEntries_t afterXevents );
T1_EXTERN T1_status_t T1_CODE T1_SetStopTriggerNoSusp( T1_nofEntries_t afterXevents );
T1_EXTERN void        T1_CODE T1_TraceEventCoreX_(    T1_uint16Least_t    eventInfo );
T1_EXTERN void        T1_CODE T1_TraceEventNoSuspCoreX_( T1_uint16Least_t eventInfo );
T1_EXTERN void        T1_CODE T1_TraceData_(        T1_uint16Least_t    eventInfo,
                                                    T1_uint8_t const   *pData,
                                                    T1_uint8Least_t     length  );
T1_EXTERN void        T1_CODE T1_TraceDataNoSusp_(  T1_uint16Least_t    eventInfo,
                                                    T1_uint8_t const   *pData,
                                                    T1_uint8Least_t     length  );
#       define T1_STOP_SEC_CODE
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_FAST
#       include "T1_MemMap.h"

/* the following global variables have to be provided (allocated) by the user */
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_EXTERN const T1_nofEntries_t                 T1_bufferSizePC[] T1_SEC_CONST_32;
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_EXTERN const T1_nofEntries_t                 T1_bufferSize T1_SEC_CONST_32;
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FARPTR const       T1_traceBufferPC[] T1_SEC_CONST_32;
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_TRACEBUFFER
#       include "T1_MemMap.h"
T1_EXTERN T1_traceEntry_t T1_FAR                T1_traceBuffer[] T1_SEC_NO_INIT_32_TRACEBUFFER;
#       define T1_STOP_SEC_NO_INIT_32_TRACEBUFFER
#       include "T1_MemMap.h"
#       if T1_USE_NEAR
#           define T1_START_SEC_CONST_16
#           include "T1_MemMap.h"
T1_EXTERN volatile T1_tickUint_t const T1_NEARPTR const T1_pTimer T1_SEC_CONST_16;
T1_EXTERN volatile T1_tickUint_t const T1_NEARPTR const T1_pSyncTimer T1_SEC_CONST_16;
#           define T1_STOP_SEC_CONST_16
#           include "T1_MemMap.h"
#           define T1_START_SEC_CONST_16
#           include "T1_MemMap.h"
T1_EXTERN volatile T1_tickUint_t const T1_NEARPTR const T1_pTimerPC[] T1_SEC_CONST_16;
#           define T1_STOP_SEC_CONST_16
#           include "T1_MemMap.h"
#       else /* ! T1_USE_NEAR */
#           define T1_START_SEC_CONST_32
#           include "T1_MemMap.h"
T1_EXTERN volatile T1_tickUint_t const T1_NEARPTR const T1_pTimer T1_SEC_CONST_32;
T1_EXTERN volatile T1_tickUint_t const T1_NEARPTR const T1_pSyncTimer T1_SEC_CONST_32;
#           define T1_STOP_SEC_CONST_32
#           include "T1_MemMap.h"
#           define T1_START_SEC_CONST_32
#           include "T1_MemMap.h"
T1_EXTERN volatile T1_tickUint_t const T1_NEARPTR const T1_pTimerPC[] T1_SEC_CONST_32;
#           define T1_STOP_SEC_CONST_32
#           include "T1_MemMap.h"
#       endif /* T1_USE_NEAR */

T1_EXTERN void T1_CODE_FAST T1_TraceEvent_(         T1_uint16Least_t    eventInfo );
T1_EXTERN void T1_CODE_FAST T1_TraceEventFast_(     T1_uint16Least_t    eventInfo );
T1_EXTERN void T1_CODE_FAST T1_TraceEventNoSusp_(   T1_uint16Least_t    eventInfo );
T1_EXTERN void T1_CODE_FAST T1_TraceSyncTimer(      T1_uint8Least_t     coreId );
T1_EXTERN void T1_CODE_FAST T1_TraceSyncTimerNoSusp( T1_uint8Least_t    coreId );
#       define T1_STOP_SEC_CODE_FAST
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_CORE0
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_TraceEventCore0_(    T1_uint16Least_t    eventInfo );
T1_EXTERN void T1_CODE_FAST T1_TraceEventNoSuspCore0_( T1_uint16Least_t eventInfo );
#       define T1_STOP_SEC_CODE_CORE0
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_CORE1
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_TraceEventCore1_(    T1_uint16Least_t    eventInfo );
T1_EXTERN void T1_CODE_FAST T1_TraceEventNoSuspCore1_( T1_uint16Least_t eventInfo );
#       define T1_STOP_SEC_CODE_CORE1
#       include "T1_MemMap.h"

#       define T1_START_SEC_CODE_CORE2
#       include "T1_MemMap.h"
T1_EXTERN void T1_CODE_FAST T1_TraceEventCore2_(    T1_uint16Least_t    eventInfo );
T1_EXTERN void T1_CODE_FAST T1_TraceEventNoSuspCore2_( T1_uint16Least_t eventInfo );
#       define T1_STOP_SEC_CODE_CORE2
#       include "T1_MemMap.h"

#       if defined T1_NOF_CORES && ! defined T1_MULTICORE_CLONE
#           if 1 == T1_NOF_CORES
#               define T1_TraceEvent( event_, info_ )                           \
                ( T1_TraceEventCore0_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#               define T1_TraceEventFast( event_, info_ )                       \
                ( T1_TraceEventCore0_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#           else /* multicore */
#               define T1_TraceEvent( event_, info_ )                           \
                ( T1_TraceEventCoreX_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#               define T1_TraceEventFast( event_, info_ )                       \
                ( T1_TraceEventCoreX_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#           endif /* T1_NOF_CORES */
#           define T1_TraceEventCore0( event_, info_ )                          \
            ( T1_TraceEventCore0_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#           define T1_TraceEventFastCore0( event_, info_ )                      \
            ( T1_TraceEventCore0_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#       else /* single core or multicore clone */
#           define T1_TraceEvent( event_, info_ )                               \
            ( T1_TraceEvent_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#           define T1_TraceEventFast( event_, info_ )                           \
            ( T1_TraceEventFast_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#           define T1_TraceEventCore0( event_, info_ )                          \
            ( T1_TraceEvent_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#           define T1_TraceEventFastCore0( event_, info_ )                      \
            ( T1_TraceEventFast_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#       endif /* T1_NOF_CORES */
#       define T1_TraceEventCore1( event_, info_ )                              \
        ( T1_TraceEventCore1_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#       define T1_TraceEventCore2( event_, info_ )                              \
        ( T1_TraceEventCore2_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#       define T1_TraceEventFastCore1( event_, info_ )                          \
        ( T1_TraceEventCore1_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#       define T1_TraceEventFastCore2( event_, info_ )                          \
        ( T1_TraceEventCore2_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#       if defined T1_NOF_CORES && ! defined T1_MULTICORE_CLONE
#           if 1 == T1_NOF_CORES
#               define T1_TraceEventNoSusp( event_, info_ )                     \
                ( T1_TraceEventNoSuspCore0_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#           else /* multicore */
#               define T1_TraceEventNoSusp( event_, info_ )                     \
                ( T1_TraceEventNoSuspCoreX_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#           endif /* T1_NOF_CORES */
#           define T1_TraceEventNoSuspCore0( event_, info_ )                    \
            ( T1_TraceEventNoSuspCore0_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#       else /* single core or multicore clone */
#           define T1_TraceEventNoSusp( event_, info_ )                         \
            ( T1_TraceEventNoSusp_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#           define T1_TraceEventNoSuspCore0( event_, info_ )                    \
            ( T1_TraceEventNoSusp_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#       endif /* T1_NOF_CORES */
#       define T1_TraceEventNoSuspCore1( event_, info_ )                        \
        ( T1_TraceEventNoSuspCore1_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#       define T1_TraceEventNoSuspCore2( event_, info_ )                        \
        ( T1_TraceEventNoSuspCore2_( T1_COMBINE_EVENT_INFO( event_, info_ ) ) )
#       define T1_TraceStart( taskId_ )                                         \
        ( T1_INCR_PREEMPTIONS( T1_TraceEvent( T1_START, taskId_ ) ) )
#       define T1_TraceStart( taskId_ )                                         \
        ( T1_INCR_PREEMPTIONS( T1_TraceEvent( T1_START, taskId_ ) ) )
#       define T1_TraceStartCore0( taskId_ )                                    \
        ( T1_INCR_PREEMPTIONS( T1_TraceEventCore0( T1_START, taskId_ ) ) )
#       define T1_TraceStartCore1( taskId_ )                                    \
        ( T1_INCR_PREEMPTIONS( T1_TraceEventCore1( T1_START, taskId_ ) ) )
#       define T1_TraceStartCore2( taskId_ )                                    \
        ( T1_INCR_PREEMPTIONS( T1_TraceEventCore2( T1_START, taskId_ ) ) )
#       define T1_TraceStartFast( taskId_ )                                     \
        ( T1_INCR_PREEMPTIONS( T1_TraceEventFast( T1_START, taskId_ ) ) )
#       define T1_TraceStartFastCore0( taskId_ )                                \
        ( T1_INCR_PREEMPTIONS( T1_TraceEventCore0( T1_START, taskId_ ) ) )
#       define T1_TraceStartFastCore1( taskId_ )                                \
        ( T1_INCR_PREEMPTIONS( T1_TraceEventCore1( T1_START, taskId_ ) ) )
#       define T1_TraceStartFastCore2( taskId_ )                                \
        ( T1_INCR_PREEMPTIONS( T1_TraceEventCore2( T1_START, taskId_ ) ) )
#       define T1_TraceStartNoSusp( taskId_ )                                   \
        ( T1_INCR_PREEMPTIONS( T1_TraceEventNoSusp( T1_START, taskId_ ) ) )
#       define T1_TraceStartNoSuspCore0( taskId_ )                              \
        ( T1_INCR_PREEMPTIONS( T1_TraceEventNoSuspCore0( T1_START, taskId_ ) ) )
#       define T1_TraceStartNoSuspCore1( taskId_ )                              \
        ( T1_INCR_PREEMPTIONS( T1_TraceEventNoSuspCore1( T1_START, taskId_ ) ) )
#       define T1_TraceStartNoSuspCore2( taskId_ )                              \
        ( T1_INCR_PREEMPTIONS( T1_TraceEventNoSuspCore2( T1_START, taskId_ ) ) )
#       define T1_TraceStop( taskId_ )                                          \
        ( T1_DECR_PREEMPTIONS( T1_TraceEvent( T1_STOP, taskId_ ) ) )
#       define T1_TraceStopCore0( taskId_ )                                     \
        ( T1_DECR_PREEMPTIONS( T1_TraceEventCore0( T1_STOP, taskId_ ) ) )
#       define T1_TraceStopCore1( taskId_ )                                     \
        ( T1_DECR_PREEMPTIONS( T1_TraceEventCore1( T1_STOP, taskId_ ) ) )
#       define T1_TraceStopCore2( taskId_ )                                     \
        ( T1_DECR_PREEMPTIONS( T1_TraceEventCore2( T1_STOP, taskId_ ) ) )
#       define T1_TraceStopFast( taskId_ )                                      \
        ( T1_DECR_PREEMPTIONS( T1_TraceEventFast( T1_STOP, taskId_ ) ) )
#       define T1_TraceStopFastCore0( taskId_ )                                 \
        ( T1_DECR_PREEMPTIONS( T1_TraceEventCore0( T1_STOP, taskId_ ) ) )
#       define T1_TraceStopFastCore1( taskId_ )                                 \
        ( T1_DECR_PREEMPTIONS( T1_TraceEventCore1( T1_STOP, taskId_ ) ) )
#       define T1_TraceStopFastCore2( taskId_ )                                 \
        ( T1_DECR_PREEMPTIONS( T1_TraceEventCore2( T1_STOP, taskId_ ) ) )
#       define T1_TraceStopNoSusp( taskId_ )                                    \
        ( T1_DECR_PREEMPTIONS( T1_TraceEventNoSusp( T1_STOP, taskId_ ) ) )
#       define T1_TraceStopNoSuspCore0( taskId_ )                               \
        ( T1_DECR_PREEMPTIONS( T1_TraceEventNoSuspCore0( T1_STOP, taskId_ ) ) )
#       define T1_TraceStopNoSuspCore1( taskId_ )                               \
        ( T1_DECR_PREEMPTIONS( T1_TraceEventNoSuspCore1( T1_STOP, taskId_ ) ) )
#       define T1_TraceStopNoSuspCore2( taskId_ )                               \
        ( T1_DECR_PREEMPTIONS( T1_TraceEventNoSuspCore2( T1_STOP, taskId_ ) ) )
#       if defined T1_NOF_CORES && ! defined T1_MULTICORE_CLONE
#           if 1 == T1_NOF_CORES
#               define T1_TraceStopStart( stopTaskId_, startTaskId_ )           \
                ( T1_TraceEventCore0_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#               define T1_TraceStopStartFast( stopTaskId_, startTaskId_ )       \
                ( T1_TraceEventCore0_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#           else /* multicore */
#               define T1_TraceStopStart( stopTaskId_, startTaskId_ )           \
                ( T1_TraceEventCoreX_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#               define T1_TraceStopStartFast( stopTaskId_, startTaskId_ )       \
                ( T1_TraceEventCoreX_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#           endif /* 1 == T1_NOF_CORES */
#           define T1_TraceStopStartCore0( stopTaskId_, startTaskId_ )          \
            ( T1_TraceEventCore0_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#           define T1_TraceStopStartFastCore0( stopTaskId_, startTaskId_ )      \
            ( T1_TraceEventCore0_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#           define T1_TraceStopStartNoSuspCore0( stopTaskId_, startTaskId_ )    \
            ( T1_TraceEventNoSuspCore0_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#       else /* Single core or multicore clone */
#           define T1_TraceStopStart( stopTaskId_, startTaskId_ )               \
            ( T1_TraceEvent_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#           define T1_TraceStopStartFast( stopTaskId_, startTaskId_ )           \
            ( T1_TraceEventFast_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#           define T1_TraceStopStartCore0( stopTaskId_, startTaskId_ )          \
            ( T1_TraceEvent_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#           define T1_TraceStopStartFastCore0( stopTaskId_, startTaskId_ )      \
            ( T1_TraceEvent_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#           define T1_TraceStopStartNoSuspCore0( stopTaskId_, startTaskId_ )    \
            ( T1_TraceEventNoSusp_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#       endif /* T1_NOF_CORES */
#       define T1_TraceStopStartCore1( stopTaskId_, startTaskId_ )              \
        ( T1_TraceEventCore1_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#       define T1_TraceStopStartCore2( stopTaskId_, startTaskId_ )              \
        ( T1_TraceEventCore2_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#       define T1_TraceStopStartFastCore1( stopTaskId_, startTaskId_ )          \
        ( T1_TraceEventCore1_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#       define T1_TraceStopStartFastCore2( stopTaskId_, startTaskId_ )          \
        ( T1_TraceEventCore2_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#       define T1_TraceStopStartNoSusp( stopTaskId_, startTaskId_ )             \
        ( T1_TraceEventNoSusp_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#       define T1_TraceStopStartNoSuspCore1( stopTaskId_, startTaskId_ )        \
        ( T1_TraceEventNoSuspCore1_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#       define T1_TraceStopStartNoSuspCore2( stopTaskId_, startTaskId_ )        \
        ( T1_TraceEventNoSuspCore2_(T1_COMBINE_EVENT_INFO2( T1_STOP_START, stopTaskId_, startTaskId_ )) )
#       define T1_TraceData( id_, kind_, pData_, len_ )                         \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (kind_), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceDataFast( id_, kind_, pData_, len_ )                     \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (kind_), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceDataNoSusp( id_, kind_, pData_, len_ )                   \
        T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | (kind_), (T1_uint8_t const *)(pData_), (len_) )
#       define T1_TraceUint16( id_, ui16_ )                                     \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT16, (T1_uint8_t const *)&(ui16_), 2u )
#       define T1_TraceUint16Fast( id_, ui16_ )                                 \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT16, (T1_uint8_t const *)&(ui16_), 2u )
#       define T1_TraceUint16NoSusp( id_, ui16_ )                               \
        T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT16, (T1_uint8_t const *)&(ui16_), 2u )
#       define T1_TraceUint32( id_, ui32_ )                                     \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT32, (T1_uint8_t const *)&(ui32_), 4u )
#       define T1_TraceUint32Fast( id_, ui32_ )                                 \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT32, (T1_uint8_t const *)&(ui32_), 4u )
#       define T1_TraceUint32NoSusp( id_, ui32_ )                               \
        T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_UINT32, (T1_uint8_t const *)&(ui32_), 4u )
#       define T1_TraceSint16( id_, si16_ )                                     \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT16, (T1_uint8_t const *)&(si16_), 2u )
#       define T1_TraceSint16Fast( id_, si16_ )                                 \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT16, (T1_uint8_t const *)&(si16_), 2u )
#       define T1_TraceSint16NoSusp( id_, si16_ )                               \
        T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT16, (T1_uint8_t const *)&(si16_), 2u )
#       define T1_TraceSint32( id_, si32_ )                                     \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT32, (T1_uint8_t const *)&(si32_), 4u )
#       define T1_TraceSint32Fast( id_, si32_ )                                 \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT32, (T1_uint8_t const *)&(si32_), 4u )
#       define T1_TraceSint32NoSusp( id_, si32_ )                               \
        T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_SINT32, (T1_uint8_t const *)&(si32_), 4u )
#       define T1_TraceAddr( id_, addr_ )                                       \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_ADDRESS, (T1_uint8_t const *)&(addr_), 4u )
#       define T1_TraceAddrFast( id_, addr_ )                                   \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_ADDRESS, (T1_uint8_t const *)&(addr_), 4u )
#       define T1_TraceAddrNoSusp( id_, addr_ )                                 \
        T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | T1_TRACEDATA_ADDRESS, (T1_uint8_t const *)&(addr_), 4u )
#       if defined T1_32BIT_TRACE_TIME
#           define T1_TraceString( id_, pData_, len_ )                              \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#           define T1_TraceStringFast( id_, pData_, len_ )                          \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#           define T1_TraceStringNoSusp( id_, pData_, len_ )                        \
        T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#           define T1_TraceBinary( id_, pData_, len_ )                              \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#           define T1_TraceBinaryFast( id_, pData_, len_ )                          \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#           define T1_TraceBinaryNoSusp( id_, pData_, len_ )                        \
        T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 5), (T1_uint8_t const *)(pData_), (len_) )
#       else /* 16 bit trace time */
#           define T1_TraceString( id_, pData_, len_ )                              \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#           define T1_TraceStringFast( id_, pData_, len_ )                          \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#           define T1_TraceStringNoSusp( id_, pData_, len_ )                        \
        T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_STR_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#           define T1_TraceBinary( id_, pData_, len_ )                              \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#           define T1_TraceBinaryFast( id_, pData_, len_ )                          \
        T1_TRACEDATA( _, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#           define T1_TraceBinaryNoSusp( id_, pData_, len_ )                        \
        T1_TRACEDATA( NoSusp_, (((id_) & 0x1Fu) << 4) | (T1_TRACEDATA_BIN_REST0 + (len_) % 3), (T1_uint8_t const *)(pData_), (len_) )
#       endif /* defined T1_32BIT_TRACE_TIME */
#       define T1_TraceSyncTimerFast( core_ )           T1_TraceSyncTimer( core_ )
        /* Deprecated */
#       define T1_TraceSync( pTime_ )                   ((void)0)
#       define T1_TraceSyncFast( pTime_ )               ((void)0)
#       define T1_TraceSyncNoSusp( pTime_ )             ((void)0)
#   endif /* #if defined T1_USE_LOGIC */

#   define T1_TraceEventPerFeature( event_, info_, mask_ )              \
    do                                                                  \
    {                                                                   \
        if( T1_IsFeatureEnabled( mask_ ) )                              \
        {                                                               \
            T1_TraceEvent( event_, info_ );                             \
        }                                                               \
    }                                                                   \
    while( 0 )
#   define T1_TraceEventFastPerFeature( event_, info_, mask_ )          \
    do                                                                  \
    {                                                                   \
        if( T1_IsFeatureEnabled( mask_ ) )                              \
        {                                                               \
            T1_TraceEventFast( event_, info_ );                         \
        }                                                               \
    }                                                                   \
    while( 0 )
#   define T1_TraceEventNoSuspPerFeature( event_, info_, mask_ )        \
    do                                                                  \
    {                                                                   \
        if( T1_IsFeatureEnabled( mask_ ) )                              \
        {                                                               \
            T1_TraceEventNoSusp( event_, info_ );                       \
        }                                                               \
    }                                                                   \
    while( 0 )

#else /* #if defined T1_ENABLE && !defined T1_DISABLE_T1_SCOPE */
#   define T1_scopePlugin (T1_DISABLED_PLUGIN)
/* empty macros */
#   define T1_InitTraceBuffer( )                    ((void)0)
#   define T1_TraceEvent( event_, info_ )           ((void)0)
#   define T1_TraceEventCore0( event_, info_ )      ((void)0)
#   define T1_TraceEventCore1( event_, info_ )      ((void)0)
#   define T1_TraceEventCore2( event_, info_ )      ((void)0)
#   define T1_TraceEventFast( event_, info_ )       ((void)0)
#   define T1_TraceEventFastCore0( event_, info_ )  ((void)0)
#   define T1_TraceEventFastCore1( event_, info_ )  ((void)0)
#   define T1_TraceEventFastCore2( event_, info_ )  ((void)0)
#   define T1_TraceEventNoSusp( event_, info_ )     ((void)0)
#   define T1_TraceEventNoSuspCore0( event_, info_ ) ((void)0)
#   define T1_TraceEventNoSuspCore1( event_, info_ ) ((void)0)
#   define T1_TraceEventNoSuspCore2( event_, info_ ) ((void)0)
#   define T1_TraceStart( taskId_ )                 ((void)0)
#   define T1_TraceStartFast( taskId_ )             ((void)0)
#   define T1_TraceStartNoSusp( taskId_ )           ((void)0)
#   define T1_TraceStartNoSuspCore0( taskId_ )      ((void)0)
#   define T1_TraceStartNoSuspCore1( taskId_ )      ((void)0)
#   define T1_TraceStartNoSuspCore2( taskId_ )      ((void)0)
#   define T1_TraceStop( taskId_ )                  ((void)0)
#   define T1_TraceStopFast( taskId_ )              ((void)0)
#   define T1_TraceStopNoSusp( taskId_ )            ((void)0)
#   define T1_TraceStopNoSuspCore0( taskId_ )       ((void)0)
#   define T1_TraceStopNoSuspCore1( taskId_ )       ((void)0)
#   define T1_TraceStopNoSuspCore2( taskId_ )       ((void)0)
#   define T1_TraceStopStart( stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceStopStartFast( stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceStopStartNoSusp( stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceStopStartNoSuspCore0( stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceStopStartNoSuspCore1( stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceStopStartNoSuspCore2( stopTaskId_, startTaskId_ ) ((void)0)
#   define T1_TraceData( id_, kind_, pData_, len_ ) ((void)0)
#   define T1_TraceDataFast( id_, kind_, pData_, len_ ) ((void)0)
#   define T1_TraceDataNoSusp( id_, kind_, pData_, len_ ) ((void)0)
#   define T1_TraceUint16( id_, ui16_ )             ((void)0)
#   define T1_TraceUint16Fast( id_, ui16_ )         ((void)0)
#   define T1_TraceUint16NoSusp( id_, ui16_ )       ((void)0)
#   define T1_TraceUint32( id_, ui32_ )             ((void)0)
#   define T1_TraceUint32Fast( id_, ui32_ )         ((void)0)
#   define T1_TraceUint32NoSusp( id_, ui32_ )       ((void)0)
#   define T1_TraceAddr( id_, addr_ )               ((void)0)
#   define T1_TraceAddrFast( id_, addr_ )           ((void)0)
#   define T1_TraceAddrNoSusp( id_, addr_ )         ((void)0)
#   define T1_TraceString( id_, pData_, len_ )      ((void)0)
#   define T1_TraceStringFast( id_, pData_, len_ )  ((void)0)
#   define T1_TraceStringNoSusp( id_, pData_, len_ ) ((void)0)
#   define T1_TraceBinary( id_, pData_, len_ )      ((void)0)
#   define T1_TraceBinaryFast( id_, pData_, len_ )  ((void)0)
#   define T1_TraceBinaryNoSusp( id_, pData_, len_ ) ((void)0)
#   define T1_TraceSync( pTime_ )                   ((void)0)
#   define T1_TraceSyncFast( pTime_ )               ((void)0)
#   define T1_TraceSyncNoSusp( pTime_ )             ((void)0)
#   define T1_TraceSyncTimer( core_ )               ((void)0)
#   define T1_TraceSyncTimerFast( core_ )           ((void)0)
#   define T1_TraceSyncTimerNoSusp( core_ )         ((void)0)
#   define T1_SetStopTrigger(afterXevents)          ((T1_status_t)T1_FAILED)
#   define T1_SetStopTriggerFast(afterXevents)      ((T1_status_t)T1_FAILED)
#   define T1_RestartScope( )                       ((T1_status_t)T1_NOFUNC)
#   define T1_TraceEventPerFeature( event_, info_, mask_ )          ((void)0)
#   define T1_TraceEventFastPerFeature( event_, info_, mask_ )      ((void)0)
#   define T1_TraceEventNoSuspPerFeature( event_, info_, mask_ )    ((void)0)
#endif

/*----------------------------------------------------------------------------------*/
/*--- forward declarations for user functions --------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_START_SEC_CODE_FAST
#include "T1_MemMap.h"

/*
 * the following function has to be provided by the user
 * only if using a user-defined T1_GetTraceTime or T1.delay
 */
T1_EXTERN T1_tickUint_t T1_CODE_FAST T1_GetTraceTime( void );

#define T1_STOP_SEC_CODE_FAST
#include "T1_MemMap.h"

#endif /* T1_SCOPE_INTERFACE_H_ */
