/*****************************************************************************
* Copyright 2014 Nexteer
* Nexteer Confidential
*
* Module File Name  : tiotp_regs.h
* Module Description: TI One-Time Programmable (OTP) Registers
* Product           : Gen II Plus - EA3.0
* Author            : Lovepreet Kaur
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* %version:          2 %
* %derived_by:       nz63rn %
*---------------------------------------------------------------------------------------------------------------------
* Date      Rev      Author         Change Description                                                        SCR #
* -------   -------  --------  ---------------------------------------------------------------------------  ----------
* 06/24/14  2        KMC 	     QAC cleanup                                                                  10551  
*--------------------------------------------------------------------------------------------------------------------*/

#ifndef TIOTP_REGS_H
#define TIOTP_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct tiotpregs
{
    uint32 FBSS;  	/* 0x0158 Flash Bank and Sector Sizes*/
    uint32 PMS;		/* 0x015C Package and Memory Size */
    uint32 : 32U;   /* 0x0160 Reserved*/
    uint32 : 32U;   /* 0x0164 Reserved*/
    uint32 : 32U;  	/* 0x0168 Reserved*/
    uint32 : 32U;   /* 0x016C Reserved*/
    uint32 : 32U;   /* 0x0170 Reserved*/
    uint32 : 32U;   /* 0x0174 Reserved*/
	uint32 : 32U;   /* 0x0178 Reserved*/
	uint32 : 32U;   /* 0x017C Reserved*/
	uint32 : 32U;   /* 0x0180 Reserved*/
	uint32 : 32U;   /* 0x0184 Reserved*/
	uint32 : 32U;   /* 0x0188 Reserved*/
	uint32 : 32U;   /* 0x018C Reserved*/
	uint32 : 32U;   /* 0x0190 Reserved*/
	uint32 : 32U;   /* 0x0194 Reserved*/
	uint32 : 32U;   /* 0x0198 Reserved*/
	uint32 : 32U;   /* 0x019C Reserved*/
	uint32 : 32U;   /* 0x01A0 Reserved*/
	uint32 : 32U;   /* 0x01A4 Reserved*/
	uint32 : 32U;   /* 0x01A8 Reserved*/
	uint32 : 32U;   /* 0x01AC Reserved*/
	uint32 : 32U;   /* 0x01B0 Reserved*/
	uint32 LTMH;	/* 0x01B4 LPO Trim and Max HCLK */
	uint32 : 32U;   /* 0x01B8 Reserved*/
	uint32 : 32U;   /* 0x01BC Reserved*/
	uint32 : 32U;   /* 0x01C0 Reserved*/
	uint32 : 32U;   /* 0x01C4 Reserved*/
	uint32 : 32U;   /* 0x01C8 Reserved*/
	uint32 : 32U;   /* 0x01CC Reserved*/
	uint32 : 32U;   /* 0x01D0 Reserved*/
	uint32 : 32U;   /* 0x01D4 Reserved*/
	uint32 : 32U;   /* 0x01D8 Reserved*/
	uint32 : 32U;   /* 0x01DC Reserved*/
	uint32 PNS1;    /* 0x01E0 Part Number Symbolization bytes 0 to 3*/
	uint32 PNS2;    /* 0x01E4 Part Number Symbolization bytes 4 to 7*/
	uint32 PNS3;    /* 0x01E8 Part Number Symbolization bytes 8 to 11*/
	uint32 PNS4;    /* 0x01EC Part Number Symbolization bytes 12 to 15*/
	uint32 PNS5;    /* 0x01F0 Part Number Symbolization bytes 16 to 19*/
	uint32 PNS6;    /* 0x01F4 Part Number Symbolization bytes 20 to 23*/
	uint32 PNS7;    /* 0x01F8 Part Number Symbolization bytes 24 to 27*/
	uint32 PNS8;    /* 0x01FC Part Number Symbolization bytes 28 to 31*/
	
} tiotpregs_t;

#define tiOTP ((tiotpregs_t *)(0xF0080158UL))

#endif
