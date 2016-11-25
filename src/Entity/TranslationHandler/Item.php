<?php
/**
 * @file
 * Translation handler for the special item entity.
 */

namespace Drupal\capkopper_special_item\Entity\TranslationHandler;

/**
 * Special item translation handler.
 *
 * @see capkopper_special_item_entity_info()
 */
class Item extends \EntityTranslationDefaultHandler {

  public function __construct($entity_type, $entity_info, $entity) {
    parent::__construct('capkopper_special_item', $entity_info, $entity);
  }

  /**
   * Checks whether the current user has access to this special item.
   */
  public function getAccess($op) {
    return capkopper_special_item_access($op, $this->entity);
  }

  /**
   * @see EntityTranslationDefaultHandler::entityFormTitle()
   */
  protected function entityFormTitle() {
    return capkopper_special_item_page_title($this->entity);
  }

  /**
   * Returns whether the entity is active (TRUE) or disabled (FALSE).
   */
  protected function getStatus() {
    return (boolean) $this->entity->status;
  }

}
