/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_Port.h
 *   Description:  Header of BSW Scheduler for Port
 *********************************************************************************************************************/


#ifndef SCHM_PORT_H
#define SCHM_PORT_H


#include "SchM.h"


#define SchM_Enter_Port(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_Port(area)	SCHM_EXIT_EXCLUSIVE(area)


#endif
