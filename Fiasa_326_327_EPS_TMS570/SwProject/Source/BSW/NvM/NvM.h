/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2010 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  NvM.h
 *    Component:  MemService_AsrNvM
 *       Module:  NvM
 *    Generator:  -
 *
 *  Description:  The NVRAM Manager ensure the data storage and maintenance of NV data. 
 *                The NVRAM Manager shall be able to administrate the NV data of an EEPROM 
 *                and/or a FLASH EEPROM emulation device.
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Christian Kaiser              Ck            Vector Informatik GmbH
 *  Manfred Duschinger            Du            Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  03.00.00  -           Ck      -             initial AUTOSAR 2.0.0 revision
 *  03.00.01  -           Ck      -             fixed behaviour for NVRAM blocks without permanent RAM block 
 *                                              fixed behaviour for NVRAM blocks without permanent RAM block 
 *                                              improved usage of Memory Mapping / Compiler Abstracion
 *                                              maximized link-time configurability (NVRAM blocks)
 *  03.00.02  -           Ck      -             implemented dummy callbacks for EA, to guarantee that the objects
 *                                              can be linked
 *  03.00.03  -           Ck      -             fixed include of OS services in NvM_Cfg.c
 *                                              corrected setting of CHANGED flag after successful reads
 *  03.01.00  -           Ck      -             initial AUTOSAR 2.1 revision
 *  03.01.01  -           Ck      -             internal release -  started fixing issues listed for next release.
 *  03.01.02  -           Ck     ESCAN00021797  Optimized CRC queuing algorithm (runtime)
 *                               ESCAN00021562  Added "wait for MemHwA" before completing NvM_WriteAll
 *                               ESCAN00022622  Fixed usage of CRC library functions
 *                               ESCAN00022889  Completely reworked job queuing, reduced critical section lengths
 *                               ESCAN00022986  Fixed usage of critical sections, paired enter/exit
 *  03.01.03  -           Ck     ESCAN00025422  Fixed inconsistencies between function declarations and definitions
 *  03.02.00  -           Du      -             initial AUTOSAR 3.0 revision
 *                                -             added NvM_SetBlockLockStatus API and handling of locked blocks
 *                               ESCAN00025490  Internal buffers for CRC handling added (Crc is not saved 
 *                                              after RamBlockData)
 *                               ESCAN00026660  Library version check added
 *  03.02.01  -           Ck                    Preparation for ASR3.0 Release.
 *                                              Updated all source according to VI's templates
 *                                              No Changes in code, just comments!
 *  03.02.02  -           Ck     ESCAN00026660  NvM.h does not declare API when included from NvM_Cfg.c.
 *                                              This avoids multiple, incompatible function declarations when
 *                                              using the RTE.
 *                               ESCAN00027283  Fixed definition of NvM_ServiceIdType and its values:
 *                                              It depends on usage of callbacks via RTE.
 *                                              If used, the RTE will define them, otherwise NvM_Types.h does.
 *  03.03.00  -           Du     ESCAN00029722  At requesting a high prio job, when NvM is currently idle, NvM
 *                                              calls MemIf_Cancel before processing the high prio job.
 *                                              NvM resets the internal job processing state machine only, if 
 *                                              there is a currently pending job.
 *                               ESCAN00031568  Incorrect null pointer constant NULL is replaced by NULL_PTR.
 *                               ESCAN00028104  Fixed, that Development error NVM_E_LIST_OVERFLOW occurs together 
 *                                              with NVM_E_BLOCK_PENDING
 *                               ESCAN00028575  Repair of redundant blocks: If NVM detects a defect NV Block, it is 
 *                                              written in preference to a valid NV Block. If both NV blocks are in
 *                                              same state, the write order matches the read order.
 *                               ESCAN00028591  DCM got a possibility to access NV data concurrently with NVM's 
 *                                              applications. Therefore NVRAM Blocks that are aliases of other 
 *                                              NVRAM Blocks are implemented. The aliases are neither read at
 *                                              start-up nor written at shut-down. These blocks have their own,
 *                                              common, Management Area.
 * 03.03.01  -            Ck     ESCAN00032565  Eliminated compiler Warnings.
 * 03.03.02  -            Du     ESCAN00028104  Development error NVM_E_LIST_OVERFLOW occured together with NVM_E_BLOCK_PENDING
 *                               ESCAN00029722  NvM calls MemIf_Cancel whenever it starts processing an immediate write job.
 *                                              It only cancels the "Device" the pending immediate Block will be written to.
 *                        Du     ESCAN00033499  Unused variables deleted
 * 03.03.03  -            Du     ESCAN00032992  Compiler Abstraction to parameter NvState of internal function
 *                                              NvM_IntCreateNvState was added.
 *                               ESCAN00033098  When Crc-Calculation of a DCM Block is queued, only one bit, the bit 
 *                                              of the DCM block is set in queue.    
 *                               ESCAN00032738  NVM calls underlying Cancel service with valid DeviceId parameter now.
 * 03.04.00  -            Du     ESCAN00033075  DataIndex Check in NvM_ReadBlock added.
 *                               -              Implementation of a design issue: State check (NvState) is only 
 *                                              for Blocks of MngmtType Redundant.
 *                               ESCAN00033100  Handling of DataIndex and DCM-Blocks: Job processing generally ignores
 *                                              the DataIndex if the Block Type is NATIVE or REDUNDANT.
 *                               ESCAN00033900  Improve priority handling of DCM Blocks: For DCM-Blocks original 
 *                                              priority shall be kept, but the job of a DCM-Block shall always 
 *                                              be put into "normal prio queue"
 *                               ESCAN00035089  Implemented Callbacks: NvM_JobEndNotification, NvM_JobErrorNotification
 *                               ESCAN00034073  Crc Handling is configurable: Either an internal buffer is used or Crc is
 *                                              stored at the end of RAM Block.
 * 03.04.01  -             Ck    ESCAN00039625  Fixed casts at invocations of Blocks' callbacks
 *                               ESCAN00038509  Conditions to report an error to DEM also depend on Block's Type
 *                               ESCAN00040014  Corrected definition of NvM_QryMemHwaBusy() -> compiler abstraction
 *                               Review Input   No functional/behavioral changes, improved MISRA compliance, readability
 * 3.05.00   -             Ck    ESCAN00031315  Added Invocation of Check Routine in Development Mode from NvM_Init.
 *                               ESCAN00039749  guaranteed that result of CRC32 is always the same
 *                                              (independent of NvmNoOfCrcBytes).
 *                               ESCAN00035134  Added inclusion of generated NvM_PrivateCfg.h  
 *                               ESCAN00041407  WriteBlock processing: Ensure that NvM_MainFunction is left when copying
 *                                              RAM Data to internal Buffer (Blocks with CRC)
 *                               ESCAN00041717,
 *                               ESCAN00041933  Avoid compiler warnings
 *                               ESCAN00034154  Added cancellation of interrupted job's device   
 *                               ESCAN00042136  Corrected initialization of job queue.
 *                               Review         - Added header file version cross checks in NvM.c
 *                                              - Insignificant improvements, basically related to style.
 * 3.05.01                 Ck    ESCAN00044218  NvM_Init - corrected function call to execute ROM Block size checks.
 *                               ESCAN00044082  NvM_QueueRequeueLastJob - declaration encapsulated in pre-processor condition
 * 3.07.00                 Ck    ESCAN00047171  Added Service NvM_KillWriteAll
 *                               ESCAN00038030  Changed access to NvM_BlockDescriptor members
 *                               ESCAN00028600  Changed CRC handling - Object based approach,
 *                                              Generic and pre-compile parts contained in static code; parts specific
 *                                              to a CRC type is part of NvM_Cfg.c -> we are link-time configurable
 *                                              Changed handling of internal buffer (CRC calculation/check)
 *                                              Changed ReadBlock state machine -> read into internal buffer (if CRC)
 * 3.07.01                 Ck    ESCAN00049088  fixed declaration of internal function NvM_CrcGetQueuedBlockId
 *                               ESCAN00049095  avoid compiler warnings, improve MISRA compliance
 *                               Review         unimportant changes (comments)
 *********************************************************************************************************************/

/* Do not modify this file! */


/**********************************************************************************************************************
 * PROTECTION AGAINST MULTIPLE INCLUSION
 *********************************************************************************************************************/
#if (!defined NVM_H_)
#define NVM_H_

/**********************************************************************************************************************
 * VERSION IDENTIFICATION
 *********************************************************************************************************************/
/* ##V_CFG_MANAGEMENT ##CQProject : MemService_AsrNvM CQComponent : Implementation */
#define MEMSERVICE_ASRNVM_VERSION              0x0307u
#define MEMSERVICE_ASRNVM_RELEASE_VERSION      0x01u

#define NVM_VENDOR_ID              (30u)
#define NVM_MODULE_ID              (20u)
#define NVM_INSTANCE_ID            (0u)

#define NVM_AR_MAJOR_VERSION       (2u)
#define NVM_AR_MINOR_VERSION       (2u)
#define NVM_AR_PATCH_VERSION       (0u)

#define NVM_SW_MAJOR_VERSION       (MEMSERVICE_ASRNVM_VERSION >> 8)
#define NVM_SW_MINOR_VERSION       (MEMSERVICE_ASRNVM_VERSION & 0x00FFu)
#define NVM_SW_PATCH_VERSION       MEMSERVICE_ASRNVM_RELEASE_VERSION

/**********************************************************************************************************************
 * API RELEVANT (PUBLIC) SECTION OF CONFIGURATION
 *********************************************************************************************************************/
#include "NvM_Cfg.h"

/**********************************************************************************************************************
 * API DEFINES
 *********************************************************************************************************************/
/* development errors */
#define NVM_E_PARAM_BLOCK_ID            (0x0Au)
#define NVM_E_PARAM_BLOCK_TYPE          (0x0Bu)
#define NVM_E_PARAM_BLOCK_DATA_IDX      (0x0Cu)
#define NVM_E_PARAM_ADDRESS             (0x0Du)

#define NVM_E_PARAM_DATA                (0x0Eu)

#define NVM_E_NOT_INITIALIZED           (0x14u)
#define NVM_E_BLOCK_PENDING             (0x15u)
#define NVM_E_LIST_OVERFLOW             (0x16u)
#define NVM_E_NV_WRITE_PROTECTED        (0x17u)
#define NVM_E_BLOCK_CONFIG              (0x18u)
#define NVM_E_RAM_BLOCK_LENGTH          (0x20u)
#define NVM_E_ROM_BLOCK_LENGTH          (0x21u)
/**********************************************************************************************************************
 * API MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * API TYPE DEFINITIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * API STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * API VARIABLES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * API FUNCTIONS
 *********************************************************************************************************************/
#if (!defined(NVM_SKIP_API_DECLARATIONS))
    #define NVM_SKIP_API_DECLARATIONS (STD_OFF)
#endif

#if (NVM_SKIP_API_DECLARATIONS != STD_ON)

#define NVM_START_SEC_CODE
#include "MemMap.h"

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_Init()
!
!-----------------------------------------------------------------------------
!   Function Description: Service for basic NVRAM manager initialisation:
!                         initializes internal structures and the state
!                         machines.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   none
!   Parameter (Output):  none
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
extern FUNC(void, NVM_PUBLIC_CODE) NvM_Init(void);


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_SetDataIndex(BlockId, DataIndex)
!
!-----------------------------------------------------------------------------
!   Function Description: The request shall set the index to associate a
!   dataset NV/ROM block with its corresponding RAM block.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId, DataIndex
!   Parameter (Output):  none
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (STD_ON == NVM_USE_DATASETS)
extern FUNC(void, NVM_PUBLIC_CODE) NvM_SetDataIndex
    (
        NvM_BlockIdType BlockId,
        uint8 DataIndex
    );
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_GetDataIndex(BlockId)
!
!-----------------------------------------------------------------------------
!   Function Description: The request shall get the current index
!   (association) of a dataset NV/ROM block with its corresponding
!   RAM block.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId
!   Parameter (Output):  DataIndexPtr
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (STD_ON == NVM_USE_DATASETS)
extern FUNC(void, NVM_PUBLIC_CODE) NvM_GetDataIndex
    (
        NvM_BlockIdType BlockId,
        P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) DataIndexPtr
    );
#endif


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_SetBlockProtection(BlockId)
!
!-----------------------------------------------------------------------------
!   Function Description: The request shall set/reset the write protection for
!   the NV block. This shall be done by setting the write lock attribute in the
!   administrative part of the corresponding RAM block. Any further write/erase
!   requests to the NVRAM block shall be rejected synchronously if the NV block
!   write protection is set. The data area of the RAM block shall remain 
!   writeable in case of write protection.
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId, ProtectionEnabled
!   Parameter (Output):  none
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (NVM_API_CONFIG_CLASS_3 == (NVM_API_CONFIG_CLASS & NVM_API_CONFIG_CLASS_3))
extern FUNC(void, NVM_PUBLIC_CODE) NvM_SetBlockProtection
    (
        NvM_BlockIdType BlockId,
        boolean ProtectionEnabled
    );
#endif


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_GetErrorStatus(BlockId)
!
!-----------------------------------------------------------------------------
!   Function Description: The request shall read the block dependent error/
!   status information in the administrative part of a RAM block. The
!   status/error information shall be set by a former or current asynchronous
!   request.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId
!   Parameter (Output):  RequestResultPtr
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
extern FUNC(void, NVM_PUBLIC_CODE) NvM_GetErrorStatus
    (
        NvM_BlockIdType BlockId,
        P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) RequestResultPtr
    );


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_GetVersionInfo(versioninfo)
!
!-----------------------------------------------------------------------------
!   Function Description: The request shall read the version info of the
!   module: Module Id, Vendor Id, Vendor specific version numbers
!-----------------------------------------------------------------------------
!   Parameter (Input):   none
!   Parameter (Output):  versioninfo
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (STD_ON == NVM_VERSION_INFO_API)
extern FUNC(void, NVM_PUBLIC_CODE) NvM_GetVersionInfo
    (
        P2VAR(Std_VersionInfoType, AUTOMATIC, NVM_APPL_DATA) versioninfo
    );
#endif


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_SetRamBlockStatus(BlockId, BlockChanged)
!
!-----------------------------------------------------------------------------
!   Function Description: The request shall set a permanent RAM block to the
!   valid or the invalid state.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId, BlockChanged
!   Parameter (Output):  none
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (STD_ON == NVM_SET_RAM_BLOCK_STATUS_API)
extern FUNC(void, NVM_PUBLIC_CODE) NvM_SetRamBlockStatus
    (
        NvM_BlockIdType BlockId,
        boolean BlockChanged
    );
#endif


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ReadBlock(BlockId, NvM_DstPtr)
!
!-----------------------------------------------------------------------------
!   Function Description: Request to copy the data of the NV block to
!   its corresponding RAM block. If the block to be written is permanent a
!   NULL_PTR shall be given as parameter, otherwise a pointer to the ram
!   block shall be given.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId
!   Parameter (Output):  NvM_DstPtr
!   Returnvalue:         Std_ReturnType
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (NVM_API_CONFIG_CLASS_2 == (NVM_API_CONFIG_CLASS & NVM_API_CONFIG_CLASS_2))
extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_ReadBlock
    (
        NvM_BlockIdType BlockId,
        P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr
    );
#endif


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_WriteBlock(BlockId, NvM_SrcPtr)
!
!-----------------------------------------------------------------------------
!   Function Description: Request to copy the data of the RAM block to its
!   corresponding NV block. If the block to be written is permanent a NULL_PTR
!   shall be given as parameter, otherwise a pointer to the ram block shall be
!   given.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId, NvM_SrcPtr
!   Parameter (Output):  none
!   Returnvalue:         Std_ReturnType
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (NVM_API_CONFIG_CLASS_2 == (NVM_API_CONFIG_CLASS & NVM_API_CONFIG_CLASS_2))
extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_WriteBlock
    (
        NvM_BlockIdType BlockId,
        P2CONST(uint8, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr
    );
#endif


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_RestoreBlockDefaults(BlockId, NvM_DstPtr)
!
!-----------------------------------------------------------------------------
!   Function Description: Request to restore the ROM block default data to
!   its corresponding RAM block. If the ram block is not permanent NvM_DstPtr
!   shall be used as output pointer, otherwise a NULL_PTR shall be handed.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId
!   Parameter (Output):  NvM_DstPtr
!   Returnvalue:         Std_ReturnType
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (NVM_API_CONFIG_CLASS_2 == (NVM_API_CONFIG_CLASS & NVM_API_CONFIG_CLASS_2))

extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_RestoreBlockDefaults
    (
        NvM_BlockIdType BlockId,
        P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr
    );
#endif


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_EraseNvBlock(BlockId)
!
!-----------------------------------------------------------------------------
!   Function Description: Request to erase a NV block. The content of the RAM
!   block shall remain unmodified.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId
!   Parameter (Output):  none
!   Returnvalue:         Std_ReturnType
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (NVM_API_CONFIG_CLASS_3 == (NVM_API_CONFIG_CLASS & NVM_API_CONFIG_CLASS_3))
extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_EraseNvBlock
    (
        NvM_BlockIdType BlockId
    );
#endif


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_InvalidateNvBlock(BlockId)
!
!-----------------------------------------------------------------------------
!   Function Description: Request to invalidate a NV block. The RAM block shall
!   remain unmodified.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId
!   Parameter (Output):  none
!   Returnvalue:         Std_ReturnType
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (NVM_API_CONFIG_CLASS_3 == (NVM_API_CONFIG_CLASS & NVM_API_CONFIG_CLASS_3))
extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_InvalidateNvBlock
    (
        NvM_BlockIdType BlockId
    );
#endif


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ReadAll()
!
!-----------------------------------------------------------------------------
!   Function Description: Request to read the data of all configured RAM
!   blocks from their corresponding NV blocks.
!   Only the data of valid NV blocks is read.
!-----------------------------------------------------------------------------
!   Parameter (Input):   none
!   Parameter (Output):  none
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
extern FUNC(void, NVM_PUBLIC_CODE) NvM_ReadAll(void);


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_WriteAll()
!
!-----------------------------------------------------------------------------
!   Function Description: Request to copy the data of all configured RAM
!   blocks to their corresponding NV blocks.
!   Only the data of valid RAM blocks shall be written.
!-----------------------------------------------------------------------------
!   Parameter (Input):   none
!   Parameter (Output):  none
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
extern FUNC(void, NVM_PUBLIC_CODE) NvM_WriteAll(void);


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_CancelWriteAll()
!
!-----------------------------------------------------------------------------
!   Function Description: Request to cancel a pending WriteAll request.
!-----------------------------------------------------------------------------
!   Parameter (Input):   none
!   Parameter (Output):  none
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
extern FUNC(void, NVM_PUBLIC_CODE) NvM_CancelWriteAll(void);

#if (NVM_KILL_WRITEALL_API == STD_ON)
    /*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    !   Function name: NvM_KillWriteAll()
    !
    !-----------------------------------------------------------------------------
    !   Function Description: Request to kill a pending WriteAll request, i.e.
    !                         To cancel it destructively
    !                         (in contrast to NvM_Cancelwriteall)
    !                         Shall only called by EcuM (or comparable SW)
    !-----------------------------------------------------------------------------
    !   Parameter (Input):   none
    !   Parameter (Output):  none
    !   Returnvalue:         void
    !+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    extern void NvM_KillWriteAll(void);
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_MainFunction
!
!-----------------------------------------------------------------------------
!   Function Description: This  function shall perform the processing of the
!   NVRAM Manager jobs. Therefore it has to be called cyclically.
!-----------------------------------------------------------------------------
!   Module Global: none
!   Parameter:     none
!   Returnvalue:   void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
extern FUNC(void, NVM_PUBLIC_CODE) NvM_MainFunction(void);


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_SetBlockLockStatus(BlockId, Locked)
!
!-----------------------------------------------------------------------------
!   Function Description: The request shall set/reset the lock status for
!   the NV block. This shall be done by setting the lock status attribute in the
!   administrative part of the corresponding RAM block. 
!   The NV contents associated to the NVRAM block identified by BlockId, will not
!   be modi-fied by any request. The Block shall be skipped during NvM_WriteAll. 
!   Other write/erase requests shall be rejected. At processing NvM_ReadAll a
!   locked block shall be loaded from NV memory.write protection.
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId, Locked
!   Parameter (Output):  none
!   Returnvalue:         Std_ReturnType
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_SetBlockLockStatus
    (
        NvM_BlockIdType BlockId,
        boolean Locked
    );

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (NVM_SKIP_API_DECLARATIONS != STD_ON) */

#endif
/* ---- End of File --------------------------------------------------------- */
