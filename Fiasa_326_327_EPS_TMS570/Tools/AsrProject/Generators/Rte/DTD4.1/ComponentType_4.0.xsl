<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.1\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <ComponentType>
            <xsl:apply-templates select="ComponentType" />
        </ComponentType>
    </xsl:template>
    
    <!-- ComponentType element rule -->
    <!-- Set DTD version to 4.1, No ItemConvert required -->
    <xsl:template match="ComponentType">
        <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version" />
        <xsl:attribute name="DTDVersion">4.1</xsl:attribute>
        <!-- remove ImportedServiceComp -->
        <xsl:copy-of select="@DeviceAccessorLink | @FunctionLink | @FNDerived | @Refined" />
        <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | CONTENT | Runnable | Application | SensorActuator" />
        <xsl:apply-templates select="Composition" />
        <xsl:apply-templates select="PortPrototype" />
        <xsl:copy-of select="FileEntry | GenAttrList | ExclusiveArea | InterRunnableVariable" />
    </xsl:template>

    <!-- PortPrototype element rule -->
    <xsl:template match="PortPrototype">
        <PortPrototype>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink | GenAttrList" />
            <xsl:apply-templates select="SenderReceiverComSpec" />
            <xsl:copy-of select="ClientServerComSpec | PortAPIOption" />
        </PortPrototype>
    </xsl:template>

    <!-- SenderReceiverComSpec element rule -->
    <!-- remove 'FilterClass' attribute -->
    <xsl:template match="SenderReceiverComSpec">
        <SenderReceiverComSpec>
            <xsl:copy-of select="@AliveTimeout | @ResynchroTime | @SupportInvalidate | @QueueLength | @InitValueConstLink | @DataElementPrototypeLink" />
            <xsl:copy-of select="@UsesTxAcknowledge | @TxAckTimeOut | @TxAckTimeOutUnit" />
            <xsl:copy-of select="ATTRLink" />
        </SenderReceiverComSpec>
    </xsl:template>
    
    <!-- Composition element rule -->
    <xsl:template match="Composition">
        <Composition>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="CONTENT" />
            <xsl:copy-of select="ComponentPrototype" />
            <xsl:apply-templates select="PortConnector" />
        </Composition>
    </xsl:template>
    
    <!-- PortConnector element rule -->
    <xsl:template match="PortConnector">
        <PortConnector>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="DESC | ATTRLink | GenAttrList" />
            <xsl:apply-templates select="SenderReceiverConnectorComSpec" />
            <xsl:copy-of select="ClientServerConnectorComSpec" />
        </PortConnector>
    </xsl:template>
    
    <!-- SenderReceiverConnectorComSpec element rule -->
    <!-- Rename attributes -->
    <xsl:template match="SenderReceiverConnectorComSpec">
        <SenderReceiverConnectorComSpec>
            <xsl:copy-of select="@GUID" />
            <xsl:attribute name="MaxResponseTime">
                <xsl:value-of select="@MaxTransferTime"/>
            </xsl:attribute>
            <xsl:attribute name="MaxResponseTimeUnit">
                <xsl:value-of select="@TransferTimeUnit"/>
            </xsl:attribute>
            <xsl:copy-of select="@MaxJitter | @JitterTimeUnit | @DataElementPrototypeLink" />
            <xsl:copy-of select="node()" />
        </SenderReceiverConnectorComSpec>
    </xsl:template>
    
    
</xsl:stylesheet>
