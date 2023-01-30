/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_CanSM.h
 *   Description:  Header of BSW Scheduler for CanSM
 *********************************************************************************************************************/


#ifndef SCHM_CANSM_H
#define SCHM_CANSM_H


#include "SchM.h"


#define SchM_Enter_CanSM(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_CanSM(area)	SCHM_EXIT_EXCLUSIVE(area)


#endif
