<CFSET todaysdate="#DateFormat(NOW(),'mm/dd/yyyy')#">
<CFSET thisyear="#DateFormat(NOW(),'yyyy')#">
<CFPARAM name="url.reviewID" default="0">



 

<!-- THE REVIEW -->
<cfquery name="qresponseinfo" datasource="ASIfilereview">
SELECT *
FROM review 
ORDER BY reviewID DESC 
 </cfquery>
 


 
 

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
        "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
	<title>Response DELETE</title>
<!-- stylesheet -->
<LINK REL=stylesheet href="../style_workarea.css" type="text/css">	

<!-- popup  script -->
<script language="JavaScript" type="text/javascript">

function newwin(name,x,y) {
        var n=window.open(name,"new","toolbar=yes,menubar=yes,resizable=yes,scrollbars=yes,status=yes,width="+x+",height="+y);
        n.location.href=name
	n.focus()
}
</script>

</head>


<body bgcolor="#333333">
<center>

<!--- TABLE for Rewiew status --->
<table width="800" cellspacing="0" cellpadding="0" align="left" bgcolor="#889999">
<tr>
<td width="100" colspan="2"><img src="../images/banner_prop-tool.gif" alt="" width="800" height="53"></td></tr>




<tr>
<!-- content area -->
<td>


<table width="100%">
<tr>
<td bgcolor="#889999" width="650"  valign="top" align="left"  style="padding:10px">

<div style="margin-left:30px" >
<b class="heading" style="color:#ffffff">GSA-NCR File Analysis </b>
<br><span class="text2" style="color:#ffffff">
</span>
</DIV>

<!--- links --->
<div align="right" class="small" style="margin-right:20px">
<a href="javascript:newwin('navigationbar.cfm',400,500)">links | info | help |</a>
</div>

<br>



<span class="section">Review Status</span>
<br>
<span class="instructions">
You can complete uncompleted areas by clicking on "incomplete" link in your review row. 
<br>You can edit finished sections by clicking on "complete" link in your review row. </span>

<br><br>

<!--- Navigation --->
<CFINCLUDE TEMPLATE="_nav-results.cfm">
<br><br>


<!-- Table to align input boxes and text -->
<table width="95%" bgcolor="#006666" cellspacing="1" cellpadding="2">
<tr>

<th align="center" class="notes" bgcolor="#cccccc">delete</th>
<th align="center" class="notes" bgcolor="#cccccc">reviewID</th>
<th align="center" class="notes" bgcolor="#cccccc">reviewer</th>
<th align="center" class="notes" bgcolor="#cccccc">responseID</th>
<th align="center" class="notes" bgcolor="#cccccc">questionID</th>
<th align="center" class="notes" bgcolor="#cccccc">response</th>
</td></tr>


<CFOUTPUT query="qresponseinfo">
<tr>
<td align="center" class="text" bgcolor="##ffffff"><img src="images/delete.gif" width="50" height="20"></td>
<td align="center" class="text" bgcolor="##ffffff">#qresponseinfo.reviewID#</td>
<td align="center" class="small" bgcolor="##ffffff">#qresponseinfo.reviewer#</td>
<td align="center" class="small" bgcolor="##ffffff">#qresponseinfo.responseID#</td>
<td align="center" class="small" bgcolor="##ffffff">#qresponseinfo.questionID#</td>
<td align="center" class="small" bgcolor="##ffffff">#qresponseinfo.response#</td>




</tr>

</cfoutput>

</table>







</td>
</tr>

<!-- footer -->
<TR>
<TD  align=right valign=bottom>

<TABLE WIDTH="100%" cellpadding="5">
<tr>
<td align="right">
<font color="#cccccc" size=5 style="font-size:12pt" face="arial">
Procurement sensitive information.
<br>
<b><CFOUTPUT>#thisyear#</CFOUTPUT> &#169; A c q u i s i t i o n &#160; S o l u t i o n s &#174; </b>
</td>

<td align="center" width="100">
<a href="../../asi/INTRANET/index.html">
<img src="../images/hex.gif" alt="Acquisition Solutions&#174 " width="86" height="77"  border="0"  valign=bottom></a>
</td>
</tr>
</table>


</td>
</tr>



</table>
</td>
</tr>
</table>
</center>
</body>
</html>
