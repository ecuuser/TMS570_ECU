/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2011 by Vector Informatik GmbH.                                                  All rights reserved.
 * 
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Dio.c
 *    Component:  DrvDio_Tms570Tigio01Asr
 *       Module:  Dio
 *    Generator:  -
 *
 *   Description:  This is the header file of MICROSAR CAL module Dio. This DIO Driver provides services for 
 *                reading and writing to/from
 *                        -   DIO Channels (Pins)
 *                        -   DIO Ports
 *                        -   DIO Channel Groups
 * 
 *                This module works on pins and ports which are configured by the PORT driver for this purpose. 
 *                For this reason there is no configuration and initialization of this port structure in the DIO 
 *                Driver.
 *  
 *********************************************************************************************************************/

/* module specific MISRA deviations:

   MD_DIO_11.3:
     Reason: To reduce the ROM consumption the target address was coded into a numeric parameter.
             To get the address as address a numeric to pointer cast has to be done.
     Risk: Impact on portability and readability. 
     Prevention: There are no requirements on portability to a driver. The cast is done with
                 a meaningful named macro.

   MD_DIO_11.3_2:
     Reason: The OS functions for SFR register access use integer parameter as address.
             The DIO register access mechanism bases on a memory overlay of a struct.
             This makes a cast form address to integer necessary. 
     Risk: Impact on portability and readability. 
     Prevention: There are no requirements on portability to a driver. 

   MD_DIO_11.4:
     Reason: The module uses casts to more generic pointers to get an generic interface for
             delegate functions. 
     Risk: Impact on safety, portability and readability. 
     Prevention: Pay special attention that the pointers are used in the intended way during code 
                 inspection.

    MD_DIO_16.7:
     Reason: The module used not constant pointers for input reference parameter, because
             a generic method of delegation of services was used that only allows one specific
             service interface. the const keyword is not implemented to keep this mechanism 
             flexible.
     Risk: The object the parameter is pointing to can be overwritten within the service.
     Prevention: Check that object the parameter is pointing to is not written in the services
                 at code inspection.

   MD_DIO_3206: 
     Reason: The module has some unused function parameter parameter, because
             a generic method of delegation of services was used that only allows one specific
             service interface.
     Risk:   The presence of redundant variables adds to the complexity of a program. 
     Prevention: The services are that short that the complexity impact is really small.  

*/


#define DIO_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Dio.h"


/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if (  (DIO_SW_MAJOR_VERSION != (0x01u)) \
    || (DIO_SW_MINOR_VERSION != (0x01u)) )
  #error "Vendor specific version numbers of Dio.c and Dio.h are inconsistent"
#endif

#if (  (DIO_CFG_MAJOR_VERSION != (2u)) \
    || (DIO_CFG_MINOR_VERSION != (1u)) )
  #error "Version numbers of Dio.c and Dio_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
#define DIO_REGISTER_BASE       (0xFFF70000u)

/**********************************************************************************************************************
 *    explanation of symbolic channel and port names:
 **********************************************************************************************************************
 * 
 * the symbolic channel name contains a value with all necessary attributes and addresses needed to
 * access a port:
 * 
 *      #define SomePort   (0x141C3FFFu)
 * 
 * 
 * This value means (binary value):
 * --------------------------------
 * 
 *      0b    0001 0100 0001 1010   0011 1111 1111 1111
 *            \\\\ //// \\\\ /|||   ||\\ \\\\ //// ////
 *             ---+---   ---+ |||   || ------+--------
 *                |         | |||   ||       |\     /
 *                |         | |||   ||       | --+--
 *                |         | |||   ||       |   |
 *                |         | |||   ||       |   + if register access is done via OS functions the whole offset is
 *                |         | |||   ||       |     replaced by a index of a port address array were also the index 
 *                |         | |||   ||       |     to memory area is stored (only channel ids) 
 *                |         | |||   ||       |
 *                |         | |||   ||       +-> port offset to the base address 0xFFF7 0000. KEEP IN MIND, that the
 *                |         | |||   ||              least two significant bits of the address are removed, since the 
 *                |         | |||   ||              registers are 32bit-aligned (and the least two bits default to 
 *                |         | |||   ||              zero).
 *                |         | |||   ||
 *                |         | |||   ||              The layout (mask) of the whole port offset address (including 
 *                |         | |||   ||              the extension in bit 17) in the port/channel id looks like this:
 *                |         | |||   ||
 *                |         | |||   ||                  0x0002 3FFF
 *                |         | |||   ||
 *                |         | |||   ||              The real port offset can be retrieved by shifting this by two:
 *                |         | |||   ||
 *                |         | |||   ||                  0x0002 3FFF << 2          =   0x0008 FFFC
 *                |         | |||   ||
 *                |         | |||   ||              The absolute port address is calculating by OR'ing this with the 
 *                |         | |||   ||              base address:
 *                |         | |||   ||
 *                |         | |||   ||                  0x0008 FFFC | 0xFFF7 0000 =   0xFFFF FFFC
 *                |         | |||   ||
 *                |         | |||   ++-> reserved for future use
 *                |         | |||
 *                |         | ||+-> indicates that the port is a CAN port
 *                |         | ||
 *                |         | |+-> indicates that the port's registers are allocated in the system module register 
 *                |         | |       space. This bit is used as extension of the port offset changing the base address
 *                |         | |       from 0xFFF7 0000 to 0xFFFF 0000
 *                |         | |
 *                |         | +-> indicates that this is an ADC port (input and output registers are in reversed order)
 *                |         |
 *                |         +-> offset of the pin in the port (only in channel ids, port ids do not use these bits)
 *                |
 *                +-> channel number for checking the port against the generated tables
 *                    for port ids this is the index of the array of the assigned memory area
 * 
 * 
 **********************************************************************************************************************/

/* mask to get the offset address of a port (relative to the register base address -> DIO_REGISTER_BASE) */
/* right shifted by 2 */
#define DIO_MASK_PORT_OFFSET_SH       (0x00023FFFu)
/* not shifted */
#define DIO_MASK_PORT_OFFSET_NSH      (0x0008FFFCu)

/* mask to get the index of a port address in port address table */
#define DIO_MASK_PORT_IDX             (0x0000FFFFu)

/* mask to get the pin offset in a ChannelId */
#define DIO_MASK_PIN_OFFSET       (0x00F80000u)

/* used to identify whether a port is a CAN port or a regular GIO port */
#define DIO_SHIFT_PORT_CLASS      (16u)

/* used to identify whether a port is a ADC port or a regular GIO port */
#define DIO_SHIFT_INPUT_IDX       (18u)

/* used to identify the pin offset in a ChannelId */
#define DIO_SHIFT_PIN_OFFSET     (19u)

/* shift value to get to the index against which to check in the generated arrays, whether the passed channel or 
 * port ID is valid 
 */
#define DIO_SHIFT_CHECKIDX      (24u)

/* shift value to get the memory area index from port table */
#define DIO_SHIFT_MEM_AREA_IDX  (24u)

/* mask that only contains pin for the output level of the CAN IO register */
#define DIO_CAN_IO_LEVEL_MASK     (0x2u)

/* mask that only excludes the pin for the output level of the CAN IO register */
#define DIO_INV_CAN_IO_LEVEL_MASK     (0xfffffffdu)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/
#define DIO_GET_PORT_ADDRESS(DIO_ID)    ( DIO_REGISTER_BASE | (((DIO_ID) & (uint32)DIO_MASK_PORT_OFFSET_SH) << 2u) ) /* PRQA S 3453 *//* MD_MSR_19.7 */

#if (STD_ON == DIO_SPECIAL_REGISTER_ACCESS_ENABLED)
    /* retrieves the absolute port address from a port or channel ID as uint32 value */ 
    #define DIO_GET_CHL_PORT_ADDRESS(DIO_ID)    ( DIO_REGISTER_BASE | (Dio_PortAddrTable[((DIO_ID) & (uint32)DIO_MASK_PORT_IDX)] & (uint32)DIO_MASK_PORT_OFFSET_NSH) )  /* PRQA S 3453 *//* MD_MSR_19.7 */
#else
    /* retrieves the absolute port address from a port or channel ID as uint32 value */ 
    #define DIO_GET_CHL_PORT_ADDRESS(DIO_ID)    ( DIO_GET_PORT_ADDRESS(DIO_ID) ) /* PRQA S 3453 *//* MD_MSR_19.7 */
#endif

/* retrieve the mem area from port id which is needed to use os functions for register access */
#define DIO_GET_PORT_MEM_AREA(DIO_ID) (Dio_PortMemoryAreas[((DIO_ID) >> DIO_SHIFT_MEM_AREA_IDX)]) /* PRQA S 3453 *//* MD_MSR_19.7 */

/* retrieve the mem area from channel id which is needed to use os functions for register access */
#define DIO_GET_CHL_MEM_AREA(DIO_ID)  (Dio_PortMemoryAreas[(Dio_PortAddrTable[((DIO_ID) & (uint32)DIO_MASK_PORT_IDX)] >> DIO_SHIFT_MEM_AREA_IDX)]) /* PRQA S 3453 *//* MD_MSR_19.7 */



/* retrieves the port class from a port of channel ID (used to identify a CAN port) */
#define DIO_GET_PORT_CLASS(DIO_ID)      ( ((DIO_ID) >> DIO_SHIFT_PORT_CLASS) & 1u ) /* PRQA S 3453 *//* MD_MSR_19.7 */

/* In AWM I/O ports output and input registers are swapped, but this macro always retrieves the correct idx to the
 * input register, no matter what kind of port it is (this info is encoded in the PortId and ChannelId parameters, 
 * see the design specification for details)
 */
#define DIO_GET_INPUT_IDX(DIO_ID)       ( ((DIO_ID) >> DIO_SHIFT_INPUT_IDX) & 1u ) /* PRQA S 3453 *//* MD_MSR_19.7 */

/* the same mechanism as for DIO_GET_INPUT_IDX(), only for the output register index. */
#define DIO_GET_OUTPUT_IDX(DIO_ID)      ( DIO_GET_INPUT_IDX(DIO_ID) ^ 1u ) /* PRQA S 3453 *//* MD_MSR_19.7 */

/* retrieves the pin offset in the port from a ChannelId */
#define DIO_GET_PIN_OFFSET(CHANNEL_ID)  ( ((CHANNEL_ID) & (uint32)DIO_MASK_PIN_OFFSET) >> DIO_SHIFT_PIN_OFFSET ) /* PRQA S 3453 *//* MD_MSR_19.7 */

/* retrieves the channel or port number used as index to check the validity of a port or channel Id in the 
 * generated arrays
 */
#define DIO_GET_CHECKIDX(DIO_ID)        ( (DIO_ID) >> DIO_SHIFT_CHECKIDX ) /* PRQA S 3453 *//* MD_MSR_19.7 */


/*********************************************************************************************************************
 * Wrapper macros for register access. Used to redirect read/write operations on HW registers to special Os services.* 
 *********************************************************************************************************************/
#ifndef DIO_WRITE_PROTECTED_REGISTER_32BIT
    # define DIO_WRITE_PROTECTED_REGISTER_32BIT(address, value, area)  (osWritePeripheral32((area), (address), (value))) /* PRQA S 3453 *//* MD_MSR_19.7 */
#endif

#ifndef DIO_READ_PROTECTED_REGISTER_32BIT
    # define DIO_READ_PROTECTED_REGISTER_32BIT(address, area)  (osReadPeripheral32((area), (address))) /* PRQA S 3453 *//* MD_MSR_19.7 */
#endif

#ifndef DIO_MODIFY_PROTECTED_REGISTER_32BIT
    # define DIO_MODIFY_PROTECTED_REGISTER_32BIT(address, clearmask, setmask, area) (osModifyPeripheral32((area), (address), (clearmask), (setmask))) /* PRQA S 3453 *//* MD_MSR_19.7 */
#endif

#if (DIO_SPECIAL_REGISTER_ACCESS_ENABLED == STD_ON)
#  if (DIO_SPECIAL_REGISTER_ACCESS_ONLY_FOR_PRIVILEGED_MODE_REGISTERS == STD_ON)
#    define DIO_WRITE_REGISTER_32BIT(address, value, area)                        (*((volatile uint32*)(address)) = (uint32)(value)) /* PRQA S 3453 *//* MD_MSR_19.7 */
#  else
#    define DIO_WRITE_REGISTER_32BIT(address, value, area)                        (DIO_WRITE_PROTECTED_REGISTER_32BIT(address, value, area)) /* PRQA S 3453 *//* MD_MSR_19.7 */
#  endif
#  define DIO_WRITE_REGISTER_32BIT_SUPERVISOR(address, value, area)                 (DIO_WRITE_PROTECTED_REGISTER_32BIT(address, value, area)) /* PRQA S 3453 *//* MD_MSR_19.7 */
#else
#  define DIO_WRITE_REGISTER_32BIT(address, value, area)                            (*((volatile uint32*)(address)) = (uint32)(value)) /* PRQA S 3453 *//* MD_MSR_19.7 */
#  define DIO_WRITE_REGISTER_32BIT_SUPERVISOR(address, value, area)                 (*((volatile uint32*)(address)) = (uint32)(value)) /* PRQA S 3453 *//* MD_MSR_19.7 */
#endif

#if (DIO_SPECIAL_REGISTER_ACCESS_ENABLED == STD_ON)
#  if(DIO_SPECIAL_REGISTER_ACCESS_ONLY_FOR_WRITE == STD_ON)
#    define DIO_READ_REGISTER_32BIT_INIT(address, area)                             (*((volatile uint32*)(address))) /* PRQA S 3453 *//* MD_MSR_19.7 */
#    define DIO_READ_REGISTER_32BIT(address, area)                                  (*((volatile uint32*)(address))) /* PRQA S 3453 *//* MD_MSR_19.7 */
#  else
#    if (DIO_SPECIAL_REGISTER_ACCESS_ONLY_FOR_PRIVILEGED_MODE_REGISTERS == STD_ON)
#      define DIO_READ_REGISTER_32BIT(address, area)                               (*((volatile uint32*)(address))) /* PRQA S 3453 *//* MD_MSR_19.7 */
#    else
#      define DIO_READ_REGISTER_32BIT(address, area)                               (DIO_READ_PROTECTED_REGISTER_32BIT(address, area)) /* PRQA S 3453 *//* MD_MSR_19.7 */
#    endif
#  endif
#  define DIO_READ_REGISTER_32BIT_SUPERVISOR(address, area)                          (DIO_READ_PROTECTED_REGISTER_32BIT(address, area)) /* PRQA S 3453 *//* MD_MSR_19.7 */   
#else
#  define DIO_READ_REGISTER_32BIT(address, area)                                     (*((volatile uint32*)(address))) /* PRQA S 3453 *//* MD_MSR_19.7 */
#  define DIO_READ_REGISTER_32BIT_SUPERVISOR(address, area)                          (*((volatile uint32*)(address))) /* PRQA S 3453 *//* MD_MSR_19.7 */
#endif

#if (DIO_SPECIAL_REGISTER_ACCESS_ENABLED == STD_ON)
#  if (DIO_SPECIAL_REGISTER_ACCESS_ONLY_FOR_PRIVILEGED_MODE_REGISTERS == STD_ON)
#    define DIO_MODIFY_REGISTER_32BIT(address, clearmask, setmask, area)               ((*(volatile uint32*)(address)) = (((*(volatile uint32*)(address)) & ((clearmask))) | (setmask))) /* PRQA S 3453 *//* MD_MSR_19.7 */
#  else
#    define DIO_MODIFY_REGISTER_32BIT(address, clearmask, setmask, area)               (DIO_MODIFY_PROTECTED_REGISTER_32BIT(address, clearmask, setmask, area)) /* PRQA S 3453 *//* MD_MSR_19.7 */
#  endif
#  define DIO_MODIFY_REGISTER_32BIT_SUPERVISOR(address, clearmask, setmask, area)        (DIO_MODIFY_PROTECTED_REGISTER_32BIT(address, clearmask, setmask, area)) /* PRQA S 3453 *//* MD_MSR_19.7 */
#else
#  define DIO_MODIFY_REGISTER_32BIT(address, clearmask, setmask, area)                   ((*(volatile uint32*)(address)) = (((*(volatile uint32*)(address)) & (clearmask)) | (setmask))) /* PRQA S 3453 *//* MD_MSR_19.7 */
#  define DIO_MODIFY_REGISTER_32BIT_SUPERVISOR(address, clearmask, setmask, area)        ((*(volatile uint32*)(address)) = (((*(volatile uint32*)(address)) & (clearmask)) | (setmask))) /* PRQA S 3453 *//* MD_MSR_19.7 */ 
#endif



/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/
typedef struct {
  uint32 DataInOut[2];
  uint32 DataSetClear[2];
} Dio_GioRegisterType;

/* type definition for accessing port registers */
typedef P2VAR(uint32, AUTOMATIC, DIO_VAR) Dio_32BitRefType;

typedef P2VAR(Dio_GioRegisterType, AUTOMATIC, DIO_VAR) Dio_GioRegisterRefType;

typedef P2FUNC(uint32, AUTOMATIC, Dio_ReadChannelType)        (uint32 ChannelId, Dio_32BitRefType PortRef);
typedef P2FUNC(void,   AUTOMATIC, Dio_WriteChannelType)       (uint32 ChannelId, Dio_32BitRefType PortRef, uint32 Level);
typedef P2FUNC(uint32, AUTOMATIC, Dio_ReadPortType)           (uint32 PortId, Dio_32BitRefType PortRef);
typedef P2FUNC(void,   AUTOMATIC, Dio_WritePortType)          (uint32 PortId, Dio_32BitRefType PortRef, uint32 Level);


typedef struct {
  const Dio_ReadChannelType       ReadChannel;
  const Dio_WriteChannelType      WriteChannel;
  const Dio_ReadPortType          ReadPort;
  const Dio_WritePortType         WritePort;
} Dio_PortClassType;

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 *//* MD_MSR_19.1 */

  #if (DIO_CFG_SUPPORT_CAN == STD_ON) && (DIO_CFG_SUPPORT_GIO == STD_ON)
    static FUNC(uint32, DIO_CODE) Dio_GioReadChannel(uint32 ChannelId, Dio_32BitRefType PortRef);
    static FUNC(void,   DIO_CODE) Dio_GioWriteChannel(uint32 ChannelId, Dio_32BitRefType PortRef, uint32 Level);
    static FUNC(uint32, DIO_CODE) Dio_GioReadPort(uint32 PortId, Dio_32BitRefType PortRef);
    static FUNC(void,   DIO_CODE) Dio_GioWritePort(uint32 PortId, Dio_32BitRefType PortRef, uint32 Level);


    static FUNC(uint32, DIO_CODE) Dio_CanReadChannel(uint32 ChannelId, Dio_32BitRefType PortRef);
    static FUNC(void,   DIO_CODE) Dio_CanWriteChannel(uint32 ChannelId, Dio_32BitRefType PortRef, uint32 Level);
    static FUNC(uint32, DIO_CODE) Dio_CanReadPort(uint32 PortId, Dio_32BitRefType PortRef);
    static FUNC(void,   DIO_CODE) Dio_CanWritePort(uint32 PortId, Dio_32BitRefType PortRef, uint32 Level);

  #endif

#define DIO_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 *//* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/
#define DIO_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 *//* MD_MSR_19.1 */

  #if (DIO_CFG_SUPPORT_CAN == STD_ON) && (DIO_CFG_SUPPORT_GIO == STD_ON)
    static CONST(Dio_PortClassType, DIO_CONST) Dio_Port[] = 
          {
            { /* GIO port methods */
              Dio_GioReadChannel, 
              Dio_GioWriteChannel,
              Dio_GioReadPort,
              Dio_GioWritePort
            },
            { /* CAN port methods */
              Dio_CanReadChannel, 
              Dio_CanWriteChannel,
              Dio_CanReadPort, 
              Dio_CanWritePort
            }
          };
  #endif

#define DIO_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 *//* MD_MSR_19.1 */


#define DIO_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 *//* MD_MSR_19.1 */
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Dio_GetVersionInfo
 **********************************************************************************************************************/
/*! \brief      Version Information Service
 * 
 *              This service writes the version information of this module into the data structure referenced by the 
 *              parameter. If this parameter references NULL_PTR, a development error is reported to Det. This service
 *              is only available if the pre-compile configuration parameter DIO_VERSION_INFO_API is enabled.
 * 
 *  \param[out] versioninfo         data structure where the version info shall be written to
 **********************************************************************************************************************/
#if (DIO_VERSION_INFO_API == STD_ON)
  FUNC(void, DIO_CODE)  Dio_GetVersionInfo
  (
    P2VAR(Std_VersionInfoType, AUTOMATIC, DIO_APPL_DATA) VersionInfo
  )
  {
    #if (DIO_CFG_CHK_PARAM_VINFO == STD_ON)
      if (NULL_PTR == VersionInfo)
      {
        Dio_ReportDet(DIO_SID_GET_VERSION_INFO, DIO_E_PARAM_VINFO);
        return;
      }
      else
      {
        /* parameter versioninfo is valid */
      }
    #endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
  
    VersionInfo->vendorID         = (uint16) DIO_VENDOR_ID;
    VersionInfo->moduleID         = (uint8)  DIO_MODULE_ID;
    VersionInfo->sw_major_version = (uint8)  DIO_SW_MAJOR_VERSION;
    VersionInfo->sw_minor_version = (uint8)  DIO_SW_MINOR_VERSION;
    VersionInfo->sw_patch_version = (uint8)  DIO_SW_PATCH_VERSION;
    
    /* drivers for external devices have configurable instance IDs, internal drivers default to zero */
    VersionInfo->instanceID       = (uint8) 0u;
    
    return;
  } /* End of Dio_GetVersionInfo() */ /* PRQA S 2006 */ /* MD_MSR_14.1 */
#endif


/**********************************************************************************************************************
 * Dio_ReadChannel
 **********************************************************************************************************************/
/*! \brief      Read out a DIO channel
 * 
 *              This function reads out the value of the referenced DIO channel (port pin).
 * 
 *  \param[in]  ChannelId       ChannelId representing the port pin to read from
 * 
 *  \return     Level of the DIO channel
 * 
 *  \context    The function can be called on interrupt and task level.
 *********************************************************************************************************************/
FUNC(Dio_LevelType, DIO_CODE) Dio_ReadChannel(Dio_ChannelType ChannelId)
{
  Dio_32BitRefType PortRef;

 
  PortRef = (Dio_32BitRefType) DIO_GET_CHL_PORT_ADDRESS(ChannelId); /* PRQA S 0306 *//* MD_DIO_11.3 */

  #if (DIO_CFG_CHK_PARAM_CHANNEL == STD_ON)
    if (Dio_ChannelCheckTable[DIO_GET_CHECKIDX(ChannelId)] == ChannelId)
    {
      /* ChannelId is valid, proceed in service */
    }
    else
    {
      /* ChannelId is NOT valid */
      Dio_ReportDet(DIO_SID_READ_CHANNEL, DIO_E_PARAM_INVALID_CHANNEL_ID);

      return 0u;
    }
  #endif

#if (DIO_CFG_SUPPORT_CAN == STD_ON) && (DIO_CFG_SUPPORT_GIO == STD_ON)
  {
    /* in case both GIO and CAN ports is supported by configuration, the necessary function is selected by
     * the CanPin field in the Channel-parameter. If only one of GIO or CAN ports is supported, the function
     * hierarchy is removed, and the code of the supported port type is included directly into this service.
     */
    uint32 PortClass = DIO_GET_PORT_CLASS(ChannelId);
    
    return (Dio_LevelType) Dio_Port[PortClass].ReadChannel(ChannelId, PortRef);
  }
} /* PRQA S 2006 *//* MD_MSR_14.1 */
#endif

#if (DIO_CFG_SUPPORT_CAN == STD_ON) && (DIO_CFG_SUPPORT_GIO == STD_ON)
  static FUNC(uint32, DIO_CODE) Dio_GioReadChannel(uint32 ChannelId, Dio_32BitRefType PortRef) /* PRQA S 3673 *//* MD_DIO_16.7 */
  {
#endif
#if (DIO_CFG_SUPPORT_GIO == STD_ON)
    {
      uint32 PinValue_u32;
      uint32 PortPin    = DIO_GET_PIN_OFFSET(ChannelId);
      uint32 InSelector = DIO_GET_INPUT_IDX(ChannelId);
      

      /* ADEVT ports have GIODIN and GIODOUT in reversed order, hence the InSelector selects 
       * the correct register for reading
       */
      PinValue_u32 = (( DIO_READ_REGISTER_32BIT((uint32)&(((Dio_GioRegisterRefType) PortRef)->DataInOut[InSelector]), /* PRQA S 0310 *//* MD_DIO_11.4 */ /* PRQA S 0306*//* MD_DIO_11.3_2 */ /* PRQA S 0303 *//* MD_DIO_11.3_2 */
                        DIO_GET_CHL_MEM_AREA(ChannelId) ) >> PortPin ) & 1u ); 

      return  PinValue_u32;
    }
  }
#endif

#if (DIO_CFG_SUPPORT_CAN == STD_ON) && (DIO_CFG_SUPPORT_GIO == STD_ON)
  static FUNC(uint32, DIO_CODE) Dio_CanReadChannel(uint32 ChannelId, Dio_32BitRefType PortRef) /* PRQA S 3673 *//* MD_DIO_16.7 */ /* PRQA S 3206 *//* MD_DIO_3206 */
  {
#endif
#if (DIO_CFG_SUPPORT_CAN == STD_ON)
    

    /* a can port only has one I/O pin, where the data input register is located at bit position 0 */
    return ( DIO_READ_REGISTER_32BIT_SUPERVISOR((uint32)PortRef, /* PRQA S 0306*//* MD_DIO_11.3_2 */ /* PRQA S 0303 *//* MD_DIO_11.3_2 */
                                                DIO_GET_CHL_MEM_AREA(ChannelId)) & 1u);
  }
#endif

/**********************************************************************************************************************
 * Dio_WriteChannel
 **********************************************************************************************************************/
/*! \brief      Write a value to a DIO channel
 * 
 *              This function writes the value to the referenced DIO channel (port pin).
 * 
 *  \param[in]  ChannelId       ChannelId representing the port pin to write to
 *  \param[in]  Level           Level to apply to the channel
 * 
 *  \context    The function can be called on interrupt and task level.
 *********************************************************************************************************************/
FUNC(void, DIO_CODE) Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
  Dio_32BitRefType PortRef;


  PortRef = (Dio_32BitRefType) DIO_GET_CHL_PORT_ADDRESS(ChannelId); /* PRQA S 0306 *//* MD_DIO_11.3 */
  
  #if (DIO_CFG_CHK_PARAM_CHANNEL == STD_ON)
    if (Dio_ChannelCheckTable[DIO_GET_CHECKIDX(ChannelId)] == ChannelId)
    {
      /* ChannelId is valid, proceed in service */
    }
    else
    {
      /* ChannelId is NOT valid */
      Dio_ReportDet(DIO_SID_WRITE_CHANNEL, DIO_E_PARAM_INVALID_CHANNEL_ID);
     

      return;
    }
  #endif

#if (DIO_CFG_SUPPORT_CAN == STD_ON) && (DIO_CFG_SUPPORT_GIO == STD_ON)
  {
    /* in case both GIO and CAN ports is supported by configuration, the necessary function is selected by
     * the CanPin field in the Channel-parameter. If only one of GIO or CAN ports is supported, the function
     * hierarchy is removed, and the code of the supported port type is included directly into this service.
     */
    uint32 PortClass = DIO_GET_PORT_CLASS(ChannelId);
    Dio_Port[PortClass].WriteChannel(ChannelId, PortRef, Level);


    return;
  }
} /* PRQA S 2006 *//* MD_MSR_14.1 */
#endif

#if (DIO_CFG_SUPPORT_CAN == STD_ON) && (DIO_CFG_SUPPORT_GIO == STD_ON)
  static FUNC(void, DIO_CODE) Dio_GioWriteChannel(uint32 ChannelId, Dio_32BitRefType PortRef, uint32 Level) /* PRQA S 3673 *//* MD_DIO_16.7 */ 
  {
#endif
#if (DIO_CFG_SUPPORT_GIO == STD_ON)
    {
      uint32 PortPin    = DIO_GET_PIN_OFFSET(ChannelId);
      
      /* Level ^ 1      -->> SET-Register is located at index 0, CLEAR-Register is located at index 1
       *                -->> STD_HIGH is 1 (1 should be set at index 0 to set the bit)
       *                -->> STD_LOW  is 0 (1 should be set at index 1 to clear the bit)
       */
      DIO_WRITE_REGISTER_32BIT( (uint32)&(((Dio_GioRegisterRefType) PortRef)->DataSetClear[Level ^ 1u]), /* PRQA S 0310 *//* MD_DIO_11.4 */ /* PRQA S 0306*//* MD_DIO_11.3_2 */ /* PRQA S 0303 *//* MD_DIO_11.3_2 */
                                (uint32) 1u << PortPin, 
                                DIO_GET_CHL_MEM_AREA(ChannelId));


      return;
    }
  }
#endif

#if (DIO_CFG_SUPPORT_CAN == STD_ON) && (DIO_CFG_SUPPORT_GIO == STD_ON)
  static FUNC(void, DIO_CODE) Dio_CanWriteChannel(uint32 ChannelId, Dio_32BitRefType PortRef, uint32 Level) /* PRQA S 3206 *//* MD_DIO_3206 */ /* PRQA S 3673 *//* MD_DIO_16.7 */ 
  {
#endif
#if (DIO_CFG_SUPPORT_CAN == STD_ON)


    Dio_EnterCritical();
      /* a can port only has one I/O pin, where the data output register is located at bit position 1 */
      DIO_MODIFY_REGISTER_32BIT_SUPERVISOR( (uint32) PortRef,                                    /* PRQA S 0306*//* MD_DIO_11.3_2 */ /* PRQA S 0303*//* MD_DIO_11.3_2 */
                                             ( DIO_INV_CAN_IO_LEVEL_MASK | (Level << 1u) ), 
                                             ((Level << 1u) & DIO_CAN_IO_LEVEL_MASK), 
                                             DIO_GET_CHL_MEM_AREA(ChannelId)); 
    Dio_ExitCritical();


    return;
  }
#endif


/**********************************************************************************************************************
 * Dio_ReadPort
 **********************************************************************************************************************/
/*! \brief      Read out a DIO port
 * 
 *              This function reads out the value of the referenced DIO port.
 * 
 *  \param[in]  PortId        PortId representing the port to read from
 * 
 *  \return     Level of the DIO port
 * 
 *  \context    The function can be called on interrupt and task level.
 *********************************************************************************************************************/
FUNC(Dio_PortLevelType, DIO_CODE) Dio_ReadPort(Dio_PortType PortId)
{
  Dio_32BitRefType PortRef;


  PortRef = (Dio_32BitRefType) DIO_GET_PORT_ADDRESS(PortId); /* PRQA S 0306 *//* MD_DIO_11.3 */

  #if (DIO_CFG_CHK_PARAM_PORT == STD_ON)
    if (Dio_PortCheckTable[DIO_GET_CHECKIDX(PortId)] == PortId)
    {
      /* PortId is valid, proceed in service */
    }
    else
    {
      /* PortId is NOT valid */
      Dio_ReportDet(DIO_SID_READ_PORT, DIO_E_PARAM_INVALID_PORT_ID);


      return 0u;
    }
  #endif

#if (DIO_CFG_SUPPORT_CAN == STD_ON) && (DIO_CFG_SUPPORT_GIO == STD_ON)
  {
    /* in case both GIO and CAN ports are supported by configuration, the necessary function is selected by
     * the CanPin field in the Port-parameter. If only one of GIO or CAN ports is supported, the function
     * hierarchy is removed, and the code of the supported port type is included directly into this service.
     */
    uint32 PortClass = DIO_GET_PORT_CLASS(PortId);

        
    return (Dio_PortLevelType) Dio_Port[PortClass].ReadPort(PortId, PortRef);
  }
} /* PRQA S 2006 *//* MD_MSR_14.1 */
#endif

#if (DIO_CFG_SUPPORT_CAN == STD_ON) && (DIO_CFG_SUPPORT_GIO == STD_ON)
  static FUNC(uint32, DIO_CODE) Dio_GioReadPort(uint32 PortId, Dio_32BitRefType PortRef) /* PRQA S 3673 *//* MD_DIO_16.7 */
  {
#endif
#if (DIO_CFG_SUPPORT_GIO == STD_ON)
    {
      uint32 InSelector = DIO_GET_INPUT_IDX(PortId);
      

      /* ADEVT ports have GIODIN and GIODOUT in reversed order, hence the InSelector selects 
       * the correct register for reading
       */
      return DIO_READ_REGISTER_32BIT((uint32)&(((Dio_GioRegisterRefType) PortRef)->DataInOut[InSelector]), /* PRQA S 0310 *//* MD_DIO_11.4 */ /* PRQA S 0306*//* MD_DIO_11.3_2 */ /* PRQA S 0303 *//* MD_DIO_11.3_2 */
                                     DIO_GET_PORT_MEM_AREA(PortId) );
    }
  }
#endif

#if (DIO_CFG_SUPPORT_CAN == STD_ON) && (DIO_CFG_SUPPORT_GIO == STD_ON)
  static FUNC(uint32, DIO_CODE) Dio_CanReadPort(uint32 PortId, Dio_32BitRefType PortRef) /* PRQA S 3673 *//* MD_DIO_16.7 */ /* PRQA S 3206 *//* MD_DIO_3206 */
  {
#endif
#if (DIO_CFG_SUPPORT_CAN == STD_ON)


    /* a can port only has one I/O pin, where the data input register is located at bit position 0 */
    return ( DIO_READ_REGISTER_32BIT_SUPERVISOR((uint32)PortRef, /* PRQA S 0306*//* MD_DIO_11.3_2 */ /* PRQA S 0303 *//* MD_DIO_11.3_2 */
                                                 DIO_GET_PORT_MEM_AREA(PortId)) & 1u );
}
#endif


/**********************************************************************************************************************
 * Dio_WritePort
 **********************************************************************************************************************/
/*! \brief      Write a value to a DIO port
 * 
 *              This function writes the value to the referenced DIO port.
 * 
 *  \param[in]  PortId          PortId representing the port pin to write to
 *  \param[in]  Level           Level to apply to the port
 * 
 *  \context    The function can be called on interrupt and task level.
 *********************************************************************************************************************/
FUNC(void, DIO_CODE) Dio_WritePort(Dio_ChannelType PortId, Dio_PortLevelType Level)
{
  Dio_32BitRefType PortRef;


  PortRef = (Dio_32BitRefType) DIO_GET_PORT_ADDRESS(PortId); /* PRQA S 0306 *//* MD_DIO_11.3 */

  #if (DIO_CFG_CHK_PARAM_PORT == STD_ON)
    if (Dio_PortCheckTable[DIO_GET_CHECKIDX(PortId)] == PortId)
    {
      /* PortId is valid, proceed in service */
    }
    else
    {
      /* PortId is NOT valid */
      Dio_ReportDet(DIO_SID_WRITE_PORT, DIO_E_PARAM_INVALID_PORT_ID);


      return;
    }
  #endif

#if (DIO_CFG_SUPPORT_CAN == STD_ON) && (DIO_CFG_SUPPORT_GIO == STD_ON)
  {
    /* in case both GIO and CAN ports is supported by configuration, the necessary function is selected by
     * the CanPin field in the Channel-parameter. If only one of GIO or CAN ports is supported, the function
     * hierarchy is removed, and the code of the supported port type is included directly into this service.
     */
    uint32 PortClass = DIO_GET_PORT_CLASS(PortId);
    Dio_Port[PortClass].WritePort(PortId, PortRef, Level);


    return;
  }
} /* PRQA S 2006 *//* MD_MSR_14.1 */
#endif

#if (DIO_CFG_SUPPORT_CAN == STD_ON) && (DIO_CFG_SUPPORT_GIO == STD_ON)
  static FUNC(void, DIO_CODE) Dio_GioWritePort(uint32 PortId, Dio_32BitRefType PortRef, uint32 Level) /* PRQA S 3673 *//* MD_DIO_16.7 */ 
  {
#endif
#if (DIO_CFG_SUPPORT_GIO == STD_ON)
    {
      uint32 outSelector = DIO_GET_OUTPUT_IDX(PortId);
  
      /* ADEVT ports have GIODIN and GIODOUT in reversed order, hence the outSelector selects 
       * the correct register for writing
       */
      DIO_WRITE_REGISTER_32BIT( (uint32)&(((Dio_GioRegisterRefType) PortRef)->DataInOut[outSelector]), /* PRQA S 0310 *//* MD_DIO_11.4 */ /* PRQA S 0306*//* MD_DIO_11.3_2 */ /* PRQA S 0303 *//* MD_DIO_11.3_2 */
                                Level, 
                                DIO_GET_PORT_MEM_AREA(PortId));
      

      return;
    }
  }
#endif

#if (DIO_CFG_SUPPORT_CAN == STD_ON) && (DIO_CFG_SUPPORT_GIO == STD_ON)
  static FUNC(void, DIO_CODE) Dio_CanWritePort(uint32 PortId, Dio_32BitRefType PortRef, uint32 Level) /* PRQA S 3206 *//* MD_DIO_3206 */ /* PRQA S 3673 *//* MD_DIO_16.7 */ 
  {
#endif
#if (DIO_CFG_SUPPORT_CAN == STD_ON)


    Dio_EnterCritical();
      /* a can port only has one I/O pin, where the data output register is located at bit position 1 */
      DIO_MODIFY_REGISTER_32BIT_SUPERVISOR( (uint32) PortRef,                                    /* PRQA S 0306*//* MD_DIO_11.3_2 */ /* PRQA S 0303*//* MD_DIO_11.3_2 */
                                             ( DIO_INV_CAN_IO_LEVEL_MASK | (Level << 1u) ), 
                                             ((Level << 1u) & DIO_CAN_IO_LEVEL_MASK), 
                                             DIO_GET_PORT_MEM_AREA(PortId)); 
    Dio_ExitCritical();



    return;
  }
#endif

#if(DIO_MASKED_WRITE_PORT_API == STD_ON)
/**********************************************************************************************************************
 * Dio_MasekdWritePort
 **********************************************************************************************************************/
/*! \brief      Write a value to a DIO port
 * 
 *              This function writes the value to the referenced DIO port under consideration of a bit mask.
 * 
 *  \param[in]  PortId          PortId representing the port to write to
 *  \param[in]  Level           Level to apply to the port
 *  \param[in]  Mask            Bitmask for the relevant pins of the port
 * 
 *  \context    The function can be called on interrupt and task level.
 *********************************************************************************************************************/
FUNC(void, DIO_CODE) Dio_MaskedWritePort(Dio_ChannelType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask)
{
  uint32 PortValue;


  #if (DIO_CFG_CHK_PARAM_PORT == STD_ON)
    if (Dio_PortCheckTable[DIO_GET_CHECKIDX(PortId)] == PortId)
    {
      /* PortId is valid, proceed in service */
    }
    else
    {
      /* PortId is NOT valid */
      Dio_ReportDet(DIO_SID_MASKED_WRITE_PORT, DIO_E_PARAM_INVALID_PORT_ID);


      return;
    }
  #endif


    Dio_EnterCritical();
    
    /* Read the current value of the Port */
    PortValue = Dio_ReadPort( PortId );

    /* Clear old value of this port and apply new levels */
    PortValue &= ~(uint32)Mask;    
    PortValue |= (uint32)( Level & Mask );
    
    /* Write back the modified value */
    Dio_WritePort( PortId, (Dio_PortLevelType)PortValue );
    
    Dio_ExitCritical();



    return;
  } /* PRQA S 2006 *//* MD_MSR_14.1 */
#endif /*(DIO_MASKED_WRITE_PORT_API == STD_ON)*/


/**********************************************************************************************************************
 * Dio_ReadChannelGroup
 **********************************************************************************************************************/
/*! \brief      reads a value from a DIO channel group
 * 
 *              this function reads the value of a port and shifts/masks out the information not relevant in that
 *              a channel group.
 * 
 *  \param[in]  ChannelGroupIdPtr   reference to the channel group (created by configuration)
 * 
 *  \return      value of the according channel group (shifted to read from offset 0)
 * 
 *  \context    The function can be called on interrupt and task level.
 *********************************************************************************************************************/
FUNC(Dio_PortLevelType, DIO_CODE) Dio_ReadChannelGroup(Dio_ChannelGroupRefType ChannelGroupIdPtr)
{
  uint32 PortValue;

  
  #if (DIO_CFG_CHK_PARAM_GROUP == STD_ON)
    if (NULL_PTR == ChannelGroupIdPtr)
    {
      /* null pointer is referenced by the parameter */
      Dio_ReportDet(DIO_SID_READ_CHL_GROUP, DIO_E_PARAM_INVALID_GROUP_ID);


      return 0u;
    }
    else
    {
      /* the pointer is valid, proceed */
    }

    if (Dio_PortCheckTable[DIO_GET_CHECKIDX(ChannelGroupIdPtr->port)] == ChannelGroupIdPtr->port)
    {
      /* PortId is valid, proceed in service */
    }
    else
    {
      /* PortId is NOT valid */
      Dio_ReportDet(DIO_SID_READ_CHL_GROUP, DIO_E_PARAM_INVALID_GROUP_ID);


      return 0u;
    }
  #endif

  PortValue   = Dio_ReadPort(ChannelGroupIdPtr->port);
  PortValue  &= ChannelGroupIdPtr->mask;
  PortValue >>= ChannelGroupIdPtr->offset;


  return PortValue; 
} /* PRQA S 2006 *//* MD_MSR_14.1 */


/**********************************************************************************************************************
 * Dio_WriteChannelGroup
 **********************************************************************************************************************/
/*! \brief      writes a value to a DIO channel group
 * 
 *              this function shifts/masks out the information not relevant in that channel group and 
 *              writes the value to a port. 
 * 
 *  \param[in]  ChannelGroupIdPtr   reference to the channel group (created by configuration)
 *  \param[in]  Level               level to write to the port group
 * 
 *  \context    The function can be called on interrupt and task level.
 *********************************************************************************************************************/
FUNC(void, DIO_CODE) Dio_WriteChannelGroup(Dio_ChannelGroupRefType ChannelGroupIdPtr, Dio_PortLevelType Level)
{
  uint32 PortValue;
  uint32 newValue;

  
  #if (DIO_CFG_CHK_PARAM_GROUP == STD_ON)
    if (NULL_PTR == ChannelGroupIdPtr)
    {
      /* null pointer is referenced by the parameter */
      Dio_ReportDet(DIO_SID_WRITE_CHL_GROUP, DIO_E_PARAM_INVALID_GROUP_ID);


      return;
    }
    else
    {
      /* the pointer is valid, proceed */
    }

    if (Dio_PortCheckTable[DIO_GET_CHECKIDX(ChannelGroupIdPtr->port)] == ChannelGroupIdPtr->port)
    {
      /* PortId is valid, proceed in service */
    }
    else
    {
      /* PortId is NOT valid */
      Dio_ReportDet(DIO_SID_WRITE_CHL_GROUP, DIO_E_PARAM_INVALID_GROUP_ID);


      return;
    }
  #endif

  newValue  = (Level << ChannelGroupIdPtr->offset) & ChannelGroupIdPtr->mask;
  

  Dio_EnterCritical();
    PortValue = Dio_ReadPort(ChannelGroupIdPtr->port);

    /* clear old value of this channel group and apply new levels */
    PortValue &= ~ChannelGroupIdPtr->mask;
    PortValue |= newValue;
    Dio_WritePort(ChannelGroupIdPtr->port, PortValue);
  Dio_ExitCritical();



  return; 
} /* PRQA S 2006 *//* MD_MSR_14.1 */


#define DIO_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 *//* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  END OF FILE: Dio.c
 *********************************************************************************************************************/
