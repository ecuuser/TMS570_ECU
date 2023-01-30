<?xml version="1.0" encoding="ISO-8859-1" standalone="no"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.9\DVW.DTD"/>

<!-- Root element rule -->
  <xsl:template match="/">
  <DVW>
    <xsl:apply-templates select="DVW"/>
  </DVW>
  </xsl:template>

<!-- DVW element rule -->
<!-- DO NOT set DTD version to 4.6; Stylesheet used to trigger the ObjectServer conversion  -->

  <xsl:template match="DVW"> 
    <xsl:copy-of select="@*"/>
    <xsl:copy-of select ="node()"/>
  </xsl:template>

</xsl:stylesheet>

