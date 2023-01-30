<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.6\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <VPDerivedSW>
            <xsl:apply-templates select="VPDerivedSW" />
        </VPDerivedSW>
    </xsl:template>
    
    <!-- VPDerivedSW element rule -->
    <!-- Set DTD version to 4.6, No ItemConvert required -->
    <xsl:template match="VPDerivedSW">
        <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version | @RO" />
        <xsl:attribute name="DTDVersion">4.6</xsl:attribute>
        <xsl:copy-of select="@SoftwareArchitectureLink | @SoftwareArchitectureTimeStamp" />
        <xsl:copy-of select="NAME | ATTRLink" />
        <xsl:apply-templates select="ComponentType" />
        <xsl:copy-of select="Constant | DataType | PortInterface" />
    </xsl:template>
          
    <xsl:template match="ComponentType">
        <ComponentType>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | CONTENT | Runnable | Application | SensorActuator | Composition" />
            <xsl:apply-templates select="PortPrototype" />
            <xsl:copy-of select="FileEntry | GenAttrList | ExclusiveArea | InterRunnableVariable" />
        </ComponentType>
    </xsl:template>

    <!-- PortPrototype element rule -->
    <xsl:template match="PortPrototype">
        <PortPrototype>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC" />
            <xsl:apply-templates select="ATTRLink" />
            <xsl:copy-of select="GenAttrList | SenderReceiverComSpec | ClientServerComSpec | PortAPIOption" />
        </PortPrototype>
    </xsl:template>  
    
    <!-- ATTRLink element rule -->
    <!-- Correct attribute LinkGUID for child port interfaces -->
    <xsl:template match="ATTRLink">
        <ATTRLink>
            <xsl:copy-of select="@LinkName | @LinkVersion | @LinkType" />
            <xsl:choose>
                <xsl:when test="@LinkName='PortInterface' and (@LinkGUID=@LinkChildGUID or not(@LinkChildGUID))">
                    <xsl:attribute name="LinkGUID">
                        <xsl:value-of select="/VPDerivedSW/@GUID"/>
                    </xsl:attribute>
                    <xsl:attribute name="LinkChildGUID">
                        <xsl:value-of select="@LinkGUID"/>
                    </xsl:attribute>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:copy-of select="@LinkGUID | @LinkChildGUID" />
                </xsl:otherwise>
            </xsl:choose>
        </ATTRLink>
    </xsl:template>  
    
</xsl:stylesheet>
