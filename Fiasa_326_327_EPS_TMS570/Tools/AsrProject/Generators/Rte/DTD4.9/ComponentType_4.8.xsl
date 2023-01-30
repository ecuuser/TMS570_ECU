<?xml version="1.0" encoding="ISO-8859-1" standalone="no"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.9\DVW.DTD"/>

  <!-- Root element rule -->
  <xsl:template match="/">
	  <ComponentType>
		  <xsl:apply-templates select="ComponentType"/>
	  </ComponentType>
  </xsl:template>
  
  <!-- ComponentType element rule -->
    <!-- Set DTD version to 4.9, No ItemConvert required -->
  <xsl:template match="ComponentType">
      <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version | @RO" />
      <xsl:attribute name="DTDVersion">4.9</xsl:attribute>
      <xsl:copy-of select="@DeviceAccessorLink | @FunctionLink | @FNDerived | @Refined | @SupportMI | @ImplCodeType" />
	  <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | CONTENT"/>
	  <xsl:apply-templates select="Runnable"/>
	  <xsl:copy-of select="Application | SensorActuator | Service | Composition | Calibration | PortPrototype | FileEntry | GenAttrList | ExclusiveArea | InterRunnableVariable | CalibrationParameter | PerInstanceMemory"/>
  </xsl:template>
  
  <!-- Runnable element rule -->
  <xsl:template match="Runnable">
	  <Runnable>
		  <xsl:copy-of select="@*"/>
		  <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink"/>
		  <xsl:for-each select="Trigger/*">
			  <Trigger>
				  <xsl:copy-of select="."/>
			  </Trigger>
		  </xsl:for-each>
		  <xsl:copy-of select="RunnableDataAccess | GenAttrList | OperationAccess | ExclusiveAreaAccess | InterRunnableVariableAccess"/>
	  </Runnable>
  </xsl:template>

</xsl:stylesheet>