/*****************************************************************************
* Copyright 2014 Nexteer
* Nexteer Confidential
*
* Module File Name  : dcan_regs.h
* Module Description: DCAN Peripheral Registers
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

#ifndef DCAN_REGS_H
#define DCAN_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct dcanctrlregs
{
    uint32      CTL;          /**< 0x0000: Control Register                       */
    uint32      ES;           /**< 0x0004: Error and Status Register              */
    uint32      ERRC;         /**< 0x0008: Error Counter Register                 */
    uint32      BTR;          /**< 0x000C: Bit Timing Register                    */
    uint32      INT;          /**< 0x0010: Interrupt Register                     */
    uint32      TEST;         /**< 0x0014: Test Register                          */
    uint32      : 32U;        /**< 0x0018: Reserved                               */
    uint32      PERR;         /**< 0x001C: Parity/SECDED Error Code Register      */
    uint32      REL;          /**< 0x0020: Core Release Register                  */
    uint32      ECCDIAG;      /**< 0x0024: ECC Diagnostic Register                */
    uint32      ECCDIADSTAT;  /**< 0x0028: ECC Diagnostic Status Register         */
    uint32      : 32U;        /**< 0x002C: Reserved                               */
    uint32      : 32U;        /**< 0x0030: Reserved                               */
    uint32      : 32U;        /**< 0x0034: Reserved                               */
    uint32      : 32U;        /**< 0x0038: Reserved                               */
    uint32      : 32U;        /**< 0x003C: Reserved                               */
    uint32      : 32U;        /**< 0x0040: Reserved                               */
    uint32      : 32U;        /**< 0x0044: Reserved                               */
    uint32      : 32U;        /**< 0x0048: Reserved                               */
    uint32      : 32U;        /**< 0x004C: Reserved                               */
    uint32      : 32U;        /**< 0x0050: Reserved                               */
    uint32      : 32U;        /**< 0x0054: Reserved                               */
    uint32      : 32U;        /**< 0x0058: Reserved                               */
    uint32      : 32U;        /**< 0x005C: Reserved                               */
    uint32      : 32U;        /**< 0x0060: Reserved                               */
    uint32      : 32U;        /**< 0x0064: Reserved                               */
    uint32      : 32U;        /**< 0x0068: Reserved                               */
    uint32      : 32U;        /**< 0x006C: Reserved                               */
    uint32      : 32U;        /**< 0x0070: Reserved                               */
    uint32      : 32U;        /**< 0x0074: Reserved                               */
    uint32      : 32U;        /**< 0x0078: Reserved                               */
    uint32      : 32U;        /**< 0x007C: Reserved                               */
    uint32      ABOTR;        /**< 0x0080: Auto Bus On Time Register              */
    uint32      TXRQX;        /**< 0x0084: Transmission Request X Register        */
    uint32      TXRQx[4U];    /**< 0x0088-0x0094: Transmission Request Registers  */
    uint32      NWDATX;       /**< 0x0098: New Data X Register                    */
    uint32      NWDATx[4U];   /**< 0x009C-0x00A8: New Data Registers              */
    uint32      INTPNDX;      /**< 0x00AC: Interrupt Pending X Register           */
    uint32      INTPNDx[4U];  /**< 0x00B0-0x00BC: Interrupt Pending Registers     */
    uint32      MSGVALX;      /**< 0x00C0: Message Valid X Register               */
    uint32      MSGVALx[4U];  /**< 0x00C4-0x00D0: Message Valid Registers         */
    uint32      : 32U;        /**< 0x00D4: Reserved                               */
    uint32      INTMUXx[4U];  /**< 0x00D8-0x00E4: Interrupt Multiplexer Registers */
    uint32      : 32U;        /**< 0x00E8: Reserved                               */
    uint32      : 32U;        /**< 0x00EC: Reserved                               */
    uint32      : 32U;        /**< 0x00F0: Reserved                               */
    uint32      : 32U;        /**< 0x00F4: Reserved                               */
    uint32      : 32U;        /**< 0x00F8: Reserved                               */
    uint32      : 32U;        /**< 0x00FC: Reserved                               */
    uint32      : 8U;         /**< 0x0100: IF1 Command Register, Reserved         */
    uint8 IF1CMD;             /**< 0x0100: IF1 Command Register, Command          */
    uint8 IF1STAT;            /**< 0x0100: IF1 Command Register, Status           */
    uint8 IF1NO;              /**< 0x0100: IF1 Command Register, Msg Number       */
    uint32      IF1MSK;       /**< 0x0104: IF1 Mask Register                      */
    uint32      IF1ARB;       /**< 0x0108: IF1 Arbitration Register               */
    uint32      IF1MCTL;      /**< 0x010C: IF1 Message Control Register           */
    uint8 IF1DATx[8U];        /**< 0x0110-0x0114: IF1 Data A and B Registers      */
    uint32      : 32U;        /**< 0x0118: Reserved                               */
    uint32      : 32U;        /**< 0x011C: Reserved                               */
    uint32      : 8U;         /**< 0x0120: IF2 Command Register, Reserved         */
    uint8 IF2CMD;             /**< 0x0120: IF2 Command Register, Command          */
    uint8 IF2STAT;            /**< 0x0120: IF2 Command Register, Status           */
    uint8 IF2NO;              /**< 0x0120: IF2 Command Register, Msg Number       */
    uint32      IF2MSK;       /**< 0x0124: IF2 Mask Register                      */
    uint32      IF2ARB;       /**< 0x0128: IF2 Arbitration Register               */
    uint32      IF2MCTL;      /**< 0x012C: IF2 Message Control Register           */
    uint8 IF2DATx[8U];        /**< 0x0130-0x0134: IF2 Data A and B Registers      */
    uint32      : 32U;        /**< 0x0138: Reserved                               */
    uint32      : 32U;        /**< 0x013C: Reserved                               */
    uint32      IF3OBS;       /**< 0x0140: IF3 Observation Register               */
    uint32      IF3MSK;       /**< 0x0144: IF3 Mask Register                      */
    uint32      IF3ARB;       /**< 0x0148: IF3 Arbitration Register               */
    uint32      IF3MCTL;      /**< 0x014C: IF3 Message Control Register           */
    uint8 IF3DATx[8U];        /**< 0x0150-0x0154: IF3 Data A and B Registers      */
    uint32      : 32U;        /**< 0x0158: Reserved                               */
    uint32      : 32U;        /**< 0x015C: Reserved                               */
    uint32      IF3UEy[4U];   /**< 0x0160-0x016C: IF3 Update Enable Registers     */
    uint32      : 32U;        /**< 0x0170: Reserved                               */
    uint32      : 32U;        /**< 0x0174: Reserved                               */
    uint32      : 32U;        /**< 0x0178: Reserved                               */
    uint32      : 32U;        /**< 0x017C: Reserved                               */
    uint32      : 32U;        /**< 0x0180: Reserved                               */
    uint32      : 32U;        /**< 0x0184: Reserved                               */
    uint32      : 32U;        /**< 0x0188: Reserved                               */
    uint32      : 32U;        /**< 0x018C: Reserved                               */
    uint32      : 32U;        /**< 0x0190: Reserved                               */
    uint32      : 32U;        /**< 0x0194: Reserved                               */
    uint32      : 32U;        /**< 0x0198: Reserved                               */
    uint32      : 32U;        /**< 0x019C: Reserved                               */
    uint32      : 32U;        /**< 0x01A0: Reserved                               */
    uint32      : 32U;        /**< 0x01A4: Reserved                               */
    uint32      : 32U;        /**< 0x01A8: Reserved                               */
    uint32      : 32U;        /**< 0x01AC: Reserved                               */
    uint32      : 32U;        /**< 0x01B0: Reserved                               */
    uint32      : 32U;        /**< 0x01B4: Reserved                               */
    uint32      : 32U;        /**< 0x01B8: Reserved                               */
    uint32      : 32U;        /**< 0x01BC: Reserved                               */
    uint32      : 32U;        /**< 0x01C0: Reserved                               */
    uint32      : 32U;        /**< 0x01C4: Reserved                               */
    uint32      : 32U;        /**< 0x01C8: Reserved                               */
    uint32      : 32U;        /**< 0x01CC: Reserved                               */
    uint32      : 32U;        /**< 0x01D0: Reserved                               */
    uint32      : 32U;        /**< 0x01D4: Reserved                               */
    uint32      : 32U;        /**< 0x01D8: Reserved                               */
    uint32      : 32U;        /**< 0x01DC: Reserved                               */
    uint32      TIOC;         /**< 0x01E0: TX IO Control Register                 */
    uint32      RIOC;         /**< 0x01E4: RX IO Control Register                 */
} dcanctrlregs_t;

#define DCAN1REG ((dcanctrlregs_t *)0xFFF7DC00UL)
#define DCAN2REG ((dcanctrlregs_t *)0xFFF7DE00UL)
#define DCAN3REG ((dcanctrlregs_t *)0xFFF7E000UL)

#endif
