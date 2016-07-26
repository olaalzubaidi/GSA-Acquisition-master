<?php

/**
 * @param
 *  $file - file object from hook_file_insert()
 *  Extract zip files
 */
function unarchive_zip_file($file) {
  $uri = $file->uri;
  // Do not use $file->filename
  //  Reason is if duplicate file is allowed, Drupal will append (Underscore + Number).
  //  $file->filename gives us original filename like FAC 2005-78-1 HTML Files (Current) .zip
  //  To get filename with appended we need to manipulate string like $file_name below.
  // $filename = $file->filename;
  $filesize = $file->filesize;
  if(!empty($uri)) {
    $zip_file_path = getcwd() . '/sites/default/files/' . substr($uri, strlen('public://'));
    $file_name = substr($file->uri, strpos($file->uri, 'uploads/') + strlen('uploads/')); // FAC 2005-78-1 HTML Files (Current) _0.zip
    $zip_filename = strstr($file_name, '.zip', true); // FAC 2005-78-1 HTML Files (Current) _0
    $zip_destination_path = strstr($uri, $file_name, true); // public://current/far/uploads/
    $existing_folders = array();
    $existing_folders = get_existing_folder_name($zip_destination_path);
    $folder_properties = array();
    $folder_properties = get_folder_properties($zip_destination_path);

    // get content-type from path
    $c_type = strpos($file->uri, 'far') ? 'far' : 'gsam';
  }

  $zip = new ZipArchive;
  if($zip->open($zip_file_path, ZipArchive::CREATE) === TRUE) {
    $inside_zip_folder_name = array();
    $inside_zip_folder_name = get_zip_content_folder($zip); // FAC 2005-78-1 HTML Files (Current) // Output
    if(in_array($zip_filename, $existing_folders)) {
      foreach($folder_properties as $property) {
        if($zip_filename == $property['getFilename'] && $property['getMTime'] === $file->timestamp && $property['getOwner'] === $file->uid) {
          // identical zip file uploaded and unzipped by the same user at the same time
          // this scenario should not occur at all, the probability that it may occur is almost zero.
          $user = user_load($file->uid);
          $msg = $property['getFilename'] . "/ : has already been uploaded by user " . $user->name . " at " . date('m/d/y g:ia', $property['getMTime']);
          drupal_set_message($msg, 'warning');
          watcher('current_uploads', $c_type, 'Duplicate! File has already been uploaded by same user and same time. Unarchiving aborted!');
        }
        elseif($zip_filename == $property['getFilename'] && $property['getMTime'] !== $file->timestamp && $property['getOwner'] === $file->uid) {
          // zip file uploaded and unzipped by the same user but different time
          acquisition_migrate_mkdir($zip_destination_path, $zip_filename, $zip);
          watcher('current_uploads', $c_type, 'Duplicate! File has already been uploaded by the same user at ' . date('m/d/y g:ia', $property['getMTime']));
        }
        elseif($zip_filename == $property['getFilename'] && $property['getMTime'] === $file->timestamp && $property['getOwner'] !== $file->uid) {
          // zip file uploaded and unzipped by at the same time by two different users
          $user = user_load($property['getOwner']);
          acquisition_migrate_mkdir($zip_destination_path, $zip_filename, $zip);
          watcher('current_uploads', $c_type, 'Duplicate! File has already been uploaded by another user ' . $user->name);
        }
        elseif($zip_filename == $property['getFilename'] && $property['getMTime'] !== $file->timestamp && $property['getOwner'] !== $file->uid) {
          // identical zip file uploaded and unzipped by another user at different time
          $user = user_load($property['getOwner']);
          acquisition_migrate_mkdir($zip_destination_path, $zip_filename, $zip);
          watcher('current_uploads', $c_type, 'Duplicate! File has already been uploaded by ' . $user->name . ' at ' . date('m/d/y g:ia', $property['getMTime']));
        }
      }
    } elseif(in_array($zip_filename, $inside_zip_folder_name)) {
      if(count($inside_zip_folder_name) == 1) {
        // if zip file name shares the same name with folder in the zip AND if only 1 folder in zip file
        // we don't have to mkdir, just extract it in the uploads dir
        $zip->extractTo($zip_destination_path);
      } elseif(count($inside_zip_folder_name) > 1) {
        // zip file shares same name with folder within zip but more than 1 folder in the zip
        // in this case we want to extract all inside a single container folder which has same name with zip file
        // therefore we need to mkdir in uploads dir
        acquisition_migrate_mkdir($zip_destination_path, $zip_filename, $zip);
      }
    } elseif(!in_array($zip_filename, $inside_zip_folder_name) AND in_array($zip_filename, $existing_folders)) {
      // folder that shares same name with zip file doesn't exist in uploads/ dir XOR in zip file as well
      acquisition_migrate_mkdir($zip_destination_path, $zip_filename, $zip);
    } elseif(in_array($zip_filename, $inside_zip_folder_name) AND !in_array($zip_filename, $existing_folders)) {
      // folder that shares same name with zip file doesn't exist in uploads/ dir AND exists in zip file
      $zip->extractTo($zip_destination_path);
    } elseif(!in_array($zip_filename, $inside_zip_folder_name) && !in_array($zip_filename, $existing_folders)) {
      // folder that shares same name with zip file doesn't exist in uploads/ dir AND in zip file as well
      acquisition_migrate_mkdir($zip_destination_path, $zip_filename, $zip);
    }
    $zip->close();
  } else {
      switch($zip_file_path) {
        case ZipArchive::ER_EXISTS:
          $ErrMsg = "File already exists.";
          break;
        case ZipArchive::ER_INCONS:
          $ErrMsg = "Zip archive inconsistent.";
          break;
        case ZipArchive::ER_MEMORY:
          $ErrMsg = "Malloc failure.";
          break;
        case ZipArchive::ER_NOENT:
          $ErrMsg = "No such file.";
          break;
        case ZipArchive::ER_NOZIP:
          $ErrMsg = "Not a zip archive.";
          break;
        case ZipArchive::ER_OPEN:
          $ErrMsg = "Can't open file.";
          break;
        case ZipArchive::ER_READ:
          $ErrMsg = "Read error.";
          break;
        case ZipArchive::ER_SEEK:
          $ErrMsg = "Seek error.";
          break;
        default:
          $ErrMsg = "Unknow (Code: 1000)";
          break;
      }
    drupal_set_message(t($ErrMsg), 'warning');
    watcher('current_uploads', $c_type, $ErrMsg);
  }
}

/**
 * @param
 *  $zip_destination_path - zip destination path
 *  $zip - zip file uri
 *
 *  Create directory if not exists
 */
function acquisition_migrate_mkdir($zip_destination_path, $zip_filename, $zip) {
  $dir = $zip_destination_path . $zip_filename;
  if(!file_exists($dir)) {
    drupal_mkdir($dir);
    drupal_chmod($dir, 0751);
    $new_dir = $dir;
    $zip->extractTo($new_dir);
  }
  return;
}

/**
 * @param
 *  $zip - zip file object which is about to be unzipped
 *
 *  Get all files inside a zip file
 */
function get_zip_content_file($zip) {
  $zip_content_file = array();
  for($i = 0; $i < $zip->numFiles; $i++) {
    $zip_content_file[] = $zip->getNameIndex($i, ZipArchive::FL_UNCHANGED);
  }
  return $zip_content_file;
}

/**
 * @param
 *  $zip - zip file object which is about to be unzipped
 *
 *  Get all none duplicate folders inside zip
 */
function get_zip_content_folder($zip) {
  $zip_content_folders = array();
  $zip_content_folder_old = '';
  for($i = 0; $i < $zip->numFiles; $i++) {
    $zip_content_folder = $zip->getNameIndex($i, ZipArchive::FL_UNCHANGED);
    $zip_content_folder_new = strstr($zip_content_folder, '/', true);
    if($zip_content_folder_new !== $zip_content_folder_old) {
      $zip_content_folders[] = $zip_content_folder_new;
    }
    $zip_content_folder_old = $zip_content_folder_new;
  }
  return $zip_content_folders;
}

/**
 * @param
 *  $zip - zip file object which is about to be unzipped
 *
 *  Get details of each file inside a zip file
 */
function get_zip_content_file_detail($zip) {
  $zip_content_file_detail = array();
  for($i = 0; $i < $zip->numFiles; $i++) {
    $zip_content_file_detail[] = $zip->statIndex($i, ZipArchive::FL_UNCHANGED);
  }
  return $zip_content_file_detail;
}

/**
 * @param
 *  $path - string containing path to destination folder
 * @return
 *  arrays of all existing folders
 */
function get_existing_folder_name($path) {
  $existing_folders = array();
  $existing_dirs = get_folder_properties($path);
  if(!empty($existing_dirs)) {
    foreach($existing_dirs as $existing_folder) {
      $existing_folders[] = $existing_folder['getFilename'];
    }
  }
  $existing_folders = array_diff($existing_folders, array('__MACOSX')); // remove un-wanted folder
  return array_values($existing_folders); // reset array keys
}

/**
 * @param
 *  $path - string containing path to destination folder
 * @return
 *  $dir_info - folder properties/info/attributes
 */
function get_folder_properties($path) {
  $dir_info = array();
  // If $path does not exist an exception error will be thrown
  // The way to go around this is to check if file really exists
  // If file does not exist just return nothing
  if (file_exists($path)) {
    foreach (new DirectoryIterator($path) as $file) {
      if ($file->isDot()) continue;
      if ($file->isDir()) {
        if ($file->getFilename() != '.' || $file->getFilename() != '..') {
          $dir_info[] = array(
            'getCTime'    => $file->getCTime(),
            'getMTime'    => $file->getMTime(),
            'getFilename' => $file->getFilename(),
            'getPath'     => $file->getPath(),
            'getPathname' => $file->getPathname(),
            'getOwner'    => $file->getOwner(),
            'getPerms'    => $file->getPerms(),
            'isFile'      => $file->isFile(),
            'getSize'     => $file->getSize(),
            'isReadable'  => $file->isReadable(),
            'isWritable'  => $file->isWritable(),
          );
        }
      }
    }
    if(!empty($dir_info)) {
      return $dir_info;
    }
  }
}