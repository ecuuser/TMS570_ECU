<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.3\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <PortInterfacePool>
            <xsl:apply-templates select="PortInterfacePool" />
        </PortInterfacePool>
    </xsl:template>
    
	<xsl:template match="PortInterfacePool">
	    <!-- Set DTD version to 4.2, No ItemConvert required -->
		<xsl:attribute name="DTDVersion">4.2</xsl:attribute>
		<xsl:copy-of select = "@*[name() != 'DTDVersion']" />
		<xsl:apply-templates select="PortInterface" />
	</xsl:template>
	
	<!-- PortInterface element rule -->
	<xsl:template match="PortInterface">
		<PortInterface>
		    <!-- Set DTD version to 4.2, No ItemConvert required -->
			<xsl:attribute name="DTDVersion">4.2</xsl:attribute>
			<xsl:copy-of select="@*[name() != 'DTDVersion']" />
			<xsl:copy-of select="NAME | LONGNAME | DESC | AttrLink | SenderReceiver" />
			<xsl:apply-templates select="ClientServer" />
			<xsl:copy-of select="GenAttrList" />
		</PortInterface>
	</xsl:template>
	
	<!-- ClientServer element rule -->
	<xsl:template match="ClientServer">
		<ClientServer>
			<xsl:copy-of select="@*" />
			<xsl:copy-of select="OperationPrototype" />
			<xsl:apply-templates select="ApplicationError" />
		</ClientServer>
	</xsl:template>

    <!-- ApplicationError element rule -->
    <xsl:template match="ApplicationError">
        <ApplicationError>
			<!-- remove ErrorKind and TemporalBehavior -->
			<xsl:copy-of select="@GUID | @ErrorCode" />
			<xsl:copy-of select="*" />
		</ApplicationError>
    </xsl:template>

</xsl:stylesheet>
