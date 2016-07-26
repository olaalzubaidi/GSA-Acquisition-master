<?php
/**
 * @file
 * home_page.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function home_page_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}

/**
 * Implements hook_views_api().
 */
function home_page_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function home_page_node_info() {
  $items = array(
    'front_page_carousel' => array(
      'name' => t('Front Page Carousel'),
      'base' => 'node_content',
      'description' => t('Front Page Carousel'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'video_gallery' => array(
      'name' => t('Video Gallery'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => t('Video content that can be used on the main page.'),
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
