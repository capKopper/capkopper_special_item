<?php
/**
 * @file
 *
 */

namespace Drupal\capkopper_special_item\Entity\APIController;

/**
 * The Controller for special item type entities
 */
class ItemType extends \EntityAPIControllerExportable {

  /**
   * Create a special item type.
   *
   * @param array $values
   *   An array containing the possible values.
   *
   * @return object
   *   A type object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our special item.
    $values += array(
      'id' => '',
    );
    $entity_type = parent::create($values);

    return $entity_type;
  }

  /**
   * Overridden to clear cache.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    $return = parent::save($entity, $transaction);

    // Reset the special item type cache. We need to do this first so
    // menu changes pick up our new type.
    capkopper_special_item_type_cache_reset();
    // Clear field info caches such that any changes to extra fields get
    // reflected.
    field_info_cache_clear();

    return $return;
  }

  /**
   * Overridden to clear cache.
   */
  public function delete($ids, DatabaseTransaction $transaction = NULL) {
    parent::delete($ids, $transaction);

    if ($ids) {
      // Clear field info caches such that any changes to extra fields get
      // reflected.
      field_info_cache_clear();

      capkopper_special_item_type_cache_reset();
    }
  }

}
