<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.2\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <ComponentType>
            <xsl:apply-templates select="ComponentType" />
        </ComponentType>
    </xsl:template>
    
    <!-- ComponentType element rule -->
    <!-- DO NOT Set DTD version to 4.2, call of item convert required  -->
    <xsl:template match="ComponentType">
        <xsl:copy-of select="@DTDVersion | @CMVersion | @CMState | @GUID | @Version" />
        <!-- remove ImportedServiceComp -->
        <xsl:copy-of select="@DeviceAccessorLink | @FunctionLink | @FNDerived | @Refined" />
        <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | CONTENT" />
        <xsl:apply-templates select="Runnable" />
        <xsl:copy-of select="Application | SensorActuator | Service | Composition | PortPrototype | FileEntry | GenAttrList | ExclusiveArea | InterRunnableVariable" />
    </xsl:template>

    <!-- Runnable element rule -->
    <xsl:template match="Runnable">
        <Runnable>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | Trigger" />
            <xsl:apply-templates select="RunnableDataAccess" />
            <xsl:copy-of select="GenAttrList | OperationAccess | ExclusiveAreaAccess | InterRunnableVariableAccess" />
        </Runnable>
    </xsl:template>

    <!-- RunnableDataAccess element rule -->
    <!-- Set polling as the new default for Tx-Acknowledge -->
    <xsl:template match="RunnableDataAccess">
        <RunnableDataAccess>
            <xsl:copy-of select="@GUID | @DataElementPrototypeLink | @PortPrototypeLink | @AccessMode | @TimeOut | @TimeOutUnit" />
            <xsl:choose>
                <xsl:when test="@TxAcknowledgeMode='NONE'">
                    <xsl:attribute name="TxAcknowledgeMode">POLLING</xsl:attribute>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:copy-of select="@TxAcknowledgeMode" />
                </xsl:otherwise>
            </xsl:choose>
			<xsl:copy-of select="node()" />
        </RunnableDataAccess>
    </xsl:template>
    
    
</xsl:stylesheet>
