<!--<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">-->
<!--    <xsl:template match="/root">-->
<!--        <xsl:for-each select="part">-->
<!--            <xsl:variable name="part" select="@id"/>-->
<!--            <xsl:for-each select="note">-->
<!--                <parameter>-->
<!--                    <xsl:attribute name="id">scaleTunePart<xsl:value-of select="$part"/><xsl:value-of select="@id"/>-->
<!--                    </xsl:attribute>-->
<!--                    <xsl:attribute name="name">Scale Tune Part-->
<!--                        <xsl:value-of select="$part"/>-->
<!--                        <xsl:value-of select="@id"/>-->
<!--                    </xsl:attribute>-->
<!--                    <xsl:attribute name="offsetAddress">-->
<!--                        <xsl:value-of select="@offsetAddress"/>-->
<!--                    </xsl:attribute>-->
<!--                    <xsl:attribute name="type">Number</xsl:attribute>-->
<!--                </parameter>-->
<!--            </xsl:for-each>-->
<!--        </xsl:for-each>-->
<!--    </xsl:template>-->
<!--</xsl:stylesheet>-->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/root">
    <xsl:variable name="notes" select="tokenize(notes, ',')"/>
    <xsl:variable name="parts" select="tokenize(parts, ',')"/>
    <xsl:for-each select="$parts">
        <xsl:variable name="part" select="."/>
        <xsl:for-each select="$notes">
            <xsl:variable name="note" select="."/>
            <xsl:variable name="offset" select="string(format-number(($part - 1) * 12 + position() + 35, '0x##'))"/>
            <parameter>
                <xsl:attribute name="id">scaleTunePart<xsl:value-of select="$part"/><xsl:value-of select="$note"/>
                </xsl:attribute>
                <xsl:attribute name="name">Scale Tune Part
                    <xsl:value-of select="$part"/>
                    <xsl:value-of select="$note"/>
                </xsl:attribute>
                <xsl:attribute name="offsetAddress">
                    <xsl:value-of select="$offset"/>
                </xsl:attribute>
                <xsl:attribute name="type">Number</xsl:attribute>
            </parameter>
        </xsl:for-each>
    </xsl:for-each>
</xsl:template>
</xsl:stylesheet>