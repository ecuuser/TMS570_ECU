/*****************************************************************************
| Project Name: CANfbl for Ford GGDS/I3
|    File Name: comdat.h
|
|  Description: Definition of common data structures which are shared between
|               bootloader and application software
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2009 by Vector Informatik GmbH, all rights reserved
|
| Please note, that this file contains example source code used by the
| Flash Bootloader. This code may influence the behaviour of the 
| bootloader in principle. Therefore, great care must be taken to verify
| the correctness of the implementation.
|
| The contents of the originally delivered files are only examples resp. 
| implementation proposals. With regard to the fact that these functions 
| are meant for demonstration purposes only, Vector Informatik 
| liability shall be expressly excluded in cases of ordinary negligence, 
| to the extent admissible by law or statute.
|
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| Ci           Andre Caspari             Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Version   Author  Description
| ----------  --------  ------  ----------------------------------------------
| 2009-12-02  01.00.00  Ci      Initial Version
|****************************************************************************/

#ifndef __COMDAT_H__
#define __COMDAT_H__

/*
   The following typedefs avoid the usage of Vector types (e.g. vuint8) so
   they can be easily re-used in the application software.
 */
typedef struct tBootSwId_tag
{
   unsigned char     NumberOfModules;
   /* char string: take one additional byte into account for the NULL delimiter */
   unsigned char     IdentificationParameterRecord[24 + 1];
} tBootSwId;

typedef struct tBootGenToolVer_tag
{
   unsigned char     GenerationToolSupplier;
   unsigned char     GenerationToolVersionNumber[10];
} tBootGenToolVer;

typedef struct tFblCommonData_tag
{
   /* char string: take one additional byte into account for the NULL delimiter */
   unsigned char     EcuCoreAssemblyNumber[24 + 1];
   unsigned char     EcuDeliveryAssemblyNumber[24 + 1];
   unsigned char     EcuSerialNumber[16 + 1];
   tBootSwId         BootSoftwareIdentification;
   tBootGenToolVer   BootloaderGenToolVersionNumber;
} tFblCommonData;

#if defined( VGEN_ENABLE_CANFBL )
#else
/* Common data access macro for usage in the application software */
# define fblCommonData   (*((V_MEMROM1_FAR tFblCommonData V_MEMROM2_FAR *)GetFblCommonDataPtr()))
#endif

#endif /* __COMDAT_H__ */
