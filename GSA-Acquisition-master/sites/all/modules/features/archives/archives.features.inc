<?php
/**
 * @file
 * archives.features.inc
 */

/**
 * Implements hook_node_info().
 */
function archives_node_info() {
  $items = array(
    'archives' => array(
      'name' => t('Archives'),
      'base' => 'node_content',
      'description' => t('Archives for FAR and GSAM'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
