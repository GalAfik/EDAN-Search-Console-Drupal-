<?php

function edan_search_console_admin() {

  $form['edan_search_console_host'] = array(
    '#type' => 'textfield',
    '#title' => t('Host'),
    '#default_value' => variable_get('edan_search_console_host', ''),
    );

  $form['edan_search_console_auth_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Authorization Key'),
    '#default_value' => variable_get('edan_search_console_auth_key', ''),
    );

  $form['edan_search_console_app_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Application ID'),
    '#default_value' => variable_get('edan_search_console_app_id', ''),
    );

  return system_settings_form($form);
}
