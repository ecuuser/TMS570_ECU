<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD5.2\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <SignalGroup>
            <xsl:apply-templates select="SignalGroupRoot" />
        </SignalGroup>
    </xsl:template>
    
	<!-- SignalGroup element rule: remove layout -->
	<xsl:template match="SignalGroupRoot">
		    <!-- Set DTD version to 5.2, No ItemConvert required -->
			<xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version" />
			<xsl:attribute name="DTDVersion">5.2</xsl:attribute>
			<xsl:copy-of select="@RO | @IsServicePort | @BSWModule" />
            <xsl:copy-of select="NAME | LONGNAME | DESC" />
            <xsl:apply-templates select="SignalLayout" />
            <xsl:copy-of select="PDUTiming" />
    </xsl:template>
	
    <!-- SignalLayout element rule -->
    <xsl:template match="SignalLayout">
		<xsl:if test="./ATTRLink/@LinkGUID">
			<SignalLink>
				<xsl:attribute name="LinkGUID">
					<xsl:value-of select="./ATTRLink/@LinkGUID"/>
				</xsl:attribute>
				<xsl:attribute name="LinkVersion">
					<xsl:value-of select="./ATTRLink/@LinkVersion"/>
				</xsl:attribute>
				<xsl:attribute name="LinkType">
					<xsl:value-of select="./ATTRLink/@LinkType"/>
				</xsl:attribute>
			</SignalLink>
		</xsl:if>	
    </xsl:template>
	
</xsl:stylesheet>
