/*****************************************************************************
* Copyright 2014 Nexteer
* Nexteer Confidential
*
* Module File Name  : efc_regs.h
* Module Description: EFC (eFuse) Peripheral Registers
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
******************************************************************************/


#ifndef EFC_REGS_H
#define EFC_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct efcctrlregs
{
	uint32 INSTRUCTION;    			/* 0x0	INSTRUCTION AN DUMPWORD REGISTER	*/
	uint32 ADDRESS;			    	/* 0x4 ADDRESS REGISTER    					*/
	uint32 DATA_UPPER;			    /* 0x8 DATA UPPER REGISTER    				*/
	uint32 DATA_LOWER;				/* 0xc DATA LOWER REGISTER    				*/
	uint32 SYSTEM_CONFIG;			/* 0x10 SYSTEM CONFIG REGISTER    			*/
	uint32 SYSTEM_STATUS;			/* 0x14 SYSTEM STATUS REGISTER    			*/
	uint32 ACCUMULATOR;				/* 0x18 ACCUMULATOR REGISTER    			*/
	uint32 BOUNDARY;			    /* 0x1C BOUNDARY REGISTER 					*/
	uint32 KEY_FLAG;			    /* 0x20 KEY FLAG REGISTER    				*/
	uint32 KEY;			        	/* 0x24	KEY REGISTER 						*/
	uint32 : 32;				    /* 0x28	RESERVED 							*/
	uint32 PINS;				    /* 0x2C  PINS REGISTER						*/
	uint32 CRA;				        /* 0x30  CRA								*/
	uint32 READ;				    /* 0x34 READ REGISTER						*/
	uint32 PROGRAMME;				/* 0x38 PROGRAMME REGISTER					*/
	uint32 ERROR;				    /* 0x3C	ERROR STATUS REGISTER				*/
	uint32 SINGLE_BIT;				/* 0x40	SINGLE BIT ERROR 					*/
	uint32 TWO_BIT_ERROR;			/* 0x44	DOUBLE BIT ERROR 					*/
	uint32 SELF_TEST_CYCLES;		/* 0x48	SELF TEST CYCLEX					*/
	uint32 SELF_TEST_SIGN;			/* 0x4C SELF TEST SIGNATURE					*/
} efcctrlregs_t;

#define efcREG   ((efcctrlregs_t *)0xFFF8C000UL)

#endif

