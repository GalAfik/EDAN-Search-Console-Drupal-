<?php

function _full_record_page_callback() {
  $path_parts = arg();
  $query = 'q=id:' . $path_parts[1];
  $json = _get_search_results_from_edan($query);

  echo '<pre>' . $json . '</pre>';
  exit();
}
