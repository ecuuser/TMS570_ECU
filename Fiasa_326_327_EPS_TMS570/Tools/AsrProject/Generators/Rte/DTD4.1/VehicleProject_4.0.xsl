<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.1\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <VehicleProject>
            <xsl:apply-templates select="VehicleProject" />
        </VehicleProject>
    </xsl:template>
    
    <!-- Remove obsolete conversion artifacts: CANBus, LINBus, FlexRayCluster -->
    
    <!-- VehicleProject element rule -->
    <!-- Set DTD version to 4.1, No ItemConvert required -->
    <xsl:template match="VehicleProject">
        <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version" />
        <xsl:attribute name="DTDVersion">4.1</xsl:attribute>
        <xsl:copy-of select="@FunctionNetLink | @SoftwareArchitectureLink | @CommunicationLink | @DerivedSWLink | @DesignMode | @FunctionNetTimeStamp" />
        <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT | ATTRLink" />
        <xsl:apply-templates select="ECU" />
        <xsl:copy-of select="CANBusLink | LINBusLink | FlexRayClusterLink | FuncDAMap | Component | GenAttrList | MappingConstraint | FileEntry" />
    </xsl:template>

    <!-- ECU element rule -->
    <!-- remove NetworkNode -->
    <xsl:template match="ECU">
        <ECU>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | FlexRayController | FileEntry | GenAttrList | ECUPin | DeviceInst | PinConnection | NetworkNodeLink" />
        </ECU>
    </xsl:template>

</xsl:stylesheet>
