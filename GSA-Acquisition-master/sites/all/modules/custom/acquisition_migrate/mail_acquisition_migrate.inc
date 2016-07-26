<?php

/**
 * @param
 *  $form_values - arrays
 *   - Array values needed at the time of email notification processing.
 */
function acquisition_migrate_mail_send($form_values) {
  $module = 'acquisition_migrate';
  $key = 'upload_notification';
  $to = $form_values['email'];
  $from = variable_get('site_mail');
  $params = $form_values;
  $language = language_default();
  $send = TRUE;
  $result = drupal_mail($module, $key, $to, $language, $params, $from, $send);
  if ($result['result'] !== TRUE) {
    drupal_set_message(t('There was a problem sending your message and it was not sent.'), 'error');
    watcher('current_uploads', $form_values['upload_type'], 'Email sending failed');
  } else {
    watcher('current_uploads', $form_values['upload_type'], 'Email notification sent');
  }
}

/**
 * Implements hook_mail()
 */
function acquisition_migrate_mail($key, &$message, $params) {
  global $user;
  $options = array(
    'langcode' => $message['language']->language,
  );
  $from = variable_get('site_mail');

  switch ($key) {
    case 'upload_notification':
      $message['headers'] = array(
        'MIME-Version' => '1.0',
        'Content-Type' => 'text/html; charset=UTF-8; format=flowed; delsp=yes',
        'Content-Transfer-Encoding' => '8Bit',
        'X-Mailer' => 'Drupal',
        'From' => $from,
        'Sender' => $from,
        'Return-Path' => $from,
      );
      $message['subject'] = t('@uploading e-mail sent from @site-name', array('@site-name' => variable_get('site_name', 'Drupal'), '@uploading' => check_plain($params['subject'])), $options);
      $message['body'][] = check_plain($params['message']);
      break;
  }
}

/**
 * @param
 *  $node - object
 *   - Node object with required values to construct e-mail message.
 */
function get_email_message($node) {
  if ($node->type === 'current_uploads') {
    global $base_url, $user;

    // get current uploaded file's $file obj
    $file = load_file_obj($node);

    $uid = $node->uid;
    $name = $node->name;
    $title = $node->title;
    $nid = $node->nid;
    $created = $node->created;
    !empty($node->changed) ? $changed = $node->changed : $changed = false;
    !empty($node->revision_uid) ? $revision_uid = user_load($node->revision_uid) : $revision_uid = false;
    !empty($revision_uid->name) ? $revision_uid = $revision_uid->name : $revision_uid = false;
    !empty($file) ? $filename = $file->filename : $filename = 'File either got removed or not uploaded';
    $upload_type = $node->field_upload_type['und'][0]['value'];
    $url = $base_url . '/node/' . $nid;
    $path = t('<a href="@url">You may visit the page from here.</a>', array('@url' => $url));

    $message = '';
    $message .= t($base_url . ' admin sent you details of zip file you uploaded minutes ago.<br>');
    $message .= 'Author:        ' . $name . "<br>";
    $message .= 'Title:         ' . $title . "<br>";
    !empty($nid) ? $message .= 'Node ID:   ' . $nid . "<br>" : false;
    $message .= 'Created:      ' . date("M j, Y, g:i a", $created) . "<br>";
    !empty($changed) ? $message .= 'Revised:     ' . date("M j, Y, g:i a", $changed) . "<br>" : false;
    !empty($revision_uid) ? $message .= 'Revised by:   ' . $revision_uid . "<br>" : false;
    !empty($filename) ? $message .= 'Filename:   ' . $filename . "<br>" : false;
    $message .= 'Upload type:  ' . $upload_type . "<br>";
    $message .= $path . "<br>";

    $subject = 'Uploads Notification';

    $html_message = '<!DOCTYPE HTML>'.
    '<head>'.
      '<meta http-equiv="content-type" content="text/html">'.
      '<title>' . $subject .'</title>'.
    '</head>'.
    '<body>'.
      '<div id="outer" style="width: 100%; margin: 0 auto; margin-top: 10px;">'.
        '<div id="inner" style="width: 95%;margin: 0 auto;background-color: #fff;font-family: Open Sans,Arial,sans-serif;font-size: 13px;font-weight: normal; line-height: 1.4em;color: #444; margin-top: 10px;">'.
          '<p>'.$message.'</p>'.
        '</div>'.
      '</div>'.
    '</body>'.
    '</html>';

    $form_values = array();
    $form_values['email'] = $user->mail . ',' . variable_get('site_mail', 'Drupal');
    $form_values['subject'] = $subject;
    $form_values['message'] = $html_message;
    $form_values['upload_type'] = $upload_type;
    return $form_values;
  }
}