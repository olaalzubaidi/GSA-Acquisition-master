<?php
/**
 * @file
 * home_page.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function home_page_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-footer-acquisition-system-m_regulationsgov:node/17
  $menu_links['menu-footer-acquisition-system-m_regulationsgov:node/17'] = array(
    'menu_name' => 'menu-footer-acquisition-system-m',
    'link_path' => 'node/17',
    'router_path' => 'node/%',
    'link_title' => 'Regulations.gov',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-acquisition-system-m_regulationsgov:node/17',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-far-menu_abilityone:node/17
  $menu_links['menu-footer-far-menu_abilityone:node/17'] = array(
    'menu_name' => 'menu-footer-far-menu',
    'link_path' => 'node/17',
    'router_path' => 'node/%',
    'link_title' => 'AbilityOne',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-far-menu_abilityone:node/17',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-far-menu_federal-acquisition-regulation-far:node/17
  $menu_links['menu-footer-far-menu_federal-acquisition-regulation-far:node/17'] = array(
    'menu_name' => 'menu-footer-far-menu',
    'link_path' => 'node/17',
    'router_path' => 'node/%',
    'link_title' => 'Federal Acquisition Regulation (FAR)',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-far-menu_federal-acquisition-regulation-far:node/17',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-supplemental-regulat_abilityone:node/17
  $menu_links['menu-footer-supplemental-regulat_abilityone:node/17'] = array(
    'menu_name' => 'menu-footer-supplemental-regulat',
    'link_path' => 'node/17',
    'router_path' => 'node/%',
    'link_title' => 'AbilityOne',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-supplemental-regulat_abilityone:node/17',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 0,
  );
  // Exported menu link: menu-footer-supplemental-regulat_office-of-federal-procurement-policy-ofpp:node/17
  $menu_links['menu-footer-supplemental-regulat_office-of-federal-procurement-policy-ofpp:node/17'] = array(
    'menu_name' => 'menu-footer-supplemental-regulat',
    'link_path' => 'node/17',
    'router_path' => 'node/%',
    'link_title' => 'Office of Federal Procurement Policy (OFPP)',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-supplemental-regulat_office-of-federal-procurement-policy-ofpp:node/17',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -43,
    'customized' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('AbilityOne');
  t('Federal Acquisition Regulation (FAR)');
  t('Office of Federal Procurement Policy (OFPP)');
  t('Regulations.gov');


  return $menu_links;
}
