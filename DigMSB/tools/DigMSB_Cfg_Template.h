
/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Sa_ DIGMSB_Cfg.h
* Module Description: Configuration file of DiagMgr module
* Product           : Gen II Plus - EA3.0
* Generator         : artt 2.0.2.0
* Generation Time   : 30.11.2012 08:09:43
*****************************************************************************/
/* Version Control:
 * Date Created:      Fri Jul 13 18:34:17 2012
 * %version:          6 %
 * %date_modified:    Tue Dec  3 09:39:04 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 07/13/13   1       Selva      Initial template creation
 * 08/08/13   2       Selva      Template Updated
 * 12/02/13   3       OT         Updates for FDD 50A v4
 * 04/07/14   4       Selva      Updates for FDD 50A v5 prerelease
 * 04/27/14   6       Selva      Updates for FDD 50A v6
 * 02/06/15   7       Rijvi      Updated per FDD rev.008                							           12997
 */

#ifndef  DIGMSB_CFG_H
#define  DIGMSB_CFG_H


/*******************************************************************************
**                      Define Section                                       **
*******************************************************************************/

#define	 DigMSB_Read_MtrPosPolarity_Cnt_s08(ptr)               *ptr=

/* Map the outputs back to 2ms RTE using buffering. */

#define	DigMSB_Write_MechMtrPos1_Rev_u0p16(Var)							(Var) = (Var)                                       /***Also Used in 62.5uS  of Motor Velocity***/
#define	DigMSB_Write_SysCMechMtrPos1_Rev_u0p16(Var)						(Var) = (Var)
#define	DigMSB_Write_SysCorrectedElecMtrPos_Rev_u0p16(Var)				(Var) = (Var)
#define	DigMSB_Write_MechMtrPos1TimeStamp_uSec_u32(Var)					(Var) = (Var)                                       /***Also Used in 62.5uS of Motor Velocity ***/
#define	DigMSB_Write_MechMtrPos2TimeStamp_uSec_u32(Var)					(Var) = (Var)
/*------------------------------------------------*/
#define	DigMSB_Write_CorrectedElecMtrPos_Rev_u0p16(Var)					(Var) = (Var)                                       /***Used in 62.5uS  of Motor Current  Measurement ***/


/****Used in 2ms of DigMSB***/
#define	DigMSB_Write_UncorrMechMtrPos1_Rev_u0p16(Var)					(Var) = (Var)
#define	DigMSB_Write_CumMechMtrPos_Rev_s15p16(Var)						(Var) = (Var)
#define	DigMSB_Write_Die1RxError_Cnt_u16(Var)							(Var) = (Var)
#define	DigMSB_Write_Die2RxError_Cnt_u16(Var)							(Var) = (Var)
#define	DigMSB_Write_Die1RxRevCtr_Cnt_u16(Var)							(Var) = (Var)
#define	DigMSB_Write_Die2RxRevCtr_Cnt_u16(Var)							(Var) = (Var)
#define	DigMSB_Write_Die1RxMtrPos_Cnt_u16(Var)							(Var) = (Var)
#define	DigMSB_Write_Die2RxMtrPos_Cnt_u16(Var)							(Var) = (Var)
#define	DigMSB_Write_RxMtrPos1ParityAccum_Cnt_u16(Var)   				(Var) = (Var)
#define DigMSB_Write_RxMtrPos1UnderVoltgFltAccum_Cnt_u16(Var)            (Var) = (Var)

/* macro definitions for SPI functions using SpiNxt */
#define	 MSB1GetData(ptr) mibspiGetData (mibspiREG3, TRANS_GRP_0, ptr)    /* Map SPI3 function name  arg1 -MIBSPI3 name    arg2    group notification      arg3 - Transmit data*/
#define	 MSB1SetData(ptr) mibspiSetData (mibspiREG3, TRANS_GRP_0, ptr)    /* Map SPI3 function name  arg1 -MIBSPI3 name    arg2    group notification      arg3 - receive data*/
#define	 MSB2GetData(ptr) mibspiGetData (mibspiREG5, TRANS_GRP_0, ptr)    /* Map SPI5 function name  arg1 -MIBSPI5 name    arg2    group notification      arg3 - Transmit data*/
#define	 MSB2SetData(ptr) mibspiSetData (mibspiREG5, TRANS_GRP_0, ptr)    /* Map SPI5 function name  arg1 -MIBSPI5 name    arg2    group notification      arg3 - receive data*/
#define  MSB1EnableDataTransfer() mibspiTransfer (mibspiREG3, TRANS_GRP_0)  /* Enable MIBSPI3 transfer group 0 */
#define  MSB2EnableDataTransfer() mibspiTransfer (mibspiREG5, TRANS_GRP_0)  /* Enable MIBSPI5 transfer group 0 */
#define	 MSB1GetConfig(ptr) mibspiGetData (mibspiREG3, TRANS_GRP_1, ptr)    /* Map SPI3 function name  arg1 -MIBSPI3 name    arg2    group notification      arg3 - Transmit data*/
#define	 MSB1SetConfig(ptr) mibspiSetData (mibspiREG3, TRANS_GRP_1, ptr)    /* Map SPI3 function name  arg1 -MIBSPI3 name    arg2    group notification      arg3 - receive data*/
#define	 MSB2GetConfig(ptr) mibspiGetData (mibspiREG5, TRANS_GRP_1, ptr)    /* Map SPI5 function name  arg1 -MIBSPI5 name    arg2    group notification      arg3 - Transmit data*/
#define	 MSB2SetConfig(ptr) mibspiSetData (mibspiREG5, TRANS_GRP_1, ptr)    /* Map SPI5 function name  arg1 -MIBSPI5name    arg2    group notification      arg3 - receive data*/
#define  MSB1EnableConfigTransfer() mibspiTransfer (mibspiREG3, TRANS_GRP_1)  /* Enable MIBSPI3 transfer group 1 */
#define  MSB2EnableConfigTransfer() mibspiTransfer (mibspiREG5, TRANS_GRP_1)  /* Enable MIBSPI5 transfer group 1 */

/*** End of file **************************************************************/

#endif /* DIGMSBSIGCORR_CFG_H */