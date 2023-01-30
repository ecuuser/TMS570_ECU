/*****************************************************************************
* Copyright 2011 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : EPWM_CFG.h
* Module Description: This file contains a stub header for UTP and QAC 
*                     projects
* Product           : Gen II Plus EA3.0
* Author            : Selva Sengottaiyan
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue Dec  7 20:09:21 2010
* %version:          1 %
* %derived_by:       nzx5jd %
* %date_modified:    Thu Aug  1 16:43:40 2013 % 
*---------------------------------------------------------------------------*/

#ifndef EPWM_CFG_H
#define EPWM_CFG_H


#include "CDD_Data.h"
#include "Dma.h"


#define D_CONFIGHETREGDMA_CNT_U32  			1ul

#define ePWM_Read_PWMPeriod_u16(ptr)		*(ptr) = CDD_PWMPeriod_Cnt_G_u16

#define ePWM_Read_DCPhsAComp_u16(ptr)		*(ptr) = CDD_DCPhsComp_Cnt_G_u16[0u]
#define ePWM_Read_DCPhsBComp_u16(ptr)		*(ptr) = CDD_DCPhsComp_Cnt_G_u16[1u]
#define ePWM_Read_DCPhsCComp_u16(ptr)		*(ptr) = CDD_DCPhsComp_Cnt_G_u16[2u]
#define ePWM_Read_ePWM4CMPB_Cnt_u16(ptr)	*(ptr) = CDD_ePWM4CMPB_Cnt_G_u16

#define ePWM_Write_ePWM1CMPA_Cnt_u16(val)	DMAData_G_str.PWMCmp_Cnt_u16[0][0] = (val)
#define ePWM_Write_ePWM1CMPB_Cnt_u16(val)	DMAData_G_str.PWMCmp_Cnt_u16[0][1] = (val)
#define ePWM_Write_ePWM2CMPA_Cnt_u16(val)	DMAData_G_str.PWMCmp_Cnt_u16[1][0] = (val)
#define ePWM_Write_ePWM2CMPB_Cnt_u16(val)	DMAData_G_str.PWMCmp_Cnt_u16[1][1] = (val)
#define ePWM_Write_ePWM3CMPA_Cnt_u16(val)	DMAData_G_str.PWMCmp_Cnt_u16[2][0] = (val)
#define ePWM_Write_ePWM3CMPB_Cnt_u16(val)	DMAData_G_str.PWMCmp_Cnt_u16[2][1] = (val)
#define ePWM_Write_ePWM4CMPA_Cnt_u16(val)	DMAData_G_str.PWMCmp_Cnt_u16[3][0] = (val)
#define ePWM_Write_ePWM4CMPB_Cnt_u16(val)	DMAData_G_str.PWMCmp_Cnt_u16[3][1] = (val)

#define Nhet1_Write_PWMPeriod_Cnt_u16(val)	DMAData_G_str.PWMPeriod_Cnt_u32 = (uint32)(val)


#endif

