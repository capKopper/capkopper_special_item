<?php
/**
 * @file
 * Defines the inline entity form controller for special item Entity.
 */

namespace Drupal\capkopper_special_item\Entity\InlineFormController;

class Item extends \EntityInlineEntityFormController {

  /**
   * Overrides EntityInlineEntityFormController::labels().
   */
  public function labels() {
    return array(
      'singular' => t('Special item'),
      'plural' => t('Special items'),
    );
  }

  /**
   * Overrides EntityInlineEntityFormController::entityForm().
   */
  public function entityForm($entity_form, &$form_state) {
    module_load_include('inc', 'capkopper_special_item', 'includes/capkopper_special_item.admin');
    return capkopper_special_item_form($entity_form, $form_state, $entity_form['#entity'], $entity_form['#op'], $entity_form['#entity_type']);
  }

}
