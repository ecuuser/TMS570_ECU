/*************************************************************************************
*   FILE:           T1_config.c
*
*   DESCRIPTION:    Configuration of T1 and its plug-ins for TriCore demo application
*
*   $Author: nick $
*
*   $Revision: 13089 $
*
*   $URL: https://gliwa.com/svn/repos/T1sandbox/trunk/TriCoreExV2/src/T1_config.c $
*
*   COPYRIGHT:      gliwa GmbH | know- how in embedded software
*                   Weilheim i.OB.
*                   All rights reserved
*************************************************************************************/

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "T1_AppInterface.h"
#include "T1_bid.h"

/*----------------------------------------------------------------------------------*/
/*--- Configuration macros ---------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_CONFIG                           (1)
#define T1_INIT_FEATURE_MASK                (T1_AF_TRIGGER_STARTUP | T1_AF_ALLOW_TRIGGER)
#define T1_TRACE_TIMER_COUNTS_DOWN_CORE0    (T1_FALSE)
#define T1_NOF_USER_STPWS_CORE0             (1)
#define T1_BSF_EVENT_ID_CORE0               (T1_ACTIVATION)

/*----------------------------------------------------------------------------------*/
/*--- Config includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include "T1_baseConfig.h"
#include "T1_contConfig.h"
#include "T1_delayConfig.h"
#include "T1_flexConfig.h"
#include "T1_scopeConfig.h"

/*----------------------------------------------------------------------------------*/
/*--- T1 related configuration -----------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE

#define T1_START_SEC_CONST_32
#include "T1_MemMap.h"
T1_ALLOCATE_PLUGIN_TABLE( T1_pluginTable )
T1_ALLOCATE_PLUGIN_TABLE_NO_T1_FLEX( T1_pluginTableNoFlex )
#define T1_STOP_SEC_CONST_32
#include "T1_MemMap.h"

/*----------------------------------------------------------------------------------*/
/*--- T1 cont related configuration ------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if !defined T1_DISABLE_T1_CONT

void osPrefetchAbort(void);
void osDataAbort(void);

#define T1_START_SEC_CODE
#include "T1_MemMap.h"

void T1_CODE T1_InitEventChainsCore0( void )
{
}

void T1_CODE T1_ContErrCallback( T1_uint8Least_t errMask )
{
    if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRIGGER ) )
    {
        T1_SetStopTrigger( T1_TRACEBUFFER_ENTRIES_CORE0 / 4 );
    }
    T1_TraceEvent( T1_UEV_CONT_ERR, errMask );
}

void T1_CODE T1_ContCsrnCallback( T1_resultTime_t result, T1_csrnIdx_t idx )
{
    if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRIGGER ) )
    {
        T1_SetStopTrigger( T1_TRACEBUFFER_ENTRIES_CORE0 / 8 );
        T1_TraceEvent( T1_UEV_CONT_CSRN, idx );
    }
}

T1_resultTime_t T1_CODE T1_ContStartStopCET( T1_taskIdx_t taskIdx )
{
    return 0uL; /* Not used */
}

void T1_CODE T1_CPULoadCallback( T1_uint16Least_t o, T1_uint16Least_t e )
{
    if( T1_IsFeatureEnabled( T1_AF_ALLOW_TRIGGER ) )
    {
        T1_SetStopTrigger( T1_TRACEBUFFER_ENTRIES_CORE0 / 4 );
        T1_TraceEvent( T1_UEV_CONT_CPU, ((200uL * e) / o + 1) / 2 );
    }
}

#define T1_START_SEC_CONST_8
#include "T1_MemMap.h"
T1_stpwConfig_t             T1_stpwConfig[] T1_SEC_CONST_8 =
{
    T1_CONT_CET_STOPWATCH( 0u ),        /* User stopwatch 0: CET */
};
#define T1_STOP_SEC_CONST_8
#include "T1_MemMap.h"

#define T1_START_SEC_CONST_32
#include "T1_MemMap.h"

const T1_csrnData_t         T1_csrnConfig[] T1_SEC_CONST_32 =
{
	T1_CONT_INVALID_CONSTRAINT
};
#define T1_STOP_SEC_CONST_32
#include "T1_MemMap.h"

#endif /* !defined T1_DISABLE_T1_CONT */

/*----------------------------------------------------------------------------------*/
/*--- T1 flex related configuration ------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#if !defined T1_DISABLE_T1_FLEX

#pragma FUNCTION_OPTIONS ( T1_AppPrefetchAbortHandler, " --code_state=32 -O2");
void T1_CODE T1_AppPrefetchAbortHandler( void )
{
	osRealPrefetchAbort();
}

#pragma FUNCTION_OPTIONS ( T1_AppDataAbortHandler, " --code_state=32 -O2");
void T1_CODE T1_AppDataAbortHandler( void )
{
	osRealDataAbort();
}

#else

#pragma FUNCTION_OPTIONS ( T1_DataAbortHandler, " --code_state=32 -O2");
void T1_CODE T1_DataAbortHandler( void )
{
	osRealPrefetchAbort();
}

#pragma FUNCTION_OPTIONS ( T1_PrefetchAbortHandler, " --code_state=32 -O2");
void T1_CODE T1_PrefetchAbortHandler( void )
{
	osRealDataAbort();
}

#endif /* !defined T1_DISABLE_T1_FLEX */

#define T1_STOP_SEC_CODE
#include "T1_MemMap.h"

#endif /* T1_ENABLE */

