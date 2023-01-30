<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD5.2\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <Constant>
            <xsl:apply-templates select="Constant" />
        </Constant>
    </xsl:template>
    
	<!-- Constant element rule: remove function net links -->
	<xsl:template match="Constant">
		    <!-- Set DTD version to 5.2, No ItemConvert required -->
			<xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version" />
			<xsl:attribute name="DTDVersion">5.2</xsl:attribute>
			<xsl:copy-of select="@RO | @Value | @DataTypeLink" />
	        <xsl:copy-of select="NAME | LONGNAME | DESC"/>
	        <xsl:apply-templates select="ATTRLink"/>
	        <xsl:copy-of select="ArrayElementConstant | RecordElementConstant | GenAttrList"/>
	</xsl:template>
	
    <!-- AttrLink element rule -->
    <xsl:template match="ATTRLink">
        <xsl:choose>
            <xsl:when test="@LinkName[.='SignalType' or .='PrivateSigType' or .='SignalDefine' or .='Signal']">
            </xsl:when>
            <xsl:otherwise>
                <ATTRLink>
                    <xsl:copy-of select="@*" />
                </ATTRLink>
            </xsl:otherwise>
        </xsl:choose>                
    </xsl:template>
	
</xsl:stylesheet>
