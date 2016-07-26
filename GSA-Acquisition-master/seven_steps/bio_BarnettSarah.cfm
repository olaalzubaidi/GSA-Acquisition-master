<cfquery name="qpeople" datasource="ASI_personnel">
SELECT lastname, firstname, middlename, jobtitle, streetaddress, businessphone, cellphone, fax, email, city, state , zip, jobsite, email,altemail,inactive
FROM ASIpersonnel
WHERE firstname = 'Sarah' AND lastname = 'Barnett'
ORDER BY lastname ASC
</cfquery>



<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN"
			"http://www.w3.org/TR/REC-html40/loose.dtd">
<html>
<head>
<META NAME="robots" content="noindex">
<title>ASI Team</title><meta http-equiv="Page-Enter" content="blendTrans(Duration-1.0)"> 


<!-- popup login script -->
<script language="JavaScript" type="text/javascript">

function newwin(name,x,y) {
        var n=window.open(name,"new","menubar=no,resizable=yes,scrollbars=yes,status=yes,width="+x+",height="+y);
        n.location.href=name
	n.focus()
}
</script>


<!-- stylesheet -->
<LINK REL=stylesheet href="style_bios.css" type="text/css">	


</head>
<body bgcolor="#333333" link="#006633" vlink="#006633">

<table border="0" cellpadding="0" cellspacing="0" width="800">

<!-- BANNER -->
<tr>
<td colspan=3 valign=top>
<img src="images/banner3.gif" width=800 height=51 alt="Acquisition Solutions&#174, intranet"></td></tr>



<tr>
<TD align="center" VALIGN="TOP" bgcolor="#778888" class="text" width="137" >
<!-- LEFT NAVIGATION -->
<CFINCLUDE TEMPLATE="_bio-nav.cfm">
</td>




<!-- *********************************************** -->
<!-- *********************************************** -->
<td colspan="1" align="right" valign="top" height="700" >
<!-- CENTER SECTION  -->
<table width="100%" cellpadding="0" cellspacing="0" border="0"  height="100%">
<tr>
<td colspan=2 align=left valign="top" BGCOLOR="#223333" width="100%">

<!-- UPPER TABLE W/ CONTACT INFO AND PHOTO -->

<table cellpadding="6" cellspacing="0" border="0" width="100%">
<tr>
<td bgcolor="#223333" rowspan=3 valign="top">


<CFOUTPUT QUERY="qpeople">
<!-- PHOTO -->
<img src="photos/asi/#qpeople.lastname##qpeople.firstname#.jpg" alt="#qpeople.firstname# #qpeople.lastname#" width="114" height="144" vspace="3" hspace="3" align="left"></td>

<!-- space --><td bgcolor="223333" height="10" ></td>
</tr><tr>


<td bgcolor="aabbbb" width="100%" >
<!-- NAME -->
<span class="name"><font color="ffffff">#qpeople.firstname# #qpeople.middlename# #qpeople.lastname#</font></span>

<font  size=2 face=arial color="000066">

<!-- TITLE -->
<br><font size=2 color="ffffff"><i>#qpeople.jobtitle#</i></font>

<!-- PHONE -->
<p>
<font color="ffffff">work: </font>  #qpeople.businessphone#  &nbsp;&nbsp;
<font color="ffffff">cell: </font>#qpeople.cellphone#   &nbsp;&nbsp;


<CFIF #qpeople.fax# IS NOT "">
<font color="ffffff">fax: </font> #qpeople.fax#
</CFIF>


<!-- EMAIL -->
<br><font color="ffffff">email:</font>
<a href="mailto:#qpeople.email#">#qpeople.email#</a>

<!-- BACKUP EMAIL -->
<br><font color="ffffff">alternate email: </font>
<a href="mailto:#qpeople.altemail#">#qpeople.altemail# </a>

<!--  ADDRESS -->
<br><font color="ffffff">address:</font> #qpeople.streetaddress# #qpeople.city#, #qpeople.state# #qpeople.zip#

</font>
</td>
</tr>
</CFOUTPUT>
<!-- SPACER -->
 <tr><td bgcolor="#223333" height="10">&nbsp;</td>
</tr>


</table>

</td></tr>


<!-- ************** PUT BIO INFORMATION HERE ************ -->

<tr>
<TD width=33 height="100%"  bgcolor="#223333" valign="top">
<table cellpadding="5" cellspacing="0" border="0">

<!--AT ASI -->
<tr  bgcolor="#223333">

<TD  valign="top" align="right">
<b class="heading"><font color="#99aa88">at ASI&nbsp;&nbsp;</font></b>
<BR>
<img src="images/spacer.gif" alt="" width="100" height="1"></TD>

<td class="text" width="363"  valign="top" align="left"> 
<font color="#ffffff">
-----
</font>

</td>
</tr>

<!-- BIO -->
<tr bgcolor="#223333">
<td valign="top" align="right" WIDTH="100"><b class="heading">
<font color="#99aa88">bio&nbsp;&nbsp;</font></b><BR>
<img src="images/spacer.gif" alt="" width="100" height="1"></TD>

<td class="text" width="363"  valign="top" bgcolor="#223333" align="left"> 
<font color="#ffffff">
-----
<p>

</font>
</td>
</tr>

<!-- HOBBIES -->
<tr  bgcolor="#223333">

<TD  valign="top" align="right">
<b class="heading"><font color="#99aa88">hobbies&nbsp;&nbsp;</font></b>
<BR>
<img src="images/spacer.gif" alt="" width="100" height="1"></TD>

<td class="text" width="363"  valign="top" align="left"> 
<font color="#ffffff">
-----
</font>
<BR><BR>
</td>
</tr>


<!--FAMILY -->
<tr  bgcolor="#223333">

<TD  valign="top" align="right">
<b class="heading"><font color="#99aa88">family&nbsp;&nbsp;</font></b>
<BR>
<img src="images/spacer.gif" alt="" width="100" height="1"></TD>

<td class="text" width="363"  valign="top" align="left"> 
<font color="#ffffff">
-----
</font>
<BR><BR>
</td>
</tr>




 <!-- schooling -->
<!-- <tr  bgcolor="#223333">

<TD  valign="top" align="right">
<b class="heading"><font color="#99aa88">schooling&nbsp;&nbsp;</font></b>
<BR>
<img src="images/spacer.gif" alt="" width="100" height="1"></TD>

<td class="text" width="363"  valign="top" align="left"> 
<font color="#ffffff">------------ </font>
<BR><BR>
</td>
</tr> </font>
<BR><BR>
</td>
</tr>  -->

<!-- PHOTOS -->

<tr  bgcolor="#223333">
<TD valign="top" align="right">
<b class="heading"><font color="#99aa88">photos&nbsp;&nbsp;</font></b>
<br><br>
<font color="#ffffff"><i>-</i></font></TD>

<td class="text" width="363"  valign="top" align="center">

<br>
<!-- spacer -->
<img src="images/spacer.gif" width="363" height="1" alt="">

<br></td>
</tr>

<tr  bgcolor="#223333">
<TD valign="top" align="right">

<font color="#ffffff"><i>- </i></font></TD>

<td class="text" width="363"  valign="top" align="center">



</td>
</tr>


</table>
<!-- END OF CENTER TABLE --></td>


<!-- ************************************************** -->
<!--  FAVORITES -->
<td  valign="top" width=160  height="100%" bgcolor="#aabbbb"  >
<table cellpadding="5" cellspacing="0" border="0" class="text" >
<tr>
<td colspan=2 width="160" align="center">
<CFOUTPUT QUERY="qpeople">
<b class="heading-fav" style="font-variant:caps">#qpeople.firstname#'s Favorites</b></cfoutput>
<br>
</td></tr>

<tr>
<td valign="top" align="right" class="small"><font color="#FFFFFF">dinner:</font></td>
<td class="text" align="left"> -----
</td>
</tr>


<tr>
<td valign="top" align="right" class="small"><font color="#FFFFFF">book:</font></td>
<td class="text" align="left"> -----
</td>
</tr>


<tr>
<td valign="top" align="right" class="small"><font color="#FFFFFF">movie:</font></td>
<td class="text" align="left">-----</td>
</tr>
<tr>
<td valign="top" align="right" class="small"><font color="#FFFFFF">sport:</font></td>
<td class="text" align="left">-----</td></tr>

<tr>
<td valign="top" align="right" class="small"><font color="#FFFFFF">color:</font></td>
<td class="text" align="left"> ---
</td></tr>

<tr>
<td valign="top" align="right" class="small"><font color="#FFFFFF">hobby:</font></td>
<td>-----</td></tr>


<tr>
<td valign="top" align="right" class="small"><font color="#FFFFFF">music:</font> </td>
<td class="text" align="left"> ----
</td></tr>


<tr>
<td valign="top" align="right" class="small"><font color="#FFFFFF">restaurant:</font></td>
<td class="text" align="left">----
</td>
</tr>


<tr>
<td valign="top" align="right" class="small"><font color="#FFFFFF">quote:</font></td>
<td class="text" align="left">-----</b>
</td>
</tr>



</table>
</td>
</tr>
</table>
</td></tr>
</table>
</body>
</html>