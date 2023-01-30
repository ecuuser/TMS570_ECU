<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="yes" indent="yes"/>

    <xsl:template match="/">
    <xsl:text disable-output-escaping="yes">
&lt;!DOCTYPE DCF [
	&lt;!ELEMENT DCF ((NAME,ATTRDEF?,PROFILESETTINGS?,FILEREF*)?)>
	&lt;!ATTLIST DCF
	ARSCHEMA (21XSDREV0017|30XSDREV0003|31XSDREV0004|314DAI4|32XSDREV0001) "21XSDREV0017"&gt;
	&lt;!ELEMENT NAME (#PCDATA)&gt;
	&lt;!ELEMENT ATTRDEF (#PCDATA)&gt;
	&lt;!ELEMENT FILEREF (ARXML, DCB?, ECUC?, GENATTR?)&gt;
	&lt;!ELEMENT ARXML (#PCDATA)&gt;
	&lt;!ATTLIST ARXML TYPE CDATA "" 
    ROOTITEM (CONSTANT|DATATYPE|PORTINTERFACE|SIGNAL|COMPONENTTYPE|ECUPROJECT|VEHICLEPROJECT) #REQUIRED &gt;
	&lt;!ELEMENT DCB (#PCDATA)&gt;
	&lt;!ELEMENT ECUC (#PCDATA)&gt;
  &lt;!ELEMENT GENATTR (#PCDATA)&gt;
  &lt;!ELEMENT PROFILESETTINGS (#PCDATA)&gt;
]&gt;
</xsl:text>
	<xsl:apply-templates/>
    </xsl:template>

	<xsl:template match="DCF">
	<xsl:copy>
		<xsl:apply-templates select="@*"/>    	
    	<xsl:apply-templates select="node()">
	     <xsl:sort select="ARXML" order="ascending"/>
       </xsl:apply-templates>
       
    </xsl:copy>
  </xsl:template>
  
	<xsl:template match="@*|node()">
	<xsl:copy>
		<xsl:apply-templates select="*|@*|node()" />
	</xsl:copy>
	</xsl:template>

</xsl:stylesheet>