; Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1

;*****************************************************************************
; Project Name: OSEK 3.0
;    File Name: vrm.inc
;
;  Module version: $vv$=1.01
;
;  Description: Assembler header file for release management
;
;-----------------------------------------------------------------------------
;               C O P Y R I G H T
;-----------------------------------------------------------------------------
; Copyright (c) 2011 Vector Informatik GmbH               All rights reserved.
;****************************************************************************/


; KB begin vrmAsmReleaseNumberReference (overwritten)
; Assembler source release number reference
osdVrmAsmMajRelNumRef        .set 5
osdVrmAsmMinRelNumRef        .set 6

; Assembler generator release number reference
osdVrmAsmGenMajRelNumRef     .set 5
osdVrmAsmGenMinRelNumRef     .set 6
; KB end vrmAsmReleaseNumberReference

; source VRM checks

 .if (osdVrmAsmMajRelNum!=osdVrmAsmMajRelNumRef)
 .emsg "VRM: major release number mismatch (Source)"
 .endif

 .if (osdVrmAsmMinRelNum!=osdVrmAsmMinRelNumRef)
 .emsg "VRM: minor release number mismatch (Source)"
 .endif


; generator VRM checks

 .if osdVrmAsmGenMajRelNum!=osdVrmAsmGenMajRelNumRef
 .emsg "VRM: major release number mismatch (Generator)"
 .endif

 .if osdVrmAsmGenMinRelNum!=osdVrmAsmGenMinRelNumRef
 .emsg "VRM: minor release number mismatch (Generator)"
 .endif

