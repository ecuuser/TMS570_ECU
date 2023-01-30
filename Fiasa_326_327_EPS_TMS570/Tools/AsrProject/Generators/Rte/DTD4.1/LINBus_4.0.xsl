<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.1\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <LINBus>
            <xsl:apply-templates select="LINBus" />
        </LINBus>
    </xsl:template>
    
    <!-- Remove obsolete conversion artifacts at the NetworkNode -->
    
    <!-- LINBus element rule -->
    <!-- Set DTD version to 4.1, No ItemConvert required -->
    <xsl:template match="LINBus">
        <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version" />
        <xsl:attribute name="DTDVersion">4.1</xsl:attribute>
        <xsl:copy-of select="@VehicleProjectGUID | @Manufacturer | @NMType | @Protocol | @Bitrate | @LDF | @ChannelName" />
        <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT" />
        <xsl:apply-templates select="LINUnconditionalFrame" />
        <xsl:copy-of select="LINEventTriggeredFrame | LINSporadicFrame" />
        <xsl:apply-templates select="Channel" />
        <xsl:copy-of select="GenAttrList | ScheduleTable | NetworkSignal" />
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
