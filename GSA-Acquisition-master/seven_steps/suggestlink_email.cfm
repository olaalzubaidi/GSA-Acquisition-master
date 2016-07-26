<CFPARAM name="form.email" default="rrogin@acqsolinc.com">


<style>
.heading {font-size:20pt;font-family:georgia,serif;color:#ffcc66}
.text {font-size:10pt;font-family:arial}
.small {font-size:8pt;font-family:arial}
.reverse {color:#ffffff}
.box {border-style:solid;border-color:#ffcc66;background-color:#ffffcc;height:500px}
</style>



<CFMAIL
to = "dorsinger@acqsolinc.com" 
from = "#form.email#" 
subject = "Seven Steps Suggest-a-Link" 
server = "mail.acqsolinc.com" 
type="HTML"
>


<b class="heading">
<font color="##000099" face="arial" size="4">Seven Steps Suggest-a-Link</b></font>



<p>
<font color="##000066" face="arial" size="2"><b>Suggested Link:</b></font>
<font color="##333333" face="arial" size="1">#form.url#</font>

<p>
<font color="##000066" face="arial" size="2"><b>Description:</b></font>
<font color="##333333" face="arial" size="2">#form.description#</font>

<p>
<font color="##000066" face="arial" size="2"><b>Suggested Location:</b></font>
<font color="##333333" face="arial" size="2">#form.where#</font>

<p>
<font color="##000066" face="arial" size="2"><b>Name:</b></font>
<font color="##333333" face="arial" size="2">#form.name#</font>

<p>
<font color="##000066" face="arial" size="2"><b>Email address:</b></font>
<font color="##333333" face="arial" size="2">#form.email#</font>


</cfmail>


<html>
<body bgcolor="#000066">
<center>
<p class="box" valign="middle">
<font color="##000066" face="arial" size="4">Your email has been sent. 

<br><br>
<i>Thank you for your suggestion!</i>
</font>

</center>
</body>
</html>