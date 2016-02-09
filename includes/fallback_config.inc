<?php
// $Id: fallback_config.inc,v 1.2 2007/05/22 12:26:34 mhaase Exp $
// -----------------------------------------------------------------------------
//                                                                            --
// Pryde Site Suite                                                           --
// fallback_config.inc                                                         --
//                                                                            --
// copyright: Marcus Haase (mail@marcus.haase.name)                           --
// The use of this Script is only allowed with the author's authorisation     --
// Any modification of the sources is strictly forbidden                      --
//                                                                            --
// -----------------------------------------------------------------------------

if (!isset($PSS["run_dir"])) $PSS["run_dir"] = '/content/';

if (!isset($PSS["admin_comment_languages"])) $PSS["admin_comment_languages"] = array('de', 'en');

if (!isset($PSS["thumbs_enable"]) || $PSS["thumbs_enable"] != true && $PSS["thumbs_enable"] != false)
	$PSS["thumbs_enable"] = true;

if (!isset($PSS["file_conf"])) $PSS["file_conf"] = '.pss.conf';
if (!isset($PSS["dir_thumbs"])) $PSS["dir_thumbs"] = '.thumbs';
if (!isset($PSS["dir_resize"])) $PSS["dir_resize"] = '.resize';

if (!isset($PSS["textcat_prefix"])) $PSS["textcat_prefix"] = '';

if (!isset($PSS["textcat_autodetect"]) || $PSS["textcat_autodetect"] != true && $PSS["textcat_autodetect"] != false)
	$PSS["textcat_autodetect"] = false;

if (!isset($PSS["textcat_use_userpath"]) || $PSS["textcat_use_userpath"] != true && $PSS["textcat_use_userpath"] != false)
	$PSS["textcat_use_userpath"] = false;

if (!isset($PSS["textcat_fallback"]) || $PSS["textcat_fallback"] != true && $PSS["textcat_fallback"] != false)
	$PSS["textcat_fallback"] = true;

if (!isset($PSS["linux_chmod_generated"]) || $PSS["linux_chmod_generated"] != true && $PSS["linux_chmod_generated"] != false)
	$PSS["linux_chmod_generated"] = false;

if (!isset($PSS["inherit_parentlink"]) || $PSS["inherit_parentlink"] != true && $PSS["inherit_parentlink"] != false)
	$PSS["inherit_parentlink"] = false;

if (!isset($PSS["textcat_file"]) || $PSS["textcat_file"] == '') $PSS["textcat_file"] = 'en';

if (!isset($PSS["image_quality"]) || $PSS["image_quality"] < 30 || $PSS["image_quality"] > 100)
	$PSS["image_quality"] = 75;

if (!isset($PSS["hide_footer"]) || $PSS["hide_footer"] != true && $PSS["hide_footer"] != false)
	$PSS["hide_footer"] = false;

if (!isset($PSS["page_title"]) || $PSS["page_title"] == '')
	$PSS["page_title"] = $_SERVER["HTTP_HOST"];

if (!isset($PSS["admin_enable"]) || $PSS["admin_enable"] != true && $PSS["admin_enable"] != false)
	$PSS["admin_enable"] = false;

if (!isset($PSS["admin_comment_textarea_width"]) || $PSS["admin_comment_textarea_width"] < 100 || $PSS["admin_comment_textarea_width"] > 600)
	$PSS["admin_comment_textarea_width"] = 300;

if (!isset($PSS["admin_comment_textarea_height"]) || $PSS["admin_comment_textarea_height"] < 50 || $PSS["admin_comment_textarea_height"] > 400)
	$PSS["admin_comment_textarea_height"] = 100;

if (!isset($PSS["admin_comment_linebreaks"]) || $PSS["admin_comment_linebreaks"] != 'html' && $PSS["admin_comment_linebreaks"] != 'text')
	$PSS["admin_comment_linebreaks"] = 'html';

if (!isset($PSS["search_enable"]) || $PSS["search_enable"] != true && $PSS["search_enable"] != false)
	$PSS["search_enable"] = false;

if (!isset($PSS["search_byuser"]) || $PSS["search_byuser"] != true && $PSS["search_byuser"] != false)
	$PSS["search_byuser"] = false;

if (!isset($PSS["search_byuser_selectwidth"]) || $PSS["search_byuser_selectwidth"] < 50 || $PSS["search_byuser_selectwidth"] > 500)
	$PSS["search_byuser_selectwidth"] = 150;

if (!isset($PSS["search_byuser_position"]) || $PSS["search_byuser_position"] != 'right' && $PSS["search_byuser_position"] != 'left')
	$PSS["search_byuser_position"] = 'left';

if (!isset($PSS["db_type"]) || $PSS["db_type"] != 'mysql' && $PSS["db_type"] != 'mysqli' && $PSS["db_type"] != 'mssql')
	$PSS["db_type"] = 'mysql';

if (!isset($PSS["db_table_files"])) $PSS["db_table_files"] = 'files';
if (!isset($PSS["db_table_matches"])) $PSS["db_table_matches"] = 'matches';
if (!isset($PSS["db_table_keywords"])) $PSS["db_table_keywords"] = 'keywords';
if (!isset($PSS["db_table_keywords"])) $PSS["db_table_keywords_lang"] = 'keywords_lang';
if (!isset($PSS["db_table_categories"])) $PSS["db_table_categories"] = 'categories';
if (!isset($PSS["db_table_categories"])) $PSS["db_table_categories_lang"] = 'categories_lang';
if (!isset($PSS["db_table_comments"])) $PSS["db_table_comments"] = 'comments';
if (!isset($PSS["db_table_users"])) $PSS["db_table_users"] = 'users';

if (!isset($PSS["allow_unpack"]) || $PSS["allow_unpack"] != true && $PSS["allow_unpack"] != false)
	$PSS["allow_unpack"] = false;

if (!isset($PSS["allow_changelog"]) || $PSS["allow_changelog"] != true && $PSS["allow_changelog"] != false)
	$PSS["allow_changelog"] = true;
if (!isset($PSS["allow_documentation"]) || $PSS["allow_documentation"] != true && $PSS["allow_documentation"] != false)
	$PSS["allow_documentation"] = true;

if (!isset($PSS["debug_enable"]) || $PSS["debug_enable"] != true && $PSS["debug_enable"] != false) $PSS["debug_enable"] = false;

?>
