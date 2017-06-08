<?php

include('edan_search_console.utilities.inc');

function _edan_search_console_full_record_page_callback() {
  $path_parts = arg();
  $query = 'q=id:' . $path_parts[3];
  $json = _edan_search_console_get_search_results_from_edan($query);

  echo '<pre>' . $json . '</pre>';
  exit();
}
