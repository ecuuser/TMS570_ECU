/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_Fee.h
 *   Description:  Header of BSW Scheduler for Fee
 *********************************************************************************************************************/


#ifndef SCHM_FEE_H
#define SCHM_FEE_H


#include "SchM.h"


#define SchM_Enter_Fee(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_Fee(area)		SCHM_EXIT_EXCLUSIVE(area)


#endif
