/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_PduR.h
 *   Description:  Header of BSW Scheduler for PduR
 *********************************************************************************************************************/


#ifndef SCHM_PDUR_H
#define SCHM_PDUR_H


#include "SchM.h"


#define SchM_Enter_PduR(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_PduR(area)	SCHM_EXIT_EXCLUSIVE(area)


#endif
