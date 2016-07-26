<?php
/**
 * @file
 * home_page.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function home_page_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Main Page Body';
  $fe_block_boxes->format = 'php_code';
  $fe_block_boxes->machine_name = 'home_body';
  $fe_block_boxes->body = '<div id="main-content">
            <!--Content Region-->
            <div id="secondary-links">
                <a href="/?q=browsefar" id="far" class="grow">FAR</a>
                <a href="#" id="news" class="grow">News & Announcements</a>
                <a href="/?q=archives" id="archives" class="grow">Archives</a>
                <a href="/?q=Supplemental_Regulations" id="regulations" class="grow">Supplemental Regulations</a>
            </div>
           
        </div>';

  $export['home_body'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Home Slider';
  $fe_block_boxes->format = 'php_code';
  $fe_block_boxes->machine_name = 'home_slider';
  $fe_block_boxes->body = '<div id="landing-slider-wrapper">
<div id="landing-slider">
            <!--Front Carousel Region-->
            <div>
                <div class="slide-left">
                    <p>Redesigned Acquisition.Gov Portal</p>
                    <a href="#" class="read-more">READ MORE</a>
                </div>
                <img src="/sites/all/themes/acquisition/images/landing-slider-image.png" alt="computer screen graphic">
            </div>
            <div>
                <div class="slide-left">
                    <p>Redesigned Acquisition.Gov Portal</p>
                    <a href="#" class="read-more">READ MORE</a>
                </div>
                <img src="/sites/all/themes/acquisition/images/landing-slider-image.png" alt="computer screen graphic">
            </div>
            <div>
                <div class="slide-left">
                    <p>Redesigned Acquisition.Gov Portal</p>
                    <a href="#" class="read-more">READ MORE</a>
                </div>
                <img src="/sites/all/themes/acquisition/images/landing-slider-image.png" alt="computer screen graphic">
            </div>
        </div>
        </div>';

  $export['home_slider'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Site Header';
  $fe_block_boxes->format = 'php_code';
  $fe_block_boxes->machine_name = 'site_header';
  $fe_block_boxes->body = '    <div id="header-bar">
        <a href="/"><img src="/sites/all/themes/acquisition/images/logo.png" alt="Acquisition.gov"></a>
    </div>';

  $export['site_header'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Search Block';
  $fe_block_boxes->format = 'php_code';
  $fe_block_boxes->machine_name = 'site_search';
  $fe_block_boxes->body = ' <div id="search-container">
                <input type="text" id="search">
                <a href="#">Advanced Search</a>
</div>';

  $export['site_search'] = $fe_block_boxes;

  return $export;
}
