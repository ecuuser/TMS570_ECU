<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.1\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <VPCommunication>
            <xsl:apply-templates select="VPCommunication" />
        </VPCommunication>
    </xsl:template>
    
    <!-- Remove obsolete conversion artifacts: NetworkSignal -->
    
    <!-- VPCommunication element rule -->
    <!-- Set DTD version to 4.1, No ItemConvert required -->
    <xsl:template match="VPCommunication">
        <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version" />
        <xsl:attribute name="DTDVersion">4.1</xsl:attribute>
        <xsl:copy-of select="@VehicleProjectLink" />
        <xsl:copy-of select="NAME | ATTRLink" />
        <xsl:apply-templates select="SignalRouting" />
    </xsl:template>

    <!-- SignalRouting element rule -->
    <!-- remove NetworkSignal -->
    <xsl:template match="SignalRouting">
        <SignalRouting>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="ATTRLink | FuncDAMapLink | SignalRoutingConstraint | DataElementLink" />
        </SignalRouting>
    </xsl:template>

</xsl:stylesheet>
