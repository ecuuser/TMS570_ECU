<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD5.2\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <ConstantPool>
            <xsl:apply-templates select="ConstantPool" />
        </ConstantPool>
    </xsl:template>
    
	<xsl:template match="ConstantPool">
        <!-- DO NOT Set DTD version to 5.2, call of item convert required  -->
		<xsl:copy-of select="@*" />
		<xsl:apply-templates select="Constant" />
	</xsl:template>

	<!-- Constant element rule: remove function net links -->
	<xsl:template match="Constant">
		<Constant>
            <!-- DO NOT Set DTD version to 5.2, call of item convert required  -->
		    <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version | @DTDVersion | @RO | @Value | @DataTypeLink" />
	        <xsl:copy-of select="NAME | LONGNAME | DESC"/>
	        <xsl:apply-templates select="ATTRLink"/>
	        <xsl:copy-of select="ArrayElementConstant | RecordElementConstant | GenAttrList"/>
		</Constant>
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
