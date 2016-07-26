<?php
/**
 * @file
 * current_uploads.features.inc
 */

/**
 * Implements hook_node_info().
 */
function current_uploads_node_info() {
  $items = array(
    'current_uploads' => array(
      'name' => t('Current Uploads'),
      'base' => 'node_content',
      'description' => t('Current FAR & GSAM uploads'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
