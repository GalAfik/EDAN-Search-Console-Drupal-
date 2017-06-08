<?php

include('edan_search_console.utilities.inc');

function _edan_search_console_facets_guide_page_callback() {
  $autocomplete_options = array();
  $results = json_decode(_edan_search_console_get_facets_from_edan(), TRUE);
  foreach ($results['facets'] as $facet_name => $facet_values) {
    foreach ($facet_values as $facet_value) {
      $autocomplete_options[ $facet_name ][] = $facet_value[0];
    }
  }

  foreach ($autocomplete_options as $key => $values) {
    echo '<h2>' . $key . '</h2><ul>';
    foreach ($values as $value) {
      echo '<li>' . $value . '</li>';
    }
    echo '</ul><br>';
  }
  exit();
}
