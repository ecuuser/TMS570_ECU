;*****************************************************************************
; Copyright 2010 Nexteer Automotive, All Rights Reserved.
; Nexteer Confidential
;
; Module File Name  : sys_core.asm
; Module Description: TI Halcogen based micro init
; Product           : Gen II Plus - EA3.0
; Author            : Jeremy Warmbier
;*****************************************************************************
;---------------------------------------------------------------------------
; Version Control:
; Date Created:      Thu Nov 11 16:33:22 2010
; %version:          3 %
; %derived_by:       czgng4 %
; %date_modified:    Thu Oct  3 16:34:57 2013 % 
;----------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; sys_core.asm
;
; (c) Texas Instruments 2009-2010, All rights reserved.
;

    .text
    .arm

;-------------------------------------------------------------------------------
; Enable VFP Unit

    .def     _coreEnableVfp_
    .asmfunc

_coreEnableVfp_

        mrc   p15,     #0x00,      r0,       c1, c0, #0x02
        orr   r0,      r0,         #0xF00000
        mcr   p15,     #0x00,      r0,       c1, c0, #0x02
        mov   r0,      #0x40000000
        fmxr  fpexc,   r0
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Initialize CPU Registers, including banked registers for all modes
	.ref _StackUSER_
	.ref _StackFIQ_
	.ref _StackUND_
	.ref _StackIRQ_
	.ref _StackABORT_
	.ref _StackSVC_

	.def     _coreInitRegisters_
    .asmfunc

_coreInitRegisters_

	; After reset, the CPU is in the Supervisor mode (M = 10011)
	    mov r0,  lr
	    mov r1,  #0x0000
	    mov r2,  #0x0000
	    mov r3,  #0x0000
	    mov r4,  #0x0000
	    mov r5,  #0x0000
	    mov r6,  #0x0000
	    mov r7,  #0x0000
	    mov r8,  #0x0000
	    mov r9,  #0x0000
	    mov r10, #0x0000
	    mov r11, #0x0000
	    mov r12, #0x0000
		ldr sp,  svcSp

	    ; Switch to FIQ mode (M = 10001)
	    cps      #17
	    mov r8,  #0x0000
	    mov r9,  #0x0000
	    mov r10, #0x0000
	    mov r11, #0x0000
	    mov r12, #0x0000

		; Abort mode
        cps   #23
        ldr   sp,       abortSp
        mov   lr,		r0

        ; Undefined instruction mode
        cps   #27
        ldr   sp,       undefSp
        mov   lr,		r0

        ; FIQ mode
        cps   #17
        ldr   sp,       fiqSp
        mov   lr,		r0

        ; IRQ mode
        cps   #18
        ldr   sp,       irqSp
        mov   lr,		r0

        ; System mode
        cps   #31
        ldr   sp,       userSp		; SYS mode shares stack with User mode
        mov   lr,		r0

	    ; Switch back to Supervisor Mode (M = 10011)
	    cps #19
		fmdrr d0,         r1,     r1
        fmdrr d1,         r1,     r1
        fmdrr d2,         r1,     r1
        fmdrr d3,         r1,     r1
        fmdrr d4,         r1,     r1
        fmdrr d5,         r1,     r1
        fmdrr d6,         r1,     r1
        fmdrr d7,         r1,     r1
        fmdrr d8,         r1,     r1
        fmdrr d9,         r1,     r1
        fmdrr d10,        r1,     r1
        fmdrr d11,        r1,     r1
        fmdrr d12,        r1,     r1
        fmdrr d13,        r1,     r1
        fmdrr d14,        r1,     r1
        fmdrr d15,        r1,     r1
        bl    next1
next1
        bl    next2
next2
        bl    next3
next3
        bl    next4
next4
        bx    r0

userSp	.word _StackUSER_
svcSp   .word _StackSVC_
fiqSp   .word _StackFIQ_
irqSp   .word _StackIRQ_
abortSp .word _StackABORT_
undefSp .word _StackUND_

    .endasmfunc

;-------------------------------------------------------------------------------
; Clear ESM CCM errorss

    .def  _esmCcmErrorsClear_
    .asmfunc

_esmCcmErrorsClear_:

        ldr   r0, ESMSR1_REG	; load the ESMSR1 status register address
		ldr   r2, ESMSR1_ERR_CLR
		str	  r2, [r0]	 	; clear the ESMSR1 register

		ldr   r0, ESMSR2_REG	; load the ESMSR2 status register address
		ldr   r2, ESMSR2_ERR_CLR
		str	  r2, [r0]	 	; clear the ESMSR2 register

		ldr   r0, ESMSSR2_REG	; load the ESMSSR2 status register address
		ldr   r2, ESMSSR2_ERR_CLR
		str	  r2, [r0]	 	    ; clear the ESMSSR2 register

		ldr   r0, ESMKEY_REG	; load the ESMKEY register address
		mov	  r2, #0x5             ; load R2 with 0x5
		str	  r2, [r0]	 	    ; clear the ESMKEY register

		ldr   r0, VIM_INTREQ	; load the INTREQ register address
		ldr   r2, VIM_INT_CLR
		str	  r2, [r0]	 	; clear the INTREQ register

		ldr   r0, CCMR4_STAT_REG	; load the CCMR4 status register address
		ldr   r2, CCMR4_ERR_CLR
		str	  r2, [r0]	 	; clear the CCMR4 status register
        bx    lr

ESMSR1_REG      .word  0xFFFFF518
ESMSR2_REG      .word  0xFFFFF51C
ESMKEY_REG      .word  0xFFFFF538
ESMSSR2_REG     .word  0xFFFFF53C
CCMR4_STAT_REG  .word  0xFFFFF600
CCMR4_ERR_CLR   .word  0x00010000
ESMSR1_ERR_CLR  .word  0x80000000
ESMSR2_ERR_CLR  .word  0x00000004
ESMSSR2_ERR_CLR .word  0x00000004
VIM_INT_CLR     .word  0x00000001
VIM_INTREQ      .word  0xFFFFFE20

    .endasmfunc

;-------------------------------------------------------------------------------
; Enable RAM ECC Support

    .def     _coreEnableRamEcc_
    .asmfunc

_coreEnableRamEcc_

        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        orr   r0,  r0,    #0x0C000000
        dmb
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        isb
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Disable RAM ECC Support

    .def     _coreDisableRamEcc_
    .asmfunc

_coreDisableRamEcc_

        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        bic   r0,  r0,    #0x0C000000
        dmb
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        isb
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Get debug status register

    .def  _coreGetDebugStatusAndControlRegister_
    .asmfunc

_coreGetDebugStatusAndControlRegister_:

        mrc   p14, #0x00, r0, c0, c1, #0x00
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Get secondary auxiliary control register

    .def  _coreGetSecondaryAuxiliaryControlRegister_
    .asmfunc
_coreGetSecondaryAuxiliaryControlRegister_:

        mrc   p15, #0, r0, c15, c0, #0
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Set secondary auxiliary control register

    .def  _coreSetSecondaryAuxiliaryControlRegister_
    .asmfunc
_coreSetSecondaryAuxiliaryControlRegister_:

        mcr   p15, #0, r0, c15, c0, #0
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Get Floating Point Status and Control Register

    .def  _coreGetFPSCR_
    .asmfunc
_coreGetFPSCR_:

		fmrx r0, FPSCR
		bx	lr

    .endasmfunc

;-------------------------------------------------------------------------------
; C++ construct table pointers

    .def    __TI_PINIT_Base, __TI_PINIT_Limit
    .weak   SHT$$INIT_ARRAY$$Base, SHT$$INIT_ARRAY$$Limit

__TI_PINIT_Base  .long SHT$$INIT_ARRAY$$Base
__TI_PINIT_Limit .long SHT$$INIT_ARRAY$$Limit

    


;*******************************************************************************************************
;
;CHANGE HISTORY:
;
;Date      Rev      Author         Change Description                                         SCR #
;                                    (MDD Rev & Date)
;-------   -------  --------  -----------------------------------                           ----------
;06/09/12   1.0      LWW      Initial file creation
;06/06/13   2.0      KMC      Added functions needed for Cd_uDiag fp exception handling		sag_EPS#8587
;10/03/13   3.0      LWW      Added fuction to disable RAM ECC
;*******************************************************************************************************
