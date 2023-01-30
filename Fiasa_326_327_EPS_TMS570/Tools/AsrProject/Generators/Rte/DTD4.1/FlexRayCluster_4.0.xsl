<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.1\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <FlexRayCluster>
            <xsl:apply-templates select="FlexRayCluster" />
        </FlexRayCluster>
    </xsl:template>
    
    <!-- Remove obsolete conversion artifacts at the NetworkNode -->
    
    <!-- FlexRayCluster element rule -->
    <!-- Set DTD version to 4.1, No ItemConvert required -->
    <xsl:template match="FlexRayCluster">
        <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version" />
        <xsl:attribute name="DTDVersion">4.1</xsl:attribute>
        <xsl:copy-of select="@VehicleProjectGUID | @Manufacturer | @NMType" />
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
            <xsl:copy-of select="NAME | LONGNAME | DESC | GenAttrList" />
        </NetworkNode>
    </xsl:template>
    
</xsl:stylesheet>
