<?xml version="1.0" encoding="UTF-8"?>
<!--
***********************************************************************************************************************
*  COPYRIGHT
*  ********************************************************************************************************************
*  Copyright (c) 2006-2009 by Vector Informatik GmbH, all rights reserved
*
*                This software is copyright protected and proprietary to Vector Informatik GmbH.
*                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
*                 All other rights remain with Vector Informatik GmbH.
***********************************************************************************************************************


***********************************************************************************************************************
*  FILE DESCRIPTION
*  ********************************************************************************************************************
*         File:  SWC_WdgM.xsl
*    Component:  SysService_AsrWdM
*      Version:  GroupVersion="2.1.x"
*       Module:  WdgM
*
*   Description: -
***********************************************************************************************************************


***********************************************************************************************************************
*  AUTHOR IDENTITY
*  ********************************************************************************************************************
*  Name                          Initials      Company
*  ********************************************************************************************************************
*  Peter Paulus                  Pp            Vector Informatik GmbH
*  ********************************************************************************************************************
*  REVISION HISTORY
*  ********************************************************************************************************************
*  Version   Date        Author  Change Id     Description
*  ********************************************************************************************************************
*  02.00.00  2008-02-19  Pp      Creation of WdgM according to ASR3.0 release.
*  02.00.01  2008-05-19  Pp      ESCAN00026988 No changes in this file.
*                                              Resolved CodeInspection issues.
*  02.00.02  2008-06-03  Pp                    No changes in this file.
*  02.00.03  2008-06-09  Pp                    Removed svn keyword Id.
*  02.01.00  2008-06-30  Pp      ESCAN00027956 Added generator version check.
*  02.01.01  2008-07-16  Bmz     ESCAN00028458 no changes in define
*  02.01.02  2008-07-29  Bmz     ESCAN00028784 OPERATION-INVOKED-EVENT: the P-PORT-PROTOTYPE-REF is corrected to  �ComponentType/WdgM/globalmode�
*  02.02.00  2008-11-27  Bmz     ESCAN00030954 ECU mode management support
*                                ESCAN00031023 Bugfixing Callback Function Update - no changes in define
*                                ESCAN00031400 Bswmd Version insert - no changes in define
*  02.02.01  2009-03.01  Bmz     ESCAN00033401 No changes in this file.
*                                ESCAN00032075 No changes in this file.
*                                ESCAN00032646 No changes in this file.
*                                ESCAN00032744 No changes in this file.
*                                ESCAN00032077 No changes in this file.
*                                ESCAN00033836 the export of semantic information of service port interfaces added
*  02.03.00  2009-07-09  Bmz     ESCAN00035918 No changes in this file.
*                                ESCAN00034698 No changes in this file.
*                                ESCAN00036334 No changes in this file.
*                                ESCAN00032744 No changes in this file.
*                                -             Copyright update
*                                ESCAN00036400 No changes in this file.
*  02.03.01  2009-10-20  Bmz     ESCAN00038585 The wrong cycle function name is genereated for Alive Superivisions via DaVinciDeveloper
*                                              in case the Rte Mode Switch Notification is enabled.
*                                ESCAN00037101 No changes in this file.
*  02.03.02  2010-03-15  Bmz     ESCAN00041402 No changes in this file.
*                                ESCAN00041506 No changes in this file.
*  02.03.03  2010-05-06  Bmz     ESCAN00042306 No changes in this file.
*                                -             version update
*                                ESCAN00042796 No changes in this file.
*  02.03.04  2010-08-20  Bmz     ESCAN00043727 No changes in this file.
*  02.04.00  2010-12-07  Cer,Bmz ESCAN00045139 Added generation of module prefixes for symbolic names (Generation.xml)
*                                ESCAN00046406 Relation for container 'SupervisedEntity_0' reworked (Identifier.xml)
*                                ESCAN00045984 Removed string compares for numeric values (Validation.xml)
*                                ESCAN00031590 Renamed ports and modes in the SWC generation (SWC_WdgM.xsl),
*                                              IdentifierS.xml and WdgMS.xml to make service mapping easier
*                                SW-Version Update
*  02.04.01  2011-02-23  Bmz     ESCAN00048848 No changes in this file.
*
*  **.**.**  2011-06-08  JDU     draft by TTTech
*  **.**.**  2011-06-14  JDU     2nd draft by TTTech using feedback by Mr. Kalmbach/Vector
*  **.**.**  2011-07-13  JDU     Release Candidate
*  **.**.**  2011-08-26  JDU     generate code for `WdgM_MainFunction` and `WdgM_UpdateTickCount`
*  **.**.**  2011-09-14  JDU     [42475] AUTOSAR 3.1 compatibility
*  **.**.**  2011-09-14  JDU     [42548] fixed `GetLocalStatus` parameter type
*  **.**.**  2011-09-20  JDU     [42628,42629] new functions
*  **.**.**  2011-09-21  JDU     [42660] `UpdateTickCount` is periodic
*  **.**.**  2011-09-26  JDU     [42626] use `WdgM_LocalStatusType` as parameter type
*  **.**.**  2011-09-27  JDU     [42718] fix `ActivateSupervisionEntity` parameter list
*  **.**.**  2011-09-27  JDU     [42719] fix `DeactivateSupervisionEntity` parameter list
*  **.**.**  2011-09-27  JDU     [42475] use `UpdateAliveCounter` for 3.1 entities
*  **.**.**  2011-09-30  JDU     [42660] provide arguments for `UpdateTickCount`
*  **.**.**  2011-10-03  JDU     [42626] fix `PORT-API-OPTION` elements
*  **.**.**  2011-10-03  JDU     [42794] ensure unique `RUNNABLE` names
*  **.**.**  2011-10-04  JDU     [42475] use the right interface name
*  **.**.**  2011-10-21  JDU     [43187] temporarily remove AUTOSAR 3.1 compatibility mode
*  **.**.**  2011-10-21  JDU     [43206] support two new functions
*  **.**.**  2011-10-24  JDU     [43206] generate callback functions for each entity
*  **.**.**  2011-10-25  JDU     [43240] remove superflous prefix and fix parameter list
*  **.**.**  2011-11-02  JDU     [43240] remove superflous prefix for Global State Change Callback
*  **.**.**  2011-11-02  JDU     [43240] fixed the Local State Change callbacks.
*  **.**.**  2012-04-05  JDU     [42794] `WdgUpdateAliveCounter` should work now
*  **.**.**  2012-07-11  JDU     [42794] bugfix functions added to 4.0
*
***********************************************************************************************************************
-->
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2004/07/xpath-functions" xmlns:xdt="http://www.w3.org/2004/07/xpath-datatypes" xmlns="http://autosar.org/3.1.4" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" exclude-result-prefixes="xsl fo xs fn xdt">
  <xsl:output method="xml" encoding="UTF-8" indent="yes"/>
  <xsl:variable name="COMP_NAME" select="'WdgM'"/>
  <xsl:variable name="WDGM_SUPERVISED_ENTITY_ID_TYPE" select="//*[local-name() = 'DEFINITION-REF' and .= '/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntityIdType']/../*[local-name() = 'VALUE']"/>
  <xsl:variable name="WDGM_SUPERVISION_CYCLE"         select="//*[local-name() = 'DEFINITION-REF' and .= '/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMSupervisionCycle']/../*[local-name() = 'VALUE']"/>
  <xsl:variable name="WDGM_TICKS_PER_SECOND"          select="//*[local-name() = 'DEFINITION-REF' and .= '/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMTicksPerSecond']/../*[local-name() = 'VALUE']"/>

  <!--
  DO NOT DELETE THIS COMMENT!!! THIS IS INTENDED.
  -->
  <xsl:variable name="WDGM_CBK_MODE_SWITCH_NOTIFICATION" select="//*[local-name() = 'DEFINITION-REF' and .= '/TTTECH/WdgM/WdgMGeneral/WdgMCbkModeSwitchNotification']/../*[local-name() = 'VALUE']"/>
  <!--
  DO NOT DELETE THIS COMMENT!!! THIS IS INTENDED.
  -->
  <!-- Root template (Entry Point of Transformation) -->
  <xsl:template match="/">
    <AUTOSAR>
      <xsl:attribute name="xsi:schemaLocation">http://autosar.org/3.1.4 autosar.xsd</xsl:attribute>
      <TOP-LEVEL-PACKAGES>
        <AR-PACKAGE>
          <SHORT-NAME>ComponentType</SHORT-NAME>
          <ELEMENTS>
            <SERVICE-COMPONENT-TYPE>
              <SHORT-NAME><xsl:value-of select="$COMP_NAME"/></SHORT-NAME>
              <CATEGORY>ServiceComponent</CATEGORY>
              <!-- Add export of special data group DV_SDG for service port interfaces -->
              <ADMIN-DATA>
                <SDGS>
                  <SDG GID="DV_SDG">
                    <SD GID="DV_BSWM">WdgM</SD>
                 </SDG>
                </SDGS>
              </ADMIN-DATA>
              <!-- Add Port Prototypes -->
              <xsl:call-template name="WDGM_PORT_PROTOTYPES"/>
            </SERVICE-COMPONENT-TYPE>
            <!-- Add Implementation -->
            <xsl:call-template name="SWC_IMPLEMENTATION"/>
            <!-- Add Internal Behavior -->
            <xsl:call-template name="WDGM_INTERNAL_BEHAVIOR"/>
          </ELEMENTS>
        </AR-PACKAGE>
        <AR-PACKAGE>
          <xsl:call-template name="WDGM_PORT_INTERFACES"/>
        </AR-PACKAGE>
        <AR-PACKAGE>
          <!-- DataTypes needed by WdgM -->
          <xsl:call-template name="WDGM_TYPES"/>
        </AR-PACKAGE>
        <AR-PACKAGE>
          <!-- ModeDeclaration for WdgM -->
          <xsl:call-template name="WDGM_MODE_DECLARATION_GROUP"/>
        </AR-PACKAGE>
      </TOP-LEVEL-PACKAGES>
      </AUTOSAR><xsl:text>
</xsl:text>
    <xsl:comment> SWC_WdgM.xsl 1.13.0 </xsl:comment>
  </xsl:template>

  <!--
  =====================================================================================================================
      PORT PROTOTYPES
  =====================================================================================================================
  -->
  <!-- Port Protoype Template -->
  <xsl:template name="WDGM_PORT_PROTOTYPES">
    <xsl:variable name="se31cnt" select="count (//*[local-name () = 'DEFINITION-REF' and .= '/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMSupportedAutosarAPI']/../*[local-name () = 'VALUE' and .= 'API_3_1'])"/>
    <xsl:variable name="is31config" select="$se31cnt > 0"/>
    <xsl:variable name="is40config" select="$se31cnt = 0"/>
    <PORTS>
      <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMSupervisedEntityId']/..">
        <xsl:variable name="entityID"   select="./*[local-name() = 'VALUE']"/>
        <xsl:variable name="entityName" select="../../*[local-name() = 'SHORT-NAME']"/>
        <xsl:variable name="entityIdToken">
          <xsl:choose>
            <xsl:when test="$entityID &lt; 10">SE00<xsl:value-of select="$entityID" />_<xsl:value-of select="$entityName" /></xsl:when>
            <xsl:when test="$entityID &lt; 100">SE0<xsl:value-of select="$entityID" />_<xsl:value-of select="$entityName" /></xsl:when>
            <xsl:otherwise>SE<xsl:value-of select="$entityID" />_<xsl:value-of select="$entityName" /></xsl:otherwise>
          </xsl:choose>
        </xsl:variable>
        <xsl:if test="$is40config">
          <xsl:for-each select="../..//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMCheckpoint/WdgMCheckpointId']/..">
            <xsl:variable name="checkpointID"   select="./*[local-name() = 'VALUE']"/>
            <xsl:variable name="checkpointName" select="../../*[local-name() = 'SHORT-NAME']"/>
            <xsl:variable name="checkpointIdToken">
              <xsl:choose>
                <xsl:when test="$checkpointID &lt; 10">CP00<xsl:value-of select="$checkpointID" />_<xsl:value-of select="$checkpointName" /></xsl:when>
                <xsl:when test="$checkpointID &lt; 100">CP0<xsl:value-of select="$checkpointID" />_<xsl:value-of select="$checkpointName" /></xsl:when>
                <xsl:otherwise>CP<xsl:value-of select="$checkpointID" />_<xsl:value-of select="$checkpointName" /></xsl:otherwise>
              </xsl:choose>
            </xsl:variable>
        <P-PORT-PROTOTYPE>
          <SHORT-NAME><xsl:value-of select="$entityIdToken"/>_<xsl:value-of select="$checkpointIdToken"/></SHORT-NAME>
          <DESC>
            <L-2 L="EN">P-Port Prototype for Supervised Entity <xsl:value-of select="$entityName" /> with ID <xsl:value-of select="$entityID" />
              and Checkpoint <xsl:value-of select="$checkpointName"/> with ID <xsl:value-of select="$checkpointID"/>.</L-2>
          </DESC>
          <PROVIDED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">/PortInterface/WdgM_AliveSupervision</PROVIDED-INTERFACE-TREF>
        </P-PORT-PROTOTYPE>
          </xsl:for-each>
        </xsl:if>
        <P-PORT-PROTOTYPE>
          <SHORT-NAME><xsl:value-of select="$entityIdToken"/></SHORT-NAME>
          <DESC>
            <L-2 L="EN">P-Port Prototype for Supervised Entity <xsl:value-of select="$entityName" /> with ID <xsl:value-of select="$entityID" /></L-2>
          </DESC>
          <PROVIDED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">/PortInterface/WdgM_IndividualMode</PROVIDED-INTERFACE-TREF>
        </P-PORT-PROTOTYPE>
      <xsl:if test="$is31config">
        <P-PORT-PROTOTYPE>
          <SHORT-NAME><xsl:value-of select="$entityIdToken"/>_API_31</SHORT-NAME>
          <DESC>
            <L-2 L="EN">P-Port Prototype for Supervised Entity <xsl:value-of select="$entityName" /> with ID <xsl:value-of select="$entityID" /> (API 3.1)
            </L-2>
          </DESC>
          <PROVIDED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">/PortInterface/WdgM_AliveSupervision</PROVIDED-INTERFACE-TREF>
        </P-PORT-PROTOTYPE>
      </xsl:if>
      </xsl:for-each>
      <P-PORT-PROTOTYPE>
        <SHORT-NAME>Global</SHORT-NAME>
        <DESC>
          <L-2 L="EN">P-Port Prototype for Global Mode </L-2>
        </DESC>
        <PROVIDED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">/PortInterface/WdgM_GlobalMode</PROVIDED-INTERFACE-TREF>
      </P-PORT-PROTOTYPE>
          <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMTrigger/WdgMTriggerModeId']/..">
            <xsl:variable name="modeID"   select="./*[local-name() = 'VALUE']"/>
            <xsl:choose>
              <xsl:when test="$is31config">
      <P-PORT-PROTOTYPE>
        <SHORT-NAME>MODE_<xsl:value-of select="$modeID"/></SHORT-NAME>
        <DESC>
          <L-2 L="EN">P-Port Prototype for Trigger Mode <xsl:value-of select="$modeID"/></L-2>
        </DESC>
        <PROVIDED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">/PortInterface/WdgM_GlobalMode</PROVIDED-INTERFACE-TREF>
      </P-PORT-PROTOTYPE>
              </xsl:when>
              <xsl:when test="$is40config">
                <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMCallerIds/WdgMCallerId']/..">
                  <xsl:variable name="callerID" select="./*[local-name() = 'VALUE']"/>
      <P-PORT-PROTOTYPE>
        <SHORT-NAME>MODE_<xsl:value-of select="$modeID"/>_CALLER_ID_<xsl:value-of select="$callerID"/></SHORT-NAME>
        <DESC>
          <L-2 L="EN">P-Port Prototype for Trigger Mode <xsl:value-of select="$modeID"/> and Caller ID <xsl:value-of select="$callerID"/></L-2>
        </DESC>
        <PROVIDED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">/PortInterface/WdgM_GlobalMode</PROVIDED-INTERFACE-TREF>
      </P-PORT-PROTOTYPE>
                </xsl:for-each>
              </xsl:when>
            </xsl:choose>
          </xsl:for-each>
    </PORTS>
  </xsl:template>

  <!--
  =====================================================================================================================
      SWC IMPLEMENTATION
  =====================================================================================================================
  -->
  <xsl:template name="SWC_IMPLEMENTATION">
    <SWC-IMPLEMENTATION>
      <SHORT-NAME>WdgM_Implementation</SHORT-NAME>
      <BEHAVIOR-REF DEST="INTERNAL-BEHAVIOR">/ComponentType/WdgM_InternalBehavior</BEHAVIOR-REF>
    </SWC-IMPLEMENTATION>
  </xsl:template>
  <!--
  =====================================================================================================================
      INTERNAL BEHAVIOR
  =====================================================================================================================
  -->
  <!-- Runnables Template -->
  <xsl:template name="WDGM_INTERNAL_BEHAVIOR">
    <INTERNAL-BEHAVIOR>
      <SHORT-NAME>WdgM_InternalBehavior</SHORT-NAME>
      <COMPONENT-REF DEST="SERVICE-COMPONENT-TYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/></COMPONENT-REF>
      <xsl:call-template name="WDGM_OPERATION_INVOKED_EVENTS"/>
      <xsl:call-template name="WDGM_PORT_DEFINED_ARGUMENTS"/>
      <xsl:call-template name="WDGM_RUNNABLES"/>
    </INTERNAL-BEHAVIOR>
  </xsl:template>
  <!--
  =====================================================================================================================
      OPERATION INVOKED EVENTS
  =====================================================================================================================
  -->
  <!-- Operation Invoked events Template -->
  <xsl:template name="WDGM_OPERATION_INVOKED_EVENTS">
    <xsl:variable name="se31cnt"    select="count (//*[local-name () = 'DEFINITION-REF' and .= '/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMSupportedAutosarAPI']/../*[local-name () = 'VALUE' and .= 'API_3_1'])"/>
    <xsl:variable name="is31config" select="$se31cnt > 0"/>
    <xsl:variable name="is40config" select="$se31cnt = 0"/>
    <xsl:variable name="timebase_source" select="//*[(local-name () = 'DEFINITION-REF') and (.='/TTTECH/WdgM/WdgMGeneral/WdgMTimebaseSource')]/../*[(local-name () = 'VALUE')]"/>
    <EVENTS>
      <OPERATION-INVOKED-EVENT>
        <SHORT-NAME>V_WDGM_GMO</SHORT-NAME>
        <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/WdgM_InternalBehavior/GetMode</START-ON-EVENT-REF>
        <OPERATION-IREF>
          <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/Global</P-PORT-PROTOTYPE-REF>
          <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/WdgM_GlobalMode/GetMode</OPERATION-PROTOTYPE-REF>
        </OPERATION-IREF>
      </OPERATION-INVOKED-EVENT>
      <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMTrigger/WdgMTriggerModeId']/..">
        <xsl:variable name="modeID"   select="./*[local-name() = 'VALUE']"/>
        <xsl:choose>
          <xsl:when test="$is31config">
      <OPERATION-INVOKED-EVENT>
        <SHORT-NAME>V_WDGM_<xsl:value-of select="$modeID"/>_SMO</SHORT-NAME>
        <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/WdgM_InternalBehavior/SetMode</START-ON-EVENT-REF>
        <OPERATION-IREF>
          <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/MODE_<xsl:value-of select="$modeID"/></P-PORT-PROTOTYPE-REF>
          <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/WdgM_GlobalMode/SetMode</OPERATION-PROTOTYPE-REF>
        </OPERATION-IREF>
      </OPERATION-INVOKED-EVENT>
          </xsl:when>
          <xsl:when test="$is40config">
            <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMCallerIds/WdgMCallerId']/..">
              <xsl:variable name="callerID" select="./*[local-name() = 'VALUE']"/>
      <OPERATION-INVOKED-EVENT>
        <SHORT-NAME>V_WDGM_<xsl:value-of select="$modeID"/>_CALLER_ID_<xsl:value-of select="$callerID"/>_SMO</SHORT-NAME>
        <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/WdgM_InternalBehavior/SetMode</START-ON-EVENT-REF>
        <OPERATION-IREF>
          <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/MODE_<xsl:value-of select="$modeID"/>_CALLER_ID_<xsl:value-of select="$callerID"/></P-PORT-PROTOTYPE-REF>
          <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/WdgM_GlobalMode/SetMode</OPERATION-PROTOTYPE-REF>
        </OPERATION-IREF>
      </OPERATION-INVOKED-EVENT>
            </xsl:for-each>
          </xsl:when>
        </xsl:choose>
      </xsl:for-each>
      <OPERATION-INVOKED-EVENT>
        <SHORT-NAME>V_WDGM_GGS</SHORT-NAME>
        <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/WdgM_InternalBehavior/GetGlobalStatus</START-ON-EVENT-REF>
        <OPERATION-IREF>
          <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/Global</P-PORT-PROTOTYPE-REF>
          <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/WdgM_GlobalMode/GetGlobalStatus</OPERATION-PROTOTYPE-REF>
        </OPERATION-IREF>
      </OPERATION-INVOKED-EVENT>
      <OPERATION-INVOKED-EVENT>
        <SHORT-NAME>V_WDGM_PRE</SHORT-NAME>
        <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/WdgM_InternalBehavior/PerformReset</START-ON-EVENT-REF>
        <OPERATION-IREF>
          <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/Global</P-PORT-PROTOTYPE-REF>
          <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/WdgM_GlobalMode/PerformReset</OPERATION-PROTOTYPE-REF>
        </OPERATION-IREF>
      </OPERATION-INVOKED-EVENT>
      <OPERATION-INVOKED-EVENT>
        <SHORT-NAME>V_WDGM_GSC</SHORT-NAME>
        <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/WdgM_InternalBehavior/GlobalStateChangeCbk</START-ON-EVENT-REF>
        <OPERATION-IREF>
          <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/Global</P-PORT-PROTOTYPE-REF>
          <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/WdgM_GlobalMode/GlobalStateChangeCbk</OPERATION-PROTOTYPE-REF>
        </OPERATION-IREF>
      </OPERATION-INVOKED-EVENT>
      <TIMING-EVENT>
        <SHORT-NAME>V_WDGM_MAI</SHORT-NAME>
        <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/WdgM_InternalBehavior/MainFunction</START-ON-EVENT-REF>
        <PERIOD><xsl:value-of select="$WDGM_SUPERVISION_CYCLE"/></PERIOD>
      </TIMING-EVENT>
      <xsl:if test="$timebase_source = 'WDGM_EXTERNAL_TICK'">
      <TIMING-EVENT>
        <SHORT-NAME>V_WDGM_UTC</SHORT-NAME>
        <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/WdgM_InternalBehavior/UpdateTickCount</START-ON-EVENT-REF>
        <PERIOD><xsl:value-of select="1 div number ($WDGM_TICKS_PER_SECOND)"/></PERIOD>
      </TIMING-EVENT>
      </xsl:if>
      <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMSupervisedEntityId']/..">
        <xsl:variable name="entityID"   select="./*[local-name() = 'VALUE']"/>
        <xsl:variable name="entityName" select="../../*[local-name() = 'SHORT-NAME']"/>
        <xsl:variable name="entityIdToken">
          <xsl:choose>
            <xsl:when test="$entityID &lt; 10">SE00<xsl:value-of select="$entityID" />_<xsl:value-of select="$entityName" /></xsl:when>
            <xsl:when test="$entityID &lt; 100">SE0<xsl:value-of select="$entityID" />_<xsl:value-of select="$entityName" /></xsl:when>
            <xsl:otherwise>SE<xsl:value-of select="$entityID" />_<xsl:value-of select="$entityName" /></xsl:otherwise>
          </xsl:choose>
        </xsl:variable>

        <OPERATION-INVOKED-EVENT>
          <xsl:choose>
            <xsl:when test="$is31config">
              <SHORT-NAME>V_WDGM_<xsl:value-of select="$entityIdToken"/>_GAS</SHORT-NAME>
              <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/WdgM_InternalBehavior/GetAliveSupervisionStatus</START-ON-EVENT-REF>
              <OPERATION-IREF>
                <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/<xsl:value-of select="$entityIdToken"/></P-PORT-PROTOTYPE-REF>
                <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/WdgM_IndividualMode/GetAliveSupervisionStatus</OPERATION-PROTOTYPE-REF>
              </OPERATION-IREF>
            </xsl:when>
            <xsl:when test="$is40config">
              <SHORT-NAME>V_WDGM_<xsl:value-of select="$entityIdToken"/>_GLS</SHORT-NAME>
              <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/WdgM_InternalBehavior/GetLocalStatus</START-ON-EVENT-REF>
              <OPERATION-IREF>
                <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/<xsl:value-of select="$entityIdToken"/></P-PORT-PROTOTYPE-REF>
                <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/WdgM_IndividualMode/GetLocalStatus</OPERATION-PROTOTYPE-REF>
              </OPERATION-IREF>
            </xsl:when>
          </xsl:choose>
        </OPERATION-INVOKED-EVENT>

        <OPERATION-INVOKED-EVENT>
          <xsl:choose>
            <xsl:when test="$is31config">
                <SHORT-NAME>V_WDGM_<xsl:value-of select="$entityIdToken"/>_AAS</SHORT-NAME>
                <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/WdgM_InternalBehavior/ActivateAliveSupervision</START-ON-EVENT-REF>
                <OPERATION-IREF>
                  <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/<xsl:value-of select="$entityIdToken"/></P-PORT-PROTOTYPE-REF>
                  <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/WdgM_IndividualMode/ActivateAliveSupervision</OPERATION-PROTOTYPE-REF>
                </OPERATION-IREF>
            </xsl:when>
            <xsl:when test="$is40config">
                <SHORT-NAME>V_WDGM_<xsl:value-of select="$entityIdToken"/>_ASE</SHORT-NAME>
                <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/WdgM_InternalBehavior/ActivateSupervisionEntity</START-ON-EVENT-REF>
                <OPERATION-IREF>
                  <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/<xsl:value-of select="$entityIdToken"/></P-PORT-PROTOTYPE-REF>
                  <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/WdgM_IndividualMode/ActivateSupervisionEntity</OPERATION-PROTOTYPE-REF>
                </OPERATION-IREF>
            </xsl:when>
          </xsl:choose>
        </OPERATION-INVOKED-EVENT>

        <OPERATION-INVOKED-EVENT>
          <xsl:choose>
            <xsl:when test="$is31config">
                <SHORT-NAME>V_WDGM_<xsl:value-of select="$entityIdToken"/>_DAS</SHORT-NAME>
                <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/WdgM_InternalBehavior/DeactivateAliveSupervision</START-ON-EVENT-REF>
                <OPERATION-IREF>
                  <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/<xsl:value-of select="$entityIdToken"/></P-PORT-PROTOTYPE-REF>
                  <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/WdgM_IndividualMode/DeactivateAliveSupervision</OPERATION-PROTOTYPE-REF>
                </OPERATION-IREF>
            </xsl:when>
            <xsl:when test="$is40config">
                <SHORT-NAME>V_WDGM_<xsl:value-of select="$entityIdToken"/>_DSE</SHORT-NAME>
                <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/WdgM_InternalBehavior/DeactivateSupervisionEntity</START-ON-EVENT-REF>
                <OPERATION-IREF>
                  <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/<xsl:value-of select="$entityIdToken"/></P-PORT-PROTOTYPE-REF>
                  <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/WdgM_IndividualMode/DeactivateSupervisionEntity</OPERATION-PROTOTYPE-REF>
                </OPERATION-IREF>
            </xsl:when>
          </xsl:choose>
        </OPERATION-INVOKED-EVENT>

        <xsl:if test="$is31config">
          <OPERATION-INVOKED-EVENT>
            <SHORT-NAME>V_WDGM_<xsl:value-of select="$entityIdToken"/>_UAC</SHORT-NAME>
            <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/WdgM_InternalBehavior/UpdateAliveCounter</START-ON-EVENT-REF>
            <OPERATION-IREF>
              <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/<xsl:value-of select="$entityIdToken"/>_API_31</P-PORT-PROTOTYPE-REF>
              <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/WdgM_AliveSupervision/UpdateAliveCounter</OPERATION-PROTOTYPE-REF>
            </OPERATION-IREF>
          </OPERATION-INVOKED-EVENT>
        </xsl:if>

        <xsl:if test="$is40config">
          <xsl:for-each select="../..//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMCheckpoint/WdgMCheckpointId']/..">
          <xsl:variable name="checkpointID"   select="./*[local-name() = 'VALUE']"/>
          <xsl:variable name="checkpointName" select="../../*[local-name() = 'SHORT-NAME']"/>
          <xsl:variable name="checkpointIdToken">
            <xsl:choose>
              <xsl:when test="$checkpointID &lt; 10">CP00<xsl:value-of select="$checkpointID" />_<xsl:value-of select="$checkpointName" /></xsl:when>
              <xsl:when test="$checkpointID &lt; 100">CP0<xsl:value-of select="$checkpointID" />_<xsl:value-of select="$checkpointName" /></xsl:when>
              <xsl:otherwise>CP<xsl:value-of select="$checkpointID" />_<xsl:value-of select="$checkpointName" /></xsl:otherwise>
            </xsl:choose>
          </xsl:variable>

            <OPERATION-INVOKED-EVENT>
              <SHORT-NAME>V_WDGM_<xsl:value-of select="$entityIdToken"/>_<xsl:value-of select="$checkpointIdToken"/>_CPR</SHORT-NAME>
              <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/WdgM_InternalBehavior/CheckpointReached</START-ON-EVENT-REF>
              <OPERATION-IREF>
                <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/<xsl:value-of select="$entityIdToken"/>_<xsl:value-of select="$checkpointIdToken"/></P-PORT-PROTOTYPE-REF>
                <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/WdgM_AliveSupervision/CheckpointReached</OPERATION-PROTOTYPE-REF>
              </OPERATION-IREF>
            </OPERATION-INVOKED-EVENT>
          </xsl:for-each>
        </xsl:if>
      </xsl:for-each>
      <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMLocalStateChangeCbk']">
        <xsl:variable name="callbackName" select="../*[local-name() = 'VALUE']"/>
        <xsl:variable name="entityID"     select="../..//*[local-name () = 'DEFINITION-REF' and .= '/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMSupervisedEntityId']/../*[local-name() = 'VALUE']"/>
        <xsl:variable name="entityName"   select="../../../*[local-name() = 'SHORT-NAME']"/>
        <xsl:variable name="entityIdToken">
          <xsl:choose>
            <xsl:when test="$entityID &lt; 10">SE00<xsl:value-of select="$entityID" />_<xsl:value-of select="$entityName" /></xsl:when>
            <xsl:when test="$entityID &lt; 100">SE0<xsl:value-of select="$entityID" />_<xsl:value-of select="$entityName" /></xsl:when>
            <xsl:otherwise>SE<xsl:value-of select="$entityID" />_<xsl:value-of select="$entityName" /></xsl:otherwise>
          </xsl:choose>
        </xsl:variable>
        <OPERATION-INVOKED-EVENT>
          <SHORT-NAME>V_WDGM_<xsl:value-of select="$entityIdToken"/>_LSC</SHORT-NAME>
          <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/WdgM_InternalBehavior/<xsl:value-of select="$callbackName"/></START-ON-EVENT-REF>
          <OPERATION-IREF>
            <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/Global</P-PORT-PROTOTYPE-REF>
            <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/WdgM_GlobalMode/<xsl:value-of select="$callbackName"/></OPERATION-PROTOTYPE-REF>
          </OPERATION-IREF>
        </OPERATION-INVOKED-EVENT>
      </xsl:for-each>
    </EVENTS>
  </xsl:template>
  <!--
  =====================================================================================================================
      PORT DEFINED ARGUMENTS
  =====================================================================================================================
  -->
  <!-- Port defined Arguments Template -->
  <xsl:template name="WDGM_PORT_DEFINED_ARGUMENTS">
    <xsl:variable name="se31cnt"    select="count (//*[local-name () = 'DEFINITION-REF' and .= '/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMSupportedAutosarAPI']/../*[local-name () = 'VALUE' and .= 'API_3_1'])"/>
    <xsl:variable name="is31config" select="$se31cnt > 0"/>
    <xsl:variable name="is40config" select="$se31cnt = 0"/>
    <PORT-API-OPTIONS>
      <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMSupervisedEntityId']/..">
        <xsl:variable name="entityID"   select="./*[local-name() = 'VALUE']"/>
        <xsl:variable name="entityName" select="../../*[local-name() = 'SHORT-NAME']"/>
        <xsl:variable name="entityIdToken">
          <xsl:choose>
            <xsl:when test="$entityID &lt; 10">SE00<xsl:value-of select="$entityID" />_<xsl:value-of select="$entityName" /></xsl:when>
            <xsl:when test="$entityID &lt; 100">SE0<xsl:value-of select="$entityID" />_<xsl:value-of select="$entityName" /></xsl:when>
            <xsl:otherwise>SE<xsl:value-of select="$entityID" />_<xsl:value-of select="$entityName" /></xsl:otherwise>
          </xsl:choose>
        </xsl:variable>
        <xsl:if test="$is40config">
          <xsl:for-each select="../..//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMCheckpoint/WdgMCheckpointId']/..">
            <xsl:variable name="checkpointID"   select="./*[local-name() = 'VALUE']"/>
            <xsl:variable name="checkpointName" select="../../*[local-name() = 'SHORT-NAME']"/>
            <xsl:variable name="checkpointIdToken">
              <xsl:choose>
                <xsl:when test="$checkpointID &lt; 10">CP00<xsl:value-of select="$checkpointID" />_<xsl:value-of select="$checkpointName" /></xsl:when>
                <xsl:when test="$checkpointID &lt; 100">CP0<xsl:value-of select="$checkpointID" />_<xsl:value-of select="$checkpointName" /></xsl:when>
                <xsl:otherwise>CP<xsl:value-of select="$checkpointID" />_<xsl:value-of select="$checkpointName" /></xsl:otherwise>
              </xsl:choose>
            </xsl:variable>
          <PORT-API-OPTION>
            <PORT-ARG-VALUES>
              <INTEGER-LITERAL>
                <SHORT-NAME><xsl:value-of select="$entityIdToken"/>_<xsl:value-of select="$checkpointID"/></SHORT-NAME>
                <TYPE-TREF DEST="INTEGER-TYPE">/DataType/WdgM_SupervisedEntityIdType</TYPE-TREF>
                <VALUE><xsl:value-of select="$entityID"/></VALUE>
              </INTEGER-LITERAL>
              <INTEGER-LITERAL>
                <SHORT-NAME><xsl:value-of select="$checkpointIdToken"/></SHORT-NAME>
                <TYPE-TREF DEST="INTEGER-TYPE">/DataType/WdgM_CheckpointIdType</TYPE-TREF>
                <VALUE><xsl:value-of select="$checkpointID"/></VALUE>
              </INTEGER-LITERAL>
            </PORT-ARG-VALUES>
            <PORT-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/<xsl:value-of select="$entityIdToken"/>_<xsl:value-of select="$checkpointIdToken"/></PORT-REF>
          </PORT-API-OPTION>
          </xsl:for-each>
        </xsl:if>
        <PORT-API-OPTION>
          <PORT-ARG-VALUES>
            <INTEGER-LITERAL>
              <SHORT-NAME><xsl:value-of select="$entityIdToken"/>_GLS</SHORT-NAME>
              <TYPE-TREF DEST="INTEGER-TYPE">/DataType/WdgM_SupervisedEntityIdType</TYPE-TREF>
              <VALUE><xsl:value-of select="$entityID"/></VALUE>
            </INTEGER-LITERAL>
          </PORT-ARG-VALUES>
          <PORT-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/<xsl:value-of select="$entityIdToken"/></PORT-REF>
        </PORT-API-OPTION>
      <xsl:if test="$is31config">
        <!-- for UpdateAliveCounter (3.1) -->
        <PORT-API-OPTION>
          <PORT-ARG-VALUES>
            <INTEGER-LITERAL>
              <SHORT-NAME><xsl:value-of select="$entityIdToken"/>_API_31</SHORT-NAME>
              <TYPE-TREF DEST="INTEGER-TYPE">/DataType/WdgM_SupervisedEntityIdType</TYPE-TREF>
              <VALUE><xsl:value-of select="$entityID"/></VALUE>
            </INTEGER-LITERAL>
          </PORT-ARG-VALUES>
          <PORT-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/<xsl:value-of select="$entityIdToken"/>_API_31</PORT-REF>
        </PORT-API-OPTION>
      </xsl:if>
      </xsl:for-each>
      <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMConfigSet/WdgMMode/WdgMTrigger/WdgMTriggerModeId']">
        <xsl:variable name="modeID"   select="../*[local-name() = 'VALUE']"/>
        <xsl:choose>
          <xsl:when test="$is31config">
          <PORT-API-OPTION>
            <PORT-ARG-VALUES>
              <INTEGER-LITERAL>
                <SHORT-NAME>MODE_<xsl:value-of select="$modeID"/></SHORT-NAME>
                <TYPE-TREF DEST="INTEGER-TYPE">/DataType/WdgM_ModeType</TYPE-TREF>
                <VALUE><xsl:value-of select="$modeID"/></VALUE>
              </INTEGER-LITERAL>
            </PORT-ARG-VALUES>
            <PORT-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/MODE_<xsl:value-of select="$modeID"/></PORT-REF>
          </PORT-API-OPTION>
          </xsl:when>
          <xsl:when test="$is40config">
            <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMCallerIds/WdgMCallerId']/..">
              <xsl:variable name="callerID" select="./*[local-name() = 'VALUE']"/>
          <PORT-API-OPTION>
            <PORT-ARG-VALUES>
              <INTEGER-LITERAL>
                <SHORT-NAME>MODE_<xsl:value-of select="$modeID"/></SHORT-NAME>
                <TYPE-TREF DEST="INTEGER-TYPE">/DataType/WdgM_ModeType</TYPE-TREF>
                <VALUE><xsl:value-of select="$modeID"/></VALUE>
              </INTEGER-LITERAL>
              <INTEGER-LITERAL>
                <SHORT-NAME>CALLER_<xsl:value-of select="$callerID"/></SHORT-NAME>
                <TYPE-TREF DEST="INTEGER-TYPE">/DataType/UInt16</TYPE-TREF>
                <VALUE><xsl:value-of select="$callerID"/></VALUE>
              </INTEGER-LITERAL>
            </PORT-ARG-VALUES>
            <PORT-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/MODE_<xsl:value-of select="$modeID"/>_CALLER_ID_<xsl:value-of select="$callerID"/></PORT-REF>
          </PORT-API-OPTION>
            </xsl:for-each>
          </xsl:when>
        </xsl:choose>
      </xsl:for-each>
    </PORT-API-OPTIONS>
  </xsl:template>
  <!--
  =====================================================================================================================
      RUNNABLES
  =====================================================================================================================
  -->
  <!-- Runnables Template -->
  <xsl:template name="WDGM_RUNNABLES">
    <xsl:variable name="se31cnt" select="count (//*[local-name () = 'DEFINITION-REF' and .= '/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMSupportedAutosarAPI']/../*[local-name () = 'VALUE' and .= 'API_3_1'])"/>
    <xsl:variable name="is31config" select="$se31cnt > 0"/>
    <xsl:variable name="is40config" select="$se31cnt = 0"/>
    <xsl:variable name="timebase_source" select="//*[(local-name () = 'DEFINITION-REF') and (.='/TTTECH/WdgM/WdgMGeneral/WdgMTimebaseSource')]/../*[(local-name () = 'VALUE')]"/>
    <RUNNABLES>
      <RUNNABLE-ENTITY>
        <SHORT-NAME>GetMode</SHORT-NAME>
        <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
        <SYMBOL>WdgM_GetMode</SYMBOL>
      </RUNNABLE-ENTITY>
      <RUNNABLE-ENTITY>
        <SHORT-NAME>SetMode</SHORT-NAME>
        <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
        <SYMBOL>WdgM_SetMode</SYMBOL>
      </RUNNABLE-ENTITY>
      <xsl:if test="$is31config">
      <RUNNABLE-ENTITY>
        <SHORT-NAME>UpdateAliveCounter</SHORT-NAME>
        <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
        <SYMBOL>WdgM_UpdateAliveCounter</SYMBOL>
      </RUNNABLE-ENTITY>
      </xsl:if>
      <xsl:if test="$is40config">
      <RUNNABLE-ENTITY>
        <SHORT-NAME>CheckpointReached</SHORT-NAME>
        <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
        <SYMBOL>WdgM_CheckpointReached</SYMBOL>
      </RUNNABLE-ENTITY>
      </xsl:if>
      <xsl:if test="$is31config">
      <RUNNABLE-ENTITY>
        <SHORT-NAME>GetAliveSupervisionStatus</SHORT-NAME>
        <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
        <SYMBOL>WdgM_GetLocalStatus</SYMBOL>
      </RUNNABLE-ENTITY>
      </xsl:if>
      <xsl:if test="$is40config">
      <RUNNABLE-ENTITY>
        <SHORT-NAME>GetLocalStatus</SHORT-NAME>
        <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
        <SYMBOL>WdgM_GetLocalStatus</SYMBOL>
      </RUNNABLE-ENTITY>
      </xsl:if>
      <xsl:if test="$is31config">
      <RUNNABLE-ENTITY>
        <SHORT-NAME>ActivateAliveSupervision</SHORT-NAME>
        <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
        <SYMBOL>WdgM_ActivateSupervisionEntity</SYMBOL>
      </RUNNABLE-ENTITY>
      </xsl:if>
      <xsl:if test="$is40config">
      <RUNNABLE-ENTITY>
        <SHORT-NAME>ActivateSupervisionEntity</SHORT-NAME>
        <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
        <SYMBOL>WdgM_ActivateSupervisionEntity</SYMBOL>
      </RUNNABLE-ENTITY>
      </xsl:if>
      <xsl:if test="$is31config">
      <RUNNABLE-ENTITY>
        <SHORT-NAME>DeactivateAliveSupervision</SHORT-NAME>
        <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
        <SYMBOL>WdgM_DeactivateSupervisionEntity</SYMBOL>
      </RUNNABLE-ENTITY>
      </xsl:if>
      <xsl:if test="$is40config">
      <RUNNABLE-ENTITY>
        <SHORT-NAME>DeactivateSupervisionEntity</SHORT-NAME>
        <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
        <SYMBOL>WdgM_DeactivateSupervisionEntity</SYMBOL>
      </RUNNABLE-ENTITY>
      </xsl:if>
      <RUNNABLE-ENTITY>
        <SHORT-NAME>GetGlobalStatus</SHORT-NAME>
        <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
        <SYMBOL>WdgM_GetGlobalStatus</SYMBOL>
      </RUNNABLE-ENTITY>
      <RUNNABLE-ENTITY>
        <SHORT-NAME>PerformReset</SHORT-NAME>
        <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
        <SYMBOL>WdgM_PerformReset</SYMBOL>
      </RUNNABLE-ENTITY>
      <RUNNABLE-ENTITY>
        <SHORT-NAME>MainFunction</SHORT-NAME>
        <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
        <SYMBOL>WdgM_MainFunction</SYMBOL>
      </RUNNABLE-ENTITY>
      <xsl:if test="$timebase_source = 'WDGM_EXTERNAL_TICK'">
      <RUNNABLE-ENTITY>
        <SHORT-NAME>UpdateTickCount</SHORT-NAME>
        <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
        <SYMBOL>WdgM_UpdateTickCount</SYMBOL>
      </RUNNABLE-ENTITY>
      </xsl:if>
      <RUNNABLE-ENTITY>
        <SHORT-NAME>GlobalStateChangeCbk</SHORT-NAME>
        <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
        <SYMBOL>GlobalStateChangeCbk</SYMBOL>
      </RUNNABLE-ENTITY>
      <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMLocalStateChangeCbk']">
        <xsl:variable name="callbackName" select="../*[local-name() = 'VALUE']"/>
        <RUNNABLE-ENTITY>
          <SHORT-NAME><xsl:value-of select="$callbackName"/></SHORT-NAME>
          <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
          <SYMBOL><xsl:value-of select="$callbackName"/></SYMBOL>
        </RUNNABLE-ENTITY>
      </xsl:for-each>
    </RUNNABLES>
  </xsl:template>

  <!--
  =====================================================================================================================
      PORT INTERFACES
  =====================================================================================================================
  -->
  <!-- Port Interface Template -->
  <xsl:template   name="WDGM_PORT_INTERFACES">
    <xsl:variable name="se31cnt" select="count (//*[local-name () = 'DEFINITION-REF' and .= '/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMSupportedAutosarAPI']/../*[local-name () = 'VALUE' and .= 'API_3_1'])"/>
    <xsl:variable name="is31config" select="$se31cnt > 0"/>
    <xsl:variable name="is40config" select="$se31cnt = 0"/>
    <xsl:variable name="timebase_source" select="//*[(local-name () = 'DEFINITION-REF') and (.='/TTTECH/WdgM/WdgMGeneral/WdgMTimebaseSource')]/../*[(local-name () = 'VALUE')]"/>
    <SHORT-NAME>PortInterface</SHORT-NAME>
    <ELEMENTS>
      <!-- WdgM_AliveSupervision interface -->
      <CLIENT-SERVER-INTERFACE>
        <SHORT-NAME>WdgM_AliveSupervision</SHORT-NAME>
        <ADMIN-DATA>
          <SDGS>
            <SDG GID="DV_SDG">
              <SD GID="DV_BSWM">WdgM</SD>
            </SDG>
          </SDGS>
        </ADMIN-DATA>
        <IS-SERVICE>true</IS-SERVICE>
        <OPERATIONS>
          <xsl:if test="$is31config">
          <OPERATION-PROTOTYPE>
            <SHORT-NAME>UpdateAliveCounter</SHORT-NAME>
            <DESC>
              <L-2>Indicates to the Watchdog Manager that a Checkpoint within a Supervised Entity has been reached. Equivalent to CheckpointReached in AUTOSAR 4.0</L-2>
            </DESC>
            <POSSIBLE-ERROR-REFS>
              <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/WdgM_AliveSupervision/E_NOT_OK</POSSIBLE-ERROR-REF>
            </POSSIBLE-ERROR-REFS>
          </OPERATION-PROTOTYPE>
          </xsl:if>
          <xsl:if test="$is40config">
          <OPERATION-PROTOTYPE>
            <SHORT-NAME>CheckpointReached</SHORT-NAME>
            <DESC>
              <L-2>Indicates to the Watchdog Manager that a Checkpoint within a Supervised Entity has been reached.</L-2>
            </DESC>
            <POSSIBLE-ERROR-REFS>
              <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/WdgM_AliveSupervision/E_NOT_OK</POSSIBLE-ERROR-REF>
            </POSSIBLE-ERROR-REFS>
          </OPERATION-PROTOTYPE>
          </xsl:if>
        </OPERATIONS>
        <POSSIBLE-ERRORS>
          <APPLICATION-ERROR>
            <SHORT-NAME>E_NOT_OK</SHORT-NAME>
            <ERROR-CODE>1</ERROR-CODE>
          </APPLICATION-ERROR>
        </POSSIBLE-ERRORS>
      </CLIENT-SERVER-INTERFACE>
      <CLIENT-SERVER-INTERFACE>
        <SHORT-NAME>WdgM_IndividualMode</SHORT-NAME>
        <ADMIN-DATA>
          <SDGS>
            <SDG GID="DV_SDG">
              <SD GID="DV_BSWM">WdgM</SD>
            </SDG>
          </SDGS>
        </ADMIN-DATA>
        <IS-SERVICE>true</IS-SERVICE>
        <OPERATIONS>
          <xsl:if test="$is31config">
          <OPERATION-PROTOTYPE>
            <SHORT-NAME>GetAliveSupervisionStatus</SHORT-NAME>
            <DESC>
              <L-2>Returns the monitoring status of an individual Supervised Entity. Equivalent to `GetLocalStatus` in AUTOSAR 4.0</L-2>
            </DESC>
            <ARGUMENTS>
              <ARGUMENT-PROTOTYPE>
                <SHORT-NAME>Status</SHORT-NAME>
                <TYPE-TREF DEST="INTEGER-TYPE">/DataType/WdgM_LocalStatusType</TYPE-TREF>
                <DIRECTION>OUT</DIRECTION>
              </ARGUMENT-PROTOTYPE>
            </ARGUMENTS>
            <POSSIBLE-ERROR-REFS>
              <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/WdgM_IndividualMode/E_NOT_OK</POSSIBLE-ERROR-REF>
            </POSSIBLE-ERROR-REFS>
          </OPERATION-PROTOTYPE>
          </xsl:if>
          <xsl:if test="$is40config">
          <OPERATION-PROTOTYPE>
            <SHORT-NAME>GetLocalStatus</SHORT-NAME>
            <DESC>
              <L-2>Returns the monitoring status of an individual Supervised Entity.</L-2>
            </DESC>
            <ARGUMENTS>
              <ARGUMENT-PROTOTYPE>
                <SHORT-NAME>Status</SHORT-NAME>
                <TYPE-TREF DEST="INTEGER-TYPE">/DataType/WdgM_LocalStatusType</TYPE-TREF>
                <DIRECTION>OUT</DIRECTION>
              </ARGUMENT-PROTOTYPE>
            </ARGUMENTS>
            <POSSIBLE-ERROR-REFS>
              <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/WdgM_IndividualMode/E_NOT_OK</POSSIBLE-ERROR-REF>
            </POSSIBLE-ERROR-REFS>
          </OPERATION-PROTOTYPE>
          </xsl:if>
          <xsl:if test="$is31config">
          <OPERATION-PROTOTYPE>
            <SHORT-NAME>ActivateAliveSupervision</SHORT-NAME>
            <DESC>
              <L-2>This function activates the monitoring of the given Supervised Entity. Equivalent to ActivateSupervisionEntity in AUTOSAR 4.0</L-2>
            </DESC>
            <ARGUMENTS>
            </ARGUMENTS>
            <POSSIBLE-ERROR-REFS>
              <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/WdgM_IndividualMode/E_NOT_OK</POSSIBLE-ERROR-REF>
            </POSSIBLE-ERROR-REFS>
          </OPERATION-PROTOTYPE>
          </xsl:if>
          <xsl:if test="$is40config">
          <OPERATION-PROTOTYPE>
            <SHORT-NAME>ActivateSupervisionEntity</SHORT-NAME>
            <DESC>
              <L-2>This function activates the monitoring of the given Supervised Entity</L-2>
            </DESC>
            <ARGUMENTS>
            </ARGUMENTS>
            <POSSIBLE-ERROR-REFS>
              <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/WdgM_IndividualMode/E_NOT_OK</POSSIBLE-ERROR-REF>
            </POSSIBLE-ERROR-REFS>
          </OPERATION-PROTOTYPE>
          </xsl:if>
          <xsl:if test="$is31config">
          <OPERATION-PROTOTYPE>
            <SHORT-NAME>DeactivateAliveSupervision</SHORT-NAME>
            <DESC>
              <L-2>This function deactivates the monitoring of the given Supervised Entity. Equivalent to DeactivateSupervisionEntity in AUTOSAR 4.0</L-2>
            </DESC>
            <ARGUMENTS>
            </ARGUMENTS>
            <POSSIBLE-ERROR-REFS>
              <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/WdgM_IndividualMode/E_NOT_OK</POSSIBLE-ERROR-REF>
            </POSSIBLE-ERROR-REFS>
          </OPERATION-PROTOTYPE>
          </xsl:if>
          <xsl:if test="$is40config">
          <OPERATION-PROTOTYPE>
            <SHORT-NAME>DeactivateSupervisionEntity</SHORT-NAME>
            <DESC>
              <L-2>This function deactivates the monitoring of the given Supervised Entity</L-2>
            </DESC>
            <ARGUMENTS>
            </ARGUMENTS>
            <POSSIBLE-ERROR-REFS>
              <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/WdgM_IndividualMode/E_NOT_OK</POSSIBLE-ERROR-REF>
            </POSSIBLE-ERROR-REFS>
          </OPERATION-PROTOTYPE>
          </xsl:if>
        </OPERATIONS>
        <POSSIBLE-ERRORS>
          <APPLICATION-ERROR>
            <SHORT-NAME>E_NOT_OK</SHORT-NAME>
            <ERROR-CODE>1</ERROR-CODE>
          </APPLICATION-ERROR>
        </POSSIBLE-ERRORS>
      </CLIENT-SERVER-INTERFACE>
      <CLIENT-SERVER-INTERFACE>
        <SHORT-NAME>WdgM_GlobalMode</SHORT-NAME>
        <ADMIN-DATA>
          <SDGS>
            <SDG GID="DV_SDG">
              <SD GID="DV_BSWM">WdgM</SD>
            </SDG>
          </SDGS>
        </ADMIN-DATA>
        <IS-SERVICE>true</IS-SERVICE>
        <OPERATIONS>
          <OPERATION-PROTOTYPE>
            <SHORT-NAME>GetMode</SHORT-NAME>
            <DESC>
              <L-2>Returns the current mode of the Watchdog Manager.</L-2>
            </DESC>
            <ARGUMENTS>
              <ARGUMENT-PROTOTYPE>
                <SHORT-NAME>Mode</SHORT-NAME>
                <TYPE-TREF DEST="INTEGER-TYPE">/DataType/WdgM_ModeType</TYPE-TREF>
                <DIRECTION>OUT</DIRECTION>
              </ARGUMENT-PROTOTYPE>
            </ARGUMENTS>
            <POSSIBLE-ERROR-REFS>
              <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/WdgM_GlobalMode/E_NOT_OK</POSSIBLE-ERROR-REF>
            </POSSIBLE-ERROR-REFS>
          </OPERATION-PROTOTYPE>
          <OPERATION-PROTOTYPE>
            <SHORT-NAME>SetMode</SHORT-NAME>
            <DESC>
              <L-2>Sets the mode of the Watchdog Manager if the caller is allowed to do so.</L-2>
            </DESC>
            <POSSIBLE-ERROR-REFS>
              <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/WdgM_GlobalMode/E_NOT_OK</POSSIBLE-ERROR-REF>
            </POSSIBLE-ERROR-REFS>
          </OPERATION-PROTOTYPE>
          <OPERATION-PROTOTYPE>
            <SHORT-NAME>MainFunction</SHORT-NAME>
            <DESC>
              <L-2>Performs the processing of the cyclic Watchdog Manager jobs.</L-2>
            </DESC>
            <POSSIBLE-ERROR-REFS>
              <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/WdgM_GlobalMode/E_NOT_OK</POSSIBLE-ERROR-REF>
            </POSSIBLE-ERROR-REFS>
          </OPERATION-PROTOTYPE>
          <xsl:if test="$timebase_source = 'WDGM_EXTERNAL_TICK'">
          <OPERATION-PROTOTYPE>
            <SHORT-NAME>UpdateTickCount</SHORT-NAME>
            <DESC>
              <L-2>Increments the Watchdog Manager tick counter by one</L-2>
            </DESC>
            <POSSIBLE-ERROR-REFS>
              <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/WdgM_GlobalMode/E_NOT_OK</POSSIBLE-ERROR-REF>
            </POSSIBLE-ERROR-REFS>
          </OPERATION-PROTOTYPE>
          </xsl:if>
          <OPERATION-PROTOTYPE>
            <SHORT-NAME>GetGlobalStatus</SHORT-NAME>
            <DESC>
              <L-2>Returns the global monitoring status of the Watchdog Manager.</L-2>
            </DESC>
            <ARGUMENTS>
              <ARGUMENT-PROTOTYPE>
                <SHORT-NAME>Status</SHORT-NAME>
                <TYPE-TREF DEST="INTEGER-TYPE">/DataType/WdgM_GlobalStatusType</TYPE-TREF>
                <DIRECTION>OUT</DIRECTION>
              </ARGUMENT-PROTOTYPE>
            </ARGUMENTS>
            <POSSIBLE-ERROR-REFS>
              <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/WdgM_GlobalMode/E_NOT_OK</POSSIBLE-ERROR-REF>
            </POSSIBLE-ERROR-REFS>
          </OPERATION-PROTOTYPE>
          <OPERATION-PROTOTYPE>
            <SHORT-NAME>GlobalStateChangeCbk</SHORT-NAME>
            <DESC>
              <L-2>Global state change callback notification</L-2>
            </DESC>
            <ARGUMENTS>
              <ARGUMENT-PROTOTYPE>
                <SHORT-NAME>Status</SHORT-NAME>
                <TYPE-TREF DEST="INTEGER-TYPE">/DataType/WdgM_GlobalStatusType</TYPE-TREF>
                <DIRECTION>IN</DIRECTION>
              </ARGUMENT-PROTOTYPE>
            </ARGUMENTS>
            <POSSIBLE-ERROR-REFS>
              <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/WdgM_GlobalMode/E_NOT_OK</POSSIBLE-ERROR-REF>
            </POSSIBLE-ERROR-REFS>
          </OPERATION-PROTOTYPE>
          <OPERATION-PROTOTYPE>
            <SHORT-NAME>LocalStateChangeCbk</SHORT-NAME>
            <DESC>
              <L-2>Local state change callback notification</L-2>
            </DESC>
            <ARGUMENTS>
              <ARGUMENT-PROTOTYPE>
                <SHORT-NAME>Status</SHORT-NAME>
                <TYPE-TREF DEST="INTEGER-TYPE">/DataType/WdgM_LocalStatusType</TYPE-TREF>
                <DIRECTION>IN</DIRECTION>
              </ARGUMENT-PROTOTYPE>
            </ARGUMENTS>
            <POSSIBLE-ERROR-REFS>
              <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/WdgM_GlobalMode/E_NOT_OK</POSSIBLE-ERROR-REF>
            </POSSIBLE-ERROR-REFS>
          </OPERATION-PROTOTYPE>
          <OPERATION-PROTOTYPE>
            <SHORT-NAME>PerformReset</SHORT-NAME>
            <DESC>
              <L-2>Instructs the Watchdog Manager to cause a watchdog reset.</L-2>
            </DESC>
            <POSSIBLE-ERROR-REFS>
              <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/WdgM_GlobalMode/E_NOT_OK</POSSIBLE-ERROR-REF>
            </POSSIBLE-ERROR-REFS>
          </OPERATION-PROTOTYPE>
          <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .='/TTTECH/WdgM/WdgMGeneral/WdgMSupervisedEntity/WdgMLocalStateChangeCbk']">
            <xsl:variable name="callbackName" select="../*[local-name() = 'VALUE']"/>
            <OPERATION-PROTOTYPE>
              <SHORT-NAME><xsl:value-of select="$callbackName"/></SHORT-NAME>
              <DESC>
                <L-2>Callback function (see documentation on `WdgM_LocalStateChangeCbk`).</L-2>
              </DESC>
              <ARGUMENTS>
                <ARGUMENT-PROTOTYPE>
                  <SHORT-NAME>Status</SHORT-NAME>
                  <TYPE-TREF DEST="INTEGER-TYPE">/DataType/WdgM_LocalStatusType</TYPE-TREF>
                  <DIRECTION>IN</DIRECTION>
                </ARGUMENT-PROTOTYPE>
              </ARGUMENTS>
              <POSSIBLE-ERROR-REFS>
                <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/WdgM_IndividualMode/E_NOT_OK</POSSIBLE-ERROR-REF>
              </POSSIBLE-ERROR-REFS>
            </OPERATION-PROTOTYPE>
          </xsl:for-each>
        </OPERATIONS>
        <POSSIBLE-ERRORS>
          <APPLICATION-ERROR>
            <SHORT-NAME>E_NOT_OK</SHORT-NAME>
            <ERROR-CODE>1</ERROR-CODE>
          </APPLICATION-ERROR>
        </POSSIBLE-ERRORS>
      </CLIENT-SERVER-INTERFACE>
    </ELEMENTS>
  </xsl:template>

  <!--
  =====================================================================================================================
      TYPES TEMPLATE
  =====================================================================================================================
  -->
  <xsl:template name="WDGM_TYPES">
    <SHORT-NAME>DataType</SHORT-NAME>
    <ELEMENTS>
      <COMPU-METHOD>
        <SHORT-NAME>CM_WdgM_LocalStatusType</SHORT-NAME>
        <COMPU-INTERNAL-TO-PHYS>
          <COMPU-SCALES>
            <COMPU-SCALE>
              <LOWER-LIMIT>0</LOWER-LIMIT>
              <UPPER-LIMIT>0</UPPER-LIMIT>
              <COMPU-CONST>
                <VT>WDGM_LOCAL_STATUS_OK</VT>
              </COMPU-CONST>
            </COMPU-SCALE>
            <COMPU-SCALE>
              <LOWER-LIMIT>1</LOWER-LIMIT>
              <UPPER-LIMIT>1</UPPER-LIMIT>
              <COMPU-CONST>
                <VT>WDGM_LOCAL_STATUS_FAILED</VT>
              </COMPU-CONST>
            </COMPU-SCALE>
            <COMPU-SCALE>
              <LOWER-LIMIT>2</LOWER-LIMIT>
              <UPPER-LIMIT>2</UPPER-LIMIT>
              <COMPU-CONST>
                <VT>WDGM_LOCAL_STATUS_EXPIRED</VT>
              </COMPU-CONST>
            </COMPU-SCALE>
            <COMPU-SCALE>
              <LOWER-LIMIT>4</LOWER-LIMIT>
              <UPPER-LIMIT>4</UPPER-LIMIT>
              <COMPU-CONST>
                <VT>WDGM_LOCAL_STATUS_DEACTIVATED</VT>
              </COMPU-CONST>
            </COMPU-SCALE>
          </COMPU-SCALES>
        </COMPU-INTERNAL-TO-PHYS>
      </COMPU-METHOD>
      <COMPU-METHOD>
        <SHORT-NAME>CM_WdgM_GlobalStatusType</SHORT-NAME>
        <COMPU-INTERNAL-TO-PHYS>
          <COMPU-SCALES>
            <COMPU-SCALE>
              <LOWER-LIMIT>0</LOWER-LIMIT>
              <UPPER-LIMIT>0</UPPER-LIMIT>
              <COMPU-CONST>
                <VT>WDGM_GLOBAL_STATUS_OK</VT>
              </COMPU-CONST>
            </COMPU-SCALE>
            <COMPU-SCALE>
              <LOWER-LIMIT>1</LOWER-LIMIT>
              <UPPER-LIMIT>1</UPPER-LIMIT>
              <COMPU-CONST>
                <VT>WDGM_GLOBAL_STATUS_FAILED</VT>
              </COMPU-CONST>
            </COMPU-SCALE>
            <COMPU-SCALE>
              <LOWER-LIMIT>2</LOWER-LIMIT>
              <UPPER-LIMIT>2</UPPER-LIMIT>
              <COMPU-CONST>
                <VT>WDGM_GLOBAL_STATUS_EXPIRED</VT>
              </COMPU-CONST>
            </COMPU-SCALE>
            <COMPU-SCALE>
              <LOWER-LIMIT>3</LOWER-LIMIT>
              <UPPER-LIMIT>3</UPPER-LIMIT>
              <COMPU-CONST>
                <VT>WDGM_GLOBAL_STATUS_STOPPED</VT>
              </COMPU-CONST>
            </COMPU-SCALE>
            <COMPU-SCALE>
              <LOWER-LIMIT>4</LOWER-LIMIT>
              <UPPER-LIMIT>4</UPPER-LIMIT>
              <COMPU-CONST>
                <VT>WDGM_GLOBAL_STATUS_DEACTIVATED</VT>
              </COMPU-CONST>
            </COMPU-SCALE>
          </COMPU-SCALES>
        </COMPU-INTERNAL-TO-PHYS>
      </COMPU-METHOD>
      <INTEGER-TYPE>
        <SHORT-NAME>UInt8</SHORT-NAME>
        <LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
        <UPPER-LIMIT INTERVAL-TYPE="CLOSED">255</UPPER-LIMIT>
      </INTEGER-TYPE>
      <INTEGER-TYPE>
        <SHORT-NAME>UInt16</SHORT-NAME>
        <LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
        <UPPER-LIMIT INTERVAL-TYPE="CLOSED">65535</UPPER-LIMIT>
      </INTEGER-TYPE>
      <INTEGER-TYPE>
        <SHORT-NAME>WdgM_SupervisedEntityIdType</SHORT-NAME>
        <!-- Add export of special data group DV_SDG for service port interfaces -->
        <ADMIN-DATA>
          <SDGS>
            <SDG GID="DV_SDG">
              <SD GID="DV_BSWM">WdgM</SD>
            </SDG>
          </SDGS>
        </ADMIN-DATA>
        <LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
<!--      <xsl:if test="$WDGM_SUPERVISED_ENTITY_ID_TYPE = 'uint8'"> -->
<!--        <UPPER-LIMIT INTERVAL-TYPE="CLOSED">255</UPPER-LIMIT> -->
<!--      </xsl:if> -->
<!--      <xsl:if test="$WDGM_SUPERVISED_ENTITY_ID_TYPE = 'uint16'"> -->
        <UPPER-LIMIT INTERVAL-TYPE="CLOSED">65535</UPPER-LIMIT>
<!--      </xsl:if>  -->
      </INTEGER-TYPE>
      <INTEGER-TYPE>
        <SHORT-NAME>WdgM_CheckpointIdType</SHORT-NAME>
        <!-- Add export of special data group DV_SDG for service port interfaces -->
        <ADMIN-DATA>
          <SDGS>
            <SDG GID="DV_SDG">
              <SD GID="DV_BSWM">WdgM</SD>
            </SDG>
          </SDGS>
        </ADMIN-DATA>
        <LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
<!--      <xsl:if test="$WDGM_SUPERVISED_ENTITY_ID_TYPE = 'uint8'"> -->
<!--      <UPPER-LIMIT INTERVAL-TYPE="CLOSED">255</UPPER-LIMIT> -->
<!--      </xsl:if> -->
<!--      <xsl:if test="$WDGM_SUPERVISED_ENTITY_ID_TYPE = 'uint16'"> -->
        <UPPER-LIMIT INTERVAL-TYPE="CLOSED">65535</UPPER-LIMIT>
<!--          </xsl:if>  -->
      </INTEGER-TYPE>
      <INTEGER-TYPE>
        <SHORT-NAME>WdgM_ModeType</SHORT-NAME>
        <ADMIN-DATA>
          <SDGS>
            <SDG GID="DV_SDG">
              <SD GID="DV_BSWM">WdgM</SD>
            </SDG>
          </SDGS>
        </ADMIN-DATA>
        <LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
        <UPPER-LIMIT INTERVAL-TYPE="CLOSED">255</UPPER-LIMIT>
      </INTEGER-TYPE>
      <INTEGER-TYPE>
        <SHORT-NAME>WdgM_LocalStatusType</SHORT-NAME>
        <ADMIN-DATA>
          <SDGS>
            <SDG GID="DV_SDG">
              <SD GID="DV_BSWM">WdgM</SD>
            </SDG>
          </SDGS>
        </ADMIN-DATA>
        <SW-DATA-DEF-PROPS>
          <COMPU-METHOD-REF DEST="COMPU-METHOD">/DataType/CM_WdgM_LocalStatusType</COMPU-METHOD-REF>
        </SW-DATA-DEF-PROPS>
        <LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
        <UPPER-LIMIT INTERVAL-TYPE="CLOSED">255</UPPER-LIMIT>
      </INTEGER-TYPE>
      <INTEGER-TYPE>
        <SHORT-NAME>WdgM_GlobalStatusType</SHORT-NAME>
        <ADMIN-DATA>
          <SDGS>
            <SDG GID="DV_SDG">
              <SD GID="DV_BSWM">WdgM</SD>
            </SDG>
          </SDGS>
        </ADMIN-DATA>
        <SW-DATA-DEF-PROPS>
          <COMPU-METHOD-REF DEST="COMPU-METHOD">/DataType/CM_WdgM_GlobalStatusType</COMPU-METHOD-REF>
        </SW-DATA-DEF-PROPS>
        <LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
        <UPPER-LIMIT INTERVAL-TYPE="CLOSED">255</UPPER-LIMIT>
      </INTEGER-TYPE>
    </ELEMENTS>
  </xsl:template>

  <!--
  =====================================================================================================================
      MODE DECLARATION GROUP TEMPLATE
  =====================================================================================================================
  -->
  <xsl:template name="WDGM_MODE_DECLARATION_GROUP">
    <SHORT-NAME>ModeDeclarationGroup</SHORT-NAME>
    <ELEMENTS>
    </ELEMENTS>
  </xsl:template>
</xsl:stylesheet>
