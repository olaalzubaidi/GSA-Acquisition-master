<?php

/**
 * General query for FAR or GSAM
 */
function get_part_subpart($type = '', $doc_type = NULL, $listed_in_index = NULL, $part_number = NULL, $sub_part_number = NULL, $status = 1) {
  $query = db_select('node', 'n');
  $query->join('field_data_field_part_number', 'p', 'n.nid = p.entity_id');
  $query->join('field_data_field_sub_part_number', 'sp', 'n.nid = sp.entity_id');
  $query->join('field_data_field_doc_type', 'dt', 'n.nid = dt.entity_id');
  $query->join('field_data_field_file_location', 'fl', 'n.nid = fl.entity_id');
  $query->join('field_data_field_listed_in_index', 'li', 'n.nid = li.entity_id');
  $query->distinct();
  $query->fields('n',array('nid', 'title', 'status'));
  $query->fields('p',array('field_part_number_value'));
  $query->fields('sp',array('field_sub_part_number_value'));
  $query->fields('dt',array('field_doc_type_value'));
  $query->fields('fl',array('field_file_location_value'));
  $query->fields('li',array('field_listed_in_index_value'));
  (($type != '') ? ($query->condition('type', $type, '=')) : false);
  (!empty($doc_type) ? ($query->condition('dt.field_doc_type_value', $doc_type, '=')) : false);
  (!empty($part_number) ? ($query->condition('p.field_part_number_value', $part_number, '=')) : false);
  (!empty($sub_part_number) ? ($query->condition('sp.field_sub_part_number_value', $sub_part_number, '=')) : false);
  (!empty($listed_in_index) ? ($query->condition('li.field_listed_in_index_value', $listed_in_index, '=')) : $query->condition('li.field_listed_in_index_value', 0, '='));
  $query->condition('status', $status, '=');
  $results = $query->execute();
  $rtn = array();
  foreach($results as $result) {
    $rtn[] = $result;
  }
  return $rtn;
}

/**
 * Query results for FAR or GSAM file_path
 */
function get_part_subpart_file_path($type = '', $doc_type, $part_number, $sub_part_number = NULL) {
  $results = get_part_subpart($type, $doc_type, 1, $part_number, $sub_part_number);
  foreach($results as $result) {
    if($result) {
      return $result->field_file_location_value;
    } else {
      return false;
    }
  }
}

/**
 * Query results for FAR or GSAM node_title
 */
function get_part_subpart_node_title($type = '', $doc_type, $part_number, $sub_part_number = NULL) {
  $results = get_part_subpart($type, $doc_type, 1, $part_number, $sub_part_number);
  foreach($results as $result) {
    return $result->title;
  }
}

/**
 * Query results for FAR or GSAM part_number
 */
function get_part_number($type = '') {
  $results = get_part_subpart($type, 'Part', 1);
  $part_number = array();
  foreach($results as $result) {
    $part_number[] = $result;
  }
  return $part_number;
}

/**
 * Query results for FAR or GSAM subpart_number
 */
function get_subpart_number($type = '', $part_number) {
  $results = get_part_subpart($type, 'Subpart', 1, $part_number);
  $subpart_number = array();
  foreach($results as $result) {
    if(!empty($result)) {
      $subpart_number[] = $result;
    }
  }
  return $subpart_number;
}

/**
 * Query results for FAR/GSAM Part/Subpart listed in TOC Index
 */
function get_listed_in_index($type = '', $listed_in_index = 1) {
  $results = get_part_subpart($type, null, $listed_in_index);
  $subpart_number = array();
  foreach($results as $result) {
    if(!empty($result)) {
      $subpart_number[] = $result;
    }
  }
  return $subpart_number;
}

/**
 * Query results for FAR or GSAM node_title
 */
function get_part_subpart_nid($type = '', $doc_type, $part_number, $sub_part_number = NULL) {
  $results = get_part_subpart($type, $doc_type, 1, $part_number, $sub_part_number);
  foreach($results as $result) {
    return $result->nid;
  }
}


/**
 * Function that returns an associative array of Parts and Subparts
 */
function get_part_subpart_info($c_type = NULL) {
  $sql = "
    SELECT n.nid, n.title, n.type, p.field_part_number_value, s.field_sub_part_number_value, l.field_file_location_value, i.field_listed_in_index_value, d.field_doc_type_value
    FROM {node} n
    INNER JOIN {field_data_field_part_number} p ON n.nid = p.entity_id
    INNER JOIN {field_data_field_sub_part_number} s ON n.nid = s.entity_id
    INNER JOIN {field_data_field_file_location} l ON n.nid = l.entity_id
    INNER JOIN {field_data_field_listed_in_index} i ON n.nid = i.entity_id
    INNER JOIN {field_data_field_doc_type} d ON n.nid = d.entity_id
    WHERE n.type = :type AND n.status = 1 AND i.field_listed_in_index_value = 1";

    $results = db_query($sql, array(':type' => $c_type));
    $results = $results->fetchAll();
    $p = array();
    foreach($results as $result) {
      $subpart = array();
      if($result->field_doc_type_value == 'Part'){
        $p[$result->field_part_number_value] = array(
          'nid'         => $result->nid,
          'title'       => $result->title,
          'doc_type'    => $result->field_doc_type_value,
          'url'         => $result->field_file_location_value,
          'part'        => $result->field_part_number_value,
          'listed'      => $result->field_listed_in_index_value,
          'subpart'     => NULL
        );
      }
      elseif($result->field_doc_type_value == 'Subpart') {
        $subpart =  array(
          'nid'       => $result->nid,
          'title'     => $result->title,
          'doc_type'  => $result->field_doc_type_value,
          'url'       => $result->field_file_location_value,
          'part'      => $result->field_part_number_value,
          'listed'    => $result->field_listed_in_index_value,
          'subpart'   => $result->field_sub_part_number_value
        );
        $ap[$result->field_part_number_value]['subpart'][$result->field_sub_part_number_value] = $subpart;
      }
    }
    if(!empty($ap)) {
      foreach($ap as $key => $val) {
        $p[$key]['subpart'] = $val['subpart'];
      }
    }
  return $p;
}