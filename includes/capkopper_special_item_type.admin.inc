<?php

/**
 * @file
 * Special item type editing UI.
 */

use Drupal\capkopper_special_item\Entity\ItemType as SpecialItemType;

/**
 * Generates the special item type editing form.
 * @see capkopper_special_item_type_form_validate()
 * @see capkopper_special_item_type_form_submit()
 */
function capkopper_special_item_type_form($form, &$form_state, SpecialItemType $capkopper_special_item_type, $op = 'edit') {
  if ($op == 'clone') {
    $capkopper_special_item_type->label .= ' (cloned)';
    $capkopper_special_item_type->type = '';
  }

  $form_state['capkopper_special_item_type'] = $capkopper_special_item_type;

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $capkopper_special_item_type->label,
    '#description' => t('The human-readable name of this special item type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine-readable type name.
  if (empty($capkopper_special_item_type->type)) {
    $form['type'] = array(
      '#type' => 'machine_name',
      '#default_value' => '',
      '#maxlength' => 32,
      '#machine_name' => array(
        'exists' => 'capkopper_special_item_get_types',
        'source' => array('label'),
      ),
      '#description' => t('A unique machine-readable name for this special item type. It must only contain lowercase letters, numbers, and underscores.'),
    );
  }
  else {
    $form['type'] = array(
      '#type' => 'value',
      '#value' => $capkopper_special_item_type->type,
    );
  }

  if (module_exists('entity_translation')) {
    $form['multilingual'] = array(
      '#type' => 'radios',
      '#title' => t('Multilingual support'),
      '#description' => t('If <em>Entity translation</em> is enabled it will be possible to provide a different version of the same special item for each available language.') . '<br />' . t('You can find more options in the <a href="!url">entity translation settings</a>.', array('!url' => url('admin/config/regional/entity_translation'))) . '<br />' . t('Existing Special items will not be affected by changing this option.'),
      '#options' => array(
        0 => t('Disabled'),
        ENTITY_TRANSLATION_ENABLED => t('Enabled via <em>Entity translation</em>'),
      ),
      '#default_value' => variable_get('language_capkopper_special_item_type_' . $capkopper_special_item_type->type, 0),
    );
  }

  $form['actions'] = array(
    '#type' => 'actions',
    '#weight' => 40,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save special item type'),
    '#submit' => array_merge($submit, array('capkopper_special_item_type_form_submit')),
  );

  if (!empty($form_state['capkopper_special_item_type']->type)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete special item type'),
      '#suffix' => l(t('Cancel'), 'admin/structure/special-item'),
      '#submit' => array_merge($submit, array('capkopper_special_item_type_form_submit_delete')),
      '#weight' => 45,
    );
  }
  else {
    $form['actions']['save_continue'] = array(
      '#type' => 'submit',
      '#value' => t('Save and add fields'),
      '#suffix' => l(t('Cancel'), 'admin/structure/special-item'),
      '#submit' => array_merge($submit, array('capkopper_special_item_type_form_submit')),
      '#weight' => 45,
    );
  }

  $form['#validate'][] = 'capkopper_special_item_type_form_validate';

  return $form;
}

/**
 * Form validate handler; validate the special item type form.
 *
 * @see capkopper_special_item_type_form()
 * @see capkopper_special_item_type_form_submit()
 */
function capkopper_special_item_type_form_validate($form, &$form_state) {
  $capkopper_special_item_type = $form_state['capkopper_special_item_type'];

  // If saving a new special item type, ensure it has a unique machine name.
  if (empty($capkopper_special_item_type->type) && capkopper_special_item_get_types($form_state['values']['type'])) {
    form_set_error('type', t('The machine name specified is already in use.'));
  }
}

/**
 * Form API submit callback for the type form.
 */
function capkopper_special_item_type_form_submit(&$form, &$form_state) {
  $capkopper_special_item_type = entity_ui_form_submit_build_entity($form, $form_state);
  $capkopper_special_item_type->save();

  // Set the multingual value for the special item type if entity translation is enabled.
  if (module_exists('entity_translation')) {
    variable_set('language_capkopper_special_item_type_' . $capkopper_special_item_type->type, $form_state['values']['multilingual']);
  }

  // Redirect based on the button clicked.
  drupal_set_message(t('Special item type saved.'));

  if ($form_state['triggering_element']['#parents'][0] == 'save_continue') {
    $form_state['redirect'] = 'admin/structure/special-item/manage/' . $capkopper_special_item_type->type . '/fields';
  }
  else {
    $form_state['redirect'] = 'admin/structure/special-item';
  }
}

/**
 * Form API submit callback for the delete button.
 */
function capkopper_special_item_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/special-item/manage/' . $form_state['capkopper_special_item_type']->type . '/delete';
}
