<?php
/**
 * @file
 *
 */

namespace Drupal\capkopper_special_item\Entity;

/**
 * The class used for special item entities
 */
class Item extends \Entity {

  /**
   * The user ID who created this special item.
   *
   * @var int
   */
  public $uid;

  /**
   * The label of this special item.
   *
   * @var string
   */
  public $label;

  /**
   * Class constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'capkopper_special_item');
  }

  /**
   * Defines the default entity label.
   */
  protected function defaultLabel() {
    return $this->label;
  }

  /**
   * Defines the default entity URI.
   */
  protected function defaultUri() {
    return NULL;
    //return array('path' => 'special-item/' . $this->item_id);
  }

  /**
   * Returns the user who created this special item.
   */
  public function user() {
    return user_load($this->uid);
  }

  /**
   * Sets a new user as author.
   *
   * @param $account
   *   The user account object or the user account id (uid).
   */
  public function setUser($account) {
    $this->uid = is_object($account) ? $account->uid : $account;
  }

}
