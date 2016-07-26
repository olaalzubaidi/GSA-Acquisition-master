<?php
/**
 * @file
 * home_page.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function home_page_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-footer-acquisition-system-m.
  $menus['menu-footer-acquisition-system-m'] = array(
    'menu_name' => 'menu-footer-acquisition-system-m',
    'title' => 'Acquisition Systems',
    'description' => 'This is the menu down in the footer of the page for Acquisition System.',
  );
  // Exported menu: menu-footer-far-menu.
  $menus['menu-footer-far-menu'] = array(
    'menu_name' => 'menu-footer-far-menu',
    'title' => 'FAR',
    'description' => 'This is the menu down in the footer for the FAR menu group.',
  );
  // Exported menu: menu-footer-supplemental-regulat.
  $menus['menu-footer-supplemental-regulat'] = array(
    'menu_name' => 'menu-footer-supplemental-regulat',
    'title' => 'Supplemental Regulations',
    'description' => 'This is down in the footer at the bottom of the page for Supplemental Regulations.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Acquisition Systems');
  t('FAR');
  t('Supplemental Regulations');
  t('This is down in the footer at the bottom of the page for Supplemental Regulations.');
  t('This is the menu down in the footer for the FAR menu group.');
  t('This is the menu down in the footer of the page for Acquisition System.');


  return $menus;
}
