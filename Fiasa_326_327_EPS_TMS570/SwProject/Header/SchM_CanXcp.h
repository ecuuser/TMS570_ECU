/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_CanXcp.h
 *   Description:  Header of BSW Scheduler for CanXcp
 *********************************************************************************************************************/


#ifndef SCHM_CANXCP_H
#define SCHM_CANXCP_H


#include "SchM.h"


#define SchM_Enter_CanXcp(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_CanXcp(area)	SCHM_EXIT_EXCLUSIVE(area)


#endif
