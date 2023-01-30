/* -----------------------------------------------------------------------------
  Filename:    fbl_cfg.h
  Description: Toolversion: 04.00.00.01.30.06.45.01.00.00
               
               Serial Number: CBD1300645
               Customer Info: Nexteer Automotive Corporation
                              Package: FBL Fiat SLP4 - CANfbl for FIAT
                              Micro: 0812BPGEQQ1
                              Compiler: TexasInstruments 4.9.5
               
               
               Generator Fwk   : GENy 
               Generator Module: GenTool_GenyFblCanBase
               
               Configuration   : C:\TESynergy\Working\ES_EPS_EA3_FBL_Fiat-nzdx8v\ES_EPS_EA3_FBL_Fiat\SwProject\GENy_files\GENyConfiguration_Fiat_329_332.gny
               
               ECU: 
                       TargetSystem: Hw_Tms470/570Cpu (Dcan)
                       Compiler:     TexasInstruments
                       Derivates:    TMS570LS0322
               
               Channel "Channel0":
                       Databasefile: C:\Users\nzdx8v\Desktop\Projects\Test\Test\ES_EPS_EA3_FBL_Fiat-Final\ES_EPS_EA3_FBL_Fiat\SwProject\GENy_files\NET_EE_BCAN_P312_vector.dbc
                       Bussystem:    CAN
                       Manufacturer: Fiat
                       Node:         CTM

 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2001-2014 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

#if !defined(__FBL_CFG_H__)
#define __FBL_CFG_H__

/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define FBL_WATCHDOG_OFF
#define FBL_WATCHDOG_TIME                    (1 / FBL_REPEAT_CALL_CYCLE)
#define FBL_HEADER_ADDRESS                   0x0200u
#define FBL_ENABLE_APPL_TASK
#define FBL_ENABLE_MULTIPLE_MODULES
#define SWM_DATA_MAX_NOAR                    10
#define FBL_DIAG_BUFFER_LENGTH               1026
#define FBL_DIAG_TIME_P2MAX                  (50 / FBL_REPEAT_CALL_CYCLE)
#define FBL_DIAG_TIME_P3MAX                  (5000 / FBL_REPEAT_CALL_CYCLE)
#define FBL_ENABLE_SLEEPMODE
#define kFillChar                            0xFFu
#define FBL_DISABLE_MULTIPLE_MEM_DEVICES
#define FBL_ENABLE_PRESENCE_PATTERN
#define FBL_ENABLE_FBL_START
#define FBL_MTAB_NO_OF_BLOCKS                2
/* Data Processing */
#define FBL_DISABLE_DATA_PROCESSING
#define FBL_DISABLE_ENCRYPTION_MODE
#define FBL_DISABLE_COMPRESSION_MODE
/* Project State */
#define FBL_INTEGRATION                      2
#define FBL_PRODUCTION                       1
#define FBL_PROJECT_STATE                    FBL_INTEGRATION
#define FBL_ENABLE_SYSTEM_CHECK
#define FBL_ENABLE_DEBUG_STATUS
#define FBL_ENABLE_ASSERTION
/* FblLib_Mem */
#define FBL_MEM_PROC_BUFFER_SIZE             0x0100
/* CAN Identifier */

/* Tmsx70Dcan specific ******************************************************* */
#define FBL_TIMER_PRESCALER_VALUE            0x01
#define FBL_TIMER_RELOAD_VALUE               0x9C3F
#define DELAY                                0

#define CAN_BITTIMING                        0x7A07
#define CAN_BRP_REG                          0x00
#define CAN_CTRL_ADDR                        0xFFF7DC00
#define CAN_NUMBER_OF_HW_OBJECTS             32
#define FLASH_SIZE                           0x2000
#define FBL_WD_TRIGGER_SIZE                  1024
#define FBL_WDTRIGGER_EXTRA_WORDS            128

/* FIAT specific ************************************************************* */
#define FBL_DISABLE_USERSUBFUNCTION
#define kFblDiagMaxDidReq                    20
#define FBL_DISABLE_SWIL_I
#define FBL_DISABLE_SWIL_II
#define FBL_DISABLE_MULTIPLE_NODES
#define DIAG_NODE_ADDRESS                    0x30
#define FBL_ADDRESSLEN                       0x04


/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

/* User Config File ********************************************************** */
/*************************************************/
/* Configuration Area F021 Flash Driver          */
/*************************************************/

/* Tms570 HCLK frequency in MHz */
#define FBL_HCLK      160

/* GENy support for logical blocks cannot be used yet */
#undef FBL_MTAB_NO_OF_BLOCKS

/* Info about logical blocks: */ 
#define FBL_MTAB_NO_OF_CODE_BLOCKS 1
#define FBL_MTAB_NO_OF_DATA_BLOCKS 1

#define FBL_MTAB_NO_OF_BLOCKS (FBL_MTAB_NO_OF_CODE_BLOCKS + FBL_MTAB_NO_OF_DATA_BLOCKS  )
/* User Section ************************************************************** */
#define FBL_ENABLE_EXTENDED_ID
#define FBL_DISABLE_REPROGRAMMABLE_LBT
#define FBL_DISABLE_GAP_FILL			
#define FBL_ENABLE_TRANSFER_VERIFICATION_CHECK
#define FBL_ENABLE_CAN_CONFIRMATION
#if defined( FBL_DISABLE_SWIL_I ) && defined( FBL_DISABLE_SWIL_II )
# define FBL_ENABLE_FLASHDRV_ROM
#else
# define FBL_DISABLE_FLASHDRV_ROM
#endif
#define FBL_CAN_FUNC_RXID       MK_EXTID(0X18DBFEF1)//MK_EXTID(0x18DBFEF4)                                             /* Functional request ID*/
#define FBL_CAN_TXID            MK_EXTID(0x18DAF430)//MK_EXTID(0x18DAF400|DIAG_NODE_ADDRESS)                           /* Response ID */
#define FBL_CAN_RXID            MK_EXTID(0x18DA30F4)//MK_EXTID(0x18DA00F4|((vuint16)(DIAG_NODE_ADDRESS)<<8))           /* Physical request ID*/
/* *************************************************************************** */


/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 174001433
      #error "The magic number of the generated file <C:\TESynergy\Working\ES_EPS_EA3_FBL_Fiat-nzdx8v\ES_EPS_EA3_FBL_Fiat\SwProject\GENy_files\fbl_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 174001433
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __FBL_CFG_H__ */
