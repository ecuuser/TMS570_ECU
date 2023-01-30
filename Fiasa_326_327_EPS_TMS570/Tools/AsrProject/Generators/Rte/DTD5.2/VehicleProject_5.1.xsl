<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD5.2\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <VehicleProject>
            <xsl:apply-templates select="VehicleProject" />
        </VehicleProject>
    </xsl:template>
    
    <!-- VehicleProject element rule -->
    <!-- Set DTD version to 5.2, No ItemConvert required -->
    <!-- Remove software component and function design -->
    <xsl:template match="VehicleProject">
        <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version | @RO" />
        <xsl:attribute name="DTDVersion">5.2</xsl:attribute>
        <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT" />
        <xsl:apply-templates select="ATTRLink" />
        <xsl:apply-templates select="ECU" />
        <xsl:copy-of select="CANBusLink | LINBusLink | FlexRayClusterLink | GenAttrList | FileEntry" />
        <xsl:apply-templates select="FrTp" />
    </xsl:template>
    
    <!-- ECU element rule -->
    <!-- Remove Pins, Devices  -->
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

    <!-- AttrLink element rule -->
    <xsl:template match="ATTRLink">
        <xsl:choose>
            <xsl:when test="@LinkName[.='FunctionNet' or .='DerivedSW' or .='SoftwareArchitecture' or .='DirectSDU' or .='ReversedSDU']">
            </xsl:when>
            <xsl:otherwise>
                <ATTRLink>
                    <xsl:copy-of select="@*" />
                </ATTRLink>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>

</xsl:stylesheet>
