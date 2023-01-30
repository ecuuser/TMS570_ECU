; Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1

;*****************************************************************************
; Project Name: AUTOSAR OS 3.0
;    File Name: osekasm.asm
;
;  Module version: $vv$=1.13
;
;  Description: Assembler functions for OSEK TMS570 (TI compiler version)
;
;-----------------------------------------------------------------------------
;               C O P Y R I G H T
;-----------------------------------------------------------------------------
; Copyright (c) 2011-2012 Vector Informatik GmbH          All rights reserved.
;****************************************************************************/

  .sect ".oscode"  ; TR:SPMF95:0010 

; some OSEK constants
osRef_AAAAAAAA             .word 0AAAAAAAAh   ; TR:SPMF89:01.0033

PRE_READY                  .equ 0
; TR:SOSK22:0036 Start
RUNNING                    .equ 1
; TR:SOSK22:0036 End
; TR:SOSK22:0037 Start 
READY                      .equ 3
; TR:SOSK22:0037 End 

STANDARD_STATUS            .equ 0
EXTENDED_STATUS            .equ 1

CTX_TASK                   .equ 1

osdORTINoService           .equ 0

osdNoActiveTask            .equ 0xffff
osdNoActivePrio            .equ 0xffff

  ; use correct register names if redefined in tcb.inc
  .asg "c0", c0
  .asg "c1", c1

  .ref osConfigBlock
tsConfigBlock .struct
aucMagicNumber   .word     ; 130 42 12 196  = 0x82 2A 0C C4
uiLength         .half
uiHardwareID     .half     ; Hardware Identification
ucMajorVersion   .byte
ucMinorVersion   .byte
uiConfigBlockVersion .half   ; configuration block format version
uiUserConfigurationVersion .half   ; user configuration version

; start addresses of sub-containers (fixed number)
uiStartAddressConfBlock               .word
uiStartAddressSubCont0                .word
uiStartAddressTaskStart               .word
uiStartAddressTaskPreemptive          .word
uiStartAddressTaskTrusted             .word
uiStartAddressStackStart              .word
uiStartAddressStackEnd                .word
uiStartAddressTaskMPUSettings         .word
uiStartAddressTaskToAppl              .word
uiStartAddressNTFTaskStackMPUSetting  .word
uiStartAddressNTFTaskStackStartAddress.word
uiStartAddressNTFTaskStackEndAddress  .word
uiStartAddressISRMPUSettings          .word
uiStartAddressISRToAppl               .word
uiStartAddressISRTrusted              .word
uiStartAddressNTFISRStackMPUSetting   .word
uiStartAddressNTFISRStackStartAddress .word
uiStartAddressNTFISRStackEndAddress   .word
uiStartAddressISRStackStart           .word
uiStartAddressISRStackEnd             .word
uiStartAddressTrustedFct              .word
uiStartAddressTrustedFctToAppl        .word
uiStartAddressNonTrustedFct           .word
uiStartAddressNonTrustedFctToAppl     .word
uiStartAddressSpecStackStart          .word
uiStartAddressSpecStackEnd            .word
uiStartAddressOSMPUSettings           .word
uiStartAddressApplMPUSettings         .word
uiStartAddressPeripheralRegionStart   .word
uiStartAddressPeripheralRegionEnd     .word
uiStartAddressPeripheralRegionAccess  .word
uiStartAddressISRPrio                 .word
uiStartAddressISREnableNesting        .word
uiStartAddressIRQFIQSetting           .word
uiStartAddressINTChannelMap           .word

; Sub-Container 0 = General (fixed number)
uiNumberOfTasks                .half
uiNumberOfCat2ISRs             .half
uiNumberOfTrustedFunctions     .half
uiNumberOfNonTrustedFunctions  .half
uiNumberOfIRQNestings          .half
uiNumberOfApplications         .half
uiNumberOfSpecStacks           .half
uiNumberOfPeripheralRegions    .half
ucStackUsageMeasurement        .byte
   .endstruct

osConfigBlock .tag tsConfigBlock  
  
  .def osDispatcher
  .def osDirectSWIDispatcher
  .def osStartOSasm
  .def osPrefetchAbort
  .def osFIQ
  .def osUnhandledExceptionWrapper
  .def osDataAbort
  .def osSWI
  .def osUndefInstruction
  .def osEnterCallLeaveISR
  
osExtRef .macro rname
  .ref :rname:
osRef_:rname:    .word  :rname:
 .endm
 
  osExtRef osaActiveTaskIndex
  osExtRef osHighReadyTaskPrio
  osExtRef osActiveTaskPrio
  osExtRef osHighReadyTaskIndex
  osExtRef osaTcbSP
  osExtRef osaTcbValid
  osExtRef osLockDispatcher
  osExtRef osTcbTaskState
  osExtRef osSystemStack
  osExtRef osIrqStack
  osExtRef osSupervisorStack
  osExtRef osStartDispatcher
  osExtRef osUnhandledException
  osExtRef _dabort			;Nexteer edit for anomaly 3032
  osExtRef _pabort		;Nexteer edit for anomaly 3032
 
  osExtRef osaActiveApplicationID
  osExtRef osSetMPUForTask
  osExtRef osCurrentContext
  osExtRef osProtectionTrap
  
  osExtRef osaIntNestingDepth
  osExtRef osaActiveISRID
  .ref osIntNestingOverflow
  .ref osSystemStackOverflow
  .ref osEnterProtectedISR  
  .ref osLeaveProtectedISR  
  
osRef_osdErrYOStackOverflow           .word 0xA101
osRef_osdErrYOIrqStackOverflow        .word 0xA102
osRef_osdErrYOIntHdlStackOverflow     .word 0xA103 
osRef_osdErrDPStartValidContext       .word 0xA401
osRef_osdErrDPResumeInvalidContext    .word 0xA402
osRef_osdErrDPWrongHighReadyTaskIndex .word 0xA501   

osRef_osDispatcher .word osDispatcher
osRef_osCheck_Write .word osCheck_Write
osRef_osCheck_Return .word osCheck_Return

  osExtRef osORTICurrentServiceId
  osExtRef osTcbORTIServiceId

  osExtRef osMissingTerminateError
  osExtRef osPeripheralError

oscnfTcbStackBottom  .word osConfigBlock.uiStartAddressStackStart
oscnfTcbStackTop  .word osConfigBlock.uiStartAddressStackEnd
oscnfTcbIsTrusted    .word osConfigBlock.uiStartAddressTaskTrusted
oscnfTcbTaskPreemption    .word osConfigBlock.uiStartAddressTaskPreemptive
oscnfTcbTaskStartAddress    .word osConfigBlock.uiStartAddressTaskStart
oscnfSpecStackStart    .word osConfigBlock.uiStartAddressSpecStackStart
oscnfSpecStackEnd    .word osConfigBlock.uiStartAddressSpecStackEnd
oscnfNumberOfTasks    .word osConfigBlock.uiNumberOfTasks
oscnfISRStackStart    .word osConfigBlock.uiStartAddressISRStackStart
oscnfISRStackEnd    .word osConfigBlock.uiStartAddressISRStackEnd
oscnfNumberOfIRQNestings    .word osConfigBlock.uiNumberOfIRQNestings
oscnfStackUsageMeasurement    .word osConfigBlock.ucStackUsageMeasurement
oscnfTaskToAppl    .word osConfigBlock.uiStartAddressTaskToAppl
oscnfPeripheralRegionStart    .word osConfigBlock.uiStartAddressPeripheralRegionStart
oscnfPeripheralRegionEnd    .word osConfigBlock.uiStartAddressPeripheralRegionEnd
oscnfPeripheralRegionAccess    .word osConfigBlock.uiStartAddressPeripheralRegionAccess
oscnfNumberOfPeripheralRegions   .word osConfigBlock.uiNumberOfPeripheralRegions
oscnfISRPrio                     .word osConfigBlock.uiStartAddressISRPrio
oscnfISREnableNesting            .word osConfigBlock.uiStartAddressISREnableNesting
oscnfISRTrusted            .word osConfigBlock.uiStartAddressISRTrusted

stkIdxSystemStack .equ 0
stkIdxIrqStack    .equ 1
stkIdxStartupStack .equ 2
stkIdxSupervisorStack    .equ 3
stkIdxAPIStack    .equ 4
  
  osExtRef osStackOverflow
  osExtRef osFillSystemStack
  osExtRef osInitSystemStack
  osExtRef osLastActiveTaskIndex
 
  osExtRef osSetMPUForOS
  osExtRef osAsmAssertFailed
  
  .ref osSaveTaskMPUSettings
  .ref osRestoreTaskMPUSettings
  .ref osInitTaskStacks  

osSysMode .equ 011111b
osSVCMode .equ 010011b
osIRQMode .equ 010010b
osAbortMode .equ 10111b


osEnterCallLeaveISR
   ; TR:SPMF89:01.0034 Start
   ; TR:SPMF89:01.0094 Start
   ;registers {r0,r1,lr,r2,r3,r4,ip} already pushed and lr points to ISR function reference, r3 = ISRid
   ; must never run in FIQ mode where ip is shadowed!
   ldr    ip,[lr]                 ; IP = *LR  (address of ISR handler to call)         

   ; TR:SPMF89:01.0005 Start
   mrs    r0, SPSR                ; r0 = SPSR
   str    r0, [sp, #-4]!          ; push SPSR (from r0)
   ; TR:SPMF89:01.0005 End

   ; Step 1 of design INT Cat2 entry
   ; lock Dispatcher TR:SOSK22:0008 Start
   ldr    r0, osRef_osLockDispatcher   ; r0 = &osLockDispatcher
   ldrb   r1,[r0]                      ; r1 = osLockDispatcher  (r1 = *r0)
   add    r1,r1,#1                     ; r1 = r1 + 1
   strb   r1,[r0]                      ; osLockDispatcher++  (*r0 = r1)
   ; TR:SOSK22:0008 End

   ; Step 2 of design INT Cat2 entry
   ; increment osaIntNestingDepth
   ldr    r0, osRef_osaIntNestingDepth ; r0 = &osaIntNestingDepth
   ldrb   r1,[r0]                      ; r1 = osaIntNestingDepth  (r1 = *r0)

   ; Step 3 of design INT Cat2 entry
   ; check nesting limit
   ; TR:SPMF89:0007 Start
   ldr    r4, oscnfNumberOfIRQNestings ; r4 = &osConfigBlock.uiNumberOfIRQNestings
   ldrh   r4,[r4]                      ; r4 = osConfigBlock.uiNumberOfIRQNestings
   add    r4,r4,#1                     ; r4 = r4+1  (+1 because of phantom vector)
   cmp    r1,r4                        ; r1 = r4?
   beq    osIntNestingOverflow         ; if (osaIntNestingDepth == osConfigBlock.uiNumberOfIRQNestings) goto osIntNestingOverflow

   cmp    r1, #0                       ; r1 == 0 ?  (set CPSR.Z if first interrupt nesting level)
   add    r1,r1,#1                     ; r1 = r1+1
   strb   r1,[r0]                      ; osaIntNestingDepth++   (*r0 = r1)
   ; TR:SPMF89:0007 End

   mov    r4, sp                       ;r4 = SP

   ; Step 4 of design INT Cat2 entry
   ; switch to system mode
   ; TR:SPMF89:01.0009 Start
   cps    #0x1F                        ; CPSR.M = system mode, switch to system mode

   ; Step 5 of design INT Cat2 entry
   mov  r0, sp                         ; r0 = SP
   ldr  r2, oscnfISRStackEnd           ; r2 = &osConfigBlock.uiStartAddressISRStackEnd
   ldr  r2, [r2]                       ; r2 = osConfigBlock.uiStartAddressISRStackEnd
   sub  r2, r2, #4                     ; r2 = r2-4
   ldr  sp, [r2, +r1, lsl #2]          ; SP = ISRStackEnd[osaIntNestingDepth-1]  (SP = *(r2 + (r1 << 2)))
   
   ; Step 6 of design INT Cat2 entry
   ; TR:SPMF89:0029 Start
   ldr  r2, oscnfISRStackStart         ; r2 = &osConfigBlock.uiStartAddressISRStackStart
   ldr  r2, [r2]                       ; r2 = osConfigBlock.uiStartAddressISRStackStart
   sub  r2, r2, #4                     ; r2 = r2-4
   ldr  r2, [r2, +r1, lsl #2]          ; SP = ISRStackStart[osaIntNestingDepth-1]  (r2 = *(r2 + (r1 << 2)))
   sub  r2, sp, r2                     ; r2 = sp - r2
   cmp  r2, #216                       ; r2 == 216?   we need space for (14 words + 16 double words) context + 7 words for wrapper + 1 word stack pattern
   ldrle r0, osRef_osdErrYOIntHdlStackOverflow   ; if (r2 >= 216) r0 = osdErrYOIntHdlStackOverflow
   ble  osSystemStackOverflow          ; if (r2 >= 216) call osSystemStackOverflow(osdErrYOIntHdlStackOverflow)
   ; TR:SPMF89:0029 End
   
   ; Step 7 of design INT Cat2 entry
   ; TR:SPMF89:01.0009 End
   ; TR:SPMF89:0004 Start
   str  r0, [sp, #-4]!                 ; push r0   (save sp)
   str  r4, [sp, #-4]!                 ; push r4   (save IRQ sp)

   str    lr, [sp, #-4]!               ; push LR   (save LRsys)

   fstmdbd sp!,{d0-d15}                ; push d0-d15
   fmrx r0, FPSCR                      ; r0 = FPSCR
   fmrx r2, FPEXC                      ; r2 = FPEXC
   stmfd  sp!,{r0,r2}                  ; push r0, r2  (FPSCR, FPEXC)
   ; TR:SPMF89:0004 End
   

   ; Step 8 of design INT Cat2 entry
   ldr    r0,osRef_osORTICurrentServiceId   ; r0 = &osORTICurrentServiceId
   ldrb   r2, [r0]                          ; r2 = osORTICurrentServiceId
   str    r2, [sp, #-4]!                    ; push r2 = osORTICurrentServiceId
   mov    r2,#osdORTINoService              ; r2 = osdORTINoService
   strb   r2, [r0]                          ; osORTICurrentServiceId = osdORTINoService  (*r0 = r2)

   ; Step 9 of design INT Cat2 entry
   ; TR:SASR30:0108 Start
   ; TR:SASR30:0109 Start
   ; save active ISR ID
   ldr    r0,osRef_osaActiveISRID      ; r0 = &osaActiveISRID
   ldrh   r2, [r0]                     ; r2 = osaActiveISRID
   str    r2, [sp, #-4]!               ; push r2 = osaActiveISRID
   strh   r3, [r0]                     ; osaActiveISRID = r3 = current ISR ID
   ; TR:SASR30:0109 End
   ; TR:SASR30:0108 End

   ; Step 10 of design INT Cat2 entry
  stmfd  sp!,{r5-r11}                  ; push r5-r11
  ; Note: Pass stack pointer to osEnterProtectedISR at same point as expected
  ;       at Label osLeaveISR because after killing of ISR we will return to
  ;       osLeaveISR with this sp
  mov    r0, sp                        ; r0 = SP
  stmfd  sp!,{r1,r3,ip}                ; push r1,r3,ip
  bl osEnterProtectedISR               ; osEnterProtectedISR(sp, nestDepth);
  ldmfd  sp!,{r1,r3,ip}                ; pop r1,r3,ip

   ; !!! r1 must still contain value of osaIntNestingDepth !!!

  ; Step 11 of design INT Cat2 entry
CallISR
   ldr      r0, oscnfISREnableNesting  ; r0 = &osConfigBlock.uiStartAddressISREnableNesting 
   ldr      r0, [r0]                   ; r0 = osConfigBlock.uiStartAddressISREnableNesting
   ldrb     r0, [r0, +r3]              ; r0 = ISREnableNesting[ISRID]  (r0 = *(r0+r3))
   cmp      r0, #1                     ; ISREnableNesting[ISRID] == 1 ?
   beq      osNestEnabled              ; if (ISREnableNesting[ISRID] == 1) goto osNestEnabled

; ISR without nesting
   stmfd    sp!, {r6, lr}              ; push r6, lr

   ldr      r6, oscnfISRTrusted        ; r6 = &osConfigBlock.uiStartAddressISRTrusted
   ldr      r6, [r6]                   ; r6 = osConfigBlock.uiStartAddressISRTrusted
   ldrb     r6, [r6, +r3]              ; r6 = ISRTrusted[ISRID]

   cmp      r6, #1                     ; ISRTrusted[ISRID] == 1 ?
   beq      osISRTrstNoNest            ; if (ISRTrusted[ISRID] == 1) goto osISRTrstNoNest
   cps      #0x10                      ; CPSR.M = user mode, switch to user mode
   mov      lr,pc                      ; LR = PC
   bx       r12                        ; call (r12)
   swi      #0x83                      ; Trap(0x83)   switch to system mode
   b        osISRAfterCallNoNest       ; goto osISRAfterCallNoNest
osISRTrstNoNest
   mov      lr,pc                      ; LR = PC
   bx       r12                        ; call (r12)
   ; TR:SPMF89:01.0034 End

   ; TR:SPMF89:01.0035 Start
osISRAfterCallNoNest   
   ldmfd    sp!, {r6, lr}              ; pop r6, lr
   b        osLeaveISR                 ; goto osLeaveISR
   
osNestEnabled ; ISR nesting enabled   
   ldr      r0, oscnfISRPrio           ; r0 = &osConfigBlock.uiStartAddressISRPrio
   ldr      r0, [r0]                   ; r0 = osConfigBlock.uiStartAddressISRPrio
   ldrb     r0, [r0, +r3]              ; r0 = ISRPrio[ISRID]
   
   mov      r1, #1                     ; r1 = 1
   and      r2, r0, #0x1F              ; r2 = r0 & 0x1F 
   mov      r1, r1, lsl r2             ; r1 = r1 << r2    (= reqMask)
   mov      r2, r0, lsr #5             ; r2 = r0 >> 5  (= reqNr)

   cmp      r2, #0                     ; r2 == 0 ?
   bne      osReqMask_1_2              ; if (r2 != 0) goto osReqMask_1_2
   
; reqMask == 0   
   stmfd    sp!, {r4, r5, r6, r7, r8, r9, lr}   ; push r4, r5, r6, r7, r8, r9, lr
   mov      r0, r12                             ; r0 = r12
   mov      r4, #0                              ; r4 = 0
   
   ; TR:SASR30:0022 Start Read privilege mode of ISR
   ; TR:SASR30:0075 Start Read privilege mode of ISR
   ; TR:SASR30:0322 Start Read privilege mode of ISR
   ; TR:SASR30:0324 Start Read privilege mode of ISR
   ; TR:SASR30:0338 Start Read privilege mode of ISR
   ldr      r6, oscnfISRTrusted      ; r6 = &osConfigBlock.uiStartAddressISRTrusted
   ldr      r6, [r6]                 ; r6 = &osConfigBlock.uiStartAddressISRTrusted
   ldrb     r6, [r6, +r3]            ; r6 = ISRTrusted[ISRID]  (r6 = *(r6+3))
   ; TR:SASR30:0338 End 
   ; TR:SASR30:0324 End 
   ; TR:SASR30:0322 End  
   ; TR:SASR30:0075 End
   ; TR:SASR30:0022 End 
   
   ; TR:SPMF89:01.0007 Start
   ldr      r7, [r4, #-448]          ; r7 = *(0xFFFFFE40)     read ISR mask 0
   ldr      r8, [r4, #-444]          ; r8 = *(0xFFFFFE44)     read ISR mask 1
   ldr      r9, [r4, #-440]          ; r9 = *(0xFFFFFE48)     read ISR mask 2
   ; Disable priorities same and lower in mask 0
   mov      r12, r1                  ; r12 = r1  (reqMask)   
   sub      r12, r4, r12             ; r12 = r4-r12
   str      r12, [r4, #-448]         ; *(0xFFFFFE40) = r12;
   mvn      r5, r12                  ; r5 = ~r12
   and      r5, r5, r7               ; r5 = r5 & r7
   ; Disable lower priorities in mask 1 and 2
   sub      r12, r4, #1              ; r12 = r4-1 = 0xffffffff   
   str      r12, [r4, #-444]         ; *(0xFFFFFE44) = r12 = 0xffffffff  
   str      r12, [r4, #-440]         ; *(0xFFFFFE48) = r12 = 0xffffffff
disLoop0:
   ; wait until writing is finished
   ldr      r12, [r4, #-440]         ; r12 = *(0xFFFFFE48)
   cmp      r12, #0x0                ; r12 == 0?
   bne      disLoop0                 ; if (*(0xFFFFFE48) != 0) goto disLoop0
   ldr      r12, [r4, #-444]         ; r12 = *(0xFFFFFE44)
   cmp      r12, #0x0                ; r12 == 0?
   bne      disLoop0                 ; if (*(0xFFFFFE44) != 0) goto disLoop0
   ldr      r12, [r4, #-448]         ; r12 = *(0xFFFFFE40)
   cmp      r12, r5                  ; r12 == r5?
   bne      disLoop0                 ; if (*(0xFFFFFE40) != r5) goto disLoop0
   cpsie    i                        ; CPSR.I = 0,  enable IRQ  TR:SPMF48:0002
   ; TR:SPMF89:01.0007 End

   ; TR:SASR30:0022 Start Set respective mode for ISR
   ; TR:SASR30:0075 Start Set respective mode for ISR
   ; TR:SASR30:0322 Start Set respective mode for ISR
   ; TR:SASR30:0324 Start Set respective mode for ISR
   ; TR:SASR30:0338 Start Set respective mode for ISR
   cmp      r6, #1                   ; r6 == 1?   (r6 == 1 if ISR is trusted)
   beq      osISRTrst0               ; if (r6 == 1) goto osISRTrst0
   ; call non-trusted ISR handler
   cps      #0x10                    ; CPSR.M = user mode, switch to user mode
   mov      lr,pc                    ; LR = PC
   bx       r0                       ; call (R0)  (= address of ISR handler)
   swi      #0x83                    ; TRAP(0x83), switch to system mode
   b        osISRAfterCall0          ; goto osISRAfterCall0
osISRTrst0
   ; call trusted ISR handler
   ; Step 12 of design INT Cat2 entry (if ISR of mask 0)
   mov      lr,pc                    ; LR = PC
   bx       r0                       ; call (R0)  (= address of ISR handler)
   ; TR:SASR30:0338 End 
   ; TR:SASR30:0324 End 
   ; TR:SASR30:0322 End 
   ; TR:SASR30:0075 End 
   ; TR:SASR30:0022 End 

osISRAfterCall0   
   cpsid  i                          ; CPSR.I = 1,  disable IRQ interrupt
   ; TR:SPMF89:01.0008 Start
   str      r9, [r4, #-456]   ; *FFFFFE38 = r9,  restore ISR mask 2
   str      r8, [r4, #-460]   ; *FFFFFE34 = r9,  restore ISR mask 1
   str      r7, [r4, #-464]   ; *FFFFFE30 = r9,  restore ISR mask 0
   ; TR:SPMF89:01.0008 End
   ldmfd    sp!, {r4, r5, r6, r7, r8, r9, lr}   ; pop r4, r5, r6, r7, r8, r9, lr
   b osLeaveISR                                 ; goto osLeaveISR
   
osReqMask_1_2
   cmp      r2, #1                     ; r2 == 1 ?         
   bne      osReqMask_2
 
; reqMask = first affected mask == 1, set mask1, mask2
   stmfd    sp!, {r4, r5, r6, r7, r8, lr}   ; push r4, r5, r6, r7, r8, lr
   mov      r0, r12                             ; r0 = r12 (= ISR handler to call) 
   mov      r4, #0                              ; r4 = 0
   
   ; TR:SASR30:0022 Start Read privilege mode of ISR
   ; TR:SASR30:0075 Start Read privilege mode of ISR
   ; TR:SASR30:0322 Start Read privilege mode of ISR
   ; TR:SASR30:0324 Start Read privilege mode of ISR
   ; TR:SASR30:0338 Start Read privilege mode of ISR
   ldr      r6, oscnfISRTrusted      ; r6 = &osConfigBlock.uiStartAddressISRTrusted
   ldr      r6, [r6]                 ; r6 = &osConfigBlock.uiStartAddressISRTrusted
   ldrb     r6, [r6, +r3]            ; r6 = ISRTrusted[ISRID]  (r6 = *(r6+3))
   ; TR:SASR30:0338 End 
   ; TR:SASR30:0324 End 
   ; TR:SASR30:0322 End  
   ; TR:SASR30:0075 End
   ; TR:SASR30:0022 End 

   ; TR:SPMF89:01.0007 Start
   ldr      r7, [r4, #-444]          ; r7 = *(0xFFFFFE44)     read ISR mask 1
   ldr      r8, [r4, #-440]          ; r8 = *(0xFFFFFE48)     read ISR mask 2
   ; Disable priorities same and lower in mask 1
   mov      r12, r1                  ; r12 = r1  (reqMask)
   sub      r12, r4, r12             ; r12 = r4-r12
   str      r12, [r4, #-444]         ; *(0xFFFFFE44) = r12;
   mvn      r5, r12                  ; r5 = ~r12
   and      r5, r5, r7               ; r5 = r5 & r7
   ; Disable lower priorities in mask 2
   sub      r12, r4, #1              ; r12 = r4-1 = 0xffffffff
   str      r12, [r4, #-440]         ; *(0xFFFFFE48) = r12 = 0xffffffff
disLoop1:
   ; wait until writing is finished
   ldr      r12, [r4, #-440]         ; r12 = *(0xFFFFFE48)
   cmp      r12, #0x0                ; r12 == 0?
   bne      disLoop1                 ; if (*(0xFFFFFE48) != 0) goto disLoop1
   ldr      r12, [r4, #-444]         ; r12 = *(0xFFFFFE44)
   cmp      r12, r5                  ; r12 == r5?
   bne      disLoop1                 ; if (*(0xFFFFFE44) != r5) goto disLoop1
   cpsie    i                        ; CPSR.I = 0,  enable IRQ  TR:SPMF48:0002
   ; TR:SPMF89:01.0007 End

   ; TR:SASR30:0022 Start 
   ; TR:SASR30:0075 Start
   ; TR:SASR30:0322 Start 
   ; TR:SASR30:0324 Start
   cmp      r6, #1                   ; r6 == 1?   (r6 == 1 if ISR is trusted)
   beq      osISRTrst1               ; if (r6 == 1) goto osISRTrst1
   ; call non-trusted ISR handler
   cps      #0x10                    ; CPSR.M = user mode, switch to user mode
   mov      lr,pc                    ; LR = PC
   bx       r0                       ; call (R0)  (= address of ISR handler)
   swi      #0x83                    ; TRAP(0x83), switch to system mode
   b        osISRAfterCall1          ; goto osISRAfterCall1
osISRTrst1
   ; call trusted ISR handler
   ; Step 12 of design INT Cat2 entry (if ISR of mask 1)
   mov      lr,pc                    ; LR = PC
   bx       r0                       ; call (R0)  (= address of ISR handler)
   ; TR:SASR30:0324 End 
   ; TR:SASR30:0322 End 
   ; TR:SASR30:0075 End 
   ; TR:SASR30:0022 End 

osISRAfterCall1   
   cpsid  i                          ; CPSR.I = 1,  disable IRQ interrupt
   ; TR:SPMF89:01.0008 Start
   str      r8, [r4, #-456]   ; *FFFFFE38 = r8,  restore ISR mask 2
   str      r7, [r4, #-460]   ; *FFFFFE34 = r9,  restore ISR mask 1
   ; TR:SPMF89:01.0008 End
   ldmfd    sp!, {r4, r5, r6, r7, r8, lr}   ; pop r4, r5, r6, r7, r8, lr
   b osLeaveISR                                 ; goto osLeaveISR
 
osReqMask_2
; reqMask == 2
   stmfd    sp!, {r4, r5, r6, r7, lr}   ; push r4, r5, r6, r7, lr
   mov      r0, r12                             ; r0 = r12 (= ISR handler to call) 
   mov      r4, #0                              ; r4 = 0

   ldr      r6, oscnfISRTrusted      ; r6 = &osConfigBlock.uiStartAddressISRTrusted
   ldr      r6, [r6]                 ; r6 = &osConfigBlock.uiStartAddressISRTrusted
   ldrb     r6, [r6, +r3]            ; r6 = ISRTrusted[ISRID]  (r6 = *(r6+3))

   ; TR:SPMF89:01.0007 Start
   ldr      r7, [r4, #-440]          ; r7 = *(0xFFFFFE48)     read ISR mask 2
   ; Disable priorities same and lower in mask 2
   mov      r12, r1                  ; r12 = r1  (reqMask)
   sub      r12, r4, r12             ; r12 = r4-r12
   str      r12, [r4, #-440]         ; *(0xFFFFFE48) = r12;
   mvn      r5, r12                  ; r5 = ~r12
   and      r5, r5, r7               ; r5 = r5 & r7
disLoop2:
   ; wait until writing is finished
   ldr      r12, [r4, #-440]         ; r12 = *(0xFFFFFE48)
   cmp      r12, r5                  ; r12 == r5?
   bne      disLoop2                 ; if (*(0xFFFFFE44) != r5) goto disLoop2
   cpsie    i                        ; CPSR.I = 0,  enable IRQ  TR:SPMF48:0002
   ; TR:SPMF89:01.0007 End
   cmp      r6, #1                   ; r6 == 1?   (r6 == 1 if ISR is trusted)
   beq      osISRTrst2               ; if (r6 == 1) goto osISRTrst2
   ; call non-trusted ISR handler
   cps      #0x10                    ; CPSR.M = user mode, switch to user mode
   mov      lr,pc                    ; LR = PC
   bx       r0                       ; call (R0)  (= address of ISR handler)
   swi      #0x83                    ; TRAP(0x83), switch to system mode
   b        osISRAfterCall2          ; goto osISRAfterCall2
osISRTrst2
   ; call trusted ISR handler
   ; Step 12 of design INT Cat2 entry (if ISR of mask 2)
   mov      lr,pc                    ; LR = PC
   bx       r0                       ; call (R0)  (= address of ISR handler)

osISRAfterCall2   
   cpsid  i                          ; CPSR.I = 1,  disable IRQ interrupt
   ; TR:SPMF89:01.0008 Start
   str      r7, [r4, #-456]   ; *FFFFFE38 = r7,  restore ISR mask 2
   ; TR:SPMF89:01.0008 End
   ldmfd    sp!, {r4, r5, r6, r7, lr}   ; pop r4, r5, r6, r7, lr 

osLeaveISR
   ; TR:SPMF89:01.0032 Start
   ; TR:SPMF89:0025 Start
   ; TR:SASR30:0025 Start
   ; TR:SPMF89:0030 Start
   ; Step 1 of design INT Cat2 exit
   ldr    r0, osRef_osaIntNestingDepth   ; r0 = &osaIntNestingDepth
   ldrb   r1,[r0]                        ; r1 = osaIntNestingDepth
   sub  r1, r1, #1                       ; r1 = osaIntNestingDepth-1;
   ldr  r0, oscnfISRStackStart           ; r0 = &osConfigBlock.uiStartAddressISRStackStart
   ldr  r0,[r0]                          ; r0 = osConfigBlock.uiStartAddressISRStackStart
   ldr  r0,[r0, +r1, lsl #2]             ; r0 = ISRStackStart[osaIntNestingDepth-1] (r0 = *(r0 + (r1 << 2)))
   ldr  r1,[r0]                          ; r1 = <bottom word of IRQHdStack>
   ldr  r2, osRef_AAAAAAAA;              ; r2 = 0xAAAAAAAA
   cmp  r1, r2                           ; <bottom word> != 0xAAAAAAAA ?
   ldrne  r0, osRef_osdErrYOIntHdlStackOverflow   ; if <bottom word> != 0xAAAAAAAA r0 = osdErrYOIntHdlStackOverflow 
   blne   osSystemStackOverflow                   ; if <bottom word> != 0xAAAAAAAA call osSystemStackOverflow(osdErrYOIntHdlStackOverflow)
   ; TR:SPMF89:01.0032 End
   ; TR:SPMF89:0025 End
   ; TR:SASR30:0025 End
   ; TR:SPMF89:0030 End

   cpsid  i                              ; CPSR.I = 1   disable IRQ interrupt

   ; Step 2 of design INT Cat2 exit
   ldmfd  sp!,{r5-r11}                   ; pop r5-r11
   bl osLeaveProtectedISR                ; call osLeaveProtectedISR()

   ; TR:SASR30:0108 Start
   ; TR:SASR30:0109 Start
   ; restore active ISR ID
   ldr    r0, [sp], #+4                  ; pop r0  (saved ISR ID)        
   ldr    r1, osRef_osaActiveISRID       ; r1 = &osaActiveISRID
   strh   r0, [r1]                       ; osaActiveISRID = r0   (*r1 = r0)
   ; TR:SASR30:0109 End
   ; TR:SASR30:0108 End

   ldr    r0, [sp], #+4                      ; pop r0  (saved ISR ID)
   ldr    r1, osRef_osORTICurrentServiceId   ; r1 = &osORTICurrentServiceId; 
   strb   r0, [r1]                           ; osORTICurrentServiceId = r0   (*r1 = r0)


   ; Step 3 of design INT Cat2 exit
   ; decrement osaIntNestingDepth
   ldr    r0, osRef_osaIntNestingDepth       ; r0 = &osaIntNestingDepth
   ldrb   r1,[r0]                            ; r1 = osaIntNestingDepth   (r1 = *r0)
   subs   r1,r1,#1                           ; r1 = r1 - 1 (and set Z flag if first interrupt nesting level)
   strb   r1,[r0]                            ; osaIntNestingDepth = r1  (*r0 = r1) 

   ; Step 4 of design INT Cat2 exit
   ; TR:SPMF89:0004 Start
   ldmfd  sp!,{r0-r1}                        ; pop r0, r1
   fmxr FPSCR, r0                            ; FPSCR = r0
   fmxr FPEXC, r1                            ; FPEXC = r1
   fldmiad sp!,{d0-d15}                      ; pop d0-d15
   ldr    lr, [sp], #+4                      ; pop LR

   ldr  r0, [sp], #+4                        ; pop r0  (get saved IRQ sp)
   ldr  sp, [sp]                             ; pop SP
   ; TR:SPMF89:0004 End

   ; switch to irq mode
   cps    #0x12                              ; CPSR.M = 0x12, switch to IRQ mode

   ; Step 5 of design INT Cat2 exit
   mov  sp, r0                               ; SPirq = r0
   ; decrement osLockDispatcher  TR:SOSK22:0004 Start
   ldr    r0, osRef_osLockDispatcher         ; r0 = &osLockDispatcher
   ldrb   r1,[r0]                            ; r1 = osLockDispatcher  (r1 = *r0)
   subs   r1,r1,#1                           ; r1 = r1-1
   strb   r1,[r0]                            ; osLockDispatcher = r0   (*r0 = r1)
   ;  TR:SOSK22:0004 End
   
   ; return from IRQ if dispatcher locked
   bne    LeaveISR_normal                    ; if Z flag not set goto LeaveISR_normal
   ldr    r0, osRef_osStartDispatcher        ; r0 = &osStartDispatcher
   ldrb   r1,[r0]                            ; r1 = osStartDispatcher
   teq    r1,#0                              ; osStartDispatcher == 0 ?
   ; return from IRQ if dispatcher not started
   beq    LeaveISR_normal                    ; if (osStartDispatcher == 0) goto LeaveISR_normal 

   ; jump to dispatcher
   ldmfd  sp!,{r0,r2,r3,r4,ip}               ; pop r0,r2,r3,r4,ip        TR:SASR30:0037 
   mov    r1, sp                             ; r1 = SP
   add    sp,sp, #12                         ; SP = SP + 12   adjust SPirq

   ; switch to SVC mode
   cps    #0x13                   ; CPSR.M = 0x13, switch to supervisor mode
   ; Restore SPSR
   msr    SPSR_cxsf, r0           ; SPSR = r0    TR:SASR30:0037 

   ldmfd  r1,{r0, r1, lr}         ; pop r0,r1,lr (from IRQ stack)
   sub    lr, lr,#4               ; LR = LR-4  (convert LRirq to LRsvc)
   stmfd  sp!,{r0, r1, r5}        ; push r0,r1,r5   (on SVC stack, prepare for dispatcher call)

   ldr    r0, osRef_osDispatcher  ; r0 = osDispatcher
   mov    pc,r0                   ; PC = r0  call osDispatcher()


LeaveISR_normal
   ; normal return from IRQ
   ldr    r0, [sp], #+4           ; pop r0  (saved SPSRirq)
   msr    SPSR_cxsf, r0           ; SPSR = r0

   ldmfd  sp!,{r2,r3,r4,ip}       ; pop r2,r3,r4,ip
   ldmfd  sp!,{r0,r1,lr}          ; pop r0,r1,lr
   subs   pc,lr,#4                ; PC = LR-4, CPSR = SPSR   (return from IRQ)
   ; TR:SPMF89:01.0035 End
   ; TR:SPMF89:01.0094 End

   
; Stack frame:
;
;    r0
;    r1
;    r5                          
;    SPSR(svc) = CPSR of task
;    LR(svc) = PC of task
;    FPSCR                      
;    FPEXC                      
;    d0..d15                    
;    r2
;    r3
;    r4
;    r6                         
;    r7
;    r8
;    r9
;    r10
;    r11
;    r12
;    LR(sys) = LR of task


; TR:SOSK22:0007 Start
; TR:SOSK22:0035 Start
; TR:SOSK22:0028 Start
;-+--------------------------------------------------------------------------
; osDispatcher                                                               
; Funktion: osDispatcher                                                       
;   - saves old task kontext
;   - switches to new task
;   - contains IDLE-Loop                                                     
; Parameter:                                                                 
; Returnvalue:                                                               
;----------------------------------------------------------------------------

osDirectSWIDispatcher    ; called directly by SWI vector
 ; save some scratch registers
  stmfd  sp!,{r0, r1, r5}

 ; TR:SOSK22:0032 Start
 ; TR:SOSK22:0033 Start

osDispatcher
  ; load osaActiveTaskIndex into r5
  ldr    r1, osRef_osaActiveTaskIndex   ; r1 = &osaActiveTaskIndex        
  ldrh   r5, [r1]                       ; r5 = osaActiveTaskIndex

  mov    r0, #0x10000                   ; r0 = 0x10000osdNoActiveTask
  sub    r0,r0,#1                       ; r0 = r0-1 = 0xFFFF = osdNoActiveTask
  cmp    r5, r0                         ; osaActiveTaskIndex == osdNoActiveTask ?

  ; check task stack
  bne    osDispNoCheck                  ; if (osaActiveTaskIndex != osdNoActiveTask) goto osDispNoCheck, 
                                        ; stack will be checked later (using osaActiveTaskIndex)

  ; no saving old context => restore SP (discard already saved scratch registers r0, r1, r5)
  add    sp,sp,#12                      ; SP = SP + 12

  ; TR:SPMF89:01.0030 Start
  ; TR:SPMF89:0015 Start
  ; TR:SPMF89:0017 Start
  ; TR:SPMF89:0024 Start
  ; TR:SASR30:0025 Start
  ; TR:SASR30:0314 Start Task stack check of last active task in dispatcher 
  ; stack check using osLastActiveTaskIndex  TR:SPMF07:0005 Start
  ldr    r2, oscnfTcbStackBottom          ; r2 = &osConfigBlock.uiStartAddressStackStart
  ldr    r2,[r2]                          ; r2 = osConfigBlock.uiStartAddressStackStart
  ldr    r3, osRef_osLastActiveTaskIndex  ; r3 = &osLastActiveTaskIndex         
  ldrh   r4,[r3]                          ; r4 = osLastActiveTaskIndex
  ldr    r3,[r2, +r4, lsl #2]             ; r3 = osConfigBlock.uiStartAddressStackStart[osLastActiveTaskIndex] (= *(r2+(r4<<2)))
  ldr    r2, [r3]                         ; r2 = *(osConfigBlock.uiStartAddressStackStart[osLastActiveTaskIndex]) = stack bottom word
  ldr    r3, osRef_AAAAAAAA;              ; r3 = 0xAAAAAAAA
  cmp    r2, r3                           ; r2 == r3 ? (check for empty stack pattern)
  beq    osNextTask                       ; if (stack botom word == 0xAAAAAAAA) goto osNextTask

  ; stack overflow detected
  ldr    r2, osRef_osStackOverflow        ; r12 = &osStackOverflow
  mov    lr, pc                           ; LR = PC
  bx     r2                               ; call osStackOverflow()
  ; TR:SPMF89:01.0030 End
  ; TR:SPMF89:0015 End
  ; TR:SPMF89:0017 End
  ; TR:SPMF89:0024 End
  ; TR:SPMF07:0005 End
  ; TR:SASR30:0314 End
  ; TR:SASR30:0025 End
  
osDispNoCheck
  ; reached if (osaActiveTaskIndex != osdNoActiveTask) => context must be saved
  cps    #osSysMode                       ; CPSR.M = system mode, switch to system mode

  ; save old task context (on task stack!)
  ; TR:SPMF89:01.0002 Start   
  stmfd  sp!,{r2-r4,r6-r12,lr}            ; push r2-r4,r6-r12,lr

  ; TR:SPMF89:01.0089 Start
  fstmdbd sp!,{d0-d15}                    ; push d0-d15
  fmrx r7, FPSCR                          ; r7 = FPSCR
  fmrx r8, FPEXC                          ; r8 = FPEXC
  stmfd  sp!,{r7-r8}                      ; push r7-r8 (= FPSCR, FPEXC)
  ; TR:SPMF89:01.0089 End
 
  mov    r7,sp                            ; r7 = SPsys

  ; switch back to SVC mode
  cps    #osSVCMode                       ; CPSR.M = SVC mode, switch to supervisor mode

  mrs    r11, SPSR                        ; r11 = SPSR
  ldmfd  sp!,{r8, r9, r10}                ; pop previous values of r0, r1, r5 from SVC stack into r8, r9, r10
  stmfd  r7!,{r8-r11, lr}                 ; push previousvalues of r0, r1, r5 on task stack
  ; TR:SPMF89:01.0002 End

  ; save stack pointer of system/user mode
  ldr    r8, osRef_osaTcbSP                ; r8 = &osaTcbSP
  str    r7,[r8, +r5, lsl #2]              ; osaTcbSP[osaActiveTaskIndex] = SP (task)

 
  ; store CurrentService into tcb
  ldr    r3,osRef_osORTICurrentServiceId   ; r3 = &osORTICurrentServiceId
  ldr    r2,osRef_osTcbORTIServiceId       ; r2 = &osTcbORTIServiceId
  ldrb   r3,[r3]                           ; r3 = osORTICurrentServiceId 
  strb   r3,[r2, +r5]                      ; osTcbORTIServiceId[osaActiveTaskIndex] = r3 = osORTICurrentServiceId
  
  stmfd  sp!,{r0-r3,ip}                    ; push r0-r3,ip (non-permanent registers)
  bl     osSaveTaskMPUSettings             ; call osSaveTaskMPUSettings()
  ldmfd  sp!,{r0-r3,ip}                    ; pop r0-r3,ip (non-permanent registers)
  
  ; mark context valid
  ; TR:SPMF89:0011 Start
  ldr    r2, osRef_osaTcbValid             ; r2 = &osaTcbValid
  mov    r3, #1                            ; r3 = 1
  strb   r3,[r2, +r5]                      ; osaTcbValid[osaActiveTaskIndex] = 1   (*(r2+r5 = r3)
  ; TR:SPMF89:0011 End
    
  ; old task state == RUNNING ?
  ldr    r2, osRef_osTcbTaskState          ; r2 = &osTcbTaskState
  ldrb   r3,[r2, +r5]                      ; r3 = osTcbTaskState[osaActiveTaskIndex]
  cmp    r3,#RUNNING                       ; (osTcbTaskState[osaActiveTaskIndex] == RUNNING) ?

  moveq    r3,#READY                       ; if (osTcbTaskState[osaActiveTaskIndex] == RUNNING) r3 = READY
  streqb   r3,[r2, +r5]                    ; if (osTcbTaskState[osaActiveTaskIndex] == RUNNING) osTcbTaskState[osaActiveTaskIndex] = r3 = READY     ; TR:SOSK22:0044
  
osL01:
  ; TR:SPMF89:01.0030 Start
  ; TR:SPMF89:0014 Start
  ; TR:SPMF89:0017 Start
  ; TR:SPMF89:0024 Start
  ; TR:SASR30:0025 Start
  ; TR:SASR30:0314 Start Task stack check on stack switch
  ; check task stack   TR:SPMF07:0005 Start
  ldr    r2, oscnfTcbStackBottom           ; r2 = &osConfigBlock.uiStartAddressStackStart
  ldr    r2,[r2]                           ; r2 = osConfigBlock.uiStartAddressStackStart
  ldr    r3,[r2, +r5, lsl #2]              ; r3 = osConfigBlock.uiStartAddressStackStart[osaActiveTaskIndex] (= *(r2+(r5<<2)))
  ldr    r2, [r3]                          ; r2 = *(osConfigBlock.uiStartAddressStackStart[osaActiveTaskIndex]) = stack bottom word
  ldr    r3, osRef_AAAAAAAA                ; r3 = 0xAAAAAAAA
  cmp    r2, r3                            ; r2 == r3 ? (check for empty stack pattern)
  beq    osNextTask                        ; if (stack botom word == 0xAAAAAAAA) goto osNextTask

  ldr    r2, osRef_osStackOverflow         ; r2 = &osStackOverflow
  mov    lr, pc                            ; LR = PC
  bx     r2                                ; call osStackOverflow()
  ; TR:SPMF89:01.0030 End
  ; TR:SPMF89:0014 End
  ; TR:SPMF89:0017 End
  ; TR:SPMF89:0024 End
  ; TR:SPMF07:0005 End
  ; TR:SASR30:0314 End
  ; TR:SASR30:0025 End

osNextTask   ; start next task
  ; osaActiveTaskIndex = osHighReadyTaskIndex
  ldr    r9, osRef_osHighReadyTaskIndex        ; r9 = &osHighReadyTaskIndex      
  ldrh   r5,[r9]                               ; r5 = osHighReadyTaskIndex
  strh   r5,[r1]                               ; osaActiveTaskIndex = osHighReadyTaskIndex

  ; osActiveTaskPrio = osHighReadyTaskPrio
  ldr    r11, osRef_osHighReadyTaskPrio        ; r11 = osHighReadyTaskPrio    
  ldrh   r6,[r11]                              ; r6 = osHighReadyTaskPrio
  ldr    r10, osRef_osActiveTaskPrio           ; r10 = $osActiveTaskPrio
  strh   r6,[r10]                              ; osActiveTaskPrio = osHighReadyTaskPrio

  cmp    r5, r0                            ;  r5 = (new)osaActiveTaskIndex == OS_NO_ACTIVE_TASK ?
  beq    IdleLoop                          ; if (osaActiveTaskIndex == OS_NO_ACTIVE_TASK) goto IdleLoop

  ; range check for new task index
  ; TR:SPMF89:0008 Start
  ldr    r11, oscnfNumberOfTasks               ; r11 = &osConfigBlock.uiNumberOfTasks
  ldrh   r11,[r11]                             ; r11 = osConfigBlock.uiNumberOfTasks  (r11 = *r11)
  cmp    r11, r5                               ; r11 > r5?
  ldrle  r0, osRef_osdErrDPWrongHighReadyTaskIndex    ; if (osHighReadyTaskIndex >= osConfigBlock.uiNumberOfTasks) r0 = osdErrDPWrongHighReadyTaskIndex
  ble    osAsmAssertFailed                     ; if (osHighReadyTaskIndex >= osConfigBlock.uiNumberOfTasks)  osAsmAssertFailed(osdErrDPWrongHighReadyTaskIndex)   (never returns)
  ; TR:SPMF89:0008 End
  
  ; switch to next task

  ; osCurrentContext = osdCtxTask;
  ldr    r11, osRef_osCurrentContext         ; r11 = &osCurrentContext                       
  mov    r10,#CTX_TASK                       ; r10 = CTX_TASK
  strh   r10,[r11]                           ; osCurrentContext = CTX_TASK ((*r11) = r10)

  ; osaActiveApplicationID = oskTaskToAppl[osaActiveTaskIndex];
  ldr    r9, oscnfTaskToAppl                 ; r9 = &osConfigBlock.uiStartAddressTaskToAppl
  ldr    r9,[r9]                             ; r9 = osConfigBlock.uiStartAddressTaskToAppl
  ldrb   r10,[r9, +r5]                       ; r10 = TaskToAppl[osaActiveTaskIndex] = *(r9 + r5)
  ldr    r11, osRef_osaActiveApplicationID    ; r11 = &osaActiveApplicationID                    
  strb   r10,[r11]                           ; osaActiveApplicationID = r10 (*r11 = r10)
  
  ;       if task isnt trusted
  ldr    r9, oscnfTcbIsTrusted               ; r9 = &osConfigBlock.uiStartAddressTaskTrusted
  ldr    r9,[r9]                             ; r9 = osConfigBlock.uiStartAddressTaskTrusted
  ldrb   r10,[r9, +r5]                       ; r10 = TaskTrusted[osaActiveTaskIndex] (r10 = *(r9+r5))

  cmp    r10,#0                              ; r10 == 0  (== non-trusted) ?
  bne    osAfterMPUSetting                   ; if (r10 != 0) goto osAfterMPUSetting  (task is trusted, no MPU setting necessary)
  stmfd  sp!,{r0-r3,r8,r9,ip}                ; push r0-r3,r8,r9,ip
  bl     osSetMPUForTask                     ; call osSetMPUForTask()
  ldmfd  sp!,{r0-r3,r8,r9,ip}                ; pop r0-r3,r8,r9,ip
osAfterMPUSetting

  ; TR:SOSK22:0048 Start 
  ; lock dispatcher for nonpreemptive tasks, unlock for preemptive tasks
  ; if oskTaskPreemption[osaActiveTaskIndex] = 1 then osLockDispatcher = 0 else osLockDispatcher = 1
  ldr    r9, oscnfTcbTaskPreemption          ; r9 = &osConfigBlock.uiStartAddressTaskPreemptive
  ldr    r9,[r9]                             ; r9 = osConfigBlock.uiStartAddressTaskPreemptive
  ldrb   r10,[r9, +r5]                       ; r10 = TaskPreemptive[osaActiveTaskIndex] (r10 = *(r9+r5))
  eor    r10,r10,#1                          ; r10 = r10^1   if (r10 == 1) r10 = 0 else r10 = 1
  ldr    r11, osRef_osLockDispatcher         ; r11 = &osLockDispatcher  
  strb   r10,[r11]                           ; osLockDispatcher = r10  (*r11 = r10)
  ; TR:SOSK22:0048 End
  
  ; get state of new task
  ; note: r2 is not valid if previous task was terminated!
  ldr    r2, osRef_osTcbTaskState            ; r2 = &osTcbTaskState
  ldrb   r3,[r2, +r5]                        ; r3 = osTcbTaskState[osaActiveTaskIndex]  (r3 = *(r2+r5))

  cmp    r3,#PRE_READY                       ; osTcbTaskState[osaActiveTaskIndex] == PRE_READY ?
  bne    RestoreContext                      ; if (osTcbTaskState[osaActiveTaskIndex] != PRE_READY) goto RestoreContext

  ; task is running for the first time: create new stack frame
  
  ldr    r9, osRef_osaTcbValid               ; r9 = &osaTcbValid
  ldrb   r3,[r9, +r5]                        ; r3 = osaTcbValid[osaActiveTaskIndex]  (r3 = *(r9+r5))
  cmp    r3,#0                               ; osaTcbValid[osaActiveTaskIndex] == 0 ?
  ldrne  r0, osRef_osdErrDPStartValidContext ; if (osaTcbValid[osaActiveTaskIndex] != 0) r0 = osdErrDPStartValidContext
  bne    osAsmAssertFailed                   ; if (osaTcbValid[osaActiveTaskIndex] != 0)  osAsmAssertFailed(osdErrDPStartValidContext)   (never returns)
  
  ; osORTICurrentServiceId=osdORTINoService; 
  ldr    r9, osRef_osORTICurrentServiceId    ; r9 = &osORTICurrentServiceId
  mov    r3, #osdORTINoService               ; r3 = osdORTINoService
  strb   r3,[r9]                             ; osORTICurrentServiceId=osdORTINoService  (*r9 = r3)

  ; set task state to running
  mov    r3,#RUNNING                         ; r3 = RUNNING
  strb   r3,[r2, +r5]                        ; osTcbTaskState[osaActiveTaskIndex] = RUNNING  (*(r2+r5) = r3) TR:SOSK22:0036 TR:SOSK22:0041

  ; reset osStartDispatcher
  ldr    r9, osRef_osStartDispatcher         ; r9 = &osStartDispatcher
  mov    r3, #0                              ; r3 = 0
  strb   r3, [r9]                            ; osStartDispatcher = 0  (*r9 = r3)

  ; TR:SPMF89:01.0001 Start   
  ; get task start address
  ldr    r11, oscnfTcbTaskStartAddress       ; r11 = &osConfigBlock.uiStartAddressTaskStart
  ldr    r11,[r11]                           ; r11 = osConfigBlock.uiStartAddressTaskStart
  ldr    r9,[r11, +r5, lsl #2]               ; r9 = TcbTaskStartAddress[osaActiveTaskIndex]   (r9 = *(r11 + (r5 << 2)))   TR:SOSK22:0046

  ; switch to system mode (for stack access)
  cps    #osSysMode                          ; CPSR.M = system mode, switch to system mode

  ldr    r10, oscnfTcbStackTop               ; r10 = &osConfigBlock.uiStartAddressStackEnd
  ldr    r10,[r10]                           ; r10 = osConfigBlock.uiStartAddressStackEnd
  ldr    sp,[r10, +r5, lsl #2]               ; (new task) SP = TcbStackTop[osaActiveTaskIndex]  (SP = *(r10 + (r5 << 2)))

  ; set lr to error handler
  ldr    lr, osRef_osMissingTerminateError   ; LR = &osMissingTerminateError

  ; switch back to SVC mode
  cps    #osSVCMode                          ; CPSR.M = SVC mode, switch to supervisor mode

  ; TR:SOSK22:0003 Start  
  ; TR:SOSK22:0005 Start  
  ; TR:SASR30:0022 Start 
  ; TR:SASR30:0075 Start
  ; TR:SASR30:0322 Start 
  ; TR:SASR30:0324 Start 
  ; init status register for new task
  ;    IRQ   : enabled
  ;    FIQ   : unchanged
  ;    Thumb : enabled for Thumb-Mode, else disabled
  ;    Mode  : system or user mode (depending on task mode support)

  mrs    r4, SPSR                            ; r4 = SPSR
  and    r4, r4, #01010000b                  ; r4 = r4 & 0xA0  (clear IRQ flag, keep current FIQ flag, set mode flags to user mode, clear Thumb flag)

  ldr    r11, oscnfTcbIsTrusted              ; r11 = &osConfigBlock.uiStartAddressTaskTrusted
  ldr    r11,[r11]                           ; r11 = osConfigBlock.uiStartAddressTaskTrusted
  ldrb   r1,[r11, +r5]                       ; r1 = TaskTrusted[osaActiveTaskIndex]  (r1 = *(r11+r5))
  cmp    r1,#1                               ; r1 == 1 ?  (is task trusted ?)
  orreq  r4, r4, #00011111b                  ; if (r1 == 1) r4 = r4 | 0x1F    (set mode bits to system mode)
  ; TR:SASR30:0324 End 
  ; TR:SASR30:0322 End  
  ; TR:SASR30:0075 End
  ; TR:SASR30:0022 End 
  
  tst    r9,#1                               ; r9 == 1 ?   is task start address thumb code?   
;  .if (osdThumbMode == 1)
   orrne    r4, r4, #00110000b               ; if (r9 != 1) r4 = r4 | 0x30 (set thumb bit, start in thumb mode)
;  .else
   orreq    r4, r4, #00010000b               ; if (r9 != 1) r4 = r4 | 0x10 (keep (cleared) thumb bit, start in ARM mode)
;  .endif

  orr    r4,r4, #0x300                       ; r4 = r4 & 0x300  (set E and A flags)
  msr    SPSR_cxsf, r4                       ; SPSR = r4    TR:SASR30:0322 TR:SASR30:0324 TR:SASR30:0075 TR:SASR30:0022 
  ; TR:SOSK22:0003 End  
  ; TR:SOSK22:0005 End
  ; TR:SPMF89:01.0001 End   
  
  movs   pc, r9                              ; PC = r9, CPSR = SPSR  (jump to new task)


RestoreContext
  ; task was running before: restore old task context
  ldr    r2, osRef_osaTcbValid               ; r2 = &osaTcbValid
  ldrb   r3,[r2, +r5]                        ; r3 = osaTcbValid[osaActiveTaskIndex]  (r3 = *(r2+r5))
  cmp    r3,#1                               ; osaTcbValid[osaActiveTaskIndex] == 1 ?
  ldrne  r0, osRef_osdErrDPResumeInvalidContext ; if (osaTcbValid[osaActiveTaskIndex] != 1) r0 = osdErrDPResumeInvalidContext
  bne    osAsmAssertFailed                   ; if (osaTcbValid[osaActiveTaskIndex] != 1)  osAsmAssertFailed(osdErrDPResumeInvalidContext)   (never returns)
  mov    r3,#0                               ; r3 = 0
  strb   r3,[r2, +r5]                        ; osaTcbValid[osaActiveTaskIndex] = 0  (*(r2+r5) = r3)
  
  bl osRestoreTaskMPUSettings                ; call osRestoreTaskMPUSettings() 

   ; restore tcb into CurrentService
  ldr    r2,osRef_osTcbORTIServiceId         ; r2 = &osTcbORTIServiceId
  ldr    r3,osRef_osORTICurrentServiceId     ; r3 = &osORTICurrentServiceId
  ldrb   r2,[r2, +r5]                        ; r2 = osTcbORTIServiceId[osaActiveTaskIndex]   (r2 = *(r2+r5))
  strb   r2,[r3]                             ; osORTICurrentServiceId = r2 = osTcbORTIServiceId[osaActiveTaskIndex]  (*r3 = r2)

  ; restore stack pointer
  ldr    r8, osRef_osaTcbSP                  ;  r8 = &osaTcbSP                 
  ldr    r7,[r8, +r5, lsl #2]                ; r7 = osaTcbSP[osaActiveTaskIndex]   (r7 = *(r8 + (r5 << 2)))

  ; set task state to RUNNING
  ldr    r2, osRef_osTcbTaskState            ; r2 = &osTcbTaskState
  mov    r3,#RUNNING                         ; r3 = RUNNING
  strb   r3,[r2, +r5]                        ; osTcbTaskState[osaActiveTaskIndex] = RUNNING  (*(r2+r5) = r3) ; TR:SOSK22:0036 

  ; reset osStartDispatcher
  ldr    r9, osRef_osStartDispatcher         ; r9 = &osStartDispatcher
  mov    r3, #0                              ; r3 = 0;
  strb   r3, [r9]                            ; osStartDispatcher = 0   (*r9 = r3)

  ; restore task context

  ldmfd  r7!,{r0, r1, r5, r8, lr}            ; pop r0, r1, r5, r8, lr (use r7 as stack pointer)

  msr    SPSR_cxsf, r8                       ; SPSR = r8
  
  ; switch to system mode

  cps    #osSysMode                          ; CPSR.M = system mode, switch to system mode

  mov    sp, r7                              ; SP = r7   set task SP 

  ; TR:SPMF89:01.0089 Start
  ldmfd  sp!,{r7-r8}                         ; pop r7-r8
  fmxr FPSCR, r7                             ; FPSCR = r7
  fmxr FPEXC, r8                             ; FPEXC = r8
  fldmiad sp!,{d0-d15}                       ; pop d0-d15
  ; TR:SPMF89:01.0089 End
 
  ; restore remaining registers
  ldmfd  sp!,{r2-r4,r6-r12,lr}               ; pop r2-r4,r6-r12,lr

  ; switch back to SVC mode
  cps    #osSVCMode                          ; CPSR.M = SVC mode, switch to supervisor mode

  movs   pc,lr                               ; PC = LR   return from dispatcher to task
  ; TR:SOSK22:0031 Start 
IdleLoop
  ; called if no task is READY
 
  ; osaActiveApplicationID = INVALID_OSAPPLICATION;
  ; TR:SASR30:0107 Start
  mov    r9,#0xff                           ; r9 = 0xff = INVALID_OSAPPLICATION
  ldr    r8, osRef_osaActiveApplicationID   ; r8 = &osaActiveApplicationID                       
  strb   r9,[r8]                            ; osaActiveApplicationID = 0xFF   (*r8 = r9)
  ; TR:SASR30:0107 End

  ; unlock dispatcher
  mov    r9, #0                             ; r9 = 0
  ldr    r8, osRef_osLockDispatcher         ; r8 = &osLockDispatcher
  strb   r9,[r8]                            ; osLockDispatcher = 0

  cpsie  i                                  ; CPSR.I = 0, enable IRQ interrupts         

InnerIdleLoop

  ; poll osStartDispatcher
  ldr    r8, osRef_osStartDispatcher        ; r8 = &osStartDispatcher
  ldrb   r9, [r8]                           ; r9 = osStartDispatcher
  cmp    r9, #0                             ; osStartDispatcher == 0 ? 
  ; if osStartDispatcher == TRUE activate delayed interrupt
  beq    l_nodelayedint                     ; if (osStartDispatcher == 0) goto l_nodelayedint 
  swi    #0x81                              ; SWI (Trap) 0x81, start dispatcher
l_nodelayedint
  b InnerIdleLoop                           ; goto InnerIdleLoop    TR:SOSK22:0031 End ; TR:SOSK22:0035 End ; TR:SOSK22:0028 End ; TR:SOSK22:0007 End

 ; TR:SOSK22:0032 End
 ; TR:SOSK22:0033 End

 
 
 
; TR:SOSK22:0150 Start
; handlers for unhandled exceptions

osUndefInstruction:
  ldr    r0, osRef_osUnhandledException   ; r0 = &osUnhandledException
  mov    lr, pc                           ; LR = PC
  bx     r0                               ; call osUnhandledException()
; TR:SOSK22:0150 End  


; Trap handler for SWI
osSWI:
; TR:SPMF89:01.0092 Start
  stmfd  sp!,{r0, r1, r5}     ; push r0, r1, r5

 ; read SWI argument
  mrs    r1, SPSR             ; r1 = SPSR   read mode of caller
  tst    r1, #00100000b       ; r1 == 0x20 ?  test T bit
; .if (osdThumbMode == 1)
  ldrbne   r1,[lr, #-1]       ; (if T bit set) r1 = *(LR-1)   read argument from thumb mode
; .else
  ldrheq   r1,[lr, #-2]       ; (if T bit not set) r1 = *(LR-2)   read argument from ARM mode
; .endif
  sub    r0, r1, #128         ; r0 = r1 - 128
  cmp    r0, #128             ; r0 < 0x80 ?  
  bcs    osSWIL1              ; if (r0 < 0x80) goto osSWIL1 (call application SWI handler)

  cmp    r1, #0x81            ; r1 == 0x81? 
  bne    osSWIL2              ; if (r1 != 0x81)
  
  ; case 0x81, goto Dispatcher
  b      osDispatcher ; TR:SOSK22:0052 , TR:SOSK22:0053 , TR:SOSK22:0054 , TR:SOSK22:0055 , TR:SOSK22:0056 
                      ; TR:SOSK22:0057 ,
osSWIL2:   
  ; TR:SPMF89:01.0036 Start
  cmp    r1, #0x83            ; r1 == 0x83?
  bne    osSWIL3

  ; osuint32 osSwitchToPrivMode(void)  (switch to privileged mode)
  ldmfd  sp!,{r0, r1, r5}     ; pop r0, r1, r5   restore context and sp (remaining code uses non-permanent registers only)

  mrs    r1, SPSR             ; r1 = SPSR   read mode of caller
  and    r0, r1, #00011111b   ; r0 = r1 & 0x1F   mask mode bits
  cmp    r0, #00010000b       ; r0 == 0x10?   if mode bits != UserMode goto osSWIalreadyPriv
  bne    osSWIalreadyPriv     ; if (r0 != 0x10) goto osSWIalreadyPriv
  orr    r1, r1, #00011111b   ; r1 = r1 | 0x1f   set system mode
  mov    r0,#0                ; r0 = 0   return 0 (called from user mode)
  msr    SPSR_cxsf, r1        ; SPSR = r1    set SPSR (=mode after return from SWI) to system mode
  movs   pc, lr               ; PC = LR,  CPSR = SPSR     return from SWI and switch to system mode
osSWIalreadyPriv:             ; call was already from privileged mode, no mode switch
  mov    r0,#1                ; r0 = 1   return 1 (called from privileged mode)
  ; TR:SPMF89:01.0036 End
  ; TR:SPMF89:01.0037 Start
  movs   pc, lr               ; PC = LR,  CPSR = SPSR     return from SWI
  ; TR:SPMF89:01.0037 End
  
; TR:SASR30:0031 Start
osSWIL3:   ; peripheral access function
  sub    r5, r1, #0x84
  ; now r5 = peripheral function index
  cmp    r5, #8               ;  r5 = 8?      TR:SOSK22:0007 End
  bhi    osSWIL6              ; if r5 > 8 goto osSWIL6

  ldr    r0,[sp]             ; r0 = *SP    = areaID
  stmfd  sp!,{r6}            ; push r6  save scratch register
  
  ; TR:SPMF89:01.0051 Start
  ; TR:SPMF89:01.0055 Start
  ; TR:SPMF89:01.0059 Start
  ; TR:SPMF89:01.0062 Start
  ; TR:SPMF89:01.0064 Start
  ; TR:SPMF89:01.0066 Start
  ; TR:SPMF89:01.0068 Start
  ; TR:SPMF89:01.0070 Start
  ; TR:SPMF89:01.0072 Start
  ldr    r6,oscnfNumberOfPeripheralRegions   ; r6 = &osConfigBlock.uiNumberOfPeripheralRegions
  ldrh   r6,[r6]                             ; r6 = osConfigBlock.uiNumberOfPeripheralRegions
  cmp    r6,r0                               ; r0 >= r6?
  bls    osPeriphErrorDetected               ; if (r0 >= osConfigBlock.uiNumberOfPeripheralRegions) goto osPeriphErrorDetected
  
  ldr    r6,osRef_osaActiveApplicationID     ; r6 = &osaActiveApplicationID                        
  ldrb   r1,[r6]                             ; r1 = osaActiveApplicationID
  mov    r6, #1                              ; r6 = 1
  mov    r6, r6, lsl r1                      ; r6 = r6 << r1   (mask for application ID)
  
  ldr    r1, oscnfPeripheralRegionAccess     ; r1 = &osConfigBlock.uiStartAddressPeripheralRegionAccess
  ldr    r1,[r1]                             ; r1 = osConfigBlock.uiStartAddressPeripheralRegionAccess
  ldr    r1,[r1, +r0, lsl #2]                ; r1 = PeripheralRegionAccess[r0]   (r1 = *(r1 + (r0 << 2))
  
  ands   r6, r6, r1                          ; r6 = r6 & r1
  beq    osPeriphErrorDetected               ; if (r6 == 0) goto osPeriphErrorDetected

  ldr    r6, oscnfPeripheralRegionStart      ; r6 = &osConfigBlock.uiStartAddressPeripheralRegionStart
  ldr    r6,[r6]                             ; r6 = osConfigBlock.uiStartAddressPeripheralRegionStart
  ldr    r6,[r6, +r0, lsl #2]                ; r6 = PeripheralRegionStart[r0]   (r6 = *(r6 + (r0 << 2)))
  
  ldr    r1, oscnfPeripheralRegionEnd        ; r1 = &osConfigBlock.uiStartAddressPeripheralRegionEnd
  ldr    r1,[r1]                             ; r1 = osConfigBlock.uiStartAddressPeripheralRegionEnd
  ldr    r0,[r1, +r0, lsl #2]                ; r0 = PeripheralRegionStart[r0]   (r0 = *(r1 + (r0 << 2)))
  
  ldr    r1,[sp, #8]                         ; r1 = *(SP+8)
  cmp    r6,r1                               ; (r1 == r6) ?
  bhi    osPeriphErrorDetected               ; (if r1 < r6) goto osPeriphErrorDetected   (address < start address of area)
  ; TR:SPMF89:01.0051 End
  ; TR:SPMF89:01.0055 End
  ; TR:SPMF89:01.0059 End
  ; TR:SPMF89:01.0062 End
  ; TR:SPMF89:01.0064 End
  ; TR:SPMF89:01.0066 End
  ; TR:SPMF89:01.0068 End
  ; TR:SPMF89:01.0070 End
  ; TR:SPMF89:01.0072 End

  adr    r6, osSWILblTab                     ; r6 = &osSWILblTab
  ldr    pc, [r6, +r5, lsl #2]               ; goto osSWILblTab[r5]    (PC = *(r6 + (r5 << 2)))

osWritePeripheral8Trap:                      ; 0x84 TR:SPMF95:0004 
  cmp    r0,r1                               ; r1 <= r0?
  bcc    osPeriphErrorDetected               ; if (r1 > r0) goto osPeriphErrorDetected   (r1 > end address)
  ldmfd  sp!,{r6}                            ; pop r6
  ldmfd  sp!,{r0, r1, r5}                    ; pop r0, r1, r5
  strb   r2,[r1]                             ; *r1 = r2   TR:SPMF89:01.0053
  movs   pc, lr                              ; PC = LR, CPSR = SPSR   return from SWI
  
osWritePeripheral16Trap:   ; 0x85 TR:SPMF95:0005 
  add    r1,r1,#1                            ; r1 = r1 + 1
  cmp    r0,r1                               ; r1 <= r0?
  bcc    osPeriphErrorDetected               ; if (r1 > r0) goto osPeriphErrorDetected   (r1 > end address)
  ldmfd  sp!,{r6}                            ; pop r6
  ldmfd  sp!,{r0, r1, r5}                    ; pop r0, r1, r5
  strh   r2,[r1]                             ; *r1 = r2   TR:SPMF89:01.0057
  movs   pc, lr                              ; PC = LR, CPSR = SPSR   return from SWI
  
osWritePeripheral32Trap:   ; 0x86 TR:SPMF95:0006 
  add    r1,r1,#3                            ; r1 = r1 + 3
  cmp    r0,r1                               ; r1 <= r0?
  bcc    osPeriphErrorDetected               ; if (r1 > r0) goto osPeriphErrorDetected   (r1 > end address)
  ldmfd  sp!,{r6}                            ; pop r6
  ldmfd  sp!,{r0, r1, r5}                    ; pop r0, r1, r5
  str    r2,[r1]                             ; *r1 = r2   TR:SPMF89:01.0061
  movs   pc, lr                              ; PC = LR, CPSR = SPSR   return from SWI
  

osReadPeripheral8Trap:   ; 0x84 TR:SPMF95:0001 
  cmp    r0,r1                               ; r1 <= r0?
  bcc    osPeriphErrorDetected               ; if (r1 > r0) goto osPeriphErrorDetected   (r1 > end address)
  ldmfd  sp!,{r6}                            ; pop r6
  ldmfd  sp!,{r0, r1, r5}                    ; pop r0, r1, r5
  ldrb   r0,[r1]                             ; r0 = *r1   TR:SPMF89:01.0050
  movs   pc, lr                              ; PC = LR, CPSR = SPSR   return from SWI
  
osReadPeripheral16Trap:   ; 0x85 TR:SPMF95:0002 
  add    r1,r1,#1                            ; r1 = r1 + 1
  cmp    r0,r1                               ; r1 <= r0?
  bcc    osPeriphErrorDetected               ; if (r1 > r0) goto osPeriphErrorDetected   (r1 > end address)
  ldmfd  sp!,{r6}                            ; pop r6
  ldmfd  sp!,{r0, r1, r5}                    ; pop r0, r1, r5
  ldrh   r0,[r1]                             ; r0 = *r1   TR:SPMF89:01.0054
  movs   pc, lr                              ; PC = LR, CPSR = SPSR   return from SWI
  
osReadPeripheral32Trap:   ; 0x86 TR:SPMF95:0003 
  add    r1,r1,#3                            ; r1 = r1 + 3
  cmp    r0,r1                               ; r1 <= r0?
  bcc    osPeriphErrorDetected               ; if (r1 > r0) goto osPeriphErrorDetected   (r1 > end address)
  ldmfd  sp!,{r6}                            ; pop r6
  ldmfd  sp!,{r0, r1, r5}                    ; pop r0, r1, r5
  ldr    r0,[r1]                             ; r0 = *r1   TR:SPMF89:01.0058
  movs   pc, lr                              ; PC = LR, CPSR = SPSR   return from SWI
  
  
osModifyPeripheral8Trap:   ; 0x84 TR:SPMF95:0007 
  cmp    r0,r1                               ; r1 <= r0?
  bcc    osPeriphErrorDetected               ; if (r1 > r0) goto osPeriphErrorDetected   (r1 > end address)
  ldmfd  sp!,{r6}                            ; pop r6
  ldmfd  sp!,{r0, r1, r5}                    ; pop r0, r1, r5
  ; TR:SPMF89:01.0095 Start
  ldrb   r0,[r1]                             ; r0 = *r1
  and    r0,r0,r2                            ; r0 = r0 & r2
  orr    r0,r0,r3                            ; r0 = r0 & r3
  strb   r0,[r1]                             ; *r1 = r0
  ; TR:SPMF89:01.0095 End
  movs   pc, lr                              ; PC = LR, CPSR = SPSR   return from SWI
  
osModifyPeripheral16Trap:   ; 0x85 TR:SPMF95:0008 
  add    r1,r1,#1                            ; r1 = r1 + 1
  cmp    r0,r1                               ; r1 <= r0?
  bcc    osPeriphErrorDetected               ; if (r1 > r0) goto osPeriphErrorDetected   (r1 > end address)
  ldmfd  sp!,{r6}                            ; pop r6
  ldmfd  sp!,{r0, r1, r5}                    ; pop r0, r1, r5
  ; TR:SPMF89:01.0096 Start
  ldrh   r0,[r1]                             ; r0 = *r1
  and    r0,r0,r2                            ; r0 = r0 & r2
  orr    r0,r0,r3                            ; r0 = r0 & r3
  strh   r0,[r1]                             ; *r1 = r0
  ; TR:SPMF89:01.0096 End
  movs   pc, lr                              ; PC = LR, CPSR = SPSR   return from SWI
  
osModifyPeripheral32Trap:   ; 0x86 TR:SPMF95:0009 
  add    r1,r1,#3                            ; r1 = r1 + 3
  cmp    r0,r1                               ; r1 <= r0?
  bcc    osPeriphErrorDetected               ; if (r1 > r0) goto osPeriphErrorDetected   (r1 > end address)
  ldmfd  sp!,{r6}                            ; pop r6
  ldmfd  sp!,{r0, r1, r5}                    ; pop r0, r1, r5
  ; TR:SPMF89:01.0097 Start
  ldr    r0,[r1]                             ; r0 = *r1
  and    r0,r0,r2                            ; r0 = r0 & r2
  orr    r0,r0,r3                            ; r0 = r0 & r3
  str    r0,[r1]                             ; *r1 = r0
  ; TR:SPMF89:01.0097 End
  movs   pc, lr                              ; PC = LR, CPSR = SPSR   return from SWI
; TR:SASR30:0031 End
  
osSWIL6:   
  ; goto r3 fct
  ldmfd  sp!,{r0, r1, r5}                    ; pop r0, r1, r5
  mov    pc, r3                              ; PC = r3

osSWIL1:   ; link to appl SWI handler
  ldmfd  sp!,{r0, r1, r5}                    ; pop r0, r1, r5

  b      osUnhandledException                ; goto osUnhandledException     (no appl SWI handler allowed here) 
; TR:SPMF89:01.0092 End

; TR:SASR30:0031 Start
; Function table for preipheral access API
osSWILblTab:
  .word osWritePeripheral8Trap   ; TR:SPMF95:0004 
  .word osWritePeripheral16Trap  ; TR:SPMF95:0005 
  .word osWritePeripheral32Trap  ; TR:SPMF95:0006 
  .word osReadPeripheral8Trap    ; TR:SPMF95:0001 
  .word osReadPeripheral16Trap   ; TR:SPMF95:0002 
  .word osReadPeripheral32Trap   ; TR:SPMF95:0003 
  .word osModifyPeripheral8Trap  ; TR:SPMF95:0007 
  .word osModifyPeripheral16Trap ; TR:SPMF95:0008 
  .word osModifyPeripheral32Trap ; TR:SPMF95:0009 
  
  ; TR:SPMF89:01.0052 Start
  ; TR:SPMF89:01.0056 Start
  ; TR:SPMF89:01.0060 Start
  ; TR:SPMF89:01.0063 Start
  ; TR:SPMF89:01.0065 Start
  ; TR:SPMF89:01.0067 Start
  ; TR:SPMF89:01.0069 Start
  ; TR:SPMF89:01.0071 Start
  ; TR:SPMF89:01.0073 Start
osPeriphErrorDetected:  
  ; handle peripherall access error
  ldmfd  sp!,{r6}           ; pop r6
  ldmfd  sp!,{r0, r1, r5}   ; pop r0, r1, r5
  bl     osPeripheralError  ; call osPeripheralError
  ; TR:SPMF89:01.0052 End
  ; TR:SPMF89:01.0056 End
  ; TR:SPMF89:01.0060 End
  ; TR:SPMF89:01.0063 End
  ; TR:SPMF89:01.0065 End
  ; TR:SPMF89:01.0067 End
  ; TR:SPMF89:01.0069 End
  ; TR:SPMF89:01.0071 End
  ; TR:SPMF89:01.0073 End
  movs   pc, lr               ; PC = LR, CPSR = SPRS   return from SWI
; TR:SASR30:0031 End 
  
osPrefetchAbort:
  stmfd  sp!,{r0, r1}          ; push r0, r1

  mrc p15, #0, r0, c5, c0, #1  ; r0 = p15,1  Read Instruction Fault Status Register
  mov r1,#10000001111b         ; r1 = 0x40f
  and r0, r0, r1               ; r0 = r0 & r1

  cmp r0,#01101b               ; r0 == 0x0d ?  (permission fault)
  beq    osProtectionTrap      ; if (r0 == 0x0d) call osProtectionTrap
  cmp r0,#00000b               ; r0 == 0x00 ?  (background fault)
  beq    osProtectionTrap      ; if (r0 == 0x00) call osProtectionTrap
  cmp r0,#00001b               ; r0 == 0x01 ?  (alignment fault)
  beq    osProtectionTrap      ; if (r0 == 0x01) call osProtectionTrap
  
  ; no MPU fault, jump to application abort handler
  ldmfd  sp!,{r0, r1}          ; pop r0, r1
  b      _pabort  ; NEXTEER EDIT: goto Nexteer Prefetch Abort Handler 

  
osDataAbort:                   
; TR:SPMF89:01.0093 Start
  stmfd  sp!,{r0, r1}          ; push r0, r1

  ; exception caused by osCheckMPUAccess?
  sub r0, lr, #8               ; r0 = LR-8 (= address which caused memory violation)
  ldr r1, osRef_osCheck_Write  ; r1 = &osCheck_Write   address where osCheckMPUAccess tries to write
  cmp r0, r1                   ; r0 == r1?  violation address from osCheckMPUAccess?
  beq osCheckAbort             ; if (r0 == r1) goto osCheckAbort    jump if exception was caused by osCheckMPUAccess
  
  mrc p15, #0, r0, c5, c0, #0  ; r0 = p15,0  Read Data Fault Status Register
  mov r1,#10000001111b         ; r1 = 0x40f
  and r0, r0, r1               ; r0 = r0 & r1

  ; TR:SASR30:0031 Start
  cmp r0,#01101b               ; r0 == 0x0d ?  (permission fault)
  beq    osProtectionTrap      ; if (r0 == 0x0d) call osProtectionTrap
  cmp r0,#00000b               ; r0 == 0x00 ?  (background fault)
  beq    osProtectionTrap      ; if (r0 == 0x00) call osProtectionTrap
  ; TR:SASR30:0031 End
  cmp r0,#00001b               ; r0 == 0x01 ?  (alignment fault)
  beq    osProtectionTrap      ; if (r0 == 0x01) call osProtectionTrap
  
  ; no MPU fault, jump to application abort handler
  ldmfd  sp!,{r0, r1}          ; pop r0, r1
  b      _dabort  ; NEXTEER EDIT: goto Nexteer Prefetch Abort Handler 
  
  ; exception was caused by osCheckMPUAccess  
osCheckAbort:
  ldr    lr, osRef_osCheck_Return  ; LR = &osCheck_Return (=return address)
  ; return fron exception
  ldmfd  sp!,{r0, r1}              ; pop r0, r1
  movs   pc, lr                    ; PC = LR, CPSR = SPSR   return from exception
; TR:SPMF89:01.0093 End
  

osFIQ:
  ldr    r0, osRef_osUnhandledException   ; r0 = &osUnhandledException
  mov    lr, pc                           ; LR = PC
  bx     r0                               ; call osUnhandledException()


osUnhandledExceptionWrapper:
  ldr    r0, osRef_osUnhandledException   ; r0 = &osUnhandledException
  mov    lr, pc                           ; LR = PC
  bx     r0                               ; call osUnhandledException()

; TR:SOSK22:0133 Start
;-+--------------------------------------------------------------------------
; osStartOSasm                                                               
; Funktion: Assembler startup code                                                       
;   - assembler initialisation code                                                 
;   - jumps to osStartOSc
;   - never returns
; Parameter:                                                                 
; Returnvalue:                                                               
;----------------------------------------------------------------------------
   
   .ref osInitISRs
   .ref osInitSctx
   
  .def $osStartOSasm
$osStartOSasm
  .state16
  bx     pc            ; change to ARM mode if called from Thumb mode
  nop
  .state32

osStartOSasm
  ; Step 1 of design StartOS (ASIL part)
  ; Initialize all stack pointers used by OS  TR:SPMF05:0002 Start
  ; set IRQ mode, disable IRQ
  ; TR:SPMF89:01.0038 Start
  cpsid i,#osIRQMode                ; CPSR.M = osIRQMode, switch to IRQ mode

  ; set IRQ stack pointer
  ldr r0, oscnfSpecStackEnd         ; r0 = &osConfigBlock.uiStartAddressSpecStackEnd
  ldr r0, [r0]                      ; r0 = osConfigBlock.uiStartAddressSpecStackEnd
  ldr sp, [r0,#4*stkIdxIrqStack]    ; SP = SpecStackEnd[stkIdxIrqStack]   (SP = *(r0 + 4*stkIdxIrqStack))

  ; TR:SPMF89:01.0018 Start 
  ; TR:SPMF89:01.0029 Start
  ; set Abort mode
  cpsid i,#osAbortMode              ; CPSR.M = osAbortMode, switch to abort mode

  ; set abort stack pointer
  ldr r0, oscnfSpecStackEnd           ; r0 = &osConfigBlock.uiStartAddressSpecStackEnd
  ldr r0, [r0]                        ; r0 = osConfigBlock.uiStartAddressSpecStackEnd
  ldr sp, [r0,#4*stkIdxSystemStack]   ; SP = SpecStackEnd[stkIdxSystemStack]   (SP = *(r0 + 4*stkIdxSystemStack))
  ; TR:SPMF89:01.0029 End
  ; TR:SPMF89:01.0018 End
  
  ; switch to supervisor mode
  cps #osSVCMode                    ; CPSR.M = osSVCMode, switch to supervisor mode

  ; set SVC stack pointer
  ldr r0, oscnfSpecStackEnd               ; r0 = &osConfigBlock.uiStartAddressSpecStackEnd
  ldr r0, [r0]                            ; r0 = osConfigBlock.uiStartAddressSpecStackEnd
  ldr sp, [r0,#4*stkIdxSupervisorStack]   ; SP = SpecStackEnd[stkIdxSupervisorStack]   (SP = *(r0 + 4*stkIdxSupervisorStack))

  ; switch to system mode
  cps #osSysMode                          ; CPSR.M = osSysMode, switch to system mode


  ; TR:SPMF89:01.0027 Start
  ; set stack pointer to startup stack
  ldr r0, oscnfSpecStackEnd               ; r0 = &osConfigBlock.uiStartAddressSpecStackEnd
  ldr r0, [r0]                            ; r0 = osConfigBlock.uiStartAddressSpecStackEnd
  ldr sp, [r0,#4*stkIdxStartupStack]      ; SP = SpecStackEnd[stkIdxStartupStack]   (SP = *(r0 + 4*stkIdxStartupStack))
  ; TR:SPMF89:01.0027 End
  ; TR:SPMF05:0002 End
  
  ; Step 2 of design StartOS (ASIL part)
  ; fill system stack with empty pattern
  ldr r0, oscnfStackUsageMeasurement      ; r0 = &osConfigBlock.ucStackUsageMeasurement
  ldrb r0,[r0]                            ; r0 = osConfigBlock.ucStackUsageMeasurement
  cmp r0,#1                               ; osConfigBlock.ucStackUsageMeasurement == 1?
  ldreq   r0, osRef_osFillSystemStack     ; if (osConfigBlock.ucStackUsageMeasurement == 1) r0 = &osFillSystemStack
  ldrne   r0, osRef_osInitSystemStack     ; if (osConfigBlock.ucStackUsageMeasurement == 0) r0 = &osInitSystemStack
  mov   lr, pc                            ; LR = PC
  bx    r0                                ; call *r0()

  ldr r0, oscnfStackUsageMeasurement      ; r0 = &osConfigBlock.ucStackUsageMeasurement
  ldrb r0,[r0]                            ; r0 = osConfigBlock.ucStackUsageMeasurement
  cmp r0,#1                               ; osConfigBlock.ucStackUsageMeasurement == 1?

  ; fill task stacks
  bleq osFillTaskStacks                   ; if (osConfigBlock.ucStackUsageMeasurement == 1) call osFillTaskStacks
  blne osInitTaskStacks                   ; if (osConfigBlock.ucStackUsageMeasurement == 1) call osInitTaskStacks

  ; Step 3 of design StartOS (ASIL part)
  bl osInitISRs                           ; call osInitISRs()
  ; Step 4 and 5 of design StartOS (ASIL part)
  bl osInitSctx                           ; osInitSctx()
  ; TR:SPMF89:01.0038 End
  ; Step 6 of design StartOS (ASIL part)
  b osPsysStartOSc  ; TR:SPMF05:0001  TR:SOSK22:0133 End 
 
;-+--------------------------------------------------------------------------
; osFillTaskStacks                                                               
; Funktion: Fill task stacks with empty pattern                                                       
; Parameter:                                                                 
; Returnvalue:                                                               
;----------------------------------------------------------------------------
   
osFillTaskStacks:
  mov r0, #0                         ; r0 = 0    first task index
  ldr r3, oscnfNumberOfTasks         ; r3 = &osConfigBlock.uiNumberOfTasks
  ldrh r3,[r3]                       ; r3 = osConfigBlock.uiNumberOfTasks
  ldr r12, osRef_AAAAAAAA            ; r12 = 0xaaaaaaaa   (empty pattern)
  
osFillLoop1                          ; for all tasks
  cmp r0, r3                         ; r0 == r3?
  bcs osExitFillTaskStack            ; if (r0 >= r3) goto osExitFillTaskStack

  ldr r2, oscnfTcbStackTop           ; r2 = osConfigBlock.uiStartAddressStackEnd
  ldr r2,[r2]                        ; r2 = osConfigBlock.uiStartAddressStackEnd
  ldr r1,[r2, +r0, lsl #2]           ; r1 = StackEnd[r0]  (r1 = *(r2 + (r0 << 2)))

  tst r1, r1                         ; r1 == 0?
  beq osNextTaskIndex                ; if (r1 == 0) goto osNextTaskIndex

  ldr r2, oscnfSpecStackEnd          ; r2 = &osConfigBlock.uiStartAddressSpecStackEnd
  ldr r2, [r2]                       ; r2 = osConfigBlock.uiStartAddressSpecStackEnd
  ldr r2, [r2,#4*stkIdxStartupStack] ; r2 = SpecStackEnd[stkIdxStartupStack]   (r2 = *(r2 + (4*stkIdxStartupStack)))
  cmp r1, r2                         ; r1 == r2 ?
  moveq r1, sp                       ; if  (r1 == r2) r1 = SP   (if startup stack, start filling at current SP because we are running on this stack)                                                         

  ldr r2, oscnfTcbStackBottom        ; r2 = &osConfigBlock.uiStartAddressStackStart
  ldr r2,[r2]                        ; r2 = osConfigBlock.uiStartAddressStackStart
  ldr r2,[r2, +r0, lsl #2]           ; r2 = StackStart[r0]   (r2 = *(r2 + (r0 << 2)))

osFillLoop2                          ; for all stack words
  cmp r2, r1                         ; r2 == r1?
  bcs osNextTaskIndex                ; if (r2 >= r1) goto osNextTaskIndex

  str r12, [r1, #-4]!                ; *(--r1) = r12     fill with empty pattern
  b   osFillLoop2                    ; goto osFillLoop2
  
osNextTaskIndex  
  add r0, r0, #1                     ; r0 = r0 + 1    next task index
  b   osFillLoop1                    ; goto osFillLoop1
  
osExitFillTaskStack
  mov pc,lr                          ; PC = LR    return

  

  .def $osGetHighPrioBit
$osGetHighPrioBit
  .state16
  bx     pc                      ; change to ARM mode if called from Thumb mode
  nop
  .state32
  .def osGetHighPrioBit
 .armfunc osGetHighPrioBit
osGetHighPrioBit:
  nop                           ; avoid mode switch problems for mixed ARM/Thumb mode
  .word 0xe16f0f10              ; r0 = bit position of highest 1   clz r0,r0
  bx    lr                      ; PC = LR   return r0

  .endasmfunc

 
  ; enable hardware vectored interrup mode
  .def $osEnableHWVector
$osEnableHWVector
  .state16                           
  bx     pc                          ; change to ARM mode if called from Thumb mode
  nop
  .state32
  .def osEnableHWVector
 .armfunc osEnableHWVector
osEnableHWVector:
  mrc p15, #0, r1, c1, c0, #0        ; r1 = p15,0   read System Control Register configuration data
  orr r1, r1, #0x01000000            ; r1 = r1 | 0x40   set VE flag 
  mcr p15, #0, r1, c1, c0, #0        ; p15,0 = r1   write System Control Register configuration data
  bx    lr                           ; PC = LR    return

  .endasmfunc


  ; disable hardware vectored interrup mode
  .def $osDisableHWVector
$osDisableHWVector
  .state16
  bx     pc                 ; change to ARM mode if called from Thumb mode
  nop
  .state32
  .def osDisableHWVector
 .armfunc osDisableHWVector
osDisableHWVector:
  mrc p15, #0, r1, c1, c0, #0        ; r1 = p15,0   read System Control Register configuration data
  bic r1, r1, #0x01000000            ; r1 = r1 & ~0x40   reset VE flag 
  mcr p15, #0, r1, c1, c0, #0        ; p15,0 = r1   write System Control Register configuration data
  bx    lr                           ; PC = LR    return

  .endasmfunc

  
;  void osSetupMPURegion(osuint8 regionNr, osuint32 baseAddr, osuint32 sizeCnf, osuint32 accessCtrl);
  .def $osSetupMPURegion
$osSetupMPURegion
  .state16
  bx     pc              ; change to ARM mode if called from Thumb mode
  nop
  .state32
  .def osSetupMPURegion
 .armfunc osSetupMPURegion
osSetupMPURegion:
  mcr p15, #0, r0, c6, c2, #0 ; p15,c6,c2,1 = r0     Select region in MPU Memory Region Number Register
  mcr p15, #0, r1, c6, c1, #0 ; p15,c6,c1,0 = r1     Write Region Base Address Register
  mcr p15, #0, r2, c6, c1, #2 ; p15,c6,c1,2 = r2     Region Size and Enable Register
  mcr p15, #0, r3, c6, c1, #4 ; p15,c6,c1,4 = r3     Region Access Control Register

  mrc p15, #0, r2, c6, c1, #0 ; r2 = p15,c6,c1,0
  bx    lr                    ; PC = LR    return
  .endasmfunc

  
;  void osStoreRegionSettings(osuint8 r0, osuint32 *r1, osuint32 *r2, osuint32 *r3);
  .def $osStoreRegionSettings
$osStoreRegionSettings
  .state16
  bx     pc              ; change to ARM mode if called from Thumb mode
  nop
  .state32
  .def osStoreRegionSettings
 .armfunc osStoreRegionSettings
osStoreRegionSettings:
  mcr p15, #0, r0, c6, c2, #0    ; p15,c6,c2,0 = r0   Select region in MPU Memory Region Number Register
  
  mrc p15, #0, r0, c6, c1, #0    ; r0 = p15,c6,c1,0   Region Base Address Register
  str r0,[r1]                    ; *r1 = r0
  
  mrc p15, #0, r0, c6, c1, #2    ; r0 = p15,c6,c1,2 Region Size and Enable Register
  str r0,[r2]                    ; *r2 = r0
  
  cmp r3,#0                      ; r3 == 0 ?   store access only if reference != 0
  beq _osNoAccessToStore         ; if (r3 == 0) goto _osNoAccessToStore
  mrc p15, #0, r0, c6, c1, #4    ; r0 = p15,c6,c1,4   Region access control Register
  str r0,[r3]                    ; *r3 = r0
  
_osNoAccessToStore  
  bx    lr                       ; PC = LR    return
  .endasmfunc


  ; TR:SPMF89:0033 Start
  ;  void osCheckMPUAccess(osuint8 *DestinationAddress);
  .def $osCheckMPUAccess
$osCheckMPUAccess
  .state16
  bx     pc                     ; change to ARM mode if called from Thumb mode
  nop
  .state32
  .def osCheckMPUAccess
  .def osCheck_Write
  .def osCheck_Return
 .armfunc osCheckMPUAccess
osCheckMPUAccess:
  stmfd    sp!, {r4, r5, lr}    ; push r4, r5, lr   save modified permanent registers and LR
  mov      r5, r0               ; r5 = r0   save r0 (= argument DestinationAddress) into permanent register r5 (not destroyed during trap)
  mrs      r4, CPSR             ; r4 = CPSR   save CPSR into permanent register r4 (not destroyed during trap)
  ; disable all interrupts
  swi      #0x83                ; Trap 0x83   enter privileged mode to be able to disable to disable interrupts
  cpsid    i                    ; CPSR.I = 1    disable IRQ
  cmp      r0, #0               ; r0 == 0?   was previous mode privileged? (returned in r0 by SWI (trap))
  bne      osCheckMPUAccess_1   ; if (r0 != 0) goto osCheckMPUAccess_1     jump if previous mode was already privileged
  cps      #010000b             ; CPSR.M = 0x10, switch to user mode    back to user mode
osCheckMPUAccess_1:
  stmfd sp!, {r4}               ; push r4   save previous CPSR value
  
  ; read content of the destination address and save it to local "variable" r1
  ldrb  r1, [r5]                ; r1 = *r5   DestinationAddress
  mov   r2, #0xff               ; r2 = 0xFF
osCheck_Write:
  ; Try to write to destination address     
  strb  r2, [r5]                ; *DestinationAddress = 0xFF (*r5 = r2)
  ; Restore content of destination address from local "variable" r1
  strb  r1, [r5]                ; *DestinationAddress = r1   (*r5 = r1)
  
  ; Enable all interrupts
  ldmfd sp!, {r4}               ; pop r4    r4 = previous value of CPSR
  swi      #0x83                ; TRAP 0x83    enter privileged mode
  msr      CPSR_cf, r4          ; CPSR = r4    restore CPSR, this restores previous interrupt flag and previous mode
  ; return 0
  mov      r0, #0               ; r0 = 0    (= return value)
  ldmfd    sp!, {r4, r5, lr}    ; pop r4, r5, lr   restore modified permanent registers and LR
  bx    lr                      ; PC = LR    return
   
osCheck_Return:                 ; reached if write caused a memory protection violation
  ; Enable all interrupts
  ldmfd sp!, {r4}               ; pop r4 = previous value of CPSR
  swi      #0x83                ; Trap 0x83  enter privileged mode
  msr      CPSR_cf, r4          ; CPSR = r4   restore CPSR, this restores previous interrupt flag and previous mode
  ; return 1
  mov      r0, #1               ; r0 = 1 (= return value)
  ldmfd    sp!, {r4, r5, lr}    ; pop r4, r5, lr    restore modified permanent registers and LR
  bx    lr                      ; PC = LR    return
  .endasmfunc
  ; TR:SPMF89:0033 End



;  void osCallApplHook(osuint32 errCode, osuint32 hookFct, osuint32 stackAddr);
  .def $osCallApplHook
$osCallApplHook
  .state16
  bx     pc                      ; change to ARM mode if called from Thumb mode
  nop
  .state32
  .def osCallApplHook
 .armfunc osCallApplHook
osCallApplHook:
   stmfd    sp!, {r7}            ; push r7
   mrs      r7, CPSR             ; r7 = CPSR
   cps      #0x1F                ; CPSR.M = 0x1f, switch to system mode
   stmfd    sp!, {r4, lr}        ; push r4, lr

   mov      r4, sp               ; r4 = sp
   mov      sp, r2               ; sp = r2
   cps      #0x10                ; CPSR.M = 0x10, switch to user mode
   mov      lr,pc                ; LR = PC
   bx       r1                   ; call (r1())
   swi      #0x83                ; Trap 0x83  enter privileged mode
   mov      sp, r4               ; SP = r4
   ldmfd    sp!, {r4, lr}        ; pop r4, lr
   msr      CPSR_cxsf, r7        ; CPSR = r7
   ldmfd    sp!, {r7}            ; pop r7
  bx    lr                       ; PC = LR    return
  .endasmfunc

;  void osCallNTF(NonTrustedFunctionIndexType r0, NonTrustedFunctionParameterRefType r1,
;                  osuint32 r2, osuint32 r3);
;  no stack switch if stackAddr == 0
  .def $osCallNTF
$osCallNTF
  .state16
  bx     pc                ; change to ARM mode if called from Thumb mode
  nop
  .state32
  .def osCallNTF
 .armfunc osCallNTF
osCallNTF:
 
   stmfd    sp!, {r7}             ; push r7
   mrs      r7, CPSR              ; r7 = CPSR
   cps      #0x1F                 ; CPSR.M = 0x1f, switch to system mode
   stmfd    sp!, {r4, r5, lr}     ; push r4, r5, LR

   mov      r5, r3                ; r5 = r3
   cmp      r5, #0                ; r5 == 0?
   beq      _osNTFNoStackSwitch1  ; if (r5 == 0) goto _osNTFNoStackSwitch1
   mov      r4, sp                ; r4 = sp
   mov      sp, r3                ; sp = r3
_osNTFNoStackSwitch1:   
   cps      #0x10                 ; CPSR.M = 0x10, switch to user mode
   mov      lr,pc                 ; LR = PC
   bx       r2                    ; call (r2)
   swi      #0x83                 ; Trap 0x83    enter privileged mode

   cmp      r5, #0                ; r5 == 0?
   beq      _osNTFNoStackSwitch2  ; if (r5 == 0) goto _osNTFNoStackSwitch2
   mov      sp, r4                ; SP = r4
_osNTFNoStackSwitch2:   
   ldmfd    sp!, {r4, r5, lr}     ; pop r4, r5, lr
   msr      CPSR_cxsf, r7         ; CPSR = r7
   ldmfd    sp!, {r7}             ; pop r7
  bx    lr                        ; PC = LR    return
  .endasmfunc

  
  
  .def $osMPUEnable
$osMPUEnable
  .state16
  bx     pc                 ; change to ARM mode if called from Thumb mode
  nop
  .state32
  .def osMPUEnable
 .armfunc osMPUEnable
osMPUEnable:
  mrc p15, #0, r1, c1, c0, #0    ; r1 = p15,c1,0   read CP15 register 1
  orr r1, r1, #0x00001           ; r1 = r1 | 0x00001   set MPU enable bit
  orr r1, r1, #0x20000           ; r1 = r1 | 0x20000   enable background region for privileged access
  dsb                            ; Data Synchronization Barrier
  mcr p15, #0, r1, c1, c0, #0    ; p15,c1,0 = r1   enable MPU
  isb                            ; Instruction Synchronization Barrier

  bx    lr                       ; PC = LR    return
  .endasmfunc

  .def $osMPUDisable
$osMPUDisable
  .state16
  bx     pc                      ; change to ARM mode if called from Thumb mode
  nop
  .state32
  .def osMPUDisable
 .armfunc osMPUDisable
osMPUDisable:
  mrc p15, #0, r1, c1, c0, #0    ; r1 = p15,c1,0   read CP15 register 1
  bic r1, r1, #0x1               ; r1 = r1 & ~0x1   clear MPU enable bit
  dsb                            ; Data Synchronization Barrier
  mcr p15, #0, r1, c1, c0, #0    ; disable MPU 
  isb                            ; Instruction Synchronization Barrier
  bx    lr                       ; PC = LR    return
  .endasmfunc


  .include "tcb.inc"

  ; use correct register names if redefined in tcb.inc
  .asg "c0", c0
  .asg "c1", c1
  

  .ref osAPIStack
  .ref osStatusTypeReturn
  .ref osaOnAPIStack
  .ref osSetMPUForOS
  
  ; Wrapper for all AUTOSAR-API functions
; Execute function in non-privileged mode with memory protection enabled
osAPIWrapper .macro apiname, retarg, retargsize
; TR:SPMF89:01.0091 Start
; we need local references for each API to ensure that all labels are
; accesible PC relative
osStartDispatcherRef?  .word osStartDispatcher
osLockDispatcherRef?   .word osLockDispatcher
osStatusTypeReturn?    .word osStatusTypeReturn
osaOnAPIStackRef?       .word osaOnAPIStack
osaActiveTaskIndexRef? .word osaActiveTaskIndex
osActiveTaskPrioRef?   .word osActiveTaskPrio
oscnfSpecStackEnd?     .word osConfigBlock.uiStartAddressSpecStackEnd
  
  .def osPsys:apiname:  ; export symbol osPsys<API name>
  osExtRef os:apiname:  ; import API function
; TR:SOSK22:0028 Start 
 .armfunc osPsys:apiname:
osPsys:apiname::
  ; save registers
  stmfd           sp!, {r4, r6, r7, r8, r9, lr}   ; push r4, r6, r7, r8, r9, lr
  stmfd           sp!, {r0, r1, r2, r3}           ; push r0, r1, r2, r3  (function arguments)
  
  mrs             r9, CPSR                    ; r9 = CPSR, (r9 is permanent register)

  ; Step 1 of design
  ; switch to privileged mode, return TRUE (in R0) if already privileged
  swi             #0x83                       ; Trap 0x83   for privilege switch
  cpsid           i                           ; CPSR.I = 1    disable IRQ

  mov             r4, r0                      ; r4 = r0   save previous mode (r4 is permanent register)

  
  ; Step 2 of design
  bl osSetMPUForOS                            ; osSetMPUForOS() 

  ; Step 3 of design
  ; osLockDispatcher += 1  TR:SOSK22:0004 Start
  ldr             r0, osLockDispatcherRef?    ; r0 = &osLockDispatcher
  ldrb            r1, [r0]                    ; r1 = osLockDispatcher
  add             r1,r1,#1                    ; r1 += 1
  strb            r1, [r0]                    ; osLockDispatcher = r1
  ; TR:SOSK22:0004 End

  ; Step 4 of design
  ; osaOnAPIStack += 1, indicates that we are on API stack
  ldr             r0, osaOnAPIStackRef?        ; r0 = &osaOnAPIStack
  ldrb            r8, [r0]                    ; r8 = osaOnAPIStack
  add             r8,r8,#1                    ; r8 += 1
  strb            r8, [r0]                    ; osaOnAPIStack = r8

  ldmfd           sp!, {r0, r1, r2, r3}       ; pop r0, r1, r2, r3

  cps             #0x1F                       ; CPSR.M = 0x1F   switch to system mode
  .if ($$symlen(retarg) != 0)
  mov             r7, r:retarg:               ; r7 = Rx  Register with reference argument
  .endif

  cmp             r8, #1                      ; r8 == 1 ?
  bne             $6                          ; if (r8 != 1) goto $6  (we are already on API stack)
  
  mov             r8, sp                      ; r8 = SP
  
  ldr             r6, oscnfSpecStackEnd?      ; r6 = &osConfigBlock.uiStartAddressSpecStackEnd
  ldr             r6, [r6]                    ; r6 = osConfigBlock.uiStartAddressSpecStackEnd
  ldr             sp, [r6,#4*stkIdxAPIStack]  ; SP = SpecStackEnd[stkIdxAPIStack]  (SP = *(r6 + (4*stkIdxAPIStack))
  
  stmfd           r13!, {r8}                  ; *(--SP) = r8 (=saved SP)
$6: 
  ; Step 5 of design
  cps              #16                        ; CPSR.M = 0x16   switch to (non-privileged) user mode
  
  ; Step 6 of design
  bl              os:apiname:                 ; r0 = os<APIName>(...)
  mov             r8, r0                      ; r8 = r0 (r8 is permanent register)

  ; Step 7 of design
  ; enter privileged mode
  swi             #0x83                       ; Trap 0x83    for privilege switch

  ; Step 8 of design
  ; TR:SASR30:0018 Start
  bl osSetMPUForTask                          ; call osSetMPUForTask()  TR:SPMF89:0003

  ; Step 9 of design
  .if ($$symlen(retarg) != 0)
  ldr             r3, osStatusTypeReturn?     ; r3 = &osStatusTypeReturn
  ldrb            r0, [r3]                    ; r0 = osStatusTypeReturn
  ; return reference argument value if E_OK
  cmp             r0,#0                       ; r0 == 0?  (== E_OK?)
  bne             $4                          ; if (r0 != 0) goto $4
  
  cmp             r4, #0                      ; r4 == 0?  previous mode == non-privileged?
  bne             $5                          ; if (r4 != 0) goto $5  (caller was privileged)
  cps             #16                         ; CPSR.M = 0x16   switch to (non-privileged) user mode
$5:
  .if (($$symcmp(retargsize,"1")) == 0)
  strb            r8, [r7]                    ; *r7 = r8   (8 bit)
  .elseif (($$symcmp(retargsize,"2")) == 0)
  strh            r8, [r7]                    ; *r7 = r8   (16 bit)
  .elseif (($$symcmp(retargsize,"4")) == 0)
  str             r8, [r7]                    ; *r7 = r8   (32 bit)
  .endif
  bne             $4                          ; if (r4 != 0) goto $4  (caller was privileged)
  swi             #0x83                       ; Trap 0x83   for privilege switch
$4:
  .else
  mov             r0, r8                      ; r0 = function result 
  .endif
  ; TR:SASR30:0018 End
  
  ; Step 10 of design
  ldr             r8, osaOnAPIStackRef?        ; r8 = &osaOnAPIStack
  ldrb            r7, [r8]                    ; r7 = osaOnAPIStack   (r7 = *r8)
  sub             r7,r7,#1                    ; r7 = r7 - 1
  strb            r7, [r8]                    ; osaOnAPIStack = r7
  cmp             r7, #0                      ; r7 == 0 ?
  bne             $7                          ; if (r7 != 0) goto $7
  
  ldmfd           sp!, {sp}                   ; SP = *(SP); SP++
$7: 
  ; Step 11 of design
  cmp             r4, #0                      ; r4 == 0?    previous mode == non-privileged?
  beq             $8                          ; if (r4 != 0) goto $8
  orr             r8, r9, #10000000b          ; r8 = r9 | 0x80
  msr             CPSR_c, r8                  ; CPSR = r8    (disable IRQ)
$8:

  ldr             r8, osLockDispatcherRef?    ; r8 = &osLockDispatcher
  ldrb            r7, [r8]                    ; r7 = osLockDispatcher
  sub             r7,r7,#1                    ; r7 = r7 - 1
  strb            r7, [r8]                    ; osLockDispatcher = r7

$1: 
  .if (($$symcmp(apiname,"StartOSc")) == 0)
  .else
  cmp             r0, #0                      ; r0 == 0  == E_OK ?  dispatcher call only if API successful
  bne             $2                          ; if (r0 != 0) goto $2
  .endif
  
  .if (($$symcmp(apiname,"Schedule")) == 0)
  .elseif (($$symcmp(apiname,"TerminateTask")) == 0)
  .elseif (($$symcmp(apiname,"ChainTask")) == 0)
  .elseif (($$symcmp(apiname,"WaitEvent")) == 0)
  .else
  cmp             r7, #0                      ; r7 == 0 ?
  bne             $2                          ; if (r7 != 0) goto $2
  .endif
  
  .if (($$symcmp(apiname,"TerminateTask")) == 0)
  ldr             r8, osaActiveTaskIndexRef?  ; r8 = &osaActiveTaskIndex
  mov             r7, #osdNoActiveTask        ; r7 = osdNoActiveTask
  strh            r7, [r8]                    ; osaActiveTaskIndex = osdNoActiveTask  (*r8 = r7)
  ldr             r8, osActiveTaskPrioRef?    ; r8 = osActiveTaskPrio
  mov             r7, #osdNoActivePrio        ; r7 = osdNoActivePrio
  strh            r7, [r8]                    ; osActiveTaskPrio = osdNoActivePrio
  .endif
  
  .if (($$symcmp(apiname,"ChainTask")) == 0)
  ldr             r8, osaActiveTaskIndexRef?  ; r8 = &osaActiveTaskIndex
  mov             r7, #osdNoActiveTask        ; r7 = osdNoActiveTask
  strh            r7, [r8]                    ; osaActiveTaskIndex = osdNoActiveTask  (*r8 = r7)
  ldr             r8, osActiveTaskPrioRef?    ; r8 = osActiveTaskPrio
  mov             r7, #osdNoActivePrio        ; r7 = osdNoActivePrio
  strh            r7, [r8]                    ; osActiveTaskPrio = osdNoActivePrio
  .endif
  
  .if (($$symcmp(apiname,"StartOSc")) != 0)
  ldr             r8, osStartDispatcherRef?   ; r8 = &osStartDispatcher
  ldrb            r7, [r8]                    ; r7 = osStartDispatcher
  cmp             r7, #0                      ; r7 == 0 ?
  ; if osStartDispatcher == TRUE activate delayed interrupt
  beq             $2                          ; if (osStartDispatcher == 0) goto $2
  .endif
  swi             #0x81                       ; Trap 0x81  call dispatcher trap
$2:
  tst             r9, #0x80                   ; r9 & 0x80 == 0x80?   flags = r9 & 0x80 (test saved IRQ bit in r9)
  bne             $3                          ; if (r9 & 0x80 != 0x80) goto $3     if (r9 & 0x80) goto $3
  cpsie           i                           ; CPSR.I = 0    enable IRQ
$3
  cmp             r4, #0                      ; r4 == 0?    previous mode == non-privileged?
  bne             $9                          ; if (r4 != 0) goto $9    if (previous mode != non-privileged) goto $1
  cps             #16                         ; CPSR.M = 0x16    switch to non-privileged user mode
$9
  ldmfd           r13!, {r4, r6, r7, r8, r9, pc}  ; pop r3, r4, r7, r8, r9, pc
; TR:SOSK22:0028 End   
; TR:SPMF89:01.0091 End
   
  .newblock
  .endasmfunc
  .endm
  
  .ref osStartDispatcher
osRef_osStartDispatcherRef  .word osStartDispatcher
osRef_osLockDispatcherRef   .word osLockDispatcher

  .if (osdNumberOfAllTasks > 0)
  osAPIWrapper ActivateTask
  osAPIWrapper TerminateTask
  osAPIWrapper ChainTask 
  osAPIWrapper Schedule 
  osAPIWrapper GetTaskID,0,2 
  osAPIWrapper GetTaskState,1,1 
  .endif
  
  .if ((osdNumberOfAllResources) > 0)
  osAPIWrapper GetResource 
  osAPIWrapper ReleaseResource 
  .endif
 
  .if (osdNumberOfExtendedTasks > 0) 
  osAPIWrapper SetEvent 
  osAPIWrapper ClearEvent 
  osAPIWrapper GetEvent,1,4
  osAPIWrapper WaitEvent 
  .endif

  .if (osdNumberOfAlarms > 0)
  osAPIWrapper SetRelAlarm 
  osAPIWrapper SetAbsAlarm 
  osAPIWrapper CancelAlarm 
  osAPIWrapper GetAlarm,1,4 
  .endif
  
  .if (osdNumberOfScheduleTables > 0)
  osAPIWrapper StartScheduleTableRel 
  osAPIWrapper StartScheduleTableAbs 
  osAPIWrapper StopScheduleTable 
  osAPIWrapper GetScheduleTableStatus,1,1 
  osAPIWrapper NextScheduleTable 
  .endif
  
  .if (osdNumberOfSWCounters > 0)
  osAPIWrapper IncrementCounter 
  .endif

  osAPIWrapper GetApplicationID 
  osAPIWrapper CheckObjectAccess 
  osAPIWrapper CheckObjectOwnership 
  osAPIWrapper StartOSc
  ; TR:SPMF89:01.0045 Start
  osAPIWrapper ShutdownOS
  ; TR:SPMF89:01.0045 End

