<?php

/**
 * Create GSAM nodes from html docs
 */
function acquisition_migrate_gsam_content($c_type = 'gsam', $dir, $fileUri = null) {
  global $user;

  $dir = 'sites/default/files/current/' . $c_type . '/html';
  if($fileUri) {
    $zip_source = 'sites/default/files/' . substr($fileUri, strlen('public://'));
  } else {
    $zip_source = '';
  }
  $pdf = array();
  $pdf = get_pdf_files($c_type);

  $files = get_html_files($c_type);
  foreach($files as $file) {
    // we parse GSAMTOC.html file to capture all href and anchor tag values
    if($file->name === 'GSAMTOC') {
      $gsamtoc_file_uri = $file->uri;
    }
    // we parse gsamtoc553.html to capture all href and anchor tag values
    // basically this file has all required forms under part 553
    elseif($file->name === 'GSAMTOC553') {
      $gsamtoc553_file_uri = $file->uri;
    }
  }
  $listed = 0;

  // capture all file_names in href attribute to this array, which will be used to avoid duplicates.
  $file_names = $file_names_2 = array();

  $DOM = new DOMDocument;
  if(!empty($gsamtoc_file_uri)) {
    $DOM->load($gsamtoc_file_uri);
    $a_tag = array();
    // capture all anchor tag values
    $a_tag_values = $DOM->getElementsByTagName('a');
    foreach($a_tag_values as $key => $value) {
      // triming is very important to avoid site crashes due to bad chars
      $a_tag_value = trim(check_plain($a_tag_values->item($key)->nodeValue), " \t\n\r\0\x0B");
      // make sure you are saving clean strings that don't break site at the time of content migration
      $a_tag_href = urldecode(trim(check_plain($value->getAttribute('href')), " \t\n\r\0\x0B"));
      // we use it here in foreach loop individually and
      // we will use it outside this foreach loop capturing it as array
      // skips where href is not found
      if(!empty($a_tag_href)) {
        $file_names[] = strstr($a_tag_href, '.html#', true);
      }
      // skip all empty anchor tags and href attributes
      if(!empty($a_tag_value) && !empty($a_tag_href)) {
        // this part of iteration/parsing is similar with FAR parsing
        // please refere far_acquisition_migrate.inc for any helpfull comments
        if($regex = preg_match('/^Part[0-9]{3}.html#wp[0-9]{1,9}$/', $a_tag_href, $matches)) {
          $field_part_number = substr($a_tag_href, 4, 3);
          $field_sub_part_number = substr(strstr($a_tag_value, ' ', true), 4);
          $field_doc_type = 'Subpart';
          $subchapter = get_gsam_subchapter($field_part_number);
          $node_title = $a_tag_value;
          $file_uri = '';
          $file_uri = $dir . '/' . $a_tag_href;
          // capture $file_path without '#'
          // this will lead us to the file
          $file_path = strstr($file_uri, '#', true);
          $html_content = !empty($file_path) ? parse_html_doc_file($file_path) : '';
          $tags_array = array('GSAM', $subchapter, 'Part ' . $field_part_number, $field_doc_type);
          $listed = 1;
          // attach pdf_path to node being created
          $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
          acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
        } elseif($regex = preg_match('/^Part[0-9]{3}App[A-Z]{1}.html#wp[0-9]{1,9}$/', $a_tag_href, $matches)) {
          $field_part_number = substr($a_tag_href, 4, 3);
          $field_sub_part_number = substr($a_tag_href, 7, 4);
          $field_doc_type = 'Subpart';
          $subchapter = get_gsam_subchapter($field_part_number);
          $node_title = $a_tag_value;
          $file_uri = '';
          $file_uri = $dir . '/' . $a_tag_href;
          $file_path = strstr($file_uri, '#', true);
          $html_content = !empty($file_path) ? parse_html_doc_file($file_path) : '';
          $tags_array = array('GSAM', $subchapter, 'Part ' . $field_part_number, $field_doc_type);
          $listed = 1;
          $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
          acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
        } elseif($regex = preg_match('/^Part[0-9]{3}_Sub[0-9]{1}[A-Z]{0,1}.html#wp[0-9]{1,9}$/', $a_tag_href, $matches)) {
          $field_part_number = substr($a_tag_value, 0, 3);
          $field_sub_part_number = substr(strstr($a_tag_value, ' ', true), 4);
          $field_doc_type = 'Subpart';
          $subchapter = get_gsam_subchapter($field_part_number);
          $node_title = $a_tag_value;
          $file_uri = '';
          $file_uri = $dir . '/' . $a_tag_href;
          $file_path = strstr($file_uri, '#', true);
          $html_content = !empty($file_path) ? parse_html_doc_file($file_path) : '';
          $tags_array = array('GSAM', $subchapter, 'Part ' . $field_part_number, $field_doc_type);
          $listed = 1;
          $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
          acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
        } elseif($regex = preg_match('/^GSAMTOC[0-9]{3}.html#wp[0-9]{1,9}$/', $a_tag_href, $matches)) {
          $field_part_number = substr($a_tag_href, 7, 3);
          $field_sub_part_number = substr(strstr($a_tag_value, ' ', true), 4);
          $field_doc_type = 'Part';
          $subchapter = get_gsam_subchapter($field_part_number);
          $node_title = $a_tag_value;
          $file_uri = '';
          $file_uri = $dir . '/' . $a_tag_href;
          $file_path = strstr($file_uri, '#', true);
          $html_content = !empty($file_path) ? parse_html_doc_file($file_path) : '';
          $tags_array = array('GSAM', $subchapter, 'Part' , $field_doc_type);
          $listed = 1;
          $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
          acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
        } elseif($regex = preg_match('/^Subch[A-Z]{1}.html#wp[0-9]{1,9}$/', $a_tag_href, $matches)) {
          $field_part_number = substr($a_tag_href, 0, 5);
          $field_sub_part_number = substr($a_tag_href, 5, 1);
          $field_doc_type = 'Subchapter';
          $node_title = $a_tag_value;
          $file_uri = '';
          $file_uri = $dir . '/' . $a_tag_href;
          $file_path = strstr($file_uri, '#', true);
          $html_content = !empty($file_path) ? parse_html_doc_file($file_path) : '';
          $tags_array = array('GSAM', $field_doc_type);
          $subchapter = '';
          $pdf_path = '';
          acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
        } elseif($regex = preg_match('/^Foreword.html#wp[0-9]{1,9}$/', $a_tag_href, $matches)) {
          $field_part_number = 'Foreword';
          $field_sub_part_number = '';
          $field_doc_type = '';
          $node_title = $a_tag_value;
          $file_uri = '';
          $file_uri = $dir . '/' . $a_tag_href;
          $file_path = strstr($file_uri, '#', true);
          $html_content = !empty($file_path) ? parse_html_doc_file($file_path) : '';
          $tags_array = array('GSAM');
          $subchapter = '';
          $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
          acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
        }
      }
    }
  }

  if(!empty($gsamtoc553_file_uri)) {
    $DOM->load($gsamtoc553_file_uri);
    $forms_tag = array();
    $file_names_2 = array(); // we use this for the rest of .html files not included in the TOC file.
    $forms_tag_values = $DOM->getElementsByTagName('a');
    foreach($forms_tag_values as $key => $value) {
      $forms_tag_value = trim(check_plain($forms_tag_values->item($key)->nodeValue));
      $forms_tag_href = urldecode(trim(check_plain($value->getAttribute('href')), " \t\n\r\0\x0B"));
      // we use it here in foreach loop individually and
      // we will use it outside this foreach loop capturing it as array
      // skip where href is not found to avoid capturing null or false results
      if(!empty($forms_tag_href)) {
        $file_names_2[] = substr($forms_tag_href, 0, strpos($forms_tag_href, '.html#'));
      }
      // avoid empty results
      if(!empty($forms_tag_value) && !empty($forms_tag_href)) {
        if($regex = preg_match('/^Part[0-9]{3}Forms[a-z]{0,1}[0-9]{1,2}.html#wp[0-9]{1,9}$/', $forms_tag_href, $matches)) {
          $field_part_number = substr($forms_tag_href, 4, 3);
          $field_sub_part_number = substr($forms_tag_href, 7, strpos($forms_tag_href, ('.')) - 7);
          $field_doc_type = 'Forms';
          $subchapter = get_gsam_subchapter($field_part_number);
          $node_title = $forms_tag_value;
          $file_uri = '';
          $file_uri = $dir . '/' . $forms_tag_href;
          $file_path = strstr($file_uri, '#', true);
          $html_content = !empty($file_path) ? parse_html_doc_file($file_path) : '';
          $tags_array = array('GSAM', $subchapter, 'Part ' . $field_part_number, $field_doc_type);
          $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
          acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
        }
      }
    }
  }

  // Parse and migrate rest of the files that are not included in TOC anchor tags.
  // All these html docs reside in 'sites/default/files/current/gsam/html'
  $other_file_names = array();
  $other_file_names = array_merge($file_names, $file_names_2);
  foreach($files as $file) {
    $file_uri = $file->uri;
    $file_name = $file->name;
    // by now we have migrated so many files from GSAMTOC.html href links
    // but that doesn't give us all the files that exist in the file directory
    // now we need to go to the file directory and parse eahc file at a time
    // while parsing we will exclude all files that have already been migrated
    // and capture and migrate thte only files that have never been migrated before.
    if(!in_array($file_name, $other_file_names)) {
      if($regex = preg_match('/^Part[0-9]{3}Forms[a-z]{0,1}[0-9]{1,2}$/', $file_name, $matches)) {
        $field_part_number = substr($file_name, 4, 3);
        $field_sub_part_number = substr($file_name, 7);
        $field_doc_type = 'Forms';
        $subchapter = get_gsam_subchapter($field_part_number);
        $tags_array = array('GSAM', $subchapter, 'Part ' . $field_part_number, $field_doc_type);
        $node_title = parse_html_page_title($file_uri, 'title');
        $html_content = !empty($file_uri) ? parse_html_doc_file($file_uri) : '';
        $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
        acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
      } elseif($file_name === 'GSAMTOC') {
        $field_part_number = '';
        $field_sub_part_number = '';
        $field_doc_type = '';
        $node_title = parse_html_page_title($file_uri, 'title');
        $html_content = !empty($file_uri) ? parse_html_doc_file($file_uri) : '';
        $tags_array = array('GSAM');
        $subchapter = '';
        $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
        acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
      } else {
        $field_part_number = $file_name;
        $field_sub_part_number = '';
        $field_doc_type = '';
        $tags_array = array('GSAM');
        $subchapter = '';
        $node_title = parse_html_page_title($file_uri, 'title');
        $html_content = !empty($file_uri) ? parse_html_doc_file($file_uri) : '';
        $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
        acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
      }
    }
  }
  $nids = array();
  $file_names = array_merge(array_filter($file_names), array_filter($file_names_2));
  $nids = _get_update_diff($file_names, $c_type, 1);
  _unpublish_update_diff_nodes($nids);
  if(!empty($nids)) {
    watcher('current_uploads', $c_type, implode(", ", $nids) . ' nodes got unpublished');
  }
}


/**
 * Creates nodes based on passed parameters
 *  This functino will create nodes for both FAR and GSAM.
 *
 * $c_type                = Content type
 * $uid                   = User ID
 * $node_title            = Node Title
 * $html_content          = HTML document contents as is
 * $field_part_number     = Part Number
 * $field_sub_part_number = Field Subpart Number
 * $field_doc_type        = Field Doc Type
 * $subchapter            = Field Doc Type
 * $file_uri              = File URI
 * $tags_array            = Tags
 * $listed                = Listed (boolean) Yes or No
 *
 * This function doesn't return anything.
 */
function acquisition_migrate_content($c_type, $uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array = array(), $listed, $pdf_path, $zip_source) {
  $node = new stdClass();
  $node->type = $c_type;
  $node->language = LANGUAGE_NONE;
  $node->title = $node_title;
  $node->uid = $uid;
  $node->status = 1;
  $node->comment = 0;
  $node->promote = 0;
  $node->sticky = 0;
  $node->revision = TRUE;
  $node->log = 1;
  node_object_prepare($node);
  $node->body['und'][0] = array(
    'value' => $html_content,
    'format' => NULL,
    'safe_value' => check_plain($html_content),
  );
  // Insert Tags
  if(!empty($tags_array)) {
    foreach($tags_array as $tkey => $tval) {
      if($term = taxonomy_get_term_by_name($tval)) {
        //Assign an existing taxonomy
        $terms_array = array_keys($term);
        $node->field_meta_tags['und'][$tkey]['tid'] = $terms_array[0];
      } else {
        //Create a new taxonomy if not
        $term = new stdClass();
        $term->name = $tval;
        $term->vid = 1;
        if(!empty($term->name)) {
          $term_save = taxonomy_term_save($term);
          $array_keys = array_keys(taxonomy_get_term_by_name($tval));
          $tid = $array_keys[0];
          if($tid != NULL) {
            // here is the line that inserts all these tags in the node field
            $node->field_meta_tags['und'][$tkey]['tid'] = $tid;
          }
        }
      }
    }
  }
  $node->field_part_number['und'][0]['value'] = $field_part_number;
  $node->field_sub_part_number['und'][0]['value'] = $field_sub_part_number;
  $node->field_doc_type['und'][0]['value'] = $field_doc_type;
  $node->field_sub_chapter['und'][0]['value'] = $subchapter;
  $node->field_year['und'][0]['value'] = "2014";
  $node->field_file_location['und'][0]['value'] = $file_uri;
  $node->field_pdf_file_path['und'][0]['value'] = $pdf_path;
  $node->field_zip_file_path['und'][0]['value'] = $zip_source;
  $node->field_listed_in_index['und'][0]['value'] = $listed;

  // sanitize html-page-title to compare with existing migrated content residing in the database
  $existing_node = '';
  //$existing_node = get_node_info($node_title, $node->type, 'single', null, $file_uri, null);
  $existing_node = get_node_info(null, $node->type, 'single', null, $file_uri, null);
  // get file_name of the current file that is being migrated
  $file_name = substr($file_uri, strpos($file_uri, '/html/'), strpos($file_uri, '.html'));
  if(!empty($existing_node)) {
    // node exists
    //if($node_title == $existing_node->title) {
    if(strpos($existing_node->field_file_location_value, $file_name) == true) {
      // do updates if body value changed and
      // make sure we are updating an existing node
      // we can check if content source is coming from the same .html file
      // just match file_name, if the same, we are good to go ahead and update the node.
      //if($html_content != $existing_node->body_value && strpos($existing_node->field_file_location_value, $file_name) == true) {
      if($html_content != $existing_node->body_value OR $node_title != $existing_node->title) {
        // while updating we uniqely identify each node by its nid
        $node->nid = $existing_node->nid;
        // and vid
        $node->vid = $existing_node->vid;
        // we alreddy know this is an update, so we tell it node is not new.
        $node->is_new = FALSE;
        // Create aliased urls
        $node->path = array(
          'source' => $node->nid,
          'alias' => 'browse/' . $node->type . (!empty($field_part_number) ? ('/' . $field_part_number) : false) . (!empty($field_sub_part_number) ? ('/' . $field_sub_part_number) : false),
          'language' => 'und',
        );
        // after saving aliased path we are ready to save the node just created or updated
        path_save($node->path);
        $node = node_submit($node);
        node_save($node);
      }
    }
  } else {
    // if the above condition did not occur then we will be creatign a new node
    $node->path = array(
      'alias' => 'browse/' . $node->type . (!empty($field_part_number) ? ('/' . $field_part_number) : false) . (!empty($field_sub_part_number) ? ('/' . $field_sub_part_number) : false),
      'language' => 'und',
    );
    path_save($node->path);
    $node->is_new = TRUE;
    $node = node_submit($node);
    $node_save = node_save($node);
  }
}


/**
 * GSAM Subchapters that we use for tagging purposes.
 */
function get_gsam_subchapter($pfn = 0) {
  switch ($pfn) {
    case ($pfn >= 501 && $pfn <= 504):
      $subchapter = "Subchapter A-General";
      break;
    case ($pfn >= 505 && $pfn <= 512):
      $subchapter = "Subchapter B-Competition and Acquisition Planning";
      break;
    case ($pfn >= 513 && $pfn <= 518):
      $subchapter = "Subchapter C-Contracting Methods and Contract Types";
      break;
    case ($pfn >= 519 && $pfn <= 526):
      $subchapter = "Subchapter D-Socioeconomic Programs";
      break;
    case ($pfn >= 527 && $pfn <= 533):
      $subchapter = "Subchapter E-General Contracting Requirements";
      break;
    case ($pfn >= 534 && $pfn <= 541):
      $subchapter = "Subchapter F-Special Categories of Contracting";
      break;
    case ($pfn >= 542 && $pfn <= 551):
      $subchapter = "Subchapter G-Contract Management";
      break;
    case ($pfn >= 552 && $pfn <= 553):
      $subchapter = "Subchapter H-Cluases and Forms";
      break;
    case ($pfn == 570):
      $subchapter = "Subchapter I-Special Contracting Programs";
      break;
    default:
      $subchapter = false;
      break;
  }
  return $subchapter;
}
