<?php
/**
 * @file
 * Definition of the node plugin.
 */

$plugin = array(
  // _ctools_registry_files_alter() will never find the class file and claim for
  // missing plugin class file, but we don't care of that since the file is
  // loaded using PSR-4.
  'handler' => 'Drupal\\capkopper_special_item\\Panelizer\\Item',
  'entity path' => 'special-item/%capkopper_special_item',
  'uses page manager' => TRUE,
  'hooks' => array(
    'menu' => TRUE,
    'admin_paths' => TRUE,
    'permission' => TRUE,
    'panelizer_defaults' => TRUE,
    'default_page_manager_handlers' => TRUE,
    'form_alter' => TRUE,
    //'page_alter' => TRUE,
    'views_data_alter' => TRUE,
  ),
);
