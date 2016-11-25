<?php
/**
 * @file
 *
 */

namespace Drupal\capkopper_special_item\Entity\UIController;

/**
 * UI controller.
 */
class ItemType extends \EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['title'] = 'Special item types';
    $items[$this->path]['description'] = 'Manage special item entity types, including adding and removing fields and the display of fields.';
    //$items[$this->path]['type'] = MENU_LOCAL_TASK;

    return $items;
  }

}
