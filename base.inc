<?php
// $Id: base.inc,v 1.17 2007/09/03 10:16:21 mhaase Exp $
// -----------------------------------------------------------------------------
//                                                                            --
// Pryde Site Suite                                                           --
// base.inc                                                                   --
//                                                                            --
// copyright: Marcus Haase (mail@marcus.haase.name)                           --
// The use of this Script is only allowed with the author's authorisation     --
// Any modification of the sources is strictly forbidden                      --
//                                                                            --
// -----------------------------------------------------------------------------

// Version Information
$PSS["ver_short"] = '2.3.d.13';
$PSS["ver_long"] = $PSS["ver_short"].' - 02.07.2012';
/*
Version legend
2 (major) . 2 (minor) . d/b/c/0 (increment)
if increment == d or b or c another increment is made -> . 1 (Development or Beta version)
So:
2.2.d.1 means: Development version 1 of 2.2
2.2.b.1 means: Beta version 1 of 2.2
2.2.c.1 means: RC 1 of 2.2
2.2 means: Release of 2.2
2.2.1 means: Release 2.2 increment 1
i means interim
*/

// set error_reporting to configured set
if (!$PSS["debug_enable"]) {
	error_reporting(0);
	ini_set('display_errors', 0);
} else {
	error_reporting(E_ALL);
	ini_set('display_errors', 1);
}

ini_set('arg_separator.output','&amp;');

// script-run time measurement
$TMP = explode(" ",microtime());
$PSS["perf_stime"] = $TMP[1].substr($TMP[0],1);
unset($TMP);

// compatibility for old config var
if (!isset($PSS) && isset($PSS_)) {
	$PSS = $PSS_;
	unset($PSS_);
} // end compatibility

// build needed path-values
$PSS["path_baselib"] = $PSS["path_codebase"].'baselib/';
$PSS["path_includes"] = $PSS["path_codebase"].'includes/';
$PSS["path_misc"] = $PSS["path_codebase"].'misc/';

// Startup values
$PSS["images_exist"] = false;
$PSS["PSS_DIR"] = '';
$PSS["show_msg"] = false;
$PSS["show_cp"] = false;
$PSS["show_ucp"] = false;
$PSS["show_search"] = false;
$PSS["show_image"] = false;
$PSS["l"] = '';
$sTag = '';

if (is_file($PSS["path_codebase"].'globals.conf.php')) include_once($PSS["path_codebase"].'globals.conf.php');

// includes-loader
if (!include_once($PSS["path_includes"].'prerequisites.inc'))
	die('<br>PSS startup error:<br>The file: <em>'.$PSS["path_includes"].'prerequisites.inc</em> could not be loaded.');

$PSS["request"] = parse_url($_SERVER["REQUEST_URI"]);
$PSS["request"]["path"] = urldecode($PSS["request"]["path"]);
$PSS["path"] = urldecode($_SERVER["DOCUMENT_ROOT"].$PSS["request"]["path"]);

$PSS["resize"] = $C["imgview"]["limitsize"];

if (isset($_SESSION["user"]) && $C["imgview"]["viewer"] == 'highslide') $C["imgview"]["viewer"] = 'popup';

if ($PSS["run_mode"] == 'embeded') {
	$TMP = str_replace($PSS["run_dir"], '', $PSS["request"]["path"]);;
	if ($TMP != '' && $TMP != substr($PSS["run_dir"], 0, strlen($PSS["run_dir"]) -1)) $PSS["PSS_DIR"] = $TMP;
	unset($TMP);
} else $PSS["PSS_DIR"] = $PSS["request"]["path"];
// get position of pagesnav - fallback for .pss.conf
if ($C["table"]["position_pagesnav"] != 'top' && $C["table"]["position_pagesnav"] != 'bottom' &&
		$C["table"]["position_pagesnav"] != 'both') $C["table"]["position_pagesnav"] = 'both';

// If popup then force resize
if ($C["imgview"]["viewer"] == 'popup') $PSS["resize"] = true;

// check for valid request if not die
verifyRequest($PSS["request"]);

if (checkModule() && isset($_REQUEST["reload"]) && $PSS["admin_enable"] && isset($_SESSION["user"])) {
	$hResult = doUserquery('refresh');
	$_SESSION["user"] = $DB->fetchArray($hResult);
	unset($hResult);
}

// admin overrides
if (isset($_SESSION["user"]) && $_SESSION["user"]["usr_pref_showhidden"] == 1) $C["global"]["showhidden"] = true;
elseif (isset($_SESSION["user"]) && $_SESSION["user"]["usr_pref_showhidden"] == 0) $C["global"]["showhidden"] = false;

if (isset($_SESSION["user"]) && $_SESSION["user"]["usr_pref_shownav"] == 1) $C["global"]["show_navigation"] = true;
elseif (isset($_SESSION["user"]) && $_SESSION["user"]["usr_pref_shownav"] == 0) $C["global"]["show_navigation"] = false;

if (isset($_SESSION["user"]) && $_SESSION["user"]["usr_pref_showfiles"] == 1) $C["global"]["show_files"] = true;
elseif (isset($_SESSION["user"]) && $_SESSION["user"]["usr_pref_showfiles"] == 0) $C["global"]["show_files"] = false;

if (isset($_SESSION["user"]) && $_SESSION["user"]["usr_pref_showdate"] == 1) $C["thumbs"]["show_date"] = true;
elseif (isset($_SESSION["user"]) && $_SESSION["user"]["usr_pref_showdate"] == 0) $C["thumbs"]["show_date"] = false;

if (isset($_SESSION["user"]) && $_SESSION["user"]["usr_pref_showdimensions"] == 1) $C["thumbs"]["show_dimensions"] = true;
elseif (isset($_SESSION["user"]) && $_SESSION["user"]["usr_pref_showdimensions"] == 0) $C["thumbs"]["show_dimensions"] = false;

if (isset($_SESSION["user"]) && $_SESSION["user"]["usr_pref_showfilesize"] == 1) $C["thumbs"]["show_size"] = true;
elseif (isset($_SESSION["user"]) && $_SESSION["user"]["usr_pref_showfilesize"] == 0) $C["thumbs"]["show_size"] = false;

if (isset($_SESSION["user"]) && $_SESSION["user"]["usr_pref_override_rowscols"] == 1) {
	$C["table"]["maxrows"] = $_SESSION["user"]["usr_pref_thumbsrows"];
	$C["table"]["maxcols"] = $_SESSION["user"]["usr_pref_thumbscols"];
}

//echo debug($PSS);

// -----------------------------------------------------------------------------
// --                       Work begins here                                  --
// -----------------------------------------------------------------------------

// If indexing is not set to true die and display an error-message
if (!$C["global"]["showindex"]) PSS_quit('Indexing disabled');

// docu / changelog
if ($PSS["allow_changelog"] && isset($_GET["changelog"])) {
	$sTag .= "<pre>\n\n".file_get_contents($PSS["path_misc"].'changelog.txt').'</pre>';
	$PSS["show_msg"] = true;
} elseif ($PSS["allow_documentation"] && isset($_GET["documentation"])) {
	$sTag .= '<table border="0" cellspacing="0" cellpadding="0"><tr><td class="pss_dir">';
	$sTag .= file_get_contents($PSS["path_misc"].'documentation.html').'</td></tr></table>';
	$PSS["show_msg"] = true;
}

// login handling
if (checkModule()) {
	if (isset($_REQUEST["login"]) && $PSS["admin_enable"]) { // Begin Login / Logout
		$sTag .= handleLogin();
		$PSS["show_msg"] = true;
	} elseif (isset($_REQUEST["logout"])) {
		$sTag .= handleLogout();
		$PSS["show_msg"] = true;
		// End Login / Logout
	}
}

// admin-file operations here (link/unlink/keywords/comment/owner)
if ($PSS["admin_enable"]) {
	$sTag .= doFileoperations(); // link / unlink / add keywords and so on - functions.users.inc
	if (isset($_SESSION["user"]) && $_SESSION["user"]["usr_class"] <= 1 && isset($_REQUEST["cp"])) {
		$PSS["show_cp"] = true;
		$sTag = handleCP(); // control panel - functions.users.inc
	} elseif (isset($_SESSION["user"]) && $_SESSION["user"]["usr_class"] <= 1 && isset($_REQUEST["ucp"])) {
		$PSS["show_ucp"] = true;
		$sTag = handleUCP(); // control panel - functions.users.inc
	}
}

// image display
if (checkModule()) {
	if (isset($_GET["view"])) {
		$PSS["view"] = explode('|', $_GET["view"]);
		$PSS["view"][0] = uDecode($PSS["view"][0]);
		$PSS["view"][1] = uDecode($PSS["view"][1]);
		if (isset($PSS["view"][0]) && isset($PSS["view"][1]) && is_file($_SERVER["DOCUMENT_ROOT"].$PSS["view"][0].$PSS["view"][1])) {
			$sTag .= PSS_showImage();
			$PSS["show_image"] = true;
		}
	}
}

if (checkModule()) {
	/*                                                                          */
	/*                       Begin Search-handling                              */
	/*                                                                          */
	if ($PSS["search_enable"]) {
		if (isset($_REQUEST["a"]) && $_REQUEST["a"] == 'search') {
			if (isset($_REQUEST["key0"]) || isset($_REQUEST["key1"])) {
				unset($_SESSION["aKeyword"]);
				if (isset($_REQUEST["key0"])) $_SESSION["aKeyword"][0] = $_REQUEST["key0"];
				if (isset($_REQUEST["key1"])) $_SESSION["aKeyword"][1] = $_REQUEST["key1"];
				if (isset($_REQUEST["key2"])) $_SESSION["aKeyword"][2] = $_REQUEST["key2"];
				if (isset($_REQUEST["key3"])) $_SESSION["aKeyword"][3] = $_REQUEST["key3"];
			}
			$PSS["searchresults"] = prepareSearchresults(doSearchquery());
		} else unset($_SESSION["aSearchresults"], $_SESSION["aKeyword"]);
		// endif a == search
	} // endif search_enable
	/*                                                                          */
	/*                        End Search-handling                               */
	/*                                                                          */
}

if (checkModule()) {
	$PSS["handle_dir"] = opendir($PSS["path"]) OR PSS_quit('Access denied.');
	// Sortieren der dateien nach: bilder, verzeichnisse, dateien
	$PSS["files_exist"] = false;
	//echo debug($_SESSION["user"]);
	if ($C["global"]["show_thumbs"] || $PSS["show_navigation"] || $PSS["show_files"]) {
		while($TMP["direntry"] = readdir($PSS["handle_dir"])) {
			if (@($TMP["direntry"][0] == '.' && $TMP["direntry"][1] != '.') && !$C["global"]["showhidden"] || $TMP["direntry"] == '.') continue;
			elseif (@is_dir($PSS["path"].$TMP["direntry"])) {
				$PSS["dirs"][] = $TMP["direntry"];
				if ($TMP["direntry"] != '..') $PSS["files_exist"] = true;
			} else {
				if ($C["global"]["show_thumbs"]) {
					$TMP["file"] = @GetImageSize($PSS["path"].$TMP["direntry"]);
					if ($TMP["file"][2] == 1 || $TMP["file"][2] == 2 || $TMP["file"][2] == 3) {
						$PSS["images"][] = array(
							"path" => $PSS["request"]["path"],
							"name" => $TMP["direntry"],
						);
						$PSS["images_exist"] = true;
					} elseif ($C["global"]["show_files"]) {
						if ($TMP["direntry"] != '..') $PSS["files"][] = $TMP["direntry"];
					} // endif is this a gif/jpeg/png?
					$PSS["files_exist"] = true;
				} elseif ($PSS["show_files"]) {
					if ($TMP["direntry"] != '..') $PSS["files"][] = $TMP["direntry"];
				}
			} // endif $TMP["direntry"][0] == '.' && $TMP["direntry"][1] != '.'
		} // endwhile
		if (isset($PSS["images"]) && is_array($PSS["images"])) sort($PSS["images"]);
		unset($TMP["direntry"]);
		closedir($PSS["handle_dir"]);
	}
	// Vorbereiten der Ausgabe
	// Navi anzeigen
	if($C["global"]["show_navigation"]) $PSS["html_navigation"] = PSS_showNavigation($PSS["dirs"], $PSS["files_exist"]);
	else $PSS["html_navigation"] = '';

	// Readme anzeigen?
	if($C["global"]["show_readme"] && !isset($_SESSION["aSearchresults"])) $PSS["html_readme"] = PSS_showReadme();
	else $PSS["html_readme"] = '';
	// Whereami anzeigen?
	if($C["global"]["show_whereami"] && !isset($_SESSION["aSearchresults"])) $PSS["html_whereami"] = PSS_showWhereami();
	else $PSS["html_whereami"] = '';
	// Gibt es suchresultate / Thumbs anzeigen?
	if($C["global"]["show_thumbs"] && isset($PSS["images"]) || isset($_SESSION["aSearchresults"])) {
		$PSS["html_thumbs"] = PSS_showThumbs();
	} else {
		$PSS["html_thumbs"] = '';
	}
	// files anzeigen?
	if ($C["global"]["show_files"] && isset($PSS["files"]) && !isset($_SESSION["aSearchresults"])) {
		$PSS["html_files"] = PSS_showFiles($PSS["files"]);
	} else {
		$PSS["html_files"] = '';
	}
	// search aktiv?
	if($PSS["search_enable"] && $C["global"]["show_search"]) $PSS["html_search"] = showSearchform();
	// sortierung
	$PSS["items"][1] = $C["global"]["item_1"];
	$PSS["items"][2] = $C["global"]["item_2"];
	$PSS["items"][3] = $C["global"]["item_3"];
	$PSS["items"][4] = $C["global"]["item_4"];
}

if ($sTag != '') {
	$PSS["html"] = $sTag;
} else {
	$TMP["first"] = true;
	$TMP["content"] = '';
	foreach($PSS["items"] as $sThisitem) {
		if($PSS["html_".$sThisitem] != '') {
			if($TMP["first"]) {
				$TMP["content"] .= $PSS["html_".$sThisitem];
				$TMP["first"] = false;
			} else {
				$TMP["content"] .= '<hr size="1" noshade>';
				$TMP["content"] .= $PSS["html_".$sThisitem];
			}
		}
	}
	@$PSS["html"] .= $PSS["html_search"];
	@$PSS["html"] .= $TMP["content"];
	unset($TMP, $sThisitem);
}

if ($PSS["admin_enable"]) $PSS["html_user"] = generateUsermenu();
else $PSS["html_user"] = '';

$TMP = explode(" ",microtime());
$PSS["perf_etime"] = $TMP[1].substr($TMP[0],1);

echo PSS_head().((isset($sDebug)) ? $sDebug : '').$PSS["html_user"].$PSS["html"].PSS_foot($PSS["hide_footer"])."\n<!-- ".$PSS["ver_short"].'.';

if (extension_loaded('bcmath')) echo bcsub($PSS["perf_etime"],$PSS["perf_stime"],6);

echo ' !-->';

?>