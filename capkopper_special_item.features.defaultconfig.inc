<?php
/**
 * @file
 * capkopper_special_item.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function capkopper_special_item_defaultconfig_features() {
  return array(
    'capkopper_special_item' => array(
      'views_default_views' => 'views_default_views',
    ),
  );
}

/**
 * Implements hook_defaultconfig_views_default_views().
 */
function capkopper_special_item_defaultconfig_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'special_items';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'capkopper_special_item';
  $view->human_name = 'Special items';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Manage Special items';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'plus';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer capkopper_special_item';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Order by';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'item_id' => 'item_id',
    'label' => 'label',
    'type' => 'type',
    'language' => 'language',
    'status' => 'status',
    'created' => 'created',
    'name' => 'name',
    'edit_capkopper_special_item' => 'edit_capkopper_special_item',
    'delete_capkopper_special_item' => 'edit_capkopper_special_item',
    'clone_capkopper_special_item' => 'edit_capkopper_special_item',
    'export_capkopper_special_item' => 'edit_capkopper_special_item',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'item_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'label' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'language' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_capkopper_special_item' => array(
      'align' => '',
      'separator' => ' - ',
      'empty_column' => 0,
    ),
    'delete_capkopper_special_item' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'clone_capkopper_special_item' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'export_capkopper_special_item' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty text';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<p>There is no existing items.</p>';
  $handler->display->display_options['empty']['area']['format'] = 'panopoly_wysiwyg_text';
  /* Relationship: Special item: Creator */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'capkopper_special_item';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Special item: Special item ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'capkopper_special_item';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  /* Field: Special item: Label */
  $handler->display->display_options['fields']['label']['id'] = 'label';
  $handler->display->display_options['fields']['label']['table'] = 'capkopper_special_item';
  $handler->display->display_options['fields']['label']['field'] = 'label';
  $handler->display->display_options['fields']['label']['link_to_entity'] = 0;
  /* Field: Special item: Special item type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'capkopper_special_item';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = 'Type';
  /* Field: Special item: Language */
  $handler->display->display_options['fields']['language']['id'] = 'language';
  $handler->display->display_options['fields']['language']['table'] = 'capkopper_special_item';
  $handler->display->display_options['fields']['language']['field'] = 'language';
  /* Field: Special item: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'capkopper_special_item';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* Field: Special item: Date submitted */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'capkopper_special_item';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'panopoly_time';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  /* Field: Special item: Edit Link */
  $handler->display->display_options['fields']['edit_capkopper_special_item']['id'] = 'edit_capkopper_special_item';
  $handler->display->display_options['fields']['edit_capkopper_special_item']['table'] = 'capkopper_special_item';
  $handler->display->display_options['fields']['edit_capkopper_special_item']['field'] = 'edit_capkopper_special_item';
  $handler->display->display_options['fields']['edit_capkopper_special_item']['label'] = 'Actions';
  /* Field: Special item: Delete Link */
  $handler->display->display_options['fields']['delete_capkopper_special_item']['id'] = 'delete_capkopper_special_item';
  $handler->display->display_options['fields']['delete_capkopper_special_item']['table'] = 'capkopper_special_item';
  $handler->display->display_options['fields']['delete_capkopper_special_item']['field'] = 'delete_capkopper_special_item';
  /* Field: Special item: Clone Link */
  $handler->display->display_options['fields']['clone_capkopper_special_item']['id'] = 'clone_capkopper_special_item';
  $handler->display->display_options['fields']['clone_capkopper_special_item']['table'] = 'capkopper_special_item';
  $handler->display->display_options['fields']['clone_capkopper_special_item']['field'] = 'clone_capkopper_special_item';
  /* Field: Special item: Export Link */
  $handler->display->display_options['fields']['export_capkopper_special_item']['id'] = 'export_capkopper_special_item';
  $handler->display->display_options['fields']['export_capkopper_special_item']['table'] = 'capkopper_special_item';
  $handler->display->display_options['fields']['export_capkopper_special_item']['field'] = 'export_capkopper_special_item';
  /* Sort criterion: Special item: Date changed */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'capkopper_special_item';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  /* Sort criterion: Special item: Label */
  $handler->display->display_options['sorts']['label']['id'] = 'label';
  $handler->display->display_options['sorts']['label']['table'] = 'capkopper_special_item';
  $handler->display->display_options['sorts']['label']['field'] = 'label';
  /* Filter criterion: Special item: Label */
  $handler->display->display_options['filters']['label']['id'] = 'label';
  $handler->display->display_options['filters']['label']['table'] = 'capkopper_special_item';
  $handler->display->display_options['filters']['label']['field'] = 'label';
  $handler->display->display_options['filters']['label']['operator'] = 'contains';
  $handler->display->display_options['filters']['label']['exposed'] = TRUE;
  $handler->display->display_options['filters']['label']['expose']['operator_id'] = 'label_op';
  $handler->display->display_options['filters']['label']['expose']['label'] = 'Label';
  $handler->display->display_options['filters']['label']['expose']['operator'] = 'label_op';
  $handler->display->display_options['filters']['label']['expose']['identifier'] = 'label';
  $handler->display->display_options['filters']['label']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['label']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['label']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['label']['expose']['autocomplete_min_chars'] = '0';
  $handler->display->display_options['filters']['label']['expose']['autocomplete_field'] = 'label';
  $handler->display->display_options['filters']['label']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['label']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['label']['expose']['autocomplete_dependent'] = 0;
  /* Filter criterion: Special item: Special item type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'capkopper_special_item';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Special item: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'capkopper_special_item';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['exposed'] = TRUE;
  $handler->display->display_options['filters']['language']['expose']['operator_id'] = 'language_op';
  $handler->display->display_options['filters']['language']['expose']['label'] = 'Language';
  $handler->display->display_options['filters']['language']['expose']['operator'] = 'language_op';
  $handler->display->display_options['filters']['language']['expose']['identifier'] = 'language';
  $handler->display->display_options['filters']['language']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['language']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Special item: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'capkopper_special_item';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );

  /* Display: System */
  $handler = $view->new_display('system', 'System', 'admin_overview');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['path'] = 'admin/content/special-item';
  $export['special_items'] = $view;

  return $export;
}
