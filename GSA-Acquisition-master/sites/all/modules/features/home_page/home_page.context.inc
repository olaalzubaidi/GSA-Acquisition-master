<?php
/**
 * @file
 * home_page.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function home_page_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'homepage';
  $context->description = 'home page';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-4' => array(
          'module' => 'block',
          'delta' => '4',
          'region' => 'header',
          'weight' => '-10',
        ),
        'nice_menus-1' => array(
          'module' => 'nice_menus',
          'delta' => '1',
          'region' => 'main_nav',
          'weight' => '-10',
        ),
        'search-form' => array(
          'module' => 'search',
          'delta' => 'form',
          'region' => 'search_box',
          'weight' => '-10',
        ),
        'block-2' => array(
          'module' => 'block',
          'delta' => '2',
          'region' => 'front_carousel',
          'weight' => '-10',
        ),
        'views-e5fd8284cc935fbbb83cc032eeba1450' => array(
          'module' => 'views',
          'delta' => 'e5fd8284cc935fbbb83cc032eeba1450',
          'region' => 'content',
          'weight' => '-10',
        ),
        'block-1' => array(
          'module' => 'block',
          'delta' => '1',
          'region' => 'content',
          'weight' => '-9',
        ),
        'menu-menu-training' => array(
          'module' => 'menu',
          'delta' => 'menu-training',
          'region' => 'content',
          'weight' => '-8',
        ),
        'menu-menu-resources' => array(
          'module' => 'menu',
          'delta' => 'menu-resources',
          'region' => 'content',
          'weight' => '-7',
        ),
        'menu-menu-useful-links' => array(
          'module' => 'menu',
          'delta' => 'menu-useful-links',
          'region' => 'content',
          'weight' => '-6',
        ),
        'menu-menu-footer-far-menu' => array(
          'module' => 'menu',
          'delta' => 'menu-footer-far-menu',
          'region' => 'footer',
          'weight' => '-22',
        ),
        'menu-menu-footer-acquisition-system-m' => array(
          'module' => 'menu',
          'delta' => 'menu-footer-acquisition-system-m',
          'region' => 'footer',
          'weight' => '-21',
        ),
        'menu-menu-footer-supplemental-regulat' => array(
          'module' => 'menu',
          'delta' => 'menu-footer-supplemental-regulat',
          'region' => 'footer',
          'weight' => '-20',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('home page');
  $export['homepage'] = $context;

  return $export;
}
