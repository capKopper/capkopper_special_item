<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying links to entities
 * as fields.
 */

namespace Drupal\capkopper_special_item\Views\Handler\Field;

use Drupal\capkopper_special_item\Entity\Item as SpecialItem;

/**
 * Field handler to present a link to a special item operation.
 *
 * @ingroup views_field_handlers
 */
class ItemLink extends \views_handler_field {

  /**
   * The current operation.
   *
   * @var string
   */
  protected $op = 'view';

  /**
   * The class constructor.
   *
   * (@inheritdoc)
   */
  public function construct() {
    parent::construct();

    $this->additional_fields['item_id'] = 'item_id';
    $this->additional_fields['type'] = 'type';
  }

  /**
   * (@inheritdoc)
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => '', 'translatable' => TRUE);
    return $options;
  }

  /**
   * (@inheritdoc)
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );

    // The path is set by render_link function so don't allow to set it.
    $form['alter']['path'] = array('#access' => FALSE);
    $form['alter']['external'] = array('#access' => FALSE);
  }

  /**
   * (@inheritdoc)
   */
  public function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * (@inheritdoc)
   */
  public function render($values) {
    $item_id = $this->get_value($values, 'item_id');
    $type = $this->get_value($values, 'type');

    if ($item_id && $type) {
      $data = array(
        'item_id' => $item_id,
        'type' => $type,
      );

      if ($entity = entity_create('capkopper_special_item', $data)) {
        return $this->render_link($entity, $values);
      }
    }
  }

  /**
   * (@inheritdoc)
   */
  public function render_link(SpecialItem $capkopper_special_item, $values) {
    if (capkopper_special_item_access($this->op, $capkopper_special_item)) {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = $this->operation_uri($capkopper_special_item);
      $this->options['alter']['query'] = drupal_get_destination();

      $text = !empty($this->options['text']) ? $this->options['text'] : $this->operation_default_title();
      return $text;
    }
  }

  /**
   * Get the target URI for the current operation.
   *
   * @return string
   */
  protected function operation_uri(SpecialItem $capkopper_special_item) {
    return "special-item/$capkopper_special_item->item_id";
  }

  /**
   * Get the link default title for the current operation.
   *
   * @return string
   */
  protected function operation_default_title() {
    return t('view');
  }

}
