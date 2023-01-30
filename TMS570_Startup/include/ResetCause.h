/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : ResetCause.h
* Module Description: This file contains the definition of the ResetCause variable
* Product           : Gen II Plus EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/* Version Control:
 * Date Created:      Fri May 11 12:17:00 2012
 * %version:          6 %
 * %derived_by:       nz63rn %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 06/09/12  1        LWW       Initial Version
 * 07/06/12  2        LWW       Updates for application reset causes
 * 11/13/12  3        LWW       Added MPU violation reset cause
 * 11/29/12  4        LWW       Added different Wdg Reset causes
 * 05/30/13	 5		  KMC		Added FPU exception reset causes
 * 02/01/15  6        KMC       Added HTU and DMA reset causes; QAC cleanup										CR12836
 */

#ifndef RESETCAUSE_H_
#define RESETCAUSE_H_

#include "Platform_Types.h"
#include "Compiler.h"

#define PWRONRESET 				0x0000FFFFUL
#define DEBUGRESET 				0x0001FFFEUL
#define CPURESET 				0x0002FFFDUL
#define SPPBISTFAILED 			0x0003FFFCUL
#define DPPBISTFAILED 			0x0004FFFBUL
#define EXTRESET 				0x0005FFFAUL
#define OSCFAIL 				0x0006FFF9UL
#define SWRESET 				0x0007FFF8UL
#define WDGFAIL 				0x0008FFF7UL
#define CCMSTEFFAILED 			0x0009FFF6UL
#define CCMSTFAILED 			0x000AFFF5UL
#define CCMEFFAILED 			0x000BFFF4UL
#define PBISTSCFAILED 			0x000CFFF3UL
#define STCSCFAILED 			0x000DFFF2UL
#define STCFAILED 				0x000EFFF1UL
#define ESM3NONZERO 			0x000FFFF0UL
#define EFCSTFAILED 			0x0010FFEFUL
#define EFCSTUCKZERO 			0x0011FFEEUL
#define EFCERROR 				0x0012FFEDUL
#define FLSBUS2CORRFAILED 		0x0013FFECUL
#define FLSBUS2ADDCAPFAILED 	0x0014FFEBUL
#define FLSBUS2MULBITDETFAILED 	0x0015FFEAUL
#define FLSBUS2SNGBITDETFAILED 	0x0016FFE9UL
#define VIMPARFLGFAILED			0x0017FFE8UL
#define VIMPARADDERRFAILED		0x0018FFE7UL
#define VIMPARESMFAILED			0x0019FFE6UL
#define DCAN1PARESMFAILED		0x001AFFE5UL
#define DCAN2PARESMFAILED		0x001BFFE4UL
#define DCAN3PARESMFAILED		0x001CFFE3UL
#define DMAPARESMFAILED			0x001DFFE2UL
#define MIBADC1PARESMFAILED		0x001EFFE1UL
#define MIBADC2PARESMFAILED		0x001FFFE0UL
#define MIBSPI1PARESMFAILED		0x0020FFDFUL
#define MIBSPI3PARESMFAILED		0x0021FFDEUL
#define MIBSPI5PARESMFAILED		0x0022FFDDUL
#define N2HET1PARESMFAILED		0x0023FFDCUL
#define N2HET1TUPARESMFAILED	0x0024FFDBUL
#define N2HET2PARESMFAILED		0x0025FFDAUL
#define N2HET2TUPARESMFAILED	0x0026FFD9UL
#define B0MULBITRAMECCDETFAILED	0x0027FFD8UL
#define B1MULBITRAMECCDETFAILED	0x0028FFD7UL
#define B0SNGBITRAMECCDETFAILED	0x0029FFD6UL
#define B1SNGBITRAMECCDETFAILED	0x002AFFD5UL
#define SNGBITFLSECCDETFAILED	0x002BFFD4UL
#define MULBITFLSECCDETFAILED	0x002CFFD3UL
#define LPOTRIMERROR			0x002DFFD2UL
#define DATAMULBITRAMECCFAILED	0x002EFFD1UL
#define DATAMULBITFLSECCFAILED	0x002FFFD0UL
#define CPUDATAABORT			0x0030FFCFUL
#define CPUPREFETCHABORT		0x0031FFCEUL
#define PRFTCMULBITRAMECCFAILED	0x0032FFCDUL
#define PRFTCMULBITFLSECCFAILED	0x0033FFCCUL
#define UNDEFINST				0x0034FFCBUL
#define CLOCKMONITOR			0x0035FFCAUL
#define CCMFAILED				0x0036FFC9UL
#define FMCUNCORRERR			0x0037FFC8UL
#define B0UNCORRERR				0x0038FFC7UL
#define B1UNCORRERR				0x0039FFC6UL
#define B0ADDPARERR				0x003AFFC5UL
#define B1ADDPARERR				0x003BFFC4UL
#define FLSECCLIVELOCK			0x003CFFC3UL
#define VIMMULTBITFLT			0x003DFFC2UL
#define VIMPARTHRSHFLT			0x003EFFC1UL
#define UNUSEDINTERRUPT			0x003FFFC0UL
#define STACKOVERWRITE			0x0040FFBFUL
#define MPUVIOLATION			0x0041FFBEUL
#define WDGALIVEMONFAIL			0x0042FFBDUL
#define WDGDEADLINEFAIL			0x0043FFBCUL
#define WDGPROGFLOWFAIL			0x0044FFBBUL
#define SWWDGFAIL				0x0045FFBAUL
#define FPUDZCEXCP				0x0046FFB9UL
#define FPUOFCEXCP				0x0047FFB8UL
#define FPUIOCEXCP				0x0048FFB7UL
#define FPUUNKNOWNEXCP			0x0049FFB6UL
#define HTU1MPUSTARTUPFAIL		0x004AFFB5UL
#define HTU2MPUSTARTUPFAIL		0x004BFFB4UL
#define DMAMPUSTARTUPFAIL		0x004CFFB3UL

typedef uint32 ENUM_ResetCause;
extern volatile VAR(ENUM_ResetCause, CD_RESETHANDLER_VAR_NOINIT) ResetCause_Cnt_Enum;

#endif /* RESETCAUSE_H_ */
