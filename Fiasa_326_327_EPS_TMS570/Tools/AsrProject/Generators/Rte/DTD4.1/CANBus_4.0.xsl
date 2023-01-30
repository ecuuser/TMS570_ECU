<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.1\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <CANBus>
            <xsl:apply-templates select="CANBus" />
        </CANBus>
    </xsl:template>
    
    <!-- Remove obsolete conversion artifacts at the NetworkNode -->
    
    <!-- CANBus element rule -->
    <!-- Set DTD version to 4.1, No ItemConvert required -->
    <xsl:template match="CANBus">
        <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version" />
        <xsl:attribute name="DTDVersion">4.1</xsl:attribute>
        <xsl:copy-of select="@VehicleProjectGUID | @Manufacturer | @NMType | @Bitrate | @Framesize | @ConnectableStations" />
        <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT | CANFrame" />
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
