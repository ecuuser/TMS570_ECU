/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_WdgM.h
 *   Description:  Header of BSW Scheduler for WdgM
 *********************************************************************************************************************/


#ifndef SCHM_WDGM_H
#define SCHM_WDGM_H


#include "SchM.h"


#define SchM_Enter_WdgM(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_WdgM(area)	SCHM_EXIT_EXCLUSIVE(area)


#endif
