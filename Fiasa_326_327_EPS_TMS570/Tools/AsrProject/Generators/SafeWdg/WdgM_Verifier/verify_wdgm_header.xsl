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
# Revision Dates
#    18-Nov-2011 (JDU) [43615] Creation
#    23-Nov-2011 (JDU) [43615] reordering of #define's
#    01-Dec-2011 (JDU) [43615] taking on local transitions
#    02-Dec-2011 (JDU) [43615] can generate local transition info
#    02-Dec-2011 (JDU) [43615] renaming: generating compile-time data
-->

<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:output method="text" omit-xml-declaration="yes" indent="no" />
  <xsl:strip-space elements="*"/>
  <xsl:param name="header-data"/>


  <xsl:template match="/">
/*******************************************************************************
                           wdgm_verifier_input.h
                       GENERATED CODE - DO NOT CHANGE!
                                                                       <xsl:text>{0.16.0}</xsl:text>
<xsl:value-of select="$header-data"/>
*******************************************************************************/

#ifndef _WDGM_VERIFIER_INPUT_H
#define _WDGM_VERIFIER_INPUT_H
    <xsl:call-template name="summary"/>
<xsl:text>
#endif

</xsl:text>
  </xsl:template>


  <xsl:template name="summary">
    <xsl:variable name="ENTITY_CNT"            select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity'])"/>
    <xsl:variable name="CHECKPOINT_CNT"        select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMCheckpoint'])"/>
    <xsl:variable name="mode_id"               select="//*[local-name ()        = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMModeId']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="LOCAL_TRANS_CNT"       select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMLocalTransition'])"/>
    <xsl:variable name="GLOBAL_TRANS_CNT"      select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMProgramFlowSupervision/WdgMGlobalTransition'])"/>
    <xsl:variable name="DL_SUPERVISION_CNT"    select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMDeadlineSupervision'])"/>
    <xsl:variable name="ALIVE_SUPERVISION_CNT" select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMAliveSupervision'])"/>
    <xsl:variable name="LSP_CNT"               select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMLocalStatusParams'])"/>
    <xsl:variable name="MODE_CNT"              select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMTicksPerSecond'])"/>
    <xsl:variable name="TICKS_PER_SECOND"      select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMTicksPerSecond']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="SUPERVISION_CYCLE"     select="//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMSupervisionCycle']/../*[local-name () = 'VALUE']"/>
    <xsl:variable name="TRIGGER_CNT"           select="count (//*[local-name () = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMTrigger'])"/>
#include "wdgm_verifier_types.h"
/* the main structure's name */
#define MAIN_STRUCT_NAME WdgMConfig_Mode<xsl:value-of select="$mode_id"/>

/* Total number of entities */
#define ENTITY_CNT <xsl:value-of select="$ENTITY_CNT"/>

/* Total number of checkpoints: <xsl:value-of select="$CHECKPOINT_CNT"/> */
#define CHECKPOINT_CNT <xsl:value-of select="$CHECKPOINT_CNT"/>

/* Total number of local transitions */
#define LOCAL_TRANS_CNT <xsl:value-of select="$LOCAL_TRANS_CNT"/>

/* Total number of global transitions */
#define GLOBAL_TRANS_CNT <xsl:value-of select="$GLOBAL_TRANS_CNT"/>

/* Total number of Deadline Supervision elements */
#define DL_SUPERVISION_CNT <xsl:value-of select="$DL_SUPERVISION_CNT"/>

/* Total number of Alive Supervision elements */
#define ALIVE_SUPERVISION_CNT <xsl:value-of select="$ALIVE_SUPERVISION_CNT"/>

/* Total number of Local Status Parameter elements */
#define LSP_CNT <xsl:value-of select="$LSP_CNT"/>

/* Number of WdgMMode elements found */
#define WDGM_MODE_CNT <xsl:value-of select="$MODE_CNT"/>

/* Ticks per second */
#define TICKS_PER_SECOND <xsl:value-of select="$TICKS_PER_SECOND"/>

/* WdgMSupervisionCycle */
#define SUPERVISION_CYCLE <xsl:value-of select="$SUPERVISION_CYCLE"/>

/* WdgMTrigger */
#define TRIGGER_CNT <xsl:value-of select="$TRIGGER_CNT"/>

extern verifier_main_struct_t const verifier_info;
  </xsl:template>
</xsl:stylesheet>

