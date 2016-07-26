<?php
$table_contents = acquisition_browse_far_internal($processed_vars['far_part_subpart']);
drupal_set_title('Federal Acquisition Regulation (FAR)');
drupal_add_js('misc/jquery.js');
$curpdfinfo = acquisition_central_current_downlodable_file('far','pdf');
$curhtmlinfo = acquisition_central_current_downlodable_file('far','html');
$curfarinfo = acquisition_central_get_curinfo('FAR');
?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/html">
<head>
    <title>Acquisition.gov</title>
    <script type="text/javascript">
        function iframeLoaded() {
            var iFrameID = document.getElementById('browse');
            if(iFrameID) {
                // here you can make the height, I delete it first, then I make it again
                iFrameID.height = "";
                iFrameID.height = iFrameID.contentWindow.document.body.scrollHeight + "px";
            }
        }
        function browserurlchange(url){
            var stateObj = { foo: "bar" };
            history.pushState(stateObj, "page 2", '/?q='+url);
        }

        function getIframeSrc() {
            var iframeUrl = document.getElementById("browse").contentWindow.location.href;
            window.location= "/downloadcurrentzip?url="+encodeURIComponent(iframeUrl);
        }
        function closePrint () {
            document.body.removeChild(this.__container__);
        }

        function setPrint () {
            this.contentWindow.__container__ = this;
            this.contentWindow.onbeforeunload = closePrint;
            this.contentWindow.onafterprint = closePrint;
            this.contentWindow.focus(); // Required for IE
            this.contentWindow.print();
        }

        function printPage (sURL) {
            var oHiddFrame = document.createElement("iframe");
            oHiddFrame.onload = setPrint;
            oHiddFrame.style.visibility = "hidden";
            oHiddFrame.style.position = "fixed";
            oHiddFrame.style.right = "0";
            oHiddFrame.style.bottom = "0";
            oHiddFrame.src = sURL;
            document.body.appendChild(oHiddFrame);
        }
        function printCurrentPage(){
            var iframeUrl = document.getElementById("browse").contentWindow.location.href;
            printPage(iframeUrl);
        }

        //$(document).ready(function() {
        //    $("li.menu-path-browsefar").click(function() {
        //        $("#bottom-sticky").hide();
        //    });
        //    $("#browsefarinternal").click(function() {
        //        $("#bottom-sticky").hide();
        //    });
        //    $("a[href^='/sites/default/files']").click(function() {
        //        $("#bottom-sticky").show();
        //    });
        //    $("#browse").click(function() {
        //        $("#bottom-sticky").show();
        //    });
        //});
        var currFFZoom = 1;
        var currIEZoom = 100;

        function plus(){
            //alert('sad');
            var step = 0.02;
            currFFZoom += step;
            $('body').css('MozTransform','scale(' + currFFZoom + ')');
            var stepie = 2;
            currIEZoom += stepie;
            $('body').css('zoom', ' ' + currIEZoom + '%');

        };
        function minus(){
            //alert('sad');
            var step = 0.02;
            currFFZoom -= step;
            $('body').css('MozTransform','scale(' + currFFZoom + ')');
            var stepie = 2;
            currIEZoom -= stepie;
            $('body').css('zoom', ' ' + currIEZoom + '%');
        };

    </script>
</head>

<body>
<!--<div id="content-wrapper">-->
<!--    <div id="main-content-internal">-->
        <!--Content Region-->
        <div id="parts-column">
            <div id="parts-column-header">
                <h3>Far Parts</h3>
            </div>
            <div id="parts-wrapper">
                <p><a id='browsefarinternal' href='browsefarinternal' target='browse'>Index</a></p>
                <p><a href="/sites/default/files/current/far/html/FARMTOC.html" target="browse">Table of Contents</a></p>
                <?php
                print $processed_vars['far_left_navigation'];
                ?>
            </div>
        </div>
<div id="bottom-sticky"><a id="download" href='#' onclick='getIframeSrc()' title="Download">Download</a>&nbsp;<a id='print' href='#' onclick='printCurrentPage()' title="print">Print</a>&nbsp;<a id='search' href='/?q=search/site/*&f[0]=bundle%3Afar' title="search">Search</a>
</div>
<!--<div id="download-entire"><p>FAC Number/Effective Date:&nbsp;&nbsp;&nbsp;<span class=''>FAC 2005-83-3/11-01-2015</span> - Download Entire FAR - <a id="download-html" title='File Size:<?=$curhtmlinfo['filesize']?>' href='<?=$curhtmlinfo['filename']?>'>HTML</a>  <a id="download-pdf" title='File Size:<?=$curpdfinfo['filesize']?>' href='<?=$curpdfinfo['filename']?>'> PDF</a></p>&nbsp;<span onclick="plus();" style="background-color:#27324b;color:white;" title="Click here to increase the font size">A+</span>&nbsp;&nbsp;<span onclick="minus();"  style="background-color:#27324b;color:white;"  title="Click here to decrease the font size">A-</span>-->
<div id="download-entire"><p>FAC Number/Effective Date:&nbsp;&nbsp;&nbsp;<span class=''><?=$curfarinfo['cur_version']?>/<?=$curfarinfo['cur_effective_date']?></span> - Download Entire FAR - <a id="download-html" title='File Size:<?=$curhtmlinfo['filesize']?>' href='<?=$curhtmlinfo['filename']?>'>HTML</a>  <a id="download-pdf" title='File Size:<?=$curpdfinfo['filesize']?>' href='<?=$curpdfinfo['filename']?>'> PDF</a></p>&nbsp;<span onclick="plus();" style="background-color:#27324b;color:white;" title="Click here to increase the font size">A+</span>&nbsp;&nbsp;<span onclick="minus();"  style="background-color:#27324b;color:white;"  title="Click here to decrease the font size">A-</span>
</div>
        <?php if($processed_vars['far_page'] != '' && (drupal_get_path_alias($_GET['q']) != 'browse/far')){ ?>
        <iframe id='browse' onload="iframeLoaded()" name='browse'  width='100%' src="<?php print $processed_vars['far_page'];?>?&searchTerms=<?=isset($_GET['searchTerms'])?html_entity_decode($_GET['searchTerms']):''?>
" height="1000px">the related document</iframe><div id='backtop' style="background-color: #d7f1f8;color: black;border-radius: 2px;    padding: 3px;color:#5c5c5c;display: block;float: right;"><a href="#downloadarea" onclick="parent.scrollTo(0,0);top.frames['browse'].window.scrollTo(0,0);">Go to the top</a></div>
        <?php } else{ ?>
        <iframe id='browse1' title="browsefar"  name='browse'  width='100%' src='browsefarinternal' height="1000px">the related document  </iframe>
<div id='backtop' style="background-color: #d7f1f8;color: black;border-radius: 2px;    padding: 3px;color:#5c5c5c;display: block;float: right;"><a href="#downloadarea" onclick="parent.scrollTo(0,0);top.frames['browse'].window.scrollTo(0,0);">Go to the top</a></div>
        <?php }?>

<!--    </div>-->
<!--</div>-->
</body>
</html>

<?php
if(arg(0) == 'browsefarinternal')
    exit;
?>
