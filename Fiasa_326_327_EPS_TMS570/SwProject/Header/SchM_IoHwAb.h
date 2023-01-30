/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_IoHwAb.h
 *   Description:  Header of BSW Scheduler for IoHwAb
 *********************************************************************************************************************/


#ifndef SCHM_IOHWAB_H
#define SCHM_IOHWAB_H


#include "SchM.h"


#define SchM_Enter_IoHwAb(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_IoHwAb(area)	SCHM_EXIT_EXCLUSIVE(area)


#endif
