/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_NvM.h
 *   Description:  Header of BSW Scheduler for NvM
 *********************************************************************************************************************/


#ifndef SCHM_NVM_H
#define SCHM_NVM_H


#include "SchM.h"


#define SchM_Enter_NvM(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_NvM(area)		SCHM_EXIT_EXCLUSIVE(area)


#endif
