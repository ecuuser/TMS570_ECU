<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.6\DVW.DTD" />
    
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
    <!-- Set DTD version to 4.6, No ItemConvert required -->
    <xsl:template match="ECUProject">
        <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version | @RO" />
        <xsl:attribute name="DTDVersion">4.6</xsl:attribute>
        <xsl:copy-of select="@ECULink | @GenOutputLevel | @BSWMDFileCom | @BSWMDFileOs | @ECUCFile | @ECUCFileLastUpdate | @CommunicationMode" />
        <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT | ATTRLink | FileEntry | Task | TaskMap | NVMBlock | MemoryMap" />        
        <xsl:apply-templates select="ECUSWComposition" />
        <xsl:apply-templates select="ECUCommunication" />
        <xsl:copy-of select="ExternalTool | Generator |GenAttrList" />          
    </xsl:template>
          
    <!-- ECUSWComposition element rule -->
    <xsl:template match="ECUSWComposition">
        <ECUSWComposition>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink" />
            <xsl:apply-templates select="ProxyComponent" />
            <xsl:apply-templates select="ProxyPortPrototype" />
            <xsl:copy-of select="ProxyPortConnector | ComponentPrototype | PortConnector | PortPrototype | DataMapping | ServicePortConnector | GenAttrList" />
        </ECUSWComposition>
    </xsl:template>  
    
    <!-- ProxyComponent element rule -->
    <xsl:template match="ProxyComponent">
        <ProxyComponent>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="ATTRLink | GenAttrList" />
            <xsl:apply-templates select="ProxyPortPrototype" />
        </ProxyComponent>
    </xsl:template>  
    
    <!-- ProxyPortPrototype element rule -->
    <xsl:template match="ProxyPortPrototype">
        <ProxyPortPrototype>
            <xsl:copy-of select="@*" />
            <NAME />
            <xsl:copy-of select="ATTRLink | GenAttrList" />
        </ProxyPortPrototype>
    </xsl:template>  
    
    <!-- ECUCommunication element rule -->
    <xsl:template match="ECUCommunication">
        <ECUCommunication>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="ATTRLink | Signal | SignalType | SignalGroupRoot | ECU" />
            <xsl:apply-templates select="CANBus" />
            <xsl:apply-templates select="LINBus" />
            <xsl:apply-templates select="FlexRayCluster" />
        </ECUCommunication>
    </xsl:template>  
    
    <!-- CANBus element rule -->
    <xsl:template match="CANBus">
        <CANBus>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT | CANFrame | Channel | GenAttrList" />
            <xsl:apply-templates select="NetworkSignal" />
        </CANBus>
    </xsl:template>  
    
    <!-- LINBus element rule -->
    <xsl:template match="LINBus">
        <LINBus>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT | LINUnconditionalFrame | LINEventTriggeredFrame | LINSporadicFrame | Channel | GenAttrList | ScheduleTable" />
            <xsl:apply-templates select="NetworkSignal" />
        </LINBus>
    </xsl:template>  
    
    <!-- FlexRayCluster element rule -->
    <xsl:template match="FlexRayCluster">
        <FlexRayCluster>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | CONTENT | FlexRayFrame | Channel | GenAttrList" />
            <xsl:apply-templates select="NetworkSignal" />
        </FlexRayCluster>
    </xsl:template>  
    
    <!-- NetworkSignal element rule -->
    <xsl:template match="NetworkSignal">
        <NetworkSignal>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="DESC" />
            <xsl:apply-templates select="ATTRLink" />
            <xsl:copy-of select="GenAttrList | MultiplexorGroupLink | RxNodeRelation | TxNodeRelation | MappedSignalLink" />
        </NetworkSignal>
    </xsl:template>  
    
    <!-- ATTRLink element rule -->
    <!-- Correct attribute LinkGUID for child signals -->
    <xsl:template match="ATTRLink">
        <xsl:if test="@LinkName='Signal'">
            <ATTRLink>
                <xsl:copy-of select="@LinkName | @LinkVersion | @LinkType" />
                <xsl:choose>
                    <xsl:when test="@LinkGUID=@LinkChildGUID or not(@LinkChildGUID)">
                        <xsl:attribute name="LinkGUID">
                            <xsl:value-of select="/ECUProject/@GUID"/>
                        </xsl:attribute>
                        <xsl:attribute name="LinkChildGUID">
                            <xsl:value-of select="@LinkGUID"/>
                        </xsl:attribute>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:copy-of select="@LinkGUID | @LinkChildGUID" />
                    </xsl:otherwise>
                </xsl:choose>
            </ATTRLink>
        </xsl:if>
    </xsl:template>  
    
</xsl:stylesheet>
