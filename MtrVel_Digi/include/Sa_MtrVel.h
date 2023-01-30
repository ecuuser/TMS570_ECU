/**********************************************************************
*
*	Header %name:	Sa_MtrVel.h %
*	Instance:		sag_EPS_1
*	Description:	
*	%created_by:	nzt9hv %
*	%date_created:	Tue Jun 11 16:35:11 2013 %
*
**********************************************************************/
#ifndef SA_MTRVEL_H
#define SA_MTRVEL_H

#include "Std_Types.h"

/* Component private variables */
#ifdef MTRVEL_C

#define D_MTRVELOSBUFNUM_CNT_U08    4U /* 2 buffers required for algorithm, copies of buffers required for snapshot data results in 4 total buffers */
#define D_SNAPSHOTBUF_CNT_U08			2u /* number of buffers for holding snapshot data of variable set for data acquisition */

extern VAR(uint8, AUTOMATIC) MtrVel3_OsBufPos_Cnt_M_u08[D_MTRVELOSBUFNUM_CNT_U08];
extern VAR(float32, AUTOMATIC) MtrVel3_PosBuffer_Rad_M_f32[D_MTRVELOSBUFNUM_CNT_U08][D_MTRVELOSBUFSZ_CNT_U08];
extern VAR(uint16, AUTOMATIC) 	MtrVel3_TimeBuffer_uS_M_u16p0[D_MTRVELOSBUFNUM_CNT_U08][D_MTRVELOSBUFSZ_CNT_U08];

extern volatile VAR(uint8, AUTOMATIC) MtrVel_OsBufSelect_Cnt_M_u08;
#endif

extern FUNC(void, SA_MTRVEL_CODE) MtrVel3_Per1(void);
#endif
