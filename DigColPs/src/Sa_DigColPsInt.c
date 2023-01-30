/***********************************************************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Sa_DigColPsInt.c
* Module Description: Digital Column Position Sensor I2C Interface
* Product           : Gen II Plus - EA3.0
* Author            : Jared Julien
*
***********************************************************************************************************************/
/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/
/* Version Control:
 * Date Created:      Thur Aug 8 11:20:41 2013 %
 * %version:          7 %
 * %derived_by:       hz3w2h %
 * %date_modified:    Thu Feb 27 08:47:52 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 08/08/13  1        Jared     New driver for initial use with DigColPs component                            8850
 * 02/27/14  2        Rijvi     Updated to FDD v003                                                           10979
 * 03/20/14  3        Rijvi     Update to FDD rev.004                                                         11266
 *                              Update to FDD rev.005 (anomaly# 6471)                                         11594
 *                              Fix Anomaly# 6089                                                             11611
 * 03/26/14  4        Rijvi     Updated to FDD rev.006                                                        11641
 * 05/10/14  5        Selva     Updated for FDD rev 007                                                       11909
 * 06/30/14  6        Jared     Updated to FDD rev 008 (Dual Spur design)                                     12145
 * 09/05/14  7        Vishnu    Updated for FDD rev 12.0 (DSS Compatibility)								  12427
 */
/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/

#include "Rte_Sa_DigColPs.h"

/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/
#include "Sa_DigColPsInt.h"
#include "I2cNxtr.h"
#include "I2cNxtr_Cfg.h"
#include "SystemTime.h"
#include "CalConstants.h"

/* PRQA S 4395 EOF 
* MISRA-C: 2004 Rule 10.4: This deviation is required for library macros.  The rule is suppressed for the entire file */

/* PRQA S 303 EOF 
* MISRA-C: 2004 Rule 11.3:This deviation is required for register access.  
If there is frequency of usage throughout the file then rule can be suppressed for the entire file. 
Annotation at each deviation unecessarily clutters the file. */

/* MISRA-C:2004 Rule 8.7: Deviation required for the display variables because of memory map */ 

#define D_COLSENSOR_CNT_U08         0U
#define D_SPURSENSOR_CNT_U08        1U

#define D_CLEARSTATUSBITS_CNT_U16   0x0007U
#define D_RESETCMD_CNT_U16          0x0746U
#define D_EXTREADADDRREGCMD_CNT_U16 0x0307U
#define D_EXTREADCTRLREGCMD_CNT_U16 0x8000U


#define D_NACKOCCURRED_CNT_U08      0x02U
#define D_BBSEQERR_CNT_U08          0x04U
#define D_RECVOVERRUNERR_CNT_U08    0x08U
#define D_TRANSNOTCOMP_CNT_U08      0x10U
#define D_CMDFAILED_CNT_U08         0x20U

#define D_SENSINITNOTDONE_CNT_U08           (uint8)(1U<<7U)
#define D_SECTOMILLSEC_CNT_F32               1000.0f

#define D_ANGLEDATA_CNT_U08         1U

#define D_NONE_CNT_U08              0x00U
#define D_ANGLEREG_CNT_U08          0x20U
#define D_CONTROLREG_CNT_U08        0x1EU
#define D_ERRORREG_CNT_U08          0x24U
#define D_EXTERRORREG_CNT_U08       0x26U
#define D_STATUSREG_CNT_U08         0x22U
#define D_EXTREADADDRREG_CNT_U08    0x0AU
#define D_EXTREADCTRLREG_CNT_U08    0x0CU
#define D_EXTREADDATREG_CNT_U08     0x0EU

#define D_SENSINITDELAY_MS_U08       32U
#define D_MAXATTEMPTSFORCUSTDATREAD_CNT_U08   10U


typedef enum {
	INIT_NOT_INITIALIZED = 0U,

	/* -- Read and Reset Error Registers from Sensor1/Col Sensor -- */
	INIT_SENSOR1_READERROR_SETREG,
	INIT_SENSOR1_READERROR_READ,
	INIT_SENSOR1_READEXTERR_SETREG,
	INIT_SENSOR1_READEXTERR_READ,
	INIT_SENSOR1_SENDCMD,
	INIT_SENSOR1_CHECKSTAT_SETREG,
	INIT_SENSOR1_CHECKSTAT_READ,

	/* -- Read and Reset Error Registers from Sensor2/Spur Sensor -- */
	INIT_SENSOR2_READERROR_SETREG,
	INIT_SENSOR2_READERROR_READ,
	INIT_SENSOR2_READEXTERR_SETREG,
	INIT_SENSOR2_READEXTERR_READ,
	INIT_SENSOR2_SENDCMD,
	INIT_SENSOR2_CHECKSTAT_SETREG,
	INIT_SENSOR2_CHECKSTAT_READ,

	/* -- Send commands to both sensors to read 'CustomerData' -- */
	INIT_SENSOR1_EXTREADADDRREG_SENDCMD,
	INIT_SENSOR1_EXTREADCTRLREG_SENDCMD,
	INIT_SENSOR1_DUMMY_SEND,
	INIT_SENSOR1_DUMMY_READ,
	INIT_SENSOR2_EXTREADADDRREG_SENDCMD,
	INIT_SENSOR2_EXTREADCTRLREG_SENDCMD,
	INIT_SENSOR2_DUMMY_SEND,
	INIT_SENSOR2_DUMMY_READ,
	
	/* -- Check both sensors whether they are ready to read 'CustomerData' -- */
	INIT_SENSOR1_EXTREADCTRLREG_SETREG,
	INIT_SENSOR1_EXTREADCTRLREG_READ,
	INIT_SENSOR2_EXTREADCTRLREG_SETREG,
	INIT_SENSOR2_EXTREADCTRLREG_READ,

	/* -- Read 'CustomerData' from both sensors -- */
	INIT_SENSOR1_EXTREADDATREG_SETREG,
	INIT_SENSOR1_EXTREADDATREG_READ,
	INIT_SENSOR2_EXTREADDATREG_SETREG,
	INIT_SENSOR2_EXTREADDATREG_READ,

	INIT_COMPLETE,

	/* -- Read Angle Data from both sensors -- */
	READ_SENSOR1_SETREG,
	READ_SENSOR1_GETDATA,
	READ_SENSOR2_SETREG,
	READ_SENSOR2_GETDATA,

	READ_COMPLETE
} CommStepType;


#define DIGCOLPSINT_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(CommStepType, SA_DIGCOLPSINT_VAR) DigColPsInt_CurrentStepNo_Cnt_M_enum;
#define DIGCOLPSINT_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */


#define DIGCOLPSINT_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint32, SA_DIGCOLPSINT_VAR) DigColPsInt_InitialTime_mS_M_u32;
#define DIGCOLPSINT_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */


#define DIGCOLPSINT_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint16, SA_DIGCOLPSINT_VAR) DigColPsInt_ColSnsrData_Cnt_M_u16;
STATIC volatile VAR(uint16, SA_DIGCOLPSINT_VAR) DigColPsInt_ColSnsrErrData_Cnt_D_u16; /* PRQA S 3218 */
STATIC volatile VAR(uint16, SA_DIGCOLPSINT_VAR) DigColPsInt_ColSnsrExtErrData_Cnt_D_u16;/* PRQA S 3218 */
STATIC volatile VAR(uint16, SA_DIGCOLPSINT_VAR) DigColPsInt_ColSnsrCheckStatData_Cnt_D_u16;/* PRQA S 3218 */
STATIC VAR(uint16, SA_DIGCOLPSINT_VAR) DigColPsInt_SpurSnsrData_Cnt_M_u16;/* PRQA S 3218 */
STATIC volatile VAR(uint16, SA_DIGCOLPSINT_VAR) DigColPsInt_SpurSnsrErrData_Cnt_D_u16;/* PRQA S 3218 */
STATIC volatile VAR(uint16, SA_DIGCOLPSINT_VAR) DigColPsInt_SpurSnsrExtErrData_Cnt_D_u16;/* PRQA S 3218 */
STATIC volatile VAR(uint16, SA_DIGCOLPSINT_VAR) DigColPsInt_SpurSnsrCheckStatData_Cnt_D_u16;/* PRQA S 3218 */
STATIC VAR(uint16, SA_DIGCOLPSINT_VAR) DigColPsInt_I2CHwCustData_Uls_M_u16;/* PRQA S 3218 */
STATIC VAR(uint16, SA_DIGCOLPSINT_VAR) DigColPsInt_I2CHwIncompleteCustData_Uls_M_u16;/* PRQA S 3218 */

#define DIGCOLPSINT_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */

#define DIGCOLPSINT_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint8, SA_DIGCOLPSINT_VAR) DigColPsInt_CurrentSlave_Cnt_M_u08;
STATIC VAR(uint8, SA_DIGCOLPSINT_VAR) DigColPsInt_RecvdDataType_Cnt_M_u08;
STATIC VAR(uint8, SA_DIGCOLPSINT_VAR) DigColPsInt_Buffer_Cnt_M_u08[D_COMMBUFFERSIZE_CNT_U08];
STATIC VAR(uint8, SA_DIGCOLPSINT_VAR) DigColPsInt_PrevReqDataType_Cnt_M_u08;
STATIC VAR(uint8, SA_DIGCOLPSINT_VAR) DigColPsInt_TransactionCnt_Cnt_M_u08;
STATIC VAR(uint8, SA_DIGCOLPSINT_VAR) DigColPsInt_PrevTransactionCnt_Cnt_M_u08;/* PRQA S 3218 */
STATIC VAR(uint8, SA_DIGCOLPSINT_VAR) DigColPsInt_AttempOccurForCustDatRead_Cnt_M_u08;/* PRQA S 3218 */
#define DIGCOLPSINT_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */

#define DIGCOLPSINT_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, SA_DIGCOLPSINT_VAR) DigColPsInt_InitFailedOnce_Cnt_M_lgc;
STATIC VAR(boolean, SA_DIGCOLPSINT_VAR) DigColPsInt_BusBusySeqError_Cnt_M_lgc;
STATIC VAR(boolean, SA_DIGCOLPSINT_VAR) DigColPsInt_NackOccured_Cnt_M_lgc;
STATIC VAR(boolean, SA_DIGCOLPSINT_VAR) DigColPsInt_SkipRegisterWrite_Cnt_M_lgc;
STATIC VAR(boolean, SA_DIGCOLPSINT_VAR) DigColPsInt_RecvOverrunError_Cnt_M_lgc;
STATIC VAR(boolean, SA_DIGCOLPSINT_VAR) DigColPsInt_SensInitialized_Cnt_M_lgc;
STATIC VAR(boolean, SA_DIGCOLPSINT_VAR) DigColPsInt_CmdFailOccurred_Cnt_M_lgc;
STATIC VAR(boolean, SA_DIGCOLPSINT_VAR) DigColPsInt_ColCustDatFound_Cnt_M_lgc;/* PRQA S 3218 */
STATIC VAR(boolean, SA_DIGCOLPSINT_VAR) DigColPsInt_SpurCustDatFound_Cnt_M_lgc;/* PRQA S 3218 */
#define DIGCOLPSINT_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */


/*** Locally Defined Lookup Tables ***/
#define DIGCOLPSINT_START_SEC_CONST_8
#include "MemMap.h" /* PRQA S 5087 */
STATIC CONST(uint8, SA_DIGCOLPSINT_VAR) T_DataRegisters_Cnt_u08[9] = {
	D_NONE_CNT_U08,
	D_ANGLEREG_CNT_U08,
	D_CONTROLREG_CNT_U08,
	D_ERRORREG_CNT_U08,
	D_EXTERRORREG_CNT_U08,
	D_STATUSREG_CNT_U08,
	D_EXTREADADDRREG_CNT_U08,
    D_EXTREADCTRLREG_CNT_U08,
    D_EXTREADDATREG_CNT_U08
};
#define DIGCOLPSINT_STOP_SEC_CONST_8
#include "MemMap.h" /* PRQA S 5087 */


/*** Function Prototypes ***/
STATIC INLINE FUNC(void, SA_DIGCOLPSINT_CODE) SetupWriteData(VAR(uint8, AUTOMATIC) Register_Cnt_T_u08, VAR(uint16, AUTOMATIC) Data_Cnt_T_u16);
STATIC INLINE FUNC(void, SA_DIGCOLPS_CODE) SetupWriteRegister(VAR(uint8, AUTOMATIC) Register_Cnt_T_u08);
STATIC INLINE FUNC(void, SA_DIGCOLPS_CODE) SetupRead(void);


/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/

/*======================================================================================================================
 * Function: DigColPsInt_Init
 * --------------------------------------------------------------------------------------------------------------------
 * Performs the initialization sequence for the I2C peripheral and sensors.
 *
 * Inputs:  N/A
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, SA_DIGCOLPS_CODE) DigColPsInt_Init(void)
{
	/* -----[ Mode Register Configuration ]--------------------------------------------------------
	 * 0x0        0        2        0
	 * 0b0 0 0 0  0 0 0 0  0 0 1 0  0 0 0 0
	 *   | | | |  | | | |  | | | |  | | | |
	 *   | | | |  | | | |  | | | |  | '-o-o- 0-2: Bit count
	 *   | | | |  | | | |  | | | |  '------- 3: Free data format enable bit
	 *   | | | |  | | | |  | | | '---------- 4: Start byte mode enable bit
	 *   | | | |  | | | |  | | '------------ 5: I2C Reset Enable bit
	 *   | | | |  | | | |  | '-------------- 6: Digital Loop-back enable bit
	 *   | | | |  | | | |  '---------------- 7: Repeat mode enable bit
	 *   | | | |  | | | '------------------- 8: Expand address enable bit
	 *   | | | |  | | '--------------------- 9: Transmit/receive bit
	 *   | | | |  | '----------------------- 10: Master/slave mode bit
	 *   | | | |  '------------------------- 11: Stop condition
	 *   | | | '---------------------------- 12: RESERVED
	 *   | | '------------------------------ 13: Start condition
	 *   | '-------------------------------- 14: Free running bit
	 *   '---------------------------------- 15: No-acknowledge mode
	 * --------------------------------------------------------------------------------------------
	 */
	I2c_Init(D_I2CREG_STRCPTR);
	I2c_SetCount(D_I2CREG_STRCPTR, 2U);
	I2c_EnableNotification(D_I2CREG_STRCPTR, (uint32)(I2C_RX_INT |
					I2C_TX_INT | I2C_AL_INT | I2C_NACK_INT | I2C_SCD_INT | I2C_ARDY_INT));
	I2c_Enable(D_I2CREG_STRCPTR);


	DigColPsInt_I2CHwCustData_Uls_M_u16 = D_I2CHWCUSTDATAUNKWN_CNT_U16;

	GetSystemTime_mS_u32( &DigColPsInt_InitialTime_mS_M_u32 );
}


/*======================================================================================================================
 * Function: DigColPsInt_GetData
 * --------------------------------------------------------------------------------------------------------------------
 * Return the buffered data read since the previous call to DigColPsInt_StartRequest().  The data for both sensors
 * will be returned in the passed pointers and the third pointer parameter indicated the type of data that has been
 * returned - corresponding to the requested data type.
 *
 * The return value from the function indicates any communication faults that may have occurred during the transfer.
 *
 * Inputs:  ColSnsrDataPtr_Cnt_T_u16 - Returned column sensor data.
 *          SpurSnsrDataPtr_Cnt_T_u16 - Returned spur sensor data.
 *          DataTypePtr_Cnt_T_u08 - Returned data type.
 *
 * Output:  CommFaults_Cnt_T_b08 - Communication faults that occurred during transfer - returns 0 for no faults:
 *              1: Reserved for parity fault device 1.
 *              2: Negative acknowledge occurred during write operation.
 *              4: Bus Busy sequence error
 *              8: Transaction failed to complete without specific fault indication.
 *              16: Reserved for parity fault device 2.
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(uint8, SA_DIGCOLPS_CODE) DigColPsInt_GetData(
	P2VAR(uint16, AUTOMATIC, AUTOMATIC) ColSnsrDataPtr_Cnt_T_u16,
	P2VAR(uint16, AUTOMATIC, AUTOMATIC) SpurSnsrDataPtr_Cnt_T_u16,
	P2VAR(uint8, AUTOMATIC, AUTOMATIC) DataTypePtr_Cnt_T_u08
)
{
	VAR(uint8, AUTOMATIC) CommFaults_Cnt_T_b08 = 0U;
	VAR(uint16, AUTOMATIC) ElapsedTime_mS_T_u16 = 0U;

	/* --- If the sensors are not initialized then check for elapsed time to Initialize the Angle Sensors ---------- */
	if(DigColPsInt_SensInitialized_Cnt_M_lgc == FALSE)
	{
		DtrmnElapsedTime_mS_u16( DigColPsInt_InitialTime_mS_M_u32, &ElapsedTime_mS_T_u16 );
		if( ElapsedTime_mS_T_u16 >= (uint16)D_SENSINITDELAY_MS_U08 )
		{
			DigColPsInt_CurrentSlave_Cnt_M_u08 = k_ColSensorI2CAddress_Cnt_u08;
			DigColPsInt_InitFailedOnce_Cnt_M_lgc = FALSE;
			SetupWriteRegister(D_ERRORREG_CNT_U08);
			DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_SENSOR1_READERROR_SETREG;

			DigColPsInt_SensInitialized_Cnt_M_lgc = TRUE;
			GetSystemTime_mS_u32(&DigColPsInt_InitialTime_mS_M_u32);
		}
	}
	else
	{
		if (DigColPsInt_CurrentStepNo_Cnt_M_enum < INIT_COMPLETE)
		{
			DtrmnElapsedTime_mS_u16(DigColPsInt_InitialTime_mS_M_u32, &ElapsedTime_mS_T_u16);
			if (ElapsedTime_mS_T_u16 > (uint16)(k_I2CHWInitTransactionTime_Sec_f32*D_SECTOMILLSEC_CNT_F32))
			{
				CommFaults_Cnt_T_b08 = D_SENSINITNOTDONE_CNT_U08;
			}
		}
	}

	/* NackOccured is set when the NACK received interrupt occurs */
	if (DigColPsInt_NackOccured_Cnt_M_lgc == TRUE)
	{
		CommFaults_Cnt_T_b08 |= D_NACKOCCURRED_CNT_U08;
		DigColPsInt_NackOccured_Cnt_M_lgc = FALSE;
	}

	/* Receiver Overrun is set when the Receive Overrun Error occurs */
	if (DigColPsInt_RecvOverrunError_Cnt_M_lgc == TRUE)
	{
		CommFaults_Cnt_T_b08 |= D_RECVOVERRUNERR_CNT_U08;
		DigColPsInt_RecvOverrunError_Cnt_M_lgc = FALSE;
	}

	/* BusBusySeqError is set when the BUS BUSY interrupt occurs */
	if (DigColPsInt_BusBusySeqError_Cnt_M_lgc == TRUE)
	{
		CommFaults_Cnt_T_b08 |= D_BBSEQERR_CNT_U08;
		DigColPsInt_BusBusySeqError_Cnt_M_lgc = FALSE;
	}

	/* Command Fail Occurred bit is set from two sources (retry failures for clearing of errors
	 * at INIT OR a timeout occurs when an extended read from the A1332 is executed */
	if (DigColPsInt_CmdFailOccurred_Cnt_M_lgc == TRUE)
	{
		/* If set during initialization, this bit will remain set for the duration of the ignition cycle. */
		CommFaults_Cnt_T_b08 |= D_CMDFAILED_CNT_U08;
	}

	/* Transaction counter used to identify stale data */
	if ( (DigColPsInt_TransactionCnt_Cnt_M_u08 == DigColPsInt_PrevTransactionCnt_Cnt_M_u08) && (DigColPsInt_RecvdDataType_Cnt_M_u08 != D_NONE_CNT_U08) )
	{
		CommFaults_Cnt_T_b08 |= D_TRANSNOTCOMP_CNT_U08;
	}
	DigColPsInt_PrevTransactionCnt_Cnt_M_u08 = DigColPsInt_TransactionCnt_Cnt_M_u08;


	*ColSnsrDataPtr_Cnt_T_u16 = DigColPsInt_ColSnsrData_Cnt_M_u16;
	*SpurSnsrDataPtr_Cnt_T_u16 = DigColPsInt_SpurSnsrData_Cnt_M_u16;
	*DataTypePtr_Cnt_T_u08 = DigColPsInt_RecvdDataType_Cnt_M_u08;

	return CommFaults_Cnt_T_b08;
}


/*======================================================================================================================
 * Function: DigColPsInt_StartRequest
 * --------------------------------------------------------------------------------------------------------------------
 * Setup and start the interrupt driven process of fetching sensor data over the I2C interface.  The transfer is
 * automated through the use of interrupts and the notification function DigColPsInt_InterruptNotification()
 * defined below.  All transfers will always include the retrieval of the requested data from both sensors.
 *
 * Inputs:  Type_Cnt_T_u08 - Type of data that is being requested for this transfer:
 *              1 - Angle: Request sensor angle data.
 *              2 - Control: Request the control register data.
 *              3 - Error: Request error register data.
 *              4 - ExtError: Request extended error data register.
 *              5 - Status: Request status register data.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, SA_DIGCOLPS_CODE) DigColPsInt_StartRequest(VAR(uint8, AUTOMATIC) Type_Cnt_T_u08)
{
	VAR(uint16, AUTOMATIC) Status_Cnt_T_u16;

	if ((DigColPsInt_SensInitialized_Cnt_M_lgc == TRUE) && (DigColPsInt_CurrentStepNo_Cnt_M_enum >= INIT_COMPLETE))
	{
		Status_Cnt_T_u16 = I2c_GetStatus(D_I2CREG_STRCPTR);
		if ((Status_Cnt_T_u16 & I2C_BUSBUSY) == 0U)
		{
			DigColPsInt_CurrentSlave_Cnt_M_u08 = k_ColSensorI2CAddress_Cnt_u08;

			if ((Type_Cnt_T_u08 == D_ANGLEDATA_CNT_U08) && (DigColPsInt_PrevReqDataType_Cnt_M_u08 == D_ANGLEDATA_CNT_U08))
			{
				/* Take advantage of wrapping register reads for angle data to speed up transfer if previously read angle data
				* otherwise set the register using the else case below.
				*/
				DigColPsInt_SkipRegisterWrite_Cnt_M_lgc = TRUE;
				SetupRead();
				DigColPsInt_CurrentStepNo_Cnt_M_enum = READ_SENSOR1_GETDATA;
			}
			else if ((Type_Cnt_T_u08 > D_NONE_CNT_U08) && (Type_Cnt_T_u08 <= D_STATUSREG_CNT_U08))
			{
				/* In this case, we must specify the register address we would like to read.  Send that first as a master
				* transmitter and then switch over to receive the requested data
				*/
				DigColPsInt_SkipRegisterWrite_Cnt_M_lgc = FALSE;
				SetupWriteRegister(T_DataRegisters_Cnt_u08[Type_Cnt_T_u08]);
				DigColPsInt_CurrentStepNo_Cnt_M_enum = READ_SENSOR1_SETREG;
			}
			else
			{
				/* Do nothing - don't understand requested type */
			}

			DigColPsInt_PrevReqDataType_Cnt_M_u08 = Type_Cnt_T_u08;
		}
	}
}


/*======================================================================================================================
 * Function: DigColPsInt_InterruptNotification
 * --------------------------------------------------------------------------------------------------------------------
 * I2C interrupt notification handler function.  Mapped through I2cNxtr_Cfg.h to be called by I2cNxtr component when
 * an enabled I2C interrupt fires.  This function handles all transfers of data started by calling the
 * DigColPsInt_StartRequest() function.
 *
 * Inputs:  Flags_Cnt_T_b16 - Interrupt flag bitfield indicating which interrupt fired.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, SA_DIGCOLPS_CODE) DigColPsInt_InterruptNotification(VAR(uint16, AUTOMATIC) Flags_Cnt_T_b16)
{

	switch ((i2cIntFlags)Flags_Cnt_T_b16)
	{
	/* -----[ Negative Acknowledge Interrupt ]---------------------------------------------------------------------- */
	case I2C_NACK_INT:
		/* NACK received */
		DigColPsInt_NackOccured_Cnt_M_lgc = TRUE;
		I2c_GenStopCond(D_I2CREG_STRCPTR);
		if (DigColPsInt_CurrentStepNo_Cnt_M_enum < INIT_SENSOR2_READERROR_SETREG)
		{
			/* Skip to next sensor initialization */
			DigColPsInt_CurrentSlave_Cnt_M_u08 = k_SpurSensorI2CAddress_Cnt_u08;
			SetupWriteRegister(D_ERRORREG_CNT_U08);
			DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_SENSOR2_READERROR_SETREG;
		}
		else if(DigColPsInt_CurrentStepNo_Cnt_M_enum < INIT_SENSOR1_EXTREADADDRREG_SENDCMD)
		{
			/* Skip to 'CustomerData' read */
			DigColPsInt_CurrentSlave_Cnt_M_u08 = k_ColSensorI2CAddress_Cnt_u08;
			SetupWriteData(D_EXTREADADDRREG_CNT_U08, D_EXTREADADDRREGCMD_CNT_U16);
			DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_SENSOR1_EXTREADADDRREG_SENDCMD;
		}
		else if (DigColPsInt_CurrentStepNo_Cnt_M_enum < INIT_COMPLETE)
		{
			/* Skip to final init step */
			DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_COMPLETE;
		}
		else
		{
			/* Skip to final read step */
			DigColPsInt_CurrentStepNo_Cnt_M_enum = READ_COMPLETE;
		}
		break;

	/* -----[ Arbitration Lost Interrupt ]-------------------------------------------------------------------------- */
	case I2C_AL_INT:
		I2c_SetStatus(D_I2CREG_STRCPTR, D_CLEARSTATUSBITS_CNT_U16);
		DigColPsInt_BusBusySeqError_Cnt_M_lgc = TRUE;
		if (DigColPsInt_CurrentStepNo_Cnt_M_enum < INIT_COMPLETE)
		{
			/* Skip to final init step */
			DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_COMPLETE;
		}
		else
		{
			/* Skip to final read step */
			DigColPsInt_CurrentStepNo_Cnt_M_enum = READ_COMPLETE;
		}
		break;

	/* -----[ Receiver Overrun Error ]------------------------------------------------------------------------------ */
	case I2C_RECV_OVERRUN:
		DigColPsInt_RecvOverrunError_Cnt_M_lgc = TRUE;
		break;

	/* -----[ Stop Detect Interrupt ]------------------------------------------------------------------------------- */
	case I2C_SCD_INT:
		switch (DigColPsInt_CurrentStepNo_Cnt_M_enum)
		{
		/*** Sensor Initialization Steps ***/
		case INIT_SENSOR1_READERROR_READ:
			DigColPsInt_ColSnsrErrData_Cnt_D_u16 = ((uint16)DigColPsInt_Buffer_Cnt_M_u08[0] << 8) | (uint16)DigColPsInt_Buffer_Cnt_M_u08[1];
			SetupWriteRegister(D_EXTERRORREG_CNT_U08);
			DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_SENSOR1_READEXTERR_SETREG;
			break;

		case INIT_SENSOR1_READEXTERR_READ:
			DigColPsInt_ColSnsrExtErrData_Cnt_D_u16 = ((uint16)DigColPsInt_Buffer_Cnt_M_u08[0] << 8) | (uint16)DigColPsInt_Buffer_Cnt_M_u08[1];
			SetupWriteData(D_CONTROLREG_CNT_U08, D_RESETCMD_CNT_U16);
			DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_SENSOR1_SENDCMD;
			break;

		case INIT_SENSOR1_CHECKSTAT_READ:
			DigColPsInt_ColSnsrCheckStatData_Cnt_D_u16 = ((uint16)DigColPsInt_Buffer_Cnt_M_u08[0] << 8) | (uint16)DigColPsInt_Buffer_Cnt_M_u08[1];
			if (((DigColPsInt_Buffer_Cnt_M_u08[0] & 0x40U) != 0U) && (DigColPsInt_InitFailedOnce_Cnt_M_lgc == FALSE))
			{
				/* Try one additional time */
				DigColPsInt_InitFailedOnce_Cnt_M_lgc = TRUE;
				DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_SENSOR1_READERROR_SETREG;
			}
			else
			{
				if( (DigColPsInt_Buffer_Cnt_M_u08[0] & 0x40U) != 0U )
				{
					DigColPsInt_CmdFailOccurred_Cnt_M_lgc = TRUE;
				}
				/* Col Sensor fully initialized - setup for spur sensor */
				DigColPsInt_CurrentSlave_Cnt_M_u08 = k_SpurSensorI2CAddress_Cnt_u08;
				DigColPsInt_InitFailedOnce_Cnt_M_lgc = FALSE;
				DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_SENSOR2_READERROR_SETREG;
			}
			SetupWriteRegister(D_ERRORREG_CNT_U08);
			break;

		case INIT_SENSOR2_READERROR_READ:
			DigColPsInt_SpurSnsrErrData_Cnt_D_u16 = ((uint16)DigColPsInt_Buffer_Cnt_M_u08[0] << 8) | (uint16)DigColPsInt_Buffer_Cnt_M_u08[1];
			SetupWriteRegister(D_EXTERRORREG_CNT_U08);
			DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_SENSOR2_READEXTERR_SETREG;
			break;

		case INIT_SENSOR2_READEXTERR_READ:
			DigColPsInt_SpurSnsrExtErrData_Cnt_D_u16 = ((uint16)DigColPsInt_Buffer_Cnt_M_u08[0] << 8) | (uint16)DigColPsInt_Buffer_Cnt_M_u08[1];
			SetupWriteData(D_CONTROLREG_CNT_U08, D_RESETCMD_CNT_U16);
			DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_SENSOR2_SENDCMD;
			break;

		case INIT_SENSOR1_DUMMY_READ:
			DigColPsInt_CurrentSlave_Cnt_M_u08 = k_SpurSensorI2CAddress_Cnt_u08;
			SetupWriteData(D_EXTREADADDRREG_CNT_U08, D_EXTREADADDRREGCMD_CNT_U16);
			DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_SENSOR2_EXTREADADDRREG_SENDCMD;
			break;

		case INIT_SENSOR2_DUMMY_READ:
			DigColPsInt_CurrentSlave_Cnt_M_u08 = k_ColSensorI2CAddress_Cnt_u08;
			SetupWriteRegister(D_EXTREADCTRLREG_CNT_U08);
			DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_SENSOR1_EXTREADCTRLREG_SETREG;
			break;

		case INIT_SENSOR2_CHECKSTAT_READ:
			DigColPsInt_SpurSnsrCheckStatData_Cnt_D_u16 = ((uint16)DigColPsInt_Buffer_Cnt_M_u08[0] << 8) | (uint16)DigColPsInt_Buffer_Cnt_M_u08[1];
			if (((DigColPsInt_Buffer_Cnt_M_u08[0] & 0x40U) != 0U) && (DigColPsInt_InitFailedOnce_Cnt_M_lgc == FALSE))
			{
				/* Try one additional time */
				DigColPsInt_InitFailedOnce_Cnt_M_lgc = TRUE;
				SetupWriteRegister(D_ERRORREG_CNT_U08);
				DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_SENSOR2_READERROR_SETREG;
			}
			else
			{
				if( (DigColPsInt_Buffer_Cnt_M_u08[0] & 0x40U) != 0U )
				{
					DigColPsInt_CmdFailOccurred_Cnt_M_lgc = TRUE;
				}
				DigColPsInt_InitFailedOnce_Cnt_M_lgc = FALSE;

				DigColPsInt_CurrentSlave_Cnt_M_u08 = k_ColSensorI2CAddress_Cnt_u08;
				SetupWriteData(D_EXTREADADDRREG_CNT_U08, D_EXTREADADDRREGCMD_CNT_U16);
				DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_SENSOR1_EXTREADADDRREG_SENDCMD;
			}
			break;

		/*** Sensor Initialization Steps to Read 'CustomerData' ***/
		case INIT_SENSOR1_EXTREADCTRLREG_READ:
			if( (DigColPsInt_Buffer_Cnt_M_u08[1] & 0x01U) == 0x01U )
			{
				DigColPsInt_ColCustDatFound_Cnt_M_lgc = TRUE;
			}
			DigColPsInt_CurrentSlave_Cnt_M_u08 = k_SpurSensorI2CAddress_Cnt_u08;
			SetupWriteRegister(D_EXTREADCTRLREG_CNT_U08);
			DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_SENSOR2_EXTREADCTRLREG_SETREG;
			break;

		case INIT_SENSOR2_EXTREADCTRLREG_READ:
			if( (DigColPsInt_Buffer_Cnt_M_u08[1] & 0x01U) == 0x01U )
			{
				DigColPsInt_SpurCustDatFound_Cnt_M_lgc = TRUE;
			}

			DigColPsInt_AttempOccurForCustDatRead_Cnt_M_u08++;
			if( (DigColPsInt_ColCustDatFound_Cnt_M_lgc == TRUE) && (DigColPsInt_SpurCustDatFound_Cnt_M_lgc == TRUE) )
			{
				DigColPsInt_CurrentSlave_Cnt_M_u08 = k_ColSensorI2CAddress_Cnt_u08;
				SetupWriteRegister(D_EXTREADDATREG_CNT_U08);
				DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_SENSOR1_EXTREADDATREG_SETREG;
			}
			else if( DigColPsInt_AttempOccurForCustDatRead_Cnt_M_u08 > D_MAXATTEMPTSFORCUSTDATREAD_CNT_U08 )
			{
				DigColPsInt_CmdFailOccurred_Cnt_M_lgc = TRUE;
				DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_COMPLETE;
			}
			else
			{
				DigColPsInt_CurrentSlave_Cnt_M_u08 = k_ColSensorI2CAddress_Cnt_u08;
				SetupWriteRegister(D_EXTREADCTRLREG_CNT_U08);
				DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_SENSOR1_EXTREADCTRLREG_SETREG;
			}
			break;

		case INIT_SENSOR1_EXTREADDATREG_READ:
			/*** MISRA Rule 21.1 operation is redundant is ignored as D_I2CHWCUSTDATACOL_CNT_U16 value change in FDD requires no functional changes in code***/
			DigColPsInt_I2CHwIncompleteCustData_Uls_M_u16 = ((uint16)(DigColPsInt_Buffer_Cnt_M_u08[1]) >> 4U ) & D_I2CHWCUSTDATACOL_CNT_U16;
			DigColPsInt_CurrentSlave_Cnt_M_u08 = k_SpurSensorI2CAddress_Cnt_u08;
			SetupWriteRegister(D_EXTREADDATREG_CNT_U08);
			DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_SENSOR2_EXTREADDATREG_SETREG;
			break;

		case INIT_SENSOR2_EXTREADDATREG_READ:
			DigColPsInt_I2CHwIncompleteCustData_Uls_M_u16 |= ( (uint16)(DigColPsInt_Buffer_Cnt_M_u08[1])) & D_I2CHWCUSTDATASPUR_CNT_U16;
			DigColPsInt_I2CHwCustData_Uls_M_u16 = DigColPsInt_I2CHwIncompleteCustData_Uls_M_u16;
			DigColPsInt_CurrentStepNo_Cnt_M_enum = INIT_COMPLETE;
			break;


		/*** Sensor Read Steps ***/
		case READ_SENSOR1_GETDATA:
			/* store the received data and switch to read from the spur sensor */
			DigColPsInt_ColSnsrData_Cnt_M_u16 = ((uint16)DigColPsInt_Buffer_Cnt_M_u08[0] << 8) | (uint16)DigColPsInt_Buffer_Cnt_M_u08[1];
			DigColPsInt_CurrentSlave_Cnt_M_u08 = k_SpurSensorI2CAddress_Cnt_u08;
			if (DigColPsInt_SkipRegisterWrite_Cnt_M_lgc == TRUE)
			{
				/* if register selection was skipped for column sensor, skip for spur sensor too */
				SetupRead();
				DigColPsInt_CurrentStepNo_Cnt_M_enum = READ_SENSOR2_GETDATA;
			}
			else
			{
				/* Otherwise, transmit the register address before reading data */
				SetupWriteRegister(T_DataRegisters_Cnt_u08[DigColPsInt_PrevReqDataType_Cnt_M_u08]);
				DigColPsInt_CurrentStepNo_Cnt_M_enum = READ_SENSOR2_SETREG;
			}
			break;

		case READ_SENSOR2_GETDATA:
			/* Store the received data and indicate that the reception has successfully completed */
			DigColPsInt_SpurSnsrData_Cnt_M_u16 = ((uint16)DigColPsInt_Buffer_Cnt_M_u08[0] << 8) | (uint16)DigColPsInt_Buffer_Cnt_M_u08[1];
			DigColPsInt_RecvdDataType_Cnt_M_u08 = DigColPsInt_PrevReqDataType_Cnt_M_u08;
			DigColPsInt_CurrentStepNo_Cnt_M_enum = READ_COMPLETE;
			DigColPsInt_TransactionCnt_Cnt_M_u08 = (DigColPsInt_TransactionCnt_Cnt_M_u08 + 1U) & 0xFFU;
			break;

		default:
			/* Do nothing on unknown step */
			break;
		}
		break;

	/* -----[ Register Access Ready Interrupt ]--------------------------------------------------------------------- */
	/* Despite the name - the ARDY interrupt actually fires on a transmission after the slave address and write bit
	 * have been clocked out.  The steps below are used to switch to master-receiver mode and receive 2 bytes of data
	 * from the sensor who's slave address has already been setup using the I2c_SetupMasterTransmit function. */
	case I2C_ARDY_INT:
		switch (DigColPsInt_CurrentStepNo_Cnt_M_enum)
		{
		case INIT_SENSOR1_READERROR_SETREG:
		case INIT_SENSOR1_READEXTERR_SETREG:
		case INIT_SENSOR1_CHECKSTAT_SETREG:
		case INIT_SENSOR2_READERROR_SETREG:
		case INIT_SENSOR2_READEXTERR_SETREG:
		case INIT_SENSOR2_CHECKSTAT_SETREG:
		case INIT_SENSOR1_EXTREADCTRLREG_SETREG:
		case INIT_SENSOR2_EXTREADCTRLREG_SETREG:
		case INIT_SENSOR1_EXTREADDATREG_SETREG:
		case INIT_SENSOR2_EXTREADDATREG_SETREG:
		case READ_SENSOR1_SETREG:
		case READ_SENSOR2_SETREG:
			/* Restart and receive two bytes of data from the sensor */
			SetupRead();
			DigColPsInt_CurrentStepNo_Cnt_M_enum++;
			break;

		case INIT_SENSOR1_SENDCMD:
		case INIT_SENSOR2_SENDCMD:
			SetupWriteRegister(D_ANGLEREG_CNT_U08);
			DigColPsInt_CurrentStepNo_Cnt_M_enum++;
			break;

		case INIT_SENSOR1_EXTREADADDRREG_SENDCMD:
		case INIT_SENSOR2_EXTREADADDRREG_SENDCMD:
			SetupWriteData(D_EXTREADCTRLREG_CNT_U08, D_EXTREADCTRLREGCMD_CNT_U16);
			DigColPsInt_CurrentStepNo_Cnt_M_enum++;
			break;

		case INIT_SENSOR1_EXTREADCTRLREG_SENDCMD:

			SetupWriteRegister(D_ANGLEREG_CNT_U08);
			DigColPsInt_CurrentStepNo_Cnt_M_enum++;
			break;



		case INIT_SENSOR1_DUMMY_SEND:
			/* Restart and receive two bytes of data from the sensor */
			SetupRead();
			DigColPsInt_CurrentStepNo_Cnt_M_enum++;
			break;

		case INIT_SENSOR2_EXTREADCTRLREG_SENDCMD:
			SetupWriteRegister(D_ANGLEREG_CNT_U08);
			DigColPsInt_CurrentStepNo_Cnt_M_enum++;

			DigColPsInt_AttempOccurForCustDatRead_Cnt_M_u08 = 0U;
			break;

		case INIT_SENSOR2_DUMMY_SEND:
			/* Restart and receive two bytes of data from the sensor */
			SetupRead();
			DigColPsInt_CurrentStepNo_Cnt_M_enum++;
			break;


		default:
			/* Do nothing on unknown step */
			break;
		}
		break;

	default:
		/* Do nothing on unknown interrupt */
		break;
	}
}



/*======================================================================================================================
 * Function: DigColPsInt_GetCustData
 * --------------------------------------------------------------------------------------------------------------------
 * Returns DigColPsInt_I2CHwCustData_Uls_M_u16.
 *
 * Inputs:  N/A
 *
 * Output:  DigColPsInt_I2CHwCustData_Uls_M_u16
 *--------------------------------------------------------------------------------------------------------------------*/
FUNC(uint16, SA_DIGCOLPS_CODE) DigColPsInt_GetCustData(void)
{
	return DigColPsInt_I2CHwCustData_Uls_M_u16;
}


/*======================================================================================================================
 * Function: SetupWriteData
 * --------------------------------------------------------------------------------------------------------------------
 * Local function to aid setup of I2C peripheral to write 2 bytes of data (16 bit value) to a specified register.
 *
 * Inputs:  N/A
 *
 * Output:
 *--------------------------------------------------------------------------------------------------------------------*/
STATIC INLINE FUNC(void, SA_DIGCOLPSINT_CODE) SetupWriteData(
	VAR(uint8, AUTOMATIC) Register_Cnt_T_u08,
	VAR(uint16, AUTOMATIC) Data_Cnt_T_u16
)
{
	DigColPsInt_Buffer_Cnt_M_u08[0] = Register_Cnt_T_u08;
	DigColPsInt_Buffer_Cnt_M_u08[1] = (uint8)(Data_Cnt_T_u16 >> 8);
	DigColPsInt_Buffer_Cnt_M_u08[2] = (uint8)(Data_Cnt_T_u16 & 0xFFU);
	I2c_SetupMasterTransmit(D_I2CREG_STRCPTR, DigColPsInt_CurrentSlave_Cnt_M_u08, 3U);
	I2c_Send(D_I2CREG_STRCPTR, 3U, DigColPsInt_Buffer_Cnt_M_u08);
}


/*======================================================================================================================
 * Function: SetupWriteRegister
 * --------------------------------------------------------------------------------------------------------------------
 * Local function to aid setup of I2C peripheral to write register address before restarting to perform read operation.
 *
 * Inputs:  Register_Cnt_T_u08 - Register address which shall be sent.
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
STATIC INLINE FUNC(void, SA_DIGCOLPS_CODE) SetupWriteRegister(
	VAR(uint8, AUTOMATIC) Register_Cnt_T_u08
)
{
	DigColPsInt_Buffer_Cnt_M_u08[0] = Register_Cnt_T_u08;
	I2c_SetupMasterTransmit(D_I2CREG_STRCPTR, DigColPsInt_CurrentSlave_Cnt_M_u08, 1U);
	I2c_Send(D_I2CREG_STRCPTR, 1U, DigColPsInt_Buffer_Cnt_M_u08);
}


/*======================================================================================================================
 * Function: SetupRead
 * --------------------------------------------------------------------------------------------------------------------
 * Local function to aid setup of I2C peripheral to read two bytes of data from the slave address set in
 * DigColPsInt_CurrentSlave_Cnt_M_u08.
 *
 * Inputs:  N/A
 *
 * Output:  N/A
 *--------------------------------------------------------------------------------------------------------------------*/
STATIC INLINE FUNC(void, SA_DIGCOLPS_CODE) SetupRead(void)
{
	I2c_SetupMasterReceive(D_I2CREG_STRCPTR, DigColPsInt_CurrentSlave_Cnt_M_u08, 2U);
	I2c_SetRecv(D_I2CREG_STRCPTR, 2U, DigColPsInt_Buffer_Cnt_M_u08);
}


/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/
