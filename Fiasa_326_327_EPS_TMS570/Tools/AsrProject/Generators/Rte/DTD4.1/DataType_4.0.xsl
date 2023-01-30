<?xml version="1.0" encoding="ISO-8859-1" standalone="no" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" version="1.0" encoding="ISO-8859-1" standalone="no" doctype-system="..\DTD4.1\DVW.DTD" />
    
    <!-- Retain white space within all elements -->
    <xsl:preserve-space elements="*" />
    
    <!-- Root element rule -->
    <xsl:template match="/">
        <DataType>
            <xsl:apply-templates select="DataType" />
        </DataType>
    </xsl:template>
    
    <!-- DataType element rule -->
    <!-- DO NOT Set DTD version to 4.1, call of item convert required  -->
    <!-- Remove the BaseType of enumeration types; copy all settings -->
    <xsl:template match="DataType">
        <xsl:copy-of select="@*" />
        <xsl:copy-of select="NAME | LONGNAME | DESC | ATTRLink" />
        <xsl:apply-templates select="PrimitiveType" />
        <xsl:copy-of select="ComplexType | GenAttrList" />
    </xsl:template>

    <!-- PrimitiveType element rule -->
    <xsl:template match="PrimitiveType">
        <PrimitiveType>
            <xsl:copy-of select="@*" />
            <xsl:copy-of select="BooleanPrimitive | IntegerPrimitive | RealPrimitive | OpaquePrimitive" />
            <xsl:apply-templates select="EnumerationPrimitive" />
        </PrimitiveType>
    </xsl:template>

    <!-- Correct Limits for 32-bit integer -->
    <xsl:template match="EnumerationPrimitive">
        <EnumerationPrimitive>
            <xsl:copy-of select="@GUID" />
            <xsl:attribute name="Old_DataTypeLink">DataType</xsl:attribute>
            EnumerationElement
            <xsl:apply-templates select="ATTRLink" />
            <xsl:copy-of select="EnumerationElement" />
        </EnumerationPrimitive>
    </xsl:template>
    
    <xsl:template match="ATTRLink">
        <ATTRLink>
            <xsl:copy-of select="@LinkGUID | @LinkVersion | @LinkChildGUID | @LinkType" />
            <xsl:attribute name="LinkName">Old_DataType</xsl:attribute>
        </ATTRLink>
    </xsl:template>
    
</xsl:stylesheet>
