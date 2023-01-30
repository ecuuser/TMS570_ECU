/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_Wdg.h
 *   Description:  Header of BSW Scheduler for Wdg
 *********************************************************************************************************************/


#ifndef SCHM_WDG_H
#define SCHM_WDG_H


#include "SchM.h"


#define SchM_Enter_Wdg_TMS570LS3x(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_Wdg_TMS570LS3x(area)	SCHM_EXIT_EXCLUSIVE(area)


#endif
