<?php
// $Id: prerequisites.inc,v 1.4 2007/05/22 12:26:35 mhaase Exp $
// -----------------------------------------------------------------------------
//                                                                            --
// Pryde Site Suite                                                           --
// prerequisites.inc                                                          --
//                                                                            --
// copyright: Marcus Haase (mail@marcus.haase.name)                           --
// The use of this Script is only allowed with the author's authorisation     --
// Any modification of the sources is strictly forbidden                      --
//                                                                            --
// -----------------------------------------------------------------------------

// config file redundancy and plausibility check
if (!include_once($PSS["path_includes"].'fallback_config.inc'))
	die('<br>PSS startup error:<br>The file: <em>'.$PSS["path_includes"].'fallback_config.inc</em> could not be loaded.');

// textcat path
if ($PSS["textcat_use_userpath"]) {

	$PSS["path_textcats"] = $PSS["textcat_path"];

} else {

	$PSS["path_textcats"] = $PSS["path_codebase"].'textcats/';

}

// embeded stuff
if (isset($_SERVER["HTTP_USER_AGENT"]) && $_SERVER["HTTP_USER_AGENT"] == 'pss_embed') {

	$PSS["run_mode"] = 'embeded';

} else {

	$PSS["run_mode"] = 'standalone';

}

// add trailing slashes
$PSS["dir_thumbs"] = $PSS["dir_thumbs"].'/';
$PSS["dir_resize"] = $PSS["dir_resize"].'/';

if (!include_once($PSS["path_includes"].'functions.misc.inc'))
	die('<br>PSS startup error:<br>The file: <em>'.$PSS["path_includes"].'functions.misc.inc</em> could not be loaded.');

if (!include_once($PSS["path_includes"].'configreader.inc'))
	die('<br>PSS startup error:<br>The file: <em>'.$PSS["path_includes"].'configreader.inc</em> could not be loaded.');

if (!include_once($PSS["path_includes"].'functions.template.inc'))
	die('<br>PSS startup error:<br>The file: <em>'.$PSS["path_includes"].'functions.template.inc</em> could not be loaded.');

if (!include_once($PSS["path_includes"].'functions.showimage.inc'))
	die('<br>PSS startup error:<br>The file: <em>'.$PSS["path_includes"].'functions.showimage.inc</em> could not be loaded.');

if (!include_once($PSS["path_includes"].'functions.image.inc'))
	die('<br>PSS startup error:<br>The file: <em>'.$PSS["path_includes"].'functions.image.inc</em> could not be loaded.');

if (!include_once($PSS["path_baselib"].'class.form.inc'))
	die('<br>PSS startup error:<br>The file: <em>'.$PSS["path_baselib"].'class.form.inc</em> could not be loaded.');

if (!include_once($PSS["path_includes"].'functions.form.inc'))
	die('<br>PSS startup error:<br>The file: <em>'.$PSS["path_includes"].'functions.form.inc</em> could not be loaded.');

// get language / textcat - function in functions.misc.inc
include_once(getLanguage());

if (!include_once($PSS["path_includes"].'functions.javascript.inc'))
	die('<br>PSS startup error:<br>The file: <em>'.$PSS["path_includes"].'functions.javascript.inc</em> could not be loaded.');

// if admin_enable is false, search cannot be active
if ($PSS["admin_enable"]) {

	if (!include_once($PSS["path_includes"].'functions.user.inc'))
		die('<br>PSS startup error:<br>The file: <em>'.$PSS["path_includes"].'functions.user.inc</em> could not be loaded.');

	if (!include_once($PSS["path_includes"].'session.inc'))
		die('<br>PSS startup error:<br>The file: <em>'.$PSS["path_includes"].'session.inc</em> could not be loaded.');

	if (!include_once($PSS["path_baselib"].'class.'.$PSS["db_type"].'.inc'))
		die('<br>PSS startup error:<br>The file: <em>'.$PSS["path_baselib"].'class.'.$PSS["db_type"].'.inc</em> could not be loaded.');

	if (!include_once($PSS["path_includes"].'functions.db.inc'))
		die('<br>PSS startup error:<br>The file: <em>'.$PSS["path_includes"].'functions.db.inc</em> could not be loaded.');

	$DB = new DB();
	$DB->selectDB($PSS["db_name"]);

	if ($PSS["search_enable"]) {

		if (!include_once($PSS["path_includes"].'functions.search.inc'))
			die('<br>PSS startup error:<br>The file: <em>'.$PSS["path_includes"].'functions.search.inc</em> could not be loaded.');

	}

} else {

	$PSS["search_enable"] = false;

}





?>