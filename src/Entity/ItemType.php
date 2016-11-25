<?php
/**
 * @file
 *
 */

namespace Drupal\capkopper_special_item\Entity;

/**
 * The class used for special item type entities
 */
class ItemType extends \Entity {

  /**
   * The special item type (bundle).
   *
   * @var mixed
   */
  public $type;

  /**
   * The special item label.
   *
   * @var mixed
   */
  public $label;

  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'capkopper_special_item_type');
  }

}
