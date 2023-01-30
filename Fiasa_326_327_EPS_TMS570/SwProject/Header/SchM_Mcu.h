/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_Mcu.h
 *   Description:  Header of BSW Scheduler for Mcu
 *********************************************************************************************************************/


#ifndef SCHM_MCU_H
#define SCHM_MCU_H


#include "SchM.h"


#define SchM_Enter_Mcu(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_Mcu(area)		SCHM_EXIT_EXCLUSIVE(area)


#endif
