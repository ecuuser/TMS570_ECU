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
 *  Description:  This file defines the layout of Bank7.
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
#include "Std_Types.h"
#include "Device_TMS570LS07.h"
#include "Device_header.h"

/* Start Device Definition */
/*SAFETYMCUSW 79 S MR:19.4 <APPROVED> "Reason - F021_CPU0_BASE_ADDRESS is a symbolic constant"*/
/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
#define DEVICE_BANKCONTROLREGISTER  F021_CPU0_BASE_ADDRESS  /* Control Register Address */

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_START_SEC_CONST_UNSPECIFIED
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

#if ((TI_FEE_GENERATE_DEVICEANDVIRTUALSECTORSTRUC == STD_OFF)&& (TI_FEE_PHYSICALSECTOR_SIZE == 4U))
const Device_FlashType Device_FlashDevice =
{
   "TMS570LS07x",                      	/* Device name */
   0x00000000U,                         /* Device Engineering ID */
   Device_ErrorHandlingEcc,             /* Indicates which type of bit Error handling is on the device */   
   Device_CortexR4,					    /* Indicates the Master core type on the device */	   
   TRUE,                              	/* Indicates if the device supports Flash interrupts for processing Flash */   
   31U,                                 /* Nominal time for one write command operation in uS - This value still needs 
                                           to be characterized */
   300U,                                /* Maximum time for one write command operation in uS - This value still needs 
                                           to be characterized */       
   {                                    /* Array of Banks on the device */
	   {    /* Start of Bank Definition */
			 /*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here."*/
			 /*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
			 DEVICE_BANKCONTROLREGISTER,	   	/* Pointer to the Flash control register for this bank */
			 Fapi_FlashBank7,               	/* Core number for this bank */                
			{                           /* Array of the Sectors within a bank */
					{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector0 is enum."*/
					Fapi_FlashSector0,   /* Sector number */
					0xF0200000U,         /* Starting address of the sector */
					0x00001000U,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0100000U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector1 is enum."*/
					Fapi_FlashSector1,   /* Sector number */
					0xF0201000U,         /* Starting address of the sector */
					0x00001000U,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0100200U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector2 is enum."*/
					Fapi_FlashSector2,   /* Sector number */
					0xF0202000U,         /* Starting address of the sector */
					0x00001000U,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0100400U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector3 is enum."*/
					Fapi_FlashSector3,   /* Sector number */
					0xF0203000U,         /* Starting address of the sector */
					0x00001000U,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0100600U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector4 is enum."*/
					Fapi_FlashSector4,   /* Sector number */
					0xF0204000U,         /* Starting address of the sector */
					0x00001000U,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0100800U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector5 is enum."*/
					Fapi_FlashSector5,   /* Sector number */
					0xF0205000U,         /* Starting address of the sector */
					0x00001000U,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0100A00U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector6 is enum."*/
					Fapi_FlashSector6,   /* Sector number */
					0xF0206000U,         /* Starting address of the sector */
					0x00001000U,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0100C00U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector7 is enum."*/
					Fapi_FlashSector7,   /* Sector number */
					0xF0207000U,         /* Starting address of the sector */
					0x00001000U,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0100E00U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector8 is enum."*/
					Fapi_FlashSector8,   /* Sector number */
					0xF0208000U,         /* Starting address of the sector */
					0x00001000U,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0101000U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector9 is enum."*/
					Fapi_FlashSector9,   /* Sector number */
					0xF0209000U,         /* Starting address of the sector */
					0x00001000U,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0101200U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector10 is enum."*/
					Fapi_FlashSector10,   /* Sector number */
					0xF020A000U,         /* Starting address of the sector */
					0x00001000U,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0101400U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector11 is enum."*/
					Fapi_FlashSector11,   /* Sector number */
					0xF020B000U,         /* Starting address of the sector */
					0x00001000U,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0101600U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector12 is enum."*/
					Fapi_FlashSector12,   /* Sector number */
					0xF020C000U,         /* Starting address of the sector */
					0x00001000U,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0101800U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector13 is enum."*/
					Fapi_FlashSector13,   /* Sector number */
					0xF020D000U,         /* Starting address of the sector */
					0x00001000U,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0101A00U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector14 is enum."*/
					Fapi_FlashSector14,   /* Sector number */
					0xF020E000U,         /* Starting address of the sector */
					0x00001000U,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0101C00U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				},  /* End of Sector Definition */
				{   /* Start of Sector Definition */
					/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  Fapi_FlashSector15 is enum."*/
					Fapi_FlashSector15,   /* Sector number */
					0xF020F000U,         /* Starting address of the sector */
					0x00001000U,         /* Length of the sector */
					100000U,              /* Number of cycles the sector is rated for */
					0xF0101E00U,		 /* Defines the address offset to the Error Handling address */
					0x00000200U			 /* Length of the ECC for a sector */
				}  /* End of Sector Definition */				
			}
	   }  /* End of Bank Definition */
   }   /* End of Bank Array */
};  /* End of Device Definition */
#endif

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_CONST_UNSPECIFIED
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/* End of File */
