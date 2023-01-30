<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.4\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <ECUProject>
            <xsl:apply-templates select="ECUProject" />
        </ECUProject>
    </xsl:template>
    
    <!-- Remove obsolete conversion artifacts: SignalRouting -->
    
    <!-- ECUProject element rule -->
    <!-- Set DTD version to 4.4, No ItemConvert required -->
    <xsl:template match="ECUProject">
        <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version" />
        <xsl:attribute name="DTDVersion">4.4</xsl:attribute>
        <xsl:copy-of select="@ECULink | @GenOutputLevel | @BSWMDFileCom | @BSWMDFileOs | @ECUCFile | @ECUCFileLastUpdate | @CommunicationMode" />
        <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT | ATTRLink | FileEntry | Task | TaskMap | ECUSWComposition" />        
        <xsl:apply-templates select="ECUCommunication" />
        <xsl:copy-of select="ExternalTool | Generator |GenAttrList" />          
    </xsl:template>
          
    <!-- ECUCommunication element rule -->
    <!-- remove SignalRouting -->
    <xsl:template match="ECUCommunication">
        <ECUCommunication>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="ATTRLink | Signal | SignalType | SignalGroupRoot | ECU | CANBus | LINBus | FlexRayCluster" />
        </ECUCommunication>
    </xsl:template>  
    
</xsl:stylesheet>
