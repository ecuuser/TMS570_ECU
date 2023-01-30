<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD5.2\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <PortInterface>
            <xsl:apply-templates select="PortInterface" />
        </PortInterface>
    </xsl:template>
    
	<!-- PortInterface element rule: remove function net links -->
	<xsl:template match="PortInterface">
		    <!-- Set DTD version to 5.2, No ItemConvert required -->
			<xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version" />
			<xsl:attribute name="DTDVersion">5.2</xsl:attribute>
			<xsl:copy-of select="@RO | @IsServicePort | @BSWModule" />
            <xsl:copy-of select="NAME | LONGNAME | DESC" />
            <xsl:apply-templates select="ATTRLink" />
            <xsl:apply-templates select="SenderReceiver" />
            <xsl:apply-templates select="ClientServer" />
            <xsl:copy-of select="CalInterface | GenAttrList" />
	</xsl:template>
	
    <!-- SenderReceiver element rule -->
    <xsl:template match="SenderReceiver">
        <SenderReceiver>
            <xsl:copy-of select="@*"/>
            <xsl:apply-templates select="DataElementPrototype" />
            <xsl:copy-of select="ModeDclrGroupPrototype" />
        </SenderReceiver>
    </xsl:template>
	
    <!-- DataElementPrototype element rule: remove function net links -->
    <xsl:template match="DataElementPrototype">
        <DataElementPrototype>
            <xsl:copy-of select="@GUID | @DataTypeLink | @IsQueued"/>
            <xsl:copy-of select="NAME | LONGNAME | DESC" />
            <xsl:apply-templates select="ATTRLink" />
            <xsl:copy-of select="GenAttrList" />
        </DataElementPrototype>
    </xsl:template>
	
    <!-- ClientServer element rule -->
    <xsl:template match="ClientServer">
        <ClientServer>
            <xsl:copy-of select="@*"/>
            <xsl:apply-templates select="OperationPrototype" />
            <xsl:copy-of select="ApplicationError" />
        </ClientServer>
    </xsl:template>
	
    <!-- OperationPrototype element rule: remove function net attribute -->
    <xsl:template match="OperationPrototype">
        <OperationPrototype>
            <xsl:copy-of select="@GUID"/>
			<xsl:copy-of select="node()" />
        </OperationPrototype>
    </xsl:template>
	
    <!-- AttrLink element rule -->
    <xsl:template match="ATTRLink">
        <xsl:choose>
            <xsl:when test="@LinkName[.='Signal' or .='SignalGroupRoot' or .='FunctionTrigger']">
            </xsl:when>
            <xsl:otherwise>
                <ATTRLink>
                    <xsl:copy-of select="@*" />
                </ATTRLink>
            </xsl:otherwise>
        </xsl:choose>                
    </xsl:template>
	
</xsl:stylesheet>
