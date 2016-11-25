<?php
/**
 * @file
 * Defines the extra fields of special item entity.
 */

namespace Drupal\capkopper_special_item\Entity\ExtraFields;

class Item implements \EntityExtraFieldsControllerInterface {

  /**
   * Implements EntityExtraFieldsControllerInterface::fieldExtraFields().
   */
  public function fieldExtraFields() {
    $extra = [];

    foreach (capkopper_special_item_get_types() as $type => $info) {
      $extra['capkopper_special_item'][$type] = array(
        'form' => array(
          'label' => array(
            'label' => t('Label'),
            'description' => t('Special item label form element'),
            'weight' => -5,
          ),
          'status' => array(
            'label' => t('Status'),
            'description' => t('Special item status form element'),
            'weight' => 35,
          ),
        ),
        'display' => array(
          'label' => array(
            'label' => t('Label'),
            'description' => t('Special item label'),
            'weight' => -5,
          ),
          'status' => array(
            'label' => t('Status'),
            'description' => t('Whether the Special item is active or disabled'),
            'weight' => 5,
          ),
        ),
      );
    }

    return $extra;
  }

}
