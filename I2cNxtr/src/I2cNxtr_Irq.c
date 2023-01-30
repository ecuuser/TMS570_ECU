/***********************************************************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : I2cNxtr_Irq.c
* Module Description: I2C Driver: Nexteer implementation.
* Product           : Gen II Plus - EA3.0
* Author            : Jared Julien
*
* Notes:
* Presently this module does not follow Autosar API implementations since no standards were released at the time
* this component was created.
*
***********************************************************************************************************************/
/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/
/* Version Control:
 * Date Created:      Thur Aug 8 11:20:41 2013 %
 * %version:          4 %
 * %derived_by:       jzk9cc %
 * %date_modified:    Mon Feb 24 13:45:45 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 08/08/13  1        Jared     New driver for initial use with DigColPosSnsr component                         8850
 * 09/20/13  2        Jared     Added module short name to I2cTransfer module level variable                    8850
 * 10/07/13  3        Blake     Added Metrics hooks                                                             9288
 * 02/24/14  4        Rijvi     Added check point for receiver overrun in side the ISR                          11479
 */
/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/
#include "I2cNxtr.h"
#include "I2cNxtr_Cfg.h"
#include "Os.h"
#include "Metrics.h"


/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/

/*======================================================================================================================
 * Function: Isr_I2c
 * --------------------------------------------------------------------------------------------------------------------
 * Interrupt function for I2C1.  Fires when any I2C1 interrupt occurs and IVR must be consulted to determine the cause
 * of the interrupt.  This function then calls I2c_Notification and passes the appropriate flag to indicate the
 * interrupt cause.  I2c_Notification is defined externally and configured through I2cNxtr_Cfg.h.
 *
 * At this level, the only process that is automated is the transmission and reception of data upon which the
 * corresponding transmit notification fires when transmission is complete.  All other interrupt causes are passed
 * along to the configured I2c_Notification() function.
 *
 * Inputs:  N/A
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
ISR(Isr_I2c)
{
	VAR(uint32, AUTOMATIC) Vector_Cnt_T_u32;
	VAR(uint8, AUTOMATIC) RxData_Cnt_T_u08;
	
	Metrics_TaskStart(D_I2CNXT_CNT_U08);

	Vector_Cnt_T_u32 = I2c_GetIntVect(D_I2CREG_STRCPTR);

	switch (Vector_Cnt_T_u32)
	{
	case 1U:
		/*****[ Arbitration-Lost Interrupt ]**********************************/
		/* Generated when the I2C module has lost an arbitration contest with
		 * another master-transmitter.
		 */
		I2c_Notification((uint16)I2C_AL_INT);
		break;

	case 2U:
		/*****[ No-Acknowledge Interrupt ]************************************/
		/* Generated when the master I2C does not receive an acknowledge from
		 * the receiver.
		 */
		I2c_Notification((uint16)I2C_NACK_INT);
		break;

	case 3U:
		/*****[ Register Access Ready Interrupt ]*****************************/
		/* Generated when the previously programmed address, data and command
		 * have been performed and the status bits have been updated.  The
		 * interrupt is used to notify the device that the I2C registers are
		 * ready to be accessed.
		 */
		I2c_Notification((uint16)I2C_ARDY_INT);
		break;

	case 4U:
		/*****[ Receive Data Ready Interrupt ]********************************/
		/* Generated when the received data in the receive-shift register
		 * (I2CSR) has been copied into the data receive register (I2CDRR).
		 * The RXRDY bit can also be polled by the device to determine when to
		 * read the received data in the I2CDRR.
		 */
		/* Receiver overrun condition is checked before read byte from DRR register  */
		if( (I2c_GetStatus(D_I2CREG_STRCPTR) & I2C_RECV_OVERRUN) != 0U)
		{
			I2c_Notification((uint16)I2C_RECV_OVERRUN);	
		}
		/* Always read byte from DRR register to clear RX buffer */
		RxData_Cnt_T_u08 = I2c_ReceiveByte(D_I2CREG_STRCPTR);

		if (I2cNxtr_I2cTransfer_Cnt_M_str.Length_Cnt_u32 > 0U)
		{
			/* Receive next byte */
			*I2cNxtr_I2cTransfer_Cnt_M_str.DataPtr_Cnt_u08 = RxData_Cnt_T_u08;
			I2cNxtr_I2cTransfer_Cnt_M_str.DataPtr_Cnt_u08++;
			I2cNxtr_I2cTransfer_Cnt_M_str.Length_Cnt_u32--;
		}
		break;

	case 5U:
		/*****[ Transmit Data Ready Interrupt ]*******************************/
		/* Generated when the transmitted data has been copied from the data
		 * transmit register (I2CDXR) into the transmit-shift register
		 * (I2CXSR).  The TXRDY bit can also be polled by the device to
		 * determine when to  write the next data into I2CDXR
		 */
		I2cNxtr_I2cTransfer_Cnt_M_str.Length_Cnt_u32--;
		if (I2cNxtr_I2cTransfer_Cnt_M_str.Length_Cnt_u32 > 0U)
		{
			/* Transmit next byte */
			I2c_SendByte(D_I2CREG_STRCPTR, *I2cNxtr_I2cTransfer_Cnt_M_str.DataPtr_Cnt_u08);
			I2cNxtr_I2cTransfer_Cnt_M_str.DataPtr_Cnt_u08++;
		}
		else
		{
			/* Transmission Completed */
			I2c_SetStatus(D_I2CREG_STRCPTR, (uint16)I2C_TX_INT);
			I2c_Notification((uint16)I2C_TX_INT);
		}
		break;

	case 6U:
		/*****[ Stop Condition Detect Interrupt ]*****************************/
		/* Generated when a STOP condition has been detected.
		 */
		I2c_Notification((uint16)I2C_SCD_INT);
		break;

	case 7U:
		/*****[ Address as Slave Interrupt ]**********************************/
		/* Generated when the I2C has recognized its own slave address or an
		 * address of all zeroes.
		 */
		I2c_Notification((uint16)I2C_AAS_INT);
		break;

	default:
		/*****[ Phantom Interrupt ]*******************************************/
		/* Clear flags and return
		 */
		I2c_SetStatus(D_I2CREG_STRCPTR, 0x07FFU);
		break;
	}
	
	Metrics_TaskEnd(D_I2CNXT_CNT_U08);
}

/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/
