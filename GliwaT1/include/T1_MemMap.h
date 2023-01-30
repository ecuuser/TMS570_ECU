/*************************************************************************************
*   FILE:           T1_MemMap.h
*
*   DESCRIPTION:    This header selects the T1 sections for the following compilers:
*                   TI
*
*   VISIBILITY:     extern
*
*   Copyright:      Gliwa GmbH | know- how in embedded software
*                   Weilheim i.OB.
*                   All rights reserved
*************************************************************************************/

#if defined __TMS470__

#   if 0

#   elif defined T1_START_SEC_CODE
#       undef T1_START_SEC_CODE
#       pragma SET_CODE_SECTION( ".T1_code" )
#   elif defined T1_STOP_SEC_CODE
#       undef T1_STOP_SEC_CODE
#       pragma SET_CODE_SECTION( )

#   elif defined T1_START_SEC_CODE_CORE0
#       undef T1_START_SEC_CODE_CORE0
#       pragma SET_CODE_SECTION( ".T1_codeCore0" )
#   elif defined T1_STOP_SEC_CODE_CORE0
#       undef T1_STOP_SEC_CODE_CORE0
#       pragma SET_CODE_SECTION( )

#   elif defined T1_START_SEC_CODE_CORE1
#       undef T1_START_SEC_CODE_CORE1
#       pragma SET_CODE_SECTION( ".T1_codeCore1" )
#   elif defined T1_STOP_SEC_CODE_CORE1
#       undef T1_STOP_SEC_CODE_CORE1
#       pragma SET_CODE_SECTION( )

#   elif defined T1_START_SEC_CODE_CORE2
#       undef T1_START_SEC_CODE_CORE2
#       pragma SET_CODE_SECTION( ".T1_codeCore2" )
#   elif defined T1_STOP_SEC_CODE_CORE2
#       undef T1_STOP_SEC_CODE_CORE2
#       pragma SET_CODE_SECTION( )

#   elif defined T1_START_SEC_CODE_FAST
#       undef T1_START_SEC_CODE_FAST
#       pragma SET_CODE_SECTION( ".T1_codeFast" )
#   elif defined T1_STOP_SEC_CODE_FAST
#       undef T1_STOP_SEC_CODE_FAST
#       pragma SET_CODE_SECTION( )

#   elif defined T1_START_SEC_CONST_8
#       undef T1_START_SEC_CONST_8
#       pragma SET_DATA_SECTION( ".T1_const" )
#   elif defined T1_STOP_SEC_CONST_8
#       undef T1_STOP_SEC_CONST_8
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_CONST_16
#       undef T1_START_SEC_CONST_16
#       pragma SET_DATA_SECTION( ".T1_const" )
#   elif defined T1_STOP_SEC_CONST_16
#       undef T1_STOP_SEC_CONST_16
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_CONST_32
#       undef T1_START_SEC_CONST_32
#       pragma SET_DATA_SECTION( ".T1_const" )
#   elif defined T1_STOP_SEC_CONST_32
#       undef T1_STOP_SEC_CONST_32
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NEAR_NO_INIT_8
#       undef T1_START_SEC_NEAR_NO_INIT_8
#       pragma SET_DATA_SECTION( ".T1_sbss" )
#   elif defined T1_STOP_SEC_NEAR_NO_INIT_8
#       undef T1_STOP_SEC_NEAR_NO_INIT_8
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NEAR_NO_INIT_8_CORE0
#       undef T1_START_SEC_NEAR_NO_INIT_8_CORE0
#       pragma SET_DATA_SECTION( ".T1_sbssCore0" )
#   elif defined T1_STOP_SEC_NEAR_NO_INIT_8_CORE0
#       undef T1_STOP_SEC_NEAR_NO_INIT_8_CORE0
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NEAR_NO_INIT_8_CORE1
#       undef T1_START_SEC_NEAR_NO_INIT_8_CORE1
#       pragma SET_DATA_SECTION( ".T1_sbssCore1" )
#   elif defined T1_STOP_SEC_NEAR_NO_INIT_8_CORE1
#       undef T1_STOP_SEC_NEAR_NO_INIT_8_CORE1
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NEAR_NO_INIT_8_CORE2
#       undef T1_START_SEC_NEAR_NO_INIT_8_CORE2
#       pragma SET_DATA_SECTION( ".T1_sbssCore2" )
#   elif defined T1_STOP_SEC_NEAR_NO_INIT_8_CORE2
#       undef T1_STOP_SEC_NEAR_NO_INIT_8_CORE2
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NEAR_NO_INIT_8_CLONE
#       undef T1_START_SEC_NEAR_NO_INIT_8_CLONE
#       pragma SET_DATA_SECTION( ".T1_sbssClone" )
#   elif defined T1_STOP_SEC_NEAR_NO_INIT_8_CLONE
#       undef T1_STOP_SEC_NEAR_NO_INIT_8_CLONE
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NEAR_NO_INIT_16
#       undef T1_START_SEC_NEAR_NO_INIT_16
#       pragma SET_DATA_SECTION( ".T1_sbss" )
#   elif defined T1_STOP_SEC_NEAR_NO_INIT_16
#       undef T1_STOP_SEC_NEAR_NO_INIT_16
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NEAR_NO_INIT_16_CORE0
#       undef T1_START_SEC_NEAR_NO_INIT_16_CORE0
#       pragma SET_DATA_SECTION( ".T1_sbssCore0" )
#   elif defined T1_STOP_SEC_NEAR_NO_INIT_16_CORE0
#       undef T1_STOP_SEC_NEAR_NO_INIT_16_CORE0
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NEAR_NO_INIT_16_CORE1
#       undef T1_START_SEC_NEAR_NO_INIT_16_CORE1
#       pragma SET_DATA_SECTION( ".T1_sbssCore1" )
#   elif defined T1_STOP_SEC_NEAR_NO_INIT_16_CORE1
#       undef T1_STOP_SEC_NEAR_NO_INIT_16_CORE1
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NEAR_NO_INIT_16_CORE2
#       undef T1_START_SEC_NEAR_NO_INIT_16_CORE2
#       pragma SET_DATA_SECTION( ".T1_sbssCore2" )
#   elif defined T1_STOP_SEC_NEAR_NO_INIT_16_CORE2
#       undef T1_STOP_SEC_NEAR_NO_INIT_16_CORE2
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NEAR_NO_INIT_16_CLONE
#       undef T1_START_SEC_NEAR_NO_INIT_16_CLONE
#       pragma SET_DATA_SECTION( ".T1_sbssClone" )
#   elif defined T1_STOP_SEC_NEAR_NO_INIT_16_CLONE
#       undef T1_STOP_SEC_NEAR_NO_INIT_16_CLONE
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NEAR_NO_INIT_32
#       undef T1_START_SEC_NEAR_NO_INIT_32
#       pragma SET_DATA_SECTION( ".T1_sbss" )
#   elif defined T1_STOP_SEC_NEAR_NO_INIT_32
#       undef T1_STOP_SEC_NEAR_NO_INIT_32
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NEAR_NO_INIT_32_CORE0
#       undef T1_START_SEC_NEAR_NO_INIT_32_CORE0
#       pragma SET_DATA_SECTION( ".T1_sbssCore0" )
#   elif defined T1_STOP_SEC_NEAR_NO_INIT_32_CORE0
#       undef T1_STOP_SEC_NEAR_NO_INIT_32_CORE0
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NEAR_NO_INIT_32_CORE1
#       undef T1_START_SEC_NEAR_NO_INIT_32_CORE1
#       pragma SET_DATA_SECTION( ".T1_sbssCore1" )
#   elif defined T1_STOP_SEC_NEAR_NO_INIT_32_CORE1
#       undef T1_STOP_SEC_NEAR_NO_INIT_32_CORE1
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NEAR_NO_INIT_32_CORE2
#       undef T1_START_SEC_NEAR_NO_INIT_32_CORE2
#       pragma SET_DATA_SECTION( ".T1_sbssCore2" )
#   elif defined T1_STOP_SEC_NEAR_NO_INIT_32_CORE2
#       undef T1_STOP_SEC_NEAR_NO_INIT_32_CORE2
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NEAR_NO_INIT_32_CLONE
#       undef T1_START_SEC_NEAR_NO_INIT_32_CLONE
#       pragma SET_DATA_SECTION( ".T1_sbssClone" )
#   elif defined T1_STOP_SEC_NEAR_NO_INIT_32_CLONE
#       undef T1_STOP_SEC_NEAR_NO_INIT_32_CLONE
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_8
#       undef T1_START_SEC_NO_INIT_8
#       pragma SET_DATA_SECTION( ".T1_bss" )
#   elif defined T1_STOP_SEC_NO_INIT_8
#       undef T1_STOP_SEC_NO_INIT_8
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_8_CORE0
#       undef T1_START_SEC_NO_INIT_8_CORE0
#       pragma SET_DATA_SECTION( ".T1_bssCore0" )
#   elif defined T1_STOP_SEC_NO_INIT_8_CORE0
#       undef T1_STOP_SEC_NO_INIT_8_CORE0
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_8_CORE1
#       undef T1_START_SEC_NO_INIT_8_CORE1
#       pragma SET_DATA_SECTION( ".T1_bssCore1" )
#   elif defined T1_STOP_SEC_NO_INIT_8_CORE1
#       undef T1_STOP_SEC_NO_INIT_8_CORE1
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_8_CORE2
#       undef T1_START_SEC_NO_INIT_8_CORE2
#       pragma SET_DATA_SECTION( ".T1_bssCore2" )
#   elif defined T1_STOP_SEC_NO_INIT_8_CORE2
#       undef T1_STOP_SEC_NO_INIT_8_CORE2
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_8_CLONE
#       undef T1_START_SEC_NO_INIT_8_CLONE
#       pragma SET_DATA_SECTION( ".T1_bssClone" )
#   elif defined T1_STOP_SEC_NO_INIT_8_CLONE
#       undef T1_STOP_SEC_NO_INIT_8_CLONE
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_16
#       undef T1_START_SEC_NO_INIT_16
#       pragma SET_DATA_SECTION( ".T1_bss" )
#   elif defined T1_STOP_SEC_NO_INIT_16
#       undef T1_STOP_SEC_NO_INIT_16
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_16_CORE0
#       undef T1_START_SEC_NO_INIT_16_CORE0
#       pragma SET_DATA_SECTION( ".T1_bssCore0" )
#   elif defined T1_STOP_SEC_NO_INIT_16_CORE0
#       undef T1_STOP_SEC_NO_INIT_16_CORE0
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_16_CORE1
#       undef T1_START_SEC_NO_INIT_16_CORE1
#       pragma SET_DATA_SECTION( ".T1_bssCore1" )
#   elif defined T1_STOP_SEC_NO_INIT_16_CORE1
#       undef T1_STOP_SEC_NO_INIT_16_CORE1
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_16_CORE2
#       undef T1_START_SEC_NO_INIT_16_CORE2
#       pragma SET_DATA_SECTION( ".T1_bssCore2" )
#   elif defined T1_STOP_SEC_NO_INIT_16_CORE2
#       undef T1_STOP_SEC_NO_INIT_16_CORE2
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_16_CLONE
#       undef T1_START_SEC_NO_INIT_16_CLONE
#       pragma SET_DATA_SECTION( ".T1_bssClone" )
#   elif defined T1_STOP_SEC_NO_INIT_16_CLONE
#       undef T1_STOP_SEC_NO_INIT_16_CLONE
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_32
#       undef T1_START_SEC_NO_INIT_32
#       pragma SET_DATA_SECTION( ".T1_bss" )
#   elif defined T1_STOP_SEC_NO_INIT_32
#       undef T1_STOP_SEC_NO_INIT_32
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_32_CORE0
#       undef T1_START_SEC_NO_INIT_32_CORE0
#       pragma SET_DATA_SECTION( ".T1_bssCore0" )
#   elif defined T1_STOP_SEC_NO_INIT_32_CORE0
#       undef T1_STOP_SEC_NO_INIT_32_CORE0
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_32_CORE1
#       undef T1_START_SEC_NO_INIT_32_CORE1
#       pragma SET_DATA_SECTION( ".T1_bssCore1" )
#   elif defined T1_STOP_SEC_NO_INIT_32_CORE1
#       undef T1_STOP_SEC_NO_INIT_32_CORE1
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_32_CORE2
#       undef T1_START_SEC_NO_INIT_32_CORE2
#       pragma SET_DATA_SECTION( ".T1_bssCore2" )
#   elif defined T1_STOP_SEC_NO_INIT_32_CORE2
#       undef T1_STOP_SEC_NO_INIT_32_CORE2
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_32_CLONE
#       undef T1_START_SEC_NO_INIT_32_CLONE
#       pragma SET_DATA_SECTION( ".T1_bssClone" )
#   elif defined T1_STOP_SEC_NO_INIT_32_CLONE
#       undef T1_STOP_SEC_NO_INIT_32_CLONE
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_32_TRACEBUFFER
#       undef T1_START_SEC_NO_INIT_32_TRACEBUFFER
#       pragma SET_DATA_SECTION( ".T1_traceBuffer" )
#   elif defined T1_STOP_SEC_NO_INIT_32_TRACEBUFFER
#       undef T1_STOP_SEC_NO_INIT_32_TRACEBUFFER
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_32_TRACEBUFFER_CORE0
#       undef T1_START_SEC_NO_INIT_32_TRACEBUFFER_CORE0
#       pragma SET_DATA_SECTION( ".T1_traceBufferCore0" )
#   elif defined T1_STOP_SEC_NO_INIT_32_TRACEBUFFER_CORE0
#       undef T1_STOP_SEC_NO_INIT_32_TRACEBUFFER_CORE0
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_32_TRACEBUFFER_CORE1
#       undef T1_START_SEC_NO_INIT_32_TRACEBUFFER_CORE1
#       pragma SET_DATA_SECTION( ".T1_traceBufferCore1" )
#   elif defined T1_STOP_SEC_NO_INIT_32_TRACEBUFFER_CORE1
#       undef T1_STOP_SEC_NO_INIT_32_TRACEBUFFER_CORE1
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_32_TRACEBUFFER_CORE2
#       undef T1_START_SEC_NO_INIT_32_TRACEBUFFER_CORE2
#       pragma SET_DATA_SECTION( ".T1_traceBufferCore2" )
#   elif defined T1_STOP_SEC_NO_INIT_32_TRACEBUFFER_CORE2
#       undef T1_STOP_SEC_NO_INIT_32_TRACEBUFFER_CORE2
#       pragma SET_DATA_SECTION( )

#   elif defined T1_START_SEC_NO_INIT_32_TRACEBUFFER_CLONE
#       undef T1_START_SEC_NO_INIT_32_TRACEBUFFER_CLONE
#       pragma SET_DATA_SECTION( ".T1_traceBufferClone" )
#   elif defined T1_STOP_SEC_NO_INIT_32_TRACEBUFFER_CLONE
#       undef T1_STOP_SEC_NO_INIT_32_TRACEBUFFER_CLONE
#       pragma SET_DATA_SECTION( )

#   else
#       error "T1_MemMap.h: no valid section define used."
#   endif

#else
#   error "T1_MemMap.h: no recognised compiler."
#endif
