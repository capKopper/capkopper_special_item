<?php
/**
 * @file
 *
 */

namespace Drupal\capkopper_special_item\Entity\UIController;

/**
 * UI controller.
 */
class Item extends \EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   *
   * Main reason for doing this is that parent class hook_menu() is, optimized
   * for entity type administration.
   */
  public function hook_menu() {
    // TODO: EntityDefaultUIController controller automatically adds the menu
    // to import entities, but there is a bug with this action and can not work
    // with the version of your entity_api module, track the issue # 2112755
    // https://www.drupal.org/node/2112755
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%entity_object';

    $items = parent::hook_menu();
    $module_path = drupal_get_path('module', $this->entityInfo['module']);

    // Extend the 'add' path.
    $items[$this->path . '/add'] = array(
      'title' => 'Add special item',
      'page callback' => 'entity_ui_bundle_add_page',
      'page arguments' => array($this->entityType),
      'access callback' => 'entity_access',
      'access arguments' => array('create', $this->entityType),
      'type' => MENU_SUGGESTED_ITEM,
    );

    $items[$this->path . '/add/%'] = array(
      'title callback' => 'entity_ui_get_action_title',
      'title arguments' => array('add', $this->entityType, $this->id_count + 1),
      'page callback' => 'entity_ui_get_bundle_add_form',
      'page arguments' => array($this->entityType, $this->id_count + 1),
      'access callback' => 'entity_access',
      'access arguments' => array('create', $this->entityType),
      'file path' => $module_path,
      'file' => 'includes/capkopper_special_item.admin.inc',
    );

    unset($items[$this->path . '/import']); // Remove this for exportable entities.

    // Remove this if there is an defined URI callback.
    /*$items['special-item/' . $wildcard] = array(
      'title callback' => 'capkopper_special_item_page_title',
      'title arguments' => array(1),
      'page callback' => 'capkopper_special_item_page_view',
      'page arguments' => array(1),
      'access callback' => 'entity_access',
      'access arguments' => array('view', $this->entityType, 1),
    );*/

    return $items;
  }

}
