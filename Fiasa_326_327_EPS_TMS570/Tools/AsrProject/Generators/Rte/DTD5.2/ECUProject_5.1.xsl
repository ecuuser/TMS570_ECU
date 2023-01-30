<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD5.2\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <ECUProject>
            <xsl:apply-templates select="ECUProject" />
        </ECUProject>
    </xsl:template>
    
    <!-- ECUProject element rule -->
    <!-- Set DTD version to 5.2, No ItemConvert required -->
    <xsl:template match="ECUProject">
        <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version | @RO" />
        <xsl:attribute name="DTDVersion">5.2</xsl:attribute>
        <xsl:copy-of select="@GenOutputLevel | @BSWMDFileCom | @BSWMDFileNvM | @BSWMDFileOs | @ECUCFile | @ECUCFileLastUpdate | @AllowGenerationOfUnsavedData" />
        <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT | FileEntry | Task | TaskMap | NVMBlock | MemoryMap" />
        <xsl:apply-templates select="ECUSWComposition" />
        <xsl:apply-templates select="ECUCommunication" />
        <xsl:copy-of select="ExternalTool | Generator | GenAttrList | OsApplication" />
    </xsl:template>

    <!-- ECUSWComposition element rule: remove proxy objects -->
    <xsl:template match="ECUSWComposition">
        <ECUSWComposition>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | ComponentPrototype" />
            <xsl:apply-templates select="PortConnector" />
            <xsl:copy-of select="PortPrototype" />
            <xsl:apply-templates select="DataMapping" />
            <xsl:apply-templates select="ServicePortConnector" />
            <xsl:copy-of select="GenAttrList" />
        </ECUSWComposition>
    </xsl:template>

    <!-- DataMapping element rule-->
    <xsl:template match="DataMapping">
        <DataMapping>
            <xsl:copy-of select="@*"/>
            <xsl:copy-of select="ATTRLink"/>
            <xsl:apply-templates select="DataElement"/>
        </DataMapping>
    </xsl:template>

    <!-- DataElement element rule: rename SignalGroupRoot-->
    <xsl:template match="DataElement">
        <DataElement>
            <xsl:copy-of select="@GUID | @DataElementPrototypeLink | @PortPrototypeLink | @ArrayIndex | @RecordTypeElementLink | @ArrayTypeElementLink"/>
            <xsl:attribute name="DataMapComplexElementLink">SignalGroup</xsl:attribute>
            <xsl:copy-of select="@DataMapPrimitiveElementLink"/>
            <xsl:apply-templates select="ATTRLink" />
            <xsl:copy-of select="DataElementLink | GenAttrList"/>
        </DataElement>
    </xsl:template>

    <!-- PortConnector element rule: remove function net links -->
    <xsl:template match="PortConnector">
        <PortConnector>
            <xsl:copy-of select="@GUID | @ReceiverPortLink | @TransmitterPortLink | @ReceiveCompPrototypeLink | @ReceiveCompTypeLink | @TransmitCompPrototypeLink | @TransmitCompTypeLink"/>
            <xsl:copy-of select="DESC"/>
            <xsl:apply-templates select="ATTRLink"/>
            <xsl:copy-of select="GenAttrList | SenderReceiverConnectorComSpec | ClientServerConnectorComSpec"/>
        </PortConnector>
    </xsl:template>

    <!-- ServicePortConnector element rule: remove function net links -->
    <xsl:template match="ServicePortConnector">
        <ServicePortConnector>
            <xsl:copy-of select="@GUID | @ReceiverPortLink | @TransmitterPortLink | @ReceiveCompPrototypeLink | @TransmitCompPrototypeLink"/>
            <xsl:copy-of select="node()"/>
        </ServicePortConnector>
    </xsl:template>

    <!-- ECUCommunication element rule: PDU / signal group adaptation -->
    <xsl:template match="ECUCommunication">
        <ECUCommunication>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | Signal | SignalType" />
            <xsl:apply-templates select="SignalGroupRoot" />
            <xsl:apply-templates select="ECU" />
            <xsl:apply-templates select="CANBus" />
            <xsl:apply-templates select="LINBus" />
            <xsl:apply-templates select="FlexRayCluster" />
            <xsl:apply-templates select="FrTp" />
        </ECUCommunication>
    </xsl:template>

    <!-- SignalGroup element rule: remove layout, rename SignalGroupRoot -->
    <xsl:template match="SignalGroupRoot">
        <SignalGroup>
            <!-- Set DTD version to 5.2, No ItemConvert required -->
            <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version" />
            <xsl:attribute name="DTDVersion">5.2</xsl:attribute>
            <xsl:copy-of select="@RO | @IsServicePort | @BSWModule" />
            <xsl:copy-of select="NAME | LONGNAME | DESC" />
            <xsl:apply-templates select="SignalLayout" />
            <xsl:copy-of select="PDUTiming" />
        </SignalGroup>
    </xsl:template>

    <!-- SignalLayout element rule -->
    <xsl:template match="SignalLayout">
		<xsl:if test="./ATTRLink/@LinkGUID">
			<SignalLink>
				<xsl:attribute name="LinkGUID">
					<xsl:value-of select="./ATTRLink/@LinkGUID"/>
				</xsl:attribute>
				<xsl:attribute name="LinkVersion">
					<xsl:value-of select="./ATTRLink/@LinkVersion"/>
				</xsl:attribute>
				<xsl:attribute name="LinkType">
					<xsl:value-of select="./ATTRLink/@LinkType"/>
				</xsl:attribute>
				<xsl:attribute name="LinkChildGUID">
					<xsl:value-of select="./ATTRLink/@LinkChildGUID"/>
				</xsl:attribute>
			</SignalLink>
		</xsl:if>	
    </xsl:template>

    <!-- ECU element rule -->
    <xsl:template match="ECU">
        <ECU>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | FlexRayController | NetworkNode | FileEntry | GenAttrList | NetworkNodeLink | GatewaySignalMapping" />
            <xsl:apply-templates select="PDUGroup" />
        </ECU>
    </xsl:template>

    <!-- PDUGroup element rule -->
    <!-- Remove old SignalGroupLinks  -->
    <xsl:template match="PDUGroup">
        <PDUGroup>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | PDUGroupLink" />
        </PDUGroup>
    </xsl:template>

    <!-- FrTp element rule -->
    <xsl:template match="FrTp">
        <FrTp>
            <xsl:copy-of select = "@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | FrTpAddress" />
            <xsl:apply-templates select="FrTpConnection" />
            <xsl:copy-of select="FrTpConnectionControl | FrTpNode" />
        </FrTp>
    </xsl:template>

    <!-- FrTpConnection element rule: remove SignalGroupRoot -->
    <xsl:template match="FrTpConnection">
        <FrTpConnection>
            <xsl:copy-of select="@GUID | @ConnectionControlLink | @MulticastLink | @TxTpNodeLink" />
            <xsl:apply-templates select="ATTRLink" />
            <xsl:copy-of select="FrTpNodeLink" />
        </FrTpConnection>
    </xsl:template>

    <!-- CANBus element rule -->
    <xsl:template match="CANBus">
        <CANBus>
            <!-- Set DTD version to 5.2, No ItemConvert required -->
            <xsl:attribute name="DTDVersion">5.2</xsl:attribute>
            <xsl:copy-of select= "@*[name() != 'DTDVersion']" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT" />
            <xsl:apply-templates select="CANFrame" />
            <xsl:copy-of select="Channel | GenAttrList | NetworkSignal" />
        </CANBus>
    </xsl:template>

    <!-- LINBus element rule -->
    <xsl:template match="LINBus">
        <LINBus>
            <!-- Set DTD version to 5.2, No ItemConvert required -->
            <xsl:attribute name="DTDVersion">5.2</xsl:attribute>
            <xsl:copy-of select = "@*[name() != 'DTDVersion']" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT" />
            <xsl:apply-templates select="LINUnconditionalFrame" />
            <xsl:apply-templates select="LINEventTriggeredFrame" />
            <xsl:apply-templates select="LINSporadicFrame" />
            <xsl:copy-of select="Channel | GenAttrList | ScheduleTable | NetworkSignal" />
        </LINBus>
    </xsl:template>

    <!-- FlexRayCluster element rule -->
    <xsl:template match="FlexRayCluster">
        <FlexRayCluster>
            <!-- Set DTD version to 5.2, No ItemConvert required -->
            <xsl:attribute name="DTDVersion">5.2</xsl:attribute>
            <xsl:copy-of select = "@*[name() != 'DTDVersion']" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT" />
            <xsl:apply-templates select="FlexRayFrame" />
            <xsl:copy-of select="Channel | GenAttrList | NetworkSignal" />
        </FlexRayCluster>
    </xsl:template>

    <!-- CANFrame element rule -->
    <xsl:template match="CANFrame">
        <CANFrame>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | GenAttrList | MultiplexorGroup | FrameNodeMap | FrameConstraint | MappedSignal" />
            <xsl:apply-templates select="MappedSignalGroup" />
            <xsl:copy-of select="NetworkNodeLink" />
        </CANFrame>
    </xsl:template>

    <!-- LINUnconditionalFrame element rule  -->
    <xsl:template match="LINUnconditionalFrame">
        <LINUnconditionalFrame>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | GenAttrList | MultiplexorGroup | FrameNodeMap | FrameConstraint | MappedSignal" />
            <xsl:apply-templates select="MappedSignalGroup" />
            <xsl:copy-of select="NetworkNodeLink" />
        </LINUnconditionalFrame>
    </xsl:template>

    <!-- LINEventTriggeredFrame element rule -->
    <xsl:template match="LINEventTriggeredFrame">
        <LINEventTriggeredFrame>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | GenAttrList | MultiplexorGroup | FrameNodeMap | FrameConstraint | MappedSignal | LINUnconditionalFrameIndex" />
            <xsl:apply-templates select="MappedSignalGroup" />
            <xsl:copy-of select="NetworkNodeLink" />
        </LINEventTriggeredFrame>
    </xsl:template>

    <!-- LINSporadicFrame element rule -->
    <xsl:template match="LINSporadicFrame">
        <LINSporadicFrame>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | GenAttrList | MultiplexorGroup | FrameNodeMap | FrameConstraint | MappedSignal | LINUnconditionalFrameIndex" />
            <xsl:apply-templates select="MappedSignalGroup" />
            <xsl:copy-of select="NetworkNodeLink" />
        </LINSporadicFrame>
    </xsl:template>

    <!-- FlexRayFrame element rule -->
    <xsl:template match="FlexRayFrame">
        <FlexRayFrame>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | GenAttrList | MultiplexorGroup | FrameNodeMap | FrameConstraint | MappedSignal" />
            <xsl:apply-templates select="MappedSignalGroup" />
            <xsl:copy-of select="NetworkNodeLink" />
        </FlexRayFrame>
    </xsl:template>

    <!-- MappedSignalGroup element rule: remove StartBit, rename SignalGroupRoot -->
    <xsl:template match="MappedSignalGroup">
        <MappedSignalGroup>
            <xsl:copy-of select="@GUID | @SignalGroupLink" />
            <xsl:attribute name="SignalGroupLink">SignalGroup</xsl:attribute>
            <xsl:copy-of select="@ComSignalName | @UpdateBitPosition" />
            <xsl:apply-templates select="ATTRLink" />
            <xsl:copy-of select="GenAttrList" />
        </MappedSignalGroup>
    </xsl:template>

    <!-- AttrLink element rule -->
    <xsl:template match="ATTRLink">
        <xsl:choose>
            <xsl:when test="@LinkName[.='ProxyReceiverPort' or .='ProxyTransmitterPort' or .='DirectSDU' or .='ReversedSDU']">
            </xsl:when>
            <xsl:when test="@LinkName[.='SignalGroupRoot']">
                <ATTRLink>
                    <xsl:attribute name="LinkName">SignalGroup</xsl:attribute>
                    <xsl:copy-of select="@LinkVersion | @LinkGUID" />
                    <xsl:attribute name="LinkType">SignalGroup</xsl:attribute>
                    <xsl:copy-of select="@LinkChildGUID" />
                </ATTRLink>
            </xsl:when>
            <xsl:when test="@LinkName[.='DataMapComplexElement']">
                <ATTRLink>
                    <xsl:attribute name="LinkName">DataMapComplexElement</xsl:attribute>
                    <xsl:copy-of select="@LinkVersion | @LinkGUID" />
                    <xsl:attribute name="LinkType">SignalGroup</xsl:attribute>
                    <xsl:copy-of select="@LinkChildGUID" />
                </ATTRLink>
            </xsl:when>
            <xsl:otherwise>
                <ATTRLink>
                    <xsl:copy-of select="@*" />
                </ATTRLink>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>

</xsl:stylesheet>
