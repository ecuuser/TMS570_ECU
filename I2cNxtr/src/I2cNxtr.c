/***********************************************************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : I2cNxtr.c
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
 * %version:          2 %
 * %derived_by:       kzdyfh %
 * %date_modified:    Mon Aug 26 13:39:03 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 08/08/13  1        Jared     New driver for initial use with DigColPosSnsr component                      8850
 * 06/03/14  2        Jared     Updated to correct A6836 by stobing I2C SCL on init                          12004
 */
/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/
#include "I2cNxtr.h"
#include "Std_Types.h"
#include "interrupts.h"
#include "I2cNxtr_Cfg.h"
#include "SystemTime.h"


#define D_CLKRESETPULSES_CNT_U08	18U
#define D_CLOCKPERIOD_US_U08		5U


#define I2CNXTR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
VAR(I2cTransferType, I2CNXTR_VAR) I2cNxtr_I2cTransfer_Cnt_M_str;
#define I2CNXTR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */



/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/

/*======================================================================================================================
 * Function: I2c_Init
 * --------------------------------------------------------------------------------------------------------------------
 * This function initializes the I2C module.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_Init(CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str)
{
	VAR(uint8, AUTOMATIC) PulseCount_Cnt_T_u08;
	VAR(uint32, AUTOMATIC) StartTime_uS_T_u32;
	VAR(uint16, AUTOMATIC) ElapsedTime_uS_T_u16;

	/* The following block of code is responsible for providing clocks on the SCL line after any reset   This step is
	 * performed to reset the state machine in the connected device(s) in the event that the reset occurred
	 * mid-transmission.  This is the only way to reset the HWA sensor used over I2C in such an event as there is no
	 * hardware to reset the device save pulling power to the sensor.
	 */
	I2cRegPtr_Cnt_T_str->DOUT |= 1U;    /* start with SCL high as that's the default I2C state */
	I2cRegPtr_Cnt_T_str->DIR |= 1U;     /* set SCL as output */
	I2cRegPtr_Cnt_T_str->DIR &= (uint8)(~2U);  /* make SDA high impedance */
	I2cRegPtr_Cnt_T_str->FUN |= 1U;     /* take control of SCL and SDA as GPIO */
	for (PulseCount_Cnt_T_u08 = 0U; PulseCount_Cnt_T_u08 < (D_CLKRESETPULSES_CNT_U08 * 2U); PulseCount_Cnt_T_u08 += 1U)
	{
		/* toggle state of SCL */
		I2cRegPtr_Cnt_T_str->DOUT ^= 1U;

		/* delay for one clock cycle */
		GetSystemTime_uS_u32(&StartTime_uS_T_u32);
		ElapsedTime_uS_T_u16 = 0U;
		while (ElapsedTime_uS_T_u16 < D_CLOCKPERIOD_US_U08)
		{
			DtrmnElapsedTime_uS_u16(StartTime_uS_T_u32, &ElapsedTime_uS_T_u16);
		}
	}
	I2cRegPtr_Cnt_T_str->FUN &= (uint8)(~1U);  /* return SCL and SDA to I2C control from GPIO */

	/* I2C out of reset */
	I2cRegPtr_Cnt_T_str->MDR = 0U;   /* I2C reset */

	/* set prescale - 100khz */
	I2cRegPtr_Cnt_T_str->PSC = 9U;

	/* set clock rate */
	I2cRegPtr_Cnt_T_str->CLKH =  35U;
	I2cRegPtr_Cnt_T_str->CLKL =  35U;

	/* Set I2C extended mode */
	I2cRegPtr_Cnt_T_str->EMDR = 0U;
	I2cRegPtr_Cnt_T_str->DRR = 0x0000U;
	I2cRegPtr_Cnt_T_str->CNT = 2U;

	/* Disable all interrupts */
	I2cRegPtr_Cnt_T_str->IMR = 0U;

	/* set i2c pins functional mode */
	I2cRegPtr_Cnt_T_str->FUN = 0U;

	/* set i2c pins default output value */
	I2cRegPtr_Cnt_T_str->DOUT = 0U  /* sda pin */
							  | 0U; /* scl pin */

	/* set i2c pins output direction */
	I2cRegPtr_Cnt_T_str->DIR = (uint8)(1U << 1U)   /* sda pin */
							 | (uint8)(1U);       /* scl pin */

	/* set i2c pins open drain enable */
	I2cRegPtr_Cnt_T_str->ODR = (uint8)(1U << 1U)   /* sda pin */
							 | (uint8)(1U);       /* scl pin */

	/* set i2c pins pullup/pulldown enable */
	I2cRegPtr_Cnt_T_str->PD = (uint8)(0U << 1U)  /* sda pin */
							| (uint8)(0U);      /* scl pin */

	/* set i2c pins pullup/pulldown select */
	I2cRegPtr_Cnt_T_str->PSL = (uint8)(0U << 1U)    /* sda pin */
							 | (uint8)(0U);        /* scl pin */

	/* set interrupt enable */
	I2cRegPtr_Cnt_T_str->IMR = (uint8)(0U << 6U)  /* Address as slave interrupt      */
							 | (uint8)(0U << 5U)  /* Stop Condition detect interrupt */
							 | (uint8)(0U << 4U)  /* Transmit data ready interrupt   */
							 | (uint8)(0U << 3U)  /* Receive data ready interrupt    */
							 | (uint8)(0U << 2U)  /* Register Access ready interrupt */
							 | (uint8)(0U << 1U)  /* No Acknowledgement interrupt    */
							 | (uint8)(0U);      /* Arbitration Lost interrupt      */

	/* initialize global transfer variables */
	I2cNxtr_I2cTransfer_Cnt_M_str.Mode_Cnt_b32   = 0U;
	I2cNxtr_I2cTransfer_Cnt_M_str.Length_Cnt_u32 = 0U;

	EnableI2CInterrupt();
}



/*======================================================================================================================
 * Function: I2c_Enable
 * --------------------------------------------------------------------------------------------------------------------
 * Call this function to enable the I2C interface after configuration is completed.  The function takes the I2C
 * peripheral out of reset.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_Enable(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
)
{
	I2cRegPtr_Cnt_T_str->MDR |= I2C_RESET_OUT;
}


/*======================================================================================================================
 * Function: I2c_Reset
 * --------------------------------------------------------------------------------------------------------------------
 * Call this function to disable the I2C interface and reset all registers to their initial values.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_Reset(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
)
{
	I2cRegPtr_Cnt_T_str->MDR &= (uint32)(~I2C_RESET_OUT);
}


/*======================================================================================================================
 * Function: I2c_SetupMasterTransmit
 * --------------------------------------------------------------------------------------------------------------------
 * Put the I2C peripheral into master transmit mode, set the slave address and transfer length and generate a start
 * condition on the bus.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_SetupMasterTransmit(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint8, AUTOMATIC) SlaveAddress_Cnt_T_u08,
	VAR(uint16, AUTOMATIC) DataLength_Cnt_T_u16
)
{
	/* set i2c slave address */
	I2cRegPtr_Cnt_T_str->SAR = SlaveAddress_Cnt_T_u08;

	/* Set the number of bytes to be sent */
	I2cRegPtr_Cnt_T_str->CNT = DataLength_Cnt_T_u16;

	/* Set TMS570 as transmitter in master mode & generate start condition*/
	I2cRegPtr_Cnt_T_str->MDR = (uint32)(I2C_RESET_OUT | I2C_MASTER | I2C_TRANSMITTER | I2C_START_COND);
}


/*======================================================================================================================
 * Function: I2c_SetupMasterReceive
 * --------------------------------------------------------------------------------------------------------------------
 * Put the I2C peripheral into master transmit mode, set the slave address and transfer length and generate a start
 * condition on the bus.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_SetupMasterReceive(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint8, AUTOMATIC) SlaveAddress_Cnt_T_u08,
	VAR(uint16, AUTOMATIC) DataLength_Cnt_T_u16
)
{
	/* set i2c slave address */
	I2cRegPtr_Cnt_T_str->SAR = SlaveAddress_Cnt_T_u08;

	/* Set the number of bytes to be sent */
	I2cRegPtr_Cnt_T_str->CNT = DataLength_Cnt_T_u16;

	/* Set TMS570 as receiver in master mode & generate start condition.  Setting the I2C_STOP_COND bit when CNT > 0
	 * will cause automatic generation of an I2C STOP condition when CNT decrements to 0. */
	I2cRegPtr_Cnt_T_str->MDR = (uint32)(I2C_RESET_OUT | I2C_MASTER | I2C_START_COND | I2C_STOP_COND);
}


/*======================================================================================================================
 * Function: I2c_SwitchMasterReceive
 * --------------------------------------------------------------------------------------------------------------------
 * Switch the I2C peripheral to master receiver mode after the device has already been in master transmitter mode.
 * Use this function after sending data to the device.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_SwitchMasterReceive(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint16, AUTOMATIC) DataLength_Cnt_T_u16
)
{
	/* Set the number of bytes to be sent */
	I2cRegPtr_Cnt_T_str->CNT = DataLength_Cnt_T_u16;

	/* Set TMS570 as receiver in master mode & generate start condition.  Setting the I2C_STOP_COND bit when CNT > 0
	 * will cause automatic generation of an I2C STOP condition when CNT decrements to 0. */
	I2cRegPtr_Cnt_T_str->MDR = (uint32)(I2C_RESET_OUT | I2C_MASTER | I2C_START_COND | I2C_STOP_COND);
}


/*======================================================================================================================
 * Function: I2c_SetCount
 * --------------------------------------------------------------------------------------------------------------------
 * This command will set the number of bytes the ECU is to expect during a read service. Note, in Repeat mode, this
 * is a don't care value.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *          Count_Cnt_T_u16 - Number of bytes before STOP condition is generated.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_SetCount(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint16, AUTOMATIC) Count_Cnt_T_u16
)
{
	I2cRegPtr_Cnt_T_str->CNT = Count_Cnt_T_u16;
}


/*======================================================================================================================
 * Function: I2c_SetOwnAdd
 * --------------------------------------------------------------------------------------------------------------------
 * Set our I2C slave address for use with slave I2C communication.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *          Address_Cnt_T_u16 - I2C slave address - maximum value depends on addressing mode configured (7/10 bit).
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_SetOwnAdd(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint16, AUTOMATIC) Address_Cnt_T_u16
)
{
	I2cRegPtr_Cnt_T_str->OAR = Address_Cnt_T_u16;
}


/*======================================================================================================================
 * Function: I2c_SetSlaveAdd
 * --------------------------------------------------------------------------------------------------------------------
 * Set outgoing slave address used with I2C master communications.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *          Address_Cnt_T_u16 - I2C slave address - maximum value depends on addressing mode configured (7/10 bit).
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_SetSlaveAdd(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint16, AUTOMATIC) Address_Cnt_T_u16
)
{
	I2cRegPtr_Cnt_T_str->SAR = Address_Cnt_T_u16;
}


/*======================================================================================================================
 * Function: I2c_SetFunctional
 * --------------------------------------------------------------------------------------------------------------------
 * Change functional behaviour of pins at runtime this allows to dynamically change the functionality of the i2c pins
 * between functional and GIO mode.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *          Port_Cnt_T_u08 - Value to write to FUN register:
 *              0 - Functional
 *              1 - GIO Mode
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_SetFunctional(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint8, AUTOMATIC) Port_Cnt_T_u08
)
{
	/* also known as FCN register */
	I2cRegPtr_Cnt_T_str->FUN = Port_Cnt_T_u08;
}


/*======================================================================================================================
 * Function: I2c_SetBaudrate
 * --------------------------------------------------------------------------------------------------------------------
 * Change baudrate at runtime.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *          Baud_Hz_T_u32 - Baudrate in Hertz.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_SetBaudrate(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint32, AUTOMATIC) Baud_Hz_T_u32
)
{
	VAR(uint32, AUTOMATIC) Prescale_Uls_T_u32;
	VAR(float32, AUTOMATIC) Vclk_Hz_T_f32;

	Vclk_Hz_T_f32 = D_VCLK_HZ_F32;

	Prescale_Uls_T_u32 = (uint32)(Vclk_Hz_T_f32 / (float32)((Baud_Hz_T_u32 * 16U) - 1U)) & 0x00FFFFFFU;
	I2cRegPtr_Cnt_T_str->PSC = Prescale_Uls_T_u32;
}


/*======================================================================================================================
 * Function: I2c_IsTxReady
 * --------------------------------------------------------------------------------------------------------------------
 * Checks to see if the TX buffer ready flag is set, returns FALSE is flags not set otherwise will return TRUE.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *
 * Output:  TRUE if TX buffer ready flag is set, else FALSE.
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(boolean, I2CNXTR_CODE) I2c_IsTxReady(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
)
{
	return (I2cRegPtr_Cnt_T_str->STR & I2C_TX_INT) != 0U;
}


/*======================================================================================================================
 * Function: I2c_SendByte
 * --------------------------------------------------------------------------------------------------------------------
 * Sends a single byte in polling mode, will wait in the routine until the transmit buffer is empty before sending
 * the byte.  Use i2cIsTxReady to check for TX buffer empty before calling i2cSendByte to avoid waiting.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *          Byte_Cnt_T_u08 - Single byte to transfer.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_SendByte(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint8, AUTOMATIC) Byte_Cnt_T_u08
)
{
	I2cRegPtr_Cnt_T_str->DXR = Byte_Cnt_T_u08;
}


/*======================================================================================================================
 * Function: I2c_Send
 * --------------------------------------------------------------------------------------------------------------------
 * Send a block of data pointed to by 'data' and 'length' bytes long.  If interrupts have been enabled the data is sent
 * using interrupt mode, otherwise polling mode is used.  In interrupt mode transition of the first byte is started
 * and the routine returns immediately, i2cSend must not be called again until the transfer is complete, when the
 * i2cNotification callback will be called.  In polling mode, i2cSend will not return  until the transfer is complete.
 *
 * Note:  If data word is less than 8 bits, then the data must be left aligned in the data byte.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *          Length_Cnt_T_u32 - Number of bytes to transmit.
 *          DataPtr_Cnt_T_u08 - Pointer to buffer holding data to be transferred.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_Send(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint32, AUTOMATIC) Length_Cnt_T_u32,
	P2VAR(uint8, AUTOMATIC, AUTOMATIC) DataPtr_Cnt_T_u08
)
{
	if ((I2cNxtr_I2cTransfer_Cnt_M_str.Mode_Cnt_b32 & I2C_TX_INT) != 0U)
	{
		/* Use Interrupt Mode */
		I2cNxtr_I2cTransfer_Cnt_M_str.Length_Cnt_u32 = Length_Cnt_T_u32;
		I2cNxtr_I2cTransfer_Cnt_M_str.DataPtr_Cnt_u08 = DataPtr_Cnt_T_u08;

		/* start transmit by sending first byte */
		I2cRegPtr_Cnt_T_str->DXR = *I2cNxtr_I2cTransfer_Cnt_M_str.DataPtr_Cnt_u08;
		I2cNxtr_I2cTransfer_Cnt_M_str.DataPtr_Cnt_u08++;
		I2cRegPtr_Cnt_T_str->IMR |= I2C_TX_INT;
	}
	else
	{
		/* Use Polling Mode */
		while (Length_Cnt_T_u32 > 0U)
		{
			Length_Cnt_T_u32--;
			while ((I2cRegPtr_Cnt_T_str->STR & I2C_TX_INT) == 0U)
			{
				/* wait */
			}
			I2cRegPtr_Cnt_T_str->DXR = *DataPtr_Cnt_T_u08;
			DataPtr_Cnt_T_u08++;
		}
	}
}


/*======================================================================================================================
 * Function: I2c_IsRxReady
 * --------------------------------------------------------------------------------------------------------------------
 * Checks to see if the RX buffer full flag is set, returns FALSE is flag is not set otherwise will return TRUE.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *
 * Output:  TRUE if RX buffer full flag is set, else FALSE.
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(boolean, I2CNXTR_CODE) I2c_IsRxReady(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
)
{
	return (I2cRegPtr_Cnt_T_str->STR & I2C_RX_INT) != 0U;
}


/*======================================================================================================================
 * Function: I2c_RxError
 * --------------------------------------------------------------------------------------------------------------------
 * Returns the Rx framing, overun and parity errors flags, also clears the error flags before returning.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *
 * Output:  Bitfield containing AL and NACK flags if set.
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(uint32, I2CNXTR_CODE) I2c_RxError(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
)
{
	VAR(uint32, AUTOMATIC) Status_Cnt_T_b32 = I2cRegPtr_Cnt_T_str->STR & (uint32)(I2C_AL_INT | I2C_NACK_INT);

	I2cRegPtr_Cnt_T_str->STR = (uint32)(I2C_AL_INT | I2C_NACK_INT);

	return Status_Cnt_T_b32;
}


/*======================================================================================================================
 * Function: I2c_ReceiveByte
 * --------------------------------------------------------------------------------------------------------------------
 * Receives a single byte in polling mode.  If there is not a byte in the receive buffer the routine will wait
 * until one is received.   Use i2cIsRxReady to check to see if the buffer is full to avoid waiting.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *
 * Output:  Single received byte from the I2C RX buffer.
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(uint8, I2CNXTR_CODE) I2c_ReceiveByte(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
)
{
	return (uint8)I2cRegPtr_Cnt_T_str->DRR;
}


/*======================================================================================================================
 * Function: I2c_SetRecv
 * --------------------------------------------------------------------------------------------------------------------
 * Receive a block of 'length' bytes long and place it into the data buffer pointed to by 'data'.  If interrupts have
 * been enabled the data is received using interrupt mode, otherwise polling mode is used.  In interrupt mode receive
 * is setup and the routine returns immediately, i2cReceive must not be called again until the transfer is complete,
 * when the i2cNotification callback will be called.  In polling mode, i2cReceive will not return  until the transfer
 * is complete.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *          Length_Cnt_T_u32 - Length of data to receive.
 *          DataPtr_Cnt_T_u08 - Pointer to buffer to gold received data.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_SetRecv(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint32, AUTOMATIC) Length_Cnt_T_u32,
	P2VAR(uint8, AUTOMATIC, AUTOMATIC) DataPtr_Cnt_T_u08
)
{
	if ((I2cRegPtr_Cnt_T_str->IMR & I2C_RX_INT) != 0U)
	{
		/* clear error flags */
		I2cRegPtr_Cnt_T_str->STR = (uint32)(I2C_AL_INT | I2C_NACK_INT);

		I2cNxtr_I2cTransfer_Cnt_M_str.Length_Cnt_u32 = Length_Cnt_T_u32;
		I2cNxtr_I2cTransfer_Cnt_M_str.DataPtr_Cnt_u08 = DataPtr_Cnt_T_u08;
	}
	else
	{
		while (Length_Cnt_T_u32 > 0U)
		{
			Length_Cnt_T_u32--;
			while ((I2cRegPtr_Cnt_T_str->STR & I2C_RX_INT) == 0U)
			{
				/* wait */
			}
			*DataPtr_Cnt_T_u08 = (uint8)I2cRegPtr_Cnt_T_str->DRR;
			DataPtr_Cnt_T_u08++;
		}
	}
}


/*======================================================================================================================
 * Function: I2c_SetDirection
 * --------------------------------------------------------------------------------------------------------------------
 * Set port direction.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *          Dir_Cnt_T_u08 - Value to write to PCDIR register.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_SetDirection(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint8, AUTOMATIC) Dir_Cnt_T_u08
)
{
	I2cRegPtr_Cnt_T_str->DIR = Dir_Cnt_T_u08;
}


/*======================================================================================================================
 * Function: I2c_SetBit
 * --------------------------------------------------------------------------------------------------------------------
 * Writes a value to the specified pin of the i2c port.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *          Bit_Cnt_T_u08 - Number (0-18) that specifies the bit to be written to.
 *          Value_Cnt_T_u08 - Binary value to write to the port pin.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_SetBit(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint8, AUTOMATIC) Bit_Cnt_T_u08,
	VAR(uint8, AUTOMATIC) Value_Cnt_T_u08
)
{
	if (Value_Cnt_T_u08 != 0U)
	{
		I2cRegPtr_Cnt_T_str->SET = (uint32)((uint32)1U << Bit_Cnt_T_u08);
	}
	else
	{
		I2cRegPtr_Cnt_T_str->CLR = (uint32)((uint32)1U << Bit_Cnt_T_u08);
	}
}


/*======================================================================================================================
 * Function: I2c_GetBit
 * --------------------------------------------------------------------------------------------------------------------
 * Reads a the current value from the specified pin of the i2c port.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *          Bit_Cnt_T_u08 - Number (0-18) that specifies the bit to be read from.
 *
 * Output:  State of read bit.
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(uint32, I2CNXTR_CODE) I2c_GetBit(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint8, AUTOMATIC) Bit_Cnt_T_u08
)
{
	return (I2cRegPtr_Cnt_T_str->DIN >> Bit_Cnt_T_u08) & 1U;
}


/*======================================================================================================================
 * Function: I2c_EnableNotification
 * --------------------------------------------------------------------------------------------------------------------
 * Enable selected I2C interrupts.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *          Flags_Cnt_T_b32 - Interrupts to be enabled, can be stored value of:
 *              I2C_FE_INT    - framming error,
 *              I2C_OE_INT    - overrun error,
 *              I2C_PE_INT    - parity error,
 *              I2C_RX_INT    - receive buffer ready,
 *              I2C_TX_INT    - transmit buffer ready,
 *              I2C_WAKE_INT  - wakeup,
 *              I2C_BREAK_INT - break detect
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_EnableNotification(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint32, AUTOMATIC) Flags_Cnt_T_b32
)
{
	I2cNxtr_I2cTransfer_Cnt_M_str.Mode_Cnt_b32 |= (Flags_Cnt_T_b32 & I2C_TX_INT);
	I2cRegPtr_Cnt_T_str->IMR = (Flags_Cnt_T_b32 & (uint32)(~I2C_TX_INT));
}


/*======================================================================================================================
 * Function: I2c_DisableNotification
 * --------------------------------------------------------------------------------------------------------------------
 * Disable selected I2C interrupts.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *          Flags_Cnt_T_b32 - Interrupts to be disabled, can be stored value of:
 *              I2C_FE_INT    - framming error,
 *              I2C_OE_INT    - overrun error,
 *              I2C_PE_INT    - parity error,
 *              I2C_RX_INT    - receive buffer ready,
 *              I2C_TX_INT    - transmit buffer ready,
 *              I2C_WAKE_INT  - wakeup,
 *              I2C_BREAK_INT - break detect
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_DisableNotification(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint32, AUTOMATIC) Flags_Cnt_T_b32
)
{
	I2cNxtr_I2cTransfer_Cnt_M_str.Mode_Cnt_b32 &= ~(Flags_Cnt_T_b32 &  I2C_TX_INT);
	I2cRegPtr_Cnt_T_str->IMR = (Flags_Cnt_T_b32 & (uint32)(~I2C_TX_INT));
}


/*======================================================================================================================
 * Function: I2c_GenStartCond
 * --------------------------------------------------------------------------------------------------------------------
 * This function will update the mode register to generate a start condition on the I2C bus.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_GenStartCond(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
)
{
	I2cRegPtr_Cnt_T_str->MDR |= I2C_START_COND;
}


/*======================================================================================================================
 * Function: I2c_GenStopCond
 * --------------------------------------------------------------------------------------------------------------------
 * This function will update the mode register to generate a stop condition on the I2C bus.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_GenStopCond(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
)
{
	I2cRegPtr_Cnt_T_str->MDR |= I2C_STOP_COND;
}


/*======================================================================================================================
 * Function: I2c_GetIntVect
 * --------------------------------------------------------------------------------------------------------------------
 * Return the interrupt vector register.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *
 * Output:  Interrupt vector flag register.
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(uint8, I2CNXTR_CODE) I2c_GetIntVect(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
)
{
	return (uint8)I2cRegPtr_Cnt_T_str->IVR;
}


/*======================================================================================================================
 * Function: I2c_GetStatus
 * --------------------------------------------------------------------------------------------------------------------
 * Return the status register.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *
 * Output:  Status flag register.
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(uint16, I2CNXTR_CODE) I2c_GetStatus(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
)
{
	return (uint16)I2cRegPtr_Cnt_T_str->STR;
}


/*======================================================================================================================
 * Function: I2c_SetStatus
 * --------------------------------------------------------------------------------------------------------------------
 * Return the status register.
 *
 * Inputs:  I2cRegPtr_Cnt_T_str - Pointer to I2C register structure.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, I2CNXTR_CODE) I2c_SetStatus(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint16, AUTOMATIC) Status_Cnt_T_u16
)
{
	I2cRegPtr_Cnt_T_str->STR = Status_Cnt_T_u16;
}


/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/
