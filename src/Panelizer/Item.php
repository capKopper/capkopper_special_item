<?php
/**
 * @file
 * Special item Panelizer entity plugin.
 */

namespace Drupal\capkopper_special_item\Panelizer;

/**
 * The class used for special item entities
 */
class Item extends \PanelizerEntityDefault {

  /**
   * (@inheritdoc)
   */
  public $views_table = 'capkopper_special_item';

  public $uses_page_manager = TRUE;

  // This is disabled by default, because it depends on the hierarchy level of
  // the entity type admin path. This last should not exceed 5 parts (from 0 to
  // 4) otherwise the maximum number of elements for a menu item (8) will be
  // overtaken.
  // If all is OK there, you need to uncomment the 2 following lines and the
  // method "hook_page_alter".
  public $entity_admin_root = 'admin/structure/special-item/manage/%';

  public $entity_admin_bundle = 4;

  /**
   * (@inheritdoc)
   */
  public function entity_access($op, $entity) {
    return capkopper_special_item_access($op, $entity);
  }

  /**
   * (@inheritdoc)
   */
  public function entity_save($entity) {
    return entity_save('capkopper_special_item', $entity);
  }

  /**
   * (@inheritdoc)
   */
  public function entity_bundle_label() {
    return t('Special item type');
  }

  /**
   * (@inheritdoc)
   */
  function get_default_display($bundle, $view_mode) {
    $display = parent::get_default_display($bundle, $view_mode);
    // Add the special item label to the display since we can't get that automatically.
    $display->title = '%capkopper_special_item:label';

    return $display;
  }

  /**
   * Identify whether page manager is enabled for this entity type.
   */
  public function is_page_manager_enabled() {
    return variable_get('capkopper_special_item_capkopper_special_item_view_disabled', TRUE);
  }

  /**
   * Implements a delegated hook_page_manager_handlers().
   *
   * This makes sure that all panelized entities have the proper entry
   * in page manager for rendering.
   */
  public function hook_default_page_manager_handlers(&$handlers) {
    $handler = new \stdClass;
    $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
    $handler->api_version = 1;
    $handler->name = 'capkopper_special_item_view_panelizer';
    $handler->task = 'capkopper_special_item_view';
    $handler->subtask = '';
    // NOTE: This is named panelizer_node for historical reasons.
    $handler->handler = 'panelizer_node';
    $handler->weight = -100;
    $handler->conf = array(
      'title' => t('Special item panelizer'),
      'context' => 'argument_entity_id:capkopper_special_item_1',
      'access' => array(),
    );
    $handlers['capkopper_special_item_view_panelizer'] = $handler;

    return $handlers;
  }

  /**
   * Implements a delegated hook_form_alter.
   *
   * We want to add Panelizer settings for the bundle to the special item type form.
   */
  public function hook_form_alter(&$form, &$form_state, $form_id) {
    if ($form_id == 'capkopper_special_item_type_form') {
      if (isset($form_state['capkopper_special_item_type']->type)) {
        $bundle = $form_state['capkopper_special_item_type']->type;
        $this->add_bundle_setting_form($form, $form_state, $bundle, array('type'));
      }
    }
  }

  public function hook_page_alter(&$page) {
    // Add an extra "Panelizer" action on the special item types admin page.
    if ($_GET['q'] == 'admin/structure/special-item') {
      // This only works with some themes.
      if (!empty($page['content']['system_main']['table'])) {
        // Shortcut.
        $table = &$page['content']['system_main']['table'];

        // Operations column should always be the last column in header.
        // Increase its colspan by one to include possible panelizer link.
        $operationsCol = end($table['#header']);
        if (!empty($operationsCol['colspan'])) {
          $operationsColKey = key($table['#header']);
          $table['#header'][$operationsColKey]['colspan']++;
        }

        // Since we can't tell what row a type is for, but we know that they
        // were generated in this order, go through the original types list.
        $types = capkopper_special_item_get_types();
        $row_index = 0;
        foreach ($types as $bundle => $capkopper_special_item_type) {
          $type = $types[$bundle];

          if ($this->is_panelized($bundle) && panelizer_administer_entity_bundle($this, $bundle)) {
            $table['#rows'][$row_index][] = array('data' => l(t('panelizer'), 'admin/structure/special-item/manage/' . $bundle . '/panelizer'));
          }
          else {
            $table['#rows'][$row_index][] = array('data' => '');
          }

          // Update row index for next pass.
          $row_index++;
        }
      }
    }
  }

  /**
   * (@inheritdoc)
   */
  public function preprocess_panelizer_view_mode(&$vars, $entity, $element, $panelizer, $info) {
    parent::preprocess_panelizer_view_mode($vars, $entity, $element, $panelizer, $info);

    if (empty($entity->status)) {
      $vars['classes_array'][] = 'capkopper-special-item-disabled';
    }
  }

  function render_entity($entity, $view_mode, $langcode = NULL, $args = array(), $address = NULL, $extra_contexts = array()) {
    // Just add a special tag to the entity so we know it is being rendered by
    // the Panelizer module, when the ENTITY_TYPE_view() hook is called.
    $entity->panelizer_rendering = TRUE;

    $info = parent::render_entity($entity, $view_mode, $langcode, $args, $address, $extra_contexts);
    if (empty($entity->status)) {
      $info['classes_array'][] = 'capkopper-special-item-disabled';
    }

    unset($entity->panelizer_rendering);
    return $info;
  }

}
