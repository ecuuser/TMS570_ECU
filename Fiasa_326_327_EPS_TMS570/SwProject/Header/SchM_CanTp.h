/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_CanTp.h
 *   Description:  Header of BSW Scheduler for CanTp
 *********************************************************************************************************************/


#ifndef SCHM_CANTP_H
#define SCHM_CANTP_H


#include "SchM.h"


#define SchM_Enter_CanTp(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_CanTp(area)	SCHM_EXIT_EXCLUSIVE(area)


#endif
