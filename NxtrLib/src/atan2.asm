;-------------------------------------------------------------------------------
; atan2.asm
;
; (c) Texas Instruments 2012, All rights reserved.
;
	.global octants
    .text
    .thumb

;-------------------------------------------------------------------------------
; atan2_asm.  Assembly Language optimized atan routine for signed 16-bit inputs (x,y)

    .def     _atan2_asm_
    .asmfunc

_atan2_asm_

		stmfd R13!, {R2, R3, R7, R8, R9, R10, R11, R14}				; Store multiple...

;	y_zero = (y==0);			// Perform the compare of y==0
;	x_orig = x;					// Store original x value

        tst r1,#0xffffffff		; Test is y=0
        mrs	r8,CPSR				; Move the program status register (with condition codes) to r8
		mov	r9,#0x00000001		; This is zero flag (bit 30), preshifted by 30 for the comparison
        mov r10,r0				; Store r0 (x_orig) in r10 for later processing
        and	r8,r9,r8, lsr #30	; And to get just the Z flag, Shift by 30 so r8 = 1 if y=0

;    z = (y>>15)&1; 			// z = 1 if (y<0) else z = 0
;    oct = 4*z;					// If (y<0), then oct = 4
;    zp = (z^1)&1;				// zp is inverted z

		lsr r2,r1,#15			; Logical shift y by 15
		and r2,r2,#1			; And with 0x1 -- r2 is now z
		lsl	r7,r2,#2			; Then shift by 2(mult by 4) and store OCT in r7
		eor r3,r2,#1			; Exclusive Or, Now R3 has zp

;    z = zp - z;				// change z into -1 or +1 (if y<0, then z = -1, if y>=0, then z=1)
;    x = x*z;					// If y<0, then x=-x, else x=x
;    y = y*z;					// if y<0, then y=-y

        sub r2,r3,r2			; Make z = zp - z
        smulbb r0,r2,r0			; Multiply x * z
        smulbb r1,r2,r1			; Multiply y*z

;    z = ((x-1)>>15)&1;			// z = 1 if (x<=0), else z = 0 !! Warning, using x-1 limits input range of X
;    oct += 2*z;				// If x<0, then add 2 to oct mapping
;    zp = (z^1)&1;				// zp is inverted z bit

		sub r2,r0,#1			; Subtract one from X input
		and r2,r9,r2, lsr #15	; shift r2 right by 15, AND with #1
		mov r9,#2				; Move #2 into r9 for MAC operation
		eor r3,r2,#1			; Exclusive Or
		smlabb	r7,r2,r9,r7		; Now oct += 2*z...
		mov r9,r0				; Move r0 into r9 for temp storage
		and r3,r3,#1			; Now R3 has zp

;    temp = x;					// store x in a temp location
;    x = y*z + x*zp;			// If x<0 then x = y, else x = x
;    y = y*zp - temp*z;			// if x<0, then y=-x, else, y = y

		mov r11,#0xffffffff		; Load -1 into r11
		smulbb r0,r3,r0			; Multiply x*zp
		smulbb	r9,r11,r9		; make temp = -x
		smlabb	r0,r1,r2,r0		; X = y*z + z*zp
		smulbb r1,r3,r1			; multipl y*zp
		smlabb r1,r9,r2,r1		; Now y = y*zp - temp*z

;    temp = y-x;				// Create temp value for y-x
;    zp = ((temp)>>15)&1; 		// zp = 0 if (x<=y), else zp = 1

;    z = (zp^1)&1;				// z in this case will be inverted zp (i.e. z =1 if (x<=y))
;    oct += z;					// increment octant by z (if x<=y then oct +=1)
;    x = x + y*z;				// if (x<=y) then x = x + y (else x = x)
;    y = y*zp + temp*z; 		// if (x<=y) then y = y-x (else y = y)

		sub	r9,r1,r0			; put y-z into temp
		lsr	r3,r9,#15			; temp shifted by 15
		and r3,r3,#1			; and with 1, r3 now has zp
		eor r2,r3,#1			; exclusive or (z = zp^1), so now r2 is z
		add r7,r2,r7			; Oct += z
		smlabb r0,r1,r2,r0		; x = x + y*z
		smulbb	r1,r3,r1		; y = y*zp
		smlabb r1,r9,r2,r1		; y = y*zp + temp*z

;    phi = octants[oct]*((BRAD_PI))/4; 			//  phi is set by the octant table value scaled by BRAD_PI/4 (octant value);
;    t = ((int)y<<fixShift)/((int)(x)+0);		// Perform divide with dynamic range scaling
;    t2= (-t*t)>>fixShift;						// t2 = -1*t^2.  Also, shift back

		mov r3,#0x8000			; This is 2^15
		mul	r1,r3,r1			; Shift y left by 15 using multiplication
		sdiv r1,r1,r0			; This is t

		ldr r2,oct				; Load base address of octants[]
		lsl r7,#2				; Need to get to word addressing (mult by 4) for offset
		ldr r3, [r2, r7]		; load r3 with octants[oct]
		mov	r7,#0x1000			; This is Brad_PI/4
		smulbb r3,r3,r7			; Now r3 is PHI

		mul r2,r1,r1			; This is t*t
		mov r0,#0x00a9			; Start with first constant value
		mul r2,r11,r2			; This is -1*t*t
		asr	r2,r2,#15			; Shift back, r2 is now t2

;    dphi= 0x00A9;
;    dphi= 0x0390 + (t2*dphi>>fixShift);
;    dphi= 0x091C + (t2*dphi>>fixShift);
;    dphi= 0x0FB6 + (t2*dphi>>fixShift);
;    dphi= 0x16AA + (t2*dphi>>fixShift);
;    dphi= 0x2081 + (t2*dphi>>fixShift);
;    dphi= 0x3651 + (t2*dphi>>fixShift);
;    dphi= 0xA2F9 + (t2*dphi>>fixShift);

		mov r11,#0x0390			; Load constant
		smulbb	r0,r2,r0		; Multiply
		add	r0,r11,r0, asr #15	; Add and Shift

		mov r11,#0x091c			; Load constant
		smulbb	r0,r2,r0		; Multiply
		add	r0,r11,r0, asr #15	; Add and Shift

		mov r11,#0x0fb6			; Load constant
		smulbb	r0,r2,r0		; Multiply
		add	r0,r11,r0, asr #15	; Add and Shift

		mov r11,#0x16aa			; Load constant
		smulbb	r0,r2,r0		; Multiply
		add	r0,r11,r0, asr #15	; Add and Shift

		mov r11,#0x2081			; Load constant
		smulbb	r0,r2,r0		; Multiply
		add	r0,r11,r0, asr #15	; Add and Shift

		mov r11,#0x3651			; Load constant
		smulbb	r0,r2,r0		; Multiply
		add	r0,r11,r0, asr #15	; Add and Shift

		mov r11,#0xa2f9			; Load constant
		smulbb	r0,r2,r0		; Multiply
		add	r0,r11,r0, asr #15	; Add and Shift

;    phi = phi - (dphi*t >> (fixShift+3));		// Final algorithm adjustment
;    phi = (phi*(1-y_zero));					// If y = 0, then set phi = 0 to clear phi for special cases

		mul r0,r1,r0			; This is dphi*t
		mov r11,#1				; Load r11 with the constant 1
		sub r0,r3,r0, asr #18	; Shift r0 to right 18. after subtract, r0 is phi = phi -...
		sub r9,r11,r8			; r9 is now 1-y_zero
		smulbb r0,r9,r0			; This is final phi

;    z = (x_orig>>15)&1; 		// z = 1 if x_original is less than 0
;    zp = (z^1)&1;				// zp is inverted z
;    z = zp - z;				// change z into -1 or +1 (if x_orig<0, then z = -1, if x_orig>=0, then z=1)

		asr r2,r10,#15			; Shift X_original by 15 and store in r2
		and r2,r2,#1			; And with 1 to get sign bit
		eor r3,r2,#1			; Exclusive Or, now r3 is Zp
		sub	r2,r3,r2			; Now r2 is z and r3 is zp
		mov	r9,#0x40000000		; This is zero flag (bit 30)

;    phi += (y_zero*(int)z*(BRAD_PI_DIV2));		// If y=0 and x_orig<0, then phi = -pi/2, if y=0 and x_orig>0, then phi = pi/2
;    z = 1 - ((x_orig == 0) & y_zero);			// Compare for original x = 0 and y = 0

		smulbb	r7,r2,r8		; Multiply y_zero * z and put in r7
		add r0,r0,r7, lsl #13	; Multiply by Brad_pi_div2 in r7.  R0 is phi += ...

        tst r10,#0xffffffff		; Test x_orig = 0
        mrs	r10,CPSR			; Move the program status register (with condition codes) to r8
        and	r10,r9,r10			; And to get just the Z flag
		and r10,r8,r10, lsr #30	; (x_orig == 0) & y_zero)
		sub r2,r11,r10

;    phi = phi*z;				// Finally, if y=0 and x = 0, return 0

		smulbb r0,r2,r0

		LDMFD           R13!, {R2, R3, R7, R8, R9, R10, R11, PC}

oct	.word octants

    .endasmfunc


;-------------------------------------------------------------------------------

