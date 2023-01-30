/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2007-2013 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  NmStack_Types.h
 *    Component:  AUTOSAR NM Interface
 *       Module:  AUTOSAR NM
 *    Generator:  -
 *
 *  Description:  Type definitions of AUTOSAR Network Management
 *                AUTOSAR Release 3.0
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Oliver Hornung                visoh         Vector Informatik GmbH
 *  Markus Drescher               vismdr        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  2.00.00   2007-07-23  visoh   ESCAN00021576 Update to AUTOSAR 3.0
 *                        vismas  ESCAN00022361 No changes
 *  2.01.00   2008-02-01  visoh   ESCAN00024708 Added Coordinator Synchronization Support
 *  2.02.00   2008-02-27  visoh   ESCAN00024931 No changes
 *  2.02.01   2008-03-06  visoh                 No changes
 *  2.03.00   2008-03-10  visoh   ESCAN00025260 No changes
 *                                ESCAN00025261 Extended Coordinator Synchronization Support
 *  2.04.00   2008-03-30  visoh   ESCAN00025670 No changes
 *  2.05.00   2008-04-21  visoh   ESCAN00025482 No changes
 *                                ESCAN00026022 No changes
 *                                ESCAN00026252 No changes
 *  2.05.01   2008-04-23  visoh   ESCAN00026228 No changes
 *                                ESCAN00026487 No changes
 *                                ESCAN00026663 No changes
 *                                ESCAN00026866 No changes
 *  2.06.00   2008-05-30  visoh   ESCAN00027192 No changes
 *                                ESCAN00027193 No changes
 *  2.06.01   2008-06-19  vismas  ESCAN00027732 No changes
 *  2.07.00   2008-07-07  visoh   ESCAN00027720 No changes
 *                                ESCAN00027899 No changes
 *                                ESCAN00028004 No changes
 *  2.07.01   2008-08-08  visoh   ESCAN00029050 No changes
 *                                ESCAN00029133 No changes
 *  2.08.00   2008-08-08  visoh   ESCAN00028596 Extension for usage with ComM 2.1
 *                                ESCAN00029046 No changes
 *  2.08.01   2008-09-17  visoh   ESCAN00030021 No changes
 *  2.08.02   2008-09-18  visoh   ESCAN00030093 No changes
 *                                ESCAN00030107 No changes
 *  2.09.00   2008-09-23  visoh   ESCAN00030006 No changes
 *                                ESCAN00030120 No changes
 *                                ESCAN00030707 No changes
 *                                ESCAN00030724 No changes
 *  2.09.01   2008-09-24  visoh   ESCAN00031071 No changes
 *  2.10.00   2008-11-25  visoh   ESCAN00031593 No changes
 *                                ESCAN00031961 Changed Bit Order for Coordinator Extension
 *                                ESCAN00032241 No changes
 *                                ESCAN00032242 No changes
 *                                ESCAN00032243 No changes
 *  2.10.01   2009-03-10  visoh   ESCAN00032478 No changes
 *                                ESCAN00033744 No changes
 *                                ESCAN00034048 No changes
 *                                ESCAN00034422 No changes
 *  2.10.02   2009-05-07  visoh   ESCAN00034830 No changes
 *  2.10.03   2009-06-22  visoh   ESCAN00034255 Corrected state name
 *                                ESCAN00035907 Added additional Mask for Extended Coordinator Synchronization Support
 *  2.11.00   2009-07-23  visoh   ESCAN00034949 No changes in this file
 *                                ESCAN00036116 No changes in this file
 *                                ESCAN00036310 No changes in this file
 *                                ESCAN00036561 No changes in this file
 *                                ESCAN00036562 No changes in this file
 *                                ESCAN00036609 No changes in this file
 *  2.11.01   2009-08-27  visoh   ESCAN00037414 No changes in this file
 *  2.12.00   2009-11-13  visoh   ESCAN00039161 No changes in this file
 *  2.13.00   2010-06-16  visoh   ESCAN00043405 No changes in this file
 *                                ESCAN00043406 No changes in this file
 *                                ESCAN00043439 No changes in this file
 *                                ESCAN00043541 No changes in this file
 *  2.14.00   2010-06-30  visoh   ESCAN00043702 No changes in this file
 *                                ESCAN00043723 No changes in this file
 *                                ESCAN00043725 No changes in this file
 *                                ESCAN00043708 No changes in this file
 *                                ESCAN00044061 No changes in this file
 *                                ESCAN00044134 No changes in this file
 *  2.15.00   2010-07-27  visoh   ESCAN00043781 No changes in this file
 *  2.16.00   2010-08-11  visoh   ESCAN00043776 No changes in this file
 *                                ESCAN00043778 No changes in this file
 *                                ESCAN00043792 No changes in this file
 *                                ESCAN00044593 Adapted Nm_ReturnType
 *  2.17.00   2010-09-30  visoh   ESCAN00045723 No changes in this file
 *                                ESCAN00045745 No changes in this file
 *                                ESCAN00046522 Support Fiat Class B NM (MSR)
 *                                ESCAN00046271 No changes in this file
 *                                ESCAN00046777 No changes in this file
 *                                ESCAN00047251 No changes in this file
 *                                ESCAN00047596 No changes in this file
 *                                ESCAN00048718 No changes in this file
 *                                ESCAN00048796 No changes in this file
 *  2.17.01   2011-05-03  vismdr  ESCAN00049359 No changes in this file
 *  2.18.00   2011-06-01  vismdr  ESCAN00048490 No changes in this file
 *                                ESCAN00050087 No changes in this file
 *                                ESCAN00051368 No changes in this file
 *                                ESCAN00051656 No changes in this file
 *                                ESCAN00051914 No changes in this file
 *                                ESCAN00052253 No changes in this file
 *  2.19.00   2011-12-01  vismdr  ESCAN00052258 No changes in this file
 *                                ESCAN00053241 No changes in this file
 *                                ESCAN00053242 No changes in this file
 *                                ESCAN00055736 Adapted availability of NM_ENABLE_COORD_SYNC_SUPPORT
 *  2.19.01   2012-02-13  vismdr  ESCAN00055255 No changes in this file
 *                                ESCAN00056545 Removed dependency of NM_ENABLE_COORD_SYNC_SUPPORT for other modules
 *                                ESCAN00057429 No changes in this file
 *  2.20.00   2012-06-12  vismdr  ESCAN00059354 No changes in this file
 *  2.21.00   2012-08-28  vismdr  ESCAN00057459 No changes in this file
 *                                ESCAN00061077 No changes in this file
 *  2.22.00   2012-11-21  vismdr  ESCAN00062789 No changes in this file
 *  2.23.00   2013-02-07  vismdr  ESCAN00064216 No changes in this file
 *                                ESCAN00064982 No changes in this file
 *                                ESCAN00065144 No changes in this file
 *  2.24.00   2013-04-09  vismdr  ESCAN00065186 No changes in this file
 *                                ESCAN00066111 No changes in this file
 *  2.25.00   2013-08-09  vismdr  ESCAN00069032 No changes in this file
 *                                ESCAN00069710 Added state 'BusOff'
 *********************************************************************************************************************/

#if !defined (NM_STACK_TYPES_H)
#define NM_STACK_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"                                                                     /* Include standard types */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* AUTOSAR Specification Version Information (BCD coded) */
#define NM_STACKTYPES_MAJOR_VERSION   (0x02u)
#define NM_STACKTYPES_MINOR_VERSION   (0x25u)
#define NM_STACKTYPES_PATCH_VERSION   (0x00u)

#define NM_COORD_BIT_PRIO_POS         (1u)      /* Bit Start Position of the Coordination Priority (0..7) */
#define NM_COORD_BIT_SLEEP            (0x08u)   /* Sleep Bit in the Control Bit Vector */
#define NM_COORD_BIT_PRIO_MASK        (0x06u)   /* Bit Mask for the Coordinator Priority */
#define NM_COORD_BIT_MASK             (0x0Eu)   /* Bit Mask for the Coordination Bits */
#define NM_COORD_BIT_INV_MASK         (0xF1u)   /* Inverted Bit Mask for the Coordination Bits */

/* Return values for NM functions */
#define NM_E_OK                       ((uint8)E_OK)      /* Function call has been successfully accomplished and
                                                            returned */
#define NM_E_NOT_OK                   ((uint8)E_NOT_OK)  /* Function call has been unsuccessfully accomplished and
                                                            returned because of an internal execution error.  */
#define NM_E_NOT_EXECUTED             ((uint8)2u)        /* Function call has been successfully accomplished and
                                                            returned since execution of a service in the current 
                                                            state is not allowed. */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* Return type for NM functions */
typedef uint8 Nm_ReturnType;

/* State of the network management state machine */
typedef enum
{
  NM_STATE_UNINIT                 = 0u,   /* Uninitialized State */
  NM_STATE_BUS_SLEEP              = 1u,   /* Bus-Sleep State */
  NM_STATE_PREPARE_BUS_SLEEP      = 2u,   /* Prepare Bus-Sleep State */
  NM_STATE_READY_SLEEP            = 3u,   /* Ready Sleep State */
  NM_STATE_NORMAL_OPERATION       = 4u,   /* Normal Operation State */
  NM_STATE_REPEAT_MESSAGE         = 5u,   /* Repeat Message State */
  NM_STATE_SYNCHRONIZE            = 6u,   /* Synchronized State */
  NM_STATE_WAIT_CHECK_ACTIVATION  = 7u,   /* Wait Check Activation */
  NM_STATE_WAIT_NETWORK_STARTUP   = 8u,   /* Wait Network Startup */
  NM_STATE_BUS_OFF                = 9u    /* BusOff */
} Nm_StateType;
 
/* Modes of the network management state machine */
typedef enum
{
  NM_MODE_BUS_SLEEP           = 0u,   /* Bus-Sleep Mode */
  NM_MODE_PREPARE_BUS_SLEEP   = 1u,   /* Prepare Bus-Sleep Mode */
  NM_MODE_SYNCHRONIZE         = 2u,   /* Synchronized Mode */
  NM_MODE_NETWORK             = 3u    /* Network Mode */
} Nm_ModeType;


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif  /* NM_STACK_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: NmStack_Types.h
 *********************************************************************************************************************/
