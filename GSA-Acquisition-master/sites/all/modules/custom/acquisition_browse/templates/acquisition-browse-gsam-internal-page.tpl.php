<?php
$themepath = drupal_get_path('theme',$GLOBALS['theme']);
?>
<!DOCTYPE html>
<html>
<head>
    <title>Acquisition.gov</title>
    <link rel="stylesheet" type="text/css" href="<?=$themepath?>/styles/styles.css">
    <link rel="stylesheet" type="text/css" href="<?=$themepath?>/styles/fonts.css">
    <link rel="stylesheet" type="text/css" href="<?=$themepath?>/js/slick/slick.css">

    <script src="<?=$themepath?>/js/jquery-1.11.2.min.js"></script>
    <script src="<?=$themepath?>/js/slick/slick.min.js"></script>
    <script src="<?=$themepath?>/js/global.js"></script>
</head>

<body>
<div class="browse-headers">
    <h3>Title & Number</h3>
    <div class="browse-header-right"><a name='downloadarea'>&nbsp;</a>
        <h4 id="select-format">Select the download format</h4>
        <div id="browse-iframe-header-right-sub">
            <h4>HTML</h4>
            <h4>PDF</h4>
        </div>
    </div>
</div>
<table id='browse-table'>
    <tbody>
    <?php print $processed_vars['table_contents'];?>

    </tbody>
</table>
</body>
</html>