<?php

function _edan_search_console_full_record_page_callback() {
  $path_parts = arg();
  $query = 'q=id:' . $path_parts[1];
  $json = _get_search_results_from_edan($query);

  echo '<pre>' . $json . '</pre>';
  exit();
}
