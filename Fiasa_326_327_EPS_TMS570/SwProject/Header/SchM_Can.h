/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_Can.h
 *   Description:  Header of BSW Scheduler for Can
 *********************************************************************************************************************/


#ifndef SCHM_CAN_H
#define SCHM_CAN_H


#include "SchM.h"


#define SchM_Enter_Can(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_Can(area)		SCHM_EXIT_EXCLUSIVE(area)


#endif
