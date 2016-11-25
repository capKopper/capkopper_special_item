<?php

/**
 * @file
 * capkopper_special_item editing UI.
 */

use Drupal\capkopper_special_item\Entity\Item as SpecialItem;

/**
 * Form callback: create or edit a special item.
 */
function capkopper_special_item_form($form, &$form_state, SpecialItem $capkopper_special_item, $op = 'edit', $entity_type) {
  // Add the breadcrumb for the form's location.
  capkopper_special_item_set_breadcrumb();

  // Add the default field elements.
  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Special item Label'),
    '#default_value' => isset($capkopper_special_item->label) ? $capkopper_special_item->label : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );

  // Add the field related form elements.
  $form_state['capkopper_special_item'] = $capkopper_special_item;

  if (empty($langcode)) {
    $langcode = LANGUAGE_NONE;
  }

  field_attach_form('capkopper_special_item', $capkopper_special_item, $form, $form_state, $langcode);

  $form['status'] = array(
    '#type' => 'radios',
    '#title' => t('Status'),
    '#options' => array(
      '1' => t('Active'),
      '0' => t('Disabled'),
    ),
    '#default_value' => $capkopper_special_item->status,
    '#required' => TRUE,
    '#weight' => 35,
  );

  $form['actions'] = array(
    '#type' => 'actions',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // Simply use default language
  $form['language'] = array(
    '#type' => 'value',
    '#value' => $langcode,
  );

  // We add the form #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save special item'),
    '#submit' => $submit + array('capkopper_special_item_edit_form_submit'),
  );

  if (!empty($capkopper_special_item->label)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete special item'),
      '#suffix' => l(t('Cancel'), 'admin/content/special-item'),
      '#submit' => $submit + array('capkopper_special_item_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'] = array('capkopper_special_item_edit_form_validate');

  return $form;
}

/**
 * Form API validate callback for the special item form.
 */
function capkopper_special_item_edit_form_validate(&$form, &$form_state) {
  $capkopper_special_item = $form_state['capkopper_special_item'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('capkopper_special_item', $capkopper_special_item, $form, $form_state);
}

/**
 * Form API submit callback for the special item form.
 */
function capkopper_special_item_edit_form_submit(&$form, &$form_state) {
  global $user;

  // Save the entity and go back to the list of Special items.
  $capkopper_special_item = entity_ui_controller('capkopper_special_item')->entityFormSubmitBuildEntity($form, $form_state);

  // Save default parameters back into the $capkopper_special_item object.
  $capkopper_special_item->label = $form_state['values']['label'];
  $capkopper_special_item->status = $form_state['values']['status'];
  $capkopper_special_item->language = $form_state['values']['language'];

  // Set the special item's uid if it's being created at this time.
  if (empty($capkopper_special_item->item_id)) {
    $capkopper_special_item->uid = $user->uid;
  }

  // Notify field widgets.
  field_attach_submit('capkopper_special_item', $capkopper_special_item, $form, $form_state);

  // Save the $capkopper_special_item.
  $capkopper_special_item->save();

  // Send feedback message to the user.
  drupal_set_message(t('Special item @label saved.', array('@label' => $capkopper_special_item->label)));

  $form_state['redirect'] = 'admin/content/special-item';
}

/**
 * Form API submit callback for the delete button.
 */
function capkopper_special_item_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/special-item/manage/' . $form_state['capkopper_special_item']->item_id . '/delete';
}

/**
 * Sets the breadcrumb for administrative special item pages.
 */
function capkopper_special_item_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Special item'), 'admin/content/special-item'),
  );

  drupal_set_breadcrumb($breadcrumb);
}
