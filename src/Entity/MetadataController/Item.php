<?php
/**
 * @file
 *
 */

namespace Drupal\capkopper_special_item\Entity\MetadataController;

/**
 * controller for generating some basic metadata for CRUD entity types.
 */
class Item extends \EntityDefaultMetadataController {

  /**
   * (@inheritdoc)
   */
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['item_id'] = array(
      'label' => t('Special item ID'),
      'description' => t('The internal numeric ID of the special item.'),
      'type' => 'integer',
      'schema field' => 'item_id',
    );

    $properties['label'] = array(
      'label' => t('Label'),
      'description' => t('Label of the special item.'),
      'type' => 'text',
      'required' => TRUE,
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
      'schema field' => 'label',
    );

    $properties['language'] = array(
      'label' => t('Language'),
      'type' => 'token',
      'description' => t('The language the special item was created in.'),
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer capkopper_special_item entities',
      'options list' => 'entity_metadata_language_list',
      'schema field' => 'language',
    );

    $properties['status'] = array(
      'label' => t('Status'),
      'description' => t('Boolean indicating whether the special item is active or disabled.'),
      'type' => 'boolean',
      'options list' => 'capkopper_special_item_status_options_list',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer capkopper_special_item entities',
      'schema field' => 'status',
    );

    $properties['user'] = array(
      'label' => t('User'),
      'type' => 'user',
      'description' => t('The user who created the special item.'),
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_setter_method',
      'setter permission' => 'administer capkopper_special_item entities',
      'required' => TRUE,
      'schema field' => 'uid',
    );

    $properties['created'] = array(
      'label' => t('Date submitted'),
      'type' => 'date',
      'description' => t('The date special item was created.'),
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer capkopper_special_item entities',
      'required' => TRUE,
      'schema field' => 'created',
    );
    $properties['changed'] = array(
      'label' => t('Date changed'),
      'type' => 'date',
      'description' => t('The date the special item was most recently updated.'),
      'setter callback' => 'entity_property_verbatim_set',
      'query callback' => 'entity_metadata_table_query',
      'setter permission' => 'administer capkopper_special_item entities',
      'schema field' => 'changed',
    );

    // Type property is created in parent::entityPropertyInfo().
    $properties['type']['label'] = t('Special item type');
    $properties['type']['type'] = 'capkopper_special_item_type';
    $properties['type']['schema field'] = 'type';
    $properties['type']['description'] = t('The special item type.');

    // @todo This line could be removed depending on this http://drupal.org/node/1931376
    $properties['type']['required'] = TRUE;

    $properties['type']['setter callback'] = 'entity_property_verbatim_set';
    $properties['type']['setter permission'] = 'administer capkopper_special_item entities';

    return $info;
  }

}
