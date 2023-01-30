<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD5.4\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <ECUProject>
            <xsl:apply-templates select="ECUProject" />
        </ECUProject>
    </xsl:template>

    <!-- ECUProject element rule -->
    <!-- DO NOT Set DTD version to 5.4, call of item convert required  -->
    <xsl:template match="ECUProject">
        <xsl:copy-of select="@*" />
        <xsl:copy-of select="node()" />
    </xsl:template>

</xsl:stylesheet>
