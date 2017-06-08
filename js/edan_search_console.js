function clear_form_elements(ele) {
  // this js script handles styling and actions for the clear buttons on all 3 forms
  jQuery(ele).find(":input").each(function() {
    switch(this.type) {
      case "password":
      case "select-multiple":
      case "select-one":
      case "text":
      case "textarea":
      if (jQuery(this).attr("id") == "edit-rows" || jQuery(this).attr("id") == "edit-collections-rows") {
        jQuery(this).val("10");
      } else if (jQuery(this).attr("id") == "edit-start") {
        jQuery(this).val("1");
      } else {
        jQuery(this).val("");
      }
      break;
      case "checkbox":
      case "radio":
      this.checked = false;
    }
  });
}


jQuery(document).ready(function() {

  jQuery("#edit-clear, #edit-clear--2, #edit-clear--3").hover(
    function() {
      jQuery(this).css("background", "#0079a1")
    },
    function() {
      jQuery(this).css("background", "#008cba")
    }
  );

  jQuery("#edit-clear, #edit-clear--2, #edit-clear--3").click( function (e) {
    e.preventDefault();
    clear_form_elements(jQuery("#edan-search-console-form"));
  });

  // hide parts of description box
  jQuery(".filter-wrapper").hide();

  // handles copying to clipboard
  jQuery("#edit-copy-to-clipboard").click( function (e) {
    e.preventDefault();
    jQuery("#holdtext").select();
    // copy the temp input value to the clipboard
    document.execCommand("copy");
  });

  jQuery('#edan-search-console-form').keypress( function( e ) {
    var code = e.keyCode || e.which;
    if( code === 13 ) {
      e.preventDefault();
      return false;
    }
  })

});
