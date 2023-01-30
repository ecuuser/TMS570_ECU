/*** Generated code, do not change!                                        ***/
/*** Module WdgIf_Lcfg, written by Wdg_If_Cfg_Gen 2.0.0 (build 204883) on  ***/
/*** Fri 05-Jul-2013 13:40:18                                              ***/

#include "Wdg_TMS570LS3x_Lcfg.h"
#include "WdgIf_Lcfg.h"

#define WDGIF_START_SEC_CONST_UNSPECIFIED 
#include "MemMap.h"
const WdgIf_InterfaceFunctionsType tms570ls3x_functions =
  { Wdg_TMS570LS3x_SetMode /* Wdg_SetMode                                    */
  , Wdg_TMS570LS3x_SetTriggerWindow /* Wdg_SetTriggerWindow                  */
  };

const WdgIf_InterfaceFunctionsPerWdgDeviceType WdgIf_FunctionsPerWdg [WDGIF_NUMBER_OF_WATCHDOGS] =
  { { &tms570ls3x_functions /* Watchdog */ /* WdgFunctions                   */
    , 0 /* WdgInstance                                                       */
    } /* [0]                                                               */
  };

const WdgIf_InterfaceType WdgIf_Interface =
  { WDGIF_NUMBER_OF_WATCHDOGS /* NumOfWdgs                                   */
  , WdgIf_FunctionsPerWdg /* WdgFunctionsPerDevice                           */
  , Wdg_TMS570LS3x_GetTickCounter /* Wdg_GetTickCounter                      */
  };
#define WDGIF_STOP_SEC_CONST_UNSPECIFIED 
#include "MemMap.h"
