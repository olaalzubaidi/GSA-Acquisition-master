<?php

/**
 * Search Preprocess
 */
function acquisition_preprocess_search_result(&$variables) {
    global $language;
    $result = $variables['result'];
    $variables['url'] = check_url($result['link']);
    $variables['title'] = check_plain($result['title']);
    if (isset($result['language']) && $result['language'] != $language->language && $result['language'] != LANGUAGE_NONE) {
        $variables['title_attributes_array']['xml:lang'] = $result['language'];
        $variables['content_attributes_array']['xml:lang'] = $result['language'];
    }

    $info = array();
    if (!empty($result['module'])) {
        $info['module'] = check_plain($result['module']);
    }
    if (!empty($result['user'])) {
        $info['user'] = $result['user'];
    }
    if (!empty($result['date'])) {
        $info['date'] = format_date($result['date'], 'short');
    }
    if (isset($result['extra']) && is_array($result['extra'])) {
        $info = array_merge($info, $result['extra']);
    }
    // Check for existence. User search does not include snippets.
    $variables['snippet'] = isset($result['snippet']) ? $result['snippet'] : '';
    // Provide separated and grouped meta information..
    $variables['info_split'] = $info;
    $variables['info'] = implode(' - ', $info);
    $variables['theme_hook_suggestions'][] = 'search_result__' . $variables['module'];
    $variables['node'] = $result['node'];
    $variables['tags'] = acquisition_taxonomy_from_nid($result['node']->entity_id);
}

/**
 * Implements theme_node_preview()
 */
function acquisition_node_preview($variables) {
  $node = $variables['node'];

  if($node->type === 'current_uploads' && $node->op === 'Preview') {
    $output = '<div class="preview">';

    $preview_trimmed_version = FALSE;

    $elements = node_view(clone $node, 'teaser');
    $trimmed = drupal_render($elements);
    $elements = node_view($node, 'full');
    $full = drupal_render($elements);

    // Do we need to preview trimmed version of post as well as full version?
    if ($trimmed != $full) {
      //drupal_set_message(t('The trimmed version of your post shows what your post looks like when promoted to the main page or when exported for syndication.<span class="no-js"> You can insert the delimiter "&lt;!--break--&gt;" (without the quotes) to fine-tune where your post gets split.</span>'));
      //$output .= '<h3>' . t('Preview trimmed version') . '</h3>';
      //$output .= $trimmed;
      //$output .= '<h3>' . t('Preview full version') . '</h3>';
      $output .= $full;
    }
    else {
      $output .= $full;
    }
    $output .= "</div>\n";

    return $output;
  }
}

function acquisition_facetapi_count($variables) {
    return '<span class="counter">' . (int) $variables['count'] . '</span>';
}