/*******************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : TMS570LS202x6SFlashLnk.cmd
* Module Description: Linker Command File
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*******************************************************************************/
/*******************************************************************************
* Version Control:
* %version:          EA3#7 %
* %derived_by:       mzjphh %
*******************************************************************************/
/*******************************************************************************
* Change History:
* Date      Rev      Author     Change Description
* --------  -------  --------   ------------------------------------------------
* 07/18/13   1        OT        Initial version
* 07/23/13   2        OT        Removed MEM_FILL section
* 07/29/13   3        OT        Removed Flash API from RAM
* 07/31/13   4        OT        Added DigHwTrqSENT and Lnk_BootRelNum_Addr
* 08/07/13   5        OT        Removed AbsHwPosScom TypeH section
* 11/15/13   6        OT        Updates for bootloader changes
* 11/26/13   7        OT        Rollback bootloader changes
* 12/05/13   8        OT        Rollback fix
* 12/20/13   9        OT        Updates for application implementation
* 01/09/14   10       OT        Updates for Ap 9
* 01/14/14   11       OT        Updates for Ap 10
* 01/27/14   12       OT        Removed obsolete sections
* 05/28/14   13       OT        Updates for bootloader changes (reintroduced)
* 10/27/14   13.1.1   M. Story  A_7468 declare a small stack to be used by both IRQ and FIQ
* 11/05/14   13.1.2   OT        A_7468 update size of STACK section
* 11/18/14   13.1.3   OT        Updates for GliwaT1 integration
* 12/16/14   13.1.4   OT        Added symbols for bootloader CRC
* 12/17/14   13.1.5   OT        Optimization for compiler warnings
* 15/15/15   14       PS        Implemented software according to SCIR 3A and DSR 2A	
* 10/30/15   15       PS        Implemented software according to SCIR 4A and DSR 3A	
* 03/16/16   16       PS        Implemented software according to SCIR 8A and DSR 7A
* 10/04/16   17       NS        Moved start address of application to 0x10000 (from 0xC000)
*							    to increase space in bootloader				  
*******************************************************************************/


/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */
--retain="*(.intvecs)"

/*----------------------------------------------------------------------------*/
/* Memory Map                                                                 */
MEMORY{
	
	/* Bootloader */
	BOOT			(RX) : origin=0x00000000 length=0x0000FFF8
	BOOT_CRC		(R)  : origin=0x0000FFF8 length=0x00000008
	
	/* Application */
	APP_FLASH		(RX) : origin=0x00010000 length=0x0006FFF8 fill=0xFFFFFFFF
	APP_CRC			(R)  : origin=0x0007FFF8 length=0x00000008 fill=0xFFFFFFFF
	
	/* Calibration */
	CAL_FLASH		(R)  : origin=0x00080000 length=0x0003FFF8 fill=0xFFFFFFFF
	CAL_CRC			(R)  : origin=0x000BFFF8 length=0x00000008 fill=0xFFFFFFFF
	
	/* RAM */
	STACKS			(RW) : origin=0x08000000 length=0x00000400
	RAM				(RW) : origin=0x08000400 length=0x0001FC00
	
	/* NHET */
	NHET2RAM		(RW) : origin=0xFF440000 length=0x00000800
	NHETRAM			(RW) : origin=0xFF460000 length=0x00000800
	
	/* System Registers */
	MMC				(RW) : origin=0xFFFFFD00 length=0x40
	DEC				(RW) : origin=0xFFFFFE00 length=0x60
	SYS				(RW) : origin=0xFFFFFFD0 length=0x30
}

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */
SECTIONS{
	
	/*----------------------------------------------------------------------------*/
	/*                        Sections with Fixed Addresses                       */
	/*----------------------------------------------------------------------------*/
	
	.BoolRelNum				: 	{
									Lnk_BootRelNum_Addr = .;
								} > 0x0000FFC0
	
	.BoolRelNumDIDF180		: 	{
									Lnk_BootSwIdentificationDIDF180_Addr = .;
								} > 0x0000FFB0

	.AppPresencePattern		: 	{
									Lnk_AppBlock_Start = .;
									Lnk_AppBlock_Length = 0x70000;
								} > 0x00010000
	
	.AppBlockVersionCheck	: 	{} > 0x00010018
	.SWRelNum				: 	{} > 0x00010100
	
	.BootValidityTable		: 	{
									/* Note this checksum has to run prior to the overall flash checksum */
									CCT_Range_01_Start = .;
									CCT_Range_01_BitAddrGran = 8;
									CCT_Range_01_Category = 300;
									CCT_Range_01_Algorithm = 5;
									*(.bootvaltable)
									CCT_Range_01_Length = . - CCT_Range_01_Start;
									CCT_Range_01_Address = .;
									*(.bootvalcrc)
								} > 0x0002001C

	.osresetvect					:	{} > 0x00020060
	.osarmvect						:	{} > 0x00020064
	
	.CalPresencePattern				: 	{
											Lnk_CalBlock_Start = .;
											Lnk_CalBlock_Length = 0x40000;
										} > 0x00080000

	.CalBlockVersionCheck			: 	{} > 0x00080018

	.CustDIDCals					: 	{} > 0x00080020
	
	
	/*----------------------------------------------------------------------------*/
	/*                                RAM Segments                                */
	/*----------------------------------------------------------------------------*/
	
	.stack		:	{
						_StackSVC_   = .+ (0x0100);
						_StackUSER_  = .+ (0x0200);
						_StackUND_   = .+ (0x0300); /* Share stacks for undefined instruction and data abort */
						_StackABORT_ = .+ (0x0300);
                        _StackFIQ_   = .+ (0x0380);
                        _StackIRQ_   = .+ (0x0400);
					} > STACKS
	
	.bss    	:  	LOAD_END(Lnk_BSS_End),
					LOAD_START(Lnk_BSS_Start)
					{
						#include "./Source/GenDataOS/osobjs.inc"
						*(.ossctxdata)
					} > RAM
	
	.data   	: 	{
						#include "./Source/GenDataOS/osobjs_init.inc"
						*(.osstack)
					} > RAM
	
	.T1_bss			: {} > RAM
	.T1_traceBuffer	: {} > RAM
	
	.noclear	:	{} > RAM

	.resetcause	:	{} > 0x08003400
	

	/*----------------------------------------------------------------------------*/
	/*                            Calibration Segment                             */
	/*----------------------------------------------------------------------------*/
	
	.FlashCalSeg	: {} > CAL_FLASH
	
	.TunCal0		: {} > CAL_FLASH
	.TunCal0Per0	: {} > CAL_FLASH
	.TunCal0Per1	: {} > CAL_FLASH

	.TunCal1		: {} > CAL_FLASH
	.TunCal1Per0	: {} > CAL_FLASH
	.TunCal1Per1	: {} > CAL_FLASH

	.TunCal2		: {} > CAL_FLASH
	.TunCal2Per0	: {} > CAL_FLASH
	.TunCal2Per1	: {} > CAL_FLASH

	.TunCal3		: {} > CAL_FLASH
	.TunCal3Per0	: {} > CAL_FLASH
	.TunCal3Per1	: {} > CAL_FLASH

	.TunCal4		: {} > CAL_FLASH
	.TunCal4Per0	: {} > CAL_FLASH
	.TunCal4Per1	: {} > CAL_FLASH

	.TunCal5		: {} > CAL_FLASH
	.TunCal5Per0	: {} > CAL_FLASH
	.TunCal5Per1	: {} > CAL_FLASH

	.TunCal6		: {} > CAL_FLASH
	.TunCal6Per0	: {} > CAL_FLASH
	.TunCal6Per1	: {} > CAL_FLASH

	.TunCal7		: {} > CAL_FLASH
	.TunCal7Per0	: {} > CAL_FLASH
	.TunCal7Per1	: {} > CAL_FLASH
	
	
	/*----------------------------------------------------------------------------*/
	/*                             Application Segment                            */
	/*----------------------------------------------------------------------------*/
	
	.cinit     	:	{} > APP_FLASH
	
	.text     	:	{} > APP_FLASH
	
	.const     	:	{} > APP_FLASH
	
	.OSAPPFLASH	:	{
						*(.osvtable)
						*(.oscode)
						*(.osconst)
						.=((.-1)/4)*4+4;  /* Force align to 32bits as osconfig is structure */
						/* Note this checksum has to run prior to the overall flash checksum */
						CCT_Range_00_Start = .;
						CCT_Range_00_BitAddrGran = 8;
						CCT_Range_00_Category = 300;
						CCT_Range_00_Algorithm = 10;
						*(.osconfig)
						CCT_Range_00_Length = . - CCT_Range_00_Start-2;
						CCT_Range_00_Address = CCT_Range_00_Start + CCT_Range_00_Length;
					} > APP_FLASH, palign(64)
	
	.T1_code	:	{} > APP_FLASH
	.T1_const	:	{} > APP_FLASH
	
	#include "./T1_Fast.inc"
	
	
	/*----------------------------------------------------------------------------*/
	/*                                NHET Segments                               */
	/*----------------------------------------------------------------------------*/
	
	.HETCODE	:	{ e_HETPROGRAM0_UN = .; } > 0xFF460000
	.HET2CODE	:	{ e_HETPROGRAM1_UN = .; } > 0xFF440000
	
	
	
	/*----------------------------------------------------------------------------*/
	/*                              System Registers                              */
	/*----------------------------------------------------------------------------*/
	
	.MMC     	: 	{ _e_SARMMC_ST = .; } > MMC
	.DEC     	:	{ _e_SARDEC_ST = .; } > DEC
	.SYS     	:	{ _e_SARSYS_ST = .; } > SYS
	
	
	
	/*----------------------------------------------------------------------------*/
	/*                            Checksum Definitions                            */
	/*----------------------------------------------------------------------------*/
	
	.APPCHECKSUM :	{
						CCT_Range_10_Address = .;
						CCT_Range_10_Start = 0x10000;
						CCT_Range_10_Length = 0x6FFE0;
						CCT_Range_10_BitAddrGran = 8;
						CCT_Range_10_Category = 300;
						CCT_Range_10_Algorithm = 12;
					} > APP_CRC
	
	.CALCHECKSUM :	{
						CCT_Range_11_Address = .;
						CCT_Range_11_Start = 0x80000;
						CCT_Range_11_Length = 0x3FFF8;
						CCT_Range_11_BitAddrGran = 8;
						CCT_Range_11_Category = 200;
						CCT_Range_11_Algorithm = 12;
					} > CAL_CRC
	
	.BOOTCHECKSUM :	{
						BootCRC_Address = .;
						BootCRC_Start = 0;
					} > BOOT_CRC
}

