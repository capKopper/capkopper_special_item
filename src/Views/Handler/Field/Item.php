<?php

/**
 * @file
 * Contains the basic special item field handler.
 */

namespace Drupal\capkopper_special_item\Views\Handler\Field;

use Drupal\capkopper_special_item\Entity\Item as SpecialItem;

class Item extends \views_handler_field {

  /**
   * (@inheritdoc)
   */
  public function init(&$view, &$options) {
    parent::init($view, $options);

    if (!empty($this->options['link_to_entity'])) {
      $this->additional_fields['item_id'] = 'item_id';
      $this->additional_fields['type'] = 'type';
    }
  }

  /**
   * (@inheritdoc)
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['link_to_entity'] = array('default' => FALSE);
    return $options;
  }

  /**
   * (@inheritdoc)
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['link_to_entity'] = array(
      '#title' => t("Link this field to the special item's view page"),
      '#description' => t('This will override any other link you have set.'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['link_to_entity']),
    );
  }

  /**
   * Render whatever the data is as a link to the special item.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  public function render_link($data, $values) {
    if (!empty($this->options['link_to_entity']) && $data !== NULL && $data !== '') {
      $item_id = $this->get_value($values, 'item_id');
      $type = $this->get_value($values, 'type');

      if ($item_id && $type) {
        $entity = entity_create('capkopper_special_item', array('item_id' => $item_id, 'type' => $type));

        if ($entity && capkopper_special_item_access('view', $entity)) {
          $this->options['alter']['make_link'] = TRUE;
          $this->options['alter']['path'] = "special-item/$item_id";
        }
      }
    }

    return $data;
  }

  /**
   * (@inheritdoc)
   */
  public function render($values) {
    $value = $this->get_value($values);
    return $this->render_link($this->sanitize_value($value), $values);
  }

}
