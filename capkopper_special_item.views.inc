<?php

/**
 * @file
 * Integrate capKopper Special Item module with Views.
 */

/**
 * Implements hook_views_data_alter()
 */
function capkopper_special_item_views_data_alter(&$data) {
  $data['capkopper_special_item']['item_id']['field'] = array(
    'handler' => 'Drupal\\capkopper_special_item\\Views\\Handler\\Field\\Item',
    'click sortable' => TRUE,
  );

  $data['capkopper_special_item']['label']['field'] = array(
    'handler' => 'Drupal\\capkopper_special_item\\Views\\Handler\\Field\\Item',
    'click sortable' => TRUE,
  );

  $data['capkopper_special_item']['uid'] = array(
    'title' => t('Creator'),
    'help' => t('Relate a special item to the user who created it.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
      'label' => t('Special item creator'),
    ),
  );

  $data['capkopper_special_item']['link_capkopper_special_item'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the special item.'),
      'handler' => 'Drupal\\capkopper_special_item\\Views\\Handler\\Field\\ItemLink',
    ),
  );

  $data['capkopper_special_item']['edit_capkopper_special_item'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the special item.'),
      'handler' => 'Drupal\\capkopper_special_item\\Views\\Handler\\Field\\ItemEditLink',
    ),
  );

  $data['capkopper_special_item']['delete_capkopper_special_item'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the special item.'),
      'handler' => 'Drupal\\capkopper_special_item\\Views\\Handler\\Field\\ItemDeleteLink',
    ),
  );

  $data['capkopper_special_item']['clone_capkopper_special_item'] = array(
    'field' => array(
      'title' => t('Clone Link'),
      'help' => t('Provide a link to clone the special item.'),
      'handler' => 'Drupal\\capkopper_special_item\\Views\\Handler\\Field\\ItemCloneLink',
    ),
  );

  $data['capkopper_special_item']['export_capkopper_special_item'] = array(
    'field' => array(
      'title' => t('Export Link'),
      'help' => t('Provide a link to export the special item.'),
      'handler' => 'Drupal\\capkopper_special_item\\Views\\Handler\\Field\\ItemExportLink',
    ),
  );
}
