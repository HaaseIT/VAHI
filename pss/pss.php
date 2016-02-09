<?php

// -----------------------------------------------------------------------------
//                                                                            --
// Pryde Site Suite                                                           --
// pss.php                                                                    --
// This is the scripts configuration-file                                     --
// Edit it to your needs                                                      --
//                                                                            --
//                                                                            --
//                                                                            --
// copyright: Marcus Haase (mail@marcus.haase.name)                           --
// The use of this Script is only allowed with the author's authorisation     --
//                                                                            --
// -----------------------------------------------------------------------------

error_reporting(E_ALL);

// -----------------------------------------------------------------------------
// --                              Config                                     --
// -----------------------------------------------------------------------------

// Path to codebase (with / at the end!)
$PSS["path_codebase"] = '/var/www/pss_codebase/'; // path

// the following key is only needed if run in embeded mode
$PSS["run_dir"] = '/content/'; // path to script-directory

// Shall the script generate thumbs
$PSS["thumbs_enable"] = true; // bool

// Script file and directory configuration
$PSS["file_conf"] = '.pss.conf'; // filename
$PSS["dir_thumbs"] = '.thumbs'; // dirname
$PSS["dir_resize"] = '.resize'; // dirname

// JPEG Quality of thumbs/resizes
$PSS["image_quality"] = 75; // int

// On linux the script-created files will belong to the webserver and only it
// will have write-access. Values: true (chmod 777 on generated files) or false
// (no actions will be taken)
$PSS["linux_chmod_generated"] = false; // bool

// Hide the copyright footer (only fur purchased versions)
$PSS["hide_footer"] = false; // bool

// The title for the generated pages, hostname if left empty
$PSS["page_title"] = ''; // string

// Administration options
$PSS["admin_enable"] = true; // bool
$PSS["admin_comment_position"] = 'right'; // bottom / right
$PSS["admin_comment_width"] = 150; // numerical - only needed when position = right
$PSS["admin_comment_textarea_width"] = 300; // int
$PSS["admin_comment_textarea_height"] = 100; // int
$PSS["admin_comment_linebreaks"] = 'text'; // html / text
$PSS["admin_comment_languages"] = array('de', 'en');

// Search options
$PSS["search_enable"] = true; // bool
$PSS["search_byuser"] = true; // bool
$PSS["search_byuser_string"] = 'Search by user';
$PSS["search_byuser_selectwidth"] = 150; // int
$PSS["search_byuser_position"] = 'right'; // left / right
$PSS["search_string_all"] = 'All';

// should the textcat autom. be selected by HTTP_ACCEPT_LANGUAGE
$PSS["textcat_autodetect"] = false; // bool

// prefix to add to textcat filename
$PSS["textcat_prefix"] = ''; // string

// user defined directories for custom textcats
$PSS["textcat_use_userpath"] = false; // bool
$PSS["textcat_path"] = ''; // full path with trailing slash

// fallback to standart-textcat-files if autodetect and custom lang file not
// present
$PSS["textcat_fallback"] = true; // bool

// Wich language-file to use (currently supported: en, de) if autodetect is set
// to false - this MUST be in lowercase on on case sensitive filesystems (*NIX)
$PSS["textcat_file"] = 'en'; // en / de

// DB Parameters only need to be filled if search is activated
$PSS["db_type"] = 'mysqli'; // mysqli / mssql
$PSS["db_server"] = 'localhost'; // db-hostname
$PSS["db_user"] = 'root'; // db-username
$PSS["db_password"] = ''; // db-password
$PSS["db_name"] = 'pss'; // db-name
$PSS["db_table_files"] = 'files'; // db-table
$PSS["db_table_matches"] = 'matches'; // db-table
$PSS["db_table_keywords"] = 'keywords'; // db-table
$PSS["db_table_keywords_lang"] = 'keywords_lang'; // db-table
$PSS["db_table_categories"] = 'categories'; // db-table
$PSS["db_table_categories_lang"] = 'categories_lang'; // db-table
$PSS["db_table_comments"] = 'comments'; // db-table
$PSS["db_table_users"] = 'users'; // db-table

// if show_parentlink is set to false, should this option be inherited to
// child-directories?
$PSS["inherit_parentlink"] = false; // bool

// Shall the script respond to ?changelog / ?documentation by displaying the
// changelog / documentation?
$PSS["allow_changelog"] = true; // bool
$PSS["allow_documentation"] = true; // bool

// If this is set to false, the error_reporting will be set to 0
$PSS["debug_enable"] = true; // bool

// -----------------------------------------------------------------------------
// --                           End of Config                                 --
// -----------------------------------------------------------------------------

// Please dont remove or change the following line, the script wont work if
include($PSS["path_codebase"].'base.inc');
