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
 *         File:  Crc.c
 *    Component:  SysService_AsrCrc
 *       Module:  Crc
 *    Generator:  MICROSAR EAD
 *
 *  Description:  Crc module is used to calculate CRC values for data to
 *                ensure data integrity.
 *
 *********************************************************************************************************************/

/* source code file identification */
#define CRC_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Crc.h"

/**********************************************************************************************************************
 *  for SIP check
 *********************************************************************************************************************/
#ifndef V_SUPPRESS_EXTENDED_VERSION_CHECK
#include "v_ver.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if(   (CRC_SW_MAJOR_VERSION != (4u) ) \
    || (CRC_SW_MINOR_VERSION != (0u) ))
#error "Version numbers of Crc.c and Crc.h are inconsistent!"
#endif

#if(   (CRC_CFG_MAJOR_VERSION != (4u) ) \
    || (CRC_CFG_MINOR_VERSION != (0u) ))
#error "Version numbers of Crc.c and Crc_Cfg.h are inconsistent!"
#endif

#define CRC_START_SEC_CONST_32BIT
#include "MemMap.h"

/**********************************************************************************************************************
 * SIP check
 *********************************************************************************************************************/
#ifndef V_SUPPRESS_EXTENDED_VERSION_CHECK
/*
 The name of this const variable is defined via v_ver.h and depends on the
 version of the C file. The value of the const variable is also defined
 externally and is used for consistency checks, too.
 */
CONST( uint32, CRC_CONST ) SYSSERVICE_ASRCRC_LIB_SYMBOL = SYSSERVICE_ASRCRC_LIB_VERSION;
#endif

#define CRC_STOP_SEC_CONST_32BIT
#include "MemMap.h"

/**********************************************************************************************************************
 *  configuration check
 *********************************************************************************************************************/

/* check for correct configuration */
#if (CRC_8_MODE == CRC_8_HARDWARE)
#error "Calculation of 8bit CRC in hardware is not supported. Please configure CRC_8_MODE to either CRC_8_RUNTIME or CRC_8_TABLE"
#endif
#if (CRC_16_MODE == CRC_16_HARDWARE)
#error "Calculation of 16bit CRC in hardware is not supported. Please configure CRC_16_MODE to either CRC_16_RUNTIME or CRC_16_TABLE"
#endif
#if (CRC_32_MODE == CRC_32_HARDWARE)
#error "Calculation of 32bit CRC in hardware is not supported. Please configure CRC_32_MODE to either CRC_32_RUNTIME or CRC_32_TABLE"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
/* CRC8 polynomial */
#define CRC_POLYNOMIAL_8            (0x1du)

/* CRC16 polynomial */
#define CRC_POLYNOMIAL_16           (0x1021u)

/* CRC32 polynomial */
#define CRC_POLYNOMIAL_32           (0x04C11DB7uL)
#define CRC_POLYNOMIAL_32_REFLECT   (0xEDB88320uL)
#define CRC_FINAL_XOR_CRC32         (0xFFFFFFFFuL)

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/
/* Pre-Calculated tables */
#if (CRC_8_MODE == CRC_8_TABLE)
#define CRC_START_SEC_CONST_8BIT
#include "MemMap.h"          /* allows flexible memory mapping */

/*
 * CRC LOOKUP TABLE
 *
 * The following CRC lookup table was generated automatically
 * using the following model parameters:
 *
 *    Width                  : 8 bits
 *    Polynomial             : x^8 + x^4 + x^3 + x^2 + 1
 *                             0x11d (1-0001-1101)
 *    Initial Register Value : 0x0
 *    Reflect Input          : false
 *    Reflect Output         : false
 *    Value To XOR Output    : 0x0
 *    check value            : 0x37
 */

static CONST(uint8,CRC_CONST)Crc8Table[256] =
{
	0x00u, 0x1du, 0x3au, 0x27u,
	0x74u, 0x69u, 0x4eu, 0x53u,
	0xe8u, 0xf5u, 0xd2u, 0xcfu,
	0x9cu, 0x81u, 0xa6u, 0xbbu,
	0xcdu, 0xd0u, 0xf7u, 0xeau,
	0xb9u, 0xa4u, 0x83u, 0x9eu,
	0x25u, 0x38u, 0x1fu, 0x02u,
	0x51u, 0x4cu, 0x6bu, 0x76u,
	0x87u, 0x9au, 0xbdu, 0xa0u,
	0xf3u, 0xeeu, 0xc9u, 0xd4u,
	0x6fu, 0x72u, 0x55u, 0x48u,
	0x1bu, 0x06u, 0x21u, 0x3cu,
	0x4au, 0x57u, 0x70u, 0x6du,
	0x3eu, 0x23u, 0x04u, 0x19u,
	0xa2u, 0xbfu, 0x98u, 0x85u,
	0xd6u, 0xcbu, 0xecu, 0xf1u,
	0x13u, 0x0eu, 0x29u, 0x34u,
	0x67u, 0x7au, 0x5du, 0x40u,
	0xfbu, 0xe6u, 0xc1u, 0xdcu,
	0x8fu, 0x92u, 0xb5u, 0xa8u,
	0xdeu, 0xc3u, 0xe4u, 0xf9u,
	0xaau, 0xb7u, 0x90u, 0x8du,
	0x36u, 0x2bu, 0x0cu, 0x11u,
	0x42u, 0x5fu, 0x78u, 0x65u,
	0x94u, 0x89u, 0xaeu, 0xb3u,
	0xe0u, 0xfdu, 0xdau, 0xc7u,
	0x7cu, 0x61u, 0x46u, 0x5bu,
	0x08u, 0x15u, 0x32u, 0x2fu,
	0x59u, 0x44u, 0x63u, 0x7eu,
	0x2du, 0x30u, 0x17u, 0x0au,
	0xb1u, 0xacu, 0x8bu, 0x96u,
	0xc5u, 0xd8u, 0xffu, 0xe2u,
	0x26u, 0x3bu, 0x1cu, 0x01u,
	0x52u, 0x4fu, 0x68u, 0x75u,
	0xceu, 0xd3u, 0xf4u, 0xe9u,
	0xbau, 0xa7u, 0x80u, 0x9du,
	0xebu, 0xf6u, 0xd1u, 0xccu,
	0x9fu, 0x82u, 0xa5u, 0xb8u,
	0x03u, 0x1eu, 0x39u, 0x24u,
	0x77u, 0x6au, 0x4du, 0x50u,
	0xa1u, 0xbcu, 0x9bu, 0x86u,
	0xd5u, 0xc8u, 0xefu, 0xf2u,
	0x49u, 0x54u, 0x73u, 0x6eu,
	0x3du, 0x20u, 0x07u, 0x1au,
	0x6cu, 0x71u, 0x56u, 0x4bu,
	0x18u, 0x05u, 0x22u, 0x3fu,
	0x84u, 0x99u, 0xbeu, 0xa3u,
	0xf0u, 0xedu, 0xcau, 0xd7u,
	0x35u, 0x28u, 0x0fu, 0x12u,
	0x41u, 0x5cu, 0x7bu, 0x66u,
	0xddu, 0xc0u, 0xe7u, 0xfau,
	0xa9u, 0xb4u, 0x93u, 0x8eu,
	0xf8u, 0xe5u, 0xc2u, 0xdfu,
	0x8cu, 0x91u, 0xb6u, 0xabu,
	0x10u, 0x0du, 0x2au, 0x37u,
	0x64u, 0x79u, 0x5eu, 0x43u,
	0xb2u, 0xafu, 0x88u, 0x95u,
	0xc6u, 0xdbu, 0xfcu, 0xe1u,
	0x5au, 0x47u, 0x60u, 0x7du,
	0x2eu, 0x33u, 0x14u, 0x09u,
	0x7fu, 0x62u, 0x45u, 0x58u,
	0x0bu, 0x16u, 0x31u, 0x2cu,
	0x97u, 0x8au, 0xadu, 0xb0u,
	0xe3u, 0xfeu, 0xd9u, 0xc4u
};
#define CRC_STOP_SEC_CONST_8BIT
#include "MemMap.h"          /* allows flexible memory mapping   */
#endif

#if (CRC_16_MODE == CRC_16_TABLE)
#define CRC_START_SEC_CONST_16BIT
#include "MemMap.h"

static CONST(uint16, CRC_CONST) Crc_Table16 [ 256 ] =
{
	0x0000u, 0x1021u, 0x2042u, 0x3063u, 0x4084u, 0x50a5u, 0x60c6u, 0x70e7u,
	0x8108u, 0x9129u, 0xa14au, 0xb16bu, 0xc18cu, 0xd1adu, 0xe1ceu, 0xf1efu,
	0x1231u, 0x0210u, 0x3273u, 0x2252u, 0x52b5u, 0x4294u, 0x72f7u, 0x62d6u,
	0x9339u, 0x8318u, 0xb37bu, 0xa35au, 0xd3bdu, 0xc39cu, 0xf3ffu, 0xe3deu,
	0x2462u, 0x3443u, 0x0420u, 0x1401u, 0x64e6u, 0x74c7u, 0x44a4u, 0x5485u,
	0xa56au, 0xb54bu, 0x8528u, 0x9509u, 0xe5eeu, 0xf5cfu, 0xc5acu, 0xd58du,
	0x3653u, 0x2672u, 0x1611u, 0x0630u, 0x76d7u, 0x66f6u, 0x5695u, 0x46b4u,
	0xb75bu, 0xa77au, 0x9719u, 0x8738u, 0xf7dfu, 0xe7feu, 0xd79du, 0xc7bcu,
	0x48c4u, 0x58e5u, 0x6886u, 0x78a7u, 0x0840u, 0x1861u, 0x2802u, 0x3823u,
	0xc9ccu, 0xd9edu, 0xe98eu, 0xf9afu, 0x8948u, 0x9969u, 0xa90au, 0xb92bu,
	0x5af5u, 0x4ad4u, 0x7ab7u, 0x6a96u, 0x1a71u, 0x0a50u, 0x3a33u, 0x2a12u,
	0xdbfdu, 0xcbdcu, 0xfbbfu, 0xeb9eu, 0x9b79u, 0x8b58u, 0xbb3bu, 0xab1au,
	0x6ca6u, 0x7c87u, 0x4ce4u, 0x5cc5u, 0x2c22u, 0x3c03u, 0x0c60u, 0x1c41u,
	0xedaeu, 0xfd8fu, 0xcdecu, 0xddcdu, 0xad2au, 0xbd0bu, 0x8d68u, 0x9d49u,
	0x7e97u, 0x6eb6u, 0x5ed5u, 0x4ef4u, 0x3e13u, 0x2e32u, 0x1e51u, 0x0e70u,
	0xff9fu, 0xefbeu, 0xdfddu, 0xcffcu, 0xbf1bu, 0xaf3au, 0x9f59u, 0x8f78u,
	0x9188u, 0x81a9u, 0xb1cau, 0xa1ebu, 0xd10cu, 0xc12du, 0xf14eu, 0xe16fu,
	0x1080u, 0x00a1u, 0x30c2u, 0x20e3u, 0x5004u, 0x4025u, 0x7046u, 0x6067u,
	0x83b9u, 0x9398u, 0xa3fbu, 0xb3dau, 0xc33du, 0xd31cu, 0xe37fu, 0xf35eu,
	0x02b1u, 0x1290u, 0x22f3u, 0x32d2u, 0x4235u, 0x5214u, 0x6277u, 0x7256u,
	0xb5eau, 0xa5cbu, 0x95a8u, 0x8589u, 0xf56eu, 0xe54fu, 0xd52cu, 0xc50du,
	0x34e2u, 0x24c3u, 0x14a0u, 0x0481u, 0x7466u, 0x6447u, 0x5424u, 0x4405u,
	0xa7dbu, 0xb7fau, 0x8799u, 0x97b8u, 0xe75fu, 0xf77eu, 0xc71du, 0xd73cu,
	0x26d3u, 0x36f2u, 0x0691u, 0x16b0u, 0x6657u, 0x7676u, 0x4615u, 0x5634u,
	0xd94cu, 0xc96du, 0xf90eu, 0xe92fu, 0x99c8u, 0x89e9u, 0xb98au, 0xa9abu,
	0x5844u, 0x4865u, 0x7806u, 0x6827u, 0x18c0u, 0x08e1u, 0x3882u, 0x28a3u,
	0xcb7du, 0xdb5cu, 0xeb3fu, 0xfb1eu, 0x8bf9u, 0x9bd8u, 0xabbbu, 0xbb9au,
	0x4a75u, 0x5a54u, 0x6a37u, 0x7a16u, 0x0af1u, 0x1ad0u, 0x2ab3u, 0x3a92u,
	0xfd2eu, 0xed0fu, 0xdd6cu, 0xcd4du, 0xbdaau, 0xad8bu, 0x9de8u, 0x8dc9u,
	0x7c26u, 0x6c07u, 0x5c64u, 0x4c45u, 0x3ca2u, 0x2c83u, 0x1ce0u, 0x0cc1u,
	0xef1fu, 0xff3eu, 0xcf5du, 0xdf7cu, 0xaf9bu, 0xbfbau, 0x8fd9u, 0x9ff8u,
	0x6e17u, 0x7e36u, 0x4e55u, 0x5e74u, 0x2e93u, 0x3eb2u, 0x0ed1u, 0x1ef0u
};

#define CRC_STOP_SEC_CONST_16BIT
#include "MemMap.h"
#endif

#if (CRC_32_MODE == CRC_32_TABLE)
#define CRC_START_SEC_CONST_32BIT
#include "MemMap.h"

static CONST(uint32, CRC_CONST) Crc_Table32 [ 256 ] =
{
	0x00000000uL, 0x77073096uL, 0xEE0E612CuL, 0x990951BAuL,
	0x076DC419uL, 0x706AF48FuL, 0xE963A535uL, 0x9E6495A3uL,
	0x0EDB8832uL, 0x79DCB8A4uL, 0xE0D5E91EuL, 0x97D2D988uL,
	0x09B64C2BuL, 0x7EB17CBDuL, 0xE7B82D07uL, 0x90BF1D91uL,
	0x1DB71064uL, 0x6AB020F2uL, 0xF3B97148uL, 0x84BE41DEuL,
	0x1ADAD47DuL, 0x6DDDE4EBuL, 0xF4D4B551uL, 0x83D385C7uL,
	0x136C9856uL, 0x646BA8C0uL, 0xFD62F97AuL, 0x8A65C9ECuL,
	0x14015C4FuL, 0x63066CD9uL, 0xFA0F3D63uL, 0x8D080DF5uL,
	0x3B6E20C8uL, 0x4C69105EuL, 0xD56041E4uL, 0xA2677172uL,
	0x3C03E4D1uL, 0x4B04D447uL, 0xD20D85FDuL, 0xA50AB56BuL,
	0x35B5A8FAuL, 0x42B2986CuL, 0xDBBBC9D6uL, 0xACBCF940uL,
	0x32D86CE3uL, 0x45DF5C75uL, 0xDCD60DCFuL, 0xABD13D59uL,
	0x26D930ACuL, 0x51DE003AuL, 0xC8D75180uL, 0xBFD06116uL,
	0x21B4F4B5uL, 0x56B3C423uL, 0xCFBA9599uL, 0xB8BDA50FuL,
	0x2802B89EuL, 0x5F058808uL, 0xC60CD9B2uL, 0xB10BE924uL,
	0x2F6F7C87uL, 0x58684C11uL, 0xC1611DABuL, 0xB6662D3DuL,
	0x76DC4190uL, 0x01DB7106uL, 0x98D220BCuL, 0xEFD5102AuL,
	0x71B18589uL, 0x06B6B51FuL, 0x9FBFE4A5uL, 0xE8B8D433uL,
	0x7807C9A2uL, 0x0F00F934uL, 0x9609A88EuL, 0xE10E9818uL,
	0x7F6A0DBBuL, 0x086D3D2DuL, 0x91646C97uL, 0xE6635C01uL,
	0x6B6B51F4uL, 0x1C6C6162uL, 0x856530D8uL, 0xF262004EuL,
	0x6C0695EDuL, 0x1B01A57BuL, 0x8208F4C1uL, 0xF50FC457uL,
	0x65B0D9C6uL, 0x12B7E950uL, 0x8BBEB8EAuL, 0xFCB9887CuL,
	0x62DD1DDFuL, 0x15DA2D49uL, 0x8CD37CF3uL, 0xFBD44C65uL,
	0x4DB26158uL, 0x3AB551CEuL, 0xA3BC0074uL, 0xD4BB30E2uL,
	0x4ADFA541uL, 0x3DD895D7uL, 0xA4D1C46DuL, 0xD3D6F4FBuL,
	0x4369E96AuL, 0x346ED9FCuL, 0xAD678846uL, 0xDA60B8D0uL,
	0x44042D73uL, 0x33031DE5uL, 0xAA0A4C5FuL, 0xDD0D7CC9uL,
	0x5005713CuL, 0x270241AAuL, 0xBE0B1010uL, 0xC90C2086uL,
	0x5768B525uL, 0x206F85B3uL, 0xB966D409uL, 0xCE61E49FuL,
	0x5EDEF90EuL, 0x29D9C998uL, 0xB0D09822uL, 0xC7D7A8B4uL,
	0x59B33D17uL, 0x2EB40D81uL, 0xB7BD5C3BuL, 0xC0BA6CADuL,
	0xEDB88320uL, 0x9ABFB3B6uL, 0x03B6E20CuL, 0x74B1D29AuL,
	0xEAD54739uL, 0x9DD277AFuL, 0x04DB2615uL, 0x73DC1683uL,
	0xE3630B12uL, 0x94643B84uL, 0x0D6D6A3EuL, 0x7A6A5AA8uL,
	0xE40ECF0BuL, 0x9309FF9DuL, 0x0A00AE27uL, 0x7D079EB1uL,
	0xF00F9344uL, 0x8708A3D2uL, 0x1E01F268uL, 0x6906C2FEuL,
	0xF762575DuL, 0x806567CBuL, 0x196C3671uL, 0x6E6B06E7uL,
	0xFED41B76uL, 0x89D32BE0uL, 0x10DA7A5AuL, 0x67DD4ACCuL,
	0xF9B9DF6FuL, 0x8EBEEFF9uL, 0x17B7BE43uL, 0x60B08ED5uL,
	0xD6D6A3E8uL, 0xA1D1937EuL, 0x38D8C2C4uL, 0x4FDFF252uL,
	0xD1BB67F1uL, 0xA6BC5767uL, 0x3FB506DDuL, 0x48B2364BuL,
	0xD80D2BDAuL, 0xAF0A1B4CuL, 0x36034AF6uL, 0x41047A60uL,
	0xDF60EFC3uL, 0xA867DF55uL, 0x316E8EEFuL, 0x4669BE79uL,
	0xCB61B38CuL, 0xBC66831AuL, 0x256FD2A0uL, 0x5268E236uL,
	0xCC0C7795uL, 0xBB0B4703uL, 0x220216B9uL, 0x5505262FuL,
	0xC5BA3BBEuL, 0xB2BD0B28uL, 0x2BB45A92uL, 0x5CB36A04uL,
	0xC2D7FFA7uL, 0xB5D0CF31uL, 0x2CD99E8BuL, 0x5BDEAE1DuL,
	0x9B64C2B0uL, 0xEC63F226uL, 0x756AA39CuL, 0x026D930AuL,
	0x9C0906A9uL, 0xEB0E363FuL, 0x72076785uL, 0x05005713uL,
	0x95BF4A82uL, 0xE2B87A14uL, 0x7BB12BAEuL, 0x0CB61B38uL,
	0x92D28E9BuL, 0xE5D5BE0DuL, 0x7CDCEFB7uL, 0x0BDBDF21uL,
	0x86D3D2D4uL, 0xF1D4E242uL, 0x68DDB3F8uL, 0x1FDA836EuL,
	0x81BE16CDuL, 0xF6B9265BuL, 0x6FB077E1uL, 0x18B74777uL,
	0x88085AE6uL, 0xFF0F6A70uL, 0x66063BCAuL, 0x11010B5CuL,
	0x8F659EFFuL, 0xF862AE69uL, 0x616BFFD3uL, 0x166CCF45uL,
	0xA00AE278uL, 0xD70DD2EEuL, 0x4E048354uL, 0x3903B3C2uL,
	0xA7672661uL, 0xD06016F7uL, 0x4969474DuL, 0x3E6E77DBuL,
	0xAED16A4AuL, 0xD9D65ADCuL, 0x40DF0B66uL, 0x37D83BF0uL,
	0xA9BCAE53uL, 0xDEBB9EC5uL, 0x47B2CF7FuL, 0x30B5FFE9uL,
	0xBDBDF21CuL, 0xCABAC28AuL, 0x53B39330uL, 0x24B4A3A6uL,
	0xBAD03605uL, 0xCDD70693uL, 0x54DE5729uL, 0x23D967BFuL,
	0xB3667A2EuL, 0xC4614AB8uL, 0x5D681B02uL, 0x2A6F2B94uL,
	0xB40BBE37uL, 0xC30C8EA1uL, 0x5A05DF1BuL, 0x2D02EF8DuL
};

#define CRC_STOP_SEC_CONST_32BIT
#include "MemMap.h"
#endif

#define CRC_START_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Crc_CalculateCRC8
 **********************************************************************************************************************/
/*! \brief      Performs a CRC8 calculation on Crc_Length data bytes, pointed to by Crc_DataPtr,
 *              with the starting value of Crc_StartValue8.
 *  \param[in]  Crc_DataPtr             reference to the data buffer from which the value
 *                                      shall be calculated
 *  \param[in]  Crc_Length              Number of bytes for calculation
 *  \param[in]  Crc_StartValue8        Initial value for calculation
 *  \return     calculated 8bit CRC value
 **********************************************************************************************************************/
FUNC(uint8, CRC_CODE) Crc_CalculateCRC8
(
		Crc_DataRefType Crc_DataPtr,
		uint32 Crc_Length,
		uint8 Crc_StartValue8
)
{
#if (CRC_8_MODE == CRC_8_TABLE)
	/*** Table calculation method ***/

	uint32 count; /* loop counter for CRC calculation */
	uint8 crc_value = Crc_StartValue8; /* CRC initial value                */

	for (count = 0; count < Crc_Length; count++)
	{
		crc_value = Crc8Table[crc_value ^ Crc_DataPtr[count]];
	}
	return crc_value;
#endif

#if (CRC_8_MODE == CRC_8_RUNTIME)
	/*** Runtime calculation method ***/

	uint8 crc_value = Crc_StartValue8; /* CRC initial value            */
	uint8 crc_cur;
	uint8 crc_poly = CRC_POLYNOMIAL_8;
	uint16 i;

	/* To calculate manualy the check value, following polynom division should be done:
	 * the data sequence (e.g. default ASCII string 123456789) in hex value: 0x31 32 33 34 35 36 37 38 39
	 * should be divided by the polynom 0x1d --> the remainder of this division in hex is 37 (= check value).
	 * The next line represents this polynom division:
	 * 00110001 00110010... : 11101 -> check value = 0011 1110 (= 0x37)
	 */
	while (Crc_Length --)
	{
		crc_cur=*(Crc_DataPtr ++); /*current data pointer            */
		for (i=0;i<8;i++)
		{
			if ( (crc_value & 0x80) == (crc_cur & 0x80) )
			{
				crc_value = (crc_value << 1);
			}
			else
			{
				crc_value = (crc_value << 1) ^ crc_poly;
			}
			crc_cur = (crc_cur << 1);
		}
	}
	return crc_value;
#endif
}/* Crc_CalculateCRC8() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Crc_CalculateCRC16
 **********************************************************************************************************************/
/*! \brief      Performs a CRC16 calculation on Crc_Length data bytes, pointed to by Crc_DataPtr,
 *              with the starting value of Crc_StartValue16.
 *  \param[in]  Crc_DataPtr             reference to the data buffer from which the value
 *                                      shall be calculated
 *  \param[in]  Crc_Length              Number of bytes for calculation
 *  \param[in]  Crc_StartValue16        Initial value for calculation
 *  \return     calculated 16bit CRC value
 **********************************************************************************************************************/
FUNC(uint16, CRC_CODE) Crc_CalculateCRC16
(
Crc_DataRefType Crc_DataPtr,
uint32 Crc_Length,
uint16 Crc_StartValue16
)
{
	uint16 CrcValue_u16 = Crc_StartValue16;

#if (CRC_16_MODE == CRC_16_TABLE)
	/*** Table calculation method ***/

	uint8 TableIndex; /* CRC table index  */

	while ( Crc_Length -- )
	{
		TableIndex = ((uint8)( CrcValue_u16 >> 8 )) ^ (*( Crc_DataPtr ++ ));
		CrcValue_u16 = ( CrcValue_u16 << 8 ) ^ Crc_Table16 [ TableIndex ];
	}

	return CrcValue_u16;

#else
	/*** Runtime calculation method ***/

	while ( Crc_Length -- )
	{
		uint8 i; /* loop counter 1..8     */

		CrcValue_u16 ^= ((uint16)(*( Crc_DataPtr ++ )) << 8);

		for (i = 0; i < 8; i++)
		{
			if (CrcValue_u16 & (uint16)0x8000u)
			{
				CrcValue_u16 = (CrcValue_u16 << 1) ^ CRC_POLYNOMIAL_16;
			}
			else
			{
				CrcValue_u16 <<= 1;
			}
		}
	}

	return CrcValue_u16;

#endif
} /* Crc_CalculateCRC16() */

/***********************************************************************************************************************
 *  Crc_CalculateCRC32
 **********************************************************************************************************************/
/*! \brief      Performs a CRC32 calculation on Crc_Length data bytes, pointed to by Crc_DataPtr,
 *              with the starting value of Crc_StartValue32.
 *  \param[in]  Crc_DataPtr             reference to the data buffer from which the value
 *                                      shall be calculated
 *  \param[in]  Crc_Length              Number of bytes for calculation
 *  \param[in]  Crc_StartValue32        Initial value for calculation
 *  \return     calculated 32bit CRC value
 **********************************************************************************************************************/
FUNC(uint32, CRC_CODE) Crc_CalculateCRC32
(
Crc_DataRefType Crc_DataPtr,
uint32 Crc_Length,
uint32 Crc_StartValue32
)
{
	uint32 CrcValue_u32 = Crc_StartValue32;

#if (CRC_32_MODE == CRC_32_TABLE)
	/*** Table calculation method ***/

	while ( Crc_Length -- )
	{
		CrcValue_u32 ^= 0xFFuL & (uint32) ( *( Crc_DataPtr ++ ));
		CrcValue_u32 = ( CrcValue_u32 >> 8 ) ^
		( Crc_Table32 [ (uint8)(CrcValue_u32 )]);
	}

	return CRC_FINAL_XOR_CRC32 ^ CrcValue_u32;

#else
	/*** Runtime calculation method ***/

	while ( Crc_Length -- )
	{
		uint16 i16; /* loop counter 1..8 */

		CrcValue_u32 ^= 0xFFuL & (uint32) ( * Crc_DataPtr ++ );

		for ( i16 = 0; i16 < 8; i16 ++ )
		{
			if ( CrcValue_u32 & 1 )
			{
				CrcValue_u32 = ( CrcValue_u32 >> 1 ) ^ CRC_POLYNOMIAL_32_REFLECT;
			}
			else
			{
				CrcValue_u32 = ( CrcValue_u32 >> 1 );
			}
		}
	}

	return CRC_FINAL_XOR_CRC32 ^ CrcValue_u32;
#endif
}

/***********************************************************************************************************************
 *  Crc_GetVerionInfo
 **********************************************************************************************************************/
/*! \brief      Writes the version information to the structure referenced by the
 *              parameter 'versioninfo'.
 *  \param[out] versioninfo             reference to the structure to which the
 *                                      version information data should be
 *                                      written to.
 **********************************************************************************************************************/
#if (CRC_VERSION_INFO_API == STD_ON)
FUNC(void, CRC_CODE) Crc_GetVersionInfo
(
P2VAR(Std_VersionInfoType, AUTOMATIC, CRC_APPL_DATA) versioninfo
)
{
	versioninfo->vendorID = CRC_VENDOR_ID;
	versioninfo->moduleID = CRC_MODULE_ID;
	versioninfo->instanceID = CRC_INSTANCE_ID;
	versioninfo->sw_major_version = CRC_SW_MAJOR_VERSION;
	versioninfo->sw_minor_version = CRC_SW_MINOR_VERSION;
	versioninfo->sw_patch_version = CRC_SW_PATCH_VERSION;

	return;
}
#endif

#define CRC_STOP_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *  END OF FILE: REQ_SPEC.C
 *********************************************************************************************************************/

