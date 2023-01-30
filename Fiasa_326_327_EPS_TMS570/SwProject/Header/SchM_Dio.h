/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SchM_Dio.h
 *   Description:  Header of BSW Scheduler for Dio
 *********************************************************************************************************************/


#ifndef SCHM_DIO_H
#define SCHM_DIO_H


#include "SchM.h"


#define SchM_Enter_Dio(area)	SCHM_ENTER_EXCLUSIVE(area)
#define SchM_Exit_Dio(area)		SCHM_EXIT_EXCLUSIVE(area)


#endif
