/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_EcuM.h
 *   Description:  Header of BSW Scheduler for EcuM
 *********************************************************************************************************************/


#ifndef SCHM_ECUM_H
#define SCHM_ECUM_H


#include "SchM.h"


#define SchM_Enter_EcuM(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_EcuM(area)	SCHM_EXIT_EXCLUSIVE(area)


#endif
