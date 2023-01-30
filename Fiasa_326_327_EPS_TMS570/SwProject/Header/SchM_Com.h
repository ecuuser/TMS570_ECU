/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_Com.h
 *   Description:  Header of BSW Scheduler for Com
 *********************************************************************************************************************/


#ifndef SCHM_COM_H
#define SCHM_COM_H


#include "SchM.h"


#define SchM_Enter_Com(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_Com(area)		SCHM_EXIT_EXCLUSIVE(area)


#endif
