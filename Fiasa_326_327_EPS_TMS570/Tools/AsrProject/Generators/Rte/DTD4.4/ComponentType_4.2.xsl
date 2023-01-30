<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.4\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <ComponentType>
            <xsl:apply-templates select="ComponentType" />
        </ComponentType>
    </xsl:template>
    
    <!-- ComponentType element rule -->
	<!-- Set DTD version to 4.4, No ItemConvert required -->
    <xsl:template match="ComponentType">
		<xsl:attribute name="DTDVersion">4.4</xsl:attribute>
		<xsl:copy-of select = "@*[name() != 'DTDVersion']" />
        <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | CONTENT" />
        <xsl:apply-templates select="Runnable" />
        <xsl:copy-of select="Application | SensorActuator | Service | Composition | PortPrototype | FileEntry | GenAttrList | ExclusiveArea | InterRunnableVariable" />
    </xsl:template>

    <!-- Runnable element rule -->
    <xsl:template match="Runnable">
        <Runnable>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | Trigger | RunnableDataAccess | GenAttrList" />
            <xsl:apply-templates select="OperationAccess" />
            <xsl:copy-of select=" ExclusiveAreaAccess | InterRunnableVariableAccess" />
        </Runnable>
    </xsl:template>

    <!-- RunnableOperationAccess element rule -->
    <!-- Set 'direct' as AccessMode Value for all existing OPAccesses -->
    <xsl:template match="OperationAccess">
        <OperationAccess>
            <xsl:copy-of select="@GUID | @OperationPrototypeLink | @PortPrototypeLink" />
            <xsl:attribute name="AccessMode">DIRECT</xsl:attribute>
			<xsl:copy-of select="node()" />
        </OperationAccess>
    </xsl:template>
    
    
</xsl:stylesheet>
