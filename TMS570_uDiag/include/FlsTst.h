/**********************************************************************
*
*	Header %name:	FlsTst.h %
*	Instance:		sag_EPS_1
*	Description:	
*	%created_by:	czgng4 %
*	%date_created:	Tue Nov 27 12:28:09 2012 %
*
**********************************************************************/
#ifndef _FLSTST_H
#define _FLSTST_H

#include "Std_Types.h"	/* [FlsTst003] */
#include "FlsTst_Cfg.h" /* [FlsTst003] */


/* AUTOSAR Specifcation Release Version*/
#define FLSTST_AR_RELEASE_MAJOR_VERSION		4U
#define FLSTST_AR_RELEASE_MINOR_VERSION		0U

#define FlsTst_GetVersionInfo( versioninfo )	*versioninfo = FlsTst_VersionInfo;

#define D_CRCRESIDUECONSTANT_CNT_U64	0x800000000000000DULL /* TODO: Confirm the residue value before use */

/* DET Error Codes */
#define FLSTST_E_STATE_FAILURE			0x01U
#define FLSTST_E_PARAM_INVALID			0x02U
#define FLSTST_E_UNINIT					0x03U
#define FLSTST_E_ALREADY_INITIALIZED	0x04U
#define FLSTST_E_PARAM_CONFIG			0x05U
#define FLSTST_E_PARAM_POINTER			0x06U

/* Type definitions */
typedef enum {
	FLSTST_RESULT_NOT_TESTED = 0x00,
	FLSTST_RESULT_OK,
	FLSTST_RESULT_NOT_OK
}FlsTst_TestResultType;

typedef enum {
	FLSTST_UNINIT = 0x00,
	FLSTST_INIT = 0x01,
	FLSTST_RUNNING = 0x02,
	FLSTST_ABORTED = 0x03,
	FLSTST_SUSPENDED = 0x04
}FlsTst_StateType;

typedef enum {
	FLSTST_SLFTSTUNINIT = 0x00,
	FLSTST_SLFTSTRUNNING = 0x01,
	FLSTST_SLFTSTPASS = 0x02,
	FLSTST_SLFTSTFAIL = 0x03
}FlsTst_SelfTestStateType; /* Nexteer extension to the AUTOSAR driver */

typedef enum {
	FLSTST_NOT_TESTED = 0x00,
	FLSTST_OK = 0x01,
	FLSTST_NOT_OK = 0x02
}FlsTst_TestResultFgndType;

typedef struct {
	uint32					interval;
	FlsTst_TestResultType	result;
}FlsTst_TestResultBgndType;

typedef uint16	FlsTst_BlockIdFgndType;

typedef struct{
	/* Implementation Specific: blocksfailed is intended to be a bitfield of blocks in which failures were detected */
	uint32	blocksfailed;
}FlsTst_ErrorDetailsType;

typedef struct {
	/* Implementation Specific */
	uint32	interval;
	uint64	signature;
}FlsTst_TestSignatureFgndType;

typedef struct {
	uint32	interval;
	uint64	signature;	/* uint64 is a deviation to the AUTOSAR specification, which is required to use the 64 bit hardware CRC */
}FlsTst_TestSignatureBgndType;



/* Mainfunction definitions */
extern void FlsTst_MainFunction( void );

/* Notifiction definitions */
extern void FlsTst_TestCompleted( void );

/* API definitions */
extern void FlsTst_Init( const FlsTst_ConfigType* ConfigPtr );
extern void FlsTst_DeInit( void );
extern Std_ReturnType FlsTst_StartFgnd( FlsTst_BlockIdFgndType FgndBlockId );
extern FlsTst_TestResultBgndType FlsTst_GetTestResultBgnd( void );
extern FlsTst_TestResultFgndType FlsTst_GetTestResultFgnd( void );
extern void FlsTst_Abort( void );

#if (STD_ON == FLSTST_SUSPEND_RESUME_API)
extern void FlsTst_Suspend( void );
extern void FlsTst_Resume( void );
#endif

extern FlsTst_StateType FlsTst_GetCurrentState( void );
extern FlsTst_TestResultBgndType FlsTst_GetTestResultBgnd( void );
extern FlsTst_TestResultFgndType FlsTst_GetTestResultFgnd( void );
extern FlsTst_TestSignatureBgndType FlsTst_GetTestSignatureBgnd( void );
extern FlsTst_TestSignatureFgndType FlsTst_GetTestSignatureFgnd( void );
extern FlsTst_ErrorDetailsType FlsTst_GetErrorDetails( void );
extern Std_ReturnType FlsTst_TestEcc( void );

/* FlsTst SWC Private Definitions */
#ifdef FLSTST_PRIVATEDEFS
/* Private Module Variables */
extern VAR(FlsTst_SelfTestStateType, AUTOMATIC) FlsTst_SelfTestState;
extern VAR(FlsTst_StateType, AUTOMATIC) FlsTst_State;
extern VAR(FlsTst_ErrorDetailsType, AUTOMATIC) FlsTst_ErrorDetails;
extern VAR(uint16, AUTOMATIC) FlsTst_BgndTestBlock;
extern P2CONST(FlsTst_ConfigType, AUTOMATIC, AUTOMATIC) FlsTst_Config;
extern VAR(FlsTst_TestResultType, AUTOMATIC) FlsTst_CurrBgndTestResult;

/* Private Functions */
extern FUNC(void, AUTOMATIC) SetupBgndBlk( FlsTst_MemBlockType config );

#undef FLSTST_PRIVATEDEFS
#endif

#endif
