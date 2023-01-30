/*************************************************************************************
*   FILE:           T1_flexConfig.h
*
*   DESCRIPTION:    T1 flex configuration fragment
*
*   VISIBILITY:     extern
*
*   $Author: nick $
*
*   $Revision: 12180 $
*
*   $URL: https://gliwa.com/svn/repos/T1target/trunk/src/T1.flex/src/all/T1_flexConfig.h $
*
*   Copyright:      Gliwa GmbH | know- how in embedded software
*                   Weilheim i.OB.
*                   All rights reserved
*************************************************************************************/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX
#   ifndef T1_NOF_FLEX_ADDRS_CORE0
#       error T1_NOF_FLEX_ADDRS_CORE0 not defined
#   endif /* T1_NOF_FLEX_ADDRS_CORE0 */
#   if !defined T1_NOF_CORES
#       define T1_START_SEC_CONST_8
#       include "T1_MemMap.h"
T1_uint8_t const        T1_nofAddrs T1_SEC_CONST_8 = T1_NOF_FLEX_ADDRS_CORE0;
#       define T1_STOP_SEC_CONST_8
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32
#       include "T1_MemMap.h"
T1_pFlexAddr_t          T1_addrs[T1_NOF_FLEX_ADDRS_CORE0] T1_SEC_NO_INIT_32;
#       define T1_STOP_SEC_NO_INIT_32
#       include "T1_MemMap.h"
#   elif 1 == T1_NOF_CORES
#       define T1_START_SEC_CONST_8
#       include "T1_MemMap.h"
T1_uint8_t const        T1_nofAddrsPC[] T1_SEC_CONST_8 = { T1_NOF_FLEX_ADDRS_CORE0 };
#       define T1_STOP_SEC_CONST_8
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE0
#       include "T1_MemMap.h"
T1_pFlexAddr_t          T1_addrs0[T1_NOF_FLEX_ADDRS_CORE0] T1_SEC_NO_INIT_32_CORE0;
#       define T1_STOP_SEC_NO_INIT_32_CORE0
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_pFlexAddr_t * const  T1_addrsPC[] T1_SEC_CONST_32 = { T1_addrs0 };
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#   elif 2 == T1_NOF_CORES
#       ifndef T1_NOF_FLEX_ADDRS_CORE0
#           error T1_NOF_FLEX_ADDRS_CORE0 not defined
#       endif /* T1_NOF_FLEX_ADDRS_CORE0 */
#       ifndef T1_NOF_FLEX_ADDRS_CORE1
#           error T1_NOF_FLEX_ADDRS_CORE1 not defined
#       endif /* T1_NOF_FLEX_ADDRS_CORE1 */
#       define T1_START_SEC_CONST_8
#       include "T1_MemMap.h"
T1_uint8_t const        T1_nofAddrsPC[] T1_SEC_CONST_8 = { T1_NOF_FLEX_ADDRS_CORE0, T1_NOF_FLEX_ADDRS_CORE1 };
#       define T1_STOP_SEC_CONST_8
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE0
#       include "T1_MemMap.h"
T1_pFlexAddr_t          T1_addrs0[T1_NOF_FLEX_ADDRS_CORE0] T1_SEC_NO_INIT_32_CORE0;
#       define T1_STOP_SEC_NO_INIT_32_CORE0
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE1
#       include "T1_MemMap.h"
T1_pFlexAddr_t          T1_addrs1[T1_NOF_FLEX_ADDRS_CORE1] T1_SEC_NO_INIT_32_CORE1;
#       define T1_STOP_SEC_NO_INIT_32_CORE1
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_pFlexAddr_t * const  T1_addrsPC[] T1_SEC_CONST_32 = { T1_addrs0, T1_addrs1 };
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#   elif 3 == T1_NOF_CORES
#       ifndef T1_NOF_FLEX_ADDRS_CORE0
#           error T1_NOF_FLEX_ADDRS_CORE0 not defined
#       endif /* T1_NOF_FLEX_ADDRS_CORE0 */
#       ifndef T1_NOF_FLEX_ADDRS_CORE1
#           error T1_NOF_FLEX_ADDRS_CORE1 not defined
#       endif /* T1_NOF_FLEX_ADDRS_CORE1 */
#       ifndef T1_NOF_FLEX_ADDRS_CORE2
#           error T1_NOF_FLEX_ADDRS_CORE2 not defined
#       endif /* T1_NOF_FLEX_ADDRS_CORE2 */
#       define T1_START_SEC_CONST_8
#       include "T1_MemMap.h"
T1_uint8_t const        T1_nofAddrsPC[] T1_SEC_CONST_8 = { T1_NOF_FLEX_ADDRS_CORE0, T1_NOF_FLEX_ADDRS_CORE1, T1_NOF_FLEX_ADDRS_CORE2 };
#       define T1_STOP_SEC_CONST_8
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE0
#       include "T1_MemMap.h"
T1_pFlexAddr_t          T1_addrs0[T1_NOF_FLEX_ADDRS_CORE0] T1_SEC_NO_INIT_32_CORE0;
#       define T1_STOP_SEC_NO_INIT_32_CORE0
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE1
#       include "T1_MemMap.h"
T1_pFlexAddr_t          T1_addrs1[T1_NOF_FLEX_ADDRS_CORE1] T1_SEC_NO_INIT_32_CORE1;
#       define T1_STOP_SEC_NO_INIT_32_CORE1
#       include "T1_MemMap.h"
#       define T1_START_SEC_NO_INIT_32_CORE2
#       include "T1_MemMap.h"
T1_pFlexAddr_t          T1_addrs2[T1_NOF_FLEX_ADDRS_CORE2] T1_SEC_NO_INIT_32_CORE2;
#       define T1_STOP_SEC_NO_INIT_32_CORE2
#       include "T1_MemMap.h"
#       define T1_START_SEC_CONST_32
#       include "T1_MemMap.h"
T1_pFlexAddr_t * const  T1_addrsPC[] T1_SEC_CONST_32 = { T1_addrs0, T1_addrs1, T1_addrs2 };
#       define T1_STOP_SEC_CONST_32
#       include "T1_MemMap.h"
#   else
#       error T1_NOF_CORES too large
#   endif

#   define T1_START_SEC_CONST_8
#   include "T1_MemMap.h"
T1_uint8_t const        T1_flexDisableWithDebugger T1_SEC_CONST_8 =
#       if defined T1_FLEX_DISABLE_WITH_DEBUGGER
                                                                    T1_TRUE;
#       else
                                                                    T1_FALSE;
#       endif /* defined T1_FLEX_DISABLE_WITH_DEBUGGER */
#   define T1_STOP_SEC_CONST_8
#   include "T1_MemMap.h"

#endif /* defined T1_ENABLE && !defined T1_DISABLE_T1_FLEX */
