<?php

/**
 * Implements hook_form().
 */
function field_collection_tokens_fieldmapping_form($form, &$form_state) {
  $map = variable_get('field_collection_tokens_map', array());
  // Generate input field for each defined field_collection field.
  foreach (field_info_fields() as $field) {
    if ($field['type'] == 'field_collection') {
      $form['field_collection_tokens_' . $field['field_name'] . '_token'] = array(
        '#type' => 'textfield',
        '#title' => t('Token for: %field', array('%field' => $field['field_name'])),
        '#default_value' => isset($map[$field['field_name']]) ? '[' . $map[$field['field_name']] . ']' : '',
      );
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save tokens'),
  );

  return $form;
}

/**
 * Implements hook_form_submit().
 */
function field_collection_tokens_fieldmapping_form_submit($form, &$form_state) {
  $map = array();
  //Store all submitted tokens as a single serialised array
  //in the variables table.
  foreach($form_state['values'] as $key => $value) {
    if(substr_count($key, 'field_collection_tokens_') > 0) {
      // Filter out field_collection name
      // (the bit between 'field_collection_tokens_' and '_token')
      $start = 24;
      $length = strlen($key) - $start - 6;
      $field_name = substr($key, $start, $length);

      // Don't store the square brackets.
      $value = str_replace('[', '', $value);
      $value = str_replace(']', '', $value);

      $map[$field_name] = $value;
    }
  }
  variable_set('field_collection_tokens_map', $map);
  drupal_set_message(t('The settings have been saved'));
}

/**
 * Implements hook_form_validate().
 */
function field_collection_tokens_fieldmapping_form_validate($form, &$form_state) {
  // TODO: input validation: only allow az-09_-
}



