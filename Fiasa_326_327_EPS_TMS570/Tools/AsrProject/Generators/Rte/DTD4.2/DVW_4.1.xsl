<?xml version="1.0" encoding="ISO-8859-1" standalone="no"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.2\DVW.DTD"/>

<!-- Root element rule -->
  <xsl:template match="/">
  <DVW>
    <xsl:apply-templates select="DVW"/>
  </DVW>
  </xsl:template>

<!-- DVW element rule -->
<!-- Set DTD version to 4.2, no external conversion required  -->

  <xsl:template match="DVW">
    <xsl:attribute name="DTDVersion">4.2</xsl:attribute>
    <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version | @InstVers | @SpecialBuild | @AttrDefSetLink"/>
    <xsl:copy-of select ="node()"/>
  </xsl:template>

</xsl:stylesheet>

