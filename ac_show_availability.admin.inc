<?php
/**
 * @file menu callback for ac_show_availability admin page
 */
function _ac_show_availability_admin_settings($form, &$form_state) {
  if (!file_exists(drupal_get_path('module', 'ac_show_availability') . '/js/bxslider/jquery.bxslider.min.js')) {
    $link = l('bxslider', 'http://bxslider.com/lib/jquery.bxslider.zip');
    drupal_set_message(t("Please extract $link library to ac_show_availability/js folder"), 'error');
  }

  $form['acsa_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Resource Availability Configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#prefix' => '<div id = "acsa_filters">',
    '#suffix' => '</div>',
  );

  $form['acsa_settings']['acsa_content_type'] = array(
    '#type' => 'select',
    '#title' => t('Resource content type'),
    '#options' => array_keys(node_type_get_names()),
    '#description' => t('Select the resource content type'),
    '#default_value' => variable_get('acsa_content_type') != '' ? variable_get('acsa_content_type') : NULL,
    '#empty_value' => '',
    '#ajax' => array(
      'callback' => '_acsa_filter_ajax',
      'wrapper' => 'acsa_filters',
    )
  );

  $form['acsa_settings']['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Resource Availability Filters'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['acsa_settings']['filters']['acsa_filter_fields'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#size' => 0,
    '#default_value' => variable_get('acsa_filter_fields') != '' ? variable_get('acsa_filter_fields') : NULL,
    '#empty_value' => '',
    '#title' => t('Select filters for this resource'),
  );

  if (variable_get('acsa_filter_fields') != '') {
    $content_type = variable_get('acsa_content_type');
    if ($content_type != '') {
      $content_types = array_keys(node_type_get_names());
      $fields = field_info_instances("node", $content_types[$content_type]);
      foreach ($fields as $filter_field) {
        $field_info = field_info_field($filter_field['field_name']);
        if (isset($field_info['columns']) && (isset($field_info['columns']['value']) || isset($field_info['columns']['tid']))) {
          $filter_options[$filter_field['field_name']] = $filter_field['label'];
        }
      }
      $form['acsa_settings']['filters']['acsa_filter_fields']['#size'] = count($filter_options);
      $form['acsa_settings']['filters']['acsa_filter_fields']['#options'] = $filter_options;
    }
  }

  $form['acsa_slider'] = array(
    '#type' => 'fieldset',
    '#title' => t('Slider settings for availability table'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['acsa_slider']['acsa_slidewidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Slide width'),
    '#default_value' => variable_get('acsa_slidewidth') != '' ? variable_get('acsa_slidewidth') : 100
  );
  $form['acsa_slider']['acsa_minslides'] = array(
    '#type' => 'textfield',
    '#title' => t('Min slides'),
    '#default_value' => variable_get('acsa_minslides') != '' ? variable_get('acsa_minslides') : 2
  );
  $form['acsa_slider']['acsa_maxslides'] = array(
    '#type' => 'textfield',
    '#title' => t('Max slides'),
    '#default_value' => variable_get('acsa_maxslides') != '' ? variable_get('acsa_maxslides') : 8
  );
  $form['acsa_slider']['acsa_slidemargin'] = array(
    '#type' => 'textfield',
    '#title' => t('Slide margin'),
    '#default_value' => variable_get('acsa_slidemargin') != '' ? variable_get('acsa_slidemargin') : 0
  );

  return system_settings_form($form);
}

/**
 * Ajax form callback
 */
function _acsa_filter_ajax($form, $form_state) {
  $content_type = $form_state['values']['acsa_content_type'];
  if ($content_type != '') {
    $content_types = array_keys(node_type_get_names());
    $fields = field_info_instances("node", $content_types[$content_type]);
    foreach ($fields as $filter_field) {
      $field_info = field_info_field($filter_field['field_name']);
      if (isset($field_info['columns']) && (isset($field_info['columns']['value']) || isset($field_info['columns']['tid']))) {
        $filter_options[$filter_field['field_name']] = $filter_field['label'];
      }
    }
    $form['acsa_settings']['filters']['acsa_filter_fields']['#size'] = count($filter_options);
    $form['acsa_settings']['filters']['acsa_filter_fields']['#options'] = $filter_options;
  }
  return $form['acsa_settings'];
}