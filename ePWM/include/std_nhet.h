/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : std_nhet.h
* Module Description: NHET data structure definition
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/* Version Control:
 * Date Created:      Wed Apr 13 12:17:00 2011
 * %version:          4 %
 * %derived_by:       cz7lt6 %
 * %date_modified:    Fri Mar  2 17:00:30 2012 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 04/13/11  1        LWW       Initial K2xx Synergy Version
 * 12/12/11  2		  KJS		Added instruction typedefs for new instructions in NHET2 code. 
 * 01/12/27  3		  JJW		Renamed file to std_nhet.h to be consistent with the output of the Nhet assembler v1.7 
 * 03/02/12  4        KJS       Added OR_INSTRUCTION support for NHET2 version 2.5. 
 */

/*Nexteer file is based on the following TI file*/
/****************************************************************************/
/* std_het.h TMS470HET                                                      */
/* Copyright (c) 1996,1997  Texas Instruments Incorporated                  */
/*                                                                          */
/* Corrections by GEWE 26.04.99                                             */
/*  - Defined all instruction unions as "volatile"                          */
/*  - Defined all instruction field types as "volatile"                     */
/*  - Defined HET_MEMORY type as "volatile"                                 */
/*  - Corrected shift_condition bit length for SHFT instruction             */
/****************************************************************************/

#ifndef STD_HET_H
#define STD_HET_H

#include "Std_Types.h" /* AUTOSAR include */

typedef volatile struct memory_format
{
  uint32 program_word  ;
  uint32 control_word  ;
  uint32 data_word     ;
  uint32 reserved_word ;
} HET_MEMORY  ;

/* TODO: Instructions should be updated for latest version of NHET format. */


/*---------------------------------------------*/
/* ACMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef volatile struct acmp_format
{
  uint32                      : 11 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 8 ;
  uint32 op_code              : 4 ;
  uint32                      : 3 ;
  uint32                      : 5 ;
 
  uint32                      : 11 ;
  uint32 en_pin_action        : 1 ;
  uint32 cond_addr            : 8 ;
  uint32 pin_select           : 5 ;
  uint32                      : 2 ; 
  uint32 pin_action           : 1 ;
  uint32                      : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;
 
  uint32                      : 7 ;
  uint32 data                 : 20 ;
  uint32                      : 5 ;
 
} ACMP_FIELDS;
 
typedef volatile union
{
  ACMP_FIELDS  acmp   ;
  HET_MEMORY   memory ;
} ACMP_INSTRUCTION;


/*---------------------------------------------*/
/* ECMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef volatile struct ecmp_format   
{
  uint32                      : 11 ;          
  uint32 brk                  : 1 ;          
  uint32 next_program_address : 8 ;          
  uint32 op_code              : 4 ;
  uint32 angle_compare        : 1 ;
  uint32                      : 2 ;
  uint32                      : 5 ;

  uint32                      : 11 ;
  uint32 en_pin_action        : 1 ;
  uint32 cond_addr            : 8 ;
  uint32 pin_select           : 5 ;
  uint32 compare_mode         : 2 ;
  uint32 pin_action           : 1 ;
  uint32 optional_action      : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ; 
  uint32 interrupt_enable     : 1 ;

  uint32                      : 7 ;
  uint32 data                 : 25 ;

} ECMP_FIELDS;

typedef volatile union 
{
  ECMP_FIELDS  ecmp   ;
  HET_MEMORY   memory ;
} ECMP_INSTRUCTION;


/*---------------------------------------------*/
/* SCMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef volatile struct scmp_format     
{
  uint32                      : 11 ;          
  uint32 brk                  : 1 ;          
  uint32 next_program_address : 8 ;          
  uint32 op_code              : 4 ;
  uint32                      : 1 ;
  uint32                      : 2 ;
  uint32                      : 5 ;

  uint32                      : 11 ;
  uint32 en_pin_action        : 1 ;
  uint32 cond_addr            : 8 ;
  uint32 pin_select           : 5 ;
  uint32 compare_mode         : 2 ;
  uint32 pin_action           : 1 ;
  uint32 optional_action      : 1 ;
  uint32                      : 1 ;
  uint32 restart_en           : 1 ;
  uint32 interrupt_enable     : 1 ;

  uint32                      : 7 ;
  uint32 data                 : 20 ;
  uint32                      : 5 ;

} SCMP_FIELDS ;

typedef volatile union 
{
  SCMP_FIELDS  scmp   ;
  HET_MEMORY   memory ;
} SCMP_INSTRUCTION;


/*---------------------------------------------*/
/* MCMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef volatile struct mcmp_format                     
{
  uint32                      : 11 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 8 ;
  uint32 op_code              : 4 ;
  uint32 angle_compare        : 1 ;
  uint32                      : 2 ;
  uint32 save_subtract        : 1 ;
  uint32                      : 4 ;
 
  uint32                      : 11 ;
  uint32 en_pin_action        : 1 ;
  uint32 cond_addr            : 8 ;
  uint32 pin_select           : 5 ;
  uint32 compare_mode         : 2 ;
  uint32 pin_action           : 1 ;
  uint32 optional_action      : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;
 
  uint32                      : 7 ;
  uint32 data                 : 25 ;

} MCMP_FIELDS ; 

typedef volatile union 
{
  MCMP_FIELDS  mcmp   ;
  HET_MEMORY   memory ;
} MCMP_INSTRUCTION;

/*---------------------------------------------*/
/* MOV64 INSTRUCTION                           */
/*---------------------------------------------*/
typedef volatile struct mov64_format                     
{
  uint32                      : 11 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 8 ;          
  uint32 op_code              : 4 ;
  uint32 remote_address       : 8 ;

  uint32                      : 11 ;
  uint32 en_pin_action        : 1 ;
  uint32 cond_addr            : 8 ;
  uint32 pin_select           : 5 ;
  uint32 compare_mode         : 2 ;
  uint32 pin_action           : 1 ;
  uint32 optional_action      : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;
 
  uint32                      : 7 ;
  uint32 data                 : 25 ;

} MOV64_FIELDS ; 

typedef volatile union 
{
  MOV64_FIELDS  mov64  ;
  HET_MEMORY    memory ;
} MOV64_INSTRUCTION;


/*---------------------------------------------*/
/* DADM64 INSTRUCTION                          */
/*---------------------------------------------*/
typedef volatile struct dadm64_format                     
{
  uint32                      : 11 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 8 ;
  uint32 op_code              : 4 ;
  uint32 remote_address       : 8 ;
 
  uint32                      : 11 ;
  uint32 en_pin_action        : 1 ;
  uint32 cond_addr            : 8 ;
  uint32 pin_select           : 5 ;
  uint32 compare_mode         : 2 ;
  uint32 pin_action           : 1 ;
  uint32 optional_action      : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;
 
  uint32                      : 7 ;
  uint32 data                 : 25 ;

} DADM64_FIELDS ; 

typedef volatile union 
{
  DADM64_FIELDS  dadm64 ;
  HET_MEMORY     memory ;
} DADM64_INSTRUCTION;


/*---------------------------------------------*/
/* RADM64 INSTRUCTION                          */
/*---------------------------------------------*/
typedef volatile struct RADM64_format                     
{
  uint32                      : 11 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 8 ;
  uint32 op_code              : 4 ;
  uint32 remote_address       : 8 ;
 
  uint32                      : 11 ;
  uint32 en_pin_action        : 1 ;
  uint32 cond_addr            : 8 ;
  uint32 pin_select           : 5 ;
  uint32 compare_mode         : 2 ;
  uint32 pin_action           : 1 ;
  uint32 optional_action      : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;
 
  uint32                      : 7 ;
  uint32 data                 : 25 ;

} RADM64_FIELDS ; 


typedef volatile union 
{
  RADM64_FIELDS  radm64 ;
  HET_MEMORY     memory ;
} RADM64_INSTRUCTION;


/*---------------------------------------------*/
/* MOV32 INSTRUCTION                           */
/*---------------------------------------------*/
typedef volatile struct MOV32_format                     
{
  uint32                      : 11 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 8 ;
  uint32 op_code              : 4 ;
  uint32 remote_address       : 8 ;
 
  uint32                      : 11 ;
  uint32                      : 14 ;
  uint32 init_flag            : 1 ;
  uint32 move_type            : 3 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32                      : 1 ;
 
  uint32                      : 7 ;
  uint32 data                 : 25 ;

} MOV32_FIELDS ; 


typedef volatile union 
{
  MOV32_FIELDS  mov32  ;
  HET_MEMORY    memory ;
} MOV32_INSTRUCTION;


/*---------------------------------------------*/
/* ADM32 INSTRUCTION                           */
/*---------------------------------------------*/
typedef volatile struct ADM32_format                     
{
  uint32                      : 11 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 8 ;
  uint32 op_code              : 4 ;
  uint32 remote_address       : 8 ;
 
  uint32                      : 11 ;
  uint32                      : 14 ;
  uint32 init_flag            : 1 ;
  uint32 move_type            : 3 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32                      : 1 ;
 
  uint32                      : 7 ;
  uint32 data                 : 25 ;

} ADM32_FIELDS ; 


typedef volatile union 
{
  ADM32_FIELDS  adm32  ;
  HET_MEMORY    memory ;
} ADM32_INSTRUCTION;


/*---------------------------------------------*/
/* ADCNST INSTRUCTION                          */
/*---------------------------------------------*/
typedef volatile struct ADCNST_format                     
{
  uint32                      : 11 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 8 ;
  uint32 op_code              : 4 ;
  uint32 remote_address       : 8 ;
 
  uint32                      : 11 ;
  uint32                      : 1 ;
  uint32 const                : 20 ;
 
  uint32                      : 7 ;
  uint32 data                 : 25 ;

} ADCNST_FIELDS ;


typedef volatile union 
{
  ADCNST_FIELDS  adcnst ;
  HET_MEMORY     memory ;
} ADCNST_INSTRUCTION;


/*---------------------------------------------*/
/* CNT INSTRUCTION                             */
/*---------------------------------------------*/
typedef volatile struct CNT_format                     
{
  uint32                      : 11 ;          
  uint32 brk                  : 1 ;          
  uint32 next_program_address : 8 ;          
  uint32 op_code              : 4 ;
  uint32 angle_cnt            : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32                      : 4 ;
  uint32 interrupt_enable     : 1 ;
 

  uint32                      : 11 ;
  uint32                      : 1 ;
  uint32 max                  : 20 ;

  uint32                      : 7 ;
  uint32 data                 : 20 ;
  uint32                      : 5 ;

} CNT_FIELDS ; 

typedef volatile union 
{
  CNT_FIELDS   cnt    ; 
  HET_MEMORY   memory ;
} CNT_INSTRUCTION;


/*---------------------------------------------*/
/* APCNT INSTRUCTION                           */
/*---------------------------------------------*/
typedef volatile struct apcnt_format
{
  uint32                      : 11 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 8 ;
  uint32 op_code              : 4 ;
  uint32 interrupt_enable     : 1 ;
  uint32 period_pulse_select  : 2 ;
  uint32 pin_select           : 5 ;
 
  uint32                      : 11 ;
  uint32 previous_bit         : 1 ;
  uint32 count                : 20 ;
 
  uint32                      : 7 ;
  uint32 data                 : 20 ;
  uint32                      : 5 ;
 
} APCNT_FIELDS ;
 
typedef volatile union
{
  APCNT_FIELDS  apcnt   ;
  HET_MEMORY   memory ;
} APCNT_INSTRUCTION;
 
 

/*---------------------------------------------*/
/* PCNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef volatile struct pcnt_format                     
{
  uint32                      : 11 ;          
  uint32 brk                  : 1 ;          
  uint32 next_program_address : 8 ;          
  uint32 op_code              : 4 ;
  uint32 interrupt_enable     : 1 ;
  uint32 period_pulse_select  : 2 ;
  uint32 pin_select           : 5 ;

  uint32                      : 10 ;
  uint32 control              : 1 ;
  uint32 previous_bit         : 1 ;
  uint32 count                : 20 ;

  uint32                      : 7 ;
  uint32 data                 : 25 ;

} PCNT_FIELDS ;      

typedef volatile union 
{
  PCNT_FIELDS  pcnt   ; 
  HET_MEMORY   memory ;
} PCNT_INSTRUCTION;


/*---------------------------------------------*/
/* SCNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef volatile struct scnt_format                     
{
  uint32                      : 11 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 8 ;
  uint32 op_code              : 4 ;
  uint32                      : 1 ;
  uint32 count_mode           : 2 ;
  uint32 step_width           : 2 ;
  uint32                      : 3 ;

  uint32                      : 11 ;
  uint32                      : 1 ;
  uint32 gap_start            : 20 ;

  uint32                      : 7 ;
  uint32 data                 : 20 ;
  uint32                      : 5 ;

} SCNT_FIELDS ;      

typedef volatile union 
{
  SCNT_FIELDS  scnt   ; 
  HET_MEMORY   memory ;
} SCNT_INSTRUCTION;



/*---------------------------------------------*/
/* ACNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef volatile struct acnt_format                     
{
  uint32                      : 11 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 8 ;          
  uint32 op_code              : 4 ;
  uint32 edge_select          : 1 ;
  uint32                      : 6 ;
  uint32 interrupt_enable     : 1 ; 

  uint32                      : 11 ;
  uint32                      : 1 ;
  uint32 gap_end              : 20 ;
 
  uint32                      : 7 ;
  uint32 data                 : 20 ;
  uint32                      : 5 ;

} ACNT_FIELDS ;      

typedef volatile union 
{
  ACNT_FIELDS  acnt   ; 
  HET_MEMORY   memory ;
} ACNT_INSTRUCTION;


/*---------------------------------------------*/
/* ECNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef volatile struct ecnt_format
{
  uint32                      : 11 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 8 ;
  uint32 op_code              : 4 ;
  uint32                      : 1 ;
  uint32 count_mode           : 2 ;
  uint32 cap_en               : 1 ;
  uint32                      : 4 ;
 
  uint32                      : 11 ;
  uint32 previous_bit         : 1 ;
  uint32 cond_addr            : 8 ;
  uint32 pin_select           : 5 ;
  uint32 count_cond           : 3 ;
  uint32                      : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;

  uint32                      : 7 ;
  uint32 data                 : 20 ;
  uint32                      : 5 ;
 
} ECNT_FIELDS ;
 
typedef volatile union
{
  ECNT_FIELDS  ecnt   ;
  HET_MEMORY   memory ;
} ECNT_INSTRUCTION;


/*---------------------------------------------*/
/* DJNZ INSTRUCTION                            */
/*---------------------------------------------*/
typedef volatile struct djnz_format                     
{
  uint32                      : 11 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 8 ;          
  uint32 op_code              : 4 ;
  uint32                      : 1 ;
  uint32 count_mode           : 2 ;
  uint32                      : 5 ;

  uint32                      : 11 ;
  uint32                      : 1 ;
  uint32 cond_addr            : 8 ;
  uint32                      : 9 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;

  uint32                      : 7 ;
  uint32 data                 : 20 ;
  uint32                      : 5 ;

} DJNZ_FIELDS ;      

typedef volatile union 
{
  DJNZ_FIELDS  djnz   ; 
  HET_MEMORY   memory ;
} DJNZ_INSTRUCTION;


/*---------------------------------------------*/
/* PWCNT INSTRUCTION                           */
/*---------------------------------------------*/
typedef volatile struct pwcnt_format                     
{
  uint32                      : 11 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 8 ;
  uint32 op_code              : 4 ;
  uint32                      : 1 ;
  uint32 count_mode           : 2 ;
  uint32                      : 5 ;

  uint32                      : 11 ;
  uint32 en_pin_action        : 1 ;
  uint32 cond_addr            : 8 ;
  uint32 pin_select           : 5 ;
  uint32                      : 2 ;
  uint32 pin_action           : 1 ;
  uint32 optional_action      : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;

  uint32                      : 7 ;
  uint32 data                 : 20 ;
  uint32                      : 5 ;
 
} PWCNT_FIELDS ;      

typedef volatile union 
{
  PWCNT_FIELDS  pwcnt ;
  HET_MEMORY   memory ;
} PWCNT_INSTRUCTION;


/*---------------------------------------------*/
/* WCAP INSTRUCTION                            */
/*---------------------------------------------*/
typedef volatile struct wcap_format                     
{
  uint32                      : 11 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 8 ;
  uint32 op_code              : 4 ;
  uint32                      : 8 ;
  
  uint32                      : 11 ;
  uint32 previous_bit         : 1 ;
  uint32 cond_addr            : 8 ;
  uint32 pin_select           : 5 ;
  uint32 capture_condition    : 2 ;
  uint32                      : 2 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;

  uint32                      : 7 ;
  uint32 data                 : 25 ;

} WCAP_FIELDS ;      

typedef volatile union 
{
  WCAP_FIELDS  wcap   ; 
  HET_MEMORY   memory ;
} WCAP_INSTRUCTION;
 


/*---------------------------------------------*/
/* BR   INSTRUCTION                            */
/*---------------------------------------------*/
typedef volatile struct br_format                     
{
  uint32                      : 11 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 8 ;
  uint32 op_code              : 4 ;
  uint32                      : 8 ;

  uint32                      : 11 ;
  uint32 previous_bit         : 1 ;
  uint32 cond_addr            : 8 ;
  uint32 pin_select           : 5 ;
  uint32 branch_condition     : 3 ;
  uint32                      : 1 ;
  uint32                      : 1 ;
  uint32                      : 1 ;
  uint32 interrupt_enable     : 1 ;
 
  uint32                      : 7 ;
  uint32 data                 : 25 ;

} BR_FIELDS ;      

typedef volatile union 
{
  BR_FIELDS  br     ; 
  HET_MEMORY memory ;
} BR_INSTRUCTION;

 
/*---------------------------------------------*/
/* SHFT INSTRUCTION                            */
/*---------------------------------------------*/
typedef volatile struct shft_format                     
{
  uint32                      : 11 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 8 ;
  uint32 op_code              : 4 ;
  uint32                      : 4 ;
  uint32 shift_mode           : 4 ;
 
  uint32                      : 11 ;
  uint32                      : 1 ;
  uint32 cond_addr            : 8 ;
  uint32 data_pin_select      : 5 ;
  uint32 shift_condition      : 2 ;
  uint32                      : 2 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;

  uint32                      : 7 ;
  uint32 data                 : 20 ;
  uint32                      : 5 ;

} SHFT_FIELDS ;      

typedef volatile union 
{
  SHFT_FIELDS  shft   ; 
  HET_MEMORY   memory ;
} SHFT_INSTRUCTION;


typedef volatile union 
{
  SHFT_FIELDS  shft   ; 
  HET_MEMORY   memory ;
} SUB_INSTRUCTION;

typedef volatile union 
{
  SHFT_FIELDS  shft   ; 
  HET_MEMORY   memory ;
} ADD_INSTRUCTION;

typedef volatile union 
{
  SHFT_FIELDS  shft   ; 
  HET_MEMORY   memory ;
} DJZ_INSTRUCTION;

typedef volatile union
{
  SHFT_FIELDS  shft   ;
  HET_MEMORY   memory ;
} OR_INSTRUCTION;

#endif

