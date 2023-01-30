<?xml version="1.0" encoding="UTF-8"?>
<!--
***********************************************************************************************************************
COPYRIGHT
=======================================================================================================================
Copyright (c) 2009 by Vector Informatik GmbH.                                                      All rights reserved.

    This software is copyright protected and proprietary to Vector Informatik GmbH.
    Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
    All other rights remain with Vector Informatik GmbH.
=======================================================================================================================
FILE DESCRIPTION
=======================================================================================================================
File:           SWC_NvM.xsl
Component:      MemService_AsrNvm
Module:         NvM
Generator:      -

Description:    -

File Revision: 3.03.01
***********************************************************************************************************************
-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
							  xmlns ="http://autosar.org/3.0.1" 
							  xmlns:int="http://www.vector-informatik.com/ck"
							  xmlns:msxsl="urn:schemas-microsoft-com:xslt"
							  exclude-result-prefixes="xsl msxsl int">
								
							  
	<xsl:output method="xml" encoding="UTF-8" indent="yes"/>

	<!--
		Currently we don't wan to use the init callbacks in conjunction with service ports.
		To enable it in a later release, just set this variable to 'true'.
	-->

	<xsl:variable name="GenerateInitCallBacks" select="'false'" />

	<xsl:variable name="ComponentPackageName" select="'ComponentType'" />
	<xsl:variable name="InterfacePackageName" select="'PortInterface'" />
	<xsl:variable name="DataTypesPackageName" select="'DataTypes'"/>

	<xsl:variable name="InterfaceName_Administration" select="'NvM_Administration'" />
	<xsl:variable name="InterfaceName_NotifyFinished" select="'NvM_NotifyJobFinished'" />
	<xsl:variable name="InterfaceName_NotifyBlockInit" select="'NvM_NotifyInitBlock'" />

	<xsl:variable name="ServicePrototype_Prefix" select="'PS_'" />
	<xsl:variable name="AdminPrototype_Prefix" select="'PAdmin_'" />

	<!-- For DaVinci the BlockId Type must be unique across multiple NvM SWC Descriptions (to be mapped to diefferent ECUs), each resulting from a different configuration -->
	<xsl:variable name="BlockIdType_Name" select="'NvM_BlockIdType'"/>
	<xsl:variable name="DestPtrType_Prefix" select="'NvM_DestPtr'" />

	<xsl:variable name="RequestResultType_Name" select="'NvM_RequestResultType'" />
	<xsl:variable name="ServiceIdType_Name" select="'NvM_ServiceIdType'" />
	
		
	<!-- Override intermediate transformation: Remove all Module-Configurations that do not denote our NVM  -->
	<xsl:template match="*[(local-name()='MODULE-CONFIGURATION') and (*[local-name()='DEFINITION-REF'] != '/MICROSAR/NvM')]" mode="create-intermediate" priority="1"/>

	<!-- Override intermediate transformation: translate NvmConfigBlockDescriptor into NvmBlockDescriptor node  -->
	<xsl:template match="*[(local-name() = 'CONTAINER') and (*[local-name()='DEFINITION-REF'] = '/MICROSAR/NvM/NvmConfigBlockDescriptor')]" mode="create-intermediate" priority="1">
		<xsl:element name="int:NvmBlockDescriptor">
			<xsl:attribute name="type">
				<xsl:value-of select="local-name()"/>
			</xsl:attribute>
			<xsl:apply-templates select="*[local-name()='SHORT-NAME']|*[local-name()='DEFINITION-REF']|*" mode="create-intermediate"/>
		</xsl:element>
	</xsl:template>


	<!-- root transformation rule: perform transformation into intermediate format, and trigger transformation on this new root -->
	<xsl:template match="/">
		<xsl:variable name="intermediate-doc">
			<xsl:apply-templates select="." mode="create-intermediate"/>
		</xsl:variable>
		<xsl:apply-templates select="msxsl:node-set($intermediate-doc)" mode="transform-intermediate" />
	</xsl:template>

	<!-- Entry of actual transformation, i.e. on the intermediate XML -->
	<xsl:template match="/" mode="transform-intermediate">
		<AUTOSAR>
			<!--<xsl:element name="intermediateTree">
				<xsl:copy-of select="." />
			</xsl:element>-->
			<xsl:apply-templates select="//int:NvM[(@type='MODULE-CONFIGURATION') and (@definition-ref='/MICROSAR/NvM')][1]" />
		</AUTOSAR> 
	</xsl:template>

	<xsl:template name="DV_SDG_BSW_Module">				 
		 <ADMIN-DATA>
			<SDGS>
				<SDG GID="DV_SDG">
					<SD GID="DV_BSWM">
						<xsl:value-of select="local-name(//*[@type='MODULE-CONFIGURATION'])"/>
					</SD>
				</SDG>
			</SDGS>
		</ADMIN-DATA>
	</xsl:template>
	
	<xsl:template match="int:NvM">
		<xsl:variable name="COMP_NAME" select="int:Nvm_30_CommonVendorParams/int:NvmServiceComponentName"/>		
		
		<xsl:variable name="BehaviorName" select="concat($COMP_NAME, '_Behavior')" />
		<xsl:variable name="ImplementationName" select="concat($COMP_NAME, '_Impl')" />

		<xsl:variable name="serviceBlocks" select="int:NvmBlockDescriptor[int:NvmUseServicePorts='true']" />
		<xsl:variable name="callbackBlocks" select="$serviceBlocks[(int:NvmUseJobendCallback = 'true') or
											(((int:NvmRomBlockDataAddress = '') or (int:NvmRomBlockDataAddress = 'NULL_PTR')) 
													and (int:NvmUseInitCallback = 'true') and (int:NvmInitBlockCallback != '') and (int:NvmInitBlockCallback != 'NULL_PTR'))]" />
		<TOP-LEVEL-PACKAGES>
			<AR-PACKAGE>
				<SHORT-NAME>
					<xsl:value-of select="$ComponentPackageName" />
				</SHORT-NAME>
				<ELEMENTS>
					<SERVICE-COMPONENT-TYPE>
						<SHORT-NAME>
							<xsl:value-of select="$COMP_NAME"/>
						</SHORT-NAME>
						<DESC>
							<L-2 L="EN">
								<xsl:text>Software Component description for </xsl:text>
								<xsl:value-of select="$COMP_NAME"/>
								<xsl:text> generated from Ecuc Package: </xsl:text>
								<xsl:value-of select="ancestor::int:package[1]/@name" />
							</L-2>
						</DESC>

						<CATEGORY>ServiceComponent</CATEGORY>
						<!-- Add Port Prototypes -->

						<ADMIN-DATA>
						 <SDGS>
						  <SDG GID="DV_SDG">
							   <SD GID="DV_BSWM">								   
								   <xsl:value-of select="local-name() "/>
							   </SD>
						  </SDG>
						 </SDGS>
						</ADMIN-DATA>
						
						<PORTS>
							<!-- Nvm Service Port Prototypes -->
							<xsl:apply-templates select="$serviceBlocks" mode="NVM_ServicePrototypes"/>

							<xsl:if test="(int:NvmCommon/int:NvmApiConfigClass = 'NvmApiConfigClass3')">
								<!-- Administration Port Prototypes -->
								<xsl:apply-templates select="$serviceBlocks" mode="NVM_AdminPrototypes"/>
							</xsl:if>
							<xsl:apply-templates select="$serviceBlocks[int:NvmUseJobendCallback='true']" mode="NvM_JobendPrototypes" />

							<xsl:if test="($GenerateInitCallBacks != 'false')">
								<!-- filter Blocks by (NvmUseInitCallback == true) and (NvmRomBlockDataAddress == NULL_PTR or empty) -->
								<xsl:apply-templates select="$serviceBlocks[(int:NvmUseInitCallback='true') and (int:NvmRomBlockDataAddress[(. != 'NULL_PTR') and (.!='')])]"
															   mode="NvM_InitBlockPrototypes" />
							</xsl:if>

						</PORTS>
					</SERVICE-COMPONENT-TYPE>
					<!-- Add Implementation -->
					<SWC-IMPLEMENTATION>
						<SHORT-NAME>
							<xsl:value-of select="$ImplementationName"/>
						</SHORT-NAME>
						<BEHAVIOR-REF DEST="INTERNAL-BEHAVIOR">
							<xsl:value-of select="concat('/', $ComponentPackageName, '/', $BehaviorName)"/>
						</BEHAVIOR-REF>
					</SWC-IMPLEMENTATION>
					<!-- Add Internal Behavior -->
					<INTERNAL-BEHAVIOR>
						<SHORT-NAME>
							<xsl:value-of select="$BehaviorName" />
						</SHORT-NAME>
						<COMPONENT-REF DEST="SERVICE-COMPONENT-TYPE">
							<xsl:value-of select="concat('/', $ComponentPackageName, '/', $COMP_NAME)"/>
						</COMPONENT-REF>

						<EVENTS>
							<xsl:if test="$callbackBlocks">
								<TIMING-EVENT>
									<SHORT-NAME>MainFunction_CyclicEvent</SHORT-NAME>
									<START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">
										<xsl:value-of select="concat('/', $ComponentPackageName, '/', $BehaviorName, '/NvM_MainFunction')" />
									</START-ON-EVENT-REF>
									<PERIOD>0.010000</PERIOD>
								</TIMING-EVENT>
							</xsl:if>

							<xsl:apply-templates select="$serviceBlocks" mode="NVM_OPERATION_INVOKED_EVENTS">
								<xsl:with-param name="BehaviorName" select="$BehaviorName" />
							</xsl:apply-templates>
						</EVENTS>

						<PORT-API-OPTIONS>
							<xsl:apply-templates select="$serviceBlocks" mode="NVM_PORT_DEFINED_ARGUMENTS_SERVICE"/>

							<xsl:if test="(int:NvmCommon/int:NvmApiConfigClass = 'NvmApiConfigClass3')">
								<xsl:apply-templates select="$serviceBlocks" mode="NVM_PORT_DEFINED_ARGUMENTS_ADMIN"/>
							</xsl:if>
						</PORT-API-OPTIONS>

						<RUNNABLES>
							<xsl:if test="$callbackBlocks">
								<!--
						 Define a runnable "MainFunction", which is important for the RTE. Must be done separately because the MainFunction is NOT re-entrant.
						 Note, that this runnable is not necessary for the NvM operation itself - NvM_MainFunction will be triggered by the SchM, not by the RTE.
					-->
								<RUNNABLE-ENTITY>
									<SHORT-NAME>NvM_MainFunction</SHORT-NAME>
									<DESC>
										<L-2>
											NvM_MainFunction needs to be a runnable, because it invokes the callbacks via the RTE. The RTE, in turn needs to know its context - by knowing the runnable.
											Not that the cycle time is an arbitrary value, because the MainFunction will be triggered by the SchM.
										</L-2>
									</DESC>
									<CAN-BE-INVOKED-CONCURRENTLY>false</CAN-BE-INVOKED-CONCURRENTLY>
									<SERVER-CALL-POINTS>
										<xsl:apply-templates select="$callbackBlocks" mode="DefineCallpointOperationRefs" />
									</SERVER-CALL-POINTS>
									<SYMBOL>NvM_MainFunction</SYMBOL>
								</RUNNABLE-ENTITY>
							</xsl:if>

							<xsl:apply-templates select="./int:NvmCommon" mode="NVM_RUNNABLES"/>
						</RUNNABLES>
					</INTERNAL-BEHAVIOR>
				</ELEMENTS>
			</AR-PACKAGE>

			<!-- define Port interfaces -->
			<xsl:apply-templates select="." mode="NVM_PORT_INTERFACES"/>

			<!-- DataTypes needed by NVM -->
			<xsl:apply-templates select="." mode="NVM_BASIC_TYPES"/>
		</TOP-LEVEL-PACKAGES>		
	</xsl:template>
	
	<!--
	==================================================================================================================
	PORT PROTOTYPES
	==================================================================================================================
	-->

	<!-- Configuration dependend Port Prototypes Template -->
	<xsl:template match="int:NvmBlockDescriptor" mode="NVM_ServicePrototypes">
		<xsl:variable name="serviceInterfaceRef">
			<xsl:apply-templates select="." mode="getInterfaceReferenceByBlockCfg" />
		</xsl:variable>

		<xsl:variable name="serviceInterfaceName">
			<xsl:variable name="temp">
				<xsl:apply-templates select="." mode="getInterfaceNameByBlockCfg" />
			</xsl:variable>

			<xsl:value-of select="normalize-space($temp)" />
		</xsl:variable>

		<P-PORT-PROTOTYPE>
			<SHORT-NAME>
				<xsl:apply-templates select="." mode="PortProtoType">
					<xsl:with-param name="prototypePrefix" select="$ServicePrototype_Prefix" />
				</xsl:apply-templates>
			</SHORT-NAME>

			<LONG-NAME>
				<L-4 L="EN">
					<xsl:value-of select="concat('PPort_', @name, ' : ', $serviceInterfaceName)" />
				</L-4>
			</LONG-NAME>

			<DESC>
				<L-2 L="EN">
					P-Port Prototype of <xsl:value-of select="$serviceInterfaceName" /> for NVRAM Block <xsl:value-of select="@name" />
				</L-2>
			</DESC>

			<PROVIDED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">
				<xsl:value-of select="$serviceInterfaceRef" />
			</PROVIDED-INTERFACE-TREF>
		</P-PORT-PROTOTYPE>
	</xsl:template>
	
	<!-- Adminstration port prototype template -->
	<xsl:template match="int:NvmBlockDescriptor" mode="NVM_AdminPrototypes">
		<P-PORT-PROTOTYPE>
			<SHORT-NAME>
				<xsl:apply-templates select="."  mode="PortProtoType">
					<xsl:with-param name="prototypePrefix" select="$AdminPrototype_Prefix" />
				</xsl:apply-templates>
			</SHORT-NAME>
			<LONG-NAME>
				<L-4 L="EN">
					<xsl:value-of select="concat('PPort_', ./@name, ' : ', $InterfaceName_Administration)" />
				</L-4>
			</LONG-NAME>
			<DESC>
				<L-2 L="EN">
					P-Port Prototype of <xsl:value-of select="$InterfaceName_Administration" /> for NVRAM Block <xsl:value-of select="./@name" />
				</L-2>
			</DESC>
			<PROVIDED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">
				<xsl:value-of select="concat('/', $InterfacePackageName, '/', $InterfaceName_Administration)" />
			</PROVIDED-INTERFACE-TREF>
		</P-PORT-PROTOTYPE>
	</xsl:template>

	<!-- Jobend notification port prototype template -->
	<xsl:template match="int:NvmBlockDescriptor" mode="NvM_JobendPrototypes">
		<R-PORT-PROTOTYPE>
			<SHORT-NAME>
				<xsl:apply-templates select="." mode="PortProtoType">
					<xsl:with-param name="prototypePrefix" select="./ancestor::int:NvM/int:Nvm_30_CommonVendorParams/int:NvmSrvPortJobEndPrefix/text()" />
				</xsl:apply-templates>
			</SHORT-NAME>
			<LONG-NAME>
				<L-4 L="EN">
					<xsl:value-of select="concat('RPort_', ./@name, ' : ', $InterfaceName_NotifyFinished)" />
				</L-4>
			</LONG-NAME>
			<DESC>
				<L-2 L="EN">
					R-Port Prototype of <xsl:value-of select="$InterfaceName_NotifyFinished" /> for NVRAM Block <xsl:value-of select="./@name" />
				</L-2>
			</DESC>

			<REQUIRED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">
				<xsl:value-of select="concat('/', $InterfacePackageName, '/', $InterfaceName_NotifyFinished)" />
			</REQUIRED-INTERFACE-TREF>
		</R-PORT-PROTOTYPE>
	</xsl:template>

	<!-- Init Block callback port prototype template -->
	<xsl:template match="int:NvmBlockDescriptor" mode="NvM_InitBlockPrototypes">
		<R-PORT-PROTOTYPE>
			<SHORT-NAME>
				<xsl:apply-templates select="." mode="PortProtoType">
					<xsl:with-param name="prototypePrefix" select="./ancestor::int:NvM/int:Nvm_30_CommonVendorParams/int:NvmSrvPortInitBlockPrefix/text()" />
				</xsl:apply-templates>
			</SHORT-NAME>
			<LONG-NAME>
				<L-4 L="EN">
					<xsl:value-of select="concat('RPort_', ./@name, ' : ', $InterfaceName_NotifyBlockInit)" />
				</L-4>
			</LONG-NAME>
			<DESC>
				<L-2 L="EN">
					R-Port Prototype of <xsl:value-of select="$InterfaceName_NotifyBlockInit" /> for NVRAM Block <xsl:value-of select="./@name" />
				</L-2>
			</DESC>

			<REQUIRED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">
				<xsl:value-of select="concat('/', $InterfacePackageName, '/', $InterfaceName_NotifyBlockInit)" />
			</REQUIRED-INTERFACE-TREF>
		</R-PORT-PROTOTYPE>
	</xsl:template>

	<xsl:template match="int:NvmBlockDescriptor" mode="PortProtoType">
		<xsl:param name="prototypePrefix" select="'NO_PREFIX_GIVEN'" />

		<xsl:choose>
			<xsl:when test="./ancestor::int:NvM/int:Nvm_30_CommonVendorParams/int:Nvm_UseLongSwcNames = 'true'">
				<xsl:value-of select="concat($prototypePrefix, ./@name)"  />
			</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="blockId">
					<xsl:value-of select="./int:NvmNvramBlockIdentifier" />
				</xsl:variable>
				<xsl:value-of select="concat($prototypePrefix, normalize-space($blockId))"  />
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="int:NvmBlockDescriptor" mode="PortPrototypeReference">
		<xsl:param name="prototypePrefix" />

		<xsl:variable name="portProtoName">
			<xsl:apply-templates select="."  mode="PortProtoType">
				<xsl:with-param name="prototypePrefix" select="$prototypePrefix" />
			</xsl:apply-templates>
		</xsl:variable>

		<xsl:value-of select="concat('/', $ComponentPackageName, '/', ./ancestor::int:NvM/int:Nvm_30_CommonVendorParams/int:NvmServiceComponentName, '/',  normalize-space($portProtoName))"  />
	</xsl:template>

	<!--
	==================================================================================================================
	OPERATION_INVOKED_EVENTS
	==================================================================================================================
	-->
	<xsl:template match="int:NvmBlockDescriptor" mode="NVM_OPERATION_INVOKED_EVENTS">
		<xsl:param name="BehaviorName" select="'NO_BEHAVIOR'" />
		
		<xsl:variable name="serviceInterfaceRef">
			<xsl:apply-templates select="." mode="getInterfaceReferenceByBlockCfg" />
		</xsl:variable>

		<xsl:comment>
			<xsl:value-of select="./@name" />
		</xsl:comment>

		<xsl:call-template name="NvmOperationInvokedEventTemplate">
			<xsl:with-param name="BehaviorName" select="$BehaviorName" />
			<xsl:with-param name="interfaceReference" select="$serviceInterfaceRef" />
			<xsl:with-param name="prototypeRef">
				<xsl:apply-templates select="."  mode="PortPrototypeReference">
					<xsl:with-param name="prototypePrefix" select="$ServicePrototype_Prefix" />
				</xsl:apply-templates>
			</xsl:with-param>

			<xsl:with-param name="blockId" select="./int:NvmNvramBlockIdentifier" />
			<xsl:with-param name="operationList">
				<xsl:apply-templates select="." mode="GetBlockServiceList" />
			</xsl:with-param>
		</xsl:call-template>

		<xsl:if test="(./ancestor::int:NvM/int:NvmCommon/int:NvmApiConfigClass = 'NvmApiConfigClass3')">
			<xsl:call-template name="NvmOperationInvokedEventTemplate">
				<xsl:with-param name="BehaviorName" select="$BehaviorName" />
				<xsl:with-param name="interfaceReference" select="concat('/', $InterfacePackageName, '/', $InterfaceName_Administration)" />
				<xsl:with-param name="prototypeRef">
					<xsl:apply-templates select="."  mode="PortPrototypeReference">
						<xsl:with-param name="prototypePrefix" select="$AdminPrototype_Prefix" />
					</xsl:apply-templates>
				</xsl:with-param>
				<xsl:with-param name="blockId" select="./int:NvmNvramBlockIdentifier" />
				<xsl:with-param name="operationList" select="'SetBlockProtection = SetBlockProtection;'" />
			</xsl:call-template>
		</xsl:if>
	</xsl:template>

	<xsl:template name="NvmOperationInvokedEventTemplate">
		<xsl:param name="BehaviorName" select="'NO_BEHAVIOR'" />
		<xsl:param name="interfaceReference" select="'NO_INTERFACE'"/>
		<xsl:param name="operationList" select="'NO_OPERATION'" />
		<xsl:param name="prototypeRef" select="'NO_PROTOTYPE'" />
		<xsl:param name="blockId" select="'NVM_INVALID_BLOCK_ID'" />

		<xsl:variable name="operation" select="substring-before($operationList, ';')" />

		<xsl:if test="($operation != '')">
			<xsl:variable name="newOpList" select="substring-after($operationList, ';')" />

			<xsl:variable name="opName" select="normalize-space(substring-before($operation, '='))" />

			<OPERATION-INVOKED-EVENT>
				<SHORT-NAME>
					<xsl:value-of select="concat('V_', $blockId, '_', $opName)" />
				</SHORT-NAME>
				<START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">
					<xsl:value-of select="concat('/', $ComponentPackageName, '/', $BehaviorName, '/', normalize-space(substring-after($operation, '=')))" />
				</START-ON-EVENT-REF>
				<OPERATION-IREF>
					<P-PORT-PROTOTYPE-REF DEST="P-PORT-PROTOTYPE">
						<xsl:value-of select="$prototypeRef"/>
					</P-PORT-PROTOTYPE-REF>
					<OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">
						<xsl:value-of select="concat($interfaceReference, '/', $opName)" />
					</OPERATION-PROTOTYPE-REF>
				</OPERATION-IREF>
			</OPERATION-INVOKED-EVENT>

			<xsl:call-template name="NvmOperationInvokedEventTemplate">
				<xsl:with-param name="BehaviorName" select="$BehaviorName" />
				<xsl:with-param name="interfaceReference" select="$interfaceReference" />
				<xsl:with-param name="prototypeRef" select="$prototypeRef" />
				<xsl:with-param name="blockId" select="$blockId" />
				<xsl:with-param name="operationList" select="$newOpList" />
			</xsl:call-template>
		</xsl:if>
	</xsl:template>

	<!-- 
==================================================================================================================    
		PORT_DEFINED_ARGUMENTS
==================================================================================================================
-->
	<xsl:template match="int:NvmBlockDescriptor" mode="NVM_PORT_DEFINED_ARGUMENTS_SERVICE">
		<PORT-API-OPTION>
			<xsl:comment>
				<xsl:value-of select="./@name" />
			</xsl:comment>
			<PORT-ARG-VALUES>
				<INTEGER-LITERAL>
					<SHORT-NAME>
						<xsl:value-of select="concat('NvM_ServiceBlockId_', ./int:NvmNvramBlockIdentifier)"/>
					</SHORT-NAME>
					<TYPE-TREF DEST="INTEGER-TYPE">
						<xsl:value-of select="concat('/', $DataTypesPackageName, '/', $BlockIdType_Name)" />
					</TYPE-TREF>
					<VALUE>
						<xsl:value-of select="./int:NvmNvramBlockIdentifier"/>
					</VALUE>
				</INTEGER-LITERAL>
			</PORT-ARG-VALUES>
			<PORT-REF DEST="P-PORT-PROTOTYPE">
				<xsl:apply-templates select="."  mode="PortPrototypeReference">
					<xsl:with-param name="prototypePrefix" select="$ServicePrototype_Prefix" />
				</xsl:apply-templates>
			</PORT-REF>
		</PORT-API-OPTION>
	</xsl:template>

	<xsl:template match="int:NvmBlockDescriptor" mode="NVM_PORT_DEFINED_ARGUMENTS_ADMIN">
		<PORT-API-OPTION>
			<xsl:comment>
				<xsl:value-of select="./@name" />
			</xsl:comment>
			<PORT-ARG-VALUES>
				<INTEGER-LITERAL>
					<SHORT-NAME>
						<xsl:value-of select="concat('NvM_AdminBlockId_', ./int:NvmNvramBlockIdentifier)"/>
					</SHORT-NAME>
					<TYPE-TREF DEST="INTEGER-TYPE">
						<xsl:value-of select="concat('/', $DataTypesPackageName, '/', $BlockIdType_Name)" />
					</TYPE-TREF>
					<VALUE>
						<xsl:value-of select="./int:NvmNvramBlockIdentifier"/>
					</VALUE>
				</INTEGER-LITERAL>
			</PORT-ARG-VALUES>
			<PORT-REF DEST="P-PORT-PROTOTYPE">
				<xsl:apply-templates select="."  mode="PortPrototypeReference">
					<xsl:with-param name="prototypePrefix" select="$AdminPrototype_Prefix" />
				</xsl:apply-templates>
			</PORT-REF>
		</PORT-API-OPTION>
	</xsl:template>


	<!--	
	==================================================================================================================    
			RUNNABLES
	==================================================================================================================
	-->
	<!-- Server call points template; specify the operations the MainFunction calls, i.e. the callbacks -->
	<xsl:template match="int:NvmBlockDescriptor" mode="DefineCallpointOperationRefs">

		<!-- Job end notification -->
		<xsl:if test="./int:NvmUseJobendCallback = 'true'">
			<SYNCHRONOUS-SERVER-CALL-POINT>
				<SHORT-NAME>
					<xsl:value-of select="concat('MfCp_NyJe_Id', ./int:NvmNvramBlockIdentifier)" />
				</SHORT-NAME>
				<LONG-NAME>
					<L-4 L="EN">
						<xsl:value-of select="concat('MainFunctionCallPoint_NotifyJobEnd_', ./@name)" />
					</L-4>
				</LONG-NAME>
				<DESC>
					<L-2 L="EN">
						Specifies that the Single Block Job End Notification Callback of NVRAM Block of <xsl:value-of select="./@name" /> will be called from scope of NvM_Mainfunction.
					</L-2>
				</DESC>
				<OPERATION-IREFS>
					<OPERATION-IREF>
						<R-PORT-PROTOTYPE-REF DEST="R-PORT-PROTOTYPE">
							<xsl:apply-templates select="."  mode="PortPrototypeReference">
								<xsl:with-param name="prototypePrefix" select="./ancestor::int:NvM/int:Nvm_30_CommonVendorParams/int:NvmSrvPortJobEndPrefix" />
							</xsl:apply-templates>
						</R-PORT-PROTOTYPE-REF>
						<OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">
							<xsl:value-of select="concat('/', $InterfacePackageName, '/', $InterfaceName_NotifyFinished, '/JobFinished')" />
						</OPERATION-PROTOTYPE-REF>
					</OPERATION-IREF>
				</OPERATION-IREFS>
			</SYNCHRONOUS-SERVER-CALL-POINT>
		</xsl:if>

		<!-- 
			Block Init callback, generation depends on global variable ...
			It is intended to have to ifs, instead of using the 'and' operator ...
		-->
		<xsl:if test="($GenerateInitCallBacks != 'false')">
			<xsl:if test="(./int:NvmUseInitCallback = 'true') and (./int:NvmRomBlockDataAddress[(. = '') or (. = 'NULL_PTR')])">
				<SYNCHRONOUS-SERVER-CALL-POINT>
					<SHORT-NAME>
						<xsl:value-of select="concat('MfCp_NyBi_Id', ./int:NvmNvramBlockIdentifier)" />
					</SHORT-NAME>
					<LONG-NAME>
						<L-4 L="EN">
							<xsl:value-of select="concat('MainFunctionCallPoint_NotifyBlockInit_', ./@name)" />
						</L-4>
					</LONG-NAME>
					<DESC>
						<L-2 L="EN">
							Specifies that the Block Init Notification Callback of NVRAM Block of <xsl:value-of select="./@name" /> will be called from scope of NvM_Mainfunction.
						</L-2>
					</DESC>
					<OPERATION-IREFS>
						<OPERATION-IREF>
							<R-PORT-PROTOTYPE-REF DEST="R-PORT-PROTOTYPE">
								<xsl:apply-templates select="."  mode="PortPrototypeReference">
									<xsl:with-param name="prototypePrefix" select="./ancestor::int:NvM/int:Nvm_30_CommonVendorParams/int:NvmSrvPortInitBlockPrefix" />
								</xsl:apply-templates>
							</R-PORT-PROTOTYPE-REF>
							<OPERATION-PROTOTYPE-REF DEST="OPERATION-PROTOTYPE">
								<xsl:value-of select="concat('/', $InterfacePackageName, '/', $InterfaceName_NotifyBlockInit, '/InitBlock')" />
							</OPERATION-PROTOTYPE-REF>
						</OPERATION-IREF>
					</OPERATION-IREFS>
				</SYNCHRONOUS-SERVER-CALL-POINT>
			</xsl:if>
		</xsl:if>
	</xsl:template>
	<!--
		=======================================================================
			Runnables Template
		=======================================================================
	-->
	<!-- Define Common Runnables -->
	<xsl:template match="int:NvmCommon" mode="NVM_RUNNABLES">
		<xsl:variable name="serviceBlocks" select="./ancestor::int:NvM/int:NvmBlockDescriptor[int:NvmUseServicePorts = 'true']" />
		<xsl:call-template name="defineRunnables">
			<xsl:with-param name="runnables">
				GetErrorStatus = NvM_GetErrorStatus;
				<xsl:if test="./int:NvmSetRamBlockStatusApi = 'true'">
					SetRamBlockStatus = NvM_SetRamBlockStatus;
				</xsl:if>
				<xsl:if test="(int:NvmApiConfigClass != 'NvmApiConfigClass1')">
					ReadBlock = NvM_ReadBlock;
					WriteBlock = NvM_WriteBlock;
					<xsl:if test="count($serviceBlocks[int:NvmRomBlockDataAddress[. !='' and . != 'NULL_PTR'] or int:NvmUseInitCallback = 'true']) &gt; 0">
						RestoreBlockDefaults = NvM_RestoreBlockDefaults;
					</xsl:if>
					<xsl:if test="count($serviceBlocks[int:NvmBlockManagementType = 'NVM_BLOCK_DATASET']) &gt; 0">
						SetDataIndex = NvM_SetDataIndex;
						GetDataIndex = NvM_GetDataIndex;
					</xsl:if>
					<xsl:if test="(int:NvmApiConfigClass = 'NvmApiConfigClass3')">
						InvalidateNvBlock = NvM_InvalidateNvBlock;
						EraseBlock = NvM_EraseNvBlock;
						SetBlockProtection = NvM_SetBlockProtection;
					</xsl:if>
				</xsl:if>
			</xsl:with-param>
		</xsl:call-template>
	</xsl:template>

	<xsl:template name="defineRunnables">
		<xsl:param name="runnables" />

		<xsl:variable name="operation" select="normalize-space(substring-before($runnables, ';'))" />

		<xsl:if test="($operation != '')">
			<xsl:variable name="newRunList" select="substring-after($runnables, ';')" />

			<RUNNABLE-ENTITY>
				<SHORT-NAME>
					<xsl:value-of select="normalize-space(substring-before($operation, '='))" />
				</SHORT-NAME>
				<CAN-BE-INVOKED-CONCURRENTLY>true</CAN-BE-INVOKED-CONCURRENTLY>
				<SYMBOL>
					<xsl:value-of select="normalize-space(substring-after($operation, '='))" />
				</SYMBOL>
			</RUNNABLE-ENTITY>

			<xsl:call-template name="defineRunnables">
				<xsl:with-param name="runnables" select="$newRunList" />
			</xsl:call-template>
		</xsl:if>
	</xsl:template>

	<!--
	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		template: matches NvmBlockDescriptor
		    mode: getInterfaceNameByBlockCfg
		
		"Returns" the Interface name, which depends on the Block Config.

		Scheme: 						NvmService[_Defs][_DS]
	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	 -->

	<xsl:template match="int:NvmBlockDescriptor" mode="getInterfaceNameByBlockCfg">
		<xsl:variable name="InterfacePrefix_Service">
			<xsl:apply-templates select="./ancestor::int:NvM" mode="GetPortInterfacePrefix" />
		</xsl:variable>
		<xsl:variable name="ApiConfigClass" select="./ancestor::int:NvM/int:NvmCommon/int:NvmApiConfigClass" />

		<xsl:choose>
			<xsl:when test="($ApiConfigClass != 'NvmApiConfigClass1')">

				<xsl:variable name="operations">
					<xsl:apply-templates select="." mode="GetBlockServiceList" />
				</xsl:variable>

				<xsl:variable name="DatasetString">
					<xsl:if test="contains($operations, 'SetDataIndex')">
						_DS
					</xsl:if>
				</xsl:variable>

				<xsl:variable name="RomDefaultsString">
					<xsl:if test="contains($operations, 'RestoreBlockDefaults')">
						_Defs
					</xsl:if>
				</xsl:variable>

				<xsl:value-of select="concat(normalize-space($InterfacePrefix_Service), normalize-space($RomDefaultsString), normalize-space($DatasetString))" />
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="normalize-space($InterfacePrefix_Service)" />
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="int:NvmBlockDescriptor" mode="getInterfaceReferenceByBlockCfg">
		<xsl:variable name="interfaceName">
			<xsl:apply-templates select="." mode="getInterfaceNameByBlockCfg" />
		</xsl:variable>

		<xsl:value-of select="concat('/', $InterfacePackageName, '/', normalize-space($interfaceName))" />
	</xsl:template>

	<xsl:template match="int:NvmBlockDescriptor" mode="GetBlockServiceList">
		<!-- Format: operation = runnable; -->
		<xsl:variable name="ApiConfigClass" select="ancestor::int:NvM/int:NvmCommon/int:NvmApiConfigClass" />

		GetErrorStatus = GetErrorStatus;
		<xsl:if test="(../int:NvmCommon/int:NvmSetRamBlockStatusApi = 'true')">
			SetRamBlockStatus = SetRamBlockStatus;
		</xsl:if>
		<xsl:if test="($ApiConfigClass != 'NvmApiConfigClass1')">
			ReadBlock = ReadBlock;
			WriteBlock = WriteBlock;

			<xsl:if test="(./int:NvmUseInitCallback = 'true') or (./int:NvmRomBlockDataAddress[(text() != 'NULL_PTR') and (text() != '')])">
				RestoreBlockDefaults = RestoreBlockDefaults;
			</xsl:if>

			<xsl:if test="(./int:NvmBlockManagementType = 'NVM_BLOCK_DATASET')">
				SetDataIndex = SetDataIndex;
				GetDataIndex = GetDataIndex;
			</xsl:if>

			<xsl:if test="($ApiConfigClass = 'NvmApiConfigClass3')">
				InvalidateNvBlock = InvalidateNvBlock;
				EraseBlock = EraseBlock;
			</xsl:if>
		</xsl:if>
	</xsl:template>

	<xsl:template match="int:NvM" mode="GetPortInterfacePrefix">
		<xsl:variable name="configClass">
			<xsl:choose>
				<xsl:when test="int:NvmCommon/int:NvmApiConfigClass = 'NvmApiConfigClass3'">
					AC3
				</xsl:when>
				<xsl:when test="int:NvmCommon/int:NvmApiConfigClass = 'NvmApiConfigClass2'">
					AC2
				</xsl:when>
				<xsl:otherwise>
					AC1
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

		<xsl:variable name="setRamBlockStatus">
			<xsl:choose>
				<xsl:when test="int:NvmCommon/int:NvmSetRamBlockStatusApi='true'">
					_SRBS
				</xsl:when>
				<xsl:otherwise>
					<xsl:text/>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

		<xsl:value-of select="concat('NvM_', normalize-space($configClass), normalize-space($setRamBlockStatus), '_Srv')" />
	</xsl:template>

	<!-- 
	==================================================================================================================    
		PORT INTERFACES
	==================================================================================================================
	-->
	<!-- Port Interface Template -->
	<xsl:template match="int:NvM" mode="NVM_PORT_INTERFACES">
		<xsl:variable name="API_CONFIG_CLASS" select="./int:NvmCommon/int:NvmApiConfigClass" />
		<xsl:variable name="ServiceBlocks" select="./int:NvmBlockDescriptor[int:NvmUseServicePorts = 'true']" />
		
			<AR-PACKAGE>
				<SHORT-NAME>
					<xsl:value-of select="$InterfacePackageName" />
				</SHORT-NAME>
				<ELEMENTS>

					<!--
				+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						Provide the Administration interface (SetBlockProtection).
						It is common to all NVRAM blocks.
				+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				-->
					<xsl:if test="($API_CONFIG_CLASS = 'NvmApiConfigClass3')">
						<CLIENT-SERVER-INTERFACE>
							<SHORT-NAME>
								<xsl:value-of select="$InterfaceName_Administration" />
							</SHORT-NAME>
							
							<xsl:call-template name="DV_SDG_BSW_Module"/>							
							
							<IS-SERVICE>true</IS-SERVICE>
							<OPERATIONS>
								<OPERATION-PROTOTYPE>
									<SHORT-NAME>SetBlockProtection</SHORT-NAME>
									<ARGUMENTS>
										<ARGUMENT-PROTOTYPE>
											<SHORT-NAME>ProtectionEnabled</SHORT-NAME>
											<TYPE-TREF DEST="BOOLEAN-TYPE">
												<xsl:value-of select="concat('/', $DataTypesPackageName, '/Boolean')" />
											</TYPE-TREF>
											<DIRECTION>IN</DIRECTION>
										</ARGUMENT-PROTOTYPE>
									</ARGUMENTS>
								</OPERATION-PROTOTYPE>
							</OPERATIONS>
						</CLIENT-SERVER-INTERFACE>
					</xsl:if>

					<!--
				+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						Define the "single block job end notification" callback Port Interface.
						It is common to all NVRAM blocks.

						Define this interface only, if there are NVRAM Blocks with callbacks
				+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				-->
					<!-- Is there at least one block that has "UseServicePorts" and "Callback"? -->
					<xsl:if test="count($ServiceBlocks[int:NvmUseJobendCallback = 'true']) &gt; 0">
						<CLIENT-SERVER-INTERFACE>
							<SHORT-NAME>
								<xsl:value-of select="$InterfaceName_NotifyFinished" />
							</SHORT-NAME>
							
							<xsl:call-template name="DV_SDG_BSW_Module"/>																	
							
							<IS-SERVICE>true</IS-SERVICE>
							<OPERATIONS>
								<OPERATION-PROTOTYPE>
									<SHORT-NAME>JobFinished</SHORT-NAME>
									<ARGUMENTS>
										<ARGUMENT-PROTOTYPE>
											<SHORT-NAME>ServiceId</SHORT-NAME>
											<TYPE-TREF DEST="INTEGER-TYPE">
												<xsl:value-of select="concat('/', $DataTypesPackageName, '/', $ServiceIdType_Name)" />
											</TYPE-TREF>
											<DIRECTION>IN</DIRECTION>
										</ARGUMENT-PROTOTYPE>
										<ARGUMENT-PROTOTYPE>
											<SHORT-NAME>JobResult</SHORT-NAME>
											<TYPE-TREF DEST="INTEGER-TYPE">
												<xsl:value-of select="concat('/', $DataTypesPackageName, '/', $RequestResultType_Name)" />
											</TYPE-TREF>
											<DIRECTION>IN</DIRECTION>
										</ARGUMENT-PROTOTYPE>
									</ARGUMENTS>
									<POSSIBLE-ERROR-REFS>
										<POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">
											<xsl:value-of select="concat('/', $InterfacePackageName, '/' , $InterfaceName_NotifyFinished, '/E_NOT_OK')" />
										</POSSIBLE-ERROR-REF>
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
					<xsl:if test="($GenerateInitCallBacks != 'false')">
						<!--
					+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							Define the "block init" callback Port Interface.
							It is common to all NVRAM blocks.
					+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					-->
						<CLIENT-SERVER-INTERFACE>
							<SHORT-NAME>
								<xsl:value-of select="$InterfaceName_NotifyBlockInit" />
							</SHORT-NAME>
							
							<xsl:call-template name="DV_SDG_BSW_Module"/>																	
							
							<IS-SERVICE>true</IS-SERVICE>
							<OPERATIONS>
								<OPERATION-PROTOTYPE>
									<SHORT-NAME>InitBlock</SHORT-NAME>
									<ARGUMENTS>
										<!-- None. -->
									</ARGUMENTS>
									<POSSIBLE-ERROR-REFS>
										<POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">
											<xsl:value-of select="concat('/', $InterfacePackageName, '/' , $InterfaceName_NotifyBlockInit, '/E_NOT_OK')" />
										</POSSIBLE-ERROR-REF>
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
					<!--
				+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						Define the "basic" service port interface, i.e. that is used if API Config Classe = 1.
						It is common to all NVRAM blocks.
				+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				-->

					<xsl:if test="($API_CONFIG_CLASS = 'NvmApiConfigClass1')">
						<CLIENT-SERVER-INTERFACE>
							<SHORT-NAME>
								<xsl:apply-templates select="." mode="GetPortInterfacePrefix" />
							</SHORT-NAME>
							
							<xsl:call-template name="DV_SDG_BSW_Module"/>																	
							
							<IS-SERVICE>true</IS-SERVICE>
							<OPERATIONS>
								<xsl:apply-templates select="./int:NvmCommon" mode="NvM_CommonServiceOpPrototypesCfgDependent" />
							</OPERATIONS>
						</CLIENT-SERVER-INTERFACE>
					</xsl:if>

					<xsl:if test="($API_CONFIG_CLASS != 'NvmApiConfigClass1')">
						<xsl:variable name="romDefaultsBlocks" select="$ServiceBlocks[((int:NvmRomBlockDataAddress != 'NULL_PTR') and (int:NvmRomBlockDataAddress != '')) or (int:NvmUseInitCallback = 'true')]" />
						<xsl:variable name="noRomDefaultsBlocks" select="$ServiceBlocks[((int:NvmRomBlockDataAddress = 'NULL_PTR') or (int:NvmRomBlockDataAddress = '')) and (int:NvmUseInitCallback = 'false')]" />
						<xsl:apply-templates select="$noRomDefaultsBlocks[int:NvmBlockManagementType != 'NVM_BLOCK_DATASET'][1]" mode="NvM_ServicePortInterfaceBlockDependent" />
						<xsl:apply-templates select="$romDefaultsBlocks[int:NvmBlockManagementType != 'NVM_BLOCK_DATASET'][1]" mode="NvM_ServicePortInterfaceBlockDependent" />
						<xsl:apply-templates select="$noRomDefaultsBlocks[int:NvmBlockManagementType = 'NVM_BLOCK_DATASET'][1]" mode="NvM_ServicePortInterfaceBlockDependent" />
						<xsl:apply-templates select="$romDefaultsBlocks[int:NvmBlockManagementType = 'NVM_BLOCK_DATASET'][1]" mode="NvM_ServicePortInterfaceBlockDependent" />
					</xsl:if>
				</ELEMENTS>
			</AR-PACKAGE>
	</xsl:template>

	<!--
	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		Template to output the the common Port operations: GetErrorStatus, and, if configured, SetRamBlockStatus. 
		
		The generated port operations are common to all NVRAM blocks
	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	-->
	<xsl:template match="int:NvmCommon" mode="NvM_CommonServiceOpPrototypesCfgDependent">

		<OPERATION-PROTOTYPE>
			<SHORT-NAME>GetErrorStatus</SHORT-NAME>
			<ARGUMENTS>
				<ARGUMENT-PROTOTYPE>
					<SHORT-NAME>ErrorStatus</SHORT-NAME>
					<TYPE-TREF DEST="INTEGER-TYPE">
						<xsl:value-of select="concat('/', $DataTypesPackageName, '/', $RequestResultType_Name)"/>
					</TYPE-TREF>
					<DIRECTION>OUT</DIRECTION>
				</ARGUMENT-PROTOTYPE>
			</ARGUMENTS>
		</OPERATION-PROTOTYPE>

		<!-- Generate SetRamBlockStaus operation prototype only, if NvmSetRamBlockStatusApi = TRUE -->
		<xsl:if test="./int:NvmSetRamBlockStatusApi = 'true'">
			<OPERATION-PROTOTYPE>
				<SHORT-NAME>SetRamBlockStatus</SHORT-NAME>
				<ARGUMENTS>
					<ARGUMENT-PROTOTYPE>
						<SHORT-NAME>RamBlockStatus</SHORT-NAME>
						<TYPE-TREF DEST="BOOLEAN-TYPE">
							<xsl:value-of select="concat('/', $DataTypesPackageName, '/Boolean')" />
						</TYPE-TREF>
						<DIRECTION>IN</DIRECTION>
					</ARGUMENT-PROTOTYPE>
				</ARGUMENTS>
			</OPERATION-PROTOTYPE>
		</xsl:if>
	</xsl:template>

	<!--
	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			Define the NVM Service Port Interface.
	
			Its oprations depend on "Set Ram Block Status API" value
			as well as block specific parameters (MngmtType == DATASET, total block length).
			These parameters will be used to reduce the number of port interfaces:
			- same NVRAM blocks with similar configuration (equal total block length, Mngmt Type) share the same
			  Port Interface
			
			Therefore the Port Interface name follow the following scheme:
			NvmService_{Length}[_Dataset]

			The template matches all NvmBlockDescriptor nodes.
			It is expected to be applied only once per type.
	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	-->
	<xsl:template match="int:NvmBlockDescriptor" mode="NvM_ServicePortInterfaceBlockDependent">
		<xsl:variable name="interfaceName">
			<xsl:apply-templates select="." mode="getInterfaceNameByBlockCfg" />
		</xsl:variable>

		<xsl:variable name="interfaceReference">
			<xsl:apply-templates select="." mode="getInterfaceReferenceByBlockCfg" />
		</xsl:variable>

		<xsl:variable name="dataPtrTypeName" select="concat('/',$DataTypesPackageName , '/', $DestPtrType_Prefix)" />
		
		<CLIENT-SERVER-INTERFACE>
			<SHORT-NAME>
				<xsl:value-of select="$interfaceName" />
			</SHORT-NAME>

			<LONG-NAME>
				<L-4 L="EN">
					<xsl:variable name="BlockType_Infix">
						<xsl:if test="contains($interfaceName, '_Defs')">
							<xsl:text>_HasRomDefaults</xsl:text>
						</xsl:if>
						<xsl:if test="contains($interfaceName, '_DS')">
							<xsl:text>_IsDataSet	</xsl:text>
						</xsl:if>
					</xsl:variable>
					<xsl:value-of select="concat('NvmService_', ./ancestor::int:NvM/int:NvmCommon/int:NvmApiConfigClass, normalize-space($BlockType_Infix))" />
				</L-4>
			</LONG-NAME>
			<DESC>
				<L-2 L="EN">
					Port Interface for NVRAM Blocks 
					<xsl:choose>
						<xsl:when test="contains($interfaceName, '_Defs_DS')">
							of Management Type &quot;DATASET&quot; with default values.
						</xsl:when>
						<xsl:when test="contains($interfaceName, '_DS')">
							of Management Type &quot;DATASET&quot; without default values.
						</xsl:when>
						<xsl:when test="contains($interfaceName, '_Defs')">
							of Management Types &quot;NATIVE&quot; or &quot;REDUNDANT&quot; with default values.
						</xsl:when>
						<xsl:otherwise>
							of Management Types &quot;NATIVE&quot; or &quot;REDUNDANT&quot; without default values.
						</xsl:otherwise>
					</xsl:choose>
				</L-2>
			</DESC>
			
			<xsl:call-template name="DV_SDG_BSW_Module"/>																	
								
			<IS-SERVICE>true</IS-SERVICE>
			<OPERATIONS>
				<!-- common operation prototypes - GetErrorStatus and, optional, SetRamBlockStatus -->
				<xsl:apply-templates select="./ancestor::int:NvM/int:NvmCommon" mode="NvM_CommonServiceOpPrototypesCfgDependent" />

				<!-- API Config Class 2 operations - unconditional, since this template is only used, if the API Config Class is at least 2 -->
				<xsl:if test="contains($interfaceName, '_DS')">
					<OPERATION-PROTOTYPE>
						<SHORT-NAME>SetDataIndex</SHORT-NAME>
						<ARGUMENTS>
							<ARGUMENT-PROTOTYPE>
								<SHORT-NAME>DataIndex</SHORT-NAME>
								<TYPE-TREF DEST="INTEGER-TYPE">
									<xsl:value-of select="concat('/', $DataTypesPackageName, '/UInt8')" />
								</TYPE-TREF>
								<DIRECTION>IN</DIRECTION>
							</ARGUMENT-PROTOTYPE>
						</ARGUMENTS>
					</OPERATION-PROTOTYPE>
					<OPERATION-PROTOTYPE>
						<SHORT-NAME>GetDataIndex</SHORT-NAME>
						<ARGUMENTS>
							<ARGUMENT-PROTOTYPE>
								<SHORT-NAME>DataIndex</SHORT-NAME>
								<TYPE-TREF DEST="INTEGER-TYPE">
									<xsl:value-of select="concat('/', $DataTypesPackageName, '/UInt8')" />
								</TYPE-TREF>
								<DIRECTION>OUT</DIRECTION>
							</ARGUMENT-PROTOTYPE>
						</ARGUMENTS>
					</OPERATION-PROTOTYPE>
				</xsl:if>

				<OPERATION-PROTOTYPE>
					<SHORT-NAME>ReadBlock</SHORT-NAME>
					<ARGUMENTS>
						<ARGUMENT-PROTOTYPE>
							<SHORT-NAME>DstPtr</SHORT-NAME>
							<TYPE-TREF DEST="ARRAY-TYPE">
								<xsl:value-of select="$dataPtrTypeName" />
							</TYPE-TREF>
							<DIRECTION>OUT</DIRECTION>
						</ARGUMENT-PROTOTYPE>
					</ARGUMENTS>
					<POSSIBLE-ERROR-REFS>
						<POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">
							<xsl:value-of select="concat($interfaceReference, '/E_NOT_OK')" />
						</POSSIBLE-ERROR-REF>
					</POSSIBLE-ERROR-REFS>
				</OPERATION-PROTOTYPE>

				<OPERATION-PROTOTYPE>
					<SHORT-NAME>WriteBlock</SHORT-NAME>
					<ARGUMENTS>
						<ARGUMENT-PROTOTYPE>
							<SHORT-NAME>DstPtr</SHORT-NAME>
							<TYPE-TREF DEST="ARRAY-TYPE">
								<xsl:value-of select="$dataPtrTypeName" />
							</TYPE-TREF>
							<DIRECTION>IN</DIRECTION>
						</ARGUMENT-PROTOTYPE>
					</ARGUMENTS>
					<POSSIBLE-ERROR-REFS>
						<POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">
							<xsl:value-of select="concat($interfaceReference, '/E_NOT_OK')" />
						</POSSIBLE-ERROR-REF>
					</POSSIBLE-ERROR-REFS>
				</OPERATION-PROTOTYPE>

				<xsl:if test="contains($interfaceName, 'Defs')">
					<OPERATION-PROTOTYPE>
						<SHORT-NAME>RestoreBlockDefaults</SHORT-NAME>
						<ARGUMENTS>
							<ARGUMENT-PROTOTYPE>
								<SHORT-NAME>DstPtr</SHORT-NAME>
								<TYPE-TREF DEST="ARRAY-TYPE">
									<xsl:value-of select="$dataPtrTypeName" />
								</TYPE-TREF>
								<DIRECTION>OUT</DIRECTION>
							</ARGUMENT-PROTOTYPE>
						</ARGUMENTS>
						<POSSIBLE-ERROR-REFS>
							<POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">
								<xsl:value-of select="concat($interfaceReference, '/E_NOT_OK')" />
							</POSSIBLE-ERROR-REF>
						</POSSIBLE-ERROR-REFS>
					</OPERATION-PROTOTYPE>
				</xsl:if>

				<!-- API Config Class 3 operations - EraseBlock, InvalidateNvBlock -->
				<xsl:if test="./ancestor::int:NvM/int:NvmCommon/int:NvmApiConfigClass = 'NvmApiConfigClass3'">
					<OPERATION-PROTOTYPE>
						<SHORT-NAME>EraseBlock</SHORT-NAME>
						<POSSIBLE-ERROR-REFS>
							<POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">
								<xsl:value-of select="concat($interfaceReference, '/E_NOT_OK')" />
							</POSSIBLE-ERROR-REF>
						</POSSIBLE-ERROR-REFS>
					</OPERATION-PROTOTYPE>
					<OPERATION-PROTOTYPE>
						<SHORT-NAME>InvalidateNvBlock</SHORT-NAME>
						<POSSIBLE-ERROR-REFS>
							<POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">
								<xsl:value-of select="concat($interfaceReference, '/E_NOT_OK')" />
							</POSSIBLE-ERROR-REF>
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

	<!--	
	==================================================================================================================    
		NVM TYPES
	==================================================================================================================
	-->
	<xsl:template match="int:NvM" mode="NVM_BASIC_TYPES">
		<AR-PACKAGE>
			<SHORT-NAME>
				<xsl:value-of select="$DataTypesPackageName" />
			</SHORT-NAME>
			<ELEMENTS>
				<BOOLEAN-TYPE>
					<SHORT-NAME>Boolean</SHORT-NAME>
				</BOOLEAN-TYPE>
				<INTEGER-TYPE>
					<SHORT-NAME>UInt8</SHORT-NAME>
					<LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
					<UPPER-LIMIT INTERVAL-TYPE="CLOSED">255</UPPER-LIMIT>
				</INTEGER-TYPE>
				<INTEGER-TYPE>
					<SHORT-NAME>
						<xsl:value-of select="$BlockIdType_Name" />
					</SHORT-NAME>
					<DESC>
						<L-2 L="EN">
							It is the type to be used in the "Port Defined Arguments". According to the NVM API it must result in an uint16 data type;
							thus the upper limit does not correspond to the number of configured blocks. Therefore the this type is common to all NVM SWC Descriptions.
							The upper limit is the theoretical maximum number of NVRAM blocks, if NVM_DATASET_SELECTION_BITS equals to 1.
							(It cannot be 0 since block Id 1 is fixed to be a REDUNDANT NVRAM Block - it consists of two NV blocks)
						</L-2>
					</DESC>
					
					<xsl:call-template name="DV_SDG_BSW_Module"/>																	
					
					<LOWER-LIMIT INTERVAL-TYPE="CLOSED">1</LOWER-LIMIT>
					<UPPER-LIMIT INTERVAL-TYPE="CLOSED">
						<xsl:value-of select="32767"/>
					</UPPER-LIMIT>
				</INTEGER-TYPE>
				<INTEGER-TYPE>
					<SHORT-NAME>
						<xsl:value-of select="$RequestResultType_Name" />
					</SHORT-NAME>
					
					<xsl:call-template name="DV_SDG_BSW_Module"/>																	
					
					<SW-DATA-DEF-PROPS>
						<COMPU-METHOD-REF DEST="COMPU-METHOD">
							<xsl:value-of select="concat('/', $DataTypesPackageName, '/', $RequestResultType_Name, '_COMPU')" />
						</COMPU-METHOD-REF>
					</SW-DATA-DEF-PROPS>
					<LOWER-LIMIT INTERVAL-TYPE="CLOSED">0</LOWER-LIMIT>
					<UPPER-LIMIT INTERVAL-TYPE="CLOSED">5</UPPER-LIMIT>
				</INTEGER-TYPE>
				<COMPU-METHOD>
					<SHORT-NAME>
						<xsl:value-of select="concat($RequestResultType_Name, '_COMPU')" />
					</SHORT-NAME>		
					<COMPU-INTERNAL-TO-PHYS>
						<COMPU-SCALES>
							<COMPU-SCALE>
								<LOWER-LIMIT>0</LOWER-LIMIT>
								<UPPER-LIMIT>0</UPPER-LIMIT>
								<COMPU-CONST>
									<VT>NVM_REQ_OK</VT>
								</COMPU-CONST>
							</COMPU-SCALE>
							<COMPU-SCALE>
								<LOWER-LIMIT>1</LOWER-LIMIT>
								<UPPER-LIMIT>1</UPPER-LIMIT>
								<COMPU-CONST>
									<VT>NVM_REQ_NOT_OK</VT>
								</COMPU-CONST>
							</COMPU-SCALE>
							<COMPU-SCALE>
								<LOWER-LIMIT>2</LOWER-LIMIT>
								<UPPER-LIMIT>2</UPPER-LIMIT>
								<COMPU-CONST>
									<VT>NVM_REQ_PENDING</VT>
								</COMPU-CONST>
							</COMPU-SCALE>
							<COMPU-SCALE>
								<LOWER-LIMIT>3</LOWER-LIMIT>
								<UPPER-LIMIT>3</UPPER-LIMIT>
								<COMPU-CONST>
									<VT>NVM_REQ_INTEGRITY_FAILED</VT>
								</COMPU-CONST>
							</COMPU-SCALE>
							<COMPU-SCALE>
								<LOWER-LIMIT>4</LOWER-LIMIT>
								<UPPER-LIMIT>4</UPPER-LIMIT>
								<COMPU-CONST>
									<VT>NVM_REQ_BLOCK_SKIPPED</VT>
								</COMPU-CONST>
							</COMPU-SCALE>
							<COMPU-SCALE>
								<LOWER-LIMIT>5</LOWER-LIMIT>
								<UPPER-LIMIT>5</UPPER-LIMIT>
								<COMPU-CONST>
									<VT>NVM_REQ_NV_INVALIDATED</VT>
								</COMPU-CONST>
							</COMPU-SCALE>
						</COMPU-SCALES>
					</COMPU-INTERNAL-TO-PHYS>
				</COMPU-METHOD>

				<xsl:apply-templates select="." mode="NvM_ServiceIdType" />

				<xsl:if test="(int:NvmCommon/int:NvmApiConfigClass != 'NvmApiConfigClass1')">
					<ARRAY-TYPE>
						<SHORT-NAME>
							<xsl:value-of select="$DestPtrType_Prefix"/>
						</SHORT-NAME>
						<DESC>
							<L-2 L="EN">
								<xsl:text>DataPtr Type to be used by WriteBlock, ReadBlock and RestoreBlockDefaults operations. </xsl:text>
								<xsl:text>	This type is used for all NVRAM blocks</xsl:text>
							</L-2>
						</DESC>
						
						<xsl:call-template name="DV_SDG_BSW_Module"/>																	
											
						<ELEMENT>
							<SHORT-NAME>
								<xsl:value-of select="concat($DestPtrType_Prefix,  '_BaseType')"/>
							</SHORT-NAME>
							<TYPE-TREF DEST="INTEGER-TYPE">
								<xsl:value-of select="concat('/', $DataTypesPackageName, '/UInt8')" />
							</TYPE-TREF>
							<MAX-NUMBER-OF-ELEMENTS>
								65535
							</MAX-NUMBER-OF-ELEMENTS>
						</ELEMENT>
					</ARRAY-TYPE>
				</xsl:if>
			</ELEMENTS>
		</AR-PACKAGE>
	</xsl:template>

	<xsl:template match="int:NvM" mode="NvM_ServiceIdType">
		<!-- Is there a block that has "UseServicePorts" and "Callback"? -->
		<xsl:if test="count(int:NvmBlockDescriptor[(int:NvmUseServicePorts = 'true') and (int:NvmUseJobendCallback = 'true')]) &gt; 0">
			<INTEGER-TYPE>
				<SHORT-NAME>
					<xsl:value-of select="$ServiceIdType_Name" />
				</SHORT-NAME>
				
				<xsl:call-template name="DV_SDG_BSW_Module"/>																	
				
				<SW-DATA-DEF-PROPS>
					<COMPU-METHOD-REF DEST="COMPU-METHOD">
						<xsl:value-of select="concat('/', $DataTypesPackageName, '/', $ServiceIdType_Name, '_COMPU')" />
					</COMPU-METHOD-REF>
				</SW-DATA-DEF-PROPS>
				<LOWER-LIMIT INTERVAL-TYPE="CLOSED">6</LOWER-LIMIT>
				<UPPER-LIMIT INTERVAL-TYPE="CLOSED">12</UPPER-LIMIT>
			</INTEGER-TYPE>
			<COMPU-METHOD>
				<SHORT-NAME>
					<xsl:value-of select="concat($ServiceIdType_Name, '_COMPU')" />
				</SHORT-NAME>
				<COMPU-INTERNAL-TO-PHYS>
					<COMPU-SCALES>
						<COMPU-SCALE>
							<LOWER-LIMIT>6</LOWER-LIMIT>
							<UPPER-LIMIT>6</UPPER-LIMIT>
							<COMPU-CONST>
								<VT>NVM_READ_BLOCK</VT>
							</COMPU-CONST>
						</COMPU-SCALE>
						<COMPU-SCALE>
							<LOWER-LIMIT>7</LOWER-LIMIT>
							<UPPER-LIMIT>7</UPPER-LIMIT>
							<COMPU-CONST>
								<VT>NVM_WRITE_BLOCK</VT>
							</COMPU-CONST>
						</COMPU-SCALE>
						<COMPU-SCALE>
							<LOWER-LIMIT>8</LOWER-LIMIT>
							<UPPER-LIMIT>8</UPPER-LIMIT>
							<COMPU-CONST>
								<VT>NVM_RESTORE_BLOCK_DEFAULTS</VT>
							</COMPU-CONST>
						</COMPU-SCALE>
						<COMPU-SCALE>
							<LOWER-LIMIT>9</LOWER-LIMIT>
							<UPPER-LIMIT>9</UPPER-LIMIT>
							<COMPU-CONST>
								<VT>NVM_ERASE_BLOCK</VT>
							</COMPU-CONST>
						</COMPU-SCALE>
						<COMPU-SCALE>
							<LOWER-LIMIT>11</LOWER-LIMIT>
							<UPPER-LIMIT>11</UPPER-LIMIT>
							<COMPU-CONST>
								<VT>NVM_INVALIDATE_NV_BLOCK</VT>
							</COMPU-CONST>
						</COMPU-SCALE>
						<COMPU-SCALE>
							<LOWER-LIMIT>12</LOWER-LIMIT>
							<UPPER-LIMIT>12</UPPER-LIMIT>
							<COMPU-CONST>
								<VT>NVM_READ_ALL</VT>
							</COMPU-CONST>
						</COMPU-SCALE>
					</COMPU-SCALES>
				</COMPU-INTERNAL-TO-PHYS>
			</COMPU-METHOD>
		</xsl:if>
	</xsl:template>

	<xsl:template match="int:*|@int:*">
		<xsl:copy>
			<xsl:apply-templates select="*|@*|text()" />
		</xsl:copy>
	</xsl:template>

	<xsl:template match="int:*/text()">
		<xsl:copy/>
	</xsl:template>

	<!--
	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	+					Perform intermediate transformation -> transform SHORT-NAMEs to elements                         +
	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	-->

	<xsl:template match="*[starts-with(namespace-uri(), 'http://autosar.org') and (local-name()='AUTOSAR')]" mode="create-intermediate">
		<xsl:element name="int:module-configs">
			<xsl:apply-templates select="*[local-name()='TOP-LEVEL-PACKAGES']" mode="create-intermediate"/>
		</xsl:element>
	</xsl:template>

	<xsl:template match="*[contains('TOP-LEVEL-PACKAGES SUB-PACKAGES ELEMENTS CONTAINERS PARAMETER-VALUES', local-name())]" mode="create-intermediate">
		<xsl:apply-templates select="*" mode="create-intermediate" />
	</xsl:template>

	<xsl:template match="*[local-name()='AR-PACKAGE']" mode="create-intermediate">
		<xsl:element name="int:package">
			<xsl:apply-templates select="*" mode="create-intermediate"/>		
		</xsl:element>
	</xsl:template>

	<xsl:template match="*[local-name()='ECUC-CONFIGURATION']" mode="create-intermediate">
		<xsl:element name="int:ecuc-config">
			<xsl:apply-templates select="*" mode="create-intermediate"/>
		</xsl:element>
	</xsl:template>

	<xsl:template match="*[*[local-name()='DEFINITION-REF']]" mode="create-intermediate">
		<xsl:variable name="elem-name">
			<xsl:call-template name="resolve-definition-path">
				<xsl:with-param name="path" select="./*[local-name()='DEFINITION-REF']/text()" />
			</xsl:call-template>
		</xsl:variable>
		<xsl:element name="int:{$elem-name}">
			<xsl:attribute name="type">
				<xsl:value-of select="local-name()"/>
			</xsl:attribute>
			<xsl:apply-templates select="*[local-name()='SHORT-NAME']|*[local-name()='DEFINITION-REF']|*" mode="create-intermediate"/>
		</xsl:element>
	</xsl:template>

	<xsl:template name="resolve-definition-path">
		<xsl:param name="path" select="INVALID"/>

		<xsl:variable name="sub-path" select="substring-after($path, '/')" />
		<xsl:choose>
			<xsl:when test="$sub-path = ''">
				<xsl:value-of select="$path" />
			</xsl:when>
			<xsl:otherwise>
				<xsl:call-template name="resolve-definition-path">
					<xsl:with-param name="path" select="$sub-path" />
				</xsl:call-template>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="*[(local-name()='VALUE') and (local-name(ancestor::*[2])='PARAMETER-VALUES')]" mode="create-intermediate">
		<xsl:value-of select="text()" />
	</xsl:template>
	
	<xsl:template match="*[local-name()='DEFINITION-REF']" mode="create-intermediate">
		<xsl:attribute name="definition-ref">
			<xsl:value-of select="."/>
		</xsl:attribute>
	</xsl:template>

	<xsl:template match="*[local-name()='SHORT-NAME']" mode="create-intermediate">
		<xsl:attribute name="name">
			<xsl:value-of select="text()"/>
		</xsl:attribute>
	</xsl:template>
	
	<xsl:template match="*|@*|comment()|text()|processing-instruction()" mode="create-intermediate" />
</xsl:stylesheet>

