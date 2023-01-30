#include "T1_AppInterface.h"

#ifdef T1_ENABLE

#include "Std_Types.h"
#include "T1_AppInterface_Cfg.h"
#include "sys_pmu.h"
#include "osek.h"

#define T1_START_SEC_CONST_32
#include "T1_MemMap.h"
T1_DeclarePluginTable( T1_pluginTable );
T1_DeclarePluginTable( T1_pluginTableNoFlex );
#define T1_STOP_SEC_CONST_32
#include "T1_MemMap.h"

#define T1_START_SEC_CODE
#include "T1_MemMap.h"

/* Initialize the PMU timers, and the T1 libraries. Place as early as possible in the start up sequence. */
void T1_AppInit(void)
{
	/*Initialize and start the PMU counters.*/
	_pmuInit_();
	_pmuEnableCountersGlobal_();
	_pmuSetUserEnable_(1U);
	/* Cycle Counter: Total time for CPU utilization calculations.*/
	_pmuStartCounters_(pmuCYCLE_COUNTER);

	/* Replace T1_pluginTable with T1_pluginTableNoFlex if debugging. Otherwise strange debugging behavior will result.
	 * This line will never return if the timer is not running. */
	(void)T1_Init(T1_pluginTable);

	/* On startup tell T1 to stop tracing once the buffer is full.
	 * Means that every startup will result in a trace of startup timing. */
	if(T1_IsFeatureEnabled(T1_AF_TRIGGER_STARTUP))
	{
		T1_SetStopTriggerNoSusp(T1_TRACEBUFFER_ENTRIES_CORE0);
	}
}

/* Periodic function called to poll the received message (if necessary), and the T1 periodic handler. */
void T1_AppHandler(void)
{
#if (STD_ON == D_GLIWAT1_SWITCHTOPRIVMODE_CNT_LGC)
	VAR(uint32, AUTOMATIC) CallerIsTrusted_Cnt_T_u32;

	CallerIsTrusted_Cnt_T_u32 = osSwitchToPrivMode();
#endif

	PollT1HostToTarget();

	(void)T1_Handler();

#if (STD_ON == D_GLIWAT1_SWITCHTOPRIVMODE_CNT_LGC)
	if(0u == CallerIsTrusted_Cnt_T_u32)
	{
		osSwitchToUserMode();
	}
#endif
}

/* Runs continously in the background, processing the trace buffer.*/
void T1_AppBgHandler(void)
{
#if (STD_ON == D_GLIWAT1_SWITCHTOPRIVMODE_CNT_LGC)
	VAR(uint32, AUTOMATIC) CallerIsTrusted_Cnt_T_u32;

	CallerIsTrusted_Cnt_T_u32 = osSwitchToPrivMode();
#endif

	(void)T1_ContBgHandler();

#if (STD_ON == D_GLIWAT1_SWITCHTOPRIVMODE_CNT_LGC)
	if(0u == CallerIsTrusted_Cnt_T_u32)
	{
		osSwitchToUserMode();
	}
#endif
}

#define T1_STOP_SEC_CODE
#include "T1_MemMap.h"

/* T1 back end trace event call. Used when interrupt disable status is unknown.
 * Overridden to use the PMU instead of the RTI (which is not fast enough in most programs). */
#pragma CODE_SECTION(T1_TraceEvent_, ".T1_codeFast:T1_TraceEvent_")
#pragma FUNCTION_OPTIONS(T1_TraceEvent_, "--code_state=32");
void T1_CODE_FAST T1_TraceEvent_(T1_uint16Least_t eventInfo)
{
	uint32 cpsr;

	cpsr = _get_CPSR();

	if((0x80 & cpsr) == 0x80)
	{
		T1_TraceEventNoSuspTime_(_pmuGetCycleCount_(), eventInfo);
	}
	else
	{
		asm( " CPSID I" );
		T1_TraceEventNoSuspTime_(_pmuGetCycleCount_(), eventInfo);
		asm( " CPSIE I" );
	}
}

/* T1 back end trace event call. Used when interrupts are known to be enabled.
 * Overridden to use the PMU instead of the RTI (which is not fast enough in most programs). */
#pragma CODE_SECTION(T1_TraceEventFast_, ".T1_codeFast:T1_TraceEventFast_")
void T1_CODE_FAST T1_TraceEventFast_(T1_uint16Least_t eventInfo)
{
	asm( " CPSID I" );
	T1_TraceEventNoSuspTime_(_pmuGetCycleCount_(), eventInfo);
	asm( " CPSIE I" );
}

/* T1 back end trace event call. Used when interrupts are known to be disabled.
 * Overridden to use the PMU instead of the RTI (which is not fast enough in most programs). */
#pragma CODE_SECTION(T1_GetTraceTime, ".T1_codeFast:T1_GetTraceTime")
T1_tickUint_t T1_GetTraceTime(void)
{
	return (T1_tickUint_t)_pmuGetCycleCount_();
}

#if (STD_ON == D_GLIWAT1_SLOWWAITSTATES_CNT_LGC)
#pragma CODE_SECTION(T1_TraceEventNoSusp_, ".T1_codeFast:T1_TraceEventNoSusp_")
#pragma FUNCTION_OPTIONS(T1_TraceEvent_, "--code_state=32");
/* This version of code is faster when using the legal (3dws, 1aws) flash wait states. */
void T1_CODE_FAST T1_TraceEventNoSusp_(T1_uint16Least_t eventInfo)
{
	asm(" movw r2, T1_TraceEventNoSuspTime_");
	asm(" movt r2, T1_TraceEventNoSuspTime_");
	asm(" mov r1, r0");					/* Move event info from first parameter to second. */
	asm(" mrc   p15, #0, r0, c9, c13, #0");
	asm(" bx r2"); /* Execute this funciton with r0 as the time, and r1 as the event info. lr points to T1_TraceEventNoSusp_ caller. */
}
#else
/* This version of code is faster when executing using the illegal (2dws, 0aws) flash wait states. */
void T1_CODE_FAST T1_TraceEventNoSusp_(T1_uint16Least_t eventInfo)
{
	asm(" mov r2, lr");
	asm(" mov r1, r0");					/* Move event info from first parameter to second. */
	asm(" blx   _pmuGetCycleCount_");
	asm(" mov lr, r2");
	asm(" b T1_TraceEventNoSuspTime_"); /* Execute this funciton with r0 as the time, and r1 as the event info. lr points to T1_TraceEventNoSusp_ caller. */
}
#endif /* (STD_ON == D_GLIWAT1_SLOWWAITSTATES_CNT_LGC) */
#endif /* T1_ENABLE*/
