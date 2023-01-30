/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_ComM.h
 *   Description:  Header of BSW Scheduler for ComM
 *********************************************************************************************************************/


#ifndef SCHM_COMM_H
#define SCHM_COMM_H


#include "SchM.h"


#define SchM_Enter_ComM(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_ComM(area)	SCHM_EXIT_EXCLUSIVE(area)


#endif
