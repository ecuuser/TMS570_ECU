/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : sys_core.h
* Module Description: TI Halcogen based header
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/* Version Control:
 * Date Created:      Wed Apr 13 12:17:00 2011
 * %version:          3 %
 * %derived_by:       czgng4 %
 * %date_modified:    Thu Oct  3 16:34:55 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 06/09/12  1        LWW       Initial Version
 * 06/06/13  2        KMC       Added functions needed for Cd_uDiag floating point exception handling		sag_EPS#8587
 * 10/03/13  3        LWW       Added disable RAM ECC function
 */

#ifndef SYS_CORE_H_
#define SYS_CORE_H_

#include "Std_Types.h"

void _coreEnableVfp_(void);

void _coreInitRegisters_(void);

void _esmCcmErrorsClear_(void);

void _coreEnableRamEcc_(void);

void _coreDisableRamEcc_(void);

uint32 _coreGetDebugStatusAndControlRegister_(void);

uint32 _coreGetSecondaryAuxiliaryControlRegister_(void);

void _coreSetSecondaryAuxiliaryControlRegister_(uint32 SecAuxCtrlRegVal_Cnt_T_u32);

uint32 _coreGetFPSCR_(void);

#endif
