/*************************************************************************************
*   FILE:           T1_delayConfig.h
*
*   DESCRIPTION:    T1 delay configuration fragment
*
*   VISIBILITY:     extern
*
*   $Author: nick $
*
*   $Revision: 10792 $
*
*   $URL: https://gliwa.com/svn/repos/T1target/trunk/src/T1.delay/src/all/T1_delayConfig.h $
*
*   Copyright:      Gliwa GmbH | know- how in embedded software
*                   Weilheim i.OB.
*                   All rights reserved
*************************************************************************************/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY
#       if !defined T1_NOF_CORES
#           define T1_START_SEC_CONST_8
#           include "T1_MemMap.h"
const T1_uint8_t T1_nofDelays T1_SEC_CONST_8 = (T1_NOF_DELAYS_CORE0);
#           define T1_STOP_SEC_CONST_8
#           include "T1_MemMap.h"
#           define T1_START_SEC_NO_INIT_32
#           include "T1_MemMap.h"
T1_delay_t T1_delays[T1_NOF_DELAYS_CORE0] T1_SEC_NO_INIT_32;
#           define T1_STOP_SEC_NO_INIT_32
#           include "T1_MemMap.h"
#       elif 1 == T1_NOF_CORES
#           define T1_START_SEC_CONST_8
#           include "T1_MemMap.h"
const T1_uint8_t T1_nofDelaysPC[] T1_SEC_CONST_8 = { (T1_NOF_DELAYS_CORE0) };
#           define T1_STOP_SEC_CONST_8
#           include "T1_MemMap.h"
#           define T1_START_SEC_NO_INIT_32
#           include "T1_MemMap.h"
static T1_delay_t delays0[T1_NOF_DELAYS_CORE0] T1_SEC_NO_INIT_32;
#           define T1_STOP_SEC_NO_INIT_32
#           include "T1_MemMap.h"
#           define T1_START_SEC_CONST_32
#           include "T1_MemMap.h"
T1_delay_t * const T1_delaysPC[] T1_SEC_CONST_32 = { delays0 };
#           define T1_STOP_SEC_CONST_32
#           include "T1_MemMap.h"
#       elif 2 == T1_NOF_CORES
#           define T1_START_SEC_CONST_8
#           include "T1_MemMap.h"
const T1_uint8_t T1_nofDelaysPC[] T1_SEC_CONST_8 = { (T1_NOF_DELAYS_CORE0), (T1_NOF_DELAYS_CORE1) };
#           define T1_STOP_SEC_CONST_8
#           include "T1_MemMap.h"
#           define T1_START_SEC_NO_INIT_32
#           include "T1_MemMap.h"
static T1_delay_t delays0[T1_NOF_DELAYS_CORE0] T1_SEC_NO_INIT_32;
static T1_delay_t delays1[T1_NOF_DELAYS_CORE1] T1_SEC_NO_INIT_32;
#           define T1_STOP_SEC_NO_INIT_32
#           include "T1_MemMap.h"
#           define T1_START_SEC_CONST_32
#           include "T1_MemMap.h"
T1_delay_t * const T1_delaysPC[] T1_SEC_CONST_32 = { delays0, delays1 };
#           define T1_STOP_SEC_CONST_32
#           include "T1_MemMap.h"
#       elif 3 == T1_NOF_CORES
#           define T1_START_SEC_CONST_8
#           include "T1_MemMap.h"
const T1_uint8_t T1_nofDelaysPC[] T1_SEC_CONST_8 = { (T1_NOF_DELAYS_CORE0), (T1_NOF_DELAYS_CORE1), (T1_NOF_DELAYS_CORE2) };
#           define T1_STOP_SEC_CONST_8
#           include "T1_MemMap.h"
#           define T1_START_SEC_NO_INIT_32
#           include "T1_MemMap.h"
static T1_delay_t delays0[T1_NOF_DELAYS_CORE0] T1_SEC_NO_INIT_32;
static T1_delay_t delays1[T1_NOF_DELAYS_CORE1] T1_SEC_NO_INIT_32;
static T1_delay_t delays2[T1_NOF_DELAYS_CORE2] T1_SEC_NO_INIT_32;
#           define T1_STOP_SEC_NO_INIT_32
#           include "T1_MemMap.h"
#           define T1_START_SEC_CONST_32
#           include "T1_MemMap.h"
T1_delay_t * const T1_delaysPC[] T1_SEC_CONST_32 = { delays0, delays1, delays2 };
#           define T1_STOP_SEC_CONST_32
#           include "T1_MemMap.h"
#       else
#           error T1_NOF_CORES too large
#       endif /* T1_NOF_CORES */
#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_DELAY */
