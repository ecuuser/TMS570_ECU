<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD5.5\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <FlexRayCluster>
            <xsl:apply-templates select="FlexRayCluster" />
        </FlexRayCluster>
    </xsl:template>
    
	<!-- FlexRayCluster element rule -->
    <!-- DO NOT Set DTD version to 5.5, call of item convert required  -->
    <xsl:template match="FlexRayCluster">
        <xsl:copy-of select="@*" />
        <xsl:copy-of select="node()" />
    </xsl:template>

</xsl:stylesheet>
