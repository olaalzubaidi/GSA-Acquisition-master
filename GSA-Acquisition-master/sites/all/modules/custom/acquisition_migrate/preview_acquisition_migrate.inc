<?php

/**
 * Implements hook_node_view()
 */
function acquisition_migrate_node_view($node, $view_mode, $langcode) {
  // this script should run only for current_uploads content types
  if($node->type === 'current_uploads') {
    // $node->op needs to be checked if it is null
    // node view will be altered only during node-preview but not node-view
    // before actual node save takes place.
    if(!empty($node->op) && $node->op === 'Preview') {
      // get current uploaded file's $file obj
      $file = load_file_obj($node);

      // avoid errors when $file obj is empty or null
      if(!empty($file)) {
        $zip_file_path = getcwd() . '/sites/default/files/' . substr($file->uri, strlen('public://'));
        $zip = new ZipArchive;
        if($zip->open($zip_file_path, ZipArchive::CREATE) === TRUE) {
          $zip_content_file = array();
          // store in an array all zip file contents
          $zip_content_file = get_zip_content_file($zip);

          // using iframe is a bad idea here
          $output = "<div style='width:auto; height:200px; background-color:#F8FFF0; margin:10px; padding:10px; overflow: scroll; border: solid #D7F1F8 10px;' id='zip_content_file'>";
          $output .= implode($zip_content_file, '<br>');
          $output .= '</div>';

          // show in full mode, teaser is intentionally disabled
          if($view_mode === 'full') {
            $node->content['zip_content_file'] = array(
              0 => array(
                '#markup' => '<h1>Please Review ZIP Contents</h1><h2>Current FAR/GSAM docs will be archived. Do you want to proceed?</h2>',
                ),
              1 => array(
                '#markup' => $output,
                ),
              '#weight' => 10,
            );
          }
          $zip->close();
        }
      }
    } else {
      // we need to null $node->op to avoid error generation during node view
      // $node->op is available only during node save or preview
      $node->op = array(NULL);
    }
  }
}
