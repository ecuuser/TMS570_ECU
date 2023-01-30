/**********************************************************************
*
*	C %name:		FlsTst_Irq.c %
*	Instance:		sag_EPS_1
*	Description:	
*	%created_by:	czgng4 %
*	%date_created:	Sun Sep 30 17:22:22 2012 %
*
**********************************************************************/

#define FLSTST_PRIVATEDEFS /* Enable Private definition exposure */
#include "FlsTst.h"
#include "Os.h"
#include "crc_regs.h"


#define FLSTST_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */



/* Interrupt Offsets */
#define D_CRCPHANTOMIRQOFST_CNT_U16		0x00U
#define D_CRCCH1FAILIRQOFST_CNT_U16		0x01U

/*****************************************************************************
  * Name:        FlsTst_CrcIrq
  * Description: Nexteer extension to the AUTOSAR specification.  Handles CRC failures detected by CRC Peripheral
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
ISR(FlsTst_CrcIrq)
{
	/* Clear the CRC Current Sector Register by Reading it.  This prevents the overrun interrupt flag from setting */
	volatile VAR(uint32, AUTOMATIC)CurSec_Cnt_u32  = CRCCTRLREG->CRC_CURSEC_REG1;
	
	/* Reading CRC_INT_OFFSET_REG per TRM automatically clears the associated interrupt flag, but has not been observed to work */
	switch(CRCCTRLREG->CRC_INT_OFFSET_REG){
	case D_CRCCH1FAILIRQOFST_CNT_U16:
		/* Manually clear the interrupt status flag for this condition */
		CRCCTRLREG->CRC_STATUS = 0x02;

		/* Check to see if SelfTest caused ISR */
		if(FLSTST_SLFTSTRUNNING == FlsTst_SelfTestState)
		{
			FlsTst_SelfTestState = FLSTST_SLFTSTPASS;
			FlsTst_State = FLSTST_INIT;	/* Initialization completed*/
			FLSTST_REPORTERRORSTATUS(FLSTST_E_SELFTEST_FAILURE, 0x00U, FLSTST_EVENT_PASSED);
			FLSTST_REPORTERRORSTATUS(FLSTST_E_MPU_FAILURE, 0x00U, FLSTST_EVENT_PASSED);
			/* Initialize to test passed, any failures will over-write this status */
			FLSTST_REPORTERRORSTATUS(FLSTST_E_FLSTST_FAILURE, 0x00U, FLSTST_EVENT_PASSED);
			FLSTST_REPORTERRORSTATUS(FLSTST_E_UNEXPECTEDIRQ_FAILURE, 0x00U, FLSTST_EVENT_PASSED);
		}
		else
		{
			/* Indicate a diagnostic event failure */
			FLSTST_REPORTERRORSTATUS(FLSTST_E_FLSTST_FAILURE, 0x00U, FLSTST_EVENT_FAILED);

			/* Record Block Failure in Error Info, NOTE: when Fgnd blocks are supported the following will need to change to properly record the active test block */
			FlsTst_ErrorDetails.blocksfailed |= (1UL << FlsTst_BgndTestBlock);
			FlsTst_CurrBgndTestResult = FLSTST_RESULT_NOT_OK;
			/* The next main function call will determine how to proceed */
		}
		break;
	case D_CRCPHANTOMIRQOFST_CNT_U16:
		/* Nothing to do for phantom interrupt case */
		break;
	default:
		/* Set unexpected interrupt failure event */
		FLSTST_REPORTERRORSTATUS(FLSTST_E_UNEXPECTEDIRQ_FAILURE, FLSTST_E_FLSTST_INFO, FLSTST_EVENT_FAILED);
		break;
	}

}

#define FLSTST_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */
