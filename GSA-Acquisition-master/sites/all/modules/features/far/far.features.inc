<?php
/**
 * @file
 * far.features.inc
 */

/**
 * Implements hook_node_info().
 */
function far_node_info() {
  $items = array(
    'far' => array(
      'name' => t('FAR'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
