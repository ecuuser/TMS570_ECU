/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_BswM.h
 *   Description:  Header of BSW Scheduler for BswM
 *********************************************************************************************************************/


#ifndef SCHM_BSWM_H
#define SCHM_BSWM_H


#include "SchM.h"


#define SchM_Enter_BswM(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_BswM(area)	SCHM_EXIT_EXCLUSIVE(area)


#endif
