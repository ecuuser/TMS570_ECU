/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_CanNm.h
 *   Description:  Header of BSW Scheduler for CanNm
 *********************************************************************************************************************/


#ifndef SCHM_CANNM_H
#define SCHM_CANNM_H


#include "SchM.h"


#define SchM_Enter_CanNm(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_CanNm(area)	SCHM_EXIT_EXCLUSIVE(area)


#endif
