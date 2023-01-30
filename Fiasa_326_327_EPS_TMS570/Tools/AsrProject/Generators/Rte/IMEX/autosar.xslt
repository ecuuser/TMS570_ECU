<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:msxsl="urn:schemas-microsoft-com:xslt">
	<xsl:output method="xml" version="1.0" encoding="UTF-8" indent="yes"/>

	<xsl:template match="/">
		<xsl:copy>
			<xsl:apply-templates/>
		</xsl:copy>
	</xsl:template>
  
	<xsl:template match="*[(local-name()='ELEMENTS' and local-name(..)='AR-PACKAGE') or local-name()='TOP-LEVEL-PACKAGES' or local-name()='SUB-PACKAGES'
	  or (local-name()='CONNECTORS' and local-name(..)='ECU-INSTANCE') or local-name()='COMPONENTS' or local-name()='PORTS'
	  or local-name()='CALPRM-ELEMENTS' or local-name()='DATA-ELEMENTS' or local-name()='POSSIBLE-ERRORS' or local-name()='OPERATIONS'
	  or local-name()='CALPRM-ACCESSS' or local-name()='DATA-READ-ACCESSS' or local-name()='DATA-RECEIVE-POINTS' or local-name()='DATA-SEND-POINTS'
	  or local-name()='DATA-WRITE-ACCESSS' or local-name()='INSIDE-EXCLUSIVE-AREAS' or local-name()='SERVER-CALL-POINTS' or local-name()='USES-EXCLUSIVE-AREAS'
	  or local-name()='WAIT-POINTS' or local-name()='EVENTS' or local-name()='EXCLUSIVE-AREAS' or local-name()='INTER-RUNNABLE-VARIABLES'
	  or local-name()='NVRAM-MAPPINGS' or local-name()='PER-INSTANCE-CALPRMS' or local-name()='PER-INSTANCE-MEMORY-SIZES' or local-name()='PER-INSTANCE-MEMORYS'
	  or local-name()='RUNNABLES' or local-name()='SHARED-CALPRMS' or local-name()='INCLUDED-SIGNALS'
	  or local-name()='ECU-COMM-PORT-INSTANCES' or local-name()='COMM-CONTROLLERS' or local-name()='SIGNAL-TO-PDU-MAPPINGS' or local-name()='PDU-TO-FRAME-MAPPINGS'
	  or local-name()='END-TO-END-PROTECTIONS' or local-name()='I-SIGNAL-TO-I-PDU-MAPPINGS']">
		<xsl:copy>
			<xsl:call-template name="SortByShortName"/>
		</xsl:copy>
	</xsl:template>

<!-- basic sort templates -->
    <xsl:template name="SortByShortName">
		<xsl:apply-templates select="@*"/>
		<xsl:apply-templates select="node()">
			<xsl:sort select="name()" order="ascending"/>
			<xsl:sort select="*[local-name()='SHORT-NAME']" order="ascending"/>
		</xsl:apply-templates>
	</xsl:template>
	
	<xsl:template name="SortByGID">
		<xsl:apply-templates select="@*"/>
		<xsl:apply-templates select="*[local-name()='SDG-CAPTION']"/>
		<xsl:apply-templates select="*[local-name()='SDG-CAPTION-REF']"/>
		<xsl:apply-templates select="node()[local-name()!='SDG-CAPTION' and local-name()!='SDG-CAPTION-REF']">
			<xsl:sort select="name()" order="ascending"/>
			<xsl:sort select="@GID" order="ascending"/>
		</xsl:apply-templates>
	</xsl:template>
	
	<xsl:template match="*|@*|text()">
		<xsl:copy>
			<xsl:apply-templates select="*|@*|text()">
			 </xsl:apply-templates>
		</xsl:copy>
	</xsl:template>
	
<!-- basic sort key templates -->
	<xsl:template name="add-sort-key">
		<xsl:param name="IREF_NAME"/>
		<xsl:param name="TARGET_REF_NAME"/>
		<xsl:copy>
			<xsl:attribute name="DV_SORT_KEY">
				<xsl:variable name="SortString">
					<xsl:for-each select="*[local-name()=$IREF_NAME]/*[local-name()=$TARGET_REF_NAME]">
						<xsl:copy-of select="text()"></xsl:copy-of><xsl:text>/1/</xsl:text>
					</xsl:for-each>
				</xsl:variable>
				<xsl:value-of select="$SortString"/>
			</xsl:attribute>
			<xsl:apply-templates select="*|@*|text()">
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>
	
	<xsl:template name="remove-sort-key">
		<xsl:copy>
			<xsl:apply-templates select="*|@*[name() != 'DV_SORT_KEY']|text()"/>
<!--			<xsl:comment><xsl:text>@DV_SORT_KEY=</xsl:text><xsl:value-of select="@DV_SORT_KEY"></xsl:value-of></xsl:comment> -->
		</xsl:copy>
	</xsl:template>

<!-- specialized sort key templates -->
<!-- CONNECTIONS -->
	<xsl:template match="*[local-name()='SERVICE-CONNECTOR-PROTOTYPE']" mode="add-sort-key">
		<xsl:call-template name="add-sort-key">
			<xsl:with-param name="IREF_NAME">APPLICATION-PORT-IREF</xsl:with-param>
			<xsl:with-param name="TARGET_REF_NAME">COMPONENT-PROTOTYPE-REF</xsl:with-param>
		</xsl:call-template>
	</xsl:template>

	<xsl:template match="*[local-name()='SERVICE-CONNECTOR-PROTOTYPE']" mode="remove-sort-key">
		<xsl:call-template name="remove-sort-key"/>
	</xsl:template>	

<!-- DATA-MAPPING -->
	<xsl:template match="*[local-name()='SENDER-RECEIVER-TO-SIGNAL-MAPPING' or local-name()='SENDER-RECEIVER-TO-SIGNAL-GROUP-MAPPING']" mode="add-sort-key">
		<xsl:call-template name="add-sort-key">
			<xsl:with-param name="IREF_NAME">DATA-ELEMENT-IREF</xsl:with-param>
			<xsl:with-param name="TARGET_REF_NAME">COMPONENT-PROTOTYPE-REF</xsl:with-param>
		</xsl:call-template>
	</xsl:template>

	<xsl:template match="*[local-name()='SENDER-RECEIVER-TO-SIGNAL-MAPPING' or local-name()='SENDER-RECEIVER-TO-SIGNAL-GROUP-MAPPING']" mode="remove-sort-key">
		<xsl:call-template name="remove-sort-key"/>
	</xsl:template>
	
<!-- IMPL/ECU-MAPPING -->
	<xsl:template match="*[local-name()='SWC-TO-IMPL-MAPPING' or local-name()='SWC-TO-ECU-MAPPING'
	 or local-name()='SW-COMP-TO-IMPL-MAPPING' or local-name()='SW-COMP-TO-ECU-MAPPING']" mode="add-sort-key">
		<xsl:copy>
			<xsl:attribute name="DV_SORT_KEY">
				<xsl:variable name="SortString">
					<xsl:for-each select="*[local-name()='COMPONENT-IREFS']/*[local-name()='COMPONENT-IREF'][1]/*[local-name()='COMPONENT-PROTOTYPE-REF']">
						<xsl:copy-of select="text()"></xsl:copy-of><xsl:text>/1/</xsl:text>
					</xsl:for-each>
				</xsl:variable>
				<xsl:value-of select="$SortString"/>
			</xsl:attribute>
			<xsl:apply-templates select="*|@*|text()">
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>


	<xsl:template match="*[local-name()='SWC-TO-IMPL-MAPPING' or local-name()='SWC-TO-ECU-MAPPING'
	 or local-name()='SW-COMP-TO-IMPL-MAPPING' or local-name()='SW-COMP-TO-ECU-MAPPING']" mode="remove-sort-key">
		<xsl:call-template name="remove-sort-key"/>
	</xsl:template>
	
<!-- SET templates -->


<!-- COM-SPECs -->
	<xsl:template match="*[local-name()='REQUIRED-COM-SPECS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates select="*[local-name()='CLIENT-COM-SPEC']">
				<xsl:sort select="*[local-name()='OPERATION-REF']" order="ascending"/> <!-- AR3.0 -->
				<xsl:sort select="*[local-name()='OPERATION-IREF']/*[local-name()='OPERATION-PROTOTYPE-REF']"/> <!-- AR2.1 -->
			</xsl:apply-templates>
			<xsl:apply-templates select="*[local-name()='QUEUED-RECEIVER-COM-SPEC']">
				<xsl:sort select="*[local-name()='DATA-ELEMENT-REF']" order="ascending"/> <!-- AR3.0 -->
				<xsl:sort select="*[local-name()='DATA-ELEMENT-IREF']/*[local-name()='DATA-ELEMENT-PROTOTYPE-REF']"/> <!-- AR2.1 -->
			</xsl:apply-templates>
			<xsl:apply-templates select="*[local-name()='UNQUEUED-RECEIVER-COM-SPEC']">
				<xsl:sort select="*[local-name()='DATA-ELEMENT-REF']" order="ascending"/><!-- AR3.0 -->
				<xsl:sort select="*[local-name()='DATA-ELEMENT-IREF']/*[local-name()='DATA-ELEMENT-PROTOTYPE-REF']"/> <!-- AR2.1 -->
			</xsl:apply-templates>
			<xsl:apply-templates select="*[local-name()='PARAMETER-REQUIRE-COM-SPEC']">
				<xsl:sort select="*[local-name()='PARAMETER-REF']" order="ascending"/><!-- AR3.0 -->
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>

	<xsl:template match="*[local-name()='PROVIDED-COM-SPECS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates select="*[local-name()='MODE-SWITCH-COM-SPEC']">
				<xsl:sort select="*[local-name()='MODE-GROUP-REF']" order="ascending"/>
			</xsl:apply-templates>
			<xsl:apply-templates select="*[local-name()='QUEUED-SENDER-COM-SPEC']">
				<xsl:sort select="*[local-name()='DATA-ELEMENT-REF']" order="ascending"/> <!-- AR3.0 -->
				<xsl:sort select="*[local-name()='DATA-ELEMENT-IREF']/*[local-name()='DATA-ELEMENT-PROTOTYPE-REF']"/> <!-- AR2.1 -->
			</xsl:apply-templates>
			<xsl:apply-templates select="*[local-name()='SERVER-COM-SPEC']">
				<xsl:sort select="*[local-name()='OPERATION-REF']" order="ascending"/> <!-- AR3.0 -->
				<xsl:sort select="*[local-name()='OPERATION-IREF']/*[local-name()='OPERATION-PROTOTYPE-REF']"/> <!-- AR2.1 -->
			</xsl:apply-templates>
			<xsl:apply-templates select="*[local-name()='UNQUEUED-SENDER-COM-SPEC']">
				<xsl:sort select="*[local-name()='DATA-ELEMENT-REF']" order="ascending"/> <!-- AR3.0 -->
				<xsl:sort select="*[local-name()='DATA-ELEMENT-IREF']/*[local-name()='DATA-ELEMENT-PROTOTYPE-REF']"/> <!-- AR2.1 -->
			</xsl:apply-templates>
			<xsl:apply-templates select="*[local-name()='PARAMETER-PROVIDE-COM-SPEC']">
				<xsl:sort select="*[local-name()='PARAMETER-REF']" order="ascending"/><!-- AR3.0 -->
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>

<!-- EVENTS -->
	<xsl:template match="*[local-name()='EVENTS']">
    <xsl:copy>
		<xsl:apply-templates select="@*"/>
		<xsl:apply-templates select="node()">
			<xsl:sort select="child::*[local-name()='START-ON-EVENT-REF']" order="ascending"/>
			<xsl:sort select="descendant::*[contains(local-name(), 'PORT-PROTOTYPE-REF')]" order="ascending"/>
			<xsl:sort select="descendant::*[local-name()='DATA-ELEMENT-PROTOTYPE-REF']" order="ascending"/>
			<xsl:sort select="descendant::*[local-name()='OPERATION-PROTOTYPE-REF']" order="ascending"/>
			<xsl:sort select="descendant::*[local-name()='EVENT-SOURCE-REF']" order="ascending"/>
		</xsl:apply-templates>
    </xsl:copy>
  </xsl:template>

<!-- PORT-API-OPTIONS -->
	<xsl:template match="*[local-name()='PORT-API-OPTIONS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates select="node()">
				<xsl:sort select="name()"/>
				<xsl:sort select="*[local-name()='PORT-REF']"/>
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>

<!-- CONNECTIONS -->
	<xsl:template match="*[local-name()='CONNECTORS' and local-name(..)!='ECU-INSTANCE']">
		<xsl:copy>
		
			<xsl:apply-templates select="@*"/>

			<!-- ASSEMBLY-CONNECTOR-PROTOTYPE -->
			<xsl:apply-templates select="*[local-name()='ASSEMBLY-CONNECTOR-PROTOTYPE']">
					<xsl:sort select="*[local-name()='PROVIDER-IREF']/*[local-name()='COMPONENT-PROTOTYPE-REF']" order="ascending"/>
					<xsl:sort select="*[local-name()='PROVIDER-IREF']/*[local-name()='P-PORT-PROTOTYPE-REF']" order="ascending"/>
					<xsl:sort select="*[local-name()='REQUESTER-IREF']/*[local-name()='COMPONENT-PROTOTYPE-REF']" order="ascending"/>
					<xsl:sort select="*[local-name()='REQUESTER-IREF']/*[local-name()='R-PORT-PROTOTYPE-REF']" order="ascending"/>
			</xsl:apply-templates>
	
			<!-- DELEGATION-CONNECTOR-PROTOTYPE -->
			<xsl:apply-templates select="*[local-name()='DELEGATION-CONNECTOR-PROTOTYPE']">
				<xsl:sort select="*[local-name()='INNER-PORT-IREF']/*[local-name()='COMPONENT-PROTOTYPE-REF']" order="ascending"/>
				<xsl:sort select="*[local-name()='INNER-PORT-IREF']/*[local-name()='PORT-PROTOTYPE-REF']" order="ascending"/>
				<xsl:sort select="*[local-name()='OUTER-PORT-REF']" order="ascending"/>			
			</xsl:apply-templates>
		  
			<!-- SERVICE-CONNECTOR-PROTOTYPE -->
			<xsl:variable name="TEMP_SERVICE_CONNECTORS">
					<xsl:apply-templates select="*[local-name()='SERVICE-CONNECTOR-PROTOTYPE']" mode="add-sort-key">
					</xsl:apply-templates>
			</xsl:variable>
			<xsl:apply-templates select="msxsl:node-set($TEMP_SERVICE_CONNECTORS)/node()" mode="remove-sort-key">
				<xsl:sort select="*[local-name()='APPLICATION-PORT-IREF']/*[local-name()='SOFTWARE-COMPOSITION-REF']"/>
				<xsl:sort select="@DV_SORT_KEY"/>
				<xsl:sort select="*[local-name()='APPLICATION-PORT-IREF']/*[local-name()='PORT-PROTOTYPE-REF']"/>
				<xsl:sort select="*[local-name()='SERVICE-PORT-IREF']/*[local-name()='SERVICE-COMPONENT-PROTOTYPE-REF']"/>
				<xsl:sort select="*[local-name()='SERVICE-PORT-IREF']/*[local-name()='PORT-PROTOTYPE-REF']"/>
			</xsl:apply-templates>
		
		</xsl:copy>
	</xsl:template>

<!-- DATA-MAPPING -->
	<xsl:template match="*[local-name()='DATA-MAPPINGS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>

			<!-- SENDER-RECEIVER-TO-SIGNAL-MAPPING -->
			<xsl:variable name="TEMP_SENDER_RECEIVER_TO_SIGNAL_MAPPING">
					<xsl:apply-templates select="*[local-name()='SENDER-RECEIVER-TO-SIGNAL-MAPPING']" mode="add-sort-key">
					</xsl:apply-templates>
			</xsl:variable>
			<xsl:apply-templates select="msxsl:node-set($TEMP_SENDER_RECEIVER_TO_SIGNAL_MAPPING)/node()" mode="remove-sort-key">
				<xsl:sort select="*[local-name()='DATA-ELEMENT-IREF']/*[local-name()='SOFTWARE-COMPOSITION-REF']"/>
				<xsl:sort select="@DV_SORT_KEY"/>
				<xsl:sort select="*[local-name()='DATA-ELEMENT-IREF']/*[local-name()='PORT-PROTOTYPE-REF']"/>
				<xsl:sort select="*[local-name()='DATA-ELEMENT-IREF']/*[local-name()='DATA-ELEMENT-REF']"/>
				<xsl:sort select="*[local-name()='SIGNAL-REF']"/>
			</xsl:apply-templates>

			<!-- SENDER-RECEIVER-TO-SIGNAL-GROUP-MAPPING -->
			<xsl:variable name="TEMP_SENDER_RECEIVER_TO_SIGNAL_GROUP_MAPPING">
					<xsl:apply-templates select="*[local-name()='SENDER-RECEIVER-TO-SIGNAL-GROUP-MAPPING']" mode="add-sort-key">
					</xsl:apply-templates>
			</xsl:variable>
			
			<xsl:apply-templates select="msxsl:node-set($TEMP_SENDER_RECEIVER_TO_SIGNAL_GROUP_MAPPING)/node()" mode="remove-sort-key">
				<xsl:sort select="*[local-name()='DATA-ELEMENT-IREF']/*[local-name()='SOFTWARE-COMPOSITION-REF']"/>
				<xsl:sort select="@DV_SORT_KEY"/>
				<xsl:sort select="*[local-name()='DATA-ELEMENT-IREF']/*[local-name()='PORT-PROTOTYPE-REF']"/>
				<xsl:sort select="*[local-name()='DATA-ELEMENT-IREF']/*[local-name()='DATA-ELEMENT-REF']"/>
				<xsl:sort select="*[local-name()='SIGNAL-GROUP-REF']"/>
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>

	<xsl:template match="*[local-name()='RECORD-ELEMENT-MAPPINGS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
		
			<xsl:apply-templates select="node()">
				<xsl:sort select="*[local-name()='RECORD-ELEMENT-REF']"/>
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>

	<xsl:template match="*[local-name()='ARRAY-ELEMENT-MAPPINGS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
		
			<xsl:apply-templates select="node()">
				<xsl:sort select="*[local-name()='INDEXED-ARRAY-ELEMENT']/*[local-name()='INDEX']"/>
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>

	<xsl:template match="*[local-name()='PDU-TO-FRAME-MAPPINGS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
		
			<xsl:apply-templates select="node()">
				<xsl:sort select="*[local-name()='PDU-REF']"/>
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>
	
<!-- IMPL-MAPPING -->
	<xsl:template match="*[local-name()='SW-IMPL-MAPPINGS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			
			<!-- AR 3.0 -->
			<xsl:variable name="TEMP_SWC_TO_IMPL_MAPPING">
			<xsl:choose>
				<xsl:when test="*[local-name()='SWC-TO-IMPL-MAPPING']"> <!-- AR3.0 -->
					<xsl:apply-templates select="*[local-name()='SWC-TO-IMPL-MAPPING']" mode="add-sort-key">
					</xsl:apply-templates>				
				</xsl:when>
				<xsl:otherwise> <!-- AR2.1 -->
					<xsl:apply-templates select="*[local-name()='SW-COMP-TO-IMPL-MAPPING']" mode="add-sort-key">
					</xsl:apply-templates>								
				</xsl:otherwise>
			</xsl:choose>
					
			</xsl:variable>
			<xsl:apply-templates select="msxsl:node-set($TEMP_SWC_TO_IMPL_MAPPING)/node()" mode="remove-sort-key">
				<xsl:sort select="*[local-name()='COMPONENT-IREFS']/*[local-name()='COMPONENT-IREF']/*[local-name()='SOFTWARE-COMPOSITION-REF']"/>
				<xsl:sort select="@DV_SORT_KEY"/>
				<xsl:sort select="*[local-name()='COMPONENT-IREFS']/*[local-name()='COMPONENT-IREF']/*[local-name()='TARGET-COMPONENT-PROTOTYPE-REF']"/>
				<xsl:sort select="*[local-name()='COMPONENT-IMPLEMENTATION-REF']"/>
			</xsl:apply-templates>
			
		</xsl:copy>
	</xsl:template>

<!-- SW-MAPPINGS -->
	<xsl:template match="*[local-name()='SW-MAPPINGS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			
			<!-- AR 3.0 -->
			<xsl:variable name="TEMP_SWC_TO_ECU_MAPPING">
					<xsl:apply-templates select="*[local-name()='SWC-TO-ECU-MAPPING']" mode="add-sort-key">
					</xsl:apply-templates>
			</xsl:variable>
			<xsl:apply-templates select="msxsl:node-set($TEMP_SWC_TO_ECU_MAPPING)/node()" mode="remove-sort-key">
				<xsl:sort select="*[local-name()='COMPONENT-IREFS']/*[local-name()='COMPONENT-IREF']/*[local-name()='SOFTWARE-COMPOSITION-REF']"/>
				<xsl:sort select="@DV_SORT_KEY"/>
				<xsl:sort select="*[local-name()='COMPONENT-IREFS']/*[local-name()='COMPONENT-IREF']/*[local-name()='TARGET-COMPONENT-PROTOTYPE-REF']"/>
				<xsl:sort select="*[local-name()='ECU-INSTANCE-REF']"/>
			</xsl:apply-templates>

			<!-- AR 2.1 -->
			<xsl:variable name="TEMP_SW_COMP_TO_ECU_MAPPING">
					<xsl:apply-templates select="*[local-name()='SW-COMP-TO-ECU-MAPPING']" mode="add-sort-key">
					</xsl:apply-templates>
			</xsl:variable>
			<xsl:apply-templates select="msxsl:node-set($TEMP_SW_COMP_TO_ECU_MAPPING)/node()" mode="remove-sort-key">
				<xsl:sort select="*[local-name()='COMPONENT-IREFS']/*[local-name()='COMPONENT-IREF']/*[local-name()='SOFTWARE-COMPOSITION-REF']"/>
				<xsl:sort select="@DV_SORT_KEY"/>
				<xsl:sort select="*[local-name()='COMPONENT-IREFS']/*[local-name()='COMPONENT-IREF']/*[local-name()='TARGET-COMPONENT-PROTOTYPE-REF']"/>
				<xsl:sort select="*[local-name()='ECU-INSTANCE-IREF']/*[local-name()='SYSTEM-TOPOLOGY-INSTANCE-REF']"/>
				<xsl:sort select="*[local-name()='ECU-INSTANCE-IREF']/*[local-name()='ECU-INSTANCE-REF']"/>
			</xsl:apply-templates>
			
		</xsl:copy>
	</xsl:template>
  
<!-- FRAME-RECEIVERs AR2.1 -->
	<xsl:template match="*[local-name()='RECEIVER-IREFS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates select="node()">
				<xsl:sort select="*[local-name()='ECU-COMMUNICATION-PORT-INSTANCE-REF']" order="ascending"/>
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>

<!-- FRAME-TRIGGERINGs -->
	<xsl:template match="*[local-name()='FRAME-TRIGGERINGSS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates select="node()">
				<xsl:sort select="*[local-name()='FRAME-REF']" order="ascending"/>
				<xsl:sort select="*[local-name()='SHORT-NAME']" order="ascending"/>
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>

<!-- PDU-TRIGGERINGs -->
	<xsl:template match="*[local-name()='I-PDU-TRIGGERINGS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates select="node()">
				<xsl:sort select="*[local-name()='I-PDU-REF']" order="ascending"/>
				<xsl:sort select="*[local-name()='SHORT-NAME']" order="ascending"/>
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>
	
	<!-- SIGNAL-TRIGGERINGs -->
	<xsl:template match="*[local-name()='I-SIGNAL-TRIGGERINGS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates select="node()">
				<xsl:sort select="*[local-name()='SIGNAL-REF']" order="ascending"/>
				<xsl:sort select="*[local-name()='SHORT-NAME']" order="ascending"/>
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>
	
	<xsl:template match="*[local-name()='TRANSMISSION-MODE-CONDITIONS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates select="node()">
				<xsl:sort select="name()" order="ascending"/>
				<xsl:sort select="descendant::*[local-name()='SIGNAL-IN-I-PDU-REF']" order="ascending"/>
				<xsl:sort select="descendant::*[local-name()='DATA-FILTER']/child::*[1]" order="ascending"/>
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>
  
	<xsl:template match="*[local-name()='ABSOLUTELY-SCHEDULED-TIMINGS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates select="node()">
				<xsl:sort select="descendant::*[local-name()='SLOT-ID']" order="ascending"/>
				<xsl:sort select="descendant::*[local-name()='BASE-CYCLE']" order="ascending"/>
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>
  
<!-- GATEWAY SIGNAL-MAPPINGS -->
	<xsl:template match="*[local-name()='SIGNAL-MAPPINGS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates select="node()">
				<xsl:sort select="*[local-name()='SOURCE-SIGNAL-REF']" order="ascending"/>
				<xsl:sort select="*[local-name()='TARGET-SIGNAL-REF']" order="ascending"/>
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>

<!-- DEPENDENT-ON-MODE-IREFS -->
	<xsl:template match="*[local-name()='DEPENDENT-ON-MODE-IREFS']">
	<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates select="node()">
				<xsl:sort select="*[local-name()='R-PORT-PROTOTYPE-REF']" order="ascending"/>
				<xsl:sort select="*[local-name()='MODE-DECLARATION-GROUP-PROTOTYPE-REF']" order="ascending"/>
				<xsl:sort select="*[local-name()='MODE-DECLARATION-REF']" order="ascending"/>
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>
	
<!-- SDGS/SDG -->
	<xsl:template match="*[local-name()='SDGS' or local-name()='SDG']">
		<xsl:copy>
			<xsl:call-template name="SortByGID"/>
		</xsl:copy>
	</xsl:template>

<!-- REFERENCEs -->
	<xsl:template match="*[local-name()='SYSTEM-SIGNAL-REFS' or local-name()='FRAME-PORT-REFS' or local-name()='I-PDU-PORT-REFS' or local-name()='I-SIGNAL-PORT-REFS'
	or local-name()='I-PDU-REFS' or local-name()='ASSOCIATED-I-PDU-GROUP-REFS' or local-name()='PDU-POOL-REFS' or local-name()='I-PDU-TRIGGERING-REFS' or local-name()='I-SIGNAL-TRIGGERING-REFS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates select="node()">
				<xsl:sort select="text()" order="ascending"/>
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>
  
	<xsl:template match="*[local-name()='FIBEX-ELEMENT-REFS']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates select="node()">
				<xsl:sort select="@DEST" order="ascending"/>
				<xsl:sort select="text()" order="ascending"/>
			</xsl:apply-templates>
		</xsl:copy>
	</xsl:template>
  

</xsl:stylesheet>