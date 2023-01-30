<?xml version="1.0" encoding="UTF-8" ?>
<!--
***********************************************************************************************************************
COPYRIGHT
=======================================================================================================================
Copyright (c) 2006-2012 by Vector Informatik GmbH, all rights reserved

    This software is copyright protected and proprietary to Vector Informatik GmbH.
    Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
    All other rights remain with Vector Informatik GmbH.
=======================================================================================================================
FILE DESCRIPTION
=======================================================================================================================
File:           SWC_EcuM.xsl
Component:      SysService_AsrEcuM
Module:         EcuM
Generator:      -

Description:    -
***********************************************************************************************************************
-->
<!--
***********************************************************************************************************************
                A U T H O R   I D E N T I T Y
=======================================================================================================================
  Initials     Name                      Company
  ========    =================          ==============================================================================
  Chm          Christian Marchl          Vector Informatik GmbH
  Bmz          Bethina Mausz             Vector Informatik GmbH
  Mfr          Martin Froschhammer       Vector Informatik GmbH
  Rpp          Philipp Ritter            Vector Informatik GmbH
  Vjn          Jochen Vorreiter          Vector Informatik GmbH
=======================================================================================================================
               R E V I S I O N   H I S T O R Y
=======================================================================================================================
  Version   Date        Author  Change Id     Description
=======================================================================================================================
  03.00.01  2007-09-26  Chm     ESCAN00022372 Qualitiy assurance activities necessary for Component
                                              SysService_EcuM
  03.00.02  2007-11-21  Chm     ESCAN00023354 No Changes here
  03.00.03  2007-12-05  Chm     ESCAN00022871 No Changes here
  04.00.00  2008-03-14  Chm     ESCAN00024563 No changes here
                                ESCAN00023356 No changes here
                                ESCAN00024323 Generation of port prototypes corrected.
                                ESCAN00027863 No Changes here
  04.00.01  2008-04-16  Chm     ESCAN00026037 Added generation of GetState port
                                ESCAN00026537 No changes here
                                ESCAN00026471 No changes here
  04.01.00  2008-05-15  Chm     -             No changes here
  04.01.01  2008-06-02  Chm     -             Added ECUM_STATE_ERROR as enumeration item.
                                -             Added ECUM_ prefix for application modes retrieved from  ecuc file.
  04.01.02  2008-06-02  Chm     ESCAN00027459 No changes here
                                ESCAN00027313 No changes here
  04.01.03  2008-06-17  Chm     ESCAN00027659 No changes here
  04.02.00  2008-06-30  Chm     ESCAN00027955 No Changes here
  04.03.00  2008-07-23  Chm     ESCAN00028372 No Changes here
                                ESCAN00028511 No Changes here
  04.03.01  2008-08-08  Bmz     -             No changes here
  04.03.02  2008-08-08  Bmz     ESCAN00029221 No changes here
  04.03.03  2008-09-01  Chm     ESCAN00029621 Removed new line before xml declaration
                                ESCAN00029300 No changes here
  04.03.04  2008-09-24  Chm     ESCAN00027708 Changed generation of SW-C.
                                ESCAN00029799 No changes here
                                ESCAN00029815 No changes here
                                ESCAN00029313 No changes here
  04.04.00  2008-10-22  Chm     ESCAN00030516 No changes here
  05.00.00  2008-11-28  Chm     ESCAN00031216 No changes here
                                ESCAN00031214 Added file EcuM_PrivateCfg.h to component
                                ESCAN00030497 No changes here
                                ESCAN00030132 No changes here
                                ESCAN00031520 No changes here
                                ESCAN00031786 No changes here
                                ESCAN00031787 No changes here
  05.01.00  2009-02-19  Chm     ESCAN00032011 No changes here
            2009-02-19  Chm     ESCAN00032502 No changes here
            2009-02-19  Chm     ESCAN00033069 No changes here
            2009-02-20  Chm     ESCAN00031852 No changes here
            2009-02-23  Chm     ESCAN00029165 No changes here
            2009-02-24  Chm     ESCAN00031789 No changes here
            2009-03-04  Chm     ESCAN00033480 No changes here
            2009-03-09  Chm     ESCAN00033718 No changes here
            2009-03-16  Chm     ESCAN00033834 Add export of special data group DV_SDG for service port interfaces
  05.02.00  2009-05-19  Chm     ESCAN00035001 No changes here
            2009-07-07  Chm     ESCAN00036192 No changes here
  05.03.00  2009-07-13  Chm     ESCAN00036369 No changes here
            2009-07-13  Chm     ESCAN00036370 No changes here
            2009-07-13  Chm     ESCAN00035287 No changes here
            2009-07-15  Chm     ESCAN00036441 No changes here
            2009-07-16  Chm     ESCAN00035917 No changes here
            2009-07-16  Chm     ESCAN00035535 No changes here
            2009-07-17  Chm     ESCAN00036348 No changes here
            2009-07-16  Chm     ESCAN00035536 No changes here
            2009-07-21  Chm     ESCAN00034788 No changes here
  05.03.01  2009-10-22  Chm     ESCAN00037381 No changes here
  05.03.02  2009-12-11  Chm     ESCAN00039720 No changes here
            2009-12-11  Chm     ESCAN00037612 No changes here
            2009-12-14  Chm     ESCAN00039748 No changes here
            2009-12-15  Chm     ESCAN00034936 No changes here
            2009-12-21  Chm     ESCAN00039882 No changes here
            2010-02-19  Chm     ESCAN00040987 No changes here
            2010-02-23  Chm     ESCAN00041075 No changes here
  05.03.03  2010-04-14  Chm     ESCAN00041836 No changes here
            2010-04-19  Chm     ESCAN00041426 No changes here
            2010-04-24  Chm     ESCAN00041446 No changes here
            2010-04-24  Chm     ESCAN00041827 No changes here
  05.03.04  2010-07-29  Bmz     ESCAN00044245 No changes here
            2010-07-29  Bmz     ESCAN00044246 No changes here
            2010-07-29  Bmz     ESCAN00043065 No changes here
  05.04.00  2010-10-18  Bmz     ESCAN00044990 No changes here
                                ESCAN00046061 No changes here
  05.06.00  2010-11-26  Bmz     ESCAN00046158 Added MODE-SWITCHED-ACK for Rte_Feedback API generation (Changed generation of SW-C)
                                ESCAN00047183 No changes here
                                ESCAN00047434 No changes here
                                ESCAN00045138 No changes here
            2011-01-26  Bmz     Prefix generation for DEM-ERRORS inserted in GenerationS.xml
                                G601 updated
            2011-02-03  Bmz     ESCAN00048364 No changes here
  05.06.01  2011-03-14  Bmz     ESCAN00049201 No changes here
  05.07.00  2011-04-26  Bmz     ESCAN00049111 No changes here
  06.00.00  2011-07-18  Bmz     ESCAN00044722 No changes here
                                ESCAN00049989 No changes here
                                ESCAN00049107 No changes here
                                ESCAN00048924 No changes here
                                ESCAN00047973 No changes here
                                ESCAN00045985 No changes here
                                ESCAN00049319 No changes here
                                ESCAN00050811 No changes here
                                ESCAN00050625 No changes here
                                ESCAN00039058 No changes here
                                ESCAN00046958 No changes here
                                ESCAN00051730 No changes here
                                ESCAN00052248 SWC-D shall be generated according to AUTOSAR Schema 3.2.1 (Mj-Nr Update)
                                ESCAN00052301 No changes here
                                ESCAN00052618 No changes here
  07.00.00  2011-09-20  Bmz     ESCAN00053281 No changes here
                                ESCAN00032233 decorate exported port interface name with EcuM_ prefix
                                ESCAN00053860 No changes here
                                ESCAN00053230 MainFunction shall always be generated to Service Component Description
                                ESCAN00052193 No changes here
                                ESCAN00054560 No changes here
                                ESCAN00042868 No changes here
                                ESCAN00052498 No changes here
                                ESCAN00054279 No changes here
            2011-12-09  Mfr     ESCAN00053892 No changes here
  07.01.00  2012-03-15  Rpp     ESCAN00057621 No changes here
                                ESCAN00057625 No changes here
                                ESCAN00057639 No changes here
                                ESCAN00057640 No changes here
  07.02.00   2012-04-11  Rpp    ESCAN00057924 No changes here
                                ESCAN00058216 No changes here
                                ESCAN00054793 No changes here
                                ESCAN00058041 No changes here
                                ESCAN00058225 No changes here
                                ESCAN00048077 No changes here
                                ESCAN00058257 No changes here
                                ESCAN00058258 No changes here
                                ESCAN00058263 No changes here
                                ESCAN00058340 No changes here
  07.03.00   2012-06-23  Rpp    ESCAN00059469 No changes here
                                ESCAN00059473 No changes here
  07.04.00   2012-10-05  Vjn    ESCAN00061986 No changes here
                                ESCAN00061560 No changes here
                                ESCAN00061857 No changes here
                                ESCAN00061884 No changes here
  07.04.01   2013-01-03  Vjn    ESCAN00063627 No changes here
  07.05.00   2013-04-08  Vjn    ESCAN00062418 No changes here
                                ESCAN00066486 No changes here
                                ESCAN00067036 No changes here
  07.06.00   2013-10-08  Vjn    ESCAN00070294 No changes here
                                ESCAN00071016 No changes here
***********************************************************************************************************************
-->
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2004/07/xpath-functions" xmlns:xdt="http://www.w3.org/2004/07/xpath-datatypes" xmlns ="http://autosar.org/3.2.1" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" exclude-result-prefixes="xsl fo xs fn xdt">
  <xsl:output method="xml" encoding="UTF-8"  indent="yes"/>
  <xsl:variable name="COMP_NAME" select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/EcuM/EcuMGeneral/EcuMServicePortConfig/EcuMServiceComponentName']/../*[local-name() = 'VALUE']" />
  <xsl:variable name="OS_COUNT" select="count(//*[local-name() = 'DEFINITION-REF' and substring-after(.,substring-before(.,'/OsAppMode'))='/OsAppMode'])" />
  <xsl:variable name="GEN_SHUTDOWN_PORT" select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/EcuM/EcuMGeneral/EcuMServicePortConfig/EcuMGenShutdownTargetPort']/../*[local-name() = 'VALUE']" />
  <xsl:variable name="GEN_BOOT_TARGET_PORT" select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/EcuM/EcuMGeneral/EcuMServicePortConfig/EcuMGenBootTargetPort']/../*[local-name() = 'VALUE']" />
  <xsl:variable name="GEN_APPLICATION_MODE_PORT" select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/EcuM/EcuMGeneral/EcuMServicePortConfig/EcuMGenApplicationModePort']/../*[local-name() = 'VALUE']" />
  <xsl:variable name="GEN_STATE_REQUEST_PORT" select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/EcuM/EcuMGeneral/EcuMServicePortConfig/EcuMGenStateRequestPort']/../*[local-name() = 'VALUE']" />
  <xsl:variable name="GEN_MODE_SWITCH_PORT" select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/EcuM/EcuMGeneral/EcuMServicePortConfig/EcuMGenModeSwitchPort']/../*[local-name() = 'VALUE']" />
  <xsl:variable name="INCLUDE_RTE" select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/EcuM/EcuMGeneral/EcuMIncludeRte']/../*[local-name() = 'VALUE']" />
  <xsl:variable name="ECUM_MAINFUNCTION_PERIOD" select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/EcuM/EcuMGeneral/EcuMMainFunctionPeriod']/../*[local-name() = 'VALUE']" />
  <!-- Root template (Entry Point of Transformation) -->
  <xsl:template match="/">
  <AUTOSAR>
      <xsl:attribute name="xsi:schemaLocation">http://autosar.org/3.2.1 autosar.xsd</xsl:attribute>
      <TOP-LEVEL-PACKAGES>
        <AR-PACKAGE>
          <SHORT-NAME>ComponentType</SHORT-NAME>
          <ELEMENTS>
            <SERVICE-COMPONENT-TYPE>
              <SHORT-NAME><xsl:value-of select="$COMP_NAME" /></SHORT-NAME>
              <CATEGORY>ServiceComponent</CATEGORY>
              <xsl:call-template name="ECUM_DV_SDG_ADMIN_DATA_TEMPLATE" />
              <!-- Add Port Prototypes -->
              <xsl:call-template name="ECUM_PORT_PROTOTYPES" />
            </SERVICE-COMPONENT-TYPE>
            <!-- Add Implementation -->
            <xsl:call-template name="ECUM_IMPLEMENTATION" />
            <!-- Add Internal Behavior -->
            <xsl:call-template name="ECUM_INTERNAL_BEHAVIOR" />
          </ELEMENTS>
        </AR-PACKAGE>
        <AR-PACKAGE>
          <xsl:call-template name="ECUM_PORT_INTERFACES" />
        </AR-PACKAGE>
        <AR-PACKAGE>
          <!-- DataTypes needed by EcuM -->
          <SHORT-NAME>DataType</SHORT-NAME>
          <ELEMENTS>
            <xsl:call-template name="ECUM_TYPES" />
          </ELEMENTS>
        </AR-PACKAGE>
        <xsl:if test="$GEN_MODE_SWITCH_PORT = 'true' and $INCLUDE_RTE = 'true'">
          <AR-PACKAGE>
            <!-- ModeDeclaration for ECUM -->
            <xsl:call-template name="ECUM_MODE_DECLARATION_GROUP"/>
          </AR-PACKAGE>
        </xsl:if>
      </TOP-LEVEL-PACKAGES>
    </AUTOSAR>
  </xsl:template>
  <!-- Types Template -->
  <xsl:template name="ECUM_TYPES">
      <xsl:if test="$GEN_STATE_REQUEST_PORT = 'true'">
        <INTEGER-TYPE>
          <SHORT-NAME>EcuM_UserType</SHORT-NAME>
          <xsl:call-template name="ECUM_DV_SDG_ADMIN_DATA_TEMPLATE" />
          <LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
          <UPPER-LIMIT INTERVAL-TYPE="CLOSED">255</UPPER-LIMIT>
        </INTEGER-TYPE>
      </xsl:if>
      <INTEGER-TYPE>
        <SHORT-NAME>UInt8</SHORT-NAME>
        <LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
        <UPPER-LIMIT INTERVAL-TYPE="CLOSED">255</UPPER-LIMIT>
      </INTEGER-TYPE>
      <xsl:if test="$GEN_STATE_REQUEST_PORT = 'true' or $GEN_SHUTDOWN_PORT = 'true'">
        <INTEGER-TYPE>
          <SHORT-NAME>EcuM_StateType</SHORT-NAME>
          <xsl:call-template name="ECUM_DV_SDG_ADMIN_DATA_TEMPLATE" />
          <SW-DATA-DEF-PROPS>
            <COMPU-METHOD-REF DEST="COMPU-METHOD">/DataType/EcuM_StateType_COMPU_METHOD</COMPU-METHOD-REF>
          </SW-DATA-DEF-PROPS>
          <LOWER-LIMIT INTERVAL-TYPE="CLOSED">16</LOWER-LIMIT>
          <UPPER-LIMIT INTERVAL-TYPE="CLOSED">255</UPPER-LIMIT>
        </INTEGER-TYPE>
      </xsl:if>
      <xsl:if test="$GEN_APPLICATION_MODE_PORT = 'true'">
        <xsl:if test="$OS_COUNT != 0">
          <INTEGER-TYPE>
            <SHORT-NAME>EcuM_AppModeType</SHORT-NAME>
            <xsl:call-template name="ECUM_DV_SDG_ADMIN_DATA_TEMPLATE" />
            <SW-DATA-DEF-PROPS>
              <COMPU-METHOD-REF DEST="COMPU-METHOD">/DataType/EcuM_AppModeType_COMPU_METHOD</COMPU-METHOD-REF>
            </SW-DATA-DEF-PROPS>
          <LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
          <UPPER-LIMIT INTERVAL-TYPE="CLOSED">255</UPPER-LIMIT>
          </INTEGER-TYPE>
          <COMPU-METHOD>
            <SHORT-NAME>EcuM_AppModeType_COMPU_METHOD</SHORT-NAME>
            <COMPU-INTERNAL-TO-PHYS>
              <COMPU-SCALES>
                <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and substring-after(.,substring-before(.,'/OsAppMode'))='/OsAppMode']/..">
                  <xsl:call-template name="ECUM_APPMODE_TYPE_GEN_3_0" />
                </xsl:for-each>
              </COMPU-SCALES>
            </COMPU-INTERNAL-TO-PHYS>
          </COMPU-METHOD>
        </xsl:if>
      </xsl:if>
      <xsl:if test="$GEN_BOOT_TARGET_PORT = 'true'">
        <INTEGER-TYPE>
          <SHORT-NAME>EcuM_BootTargetType</SHORT-NAME>
          <xsl:call-template name="ECUM_DV_SDG_ADMIN_DATA_TEMPLATE" />
          <SW-DATA-DEF-PROPS>
            <COMPU-METHOD-REF DEST="COMPU-METHOD">/DataType/EcuM_BootTrgtType_COMPU_METHOD</COMPU-METHOD-REF>
          </SW-DATA-DEF-PROPS>
          <LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
          <UPPER-LIMIT INTERVAL-TYPE="CLOSED">1</UPPER-LIMIT>
        </INTEGER-TYPE>
        <COMPU-METHOD>
          <SHORT-NAME>EcuM_BootTrgtType_COMPU_METHOD</SHORT-NAME>
          <COMPU-INTERNAL-TO-PHYS>
            <COMPU-SCALES>
              <COMPU-SCALE>
                <LOWER-LIMIT>0</LOWER-LIMIT>
                <UPPER-LIMIT>0</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_BOOT_TARGET_APP</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>1</LOWER-LIMIT>
                <UPPER-LIMIT>1</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_BOOT_TARGET_BOOTLOADER</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
            </COMPU-SCALES>
          </COMPU-INTERNAL-TO-PHYS>
        </COMPU-METHOD>
      </xsl:if>
      <xsl:if test="$GEN_STATE_REQUEST_PORT = 'true' or $GEN_SHUTDOWN_PORT = 'true'">
        <COMPU-METHOD>
          <SHORT-NAME>EcuM_StateType_COMPU_METHOD</SHORT-NAME>
          <COMPU-INTERNAL-TO-PHYS>
            <COMPU-SCALES>
              <COMPU-SCALE>
                <LOWER-LIMIT>16</LOWER-LIMIT>
                <UPPER-LIMIT>16</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_STARTUP</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>17</LOWER-LIMIT>
                <UPPER-LIMIT>17</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_STARTUP_ONE</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>18</LOWER-LIMIT>
                <UPPER-LIMIT>18</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_STARTUP_TWO</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>32</LOWER-LIMIT>
                <UPPER-LIMIT>32</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_WAKEUP</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>33</LOWER-LIMIT>
                <UPPER-LIMIT>33</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_WAKEUP_ONE</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>34</LOWER-LIMIT>
                <UPPER-LIMIT>34</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_WAKEUP_VALIDATION</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>35</LOWER-LIMIT>
                <UPPER-LIMIT>35</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_WAKEUP_REACTION</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>36</LOWER-LIMIT>
                <UPPER-LIMIT>36</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_WAKEUP_TWO</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>37</LOWER-LIMIT>
                <UPPER-LIMIT>37</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_WAKEUP_WAKESLEEP</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>38</LOWER-LIMIT>
                <UPPER-LIMIT>38</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_WAKEUP_TTII</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>48</LOWER-LIMIT>
                <UPPER-LIMIT>48</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_RUN</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>50</LOWER-LIMIT>
                <UPPER-LIMIT>50</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_APP_RUN</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>51</LOWER-LIMIT>
                <UPPER-LIMIT>51</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_APP_POST_RUN</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>64</LOWER-LIMIT>
                <UPPER-LIMIT>64</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_SHUTDOWN</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>68</LOWER-LIMIT>
                <UPPER-LIMIT>68</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_PREP_SHUTDOWN</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>73</LOWER-LIMIT>
                <UPPER-LIMIT>73</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_GO_SLEEP</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>77</LOWER-LIMIT>
                <UPPER-LIMIT>77</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_GO_OFF_ONE</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>78</LOWER-LIMIT>
                <UPPER-LIMIT>78</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_GO_OFF_TWO</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>80</LOWER-LIMIT>
                <UPPER-LIMIT>80</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_SLEEP</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>128</LOWER-LIMIT>
                <UPPER-LIMIT>128</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_OFF</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>144</LOWER-LIMIT>
                <UPPER-LIMIT>144</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_RESET</VT>
                </COMPU-CONST>
              </COMPU-SCALE>
              <COMPU-SCALE>
                <LOWER-LIMIT>255</LOWER-LIMIT>
                <UPPER-LIMIT>255</UPPER-LIMIT>
                <COMPU-CONST>
                  <VT>ECUM_STATE_ERROR</VT>
                </COMPU-CONST>
              </COMPU-SCALE>              
            </COMPU-SCALES>
          </COMPU-INTERNAL-TO-PHYS>
        </COMPU-METHOD>
      </xsl:if>
  </xsl:template>

  <xsl:template name="ECUM_APPMODE_TYPE_GEN_3_0">
    <COMPU-SCALE>
      <LOWER-LIMIT><xsl:value-of select="./*[local-name() = 'PARAMETER-VALUES']/*[local-name() = 'INTEGER-VALUE' and *[local-name() = 'DEFINITION-REF' and substring-after(.,substring-before(.,'/OsAppMode/OsAppModeId'))='/OsAppMode/OsAppModeId']]/*[local-name() = 'VALUE']" /></LOWER-LIMIT>
      <UPPER-LIMIT><xsl:value-of select="./*[local-name() = 'PARAMETER-VALUES']/*[local-name() = 'INTEGER-VALUE' and *[local-name() = 'DEFINITION-REF' and substring-after(.,substring-before(.,'/OsAppMode/OsAppModeId'))='/OsAppMode/OsAppModeId']]/*[local-name() = 'VALUE']" /></UPPER-LIMIT>
      <COMPU-CONST>
        <VT>ECUM_<xsl:value-of select="./*[local-name() = 'SHORT-NAME']" /></VT>
      </COMPU-CONST>
    </COMPU-SCALE>
  </xsl:template>

  <!-- 
==================================================================================================================    
    PORT PROTOTYPES
==================================================================================================================
-->
  <!-- Port Protoype Template -->
  <xsl:template name="ECUM_PORT_PROTOTYPES">
    <PORTS>
      <xsl:call-template name="ECUM_PORT_PROTOTYPES_CONFIG_DEPENDEND" />
      <xsl:call-template name="ECUM_PORT_PROTOTYPES_STATIC" />
    </PORTS>
  </xsl:template>
  <!-- Static Port Prototypes Template -->
  <xsl:template name="ECUM_PORT_PROTOTYPES_STATIC">
    <!-- ShutdownTarget Port -->
    <xsl:if test="$GEN_SHUTDOWN_PORT = 'true'">
      <P-PORT-PROTOTYPE>
        <SHORT-NAME>shutdownTarget</SHORT-NAME>
        <DESC>
          <L-2 L="EN">P-Port Prototype of EcuM for selecting and retrieving the shutdown target and last shutdown target.</L-2>
        </DESC>
        <PROVIDED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">/PortInterface/EcuM_ShutdownTarget</PROVIDED-INTERFACE-TREF>
      </P-PORT-PROTOTYPE>
    </xsl:if>
    <!-- BootTarget Port -->
    <xsl:if test="$GEN_BOOT_TARGET_PORT = 'true'">
      <P-PORT-PROTOTYPE>
        <SHORT-NAME>bootTarget</SHORT-NAME>
        <DESC>
          <L-2 L="EN">P-Port Prototype of EcuM for selecting and retrieving the boot target.</L-2>
        </DESC>        
        <PROVIDED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">/PortInterface/EcuM_BootTarget</PROVIDED-INTERFACE-TREF>
      </P-PORT-PROTOTYPE>
    </xsl:if>
    <xsl:if test="$GEN_APPLICATION_MODE_PORT = 'true'">
      <xsl:if test="$OS_COUNT != 0">
        <P-PORT-PROTOTYPE>
          <SHORT-NAME>applicationMode</SHORT-NAME>
          <DESC>
            <L-2 L="EN">P-Port Prototype EcuM for of selecting and retrieving the shutdown target the application mode.</L-2>
          </DESC>          
          <PROVIDED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">/PortInterface/EcuM_ApplicationMode</PROVIDED-INTERFACE-TREF>
        </P-PORT-PROTOTYPE>
      </xsl:if>
    </xsl:if>
    <!-- mode switch port generation -->
    <xsl:if test="$GEN_MODE_SWITCH_PORT = 'true' and $INCLUDE_RTE = 'true'">
      <P-PORT-PROTOTYPE>
        <SHORT-NAME>currentMode</SHORT-NAME>
        <PROVIDED-COM-SPECS>
          <MODE-SWITCH-COM-SPEC>
            <MODE-GROUP-REF DEST="MODE-DECLARATION-GROUP-PROTOTYPE">/PortInterface/EcuM_CurrentMode/currentMode</MODE-GROUP-REF>
  		    <MODE-SWITCHED-ACK>
				<TIMEOUT>0.000000000</TIMEOUT>
			</MODE-SWITCHED-ACK>
            <QUEUE-LENGTH>2</QUEUE-LENGTH>
          </MODE-SWITCH-COM-SPEC>
        </PROVIDED-COM-SPECS>
        <PROVIDED-INTERFACE-TREF DEST="SENDER-RECEIVER-INTERFACE">/PortInterface/EcuM_CurrentMode</PROVIDED-INTERFACE-TREF>
      </P-PORT-PROTOTYPE>
    </xsl:if>
  </xsl:template>
  <!-- Configuration dependend Port Prototypes Template -->
  <xsl:template name="ECUM_PORT_PROTOTYPES_CONFIG_DEPENDEND">
    <xsl:if test="$GEN_STATE_REQUEST_PORT = 'true'">      
      <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/EcuM']/../*[local-name() = 'CONTAINERS']/*[local-name() = 'CONTAINER']">
    <xsl:if test="*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/EcuM/EcuMConfiguration']">
      <xsl:call-template name="ECUM_PORT_PROTOTYPES_CONFIG_DEPENDEND_USER">
        <xsl:with-param name="RuntimeId" select="position()" />
      </xsl:call-template>
    </xsl:if>
      </xsl:for-each>
    </xsl:if>
  </xsl:template>
  <xsl:template name="ECUM_PORT_PROTOTYPES_CONFIG_DEPENDEND_USER">
    <xsl:param name="RuntimeId"/>
    <xsl:for-each select=".//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/EcuM/EcuMConfiguration/EcuMUserConfig/EcuMUser']/../*[local-name() = 'VALUE']">
      <xsl:call-template name="ECUM_PORT_PROTOTYPES_CONFIG_DEPENDEND_3_0">
        <xsl:with-param name="RuntimeId" select="$RuntimeId" />
      </xsl:call-template>
    </xsl:for-each>
  </xsl:template>
  <!-- Configuration dependend Port Prototypes Template -->
  <xsl:template name="ECUM_PORT_PROTOTYPES_CONFIG_DEPENDEND_3_0">
    <xsl:param name="RuntimeId"/>
    <xsl:variable name="CURRENT_USER" select="../../../*[local-name() = 'SHORT-NAME']" />
    <xsl:if test="not(//*[./*
                            [local-name() = 'DEFINITION-REF' and .='/MICROSAR/EcuM/EcuMConfiguration']
                          and position() &lt; $RuntimeId 
                          and .//*[./*
                                     [local-name() = 'DEFINITION-REF' and .='/MICROSAR/EcuM/EcuMConfiguration/EcuMUserConfig']
                                   and 
                                   ./*
                                     [local-name() = 'SHORT-NAME' and .=$CURRENT_USER]
                                  ]
                          ])">
    <P-PORT-PROTOTYPE>
      <SHORT-NAME><xsl:value-of select="../../../*[local-name() = 'SHORT-NAME']" /></SHORT-NAME>
      <DESC>
        <L-2 L="EN">P-Port Prototype of EcuM for requesting and releasing RUN state for EcuM user <xsl:value-of select="." />.</L-2>
      </DESC>
      <PROVIDED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">/PortInterface/EcuM_StateRequest</PROVIDED-INTERFACE-TREF>
    </P-PORT-PROTOTYPE>
    </xsl:if>
  </xsl:template>
  <!-- 
==================================================================================================================    
    IMPLEMENTATION
==================================================================================================================
-->
  <!-- Runnables Template -->
  <xsl:template name="ECUM_IMPLEMENTATION">
    <SWC-IMPLEMENTATION>
      <SHORT-NAME><xsl:value-of select="$COMP_NAME" />Impl</SHORT-NAME>              
      <BEHAVIOR-REF DEST="INTERNAL-BEHAVIOR">/ComponentType/<xsl:value-of select="$COMP_NAME" />Behave</BEHAVIOR-REF>              
    </SWC-IMPLEMENTATION>
  </xsl:template>
  <!-- 
==================================================================================================================    
    INTERNAL BEHAVIOR
==================================================================================================================
-->
  <!-- Runnables Template -->
  <xsl:template name="ECUM_INTERNAL_BEHAVIOR">
      <INTERNAL-BEHAVIOR>
        <SHORT-NAME><xsl:value-of select="$COMP_NAME" />Behave</SHORT-NAME>
        <COMPONENT-REF DEST="SERVICE-COMPONENT-TYPE">/ComponentType/<xsl:value-of select="$COMP_NAME" /></COMPONENT-REF>
        <xsl:call-template name="ECUM_OPERATION_INVOKED_EVENTS" />
        <xsl:call-template name="ECUM_PORT_DEFINED_ARGUMENTS" />
        <xsl:call-template name="ECUM_RUNNABLES" />
      </INTERNAL-BEHAVIOR>
  </xsl:template>
  <!-- 
==================================================================================================================    
    RUNNABLES
==================================================================================================================
-->
  <!-- Runnables Template -->
  <xsl:template name="ECUM_RUNNABLES">
        <RUNNABLES>
          <xsl:if test="$GEN_STATE_REQUEST_PORT = 'true'">
            <RUNNABLE-ENTITY>
              <SHORT-NAME>RequestRUN</SHORT-NAME>
              <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
              <SYMBOL>EcuM_RequestRUN</SYMBOL>
            </RUNNABLE-ENTITY>
            <RUNNABLE-ENTITY>
              <SHORT-NAME>ReleaseRUN</SHORT-NAME>
              <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
              <SYMBOL>EcuM_ReleaseRUN</SYMBOL>
            </RUNNABLE-ENTITY>
            <RUNNABLE-ENTITY>
              <SHORT-NAME>RequestPOSTRUN</SHORT-NAME>
              <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
              <SYMBOL>EcuM_RequestPOST_RUN</SYMBOL>
            </RUNNABLE-ENTITY>
            <RUNNABLE-ENTITY>
              <SHORT-NAME>ReleasePOSTRUN</SHORT-NAME>
              <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
              <SYMBOL>EcuM_ReleasePOST_RUN</SYMBOL>
            </RUNNABLE-ENTITY>
            <RUNNABLE-ENTITY>
              <SHORT-NAME>GetState</SHORT-NAME>
              <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
              <SYMBOL>EcuM_GetStateWrapper</SYMBOL>
            </RUNNABLE-ENTITY>            
          </xsl:if>
          <xsl:if test="$GEN_SHUTDOWN_PORT = 'true'">
            <RUNNABLE-ENTITY>
              <SHORT-NAME>SelectShutdownTarget</SHORT-NAME>
              <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
              <SYMBOL>EcuM_SelectShutdownTarget</SYMBOL>
            </RUNNABLE-ENTITY>
            
            <RUNNABLE-ENTITY>
              <SHORT-NAME>GetShutdownTarget</SHORT-NAME>
              <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
              <SYMBOL>EcuM_GetShutdownTarget</SYMBOL>
            </RUNNABLE-ENTITY>

            <RUNNABLE-ENTITY>
              <SHORT-NAME>GetLastShutdownTarget</SHORT-NAME>
              <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
              <SYMBOL>EcuM_GetLastShutdownTarget</SYMBOL>               
            </RUNNABLE-ENTITY>
            
          </xsl:if>
          <xsl:if test="$GEN_BOOT_TARGET_PORT = 'true'">
            <RUNNABLE-ENTITY>
              <SHORT-NAME>SelectBootTarget</SHORT-NAME>
              <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
              <SYMBOL>EcuM_SelectBootTarget</SYMBOL>
            </RUNNABLE-ENTITY>
            <RUNNABLE-ENTITY>
              <SHORT-NAME>GetBootTarget</SHORT-NAME>
              <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
              <SYMBOL>EcuM_GetBootTarget</SYMBOL>
            </RUNNABLE-ENTITY>
          </xsl:if>
          <xsl:if test="$OS_COUNT != 0">
            <xsl:if test="$GEN_APPLICATION_MODE_PORT = 'true'">
              <RUNNABLE-ENTITY>
                <SHORT-NAME>SelectApplicationMode</SHORT-NAME>
                <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
                <SYMBOL>EcuM_Rte_SelectApplicationMode</SYMBOL>
              </RUNNABLE-ENTITY>
              <RUNNABLE-ENTITY>
                <SHORT-NAME>GetApplicationMode</SHORT-NAME>
                <CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
                <SYMBOL>EcuM_Rte_GetApplicationMode</SYMBOL>
              </RUNNABLE-ENTITY>
            </xsl:if>
          </xsl:if>
          <xsl:if test="$GEN_MODE_SWITCH_PORT = 'true' and $INCLUDE_RTE = 'true'">
            <RUNNABLE-ENTITY>
              <SHORT-NAME>EcuM_MainFunction</SHORT-NAME>
              <CAN-BE-INVOKED-CONCURRENTLY>false</CAN-BE-INVOKED-CONCURRENTLY>
              <MODE-SWITCH-POINTS>
                <MODE-SWITCH-POINT>
                  <SHORT-NAME>SEND_ECUM_MAINFUNCTION</SHORT-NAME>
                  <MODE-GROUP-IREF>
                    <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME" />/currentMode</P-PORT-PROTOTYPE-REF>
                    <MODE-DECLARATION-GROUP-PROTOTYPE-REF DEST="MODE-DECLARATION-GROUP-PROTOTYPE">/PortInterface/EcuM_CurrentMode/currentMode</MODE-DECLARATION-GROUP-PROTOTYPE-REF>
                  </MODE-GROUP-IREF>
                </MODE-SWITCH-POINT>
              </MODE-SWITCH-POINTS>
              <SYMBOL>EcuM_MainFunction</SYMBOL>
            </RUNNABLE-ENTITY>
          </xsl:if>
          <xsl:if test="$GEN_MODE_SWITCH_PORT = 'false' and $INCLUDE_RTE = 'true'">
            <RUNNABLE-ENTITY>
              <SHORT-NAME>EcuM_MainFunction</SHORT-NAME>
              <CAN-BE-INVOKED-CONCURRENTLY>false</CAN-BE-INVOKED-CONCURRENTLY>
              <SYMBOL>EcuM_MainFunction</SYMBOL>               
            </RUNNABLE-ENTITY>
          </xsl:if>   
        </RUNNABLES>
  </xsl:template>
  <!-- 
==================================================================================================================    
    PORT DEFINED ARGUMENTS
==================================================================================================================
-->
  <!-- Port defined Arguments Template -->
  <xsl:template name="ECUM_PORT_DEFINED_ARGUMENTS">
    <xsl:if test="$GEN_STATE_REQUEST_PORT = 'true'">
      <PORT-API-OPTIONS>
      <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/EcuM']/../*[local-name() = 'CONTAINERS']/*[local-name() = 'CONTAINER']">
    <xsl:if test="*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/EcuM/EcuMConfiguration']">
      <xsl:call-template name="ECUM_PORT_DEFINED_ARGUMENTS_USER">
        <xsl:with-param name="RuntimeId" select="position()" />
      </xsl:call-template>
    </xsl:if>
      </xsl:for-each>
      </PORT-API-OPTIONS>
    </xsl:if>
  </xsl:template>
  <xsl:template name="ECUM_PORT_DEFINED_ARGUMENTS_USER">
    <xsl:param name="RuntimeId"/>
    <xsl:for-each select=".//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/EcuM/EcuMConfiguration/EcuMUserConfig/EcuMUser']/../*[local-name() = 'VALUE']">
      <xsl:call-template name="ECUM_PORT_DEFINED_ARGUMENTS_3_0">
        <xsl:with-param name="RuntimeId" select="$RuntimeId" />
      </xsl:call-template>
    </xsl:for-each>
  </xsl:template>
  <!-- 
==================================================================================================================    
    PORT DEFINED ARGUMENTS 
==================================================================================================================
-->
  <!-- Port defined Arguments Template -->
  <xsl:template name="ECUM_PORT_DEFINED_ARGUMENTS_3_0">
    <xsl:param name="RuntimeId"/>
    <xsl:variable name="CURRENT_USER" select="../../../*[local-name() = 'SHORT-NAME']" />
    <xsl:if test="not(//*[./*
                            [local-name() = 'DEFINITION-REF' and .='/MICROSAR/EcuM/EcuMConfiguration']
                          and position() &lt; $RuntimeId 
                          and .//*[./*
                                     [local-name() = 'DEFINITION-REF' and .='/MICROSAR/EcuM/EcuMConfiguration/EcuMUserConfig']
                                   and 
                                   ./*
                                     [local-name() = 'SHORT-NAME' and .=$CURRENT_USER]
                                  ]
                          ])">
    <PORT-API-OPTION>
      <PORT-ARG-VALUES>
        <INTEGER-LITERAL>
          <SHORT-NAME><xsl:value-of select="../../../*[local-name() = 'SHORT-NAME']" /></SHORT-NAME>
          <TYPE-TREF DEST="INTEGER-TYPE">/DataType/EcuM_UserType</TYPE-TREF>
          <VALUE><xsl:value-of select="." /></VALUE>
        </INTEGER-LITERAL>
      </PORT-ARG-VALUES>
      <PORT-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME" />/<xsl:value-of select="../../../*[local-name() = 'SHORT-NAME']" /></PORT-REF>
    </PORT-API-OPTION>
    </xsl:if>
  </xsl:template>
  <!-- 
==================================================================================================================    
    OPERATION INVOKED EVENTS
==================================================================================================================
-->
  <!-- Operation Invoked events Template -->
  <xsl:template name="ECUM_OPERATION_INVOKED_EVENTS">
    <EVENTS>      
      <xsl:if test="$INCLUDE_RTE = 'true'">
        <TIMING-EVENT>
          <SHORT-NAME>TMT_EcuM_MainFunction</SHORT-NAME>
          <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME" />Behave/EcuM_MainFunction</START-ON-EVENT-REF>
          <PERIOD><xsl:value-of select="$ECUM_MAINFUNCTION_PERIOD"/></PERIOD>
        </TIMING-EVENT>        
      </xsl:if>
        <xsl:if test="$GEN_STATE_REQUEST_PORT = 'true'">
      <xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/EcuM']/../*[local-name() = 'CONTAINERS']/*[local-name() = 'CONTAINER']">
      <xsl:if test="*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/EcuM/EcuMConfiguration']">
        <xsl:call-template name="ECUM_OPERATION_INVOKED_EVENTS_USER">
          <xsl:with-param name="RuntimeId" select="position()" />
        </xsl:call-template>
      </xsl:if>
      </xsl:for-each>
      </xsl:if>
      <xsl:call-template name="ECUM_OPERATION_INVOKED_EVENTSSTATIC3_0" />
    </EVENTS>
  </xsl:template>
  <xsl:template name="ECUM_OPERATION_INVOKED_EVENTS_USER">
    <xsl:param name="RuntimeId"/>
    <xsl:for-each select=".//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/EcuM/EcuMConfiguration/EcuMUserConfig/EcuMUser']/../*[local-name() = 'VALUE']">
      <xsl:call-template name="ECUM_OPERATION_INVOKED_EVENTS_CONFIG_3_0">
        <xsl:with-param name="RuntimeId" select="$RuntimeId" />
      </xsl:call-template>
    </xsl:for-each>
  </xsl:template>

  <!-- Operation Invoked events Template -->
  <xsl:template name="ECUM_OPERATION_INVOKED_EVENTSSTATIC3_0">
    <!-- ShutdownTarget Operations -->
    <xsl:if test="$GEN_SHUTDOWN_PORT = 'true'">
      <OPERATION-INVOKED-EVENT>
        <SHORT-NAME>V_ECUM_SELECT_SHUTDOWN_TARGET</SHORT-NAME>
        <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME" />Behave/SelectShutdownTarget</START-ON-EVENT-REF>
        <OPERATION-IREF>
          <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME" />/shutdownTarget</P-PORT-PROTOTYPE-REF>
          <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/EcuM_ShutdownTarget/SelectShutdownTarget</OPERATION-PROTOTYPE-REF>
        </OPERATION-IREF>
      </OPERATION-INVOKED-EVENT>
      <OPERATION-INVOKED-EVENT>
        <SHORT-NAME>V_ECUM_GET_SHUTDOWN_TARGET</SHORT-NAME>
        <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME" />Behave/GetShutdownTarget</START-ON-EVENT-REF>
        <OPERATION-IREF>
          <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME" />/shutdownTarget</P-PORT-PROTOTYPE-REF>
          <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/EcuM_ShutdownTarget/GetShutdownTarget</OPERATION-PROTOTYPE-REF>
        </OPERATION-IREF>
      </OPERATION-INVOKED-EVENT>
      <OPERATION-INVOKED-EVENT>
        <SHORT-NAME>V_ECUM_GET_LAST_SHUTDOWN_TARGET</SHORT-NAME>
        <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME" />Behave/GetLastShutdownTarget</START-ON-EVENT-REF>                  
        <OPERATION-IREF>
          <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME" />/shutdownTarget</P-PORT-PROTOTYPE-REF>                     
          <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/EcuM_ShutdownTarget/GetLastShutdownTarget</OPERATION-PROTOTYPE-REF>
        </OPERATION-IREF>
      </OPERATION-INVOKED-EVENT>      
    </xsl:if>
    <!--  BootTarget Operations -->
    <xsl:if test="$GEN_BOOT_TARGET_PORT = 'true'">
      <OPERATION-INVOKED-EVENT>
        <SHORT-NAME>V_ECUM_SELECT_BOOT_TARGET</SHORT-NAME>
        <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME" />Behave/SelectBootTarget</START-ON-EVENT-REF>
        <OPERATION-IREF>
          <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME" />/bootTarget</P-PORT-PROTOTYPE-REF>
          <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/EcuM_BootTarget/SelectBootTarget</OPERATION-PROTOTYPE-REF>
        </OPERATION-IREF>
      </OPERATION-INVOKED-EVENT>
      <OPERATION-INVOKED-EVENT>
        <SHORT-NAME>V_ECUM_GET_BOOT_TARGET</SHORT-NAME>
        <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME" />Behave/GetBootTarget</START-ON-EVENT-REF>
        <OPERATION-IREF>
          <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME" />/bootTarget</P-PORT-PROTOTYPE-REF>
          <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/EcuM_BootTarget/GetBootTarget</OPERATION-PROTOTYPE-REF>
        </OPERATION-IREF>
      </OPERATION-INVOKED-EVENT>
    </xsl:if>
    <xsl:if test="$GEN_APPLICATION_MODE_PORT = 'true'">
    <xsl:if test="$OS_COUNT != 0">
      <OPERATION-INVOKED-EVENT>
      <SHORT-NAME>V_ECUM_SET_APPL_MODE</SHORT-NAME>
      <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME" />Behave/SelectApplicationMode</START-ON-EVENT-REF>
      <OPERATION-IREF>
        <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME" />/applicationMode</P-PORT-PROTOTYPE-REF>
        <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/EcuM_ApplicationMode/SelectApplicationMode</OPERATION-PROTOTYPE-REF>
      </OPERATION-IREF>
      </OPERATION-INVOKED-EVENT>
      <OPERATION-INVOKED-EVENT>
      <SHORT-NAME>V_ECUM_GET_APPL_MODE</SHORT-NAME>
      <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME" />Behave/GetApplicationMode</START-ON-EVENT-REF>
      <OPERATION-IREF>
        <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME" />/applicationMode</P-PORT-PROTOTYPE-REF>
        <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/EcuM_ApplicationMode/GetApplicationMode</OPERATION-PROTOTYPE-REF>
      </OPERATION-IREF>
      </OPERATION-INVOKED-EVENT>
    </xsl:if>
    </xsl:if>
  </xsl:template>

  <!-- Operation Invoked events Template -->
  <xsl:template name="ECUM_OPERATION_INVOKED_EVENTS_CONFIG_3_0">
    <xsl:param name="RuntimeId"/>
    <xsl:variable name="CURRENT_USER" select="../../../*[local-name() = 'SHORT-NAME']" />
    <xsl:if test="not(//*[./*
                            [local-name() = 'DEFINITION-REF' and .='/MICROSAR/EcuM/EcuMConfiguration']
                          and position() &lt; $RuntimeId 
                          and .//*[./*
                                     [local-name() = 'DEFINITION-REF' and .='/MICROSAR/EcuM/EcuMConfiguration/EcuMUserConfig']
                                   and 
                                   ./*
                                     [local-name() = 'SHORT-NAME' and .=$CURRENT_USER]
                                  ]
                          ])">
    <xsl:variable name="SR_Number">
      <xsl:choose>
        <xsl:when test=". &lt; 9">SR<xsl:value-of select="$RuntimeId" />00<xsl:value-of select=". + 1" /></xsl:when>
        <xsl:when test=". &lt; 99">SR<xsl:value-of select="$RuntimeId" />0<xsl:value-of select=". + 1" /></xsl:when>
        <xsl:otherwise>SR<xsl:value-of select="$RuntimeId" /><xsl:value-of select=". + 1" /></xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <OPERATION-INVOKED-EVENT>
      <SHORT-NAME>V_ECUM_<xsl:value-of select="$SR_Number" />_REQUEST_RUN</SHORT-NAME>
      <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME" />Behave/RequestRUN</START-ON-EVENT-REF>
      <OPERATION-IREF>
        <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME" />/<xsl:value-of select="../../../*[local-name() = 'SHORT-NAME']" /></P-PORT-PROTOTYPE-REF>
        <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/EcuM_StateRequest/RequestRUN</OPERATION-PROTOTYPE-REF>
      </OPERATION-IREF>
    </OPERATION-INVOKED-EVENT>
    <OPERATION-INVOKED-EVENT>
      <SHORT-NAME>V_ECUM_<xsl:value-of select="$SR_Number" />_RELEASE_RUN</SHORT-NAME>
      <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME" />Behave/ReleaseRUN</START-ON-EVENT-REF>
      <OPERATION-IREF>
        <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME" />/<xsl:value-of select="../../../*[local-name() = 'SHORT-NAME']" /></P-PORT-PROTOTYPE-REF>
        <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/EcuM_StateRequest/ReleaseRUN</OPERATION-PROTOTYPE-REF>
      </OPERATION-IREF>
    </OPERATION-INVOKED-EVENT>
    <OPERATION-INVOKED-EVENT>
      <SHORT-NAME>V_ECUM_<xsl:value-of select="$SR_Number" />_REQUEST_POST_RUN</SHORT-NAME>
      <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME" />Behave/RequestPOSTRUN</START-ON-EVENT-REF>
      <OPERATION-IREF>
        <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME" />/<xsl:value-of select="../../../*[local-name() = 'SHORT-NAME']" /></P-PORT-PROTOTYPE-REF>
        <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/EcuM_StateRequest/RequestPOSTRUN</OPERATION-PROTOTYPE-REF>
      </OPERATION-IREF>
    </OPERATION-INVOKED-EVENT>
    
    <OPERATION-INVOKED-EVENT>
      <SHORT-NAME>V_ECUM_<xsl:value-of select="$SR_Number" />_RELEASE_POST_RUN</SHORT-NAME>
      <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME" />Behave/ReleasePOSTRUN</START-ON-EVENT-REF>
      <OPERATION-IREF>
        <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME" />/<xsl:value-of select="../../../*[local-name() = 'SHORT-NAME']" /></P-PORT-PROTOTYPE-REF>
        <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/EcuM_StateRequest/ReleasePOSTRUN</OPERATION-PROTOTYPE-REF>
      </OPERATION-IREF>
    </OPERATION-INVOKED-EVENT>
    
    <OPERATION-INVOKED-EVENT>
      <SHORT-NAME>V_ECUM_<xsl:value-of select="$SR_Number" />_GET_STATE</SHORT-NAME>
      <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME" />Behave/GetState</START-ON-EVENT-REF>
      <OPERATION-IREF>
        <P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME" />/<xsl:value-of select="../../../*[local-name() = 'SHORT-NAME']" /></P-PORT-PROTOTYPE-REF>
        <OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/EcuM_StateRequest/GetState</OPERATION-PROTOTYPE-REF>
      </OPERATION-IREF>
    </OPERATION-INVOKED-EVENT>
    </xsl:if>     
  </xsl:template>
  <!-- 
==================================================================================================================    
    PORT INTERFACES
==================================================================================================================
-->
  <!-- Port Interface Template -->
  <xsl:template name="ECUM_PORT_INTERFACES">
    <xsl:call-template name="ECUM_PORT_INTERFACES_3_0" />
  </xsl:template>

  <!-- 
==================================================================================================================    
    PORT INTERFACES 
==================================================================================================================
-->
  <!-- Port Interface Template -->
  <xsl:template name="ECUM_PORT_INTERFACES_3_0">
    <SHORT-NAME>PortInterface</SHORT-NAME>
    <ELEMENTS>
      <!-- current mode interface -->
      <xsl:if test="$GEN_MODE_SWITCH_PORT = 'true' and $INCLUDE_RTE = 'true'">
        <SENDER-RECEIVER-INTERFACE>
          <SHORT-NAME>EcuM_CurrentMode</SHORT-NAME>
          <xsl:call-template name="ECUM_DV_SDG_ADMIN_DATA_TEMPLATE" />
          <IS-SERVICE>true</IS-SERVICE>
          <MODE-GROUPS>
            <MODE-DECLARATION-GROUP-PROTOTYPE>
              <SHORT-NAME>currentMode</SHORT-NAME>
              <TYPE-TREF DEST="MODE-DECLARATION-GROUP">/ModeDeclarationGroup/EcuM_Mode</TYPE-TREF>
            </MODE-DECLARATION-GROUP-PROTOTYPE>
          </MODE-GROUPS>
        </SENDER-RECEIVER-INTERFACE>  
      </xsl:if>            
      <!-- EcuM_StateRequest interface -->
      <xsl:if test="$GEN_STATE_REQUEST_PORT = 'true'">
        <CLIENT-SERVER-INTERFACE>
          <SHORT-NAME>EcuM_StateRequest</SHORT-NAME>
          <xsl:call-template name="ECUM_DV_SDG_ADMIN_DATA_TEMPLATE" />
          <IS-SERVICE>true</IS-SERVICE>
          <OPERATIONS>
            <OPERATION-PROTOTYPE>
              <SHORT-NAME>RequestRUN</SHORT-NAME>
              <POSSIBLE-ERROR-REFS>
                <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/EcuM_StateRequest/E_NOT_OK</POSSIBLE-ERROR-REF>
              </POSSIBLE-ERROR-REFS>
            </OPERATION-PROTOTYPE>
            <OPERATION-PROTOTYPE>
              <SHORT-NAME>ReleaseRUN</SHORT-NAME>
              <POSSIBLE-ERROR-REFS>
                <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/EcuM_StateRequest/E_NOT_OK</POSSIBLE-ERROR-REF>
              </POSSIBLE-ERROR-REFS>
            </OPERATION-PROTOTYPE>
            <OPERATION-PROTOTYPE>
              <SHORT-NAME>RequestPOSTRUN</SHORT-NAME>
              <POSSIBLE-ERROR-REFS>
                <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/EcuM_StateRequest/E_NOT_OK</POSSIBLE-ERROR-REF>
              </POSSIBLE-ERROR-REFS>
            </OPERATION-PROTOTYPE>
            <OPERATION-PROTOTYPE>
              <SHORT-NAME>ReleasePOSTRUN</SHORT-NAME>
              <POSSIBLE-ERROR-REFS>
                <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/EcuM_StateRequest/E_NOT_OK</POSSIBLE-ERROR-REF>
              </POSSIBLE-ERROR-REFS>
            </OPERATION-PROTOTYPE>
            <OPERATION-PROTOTYPE>
              <SHORT-NAME>GetState</SHORT-NAME>
              <ARGUMENTS>
                <ARGUMENT-PROTOTYPE>
                  <SHORT-NAME>state</SHORT-NAME>
                  <TYPE-TREF DEST="INTEGER-TYPE">/DataType/EcuM_StateType</TYPE-TREF>
                  <DIRECTION>OUT</DIRECTION>
                </ARGUMENT-PROTOTYPE>
              </ARGUMENTS>
              <POSSIBLE-ERROR-REFS>
                <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/EcuM_StateRequest/E_NOT_OK</POSSIBLE-ERROR-REF>
              </POSSIBLE-ERROR-REFS>
            </OPERATION-PROTOTYPE>                        
          </OPERATIONS>
          <POSSIBLE-ERRORS>
            <APPLICATION-ERROR>
              <SHORT-NAME>E_NOT_OK</SHORT-NAME>
              <ERROR-CODE>1</ERROR-CODE>
            </APPLICATION-ERROR>
          </POSSIBLE-ERRORS>
        </CLIENT-SERVER-INTERFACE>
      </xsl:if>
      <!--EcuM_ShutdownTarget interface-->
      <xsl:if test="$GEN_SHUTDOWN_PORT = 'true'">
        <CLIENT-SERVER-INTERFACE>
          <SHORT-NAME>EcuM_ShutdownTarget</SHORT-NAME>
          <xsl:call-template name="ECUM_DV_SDG_ADMIN_DATA_TEMPLATE" />
          <IS-SERVICE>true</IS-SERVICE>
          <OPERATIONS>
            <OPERATION-PROTOTYPE>
              <SHORT-NAME>SelectShutdownTarget</SHORT-NAME>
              <ARGUMENTS>
                <ARGUMENT-PROTOTYPE>
                  <SHORT-NAME>state</SHORT-NAME>
                  <TYPE-TREF DEST="INTEGER-TYPE">/DataType/EcuM_StateType</TYPE-TREF>
                  <DIRECTION>IN</DIRECTION>
                </ARGUMENT-PROTOTYPE>
                <ARGUMENT-PROTOTYPE>
                  <SHORT-NAME>mode</SHORT-NAME>
                  <TYPE-TREF DEST="INTEGER-TYPE">/DataType/UInt8</TYPE-TREF>
                  <DIRECTION>IN</DIRECTION>
                </ARGUMENT-PROTOTYPE>                
              </ARGUMENTS>
              <POSSIBLE-ERROR-REFS>
                <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/EcuM_ShutdownTarget/E_NOT_OK</POSSIBLE-ERROR-REF>
              </POSSIBLE-ERROR-REFS>
            </OPERATION-PROTOTYPE>
            <OPERATION-PROTOTYPE>
              <SHORT-NAME>GetShutdownTarget</SHORT-NAME>
              <ARGUMENTS>
                <ARGUMENT-PROTOTYPE>
                  <SHORT-NAME>state</SHORT-NAME>
                  <TYPE-TREF DEST="INTEGER-TYPE">/DataType/EcuM_StateType</TYPE-TREF>
                  <DIRECTION>OUT</DIRECTION>
                </ARGUMENT-PROTOTYPE>
                <ARGUMENT-PROTOTYPE>
                  <SHORT-NAME>mode</SHORT-NAME>
                  <TYPE-TREF DEST="INTEGER-TYPE">/DataType/UInt8</TYPE-TREF>
                  <DIRECTION>OUT</DIRECTION>
                </ARGUMENT-PROTOTYPE>                
              </ARGUMENTS>
              <POSSIBLE-ERROR-REFS>
                <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/EcuM_ShutdownTarget/E_NOT_OK</POSSIBLE-ERROR-REF>
              </POSSIBLE-ERROR-REFS>
            </OPERATION-PROTOTYPE>

            <OPERATION-PROTOTYPE>
              <SHORT-NAME>GetLastShutdownTarget</SHORT-NAME>
              <ARGUMENTS>
                <ARGUMENT-PROTOTYPE>
                  <SHORT-NAME>state</SHORT-NAME>
                  <TYPE-TREF DEST="INTEGER-TYPE">/DataType/EcuM_StateType</TYPE-TREF>
                  <DIRECTION>OUT</DIRECTION>
                </ARGUMENT-PROTOTYPE>
                <ARGUMENT-PROTOTYPE>
                  <SHORT-NAME>mode</SHORT-NAME>
                  <TYPE-TREF DEST="INTEGER-TYPE">/DataType/UInt8</TYPE-TREF>
                  <DIRECTION>OUT</DIRECTION>
                </ARGUMENT-PROTOTYPE>
              </ARGUMENTS>
              <POSSIBLE-ERROR-REFS>
                <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/EcuM_ShutdownTarget/E_NOT_OK</POSSIBLE-ERROR-REF>
              </POSSIBLE-ERROR-REFS>
            </OPERATION-PROTOTYPE>            
            
          </OPERATIONS>
          <POSSIBLE-ERRORS>
            <APPLICATION-ERROR>
              <SHORT-NAME>E_NOT_OK</SHORT-NAME>
              <ERROR-CODE>1</ERROR-CODE>
            </APPLICATION-ERROR>
          </POSSIBLE-ERRORS>
        </CLIENT-SERVER-INTERFACE>
      </xsl:if>
      <!--EcuM_BootTarget interface-->
      <xsl:if test="$GEN_BOOT_TARGET_PORT = 'true'">
        <CLIENT-SERVER-INTERFACE>
          <SHORT-NAME>EcuM_BootTarget</SHORT-NAME>
          <xsl:call-template name="ECUM_DV_SDG_ADMIN_DATA_TEMPLATE" />
          <IS-SERVICE>true</IS-SERVICE>
          <OPERATIONS>
            <OPERATION-PROTOTYPE>
              <SHORT-NAME>SelectBootTarget</SHORT-NAME>
              <ARGUMENTS>
                <ARGUMENT-PROTOTYPE>
                  <SHORT-NAME>target</SHORT-NAME>
                  <TYPE-TREF DEST="INTEGER-TYPE">/DataType/EcuM_BootTargetType</TYPE-TREF>
                  <DIRECTION>IN</DIRECTION>
                </ARGUMENT-PROTOTYPE>
              </ARGUMENTS>
              <POSSIBLE-ERROR-REFS>
                <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/EcuM_BootTarget/E_NOT_OK</POSSIBLE-ERROR-REF>
              </POSSIBLE-ERROR-REFS>
            </OPERATION-PROTOTYPE>
            <OPERATION-PROTOTYPE>
              <SHORT-NAME>GetBootTarget</SHORT-NAME>
              <ARGUMENTS>
                <ARGUMENT-PROTOTYPE>
                  <SHORT-NAME>state</SHORT-NAME>
                  <TYPE-TREF DEST="INTEGER-TYPE">/DataType/EcuM_BootTargetType</TYPE-TREF>
                  <DIRECTION>OUT</DIRECTION>
                </ARGUMENT-PROTOTYPE>
              </ARGUMENTS>
              <POSSIBLE-ERROR-REFS>
                <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/EcuM_BootTarget/E_NOT_OK</POSSIBLE-ERROR-REF>
              </POSSIBLE-ERROR-REFS>
            </OPERATION-PROTOTYPE>
          </OPERATIONS>
          <POSSIBLE-ERRORS>
            <APPLICATION-ERROR>
              <SHORT-NAME>E_NOT_OK</SHORT-NAME>
              <ERROR-CODE>1</ERROR-CODE>
            </APPLICATION-ERROR>
          </POSSIBLE-ERRORS>
        </CLIENT-SERVER-INTERFACE>
      </xsl:if>
      <xsl:if test="$GEN_APPLICATION_MODE_PORT = 'true'">
        <xsl:if test="$OS_COUNT != 0">
          <CLIENT-SERVER-INTERFACE>
            <SHORT-NAME>EcuM_ApplicationMode</SHORT-NAME>
            <xsl:call-template name="ECUM_DV_SDG_ADMIN_DATA_TEMPLATE" />
            <IS-SERVICE>true</IS-SERVICE>
            <OPERATIONS>
              <OPERATION-PROTOTYPE>
                <SHORT-NAME>SelectApplicationMode</SHORT-NAME>
                <ARGUMENTS>
                  <ARGUMENT-PROTOTYPE>
                    <SHORT-NAME>target</SHORT-NAME>
                    <TYPE-TREF DEST="INTEGER-TYPE">/DataType/EcuM_AppModeType</TYPE-TREF>
                    <DIRECTION>IN</DIRECTION>
                  </ARGUMENT-PROTOTYPE>
                </ARGUMENTS>
                <POSSIBLE-ERROR-REFS>
                  <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/EcuM_ApplicationMode/E_NOT_OK</POSSIBLE-ERROR-REF>
                </POSSIBLE-ERROR-REFS>
              </OPERATION-PROTOTYPE>
              <OPERATION-PROTOTYPE>
                <SHORT-NAME>GetApplicationMode</SHORT-NAME>
                <ARGUMENTS>
                  <ARGUMENT-PROTOTYPE>
                    <SHORT-NAME>state</SHORT-NAME>
                    <TYPE-TREF DEST="INTEGER-TYPE">/DataType/EcuM_AppModeType</TYPE-TREF>
                    <DIRECTION>OUT</DIRECTION>
                  </ARGUMENT-PROTOTYPE>
                </ARGUMENTS>
                <POSSIBLE-ERROR-REFS>
                  <POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/EcuM_ApplicationMode/E_NOT_OK</POSSIBLE-ERROR-REF>
                </POSSIBLE-ERROR-REFS>
              </OPERATION-PROTOTYPE>
            </OPERATIONS>
            <POSSIBLE-ERRORS>
              <APPLICATION-ERROR>
                <SHORT-NAME>E_NOT_OK</SHORT-NAME>
                <ERROR-CODE>1</ERROR-CODE>
              </APPLICATION-ERROR>
            </POSSIBLE-ERRORS>
          </CLIENT-SERVER-INTERFACE>
        </xsl:if>
      </xsl:if>
    </ELEMENTS>
  </xsl:template>
  <!-- 
  =====================================================================================================================
      MODE DECLARATION GROUP TEMPLATE
  =====================================================================================================================
  -->  
  <xsl:template name="ECUM_MODE_DECLARATION_GROUP">
    <SHORT-NAME>ModeDeclarationGroup</SHORT-NAME>
    <ELEMENTS>
      <MODE-DECLARATION-GROUP>
        <SHORT-NAME>EcuM_Mode</SHORT-NAME>
        <xsl:call-template name="ECUM_DV_SDG_ADMIN_DATA_TEMPLATE" />
        <INITIAL-MODE-REF DEST="MODE-DECLARATION">/ModeDeclarationGroup/EcuM_Mode/STARTUP</INITIAL-MODE-REF>
        <MODE-DECLARATIONS>
          <MODE-DECLARATION>
            <SHORT-NAME>STARTUP</SHORT-NAME>
          </MODE-DECLARATION>
          <MODE-DECLARATION>
            <SHORT-NAME>RUN</SHORT-NAME>
          </MODE-DECLARATION>
          <MODE-DECLARATION>
            <SHORT-NAME>POST_RUN</SHORT-NAME>
          </MODE-DECLARATION>
          <MODE-DECLARATION>
            <SHORT-NAME>SLEEP</SHORT-NAME>
          </MODE-DECLARATION>
          <MODE-DECLARATION>
            <SHORT-NAME>WAKE_SLEEP</SHORT-NAME>
          </MODE-DECLARATION>
          <MODE-DECLARATION>
            <SHORT-NAME>SHUTDOWN</SHORT-NAME>
          </MODE-DECLARATION>          
        </MODE-DECLARATIONS>
      </MODE-DECLARATION-GROUP>
    </ELEMENTS>   
  </xsl:template>

  <!-- 
  =====================================================================================================================
      MODE DECLARATION GROUP TEMPLATE
  =====================================================================================================================
  -->
  <xsl:template name="ECUM_DV_SDG_ADMIN_DATA_TEMPLATE">
  <ADMIN-DATA>
    <SDGS>
      <SDG GID="DV_SDG">
        <SD GID="DV_BSWM">EcuM</SD>
      </SDG>
    </SDGS>
  </ADMIN-DATA>
  </xsl:template>
  
</xsl:stylesheet>
