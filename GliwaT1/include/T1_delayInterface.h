/*************************************************************************************
*   FILE:           T1_delayInterface.h
*
*   DESCRIPTION:    T1 delay interface
*
*   VISIBILITY:     extern
*
*   $Author: nick $
*
*   $Revision: 10788 $
*
*   $URL: https://gliwa.com/svn/repos/T1target/trunk/src/T1.delay/src/all/T1_delayInterface.h $
*
*   Copyright:      Gliwa GmbH | know- how in embedded software
*                   Weilheim i.OB.
*                   All rights reserved
*************************************************************************************/

#ifndef T1_DELAY_INTERFACE_H_
#define T1_DELAY_INTERFACE_H_ (1)

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include "T1_baseInterface.h"

/*----------------------------------------------------------------------------------*/
/*--- type definitions -------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

typedef T1_uint8_t              T1_delayId_t;
typedef T1_uint32_t             T1_delay_t;

/*----------------------------------------------------------------------------------*/
/*--- external declarations for global variables -----------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_EXTERN T1_delay_t    * const T1_delaysPC[] T1_SEC_CONST_32;
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_DeclarePlugin( T1_delayPluginStruct );
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_NO_INIT_32
#   include "T1_MemMap.h"
T1_EXTERN T1_delay_t            T1_delays[] T1_SEC_NO_INIT_32;
#   define T1_STOP_SEC_NO_INIT_32
#   include "T1_MemMap.h"

#   define T1_START_SEC_CONST_8
#   include "T1_MemMap.h"
T1_EXTERN T1_uint8_t const      T1_nofDelaysPC[] T1_SEC_CONST_8;
T1_EXTERN T1_uint8_t const      T1_nofDelays T1_SEC_CONST_8;
#   define T1_STOP_SEC_CONST_8
#   include "T1_MemMap.h"

#endif /* #if defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY */

/*----------------------------------------------------------------------------------*/
/*--- macros and inline functions --------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_DELAY_PLUGIN_ID                      (3u)

#if defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY
#   define T1_delayPlugin                       (&T1_delayPluginStruct)
#else
#   define T1_delayPlugin                       (T1_DISABLED_PLUGIN)
#endif

#define T1_ALL_IDS                              ((T1_delayId_t)-1)

/*----------------------------------------------------------------------------------*/
/*--- forward declarations for global functions ------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY

#   define T1_START_SEC_CODE
#   include "T1_MemMap.h"

T1_EXTERN T1_status_t T1_CODE T1_DelayRoutine( T1_delayId_t id );
T1_EXTERN void        T1_CODE T1_ResetDelays( void );
T1_EXTERN void        T1_CODE T1_DelayForTimerTicks( T1_delay_t timerTicks );

#   define T1_STOP_SEC_CODE
#   include "T1_MemMap.h"

#else  /* #if defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY */

#   define T1_DelayRoutine( id_ )               (T1_PLUGIN_NOT_AVAILABLE)
#   define T1_ResetDelays( )                    ((void)0)

#endif /* #if defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY */

#endif /* T1_DELAY_INTERFACE_H_ */
