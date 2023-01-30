/***********************************************************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : I2cNxtr_Cfg.h
* Module Description: I2C Driver: Nexteer implementation.
* Product           : Gen II Plus - EA3.0
* Author            : Jared Julien
*
***********************************************************************************************************************/
/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/
/* Version Control:
 * Date Created:      Thur Aug 8 11:20:41 2013 %
 * %version:          1 %
 * %derived_by:       jzh87w %
 * %date_modified:    Mon Sep 23 12:34:04 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 08/08/13  1        Jared     New template file for configuring Nexteer I2C driver                            8850
 */
/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/
#ifndef __I2CNXTR_H__
#define __I2CNXTR_H__
/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/

/*** I2C Interrupt Notification Function Prototype ***/
/* Define this function in the receiving code to accept I2C interrupt notifications enabled by calling the
 * i2cEnableNotification() function.
 */
extern FUNC(void, AUTOMATIC) DigColPsInt_InterruptNotification(VAR(uint16, AUTOMATIC) Flags_Cnt_T_b16);


/* I2C Transmit and Receive buffer size
 * Set this to the maximum data transfer in bytes.
 * - Does not include slave address, only payload.
 */
#define D_COMMBUFFERSIZE_CNT_U08    3U


/* Use this macro to map the callback function of the above format in the receiving code file. */
#define I2c_Notification     DigColPsInt_InterruptNotification


/* The I2C register set to use for communication */
#define D_I2CREG_STRCPTR	i2cREG1


/* VCLK value used to calculate the baud rate.  VCLK is typically 1/2 the oscillator frequency */
#define D_VCLK_HZ_F32  (80.0f * 1000000.0f)


/***********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 **********************************************************************************************************************/
#endif
