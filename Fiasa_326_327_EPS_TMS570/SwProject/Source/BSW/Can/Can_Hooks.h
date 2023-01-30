/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 595 */

/*****************************************************************************
|    File Name: CanHooks.h
|  Description: Each Function listed below support a Hook for Enter and Leave 
|               Function. This can be used for monitoring or runtime measurement
|               purpose. Leave following Hook-defines empty if you do not want to
|               use this funtionality
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ------------------------------------
| Bir          Holger Birke              Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               C O R E    R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 2011-03-03 1.00.00 Bir  - Creation
|****************************************************************************/

#if !defined( __AUTOSAR_CAN_HOOKS_H__ )
#define  __AUTOSAR_CAN_HOOKS_H__

/* "Begin" and "End" standard AutoSar API function Can_GetVersionInfo */
#define CanHook_OnBegin_Can_GetVersionInfo()
#define CanHook_OnEnd_Can_GetVersionInfo()

/* "Begin" and "End" none AutoSar API function Can_InitMemory (see TechnicalReference) */
#define CanHook_OnBegin_Can_InitMemory()
#define CanHook_OnEnd_Can_InitMemory()

/* "Begin" and "End" none AutoSar API function Can_InitStruct (see TechnicalReference) */
#define CanHook_OnBegin_Can_InitStruct()
#define CanHook_OnEnd_Can_InitStruct()

/* "Begin" and "End" standard AutoSar API function Can_Init */
#define CanHook_OnBegin_Can_Init()
#define CanHook_OnEnd_Can_Init()

/* "Begin" and "End" standard AutoSar API function Can_InitController */
#define CanHook_OnBegin_Can_InitController()
#define CanHook_OnEnd_Can_InitController()

/* "Begin" and "End" standard AutoSar API function Can_SetControllerMode */
#define CanHook_OnBegin_Can_SetControllerMode()
#define CanHook_OnEnd_Can_SetControllerMode()

/* "Begin" and "End" standard AutoSar API function Can_DisableControllerInterrupts */
#define CanHook_OnBegin_Can_DisableControllerInterrupts()
#define CanHook_OnEnd_Can_DisableControllerInterrupts()

/* "Begin" and "End" standard AutoSar API function Can_EnableControllerInterrupts */
#define CanHook_OnBegin_Can_EnableControllerInterrupts()
#define CanHook_OnEnd_Can_EnableControllerInterrupts()

/* "Begin" and "End" standard AutoSar API function Can_Write */
#define CanHook_OnBegin_Can_Write()
#define CanHook_OnEnd_Can_Write()

/* "Begin" and "End" none AutoSar function CanHL_TxConfirmation (handling sucessfull Tx) */
#define CanHook_OnBegin_CanHL_TxConfirmation()
#define CanHook_OnEnd_CanHL_TxConfirmation()

/* "Begin" and "End" none AutoSar function CanBasicCanMsgReceived (handling BasicCAN reception) */
#define CanHook_OnBegin_CanBasicCanMsgReceived()
#define CanHook_OnEnd_CanBasicCanMsgReceived()

/* "Begin" and "End" none AutoSar function CanFullCanMsgReceived (handling FullCAN reception) */
#define CanHook_OnBegin_CanFullCanMsgReceived()
#define CanHook_OnEnd_CanFullCanMsgReceived()

/* "Begin" and "End" standard AutoSar API function Can_CheckWakeup */
#define CanHook_OnBegin_Can_CheckWakeup()
#define CanHook_OnEnd_Can_CheckWakeup()

/* "Begin" and "End" standard AutoSar API function Can_MainFunction_Write */
#define CanHook_OnBegin_Can_MainFunction_Write()
#define CanHook_OnEnd_Can_MainFunction_Write()

/* "Begin" and "End" standard AutoSar API function Can_MainFunction_Read */
#define CanHook_OnBegin_Can_MainFunction_Read()
#define CanHook_OnEnd_Can_MainFunction_Read()

/* "Begin" and "End" standard AutoSar API function Can_MainFunction_BusOff */
#define CanHook_OnBegin_Can_MainFunction_BusOff()
#define CanHook_OnEnd_Can_MainFunction_BusOff()

/* "Begin" and "End" standard AutoSar API function Can_MainFunction_Wakeup */
#define CanHook_OnBegin_Can_MainFunction_Wakeup()
#define CanHook_OnEnd_Can_MainFunction_Wakeup()

/* "Begin" and "End" standard AutoSar API function Can_MainFunction_Mode */
#define CanHook_OnBegin_Can_MainFunction_Mode()
#define CanHook_OnEnd_Can_MainFunction_Mode()

/* "Begin" and "End" none AutoSar API function Can_CancelTx (see TechnicalReference) */
#define CanHook_OnBegin_Can_CancelTx()
#define CanHook_OnEnd_Can_CancelTx()

/* "Begin" and "End" none AutoSar API function Can_ResetBusOffStart (see TechnicalReference) */
#define CanHook_OnBegin_Can_ResetBusOffStart()
#define CanHook_OnEnd_Can_ResetBusOffStart()

/* "Begin" and "End" none AutoSar API function Can_ResetBusOffEnd (see TechnicalReference) */
#define CanHook_OnBegin_Can_ResetBusOffEnd()
#define CanHook_OnEnd_Can_ResetBusOffEnd()

/* "Begin" and "End" none AutoSar API function Can_GetStatus (see TechnicalReference) */
#define CanHook_OnBegin_Can_GetStatus()
#define CanHook_OnEnd_Can_GetStatus()

/* Notify a State Change out of Context Can_SetControllerMode() */
#define CanHook_OnStateChange_StartSync(oldState, newState)
#define CanHook_OnStateChange_StopSync(oldState, newState)
#define CanHook_OnStateChange_WakeupSync(oldState, newState)
#define CanHook_OnStateChange_SleepSync(oldState, newState)

/* Notify a State Change out of Context Can_SetControllerMode() */
#define CanHook_OnStateChange_StartAsync(oldState, newState)
#define CanHook_OnStateChange_StopAsync(oldState, newState)
#define CanHook_OnStateChange_WakeupAsync(oldState, newState)
#define CanHook_OnStateChange_SleepAsync(oldState, newState)

/* "Begin" and "End" standard AutoSar API function Can_ChangeBaudrate */
#define CanHook_OnBegin_Can_ChangeBaudrate()
#define CanHook_OnEnd_Can_ChangeBaudrate()

/* "Begin" and "End" standard AutoSar API function Can_CheckBaudrate */
#define CanHook_OnBegin_Can_CheckBaudrate()
#define CanHook_OnEnd_Can_CheckBaudrate()


#endif /* __AUTOSAR_CAN_HOOKS_H__ */
