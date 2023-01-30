/**********************************************************************
*
*	C %name:		FlsTst.c %
*	Instance:		sag_EPS_1
*	Description:	API Implemation accoriding to AUTOSAR Specification of Flash Test v1.2.0
*	%created_by:	nz63rn %
*	%date_created:	Monday, April 07, 2014 4:25:37 PM %
*
**********************************************************************/
/* Version Control:
 * Date Created:      Tue Jul  3 13:20:08 2012
 * %version:          3 %
 * %derived_by:       nz63rn %
 * %date_modified:    Mon Apr 07 11:45:56 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 07/04/12   1       JJW       Initial version 
 * 10/10/13   2       KMC       Use all 20 bits of sector length field on CRC check -- fixes anomaly 5491     10345
 *                              QAC cleanup.
 * 04/07/14   3       KMC       Remove all direct access of DMA registers, and replace as needed with calls   11435
 *                              to DMA component functions.  Remove access to ESM registers and callbacks from
 *                              ESM interrupt handlers -- those have been moved to (other) uDiag files. QAC
 *                              cleanup.
 */

#define FLSTST_PRIVATEDEFS /* Enable Private definition exposure */
#include "FlsTst.h"

/* Include peripheral definitions used by this driver */
#include "crc_regs.h"
#include "Dma.h"

#define FLSTST_VENDORID				0U
#define FLSTST_MODULEID				0U
#define FLSTST_SW_MAJOR_VERSION		0U
#define FLSTST_SW_MINOR_VERSION		0U
#define FLSTST_SW_PATCH_VERSION		0U

#define D_FLSTSTSLFTSTLEN_CNT_U16		10U /* Per FDD 32 v000D Sec. 4.4.2.4.4 */
#define D_FLSTSTSLFTSTSEC_CNT_U32		1UL /* Number of signatures calculated during self test */
#define D_FLSTSTSLFTSTINITL_CNT_U32		0x00000000UL /* Initial CRC accumulator value lower 32 bits */
#define D_FLSTSTSLFTSTINITH_CNT_U32		0x00000000UL /* Initial CRC accumulator value upper 32 bits*/

#define D_CRCCH1BUSY_CNT_U32			0x00000001UL
#define D_CRCCH1SWRESET_CNT_U32			0x00000001UL

/* CRC_STATUS register bit masks*/
#define D_CRCSTATUSCLEAR_CNT_U32		0x0F0F0F0FUL

/* CRC_INTS register bit masks */
#define D_CRCCH1FAILENSMASK_CNT_U32		0x00000002UL

/* DMA memory protection constants */
#define D_DMACRCSIGWRITELEN_CNT_U16		8U	/* Byte length of the CRC PSA signature register */


/* Module Level Variables */
#define FLSTST_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint8, AUTOMATIC) FlsTst_ActvBufTestResultBgnd;
#define FLSTST_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */

#define FLSTST_START_SEC_VAR_16
#include "MemMap.h" /* PRQA S 5087 */
VAR(uint16, AUTOMATIC) FlsTst_BgndTestBlock = 0U;
STATIC VAR(uint16, AUTOMATIC) FlsTst_BgndInterval = 0U;
#define FLSTST_STOP_SEC_VAR_16
#include "MemMap.h" /* PRQA S 5087 */


#define FLSTST_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
VAR(FlsTst_SelfTestStateType, AUTOMATIC) FlsTst_SelfTestState; 	/* FLSTST_SLFTSTUNINIT = 0 */
VAR(FlsTst_StateType, AUTOMATIC) FlsTst_State; 					/* FLSTST_UNINIT = 0 */
STATIC VAR(boolean, AUTOMATIC) FlsTst_AbortPending; 			/* FALSE = 0 */
VAR(FlsTst_ErrorDetailsType, AUTOMATIC) FlsTst_ErrorDetails;	/* No failures = 0 */
STATIC VAR(FlsTst_TestResultBgndType, AUTOMATIC) FlsTst_TestResultBgnd[2U]; /* Interval Id = 0, FLSTST_NOT_TESTED = 0*/
STATIC VAR(FlsTst_TestResultFgndType, AUTOMATIC) FlsTst_TestResultFgnd; /* FLSTST_NOT_TESTED = 0*/
#if (STD_ON == FLSTST_GET_TEST_SIGNATURE_BGND_API)	/* [FlsTst056] */
STATIC VAR(FlsTst_TestSignatureBgndType, AUTOMATIC) FlsTst_TestSignatureBgnd;	/* [FlsTst115 default value 0] */
#endif
#if (STD_ON == FLSTST_GET_TEST_SIGNATURE_FGND_API)	/* [FlsTst059] */
STATIC VAR(FlsTst_TestSignatureFgndType, AUTOMATIC) FlsTst_TestSignatureFgnd;	/* [FlsTst116 default value 0] */
#endif
#define FLSTST_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

#define FLSTST_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
P2CONST(FlsTst_ConfigType, AUTOMATIC, AUTOMATIC) FlsTst_Config;
VAR(FlsTst_TestResultType, AUTOMATIC) FlsTst_CurrBgndTestResult;
#define FLSTST_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

#define FLSTST_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC CONST(Std_VersionInfoType, AUTOMATIC) FlsTst_VersionInfo = {	FLSTST_VENDORID,
																	FLSTST_MODULEID,
																	FLSTST_SW_MAJOR_VERSION,
																	FLSTST_SW_MINOR_VERSION,
																	FLSTST_SW_PATCH_VERSION};

STATIC CONST(uint64 , AUTOMATIC) t_FlsTstSlfTstData_Cnt_u64[D_FLSTSTSLFTSTLEN_CNT_U16] = {0x8000000000000001ULL,
																						0x0100000000000080ULL,
																						0x0040000000000200ULL,
																						0x0002000000004000ULL,
																						0x0000200000040000ULL,
																						0x0000040000200000ULL,
																						0x0000001008000000ULL,
																						0x0000000000000000ULL,
																						0xFFFFFFFFFFFFFFFFULL,
																						0xFFFFFFFF00000000ULL
																						};

STATIC CONST(uint64 , AUTOMATIC) t_FlsTstSlfTstCrc_Cnt_u64 = 0x8000000000000001ULL;

STATIC CONST(FlsTst_MemBlockType , AUTOMATIC) t_FlsTstSlfTstCfg_Cnt_Str = {	D_FLSTSTSLFTSTINITL_CNT_U32,		/* CRC Init Value */
																			D_FLSTSTSLFTSTINITH_CNT_U32,		/* CRC Init Value */
																			&t_FlsTstSlfTstCrc_Cnt_u64,			/* crcPtr */
																			t_FlsTstSlfTstData_Cnt_u64,			/* startPtr */
																			1U,									/* secnum */
																			(uint32)D_FLSTSTSLFTSTLEN_CNT_U16,	/* seclength */
																			D_FLSTSTSLFTSTLEN_CNT_U16,			/* dmaElementCnt */
																			1U									/* dmaFrameCnt */
																		};


#define FLSTST_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */


#define FLSTST_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */

/*****************************************************************************
  * Name:        FlsTst_Init
  * Description: Service for Flash Test initialization.
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, FLSTST_CODE) FlsTst_Init( const FlsTst_ConfigType* ConfigPtr )
{
	/* TODO: Move CRC register accesses to their own module for better encapsulation */
	
	
	FlsTst_Config = ConfigPtr;	/* Update Module Config Pointer with New Config Pointer */
	FlsTst_BgndInterval = 0U;	/* Reset the test interval counter at init */
	FlsTst_CurrBgndTestResult = FLSTST_RESULT_OK;

	/* Clear all interrupt flags then enable Ch1 Fail interrupt */
	CRCCTRLREG->CRC_STATUS = D_CRCSTATUSCLEAR_CNT_U32;
	CRCCTRLREG->CRC_INTS = D_CRCCH1FAILENSMASK_CNT_U32;

	/* Perform the Hardware Self Test when configured. This Self Test concept is a Nexteer extension to the driver specified by AUTOSAR */
	if(FLSTST_SLFTSTUNINIT == FlsTst_SelfTestState)
	{
		FlsTst_SelfTestState = FLSTST_SLFTSTRUNNING;
		/* Apply the self test config */
		SetupBgndBlk(t_FlsTstSlfTstCfg_Cnt_Str);
		/* The SelfTest config will cause an Error indication IRQ. The associated ISR will then complete this initialization */	
	}
	else
	{
		FlsTst_State = FLSTST_INIT;	/* Initialization completed*/
	}
}

/*****************************************************************************
  * Name:        FlsTst_DeInit
  * Description: Service for Flash Test De-Initialization.
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, FLSTST_CODE) FlsTst_DeInit( void )
{
	VAR(uint8, AUTOMATIC) NxtBuf_Cnt_T_u08;

	FlsTst_State = FLSTST_UNINIT;	/* [FlsTst029] */

	/* De-Initialize the used hardware */
	Dma_DisableFlsTstBlock();
	CRCCTRLREG->CRC_CTRL0 |= D_CRCCH1SWRESET_CNT_U32; /* Place Ch1 in Sw Reset */

	/* Initialize all state variables associated with a configuration when executing the Init function */
	NxtBuf_Cnt_T_u08 = (FlsTst_ActvBufTestResultBgnd ^ 1u) & 1u; /* XOR with 1 toggles the bit between 0 and 1, bitwise and with 1 assures index is in range */
	FlsTst_TestResultBgnd[NxtBuf_Cnt_T_u08].interval = 0U;
	FlsTst_TestResultBgnd[NxtBuf_Cnt_T_u08].result = FLSTST_RESULT_NOT_TESTED;
	FlsTst_ActvBufTestResultBgnd = NxtBuf_Cnt_T_u08;

#if (STD_ON == FLSTST_GET_TEST_SIGNATURE_BGND_API)	/* [FlsTst056] */
	FlsTst_TestSignatureBgnd.interval = 0U;
	FlsTst_TestSignatureBgnd.result = 0ULL;	/* [FlsTst115 default value 0] */
#endif
#if (STD_ON == FLSTST_GET_TEST_SIGNATURE_FGND_API)	/* [FlsTst059] */
	FlsTst_TestSignatureFgnd.interval = 0U;
	FlsTst_TestSignatureFgnd.result = 0ULL;	/* [FlsTst116 default value 0] */
#endif

}

#if (STD_ON == FLSTST_START_FGND_API)
/*****************************************************************************
  * Name:        FlsTst_StartFgnd
  * Description: Service for executing foreground Flash Test.
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
FUNC(Std_ReturnType, FLSTST_CODE) FlsTst_StartFgnd( FlsTst_BlockIdFgndType FgndBlockId )
{
	/* TODO: Implement the Foreground API when a use case merits */
	return(E_NOT_OK);
}
#endif

/*****************************************************************************
  * Name:        FlsTst_Abort
  * Description: Service for aborting the Flash Test.
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, FLSTST_CODE) FlsTst_Abort( void )
{
	/* Place the driver into the aborted state, the MainFunction shall finish the current block it is testing */
	FlsTst_AbortPending = TRUE;	/* [FlsTst031] */
}

#if (STD_ON == FLSTST_SUSPEND_RESUME_API)	/* [FlsTst088] */
/*****************************************************************************
  * Name:        FlsTst_Suspend
  * Description: Service for suspending current operation of the Flash Test, until FlsTst_Resume is called.
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, FLSTST_CODE) FlsTst_Suspend( void )
{
	if(( FLSTST_INIT == FlsTst_State ) || ( FLSTST_RUNNING == FlsTst_State ))
	{
		FlsTst_State = FLSTST_SUSPENDED;
	}
}
#endif

#if (STD_ON == FLSTST_SUSPEND_RESUME_API)	/* [FlsTst089] */
/*****************************************************************************
  * Name:        FlsTst_Resume
  * Description: Service for continuing the Flash Test at the point it was suspended.
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, FLSTST_CODE) FlsTst_Resume( void )
{
	if( FLSTST_SUSPENDED == FlsTst_State )
	{
		FlsTst_State = FLSTST_RUNNING;
	}
	/* TODO: Provide reuired DET */
}
#endif

#if (STD_ON == FLSTST_GET_CURRENT_STATE_API)	/* [FlsTst091] */
/*****************************************************************************
  * Name:        FlsTst_GetCurrentState
  * Description: Service returns the current Flash Test execution state.
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
FUNC(FlsTst_StateType, FLSTST_CODE) FlsTst_GetCurrentState( void )
{
	return( FlsTst_State );	/* [FlsTst041] */
}
#endif

#if (STD_ON == FLSTST_GET_TEST_RESULT_BGND_API)	/* [FlsTst093] */
/*****************************************************************************
  * Name:        FlsTst_GetTestResultBgnd
  * Description: Service returns the Background Flash Test result.
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
FUNC(FlsTst_TestResultBgndType, FLSTST_CODE) FlsTst_GetTestResultBgnd( void )
{
	return( FlsTst_TestResultBgnd[FlsTst_ActvBufTestResultBgnd] );
}
#endif

#if (STD_ON == FLSTST_GET_TEST_RESULT_FGND_API)	/* [FlsTst114] */
/*****************************************************************************
  * Name:        FlsTst_GetTestResultFgnd
  * Description: Service returns the Foreground Flash Test result.
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
FUNC(FlsTst_TestResultFgndType, FLSTST_CODE) FlsTst_GetTestResultFgnd( void )
{
	return( FlsTst_TestResultFgnd );
}
#endif

#if (STD_ON == FLSTST_GET_TEST_SIGNATURE_BGND_API)	/* [FlsTst056] */
/*****************************************************************************
  * Name:        FlsTst_GetTestSignatureBgnd
  * Description: Service returns the Flash Test result in background mode.
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
FUNC(FlsTst_TestSignatureBgndType, FLSTST_CODE) FlsTst_GetTestSignatureBgnd( void )
{
	return( FlsTst_TestSignatureBgnd );
}
#endif

#if (STD_ON == FLSTST_GET_TEST_SIGNATURE_FGND_API)	/* [FlsTst059] */
/*****************************************************************************
  * Name:        FlsTst_GetTestSignatureFgnd
  * Description: Service returns the Flash Test result in foreground mode.
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
FUNC(FlsTst_TestSignatureFgndType, FLSTST_CODE) FlsTst_GetTestSignatureFgnd( void )
{
	return( FlsTst_TestSignatureFgnd );
}
#endif 

#if (STD_ON == FLSTST_GET_ERROR_DETAILS_API)	/* [FlsTst062] */
/*****************************************************************************
  * Name:        FlsTst_ErrorDetailsType
  * Description: Service returns error detais monitored from the Flash module.
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
FUNC(FlsTst_ErrorDetailsType, FLSTST_CODE) FlsTst_GetErrorDetails( void )
{
	return( FlsTst_ErrorDetails );
}
#endif

#if (STD_ON == FLSTST_TEST_ECC_API)	/* [FlsTst065] */
/*****************************************************************************
  * Name:        FlsTst_TestEcc
  * Description: Service executes a test of ECC hardware. This is only applicable in case the hardware provides such functionality.
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
FUNC(Std_ReturnType, FLSTST_CODE) FlsTst_TestEcc( void )
{
	/* TODO: Implement the TestEcc API when a use case merits */
	return(E_NOT_OK);
}
#endif


/*****************************************************************************
  * Name:        FlsTst_MainFunction
  * Description: MainFunction state machine handler
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, FLSTST_CODE) FlsTst_MainFunction( void )
{
	VAR(uint8, AUTOMATIC) NxtBuf_Cnt_T_u08;

	switch(FlsTst_State){
	case FLSTST_RUNNING:
		/* Check if background blocks are configured and the Ch1 CRC is completed */
		if((FlsTst_Config->numBgndBlks > 0U) && (0UL == (D_CRCCH1BUSY_CNT_U32 & CRCCTRLREG->CRC_BUSY)))
		{			
			
			/* Configure and start next test interval */
			if(FlsTst_BgndTestBlock < ((uint16)FlsTst_Config->numBgndBlks - 1U))
			{
				if(FALSE == FlsTst_AbortPending) /* [FlsTst031] */
				{
					FlsTst_BgndTestBlock++;
					SetupBgndBlk(FlsTst_Config->MemBlk[FlsTst_BgndTestBlock]);
				}
			}
			else
			{
				/* Update the Test Results Module Variable */

				/* Double buffer used for FlsTst_TestResultBgnd data set for data consistency protection with the data reported by FlsTst_GetTestResultBgnd.
				 * An exclusive region was not used, because the associated run-time is assumed to be shorter for the double buffer in this case
				 * and the additional RAM required is negligible.  */
				NxtBuf_Cnt_T_u08 = (FlsTst_ActvBufTestResultBgnd ^ 1u) & 1u; /* XOR with 1 toggles the bit between 0 and 1, bitwise and with 1 assures index is in range */
				FlsTst_TestResultBgnd[NxtBuf_Cnt_T_u08].interval = FlsTst_BgndInterval;
				FlsTst_TestResultBgnd[NxtBuf_Cnt_T_u08].result = FlsTst_CurrBgndTestResult;
				FlsTst_ActvBufTestResultBgnd = NxtBuf_Cnt_T_u08;

				/* Increment the interval counter in preparation for the start of the next interval */
				FlsTst_State = FLSTST_INIT;
				FlsTst_BgndInterval++;
				
				#if (STD_ON == FLSTST_TEST_COMPLETE_NOTIFICATION_SUPPORTED)	/* [FlsTst159] */
				/* Provide interval completed notification */
				FlsTst_TestCompleted();
				#endif
			}

			/* Transition to the Aborted State, when requested, at this point because the current atomic sequence is completed */
			if(TRUE == FlsTst_AbortPending)
			{
				FlsTst_State = FLSTST_ABORTED;
				FlsTst_AbortPending = FALSE;
			}
		}
		break;
	case FLSTST_INIT:
		FlsTst_BgndTestBlock = 0U;
		FlsTst_State = FLSTST_RUNNING;	/* [FlsTst068] */
		FlsTst_CurrBgndTestResult = FLSTST_RESULT_OK; /* Init new test result to OK, any failure detected during interval will set it to NOT_OK */
	
		if(FlsTst_Config->numBgndBlks > 0U)
		{
			SetupBgndBlk(FlsTst_Config->MemBlk[FlsTst_BgndTestBlock]);
		}
		break;
	case FLSTST_ABORTED:
	case FLSTST_SUSPENDED:
		/* Do nothing in the aborted and suspended states */
		break;
	default: /* FLSTST_UNINIT  or invalid state, indicate a failure */
		/* Indicate a diagnostic event failure, either the self test failed to complete and trigger the ISR or this module is improperly integrated */
		(void)FLSTST_REPORTERRORSTATUS(FLSTST_E_SELFTEST_FAILURE, FLSTST_E_SELFTEST_INFO, FLSTST_EVENT_FAILED);
		break;
	}
}

#if (STD_ON == FLSTST_TEST_COMPLETE_NOTIFICATION_SUPPORTED)	/* [FlsTst159] */
/*****************************************************************************
  * Name:        FlsTst_TestCompleted
  * Description: Notification handling provided at the end of a background interval
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, FLSTST_CODE) FlsTst_TestCompleted( void )
{
	if(NULL_PTR != (*FlsTst_Config->notifFcn))	/* [FlsTst076] */
	{
		(*FlsTst_Config->notifFcn)();
	}
}
#endif



/* Local Functions (Private to FlsTst and FlsTst_Irq)*/
/*****************************************************************************
  * Name:        SetupBgndBlk
  * Description: Configure peripherals for background block range and start
  * Inputs:      config - pointer to configuration structure
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, FLSTST_CODE) SetupBgndBlk( FlsTst_MemBlockType config )
{
	/* Disable Flash Test DMA block */
	Dma_DisableFlsTstBlock();
	
	/* Set up Flash Test DMA Block */
	Dma_SetupFlsTstBlock((uint32)config.crcPtr,
						 (uint32)config.startPtr,
						 config.dmaFrameCnt,
						 config.dmaElementCnt);

	/* Perform CRC channel Restart Procedure from TRM */
	CRCCTRLREG->CRC_CTRL0 |= D_CRCCH1SWRESET_CNT_U32; /* Hold Ch1 in Sw Reset, while leaving other contents */

	CRCCTRLREG->CRC_PCOUNT_REG1 = config.seclength & 0x000FFFFFUL;	/* Number of 64-bit words in the CRC sector -- Max value is 1048575 (20 bit field in register) */
	CRCCTRLREG->CRC_SCOUNT_REG1 = config.secnum;	/* Number of sectors per block */

	CRCCTRLREG->CRC_CTRL2 &= ~(0xFFUL);	/* Reset Ch1 to Data Capture mode to allow writing of seed value */
	CRCCTRLREG->PSA_SIGREGL1 = config.crcInitL;	/* Write Ch1 CRC Init/Seed value Low 32 bits*/
	CRCCTRLREG->PSA_SIGREGH1 = config.crcInitH;	/* Write Ch1 CRC Init/Seed value  High 32 bits*/
	CRCCTRLREG->CRC_CTRL2 |= 0x01U;	/* Place Ch1 into AUTO mode */
	CRCCTRLREG->CRC_CTRL0 &= (~D_CRCCH1SWRESET_CNT_U32); /* Release Ch1 from Sw Reset */
	
	/* Enable Flash Test DMA block */
	Dma_EnableFlsTstBlock();
}

#define FLSTST_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */

