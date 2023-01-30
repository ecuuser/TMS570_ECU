/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_Gpt.h
 *   Description:  Header of BSW Scheduler for Gpt
 *********************************************************************************************************************/


#ifndef SCHM_GPT_H
#define SCHM_GPT_H


#include "SchM.h"


#define SchM_Enter_Gpt(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_Gpt(area)		SCHM_EXIT_EXCLUSIVE(area)


#endif
