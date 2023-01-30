#ifndef METRICS_H
#define METRICS_H

/* This file maintains compatibility for driver components we are not interested in updating. */

#include "T1_AppInterface.h"

#ifdef T1_ENABLE

#include "T1_AppInterface_Cfg.h"

#if (STD_ON == D_GLIWAT1_SWITCHTOPRIVMODE_CNT_LGC)

#define Metrics_TaskStart(id) \
	uint32 CallerIsTrusted_Cnt_T_u32; \
	CallerIsTrusted_Cnt_T_u32 = osSwitchToPrivMode(); \
	T1_TraceEvent(T1_START, id); \
	if(0u == CallerIsTrusted_Cnt_T_u32) { osSwitchToUserMode(); }

#define Metrics_TaskEnd(id) \
	if(0u == CallerIsTrusted_Cnt_T_u32) { osSwitchToPrivMode(); } \
	T1_TraceEvent(T1_STOP, id); \
	if(0u == CallerIsTrusted_Cnt_T_u32) { osSwitchToUserMode(); }

#else /* Don't need to switch modes. */


#define Metrics_TaskStart(id) T1_TraceEvent(T1_START, id)
#define Metrics_TaskEnd(id) T1_TraceEvent(T1_STOP, id)

#endif /* STD_ON == D_GLIWAT1_SWITCHTOPRIVMODE_CNT_LGC */

#else /* T1 is disabled. */

#define Metrics_TaskStart(id)
#define Metrics_TaskEnd(id)

#endif /* T1_ENABLE */
#endif
