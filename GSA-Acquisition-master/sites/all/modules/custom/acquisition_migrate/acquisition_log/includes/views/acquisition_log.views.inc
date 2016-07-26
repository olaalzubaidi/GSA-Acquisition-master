<?php

/**
 * Implements hook_views_data().
 */
function acquisition_log_views_data() {

  $data['acquisition_log']['table']['group'] = t('Acquisition Log');
  $data['acquisition_log']['table']['base'] = array(
    'title' => t('Acquisition Log'),
    'help' => t('Contains records we want exposed to Views.'),
  );

  $data['acquisition_log']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  // The LID field
  $data['acquisition_log']['lid'] = array(
    'title' => t('Log ID'),
    'help' => t('The record lid'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
	);

  // The Type field
  $data['acquisition_log']['type'] = array(
    'title' => t('Type'),
    'help' => t('The record type'),
    'field' => array(
      'handler' => 'views_handler_field',
      ),
    'sort' => array(
      'handler' => 'views_handler_sort',
      ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      ),
	);

  // The Content Type field
  $data['acquisition_log']['content_type'] = array(
    'title' => t('Content Type'),
    'help' => t('The record content_type'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
	);

  // The Message field
  $data['acquisition_log']['message'] = array(
    'title' => t('Message'),
    'help' => t('The record message'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
	);

  // The Request_URI field
  $data['acquisition_log']['request_uri'] = array(
    'title' => t('URI'),
    'help' => t('The record request_uri'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
	);

  // The IP field
  $data['acquisition_log']['ip'] = array(
    'title' => t('IP'),
    'help' => t('The record ip'),
    'field' => array(
      'handler' => 'views_handler_field',
      ),
    'sort' => array(
      'handler' => 'views_handler_sort',
      ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      ),
	);

  // The Timestamp field
  $data['acquisition_log']['timestamp'] = array(
    'title' => t('Date'),
    'help' => t('The record timestamp'),
    'field' => array(
      'handler' => 'views_handler_field_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
		),
	);

  // The User ID field
  $data['acquisition_log']['uid'] = array(
    'title' => t('User ID'),
    'help' => t('The record uid'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'relationship' => array(
      'base' => 'users',
      'field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('Users'),
    ),
    'argument' => array(
      'handler' => 'views_handler_argument',
      'numeric' => TRUE,
      'validate type' => 'uid',
    ),
  );

  return $data;
}