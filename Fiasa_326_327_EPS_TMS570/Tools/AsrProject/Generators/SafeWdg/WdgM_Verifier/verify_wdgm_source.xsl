<?xml version="1.0" encoding="UTF-8"?>

<!--
# Copyright (C) 2011ff TTTech Computertechnik AG. All rights reserved.
# Schoenbrunnerstrasse 7, 1040 Wien, Austria. office@tttech.com
#
#++
# Name
#    verifier.xsl
#
# Purpose
#    Extract information from a ECU description file for validation purposes
#
-->

<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:output method="text" omit-xml-declaration="yes" indent="no" />
  <xsl:strip-space elements="*"/>
  <xsl:param name="header-data"/>


  <xsl:template match="/">
/******************************************************************************
                           wdgm_verifier_info.c
                       GENERATED CODE - DO NOT CHANGE!

                                                                       <xsl:text>{0.27.1}</xsl:text>
<xsl:value-of select="$header-data"/>
*******************************************************************************/

#include "wdgm_verifier_info.h"
#include "wdgm_verifier.h"
    <xsl:call-template name="cbk_prototypes"/>
    <xsl:call-template name="local_transitions_array"/>
    <xsl:call-template name="global_transitions_array"/>
    <xsl:call-template name="checkpoint_arrays"/>
    <xsl:call-template name="entity_array"/>
    <xsl:call-template name="dl_supervision_array"/>
    <xsl:call-template name="alive_supervision"/>
    <xsl:call-template name="lsp_list"/>
    <xsl:call-template name="features"/>
    <xsl:call-template name="triggers"/>
    <xsl:call-template name="mode"/>
    <xsl:call-template name="main_struct"/>
    <xsl:call-template name="main_function"/>
  </xsl:template>


  <xsl:template name="cbk_prototypes">
    <xsl:variable name="global_cbk" select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMGlobalStateChangeCbk']/../*[local-name () = 'VALUE']"/>
    <xsl:if test="$global_cbk != ''">
void <xsl:value-of select="$global_cbk"/> (WdgM_GlobalStatusType);
</xsl:if>

    <xsl:for-each                    select="//*[local-name()  = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity']">
      <xsl:variable name="local_cbk" select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMLocalStateChangeCbk']/../*[local-name () = 'VALUE']"/>
      <xsl:if test="$local_cbk != ''">
<xsl:text>void </xsl:text><xsl:value-of select="$local_cbk"/> (WdgM_LocalStatusType);
      </xsl:if>
    </xsl:for-each>
  </xsl:template>

  <xsl:template name="local_transitions_array">
    <xsl:variable name="LTRANS_CNT" select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMLocalTransition'])"/>
    <xsl:if test="$LTRANS_CNT &gt; 0">
/****
Found <xsl:value-of select="$LTRANS_CNT"/> local transition(s)
****/
local_transition_t local_transitions [LOCAL_TRANS_CNT]<xsl:text> =</xsl:text>
      <xsl:for-each select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMLocalTransition']">
        <xsl:variable name="src"  select="substring-after (..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMLocalTransition/WdgMLocalTransitionSourceRef']/../*[local-name () = 'VALUE-REF'], 'WdgMGeneral/')"/>
        <xsl:variable name="dest" select="substring-after (..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMLocalTransition/WdgMLocalTransitionDestRef']/../*[local-name () = 'VALUE-REF'], 'WdgMGeneral/')"/>
        <xsl:variable name="src_se"  select="substring-before ($src, '/')"/>
        <xsl:variable name="src_cp"  select="substring-after  ($src, '/')"/>
        <xsl:variable name="dest_se" select="substring-before ($dest, '/')"/>
        <xsl:variable name="dest_cp" select="substring-after  ($dest, '/')"/>
        <xsl:choose>
          <xsl:when test="position () = 1">
{ { "<xsl:value-of select="$src_se"/>"        /* source entity */ </xsl:when> <xsl:otherwise>
, { "<xsl:value-of select="$src_se"/>"        /* source entity */ </xsl:otherwise>
        </xsl:choose><xsl:text>
  , </xsl:text>"<xsl:value-of select="$src_cp"/>"    /* source checkpoint */

  , "<xsl:value-of select="$dest_se"/>"        /* destination entity */
  , "<xsl:value-of select="$dest_cp"/>"        /* destination checkpoint */
  }   /* [<xsl:value-of select="position () - 1"/>] */
</xsl:for-each><xsl:text>};

</xsl:text>
    </xsl:if>

  </xsl:template>




  <xsl:template name="global_transitions_array">
    <xsl:variable name="GTRANS_CNT" select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMProgramFlowSupervision/WdgMGlobalTransition'])"/>
    <xsl:if test="$GTRANS_CNT &gt; 0">
/****
Found <xsl:value-of select="$GTRANS_CNT"/> global transition(s)
****/
global_transition_t global_transitions [GLOBAL_TRANS_CNT]<xsl:text> =</xsl:text>
      <xsl:for-each select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMProgramFlowSupervision/WdgMGlobalTransition']">
        <xsl:variable name="src"  select="substring-after (..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMProgramFlowSupervision/WdgMGlobalTransition/WdgMGlobalTransitionSourceRef']/../*[local-name () = 'VALUE-REF'], 'WdgMGeneral/')"/>
        <xsl:variable name="dest" select="substring-after (..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMProgramFlowSupervision/WdgMGlobalTransition/WdgMGlobalTransitionDestRef']/../*[local-name () = 'VALUE-REF'], 'WdgMGeneral/')"/>
        <xsl:variable name="src_se"  select="substring-before ($src, '/')"/>
        <xsl:variable name="src_cp"  select="substring-after  ($src, '/')"/>
        <xsl:variable name="dest_se" select="substring-before ($dest, '/')"/>
        <xsl:variable name="dest_cp" select="substring-after  ($dest, '/')"/>
        <xsl:choose>
          <xsl:when test="position () = 1">
{ { "<xsl:value-of select="$src_se"/>"        /* source entity */ </xsl:when> <xsl:otherwise>
, { "<xsl:value-of select="$src_se"/>"        /* source entity */ </xsl:otherwise>
        </xsl:choose><xsl:text>
  , </xsl:text>"<xsl:value-of select="$src_cp"/>"    /* source checkpoint */

  , "<xsl:value-of select="$dest_se"/>"        /* destination entity */
  , "<xsl:value-of select="$dest_cp"/>"        /* destination checkpoint */
  }   /* [<xsl:value-of select="position () - 1"/>] */
</xsl:for-each><xsl:text>};

</xsl:text>
    </xsl:if>

  </xsl:template>




  <xsl:template name="dl_supervision_array">
    <xsl:variable name="DL_SUPERVISION_CNT" select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMDeadlineSupervision'])"/>
    <xsl:if test="$DL_SUPERVISION_CNT &gt; 0">
/****
Found <xsl:value-of select="$DL_SUPERVISION_CNT"/> deadline supervision elements.
****/
dl_supervision_t deadline_supervisions [DL_SUPERVISION_CNT]<xsl:text> =</xsl:text>
      <xsl:for-each select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMDeadlineSupervision']">
        <xsl:variable name="src"  select="substring-after (..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMDeadlineSupervision/WdgMDeadlineStartRef']/../*[local-name () = 'VALUE-REF'], 'WdgMGeneral/')"/>
        <xsl:variable name="dest" select="substring-after (..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMDeadlineSupervision/WdgMDeadlineStopRef']/../*[local-name () = 'VALUE-REF'], 'WdgMGeneral/')"/>
        <xsl:variable name="src_se"  select="substring-before ($src, '/')"/>
        <xsl:variable name="src_cp"  select="substring-after  ($src, '/')"/>
        <xsl:variable name="dest_se" select="substring-before ($dest, '/')"/>
        <xsl:variable name="dest_cp" select="substring-after  ($dest, '/')"/>
        <xsl:variable name="dl_min"  select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMDeadlineSupervision/WdgMDeadlineMin']/../*[local-name () = 'VALUE']"/>
        <xsl:variable name="dl_max"  select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMDeadlineSupervision/WdgMDeadlineMax']/../*[local-name () = 'VALUE']"/>
        <xsl:choose>
          <xsl:when test="position () = 1">
{ { "<xsl:value-of select="$src_se"/>"        /* source entity */ </xsl:when> <xsl:otherwise>
, { "<xsl:value-of select="$src_se"/>"        /* source entity */ </xsl:otherwise>
        </xsl:choose><xsl:text>
  , </xsl:text>"<xsl:value-of select="$src_cp"/>"    /* source checkpoint */

  , "<xsl:value-of select="$dest_se"/>"        /* destination entity */
  , "<xsl:value-of select="$dest_cp"/>"        /* destination checkpoint */

  , <xsl:value-of select="$dl_min"/>           /* minimum deadline */
  , <xsl:value-of select="$dl_max"/>           /* maximum deadline */
  }   /* [<xsl:value-of select="position () - 1"/>] */
</xsl:for-each><xsl:text>};

</xsl:text>
    </xsl:if>

  </xsl:template>




  <xsl:template name="checkpoint_arrays">
    <xsl:variable name="ENTITY_CNT" select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMSupervisedEntityId']/..)"/>
    <xsl:if test="$ENTITY_CNT > 0">
      <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMSupervisedEntityId']/..">
        <xsl:variable name="entityID"   select="./*[local-name() = 'VALUE']"/>
        <xsl:variable name="entityName" select="../../*[local-name() = 'SHORT-NAME']"/>
        <xsl:variable name="CHECKPOINT_CNT" select="count (../..//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMCheckpoint/WdgMCheckpointId']/..)"/>
        <xsl:if test="$CHECKPOINT_CNT > 0">
/****
Found <xsl:value-of select="$CHECKPOINT_CNT"/> checkpoint(s) in supervised entity `<xsl:value-of select="$entityName"/>`
****/
cp_id_data_t se_<xsl:value-of select="$entityName"/>_cp_list [<xsl:value-of select="$CHECKPOINT_CNT"/>]<xsl:text> =</xsl:text>
          <xsl:for-each select="../..//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMCheckpoint/WdgMCheckpointId']/..">
            <xsl:variable name="checkpointID"   select="./*[local-name() = 'VALUE']"/>
            <xsl:variable name="checkpointName" select="../../*[local-name() = 'SHORT-NAME']"/>
          <xsl:choose>
            <xsl:when test="position () = 1">
{ { <xsl:value-of select="$entityID"/>        /* supervised entity's ID */ </xsl:when> <xsl:otherwise>
, { <xsl:value-of select="$entityID"/>        /* supervised entity's ID */ </xsl:otherwise>
        </xsl:choose><xsl:text>
  , </xsl:text><xsl:value-of select="$checkpointID"/><xsl:text>     /* checkpoint's ID */
  , "</xsl:text><xsl:value-of select="$entityName"/>"<xsl:text>     /* entity name */
  , "</xsl:text><xsl:value-of select="$checkpointName"/>"     /* checkpoint name */
  }   /* [<xsl:value-of select="position () - 1"/>] */
</xsl:for-each><xsl:text>};

</xsl:text>
        </xsl:if>
      </xsl:for-each>
    </xsl:if>
  </xsl:template>




  <xsl:template name="entity_array">
    <xsl:variable name="ENTITY_CNT" select="count (//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMSupervisedEntityId']/..)"/>
    <xsl:if test="$ENTITY_CNT > 0">
/****
Found <xsl:value-of select="$ENTITY_CNT"/> supervised entities.
****/
entity_struct_t entities [ENTITY_CNT]<xsl:text> =</xsl:text>
      <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMSupervisedEntityId']/..">
        <xsl:variable name="entityID"       select="./*[local-name() = 'VALUE']"/>
        <xsl:variable name="entityName"     select="../../*[local-name() = 'SHORT-NAME']"/>
        <xsl:variable name="CHECKPOINT_CNT" select="count (../..//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMCheckpoint/WdgMCheckpointId']/..)"/>
        <xsl:variable name="os_application" select="..//*[local-name () = 'DEFINITION-REF'          and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/OSApplication']/../*[local-name () = 'VALUE']"/>
        <xsl:variable name="cbk" select="..//*[local-name () = 'DEFINITION-REF'                     and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMLocalStateChangeCbk']/../*[local-name () = 'VALUE']"/>
        <xsl:variable name="api" select="..//*[local-name () = 'DEFINITION-REF'                     and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMSupportedAutosarAPI']/../*[local-name () = 'VALUE']"/>
          <xsl:choose>
            <xsl:when test="position () = 1">
{ { <xsl:value-of select="$entityID"/>        /* entity_id */ </xsl:when> <xsl:otherwise>
, { <xsl:value-of select="$entityID"/>        /* entity_id */ </xsl:otherwise>
        </xsl:choose><xsl:text>
  , "</xsl:text><xsl:value-of select="$entityName"/>"      /* entity name */
  , <xsl:value-of select="$CHECKPOINT_CNT"/><xsl:text>     /* number of checkpoints */</xsl:text>
          <xsl:choose>
            <xsl:when test="$CHECKPOINT_CNT > 0">
  , se_<xsl:value-of select="$entityName"/>_cp_list<xsl:text>     /* this entity's checkpoints */</xsl:text></xsl:when>
            <xsl:otherwise>
  , NULL_PTR                         /* entity has no checkpoints */</xsl:otherwise>
          </xsl:choose>
  , WDGM_INVALID_OSAPPLICATION   /* OSApplication */<xsl:choose><xsl:when test="$cbk != ''">
  , &amp;<xsl:value-of select="$cbk"/>    /* WdgMLocalStateChangeCbk */</xsl:when><xsl:otherwise>
  , NULL_PTR  /* supervised entity has no callback */ </xsl:otherwise></xsl:choose>
  , <xsl:choose><xsl:when test="$api='API_3_1'">true</xsl:when><xsl:otherwise>false</xsl:otherwise></xsl:choose>    /* autosar_3_1_x_compatibility */
  }   /* [<xsl:value-of select="position () - 1"/>] */
</xsl:for-each><xsl:text>};
</xsl:text>
    </xsl:if>
  </xsl:template>


  <xsl:template name="alive_supervision">
    <xsl:variable name="ALIVE_SUPERVISION_CNT" select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMAliveSupervision'])"/>
    <xsl:if test="$ALIVE_SUPERVISION_CNT &gt; 0">
/****
Found <xsl:value-of select="$ALIVE_SUPERVISION_CNT"/> alive supervisions
****/
alive_supervision_t alive_supervisions [ALIVE_SUPERVISION_CNT]<xsl:text> =</xsl:text>
      <xsl:for-each                      select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMAliveSupervision']">
        <xsl:variable name="cp_ref"      select="substring-after (..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMAliveSupervision/WdgMAliveSupervisionCheckpointRef']/../*[local-name () = 'VALUE-REF'], 'WdgMGeneral/')"/>
        <xsl:variable name="se"          select="substring-before ($cp_ref, '/')"/>
        <xsl:variable name="cp"          select="substring-after  ($cp_ref, '/')"/>
        <xsl:variable name="indications" select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMAliveSupervision/WdgMExpectedAliveIndications']/../*[local-name () = 'VALUE']"/>
        <xsl:variable name="max_margin"  select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMAliveSupervision/WdgMMaxMargin']/../*[local-name () = 'VALUE']"/>
        <xsl:variable name="min_margin"  select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMAliveSupervision/WdgMMinMargin']/../*[local-name () = 'VALUE']"/>
        <xsl:variable name="ref_cycle"   select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMAliveSupervision/WdgMSupervisionReferenceCycle']/../*[local-name () = 'VALUE']"/>
        <xsl:choose>
          <xsl:when test="position () = 1">
{ { "<xsl:value-of select="$se"/>"        /* source entity */ </xsl:when> <xsl:otherwise>
, { "<xsl:value-of select="$se"/>"        /* source entity */ </xsl:otherwise>
        </xsl:choose><xsl:text>
  , </xsl:text>"<xsl:value-of select="$cp"/>"    /* source checkpoint */
  , <xsl:value-of select="$indications"/>        /* alive indications */
  , <xsl:value-of select="$max_margin"/>         /* maximum margin */
  , <xsl:value-of select="$min_margin"/>         /* minimum margin */
  , <xsl:value-of select="$ref_cycle"/>         /* supervision reference cycle */
  }   /* [<xsl:value-of select="position () - 1"/>] */
</xsl:for-each><xsl:text>};

</xsl:text>
    </xsl:if>
  </xsl:template>


  <xsl:template name="lsp_list">
    <xsl:variable name="LSP_CNT" select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMLocalStatusParams'])"/>
    <xsl:if test="$LSP_CNT &gt; 0">
/****
Found <xsl:value-of select="$LSP_CNT"/> `WdgMLocalStatusParams` elements
****/
local_status_param_t local_status_param_list [LSP_CNT]<xsl:text> =</xsl:text>
      <xsl:for-each select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMLocalStatusParams']" >
        <xsl:variable name="se"        select="substring-after (..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMLocalStatusParams/WdgMLocalStatusSupervisedEntityRef']/../*[local-name () = 'VALUE-REF'], 'WdgMGeneral/')"/>
        <xsl:variable name="fsrc_tol"  select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMLocalStatusParams/WdgMFailedSupervisionRefCycleTol']/../*[local-name () = 'VALUE']"/>
        <xsl:variable name="fdlrc_tol" select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMLocalStatusParams/WdgMFailedDeadlineRefCycleTol']/../*[local-name () = 'VALUE']"/>
        <xsl:variable name="dlr_cycle" select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMLocalStatusParams/WdgMDeadlineReferenceCycle']/../*[local-name () = 'VALUE']"/>
        <xsl:variable name="fpfrc_tol" select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMLocalStatusParams/WdgMFailedProgramFlowRefCycleTol']/../*[local-name () = 'VALUE']"/>
        <xsl:variable name="pfr_cycle" select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMLocalStatusParams/WdgMProgramFlowReferenceCycle']/../*[local-name () = 'VALUE']"/>
        <xsl:variable name="init_mode" select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMLocalStatusParams/WdgMSupervisedEntityInitialMode']/../*[local-name () = 'VALUE']"/>
        <xsl:choose>
          <xsl:when test="position () = 1">
{ { "<xsl:value-of select="$se"/>"        /* se */ </xsl:when> <xsl:otherwise>
, { "<xsl:value-of select="$se"/>"        /* se */ </xsl:otherwise>
        </xsl:choose>
  , <xsl:value-of select="$fsrc_tol"/>  /* WdgMFailedSupervisionRefCycleTol */
  , <xsl:value-of select="$fdlrc_tol"/>  /* WdgMFailedDeadlineRefCycleTol */
  , <xsl:value-of select="$dlr_cycle"/>  /* WdgMDeadlineReferenceCycle */
  , <xsl:value-of select="$fpfrc_tol"/>  /* WdgMFailedProgramFlowRefCycleTol */
  , <xsl:value-of select="$pfr_cycle"/>  /* WdgMFailedProgramFlowRefCycleTol */
  , <xsl:value-of select="$init_mode"/>  /* WdgMSupervisedEntityInitialMode */
  }   /* [<xsl:value-of select="position () - 1"/>] */
</xsl:for-each><xsl:text>};

</xsl:text>
    </xsl:if>
  </xsl:template>


  <xsl:template name="features">
    <xsl:variable name="version_info_api"               select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMVersionInfoApi']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="dev_error_detect"               select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMDevErrorDetect']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="dem_report"                     select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMDemReport']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="defensive_behavior"             select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMDefensiveBehavior']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="immediate_reset"                select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMImmediateReset']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="off_mode_enabled"               select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMOffModeEnabled']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="use_os_suspend_interrupt"       select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMUseOsSuspendInterrupt']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="timebase_source"                select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMTimebaseSource']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="second_reset_path"              select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSecondResetPath']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="tick_overrun_correction"        select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMTickOverrunCorrection']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="entity_deactivation_enabled"    select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMEntityDeactivationEnabled']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="state_change_notification"      select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMStateChangeNotification']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="use_rte"                        select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMUseRte']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="dem_supervision_report"         select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMDemSupervisionReport']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="firstcycle_alive_counter_reset" select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMFirstCycleAliveCounterReset']/../*[local-name () = 'VALUE']"/>
wdgm_features_t const features =
{ <xsl:value-of select="$version_info_api"/>  /* version_info_api */
, <xsl:value-of select="$dev_error_detect"/>  /* dev_error_detect */
, <xsl:value-of select="$dem_report"/>  /* dem_report */
, <xsl:value-of select="$defensive_behavior"/>  /* defensive_behavior */
, <xsl:value-of select="$immediate_reset"/>  /* immediate_reset */
, <xsl:value-of select="$off_mode_enabled"/>  /* off_mode_enabled */
, <xsl:value-of select="$use_os_suspend_interrupt"/>  /* use_os_suspend_interrupt */
, <xsl:value-of select="$timebase_source"/>  /* timebase_source */
, <xsl:value-of select="$second_reset_path"/>  /* second_reset_path */
, <xsl:value-of select="$tick_overrun_correction"/>  /* tick_overrun_correction */
, <xsl:value-of select="$entity_deactivation_enabled"/>  /* entity_deactivation_enabled */
, <xsl:value-of select="$state_change_notification"/>  /* state_change_notification */
, <xsl:value-of select="$use_rte"/>  /* use_rte */
, <xsl:value-of select="$dem_supervision_report"/>  /* dem_supervision_report */
, <xsl:value-of select="$firstcycle_alive_counter_reset"/>  /* firstcycle_alive_counter_reset */
};

  </xsl:template>


  <xsl:template name="triggers">
    <xsl:variable name="TRIGGER_CNT" select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMTrigger'])"/>
      <xsl:if test="$TRIGGER_CNT > 0">
/****
Found <xsl:value-of select="$TRIGGER_CNT"/> `WdgMTrigger` elements
****/
wdgm_trigger_t const triggers [TRIGGER_CNT]<xsl:text> =</xsl:text>
        <xsl:for-each select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMTrigger']">
          <xsl:variable name="reference"       select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMTrigger/WdgMTriggerWatchdogRef']/../*[local-name () = 'VALUE-REF']"/>
          <xsl:variable name="watchdog"        select="substring-after ($reference, 'WdgMGeneral/')"/>
          <xsl:variable name="trigger_mode_id" select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMTrigger/WdgMTriggerModeId']/../*[local-name () = 'VALUE']"/>
          <xsl:variable name="wdg_mode"        select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMTrigger/WdgMWatchdogMode']/../*[local-name () = 'VALUE']"/>
          <xsl:variable name="_ws"             select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMTrigger/WdgMTriggerWindowStart']/../*[local-name () = 'VALUE']"/>
          <xsl:variable name="_cv"              select="..//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMTrigger/WdgMTriggerConditionValue']/../*[local-name () = 'VALUE']"/>
          <xsl:variable name="window_start">
              <xsl:choose>
                  <xsl:when test="$_ws != ''"><xsl:value-of select="$_ws"/></xsl:when>
                  <xsl:otherwise>0</xsl:otherwise>
              </xsl:choose>
          </xsl:variable>
          <xsl:variable name="cond_value">
              <xsl:choose>
                  <xsl:when test="$_cv != ''"><xsl:value-of select="$_cv"/></xsl:when>
                  <xsl:otherwise>0</xsl:otherwise>
              </xsl:choose>
          </xsl:variable>

          <xsl:choose>
            <xsl:when test="position () = 1">
{ { "<xsl:value-of select="$watchdog"/>"    /* WdgMTriggerWatchdogRef */ </xsl:when><xsl:otherwise>
, { "<xsl:value-of select="$watchdog"/>"    /* WdgMTriggerWatchdogRef */ </xsl:otherwise></xsl:choose>
  , <xsl:value-of  select="$trigger_mode_id"/>    /* WdgMTriggerModeId */
  , <xsl:value-of  select="$wdg_mode"/>    /* WdgMWatchdogMode */
  , <xsl:value-of  select="$window_start"/>    /* WdgMTriggerWindowStart */
  , <xsl:value-of  select="$cond_value"/>    /* WdgMTriggerConditionValue */
  }   /* [<xsl:value-of select="position () - 1"/>]  */
</xsl:for-each><xsl:text>};

</xsl:text>
      </xsl:if>

  </xsl:template>


  <xsl:template name="mode">
    <xsl:variable name="TRIGGER_CNT"          select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMTrigger'])"/>
    <xsl:variable name="init_trigger_mode_id" select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMInitialTriggerModeId']/../*[local-name () = 'VALUE']"/>
wdgm_mode_t mode_info =
{ TICKS_PER_SECOND    /* WdgMTicksPerSecond */
, SUPERVISION_CYCLE   /* WdgMSupervisionCycle */
, <xsl:value-of select="$init_trigger_mode_id"/>    /* WdgMInitialTriggerModeId */
, <xsl:choose><xsl:when test="$TRIGGER_CNT > 0">triggers</xsl:when><xsl:otherwise>NULL_PTR</xsl:otherwise></xsl:choose>
, TRIGGER_CNT
};

  </xsl:template>

  <xsl:template name="main_struct">
    <xsl:variable name="LTRANS_CNT"            select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMLocalTransition'])"/>
    <xsl:variable name="GTRANS_CNT"            select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMProgramFlowSupervision/WdgMGlobalTransition'])"/>
    <xsl:variable name="DL_SUPERVISION_CNT"    select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMDeadlineSupervision'])"/>
    <xsl:variable name="ALIVE_SUPERVISION_CNT" select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMAliveSupervision'])"/>
    <xsl:variable name="ENTITY_CNT"            select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMSupervisedEntityId']/..)"/>
    <xsl:variable name="TIMEBASE_SOURCE"       select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMTimebaseSource']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="GLOBAL_CBK"            select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMGlobalStateChangeCbk']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="LSP_CNT"               select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMLocalStatusParams'])"/>
<xsl:text>
/****
-------------------------------------------------------------------------------
BEGIN OF for-internal-use-only auxiliary data Structures
****/

data_version_t version_info =
{ 1   /* major */
, 0   /* minor */
, 0   /* patch */
};


</xsl:text>
<xsl:choose>
  <xsl:when test="$ENTITY_CNT > 0">
WdgM_EntityStatusLType      const * unique_entity_status_l_array [ENTITY_CNT];
WdgM_EntityStatusGType      const * unique_entity_status_g_array [ENTITY_CNT];
WdgM_SupervisedEntityIdType         unique_entity_id_array       [ENTITY_CNT];</xsl:when>
</xsl:choose>


verifier_main_struct_t const verifier_info<xsl:text> =</xsl:text>
    <xsl:choose>
      <xsl:when test="$LTRANS_CNT > 0">
{ local_transitions</xsl:when><xsl:otherwise>
{ NULL_PTR    /* no local transitions found */</xsl:otherwise>
    </xsl:choose>
    <xsl:text>
, LOCAL_TRANS_CNT
, </xsl:text>
    <xsl:choose>
      <xsl:when test="$GTRANS_CNT > 0">global_transitions</xsl:when>
      <xsl:otherwise>NULL_PTR    /* no global transitions found */</xsl:otherwise>
    </xsl:choose>
    <xsl:text>
, GLOBAL_TRANS_CNT
, </xsl:text>
    <xsl:choose>
      <xsl:when test="$DL_SUPERVISION_CNT > 0">deadline_supervisions</xsl:when>
      <xsl:otherwise>NULL_PTR    /* no deadline supervisions found */</xsl:otherwise>
    </xsl:choose>
    <xsl:text>
, DL_SUPERVISION_CNT
, </xsl:text>
    <xsl:choose>
      <xsl:when test="$ALIVE_SUPERVISION_CNT > 0">alive_supervisions</xsl:when>
      <xsl:otherwise>NULL_PTR    /* no alive supervisions found */</xsl:otherwise>
    </xsl:choose>
    <xsl:text>
, ALIVE_SUPERVISION_CNT
, </xsl:text>
    <xsl:choose>
      <xsl:when test="$ENTITY_CNT > 0">entities</xsl:when>
      <xsl:otherwise>NULL_PTR    /* no supervised entities found found */</xsl:otherwise>
    </xsl:choose><xsl:text>
, ENTITY_CNT
, </xsl:text>
    <xsl:choose>
      <xsl:when test="$ENTITY_CNT > 0">unique_entity_status_l_array</xsl:when>
      <xsl:otherwise>NULL_PTR</xsl:otherwise>
    </xsl:choose><xsl:text>
, </xsl:text>
    <xsl:choose>
      <xsl:when test="$ENTITY_CNT > 0">unique_entity_status_g_array</xsl:when>
      <xsl:otherwise>NULL_PTR</xsl:otherwise>
    </xsl:choose><xsl:text>
, </xsl:text>
    <xsl:choose>
      <xsl:when test="$ENTITY_CNT > 0">unique_entity_id_array</xsl:when>
      <xsl:otherwise>NULL_PTR</xsl:otherwise>
    </xsl:choose>
, <xsl:value-of select="$TIMEBASE_SOURCE"/><xsl:text>
, </xsl:text>
    <xsl:choose>
      <xsl:when test="$LSP_CNT > 0">local_status_param_list</xsl:when>
      <xsl:otherwise>NULL_PTR</xsl:otherwise>
    </xsl:choose>
, LSP_CNT
, &amp;features
, &amp;mode_info
, <xsl:choose>
    <xsl:when test="$GLOBAL_CBK != ''">&amp;<xsl:value-of select="$GLOBAL_CBK"/></xsl:when>
    <xsl:otherwise>NULL_PTR</xsl:otherwise></xsl:choose>
, &amp;version_info
};
<xsl:text>

/****
END OF for-internal-use-only auxiliary data Structures
-------------------------------------------------------------------------------
****/
</xsl:text>
  </xsl:template>


  <xsl:template name="main_function">
    <xsl:variable name="mode_id" select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMModeId']/../*[local-name () = 'VALUE']"/>
    <xsl:text>
extern const WdgM_ConfigType WdgMConfig_Mode</xsl:text><xsl:value-of select="$mode_id"/><xsl:text>;

int main (int argc, char *argv [])
{
    return verify (&amp;WdgMConfig_Mode0, &amp;verifier_info);
}
</xsl:text>
  </xsl:template>
</xsl:stylesheet>

