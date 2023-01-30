/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *                 TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *                 Property of Texas Instruments, Unauthorized reproduction and/or distribution
 *                 is strictly prohibited.  This product  is  protected  under  copyright  law
 *                 and  trade  secret law as an  unpublished work.
 *                 (C) Copyright Texas Instruments - 2012.  All rights reserved.
 *
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  fee_cbk.h
 *      Project:  Tms570_FEEDriver
 *       Module:  FEE Driver
 *    Generator:  None
 *
 *  Description:  This file declares prototypes for callback functions.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  Vishwanath Reddy
 *---------------------------------------------------------------------------------------------------------------------
 * Revision History
 *---------------------------------------------------------------------------------------------------------------------
 * Version        Date         Author               Change ID        Description
 *---------------------------------------------------------------------------------------------------------------------
 * 00.01.00       07Sept2012    Vishwanath Reddy     0000000000000    Initial Version
 * 00.01.02       30Nov2012     Vishwanath Reddy     SDOCM00097786    Misra Fixes, Memory segmentation changes.
 * 01.23.00		  12Oct2015     Vishwanath Reddy     SDOCM00119455    Updated version history.
 * 01.23.01		  17Nov2015     Vishwanath Reddy     SDOCM00120161    Updated version history.
 * 01.23.02		  10Mar2016     Vishwanath Reddy     SDOCM00121622    Updated version history.
 *********************************************************************************************************************/

#ifndef FEE_CBK_H
#define FEE_CBK_H

/* Fee Job Callback Function Declarations */
#define FEE_START_SEC_CODE
#include "MemMap.h"

/* SourceId : HL_Fee_SourceId_x */
/* DesignId : HL_FEE_DesignId_xx */
/* Requirements : AR_FEE3x_SR62 */
extern void FEE_NVM_JOB_END_NOTIFICATION (void);
extern void FEE_NVM_JOB_ERROR_NOTIFICATION (void);

#define FEE_STOP_SEC_CODE
#include "MemMap.h"

#endif /* FEE_CBK_H */

/**********************************************************************************************************************
 *  END OF FILE: fee_cbk.h
 *********************************************************************************************************************/
 

