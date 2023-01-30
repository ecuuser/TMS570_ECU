/*****************************************************************************
* Copyright 2014 Nexteer
* Nexteer Confidential
*
* Module File Name  : n2het_regs.h
* Module Description: N2HET (High-End Timer) Peripheral Registers
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue May 31 09:10:25 2011 % 
* %version:          2 %
* %derived_by:       nz63rn %
*---------------------------------------------------------------------------------------------------------------------
* Date      Rev      Author         Change Description                                                        SCR #
* -------   -------  --------  ---------------------------------------------------------------------------  ----------
* 06/24/14  2        KMC 	     QAC cleanup                                                                  10551  
*--------------------------------------------------------------------------------------------------------------------*/

#ifndef N2HET_REGS_H
#define N2HET_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct n2hetctrlregs
{

    uint32 NHETGCR;     	/**< 0x0000: Global control register              */
    uint32 NHETPFR;     	/**< 0x0004: Prescale factor register             */
    uint32 NHETADDR;    	/**< 0x0008: Current address register             */
    uint32 NHETOFF1;    	/**< 0x000C: Interrupt offset register 1          */
    uint32 NHETOFF2;    	/**< 0x0010: Interrupt offset register 2          */
    uint32 NHETINTENAS; 	/**< 0x0014: Interrupt enable set register        */
    uint32 NHETINTENAC; 	/**< 0x0018: Interrupt enable clear register      */
    uint32 NHETEXC1;    	/**< 0x001C: Exeption control register 1          */
    uint32 NHETEXC2;    	/**< 0x0020: Exeption control register 2          */
    uint32 NHETPRY;     	/**< 0x0024: Interrupt priority register          */
    uint32 NHETFLG;     	/**< 0x0028: Interrupt flag register              */
    uint32 NHETAND;     	/**< 0x002C: AND share control register           */
    uint32 : 32U;   	/**< 0x0030: Reserved                             */
    uint32 NHETHRSH;    	/**< 0x0034: High resoltion share register        */
    uint32 NHETXOR;     	/**< 0x0038: XOR share register                   */
    uint32 NHETREQENS;  	/**< 0x003C: Request enable set register          */
    uint32 NHETREQENC;  	/**< 0x0040: Request enable clear register        */
    uint32 NHETREQDS;   	/**< 0x0044: Request destination select register  */
    uint32 : 32U;   	/**< 0x0048: Reserved                             */
    uint32 NHETDIR;     	/**< 0x004C: Direction register                   */
    uint32 NHETDIN;     	/**< 0x0050: Data input register                  */
    uint32 NHETDOUT;    	/**< 0x0054: Data output register                 */
    uint32 NHETDSET;    	/**< 0x0058: Data output set register             */
    uint32 NHETDCLR;    	/**< 0x005C: Data output clear register           */
    uint32 NHETPDR;     	/**< 0x0060: Open drain register                  */
    uint32 NHETPULDIS;  	/**< 0x0064: Pull disable register                */
    uint32 NHETPSL;     	/**< 0x0068: Pull select register                 */
    uint32 : 32U;   	/**< 0x006C: Reserved                             */
    uint32 : 32U;   	/**< 0x0070: Reserved                             */
    uint32 NHETPCR;   	/**< 0x0074: Parity control register              */
    uint32 NHETPAR;     	/**< 0x0078: Parity address register              */
    uint32 NHETPPR;     	/**< 0x007C: Parity pin select register           */
    uint32 NHETSFPRLD;  	/**< 0x0080: Suppression filter preload register  */
    uint32 NHETSFENA;   	/**< 0x0084: Suppression filter enable register   */
    uint32 : 32U;   	/**< 0x0088: Reserved                             */
    uint32 NHETLBPSEL;  	/**< 0x008C: Loop back pair select register       */
    uint32 NHETLBPDIR;  	/**< 0x0090: Loop back pair direction register    */
    uint32 NHETPINDIS;  	/**< 0x0094: Pin disable register                 */

} n2hetctrlregs_t;

#define NHET0 ((n2hetctrlregs_t *) 0xFFF7B800UL)
#define NHET1 ((n2hetctrlregs_t *) 0xFFF7B900UL)

#endif
