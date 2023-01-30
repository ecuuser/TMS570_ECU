/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_Dem.h
 *   Description:  Header of BSW Scheduler for Dem
 *********************************************************************************************************************/


#ifndef SCHM_DEM_H
#define SCHM_DEM_H


#include "SchM.h"


#define SchM_Enter_Dem(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_Dem(area)		SCHM_EXIT_EXCLUSIVE(area)


#endif
