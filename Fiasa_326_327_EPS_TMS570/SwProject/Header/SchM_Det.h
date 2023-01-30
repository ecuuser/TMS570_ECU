/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_Det.h
 *   Description:  Header of BSW Scheduler for Det
 *********************************************************************************************************************/


#ifndef SCHM_DET_H
#define SCHM_DET_H


#include "SchM.h"


#define SchM_Enter_Det(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_Det(area)		SCHM_EXIT_EXCLUSIVE(area)


#endif
