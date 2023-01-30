/*************************************************************************************
*   FILE:           T1_scopeConfig.h
*
*   DESCRIPTION:    T1 scope configuration fragment
*
*   VISIBILITY:     extern
*
*   $Author: nick $
*
*   $Revision: 14701 $
*
*   $URL: https://gliwa.com/svn/repos/T1target/trunk/release/ti-arm7r/interface/T1_scopeConfig.h $
*
*   Copyright:      Gliwa GmbH | know- how in embedded software
*                   Weilheim i.OB.
*                   All rights reserved
*************************************************************************************/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_SCOPE
#   ifndef T1_TRACEBUFFER_ENTRIES_CORE0
#       error T1_TRACEBUFFER_ENTRIES_CORE0 not defined
#   endif /* T1_TRACEBUFFER_ENTRIES_CORE0 */
#   ifndef T1_TRACE_TIMER_COUNTS_DOWN_CORE0
#       error T1_TRACE_TIMER_COUNTS_DOWN_CORE0 not defined
#   endif /* T1_TRACE_TIMER_COUNTS_DOWN_CORE0 */
#   if !defined T1_NOF_CORES
#       define T1_START_SEC_NO_INIT_32_TRACEBUFFER
#       include "T1_MemMap.h"
T1_traceEntry_t T1_FAR T1_traceBuffer[T1_TRACEBUFFER_ENTRIES_CORE0] T1_SEC_NO_INIT_32_TRACEBUFFER;
#       define T1_STOP_SEC_NO_INIT_32_TRACEBUFFER
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
const T1_nofEntries_t T1_bufferSize T1_SEC_CONST_32 = (T1_TRACEBUFFER_ENTRIES_CORE0);
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#       if defined T1_PTIMER_CORE0
#           if T1_USE_NEAR
#               define T1_START_SEC_CONST_16
#               include "T1_MemMap.h"
volatile T1_tickUint_t const T1_NEARPTR const T1_pTimer T1_SEC_CONST_16 = (volatile T1_tickUint_t const T1_NEARPTR)T1_PTIMER_CORE0;
#               define T1_STOP_SEC_CONST_16
#               include "T1_MemMap.h"
#           else /* ! T1_USE_NEAR */
#               define T1_START_SEC_CONST_32
#               include "T1_MemMap.h"
volatile T1_tickUint_t const T1_NEARPTR const T1_pTimer T1_SEC_CONST_32 = (volatile T1_tickUint_t const T1_NEARPTR)T1_PTIMER_CORE0;
#               define T1_STOP_SEC_CONST_32
#               include "T1_MemMap.h"
#           endif /* T1_USE_NEAR */
#       endif /* defined T1_PTIMER_CORE0 */

#   elif 1 == T1_NOF_CORES
#       define T1_START_SEC_NO_INIT_32_TRACEBUFFER_CORE0
#       include "T1_MemMap.h"
T1_traceEntry_t T1_FAR T1_CORE0 T1_traceBuffer0[T1_TRACEBUFFER_ENTRIES_CORE0] T1_SEC_NO_INIT_32_TRACEBUFFER_CORE0;
#       define T1_STOP_SEC_NO_INIT_32_TRACEBUFFER_CORE0
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_traceEntry_t T1_FARPTR const T1_traceBufferPC[] T1_SEC_CONST_32 = { T1_traceBuffer0 };
const T1_nofEntries_t T1_bufferSizePC[] T1_SEC_CONST_32 = { (T1_TRACEBUFFER_ENTRIES_CORE0) };
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#       if defined T1_PTIMER_CORE0
#           if T1_USE_NEAR
#               define T1_START_SEC_CONST_16
#               include "T1_MemMap.h"
volatile T1_tickUint_t const T1_NEARPTR const T1_pTimerPC[] T1_SEC_CONST_16 = { (volatile T1_tickUint_t const T1_NEARPTR)T1_PTIMER_CORE0 };
#               define T1_STOP_SEC_CONST_16
#               include "T1_MemMap.h"
#           else /* !T1_USE_NEAR */
#               define T1_START_SEC_CONST_32
#               include "T1_MemMap.h"
volatile T1_tickUint_t const T1_NEARPTR const T1_pTimerPC[] T1_SEC_CONST_32 = { (volatile T1_tickUint_t const T1_NEARPTR)T1_PTIMER_CORE0 };
#               define T1_STOP_SEC_CONST_32
#               include "T1_MemMap.h"
#           endif /* T1_USE_NEAR */
#       endif /* defined T1_PTIMER_CORE0 */
#       if !defined T1_P_SYNC_TIMER
#           define T1_P_SYNC_TIMER 0
#       endif /* defined T1_P_SYNC_TIMER */
#       if T1_USE_NEAR
#           define T1_START_SEC_CONST_16
#           include "T1_MemMap.h"
volatile T1_tickUint_t const T1_NEARPTR const T1_pSyncTimer T1_SEC_CONST_16 = (volatile T1_tickUint_t const T1_NEARPTR)T1_P_SYNC_TIMER;
#           define T1_STOP_SEC_CONST_16
#           include "T1_MemMap.h"
#       else /* ! T1_USE_NEAR */
#           define T1_START_SEC_CONST_32
#           include "T1_MemMap.h"
volatile T1_tickUint_t const T1_NEARPTR const T1_pSyncTimer T1_SEC_CONST_32 = (volatile T1_tickUint_t const T1_NEARPTR)T1_P_SYNC_TIMER;
#           define T1_STOP_SEC_CONST_32
#           include "T1_MemMap.h"
#       endif /* T1_USE_NEAR */

#   elif 2 == T1_NOF_CORES
#       ifndef T1_TRACEBUFFER_ENTRIES_CORE0
#           error T1_TRACEBUFFER_ENTRIES_CORE0 not defined
#       endif /* T1_TRACEBUFFER_ENTRIES_CORE0 */
#       ifndef T1_PTIMER_CORE0
#           error T1_PTIMER_CORE0 not defined
#       endif /* T1_PTIMER_CORE0 */
#       ifndef T1_TRACE_TIMER_COUNTS_DOWN_CORE0
#           error T1_TRACE_TIMER_COUNTS_DOWN_CORE0 not defined
#       endif /* T1_TRACE_TIMER_COUNTS_DOWN_CORE0 */
#       ifndef T1_TRACEBUFFER_ENTRIES_CORE1
#           error T1_TRACEBUFFER_ENTRIES_CORE1 not defined
#       endif /* T1_TRACEBUFFER_ENTRIES_CORE1 */
#       ifndef T1_PTIMER_CORE1
#           error T1_PTIMER_CORE1 not defined
#       endif /* T1_PTIMER_CORE1 */
#       ifndef T1_TRACE_TIMER_COUNTS_DOWN_CORE1
#           error T1_TRACE_TIMER_COUNTS_DOWN_CORE1 not defined
#       endif /* T1_TRACE_TIMER_COUNTS_DOWN_CORE1 */
#       define T1_START_SEC_NO_INIT_32_TRACEBUFFER_CORE0
#       include "T1_MemMap.h"
T1_traceEntry_t T1_FAR T1_CORE0 T1_traceBuffer0[T1_TRACEBUFFER_ENTRIES_CORE0] T1_SEC_NO_INIT_32_TRACEBUFFER_CORE0;
#       define T1_STOP_SEC_NO_INIT_32_TRACEBUFFER_CORE0
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_TRACEBUFFER_CORE1
#       include "T1_MemMap.h"
T1_traceEntry_t T1_FAR T1_CORE1 T1_traceBuffer1[T1_TRACEBUFFER_ENTRIES_CORE1] T1_SEC_NO_INIT_32_TRACEBUFFER_CORE1;
#       define T1_STOP_SEC_NO_INIT_32_TRACEBUFFER_CORE1
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_traceEntry_t T1_FARPTR const T1_traceBufferPC[] T1_SEC_CONST_32 = {T1_traceBuffer0, T1_traceBuffer1};
const T1_nofEntries_t T1_bufferSizePC[] T1_SEC_CONST_32 = {(T1_TRACEBUFFER_ENTRIES_CORE0), (T1_TRACEBUFFER_ENTRIES_CORE1)};
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#       if T1_USE_NEAR
#           define T1_START_SEC_CONST_16
#           include "T1_MemMap.h"
volatile T1_tickUint_t const T1_NEARPTR const T1_pTimerPC[] T1_SEC_CONST_16 = { (volatile T1_tickUint_t const T1_NEARPTR)T1_PTIMER_CORE0, (volatile T1_tickUint_t const T1_NEARPTR)T1_PTIMER_CORE1 };
#           define T1_STOP_SEC_CONST_16
#           include "T1_MemMap.h"
#       else /* !T1_USE_NEAR */
#           define T1_START_SEC_CONST_32
#           include "T1_MemMap.h"
volatile T1_tickUint_t const T1_NEARPTR const T1_pTimerPC[] T1_SEC_CONST_32 = { (volatile T1_tickUint_t const T1_NEARPTR)T1_PTIMER_CORE0, (volatile T1_tickUint_t const T1_NEARPTR)T1_PTIMER_CORE1 };
#           define T1_STOP_SEC_CONST_32
#           include "T1_MemMap.h"
#       endif /* T1_USE_NEAR */
#       if !defined T1_P_SYNC_TIMER
#           define T1_P_SYNC_TIMER 0
#       endif /* defined T1_P_SYNC_TIMER */
#       if T1_USE_NEAR
#           define T1_START_SEC_CONST_16
#           include "T1_MemMap.h"
volatile T1_tickUint_t const T1_NEARPTR const T1_pSyncTimer T1_SEC_CONST_16 = (volatile T1_tickUint_t const T1_NEARPTR)T1_P_SYNC_TIMER;
#           define T1_STOP_SEC_CONST_16
#           include "T1_MemMap.h"
#       else /* ! T1_USE_NEAR */
#           define T1_START_SEC_CONST_32
#           include "T1_MemMap.h"
volatile T1_tickUint_t const T1_NEARPTR const T1_pSyncTimer T1_SEC_CONST_32 = (volatile T1_tickUint_t const T1_NEARPTR)T1_P_SYNC_TIMER;
#           define T1_STOP_SEC_CONST_32
#           include "T1_MemMap.h"
#       endif /* T1_USE_NEAR */

#   elif 3 == T1_NOF_CORES
#       ifndef T1_TRACEBUFFER_ENTRIES_CORE0
#           error T1_TRACEBUFFER_ENTRIES_CORE0 not defined
#       endif /* T1_TRACEBUFFER_ENTRIES_CORE0 */
#       ifndef T1_PTIMER_CORE0
#           error T1_PTIMER_CORE0 not defined
#       endif /* T1_PTIMER_CORE0 */
#       ifndef T1_TRACE_TIMER_COUNTS_DOWN_CORE0
#           error T1_TRACE_TIMER_COUNTS_DOWN_CORE0 not defined
#       endif /* T1_TRACE_TIMER_COUNTS_DOWN_CORE0 */
#       ifndef T1_TRACEBUFFER_ENTRIES_CORE1
#           error T1_TRACEBUFFER_ENTRIES_CORE1 not defined
#       endif /* T1_TRACEBUFFER_ENTRIES_CORE1 */
#       ifndef T1_PTIMER_CORE1
#           error T1_PTIMER_CORE1 not defined
#       endif /* T1_PTIMER_CORE1 */
#       ifndef T1_TRACE_TIMER_COUNTS_DOWN_CORE1
#           error T1_TRACE_TIMER_COUNTS_DOWN_CORE1 not defined
#       endif /* T1_TRACE_TIMER_COUNTS_DOWN_CORE1 */
#       ifndef T1_TRACEBUFFER_ENTRIES_CORE2
#           error T1_TRACEBUFFER_ENTRIES_CORE2 not defined
#       endif /* T1_TRACEBUFFER_ENTRIES_CORE2 */
#       ifndef T1_PTIMER_CORE2
#           error T1_PTIMER_CORE2 not defined
#       endif /* T1_PTIMER_CORE2 */
#       ifndef T1_TRACE_TIMER_COUNTS_DOWN_CORE2
#           error T1_TRACE_TIMER_COUNTS_DOWN_CORE2 not defined
#       endif /* T1_TRACE_TIMER_COUNTS_DOWN_CORE2 */
#       define T1_START_SEC_NO_INIT_32_TRACEBUFFER_CORE0
#       include "T1_MemMap.h"
T1_traceEntry_t T1_FAR T1_CORE0 T1_traceBuffer0[T1_TRACEBUFFER_ENTRIES_CORE0] T1_SEC_NO_INIT_32_TRACEBUFFER_CORE0;
#       define T1_STOP_SEC_NO_INIT_32_TRACEBUFFER_CORE0
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_TRACEBUFFER_CORE1
#       include "T1_MemMap.h"
T1_traceEntry_t T1_FAR T1_CORE1 T1_traceBuffer1[T1_TRACEBUFFER_ENTRIES_CORE1] T1_SEC_NO_INIT_32_TRACEBUFFER_CORE1;
#       define T1_STOP_SEC_NO_INIT_32_TRACEBUFFER_CORE1
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_TRACEBUFFER_CORE2
#       include "T1_MemMap.h"
T1_traceEntry_t T1_FAR T1_CORE2 T1_traceBuffer2[T1_TRACEBUFFER_ENTRIES_CORE2] T1_SEC_NO_INIT_32_TRACEBUFFER_CORE2;
#       define T1_STOP_SEC_NO_INIT_32_TRACEBUFFER_CORE2
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_traceEntry_t T1_FARPTR const T1_traceBufferPC[] T1_SEC_CONST_32 = {T1_traceBuffer0, T1_traceBuffer1, T1_traceBuffer2};
const T1_nofEntries_t T1_bufferSizePC[] T1_SEC_CONST_32 = {(T1_TRACEBUFFER_ENTRIES_CORE0), (T1_TRACEBUFFER_ENTRIES_CORE1), (T1_TRACEBUFFER_ENTRIES_CORE2)};
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#       if T1_USE_NEAR
#           define T1_START_SEC_CONST_16
#           include "T1_MemMap.h"
volatile T1_tickUint_t const T1_NEARPTR const T1_pTimerPC[] T1_SEC_CONST_16 = { (volatile T1_tickUint_t const T1_NEARPTR)T1_PTIMER_CORE0, (volatile T1_tickUint_t const T1_NEARPTR)T1_PTIMER_CORE1, (volatile T1_tickUint_t const T1_NEARPTR)T1_PTIMER_CORE2 };
#           define T1_STOP_SEC_CONST_16
#           include "T1_MemMap.h"
#       else /* !T1_USE_NEAR */
#           define T1_START_SEC_CONST_32
#           include "T1_MemMap.h"
volatile T1_tickUint_t const T1_NEARPTR const T1_pTimerPC[] T1_SEC_CONST_32 = { (volatile T1_tickUint_t const T1_NEARPTR)T1_PTIMER_CORE0, (volatile T1_tickUint_t const T1_NEARPTR)T1_PTIMER_CORE1, (volatile T1_tickUint_t const T1_NEARPTR)T1_PTIMER_CORE2 };
#           define T1_STOP_SEC_CONST_32
#           include "T1_MemMap.h"
#       endif /* T1_USE_NEAR */
#       if !defined T1_P_SYNC_TIMER
#           define T1_P_SYNC_TIMER 0
#       endif /* defined T1_P_SYNC_TIMER */
#       if T1_USE_NEAR
#           define T1_START_SEC_CONST_16
#           include "T1_MemMap.h"
volatile T1_tickUint_t const T1_NEARPTR const T1_pSyncTimer T1_SEC_CONST_16 = (volatile T1_tickUint_t const T1_NEARPTR)T1_P_SYNC_TIMER;
#           define T1_STOP_SEC_CONST_16
#           include "T1_MemMap.h"
#       else /* ! T1_USE_NEAR */
#           define T1_START_SEC_CONST_32
#           include "T1_MemMap.h"
volatile T1_tickUint_t const T1_NEARPTR const T1_pSyncTimer T1_SEC_CONST_32 = (volatile T1_tickUint_t const T1_NEARPTR)T1_P_SYNC_TIMER;
#           define T1_STOP_SEC_CONST_32
#           include "T1_MemMap.h"
#       endif /* T1_USE_NEAR */

#   else
#       error T1_NOF_CORES too large
#   endif

#   if defined T1_DISABLE_T1_FLEX
#       define T1_START_SEC_CODE
#       include "T1_MemMap.h"
void T1_FAR_CODE T1_FlexOHAddr( T1_uint32_t pAddrStart, T1_uint32_t pAddrStop )
{
    /* Empty function to allow linking without T1.flex */
}
#       define T1_STOP_SEC_CODE
#       include "T1_MemMap.h"
#   endif /* defined T1_DISABLE_T1_FLEX */
#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_SCOPE */
