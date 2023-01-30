;*****************************************************************************
; Copyright 2010 Nexteer Automotive, All Rights Reserved.
; Nexteer Confidential
;
; Module File Name  : sys_memory.asm
; Module Description: TI Halcogen based micro init
; Product           : Gen II Plus - EA3.0
; Author            : Jeremy Warmbier
;*****************************************************************************
;---------------------------------------------------------------------------
; Version Control:
; Date Created:      Thu Nov 11 16:33:22 2010
; %version:          1 %
; %derived_by:       czgng4 %
; %date_modified:    Fri Jun  8 09:31:06 2012 % 
;----------------------------------------------------------------------------
;-------------------------------------------------------------------------------
; sys_memory.asm
;
; (c) Texas Instruments 2009-2010, All rights reserved.
;

    .text
    .arm


;-------------------------------------------------------------------------------
; Initialize memory
; Requires memory initialization mask to be passed as an argument
; e.g. _memoryInit_(0x1) to initialize CPU RAM
	.ref ResetCause_Cnt_Enum

    .def     _memoryInit_
    .asmfunc

_memoryInit_
		;Nexteer Addition: Store off reset cause
        ldr   r2, int_ResetCause_Cnt_Enum
        ldr   r3, [r2]

        ldr   r12, regMinitGcr    ; MINITGCR register pointer
        mov   r1, #0xA
        str   r1, [r12]
        str   r0, [r12, #4]		  ; load RAM initialization mask from passed argument

mloop
        ldr   r0, [r12, #12]
        tst   r0, #0x100
        beq   mloop
        mov   r1, #5
        str   r1, [r12]
        ;Nexteer Addition: Restore reset cause
        str   r3, [r2]

        bx    lr

regMinitGcr   				.word	0xFFFFFF5C
int_ResetCause_Cnt_Enum		.word	ResetCause_Cnt_Enum
    .endasmfunc

;*****************************************************************************
;
;CHANGE HISTORY:
;
;Date      Rev      Author         Change Description              SCR #
;                                    (MDD Rev & Date)
;-------   -------  --------  -----------------------------------  ----------
;06/09/12   1.0      LWW       Initial file creation
;******************************************************************************
