;*****************************************************************************
; Copyright 2010 Nexteer Automotive, All Rights Reserved.
; Nexteer Confidential
;
; Module File Name  : undefinst.asm
; Module Description: undefined instruction handler
; Product           : Gen II Plus - EA3.0
; Author            : Lucas Wendling
;*****************************************************************************
;---------------------------------------------------------------------------
; Version Control:
; Date Created:      Mon Jul  2 09:12:09 2012
; %version:          1 %
; %derived_by:       czgng4 %
; %date_modified:    Mon Jul  2 09:12:09 2012 %
;----------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; undefinst.asm

    .text
    .arm


;-------------------------------------------------------------------------------

    .ref	AbortHandler
    .def	_undefinst
    .asmfunc

_undefinst
		stmfd	r13!, {r0 - r12, lr}; push registers and link register on to stack
		mov     r0, #0xFFCB			; pass undefined instruction reset cause
		movt    r0, #0x0034
		bl		AbortHandler		; branch to abort handler

    .endasmfunc


;*****************************************************************************
;
;CHANGE HISTORY:
;
;Date      Rev      Author         Change Description              SCR #
;                                    (MDD Rev & Date)
;-------   -------  --------  -----------------------------------  ----------
;07/02/12   1.0      LWW      Initial file creation
;******************************************************************************
