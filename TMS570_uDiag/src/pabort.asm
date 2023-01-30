;*****************************************************************************
; Copyright 2010 Nexteer Automotive, All Rights Reserved.
; Nexteer Confidential
;
; Module File Name  : pabort.asm
; Module Description: prefetch abort handler
; Product           : Gen II Plus - EA3.0
; Author            : Lucas Wendling
;*****************************************************************************
;---------------------------------------------------------------------------
; Version Control:
; Date Created:      Fri Jun 29 10:22:38 2012
; %version:          1 %
; %derived_by:       czgng4 %
; %date_modified:    Fri Jun 29 10:22:38 2012 %
;----------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; pabort.asm
;
; (c) Texas Instruments 2009-2010, All rights reserved.
;

    .text
    .arm


;-------------------------------------------------------------------------------
; Run Memory Test

    .ref	AbortHandler
    .def	_pabort
    .asmfunc

_pabort
		stmfd	r13!, {r0 - r12, lr}; push registers and link register on to stack

        ldr		r12, esmsr3			; ESM Group3 status register
        ldr		r0,  [r12]
        tst		r0,  #0x8			; check if bit 3 is set, this indicates uncorrectable ECC error on B0TCM
        bne		ramErrorFound
        tst		r0, #0x20			; check if bit 5 is set, this indicates uncorrectable ECC error on B1TCM
        bne		ramErrorFound

noRAMerror
		tst		r0, #0x80			; check if bit 7 is set, this indicates uncorrectable ECC error on ATCM
		bne		flashErrorFound

		mov     r0, #0xFFCE			; pass general prefetch abort reset cause
		movt    r0, #0x0031
		bl		AbortHandler		; custom prefetch abort handler required
									; If this custom handler is written in assembly, all registers used in the routine
									; and the link register must be saved on to the stack upon entry, and restored before
									; return from the routine.

		ldmfd	r13!, {r0 - r12, lr}; pop registers and link register from stack
		subs	pc, lr, #8			; restore state of CPU when abort occurred, and branch back to instruction that was aborted

ramErrorFound
		mov     r0, #0xFFCD			; pass multi bit ram prefetch abort reset cause
		movt    r0, #0x0032
		bl		AbortHandler		; branch to abort handler

flashErrorFound
		mov     r0, #0xFFCC			; pass multi bit flash prefetch abort reset cause
		movt    r0, #0x0033
		bl		AbortHandler		; branch to abort handler

esmsr3		.word	0xFFFFF520

    .endasmfunc


;*****************************************************************************
;
;CHANGE HISTORY:
;
;Date      Rev      Author         Change Description              SCR #
;                                    (MDD Rev & Date)
;-------   -------  --------  -----------------------------------  ----------
;06/29/12   1.0      LWW      Initial file creation
;******************************************************************************
