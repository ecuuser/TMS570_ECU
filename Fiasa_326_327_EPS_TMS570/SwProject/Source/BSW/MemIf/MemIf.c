/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2007 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  MemIf.h
 *    Component:  If_AsrIfMem
 *       Module:  MemIf
 *    Generator:  -  
 *
 *  Description:  The Memory Abstraction Interface provides uniform access to services of underlying
 *                Memory Hardware abstraction (MemHwA) modules, i.e. EEPROM Abstraction (EA) and
 *                Flash EEPROM Emulation (FEE). The appropriate MemHwA module is selected by a device index.
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Tobias Schmid                 Tsd           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.02.00  -           Tsd     -             first production release
 *  02.00.00  2008-04-09  Tsd     -             update for AUTOSAR Release 3.0
 *  02.00.01  2008-05-13  Tsd     -             Introduced SIP-Check
 *  02.01.00  2008-09-15  Rsu     -             Supporting 2 Fee instances in NvM
 *********************************************************************************************************************/


/*---- Includes ------------------------------------------------------------*/
#include "Std_Types.h"
#include "MemIf.h"
#ifndef V_SUPPRESS_EXTENDED_VERSION_CHECK
  #include "v_ver.h"
#endif

/*---- Callback Routines Declarations of the own module --------------------*/
/*---- Configuration switch ------------------------------------------------*/

/*---- Module switch -------------------------------------------------------*/
/*---- Includes ------------------------------------------------------------*/
/*---- Module Header Includes ----------------------------------------------*/
/*---- Callback Routines Declarations of the own module --------------------*/
/*---- Configuration switch ------------------------------------------------*/
/*---- Include of configuration (private section and const structures) -----*/

/*---- Perform version checking ------------*/
#if      ( (MEMIF_SW_MAJOR_VERSION != (2U)) \
        || (MEMIF_SW_MINOR_VERSION != (1U)) )
  #error "Version numbers of MemIf.c and MemIf.h are inconsistent!"
#endif

#if (     (MEMIF_TYPES_MAJOR_VERSION != (1U)) \
       || (MEMIF_TYPES_MINOR_VERSION != (2U)) )
  #error "Version numbers of MemIf.c and MemIf_Types.h are inconsistent!"
#endif

#if (     (MEMIF_CFG_MAJOR_VERSION != (2U)) \
       || (MEMIF_CFG_MINOR_VERSION != (1U)) )
  #error "Version numbers of MemIf.c and MemIf_Cfg.h are inconsistent!"
#endif


/*---- Identification ------------------------------------------------------*/

/*---- Version -------------------------------------------------------------*/
/*---- DATE and TIME -------------------------------------------------------*/
/*---- Internal Defines ----------------------------------------------------*/
/*---- Internal Module Global Variables ------------------------------------*/
#ifndef V_SUPPRESS_EXTENDED_VERSION_CHECK
  #define MEMIF_START_SEC_CONST_32BIT
  #include "MemMap.h"

  /* The name of this const variable is defined via v_ver.h and depends on 
   * the version of the c file. The value of the const variable is also 
   * defined externally and is used for consistency checks, too. 
   */ 
  CONST( uint32, MEMIF_CONST ) IF_ASRIFMEM_LIB_SYMBOL = IF_ASRIFMEM_LIB_VERSION;
  
  #define MEMIF_STOP_SEC_CONST_32BIT
  #include "MemMap.h"
#endif
/*---- Internal Macros -----------------------------------------------------*/
/*---- Internal Type definitions -------------------------------------------*/
/*---- Internal Structures -------------------------------------------------*/
/*---- Internal Forward Declarations ---------------------------------------*/

/*= Implementation =========================================================*/

#if (STD_ON == MEMIF_CFG_USE_FCT_API) /* implement as functions, not macros */
    #define MEMIF_START_SEC_CODE
    #include "MemMap.h"

    /*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    !   Function name: MemIf_Read
    !
    !-----------------------------------------------------------------------------
    !   Function Description:
    !   Function reads a data block from the EA/FEE
    !
    !-----------------------------------------------------------------------------
    !   Module Global: none
    !
    !   Parameter:     DeviceIndex     Number of device
    !                  BlockNumber     Logical FEE/EA block number
    !                  BlockOffset     start offset within block
    !                  DataBufferPtr   Pointer to destination data buffer in ram
    !                  Length          Number of bytes to read
    !   Returnvalue:   Std_ReturnType
    !+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    FUNC(Std_ReturnType, MEMIF_CODE) MemIf_Read(
                                                uint8 DeviceIndex,
                                               uint16 BlockNumber,
                                               uint16 BlockOffset,
                                    MemIf_DataPtr_pu8 DataBufferPtr,
                                               uint16 Length)
    {
        #if ( STD_ON == MEMIF_CFG_CHK_PARAM_DEV_INDEX)
            if ( DeviceIndex >= MemIf_NumberOfDevices_u8)
            {
                MemIf_Errorhook(MEMIF_SID_READ, MEMIF_E_PARAM_DEVICE);
                return E_NOT_OK;  /* MEMIF024 */
            }
        #endif

        return MemIf_MemHwaApis_at[DeviceIndex].Read(BlockNumber,
                                           BlockOffset,
                                           DataBufferPtr,
                                           Length);
    }

    /*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    !   Function name: MemIf_Write
    !
    !-----------------------------------------------------------------------------
    !   Function Description:
    !   Function writes a data block to the EA/FEE
    !
    !-----------------------------------------------------------------------------
    !   Module Global: none
    !
    !   Parameter:     DeviceIndex     Number of device
    !                  BlockNumber     logical EA/FEE block number (id)
    !                  DataBufferPtr   Pointer to source data buffer in memory
    !   Returnvalue:   Std_ReturnType
    !+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    FUNC(Std_ReturnType, MEMIF_CODE) MemIf_Write(
                                             uint8 DeviceIndex,
                                            uint16 BlockNumber,
                                 MemIf_DataPtr_pu8 DataBufferPtr)
    {
        #if ( STD_ON == MEMIF_CFG_CHK_PARAM_DEV_INDEX)
            if ( DeviceIndex >= MemIf_NumberOfDevices_u8)
            {
                MemIf_Errorhook(MEMIF_SID_WRITE, MEMIF_E_PARAM_DEVICE);
                return E_NOT_OK;  /* MEMIF024 */
            }
        #endif

        return MemIf_MemHwaApis_at[DeviceIndex].Write (BlockNumber, DataBufferPtr);
    }

    /*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    !   Function name: MemIf_InvalidateBlock
    !
    !-----------------------------------------------------------------------------
    !   Function Description:
    !   Function to invalidate a data block via the EA/FEE
    !
    !-----------------------------------------------------------------------------
    !   Module Global: none
    !
    !   Parameter:     DeviceIndex     Number of device
    !                  BlockNumber     logical EA/FEE block number (id)
    !   Returnvalue:   Std_ReturnType
    !+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    FUNC(Std_ReturnType, MEMIF_CODE) MemIf_InvalidateBlock(
                                                    uint8  DeviceIndex,
                                                    uint16 BlockNumber)
    {
        #if ( STD_ON == MEMIF_CFG_CHK_PARAM_DEV_INDEX)
            if ( DeviceIndex >= MemIf_NumberOfDevices_u8)
            {
                MemIf_Errorhook(MEMIF_SID_INVALIDATE, MEMIF_E_PARAM_DEVICE);
                return E_NOT_OK;  /* MEMIF024 */
            }
        #endif

        return MemIf_MemHwaApis_at[DeviceIndex].InvalidateBlock (BlockNumber);
    }

    /*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    !   Function name: MemIf_EraseImmediateBlock
    !
    !-----------------------------------------------------------------------------
    !   Function Description:
    !   Function to (pre-)erase an immediate data block via the EA/FEE
    !
    !-----------------------------------------------------------------------------
    !   Module Global: none
    !
    !   Parameter:     DeviceIndex     Number of device
    !                  BlockNumber     logical EA/FEE block number (id)
    !   Returnvalue:   Std_ReturnType
    !+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    FUNC(Std_ReturnType, MEMIF_CODE) MemIf_EraseImmediateBlock(
                                                    uint8  DeviceIndex,
                                                    uint16 BlockNumber)
    {
        #if ( STD_ON == MEMIF_CFG_CHK_PARAM_DEV_INDEX)
            if ( DeviceIndex >= MemIf_NumberOfDevices_u8)
            {
                MemIf_Errorhook(MEMIF_SID_ERASE, MEMIF_E_PARAM_DEVICE);
                return E_NOT_OK; /* MEMIF024 */
            }
        #endif

        return MemIf_MemHwaApis_at[DeviceIndex].EraseImmediateBlock (BlockNumber);
    }

    /*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    !   Function name: MemIf_Cancel
    !
    !-----------------------------------------------------------------------------
    !   Function Description:
    !   Function cancels a read, write or erase job
    !
    !-----------------------------------------------------------------------------
    !   Module Global: none
    !
    !   Parameter:     DeviceIndex     Number of device
    !   Returnvalue:   Std_ReturnType
    !+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    FUNC(void, MEMIF_CODE) MemIf_Cancel(uint8 DeviceIndex)
    {
        #if ( STD_ON == MEMIF_CFG_CHK_PARAM_DEV_INDEX)
            if (DeviceIndex >= MemIf_NumberOfDevices_u8)
            {
                MemIf_Errorhook(MEMIF_SID_CANCEL, MEMIF_E_PARAM_DEVICE);
                return;
            }
        #endif

        MemIf_MemHwaApis_at[DeviceIndex].Cancel ();
        return;
    }

    /*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    !   Function name: MemIf_GetJobResult
    !
    !-----------------------------------------------------------------------------
    !   Function Description:
    !   Function returns the result of the most recently accepted job.
    !
    !-----------------------------------------------------------------------------
    !   Module Global: none
    !
    !   Parameter:    DeviceIndex     Number of device
    !   Returnvalue:   MemIf_JobResultType
    !+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    FUNC(MemIf_JobResultType, MEMIF_CODE) MemIf_GetJobResult(uint8 DeviceIndex)
    {
        #if ( STD_ON == MEMIF_CFG_CHK_PARAM_DEV_INDEX)
            if ( DeviceIndex >= MemIf_NumberOfDevices_u8)
            {
                MemIf_Errorhook(MEMIF_SID_GET_JOB_RESULT, MEMIF_E_PARAM_DEVICE);
                return MEMIF_JOB_FAILED; /* MEMIF024 */
            }
        #endif

        return MemIf_MemHwaApis_at[DeviceIndex].GetJobResult ();
    }

    #define MEMIF_STOP_SEC_CODE
    #include "MemMap.h"
#endif /* MEMIF_CFG_USE_FCT_API */

#define MEMIF_START_SEC_CODE
#include "MemMap.h"

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: MemIf_SetMode
!
!-----------------------------------------------------------------------------
!   Function Description:
!   Function used to switch between normal and fast device access
!   affects all configured underlying modules.
!
!-----------------------------------------------------------------------------
!   Module Global: none
!
!   Parameter:     Mode            Mode of devices (normal/fast)
!   Returnvalue:   void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(void, MEMIF_CODE) MemIf_SetMode
                        (
                            MemIf_ModeType  Mode
                        )
{
    uint8_least currDevId = MemIf_NumberOfDevices_u8;
    
    do
    {
       MemIf_MemHwaApis_at[--currDevId].SetMode(Mode);
    }
    while(currDevId > 0);
    
    return;
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: MemIf_GetStatus
!
!-----------------------------------------------------------------------------
!   Function Description:
!   Function returns the status of the EA/FEE
!
!-----------------------------------------------------------------------------
!   Module Global: none
!
!   Parameter:     DeviceIndex     Number of device
!                                  MEMIF_BROADCAST_ID => query all devices
!                                  (MemIf035, MemIf036)
!   Returnvalue:   MemIf_StatusType
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(MemIf_StatusType, MEMIF_CODE) MemIf_GetStatus(uint8 DeviceIndex)
{
    #if ( STD_ON == MEMIF_CFG_CHK_PARAM_DEV_INDEX)
        if ((DeviceIndex != MEMIF_BROADCAST_ID)       && 
            (DeviceIndex >= MemIf_NumberOfDevices_u8))
        {
            MemIf_Errorhook(MEMIF_SID_GET_STATUS, MEMIF_E_PARAM_DEVICE);
            return MEMIF_UNINIT; /* MEMIF024 */
        }
    #endif

    if(MEMIF_BROADCAST_ID == DeviceIndex)
    {
        uint8_least currDevice_u8 = MemIf_NumberOfDevices_u8;
        
        /* gather the states of modules:
           one bit for: UNINIT value, BUSY, BUSY_INTERNAL */
        uint8_least currentStatusMask_u8 = 0; 

        do
        {
            currentStatusMask_u8 |= (uint8_least)
                ((uint8_least)1u << (uint8)MemIf_MemHwaApis_at[--currDevice_u8].GetStatus());
        } while(currDevice_u8 > 0);
        
        /* check the bits to determine the status to be returned */
        if(currentStatusMask_u8 & ((uint8_least)1u << MEMIF_UNINIT))
        {
            /* at least one device is not intialized */
            return MEMIF_UNINIT;
        }
        else if(currentStatusMask_u8 & ((uint8_least)1u << MEMIF_BUSY))
        {
            /* at least one device is busy */
            return MEMIF_BUSY;
        }
        else if(currentStatusMask_u8 & ((uint8_least)1u << MEMIF_BUSY_INTERNAL))
        {
            /* at least one device is performing internal operations */
            return MEMIF_BUSY_INTERNAL;
        }
        else
        {
            /* nothing pending */
            return MEMIF_IDLE;
        }
    }
    else
    {
        return MemIf_MemHwaApis_at[DeviceIndex].GetStatus ();
    }
}


#if (STD_ON == MEMIF_VERSION_INFO_API)
    void MemIf_GetVersionInfo(
        P2VAR(Std_VersionInfoType, AUTOMATIC, MEMIF_APPL_DATA) VersionInfoPtr)
    {
        #if (MEMIF_CFG_CHK_PARAM_VINFO == STD_ON)
            if (NULL_PTR != VersionInfoPtr)
            {
                /* pointer is valid, proceed with function */
            }
            else
            {
                MemIf_Errorhook(MEMIF_SID_VERSION_INFO, MEMIF_E_PARAM_VINFO);
                return;
            }
        #endif
        
        VersionInfoPtr->vendorID         = MEMIF_VENDOR_ID;
        VersionInfoPtr->moduleID         = MEMIF_MODULE_ID;
        VersionInfoPtr->instanceID       = 0u; /* MemIf has only one instance --> always zero! */
        VersionInfoPtr->sw_major_version = MEMIF_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = MEMIF_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = MEMIF_SW_PATCH_VERSION;
    }
#endif

#define MEMIF_STOP_SEC_CODE
#include "MemMap.h"

/*---- End of File ---------------------------------------------------------*/
