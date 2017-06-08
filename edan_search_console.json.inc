<?php

include('edan_search_console.utilities.inc');

function _edan_search_console_full_json_page_callback() {
  $path_parts = arg();
  $query = $path_parts[3];
  $json = _edan_search_console_get_search_results_from_edan($query);

  echo '<pre>' . $json . '</pre>';
  exit();
}
