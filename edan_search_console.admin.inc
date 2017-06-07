<?php

function search_console_admin() {

  $form['search_console_host'] = array(
    '#type' => 'textfield',
    '#title' => t('Host'),
    '#default_value' => variable_get('search_console_host', ''),
    );

  $form['search_console_auth_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Authorization Key'),
    '#default_value' => variable_get('search_console_auth_key', ''),
    );

  $form['search_console_app_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Application ID'),
    '#default_value' => variable_get('search_console_app_id', ''),
    );

  return system_settings_form($form);
}
