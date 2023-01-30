/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_NvMProxy.h
 *   Description:  Header of BSW Scheduler for NvMProxy
 *********************************************************************************************************************/


#ifndef SCHM_NVMPROXY_H
#define SCHM_NVMPROXY_H


#include "SchM.h"


#define SchM_Enter_NvMProxy(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_NvMProxy(area)	SCHM_EXIT_EXCLUSIVE(area)


#endif
