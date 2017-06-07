<?php

function search_console_admin() {

  $config = require('config.php');

  $form['search_console_host'] = array(
    '#type' => 'textfield',
    '#title' => t('Host'),
    '#default_value' => variable_get('search_console_host', $config->host),
    );

  $form['search_console_auth_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Authorization Key'),
    '#default_value' => variable_get('search_console_auth_key', $config->auth_key),
    );

  $form['search_console_app_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Application ID'),
    '#default_value' => variable_get('search_console_app_id', $config->app_id),
    );

  return system_settings_form($form);
}
