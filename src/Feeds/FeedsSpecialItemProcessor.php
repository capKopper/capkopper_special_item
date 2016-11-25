<?php
/**
 * @file
 * Custom Feeds processor for Special Item.
 */

namespace Drupal\capkopper_special_item\Feeds;

class FeedsSpecialItemProcessor extends \FeedsProcessor {

  /**
   * Implements entityType().
   */
  public function entityType() {
    return 'capkopper_special_item';
  }

  /**
   * Implements newEntity().
   */
  protected function newEntity(\FeedsSource $source) {
    $special_item = new \Drupal\capkopper_special_item\Entity\Item();

    $special_item->type = $this->bundle();
    $special_item->changed = REQUEST_TIME;
    $special_item->created = REQUEST_TIME;
    $special_item->language = LANGUAGE_NONE;
    $special_item->is_new = TRUE;
    $special_item->uid = $this->config['author'];

    return $special_item;
  }

  /**
   * Implements entitySave().
   */
  protected function entitySave($entity) {
    capkopper_special_item_save($entity);
  }

  /**
   * Implements entityDeleteMultiple().
   */
  protected function entityDeleteMultiple($entity_ids) {
    capkopper_special_item_delete_multiple($entity_ids);
  }

  /**
   * Return available mapping targets.
   */
  public function getMappingTargets() {
    $targets = parent::getMappingTargets();
    
    $targets['label'] = array(
      'name' => t('Label'),
      'description' => t('The title of the special item.'),
    );
    $targets['item_id'] = array(
      'name' => t('Special item ID'),
      'description' => t('The id of the special item. NOTE: use this feature with care, special item ids are usually assigned by Drupal.'),
      'optional_unique' => TRUE,
    );
    $targets['uid'] = array(
      'name' => t('User ID'),
      'description' => t('The Drupal user ID of the special item author.'),
    );
    $targets['status'] = array(
      'name' => t('Published status'),
      'description' => t('Whether a special item is published or not. 1 stands for published, 0 for not published.'),
    );
    $targets['created'] = array(
      'name' => t('Published date'),
      'description' => t('The UNIX time when a special item has been published.'),
    );

    // Include language field if Locale module is enabled.
    if (module_exists('locale')) {
      $targets['language'] = array(
        'name' => t('Language'),
        'description' => t('The two-character language code of the special item.'),
      );
    }

    // Let other modules expose mapping targets.
    self::loadMappers();
    $entity_type = $this->entityType();
    $bundle = $this->bundle();
    drupal_alter('feeds_processor_targets', $targets, $entity_type, $bundle);

    return $targets;
  }

}
