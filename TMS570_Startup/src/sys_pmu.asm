
;*****************************************************************************
; Copyright 2010 Nexteer Automotive, All Rights Reserved.
; Nexteer Confidential
;
; Module File Name  : sys_memory.asm
; Module Description: TI Halcogen based micro init
; Product           : Gen II Plus - EA3.0
; Author            : Lovepreet Kaur
;*****************************************************************************
;---------------------------------------------------------------------------
; Version Control:
; Date Created:      Thu Nov 11 16:33:22 2010
; %version:          1 %
; %derived_by:       gz7pm0 %
; %date_modified:    Fri May  9 09:31:06 2014 % 
;-------------------------------------------------------------------------------
; sys_pmu.asm
;
; (c) Texas Instruments 2009-2013, All rights reserved.
;

    .text
    .arm

;-------------------------------------------------------------------------------
; Enable Counters Global [Cycle, Event [0..2]]
; Note: It will reset all counters
; SourceId : PMU_SourceId_002
; DesignId : PMU_DesignId_002
; Requirements : HL_SR485

    .def     _pmuEnableCountersGlobal_
    .asmfunc

_pmuEnableCountersGlobal_

        stmfd sp!, {r0}
        mrc   p15, #0, r0, c9, c12, #0 
        orr   r0,  r0, #7
        mcr   p15, #0, r0, c9, c12, #0
        ldmfd sp!, {r0}		
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Disable Counters Global [Cycle, Event [0..2]]
; SourceId : PMU_SourceId_003
; DesignId : PMU_DesignId_003
; Requirements : HL_SR485

    .def     _pmuDisableCountersGlobal_
    .asmfunc

_pmuDisableCountersGlobal_

        stmfd sp!, {r0}
        mrc   p15, #0, r0, c9, c12, #0 
        bic   r0,  r0, #1
        mcr   p15, #0, r0, c9, c12, #0
        ldmfd sp!, {r0}		
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Reset Cycle Counter abd Event Counters [0..2]
; SourceId : PMU_SourceId_006
; DesignId : PMU_DesignId_006
; Requirements : HL_SR485

    .def     _pmuResetCounters_
    .asmfunc

_pmuResetCounters_

        stmfd sp!, {r0}
        mrc   p15, #0, r0, c9, c12, #0 
        orr   r0,  r0, #6
        mcr   p15, #0, r0, c9, c12, #0
        ldmfd sp!, {r0}		
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Start Counters [Cycle, 0..2]
; SourceId : PMU_SourceId_007
; DesignId : PMU_DesignId_007
; Requirements : HL_SR485

    .def     _pmuStartCounters_
    .asmfunc

_pmuStartCounters_

        mcr   p15, #0, r0, c9, c12, #1
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Stop Counters [Cycle, 0..2]

    .def     _pmuStopCounters_
    .asmfunc

_pmuStopCounters_
; SourceId : PMU_SourceId_008
; DesignId : PMU_DesignId_008
; Requirements : HL_SR485

        mcr   p15, #0, r0, c9, c12, #2
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Get Cycle Count
; SourceId : PMU_SourceId_010
; DesignId : PMU_DesignId_010
; Requirements : HL_SR486

    .def     _pmuGetCycleCount_
    .asmfunc

_pmuGetCycleCount_

        mrc   p15, #0, r0, c9, c13, #0
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
;*****************************************************************************
;
;CHANGE HISTORY:
;
;Date      Rev      Author         Change Description              SCR #
;                                    (MDD Rev & Date)
;-------   -------  --------  -----------------------------------  ----------
;05/09/14   1.0      LK       Initial file creation
;******************************************************************************

