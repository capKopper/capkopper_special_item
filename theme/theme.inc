<?php
/**
 * @file
 *
 */

/**
 * Processes variables for capkopper-special-item.tpl.php
 *
 * The $variables array contains the following arguments:
 * - $capkopper_special_item
 * - $view_mode
 * - $page
 *
 * @see node.tpl.php
 */
function template_preprocess_capkopper_special_item(&$variables) {
  $entity = $variables['elements']['#entity'];
  $variables['date'] = format_date($entity->created);

  if (empty($entity->status)) {
    $variables['classes_array'][] = 'capkopper-special-item-disabled';
  }
}
