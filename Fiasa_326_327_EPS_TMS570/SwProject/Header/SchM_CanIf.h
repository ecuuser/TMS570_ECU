/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_CanIf.h
 *   Description:  Header of BSW Scheduler for CanIf
 *********************************************************************************************************************/


#ifndef SCHM_CANIF_H
#define SCHM_CANIF_H


#include "SchM.h"


#define SchM_Enter_CanIf(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_CanIf(area)	SCHM_EXIT_EXCLUSIVE(area)


#endif
