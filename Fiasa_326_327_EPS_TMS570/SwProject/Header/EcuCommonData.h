/***********************************************************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief         Definition of common data structures which are shared between
 *                 bootloader and application software
 *
 *  --------------------------------------------------------------------------------------------------------------------
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \par Copyright
 *  \verbatim
 *  Copyright (c) 2013 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *
 *  \par Note
 *  \verbatim
 *  Please note, that this file contains a collection of callback functions to be used with the Flash Bootloader. 
 *  These functions may influence the behaviour of the bootloader in principle. 
 *  Therefore, great care must be taken to verify the correctness of the implementation.
 * 
 *  The contents of the originally delivered files are only examples resp. implementation proposals. 
 *  With regard to the fact that these functions are meant for demonstration purposes only, Vector Informatik´s 
 *  liability shall be expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute. 
 *  \endverbatim  
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  --------------------------------------------------------------------------------------------------------------------
 *  Armin Happel                  Hp            Vector Informatik GmbH
 *  Christian Baeuerle            CB            Vector Informatik GmbH
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  04.00.00   2013-02-22  Hp/CB                    Initial Version
 **********************************************************************************************************************/

#ifndef __COMMON_DATA_H__
#define __COMMON_DATA_H__

/***********************************************************************************************************************
 *   VERSION
 **********************************************************************************************************************/

#define FBL_ECU_COMMON_DATA_FIAT_VERSION           0x0400u
#define FBL_ECU_COMMON_DATA_FIAT_RELEASE_VERSION   0x00u

/***********************************************************************************************************************
 *  TYPEDEFS
 **********************************************************************************************************************/

/*
   The following typedefs avoid the usage of Vector types (e.g. vuint8) so
   they can be easily re-used in the application software.
 */

typedef unsigned char tFblEcuSerialNumber[16];
typedef unsigned char tFblVinOriginal[16];
typedef unsigned char tFblVehicleManufEcuHwNumber[11];
typedef unsigned char tFblSuppManEcuHwVersionNumber[1];
typedef unsigned char tFblBootSoftwareVersionInformation[13];
typedef unsigned char tFblStandardBootloaderSoftwareInformation[8];
typedef unsigned char tFblHardwareSupplierId[2];

typedef struct tagFblCommonData
{
   tFblEcuSerialNumber                       EcuSerialNumber;
   tFblVinOriginal                           VinOriginal;
   tFblVehicleManufEcuHwNumber               VehicleManufEcuHwNumber;
   tFblSuppManEcuHwVersionNumber             SuppManEcuHwVersionNumber;
   tFblBootSoftwareVersionInformation        BootSoftwareVersionInformation;
   tFblHardwareSupplierId                    HwSupplierId;
   
   tFblStandardBootloaderSoftwareInformation StandardBootloaderSoftwareInformation;
} tFblCommonData;

/***********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

#if defined( VGEN_ENABLE_CANFBL )
//#  define FBLCOMMONDATA_START_SEC_CONST_EXPORT
//#  include "memmap.h"
/* Process data shared between application and Bootloader */
V_MEMROM0 extern V_MEMROM1_FAR tFblCommonData V_MEMROM2_FAR fblCommonData;
//#  define FBLCOMMONDATA_STOP_SEC_CONST_EXPORT
//#  include "memmap.h"
#else
/* Common data access macro for usage in the application software */
# define fblCommonData   (*((V_MEMROM1_FAR tFblCommonData V_MEMROM2_FAR *)GetFblCommonDataPtr()))
#endif

#endif /* __COMMON_DATA_H__ */

/***********************************************************************************************************************
 *  END OF FILE: ECUCOMMONDATA.H
 **********************************************************************************************************************/
