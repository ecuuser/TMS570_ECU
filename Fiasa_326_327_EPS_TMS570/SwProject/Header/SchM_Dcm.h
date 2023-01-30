/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_Dcm.h
 *   Description:  Header of BSW Scheduler for Dcm
 *********************************************************************************************************************/


#ifndef SCHM_DCM_H
#define SCHM_DCM_H


#include "SchM.h"


#define SchM_Enter_Dcm(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_Dcm(area)		SCHM_EXIT_EXCLUSIVE(area)


#endif
