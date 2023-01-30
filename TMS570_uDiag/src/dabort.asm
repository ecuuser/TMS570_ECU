;*****************************************************************************
; Copyright 2010 Nexteer Automotive, All Rights Reserved.
; Nexteer Confidential
;
; Module File Name  : dabort.asm
; Module Description: data abort handler
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
; dabort.asm
;
; (c) Texas Instruments 2009-2010, All rights reserved.
;

    .text
    .arm


;-------------------------------------------------------------------------------
; Run Memory Test

    .ref	AbortHandler
    .ref 	ResetCause_Cnt_Enum
    .def	_dabort
    .asmfunc

_dabort
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

		mov     r0, #0xFFCF			; pass general data abort reset cause
		movt    r0, #0x0030
		bl		AbortHandler	; custom data abort handler required
									; If this custom handler is written in assembly, all registers used in the routine
									; and the link register must be saved on to the stack upon entry, and restored before
									; return from the routine.

		ldmfd	r13!, {r0 - r12, lr}; pop registers and link register from stack
		subs	pc, lr, #8			; restore state of CPU when abort occurred, and branch back to instruction that was aborted

ramErrorFound
		ldr		r1, ramctrl			; RAM control register for B0TCM TCRAMW
		ldr		r2, [r1]
		tst		r2, #0x100			; check if bit 8 is set in RAMCTRL, this indicates ECC memory write is enabled
		beq		ramErrorReal
		mov		r2, #0x20
		str		r2, [r1, #0x10]		; clear RAM error status register
		ldr		r1, ram2ctrl
		str		r2, [r1, #0x10]		; clear RAM error status register

		mov		r2, #0x28
		str		r2, [r12]			; clear ESM group3 flags for uncorrectable RAM ECC errors
		mov		r2, #5
		str		r2, [r12, #0x18]	; The nERROR pin will become inactive once the LTC counter expires

		ldr   r3, int_ResetCause_Cnt_Enum		; Set ResetCause back to PowerOn Reset
		mov		r4, #0xFFFF
		str   r4, [r3]

		ldmfd	r13!, {r0 - r12, lr}
		subs	pc, lr, #4			; branch to instruction after the one that caused the abort
									; this is the case because the data abort was caused intentionally
									; and we do not want to cause the same data abort again.

ramErrorReal
		mov     r0, #0xFFD1			; pass multi bit ram data abort reset cause
		movt    r0, #0x002E
		bl		AbortHandler		; branch to abort handler

flashErrorFound
		ldr		r1, flashbase
		ldr		r2, [r1, #0x6C]		; read FDIAGCTRL register
		lsr		r2, #16
		tst		r2, #5				; check if bits 19:16 are 5, this indicates diagnostic mode is enabled
		beq		flashErrorReal
		mov		r2, #1
		lsl		r2, #8
		str		r2, [r1, #0x1C]		; clear FEDACSTATUS error flag

		mov		r2, #0x80
		str		r2, [r12]			; clear ESM group3 flag for uncorrectable flash ECC error
		mov		r2, #5
		str		r2, [r12, #0x18]	; The nERROR pin will become inactive once the LTC counter expires

		ldr   r3, int_ResetCause_Cnt_Enum		; Set ResetCause back to PowerOn Reset
		mov		r4, #0xFFFF
		str   r4, [r3]

		ldmfd	r13!, {r0 - r12, lr}
		subs	pc, lr, #4			; branch to instruction after the one that caused the abort
									; this is the case because the data abort was caused intentionally
									; and we do not want to cause the same data abort again.


flashErrorReal
		mov     r0, #0xFFD0			; pass multi bit flash data abort reset cause
		movt    r0, #0x002F
		bl		AbortHandler		; branch to abort handler

int_ResetCause_Cnt_Enum		.word	ResetCause_Cnt_Enum
esmsr3		.word	0xFFFFF520
ramctrl		.word	0xFFFFF800
ram2ctrl	.word	0xFFFFF900
ram1errstat	.word	0xFFFFF810
ram2errstat	.word	0xFFFFF910
flashbase	.word	0xFFF87000

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
