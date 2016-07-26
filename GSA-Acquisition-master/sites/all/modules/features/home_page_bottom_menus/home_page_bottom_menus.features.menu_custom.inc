<?php
/**
 * @file
 * home_page_bottom_menus.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function home_page_bottom_menus_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-resources.
  $menus['menu-resources'] = array(
    'menu_name' => 'menu-resources',
    'title' => 'Resources',
    'description' => 'Third menu on front page in the body.',
  );
  // Exported menu: menu-training.
  $menus['menu-training'] = array(
    'menu_name' => 'menu-training',
    'title' => 'Training',
    'description' => 'Training menu for the front page body. This is the left menu.',
  );
  // Exported menu: menu-useful-links.
  $menus['menu-useful-links'] = array(
    'menu_name' => 'menu-useful-links',
    'title' => 'Useful Links',
    'description' => 'Second menu of three for the front page menus.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Resources');
  t('Second menu of three for the front page menus.');
  t('Third menu on front page in the body.');
  t('Training');
  t('Training menu for the front page body. This is the left menu.');
  t('Useful Links');


  return $menus;
}
