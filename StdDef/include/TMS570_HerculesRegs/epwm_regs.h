/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : epwm_regs.h
* Module Description: ePWM (Enhanced Pulse Width Modulator) Peripheral Registers
* Product           : Gen II Plus - EA3.0
* Author            : Kathleen Creager
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Mon Oct 21 12:50:19 2013 % 
* %version:          1 %
* %derived_by:       nz63rn %
* %date_modified:    Mon Oct 21 12:50:19 2013 % 
*---------------------------------------------------------------------------*/
/**********************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description              			SCR #
-------   -------  --------  -----------------------------------  		----------
10/21/13   1.0      KMC      Initial Creation -- moved register    			10549
                             definitions out of component ePWM, added
							 "volatile" keyword, changed etpwmBASE typedef 
							 struct declaration based on version 3.06.00 of
							 TI Halcogen ETPWM Register Layer Header File
							 reg_etpwm.h.
***********************************************************************************/

#ifndef EPWM_REGS_H
#define EPWM_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct etpwmBASE
{
    uint16 TBSTS;           /**<  0x0000 Time-Base Status Register*/
	uint16 TBCTL;           /**<  0x0002 Time-Base Control Register*/
    uint16 TBPHS;           /**<  0x0004 Time-Base Phase Register*/
    uint16   rsvd1;         /**<  0x0006 Reserved*/
    uint16 TBPRD;           /**<  0x0008 Time-Base Period Register*/
    uint16 TBCTR;           /**<  0x000A Time-Base Counter Register*/
    uint16 CMPCTL;          /**<  0x000C Counter-Compare Control Register*/
    uint16   rsvd2;         /**<  0x000E Reserved*/
    uint16 CMPA;            /**<  0x0010 Counter-Compare A Register*/
    uint16   rsvd3;         /**<  0x0012 Reserved*/
    uint16 AQCTLA;          /**<  0x0014 Action-Qualifier Control Register for Output A (ETPWMxA)*/
    uint16 CMPB;            /**<  0x0016 Counter-Compare B Register*/
    uint16 AQSFRC;          /**<  0x0018 Action-Qualifier Software Force Register*/
    uint16 AQCTLB;          /**<  0x001A Action-Qualifier Control Register for Output B (ETPWMxB)*/
    uint16 DBCTL;           /**<  0x001C Dead-Band Generator Control Register*/
    uint16 AQCSFRC;         /**<  0x001E Action-Qualifier Continuous S/W Force Register Set*/
    uint16 DBFED;           /**<  0x0020 Dead-Band Generator Falling Edge Delay Count Register*/
    uint16 DBRED;           /**<  0x0022 Dead-Band Generator Rising Edge Delay Count Register*/
    uint16 TZDCSEL;         /**<  0x0024 Trip Zone Digital Compare Select Register*/
    uint16 TZSEL;           /**<  0x0026 Trip-Zone Select Register*/
    uint16 TZEINT;          /**<  0x0028 Trip-Zone Enable Interrupt Register*/
    uint16 TZCTL;           /**<  0x002A Trip-Zone Control Register*/
    uint16 TZCLR;           /**<  0x002C Trip-Zone Clear Register*/
    uint16 TZFLG;           /**<  0x002E Trip-Zone Flag Register*/
    uint16 ETSEL;           /**<  0x0030 Event-Trigger Selection Register*/
    uint16 TZFRC;           /**<  0x0032 Trip-Zone Force Register*/
    uint16 ETFLG;           /**<  0x0034 Event-Trigger Flag Register*/
    uint16 ETPS;            /**<  0x0036 Event-Trigger Pre-Scale Register*/
    uint16 ETFRC;           /**<  0x0038 Event-Trigger Force Register*/
    uint16 ETCLR;           /**<  0x003A Event-Trigger Clear Register*/
    uint16   rsvd4;         /**<  0x003C Reserved*/
    uint16 PCCTL;           /**<  0x003E PWM-Chopper Control Register*/
	uint16   rsvd5[16U];    /**<  0x0040 Reserved*/
    uint16 DCACTL;          /**<  0x0060 Digital Compare A Control Register*/
    uint16 DCTRIPSEL;       /**<  0x0062 Digital Compare Trip Select Register*/
    uint16 DCFCTL;          /**<  0x0064 Digital Compare Filter Control Register*/
    uint16 DCBCTL;          /**<  0x0066 Digital Compare B Control Register*/
    uint16 DCFOFFSET;       /**<  0x0068 Digital Compare Filter Offset Register*/
    uint16 DCCAPCTL;        /**<  0x006A Digital Compare Capture Control Register*/
    uint16 DCFWINDOW;       /**<  0x006C Digital Compare Filter Window Register*/
    uint16 DCFOFFSETCNT;    /**<  0x006E Digital Compare Filter Offset Counter Register*/
    uint16 DCCAP;           /**<  0x0070 Digital Compare Counter Capture Register*/
    uint16 DCFWINDOWCNT;    /**<  0x0072 Digital Compare Filter Window Counter Register*/
} etpwmBASE_t;


/* ePWM Register Base Addresses */
#define ePWM1 ((etpwmBASE_t *)0xFCF78C00UL)
#define ePWM2 ((etpwmBASE_t *)0xFCF78D00UL)
#define ePWM3 ((etpwmBASE_t *)0xFCF78E00UL)
#define ePWM4 ((etpwmBASE_t *)0xFCF78F00UL)
#define ePWM5 ((etpwmBASE_t *)0xFCF79000UL)
#define ePWM6 ((etpwmBASE_t *)0xFCF79100UL)
#define ePWM7 ((etpwmBASE_t *)0xFCF79200UL)

#endif


