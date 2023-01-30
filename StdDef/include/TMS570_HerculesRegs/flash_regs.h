/*****************************************************************************
* Copyright 2014 Nexteer
* Nexteer Confidential
*
* Module File Name  : flash_regs.h
* Module Description: Flash Wrapper Peripheral Registers
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue May 31 09:10:25 2011 % 
* %version:          2 %
* %derived_by:       nz63rn %
*---------------------------------------------------------------------------*/
/*****************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description              SCR #
-------   -------  --------  -----------------------------------  ----------
06/24/14   2        KMC 	 QAC cleanup                           10551  
08/28/14   3        PS       Added EE_CTRL1                        12394
******************************************************************************/

#ifndef FLASH_REGS_H
#define FLASH_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct flashctrlregs
{
    uint32 FRDCNTL;     /* 0x0000 */
    uint32 FSPRD;       /* 0x0004 */
    uint32 FEDACCTRL1;  /* 0x0008 */
    uint32 FEDACCTRL2;  /* 0x000C */
    uint32 FCORERRCNT;  /* 0x0010 */
    uint32 FCORERRADD;  /* 0x0014 */
    uint32 FCORERRPOS;  /* 0x0018 */
    uint32 FEDACSTATUS; /* 0x001C */
    uint32 FUNCERRADD;  /* 0x0020 */
    uint32 FEDACSDIS;   /* 0x0024 */
    uint32 FPRIMADDTAG; /* 0x0028 */
    uint32 FREDUADDTAG; /* 0x002C */
    uint32 FBPROT;      /* 0x0030 */
    uint32 FBSE;        /* 0x0034 */
    uint32 FBBUSY;      /* 0x0038 */
    uint32 FBAC;        /* 0x003C */
    uint32 FBFALLBACK;  /* 0x0040 */
    uint32 FBPRDY;      /* 0x0044 */
    uint32 FPAC1;       /* 0x0048 */
    uint32 FPAC2;       /* 0x004C */
    uint32 FMAC;        /* 0x0050 */
    uint32 FMSTAT;      /* 0x0054 */
    uint32 FEMUDMSW;    /* 0x0058 */
    uint32 FEMUDLSW;    /* 0x005C */
    uint32 FEMUECC;     /* 0x0060 */
    uint32 FLOCK;       /* 0x0064 */
    uint32 FEMUADDR;    /* 0x0068 */
    uint32 FDIAGCTRL;   /* 0x006C */
    uint32 FRAWDATAH;   /* 0x0070 */
    uint32 FRAWDATAL;   /* 0x0074 */
    uint32 FRAWECC;     /* 0x0078 */
    uint32 FPAROVR;     /* 0x007C */
    uint32 FVREADCT;    /* 0x0080 */
    uint32 FVHVCT1;     /* 0x0084 */
    uint32 FVHVCT2;     /* 0x0088 */
    uint32 FVNVCT;      /* 0x008C */
    uint32 FVPPCT;      /* 0x0090 */
    uint32 FVWLCT;      /* 0x0094 */
    uint32 FEFUSE;      /* 0x0098 */
    uint32 : 32U;       /* 0x009C */
    uint32 : 32U;       /* 0x00A0 */
    uint32 : 32U;       /* 0x00A4 */
    uint32 : 32U;       /* 0x00A8 */
    uint32 : 32U;       /* 0x00AC */
    uint32 : 32U;       /* 0x00B0 */
    uint32 : 32U;       /* 0x00B4 */
    uint32 : 32U;       /* 0x00B8 */
    uint32 : 32U;       /* 0x00BC */
    uint32 FEDACSDIS2;  /* 0x00C0 */
    uint32 : 32U;       /* 0x00C4 */
    uint32 : 32U;       /* 0x00C8 */
    uint32 : 32U;       /* 0x00CC */
    uint32 : 32U;       /* 0x00D0 */
    uint32 : 32U;       /* 0x00D4 */
    uint32 : 32U;       /* 0x00D8 */
    uint32 : 32U;       /* 0x00DC */
    uint32 : 32U;       /* 0x00E0 */
    uint32 : 32U;       /* 0x00E4 */
    uint32 : 32U;       /* 0x00E8 */
    uint32 : 32U;       /* 0x00EC */
    uint32 : 32U;       /* 0x00F0 */
    uint32 : 32U;       /* 0x00F4 */
    uint32 : 32U;       /* 0x00F8 */
    uint32 : 32U;       /* 0x00FC */
    uint32 FBSTROBES;   /* 0x0100 */
    uint32 FPSTROBES;   /* 0x0104 */
    uint32 FBMODE;      /* 0x0108 */
    uint32 FTCR;        /* 0x010C */
    uint32 FADDR;       /* 0x0110 */
    uint32 FWRITE;      /* 0x0114 */
    uint32 FCBITSEL;    /* 0x0118 */
    uint32 FTCTRL;      /* 0x011C */
    uint32 FWPWRITE0;   /* 0x0120 */
    uint32 FWPWRITE1;   /* 0x0124 */
    uint32 FWPWRITE2;   /* 0x0128 */
    uint32 FWPWRITE3;   /* 0x012C */
    uint32 FWPWRITE4;   /* 0x0130 */
	uint32 : 32U;		/* 0x0134 */
	uint32 : 32U;		/* 0x0138 */
	uint32 : 32U;		/* 0x013C */
	uint32 : 32U;		/* 0x0140 */
	uint32 : 32U;		/* 0x0144 */
	uint32 : 32U;		/* 0x0148 */
	uint32 : 32U;		/* 0x014C */
	uint32 : 32U;		/* 0x0150 */
	uint32 : 32U;		/* 0x0154 */
	uint32 : 32U;		/* 0x0158 */
	uint32 : 32U;		/* 0x015C */
	uint32 : 32U;		/* 0x0160 */
	uint32 : 32U;		/* 0x0164 */
	uint32 : 32U;		/* 0x0168 */
	uint32 : 32U;		/* 0x016C */
	uint32 : 32U;		/* 0x0170 */
	uint32 : 32U;		/* 0x0174 */
	uint32 : 32U;		/* 0x0178 */
	uint32 : 32U;		/* 0x017C */
	uint32 : 32U;		/* 0x0180 */
	uint32 : 32U;		/* 0x0184 */
	uint32 : 32U;		/* 0x0188 */
	uint32 : 32U;		/* 0x018C */
	uint32 : 32U;		/* 0x0190 */
	uint32 : 32U;		/* 0x0194 */
	uint32 : 32U;		/* 0x0198 */
	uint32 : 32U;		/* 0x019C */
	uint32 : 32U;		/* 0x01A0 */
	uint32 : 32U;		/* 0x01A4 */
	uint32 : 32U;		/* 0x01A8 */
	uint32 : 32U;		/* 0x01AC */
	uint32 : 32U;		/* 0x01B0 */
	uint32 : 32U;		/* 0x01B4 */
	uint32 : 32U;		/* 0x01B8 */
	uint32 : 32U;		/* 0x01BC */
	uint32 : 32U;		/* 0x01C0 */
	uint32 : 32U;		/* 0x01C4 */
	uint32 : 32U;		/* 0x01C8 */
	uint32 : 32U;		/* 0x01CC */
	uint32 : 32U;		/* 0x01D0 */
	uint32 : 32U;		/* 0x01D4 */
	uint32 : 32U;		/* 0x01D8 */
	uint32 : 32U;		/* 0x01DC */
	uint32 : 32U;		/* 0x01E0 */
	uint32 : 32U;		/* 0x01E4 */
	uint32 : 32U;		/* 0x01E8 */
	uint32 : 32U;		/* 0x01EC */
	uint32 : 32U;		/* 0x01F0 */
	uint32 : 32U;		/* 0x01F4 */
	uint32 : 32U;		/* 0x01F8 */
	uint32 : 32U;		/* 0x01FC */
	uint32 : 32U;		/* 0x0200 */
	uint32 : 32U;		/* 0x0204 */
	uint32 : 32U;		/* 0x0208 */
	uint32 : 32U;		/* 0x020C */
	uint32 : 32U;		/* 0x0210 */
	uint32 : 32U;		/* 0x0214 */
	uint32 : 32U;		/* 0x0218 */
	uint32 : 32U;		/* 0x021C */
	uint32 : 32U;		/* 0x0220 */
	uint32 : 32U;		/* 0x0224 */
	uint32 : 32U;		/* 0x0228 */
	uint32 : 32U;		/* 0x022C */
	uint32 : 32U;		/* 0x0230 */
	uint32 : 32U;		/* 0x0234 */
	uint32 : 32U;		/* 0x0238 */
	uint32 : 32U;		/* 0x023C */
	uint32 : 32U;		/* 0x0240 */
	uint32 : 32U;		/* 0x0244 */
	uint32 : 32U;		/* 0x0248 */
	uint32 : 32U;		/* 0x024C */
	uint32 : 32U;		/* 0x0250 */
	uint32 : 32U;		/* 0x0254 */
	uint32 : 32U;		/* 0x0258 */
	uint32 : 32U;		/* 0x025C */
	uint32 : 32U;		/* 0x0260 */
	uint32 : 32U;		/* 0x0264 */
	uint32 : 32U;		/* 0x0268 */
	uint32 : 32U;		/* 0x026C */
	uint32 : 32U;		/* 0x0270 */
	uint32 : 32U;		/* 0x0274 */
	uint32 : 32U;		/* 0x0278 */
	uint32 : 32U;		/* 0x027C */
	uint32 : 32U;		/* 0x0280 */
	uint32 : 32U;		/* 0x0284 */
	uint32 FSM_WR_ENA;	/* 0x0288 */
	uint32 : 32U;		/* 0x028C */
	uint32 : 32U;		/* 0x0290 */
	uint32 : 32U;		/* 0x0294 */
	uint32 : 32U;		/* 0x0298 */
	uint32 : 32U;		/* 0x029C */
	uint32 : 32U;		/* 0x02A0 */
	uint32 : 32U;		/* 0x02A4 */
	uint32 : 32U;		/* 0x02A8 */
	uint32 : 32U;		/* 0x02AC */
	uint32 : 32U;		/* 0x02B0 */
	uint32 : 32U;		/* 0x02B4 */
	uint32 EEPROM_CONFIG;	/* 0x02B8 */
	uint32 : 32U;		/* 0x02BC */
	uint32 : 32U;		/* 0x02C0 */
	uint32 : 32U;		/* 0x02C4 */
	uint32 : 32U;		/* 0x02C8 */
	uint32 : 32U;		/* 0x02CC */
	uint32 : 32U;		/* 0x02D0 */
	uint32 : 32U;		/* 0x02D4 */
	uint32 : 32U;		/* 0x02D8 */
	uint32 : 32U;		/* 0x02DC */
	uint32 : 32U;		/* 0x02E0 */
	uint32 : 32U;		/* 0x02E4 */
	uint32 : 32U;		/* 0x02E8 */
	uint32 : 32U;		/* 0x02EC */
	uint32 : 32U;		/* 0x02F0 */
	uint32 : 32U;		/* 0x02F4 */
	uint32 : 32U;		/* 0x02F8 */
	uint32 : 32U;		/* 0x02FC */
	uint32 : 32U;		/* 0x0300 */
	uint32 : 32U;		/* 0x0304 */
	uint32 EE_CTRL1;    /* 0x0308 */
} flashctrlregs_t;

#define flashWREG ((flashctrlregs_t *)(0xFFF87000UL))

#endif
