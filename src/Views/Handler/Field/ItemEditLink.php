<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying edit links
 * as fields
 */

namespace Drupal\capkopper_special_item\Views\Handler\Field;

use Drupal\capkopper_special_item\Entity\Item as SpecialItem;

class ItemEditLink extends ItemLink {

  /**
   * (@inheritdoc)
   */
  protected $op = 'edit';

  /**
   * (@inheritdoc)
   */
  protected function operation_uri(SpecialItem $capkopper_special_item) {
    return "admin/content/special-item/manage/$capkopper_special_item->item_id/edit";
  }

  /**
   * (@inheritdoc)
   */
  protected function operation_default_title() {
    return t('edit');
  }

}
