<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.4\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <VehicleProject>
            <xsl:apply-templates select="VehicleProject" />
        </VehicleProject>
    </xsl:template>
    
    <!-- Remove CommunicationLink link -->
    
    <!-- VehicleProject element rule -->
    <!-- Set DTD version to 4.4, no ItemConvert required -->
    <xsl:template match="VehicleProject">
        <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version" />
        <xsl:attribute name="DTDVersion">4.4</xsl:attribute>
        <xsl:copy-of select="@FunctionNetLink | @SoftwareArchitectureLink | @DerivedSWLink | @DesignMode | @FunctionNetTimeStamp" />
        <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT" />
        <xsl:apply-templates select="ATTRLink" />
        <xsl:copy-of select="ECU | CANBusLink | LINBusLink | FlexRayClusterLink | FuncDAMap | Component | GenAttrList | MappingConstraint | FileEntry" />
    </xsl:template>
    
    <!-- AttrLink element rule -->
    <xsl:template match="ATTRLink">
        <xsl:choose>
            <xsl:when test="@LinkType[.='VPCommunication']">
            </xsl:when>
            <xsl:otherwise>
                <ATTRLink>
                    <xsl:copy-of select="@*" />
                </ATTRLink>
            </xsl:otherwise>
        </xsl:choose>                
    </xsl:template>

</xsl:stylesheet>
