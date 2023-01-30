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
 *         File:  fee.h
 *      Project:  Tms570_FEEDriver
 *       Module:  FEE Driver
 *    Generator:  None
 *
 *  Description:  This file implements the FEE Api.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  Vishwanath Reddy
 *---------------------------------------------------------------------------------------------------------------------
 * Revision History
 *---------------------------------------------------------------------------------------------------------------------
 * Version        Date         Author               Change ID        Description
 *---------------------------------------------------------------------------------------------------------------------
 * 00.01.00       07Sept2012    Vishwanath Reddy     0000000000000    Initial Version
 * 00.01.01       01Oct2012	    Vishwanath Reddy     0000000000000    Review changes
 * 00.01.02       30Nov2012     Vishwanath Reddy     SDOCM00097786    Misra Fixes, Memory segmentation changes. 
 * 00.01.03       14Jan2013     Vishwanath Reddy     SDOCM00098510    Changes as requested by Vector.
 * 00.01.04		  12Feb2013	  	Vishwanath Reddy     SDOCM00099152    Integration issues fix. 
 * 00.01.05		  04Mar2013	  	Vishwanath Reddy     SDOCM00099152    Added Deleting a block feature, bug fixes. 
 * 00.01.08		  05Apr2013	    Vishwanath Reddy     SDOCM00099152    Added feature : CRC check for unconfigured  blocks,
																	  Main function modified to complete writes as fast 
																	  as possible, Added Non polling mode support. 
* 00.01.09		  19Apr2013	  	Vishwanath Reddy     SDOCM00099152    Warning removal, Added feature comparision of data
																	  during write.	
* 01.10.00		  21Apr2013	  	Vishwanath Reddy     SDOCM00104635    Corrected version information.
                                                                      Changes for supporting more than two VS.
* 01.20.00		  21Apr2013	  	Vishwanath Reddy     SDOCM00000000    Corrected version information.
* 01.20.01		  12Sep2014	  	Vishwanath Reddy     SDOCM00000000    Updated version information for SDOCM00112930.
* 01.21.00		  15Oct2014     Vishwanath Reddy     SDOCM00113379    RAM Optimization changes.  Version Info Updated.
* 01.22.00		  26Dec2014     Vishwanath Reddy     SDOCM00114423    Changes for unification of Champion/Archer.
* 01.23.00		  12Oct2015     Vishwanath Reddy     SDOCM00119455    Updated version information for SDOCM00119455.
*                                                                     Bugfix for block lost issue.
* 01.23.01		  17Nov2015     Vishwanath Reddy     SDOCM00120161    Updated version history.
* 01.23.02		  10Mar2016     Vishwanath Reddy     SDOCM00121622    Updated version history.
*                                                                     Add a call of TI_FeeInternal_PollFlashStatus()
*                                                                     before reading data from FEE bank in
*                                                                     TI_FeeInternal_UpdateBlockOffsetArray(),
*                                                                     TI_Fee_WriteAsync(),TI_Fee_WriteSync(),
*                                                                     TI_Fee_ReadSync(), TI_Fee_Read()   
 *********************************************************************************************************************/


#ifndef FEE_H
#define FEE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "ti_fee.h"
#include "Fee_Cfg.h"


/**********************************************************************************************************************
 * Fee Published Information
 *********************************************************************************************************************/
#define FEE_VENDOR_ID          ((uint16)44U)
#define FEE_MODULE_ID          ((uint16)21U)
#define FEE_INSTANCE_ID        ((uint8) 0x00U)

#define FEE_AR_MAJOR_VERSION    0x03U
#define FEE_AR_MINOR_VERSION    0x01U
#define FEE_AR_PATCH_VERSION    0x00U
#define FEE_SW_MAJOR_VERSION       1U
#define FEE_SW_MINOR_VERSION      23U
#define FEE_SW_PATCH_VERSION       2U
#define FEE_VENDOR_API_INFIX

#define FEE_VIRTUAL_SECTOR_VERSION  1U

/* DET error defines */
#define FEE_E_UNINIT			((uint8)0x01U)
#define FEE_E_INVALID_BLOCK_NO	((uint8)0x02U)
#define FEE_E_INVALID_BLOCK_OFS	((uint8)0x03U)
#define	FEE_E_INVALID_DATA_PTR	((uint8)0x04U)
#define FEE_E_INVALID_BLOCK_LEN	((uint8)0x05U)
#define	FEE_E_BUSY				((uint8)0x06U)
#define	FEE_E_BUSY_INTERNAL		((uint8)0x07U)
#define	FEE_E_INVALID_CANCEL	((uint8)0x08U)	

/* These are the service IDs of the functions in the ASR SWS specification */
#define FEE_SID_INIT					((uint8)0x00U)
#define FEE_SID_SETMODE					((uint8)0x01U)
#define FEE_SID_READ					((uint8)0x02U)
#define FEE_SID_WRITE					((uint8)0x03U)
#define FEE_SID_CANCEL					((uint8)0x04U)
#define FEE_SID_GETSTATUS				((uint8)0x05U)
#define FEE_SID_GETJOBRESULT			((uint8)0x06U)
#define FEE_SID_INVALIDATEBLOCK			((uint8)0x07U)
#define FEE_SID_GETVERSIONINFO			((uint8)0x08U)
#define FEE_SID_ERASEIMMEDIATEBLOCK		((uint8)0x09U)
#define FEE_SID_JOBENDNOTIFICATION		((uint8)0x10U)
#define FEE_SID_JOBERRORNOTIFICATION	((uint8)0x11U)
#define FEE_SID_MAINFUNCTION			((uint8)0x12U)



/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
 
typedef void Fee_CallbackType(void);



/* Structure used to contain General device options */
typedef struct
{
   boolean FeeDevErrorDetect;                        /* Indicates if Development Error Detection is enabled */
                                                     /* Default: STD_OFF */
   uint32  FeeIndex;                                 /* Instance ID of this module. Should always be 0 */
                                                     /* Fixed Value: 0 */
   Fee_CallbackType * FeeNvmJobEndNotification;       /* Mapping to upper level job end notification */
                                                     /* Default: generic Nvm definition */
   Fee_CallbackType * FeeNvmJobErrorNotification;     /* Mapping to upper level job error notification */
                                                     /* Default: generic Nvm definition */
   boolean FeePollingMode;                           /* Indicates if polling mode is enabled */
                                                     /* Default: STD_OFF */
   boolean FeeVersionInfoApi;                        /* Indicates if the user can use the function Fee_GetVersionInfo() */
                                                     /* Default: STD_OFF */   
   uint16  FeeVirtualPageSize;                       /* Defines the virtual page size.  Our implementation is currently a static 8 byte Page Size */
                                                     /* Fixed value: 8 */      
} Fee_GeneralConfigType;

/* Structure used to contain Published Information */
typedef struct
{
   uint8   FeeBlockOverhead;                         /* Block overhead in bytes */
                                                     /* Calc: (Chunks==True?16:0) + 8 */
   float32   FeeMaximumBlockingTime;                 /* Maximum Blocking Time in uS */
                                                     /* Calc: Device max write time + 50us */
                                                     /* Default: 600us */
                                                     /* Min: 50us; Max: 2ms */
   uint8   FeePageOverhead;                          /* Page overhead in bytes - for our methods, there is none */
                                                     /* Fixed Value: 0 */
   uint8   FeeVirtualSectorOverhead;                 /* Virtual Sector overhead in bytes */
                                                     /* Fixed Value: 16 */
} Fee_PublishedInformationType;


/**********************************************************************************************************************
 * EXTERN Declarations
 *********************************************************************************************************************/
/*  Fee Global Variables */
extern const Fee_PublishedInformationType Fee_PublishedInformation;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
extern void Fee_Cancel(void);
extern Std_ReturnType Fee_EraseImmediateBlock(uint16 BlockNumber);
extern MemIf_JobResultType Fee_GetJobResult(void);
extern MemIf_StatusType Fee_GetStatus(void);
extern void Fee_GetVersionInfo(Std_VersionInfoType* VersionInfoPtr);
extern void Fee_Init(void);
extern Std_ReturnType Fee_InvalidateBlock(uint16 BlockNumber);
extern Std_ReturnType Fee_Read(uint16 BlockNumber,
                               uint16 BlockOffset,
                               uint8* DataBufferPtr,
                               uint16 Length);
extern void Fee_SetMode(MemIf_ModeType Mode);
extern Std_ReturnType Fee_Write(uint16 BlockNumber,
                                uint8* DataBufferPtr);

/*  BSW Functions */
extern void Fee_MainFunction(void);

/**********************************************************************************************************************
 *  INTERNAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
static void Fee_InternalUpdateGlobalStructure(void);
#if(FEE_NUMBER_OF_EEPS == 2U)
static MemIf_StatusType Fee_InternalGetStatus(void);
#endif

#endif /* FEE_H */
/**********************************************************************************************************************
 *  END OF FILE: fee.h
 *********************************************************************************************************************/
