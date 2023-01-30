<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.1\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <ECUProject>
            <xsl:apply-templates select="ECUProject" />
        </ECUProject>
    </xsl:template>
    
    <!-- Remove obsolete conversion artifacts: NetworkSignal -->
    
    <!-- ECUProject element rule -->
    <!-- Set DTD version to 4.1, No ItemConvert required -->
    <xsl:template match="ECUProject">
        <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version" />
        <xsl:attribute name="DTDVersion">4.1</xsl:attribute>
        <xsl:copy-of select="@ECULink | @GenOutputLevel | @BSWMDFileCom | @BSWMDFileOs | @ECUCFile | @ECUCFileLastUpdate | @CommunicationMode" />
        <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT | ATTRLink | FileEntry | Task | TaskMap" />
        <xsl:apply-templates select="ECUSWComposition" />
        <xsl:apply-templates select="ECUCommunication" />
        <xsl:copy-of select="ExternalTool | Generator |GenAttrList" />
    </xsl:template>

    <!-- ECUSWComposition element rule -->
    <xsl:template match="ECUSWComposition">
        <ECUSWComposition>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | ProxyComponent | ProxyPortPrototype | ProxyPortConnector | ComponentPrototype" />
            <xsl:apply-templates select="PortConnector" />
            <xsl:apply-templates select="PortPrototype" />
            <xsl:copy-of select="DataMapping | GenAttrList" />
        </ECUSWComposition>
    </xsl:template>

    <!-- PortConnector element rule -->
    <xsl:template match="PortConnector">
        <PortConnector>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="DESC | ATTRLink | GenAttrList" />
            <xsl:apply-templates select="SenderReceiverConnectorComSpec" />
            <xsl:copy-of select="ClientServerConnectorComSpec" />
        </PortConnector>
    </xsl:template>
    
    <!-- SenderReceiverConnectorComSpec element rule -->
    <!-- Rename attributes -->
    <xsl:template match="SenderReceiverConnectorComSpec">
        <SenderReceiverConnectorComSpec>
            <xsl:copy-of select="@GUID" />
            <xsl:attribute name="MaxResponseTime">
                <xsl:value-of select="@MaxTransferTime"/>
            </xsl:attribute>
            <xsl:attribute name="MaxResponseTimeUnit">
                <xsl:value-of select="@TransferTimeUnit"/>
            </xsl:attribute>
            <xsl:copy-of select="@MaxJitter | @JitterTimeUnit | @DataElementPrototypeLink" />
            <xsl:copy-of select="node()" />
        </SenderReceiverConnectorComSpec>
    </xsl:template>

    <!-- PortPrototype element rule -->
    <xsl:template match="PortPrototype">
        <PortPrototype>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | GenAttrList" />
            <xsl:apply-templates select="SenderReceiverComSpec" />
            <xsl:copy-of select="ClientServerComSpec | PortAPIOption" />
        </PortPrototype>
    </xsl:template>

    <!-- SenderReceiverComSpec element rule -->
    <!-- remove 'FilterClass' attribute -->
    <xsl:template match="SenderReceiverComSpec">
        <SenderReceiverComSpec>
            <xsl:copy-of select="@AliveTimeout | @ResynchroTime | @SupportInvalidate | @QueueLength | @InitValueConstLink | @DataElementPrototypeLink" />
            <xsl:copy-of select="@UsesTxAcknowledge | @TxAckTimeOut | @TxAckTimeOutUnit" />
            <xsl:copy-of select="ATTRLink" />
        </SenderReceiverComSpec>
    </xsl:template>

    <!-- ECUCommunication element rule -->
    <xsl:template match="ECUCommunication">
        <ECUCommunication>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="ATTRLink |Signal | SignalType | SignalGroupRoot" />
            <xsl:apply-templates select="SignalRouting" />
            <xsl:apply-templates select="ECU" />
            <xsl:apply-templates select="CANBus" />
            <xsl:apply-templates select="LINBus" />
            <xsl:apply-templates select="FlexRayCluster" />
        </ECUCommunication>
    </xsl:template>

    <!-- SignalRouting element rule -->
    <!-- remove NetworkSignal -->
    <xsl:template match="SignalRouting">
        <SignalRouting>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="ATTRLink | FuncDAMapLink | SignalRoutingConstraint | DataElementLink" />
        </SignalRouting>
    </xsl:template>

    <!-- ECU element rule -->
    <!-- remove NetworkNode -->
    <xsl:template match="ECU">
        <ECU>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | FlexRayController | FileEntry | GenAttrList | ECUPin | DeviceInst | PinConnection | NetworkNodeLink" />
        </ECU>
    </xsl:template>

    <!-- CANBus element rule -->
    <!-- Set DTD version to 4.1, No ItemConvert required -->
    <xsl:template match="CANBus">
        <CANBus>
            <xsl:copy-of select="@GUID | @VehicleProjectGUID | @Manufacturer | @NMType | @Bitrate | @Framesize | @ConnectableStations" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT | CANFrame" />
            <xsl:apply-templates select="Channel" />
            <xsl:copy-of select="GenAttrList | NetworkSignal" />
        </CANBus>
    </xsl:template>

    <xsl:template match="LINBus">
        <LINBus>
            <xsl:copy-of select="@GUID | @VehicleProjectGUID | @Manufacturer | @NMType | @Protocol | @Bitrate | @LDF | @ChannelName" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT" />
            <xsl:apply-templates select="LINUnconditionalFrame" />
            <xsl:copy-of select="LINEventTriggeredFrame | LINSporadicFrame" />
            <xsl:apply-templates select="Channel" />
            <xsl:copy-of select="GenAttrList | ScheduleTable | NetworkSignal" />
        </LINBus>
    </xsl:template>

    <!-- FlexRayCluster element rule -->
    <xsl:template match="FlexRayCluster">
        <FlexRayCluster>
            <xsl:copy-of select="@GUID | @VehicleProjectGUID | @Manufacturer | @NMType" />
            <xsl:copy-of select="@Baudrate | @CycleLength | @PayloadLengthStatic | @NumberOfStaticSlots | @NumberOfMiniSlots | @StaticSlotLength | @MiniSlotLength" />
            <xsl:copy-of select="@MacroTick | @WakeupSymbolTxIdle | @WakeupSymbolTxLow | @WakeupSymbolRxWindow | @WakeupSymbolRxIdle | @WakeupSymbolRxLow" />
            <xsl:copy-of select="@StaticSlotActionPointOffset | @MiniSlotActionPointOffset | @DynamicSlotIdlePhase | @NIT | @SymbolWindow | @SampleClockPeriod" />
            <xsl:copy-of select="@TSSTransmitter | @ListenNoise | @MacroPerCycle | @MaxInitError | @MaxWOClockCorrFatal | @MaxWOClockCorrPassive | @NMVectorLength" />
            <xsl:copy-of select="@SyncNodeMax | @CasRxLowMax | @CasRxLowMin | @ClusterDriftDamping | @OffsetCorrStart | @ColdStartAttempts | @LimitDynamicPayloadLength" />
            <xsl:copy-of select="@Protocol | @ProtocolVersion | @Medium | @IsHighLowBitOrder | @BitCounting | @OffsetCorrectionMax | @MaxPropagationDelay | @MinPropagationDelay" />
            <xsl:copy-of select="@EnableSymbolWindow | @EnableNetworkManagement | @AssumedPrecision | @MaxMicrotick | @NStarPath | @MacroInitialOffset" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT | FlexRayFrame" />
            <xsl:apply-templates select="Channel" />
            <xsl:copy-of select="GenAttrList | NetworkSignal" />
        </FlexRayCluster>
    </xsl:template>

    <!-- LINUnconditionalFrame element rule -->
    <!-- remove Old_EvTrigMessageID attribute -->
    <xsl:template match="LINUnconditionalFrame">
        <LINUnconditionalFrame>
            <xsl:copy-of select="@GUID | @FrameID | @DLC | @DynamicID | @MinPeriod | @MaxPeriod" />
            <xsl:copy-of select="node()" />
        </LINUnconditionalFrame>
    </xsl:template>

    <!-- Channel element rule -->
    <xsl:template match="Channel">
        <Channel>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC" />
            <xsl:apply-templates select="NetworkNode" />
            <xsl:copy-of select="GenAttrList" />
        </Channel>
    </xsl:template>

    <!-- NetworkNode element rule -->
    <!-- remove Old_ChannelLink attribute and ATTRLink -->
    <xsl:template match="NetworkNode">
        <NetworkNode>
            <xsl:copy-of select="@GUID | @ECUGUID | @LINType" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | GenAttrList | LINSlaveNodeAttributes | LINMasterNodeAttributes | LINRxFrameNodeMap" />
        </NetworkNode>
    </xsl:template>
    

</xsl:stylesheet>
