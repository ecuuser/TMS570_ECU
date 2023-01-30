/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *                 TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *                 Property of Texas Instruments, Unauthorized reproduction and/or distribution
 *                 is strictly prohibited.  This product  is  protected  under  copyright  law
 *                 and  trade  secret law as an  unpublished work.
 *                 (C) Copyright Texas Instruments - 2014.  All rights reserved.
 *
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Device_header.h
 *      Project:  Tms570_TIFEEDriver
 *       Module:  TIFEEDriver
 *    Generator:  None
 *
 *  Description:  This file includes the header file.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  Vishwanath Reddy
 *---------------------------------------------------------------------------------------------------------------------
 * Revision History
 *---------------------------------------------------------------------------------------------------------------------
 * Version        Date         Author               Change ID        Description
 *--------------------------------------------------------------------------------------------------------------------- 
 * 01.15.00		  06Jun2014    Vishwanath Reddy 	                 History Added.
 * 01.22.00		  26Dec2014    Vishwanath Reddy     SDOCM00114423    Changes for unification of Champion/Archer.
 * 01.23.00		  12Oct2015    Vishwanath Reddy     SDOCM00119455    Updated version history.
 * 01.23.01		  17Nov2015    Vishwanath Reddy     SDOCM00120161    Updated version history.
 * 01.23.02		  10Mar2016    Vishwanath Reddy     SDOCM00121622    Updated version history.
 *********************************************************************************************************************/

 /*********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#ifndef TI_FEE_DEVICEHEADER_H
#define TI_FEE_DEVICEHEADER_H

/* Include Files */
#include "fee_interface.h"
#include "F021.h"
#include "Std_Types.h"
#include "Device_types.h"

/* Uncomment the appropriate include file depending on the device you are using */
#if ((TI_FEE_GENERATE_DEVICEANDVIRTUALSECTORSTRUC == STD_OFF) && (TI_FEE_PHYSICALSECTOR_SIZE == 4U))
#include "Device_TMS570LS07.h"
#endif
#if ((TI_FEE_GENERATE_DEVICEANDVIRTUALSECTORSTRUC == STD_OFF) && (TI_FEE_PHYSICALSECTOR_SIZE == 16U))
#include "Device_TMS570LS12.h"
#endif

/* End of file */
#endif

