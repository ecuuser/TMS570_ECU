<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD5.1\DVW.DTD" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <Constant>
            <xsl:apply-templates select="Constant" />
        </Constant>
    </xsl:template>
    
    <!-- Constant element rule -->
    <!-- DO NOT Set DTD version to 5.0, call of item convert required  -->
    <xsl:template match="Constant">
        <xsl:copy-of select="@*" />
        <xsl:copy-of select="node()" />
    </xsl:template>
    
</xsl:stylesheet>