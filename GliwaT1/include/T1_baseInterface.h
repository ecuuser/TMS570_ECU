/*************************************************************************************
*   FILE:           T1_baseInterface.h
*
*   DESCRIPTION:    T1 base interface
*
*   VISIBILITY:     extern
*
*   $Author: nick $
*
*   $Revision: 13953 $
*
*   $URL: https://gliwa.com/svn/repos/T1target/trunk/src/T1.base/src/all/T1_baseInterface.h $
*
*   Copyright:      Gliwa GmbH | know- how in embedded software
*                   Weilheim i.OB.
*                   All rights reserved
*************************************************************************************/

#ifndef T1_BASE_INTERFACE_H_
#define T1_BASE_INTERFACE_H_ (1)

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include "T1_targetSpecifics.h"

/*----------------------------------------------------------------------------------*/
/*--- macros -----------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#ifndef T1_EXTERN
#   if defined __cplusplus
#       define T1_EXTERN        extern "C"
#   else
#       define T1_EXTERN        extern
#   endif
#endif

#ifndef T1_FAR
#   define T1_FAR
#endif

#ifndef T1_FARPTR
#   define T1_FARPTR            *
#endif

#ifdef T1_NEAR
#   define T1_USE_NEAR          (1)
#else
#   define T1_USE_NEAR          (0)
#   define T1_NEAR
#endif

#ifndef T1_NEARPTR
#   define T1_NEARPTR           *
#endif

#ifndef T1_NULL
#   define T1_NULL              ((void *)0)
#endif

#ifndef T1_INLINE
#   define T1_INLINE
#endif

#ifndef T1_CORE0
#   define T1_CORE0
#endif

#ifndef T1_CORE1
#   define T1_CORE1
#endif

#ifndef T1_CORE2
#   define T1_CORE2
#endif

#ifndef T1_SEC_CONST_32
#   define T1_SEC_CONST_32
#endif

#ifndef T1_SEC_CONST_16
#   define T1_SEC_CONST_16
#endif

#ifndef T1_SEC_CONST_8
#   define T1_SEC_CONST_8
#endif

#ifndef T1_SEC_CONST_32_CLONE
#   define T1_SEC_CONST_32_CLONE
#endif

#ifndef T1_SEC_CONST_16_CLONE
#   define T1_SEC_CONST_16_CLONE
#endif

#ifndef T1_SEC_CONST_8_CLONE
#   define T1_SEC_CONST_8_CLONE
#endif

#ifndef T1_CODE
#   define T1_CODE
#endif

#ifndef T1_FAR_CODE
#   define T1_FAR_CODE T1_CODE
#endif

#ifndef T1_CODE_FAST
#   define T1_CODE_FAST T1_CODE
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER
#   define T1_SEC_NO_INIT_32_TRACEBUFFER
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE0
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE0
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE1
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE1
#endif

#ifndef T1_SEC_NO_INIT_32_TRACEBUFFER_CORE2
#   define T1_SEC_NO_INIT_32_TRACEBUFFER_CORE2
#endif

#ifndef T1_SEC_NEAR_NO_INIT_32
#   define T1_SEC_NEAR_NO_INIT_32
#endif

#ifndef T1_SEC_NO_INIT_32
#   define T1_SEC_NO_INIT_32
#endif

#ifndef T1_SEC_NO_INIT_32_CORE0
#   define T1_SEC_NO_INIT_32_CORE0
#endif

#ifndef T1_SEC_NO_INIT_32_CORE1
#   define T1_SEC_NO_INIT_32_CORE1
#endif

#ifndef T1_SEC_NO_INIT_32_CORE2
#   define T1_SEC_NO_INIT_32_CORE2
#endif

#ifndef T1_SEC_NEAR_NO_INIT_16
#   define T1_SEC_NEAR_NO_INIT_16
#endif

#ifndef T1_SEC_NO_INIT_16
#   define T1_SEC_NO_INIT_16
#endif

#ifndef T1_SEC_NEAR_NO_INIT_8
#   define T1_SEC_NEAR_NO_INIT_8
#endif

#ifndef T1_SEC_NO_INIT_8
#   define T1_SEC_NO_INIT_8
#endif

#ifndef T1_SEC_NO_INIT_8_CORE0
#   define T1_SEC_NO_INIT_8_CORE0
#endif

#ifndef T1_SEC_NO_INIT_8_CORE1
#   define T1_SEC_NO_INIT_8_CORE1
#endif

#ifndef T1_SEC_NO_INIT_8_CORE2
#   define T1_SEC_NO_INIT_8_CORE2
#endif

#ifndef T1_SEC_NO_INIT_32_CLONE
#   define T1_SEC_NO_INIT_32_CLONE
#endif

#ifndef T1_SEC_NO_INIT_16_CLONE
#   define T1_SEC_NO_INIT_16_CLONE
#endif

#ifndef T1_SEC_NO_INIT_8_CLONE
#   define T1_SEC_NO_INIT_8_CLONE
#endif

#ifndef T1_STRING
#   define T1_STRING
#endif

#ifndef T1_TRACEBUFFER
#   define T1_TRACEBUFFER
#endif

#define T1_DeclarePlugin(x)         T1_EXTERN struct T1_pluginStruct const x T1_SEC_CONST_32
#define T1_DeclarePluginTable(x)    T1_EXTERN T1_pluginTable_t x T1_SEC_CONST_32
#define T1_DISABLED_PLUGIN          ((T1_pPlugin_t)-1)

#define T1_BASE_PLUGIN_ID           (0u)

/*----------------------------------------------------------------------------------*/
#ifdef T1_ENABLE
#   define T1_basePlugin            (&T1_basePluginStruct)
#else
#   define T1_basePlugin            (T1_DISABLED_PLUGIN)
#endif

#define T1_ERR_MASK                 ((T1_status_t)0x80u)
#define T1_IS_ERROR(errCode_)       (((errCode_) & T1_ERR_MASK) == T1_ERR_MASK)

#define T1_OK                       ((T1_status_t)0x00u)
#define T1_YES                      ((T1_status_t)0x01u)
#define T1_NO                       ((T1_status_t)0x02u)

/* the following return code indicates the service did not perform any action */
#define T1_NOFUNC                   ((T1_status_t)0x03u)

/* the following return codes indicate the execution of the service failed */
#define T1_FAILED                   ((T1_status_t)0x80u)
#define T1_BUSY                     ((T1_status_t)0x81u)
#define T1_NOTINITIALIZED           ((T1_status_t)0x82u)
#define T1_PLUGIN_NOT_AVAILABLE     ((T1_status_t)0x83u)
#define T1_VALUE                    ((T1_status_t)0x84u)
#define T1_INVALID_COMMAND          ((T1_status_t)0x85u)
#define T1_NOT_IN_PRIVILEGED_MODE   ((T1_status_t)0x86u)
#define T1_INVALID_ACCESS_MASK      ((T1_status_t)0x87u)
#define T1_NOT_SUPPORTED_BY_TARGET  ((T1_status_t)0x88u)
#define T1_EXTERNAL_DEBUG           ((T1_status_t)0x89u)

#ifdef T1_ENABLE

#   define T1_IsFeatureEnabled( mask_ )                             \
    ( (T1_featureMask & (T1_featureMask_t)(mask_)) != 0uL )

#   define T1_ALLOCATE_PLUGIN_TABLE( pluginTable_ )                 \
T1_pluginTable_t pluginTable_ T1_SEC_CONST_32 =                     \
{                                                                   \
    T1_basePlugin,                                                  \
    T1_scopePlugin,                                                 \
    T1_flexPlugin,                                                  \
    T1_delayPlugin,                                                 \
    T1_modPlugin,                                                   \
    T1_contPlugin                                                   \
};

#   define T1_ALLOCATE_PLUGIN_TABLE_NO_T1_FLEX( pluginTable_ )      \
T1_pluginTable_t pluginTable_ T1_SEC_CONST_32 =                     \
{                                                                   \
    T1_basePlugin,                                                  \
    T1_scopePlugin,                                                 \
    T1_DISABLED_PLUGIN,                                             \
    T1_delayPlugin,                                                 \
    T1_modPlugin,                                                   \
    T1_contPlugin                                                   \
};

#   define T1_CAT_( x_, y_ ) x_ ## y_
#   define T1_CAT( x_, y_ )  T1_CAT_( x_, y_ )

#else

#   define T1_IsFeatureEnabled( mask_ ) (0)
#   define T1_ALLOCATE_PLUGIN_TABLE( pluginTable_ )

#endif /* #ifdef T1_ENABLE */

/*----------------------------------------------------------------------------------*/
/*--- type definitions -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_CPU8BIT /* CPU has 8-bit registers */
typedef unsigned char           T1_uint8Least_t;
typedef unsigned short          T1_uint16Least_t;
typedef unsigned long           T1_uint32Least_t;
#elif defined T1_CPU16BIT /* CPU has 16-bit registers and no 8-bit registers */
typedef unsigned short          T1_uint8Least_t;
typedef unsigned short          T1_uint16Least_t;
typedef unsigned long           T1_uint32Least_t;
#elif defined T1_CPU32BIT /* CPU has 32-bit registers and no 8- or 16-bit registers */
typedef unsigned long           T1_uint8Least_t;
typedef unsigned long           T1_uint16Least_t;
typedef unsigned long           T1_uint32Least_t;
#else
#   error T1_CPU<n>BIT not defined
#endif

/* Usually platform independent */
typedef unsigned char           T1_uint8_t;
typedef unsigned short          T1_uint16_t;
typedef unsigned long           T1_uint32_t;

/* Types for more than one plug-in */
#if defined T1_32BIT_TRACE_TIME
typedef T1_uint32_t             T1_tick_t;      /* Used for storage */
#   define T1_MAX_TICK_T        ((T1_tick_t)0xFFFFFFFFuL)
typedef T1_uint32Least_t        T1_tickUint_t;  /* Never used for storage */
#else /* 16 bit time is default */
typedef T1_uint16_t             T1_tick_t;      /* Used for storage */
#   define T1_MAX_TICK_T        ((T1_tick_t)0xFFFFu)
typedef T1_uint16Least_t        T1_tickUint_t;  /* Never used for storage */
#endif /* T1_32BIT_TRACE_TIME */

typedef T1_uint8_t              T1_event_t;
typedef T1_uint8_t              T1_info_t;

typedef T1_uint8Least_t         T1_bool_t;
#define T1_TRUE                 ((T1_bool_t)1u)
#define T1_FALSE                ((T1_bool_t)0u)

typedef T1_uint8Least_t         T1_status_t;

/*----------------------------------------------------------------------------------*/
typedef T1_uint8_t              T1_pluginID_t;
/*----------------------------------------------------------------------------------*/
struct T1_pluginStruct;
typedef struct T1_pluginStruct const * T1_pPlugin_t;
typedef T1_pPlugin_t const      T1_pluginTable_t[];
/*----------------------------------------------------------------------------------*/
typedef T1_uint32_t             T1_featureMask_t;
/*----------------------------------------------------------------------------------*/
typedef struct
{
    union
    {
        T1_uint8_t  u8 [8];
        T1_uint16_t u16[4];
        T1_uint32_t u32[2];
    } d;
} T1_rawData_t;
/*----------------------------------------------------------------------------------*/
typedef struct {
    T1_uint16_t     gcpRx;
    T1_uint16_t     gcpTx;
    T1_uint16_t     t1response;
} T1_timeouts_t;

/*----------------------------------------------------------------------------------*/
/*--- external declarations for global variables -----------------------------------*/
/*----------------------------------------------------------------------------------*/

#ifdef T1_ENABLE

#   define T1_START_SEC_CONST_8
#   include "T1_MemMap.h"
T1_EXTERN const T1_uint8_t              T1_sid T1_SEC_CONST_8;
#   define T1_STOP_SEC_CONST_8
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_DeclarePlugin( T1_basePluginStruct );
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_EXTERN const T1_featureMask_t        T1_initFeatureMask T1_SEC_CONST_32;
T1_EXTERN T1_uint8_t const * const T1_pBid T1_SEC_CONST_32;
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_NO_INIT_32
#   include "T1_MemMap.h"
T1_EXTERN T1_featureMask_t              T1_featureMask T1_SEC_NO_INIT_32;
#   define T1_STOP_SEC_NO_INIT_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_8
#   include "T1_MemMap.h"

T1_EXTERN const T1_uint8_t              T1_traceTimerCountsDown T1_SEC_CONST_8;
T1_EXTERN const T1_uint8_t              T1_traceTimerCountsDownPC[] T1_SEC_CONST_8;

/*
 * The following global variable can be defined by the user to allow a 32-bit core
 * to return value with less than 32 bits (e.g. 16 bits ) from T1_GetTraceTime.
 */
#   ifdef T1_CPU32BIT
T1_EXTERN const T1_uint8_t              T1_32BitCoreWith16BitTimer T1_SEC_CONST_8;
T1_EXTERN const T1_uint8_t              T1_32BitCoreWith16BitTimerPC[] T1_SEC_CONST_8;
#   endif /* T1_CPU32BIT */

T1_EXTERN const T1_uint8_t              T1_nofCores T1_SEC_CONST_8;
T1_EXTERN const T1_uint8_t              T1_commsCoreOffset T1_SEC_CONST_8;

#   define T1_STOP_SEC_CONST_8
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_16
#   include "T1_MemMap.h"
T1_EXTERN const T1_timeouts_t           T1_timeouts T1_SEC_CONST_16;
#   define T1_STOP_SEC_CONST_16
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_EXTERN const T1_uint32_t             T1_bid T1_SEC_CONST_32;
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#endif /* #ifdef T1_ENABLE */

/*----------------------------------------------------------------------------------*/
/*--- forward declarations for global functions ------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_START_SEC_CODE
#include "T1_MemMap.h"

/*
 * For safety reasons, the services T1_SuspendAllInterrupts() and
 * T1_ResumeAllInterrupts() are present even if T1_ENABLE is not defined, i.e.
 * T1 is disabled. Thus, these services are not encapsulated by
 * #ifdef T1_ENABLE / #endif
 *
 * T1_SuspendAllInterrupts inhibits all interrupts.
 * T1_ResumeAllInterrupts restores interrupt processing.
 * These functions can safely be nested.
 * The default implementations directly disable and reenable interrupts so they have
 * to be over-ridden (implemented) by the user if any of T1_SetStopTrigger,
 * T1_SetStopTriggerFast, T1_ResetScope, T1_RestartScope or T1_Handler are called from
 * contexts without permission to directly disable interrupts.
 */
T1_EXTERN void T1_CODE T1_SuspendAllInterrupts( void );
T1_EXTERN void T1_CODE T1_ResumeAllInterrupts( void );

#ifdef T1_ENABLE

/* The following funtions have to be *called* by the user */
T1_EXTERN T1_status_t T1_CODE T1_Handler( void );
T1_EXTERN T1_status_t T1_CODE T1_Init( T1_pluginTable_t pluginTable );

/*
 * T1_AppDisableT1Handler must inhibit scheduling of the task that calls T1_Handler.
 * T1_AppEnableT1Handler must restore scheduling again.
 * The default implementations disable and reenable interrupts using
 * T1_SuspendAllInterrupts and T1_ResumeAllInterrupts so they have to be
 * over-ridden (implemented) by the user if T1_ContBgHandler is called from contexts
 * without permission to directly disable interrupts. For example, OS resource locks
 * might be used to achieve the required mutual exclusion.
 * For efficiency, they can also be over-ridden with empty functions if the task that
 * calls T1_Handler cannot, in any case, preempt the background task.
 */
T1_EXTERN void T1_CODE T1_AppDisableT1Handler( void );
T1_EXTERN void T1_CODE T1_AppEnableT1Handler( void );

T1_EXTERN T1_status_t T1_CODE T1_TxValue( T1_uint16_t val );
#define T1_DisablePlugin( pluginId_ )                       \
(                                                           \
    ( 4u < (T1_uint8Least_t)((pluginId_) - 1) )             \
    ? T1_PLUGIN_NOT_AVAILABLE                               \
    : T1_DisablePlugin_( ~((T1_uint8_t)1 << (pluginId_)) )  \
)
T1_EXTERN T1_status_t T1_CODE T1_DisablePlugin_( T1_uint8_t pluginDisableMask );

#else /* #ifdef T1_ENABLE */

#   define T1_Handler( )                        (T1_PLUGIN_NOT_AVAILABLE)
#   define T1_Init( pPluginTable_ )             (T1_PLUGIN_NOT_AVAILABLE)
#   define T1_TxValue( val_ )                   (T1_PLUGIN_NOT_AVAILABLE)
#   define T1_DisablePlugin( pluginId_ )        (T1_PLUGIN_NOT_AVAILABLE)

#endif /* #else defined T1_ENABLE */

/*
 * The following function has to be provided (implemented) by the user to transmit an
 * 8-byte frame.
 */
T1_EXTERN T1_status_t T1_CODE T1_Transmit( T1_rawData_t const T1_FARPTR pData );
/*
 * The following function has to be called by the user when an 8-byte frame arrives.
 */
T1_EXTERN T1_status_t T1_CODE T1_RxCallback( T1_rawData_t const *pData );

/*----------------------------------------------------------------------------------*/

#define T1_STOP_SEC_CODE
#include "T1_MemMap.h"

#endif /* T1_BASE_INTERFACE_H_ */
