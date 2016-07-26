<?php
drupal_add_css(path_to_theme() . '/styles/ie8.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 8', '!IE' => FALSE), 'preprocess' => FALSE));
//global $results;
$search_term = html_entity_decode(arg(2));
if($search_term == '*')
    $search_term = '';
$farcheck = '';
$gsamcheck = '';
if(isset($_REQUEST['f'])){
foreach($_REQUEST['f'] as $rkey=>$rval){
    $pos = strpos($rval, 'bundle');
    if ($pos !== false) {
        if($rval == 'bundle:far')
            $farcheck = 'checked';
        if($rval == 'bundle:gsam')
            $gsamcheck = 'checked';
    }
}
}

    ?>

<div id="header" class="clearfix">
    <?php if ($page['header']):?>
    <!--Header Region-->
    <?php print render($page['header']);?>
    <a href="http://gsa.gov" id="gsa-logo">Powered by GSA</a>
            <a href="#" class="check-text">Change Text Size</a>

    <?php endif;
    if ($page['search_box']): ?>
        <?php print render($page['search_box']);?>
        <a id="advanced-search-header" href="/?q=search/site/*">Advanced Search</a>
        <?php endif;?>
</div> <!--End header-->

<div id="main-nav">
    <?php if ($page['main_nav']):
    print render($page['main_nav']);
endif;?>
</div>
<script type='text/javascript'>
    function searchSubmit(){
        facet = '';
        if(document.getElementById("far-checkbox").checked == true)
            facet = '&f[0]=bundle%3Afar';
        if(document.getElementById("gsam-checkbox").checked == true)
            facet += '&f[1]=bundle%3Agsam';
       window.location = '/?q=search/site/'+document.getElementById("searchkeys").value+facet;
    }
</script>
<div id="content-wrapper">
    <div id="main-content-internal">
        <div id="breadcrumbs"><?php if ($breadcrumb): print $breadcrumb; endif;?></div>
        <section id="post-content" role="main">
            <?php print $messages; ?>
            <?php print render($title_prefix); ?>
            <?php if ($title): ?><h1 class="page-title"><?php print $title; ?></h1><?php endif; ?>
            <?php print render($title_suffix); ?>
            <?php print render($page['help']); ?>
            <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
        </section> <!-- /#main -->
        <form class="search-form" id="advanced-search-form" accept-charset="UTF-8" onsubmit="return false;">
            <input type="hidden" name="q" value="search/site" size="40" maxlength="255" class="form-text">
            <div>
                <div class="container-inline form-wrapper" id="edit-basic">
                    <div id="advanced-search-type" class="has-pretty-child">
                        <h3>Type</h3>
                        <div class="clearfix prettycheckbox labelright  blue"><input class="custom-checks" type="checkbox" id="far-checkbox" name="far-checkbox" <?=$farcheck?>><a href="#" class=" "></a>
                            <label for="far-checkbox">FAR</label></div>

                        <div class="clearfix prettycheckbox labelright  blue"><input class="custom-checks" type="checkbox" id="gsam-checkbox" name="gsam-checkbox" <?=$gsamcheck?>><a href="#" class=" "></a>
                            <label for="gsam-checkbox">GSAM</label></div>

                    </div>
                    <div class="form-item form-type-textfield form-item-keys">
                        <h3>Free Text</h3>
                        <input type="text" id="searchkeys" name="searchkeys" value="<?=$search_term?>" size="40" maxlength="255" class="form-text">
                    </div>
                    <input type="hidden" name="form_id" value="search_form">
                    <input type="submit" onClick="searchSubmit();">
                </div>
            </div>
        </form>
        <?php if($page['content']):?>
        <?php
        print "<div id='main-content-wrapper'>";
        //print render($page['content']['system_main']['search_form']);?>
        <?php print render($page['content']['system_main']['search_results']);
        print "</div>";
        ?>
        <?php if ($page['right_sidebar']):
            print '<div class="filter-sidebar">';
            print render($page['right_sidebar']);
            print '</div>';
        endif;?>
        <?php
        endif;?>

    </div>
</div>
</div>

<div id="footer">
    <div id="footer-wrapper">
        <div id="footer-inner-wrapper">
            <!--Footer Region-->
            <div class="soc-icons">
                <?php print acquisition_central_social_icons(); ?>
            </div>
            <div id="footer-link">
                <?php if ($page['footer']):?>
                <?php print render($page['footer']);?>
                <?php endif;?>
            </div>
        </div>
    </div>
</div>
