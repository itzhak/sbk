<?php
/* And the view, originally an export
        tips: http://drupal.org/node/685432 */
  // replaced with line below... $view = new view;
  // Create a new view
//function _verdant_share_views_default_views($quicklinks) {
function verdant_share_views_default_views() {

  // define the view with code form an export (will be modified?)

	/* BEGIN EXPORT, look for $quicklinks position in last version */

	//$quicklinks = "quicklinks might or might not be used.  Can I erase this?  iSee views_default_views.  I think it was used in the previous version, not adequate, and so has been replaced";

/* I don't think this can work -- the user's post can change fast...
	importing a view happens once, the view can then be changed,
	the user then changes their post, twisted up. */


$view = new view;
$view->name = 'verdant_module_rideshare';
$view->description = 'Rideshare View';
$view->tag = 'share';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('fields', array(
  'picture' => array(
    'label' => 'Picture',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'html' => 0,
      'strip_tags' => 0,
    ),
    'empty' => '',
    'hide_empty' => 0,
    'empty_zero' => 0,
    'exclude' => 1,
    'imagecache_preset' => '3',
    'id' => 'picture',
    'table' => 'users',
    'field' => 'picture',
    'relationship' => 'none',
    'override' => array(
      'button' => 'Override',
    ),
  ),
  'contact' => array(
    'label' => 'Contact',
    'alter' => array(
      'alter_text' => 1,
      'text' => '<div class="contact-share">[contact]</div>',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'html' => 0,
      'strip_tags' => 0,
    ),
    'empty' => '',
    'hide_empty' => 0,
    'empty_zero' => 0,
    'text' => 'contact',
    'link_display' => 'icon',
    'exclude' => 1,
    'id' => 'contact',
    'table' => 'users',
    'field' => 'contact',
    'relationship' => 'none',
    'override' => array(
      'button' => 'Override',
    ),
  ),
  'name' => array(
    'label' => 'Contact',
    'alter' => array(
      'alter_text' => 1,
      'text' => '[picture] 
[name] 
[contact] ',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'html' => 0,
      'strip_tags' => 0,
    ),
    'empty' => '',
    'hide_empty' => 0,
    'empty_zero' => 0,
    'link_to_user' => 1,
    'overwrite_anonymous' => 0,
    'anonymous_text' => '',
    'exclude' => 0,
    'id' => 'name',
    'table' => 'users',
    'field' => 'name',
    'relationship' => 'none',
    'override' => array(
      'button' => 'Override',
    ),
  ),
  'city' => array(
    'label' => 'City',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'html' => 0,
      'strip_tags' => 0,
    ),
    'empty' => '',
    'hide_empty' => 0,
    'empty_zero' => 0,
    'exclude' => 1,
    'id' => 'city',
    'table' => 'location',
    'field' => 'city',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
  'distance' => array(
    'label' => 'Distance',
    'alter' => array(
      'alter_text' => 1,
      'text' => '[distance] 
<br>[city]',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'html' => 0,
      'strip_tags' => 0,
    ),
    'empty' => '',
    'hide_empty' => 0,
    'empty_zero' => 0,
    'origin' => 'php',
    'units' => 'km',
    'latitude' => '',
    'longitude' => '',
    'postal_code' => '',
    'country' => '',
    'php_code' => '/* get the lat and long of the current user\'s post */

// get the current user id
global $user;
$uid = $user->uid;

// get the node for the rideshare for this uid
$node = node_load(array( \'uid\' => $uid, \'type\' => \'share_ride\'  ));  

/* user inserted latitude longitude is in the highest priority */
if (isset($node->locations[0][locpick])) {
    $locs = $node->locations[0][locpick];
    $lat = $locs[user_latitude];
    $lon = $locs[user_longitude];
} else if (isset($node->location)) { /* geociding calculated latitude and longitude */
    $locs = $node->location;
    $lat = $locs[latitude];
    $lon = $locs[longitude];
} else { /* this is should be impossible */
    $lat = 0;
    $lon = 0;
}

//example return: return array(\'latitude\' => 30.2671530, \'longitude\' => 70.2671530);
return array(\'latitude\' => $lat, \'longitude\' => $lon);',
    'nid_arg' => 'nid',
    'nid_loc_field' => 'node',
    'uid_arg' => '',
    'exclude' => 0,
    'id' => 'distance',
    'table' => 'location',
    'field' => 'distance',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
  'changed' => array(
    'label' => 'Updated date',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'html' => 0,
      'strip_tags' => 0,
    ),
    'empty' => '',
    'hide_empty' => 0,
    'empty_zero' => 0,
    'date_format' => 'time ago',
    'custom_date_format' => '',
    'exclude' => 0,
    'id' => 'changed',
    'table' => 'node',
    'field' => 'changed',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
  'tid' => array(
    'label' => 'Vehicle',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'html' => 0,
      'strip_tags' => 0,
    ),
    'empty' => '',
    'hide_empty' => 0,
    'empty_zero' => 0,
    'type' => 'separator',
    'separator' => ', ',
    'link_to_taxonomy' => 1,
    'limit' => 1,
    'vids' => array(
      '1' => 1,
    ),
    'exclude' => 0,
    'id' => 'tid',
    'table' => 'term_node',
    'field' => 'tid',
    'relationship' => 'none',
    'override' => array(
      'button' => 'Override',
    ),
  ),
  'body' => array(
    'label' => 'Description',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'html' => 0,
      'strip_tags' => 0,
    ),
    'empty' => '',
    'hide_empty' => 0,
    'empty_zero' => 0,
    'exclude' => 0,
    'id' => 'body',
    'table' => 'node_revisions',
    'field' => 'body',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
));
$handler->override_option('sorts', array(  
  'distance' => array(
    'order' => 'ASC',
    'origin' => 'php',
    'latitude' => '',
    'longitude' => '',
    'postal_code' => '',
    'country' => '',
    'php_code' => '/* get the lat and long of the current user\'s post */

// get the current user id
global $user;
$uid = $user->uid;

// get the node for the rideshare for this uid
$node = node_load(array( \'uid\' => $uid, \'type\' => \'share_ride\'  ));  

/* user inserted latitude longitude is in the highest priority */
if (isset($node->locations[0][locpick])) {
    $locs = $node->locations[0][locpick];
    $lat = $locs[user_latitude];
    $lon = $locs[user_longitude];
} else if (isset($node->location)) { /* geociding calculated latitude and longitude */
    $locs = $node->location;
    $lat = $locs[latitude];
    $lon = $locs[longitude];
} else { /* this is should be impossible */
    $lat = 0;
    $lon = 0;
}

//example return: return array(\'latitude\' => 30.2671530, \'longitude\' => 70.2671530);
return array(\'latitude\' => $lat, \'longitude\' => $lon);',
    'nid_arg' => '',
    'nid_loc_field' => 'node',
    'uid_arg' => '',
    'id' => 'distance',
    'table' => 'location',
    'field' => 'distance',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
));
$handler->override_option('filters', array(
  'status' => array(
    'operator' => '=',
    'value' => '1',
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'status',
    'table' => 'node',
    'field' => 'status',
    'relationship' => 'none',
  ),
  'type' => array(
    'operator' => 'in',
    'value' => array(
      'share_ride' => 'share_ride',
    ),
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'type',
    'table' => 'node',
    'field' => 'type',
    'relationship' => 'none',
    'override' => array(
      'button' => 'Override',
    ),
  ),  
  'date_filter' => array(
    'operator' => 'between',
    'value' => array(
      'value' => NULL,
      'min' => NULL,
      'max' => NULL,
      'default_date' => '',
      'default_to_date' => '',
    ),
    'group' => '0',
    'exposed' => TRUE,
    'expose' => array(
      'use_operator' => 0,
      'operator' => 'date_filter_op',
      'identifier' => 'date_filter_arrive',
      'label' => 'Arrive',
      'optional' => 1,
      'remember' => 0,
    ),
    'date_fields' => array(
      'node_data_field_arrival_time.field_arrival_time_value' => 'node_data_field_arrival_time.field_arrival_time_value',
    ),
    'date_method' => 'OR',
    'granularity' => 'hour',
    'form_type' => 'date_popup',
    'default_date' => '',
    'default_to_date' => '',
    'year_range' => '-3:+3',
    'id' => 'date_filter',
    'table' => 'node',
    'field' => 'date_filter',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
  'date_filter_1' => array(
    'operator' => 'between',
    'value' => array(
      'min' => NULL,
      'max' => NULL,
      'value' => NULL,
      'default_date' => '',
      'default_to_date' => '',
    ),
    'group' => '0',
    'exposed' => TRUE,
    'expose' => array(
      'operator' => 'date_filter_1_op',
      'label' => 'Departure',
      'use_operator' => 0,
      'identifier' => 'date_filter_depart',
      'optional' => 1,
      'remember' => 0,
    ),
    'date_fields' => array(
      'node_data_field_departure_time.field_departure_time_value' => 'node_data_field_departure_time.field_departure_time_value',
    ),
    'date_method' => 'AND',
    'granularity' => 'hour',
    'form_type' => 'date_popup',
    'default_date' => '',
    'default_to_date' => '',
    'year_range' => '-3:+3',
    'id' => 'date_filter_1',
    'table' => 'node',
    'field' => 'date_filter',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
));
$handler->override_option('access', array(
  'type' => 'none',
));
$handler->override_option('cache', array(
  'type' => 'none',
));
$handler->override_option('title', 'Share the Ride');
//$handler->override_option('header', 'Click on a heading such as "Arrive" to sort by that column.  Or use the last column to prioritize matches for the next time you come back to this page.<strong>Match by:</strong>: <a href="?flagged_favorites=All&unflagged_remove=0" 
//			title="All shares except those you have removed" >All</a> | <a href="?flagged_favorites=All&unflagged_remove=0&date_filter[min][date]=2010-06-14&date_filter[min][time]=20%3A30&date_filter[max][date]=2010-06-15&date_filter[max][time]=00:30" 
//			title="" >Match My Arrival -- 4 hour window</a> | <a href="?flagged_favorites=All&unflagged_remove=0&date_filter_depart[min][date]=2010-06-25&date_filter_depart[min][time]=06%3A31&date_filter_depart[max][date]=2010-06-25&date_filter_depart[max][time]=10%3A31" 
//			title="" >Match My Departure  -- 4 hour window</a> | <a href="?flagged_favorites=All&unflagged_remove=0&date_filter_depart[min][date]=2010-06-25&date_filter_depart[min][time]=06%3A31&date_filter_depart[max][date]=2010-06-25&date_filter_depart[max][time]=10%3A31&date_filter[min][date]=2010-06-14&date_filter[min][time]=20%3A30&date_filter[max][date]=2010-06-15&date_filter[max][time]=00:30" 
//			title="" >Matches</a> | <a href="?flagged_favorites=1&unflagged_remove=0" 
//			title="" >Favorites Only</a> | <a href="?flagged_favorites=All&unflagged_remove=1" style="font-size: .9em;"
//			title="" >Check Previously Removed</a> | <a href="javascript: var obj= document.getElementById(views-exposed-form-verdant-module-generated-rideshare-page-2); obj.style.visibility = \'invisible\'">Power Options</a>');
$handler->override_option('header_format', '1');
$handler->override_option('header_empty', 0);
$handler->override_option('footer', 'Update your search: if you don\'t find a match, check that your post is up to date and click <em>save</em>.  Clicking save even if you don\'t make changes will let others know your post is fresh.');
$handler->override_option('footer_format', '1');
$handler->override_option('footer_empty', 1);
$handler->override_option('empty', '<div class="message verdant-message">There are no matches for your current search choices.  <br/>Expand your selection choices above, or come back later.</div>');
$handler->override_option('empty_format', '2');
$handler->override_option('items_per_page', 0);
$handler->override_option('style_plugin', 'gmap');
$handler->override_option('style_options', array(
  'grouping' => '',
  'macro' => '[gmap ]',
  'datasource' => 'location',
  'latfield' => 'picture',
  'lonfield' => 'picture',
  'markers' => 'static',
  'markerfield' => 'picture',
  'markertype' => 'drupal',
));
$handler->override_option('exposed_block', TRUE);
$handler = $view->new_display('page', 'Chart', 'page_1');
$handler->override_option('style_plugin', 'table');
$handler->override_option('style_options', array(
  'grouping' => '',
  'override' => 1,
  'sticky' => 0,
  'order' => 'asc',
  'columns' => array(
    'picture' => 'picture',
    'name' => 'name',
    'contact' => 'contact',
    'city' => 'city',
    'distance' => 'distance',
    'tid' => 'tid',
    'body' => 'body',
    'changed' => 'changed',
  ),
  'info' => array(
    'picture' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'name' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'contact' => array(
      'separator' => '',
    ),
    'city' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'distance' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'tid' => array(
      'separator' => '',
    ),
    'body' => array(
      'separator' => '',
    ),
    'changed' => array(
      'sortable' => 1,
      'separator' => '',
    ),
  ),
  'default' => '-1',
));
$handler->override_option('path', 'share/ride/chart');
$handler->override_option('menu', array(
  'type' => 'normal',
  'title' => 'Rideshare Chart',
  'description' => '',
  'weight' => '0',
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'description' => '',
  'weight' => 0,
  'name' => 'navigation',
));
$handler = $view->new_display('page', 'Map', 'page_2');

$handler->override_option('arguments', array(
  'null' => array(
    'default_action' => 'default',
    'style_plugin' => 'default_summary',
    'style_options' => array(),
    'wildcard' => 'all',
    'wildcard_substitution' => 'All',
    'title' => '',
    'breadcrumb' => '',
    'default_argument_type' => 'php',
    'default_argument' => '',
    'validate_type' => 'none',
    'validate_fail' => 'not found',
    'must_not_be' => 0,
    'id' => 'null',
    'table' => 'views',
    'field' => 'null',
    'validate_user_argument_type' => 'uid',
    'validate_user_roles' => array(
      2 => 0,
    ),
    'override' => array(
      'button' => 'Use default',
    ),
    'relationship' => 'none',
    'default_options_div_prefix' => '',
    'default_argument_user' => 0,
    'default_argument_fixed' => '',
    'default_argument_php' => 'global $user;
$uid = $user->uid;

// get the node for the rideshare for this uid
$node = node_load(array( \'uid\' => $uid, \'type\' => \'share_ride\'  )); 
return $node->nid;',
    'validate_argument_node_type' => array(
      'share_ride' => 'share_ride',
      'page' => 0,
      'profile' => 0,
      'story' => 0,
    ),
    'validate_argument_node_access' => 0,
    'validate_argument_nid_type' => 'nid',
    'validate_argument_vocabulary' => array(
      1 => 0,
    ),
    'validate_argument_type' => 'tid',
    'validate_argument_transform' => 0,
    'validate_user_restrict_roles' => 0,
    'validate_argument_php' => '',
  ),
));

$handler->override_option('header', '<?php print("Create a rideshare post in the bottom of page.  That post will automatically set your defaults when you search.");?><br />

<p><div id="rideshare_map_key" style="display: inline; "><strong><?php print t("Key");?></strong>:&nbsp;&nbsp;&nbsp;<img src="/../../sites/all/modules/gmap/markers/small/bred.png"><?php print t("Passenger");?>&nbsp;&nbsp;&nbsp;<img src="/../../sites/all/modules/gmap/markers/small/orange.png"><?php print t("Driver or Passenger");?>&nbsp;&nbsp;&nbsp;<img src="/../../sites/all/modules/gmap/markers/small/yellow.png"><?php print t("Driver");?>&nbsp;&nbsp;&nbsp;<img src="/../../sites/all/modules/gmap/markers/small/green.png"><?php print t("Bus/Group taxi");?></div>
');
$handler->override_option('header_format', '3');
$handler->override_option('header_empty', 1);
$handler->override_option('style_options', array(
  'macro' => '[gmap zoom=11 | markers=drupal::37.68382032669382,-122.4382321536541 |width=98%|height=480px|control=Large |type=Map    ]    ',
  'datasource' => 'location',
  'latfield' => 'picture',
  'lonfield' => 'picture',
  'markers' => 'taxonomy',
  'markerfield' => 'picture',
  'markertype' => 'purple',
  'center_on_nodearg' => 1,
  'center_on_nodearg_arg' => 'null',
  'highlight_nodearg' => 0,
  'highlight_nodearg_arg' => 'null',
  'highlight_nodearg_color' => '#FF0000',
  'tooltipenabled' => 0,
  'tooltipfield' => 'picture',
));
$handler->override_option('row_plugin', 'node');
$handler->override_option('row_options', array(
  'relationship' => 'none',
  'build_mode' => 'teaser',
  'links' => 1,
  'comments' => 0,
));
$handler->override_option('path', 'share/ride/map');
$handler->override_option('menu', array(
  'type' => 'normal',
  'title' => 'Rideshare Map',
  'description' => '',
  'weight' => 0,
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'description' => '',
  'weight' => 0,
  'name' => 'navigation',
));



/*    END EXPORT  */

  // Let users play with this (is that a good idea?)
  $views[$view->name] = $view;

  return $views;
}

