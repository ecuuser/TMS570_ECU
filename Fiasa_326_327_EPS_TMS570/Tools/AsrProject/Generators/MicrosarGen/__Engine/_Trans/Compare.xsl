<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2004/07/xpath-functions" xmlns:xdt="http://www.w3.org/2004/07/xpath-datatypes">
	<!--$Source: _Trans/Header.xsl $-->
	<xsl:output method="html" encoding="Windows-1252"/>
	<xsl:template match="/">
		<HTML>
			<Head>
				<Title>Davinci Configurator Compare Report - [<xsl:value-of select="/Cfg-Report-Compare/General/ProjectName"/>]</Title>
				<style>
h4
	{mso-margin-top-alt:auto;
	margin-right:0cm;
	mso-margin-bottom-alt:auto;
	margin-left:0cm;
	mso-pagination:widow-orphan;
	mso-outline-level:4;
	font-size:10.0pt;
	font-family:"Times New Roman";
	font-weight:bold;}
* {
          font-family: Verdana, Helvetica, sans-serif;
          color:black;
          }

 /* Font Definitions */
 @font-face
	{font-family:"MS Mincho";
	panose-1:2 2 6 9 4 2 5 8 3 4;
	mso-font-alt:"ＭＳ 明朝";
	mso-font-charset:128;
	mso-generic-font-family:modern;
	mso-font-pitch:fixed;
	mso-font-signature:-1610612033 1757936891 16 0 131231 0;}
@font-face
	{font-family:Tahoma;
	panose-1:2 11 6 4 3 5 4 4 2 4;
	mso-font-charset:0;
	mso-generic-font-family:swiss;
	mso-font-pitch:variable;
	mso-font-signature:1627421319 -2147483648 8 0 66047 0;}
@font-face
	{font-family:"\@MS Mincho";
	panose-1:2 2 6 9 4 2 5 8 3 4;
	mso-font-charset:128;
	mso-generic-font-family:modern;
	mso-font-pitch:fixed;
	mso-font-signature:-1610612033 1757936891 16 0 131231 0;}
 /* Style Definitions */
 p.MsoNormal, li.MsoNormal, div.MsoNormal
	{mso-style-parent:"";
	margin:0cm;
	margin-bottom:.0001pt;
	mso-pagination:widow-orphan;
	font-size:12.0pt;
	font-family:"Times New Roman";
	mso-fareast-font-family:"MS Mincho";}
h1
	{mso-margin-top-alt:auto;
	margin-right:0cm;
	mso-margin-bottom-alt:auto;
	margin-left:0cm;
	text-align:center;
	mso-pagination:widow-orphan;
	mso-outline-level:1;
	background:#AD0829;
	font-size:16.0pt;
	font-family:"Times New Roman";
	color:white;
	font-weight:bold;}
h2
	{margin-top:30.0pt;
	margin-right:0cm;
	margin-bottom:15.0pt;
	margin-left:0cm;
	mso-pagination:widow-orphan;
	mso-outline-level:2;
	background:#DEDEDE;
	border:none;
	mso-border-bottom-alt:solid windowtext .75pt;
	padding:0cm;
	mso-padding-alt:0cm 0cm 4.0pt 0cm;
	font-size:14.0pt;
	font-family:"Times New Roman";
	font-weight:bold;}
h3
	{mso-margin-top-alt:auto;
	margin-right:0cm;
	mso-margin-bottom-alt:auto;
	margin-left:0cm;
	mso-pagination:widow-orphan;
	mso-outline-level:3;
	border:none;
	mso-border-bottom-alt:solid windowtext 3.0pt;
	padding:0cm;
	mso-padding-alt:0cm 0cm 3.0pt 0cm;
	font-size:12.0pt;
	font-family:"Times New Roman";
	color:#AD0829;
	font-weight:bold;}

p.MsoCommentText, li.MsoCommentText, div.MsoCommentText
	{mso-style-noshow:yes;
	margin:0cm;
	margin-bottom:.0001pt;
	mso-pagination:widow-orphan;
	font-size:10.0pt;
	font-family:"Times New Roman";
	mso-fareast-font-family:"MS Mincho";}
span.MsoCommentReference
	{mso-style-noshow:yes;
	mso-ansi-font-size:8.0pt;
	mso-bidi-font-size:8.0pt;}
a:link, span.MsoHyperlink
	{color:blue;
	text-decoration:underline;
	text-underline:single;}
a:visited, span.MsoHyperlinkFollowed
	{color:blue;
	text-decoration:underline;
	text-underline:single;}
p.MsoPlainText, li.MsoPlainText, div.MsoPlainText
	{margin-top:6.0pt;
	margin-right:0cm;
	margin-bottom:0cm;
	margin-left:0cm;
	margin-bottom:.0001pt;
	mso-pagination:widow-orphan;
	font-size:10.0pt;
	font-family:"Courier New";
	mso-fareast-font-family:"MS Mincho";}
p
	{mso-margin-top-alt:auto;
	margin-right:0cm;
	mso-margin-bottom-alt:auto;
	margin-left:0cm;
	mso-pagination:widow-orphan;
	font-size:10.0pt;
	font-family:"Times New Roman";
	mso-fareast-font-family:"MS Mincho";}
p.MsoCommentSubject, li.MsoCommentSubject, div.MsoCommentSubject
	{mso-style-noshow:yes;
	mso-style-parent:Kommentartext;
	mso-style-next:Kommentartext;
	margin:0cm;
	margin-bottom:.0001pt;
	mso-pagination:widow-orphan;
	font-size:10.0pt;
	font-family:"Times New Roman";
	mso-fareast-font-family:"MS Mincho";
	font-weight:bold;}
p.MsoAcetate, li.MsoAcetate, div.MsoAcetate
	{mso-style-noshow:yes;
	margin:0cm;
	margin-bottom:.0001pt;
	mso-pagination:widow-orphan;
	font-size:8.0pt;
	font-family:Tahoma;
	mso-fareast-font-family:"MS Mincho";}
p.small-text, li.small-text, div.small-text
	{mso-style-name:small-text;
	mso-margin-top-alt:auto;
	margin-right:0cm;
	mso-margin-bottom-alt:auto;
	margin-left:0cm;
	mso-pagination:widow-orphan;
	font-size:8.0pt;
	font-family:"Times New Roman";
	mso-fareast-font-family:"MS Mincho";}
span.SpellE
	{mso-style-name:"";
	mso-spl-e:yes;}
@page Section1
	{size:595.3pt 841.9pt;
	margin:70.85pt 70.85pt 2.0cm 70.85pt;
	mso-header-margin:35.4pt;
	mso-footer-margin:35.4pt;
	mso-paper-source:0;}
div.Section1
	{page:Section1;}
 /* List Definitions */
 @list l0
	{mso-list-id:845679751;
	mso-list-template-ids:-1979673718;}
@list l0:level1
	{mso-level-number-format:bullet;
	mso-level-text:;
	mso-level-tab-stop:36.0pt;
	mso-level-number-position:left;
	text-indent:-18.0pt;
	mso-ansi-font-size:10.0pt;
	font-family:Symbol;}
@list l0:level2
	{mso-level-tab-stop:72.0pt;
	mso-level-number-position:left;
	text-indent:-18.0pt;}
@list l0:level3
	{mso-level-tab-stop:108.0pt;
	mso-level-number-position:left;
	text-indent:-18.0pt;}
@list l0:level4
	{mso-level-tab-stop:144.0pt;
	mso-level-number-position:left;
	text-indent:-18.0pt;}
@list l0:level5
	{mso-level-tab-stop:180.0pt;
	mso-level-number-position:left;
	text-indent:-18.0pt;}
@list l0:level6
	{mso-level-tab-stop:216.0pt;
	mso-level-number-position:left;
	text-indent:-18.0pt;}
@list l0:level7
	{mso-level-tab-stop:252.0pt;
	mso-level-number-position:left;
	text-indent:-18.0pt;}
@list l0:level8
	{mso-level-tab-stop:288.0pt;
	mso-level-number-position:left;
	text-indent:-18.0pt;}
@list l0:level9
	{mso-level-tab-stop:324.0pt;
	mso-level-number-position:left;
	text-indent:-18.0pt;}
@list l1
	{mso-list-id:1221012278;
	mso-list-template-ids:-960570370;}
@list l1:level1
	{mso-level-number-format:bullet;
	mso-level-text:;
	mso-level-tab-stop:36.0pt;
	mso-level-number-position:left;
	text-indent:-18.0pt;
	mso-ansi-font-size:10.0pt;
	font-family:Symbol;}
ol
	{margin-bottom:0cm;}
ul
	{margin-bottom:0cm;}
</style>
			</Head>
			<Body bgcolor="#F7F7F7" lang="DE" link="blue" vlink="blue" style="tab-interval:35.4pt">
				<div class="Section1">
					<h1>Davinci Configurator Compare Report - <xsl:value-of select="/Cfg-Report-Compare/General/Module"/>
					</h1>
					<h4>General</h4>
					<ul type="disc">
						<li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;mso-list:l0 level1 lfo3;tab-stops:list 36.0pt;vertical-align:top">
							<span style="font-size:10.0pt">Execution TimeStamp: <xsl:value-of select="/Cfg-Report-Compare/General/TimeStamp"/>
							</span>
						</li>
						<li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;mso-list:l0 level1 lfo3;tab-stops:list 36.0pt;vertical-align:top">
							<span style="font-size:10.0pt">Tool: <xsl:value-of select="/Cfg-Report-Compare/General/Tool"/> (<xsl:value-of select="/Cfg-Report-Compare/General/ToolVersion"/>)
							</span>
						</li>
						<li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;mso-list:l0 level1 lfo3;tab-stops:list 36.0pt;vertical-align:top">
							<span style="font-size:10.0pt">Module: <xsl:value-of select="/Cfg-Report-Compare/General/Module"/>
							</span>
						</li>
						<li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;mso-list:l0 level1 lfo3;tab-stops:list 36.0pt;vertical-align:top">
							<span style="font-size:10.0pt">Self: <xsl:value-of select="/Cfg-Report-Compare/General/Self"/>
							</span>
						</li>
						<li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;mso-list:l0 level1 lfo3;tab-stops:list 36.0pt;vertical-align:top">
							<span style="font-size:10.0pt">Other: <xsl:value-of select="/Cfg-Report-Compare/General/Other"/>
							</span>
						</li>
					</ul>
					<h4>Project</h4>
					<ul type="disc">
						<li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;mso-list:l0 level1 lfo3;tab-stops:list 36.0pt;vertical-align:top">
							<span style="font-size:10.0pt">Name: <xsl:value-of select="/Cfg-Report-Compare/General/ProjectName"/>
							</span>
						</li>
						<li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;mso-list:l0 level1 lfo3;tab-stops:list 36.0pt;vertical-align:top">
							<span style="font-size:10.0pt">Folder: <xsl:value-of select="/Cfg-Report-Compare/General/ProjectFolder"/>
							</span>
						</li>
						<li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;mso-list:l0 level1 lfo3;tab-stops:list 36.0pt;vertical-align:top">
							<span style="font-size:10.0pt">Controller: <xsl:value-of select="/Cfg-Report-Compare/General/ProjectController"/>
							</span>
						</li>
						<li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;mso-list:l0 level1 lfo3;tab-stops:list 36.0pt;vertical-align:top">
							<span style="font-size:10.0pt">Revision: <xsl:value-of select="/Cfg-Report-Compare/General/ProjectRevision"/>
							</span>
						</li>
						<li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;mso-list:l0 level1 lfo3;tab-stops:list 36.0pt;vertical-align:top">
							<span style="font-size:10.0pt">Author: <xsl:value-of select="/Cfg-Report-Compare/General/ProjectAuthor"/>
							</span>
						</li>
						<li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;mso-list:l0 level1 lfo3;tab-stops:list 36.0pt;vertical-align:top">
							<span style="font-size:10.0pt">Company: <xsl:value-of select="/Cfg-Report-Compare/General/ProjectCompany"/>
							</span>
						</li>
					</ul>
				</div>
				<xsl:apply-templates/>
				<div style="mso-element:para-border-div;border:none;border-bottom:solid windowtext 3.0pt;
padding:0cm 0cm 3.0pt 0cm">
					<h3/>
				</div>
			</Body>
		</HTML>
	</xsl:template>
	<!-- ################################################## General ################################################## -->
	<xsl:template match="Statistics" name="stats" priority="1">
		<div style="mso-element:para-border-div;border:none;border-bottom:solid windowtext 3.0pt; padding:0cm 0cm 3.0pt 0cm">
			<h3>
				<xsl:value-of select="@Name"/>
			</h3>
		</div>
		<table class="MsoNormalTable" border="1" cellspacing="0" cellpadding="0" width="100%" style="width:90.0%;border-collapse:collapse;border:none;mso-border-left-alt: solid #999999 .5pt;mso-border-bottom-alt:solid #999999 .5pt;mso-border-right-alt: solid #999999 .5pt;mso-padding-alt:0cm 5.4pt 0cm 5.4pt;mso-border-insideh: .5pt solid #999999;mso-border-insidev:.5pt solid #999999">
			<tr style="mso-yfti-irow:0;mso-yfti-firstrow:yes">
				<td width="9%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt"/>
						</b>
					</p>
				</td>
				<td width="7%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">CONTAINER</span>
						</b>
					</p>
				</td>
				<td width="7%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">BOOL</span>
						</b>
					</p>
				</td>
				<td width="7%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">INTEGER</span>
						</b>
					</p>
				</td>
				<td width="7%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">FLOAT</span>
						</b>
					</p>
				</td>
				<td width="7%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">STRING</span>
						</b>
					</p>
				</td>
				<td width="7%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">ENUMERATION</span>
						</b>
					</p>
				</td>
				<td width="7%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">FUNCTION NAME</span>
						</b>
					</p>
				</td>
				<td width="7%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">LINKER SYMBOL</span>
						</b>
					</p>
				</td>
				<td width="7%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">SYMBOLIC NAME REF</span>
						</b>
					</p>
				</td>
				<td width="7%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">REFERENCE</span>
						</b>
					</p>
				</td>
				<td width="7%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">CHOICE REF</span>
						</b>
					</p>
				</td>
				<td width="7%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">FOREIGN REF</span>
						</b>
					</p>
				</td>
				<td width="7%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">INSTANCE REF</span>
						</b>
					</p>
				</td>
				<td width="7%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">Sum</span>
						</b>
					</p>
				</td>
				<td width="7%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt"/>
						</b>
					</p>
				</td>
			</tr>
			<xsl:call-template name="StatisticRows"/>
		</table>
	</xsl:template>
	<xsl:template name="StatisticRows">
		<xsl:for-each select="Row">
			<tr style="mso-yfti-irow:1">
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxConfig"/>
						</span>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxContainers"/>
						</span>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxBools"/>
						</span>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxIntegers"/>
						</span>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxFloats"/>
						</span>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxStrings"/>
						</span>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxEnums"/>
						</span>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxFuncs"/>
						</span>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxLinker"/>
						</span>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxSymbolicsRefs"/>
						</span>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxRefs"/>
						</span>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxChoiceRefs"/>
						</span>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxForeignRefs"/>
						</span>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxInstanceRefs"/>
						</span>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxSum"/>
						</span>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxRemark"/>
						</span>
					</p>
				</td>
			</tr>
		</xsl:for-each>
	</xsl:template>
	<xsl:template match="General" priority="1"/>
	<xsl:template match="Differences" priority="1">
		<div style="mso-element:para-border-div;border:none;border-bottom:solid windowtext 3.0pt; padding:0cm 0cm 3.0pt 0cm">
			<h3>
				<xsl:value-of select="@Name"/>
			</h3>
		</div>
		<table class="MsoNormalTable" border="1" cellspacing="0" cellpadding="0" width="100%" style="width:90.0%;border-collapse:collapse;border:none;mso-border-left-alt: solid #999999 .5pt;mso-border-bottom-alt:solid #999999 .5pt;mso-border-right-alt: solid #999999 .5pt;mso-padding-alt:0cm 5.4pt 0cm 5.4pt;mso-border-insideh: .5pt solid #999999;mso-border-insidev:.5pt solid #999999">
			<tr style="mso-yfti-irow:0;mso-yfti-firstrow:yes">
				<td width="100" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">Difference</span>
						</b>
					</p>
				</td>
				<td width="100" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">Type</span>
						</b>
					</p>
				</td>
				<td width="20%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">Name<br/>
							</span>
							<span style="font-size:7.0pt">Definition Reference<br/>
							Object Reference</span>
						</b>
					</p>
				</td>
				<td width="35%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">Self Value</span>
						</b>
					</p>
				</td>
				<td width="35%" valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-left-alt:solid #999999 .5pt;mso-border-bottom-alt:  solid #999999 .5pt;mso-border-right-alt:solid #999999 .5pt;background:#EEEEEE;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<b>
							<span style="font-size:10.0pt">Other Value</span>
						</b>
					</p>
				</td>
			</tr>
			<xsl:call-template name="Changes"/>
		</table>
	</xsl:template>
	<xsl:template name="Changes">
		<xsl:for-each select="Row">
			<tr style="mso-yfti-irow:1">
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxDiffType"/>
						</span>
					</p>
				</td>
						<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxTypeIcon"/>
						</span>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxClass"/>
						</span>
						<br/>
						<xsl:for-each select="nxSelfValue">
							<span style="font-size:7.0pt">
								<xsl:value-of select="@DefinitionReference"/>
								<br/>
								<xsl:value-of select="@ObjectReference"/>
								<br/>
							</span>
						</xsl:for-each>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxSelfValue"/>
						</span>
					</p>
				</td>
				<td valign="top" style="border:solid #999999 1.0pt;  border-top:none;mso-border-top-alt:solid #999999 .5pt;mso-border-alt:solid #999999 .5pt;  padding:0cm 12.0pt 0cm 5.4pt">
					<p class="MsoNormal">
						<span style="font-size:10.0pt">
							<xsl:value-of select="nxOtherValue"/>
						</span>
					</p>
				</td>
			</tr>
		</xsl:for-each>
	</xsl:template>
	<xsl:template match="*" priority="0.1">
		<xsl:apply-templates/>
	</xsl:template>
</xsl:stylesheet>
