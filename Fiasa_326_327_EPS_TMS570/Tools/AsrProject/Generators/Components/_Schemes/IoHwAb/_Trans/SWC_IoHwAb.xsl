<?xml version="1.0" encoding="UTF-8"?>
<!--
 **********************************************************************************************************************
 *  COPYRIGHT
 *  ===================================================================================================================
 *  \verbatim
 *  Copyright (c) 2010 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  ===================================================================================================================
 *  FILE DESCRIPTION
 *  ===================================================================================================================
 *         File:  SWC_IoHwAb.xsl
 *    Component:  EcuAb_AsrIoHwAb
 *       Module:  IoHwAb
 *
 *  Description:  -
 *
 *********************************************************************************************************************

 **********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  ===================================================================================================================
 *  Name                          Initials      Company
 *  ===================================================================================================================
 *  Christian Marchl              Chm           Vector Informatik GmbH
 *  Christoph Ederer              Cer           Vector Informatik GmbH
 *  ===================================================================================================================
 *  REVISION HISTORY
 *  ===================================================================================================================
 *  Version   Date        Author  Change Id     Description
 *  ===================================================================================================================
 *  1.01.01   2007-11-26  Chm     ESCAN00022772 No changes here
 *                                ESCAN00023310 Changed line ending to CRLF
 *                                -             New file header added.
 *  1.01.02   2007-02-13  Chm     ESCAN00024551 GenRule G11 affected: replaced ON with STD_ON (in condition)
 *                                -             Function GenRules changed for more readability.
 *  1.02.00   2008-05-07  Cer     5006330       Created BSWMD, reworked transformation to use ECU-C file as input,
 *                                              multiple operations in one user defined port possible now, DCM
 *                                              interface added
 *  1.02.01   2008-06-13  Cer     ESCAN00027572 Rework of identifiers in Generation.xml and Validation.xml for
 *                                              EAD versions 3.2.4.341 and later, Indexes of EAD function
 *                                              RefValue() adjusted
 *  1.02.02   2008-07-10  Cer     ESCAN00028289 Read functions available for all signals now.
 *                                ESCAN00027419 Tags removed
 *                                ESCAN00026634 SIP check added
 *  1.02.03   2008-08-21  Cer     ESCAN00028337 View.xml added to Schemes
 *                                ESCAN00029093 Error in Transformation of SWC-structure reworked
 *                                ESCAN00028340 Critical section handling added
 *            2008-09-09  Chm     ESCAN00029855 Generation of references corrected
 *                                ESCAN00029854 Version defines corrected
 *                                ESCAN00029853 Corrected critical section handling
 *  1.03.00   2008-10-02  Cer     ESCAN00030019 Shortname adapted to AUTOSAR specification
 *                                ESCAN00029653 SWC generation for float data types reworked
 *  1.04.00   2008-12-05  Cer     -             Include of 'Rte_Type.h'/'IoHwAb_Types.h' moved from implementation
 *                                              to configuration header
 *                        Chm     ESCAN00031178 Added parameter IoHwAbstractionRequirementId
 *                        Chm     ESCAN00030122 Removed automatic definition of configuration container.
 *                        Chm     ESCAN00032103 Changed critical section handling to be independent of Board
 *                                              InterruptFunctionSet parameter if SchM is used.
 *  1.05.00   2008-12-19  Cer     ESCAN00032205 SubFunction 'ResetToDefault' added to DCM interface, Configuration of
 *                                              default value added to signal configuration
 *  1.05.01   2009-02-24  Cer     ESCAN00031178 RequirementId added to GUI
 *  1.05.02   2009-03-16  Cer     ESCAN00029642 Sortability added for all the tables in the view (IoHwAb.xml)
 *                                ESCAN00032636 Multiplicity of container IoHwAbDiscrete reworked (no discrete
 *                                              signal is created on startup anymore; Identifier.xml)
 *                                ESCAN00032636 Multiplicity of container IoHwAbDiscrete reworked (no discrete
 *                                              signal is created on startup anymore; Identifier.xml)
 *                                ESCAN00032763 Dev-Error Detection is disabled by default (Identifier.xml)
 *                                ESCAN00033386 RTE includes moved from configuration header to C-files
 *                                ESCAN00033387 Added support for generation of service ports (Identifer.xml,
 *                                              SWC_IoHwAb.xsl)
 *                                ESCAN00033645 Generation of data types of IOHWAB-specific default-values fixed
 *                                              (GenIoHwAbUserSourceTemplate.xml)
 *                                ESCAN00033835 Added ADMIN-DATA to SWC generation (SWC_IoHwAb.xsl)
 *  1.06.00   2009-07-10  Cer     ESCAN00034782 Added update of CalSourceType to avoid generation of empty DIO
 *                                              entity identifiers
 *                                ESCAN00036329 Fixed icon placement in view
 *                                ESCAN00036279 Automatic generation of SWC file added
 *                                ESCAN00032561 User blocks added to IoHwAb.c to avoid overwriting of user
 *                                              modifications in the generated template
 *                                ESCAN00029651 Added informative text about all the configured CAL entities
 *                                              to IoHwAb.c
 *                                ESCAN00036542 Added include of IoHwAbstraction types to the DCM header file
 *                                ESCAN00029887 Added dummy-statement mechanism to prevent compile warnings
 *  1.06.01   2009-09-22  Cer     ESCAN00037605 Reworked DCM services to provide multiple writing to the DCM
 *                                ESCAN00037601 Functionality of DCM sub-function 'resetToDefault' corrected
 *                                ESCAN00038188 Validation of default values extended to input signals
 *  1.06.02   2010-04-28  Cer     ESCAN00040647 Added general implementation are for local functions (IoHwAb.c)
 *                                ESCAN00040708 Reworked setting of parameter IoHwAbCalSourceType to ensure, that
 *                                              generation works correctly, even if the project is not saved
 *                                ESCAN00042720 'AS'-tag added to all identifers in Identifer.xml due to an in-
 *                                              compatibility with DaVinci Configurator from version 4.00.40
 *  1.06.03   2010-11-25  Cer     ESCAN00046423 Optional generation of symbolic name prefixes added
 *                                ESCAN00044073 Renamed 'Insert' buttons in the GUI to 'Append'
 *                                ESCAN00043885 Renamed control 'Component Name' and reworked description
 *                                ESCAN00043745 Default value selection removed from DIO entity parameter
 *                                -             Removed all unnecessary information from Identifer.xml (Labels, ...)
 *********************************************************************************************************************
-->
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2004/07/xpath-functions" xmlns:xdt="http://www.w3.org/2004/07/xpath-datatypes" xmlns="http://autosar.org/3.0.1" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" exclude-result-prefixes="xsl fo xs fn xdt">
	<xsl:output method="xml" encoding="UTF-8" indent="yes"/>
	<xsl:variable name="GROUP" select="'IoHwAb'"/>
	<!-- Variables -->
	<xsl:variable name="COMP_NAME" select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbServiceComponentName']/../*[local-name() = 'VALUE']"/>
	<xsl:template match="/">
		<AUTOSAR>
			<xsl:attribute name="xsi:schemaLocation">http://autosar.org/3.0.1 autosar_301.xsd</xsl:attribute>
			<TOP-LEVEL-PACKAGES>
				<xsl:comment>----------------------------------------------------------------------------------------------------------------</xsl:comment>
				<AR-PACKAGE>
					<SHORT-NAME>ComponentType</SHORT-NAME>
					<ELEMENTS>
						<xsl:call-template name="SWC"/>
						<xsl:call-template name="INTERNAL_BEHAVIOR"/>
						<xsl:call-template name="IMPL"/>
					</ELEMENTS>
				</AR-PACKAGE>
				<xsl:comment>----------------------------------------------------------------------------------------------------------------</xsl:comment>
				<AR-PACKAGE>
					<SHORT-NAME>PortInterface</SHORT-NAME>
					<ELEMENTS>
						<xsl:call-template name="CS_INTERFACE"/>
					</ELEMENTS>
				</AR-PACKAGE>
				<xsl:comment>----------------------------------------------------------------------------------------------------------------</xsl:comment>
				<AR-PACKAGE>
					<SHORT-NAME>DataType</SHORT-NAME>
					<ELEMENTS>
						<xsl:call-template name="TYPES"/>
					</ELEMENTS>
				</AR-PACKAGE>
			</TOP-LEVEL-PACKAGES>
		</AUTOSAR>
	</xsl:template>
	<!-- End of root template-->
	<!-- #################################### Type template #################################### -->
	<xsl:template name="TYPES">
		<!-- DataType definitions -->
		<INTEGER-TYPE>
			<SHORT-NAME>IoHwAb_BoolType</SHORT-NAME>
			<ADMIN-DATA>
				<SDGS>
					<SDG GID="DV_SDG">
						<SD GID="DV_BSWM">IoHwAbstraction</SD>
					</SDG>
				</SDGS>
			</ADMIN-DATA>
			<LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
			<UPPER-LIMIT INTERVAL-TYPE="CLOSED">1</UPPER-LIMIT>
		</INTEGER-TYPE>
		<INTEGER-TYPE>
			<SHORT-NAME>IoHwAb_DiscreteGroupType</SHORT-NAME>
			<ADMIN-DATA>
				<SDGS>
					<SDG GID="DV_SDG">
						<SD GID="DV_BSWM">IoHwAbstraction</SD>
					</SDG>
				</SDGS>
			</ADMIN-DATA>
			<LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
			<xsl:call-template name="IOHWAB_DISCRETE_GROUP_TYPE_SIZE_TMPL"/>
		</INTEGER-TYPE>
		<xsl:call-template name="IOHWAB_DATATYPE_DEF"/>
		<xsl:comment>AUTOSAR standard types</xsl:comment>
		<xsl:call-template name="AR_STANDARD_TYPES"/>
	</xsl:template>
	<!-- #################################### Autosar Types template #################################### -->
	<xsl:template name="AR_STANDARD_TYPES">
		<xsl:if test="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbDataType']/../*[local-name() = 'VALUE'] = 'sint8'">
			<INTEGER-TYPE>
				<SHORT-NAME>sint8</SHORT-NAME>
				<LOWER-LIMIT INTERVAL-TYPE="CLOSED">-128</LOWER-LIMIT>
				<UPPER-LIMIT INTERVAL-TYPE="CLOSED">127</UPPER-LIMIT>
			</INTEGER-TYPE>
		</xsl:if>
		<xsl:if test="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbDataType']/../*[local-name() = 'VALUE'] = 'uint8'">
			<INTEGER-TYPE>
				<SHORT-NAME>uint8</SHORT-NAME>
				<LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
				<UPPER-LIMIT INTERVAL-TYPE="CLOSED">255</UPPER-LIMIT>
			</INTEGER-TYPE>
		</xsl:if>
		<xsl:if test="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbDataType']/../*[local-name() = 'VALUE'] = 'sint16'">
			<INTEGER-TYPE>
				<SHORT-NAME>sint16</SHORT-NAME>
				<LOWER-LIMIT INTERVAL-TYPE="CLOSED">-32768</LOWER-LIMIT>
				<UPPER-LIMIT INTERVAL-TYPE="CLOSED">32767</UPPER-LIMIT>
			</INTEGER-TYPE>
		</xsl:if>
		<xsl:if test="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbDataType']/../*[local-name() = 'VALUE'] = 'uint16'">
			<INTEGER-TYPE>
				<SHORT-NAME>uint16</SHORT-NAME>
				<LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
				<UPPER-LIMIT INTERVAL-TYPE="CLOSED">65535</UPPER-LIMIT>
			</INTEGER-TYPE>
		</xsl:if>
		<xsl:if test="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbDataType']/../*[local-name() = 'VALUE'] = 'sint32'">
			<INTEGER-TYPE>
				<SHORT-NAME>sint32</SHORT-NAME>
				<LOWER-LIMIT INTERVAL-TYPE="CLOSED">-2147483648</LOWER-LIMIT>
				<UPPER-LIMIT INTERVAL-TYPE="CLOSED">2147483647</UPPER-LIMIT>
			</INTEGER-TYPE>
		</xsl:if>
		<xsl:if test="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbDataType']/../*[local-name() = 'VALUE'] = 'uint32'">
			<INTEGER-TYPE>
				<SHORT-NAME>uint32</SHORT-NAME>
				<LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
				<UPPER-LIMIT INTERVAL-TYPE="CLOSED">4294967295</UPPER-LIMIT>
			</INTEGER-TYPE>
		</xsl:if>
		<xsl:if test="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbDataType']/../*[local-name() = 'VALUE'] = 'float32'">
			<REAL-TYPE>
				<SHORT-NAME>Float</SHORT-NAME>
				<LOWER-LIMIT INTERVAL-TYPE="CLOSED">-INFINITY</LOWER-LIMIT>
				<UPPER-LIMIT INTERVAL-TYPE="CLOSED">+INFINITY</UPPER-LIMIT>
				<ALLOW-NAN>false</ALLOW-NAN>
				<ENCODING>SINGLE</ENCODING>
			</REAL-TYPE>
		</xsl:if>
		<xsl:if test="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbDataType']/../*[local-name() = 'VALUE'] = 'float64'">
			<REAL-TYPE>
				<SHORT-NAME>Double</SHORT-NAME>
				<LOWER-LIMIT INTERVAL-TYPE="CLOSED">-INFINITY</LOWER-LIMIT>
				<UPPER-LIMIT INTERVAL-TYPE="CLOSED">+INFINITY</UPPER-LIMIT>
				<ALLOW-NAN>true</ALLOW-NAN>
				<ENCODING>DOUBLE</ENCODING>
			</REAL-TYPE>
		</xsl:if>
	</xsl:template>
	<xsl:template name="IOHWAB_DISCRETE_GROUP_TYPE_SIZE_TMPL">
		<xsl:choose>
			<xsl:when test="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbDataTypeSizes/IoHwAbDiscreteGroupSize']/../*[local-name() = 'VALUE'] = 'IOHWAB_UINT8'">
				<UPPER-LIMIT INTERVAL-TYPE="CLOSED">255</UPPER-LIMIT>
			</xsl:when>
			<xsl:when test="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbDataTypeSizes/IoHwAbDiscreteGroupSize']/../*[local-name() = 'VALUE'] = 'IOHWAB_UINT16'">
				<UPPER-LIMIT INTERVAL-TYPE="CLOSED">65535</UPPER-LIMIT>
			</xsl:when>
			<xsl:when test="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbDataTypeSizes/IoHwAbDiscreteGroupSize']/../*[local-name() = 'VALUE'] = 'IOHWAB_UINT32'">
				<UPPER-LIMIT INTERVAL-TYPE="CLOSED">4294967295</UPPER-LIMIT>
			</xsl:when>
		</xsl:choose>
	</xsl:template>
	<xsl:template name="IOHWAB_DATATYPE_DEF">
		<INTEGER-TYPE>
			<SHORT-NAME>IoHwAb_CurrentType</SHORT-NAME>
			<ADMIN-DATA>
				<SDGS>
					<SDG GID="DV_SDG">
						<SD GID="DV_BSWM">IoHwAbstraction</SD>
					</SDG>
				</SDGS>
			</ADMIN-DATA>
			<LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
			<xsl:choose>
				<xsl:when test="//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbDataTypeSizes/IoHwAbCurrentType']/../*[local-name() = 'VALUE'] = 'IOHWAB_UINT16' ">
					<UPPER-LIMIT INTERVAL-TYPE="CLOSED">65535</UPPER-LIMIT>
				</xsl:when>
				<xsl:when test="//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbDataTypeSizes/IoHwAbCurrentType']/../*[local-name() = 'VALUE']= 'IOHWAB_UINT32' ">
					<UPPER-LIMIT INTERVAL-TYPE="CLOSED">4294967295</UPPER-LIMIT>
				</xsl:when>
				<xsl:otherwise>
					<xsl:comment>Data Type failure in IoHwAb_CurrentType
						</xsl:comment>
				</xsl:otherwise>
			</xsl:choose>
		</INTEGER-TYPE>
		<INTEGER-TYPE>
			<SHORT-NAME>IoHwAb_VoltageType</SHORT-NAME>
			<ADMIN-DATA>
				<SDGS>
					<SDG GID="DV_SDG">
						<SD GID="DV_BSWM">IoHwAbstraction</SD>
					</SDG>
				</SDGS>
			</ADMIN-DATA>
			<LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
			<xsl:choose>
				<xsl:when test="//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbDataTypeSizes/IoHwAbVoltageType']/../*[local-name() = 'VALUE'] = 'IOHWAB_UINT16' ">
					<UPPER-LIMIT INTERVAL-TYPE="CLOSED">65535</UPPER-LIMIT>
				</xsl:when>
				<xsl:when test="//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbDataTypeSizes/IoHwAbVoltageType']/../*[local-name() = 'VALUE']= 'IOHWAB_UINT32' ">
					<UPPER-LIMIT INTERVAL-TYPE="CLOSED">4294967295</UPPER-LIMIT>
				</xsl:when>
				<xsl:otherwise>
					<xsl:comment>Data Type failure in  IoHwAb_VoltageType
						</xsl:comment>
				</xsl:otherwise>
			</xsl:choose>
		</INTEGER-TYPE>
		<INTEGER-TYPE>
			<SHORT-NAME>IoHwAb_ResistanceType</SHORT-NAME>
			<ADMIN-DATA>
				<SDGS>
					<SDG GID="DV_SDG">
						<SD GID="DV_BSWM">IoHwAbstraction</SD>
					</SDG>
				</SDGS>
			</ADMIN-DATA>
			<LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
			<xsl:choose>
				<xsl:when test="//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbDataTypeSizes/IoHwAbResistanceType']/../*[local-name() = 'VALUE'] = 'IOHWAB_UINT16' ">
					<UPPER-LIMIT INTERVAL-TYPE="CLOSED">65535</UPPER-LIMIT>
				</xsl:when>
				<xsl:when test="//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbDataTypeSizes/IoHwAbResistanceType']/../*[local-name() = 'VALUE']= 'IOHWAB_UINT32' ">
					<UPPER-LIMIT INTERVAL-TYPE="CLOSED">4294967295</UPPER-LIMIT>
				</xsl:when>
				<xsl:otherwise>
					<xsl:comment>Data Type failure in IoHwAb_ResistanceType
						</xsl:comment>
				</xsl:otherwise>
			</xsl:choose>
		</INTEGER-TYPE>
		<INTEGER-TYPE>
			<SHORT-NAME>IoHwAb_SignalDiagnosisType</SHORT-NAME>
			<ADMIN-DATA>
				<SDGS>
					<SDG GID="DV_SDG">
						<SD GID="DV_BSWM">IoHwAbstraction</SD>
					</SDG>
				</SDGS>
			</ADMIN-DATA>
			<LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
			<xsl:choose>
				<xsl:when test="//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbDataTypeSizes/IoHwAbSignalDiagnosisType']/../*[local-name() = 'VALUE'] = 'IOHWAB_UINT16' ">
					<UPPER-LIMIT INTERVAL-TYPE="CLOSED">65535</UPPER-LIMIT>
				</xsl:when>
				<xsl:when test="//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbDataTypeSizes/IoHwAbSignalDiagnosisType']/../*[local-name() = 'VALUE']= 'IOHWAB_UINT32' ">
					<UPPER-LIMIT INTERVAL-TYPE="CLOSED">4294967295</UPPER-LIMIT>
				</xsl:when>
				<xsl:otherwise>
					<xsl:comment>Data Type failure in IoHwAb_SignalDiagnosisType
						</xsl:comment>
				</xsl:otherwise>
			</xsl:choose>
		</INTEGER-TYPE>
		<INTEGER-TYPE>
			<SHORT-NAME>IoHwAb_PwxPeriodType</SHORT-NAME>
			<ADMIN-DATA>
				<SDGS>
					<SDG GID="DV_SDG">
						<SD GID="DV_BSWM">IoHwAbstraction</SD>
					</SDG>
				</SDGS>
			</ADMIN-DATA>
			<LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
			<xsl:choose>
				<xsl:when test="//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbDataTypeSizes/IoHwAbPwxPeriodType']/../*[local-name() = 'VALUE'] = 'IOHWAB_UINT16' ">
					<UPPER-LIMIT INTERVAL-TYPE="CLOSED">65535</UPPER-LIMIT>
				</xsl:when>
				<xsl:when test="//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbDataTypeSizes/IoHwAbPwxPeriodType']/../*[local-name() = 'VALUE']= 'IOHWAB_UINT32' ">
					<UPPER-LIMIT INTERVAL-TYPE="CLOSED">4294967295</UPPER-LIMIT>
				</xsl:when>
				<xsl:otherwise>
					<xsl:comment>Data Type failure in IoHwAb_PwxPeriodType
						</xsl:comment>
				</xsl:otherwise>
			</xsl:choose>
		</INTEGER-TYPE>
		<INTEGER-TYPE>
			<SHORT-NAME>IoHwAb_PwxDutyCycleType</SHORT-NAME>
			<ADMIN-DATA>
				<SDGS>
					<SDG GID="DV_SDG">
						<SD GID="DV_BSWM">IoHwAbstraction</SD>
					</SDG>
				</SDGS>
			</ADMIN-DATA>
			<LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
			<xsl:choose>
				<xsl:when test="//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbDataTypeSizes/IoHwAbPwxDutyCycleType']/../*[local-name() = 'VALUE'] = 'IOHWAB_UINT16' ">
					<UPPER-LIMIT INTERVAL-TYPE="CLOSED">65535</UPPER-LIMIT>
				</xsl:when>
				<xsl:when test="//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbDataTypeSizes/IoHwAbPwxDutyCycleType']/../*[local-name() = 'VALUE']= 'IOHWAB_UINT32' ">
					<UPPER-LIMIT INTERVAL-TYPE="CLOSED">4294967295</UPPER-LIMIT>
				</xsl:when>
				<xsl:otherwise>
					<xsl:comment>Data Type failure in IoHwAb_PwxDutyCycleType
						</xsl:comment>
				</xsl:otherwise>
			</xsl:choose>
		</INTEGER-TYPE>
	</xsl:template>
	<xsl:template name="IOHWAB_DATATYPE_UPPER">
		<xsl:param name="TypeName" select=".//*[local-name() = 'VALUE']"/>
		<xsl:comment>Der Wert ist: <xsl:value-of select="."/>
		</xsl:comment>
		<xsl:choose>
			<xsl:when test="//*[local-name() = 'DEFINITION-REF' and .=concat('/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbDataTypeSizes/', $TypeName)]/../*[local-name() = 'VALUE'] = 'IOHWAB_UINT16' ">
				<UPPER-LIMIT INTERVAL-TYPE="CLOSED">65535</UPPER-LIMIT>
			</xsl:when>
			<xsl:when test="//*[local-name() = 'DEFINITION-REF' and .=concat('/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbDataTypeSizes/', $TypeName)]/../*[local-name() = 'VALUE'] = 'IOHWAB_UINT32' ">
				<UPPER-LIMIT INTERVAL-TYPE="CLOSED">4294967295</UPPER-LIMIT>
			</xsl:when>
			<xsl:otherwise>
				<xsl:comment>Data Type failure in <xsl:value-of select="$TypeName"/>
				</xsl:comment>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
	<!-- #################################### Client-Server Interface template #################################### -->
	<xsl:template name="CS_INTERFACE">
		<xsl:comment>--------------- CAL INTERFACES ---------------</xsl:comment>
		<xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete']/..">
			<xsl:call-template name="SINGLE_CAL_CS_INTERFACE"/>
		</xsl:for-each>
		<xsl:comment>--------------- USER DEFINED INTERFACES ---------------</xsl:comment>
		<xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort']/..">
			<xsl:call-template name="SINGLE_USER_CS_INTERFACE"/>
		</xsl:for-each>
	</xsl:template>
	<!-- #################################### Internal Behavior template #################################### -->
	<xsl:template name="INTERNAL_BEHAVIOR">
		<INTERNAL-BEHAVIOR>
			<SHORT-NAME>
				<xsl:value-of select="$COMP_NAME"/>Behave</SHORT-NAME>
			<COMPONENT-REF DEST="ECU-ABSTRACTION-COMPONENT-TYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>
			</COMPONENT-REF>
			<xsl:call-template name="EVENTS"/>
			<xsl:call-template name="RUNNABLES"/>
		</INTERNAL-BEHAVIOR>
	</xsl:template>
	<!-- #################################### Implementation template #################################### -->
	<xsl:template name="IMPL">
		<SWC-IMPLEMENTATION>
			<SHORT-NAME><xsl:value-of select="$COMP_NAME"/>Impl</SHORT-NAME>
			<BEHAVIOR-REF DEST="INTERNAL-BEHAVIOR">/ComponentType/<xsl:value-of select="$COMP_NAME"/>Behave</BEHAVIOR-REF>
		</SWC-IMPLEMENTATION>
	</xsl:template>
	<!-- #################################### Application software component template #################################### -->
	<xsl:template name="SWC">
		<xsl:comment>Application Software Component IO Hardware Abstraction</xsl:comment>
		<ECU-ABSTRACTION-COMPONENT-TYPE>
			<SHORT-NAME>
				<xsl:value-of select="$COMP_NAME"/>
			</SHORT-NAME>
			<ADMIN-DATA>
				<SDGS>
					<SDG GID="DV_SDG">
						<SD GID="DV_BSWM">IoHwAbstraction</SD>
					</SDG>
				</SDGS>
			</ADMIN-DATA>
			<xsl:call-template name="PORT"/>
		</ECU-ABSTRACTION-COMPONENT-TYPE>
	</xsl:template>
	<!-- #################################### PORT Template #################################### -->
	<xsl:template name="PORT">
		<PORTS>
			<xsl:comment>--------------- CAL PORTS ---------------</xsl:comment>
			<xsl:call-template name="CAL_PORTS"/>
			<xsl:comment>--------------- USER DEFINED PORTS ---------------</xsl:comment>
			<xsl:call-template name="USER_PORTS"/>
		</PORTS>
	</xsl:template>
	<!-- #################################### CAL Port Template #################################### -->
	<xsl:template name="CAL_PORTS">
		<xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete']/..">
			<xsl:call-template name="SINGLE_CAL_PORTS"/>
		</xsl:for-each>
	</xsl:template>
	<!-- #################################### Single CAL Port Template #################################### -->
	<xsl:template name="SINGLE_CAL_PORTS">
		<xsl:param name="Pos" select="position()"/>
		<xsl:choose>
			<xsl:when test=".//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete/IoHwAbCreateOpSet']/../*[local-name() = 'VALUE'] = 'true' and .//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete/IoHwAbCreateOpGet']/../*[local-name() = 'VALUE'] = 'true'">
				<xsl:comment>Port Prototype of CAL Signal: <xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
				</xsl:comment>
				<P-PORT-PROTOTYPE>
					<SHORT-NAME>
						<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
					</SHORT-NAME>
					<PROVIDED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">/PortInterface/<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
					</PROVIDED-INTERFACE-TREF>
				</P-PORT-PROTOTYPE>
			</xsl:when>
			<xsl:when test=".//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete/IoHwAbCreateOpGet']/../*[local-name() = 'VALUE'] = 'true'">
				<xsl:comment>Port Prototype of CAL Signal: <xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
				</xsl:comment>
				<P-PORT-PROTOTYPE>
					<SHORT-NAME>
						<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
					</SHORT-NAME>
					<PROVIDED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">/PortInterface/<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
					</PROVIDED-INTERFACE-TREF>
				</P-PORT-PROTOTYPE>
			</xsl:when>
			<xsl:when test=".//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete/IoHwAbCreateOpSet']/../*[local-name() = 'VALUE'] = 'true'">
				<xsl:comment>Port Prototype of CAL Signal: <xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
				</xsl:comment>
				<P-PORT-PROTOTYPE>
					<SHORT-NAME>
						<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
					</SHORT-NAME>
					<PROVIDED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">/PortInterface/<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
					</PROVIDED-INTERFACE-TREF>
				</P-PORT-PROTOTYPE>
			</xsl:when>
		</xsl:choose>
	</xsl:template>
	<!-- #################################### USER defined Port Template #################################### -->
	<xsl:template name="USER_PORTS">
		<xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort']/..">
			<xsl:call-template name="SINGLE_USER_PORTS"/>
		</xsl:for-each>
	</xsl:template>
	<!-- #################################### Single User Port Template #################################### -->
	<xsl:template name="SINGLE_USER_PORTS">
		<xsl:param name="Pos" select="position()"/>
		<xsl:comment>Port Prototype: <xsl:value-of select="./*[local-name() = 'SHORT-NAME']"/>
		</xsl:comment>
		<P-PORT-PROTOTYPE>
			<SHORT-NAME>
				<xsl:value-of select="./*[local-name() = 'SHORT-NAME']"/>
			</SHORT-NAME>
			<PROVIDED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">/PortInterface/<xsl:value-of select="./*[local-name() = 'SHORT-NAME']"/>
			</PROVIDED-INTERFACE-TREF>
		</P-PORT-PROTOTYPE>
	</xsl:template>
	<!-- #################################### RUNNABLE Template #################################### -->
	<xsl:template name="RUNNABLES">
		<RUNNABLES>
			<xsl:comment>--------------- CAL RUNNABLES ---------------</xsl:comment>
			<xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete']/..">
				<xsl:call-template name="SINGLE_CAL_RUNNABLE"/>
			</xsl:for-each>
			<xsl:comment>--------------- USER DEFINED RUNNABLES ---------------</xsl:comment>
			<xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp']/..">
				<xsl:call-template name="SINGLE_USER_RUNNABLE"/>
			</xsl:for-each>
			<xsl:comment>--------------- HANDLERS ---------------</xsl:comment>
			<xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbHandlers/IoHwAbHandler']/..">
				<xsl:call-template name="SINGLE_HANDLER"/>
			</xsl:for-each>
		</RUNNABLES>
	</xsl:template>
	<!-- #################################### User Runnables Template (Creates Runnables for OP_SET,OP_GET, Signalhandling -->
	<xsl:template name="SINGLE_USER_RUNNABLE">
		<xsl:comment>User defined Runnable description for user defined operation <xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
		</xsl:comment>
		<RUNNABLE-ENTITY>
			<SHORT-NAME>IoHwAb_<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
			</SHORT-NAME>
			<CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
			<SYMBOL>IoHwAb_<xsl:value-of select=".//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbAccess']/..//*[local-name()='VALUE']"/>
				<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
			</SYMBOL>
		</RUNNABLE-ENTITY>
	</xsl:template>
	<xsl:template name="SINGLE_HANDLER">
		<RUNNABLE-ENTITY>
			<SHORT-NAME>IoHwAb_<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
			</SHORT-NAME>
			<CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
			<SYMBOL>IoHwAb_<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
			</SYMBOL>
		</RUNNABLE-ENTITY>
	</xsl:template>
	<!-- #################################### Single CAL Runnable Template #################################### -->
	<xsl:template name="SINGLE_CAL_RUNNABLE">
		<xsl:param name="Pos" select="position()"/>
		<xsl:if test=".//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete/IoHwAbCreateOpGet']/../*[local-name() = 'VALUE'] = 'true'">
			<xsl:comment>Runnable Entity description for Signal: <xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/> Operation: OP_GET</xsl:comment>
			<RUNNABLE-ENTITY>
				<SHORT-NAME>IoHwAb_Get<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
				</SHORT-NAME>
				<CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
				<SYMBOL>IoHwAb_Get<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
				</SYMBOL>
			</RUNNABLE-ENTITY>
		</xsl:if>
		<xsl:if test=".//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete/IoHwAbCreateOpSet']/../*[local-name() = 'VALUE'] = 'true' ">
			<xsl:comment>Runnable Entity description for Signal: <xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/> Operation: OP_SET</xsl:comment>
			<RUNNABLE-ENTITY>
				<SHORT-NAME>IoHwAb_Set<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
				</SHORT-NAME>
				<CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
				<SYMBOL>IoHwAb_Set<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
				</SYMBOL>
			</RUNNABLE-ENTITY>
		</xsl:if>
		<xsl:if test=".//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete/IoHwAbCreateOpDiag']/../*[local-name() = 'VALUE'] = 'true' ">
			<xsl:comment>Runnable Entity description for Signal: <xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/> Operation: OP_DIAG</xsl:comment>
			<RUNNABLE-ENTITY>
				<SHORT-NAME>IoHwAb_Diag<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
				</SHORT-NAME>
				<CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
				<SYMBOL>IoHwAb_Diag<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
				</SYMBOL>
			</RUNNABLE-ENTITY>
		</xsl:if>
	</xsl:template>
	<!-- #################################### EVENT Template #################################### -->
	<xsl:template name="EVENTS">
		<EVENTS>
			<xsl:call-template name="OPERATION_INVOKED_EVENT"/>
			<xsl:call-template name="TIMING_EVENTS"/>
		</EVENTS>
	</xsl:template>
	<!-- #################################### Operation Invoked Template #################################### -->
	<xsl:template name="OPERATION_INVOKED_EVENT">
		<xsl:comment>--------------- CAL OPERATIONS ---------------</xsl:comment>
		<xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete']/..">
			<xsl:call-template name="SINGLE_CAL_OPERATION"/>
		</xsl:for-each>
		<xsl:comment>--------------- USER DEFINED OPERATIONS ---------------</xsl:comment>
		<xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp']/..">
			<xsl:call-template name="SINGLE_USER_OPERATION"/>
		</xsl:for-each>
	</xsl:template>
	<!-- #################################### Single User Operation Invoked Template #################################### -->
	<xsl:template name="SINGLE_USER_OPERATION">
		<xsl:comment>Trigger Reference for User Operation '<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>' (part of user defined port '<xsl:value-of select="./../../*[local-name() = 'SHORT-NAME']"/>') </xsl:comment>
		<OPERATION-INVOKED-EVENT>
			<SHORT-NAME>TR<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
			</SHORT-NAME>
			<START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME"/>Behave/IoHwAb_<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
			</START-ON-EVENT-REF>
			<OPERATION-IREF>
				<P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/<xsl:value-of select="./../../*[local-name() = 'SHORT-NAME']"/>
				</P-PORT-PROTOTYPE-REF>
				<OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/<xsl:value-of select="./../../*[local-name() = 'SHORT-NAME']"/>/<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
				</OPERATION-PROTOTYPE-REF>
			</OPERATION-IREF>
		</OPERATION-INVOKED-EVENT>
	</xsl:template>
	<!-- #################################### Single CAL Operation Invoked Template #################################### -->
	<xsl:template name="SINGLE_CAL_OPERATION">
		<xsl:if test=".//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete/IoHwAbCreateOpSet']/../*[local-name() = 'VALUE'] = 'true'">
			<xsl:comment>Trigger Reference for CAL Signal: <xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/> Operation: OP_SET</xsl:comment>
			<OPERATION-INVOKED-EVENT>
				<SHORT-NAME>TW<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
				</SHORT-NAME>
				<START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME"/>Behave/IoHwAb_Set<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
				</START-ON-EVENT-REF>
				<OPERATION-IREF>
					<P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
					</P-PORT-PROTOTYPE-REF>
					<OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>/OP_SET</OPERATION-PROTOTYPE-REF>
				</OPERATION-IREF>
			</OPERATION-INVOKED-EVENT>
		</xsl:if>
		<xsl:if test=".//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete/IoHwAbCreateOpGet']/../*[local-name() = 'VALUE'] = 'true'">
			<xsl:comment>Trigger Reference for CAL Signal: <xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/> Operation: OP_GET</xsl:comment>
			<OPERATION-INVOKED-EVENT>
				<SHORT-NAME>TR<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
				</SHORT-NAME>
				<START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME"/>Behave/IoHwAb_Get<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
				</START-ON-EVENT-REF>
				<OPERATION-IREF>
					<P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
					</P-PORT-PROTOTYPE-REF>
					<OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>/OP_GET</OPERATION-PROTOTYPE-REF>
				</OPERATION-IREF>
			</OPERATION-INVOKED-EVENT>
		</xsl:if>
		<xsl:if test=".//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete/IoHwAbCreateOpDiag']/../*[local-name() = 'VALUE'] = 'true'">
			<xsl:comment>Trigger Reference for CAL Signal: <xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/> Operation: OP_DIAG</xsl:comment>
			<OPERATION-INVOKED-EVENT>
				<SHORT-NAME>TD<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
				</SHORT-NAME>
				<START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME"/>Behave/IoHwAb_Diag<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
				</START-ON-EVENT-REF>
				<OPERATION-IREF>
					<P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">/ComponentType/<xsl:value-of select="$COMP_NAME"/>/<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
					</P-PORT-PROTOTYPE-REF>
					<OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">/PortInterface/<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>/OP_DIAG</OPERATION-PROTOTYPE-REF>
				</OPERATION-IREF>
			</OPERATION-INVOKED-EVENT>
		</xsl:if>
	</xsl:template>
	<!-- ################################### SINGLE_USER_CS_INTERFACE Template #############################################-->
	<xsl:template name="SINGLE_USER_CS_INTERFACE">
		<xsl:comment>Client Server Interface for port '<xsl:value-of select="./*[local-name() = 'SHORT-NAME']"/>'</xsl:comment>
		<CLIENT-SERVER-INTERFACE>
			<SHORT-NAME>
				<xsl:value-of select="./*[local-name() = 'SHORT-NAME']"/>
			</SHORT-NAME>
			<ADMIN-DATA>
				<SDGS>
					<SDG GID="DV_SDG">
						<SD GID="DV_BSWM">IoHwAbstraction</SD>
					</SDG>
				</SDGS>
			</ADMIN-DATA>
			<IS-SERVICE>
				<xsl:if test="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbUseServicePorts']/../*[local-name() = 'VALUE'] = 'true'">true</xsl:if>
				<xsl:if test="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbUseServicePorts']/../*[local-name() = 'VALUE'] = 'false'">false</xsl:if>
			</IS-SERVICE>
			<OPERATIONS>
				<xsl:for-each select=".//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp']/..">
					<xsl:call-template name="SINGLE_USER_CS_INTERFACE_OPERATIONS"/>
				</xsl:for-each>
			</OPERATIONS>
			<POSSIBLE-ERRORS>
				<APPLICATION-ERROR>
					<SHORT-NAME>E_NOT_OK</SHORT-NAME>
					<ERROR-CODE>1</ERROR-CODE>
				</APPLICATION-ERROR>
			</POSSIBLE-ERRORS>
		</CLIENT-SERVER-INTERFACE>
	</xsl:template>
	<!-- ####################################### SINGLE_USER_CS_INTERFACE_OPERATIONS Template #################################### -->
	<xsl:template name="SINGLE_USER_CS_INTERFACE_OPERATIONS">
		<xsl:comment>User operation '<xsl:value-of select="./*[local-name() = 'SHORT-NAME']"/>'</xsl:comment>
		<OPERATION-PROTOTYPE>
			<SHORT-NAME>
				<xsl:value-of select="./*[local-name() = 'SHORT-NAME']"/>
			</SHORT-NAME>
			<ARGUMENTS>
				<ARGUMENT-PROTOTYPE>
					<SHORT-NAME>signal</SHORT-NAME>
					<xsl:choose>
						<xsl:when test=".//*[local-name() = 'DEFINITION-REF' and . = '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbDataType']/../*[local-name() = 'VALUE'] = 'IoHwAbBoolType'">
							<TYPE-TREF DEST="BOOLEAN-TYPE">/DataType/IoHwAb_<xsl:value-of select="substring-after(.//*[local-name() = 'DEFINITION-REF' and . = '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbDataType']/../*[local-name() = 'VALUE'], 'IoHwAb')"/>
							</TYPE-TREF>
						</xsl:when>
						<xsl:otherwise>
							<xsl:choose>
								<xsl:when test="contains(.//*[local-name() = 'DEFINITION-REF' and . = '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbDataType']/../*[local-name() = 'VALUE'], 'IoHwAb') ">
									<TYPE-TREF DEST="INTEGER-TYPE">/DataType/IoHwAb_<xsl:value-of select="substring-after(.//*[local-name() = 'DEFINITION-REF' and . = '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbDataType']/../*[local-name() = 'VALUE'], 'IoHwAb')"/>
									</TYPE-TREF>
								</xsl:when>
								<!--  Float datatypes need special treatment -->
								<xsl:when test="contains(.//*[local-name() = 'DEFINITION-REF' and . = '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbDataType']/../*[local-name() = 'VALUE'], 'float32') ">
									<TYPE-TREF DEST="INTEGER-TYPE">/DataType/Float</TYPE-TREF>
								</xsl:when>
								<xsl:when test="contains(.//*[local-name() = 'DEFINITION-REF' and . = '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbDataType']/../*[local-name() = 'VALUE'], 'float64') ">
									<TYPE-TREF DEST="INTEGER-TYPE">/DataType/Double</TYPE-TREF>
								</xsl:when>
								<xsl:otherwise>
									<TYPE-TREF DEST="INTEGER-TYPE">/DataType/<xsl:value-of select=".//*[local-name() = 'DEFINITION-REF' and . = '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbDataType']/../*[local-name() = 'VALUE'] "/>
									</TYPE-TREF>
								</xsl:otherwise>
							</xsl:choose>
						</xsl:otherwise>
					</xsl:choose>
					<DIRECTION>
						<xsl:if test=".//*[local-name() = 'DEFINITION-REF' and . = '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbAccess']/../*[local-name() = 'VALUE'] = 'Input' ">OUT</xsl:if>
						<xsl:if test=".//*[local-name() = 'DEFINITION-REF' and . = '/MICROSAR/IoHwAbstraction/IoHwAbUserDefSignals/IoHwAbUserDefPort/IoHwAbUserDefinedOp/IoHwAbAccess']/../*[local-name() = 'VALUE'] = 'Output'">IN</xsl:if>
					</DIRECTION>
				</ARGUMENT-PROTOTYPE>
			</ARGUMENTS>
			<POSSIBLE-ERROR-REFS>
				<POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/<xsl:value-of select="./../../*[local-name() ='SHORT-NAME']"/>/E_NOT_OK</POSSIBLE-ERROR-REF>
			</POSSIBLE-ERROR-REFS>
		</OPERATION-PROTOTYPE>
	</xsl:template>
	<!-- ####################################### SINGLE_CAL_CS_INTERFACE Template #################################### -->
	<xsl:template name="SINGLE_CAL_CS_INTERFACE">
		<xsl:comment>Client/Server Interface for CAL Signal: <xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
		</xsl:comment>
		<CLIENT-SERVER-INTERFACE>
			<SHORT-NAME>
				<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
			</SHORT-NAME>
			<ADMIN-DATA>
				<SDGS>
					<SDG GID="DV_SDG">
						<SD GID="DV_BSWM">IoHwAbstraction</SD>
					</SDG>
				</SDGS>
			</ADMIN-DATA>
			<IS-SERVICE>
				<xsl:if test="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbUseServicePorts']/../*[local-name() = 'VALUE'] = 'true'">true</xsl:if>
				<xsl:if test="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbGeneral/IoHwAbUseServicePorts']/../*[local-name() = 'VALUE'] = 'false'">false</xsl:if>
			</IS-SERVICE>
			<OPERATIONS>
				<xsl:if test=".//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete/IoHwAbCreateOpSet']/../*[local-name() = 'VALUE'] = 'true'">
					<xsl:comment>Client/Server Interface <xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>,  Operation: OP_SET</xsl:comment>
					<OPERATION-PROTOTYPE>
						<SHORT-NAME>OP_SET</SHORT-NAME>
						<ARGUMENTS>
							<ARGUMENT-PROTOTYPE>
								<SHORT-NAME>signal</SHORT-NAME>
								<xsl:call-template name="TYPE_ABSTRACTION"/>
								<DIRECTION>IN</DIRECTION>
							</ARGUMENT-PROTOTYPE>
						</ARGUMENTS>
						<POSSIBLE-ERROR-REFS>
							<POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>/E_NOT_OK</POSSIBLE-ERROR-REF>
						</POSSIBLE-ERROR-REFS>
					</OPERATION-PROTOTYPE>
				</xsl:if>
				<xsl:if test=".//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete/IoHwAbCreateOpGet']/../*[local-name() = 'VALUE'] = 'true'">
					<xsl:comment>Client/Server Interface <xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>,  Operation: OP_GET</xsl:comment>
					<OPERATION-PROTOTYPE>
						<SHORT-NAME>OP_GET</SHORT-NAME>
						<ARGUMENTS>
							<ARGUMENT-PROTOTYPE>
								<SHORT-NAME>signal</SHORT-NAME>
								<xsl:call-template name="TYPE_ABSTRACTION"/>
								<DIRECTION>OUT</DIRECTION>
							</ARGUMENT-PROTOTYPE>
						</ARGUMENTS>
						<POSSIBLE-ERROR-REFS>
							<POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>/E_NOT_OK</POSSIBLE-ERROR-REF>
						</POSSIBLE-ERROR-REFS>
					</OPERATION-PROTOTYPE>
				</xsl:if>
				<xsl:if test=".//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete/IoHwAbCreateOpDiag']/../*[local-name() = 'VALUE'] = 'true'">
					<xsl:comment>Client/Server Interface <xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>,  Operation: OP_DIAG</xsl:comment>
					<OPERATION-PROTOTYPE>
						<SHORT-NAME>OP_DIAG</SHORT-NAME>
						<ARGUMENTS>
							<ARGUMENT-PROTOTYPE>
								<SHORT-NAME>signal</SHORT-NAME>
								<xsl:call-template name="TYPE_ABSTRACTION"/>
								<DIRECTION>OUT</DIRECTION>
							</ARGUMENT-PROTOTYPE>
						</ARGUMENTS>
						<POSSIBLE-ERROR-REFS>
							<POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/PortInterface/<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>/E_NOT_OK</POSSIBLE-ERROR-REF>
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
	</xsl:template>
	<!-- #################################### Dio Abstraction port Template ##########################################-->
	<xsl:template name="TYPE_ABSTRACTION">
		<xsl:variable name="DioEntityId" select=".//*[local-name()='DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbCalSignals/IoHwAbDiscrete/IoHwAbCalSourceType']/..//*[local-name()='VALUE']"/>
		<xsl:choose>
			<xsl:when test="$DioEntityId = 'DioChannel'">
				<TYPE-TREF DEST="BOOLEAN-TYPE">/DataType/IoHwAb_BoolType</TYPE-TREF>
			</xsl:when>
			<xsl:when test="$DioEntityId = 'DioPort'">
				<TYPE-TREF DEST="INTEGER-TYPE">/DataType/IoHwAb_DiscreteGroupType</TYPE-TREF>
			</xsl:when>
			<xsl:when test="$DioEntityId = 'DioChannelGroup'">
				<TYPE-TREF DEST="INTEGER-TYPE">/DataType/IoHwAb_DiscreteGroupType</TYPE-TREF>
			</xsl:when>
		</xsl:choose>
	</xsl:template>
	<!-- #################################### Get  defined Type ##########################################-->
	<xsl:template name="GET_USER_DEF_TYPE">
		<xsl:param name="Pos" select="position()"/>
		<xsl:variable name="type" select="../../Identifier[@Name='IOHWAB_USER_PARAMETER_DATA_TYPE']/Entry[position()=$Pos]/@Value"/>
		<xsl:choose>
			<xsl:when test="$type = 'IoHwAb_BoolType'">
				<TYPE-TREF DEST="BOOLEAN-TYPE">/DataType/<xsl:value-of select="$type"/>
				</TYPE-TREF>
			</xsl:when>
			<xsl:otherwise>
				<TYPE-TREF DEST="INTEGER-TYPE">/DataType/<xsl:value-of select="$type"/>
				</TYPE-TREF>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
	<!-- #################################### TIMING-EVENT Invoked Template #################################### -->
	<xsl:template name="TIMING_EVENTS">
		<xsl:comment>--------------- HANDLERS ---------------</xsl:comment>
		<xsl:for-each select="//*[local-name() = 'DEFINITION-REF' and .= '/MICROSAR/IoHwAbstraction/IoHwAbHandlers/IoHwAbHandler']/..">
			<xsl:call-template name="SINGLE_TIMING_EVENT"/>
		</xsl:for-each>
	</xsl:template>
	<!-- #################################### TIMING-EVENT Invoked Template #################################### -->
	<xsl:template name="FORMAT_PERIOD">
		<xsl:param name="value" select=".//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbHandlers/IoHwAbHandler/IoHwAbTriggerPeriod']/../*[local-name() = 'VALUE']"/>
		<xsl:choose>
			<xsl:when test=".//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbHandlers/IoHwAbHandler/IoHwAbTimebase']/../*[local-name() = 'VALUE'] = 'IoHwAbSec'">
				<xsl:value-of select="number($value)"/>
			</xsl:when>
			<xsl:when test=".//*[local-name() = 'DEFINITION-REF' and .='/MICROSAR/IoHwAbstraction/IoHwAbHandlers/IoHwAbHandler/IoHwAbTimebase']/../*[local-name() = 'VALUE'] = 'IoHwAbMSec'">
				<xsl:value-of select="number($value) div number(1000)"/>
			</xsl:when>
		</xsl:choose>
	</xsl:template>
	<xsl:template name="SINGLE_TIMING_EVENT">
		<xsl:param name="Pos" select="position()"/>
		<TIMING-EVENT>
			<SHORT-NAME>TH<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
			</SHORT-NAME>
			<START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentType/<xsl:value-of select="$COMP_NAME"/>Behave/IoHwAb_<xsl:value-of select=".//*[local-name() = 'SHORT-NAME']"/>
			</START-ON-EVENT-REF>
			<PERIOD>
				<xsl:call-template name="FORMAT_PERIOD"/>
			</PERIOD>
		</TIMING-EVENT>
	</xsl:template>
</xsl:stylesheet>
