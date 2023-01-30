/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Adc.h
* Module Description: ADC Unit 1 Complex Device Driver
* Product           : Gen II Plus - EA3.0
* Author            : Lonnie Newton
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Fri Nov 02 09:15:00 2012
* %version:          4 %
* %derived_by:       nz63rn %
* %date_modified:    Thu Apr 10 11:30:20 2014 %
*---------------------------------------------------------------------------*/

#if !defined (ADC_H)
#define ADC_H

#include "Adc_Cfg.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define D_NUMOFGROUPS_CNT_U8			3U
#define D_GROUPEV_CNT_U8				0U
#define D_GROUP1_CNT_U8					1U
#define D_GROUP2_CNT_U8					2U
#define D_NTCPARMBIT0_CNT_U8			0x01U
#define D_NTCPARMBIT1_CNT_U8			0x02U
#define D_NTCPARMBIT2_CNT_U8			0x04U

	
/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/* Numeric ID of an ADC channel group. Range: 0-254, 255 is reserved for ADC_INVALID_GRP_ID */
typedef uint8  Adc_GroupType;

/* Type for reading the converted values of a channel group (raw, without further scaling, right aligned). */
typedef uint16 Adc_ValueGroupType;

/* Current status of the conversion of the requested ADC Channel group. */
typedef enum
{
  ADC_IDLE,
  ADC_BUSY,
  ADC_COMPLETED,
  ADC_STREAM_COMPLETED
} Adc_StatusType;

typedef struct
{
			 VAR(uint8, AUTOMATIC)					NumOfChannels;    		/* Number of channels configured for sampling in the group */
			 VAR(uint32, AUTOMATIC)					ChannelSelect;        	/* The channel select mask for starting channel conversions */
	volatile P2VAR(uint32, AUTOMATIC, AUTOMATIC)    ResultBuf; /* Address of the first location of the groups configured ADC results RAM */
} Adc_GroupConfigDataType;


/* Reference type for Adc_ValueGroupType */
typedef P2VAR(Adc_ValueGroupType,    AUTOMATIC, ADC_APPL_DATA) Adc_ValueGroupRefType;

/**********************************************************************************************************************
 *  GLOBAL MACRO API (Optimization for minimizing run-time or stubbing out unused features)
 *********************************************************************************************************************/

/************************************************************************************************************************
  * Name:        Adc_SetupResultBuffer
  * Description: This function is the Adc group result buffer setup service. It is responsible for setting up the result
  *              	buffer pointer of the group 'Group'
  * Inputs:      Group - Numeric Id of requested Adc channel group
  * 		     DataBufferPtr - ADC results of all channels of the selected group are stored in the data buffer
  *               	addressed with the pointer.
  * Outputs:     EOK
*************************************************************************************************************************/
/* This Api is provided to support for the standard Autosar API, however the design of this driver does not
 * buffer an intermediate copy of the results and therefore does not require a result buffer.  The hardware provides
 * a sufficient Adc results buffer.
 */
#define Adc_SetupResultBuffer( Group, DataBufferPtr )	(Std_ReturnType)E_OK	

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"

/* Remap generic Autosar API to Fixed configuration Api */
#define Adc_Init(x)		 Adc_Init_FixedCfg() /* Remap standard AUTOSAR API which takes 1 argument for specifying one of many
												possible configurations at run-time to the Fixed configuration provided in this design.
												The remap feature here allows the user of this module to use the standard Autosar interface
												to allow the user module to be compatible with an Adc Autosar driver for a different target
												microprocessor.
											  */
/* Declarations of API functions */
FUNC(void, ADC_CODE) Adc_Init_FixedCfg(void);  /* Not to be invoked directly since it is not the Standard Autosar API, should be invoked via the standardd API which is remapped ia a macro*/
FUNC(void, ADC_CODE) Adc_StartGroupConversion(Adc_GroupType Group);
FUNC(Std_ReturnType, ADC_CODE) Adc_ReadGroup(Adc_GroupType Group, Adc_ValueGroupRefType DataBufferPtr);
FUNC(Adc_StatusType, ADC_CODE) Adc_GetGroupStatus(Adc_GroupType Group);

#define ADC_STOP_SEC_CODE
#include "MemMap.h"

#endif  /* ADC_H */
  
/*****************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description              SCR #
-------   -------  --------  -----------------------------------  ----------
11/02/12   1.0      LN      	Initial Component Creation			CR6519
01/18/13   2      	JJW      	Updates per peer review
04/10/14   4        KMC         Updated format of values of       CR11684
                                D_NTCPARMBIT constants to 
								eliminate compiler warnings
******************************************************************************/
