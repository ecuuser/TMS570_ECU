/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : MtrCtrl_Irq.c
* Module Description: Motor Control Interrupt Request Service
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/* Version Control:
 * Date Created:      Wed Apr 13 12:17:00 2011
 * %version:          EA3#2 %
 * %derived_by:       nzdx8v %
 * %date_modified:    Mon Jan 27 15:51:06 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 04/13/11  1        LWW       Initial K2xx Synergy Version
 * 11/03/11  2        LWW       Added anomaly patch for ADC sampling
 * 03/01/12	 3		  RR		Added Function Calls for Current Mode 
 * 04/18/12	 4		  RR		Changes for IPM	
 * 02/21/13	 '3		  SAH		Added ePWM_Per1 function
 * 05/13/13	 5		  SAH		Updated MtrlCtrl function name
 * 05/21/13	 6		  SAH		Added MtrVel3_Per1
 * 07/18/13  7        OT        Updated vim.h to vim_regs.h
 * 07/30/13  8        OT        Updates for new DigMSB components
 * 08/01/13  9        OT        Updates for Nhet with SENT
 * 10/05/13  10       OT        Changed MtrCtrl ISR to FIQ
 * 01/13/14  11       OT        Changed MtrCtrl ISR back to ISR
 * 01/27/14  12       OT        Added MemMap statements
 * 04/21/14  13       OT        Updates for DMA
 * 05/08/14  14       OT        Updates for DigMSB v6
 * 05/28/14  15       OT        Updates for DMA 002.0
 * 07/21/14  16       OT        Updates for anomaly 6897 - clear ADC EOC twice
 * 10/27/14  16.1.1   M. Story  Anomaly 7339
 * 11/17/14  16.1.2   OT        Updates for GliwaT1 integration
 * 11/16/15   17       PS        Updates for SF99B version 17	 						  					EA3#4579
 */


/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"
#include "MtrCtrl_Irq.h"
#include "Os.h"
#include "adc_regs.h"
#include "dma_regs.h"
#include "CDD_Func.h"
#include "Sa_DigMSB.h"
#include "Sa_MtrVel.h"
#include "Ap_MtrCtrl.h"
#include "PwmCdd.h"
#include "ePWM.h"
#include "Nhet.h"
#include "IoHwAbstractionUsr.h"
#include "T1_AppInterface.h"


#define MTRCTRLIRQ_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint16, AUTOMATIC) Loop125usCounter_Cnt_M_u16;
#define MTRCTRLIRQ_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */

/*****************************************************************************
* Local Functions
*****************************************************************************/
extern FUNC(void, AUTOMATIC) CurrDQPer1(void);
FUNC(void, MTRCTRL_CODE) MtrCtrlTaskList(void);


/*****************************************************************************
  * Name:        EnableIrq
  * Description: 
  * Inputs:      None 
  * Outputs:     None
*****************************************************************************/
/* TODO: Determine if this INTERRUPT pragma is required when using the  */
/*        interrupt keyword.                                            */
#pragma INTERRUPT(Isr_MtrCtrl, IRQ);
MTRCTRL_COMPILER_ISR void Isr_MtrCtrl(void)
{
	T1_TraceStartNoSusp(T1_Isr_MtrCtrl_ID);
	
	MtrCtrlTaskList();
	
	IoHwAb_CaptureADC();
	
	/* BTC Interrupt Flag Clear */
	DMACTRLREG->BTCFLAG = (1u << 3);
	
	/* ADC2 Event (Group 1) EOC Interrupt Flag Clear */
	adcREG2->GxINTFLG[1u] = (1u << 3);
	
	/* clear again for anomaly 6897 */
	adcREG2->GxINTFLG[1u] = (1u << 3);
	
#ifdef T1_ENABLE
	T1_DelayRoutine(core0_userDelay_DL_ID);
#endif
	
	T1_TraceStopNoSusp(T1_Isr_MtrCtrl_ID);
}

FUNC(void, MTRCTRL_CODE) MtrCtrlTaskList(void)
{
	DigMSB_Per1();
	MtrVel3_Per1();
	
	Loop125usCounter_Cnt_M_u16 = (Loop125usCounter_Cnt_M_u16 ^ 1U);
	if( Loop125usCounter_Cnt_M_u16 == 1U )
	{
		CurrDQPer1();
		TrqCogCancRefPer1();
		PICurrCntrl_Per1();
		MicroDiag_Per1();
		CDDInterface_Per5();
	}
	
	PwmCdd_Per1();
	ePWM_Per1();
	Nhet1_Per3();
}

