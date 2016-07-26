<?php
/**
 * @file
 * gsam.features.inc
 */

/**
 * Implements hook_node_info().
 */
function gsam_node_info() {
  $items = array(
    'gsam' => array(
      'name' => t('GSAM'),
      'base' => 'node_content',
      'description' => t('GSAM'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
