/*****************************************************************************
* Copyright 2014 Nexteer
* Nexteer Confidential
*
* Module File Name  : i2c_regs.h
* Module Description: I2C Peripheral Registers
* Product           : Gen II Plus - EA3.0
* Author            : Steven Horwath
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Thu Dec 15 09:10:25 2011 % 
* %version:          2 %
* %derived_by:       nz63rn %
*---------------------------------------------------------------------------*/

/*****************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description              SCR #
-------   -------  --------  -----------------------------------  ----------
12/15/11   1		SAH      Initial Creation
06/24/14   2        KMC 	 QAC cleanup                           10551  
******************************************************************************/


#ifndef I2C_REGS_H
#define I2C_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct i2cctrlregs
{

    uint32 OAR;           /**<  0x0000 I2C Own Address register               */
    uint32 IMR;           /**<  0x0004 I2C Interrupt Mask/Status register     */
    uint32 STR;           /**<  0x0008 I2C Interrupt Status register          */
    uint32 CLKL;          /**<  0x000C I2C Clock Divider Low register         */
    uint32 CLKH;          /**<  0x0010 I2C Clock Divider High register        */
    uint32 CNT;           /**<  0x0014 I2C Data Count register                */
    uint32 DRR;           /**<  0x0018 I2C Data Receive register              */
    uint32 SAR;           /**<  0x001C I2C Slave Address register             */
    uint32 DXR;           /**<  0x0020 I2C Data Transmit register             */
    uint32 MDR;           /**<  0x0024 I2C Mode register                      */
    uint32 IVR;           /**<  0x0028 I2C Interrupt Vector register          */
    uint32 EMDR;          /**<  0x002C I2C Extended Mode register             */
    uint32 PSC;           /**<  0x0030 I2C Prescaler register                 */
    uint32 PID11;         /**<  0x0034 I2C Peripheral ID register 1           */
    uint32 PID12;         /**<  0x0038 I2C Peripheral ID register 2           */
    uint32 DMAC;          /**<  0x003C I2C DMA Control Register               */
    uint32 : 32U;         /**<  0x0040 Reserved                               */
    uint32 : 32U;         /**<  0x0044 Reserved                               */
    uint32 FUN;           /**<  0x0048 Pin Function Register                  */
    uint32 DIR;           /**<  0x004C Pin Direction Register                 */
    uint32 DIN;           /**<  0x0050 Pin Data In Register                   */
    uint32 DOUT;          /**<  0x0054 Pin Data Out Register                  */
    uint32 SET;           /**<  0x0058 Pin Data Set Register                  */
    uint32 CLR;           /**<  0x005C Pin Data Clr Register                  */
    uint32 ODR;           /**<  0x0060 Pin Open Drain Output Enable Register  */
    uint32 PD;            /**<  0x0064 Pin Pullup/Pulldown Disable Register   */
    uint32 PSL;           /**<  0x0068 Pin Pullup/Pulldown Selection Register */
} i2cctrlregs_t;

#define i2cREG1 ((i2cctrlregs_t *)0xFFF7D400UL)

#endif

