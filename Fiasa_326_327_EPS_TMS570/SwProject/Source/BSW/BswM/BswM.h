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
 *         File:  BswM.h
 *      Project:  SysService_AsrBswM
 *       Module:  MICROSAR Basic Software Mode Manager
 *    Generator:  
 *
 *  Description:  Implements AUTOSAR BswM
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
 *                                ESCAN00069773: AR3-2562: first message after restart or startup must be the Nm message
 *                                ESCAN00070914: Wrong type of memory class of BswM_UserConfig[BSWM_USER_COUNT]
 *                                ESCAN00071083: no changes
 *  01.09.00  2014-01-30  visgle  ESCAN00068671: no changes
 *                                ESCAN00071426: no changes
 *********************************************************************************************************************/


#if !defined(BSWM_H)
# define BSWM_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "ComStack_Types.h"
# include "BswM_Cfg.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*********************************************************************************************************************/
/* Version                  (abcd: Main version ab Sub Version cd )                                                  */
/*********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : SysService_AsrBswM CQComponent : Implementation */
# define SYSSERVICE_ASRBSWM_VERSION          (0x0109u)
# define SYSSERVICE_ASRBSWM_RELEASE_VERSION  (0x00u)

/* Component Version Information */
# define BSWM_SW_MAJOR_VERSION       (SYSSERVICE_ASRBSWM_VERSION >> 8u)
# define BSWM_SW_MINOR_VERSION       (SYSSERVICE_ASRBSWM_VERSION & 0x00FF)
# define BSWM_SW_PATCH_VERSION       SYSSERVICE_ASRBSWM_RELEASE_VERSION


/**********************************************************************************************************************
 * Module Identificatiion
 *********************************************************************************************************************/
# define BSWM_VENDOR_ID           (0x001Eu)
# define BSWM_MODULE_ID           (uint16)(0x002Au)

# define BSWM_AR_MAJOR_VERSION    (0x02u) /* Major version number of AUTOSAR specification on which the appropriate implementation is based on. */
# define BSWM_AR_MINOR_VERSION    (0x00u) /* Minor version number of AUTOSAR specification on which the appropriate implementation is based on. */
# define BSWM_AR_PATCH_VERSION    (0x00u) /* Patch level version number of AUTOSAR specification on which the appropriate implementation is based on. */


/**********************************************************************************************************************
 *  Macros
 *********************************************************************************************************************/
# define BSWM_RULE_IMMEDIATE             ((uint8)0x00u)
# define BSWM_RULE_DEFERRED              ((uint8)0x01u)

/* Mode domains: */
# define BSWM_DOMAIN_COMM_CHANNEL        ((uint8)0u)
# define BSWM_DOMAIN_DCM_COMCTRL_CHANNEL ((uint8)1u)
# define BSWM_DOMAIN_DCM_RESET           ((uint8)2u)
# define BSWM_DOMAIN_CANSM_CHANNEL       ((uint8)3u)
# define BSWM_DOMAIN_FRSM_CHANNEL        ((uint8)4u)
# define BSWM_DOMAIN_LINSM_CHANNEL       ((uint8)5u)
# define BSWM_DOMAIN_LINTP_CHANNEL       ((uint8)6u)
# define BSWM_DOMAIN_NM_CHANNEL          ((uint8)7u)
# define BSWM_DOMAIN_LINSM_SCHED         ((uint8)8u)
# define BSWM_DOMAIN_COMM_PNC            ((uint8)9u)

# define BSWM_DOMAIN_TIMER               ((uint8)10u)
# define BSWM_DOMAIN_LINSM_SCHED_END     ((uint8)11u)


/* DET error codes BswM0029 */
# define BSWM_E_NO_INIT                   ((uint8)0x01u)  /* (DET): A service was called prior to initialization           */
# define BSWM_E_NULL_POINTER              ((uint8)0x02u)  /* (DET): A null pointer was passed as an argument               */
# define BSWM_E_INVALID_PAR               ((uint8)0x03u)  /* (DET): A parameter was invalid (unspecific)                   */
# define BSWM_E_REQ_USER_OUT_OF_RANGE     ((uint8)0x04u)  /* (DET): A requesting user was out of range                     */
# define BSWM_E_REQ_MODE_OUT_OF_RANGE     ((uint8)0x05u)  /* (DET): A requested mode was out of range                      */
# define BSWM_E_PARAM_CONFIG              ((uint8)0x06u)  /* (DET): The provided configuration is inconsistent Development */
# define BSWM_E_ACTION_FAILED             ((uint8)0x07u)  /* (DEM): An action returned Production                          */


/* Service IDs */
# define BSWM_INITMEMORY_ID                       ((uint8)0x80u)
# define BSWM_INIT_ID                             ((uint8)0x00u)
# define BSWM_DEINIT_ID                           ((uint8)0x04u)
# define BSWM_GETVERSIONINFO_ID                   ((uint8)0x01u)
# define BSWM_REQUESTMODE_ID                      ((uint8)0x02u)
# define BSWM_COMM_CURRENTMODE_ID                 ((uint8)0x0Eu)
# define BSWM_DCM_REQUESTCOMMUNICATIONMODE_ID     ((uint8)0x06u)
# define BSWM_DCM_REQUESTRESETMODE_ID             ((uint8)0x07u)
# define BSWM_CANSM_CURRENTSTATE_ID               ((uint8)0x05u)
# define BSWM_FRSM_CURRENTSTATE_ID                ((uint8)0x0Cu)
# define BSWM_LINSM_CURRENTSTATE_ID               ((uint8)0x09u)
# define BSWM_LINSM_CURRENTSCHEDULE_ID            ((uint8)0x0Au)
# define BSWM_LINTP_REQUESTMODE_ID                ((uint8)0x0Bu)
# define BSWM_MAINFUNCTION_ID                     ((uint8)0x03u)
# define BSWM_NM_STATE_CHANGE_ID                  ((uint8)0x0Fu)
# define BSWM_DCM_SET_PASSIVE_MODE_ID             ((uint8)0x10u)
# define BSWM_DCM_APPLICATION_UPDATED_ID          ((uint8)0x14u)
# define BSWM_COMM_CURRENT_PNC_MODE_ID            ((uint8)0x15u)
# define BSWM_LINSM_SCHEDEND_NOTIFICATION_ID      ((uint8)0x16u)


# define BSWM_UNDEFINED  ((uint8)0x02u)
# define BSWM_TRUE       ((uint8)0x01u)
# define BSWM_FALSE      ((uint8)0x00u) 

# define BSWM_TRIGGER    ((uint8)0x00u)
# define BSWM_CONDITION  ((uint8)0x01u)

# define BSWM_EXEC_TRUE  ((uint8)0x01u)
# define BSWM_EXEC_FALSE ((uint8)0x02u)


# define BSWM_TMR_STOPPED  0u
# define BSWM_TMR_STARTED  1u
# define BSWM_TMR_EXPIRED  2u

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef uint8 BswM_UserDomainType;

# if defined ( BSWM_MODE_COUNT )
#  if(BSWM_MODE_COUNT > 255)
typedef uint16 BswM_ModeType;
#  else
typedef uint8  BswM_ModeType;
#  endif
# else
typedef uint8 BswM_ModeType;
# endif

# if(BSWM_USER_COUNT > 255)
typedef uint16 BswM_UserType;
# else
typedef uint8  BswM_UserType;
# endif

typedef uint16 BswM_TimerHdlType;

typedef P2FUNC(Std_ReturnType, BSWM_CODE, BswM_RuleTableFctPtrType) (void);
typedef P2CONST(BswM_RuleTableFctPtrType, AUTOMATIC, BSWM_CONST) BswM_RuleFctPtrType;
typedef uint8 BswM_BusSM_StateType;


typedef struct
{
  BswM_ModeType currentMode;
  BswM_ModeType requestedMode;
}BswM_UserModeType;

typedef struct
{
  uint8                           modeExecContext;  /* Stores if the mode rule is executed deferred or immediate.             */
  BswM_RuleFctPtrType             RuleFctPtr; /* Pointer to a function which is called in order to execute a rule */
  uint8                           NrOfRules;  /* number of rules which belong to the user */
  BswM_ModeType                   modeInitValue;    /* Value for initialization of the mode */
  BswM_UserDomainType             domain;   /* user domain: CanSM, LinSM... */
  NetworkHandleType               network;  /* network the user belongs to */
#if ( BSWM_PN_ENABLED == STD_ON )
  PNCHandleType                   pncGobalIndex; /* global Pnc index */
#endif
  BswM_TimerHdlType               TimerHandle; /* BswM timer handle */
}BswM_UserConfigType;



/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

# define BSWM_START_SEC_CONST_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
# include "MemMap.h"

extern CONST(BswM_UserConfigType, BSWM_CONST)  BswM_UserConfig[BSWM_USER_COUNT];

# define BSWM_STOP_SEC_CONST_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"




/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define BSWM_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
# include "MemMap.h"

FUNC(void, BSWM_CODE) BswM_InitMemory(void);
FUNC(void, BSWM_CODE) BswM_Init(P2CONST(BswM_ConfigType, AUTOMATIC, BSWM_PBCFG) ConfigPtr);
FUNC(void, BSWM_CODE) BswM_Deinit(void);
FUNC(void, BSWM_CODE) BswM_MainFunction(void);
FUNC(Std_ReturnType, BSWM_CODE) BswM_RequestMode(BswM_UserType requesting_user, BswM_ModeType requested_mode);

# if(BSWM_VERSION_INFO_API == STD_ON)
FUNC(void, BSWM_CODE) BswM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, BSWM_APPL_DATA) VersionInfo);
# endif

#if ( BSWM_ENABLE_DCM_APPL_UPDATE == STD_ON )
# if(BSWM_ENABLE_DCM_APPL_UPDATE_RTE == STD_OFF )

extern FUNC(void, BSWM_APPL_CODE) Appl_BswM_ApplicationUpdated(void);

# endif
#endif

# define BSWM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
# include "MemMap.h"


#endif

/**********************************************************************************************************************
 *  END OF FILE: BswM.h
 *********************************************************************************************************************/
