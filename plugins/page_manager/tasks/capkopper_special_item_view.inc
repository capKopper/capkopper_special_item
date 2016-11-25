<?php

/**
 * @file
 * Handle the 'Special item view' override task.
 *
 * This plugin overrides special-item/%capkopper_special_item and reroutes it to the
 * page manager, where a list of tasks can be used to service this request based
 * upon criteria supplied by access plugins.
 */

use Drupal\capkopper_special_item\Entity\Item as SpecialItem;

/**
 * Specialized implementation of hook_capkopper_special_item_task_tasks().
 */
function capkopper_special_item_capkopper_special_item_view_page_manager_tasks() {
  return array(
    // This is a 'page' task and will fall under the page admin UI
    'task type' => 'page',

    'title' => t('Special item template'),

    'admin title' => t('Special item template'),
    'admin description' => t('When enabled, this overrides the default Drupal behavior for displaying special item at <em>special-item/%capkopper_special_item</em>. If you add variants, you may use selection criteria such as special item type or language or user access to provide different views of Special items. If no variant is selected, the default Drupal special item view will be used. This page only affects Special items viewed as pages, it will not affect Special items viewed in lists or at other locations. Also please note that if you are using pathauto, aliases may make a special item to be somewhere else, but as far as Drupal is concerned, they are still at special-item/%capkopper_special_item.'),
    'admin path' => 'special-item/%capkopper_special_item',

    // Menu hooks so that we can alter the special-item/%capkopper_special_item menu
    // entry to point to us.
    'hook menu' => 'capkopper_special_item_capkopper_special_item_view_menu',
    'hook menu alter' => 'capkopper_special_item_capkopper_special_item_view_menu_alter',

    // This task uses 'context' handlers and must implement these to give the
    // handler data it needs.
    'handler type' => 'context',
    'get arguments' => 'capkopper_special_item_capkopper_special_item_view_get_arguments',
    'get context placeholders' => 'capkopper_special_item_capkopper_special_item_view_get_contexts',

    // Allow this to be enabled or disabled:
    'disabled' => variable_get('capkopper_special_item_capkopper_special_item_view_disabled', TRUE),
    'enable callback' => 'capkopper_special_item_capkopper_special_item_view_enable',
    'access callback' => 'capkopper_special_item_capkopper_special_item_view_access_check',
  );
}

/**
 * Callback defined by capkopper_special_item_capkopper_special_item_view_capkopper_special_item_tasks().
 *
 * Alter the special item view input so that special item view comes to us rather
 * than the normal special item view process.
 */
function capkopper_special_item_capkopper_special_item_view_menu_alter(&$items, $task) {
  if (variable_get('capkopper_special_item_capkopper_special_item_view_disabled', TRUE)) {
    return;
  }

  // Override the special item view handler for our purpose.
  $callback = $items['special-item/%capkopper_special_item']['page callback'];
  if ($callback == 'capkopper_special_item_page_view' || variable_get('capkopper_special_item_override_anyway', FALSE)) {
    $items['special-item/%capkopper_special_item']['page callback'] = 'capkopper_special_item_capkopper_special_item_view_page';
    $items['special-item/%capkopper_special_item']['file path'] = $task['path'];
    $items['special-item/%capkopper_special_item']['file'] = $task['file'];
  }
  else {
    // automatically disable this task if it cannot be enabled.
    variable_set('capkopper_special_item_capkopper_special_item_view_disabled', TRUE);
    if (!empty($GLOBALS['capkopper_special_item_enabling_capkopper_special_item_view'])) {
      drupal_set_message(t('Page manager module is unable to enable special-item/%capkopper_special_item because some other module already has overridden with %callback.', array('%callback' => $callback)), 'error');
    }
  }
}

/**
 * Entry point for our overridden special item view.
 *
 * This function asks its assigned handlers who, if anyone, would like to run
 * with it. If no one does, it passes through to Drupal core's
 * special item view, which is capkopper_special_item_page_view().
 */
function capkopper_special_item_capkopper_special_item_view_page(SpecialItem $capkopper_special_item) {
  // Load my task plugin
  $task = page_manager_get_task('capkopper_special_item_view');

  // Load the special item entity into a context.
  ctools_include('context');
  ctools_include('context-task-handler');

  // We need to mimic Drupal's behavior of setting the special item title here.
  drupal_set_title($capkopper_special_item->label);
  $uri = entity_uri('capkopper_special_item', $capkopper_special_item);
  // Set the special item path as the canonical URL to prevent duplicate content.
  drupal_add_html_head_link(array('rel' => 'canonical', 'href' => url($uri['path'], $uri['options'])), TRUE);
  // Set the non-aliased path as a default shortlink.
  drupal_add_html_head_link(array('rel' => 'shortlink', 'href' => url($uri['path'], array_merge($uri['options'], array('alias' => TRUE)))), TRUE);
  $contexts = ctools_context_handler_get_task_contexts($task, '', array($capkopper_special_item));

  $output = ctools_context_handler_render($task, '', $contexts, array($capkopper_special_item->item_id));
  if ($output != FALSE) {
    return $output;
  }

  $function = 'capkopper_special_item_page_view';
  foreach (module_implements('capkopper_special_item_override') as $module) {
    $call = $module . '_capkopper_special_item_override';
    if (($rc = $call('capkopper_special_item_view')) && function_exists($rc)) {
      $function = $rc;
      break;
    }
  }

  // Otherwise, fall back.
  return $function($capkopper_special_item);
}

/**
 * Callback to get arguments provided by this task handler.
 *
 * Since this is the special item view and there is no UI on the arguments, we
 * create dummy arguments that contain the needed data.
 */
function capkopper_special_item_capkopper_special_item_view_get_arguments($task, $subtask_id) {
  return array(
    array(
      'keyword' => 'capkopper_special_item',
      'identifier' => t('Special item being viewed'),
      'id' => 1,
      'name' => 'entity_id:capkopper_special_item',
      'settings' => array(),
    ),
  );
}

/**
 * Callback to get context placeholders provided by this handler.
 */
function capkopper_special_item_capkopper_special_item_view_get_contexts($task, $subtask_id) {
  return ctools_context_get_placeholders_from_argument(capkopper_special_item_capkopper_special_item_view_get_arguments($task, $subtask_id));
}

/**
 * Callback to enable/disable the page from the UI.
 */
function capkopper_special_item_capkopper_special_item_view_enable($cache, $status) {
  variable_set('capkopper_special_item_capkopper_special_item_view_disabled', $status);

  // Set a global flag so that the menu routine knows it needs
  // to set a message if enabling cannot be done.
  if (!$status) {
    $GLOBALS['capkopper_special_item_enabling_capkopper_special_item_view'] = TRUE;
  }
}

/**
 * Callback to determine if a page is accessible.
 *
 * @param $task
 *   The task plugin.
 * @param $subtask_id
 *   The subtask id
 * @param $contexts
 *   The contexts loaded for the task.
 * @return
 *   TRUE if the current user can access the page.
 */
function capkopper_special_item_capkopper_special_item_view_access_check($task, $subtask_id, $contexts) {
  $context = reset($contexts);
  return capkopper_special_item_access('view', $context->data);
}
