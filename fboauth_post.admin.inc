<?php
/**
 * @file
 * Administration page callbacks for the Facebook OAuth module.
 */

/**
 * Form builder. Configure Facebook OAuth.
 */
function fboauth_post_admin_settings() {

  $types = node_type_get_types();
  foreach ($types as $node_type) {
    $options[$node_type -> type] = $node_type -> name;
  }

  $form['fboauth_post_node_types'] = array('#type' => 'checkboxes', '#title' => t('Countent types that could be published to FB'), '#options' => $options, '#description' => t('Check those content types, that you want them to be able to post their content to facebook'), );

  if (count(variable_get('fboauth_post_node_types'))) {
    $form['fboauth_post_node_types']['#default_value'] = variable_get('fboauth_post_node_types');
  }

  $form['#submit'][] = 'fboauth_post_admin_settings_submit';

  return system_settings_form($form);
  
  //field_info_instances('node', 'page');
}

/**
 * Process annotation settings submission.
 */
function fboauth_post_admin_settings_submit($form, $form_state) {

  $field = field_info_field('fboauth_post_check');

  // if the annotation field does not exist then create it
  if (empty($field)) {
    $field = array('field_name' => 'fboauth_post_check', 'cardinality' => '-1', 'settings' => array('allowed_values' => array('yes' => t('Yes'), ), 'allowed_values_function' => '', ), 'translatable' => '0', 'type' => 'list_text', );

    $field = field_create_field($field);
  }

  // We should add the basic field mappinf for this content type
  $ct_mappings = variable_get('fboauth_post_ct_mapping');

  $ct_mapping = array('picture' => '', 'name' => '', 'description' => '', );

  // Loop through each of the content type checkboxes shown on the form.
  foreach ($form_state['values']['fboauth_post_node_types'] as $key => $value) {
    // If the check box for a content type is unchecked, look to see whether
    // this content type has the annotation field attached to it using the
    // field_info_instance function. If it does then we need to remove the
    // annotation field as the administrator has unchecked the box.
    if (!$value) {

      $instance = field_info_instance('node', 'fboauth_post_check', $key);
      if (!empty($instance)) {
        field_delete_instance($instance);
        watchdog("Facebook OAuth", 'Deleted Facebook OAuth field from content type:%key', array('%key' => $key));
      }
      unset($ct_mappings[$key]);
    } else {
      // If the check box for a content type is checked, look to see whether
      // the field is associated with that content type. If not then add the
      // facebook post field to the content type.
      $instance = field_info_instance('node', 'fboauth_post_check', $key);

      if (empty($instance)) {

        $instance = array('field_name' => 'fboauth_post_check', 'entity_type' => 'node', 'bundle' => $key, 'include_inactive' => TRUE, 'label' => t('Post to facebook?'), 'widget' => array('type' => 'options_buttons', 'weight' => 8, 'module' => 'options', ), );

        $instance = field_create_instance($instance);
        $ct_mappings[$key] = $ct_mapping;
        watchdog('Facebook OAuth', 'Added Facebook OAuth field to content type: %key', array('%key' => $key));
      }
    }

    variable_set('fboauth_post_ct_mapping', $ct_mappings);
  }
  // End foreach loop.
}
