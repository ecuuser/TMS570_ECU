/*************************************************************************************
*   FILE:           T1_modInterface.h
*
*   DESCRIPTION:    T1.mod interface
*
*   VISIBILITY:     extern
*
*   $Author: nick $
*
*   $Revision: 10689 $
*
*   $URL: https://gliwa.com/svn/repos/T1target/trunk/src/T1.mod/src/all/T1_modInterface.h $
*
*   Copyright:      Gliwa GmbH | know- how in embedded software
*                   Weilheim i.OB.
*                   All rights reserved
*************************************************************************************/

#ifndef T1_MOD_INTERFACE_H_
#define T1_MOD_INTERFACE_H_ (1)

/*----------------------------------------------------------------------------------*/
/*--- header includes --------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include "T1_baseInterface.h"

/*----------------------------------------------------------------------------------*/
/*--- macros and inline functions --------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#define T1_MOD_PLUGIN_ID                        (4u)

#if defined T1_ENABLE && !defined T1_DISABLE_T1_MOD
#   define T1_modPlugin                         (&T1_modPluginStruct)
#else
#   define T1_modPlugin                         (T1_DISABLED_PLUGIN)
#endif


/*----------------------------------------------------------------------------------*/
/*--- external declarations for global variables -----------------------------------*/
/*----------------------------------------------------------------------------------*/

#if defined T1_ENABLE && !defined T1_DISABLE_T1_MOD
#   define T1_START_SEC_CONST_32
#   include "T1_MemMap.h"
T1_DeclarePlugin( T1_modPluginStruct );
#   define T1_STOP_SEC_CONST_32
#   include "T1_MemMap.h"
#endif

#endif /* T1_MOD_INTERFACE_H_ */
