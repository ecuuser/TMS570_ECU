/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : DigMSB_Cfg.h
* Module Description: Configuration file of DigMSB module
* Product           : Gen II Plus - EA3.0
* Author            : Selva Sengottaiyan
*****************************************************************************/

#ifndef DIGMSB_CFG_H
#define DIGMSB_CFG_H


#include "Dma.h"
#include "CDD_Data.h"
#include "SpiNxt.h"


#define DigMSB_Read_MtrPosPolarity_Cnt_s08(ptr)				*(ptr) = CDD_MtrPosPolarity_Cnt_G_s08[CDD_AppDataFwdPthAccessBfr_Cnt_G_u16]

#define DigMSB_Write_MechMtrPos1_Rev_u0p16(val)				CDD_MechMtrPos1_Rev_G_u0p16[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define DigMSB_Write_SysCMechMtrPos1_Rev_u0p16(val)			(void)0
#define DigMSB_Write_SysCorrectedElecMtrPos_Rev_u0p16(val)	CDD_SysCCorrectedElecMtrPos_Rev_G_u0p16[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define DigMSB_Write_MechMtrPos1TimeStamp_uSec_u32(val)		CDD_MechMtrPos1TimeStamp_uSec_G_u32[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define DigMSB_Write_MechMtrPos2TimeStamp_uSec_u32(val)		CDD_MechMtrPos2TimeStamp_uSec_G_u32[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define DigMSB_Write_CorrectedElecMtrPos_Rev_u0p16(val)		CDD_CorrectedElecMtrPos_Rev_G_u0p16[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)

#define DigMSB_Write_UncorrMechMtrPos1_Rev_u0p16(val)		CDD_UncorrMechMtrPos1_Rev_G_u0p16[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define DigMSB_Write_CumMechMtrPos_Rev_s15p16(val)			CDD_CumMechMtrPos_Rev_s15p16[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define DigMSB_Write_Die1RxError_Cnt_u16(val)				CDD_Die1RxError_Cnt_G_u16[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define DigMSB_Write_Die2RxError_Cnt_u16(val)				CDD_Die2RxError_Cnt_G_u16[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define DigMSB_Write_Die1RxRevCtr_Cnt_u16(val)				CDD_Die1RxRevCtr_Cnt_G_u16[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define DigMSB_Write_Die2RxRevCtr_Cnt_u16(val)				CDD_Die2RxRevCtr_Cnt_G_u16[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define DigMSB_Write_Die1RxMtrPos_Cnt_u16(val)				CDD_Die1RxMtrPos_Cnt_G_u16[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define DigMSB_Write_Die2RxMtrPos_Cnt_u16(val)				CDD_Die2RxMtrPos_Cnt_G_u16[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define DigMSB_Write_RxMtrPos1ParityAccum_Cnt_u16(val)		CDD_RxMtrPosParityAccum_Cnt_G_u16[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define DigMSB_Write_RxMtrPos1UnderVoltgFltAccum_Cnt_u16(val) CDD_Die1UnderVoltgFltAccum_Cnt_G_u16[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)

#define	MSB1GetData(ptr)			(ptr)[0] = DMAData_G_str.FastSPI_Cnt_u16[0]; \
									(ptr)[1] = DMAData_G_str.FastSPI_Cnt_u16[1]; \
									(ptr)[2] = DMAData_G_str.FastSPI_Cnt_u16[2]
#define MSB1SetData(ptr)			mibspiSetData(mibspiREG3, TRANS_GRP_0, ptr)
#define	MSB2GetData(ptr)			(ptr)[0] = DMAData_G_str.SlowSPI_Cnt_u16[0]; \
									(ptr)[1] = DMAData_G_str.SlowSPI_Cnt_u16[1]; \
									(ptr)[2] = DMAData_G_str.SlowSPI_Cnt_u16[2]
#define MSB2SetData(ptr)			mibspiSetData(mibspiREG5, TRANS_GRP_0, ptr)
#define MSB1EnableDataTransfer()	mibspiTransfer(mibspiREG3, TRANS_GRP_0)
#define MSB2EnableDataTransfer()	mibspiTransfer(mibspiREG5, TRANS_GRP_0)
#define MSB1GetConfig(ptr)			mibspiGetData(mibspiREG3, TRANS_GRP_1, ptr)
#define MSB1SetConfig(ptr)			mibspiSetData(mibspiREG3, TRANS_GRP_1, ptr)
#define MSB2GetConfig(ptr)			mibspiGetData(mibspiREG5, TRANS_GRP_1, ptr)
#define MSB2SetConfig(ptr)			mibspiSetData(mibspiREG5, TRANS_GRP_1, ptr)
#define MSB1EnableConfigTransfer()	mibspiTransfer(mibspiREG3, TRANS_GRP_1)
#define MSB2EnableConfigTransfer()	mibspiTransfer(mibspiREG5, TRANS_GRP_1)


#endif
