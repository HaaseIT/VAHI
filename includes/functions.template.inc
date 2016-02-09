<?php
// $Id: functions.template.inc,v 1.12 2007/09/03 10:16:22 mhaase Exp $
// -----------------------------------------------------------------------------
//                                                                            --
// Pryde Site Suite                                                           --
// functions.template.inc                                                     --
//                                                                            --
// copyright: Marcus Haase (mail@marcus.haase.name)                           --
// The use of this Script is only allowed with the author's authorisation     --
// Any modification of the sources is strictly forbidden                      --
//                                                                            --
// -----------------------------------------------------------------------------

function PSS_head() {
	global $PSS, $T, $C, $bScriptopen;

	$sH = '';

	if ($PSS["run_mode"] == 'standalone') {

		$sH .= '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">'."\n";
		$sH .= '<html xmlns="http://www.w3.org/1999/xhtml">'."\n";
		$sH .= "<head>\n";
		$sH .= "  <title>".$PSS["page_title"]." - ";

		// $PSS["view"][0] = view-path, [1] = image
		if (isset($_GET["view"]) && isset($PSS["view"][0]) && isset($PSS["view"][1]) && is_file($_SERVER["DOCUMENT_ROOT"].$PSS["view"][0].$PSS["view"][1])) $sH .= $PSS["view"][1];
		else $sH .= urldecode($_SERVER["REQUEST_URI"]);

		$sH .= "</title>\n";
	}

	// CSS
	$aURLData = pathinfo($_SERVER["SCRIPT_NAME"]);
	$sH .= "\n<style type=\"text/css\">\n";
	if ($PSS["run_mode"] == 'standalone') $sH .= '@import url("'.$aURLData["dirname"].'/pss-body.css");'."\n";
	$sH .= '@import url("'.$aURLData["dirname"].'/pss.css");'."\n";
	$sH .= "</style>\n";

	// Highslide includes
	if ($C["imgview"]["viewer"] == 'highslide') {
		$sH .= '<script type="text/javascript" src="/pss/highslide/highslide-full.js"></script>'."\n";
		$sH .= '<script type="text/javascript" src="/pss/highslide/highslide.config.js" charset="utf-8"></script>'."\n";
		$sH .= '<link rel="stylesheet" type="text/css" href="/pss/highslide/highslide.css" />'."\n";
		$sH .= '<!--[if lt IE 7]>'."\n";
		$sH .= '<link rel="stylesheet" type="text/css" href="/pss/highslide/highslide-ie6.css" />'."\n";
		$sH .= '<![endif]-->'."\n";
		$sH .= '<!-- 7296c4dbc4be3e892469548ac348672f -->'."\n";
	}

	$bScriptopen = false;

	if (!$PSS["show_msg"]) {
		if ($C["imgview"]["viewer"] == 'popup') {
			if (!(isset($_GET["view"]) && isset($PSS["view"][0]) && isset($PSS["view"][1]) && is_file($_SERVER["DOCUMENT_ROOT"].$PSS["view"][0].$PSS["view"][1]))) {
				if ($PSS["images_exist"] || isset($_SESSION["aSearchresults"])) {
					$sH .= openScript();
					$sH .= showOpenpopup();

					if ($PSS["images_exist"] || isset($_SESSION["aSearchresults"])) {
						$iPopupheight = $C["popup"]["height"];
						$iPopupwidth = $C["popup"]["width"];
						if (isset($_SESSION["user"])) {
							$iPopupheight += 40;
							if ($_SESSION["user"]["usr_class"] <= 1 && !isset($_SESSION["aSearchresults"])) $iPopupwidth += 330;
						}
						$sH .= 'function PSS_openPopup(fileName) {'."\n";

						if ($PSS["run_mode"] == 'standalone') $sH .= '  openPopup(\'./?view=\' + fileName, \'PSS_Popup\', 10, 10, '.$iPopupwidth.', '.$iPopupheight.', true, false, false, false, false);'."\n";
						elseif ($PSS["run_mode"] == 'embeded') $sH .= '  openPopup(\''.$PSS["run_dir"].'?view=\' + fileName, \'PSS_Popup\', 10, 10, '.$iPopupwidth.', '.$iPopupheight.', true, false, false, false, false);'."\n";

						$sH .= '}'."\n\n";
					}
				}
			} else {
				if (isset($_SESSION["aSearchresults"]) && isset($_SESSION["user"]) && $_SESSION["user"]["usr_class"] <= 1) {
					$sH .= openScript();
					$sH .= 'function PSS_relocate(filePath, fileName) {'."\n";
					$sH .= '  window.opener.location.href = filePath + "?'.session_name().'='.session_id().'";'."\n";
					$sH .= '  window.resizeBy(330, 0);'."\n";
			//		$sH .= '  window.moveTo(10, 10);'."\n";
					$sH .= '  window.location.href = filePath + "?view=" + filePath + "|" +fileName + "&'.session_name().'='.session_id().'";'."\n";
					$sH .= '}'."\n\n";
				}
			}
		}
		if (isset($_SESSION["user"]) && $_SESSION["user"]["usr_class"] <= 1 && !isset($_REQUEST["a"]) && $_SESSION["user"]["usr_pref_showdiradmin"] == 1) {
			global $iFirstimage, $iLastimage;
			if (isset($PSS["images"]) && count($PSS["images"]) != 0) {
				// echo $iFirstimage.'-'.$iLastimage;
				$sH .= openScript();

				$sH .= 'function PSS_setCheckboxes(newVal) {'."\n";
				$sH .= '  for (var i = '.$iFirstimage.'; i <= '.$iLastimage.'; i++) {'."\n";
				$sH .= '    eval("document.PSS_admin.aFiles_" + i + ".checked = newVal;");'."\n";
				$sH .= '  }'."\n";
				$sH .= '}'."\n\n";

				$sH .= 'function PSS_checkForfiles() {'."\n";
				$sH .= '  bFileschecked = false;'."\n";
				$sH .= '  for (var i = '.$iFirstimage.'; i <= '.$iLastimage.'; i++) {'."\n";
				$sH .= '    eval("if (document.PSS_admin.aFiles_" + i + ".checked == true) { bFileschecked = true; }");'."\n";
				$sH .= '  }'."\n";
				$sH .= '  if (bFileschecked == false) { alert("'.$T["js_msg_nofiles"].'"); }'."\n";
				$sH .= '  return bFileschecked;'."\n";
				$sH .= '}'."\n\n";
			} // endif
		} // endif

		$bCategories = false;

		if (!isset($_GET["view"]) && $PSS["search_enable"]&& $C["global"]["show_search"]) {
			if ($aCategoriestree = prepareCategoriestree()) {
				$bCategories = true;
				$sH .= openScript();
				$sH .= 'var isPreNN6 = (navigator.appName == "Netscape" && parseInt(navigator.appVersion) <= 4);'."\n\n";
				$sH .= 'function list(value, name) {'."\n";
				$sH .= '  this.name = name;'."\n";
				$sH .= '  this.value = value;'."\n";
				$sH .= '}'."\n\n";

				$sH .= 'function populateSelect(bBodytag) {'."\n\n";
				$sH .= '  trigger = document.form_search.'.(($PSS["run_mode"] == 'embeded') ? 'pss_k': 'key').'0;'."\n";
				$sH .= '  target = document.form_search.'.(($PSS["run_mode"] == 'embeded') ? 'pss_k': 'key').'1;'."\n\n";
				$sH .= '  target.options.length = 0;'."\n\n";
				$sH .= '  triggerSelected = trigger.options[trigger.selectedIndex].value;'."\n\n";
				$sH .= '  eval("childrenLength = children_" + triggerSelected + ".length;");'."\n\n";
				$sH .= '  for (var i=0;i<childrenLength;i++) {'."\n";
				$sH .= '    eval("target.options[i] = new Option(children_" + triggerSelected + "[i].name, children_" + triggerSelected + "[i].value)");';
				$sH .= '  }'."\n\n";

				if (isset($_REQUEST["aSearchresults"]) || isset($_SESSION["aSearchresults"])) {
					$sH .= '  if (bBodytag) {'."\n\n";
					$sH .= '    '."\n";
					$sH .= '    target.selectedIndex = '.getSelectedbytree($aCategoriestree).';'."\n";
					$sH .= '    '."\n";
					$sH .= '  }'."\n\n";
				}

				$sH .= '  if (isPreNN6) {'."\n";
				$sH .= '    history.go(0);'."\n";
				$sH .= '  }'."\n\n";
				$sH .= '}'."\n\n";

				$sH .= prepareJSCategoriesarray($aCategoriestree);
				//echo debug(prepareCategoriestree());
			}
		}
	}
	if ($bScriptopen) {
		$sH .= '//-->'."\n";
		$sH .= '</script>'."\n";
	}
	if ($PSS["run_mode"] == 'standalone') { // dont show in embedded
		$sH .= '</head>'."\n";
		$sH .= '<body>'."\n";
	}
	return $sH;
}

function PSS_foot($bShort = false) {
	global $PSS, $C;

	$sH = '';
	if (!$bShort && $PSS["run_mode"] == 'standalone') {
		$sH .= $C["global"]["hr"];
		$sH .= '<div class="pss_main">&nbsp;Generated by <em>Visual Apache Host Indexer v. '.$PSS["ver_long"].'</em><br />';
		$sH .= '&nbsp;&copy; by <a href="http://www.haase-it.com/" class="pss_main">Haase IT</a>';
//		if ($PSS["allow_documentation"]) $sH .= ' - <a href="?documentation" target="_blank" class="pss_main">Documentation</a>';
//		if ($PSS["allow_changelog"]) $sH .= ' - <a href="?changelog" target="_blank" class="pss_main">ChangeLog</a>';
		$sH .= '</div><br />';
	} elseif (!isset($_GET["view"]) && $PSS["run_mode"] != 'standalone') $sH .= $C["global"]["hr"];
	if ($PSS["run_mode"] == 'standalone' || isset($_GET["view"])) $sH .= '</body></html>';

	return $sH;
}

function PSS_showNavigation($aDirs, $bFilesexist) {
	global $T, $C, $PSS;

	if ($C["global"]["nav_sort"] == 'desc') {
		sort($aDirs);
		if ($aDirs[0] == '..') $TMP = array_shift($aDirs);
		rsort($aDirs);
		if (isset($TMP)) {
			array_unshift($aDirs, $TMP);
			unset($TMP);
		}
	} else sort($aDirs);

	$sH = '';
	$sPath = $_SERVER["DOCUMENT_ROOT"].$PSS["request"]["path"];

	if ($T["nav_head"] != '') $sH .= '<div class="pss_fsnav_headline">'.$T["nav_head"].'</div>';

	$sH .= '<ul class="pss_fsnav">';

	if (isset($_SESSION["aSearchresults"])) $sH .= '<li class="pss_fsnav_up">'.href($PSS["PSS_DIR"]).$T["nav_back"].'</a></li>';
	else {
		foreach ($aDirs as $sDir) {
			if ($sDir == '..' && !$C["directory"]["show_parent_link"]) continue;
			elseif ($sDir == '..' && $PSS["request"]["path"] != '/') {
				$sH .= '<li class="pss_fsnav_up">';
				if ($PSS["run_mode"] == 'standalone') $sH .= href('../');
				elseif ($PSS["run_mode"] == 'embeded') {
					$sTemp = substr($PSS["request"]["path"], 0, strlen($PSS["request"]["path"]) -1);
					$iTemp = strrpos($sTemp, '/');
					$sTemp = substr($sTemp, 0, $iTemp);
					$sTemp = str_replace($PSS["run_dir"], '', $sTemp);
					if ($sTemp != '' && $sTemp != substr($PSS["run_dir"], 0, strlen($PSS["run_dir"]) -1)) $sH .= href($sTemp.'/');
					else $sH .= href();
					unset($sTemp, $iTemp);
				}
				$sH .= $T["nav_parent"].'</a></li>';
			} elseif ($sDir == '..' && $PSS["request"]["path"] == '/') continue;
			else {
				$sH .= '<li class="pss_fsnav_dir">';
				if ($PSS["run_mode"] == 'embeded' && $PSS["request"]["path"] == $PSS["run_dir"] || $PSS["run_mode"] == 'standalone') $sH .= href($sDir.'/');
				else $sH .= href(str_replace(substr($PSS["run_dir"], 0, strlen($PSS["run_dir"])), '', $PSS["request"]["path"]).$sDir.'/');
				$sH .= $sDir.'</a><br />';
			}
		}
		if (count($aDirs) == 1 && ($_SERVER["REQUEST_URI"] == '/' || !$C["directory"]["show_parent_link"])) $sH .= $T["nav_empty"];
	}
	$sH .= '</ul>';

	return $sH;
}

function PSS_showThumbs( $bShowhr = true ) {
	global $PSS, $iResizes, $iFirstimage, $iLastimage, $T, $C;

	$sH = '';
	$bThumbs = false;
	$bNewrow = true;

	if ( isset( $_SESSION["user"] ) ) {
		if ( $_SESSION["user"]["usr_pref_showallimages"] == 1 ) {
			$bLimitrows = false;
		} else {
			$bLimitrows = true;
		}
	} else {
		if ( $C["table"]["limitrows"] ) {
			$bLimitrows = true;
		} else {
			$bLimitrows = false;
		}
	}

	if ( isset( $_SESSION["aSearchresults"] ) ) {
		$aRawqueue = $_SESSION["aSearchresults"];
	}
	else {
		$aRawqueue = $PSS["images"];
		if ( isset( $_SESSION["user"] ) && $_SESSION["user"]["usr_class"] <= 1 ) { // multiple file operations form if admin
			global $DB;

			$oForm = new Form();
			$oForm->bUsestyle = true;
			$oForm->sFormaction = $_SERVER["REQUEST_URI"];
			$sH .= $oForm->openForm( 'PSS_admin' );

			if ( isset( $_REQUEST["page"] ) ) {
				$sH .= $oForm->makeHidden( 'page', $_REQUEST["page"] );
			}
		} // endif
	}

	//debug($aRawqueue);

	// if limitrows enabled
	if ( $bLimitrows ) {
		$iRawimages = count( $aRawqueue );

		// determine number of pages
		$iPages = ceil( $iRawimages / ( $C["table"]["maxrows"] * $C["table"]["maxcols"] ) );

		// echo $iRawimages;
		// echo $iPages;

		// determine current page and check for valid values
		if ( isset( $_REQUEST["page"] ) ) {
			$iPage = $_REQUEST["page"] * 1;
			if ( $iPage == 0 ) {
				$iPage = 1;
			}
			if ( $iPage > $iPages ) {
				$iPage = $iPages;
			}
		} else $iPage = 1;
		// echo $iPage;

		// determine the first and the last image to show
		if ( isset( $iPage ) && $iPage != 1 ) {
			$iFirstimage = ( $C["table"]["maxrows"] * $C["table"]["maxcols"] ) * ( $iPage - 1 );
			$iLastimage = ( $C["table"]["maxrows"] * $C["table"]["maxcols"] ) * $iPage - 1;
		} else {
			$iFirstimage = 0;
			$iLastimage = ( $C["table"]["maxrows"] * $C["table"]["maxcols"] - 1 );
		} // endif

		if ( $iLastimage > ( $iRawimages - 1 ) ) {
			$iLastimage = $iRawimages -1;
		}

		//debug('Firstimage: '.$iFirstimage.' Lastimage: '.$iLastimage.' Lastimage Rawqueue: '.($iRawimages - 1));

		// crop ilastimage if less than the maximum number of images are present
		if ( $iLastimage > $iRawimages - 1 ) {
			$iLastimage = $iRawimages - 1;
		}

		// copy images to show into final array
		foreach ( $aRawqueue as $iKey => $aValue ) {
			if ( $iKey >= $iFirstimage && $iKey <= $iLastimage ) {
				$aQueue[] = $aValue;
			} elseif ( $C["imgview"]["viewer"] == 'highslide' ) { // if viewer is highslide, collect all images for invisible adding to gallery-queue
				if ( $iKey < $iFirstimage ) {
					$aPreQueue[] = $aValue;
				} elseif ( $iKey > $iFirstimage ) {
					$aPostQueue[] = $aValue;
				}
			}
		}

		if ( $C["imgview"]["viewer"] == 'highslide' ) { // build hidden queue for highslide gallery
			if ( isset( $aPreQueue ) && isset( $aPostQueue ) ) {
				$aHiddenQueue = array_merge( $aPostQueue, $aPreQueue );
			} elseif ( isset( $aPreQueue ) ) {
				$aHiddenQueue = $aPreQueue;
			} elseif ( isset( $aPostQueue ) ) {
				$aHiddenQueue = $aPostQueue;
			}
		}
			//if (isset($aHiddenQueue)) debug($aHiddenQueue, false, 'HiddenQueue');

		//if (isset($aPreQueue)) debug($aPreQueue, false, 'PreQueue');
		//if (isset($aPostQueue)) debug($aPostQueue, false, 'PostQueue');

		/* old way
		for ($i = $iFirstimage; $i <= $iLastimage; $i++) {

			// echo $i;

			// if the image-number is present, move to final array
			if (isset($aRawqueue[$i])) $aQueue[] = $aRawqueue[$i];
			else break; // if not stop processing, no further images will come
			// endif

		} // endfor
		*/

	} else { // if limitrows disabled set values to full listing
		$aQueue = $aRawqueue;
		$iFirstimage = 0;
		$iLastimage = count( $aQueue ) - 1;
		$iPages = 1;
	} // endif limitrows enabled

	// count shown images for later display
	$iImages = count( $aQueue );

	// if more than one page is present show page navigation
	if ( $iPages > 1 ) {
		// SHOW PAGESNAV
		$sPagesnavtag = PSS_showPagesnav( $iPages, $iPage );

		if ( $C["table"]["position_pagesnav"] == 'top' || $C["table"]["position_pagesnav"] == 'both' ) {
			$sH .= $sPagesnavtag;
			$sH .= $C["global"]["hr"];
		}
	} elseif ( $PSS["html_whereami"] != '' ) {
		$sH .= '<div class="pss_whereami">'.$PSS["html_whereami"].'</div>';
		$sH .= $C["global"]["hr"];
	}

	// file admin operations form
	if ( !isset( $_SESSION["aSearchresults"] ) && isset( $_SESSION["user"] ) && $_SESSION["user"]["usr_class"] <= 1 && $_SESSION["user"]["usr_pref_showdiradmin"] == 1 ) {
		$aActions = array(
			'null|',
			'link|'.$T["thumbs_admin_select_link"],
//		  'comment|'.$T["thumbs_admin_select_comment"], // disabled for now
		);

		$sQ = "SELECT usr_id, usr_name FROM $PSS[db_table_users] ORDER BY usr_name";
		$hResult = $DB->query( $sQ );

		//if ($DB->numRows($hResult) > 1) $aActions[] = 'chown|'.$T["thumbs_admin_select_chown"];

		$aUsers[] = '|';

		while ( $aRow = $DB->fetchArray( $hResult ) ) {
			$aUsers[] = $aRow["usr_id"].'|'.$aRow["usr_name"];
		}

		$sUsertag = $T["thumbs_admin_usersselect_head"].'<br />'.$oForm->makeSelect( 'iUser', $aUsers, '', 300 );
		$sCommenttag = $T["thumbs_admin_comment_head"].'<br />';
		$sCommenttag .= $oForm->makeSelect( 'sCommentlang', prepareLangselect(), $PSS["admin_comment_languages"][0], $PSS["admin_comment_textarea_width"] );
		$sCommenttag .= '<br />'.$oForm->makeTextarea( 'sComment', '', $PSS["admin_comment_textarea_width"], $PSS["admin_comment_textarea_height"] );

		if ( $PSS["search_enable"] ) {
			unset($aKeywords);
			$bKeywords_exist = false;

			$sQ = "SELECT key_id FROM $PSS[db_table_keywords]";
			$hResult = $DB->query($sQ);

			if ( $DB->numRows( $hResult ) >= 1 ) {
				$bKeywords_exist = true;
//				$aActions[] = 'addkey|'.$T["thumbs_admin_select_addkey"]; // disabled for now
//				$aActions[] = 'delkey|'.$T["thumbs_admin_select_delkey"]; // disabled for now

				while ( $aRow = $DB->fetchArray( $hResult ) ) {
					$aKeywords[] = $aRow["key_id"].'|'.getKeywordString($aRow["key_id"]);
				}
				$sKeywordtag = $T["thumbs_admin_keywordselect_head"].'<br />'.$oForm->makeSelect('iKeyword', $aKeywords, '', 300);
			}
		}

//		$aActions[] = 'unlink|'.$T["thumbs_admin_select_unlink"]; // disabled for now
		$sAdmintag = '<div class="pss_main">';
		$sAdmintag .= '<a href="#" onClick="PSS_setCheckboxes(true); return false;">'.$T["thumbs_admin_selectall"].'</a> / ';
		$sAdmintag .= '<a href="#" onClick="PSS_setCheckboxes(false); return false;">'.$T["thumbs_admin_unselectall"].'</a>';
		$sAdmintag .= '<br /><br />';
		$sAdmintag .= "\n".'<script language="JavaScript" type="text/JavaScript">'."\n";
		$sAdmintag .= '<!--'."\n\n";
		$sAdmintag .= 'function changeAdmintd() {'."\n";
		$sAdmintag .= '  adminform = document.PSS_admin.a;'."\n";
		$sAdmintag .= '  selected = adminform.options[adminform.selectedIndex].value;'."\n";
		if ( $PSS["search_enable"] && $bKeywords_exist ) {
			$sAdmintag .= '  if (selected == "addkey" || selected == "delkey") {'."\n";
			$sAdmintag .= '    document.getElementById("td_adminform").innerHTML = \'<br />'.$sKeywordtag.'\';'."\n";
			$sAdmintag .= '  } else ';
		} else {
			$sAdmintag .= '  ';
		}
		$sAdmintag .= 'if (selected == "comment") {'."\n";
		$sAdmintag .= '    document.getElementById("td_adminform").innerHTML = \'<br />'.$sCommenttag.'\';'."\n";
		unset( $sCommenttag );
		$sAdmintag .= '  } else if (selected == "chown") {'."\n";
		$sAdmintag .= '    document.getElementById("td_adminform").innerHTML = \'<br />'.$sUsertag.'\';'."\n";
		$sAdmintag .= '  } else {'."\n";
		$sAdmintag .= '    document.getElementById("td_adminform").innerHTML = "";'."\n";
		$sAdmintag .= '  }'."\n";
		$sAdmintag .= '}'."\n";
		$sAdmintag .= '//-->'."\n";
		$sAdmintag .= '</script>'."\n";
		$sAdmintag .= '<table border="0" cellspacing="0" cellpadding="0"><tr>';
		$sAdmintag .= '<td class="pss_main" width="300">'.$T["thumbs_admin_head"].'<br />'.$oForm->makeSelect( 'a', $aActions, '', 300, 1 , false, 'onChange="changeAdmintd();"' ).'</td>';
		$sAdmintag .= '<td class="pss_main">&nbsp;<br />'.$oForm->makeSubmit( '', $T["thumbs_admin_submittext"], 100, '', 'onClick="return PSS_checkForfiles();"' ).'</td>';
		// Admin TD
		$sAdmintag .= '</tr><tr><td colspan="2" id="td_adminform" class="pss_main"><div></div></td>';
		$sAdmintag .= '</tr></table>';
		$sAdmintag .= '</div>';

		if ( $_SESSION["user"]["usr_pref_adminposition"] == 0 ) {
			$sH .= $sAdmintag;
			$sH .= $C["global"]["hr"];
		}
	}

	// is either the help or the number of files visible? if not, no need to open tablerow.
	if ( $C["thumbs"]["show_help"] || $C["thumbs"]["show_number"] ) {
		$sH .= '<div class="pss_main">';
		
		// is the help visible?
		if ( $C["thumbs"]["show_help"] ) {
			$sH .= $T["thumbs_help_head_1"];
			
			// are the filenames shown and linked?
			if ( $C["thumbs"]["link_name"] && $C["thumbs"]["show_name"] ) {
				$sH .= ' '.$T["thumbs_help_head_2"];
			}
		}

		// Are both shown? then output the linebreak
		if ( $C["thumbs"]["show_help"] && $C["thumbs"]["show_number"] ) {
			$sH .= '<br /><br />';
		}

		// is the number of files visible?
		if ( $C["thumbs"]["show_number"] ) {

			// if only one page is available
			if ( $iPages == 1 ) {
				$sH .= $T["thumbs_help_load_1"].' '.$iImages.' '.$T["thumbs_help_load_2"];
			} else {
				$sH .= $T["thumbs_help_load_3"].' '.($iFirstimage + 1).' ';
				$sH .= $T["thumbs_help_load_4"].' '.($iLastimage + 1).' ';
				$sH .= $T["thumbs_help_load_5"].' '.$iRawimages.$T["thumbs_help_load_6"];
			} // endif
		}
		$sH .= '</div>';
	} // endif showhelp / nr files
	$sH .= '<table id="pss_imagetable">';

	// Thumbs handling
	if ( $PSS["thumbs_enable"] ) {
		foreach ( $aQueue as $aThis ) {

			// Checks if thumbs-dir exists, if not, it is created
			if ( !is_dir( urldecode( $_SERVER["DOCUMENT_ROOT"].$aThis["path"].$PSS["dir_thumbs"] ) ) ) {
				mkdir( urldecode( $_SERVER["DOCUMENT_ROOT"].$aThis["path"].$PSS["dir_thumbs"] ) );
				if ( $PSS["linux_chmod_generated"] && ( !isset($_ENV["OS"] ) || strtolower( substr( $_ENV["OS"], 0, 3 ) ) != 'win' ) ) {
					chmod( urldecode( $_SERVER["DOCUMENT_ROOT"].$aThis["path"].$PSS["dir_thumbs"] ), 0777 );
				}
			} // endif
		} // endforeach
		$bThumbs = true;
	}

	$i = $iFirstimage;
	foreach( $aQueue as $aThis ) {
		$aThis["fspath"] = $_SERVER["DOCUMENT_ROOT"].$aThis["path"];
		$sThisFile = $aThis["fspath"].$aThis["name"];
		$sThisFileThumb = $aThis["fspath"].$PSS["dir_thumbs"].$aThis["name"];

		if ( $bNewrow ) {
			$sH .= '<tr>';
			$bNewrow = false;
			$iCol = 1;
		}

		$aImagedata = calculateImagesize( $aThis["fspath"].$aThis["name"] );
		$sH .= '<td class="pss_imagecell">';
		$sImagetag = '';

		if ( $C["imgview"]["viewer"] == 'popup' ) {
			$sImagetag .= '<a href="javascript: PSS_openPopup( \''.uEncode( $aThis["path"] ).'|'.uEncode( $aThis["name"] ).'\' );" class="pss_main">';
		} elseif ( $C["imgview"]["viewer"] == 'highslide' ) {
			$sImagetag .= '<a href="'.uEncode( $aThis["path"] ).uEncode( $aThis["name"] ).'" class="highslide" onclick="return hs.expand( this, config1 )" title="'.$aThis["name"].'">';
		} else {
			$aTemp["view"] = uEncode( $aThis["path"] ).'|'.uEncode( $aThis["name"] );
			if ( isset( $_REQUEST["page"] ) ) {
				$aTemp["page"] = $_REQUEST["page"];
			}
			$sImagetag .= href( $PSS["PSS_DIR"], $aTemp, 'pss_main' );
			unset( $aTemp );
		}

		// Check if the thumbnail exists, if not generate.
		// Also, this checks if the thumb has the same filetime as the original, if not -> regenerate
		// Next it checks the thumbnail-size, if it doesnt fit the config values -> regenerate
		if ( $bThumbs && $aImagedata["resize"] ) {
			if ( !is_file( $sThisFileThumb ) || filemtime( $sThisFile ) != filemtime ($sThisFileThumb ) ) {
				PSS_ResizeImage( $sThisFile, $sThisFileThumb, $aImagedata["twidth"], $aImagedata["theight"] );
				if ( is_file( $sThisFileThumb ) ) {
					touch( $sThisFileThumb, filemtime( $sThisFile ) );
				}
			}

			$aThumbdata = GetImageSize( $sThisFileThumb );

			if ( $aThumbdata[0] != $C["thumbs"]["maxwidth"] && ( $aThumbdata[0] + 1 ) != $C["thumbs"]["maxwidth"] && $aThumbdata[1] != $C["thumbs"]["maxheight"] && ( $aThumbdata[1] + 1 ) != $C["thumbs"]["maxheight"] ) {
				PSS_ResizeImage( $sThisFile, $sThisFileThumb, $aImagedata["twidth"], $aImagedata["theight"] );
				if ( is_file( $sThisFileThumb ) ) {
					touch( $sThisFileThumb, filemtime( $sThisFile ) );
				}
			}

			$sImagetag .= '<img src="'.$aThis["path"].$PSS["dir_thumbs"].$aThis["name"].'" width="'.$aImagedata["twidth"].'" height="'.$aImagedata["theight"].'" ';
		} else {
			$sImagetag .= '<img src="'.$aThis["path"].$aThis["name"].'" width="'.$aImagedata["twidth"].'" height="'.$aImagedata["theight"].'" ';
		}

		$sImagetag .= ' alt="'.$aThis["name"].'">';
		$sImagetag .= '</a>';

		$sH .= $sImagetag;

		unset($sImagetag);

		// Wenn eingeloggt zeigen ob image linked und checkbox
		if ( isset( $_SESSION["user"] ) && $_SESSION["user"]["usr_class"] <= 1 && !isset( $_SESSION["aSearchresults"] ) ) {
			$sH .= '<br />';
			if ( $_SESSION["user"]["usr_pref_showdiradmin"] == 1 ) {
				$sH .= PSS_makeCheckboxtable( $oForm->makeCheckbox( 'aFiles['.$i.']|aFiles_'.$i.'', uEncode( $aThis["path"] ).'|'.uEncode( $aThis["name"] ) ), '<span class="pss_fileinfo">'.$T["thumbs_admin_checkboxtext"].'</span>' );
			}
			$i++;

			$sQ = "SELECT fil_id, fil_user, usr_name FROM $PSS[db_table_files] ";
			$sQ .= " INNER JOIN $PSS[db_table_users] ON $PSS[db_table_users].usr_id = $PSS[db_table_files].fil_user ";
			$sQ .= "WHERE fil_path = '$aThis[path]' AND ";
			$sQ .= "fil_name = '$aThis[name]'";

			$hResult = $DB->query( $sQ );

			if ( $DB->numRows( $hResult ) == 0 ) {
				$sH .= '<div style="color:#ff0000; font-weight:bold;" class="pss_fileinfo">'.$T["thumbs_admin_notlinked"].'</div>';
			} else {
				$aRow = $DB->fetchArray($hResult);
				$sH .= '<div style="color:green; font-weight:bold;" class="pss_fileinfo">'.$T["thumbs_admin_linked"].'</div>';
				$sH .= '<div class="pss_fileinfo">'.$T["thumbs_admin_owner"].' '.$aRow["usr_name"].'</div>';

				// wenn search_enable keywords zeigen
				if ( $PSS["search_enable"] ) {
					$sKeywords = getFormatedKeywordsbyFile( $aRow["fil_id"] );
					if ( $sKeywords != '' ) {
						$sH .= '<div class="pss_fileinfo">'.$T["thumbs_admin_keywords"].' <em>'.$sKeywords.'</em></div>';
					}
				}
			}
		}

		// is the filename visible?
		if ( $C["thumbs"]["show_name"] || isset($_SESSION["user"] ) && $_SESSION["user"]["usr_class"] <= 1) {
			//$sH .= '<br />';

			$sFilename = $aThis["name"];

			if ( $C["thumbs"]["crop_extension"] ) {
				$sFilename = cropFileextension( $sFilename );
			}

			$sH .= '<div class="pss_filename">';
			// is the filename linked?
			if ( $C["thumbs"]["link_name"] || isset( $_SESSION["user"] ) && $_SESSION["user"]["usr_class"] <= 1 ) {
				$sH .= '<a href="'.$aThis["path"].$aThis["name"].'" target="_blank">'.$sFilename.'</a>';
			} else {
				$sH .= $sFilename;
			}
			$sH .= '</div>';
		}

		if ( $C["thumbs"]["show_date"] ) { // is the filedate visible?
			$sH .= '<div class="pss_fileinfo_headline">'.$T["thumbs_info_date"].'</div>';
			$sH .= '<div class="pss_fileinfo">'.date( "d.m.Y, H:i", filemtime( $sThisFile ) ).'</div>';
		}
		if ( $C["thumbs"]["show_dimensions"] ) { // are the file-dimensions visible?
			$sH .= '<div class="pss_fileinfo_headline">'.$T["thumbs_info_dimensions"].'</div>';
			$sH .= '<div class="pss_fileinfo">'.$aImagedata["width"].' x '.$aImagedata["height"].' px</div>';
		}
		if ( $C["thumbs"]["show_size"] ) { // is the filesize visible?
			$sH .= '<div class="pss_fileinfo_headline">'.$T["thumbs_info_size"].'</div>';
			$sH .= '<div class="pss_fileinfo">'.number_format( filesize( $sThisFile ), 0, ',', '.' ).' Bytes</div>';
		}
		$sH .= '</td>';

		if ( $iCol == $C["table"]["maxcols"] ) {
			$sH .= '</tr>';
			$bNewrow = true;
		}
		$iCol++;
	}

	if ( !$bNewrow ) $sH .= '</tr>';

	// Bottom admin-menu display
	if ( !isset($_SESSION["aSearchresults"] ) && isset( $_SESSION["user"] ) &&
			$_SESSION["user"]["usr_class"] <= 1 && $_SESSION["user"]["usr_pref_adminposition"] == 1 && $_SESSION["user"]["usr_pref_showdiradmin"] == 1 ) {
		$sH .= $C["global"]["hr"];
		$sH .= $sAdmintag;
	}
	if ( !isset($_SESSION["aSearchresults"] ) && isset( $_SESSION["user"] ) && $_SESSION["user"]["usr_class"] <= 1 ) {
		$oForm->closeForm();
	}
	$sH .= '</table>';

	if ( $C["imgview"]["viewer"] == 'highslide' && isset( $aHiddenQueue ) ) {
		$sH .= "\n\n";
		$sH .= '<div class="hidden-container">';
		foreach ( $aHiddenQueue as $aThis ) {
			$sH .= '<a href="'.uEncode( $aThis["path"] ).uEncode( $aThis["name"] ).'" class="highslide" onclick="return hs.expand( this, { slideshowGroup: 1 } )" title="'.$aThis["name"].'"></a>';
		}
		$sH .= '</div>';
	}
	if ( $iPages > 1 && ( $C["table"]["position_pagesnav"] == 'bottom' || $C["table"]["position_pagesnav"] == 'both' ) ) {
		$sH .= $C["global"]["hr"];
		$sH .= $sPagesnavtag;
	}
	if ( isset( $iResizes ) && ( $C["thumbs"]["show_generated"] || isset( $_SESSION["user"] ) && $_SESSION["user"]["usr_class"] <= 1 ) ) {
		$sH .= $C["global"]["hr"];
		$sH .= '<div class="pss_main">'.$iResizes.' '.$T["thumbs_info_generated"].'</div>';
	}
	return $sH;
}

function PSS_showFiles($aFiles) {
	global $T, $C, $PSS;

	$aRequest = parse_url($_SERVER["REQUEST_URI"]);
	$sPath = $_SERVER["DOCUMENT_ROOT"].$aRequest["path"];
	$sH = '';

	usort($aFiles, create_function('$a,$b', 'return strcasecmp($a,$b);'));

	if ($T["file_head"] != '') $sH .= '<div class="pss_fsnav_headline">'.$T["file_head"].'</div>';

	$sH .= '<ul class="pss_fsnav">';

	foreach($aFiles as $sFile) {

		$sFilelc = strtolower($sFile);

		if (substr($sFilelc, -4) == '.mpeg' || substr($sFilelc, -4) == '.mpg' ||
				substr($sFilelc, -4) == '.avi' || substr($sFilelc, -4) == '.m2v' ||
				substr($sFilelc, -4) == '.mov') {

			$sFiletype = 'movie';

		} elseif (substr($sFilelc, -4) == '.exe' || substr($sFilelc, -4) == '.com') $sFiletype = 'executable';
		elseif (substr($sFilelc, -4) == '.zip' || substr($sFilelc, -4) == '.rar' || substr($sFilelc, -4) == '.ace' || substr($sFilelc, -3) == '.gz') $sFiletype = 'compressed';
		elseif (substr($sFilelc, -4) == '.htm' || substr($sFilelc, -5) == '.html' ||
			substr($sFilelc, -6) == '.shtml' || substr($sFilelc, -4) == '.php' ||
			substr($sFilelc, -5) == '.php3' || substr($sFilelc, -5) == '.php4' ||
			substr($sFilelc, -6) == '.phtml' || substr($sFilelc, -4) == '.cfm' ||
			substr($sFilelc, -4) == '.asp') {

			$sFiletype = 'webdoc';

		} elseif (substr($sFilelc, -4) == '.doc' || substr($sFilelc, -4) == '.txt') $sFiletype = 'doc';
		elseif (substr($sFilelc, -4) == '.pdf') $sFiletype = 'pdf';
		else $sFiletype = 'unknown';

		$sH .= '<li class="pss_fsnav_'.$sFiletype.'">';

		if ($PSS["run_mode"] == 'embeded') $sH .= '<a href="content/'.$sFile.'" target="_blank">'; // file embed
		else $sH .= '<a href="'.$sFile.'" target="_blank">';

		$sH .= $sFile.'</a> ';
		if ($C["files"]["show_size"] == true) {

			$sFilesize = filesize(urldecode($sPath.$sFile));

			if ($C["files"]["size_format"] == 'KB') {
				$sFilesize = $sFilesize / 1024;
				$sFilesizestring = $T["file_size_kbytes"];
			} elseif ($C["files"]["size_format"] == 'MB') {
				$sFilesize = $sFilesize / 1024 / 1024;
				$sFilesizestring = $T["file_size_mbytes"];
			} else $sFilesizestring = $T["file_size_bytes"];
			$sH .= ' - '.number_format($sFilesize, (($C["files"]["size_format"] != 'B') ? 2 : 0), ',', '.').' '.$sFilesizestring.' ';

		}
		if ($C["files"]["show_date"] == true) $sH .= ' - '.date("H:i:s - d.m.Y", filemtime(urldecode($sPath.$sFile)));
		$sH .= '</li>';
	}

	$sH .= '</ul>';

	return $sH;
}

function PSS_showReadme() {
	global $C;

	$aRequest = parse_url($_SERVER["REQUEST_URI"]);
	$sPath = $_SERVER["DOCUMENT_ROOT"].urldecode($aRequest["path"]);
	$sH = '';

	if (file_exists($sPath.'/'.$C["global"]["readme_name"])) {

		$sH .= '<div class="pss_readme">';
		$aFile = file($sPath.'/'.$C["global"]["readme_name"]);

		foreach($aFile as $sFile) $sH .= $sFile;

		$sH .= '</div>';

	}

	return $sH;

}

function PSS_showWhereami() {
	global $C;

	$aRequest = parse_url($_SERVER["REQUEST_URI"]);
	$sPath = $_SERVER["DOCUMENT_ROOT"].urldecode($aRequest["path"]);
	$sH = '';

	if (file_exists($sPath.'/'.$C["global"]["whereami_name"])) $sH = file_get_contents($sPath.'/'.$C["global"]["whereami_name"]);

	return $sH;

}

function debug($mixed, $bQuiet = false, $sTitle = '') {
		if (!$bQuiet) global $sDebug;

		if (!isset($sDebug)) $sDebug = '';

		$sDebug .= '<pre class="pss_debug">';
		if ($sTitle != '') $sDebug .= $sTitle."\n";
		ob_start();
		print_r($mixed);
		$sDebug .= ob_get_contents();
		ob_end_clean();
		$sDebug .= '</pre>';

		return $sDebug;

}

function PSS_quit($sMsg) {
	$sH = PSS_head();
	$sH .= '<br /><div class="pss_head">&nbsp;'.$sMsg.'</div>';
	$sH .= PSS_foot();

	die($sH);
}

function PSS_makeCheckboxtable($sString1, $sString2, $sStyle = 'pss_main') {
	$sH = "<table border='0' cellspacing='0' cellpadding='0' valign='top'>";
	$sH .= "<tr>";
	$sH .= "<td class='$sStyle'>$sString1</td>";
	$sH .= "<td class='$sStyle'>&nbsp;</td>";
	$sH .= "<td class='$sStyle'>$sString2</td>";
	$sH .= "</tr>";
	$sH .= "</table>";

	return $sH;
}

function PSS_showPagesnav($iPages, $iPage, $aGetvars = array()) {
	global $C, $T, $PSS;

		$sH = '<div class="pss_main">'.$T["thumbs_pagesnav_head"].'</div>';

		if ($PSS["html_whereami"] != '') $sH .= '<div class="pss_whereami">'.$PSS["html_whereami"].'</div>';

		$sH .= '<ul class="pss_pagesnav">';

		// < link (one page back)
		if ($iPage == 1) $aTemp["page"] = $iPages;
		else $aTemp["page"] = $iPage - 1;

		// if in search mode paste this onto link to keep searchresults
		if (isset($_SESSION["aSearchresults"])) $aTemp["a"] = 'search';

		$sH .= '<li class="pss_th_na_le">';
		$sH .= href($PSS["PSS_DIR"], $aTemp);
		$sH .= $T["thumbs_pagesnav_left"].'</a>';
		$sH .= '</li>';

		unset($aTemp);

		// page-number links
		for ($i = 1; $i <= $iPages; $i++) {

			$aTemp["page"] = $i;

			// if in search mode paste this onto link to keep searchresults
			if (isset($_SESSION["aSearchresults"])) $aTemp["a"] = 'search';

			$sH .= '<li class="pss_th_na_num">';
			$sH .= href($PSS["PSS_DIR"], $aTemp);

			unset($aTemp);

			if ($i == $iPage) $sH .= '<span style="Text-Decoration: overline underline; font-weight: bold;">'.$i.'</span></a> ';
			else $sH .= $i.'</a> ';
			$sH .= '</li>';

		} // endfor


		// link: >
		if ($iPage == $iPages) $aTemp["page"] = 1;
		else $aTemp["page"] = $iPage + 1;

		// if in search mode paste this onto link to keep searchresults
		if (isset($_SESSION["aSearchresults"])) $aTemp["a"] = 'search';

		$sH .= '<li class="pss_th_na_re">';
		$sH .= href($PSS["PSS_DIR"], $aTemp);
		$sH .= $T["thumbs_pagesnav_right"].'</a>';
		$sH .= '</li>';

		unset($aTemp);

		$aTemp["page"] = $iPages;

		// if in search mode paste this onto link to keep searchresults
		if (isset($_SESSION["aSearchresults"])) $aTemp["a"] = 'search';


		$sH .= '</ul>';

		$sH .= '<div style="clear:both;"></div>';

		return $sH;

}

?>