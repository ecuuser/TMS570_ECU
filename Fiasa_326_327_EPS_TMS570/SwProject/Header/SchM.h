/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM.h
 *   Description:  Header of BSW Scheduler SchM
 *********************************************************************************************************************/


#ifndef SCHM_H
#define SCHM_H


#include "Os.h"


#define SCHM_ENTER_EXCLUSIVE(area)	SuspendAllInterrupts()
#define SCHM_EXIT_EXCLUSIVE(area)	ResumeAllInterrupts()


#define SchM_Init()		((void *)0)


#endif
