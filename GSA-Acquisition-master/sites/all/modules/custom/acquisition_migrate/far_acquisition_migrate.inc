<?php

/**
 * Migrate FARMTOC Parts & Subparts
 */
function acquisition_migrate_far_content($c_type = 'far', $dir, $fileUri = null) {
  global $user;

  $dir = 'sites/default/files/current/' . $c_type . '/html';
  if($fileUri) {
    $zip_source = 'sites/default/files/' . substr($fileUri, strlen('public://'));
  } else {
    $zip_source = '';
  }
  $pdf = array();
  $pdf = get_pdf_files($c_type);

  // html
  $files = get_html_files($c_type);
  foreach($files as $file) {
    if($file->name === 'FARMTOC') {
      $file_uri = $file->uri;
    }
  }
  $listed = 0;

  $DOM = new DOMDocument;
  if(!empty($file_uri)) {
    $DOM->load($file_uri);
    // get all anchor tags by parsing FARMTOC.html file
    $a_tag_values = $DOM->getElementsByTagName('a');
    $a_tag = array();
    // we use $file_names to capture all anchor tags that we found in FARMTOC.html file
    $file_names = array();
    foreach($a_tag_values as $key => $value) {
      // get each anchor tag, trim whitespaces and foreign chars
      $a_tag_value = trim(check_plain($a_tag_values->item($key)->nodeValue), " \t\n\r\0\x0B");
      // get all href attributes
      $a_tag_href = urldecode(trim(check_plain($value->getAttribute('href')), " \t\n\r\0\x0B"));
      // we capture all file_names that are found in FARMTOC.html href attributes
      if(!empty($a_tag_href)) {
        $file_names[] = strstr($a_tag_href, '.html#', true);
      }
      // make sure anchor tag and href attribute is not empty or null
      if(!empty($a_tag_value) && !empty($a_tag_href)) {
        // search for strings and matche theme with our search criteria in the href attribute
        // this search will exclude any href which is not part of the criteria
        if($regex = preg_match('/^FARTOCP[0-9]{1,2}.html#wp[0-9]{1,9}$/', $a_tag_href, $matches)) {
          // we capture 'part_number' and 'sub_part_number' from href attribute
          $field_part_number = substr($a_tag_href, strlen('FARTOCP'), strpos($a_tag_href, '.html') - strlen('FARTOCP'));
          // left-trim all preceding 0 values from all part_numbers
          $field_part_number = ltrim($field_part_number, '0');
          $field_sub_part_number = '';
          $field_doc_type = 'Part';
          $subchapter = get_far_subchapter($field_part_number);
          // use anchor tag as our node title
          $node_title = $a_tag_value;
          $file_uri = '';
          // make a complete file path
          $file_uri = $dir . '/' . $a_tag_href;
          $file_path = strstr($file_uri, '#', true);
          // if file_path is available then use it to get to the file
          // open the file and parse all contents
          // capture all parsed contents as node body
          $html_content = !empty($file_path) ? parse_html_doc_file($file_path) : '';
          // tag each node with appropriate taggings
          $tags_array = array('FAR', $subchapter, 'Part', $field_doc_type);
          // when $listed = 1 it will be listed on browsefar page
          // and when value is 0 it will be unlisted.
          $listed = 1;
          // attach pdf_path to node being created
          $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
          // pass all the above variables to a function that creates the node.
          acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
        } elseif($regex = preg_match('/^Subpart[ ][0-9]{1,2}[_][0-9]{1,2}[Reserved]{0,8}.html#wp[0-9]{1,9}$/', $a_tag_href, $matches)) {
          $fpn = '';
          $fpn = substr($a_tag_href, strlen('Subpart '), strpos($a_tag_href, '.html') - strlen('Subpart '));
          $fpn = ltrim($fpn, '0');
          // do str manipulations to get part_number and sub_part_numbers
          $field_part_number = strstr($fpn, '_', true);
          $field_sub_part_number = substr($fpn, strpos($fpn, '_') + 1);
          $field_doc_type = 'Subpart';
          $subchapter = get_far_subchapter($field_part_number);
          $node_title = $a_tag_value;
          $file_uri = '';
          $file_uri = $dir . '/' . $a_tag_href;
          $file_path = strstr($file_uri, '#', true);
          $html_content = !empty($file_path) ? parse_html_doc_file($file_path) : '';
          $tags_array = array('FAR', $subchapter, 'Part ' . $field_part_number, $field_doc_type);
          $listed = 1;
          $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
          acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
        } elseif($regex = preg_match('/^Part[ ][0-9]{1,2}_Reserved.html#wp[0-9]{1,9}$/', $a_tag_href, $matches)) {
          $fpn = '';
          $fpn = substr($a_tag_href, strlen('Part '), strpos($a_tag_href, '.html') - strlen('Part '));
          $fpn = ltrim($fpn, '0');
          $field_part_number = strstr($fpn, '_', true);
          $field_sub_part_number = substr($fpn, strpos($fpn, '_') + 1);
          $field_doc_type = 'Part';
          $subchapter = get_far_subchapter($field_part_number);
          $node_title = $a_tag_value;
          $file_uri = '';
          $file_uri = $dir . '/' . $a_tag_href;
          $file_path = strstr($file_uri, '#', true);
          $html_content = !empty($file_path) ? parse_html_doc_file($file_path) : '';
          $tags_array = array('FAR', $subchapter, $field_doc_type, 'Reserved');
          $listed = 1;
          $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
          acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
        } elseif($regex = preg_match('/^[0-9]{2}[_][0-9]{3}[_]{0,1}[0-9]{0,3}.html#wp[0-9]{1,9}$/', $a_tag_href, $matches)) {
          $fpn = '';
          $a_tag_value = ltrim($a_tag_value);
          $fpn = strstr($a_tag_value, " ", true);
          $field_part_number = strstr($fpn, '.', true);
          $field_sub_part_number = substr($fpn, strpos($fpn, '.') + 1);
          $field_doc_type = 'Subpart';
          $subchapter = get_far_subchapter($field_part_number);
          $node_title = $a_tag_value;
          $file_uri = '';
          $file_uri = $dir . '/' . $a_tag_href;
          $file_path = strstr($file_uri, '#', true);
          $html_content = !empty($file_path) ? parse_html_doc_file($file_path) : '';
          $tags_array = array('FAR', $subchapter, 'Part ' . $field_part_number, $field_doc_type);
          $listed = 1;
          $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
          acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
        } else {
          // search for any href links that has not been covered above by preg_match
          // make sure we only capture hrefs that have .html strings in the href link
          // we don't assign part_number and sub_part_number, we only tag them
          if(strpos($a_tag_href, '.html')) {
            $tag = '';
            if(strpos($a_tag_href, 'PPENDIX') || strpos($a_tag_href, strtolower('PPENDIX'))) {
              $tag = 'APPENDIX';
              $listed = 1;
            } elseif(strpos($a_tag_href, 'ndex') || strpos($a_tag_href, strtoupper('ndex'))) {
              $tag = 'Index';
              $listed = 1;
            } else {
              $tag = strstr($a_tag_href, '.html', true);
              $listed = 0;
            }
            $a_tag_value = ltrim($a_tag_value);
            $field_part_number = '';
            $field_sub_part_number = '';
            $field_doc_type = '';
            $subchapter = '';
            $node_title = $a_tag_value;
            $file_uri = '';
            $file_uri = $dir . '/' . $a_tag_href;
            $file_path = strstr($file_uri, '#', true);
            $html_content = !empty($file_path) ? parse_html_doc_file($file_path) : '';
            $tags_array = array('FAR', $tag);
            $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
            acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
          }
        }
      }
    }
  }
  // Parse and migrate rest of the files that are not included in FARMTOC.html file anchor tags.
  // All these html docs reside in 'sites/default/files/current/far/html'
  foreach($files as $file) {
    $file_uri = $file->uri;
    $file_name = $file->name;
    // Parse thru file directory and capture all files that were not included in the FARMTOC.html href attributes
    // $file_names has all href links found in FARMTOC.html
    // now while parsing here we exclude all $file->names that are already captured in file_names array.
    if(!in_array($file->name, $file_names)) {
      if($regex = preg_match('/^[0-9]{2}[_][0-9]{3}[Matrix]{0,6}[_]{0,1}[0-9]{0,3}$/', $file_name, $matches)) {
        $field_part_number = '';
        $field_sub_part_number = '';
        $field_doc_type = '';
        $subchapter = get_far_subchapter(52);
        $tags_array = array('FAR', $subchapter, 'Subpart');
        $node_title = parse_html_page_title($file_uri, 'title');
        $html_content = !empty($file_uri) ? parse_html_doc_file($file_uri) : '';
        $listed = 0;
        $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
        acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
      } elseif(preg_match('/^FormsStandard[0-9]{0,2}$/', $file_name, $matches)) {
        $field_part_number = '';
        $field_sub_part_number = '';
        $subchapter = get_far_subchapter(53);
        $field_doc_type = 'FormsStandard';
        $tags_array = array('FAR', $subchapter, 'Forms', 'FormsStandard');
        $node_title = parse_html_page_title($file_uri, 'title');
        $html_content = !empty($file_uri) ? parse_html_doc_file($file_uri) : '';
        $listed = 0;
        $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
        acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
      } elseif(preg_match('/^FormsDDWH[0-9]{0,2}$/', $file_name, $matches)) {
        $field_part_number = '';
        $field_sub_part_number = '';
        $subchapter = get_far_subchapter(53);
        $field_doc_type = 'FormsDDWH';
        $tags_array = array('FAR', $subchapter, 'Forms', 'FormsDDWH');
        $node_title = parse_html_page_title($file_uri, 'title');
        $html_content = !empty($file_uri) ? parse_html_doc_file($file_uri) : '';
        $listed = 0;
        $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
        acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
      } elseif(preg_match('/^FormsOptional[0-9]{0,2}$/', $file_name, $matches)) {
        $field_part_number = '';
        $field_sub_part_number = '';
        $subchapter = get_far_subchapter(53);
        $field_doc_type = 'FormsOptional';
        $tags_array = array('FAR', $subchapter, 'Forms', 'FormsOptional');
        $node_title = parse_html_page_title($file_uri, 'title');
        $html_content = !empty($file_uri) ? parse_html_doc_file($file_uri) : '';
        $listed = 0;
        $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
        acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
      } elseif($file_name === 'FARMTOC') {
        $field_part_number = '';
        $field_sub_part_number = '';
        $field_doc_type = '';
        $tags_array = array('FAR');
        $subchapter = '';
        $node_title = parse_html_page_title($file_uri, 'title');
        $html_content = !empty($file_uri) ? parse_html_doc_file($file_uri) : '';
        $listed = 0;
        $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
        acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
      } else {
        $field_part_number = '';
        $field_sub_part_number = '';
        $field_doc_type = '';
        $tags_array = array('FAR');
        $subchapter = '';
        $node_title = parse_html_page_title($file_uri, 'title');
        $html_content = !empty($file_uri) ? parse_html_doc_file($file_uri) : '';
        $listed = 0;
        $pdf_path = get_pdf_file_path($a_tag_href, $pdf);
        acquisition_migrate_content($c_type, $user->uid, $node_title, $html_content, $field_part_number, $field_sub_part_number, $field_doc_type, $subchapter, $file_uri, $tags_array, $listed, $pdf_path, $zip_source);
      }
    }
  }
  $nids = array();
  if(!empty($file_names)) {
    $nids = _get_update_diff($file_names, $c_type);
    _unpublish_update_diff_nodes($nids);
    if(!empty($nids)) {
      watcher('current_uploads', $c_type, implode(", ", $nids) . ' nodes got unpublished');
    }
  }
}

/**
 * @param
 *  $nids - array
 */
function _unpublish_update_diff_nodes($nids) {
  $nodes = node_load_multiple($nids);
  foreach ($nodes as $node) {
    $node->status = 0;
    node_save($node);
  }
}

/**
 * @param
 *  $file_names - array()
 *    array of all filenames parsed from FARMTOCP html file.
 *  $c_type - string
 *    either GSAM or FAR content_type
 */
function _get_update_diff($file_names, $c_type, $index = 1) {
  $node_info = get_node_info(null, $c_type, 'all', $index, null);
  $nid = array();
  foreach($node_info as $info) {
    $file_path = strstr($info['file_path'], '.html', true);
    $file_path = substr($file_path, strpos($file_path, 'html/') + strlen('html/'));
    if(!in_array($file_path, array_filter($file_names))) {
      $nid[] = $info['nid'];
    }
  }
  return $nid;
}

/**
 * FAR Subchapters
 */
function get_far_subchapter($pfn = 0) {
  switch ($pfn) {
    case ($pfn > 0 && $pfn <= 4):
      $subchapter = "Subchapter A-General";
      break;
    case ($pfn >= 5 && $pfn <= 12):
      $subchapter = "Subchapter B-Competition and Acquisition Planning";
      break;
    case ($pfn >= 13 && $pfn <= 18):
      $subchapter = "Subchapter C-Contracting Methods and Contract Types";
      break;
    case ($pfn >= 19 && $pfn <= 26):
      $subchapter = "Subchapter D-Socioeconomic Programs";
      break;
    case ($pfn >= 27 && $pfn <= 33):
      $subchapter = "Subchapter E-General Contracting Requirements";
      break;
    case ($pfn >= 34 && $pfn <= 41):
      $subchapter = "Subchapter F-Special Categories of Contracting";
      break;
    case ($pfn >= 42 && $pfn <= 51):
      $subchapter = "Subchapter G-Contract Management";
      break;
    case ($pfn >= 52 && $pfn <= 53):
      $subchapter = "Subchapter H-Cluases and Forms";
      break;
    default:
      $subchapter = false;
      break;
  }
  return $subchapter;
}
