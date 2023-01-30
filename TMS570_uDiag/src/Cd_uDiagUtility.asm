;*****************************************************************************
; Copyright 2013 Nexteer Automotive, All Rights Reserved.
; Nexteer Confidential
;
; Module File Name  : Cd_uDiagUtility.asm
; Module Description: uDiag utility functions
; Product           : Gen II Plus - EA3.0
; Author            : Kathleen Creager
;*****************************************************************************
;---------------------------------------------------------------------------
; Version Control:
; Date Created:      Thu Jun  6 12:16:47 2013
; %version:          1 %
; %derived_by:       nz63rn %
; %date_modified:    Thu Jun  6 12:18:22 2013 %
;----------------------------------------------------------------------------
;
;-------------------------------------------------------------------------------
; Cd_uDiagUtility.asm
;
;

    .text
    .arm

;-------------------------------------------------------------------------------
; Get Link Register for FIQ ISR

    .def     _uDiagGetLinkRegForFiqIsr_
    .asmfunc

_uDiagGetLinkRegForFiqIsr_:

        ldr	r0, [sp, #0x5C]
        bx	lr

    .endasmfunc

