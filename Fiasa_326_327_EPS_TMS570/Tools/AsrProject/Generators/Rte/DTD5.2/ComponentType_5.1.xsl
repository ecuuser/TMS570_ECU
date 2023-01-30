<?xml version="1.0" encoding="ISO-8859-1" standalone="no"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD5.2\DVW.DTD"/>

  <!-- Root element rule -->
  <xsl:template match="/">
        <ComponentType>
            <xsl:apply-templates select="ComponentType"/>
        </ComponentType>
  </xsl:template>
  
  <!-- ComponentType element rule -->
  <!-- Don't set DTD version to 5.2, ItemConvert required -->
  <xsl:template match="ComponentType">
        <xsl:copy-of select="@CMVersion | @CMState | @GUID | @Version | @RO" />
        <xsl:attribute name="DTDVersion">5.1</xsl:attribute>
        <xsl:copy-of select="@SupportMI | @ImplCodeType | @BSWModule | @ECUAbstraction" />
	    <xsl:copy-of select="NAME | LONGNAME | DESC"/>
	    <xsl:apply-templates select="ATTRLink"/>
	    <xsl:copy-of select="CONTENT"/>
	    <xsl:apply-templates select="Runnable"/>
	    <xsl:copy-of select="Application | SensorActuator | Service"/>
        <xsl:apply-templates select="Composition"/>
	    <xsl:copy-of select="Calibration"/>
        <xsl:apply-templates select="PortPrototype"/>
        <xsl:copy-of select="FileEntry | GenAttrList | ExclusiveArea | InterRunnableVariable | CalibrationParameter | PerInstanceMemory"/>
  </xsl:template>
  
  <!-- Composition element rule -->
  <xsl:template match="Composition">
        <Composition>
            <xsl:copy-of select="@*"/>
            <xsl:copy-of select="CONTENT | ComponentPrototype"/>
            <xsl:apply-templates select="PortConnector"/>
        </Composition>
  </xsl:template>
  
  <!-- PortConnector element rule: remove function net links -->
  <xsl:template match="PortConnector">
        <PortConnector>
            <xsl:copy-of select="@GUID | @ReceiverPortLink | @TransmitterPortLink | @ReceiveCompPrototypeLink | @ReceiveCompTypeLink | @TransmitCompPrototypeLink | @TransmitCompTypeLink"/>
	        <xsl:copy-of select="DESC"/>
	        <xsl:apply-templates select="ATTRLink"/>
	        <xsl:copy-of select="GenAttrList | SenderReceiverConnectorComSpec | ClientServerConnectorComSpec"/>
        </PortConnector>
  </xsl:template>
  
  <!-- Runnable element rule: remove function net links -->
  <xsl:template match="Runnable">
        <Runnable>
            <xsl:copy-of select="@GUID | @CanBeInvokedConcurrently | @Symbol"/>
	        <xsl:copy-of select="NAME | LONGNAME | DESC"/>
	        <xsl:apply-templates select="ATTRLink"/>
	        <xsl:copy-of select="Trigger | RunnableDataAccess | GenAttrList | OperationAccess | ExclusiveAreaAccess | InterRunnableVariableAccess | ModeSwitchAccess"/>
        </Runnable>
  </xsl:template>
  
  <!-- PortPrototype element rule: remove function net links -->
  <xsl:template match="PortPrototype">
        <PortPrototype>
            <xsl:copy-of select="@GUID | @IsInput | @PortInterfaceLink"/>
	        <xsl:copy-of select="NAME | LONGNAME | DESC"/>
	        <xsl:apply-templates select="ATTRLink"/>
          <xsl:copy-of select="GenAttrList"/>
            <xsl:apply-templates select="SenderReceiverComSpec"/>
          <xsl:copy-of select="ClientServerComSpec | ModeSwitchComSpec | PortAPIOption"/>
        </PortPrototype>
  </xsl:template>

  <!-- SenderReceiverComSpec element rule: remove ResynchroTime -->
  <xsl:template match="SenderReceiverComSpec">
    <SenderReceiverComSpec>
      <xsl:copy-of select="@GUID | @AliveTimeout | @SupportInvalidate | @HandleInvalid | @QueueLength | @InitValueConstLink | @DataElementPrototypeLink | @UsesTxAcknowledge | @TxAckTimeOut | @TxAckTimeOutUnit"/>
      <xsl:copy-of select ="node()"/>
    </SenderReceiverComSpec>
  </xsl:template>

  <!-- AttrLink element rule -->
    <xsl:template match="ATTRLink">
        <xsl:choose>
            <xsl:when test="@LinkName[.='DeviceAccessor' or .='Function' or .='FunctionPort' or .='FunctionTrigger' or .='ProxyReceiverPort' or .='ProxyTransmitterPort']">
            </xsl:when>
            <xsl:otherwise>
                <ATTRLink>
                    <xsl:copy-of select="@*" />
                </ATTRLink>
            </xsl:otherwise>
        </xsl:choose>                
    </xsl:template>

</xsl:stylesheet>