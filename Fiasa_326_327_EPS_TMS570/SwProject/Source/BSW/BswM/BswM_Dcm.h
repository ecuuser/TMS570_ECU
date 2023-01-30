/* Kernbauer Version: 1.14 Konfiguration: BswM Erzeugungsgangnummer: 23 */

/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2011-2014 by Vector Informatik GmbH.                                             All rights reserved.
 * 
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  BswM_Dcm.h
 *      Project:  SysService_AsrBswM
 *       Module:  MICROSAR Basic Software Mode Manager
 *    Generator:  
 *
 *  Description:  callback header for Dcm
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Patrick Markl                 visml         Vector Informatik GmbH
 *  Daniel Hof                    visdhf        Vector Informatik GmbH
 *  Thomas Kuhl                   vispet        Vector Informatik GmbH
 *  Leticia Garcia Herrera        visgle        Vector Informatik GmbH
 *  
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2011-01-17  visml   ESCAN00046216 Creation
 *                        visdhf
 *  01.01.00  2011-04-04  visdhf  ESCAN00049801: no changes here
 *  01.02.00  2011-06-16  visdhf  ESCAN00049881: added Partial Networks support
 *                                ESCAN00051663: removed AR version check
 *                                ESCAN00051684: extended Det error checks
 *                                ESCAN00051685: changed implementation of BswM_LinSM_CurrentSchedule() 
 *                                ESCAN00051934: changed call of BswM_Init_Gen
 *                                ESCAN00051949: added definition of BswM_Dcm_SetPassiveMode()
 *                                ESCAN00052907: added ASR SWS version defines
 *  01.02.01  2011-11-03  vispet  ESCAN00054123: Remove unnecessary variable extern declaration
 *  01.03.00  2011-11-25  vispet  ESCAN00053583: AR3-1698: Add MISRA justifications in source code for automatic generation of MISRA reports
 *                                ESCAN00053609: AR3-2069: Remove non-SchM code for critical section handling
 *                                ESCAN00054142: Missing functionality of BswM_Dcm_ApplicationUpdated
 *  01.04.00  2012-03-19  vispet  ESCAN00056682: AR3-2357 Support Mode Switch notification for SWC
 *                                ESCAN00058090: Remove preprocessor defines V_CRITICAL_SECTION_USE_SCHM_COMMENT
 *                                ESCAN00058091: Add BswM Timer Handling
 *  01.05.00  2012-06-26  vispet  ESCAN00057762: no changes
 *  01.06.00  2012-08-28  vispet  ESCAN00057856: no changes
 *                                ESCAN00060095: no changes
 *  01.06.01  2012-10-17  vispet  ESCAN00062295: no changes
 *  01.07.00  2013-04-04  visgle  ESCAN00066117: no changes
 *                                ESCAN00066271: no changes
 *                                ESCAN00062683: no changes
 *  01.08.00  2013-09-25  visgle  ESCAN00065553: no changes
 *                                ESCAN00065554: no changes
 *                                ESCAN00069773: no changes
 *                                ESCAN00070914: no changes
 *                                ESCAN00071083: no changes
 *  01.09.00  2014-01-30  visgle  ESCAN00068671: no changes
 *                                ESCAN00071426: no changes
 *********************************************************************************************************************/


#if !defined(BSWM_DCM_H)
#define BSWM_DCM_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "Dcm.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT VERSIONS
 *********************************************************************************************************************/
# define BSWM_DCM_MAJOR_VERSION   0x01u
# define BSWM_DCM_MINOR_VERSION   0x09u
# define BSWM_DCM_PATCH_VERSION   0x00u

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define BSWM_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
# include "MemMap.h" 

extern FUNC(void, BSWM_CODE) BswM_Dcm_RequestCommunicationMode(NetworkHandleType Network, Dcm_CommunicationModeType RequestedMode);
extern FUNC(void, BSWM_CODE) BswM_Dcm_RequestResetMode(Dcm_ResetModeType RequestedMode);
extern FUNC(void, BSWM_CODE) BswM_Dcm_PassiveMode(Dcm_ResetModeType RequestedMode);
extern FUNC(void, BSWM_CODE) BswM_Dcm_SetPassiveMode(boolean mode);
extern FUNC(void, BSWM_CODE) BswM_Dcm_ApplicationUpdated(void);


# define BSWM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
# include "MemMap.h" 

#endif

/**********************************************************************************************************************
 *  END OF FILE: BswM_DCM.h
 *********************************************************************************************************************/
