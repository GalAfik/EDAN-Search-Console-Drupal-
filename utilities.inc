<?php

function startsWith($needle, $haystack) {
 $length = strlen($needle);
 return (substr($haystack, 0, $length) === $needle);
}

function endsWith($needle, $haystack) {
  $length = strlen($needle);
  if ($length == 0) {
    return true;
  }

  return (substr($haystack, -$length) === $needle);
}

function _get_search_results_from_edan($query = '') {

  $config = require('config.php');
  $host = variable_get('search_console_host', $config->host);
  $authKey = variable_get('search_console_auth_key', $config->auth_key);
  $appId = variable_get('search_console_app_id', $config->app_id);
  // return $resp;
  date_default_timezone_set('UTC');
  // Specify your appid and key below
  $config = array(
    'edan_server' => $host,
    'edan_app_id' => $appId,
    'edan_auth_key' => $authKey,
    'edan_tier_type' => 1,
    );
  // Example usage
  $edan = new EDANInterface($config['edan_server'], $config['edan_app_id'], $config['edan_auth_key'], $config['edan_tier_type']);
  // Request
  $service = 'metadata/v1.1/metadata/search.htm'; // API Endpoint
  // Response
  $results_raw = $edan->sendRequest($query, $service, FALSE, $info = '');
  return $results_raw;
}

function _get_facets_from_edan($query = '') {

  $config = require('config.php');
  $host = variable_get('search_console_host', $config->host);
  $authKey = variable_get('search_console_auth_key', $config->auth_key);
  $appId = variable_get('search_console_app_id', $config->app_id);
  // return $resp;
  date_default_timezone_set('UTC');
  // Specify your appid and key below
  $config = array(
    'edan_server' => $host,
    'edan_app_id' => $appId,
    'edan_auth_key' => $authKey,
    'edan_tier_type' => 1,
    );
  // Example usage
  $edan = new EDANInterface($config['edan_server'], $config['edan_app_id'], $config['edan_auth_key'], $config['edan_tier_type']);
  // Request
  $service = 'metadata/v1.1/metadata/getFacets.htm'; // API Endpoint
  // Response
  $results_raw = $edan->sendRequest($query, $service, FALSE, $info = '');
  return $results_raw;
}

function _get_object_types() {
  return array(
    '' => 'Any',
    'edanmdm' => 'edanmdm',
    'objectgroup' => 'ogmt',
    );
}

function _get_facet_names( $object_type ) {
  switch ($object_type) {

    case 'edanmdm':
    return array(
      'online_media_type' => 'Online Media Type',
      'object_type' => 'Object Type',
      'topic' => 'Topic',
      'p.edanmdm.indexedstructured.name' => 'Name',
      'culture' => 'Culture',
      'language' => 'Language',
      'place' => 'Place',
      'date' => 'Date',
      'p.edanmdm.descriptivenonrepeating.data_source' => 'Data Source',
      );
    break;

    case 'objectgroup':
    return array(
      );
    break;

    default:
    $object_types = _get_object_types();
    // get rid of '' in object types so this doesn't call itself
    array_shift($object_types);
    $facet_array = array();
    foreach ($object_types as $key => $value) {
      $facet_array = array_merge($facet_array, _get_facet_names($key));
    }
    return $facet_array;
    break;
  }
}
