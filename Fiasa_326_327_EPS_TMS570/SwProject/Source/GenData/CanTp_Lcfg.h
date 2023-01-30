/* -----------------------------------------------------------------------------
  Filename:    CanTp_Lcfg.h
  Description: Toolversion: 11.08.02.01.30.01.24.00.00.00
               
               Serial Number: CBD1300124
               Customer Info: Nexteer Automotive Corporation
                              Package: MSR_Vector_SLP3
                              Micro: TMS570LS30376USC
                              Compiler: TexasInstruments ccs 4.9.2
               
               
               Generator Fwk   : GENy 
               Generator Module: CanTp
               
               Configuration   : C:\SynergyProjects\Haitec_LC_EPS_TMS570-nzx5jd\Haitec_LC_EPS_TMS570\Tools\AsrProject\Config\ECUC\EPS.ecuc.vdsxml
               
               ECU: 
                       TargetSystem: Hw_Tms470/570Cpu (Dcan)
                       Compiler:     TexasInstruments
                       Derivates:    TMS570LS30316U
               
               Channel "CAN00":
                       Databasefile: 
                       Bussystem:    CAN
                       Manufacturer: Vector
                       Node:         CanStateManagerConfiguration

  Generated by , 2014-03-07  10:52:22
 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2001-2011 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

#if !defined(CANTP_LCFG_H)
#define CANTP_LCFG_H

/* -----------------------------------------------------------------------------
    &&&~ Include files
 ----------------------------------------------------------------------------- */

/* START of Checksum exclude for
  - Tp_AsrTpCanLinktimeCRC */
#include "CanTp_Types.h"
/* END of Checksum exclude for
  - Tp_AsrTpCanLinktimeCRC */


/* -----------------------------------------------------------------------------
    &&&~ Global defines
 ----------------------------------------------------------------------------- */

/* START of Checksum include for
  - Tp_AsrTpCanLinktimeCRC */
/* Maximum number of SDUs supported by the CanTp on this ECU */
#define CANTP_MAX_NUM_RXSDUS                 2
#define CANTP_MAX_NUM_TXSDUS                 1
#define CANTP_NUM_RX_CHANNELS                CANTP_MAX_NUM_RXSDUS
#define CANTP_NUM_TX_CHANNELS                CANTP_MAX_NUM_TXSDUS
#define CANTP_IDENTITY_MANAGER               STD_OFF
/* END of Checksum include for
  - Tp_AsrTpCanLinktimeCRC */


/* -----------------------------------------------------------------------------
    &&&~ Global data types and structures
 ----------------------------------------------------------------------------- */

#define CANTP_START_SEC_VAR_INIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/* START of Checksum include for
  - Tp_AsrTpCanLinktimeCRC */
/* All other runtime data */
extern VAR(vCanTp_AdminDataType, CANTP_VAR_INIT) vCanTp_AdminData;

/* END of Checksum include for
  - Tp_AsrTpCanLinktimeCRC */

#define CANTP_STOP_SEC_VAR_INIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"


#define CANTP_START_SEC_VAR_NOINIT_8BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/* START of Checksum include for
  - Tp_AsrTpCanLinktimeCRC */
/* Temporary buffers to assemble CanTp-frames or parts of them */
extern VAR(uint8, CANTP_VAR_NOINIT) vCanTp_rxBuf[CANTP_NUM_RX_CHANNELS][CANTP_MAX_FRAME_LENGTH];
extern VAR(uint8, CANTP_VAR_NOINIT) vCanTp_txBuf[CANTP_NUM_TX_CHANNELS][CANTP_MAX_FRAME_LENGTH];

/* END of Checksum include for
  - Tp_AsrTpCanLinktimeCRC */

#define CANTP_STOP_SEC_VAR_NOINIT_8BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"


#define CANTP_START_SEC_VAR_NOINIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/* START of Checksum include for
  - Tp_AsrTpCanLinktimeCRC */
/* Administration data in RAM */
extern VAR(vCanTp_RxStateType, CANTP_VAR_NOINIT) vCanTp_RxState[CANTP_NUM_RX_CHANNELS];
extern VAR(vCanTp_TxStateType, CANTP_VAR_NOINIT) vCanTp_TxState[CANTP_NUM_TX_CHANNELS];

/* END of Checksum include for
  - Tp_AsrTpCanLinktimeCRC */

#define CANTP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"


#define CANTP_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/* START of Checksum include for
  - Tp_AsrTpCanLinktimeCRC */
extern FUNC(uint8, CANTP_CODE) GetAddressingType(PduIdType rxPduId);
extern FUNC(PduIdType, CANTP_CODE) GetRxSdu(PduIdType rxPduId);
extern FUNC(PduIdType, CANTP_CODE) GetRxSduExt(PduIdType rxPduId, uint8 ta);
#define GetRxSduMixed11(rxPduId, ae)         GetRxSduExt((rxPduId), (ae))
extern FUNC(PduIdType, CANTP_CODE) GetTxSdu(PduIdType rxPduId);
extern FUNC(PduIdType, CANTP_CODE) GetTxSduExt(PduIdType rxPduId, uint8 ta);
#define GetTxSduMixed11(rxPduId, ae)         GetTxSduExt((rxPduId), (ae))

/* END of Checksum include for
  - Tp_AsrTpCanLinktimeCRC */

#define CANTP_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"




/* START of Checksum include for
  - Tp_AsrTpCanLinktimeCRC */
#define CANTP_START_SEC_CONST_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/* -----------------------------------------------------------------------------
    &&&~ Production Error Detection
 ----------------------------------------------------------------------------- */

extern CONST(Dem_EventIdType, CANTP_CONST) CanTp_E_Com;


#define CANTP_STOP_SEC_CONST_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"


/* END of Checksum include for
  - Tp_AsrTpCanLinktimeCRC */


#endif /* CANTP_LCFG_H */