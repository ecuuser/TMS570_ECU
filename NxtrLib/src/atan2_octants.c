/*****************************************************************************
* Copyright 2010 Nexteer, Inc., All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : atan2.c
* Module Description: Define octants constant for use in the _atan2_asm_ function.
* Product           : Gen II Plus - EA3.0
* Author            : Blake Latchford
*****************************************************************************/

#include "Std_Types.h"

#define ATAN2_START_SEC_VAR_INIT_32
#include "MemMap.h"

sint32 octants[8] = {2,1,0,-1,-2,-3,4,3};

#define ATAN2_STOP_SEC_VAR_INIT_32
#include "MemMap.h"
