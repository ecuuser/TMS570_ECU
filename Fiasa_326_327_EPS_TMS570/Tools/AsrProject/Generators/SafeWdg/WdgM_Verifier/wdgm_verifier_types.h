/*
** Copyright (C) 2012 TTTech Computertechnik AG. All rights reserved.
** Schoenbrunnerstrasse 7, 1040 Wien, Austria. office@tttech.com
**
** Name
**   wdgm_verifier_types.h
**
** Purpose
**   Data structure used to store data found in ECU Description Files
**
**/

#ifndef _WDGM_VERIFIER_TYPES_H_
#define _WDGM_VERIFIER_TYPES_H_

#include <stdbool.h>
#include "WdgM_Cfg.h"
#define MAX_IDENTIFIER_LENGTH 128


typedef struct {
    int major;
    int minor;
    int patch;
} data_version_t;

typedef struct {
    char source_se [MAX_IDENTIFIER_LENGTH];
    char source_cp [MAX_IDENTIFIER_LENGTH];
    char dest_se   [MAX_IDENTIFIER_LENGTH];
    char dest_cp   [MAX_IDENTIFIER_LENGTH];
} local_transition_t;

typedef struct {
  char   source_se [MAX_IDENTIFIER_LENGTH];
  char   source_cp [MAX_IDENTIFIER_LENGTH];
  char   dest_se   [MAX_IDENTIFIER_LENGTH];
  char   dest_cp   [MAX_IDENTIFIER_LENGTH];
  double dl_min;
  double dl_max;
} dl_supervision_t;

typedef local_transition_t global_transition_t;

typedef const char short_name [MAX_IDENTIFIER_LENGTH];

typedef struct {
    int se_id;
    int cp_id;
    short_name se_name;
    short_name cp_name;
} cp_id_data_t;


typedef struct {
    int id;
    short_name name;
    int cp_cnt;         /* number of checkpoints */
    cp_id_data_t * checkpoint_list;
    int OSApplication;
    void (* WdgM_LocalStateChangeCbk) (WdgM_LocalStatusType);
    bool autosar_3_1_compatibility;
} entity_struct_t;


typedef struct {
    char WdgMTriggerWatchdogRef [MAX_IDENTIFIER_LENGTH];
    int  WdgMTriggerModeId;
    int  WdgMWatchdogMode;
    int  WdgMTriggerWindowStart;
    int  WdgMTriggerConditionValue;
} wdgm_trigger_t;


typedef struct {
    double ticks_per_second;
    double supervision_cycle;
    int    initial_trigger_mode_id;
    wdgm_trigger_t const * triggers;
    int   trigger_cnt;
} wdgm_mode_t;


typedef struct {
  char se [MAX_IDENTIFIER_LENGTH];
  char cp [MAX_IDENTIFIER_LENGTH];
  int  WdgMExpectedAliveIndications;
  int  WdgMMaxMargin;
  int  WdgMMinMargin;
  int  WdgMSupervisionReferenceCycle;
} alive_supervision_t;


typedef struct {
  char se [MAX_IDENTIFIER_LENGTH];
  int  WdgMFailedSupervisionRefCycleTol;
  int  WdgMFailedDeadlineRefCycleTol;
  int  WdgMDeadlineReferenceCycle;
  int  WdgMFailedProgramFlowRefCycleTol;
  int  WdgMProgramFlowReferenceCycle;
  int  WdgMSupervisedEntityInitialMode;
} local_status_param_t;


typedef struct {
    bool version_info_api;
    bool dev_error_detect;
    bool dem_report;
    bool defensive_behavior;
    bool immediate_reset;
    bool off_mode_enabled;
    bool use_os_suspend_interrupt;
    int  timebase_source;
    bool second_reset_path;
    bool tick_overrun_correction;
    bool entity_deactivation_enabled;
    bool state_change_notification;
    bool use_rte;
    bool dem_supervision_report;
    bool firstcycle_alive_counter_reset;
} wdgm_features_t;


typedef struct {
    local_transition_t          const  * local_transitions;
    int                                  local_trans_cnt;
    global_transition_t         const  * global_transitions;
    int                                  global_trans_cnt;
    dl_supervision_t            const  * dl_supervision_list;
    int                                  dl_supervision_cnt;
    alive_supervision_t                * alive_supervision_list;
    int                                  alive_supervision_cnt;
    entity_struct_t             const  * entity_list;
    int                                  entity_cnt;
    WdgM_EntityStatusLType      const ** entity_status_l_array;
    WdgM_EntityStatusGType      const ** entity_status_g_array;
    WdgM_SupervisedEntityIdType        * entity_id_array;
    int                                  WdgMTimebaseSource;
    local_status_param_t        const  * lsp_list;
    int                                  lsp_cnt;
    wdgm_features_t             const  * features;
    wdgm_mode_t                 const  * mode_info;
    void                              (* WdgM_GlobalStateChangeCbk) (WdgM_GlobalStatusType);
    data_version_t              const  * version_info;
} verifier_main_struct_t;

#endif
