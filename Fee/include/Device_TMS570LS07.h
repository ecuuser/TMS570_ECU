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
 *         File:  Device_TMS570LS07.c
 *      Project:  Tms570_TIFEEDriver
 *       Module:  TIFEEDriver
 *    Generator:  None
 *
 *  Description:  This file defines the number of sectors.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  Vishwanath Reddy
 *---------------------------------------------------------------------------------------------------------------------
 * Revision History
 *---------------------------------------------------------------------------------------------------------------------
 * Version        Date         Author               Change ID        Description
 *--------------------------------------------------------------------------------------------------------------------- 
 * 01.17.01		  30Oct2014    Vishwanath Reddy 	SDOCM00113536    Initial Version.
 * 01.22.00		  26Dec2014    Vishwanath Reddy     SDOCM00114423    Changes for unification of Champion/Archer.
 * 01.23.00		  12Oct2015    Vishwanath Reddy     SDOCM00119455    Updated version history.
 * 01.23.01		  17Nov2015    Vishwanath Reddy     SDOCM00120161    Updated version history.
 * 01.23.02		  10Mar2016    Vishwanath Reddy     SDOCM00121622    Updated version history.  
 *********************************************************************************************************************/

 /*********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#ifndef DEVICE_TMS570LS07x_H
#define DEVICE_TMS570LS07x_H

#include "fee_interface.h"

#if ((TI_FEE_GENERATE_DEVICEANDVIRTUALSECTORSTRUC == STD_OFF) && (TI_FEE_PHYSICALSECTOR_SIZE == 4U))

/** @def DEVICE_CONFIGURATION_VERSION
*   @brief Device Configuration Version
*
*   @note Indicates the current version of the device files
*/
#define DEVICE_CONFIGURATION_VERSION 0U             /* Indicates the current version of the device files */

/** @def DEVICE_NUMBER_OF_FLASH_BANKS
*   @brief Number of Flash Banks
*
*   @note Defines the number of Flash Banks on the device
*/
#define DEVICE_NUMBER_OF_FLASH_BANKS 1U             /* Defines the number of Flash Banks on the device */


/** @def DEVICE_BANK_MAX_NUMBER_OF_SECTORS
*   @brief Maximum number of Sectors
*
*   @note Defines the maxium number of sectors in all banks
*/
#define DEVICE_BANK_MAX_NUMBER_OF_SECTORS 16U        /* Defines the maximum number of sectors in all banks */

/** @def DEVICE_BANK1_NUMBER_OF_SECTORS
*   @brief Number of Sectors
*
*   @note Defines the number of sectors in bank1
*/
#define DEVICE_BANK1_NUMBER_OF_SECTORS 16U           /* Defines the number of sectors in bank1 */


/** @def DEVICE_NUMBER_OF_READ_CYCLE_THRESHOLDS
*   @brief Number of Sectors
*
*   @note Defines the number of Read Cycle Thresholds 
*/
#define DEVICE_NUMBER_OF_READ_CYCLE_THRESHOLDS 4U   /* Defines the number of Read Cycle Thresholds */

#endif

#endif /* DEVICE_TMS570LS07x_H */

/* End of File */
