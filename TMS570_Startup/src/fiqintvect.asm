; Version Control:
; Date Created:      Mon Mar 19 13:59:02 2012 %
; %version:          1 %
; %derived_by:       nz63rn %
; %date_modified:    Mon Jun 10 08:01:15 2013 %
;---------------------------------------------------------------------------------------------------------------------
; Date      Rev      Author         Change Description                                                        SCR #
; -------   -------  --------  ---------------------------------------------------------------------------  ----------
; 06/10/13  1 		  KMC		Initial creation in TMS570_Startup component, to support fp exception fiq

	.text
	.arm
	
	
	.def	_fiqhandler
    .asmfunc

_fiqhandler
 	ldr		r8, fiqvectreg
	ldr		pc,  [r8]

fiqvectreg	.word	0xFFFFFE74

    .endasmfunc
