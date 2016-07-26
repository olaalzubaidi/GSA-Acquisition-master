<?php

/**
 * Prepare all params to be pased to function that creates archives of current docs.
 */
function archive_current_far_gsam_docs($node) {
  // Get content type 'far' or 'gsam'
  $u_type = '';
  $u_type = strtoupper($node->field_upload_type['und'][0]['value']); // GSAM

  $fac_number = '';
  $uid = '';
  $upload_type = '';
  $year = '';
  $effective_date = '';
  $results = get_last_upload($u_type);
  foreach($results as $result) {
    $fac_number = $result->field_fac_number_value;
    $uid = $result->uid;
    $upload_type = strtolower($result->field_upload_type_value);
    $effective_date = $result->field_archive_effective_date_value;
  }
  // current uploads fac_number
  $fac_n = '';
  // below lines of code depend on query $result above
  if(!empty($result) || !empty($upload_type)) {
    switch ($upload_type) {
      case 'far':
        $archive_name = array(
          'html'        => 'FAC ' .  $fac_number . ' HTML Files.zip',
          'pdf'         => 'FAC ' .  $fac_number . ' PDF.zip',
          'loose_leaf'  => 'FAC ' .  $fac_number . ' Loose_leaf.zip',
        );
        break;
      case 'gsam':
        $archive_name = array(
          'html'        => 'GSAM ' .  $fac_number . ' HTML Files.zip',
          'pdf'         => 'GSAM ' .  $fac_number . ' PDF.zip',
          'loose_leaf'  => 'FAC ' .  $fac_number . ' Loose_leaf.zip',
        );
        break;
    }

    // zip file destination dir
    $dest_html        = getcwd() . '/sites/default/files/current/' . $upload_type . '/zip/html/' . $archive_name['html'];
    $dest_pdf         = getcwd() . '/sites/default/files/current/' . $upload_type . '/zip/pdf/' . $archive_name['pdf'];
    $dest_loose_leaf  = getcwd() . '/sites/default/files/current/' . $upload_type . '/zip/loose_leaf/' . $archive_name['loose_leaf'];

    // current uploads fac_number
    $fac_n = $node->field_fac_number['und'][0]['value'];

    // last upload fac_number should bot be the same with current upload fac_number
    // if same fac_number current upload is not new, possibly an update of last upload
    // therefore we should not move files
    if(file_exists($dest_html) && $fac_n != $fac_number) {
      // create Archive nodes
      $title = $fac_number;
      $archive_type = $upload_type;
      $pdf_file = substr($dest_pdf, strpos($dest_pdf, 'sites/'));
      $zip_file = substr($dest_html, strpos($dest_html, 'sites/'));
      $loose_leaf = substr($dest_loose_leaf, strpos($dest_loose_leaf, 'sites/'));
      $year = date('Y', strtotime("$effective_date"));
      $tags_array = array($year, $archive_type);
      _archiver_node_generate($title, $uid, $tags_array, $year, $archive_type, $pdf_file, $zip_file, $loose_leaf, $fac_number, $effective_date);

      // remove current zipped html, pdf, loose_leaf docs
      exec('rm -rf ' . "'$dest_html'" . " '$dest_pdf'" . " '$dest_loose_leaf'");
    } elseif($fac_n == $fac_number) {
      watcher('archives', $upload_type, 'Archiving not allowed while updating last upload');
    }
  } else {
    watcher('archives', $u_type, 'Current file archiving unavailable');
  }
}

/**
 * Function that gets the last upload
 */
function get_last_upload($type) {
  $query = db_select('node', 'n');
  $query->join('field_data_field_fac_number', 'fn', 'n.nid = fn.entity_id');
  $query->join('field_data_field_upload_type', 'ut', 'n.nid = ut.entity_id');
  $query->join('field_data_field_archive_effective_date', 'ed', 'n.nid = ed.entity_id');
  $query->fields('n',array('uid','created'))
  ->fields('fn',array('field_fac_number_value'))
  ->fields('ut',array('field_upload_type_value'))
  ->fields('ed',array('field_archive_effective_date_value'))
  ->condition('type', 'current_uploads','=')
  ->condition('field_upload_type_value', $type,'=')
  ->orderBy('created', 'DESC')
  ->range(0,1);
  $results = $query->execute();

	$rsl = array();
	foreach($results as $result) {
		$rsl[] = $result;
	}
	return $rsl;
}

/**
 * During uploading and after files are moved to their destination
 *  - this function creates zip files of /html /pdf and /loose_leaf dirs
 *  - that are stored in /current/[far/gsam]/zip dir/.
 *  - These archived files will be moved to /archives dir on the next file upload.
 */
function zip_current_far_gsam_dir($node) {
  // Get content type 'far' or 'gsam'
  $upload_type = '';
  $upload_type = strtolower($node->field_upload_type['und'][0]['value']);
  $fac_number = '';
  $fac_number = $node->field_fac_number['und'][0]['value'];

  if(!empty($upload_type)) {
    switch ($upload_type) {
      case 'far':
        $archive_name = array(
          'html'        => 'FAC ' .  $fac_number . ' HTML Files.zip',
          'pdf'         => 'FAC ' .  $fac_number . ' PDF.zip',
          'loose_leaf'  => 'FAC ' .  $fac_number . ' Loose_leaf.zip',
        );
        break;
      case 'gsam':
        $archive_name = array(
          'html'        => 'GSAM ' .  $fac_number . ' HTML Files.zip',
          'pdf'         => 'GSAM ' .  $fac_number . ' PDF.zip',
          'loose_leaf'  => 'FAC ' .  $fac_number . ' Loose_leaf.zip',
        );
        break;
    }

    $archive_folders = array(
      'html'        => getcwd() . '/sites/default/files/current/' . $upload_type . '/html',
      'pdf'         => getcwd() . '/sites/default/files/current/' . $upload_type . '/pdf',
      'loose_leaf'  => getcwd() . '/sites/default/files/current/' . $upload_type . '/loose_leaf',
    );

    // zip file destination dir
    $dest_html        = getcwd() . '/sites/default/files/current/' . $upload_type . '/zip/html';
    $dest_pdf         = getcwd() . '/sites/default/files/current/' . $upload_type . '/zip/pdf';
    $dest_loose_leaf  = getcwd() . '/sites/default/files/current/' . $upload_type . '/zip/loose_leaf';

    // create dir if not there
    if(!file_exists($dest_html))
      drupal_mkdir($dest_html, 0755, true);
    if(!file_exists($dest_pdf))
      drupal_mkdir($dest_pdf, 0755, true);
    if(!file_exists($dest_loose_leaf))
      drupal_mkdir($dest_loose_leaf, 0755, true);

    // before new zip remove old stuff first
    exec('rm -rf ' . "$dest_html" . '/*' . " $dest_pdf" . '/*' . " $dest_loose_leaf" . '/*', $old_stuff_output, $old_stuff_result);
    if($old_stuff_result == 0) {
      watcher('current_uploads', $upload_type, 'Old ' . strtoupper($upload_type) . ' html, pdf, loose_leaf dirs removed');
    } else {
      watcher('current_uploads', $upload_type, 'Failed to remove old ' . strtoupper($upload_type) . ' html, pdf, loose_leaf dirs');
    }
    // zip
    $current = getcwd() . '/sites/default/files/current/' . $upload_type;
    exec('cd ' . $current . '; zip -r "' . $archive_name['html'] . '" html/* ; mv -f "' . $archive_name['html'] . '" ' . $dest_html, $exec_output, $exec_result);
    if($exec_result == 0) {
      watcher('current_uploads', $upload_type, 'Current ' . strtoupper($upload_type) . ' html dir archived');
    } else {
      watcher('current_uploads', $upload_type, 'Failed to archive current ' . strtoupper($upload_type) . ' html dir');
    }
    exec('cd ' . $current . '; zip -r "' . $archive_name['pdf'] . '" pdf/* ; mv -f "' . $archive_name['pdf'] . '" ' . $dest_pdf, $exec_output, $exec_result);
    if($exec_result == 0) {
      watcher('current_uploads', $upload_type, 'Current ' . strtoupper($upload_type) . ' pdf dir archived');
    } else {
      watcher('current_uploads', $upload_type, 'Failed to archive current ' . strtoupper($upload_type) . ' pdf dir');
    }
    exec('cd ' . $current . '; zip -r "' . $archive_name['loose_leaf'] . '" loose_leaf/* ; mv -f "' . $archive_name['loose_leaf'] . '" ' . $dest_loose_leaf, $exec_output, $exec_result);
    if($exec_result == 0) {
      watcher('current_uploads', $upload_type, 'Current ' . strtoupper($upload_type) . ' loose_leaf dir archived');
    } else {
      watcher('current_uploads', $upload_type, 'Failed to archive current ' . strtoupper($upload_type) . ' loose_leaf');
    }
  }
}

/**
 * Archives current document directories
 * Creates an archive content type node on the fly
 */
function _archiver_node_generate($title = '', $uid = '', $tags_array = array(), $year, $archive_type = '', $pdf_file = '', $zip_file = '', $loose_leaf = '', $fac_number = '', $archive_effective_date = '') {
  $node = new stdClass();
  $node->type = 'archives';
  $node->language = LANGUAGE_NONE;
  $node->title = $title;
  $node->uid = $uid;
  $node->status = 1;
  $node->comment = 0;
  $node->promote = 0;
  $node->sticky = 0;
  $node->revision = TRUE;
  $node->log = 1;
  node_object_prepare($node);

  // Insert Tags
  if(!empty($tags_array)) {
    foreach($tags_array as $tkey => $tval) {
      if($term = taxonomy_get_term_by_name($tval)) {
        //Assign an existing taxonomy
        $terms_array = array_keys($term);
        $node->field_tags['und'][$tkey]['tid'] = $terms_array[0];
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
            $node->field_tags['und'][$tkey]['tid'] = $tid;
          }
        }
      }
    }
  }
  $node->field_year['und'][0] = array(
    'value' => $year,
  );
  $node->field_archive_type['und']['0']['value'] = strtoupper($archive_type);

  $html = file_default_scheme() . '://archives/' . $archive_type . '/zip';
  $pdf  = file_default_scheme() . '://archives/' . $archive_type . '/pdf';
  $leaf = file_default_scheme() . '://archives/' . $archive_type . '/loose_leaf';

  // create dir if not there
  if(!file_exists($html))
    drupal_mkdir($html, 0755, true);
  if(!file_exists($pdf))
    drupal_mkdir($pdf, 0755, true);
  if(!file_exists($leaf))
    drupal_mkdir($leaf, 0755, true);

  //File Object Assign for pdf file
  if(!empty($pdf_file) && file_exists($pdf_file)) {
    $file = new StdClass();
    $file->uid = $uid;
    $file->uri = $pdf_file;
    $file->filename = basename($pdf_file);
    $dest = file_default_scheme() . '://archives/' . $archive_type . '/pdf/';
    $file = file_copy($file, $dest);
    $file->filemime = file_get_mimetype($file->uri);
    $file->status = 1;
    $file->display = 1;
    $file->description = basename($pdf_file);
    $node->field_pdf_file['und']['0'] = (array)$file;
  }

  //File Object Assign for zip file
  if(!empty($zip_file) && file_exists($zip_file)) {
    $file1 = new StdClass();
    $file1->uid = $uid;
    $file1->uri = $zip_file;
    $file1->filename = basename($zip_file);
    $dest1 = file_default_scheme() . '://archives/' . $archive_type . '/zip/';
    $file1 = file_copy($file1, $dest1);
    $file1->filemime = file_get_mimetype($file1->uri);
    $file1->status = 1;
    $file1->display = 1;
    $file1->description = basename($zip_file);
    $node->field_zip_file['und']['0'] = (array)$file1;
  }

  //File Object Assign for zip file
  if(!empty($loose_leaf) && file_exists($loose_leaf)) {
    $file2 = new StdClass();
    $file2->uid = $uid;
    $file2->uri = $loose_leaf;
    $file2->filename = basename($loose_leaf);
    $dest2 = file_default_scheme() . '://archives/' . $archive_type . '/loose_leaf/';
    $file2 = file_copy($file2, $dest2);
    $file2->filemime = file_get_mimetype($file2->uri);
    $file2->status = 1;
    $file2->display = 1;
    $file2->description = basename($loose_leaf);
    $node->field_loose_leaf['und']['0'] = (array)$file2;
  }

  $node->field_fac_number['und'][0]['value'] = $fac_number;
  $node->field_archive_effective_date['und'][0] = array(
    'value' => $archive_effective_date,
  );

  $node = node_submit($node);
  node_save($node);

  $f  = file_exists($pdf_file) ? $file->filename . ', ' : '';
  $f1 = file_exists($zip_file) ? $file1->filename . ', ' : '';
  $f2 = file_exists($loose_leaf) ? $file2->filename : '';
  $msg = $f . $f1 . $f2;
  watcher('archives', $archive_type, $msg . ' ARCHIVED');
}

/**
 * This function queries last archived node
 *  - Now there is no need for this function but we might use it later in  future
 *  - Just keep it commented as is
 */
//function _get_last_archive($fac_number = '', $zip_file_description = '', $title = NULL) {
//  $query = db_select('node', 'n');
//  $query->join('field_data_field_fac_number', 'f', 'f.entity_id = n.nid');
//  $query->join('field_data_field_archive_type', 't', 't.entity_id = n.nid');
//  $query->join('field_data_field_zip_file', 'z', 'z.entity_id = n.nid');
//  $query->fields('n',array('nid', 'title','created'));
//  $query->fields('f',array('field_fac_number_value'));
//  $query->fields('z',array('field_zip_file_description'));
//  $query->fields('t',array('field_archive_type_value'));
//  $query->condition('type', 'archives','=');
//  $query->condition('status', 1,'=');
//  $query->range(0,1);
//  !empty($title) ? $query->condition('title', $title,'=') : false;
//  !empty($fac_number) ? $query->condition('field_fac_number_value', $fac_number,'=') : false;
//  !empty($zip_file_description) ? $query->condition('field_zip_file_description', $zip_file_description,'=') : false;
//  $results = $query->execute()->fetchAll();
//
//  $db_result = array();
//  foreach($results as $result) {
//    if($result) {
//      $db_result[] = array(
//        'nid' => $result->nid,
//        'title' => $result->title,
//        'fac_number' => $result->field_fac_number_value,
//        'zip_file_description' => $result->field_zip_file_description,
//      );
//    }
//  }
//  return $db_result;
//}
