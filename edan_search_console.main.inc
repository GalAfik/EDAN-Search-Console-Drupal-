<?php

include('edan_search_console.utilities.inc');

function _edan_search_console_build_query_tab($form, &$form_state) {
  $form['query_tab'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Query'),
    '#group' => 'group_tabs',
    );
  $form['query_tab']['query'] = array(
    '#title' => t('Raw Decoded Query'),
    '#type' => 'textarea',
    '#description' => 'You may enter your search filters as a raw query into this field in order to narrow down your search results.',
    '#group' => 'query_tab',
    );
  $form['query_tab']['encoded_query'] = array(
    '#title' => t('Encoded Query'),
    '#type' => 'item',
    '#markup' => '<pre>' . (isset($form_state['encoded_query']) ? $form_state['encoded_query'] : '') . '</pre>',
    '#description' => 'This is a URL-safe encoded query to use in your application.',
    '#group' => 'query_tab',
    );
  // submit button
  $form['query_tab']['button_container'] = array(
    '#type' => 'item',
    '#attributes' => array('class' => array('container-inline')),
    );
  $form['query_tab']['button_container']['submit'] = array(
    '#value' => 'Submit',
    '#type' => 'submit',
    '#name' => 'query_submit',
    '#group' => 'query_tab',
    );
  $form['query_tab']['button_container']['clear'] = array(
    '#value' => 'Clear',
    '#type' => 'submit',
    '#name' => 'query_clear',
    '#group' => 'query_tab',
    '#attributes' => array('style' => 'background: #008cba; color: #fff;'),
    );

  return $form;
}

function _edan_search_console_build_collections_tab($form, &$form_state) {
  $form['collections_url_tab'] = array(
    '#type'  => 'fieldset',
    '#title' => t('URL'),
    '#group' => 'group_tabs',
    );
  $form['collections_url_tab']['collections_url'] = array(
    '#title' => t('Collections URL'),
    '#type' => 'textfield',
    '#description' => 'Paste a <b><a href="http://collections.si.edu" target="_blank">collection.si.edu</a></b> URL into the field above to replicate the search on this page. You may modify the search using the Search Filters above or by adding requirements to the Raw Query below.',
    '#group' => 'collections_url_tab',
    '#maxlength' => 100000,
    );
  $form['collections_url_tab']['collections_rows'] = array(
    '#title' => t('rows ( 100 max )'),
    '#type' => 'textfield',
    '#default_value' => 10,
    '#description' => 'All Collections.si.edu searches default to <b>10 rows</b>.',
    '#group' => 'collections_url_tab',
    );
  // submit button
  $form['collections_url_tab']['button_container'] = array(
    '#type' => 'item',
    '#attributes' => array('class' => array('container-inline')),
    );
  $form['collections_url_tab']['button_container']['submit'] = array(
    '#value' => 'Submit',
    '#type' => 'submit',
    '#name' => 'collections_url_submit',
    '#prefix' => '<br>',
    '#group' => 'collections_url_tab',
    );
  $form['collections_url_tab']['button_container']['clear'] = array(
    '#value' => 'Clear',
    '#type' => 'submit',
    '#name' => 'collections_clear',
    '#group' => 'collections_url_tab',
    '#attributes' => array('style' => 'background: #008cba; color: #fff;'),
    );

  return $form;
}

function _edan_search_console_build_filters_tab($form, &$form_state) {
  // Search Field Filters Tab
  $form['search_field_filters_tab'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Filters'),
    '#group' => 'group_tabs',
    );

  $form['search_field_filters_tab']['q'] = array(
    '#title' => t('q'),
    '#type' => 'textfield',
    '#description' => 'The q parameter is normally the main query for the request. See Solr query syntax for more information on different types of queries and syntaxes.',
    '#group' => 'search_field_filters_tab',
    );
  $form['search_field_filters_tab']['rows'] = array(
    '#title' => t('rows ( 100 max )'),
    '#type' => 'textfield',
    '#default_value' => 10,
    '#description' => 'This parameter is used to paginate results from a query. It specify the maximum number of documents from the complete result set to return to the client for every request. You can consider it as the maximum number of result appear in the page. (default_value value:10)',
    '#group' => 'search_field_filters_tab',
    );
  $form['search_field_filters_tab']['start'] = array(
    '#title' => t('start ( Do not exceed the maximum number of records! )'),
    '#type' => 'textfield',
    '#default_value' => 1,
    '#description' => 'This parameter is used to paginate results from a query. When specified, it indicates the offset (by default, 1) in the complete result set for the queries where the set of returned documents should begin.',
    '#group' => 'search_field_filters_tab',
    );

  $object_types = _edan_search_console_get_object_types();

  $form['search_field_filters_tab']['record_type'] = array(
    '#type' => 'select',
    '#title' => t('Record Type'),
    '#description' => 'This selection will limit the results to only show records of the selected type.',
    '#options' => $object_types,
    '#group' => 'search_field_filters_tab',
    '#ajax' => array(
      'wrapper' => 'facet-wrapper',
      'callback' => 'search_console_ajax_callback',
      ),
    );

  // Get the value of the 'record_type' field.
  $form['search_field_filters_tab']['facets'] = array(
    '#type' => 'fieldset',
    '#title' => 'Facets',
    '#prefix' => '<div id="facet-wrapper">',
    '#suffix' => '</div>',
    '#description' => 'Facets can be used to narrow your search query by specific attributes contained within each record. In order to select all records containing images, you might add an "Online Media Type" facet and set it to "Images". Some available facets and their qualified values may be viewed <a href="/edan/facets-reference-guide" target="_blank">here</a>.',
    );

  // get list of facet names based on type
  // $facets = array();
  // foreach ($object_types as $key => $value) {
  //   $facets[ $key ] = _edan_search_console_get_facets_from_edan( $key );
  // }

  // logic for building out facet fields
  if(empty($form_state['facet_num_items']) && empty($form_state['default_facets'])) {
    $form_state['facet_num_items'] = 0;
  }
  $form_state['facet_num_items'] = !empty($form_state['facet_num_items']) ? $form_state['facet_num_items'] : 0;
  $form_state['facet_num_items'] = !empty($form_state['default_facets']) ? count($form_state['default_facets']) : 0;


  // handling for autocomplete tooltip on facet input fields
  drupal_add_library('system', 'ui.autocomplete');
  $object_type = isset($form_state['values']['record_type']) ? $form_state['values']['record_type'] : '';
  // build out all of the facet forms
  if (!empty($form_state['default_facets'])) {
    // manually set up a counter
    $i = 1;
    // set the record type if it exists and remove it from the array
    if (array_key_exists('type', $form_state['default_facets'])) {
      $form_state['input']['record_type'] = $form_state['default_facets']['type'];
      unset($form_state['default_facets']['type']);
    }
    // build out the facets
    foreach ($form_state['default_facets'] as $key => $value) {
      $options = _edan_search_console_get_facet_names($object_type);
      // only add the facet if it exists for the record type
      if (array_key_exists($key, $options)) {
        $form['search_field_filters_tab']['facets']['facet_name_' . $i] = array(
          '#type' => 'select',
          '#title' => t('Facet #' . $i),
          '#options' => $options,
          '#default_value' => $key,
          );
        $form['search_field_filters_tab']['facets']['facet_value_' . $i] = array(
          '#type' => 'textfield',
          '#default_value' => $value,
          '#group' => 'search_field_filters_tab',
          );

        // advance counter to match loop
        $i++;
      }
    }

  } else {
    for ($i = 1; $i <= $form_state['facet_num_items']; $i++) {
      $form['search_field_filters_tab']['facets']['facet_name_' . $i] = array(
        '#type' => 'select',
        '#title' => t('Facet #' . $i),
        '#options' => _edan_search_console_get_facet_names($object_type),
        // '#ajax' => array(
        //   'wrapper' => 'facet-wrapper',
        //   'callback' => 'search_console_ajax_callback',
        //   ),
        );
      $form['search_field_filters_tab']['facets']['facet_value_' . $i] = array(
        '#type' => 'textfield',
        '#group' => 'search_field_filters_tab',
        );

      $form_state['facet_name'] = isset($form_state['values']['facet_name_' . $i]) ? $form_state['values']['facet_name_' . $i] : '';

      // following this, autocomplete_options contains an array of facet names that each contains an array of possible facet values for that field
      $autocomplete_options = array();
      $results = json_decode(_edan_search_console_get_facets_from_edan(), TRUE);
      foreach ($results['facets'] as $facet_name => $facet_values) {
        foreach ($facet_values as $facet_value) {
          $autocomplete_options[ $facet_name ][] = $facet_value[0];
        }
      }
    }

    // // add tooltip script for each field that has existing facets
    // if (array_key_exists($facet_name, $autocomplete_options)) {
    //   $autocomplete_js = '
    //   jQuery(document).ready(function() {
    //     var tags =' . json_encode($autocomplete_options[$facet_name]) . ';
    //     jQuery("[id^=edit-facet-value-' . $i . ']").autocomplete({
    //       source: tags,
    //       minLength: 0
    //     });
    //     jQuery("[id^=edit-facet-value-' . $i . ']").click(function() {
    //       jQuery("[id^=edit-facet-value-' . $i . ']").autocomplete( "search", "" );
    //     });
    //   });';
    //   drupal_add_js($autocomplete_js, 'inline');
    // }
  }

  $form['search_field_filters_tab']['facets']['add_facet_item'] = array(
    '#name' => 'add_facet_item',
    '#type' => 'submit',
    '#value' => t('Add a Facet'),
    '#submit' => array('_edan_search_console_facet_add_item'),
    '#attributes' => array('style' => 'font-size: 0.8rem; padding: 6px 8px; border-radius: 4px; margin-bottom: 0rem;'),
    '#group' => 'search_field_filters_tab',
    );

  // If we have more than one item, this button allows removal of the last item.
  if ($form_state['facet_num_items'] > 0) {
    $form['search_field_filters_tab']['facets']['remove_facet_item'] = array(
      '#name' => 'remove_facet_item',
      '#type' => 'submit',
      '#value' => t('Remove Latest Facet'),
      '#submit' => array('_edan_search_console_facet_remove_item'),
      '#limit_validation_errors' => array(),
      '#attributes' => array('style' => 'font-size: 0.8rem; padding: 6px 8px; border-radius: 4px; margin-bottom: 0rem;'),
      '#group' => 'search_field_filters_tab',
      );
  }

  // submit button
  $form['search_field_filters_tab']['button_container'] = array(
    '#type' => 'item',
    '#attributes' => array('class' => array('container-inline')),
    );
  $form['search_field_filters_tab']['button_container']['submit'] = array(
    '#value' => 'Submit',
    '#type' => 'submit',
    '#name' => 'search_field_filters_submit',
    '#prefix' => '<br>',
    '#group' => 'search_field_filters_tab',
    );
  $form['search_field_filters_tab']['button_container']['clear'] = array(
    '#value' => 'Clear',
    '#type' => 'submit',
    '#name' => 'filters_clear',
    '#group' => 'search_field_filters_tab',
    '#attributes' => array('style' => 'background: #008cba; color: #fff;'),
    );

  return $form;
}

function _edan_search_console_build_results_area($form, &$form_state) {
  $form['rows_reference'] = array(
   '#type' => 'item',
   '#markup' => isset($form_state['rows_reference']) ? '<b>Number of Records Found:</b><pre>' . $form_state['rows_reference'] . '</pre>' : '',
   );
  $form['rows_returned_reference'] = array(
   '#type' => 'item',
   '#markup' => isset($form_state['rows_returned_reference']) ? '<b>Number of Records Returned:</b><pre>' . $form_state['rows_returned_reference'] . '</pre>' : '',
   );
  $form['query_reference'] = array(
    '#type' => 'item',
    '#markup' => isset($form_state['query_reference']) ? '<b>Last Valid Query:</b><pre>' . str_replace(' ', '+', urldecode($form_state['query_reference'])) . '</pre>' : '',
    );

  // results display area
  $form['group_search_results_tabs'] = array(
    '#type'     => 'vertical_tabs',
    );

  if(isset($form_state['structured_search_results'])){
    $form['structured_search_results_tab'] = array(
      '#type'  => 'fieldset',
      '#title' => t('Structured Results'),
      '#group' => 'group_search_results_tabs',
      );

    if(!empty($form_state['structured_search_results'])){
      foreach ($form_state['structured_search_results'] as $key => $record) {
        $fields_to_ignore = array(
          'content',
          'title',
          'hash',
          'docSignature',
          'lastTimeUpdated',
          );
        // get fields printed out nicely for the structured search resutls
        $fields = '';
        $fields .= (isset($record['title']) ? '<h2>' . $record['title'] . '</h2>' : '');
        foreach ($record as $field_key => $field_value) {
          if(!in_array($field_key, $fields_to_ignore)) {
            $fields .= '<strong>' . str_pad($field_key . ':', 16) . '</strong>' . $field_value . "\n";
          }
        }
        // add an image to the result if one exists
        $image = '';
        // if it's an ids image
        if (isset($record['content']['descriptiveNonRepeating']['online_media']['media'][0]['idsId'])) {
          // set the thumbnail
          $thumbnail_link_literal = $record['content']['descriptiveNonRepeating']['online_media']['media'][0]['idsId'];
          $thumbnail_link = 'https://ids.si.edu/ids/deliveryService/?max_w=100&id=' . $thumbnail_link_literal;
          // set the link
          $full_image_link_literal = $record['content']['descriptiveNonRepeating']['online_media']['media'][0]['idsId'];
          $full_image_link = 'https://ids.si.edu/ids/deliveryService/?id=' . $full_image_link_literal;
          // create the image tag
          $image = '<a href="' . $full_image_link . '" target="_blank" style="display: flex;max-width: 25%;margin: auto;"><img src="' . $thumbnail_link . '"></a>';
        }elseif (isset($record['content']['descriptiveNonRepeating']['online_media']['media'][0]['thumbnail'])) {
          // set the thumbnail
          $thumbnail_link_literal = $record['content']['descriptiveNonRepeating']['online_media']['media'][0]['thumbnail'];
          $thumbnail_link = startsWith('http', $thumbnail_link_literal) ? $thumbnail_link_literal : 'https://ids.si.edu/ids/deliveryService/?max_w=100&id=' . $thumbnail_link_literal;
          // set the link
          $full_image_link_literal = $record['content']['descriptiveNonRepeating']['online_media']['media'][0]['content'];
          $full_image_link = startsWith('http', $thumbnail_link_literal) ? $full_image_link_literal : 'https://ids.si.edu/ids/deliveryService/?id=' . $full_image_link_literal;
          // create the image tag
          $image = '<a href="' . $full_image_link . '" target="_blank" style="display: flex;max-width: 25%;margin: auto;"><img src="' . $thumbnail_link . '"></a>';
        }

        $form['structured_search_results_tab']['structured_search_results'][$key] = array(
          '#type' => 'item',
          '#markup' => '<pre>' .
          ( !empty($image) ?
            '<div style="float:left; max-width: 70%; padding-right: 5%;">' . $fields . '</div>' . $image
            :
            '<div style="float:left;">' . $fields . '</div>' ) .
          '<a href="/edan/search-console/full-record/' . $record['id'] . '" target="_blank" style="float: left;clear: both;">View Full Record</a>
        </pre>',
        '#group' => 'structured_search_results_tab',
        );
      }
    }else{
      drupal_set_message('Your search returned no results. This may be due to a lack of matching records within EDAN or an invalid parameter. Please check that all of your parameters are set correctly.', 'warning');
      $form['structured_search_results_tab']['structured_search_results'] = array(
        '#type' => 'item',
        '#markup' => '<pre>The Query returned no results.</pre>',
        '#group' => 'structured_search_results_tab',
        );
    }
  }

  if(isset($form_state['raw_json_results'])){

    $form['raw_json_results_tab'] = array(
      '#type'  => 'fieldset',
      '#title' => t('Raw JSON Results'),
      '#group' => 'group_search_results_tabs',
      );


    if(!empty($form_state['raw_json_results'])) {
      if(substr_count( $form_state['raw_json_results'], "\n" ) <= 1000){
        $output = $form_state['raw_json_results'];
        $link_to_fulltext = '';
      }else {
        $lines = explode("\n", $form_state['raw_json_results']);
        $output = implode("\n", array_slice($lines, 0, 1000));
        $link_to_fulltext = '<a href="/edan/search-console/full-json/' . $form_state['query_reference'] . '"" target="_blank">Click to view full JSON</a>';
      }

      $form['raw_json_results_tab']['copy_to_clipboard'] = array(
        '#value' => 'Copy to Clipboard',
        '#type' => 'submit',
        '#name' => 'copy',
        '#group' => 'raw_json_results_tab',
        '#attributes' => array('style' => '-webkit-border-radius: 0px;'),
        );

      // print out the json output
      $form['raw_json_results_tab']['raw_json_results'] = array(
        '#type' => 'item',
        '#markup' =>
        '<textarea id="holdtext" style="height: 20px; width: 20px; position: absolute; top: -10000px;"">' . $form_state['raw_json_results'] . '</textarea>
        <pre>' . $output . '</pre>' . $link_to_fulltext,
        '#group' => 'raw_json_results_tab',
        );
    }
  }
  if(!empty($form_state['structured_search_results']) || !empty($form_state['raw_json_results'])){
    $form['link_to_top'] = array(
      '#type' => 'item',
      '#markup' => '<a href="#">Back to top of page</a>',
      );
  }

  return $form;
}

function edan_search_console_form($form, &$form_state) {

  // admin permissions area
  if (user_access('administer search console settings')) {
    // hyperlink to the admin page for changing authentication settings
    $form['link_to_settings'] = array(
      '#type' => 'item',
      '#markup' => 'Settings may be changed through the ' . l('settings page', '/admin/content/edan-search-console') . '.',
      );
  }

  $form['group_tabs'] = array(
    '#type'     => 'vertical_tabs',
    );

  // build the form tabs
  $form = _edan_search_console_build_filters_tab($form, $form_state);
  $form = _edan_search_console_build_query_tab($form, $form_state);
  $form = _edan_search_console_build_collections_tab($form, $form_state);
  // build the results area
  $form = _edan_search_console_build_results_area($form, $form_state);

  // Required file manangement JS
  drupal_add_js(
    drupal_get_path('module', 'edan_search_console') . '/js/edan_search_console.js',
    array('scope' => 'footer', 'weight' => 3)
    );
  drupal_add_css(
    drupal_get_path('module', 'edan_search_console') . '/css/edan_search_console.css',
    array('group' => CSS_DEFAULT, 'every_page' => TRUE)
    );

  return $form;
}

function _edan_search_console_facet_add_item($form, &$form_state) {
  $form_state['facet_num_items']++;
  $form_state['rebuild'] = TRUE;
}

function _edan_search_console_facet_remove_item($form, &$form_state) {
  if ($form_state['facet_num_items'] > 0) {
    $form_state['facet_num_items']--;
  }
  $form_state['rebuild'] = TRUE;
}

function edan_search_console_ajax_callback($form, $form_state) {
  return $form['search_field_filters_tab']['facets'];
}

function edan_search_console_form_submit($form, &$form_state) {
  // initialize the empty query that will eventually be submitted to EDAN for results
  $query = '';

  // check which tab on the search form submitted to this function and therefore, which fields need to be checked for relevant data
  switch($form_state['triggering_element']['#name']){

    // this is the filters tab form
    case 'search_field_filters_submit':

    // add optional parameters if they are set
    $query_parameters = array();
    $query_parameters['q'] = !empty($form_state['values']['q']) ? $form_state['values']['q'] : '';
    $query_parameters['rows'] = !empty($form_state['values']['rows']) ? $form_state['values']['rows'] : '0';
    $query_parameters['start'] = !empty($form_state['values']['start']) ? $form_state['values']['start'] : '1';
    $query_parameters['fqs'] = array();

    // build out the fqs from applicable, set facets and set record type according to dropdown selection
    if(isset($form_state['values']['record_type']) && !empty($form_state['values']['record_type'])) {
      // look for only records of type record_type
      $record_type = $form_state['values']['record_type'];
      $query_parameters['fqs'][] = 'type:' . $record_type;
    }

    // add facets to search
    foreach ($form_state['values'] as $key => $value) {
      if (startsWith('facet_name_', $key) && !empty($value)) {
        $facet_number = str_replace('facet_name_', '', $key);
        if (array_key_exists('facet_value_' . $facet_number, $form_state['values']) &&
          !empty($form_state['values']['facet_value_' . $facet_number])) {
          // add this name:value pair to the fqs
          $query_parameters['fqs'][] = $form_state['values']['facet_name_' . $facet_number] . ':' . $form_state['values']['facet_value_' . $facet_number];
        }
      }
    }

    // build out the final query
    $query = 'fqs=[';
    // add all fq parameters as fqs to the final query first
    $last_element_in_array = count($query_parameters['fqs']) - 1;
    foreach ($query_parameters['fqs'] as $key => $fq) {
      $query .= '"' . str_replace(',', '+', $fq) . '"';
      // add comma if this is not the last element
      if ($key != $last_element_in_array) {
        $query .= ',';
      }
    }
    $query .= ']';
    // unset fqs from the parameters to make sure it's not reapplied
    unset($query_parameters['fqs']);
    foreach ($query_parameters as $key => $value) {
      // only add the ampersand if the query is not empty
      if (!empty($query)) {
        $query .= '&';
      }
      // add value to the query
      $query .= $key . '=' . str_replace(',', '+', $value);
    }

    // get rid of unnecessary spaces in the query
    $query = str_replace(' ', '+', $query);
    $query = preg_replace('/[++]+/', '+', $query);

    // set form reference for the final query
    $form_state['query_reference'] = $query;
    $form_state['default_facets'] = array();

    // set query on the query tab
    $form_state['input']['query'] = $query;
    $form_state['encoded_query'] = urlencode($query);
    $form_state['input']['collections_rows'] = $query_parameters['rows'];
    break;


    // this is the collections url form
    case 'collections_url_submit':
    // get the query from a collections.si.edu url
    if(!empty($form_state['values']['collections_url'])){

      // reset the filters fields
      $form_state['input']['q'] = '';
      $form_state['input']['rows'] = 10;
      $form_state['input']['start'] = 1;

      // set query
      $temp_query = end(explode('http://collections.si.edu/search/results.htm?', urldecode($form_state['values']['collections_url'])));
      $temp_query_parameters = explode('&', $temp_query);
      $query_parameters = array();
      $query_parameters['fqs'] = array();
      // set the key to the parameter name and the value to just the value
      foreach ($temp_query_parameters as $temp_query_param) {
        // the key in this case is the parameter
        $key = reset(explode('=', $temp_query_param));
        // the value is what the parameter is set to
        $value = end(explode('=', $temp_query_param));
        switch ($key) {
          case 'fq':
          $sanitized_value = str_replace('"', '', urldecode($value));
          $query_parameters['fqs'][] = $sanitized_value;
          break;
          case 'q':
          $query_parameters['q'] = $value;
          // set the filters on the filters tab
          $form_state['input']['q'] .= $value;
          break;
          default:
          $query_parameters[$key] = $value;
          // set the filters on the filters tab
          if (isset($form_state['input'][$key])) {
            $form_state['input'][$key] = $value;
          }
          break;
        }
      }

      // build out the final query
      $query = 'fqs=[';
      $form_state['default_facets'] = array();
      // add all fq parameters as fqs to the final query first
      $last_element_in_array = count($query_parameters['fqs']) - 1;
      foreach ($query_parameters['fqs'] as $key => $fq) {
        $query .= str_replace(',', '+', $fq);
        // add comma if this is not the last element
        if ($key != $last_element_in_array) {
          $query .= ',';
        }

        // set the filters on the filters tab
        $fq_key = reset(explode(':', $fq));
        $fq_value = end(explode(':', $fq));
        $form_state['default_facets'][$fq_key] = $fq_value;
      }
      $query .= ']';
      // unset fqs from the parameters to make sure it's not reapplied
      unset($query_parameters['fqs']);
      foreach ($query_parameters as $key => $value) {
        // only add the ampersand if the query is not empty
        if (!empty($query)) {
          $query .= '&';
        }
        // add value to the query
        $query .= $key . '=' . str_replace(',', '+', $value);
      }
      // add rows to the final query if necessary
      if (!empty($form_state['input']['collections_rows'])) {
        $query .= '&rows=' . $form_state['input']['collections_rows'];
        $form_state['input']['rows'] = $form_state['input']['collections_rows'];
      }

      // get rid of unnecessary spaces in the query
      $query = str_replace(' ', '+', $query);
      $query = preg_replace('/[+]{2,}/', '+', $query);

      // set form reference for the final query
      $form_state['query_reference'] = $query;

      // set query on the query tab
      $form_state['input']['query'] = $query;
      $form_state['encoded_query'] = urlencode($query);
      $form_state['input']['record_type'] = 'edanmdm';
    }
    break;


    // this is the simple query form
    case 'query_submit':

    if(!empty($form_state['values']['query'])){
      $query = str_replace(' ', '+', $form_state['values']['query']);
      // set the encoded query for reference
      $form_state['encoded_query'] = urlencode($query);
    }
    $form_state['query_reference'] = $query;


    // reset the filters fields
    $form_state['input']['q'] = '';
    $form_state['input']['rows'] = 10;
    $form_state['input']['start'] = 1;
    $form_state['input']['collections_url'] = '';
    // fill in the other tabs using the query as reference
    $temp_query_parameters = explode('&', $query);
    $query_parameters['fqs'] = array();
    foreach ($temp_query_parameters as $temp_query_param) {
      // the key in this case is the parameter
      $key = reset(explode('=', $temp_query_param));
      // the value is what the parameter is set to
      $value = end(explode('=', $temp_query_param));
      switch ($key) {
        case 'fqs':
        $fqs_array = explode(',', str_replace('"', '', substr($value, 1, -1)));
        foreach ($fqs_array as $fq) {
          $query_parameters['fqs'][] = $fq;
        }
        break;
        case 'q':
        $form_state['input']['q'] .= $value;
        break;
        case 'rows':
        $form_state['input']['rows'] = $value;
        $form_state['input']['collections_rows'] = $value;
        break;
        default:
        if (isset($form_state['input'][$key])) {
          $form_state['input'][$key] = $value;
        }
        break;
      }
    }

    $form_state['default_facets'] = array();
    foreach ($query_parameters['fqs'] as $key => $fq) {
      // set the filters on the filters tab
      $fq_key = reset(explode(':', $fq));
      $fq_value = end(explode(':', $fq));
      $form_state['default_facets'][$fq_key] = $fq_value;
    }
    break;
  }

  // this block submits the query to EDAN and cleans up/prints out the results for the user
  if(!empty($query)){

    // error handling section
    $query_parameters = array();
    $parameter_array = explode('&', $query);
    foreach ($parameter_array as $value) {
      list($k, $v) = explode('=', $value);
      $query_parameters[$k] = $v;
    }
    // q is empty
    if (!isset($query_parameters['q']) || empty($query_parameters['q'])) {
      drupal_set_message('You have not entered a "q" value! Your EDAN search will return a list of generic records.', 'warning');
    }
    // rows is invalid
    if (!isset($query_parameters['rows']) || !is_numeric($query_parameters['rows']) || $query_parameters['rows'] <= 0) {
      drupal_set_message('The "rows" value you have entered seems to be invalid (' . (isset($query_parameters['rows']) ? $query_parameters['rows'] : 'EMPTY VALUE') . '). Make sure that "rows" is a positive integer between 1 and 100.', 'warning');
    }
    // start is invalid
    if (!isset($query_parameters['start']) || !is_numeric($query_parameters['start']) || $query_parameters['start'] < 0) {
      drupal_set_message('The "start" value you have entered seems to be invalid (' . (isset($query_parameters['start']) ? $query_parameters['start'] : 'EMPTY VALUE') . '). Make sure that "start" is a positive integer above 0.', 'warning');
    }

    // set the raw json results
    $raw_json_results = _edan_search_console_get_search_results_from_edan(isset($query) ? $query : '');
    $form_state['raw_json_results'] = $raw_json_results;

    // set the structured search results
    $raw_json = json_decode($raw_json_results, true);
    if(isset($raw_json['rows'])){
      $form_state['rows_reference'] = $raw_json['numFound'];
      $form_state['rows_returned_reference'] = count($raw_json['rows']);
      // reset the results
      $form_state['structured_search_results'] = array();
      // add rows to results
      foreach ($raw_json['rows'] as $key => $record) {
        $form_state['structured_search_results'][] = $record;
      }
    }else{
      drupal_set_message('Something went wrong. Please contact an Administrator for help.', 'error');
    }
  }else{
    drupal_set_message('The query you entered seems to be empty. Please adjust your search and try again or contact an Administrator for help.', 'error');
  }

  // rebuild the form with new inputs and results set
  $form_state['rebuild'] = TRUE;
}