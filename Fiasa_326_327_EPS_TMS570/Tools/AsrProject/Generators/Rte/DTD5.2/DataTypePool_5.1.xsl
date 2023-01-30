<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD5.2\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <DataTypePool>
            <xsl:apply-templates select="DataTypePool" />
        </DataTypePool>
    </xsl:template>
    
	<xsl:template match="DataTypePool">
	    <!-- Set DTD version to 5.2, No ItemConvert required -->
		<xsl:attribute name="DTDVersion">5.2</xsl:attribute>
		<xsl:copy-of select = "@*[name() != 'DTDVersion']" />
		<xsl:apply-templates select="DataType" />
	</xsl:template>
	
	<!-- DataType element rule: remove function net links -->
	<xsl:template match="DataType">
		<DataType>
		    <!-- Set DTD version to 5.2, No ItemConvert required -->
			<xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version" />
			<xsl:attribute name="DTDVersion">5.2</xsl:attribute>
			<xsl:copy-of select="@RO | @Primitive | @BSWModule" />
			<xsl:copy-of select="node()" />
		</DataType>
	</xsl:template>
	
</xsl:stylesheet>
