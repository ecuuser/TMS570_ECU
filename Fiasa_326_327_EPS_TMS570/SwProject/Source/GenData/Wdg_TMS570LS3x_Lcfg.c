/*** Generated code, do not change!                                        ***/
/*** Module Wdg_TMS570LS3x_Lcfg, written by Wdg_Drv_Cfg_Gen_TMS570LS3X     ***/
/*** 2.0.2 (build 205864) on Fri 05-Jul-2013 13:40:17                      ***/

#include "Wdg_TMS570LS3x_Lcfg.h"

#define WDG_START_SEC_CONST_UNSPECIFIED 
#include "MemMap.h"
const Wdg_BasicConfigurationType wdg_TMS570LS3x_config_basic =
  { WDGIF_SLOW_MODE /* InitialMode                                           */
  , 6 /* InitialTimeout_ms                                                   */
  , 0 /* InitialWindowStart_ms                                               */
  , 419 /* SlowModeMax_ms                                                      */
  , 419 /* FastModeMax_ms                                                      */
  , 2 /* WdgConfigMajorVersion                                                 */
  , 0 /* WdgConfigMinorVersion                                                 */
  };

const Wdg_TMS570LS3x_ConfigType wdg_tms570ls3x_config =
  { &wdg_TMS570LS3x_config_basic /* BasicCfgPtr                              */
  , 80000 /* RTICLK_khz                                                      */
  , 1000000 /* TickFreq_hz                                                   */
  , 2081273 + WDGIF_SLOW_MODE /* ConfigChecksum                                */
  };
#define WDG_STOP_SEC_CONST_UNSPECIFIED 
#include "MemMap.h"
