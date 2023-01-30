/***********************************************************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : I2cNxtr.h
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
 * %version:          3 %
 * %derived_by:       jzk9cc %
 * %date_modified:    Mon Feb 24 13:42:54 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 08/08/13  1        Jared     New driver for initial use with DigColPosSnsr component                         8850
 * 09/20/13  2        Jared     Added module short name to I2cTransfer module level variable                    8850
 * 02/24/14  3        Rijvi     Added a new enum type for receive overrun error                                 11479
 */
/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/
#ifndef __I2C_H__
#define __I2C_H__
/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/
#include "i2c_regs.h"

typedef struct {
	VAR(uint32, AUTOMATIC) Mode_Cnt_b32;
	VAR(uint32, AUTOMATIC) Length_Cnt_u32;
	P2VAR(uint8, AUTOMATIC, AUTOMATIC) DataPtr_Cnt_u08;
} I2cTransferType;

extern VAR(I2cTransferType, AUTOMATIC) I2cNxtr_I2cTransfer_Cnt_M_str;


/** @enum i2cMode
*   @brief Alias names for i2c modes
*   This enumeration is used to provide alias names for I2C modes:
*/

enum i2cMode
{
	I2C_FD_FORMAT   = 0x0008U,  /* Free Data Format    */
	I2C_START_BYTE  = 0x0010U,
	I2C_RESET_OUT   = 0x0020U,  I2C_RESET_IN   = 0x0000U,
	I2C_DLOOPBACK   = 0x0040U,
	I2C_REPEATMODE  = 0x0080U,  /* In Master Mode only */
	I2C_10BIT_AMODE = 0x0100U,  I2C_7BIT_AMODE = 0x0000U,
	I2C_TRANSMITTER = 0x0200U,  I2C_RECEIVER   = 0x0000U,
	I2C_MASTER      = 0x0400U,  I2C_SLAVE      = 0x0000U,
	I2C_STOP_COND   = 0x0800U,  /* In Master Mode only */
	I2C_START_COND  = 0x2000U,  /* In Master Mode only */
	I2C_FREE_RUN    = 0x4000U,
	I2C_NACK_MODE   = 0x8000U
};


/** @enum i2cBitCount
*   @brief Alias names for i2c bit count
*   This enumeration is used to provide alias names for I2C bit count:
*/

enum i2cBitCount
{
	I2C_2_BIT   = 0x2U,
	I2C_3_BIT   = 0x3U,
	I2C_4_BIT   = 0x4U,
	I2C_5_BIT   = 0x5U,
	I2C_6_BIT   = 0x6U,
	I2C_7_BIT   = 0x7U,
	I2C_8_BIT   = 0x0U
};



/** @enum i2cIntFlags
*   @brief Interrupt Flag Definitions
*
*   Used with I2CEnableNotification, I2CDisableNotification
*/
typedef enum
{
	I2C_AL_INT     = 0x0001U,  /* arbitration lost      */
	I2C_NACK_INT   = 0x0002U,  /* no acknowledgment    */
	I2C_ARDY_INT   = 0x0004U,  /* access ready          */
	I2C_RX_INT     = 0x0008U,  /* receive data ready    */
	I2C_TX_INT     = 0x0010U,  /* transmit data ready   */
	I2C_SCD_INT    = 0x0020U,  /* stop condition detect */
	I2C_AAS_INT    = 0x0040U,   /* address as slave      */
	I2C_RECV_OVERRUN = 0x0800U  /* receiver overrun error. Note: This is not an interrupt;     */
	                            /* overrun condition is checked only when I2C_RX_INT is fired. */
} i2cIntFlags;


/** @enum i2cStatFlags
*   @brief Interrupt Status Definitions
*
*/
enum i2cStatFlags
{
	I2C_AL         = 0x0001U,  /* arbitration lost          */
	I2C_NACK       = 0x0002U,  /* no acknowledgement        */
	I2C_ARDY       = 0x0004U,  /* access ready              */
	I2C_RX         = 0x0008U,  /* receive data ready        */
	I2C_TX         = 0x0010U,  /* transmit data ready       */
	I2C_SCD        = 0x0020U,  /* stop condition detect     */
	I2C_AD0        = 0x0100U,  /* address Zero Status       */
	I2C_AAS        = 0x0200U,  /* address as slave          */
	I2C_XSMT       = 0x0400U,  /* Transmit shift empty not  */
	I2C_RXFULL     = 0x0800U,  /* receive full              */
	I2C_BUSBUSY    = 0x1000U,  /* bus busy                  */
	I2C_NACKSNT    = 0x2000U,  /* No Ack Sent               */
	I2C_SDIR       = 0x4000U   /* Slave Direction           */
};


/** @enum i2cDMA
*   @brief I2C DMA definitions
*
*   Used before i2c transfer
*/
enum i2cDMA
{
	I2C_TXDMA   = 0x20U,
	I2C_RXDMA   = 0x10U
};

/* Configuration registers */
typedef struct i2c_config_reg
{
	uint32 CONFIG_OAR;
	uint32 CONFIG_IMR;
	uint32 CONFIG_CLKL;
	uint32 CONFIG_CLKH;
	uint32 CONFIG_CNT;
	uint32 CONFIG_SAR;
	uint32 CONFIG_MDR;
	uint32 CONFIG_EMDR;
	uint32 CONFIG_PSC;
	uint32 CONFIG_DMAC;
	uint32 CONFIG_FUN;
	uint32 CONFIG_DIR;
	uint32 CONFIG_ODR;
	uint32 CONFIG_PD;
	uint32 CONFIG_PSL;
} i2c_config_reg_t;


/* Configuration registers initial value for I2C*/
#define I2C_OAR_CONFIGVALUE         0x00000000U
#define I2C_IMR_CONFIGVALUE       ((0U << 6U) \
								 | (0U << 5U) \
								 | (0U << 4U) \
								 | (1U << 3U) \
								 | (0U << 2U) \
								 | (0U << 1U) \
								 | (0U))

#define I2C_CLKL_CONFIGVALUE        35U
#define I2C_CLKH_CONFIGVALUE        35U
#define I2C_CNT_CONFIGVALUE         8U
#define I2C_SAR_CONFIGVALUE         0x00000000U
#define I2C_MDR_CONFIGVALUE        (0x00000000U \
								 | (1U <<11U) \
								 | (1U <<10U) \
								 | (I2C_TRANSMITTER) \
								 | (I2C_7BIT_AMODE) \
								 | (0 << 7U) \
								 | (0U) \
								 | (I2C_8_BIT) \
								 | I2C_RESET_OUT)

#define I2C_EMDR_CONFIGVALUE        0x00000001U
#define I2C_PSC_CONFIGVALUE         9U
#define I2C_DMAC_CONFIGVALUE        0x00000000U
#define I2C_FUN_CONFIGVALUE         0U
#define I2C_DIR_CONFIGVALUE       ((0U << 1U) \
								 | (0U))
#define I2C_ODR_CONFIGVALUE       ((0U << 1U) \
								 | (0U))
#define I2C_PD_CONFIGVALUE        ((0U << 1U) \
								 | (0U))
#define I2C_PSL_CONFIGVALUE       ((1U << 1U) \
								 | (1U))


FUNC(void, I2CNXTR_CODE) I2c_Init(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
);
FUNC(void, I2CNXTR_CODE) I2c_Enable(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
);
FUNC(void, I2CNXTR_CODE) I2c_Reset(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
);
FUNC(void, I2CNXTR_CODE) I2c_SetupMasterTransmit(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint8, AUTOMATIC) SlaveAddress_Cnt_T_u08,
	VAR(uint16, AUTOMATIC) DataLength_Cnt_T_u16
);
FUNC(void, I2CNXTR_CODE) I2c_SetupMasterReceive(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint8, AUTOMATIC) SlaveAddress_Cnt_T_u08,
	VAR(uint16, AUTOMATIC) DataLength_Cnt_T_u16
);
FUNC(void, I2CNXTR_CODE) I2c_SwitchMasterReceive(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint16, AUTOMATIC) DataLength_Cnt_T_u16
);
FUNC(void, I2CNXTR_CODE) I2c_SetCount(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint16, AUTOMATIC) Count_Cnt_T_u16
);
FUNC(void, I2CNXTR_CODE) I2c_SetOwnAdd(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint16, AUTOMATIC) Address_Cnt_T_u16
);
FUNC(void, I2CNXTR_CODE) I2c_SetSlaveAdd(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint16, AUTOMATIC) Address_Cnt_T_u16
);
FUNC(void, I2CNXTR_CODE) I2c_SetFunctional(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint8, AUTOMATIC) Port_Cnt_T_u08
);
FUNC(void, I2CNXTR_CODE) I2c_SetBaudrate(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint32, AUTOMATIC) Baud_Hz_T_u32
);
FUNC(boolean, I2CNXTR_CODE) I2c_IsTxReady(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
);
FUNC(void, I2CNXTR_CODE) I2c_SendByte(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint8, AUTOMATIC) Byte_Cnt_T_u08
);
FUNC(void, I2CNXTR_CODE) I2c_Send(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint32, AUTOMATIC) Length_Cnt_T_u32,
	P2VAR(uint8, AUTOMATIC, AUTOMATIC) DataPtr_Cnt_T_u08
);
FUNC(boolean, I2CNXTR_CODE) I2c_IsRxReady(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
);
FUNC(uint32, I2CNXTR_CODE) I2c_RxError(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
);
FUNC(uint8, I2CNXTR_CODE) I2c_ReceiveByte(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
);
FUNC(void, I2CNXTR_CODE) I2c_SetRecv(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint32, AUTOMATIC) Length_Cnt_T_u32,
	P2VAR(uint8, AUTOMATIC, AUTOMATIC) DataPtr_Cnt_T_u08
);
FUNC(void, I2CNXTR_CODE) I2c_SetDirection(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint8, AUTOMATIC) Dir_Cnt_T_u08
);
FUNC(void, I2CNXTR_CODE) I2c_SetBit(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint8, AUTOMATIC) Bit_Cnt_T_u08,
	VAR(uint8, AUTOMATIC) Value_Cnt_T_u08
);
FUNC(uint32, I2CNXTR_CODE) I2c_GetBit(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint8, AUTOMATIC) Bit_Cnt_T_u08
);
FUNC(void, I2CNXTR_CODE) I2c_EnableNotification(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint32, AUTOMATIC) Flags_Cnt_T_b32
);
FUNC(void, I2CNXTR_CODE) I2c_DisableNotification(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint32, AUTOMATIC) Flags_Cnt_T_b32
);
FUNC(void, I2CNXTR_CODE) I2c_GenStartCond(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
);
FUNC(void, I2CNXTR_CODE) I2c_GenStopCond(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
);
FUNC(uint8, I2CNXTR_CODE) I2c_GetIntVect(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
);
FUNC(uint16, I2CNXTR_CODE) I2c_GetStatus(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str
);
FUNC(void, I2CNXTR_CODE) I2c_SetStatus(
	CONSTP2VAR(i2cctrlregs_t, AUTOMATIC, AUTOMATIC) I2cRegPtr_Cnt_T_str,
	VAR(uint16, AUTOMATIC) Status_Cnt_T_u16
);


/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/
#endif


