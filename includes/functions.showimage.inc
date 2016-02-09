<?php
// $Id: functions.showimage.inc,v 1.7 2007/09/03 10:16:22 mhaase Exp $
// -----------------------------------------------------------------------------
//                                                                            --
// Pryde Site Suite                                                           --
// functions.showimage.inc                                                    --
//                                                                            --
// copyright: Marcus Haase (mail@marcus.haase.name)                           --
// The use of this Script is only allowed with the author's authorisation     --
// Any modification of the sources is strictly forbidden                      --
//                                                                            --
// -----------------------------------------------------------------------------

function PSS_showOsizeLink($bResized, $aImagedata) {
	global $PSS, $T, $C;

	$sH = '';

	if ($bResized) {

		$aTemp["view"] = $_REQUEST["view"];
		$aTemp["osize"] = '1';

		if (isset($_REQUEST["page"])) $aTemp["page"] = $_REQUEST["page"];

		$sH .= href($PSS["PSS_DIR"], $aTemp);

		unset($aTemp);

		$sH .= $T["image_nav_osize"].'</a><br />';

	} else {

		if ($aImagedata[0] > $C["imgview"]["maxwidth"] || $aImagedata[1] > $C["imgview"]["maxheight"]) {

			$aTemp["view"] = $_REQUEST["view"];
			if (isset($_REQUEST["page"])) $aTemp["page"] = $_REQUEST["page"];

			$sH .= href($PSS["PSS_DIR"], $aTemp);

			unset($aTemp);

			$sH .= $T["image_nav_resized"].'</a><br />';

		}

	}

	return $sH;

}

function PSS_showImageAdminOptions($sFileactiontag, $bFilelinked, $aThisimage, $sNavi, $aFile) {
	global $T, $DB, $PSS;

	$sH = '';

	$sH .= '</td><td class="pss_dir" valign="top" style="padding-left: 5px;">';

	$sH .= '<strong>'.$T["image_admin_head"].'</strong><br /><br />';

	$sH .= $sFileactiontag;

	if (!$bFilelinked) {

		$sH .= $T["image_admin_notlinked_1"];
		$sH .= '<a href="'.$aThisimage["path"].'?view='.$_GET["view"].'&a=link&aFiles[0]='.uEncode($aThisimage["path"]).'|'.uEncode($aThisimage["name"]).'">';
		$sH .= $T["image_admin_notlinked_2"].'</a>'.$T["image_admin_notlinked_3"];
		$sH .= '<br /><br />';

	} else {

		if ($PSS["search_enable"]) {

			$sQ = "SELECT ";
			$sQ .= $PSS["db_table_keywords"].".key_id, ";
			$sQ .= $PSS["db_table_keywords"].".key_category FROM ".$PSS["db_table_matches"]." ";
			$sQ .= "INNER JOIN ".$PSS["db_table_keywords"]." ON ";
      $sQ .= $PSS["db_table_keywords"].".key_id = ".$PSS["db_table_matches"].".mat_kid ";
			$sQ .= "WHERE mat_fid = '$aFile[fil_id]'";

			// echo $sQ;

			$hResult = $DB->query($sQ);
			//echo $DB->error();

			while ($aRow = $DB->fetchArray($hResult)) $aFile["keywords"][] = $aRow;

			if (!isset($aFile["keywords"]) || count($aFile["keywords"]) == 0) {

				$sH .= $T["image_admin_nokeywords"].'<br /><br />';

			} else {

				$sH .= $T["image_admin_keywords_head"].'<br />';

				$sKtag = '';

				foreach ($aFile["keywords"] as $aThis) {

					$sKtag .= getKeywordString($aThis["key_id"]).', ';

				}

				$sH .= '<em>'.cutStringend($sKtag, 2).'</em><br /><br />';

			} // endif keywords exist

			// add keyword
			$sH .= $T["image_admin_addkeyword_head"].'<br />';

			$sQuery = "SELECT * FROM $PSS[db_table_keywords]";

			$hResult = $DB->query($sQuery);

			if ($DB->numRows($hResult)) {

				$oForm = new Form();
				$oForm->bUsestyle = true;
				$oForm->sFormaction = $aThisimage["path"];
				$oForm->sFormmethod = 'GET';

				$sH .= $oForm->openForm();
				$sH .= $oForm->makehidden('view', $_GET["view"]);
				$sH .= $oForm->makeHidden('a', 'addkey');
				$sH .= $oForm->makeHidden('aFiles[0]', uEncode($aThisimage["path"]).'|'.uEncode($aThisimage["name"]));

				while ($aRow = $DB->fetchArray($hResult)) $aKeywords[] = $aRow;

				$aOptions[] = '|';

				foreach ($aKeywords as $aThis) {

					$bDouble = false;

					if (isset($aFile["keywords"])) {

						foreach ($aFile["keywords"] as $aSubthis) {

							if ($aThis["key_id"] == $aSubthis["key_id"]) $bDouble = true;

						}

					}

					if (!$bDouble) $aOptions[] = $aThis["key_id"].'|'.getKeywordString($aThis["key_id"]);

				}

				// echo debug($aOptions);

				$sH .= $oForm->makeSelect('iKeyword', $aOptions, '', 150);
				$sH .= $oForm->makeSubmit('', $T["image_admin_submittext"], 100);

				$sH .= $oForm->closeForm();

				// echo debug($aFile);

				unset($aOptions, $oForm);

				// del keyword
				$sH .= $T["image_admin_delkeyword_head"].'<br />';

				$oForm = new Form();
				$oForm->bUsestyle = true;
				$oForm->sFormaction = $aThisimage["path"].'?view='.$_GET["view"];
				$oForm->sFormmethod = 'GET';

				$sH .= $oForm->openForm();
				$sH .= $oForm->makehidden('view', $_GET["view"]);
				$sH .= $oForm->makeHidden('a', 'delkey');
				$sH .= $oForm->makeHidden('aFiles[0]', uEncode($aThisimage["path"]).'|'.uEncode($aThisimage["name"]));

				$aOptions[] = '|';

        //debug($aFile["keywords"]);
				if (isset($aFile["keywords"])) {

					foreach ($aFile["keywords"] as $aThis) {
            //debug($aThis);
            $mKeywordstring = getKeywordString($aThis["key_id"]);
            //debug($mKeywordstring);
            $aOptions[] = $aThis["key_id"].'|'.$mKeywordstring;

          }

				}

        //debug($aOptions);

				$sH .= $oForm->makeSelect('iKeyword', $aOptions, '', 150);
				$sH .= $oForm->makeSubmit('', $T["image_admin_submittext"], 100);

				$sH .= $oForm->closeForm();

			}

		} // endif $PSS["search_enable"]

		// comment admin
		$sH .= $T["image_admin_comment_head"].'<br />';

		$oForm = new Form();
		$oForm->bUsestyle = true;
		$oForm->sFormaction = $aThisimage["path"].'?view='.$_GET["view"];

		$sH .= $oForm->openForm('PSS_admin');
		$sH .= $oForm->makehidden('view', $_GET["view"]);
		$sH .= $oForm->makeHidden('a', 'comment');
		$sH .= $oForm->makeHidden('aFiles[0]', uEncode($aThisimage["path"]).'|'.uEncode($aThisimage["name"]));

		$sH .= "\n".'<script language="JavaScript" type="text/JavaScript">'."\n";
		$sH .= '<!--'."\n\n";
		$sH .= 'function changeCommentlang() {'."\n";
		$sH .= 'adminform = document.PSS_admin.sCommentlang;'."\n";
		$sH .= 'selected = adminform.options[adminform.selectedIndex].value;'."\n";
		$sH .= 'location = "http://'.$_SERVER["HTTP_HOST"].$_SERVER["REQUEST_URI"].'&sCommentlang=" + selected;'."\n";
		$sH .= ''."\n";
		$sH .= ''."\n";
		$sH .= '}'."\n";
		$sH .= '//-->'."\n";
		$sH .= '</script>'."\n";

		if (isset($_REQUEST["sCommentlang"])) {

			$TMP = $_REQUEST["sCommentlang"];

		} else {

			$TMP = $PSS["l"];

		}

		$sH .= $oForm->makeSelect('sCommentlang', prepareLangselect(), $TMP, $PSS["admin_comment_textarea_width"], 1, false, 'onChange="changeCommentlang();"');
		$sH .= '<br />';

		unset($TMP);

		$TMP = '';
		if (isset($aFile["comment"])) $TMP = $aFile["comment"];
		$sH .= $oForm->makeTextarea('sComment', $TMP, $PSS["admin_comment_textarea_width"], $PSS["admin_comment_textarea_height"]);
		unset($TMP);

		$sH .= '<br />';
		$sH .= $oForm->makeSubmit('', $T["image_admin_submittext"], $PSS["admin_comment_textarea_width"]);

		$sH .= $oForm->closeForm();

		// unlink
		$sH .= $T["image_admin_unlink_1"];
		$sH .= '<a href="'.$aThisimage["path"].'?view='.$_GET["view"].'&a=unlink';
		$sH .= '&aFiles[0]='.uEncode($aThisimage["path"]).'|'.uEncode($aThisimage["name"]).'">';
		$sH .= $T["image_admin_unlink_2"].'</a>';
		$sH .= $T["image_admin_unlink_3"];
		$sH .= '<br /><br />';

	}

	$sH .= '<span class="pss_main">'.$sNavi.'</span>';
	$sH .= '</td>';

	return $sH;

}

function PSS_showImage() {
	global $PSS, $DB, $T, $C;

	$bShow_details = ($C["imgview"]["show_name"] || $C["imgview"]["show_dimensions"] || $C["imgview"]["show_type"] ||
										$C["imgview"]["show_size"] || $C["imgview"]["show_date"] || $C["imgview"]["show_link"]);
	$bShow_osize = $C["imgview"]["allow_osize"] && $PSS["resize"];
	$bShow_navblock = ($C["imgview"]["show_navi"] || $bShow_osize);

	$aThisimage["path"] = $PSS["view"][0];
	$aThisimage["name"] = $PSS["view"][1];

	$sPath = $_SERVER["DOCUMENT_ROOT"].$aThisimage["path"];
	$sFiledate = date("d.m.Y H:i:s", filemtime($sPath.$aThisimage["name"]));

	if ($PSS["admin_enable"]) {

		$aFile = getFiledata($aThisimage["path"], $aThisimage["name"]);

		if ((!isset($aFile["comment"]) || $aFile["comment"] == '') && $C["imgview"]["comment_is_filename_if_not_in_db"]) {

			$C["imgview"]["comment_position"] = 'bottom';

		}

	} else $aFile = array();

	if ($PSS["admin_enable"] && !isset($_SESSION["aSearchresults"]) &&
			isset($_SESSION["user"]) && $_SESSION["user"]["usr_class"] <= 1) {

		// Check if file is linked already
		if (is_array($aFile)) $bFilelinked = true;
		else $bFilelinked = false;

		$sFileactiontag = '';

		// link file message
		if (isset($_GET["a"]) && $_GET["a"] == 'link' && $bFilelinked) $sFileactiontag .= $T["actions_link_ft"].'<br />';

		// wenn file gelinkt ggf dateioperationsmeldungen ausgeben
		if ($bFilelinked) {

			if (isset($_REQUEST["a"]) && $_REQUEST["a"] == 'addkey' &&
					isset($_REQUEST["iKeyword"]) && $_REQUEST["iKeyword"] != '' &&
					$PSS["search_enable"]) {

				$sFileactiontag .= '<span style="color:green;">'.$T["actions_keyword_ft"].'</span><br /><br />';

			} elseif (isset($_REQUEST["a"]) && $_REQUEST["a"] == 'delkey' &&
						isset($_REQUEST["iKeyword"]) && $_REQUEST["iKeyword"] != '' &&
						$PSS["search_enable"]) {

				$sFileactiontag .= '<span style="color:#ff0000;">'.$T["actions_keyword_remove_ft"].'</span><br /><br />';

			}

		}

	} // endif admin_enable, !searchresults, userclass <= 1

	// Navi bauen wenn nötig
	if ($C["imgview"]["show_navi"]) {

		if (isset($_SESSION["aSearchresults"])) {

			$aQueue = $_SESSION["aSearchresults"];

		} else {

			$hDir = opendir($sPath) OR PSS_quit($T["error_denied"]);

			while($sFile = readdir($hDir)) {

				if (@($sFile[0] == '.' && $sFile[1] != '.') && !$C["global"]["showhidden"] || $sFile == '.' || @is_dir($sPath.$sFile)) {

					continue;

				} else {

					$aFiletemp = @GetImageSize($sPath.$sFile);

					if ($aFiletemp[2] == 1 || $aFiletemp[2] == 2 || $aFiletemp[2] == 3) {

						$aQueue[] = array(
													"path" => $aThisimage["path"],
													"name" => $sFile,
												);

					} // endif

				} // endif

			} // endwhile

			sort($aQueue);

		} // endif searchresults/no

		$iImages = (count($aQueue) - 1);
		$sNavi = '';

		//echo debug($aQueue);
		foreach($aQueue as $sKey => $aThis) {

			if ($aThis["path"] == $aThisimage["path"] && $aThis["name"] == $aThisimage["name"]) {

				if (isset($_REQUEST["page"])) $aTemp["page"] = $_REQUEST["page"];
				if (isset($_REQUEST["osize"])) $aTemp["osize"] = $_REQUEST["osize"];

				if ($sKey != 0) {

					$aTemp["view"] = uEncode($aQueue[($sKey - 1)]["path"]).'|'.uEncode($aQueue[($sKey - 1)]["name"]);

				} else {

					$aTemp["view"] = uEncode($aQueue[$iImages]["path"]).'|'.uEncode($aQueue[$iImages]["name"]);

				} // endif $sKey != 0

				$sNavi .= '<ul class="pss_pagesnav">';
				$sNavi .= '<li class="pss_img_na_ba">';
				$sNavi .= href($PSS["PSS_DIR"], $aTemp);
				$sNavi .= $T["image_nav_left"].'</a>';
				$sNavi .= '</li>';

				unset($aTemp);


				if ($C["imgview"]["viewer"] == 'popup') {

					$sNavi .= '<li class="pss_img_na_cl">';
					$sNavi .= '<a href="#" onClick="window.close();">'.$T["image_nav_popup_close_1"].'</a>';
					$sNavi .= '</li>';

				} else {

					if (isset($_SESSION["aSearchresults"])) {

						$aTemp["a"] = 'search';
						if (isset($_REQUEST["page"])) $aTemp["page"] = $_REQUEST["page"];

					} else {

						$aTemp = array();
						if (isset($_REQUEST["page"])) $aTemp["page"] = $_REQUEST["page"];

					} // endif isset($_SESSION["aSearchresults"])

					$sNavi .= '<li class="pss_img_na_cl">';
					$sNavi .= href($PSS["PSS_DIR"], $aTemp);
					$sNavi .= $T["image_nav_index"].'</a>';
					$sNavi .= '</li>';

					unset($aTemp);

				} // endif $C["popup"]["enable"]

				if (isset($_REQUEST["page"])) $aTemp["page"] = $_REQUEST["page"];
				if (isset($_REQUEST["osize"])) $aTemp["osize"] = $_REQUEST["osize"];

				if ($sKey < $iImages) {

					$aTemp["view"] = uEncode($aQueue[($sKey + 1)]["path"]).'|'.uEncode($aQueue[($sKey + 1)]["name"]);

				} else {

					$aTemp["view"] = uEncode($aQueue[0]["path"]).'|'.uEncode($aQueue[0]["name"]);

				} // $sKey < $iImages

				$sNavi .= '<li class="pss_img_na_fo">';
				$sNavi .= href($PSS["PSS_DIR"], $aTemp);
				$sNavi .= $T["image_nav_right"].'</a>';
				$sNavi .= '</li>';
				$sNavi .= '</ul>';

				unset($aTemp);

			} // endif $aThis["path"] == $aThisimage["path"] && $aThis["name"] == $aThisimage["name"]

		} // endforeach

	}

	$aImagedata = GetImageSize($sPath.$aThisimage["name"]) OR PSS_quit($T["error_denied"]);

	if ($aImagedata[2] == 1) { $sType = 'Gif'; }
	elseif ($aImagedata[2] == 2) { $sType = 'Jpeg'; }
	elseif ($aImagedata[2] == 3) { $sType = 'Png'; }

	$bResized = false;

	if (!(isset($_REQUEST["osize"]) && $_REQUEST["osize"] == '1')) {

		if ($PSS["resize"] && ($aImagedata[0] > $C["imgview"]["maxwidth"] || $aImagedata[1] > $C["imgview"]["maxheight"])) {

			$aImagedataresized = calculateImagesize($sPath.$aThisimage["name"]);

			if (!is_dir($sPath.$PSS["dir_resize"])) {

				mkdir($sPath.$PSS["dir_resize"]);

				if ($PSS["linux_chmod_generated"] && (!isset($_ENV["OS"]) || strtolower(substr($_ENV["OS"], 0, 3)) != 'win')) {

					chmod($sPath.$PSS["dir_resize"], 0777);

				}

			} // endif !is_dir

			if (!is_file($sPath.$PSS["dir_resize"].$aThisimage["name"])
					|| filemtime($sPath.$aThisimage["name"]) != filemtime($sPath.$PSS["dir_resize"].$aThisimage["name"])) {

				PSS_ResizeImage($sPath.$aThisimage["name"], $sPath.$PSS["dir_resize"].$aThisimage["name"], $aImagedataresized["twidth"], $aImagedataresized["theight"]);

				if (is_file($sPath.$PSS["dir_resize"].$aThisimage["name"]))
					touch($sPath.$PSS["dir_resize"].$aThisimage["name"], filemtime($sPath.$aThisimage["name"]));

			} // endif!is_file

			$aResizeddata = GetImageSize($sPath.$PSS["dir_resize"].$aThisimage["name"]);

			if ($aResizeddata[0] != $C["imgview"]["maxwidth"] && ($aResizeddata[0] + 1) != $C["imgview"]["maxwidth"] && $aResizeddata[1] != $C["imgview"]["maxheight"] && ($aResizeddata[1] + 1) != $C["imgview"]["maxheight"]) {

				PSS_ResizeImage($sPath.$aThisimage["name"], $sPath.$PSS["dir_resize"].$aThisimage["name"], $aImagedataresized["twidth"], $aImagedataresized["theight"]);

				if (is_file($sPath.$PSS["dir_resize"].$aThisimage["name"]))
					touch($sPath.$PSS["dir_resize"].$aThisimage["name"], filemtime($sPath.$aThisimage["name"]));

			}

			$bResized = true;

		}

	}

	// O-Size Links
	if (!$C["imgview"]["viewer"] == 'popup' && ($bShow_osize || (isset($_REQUEST["osize"]) && $_REQUEST["osize"] == '1'))) $sNavi .= PSS_showOsizeLink($bResized, $aImagedata);

	// image-tag vorbereiten und bildgröße verfügbar machen
	if ($bResized) {

		$sImagetag = '<img src="'.$aThisimage["path"].$PSS["dir_resize"].$aThisimage["name"].'" width="'.$aImagedataresized["twidth"].'" height="'.$aImagedataresized["theight"].'" ';

		$aImagesize = array(
			'width' => $aImagedataresized["twidth"],
			'height' => $aImagedataresized["theight"],
		);

	} else {

		$sImagetag = '<img src="'.$aThisimage["path"].$aThisimage["name"].'" '.$aImagedata[3].' ';

		$aImagesize = array(
			'width' => $aImagedata[0],
			'height' => $aImagedata[1],
		);

	}

	$sImagetag .= ' alt="'.$aThisimage["name"].'"><br /><br />';

	$sH = '';

	// autoresize popup
	if ($C["imgview"]["viewer"] == 'popup' && $C["popup"]["auto_resize"]) $sH .= PSS_resize_popup($aImagesize, $aFile);

	$sH .= '<div class="pss_main">';

	if ($bShow_navblock && ($C["imgview"]["position_navi"] == 'both' || $C["imgview"]["position_navi"] == 'top')) $sH .= $sNavi.'<br />';

	if (!isset($_SESSION["aSearchresults"])) {

		if (isset($_SESSION["user"]) && $_SESSION["user"]["usr_class"] <= 1 ||
				$C["imgview"]["comment_position"] == 'right' && isset($aFile["comment"]) && $aFile["comment"] != '')
			$sH .= '<table border="0" cellspacing="0" cellpadding="0"><tr><td class="pss_main" valign="top">';

	} else {

		if ($C["imgview"]["comment_position"] == 'right' && isset($aFile["comment"]) && $aFile["comment"] != '')
			$sH .= '<table border="0" cellspacing="0" cellpadding="0"><tr><td class="pss_main" valign="top">';

	}

	if ($C["imgview"]["viewer"] == 'popup' && $C["imgview"]["click_links_back"]) {

		$sH .= $T["image_nav_clickonimagecloses"].'<a href="#" onClick="window.close();">';

	} elseif ($C["imgview"]["click_links_back"]) {

		if ($C["imgview"]["click_links_back_help"] == 'top' ||
				$C["imgview"]["position_navi"] == 'bottom' ||
				$C["imgview"]["position_navi"] == 'both') $sH .= $T["image_nav_clickonimageback"].'<br />';

		if (isset($_SESSION["aSearchresults"])) {

			$aTemp["a"] = 'search';
			if (isset($_REQUEST["page"])) $aTemp["page"] = $_REQUEST["page"];

			$sH .= href($PSS["PSS_DIR"], $aTemp);

			unset($aTemp);

		} else {

			$aTemp = '';

			if (isset($_REQUEST["page"])) $aTemp ["page"] = $_REQUEST["page"];

			$sH .= href($PSS["PSS_DIR"], $aTemp);

			unset($aTemp);

		} // endif isset($_SESSION["aSearchresults"])

	}

	$sH .= $sImagetag;

	if ($C["imgview"]["click_links_back"]) $sH .= '</a>';

	if ($C["imgview"]["viewer"] != 'popup' && $C["imgview"]["click_links_back"] &&
			$C["imgview"]["click_links_back_help"] == 'bottom' &&
			$C["imgview"]["position_navi"] == 'top')  {

		if ($C["imgview"]["click_links_back_help_linked"]) {

			if (isset($_SESSION["aSearchresults"])) {

				$aTemp["a"] = 'search';
				if (isset($_REQUEST["page"])) $aTemp["page"] = $_REQUEST["page"];

				$sH .= href($PSS["PSS_DIR"], $aTemp);

				unset($aTemp);

			} else {

				$aTemp = '';

				if (isset($_REQUEST["page"])) $aTemp ["page"] = $_REQUEST["page"];

				$sH .= href($PSS["PSS_DIR"], $aTemp);

				unset($aTemp);

			} // endif isset($_SESSION["aSearchresults"])

		}

		$sH .= '[ '.$T["image_nav_clickonimageback"].' ]<br /><br />';

		if ($C["imgview"]["click_links_back_help_linked"]) $sH .= '</a>';

	}

	if (isset($_SESSION["aSearchresults"])) {

		if ($C["imgview"]["comment_position"] == 'right' && isset($aFile["comment"]) && $aFile["comment"] != '') {

			$sH .= '</td><td></td><td width="'.$C["imgview"]["comment_width"].'" valign="top">';

			if ($C["imgview"]["viewer"] == 'popup')
				$sH .= '<span class="pss_main">&nbsp;</span><br />';

			if ($C["imgview"]["crop_extension"]) $sFileName = cropFileextension($aThisimage["name"]);
			else $sFileName = $aThisimage["name"];

			$sH .= '<div class="pss_comment_right">';

			if ($PSS["admin_comment_linebreaks"] == 'text') {

				$sH .= nl2br(str_replace('[keywords]', getFormatedKeywordsbyFile($aFile["fil_id"]), str_replace('[path]', $aFile["fil_path"], str_replace('[name]', $sFileName, $aFile["comment"]))));

			} else {

				$sH .= str_replace('[keywords]', getFormatedKeywordsbyFile($aFile["fil_id"]), str_replace('[path]', $aFile["fil_path"], str_replace('[name]', $sFileName, $aFile["comment"])));

			}

			$sH .= '</td>';
			$sH .= '</tr></table>';

		}

	} else {

		if ($C["imgview"]["comment_position"] == 'right' && isset($aFile["comment"]) && $aFile["comment"] != '') {

			$sH .= '</td><td></td><td width="'.$C["imgview"]["comment_width"].'" valign="top">';

			if ($C["imgview"]["viewer"] == 'popup')
				$sH .= '<span class="pss_main">&nbsp;</span><br />';

			if ($C["imgview"]["crop_extension"]) $sFileName = cropFileextension($aThisimage["name"]);
			else $sFileName = $aThisimage["name"];

			$sH .= '<div class="pss_comment_right">';

			if ($PSS["admin_comment_linebreaks"] == 'text') {

				$sH .= nl2br(str_replace('[keywords]', getFormatedKeywordsbyFile($aFile["fil_id"]), str_replace('[path]', $aFile["fil_path"], str_replace('[name]', $sFileName, $aFile["comment"]))));

			} else {

				$sH .= str_replace('[keywords]', getFormatedKeywordsbyFile($aFile["fil_id"]), str_replace('[path]', $aFile["fil_path"], str_replace('[name]', $sFileName, $aFile["comment"])));

			}

			$sH .= '</div></td>';

		}

		if (isset($_SESSION["user"]) && $_SESSION["user"]["usr_class"] <= 1) {

			$sH .= PSS_showImageAdminOptions($sFileactiontag, $bFilelinked, $aThisimage, $sNavi, $aFile);

		}

		if (isset($_SESSION["user"]) && $_SESSION["user"]["usr_class"] <= 1 ||
				$C["imgview"]["comment_position"] == 'right' && isset($aFile["comment"]) && $aFile["comment"] != '')
			$sH .= '</tr></table>';

	}

	if ((isset($aFile["comment"]) || $C["imgview"]["comment_is_filename_if_not_in_db"]) && $C["imgview"]["comment_position"] == 'bottom') {

		if ($C["imgview"]["crop_extension"]) $sFileName = cropFileextension($aThisimage["name"]);
		else $sFileName = $aThisimage["name"];

		$sComment = '<span class="pss_comment_bottom">';

		if (isset($aFile["comment"]) && $aFile["comment"] != '') $sComment .= str_replace('[keywords]', getFormatedKeywordsbyFile($aFile["fil_id"]), str_replace('[path]', $aFile["fil_path"], str_replace('[name]', $sFileName, $aFile["comment"])));
    else $sComment .= $sFileName;

		$sComment .= '</span>';

		if ($C["imgview"]["viewer"] == 'popup') {

			if (isset($_SESSION["user"]) && isset($_SESSION["aSearchresults"])) $sH .= '<a href="javascript:PSS_relocate(\''.$aFile["fil_path"].'\', \''.$aFile["fil_name"].'\');">['.$T["image_admin_gotoimage"].']</a>'.'&nbsp;&nbsp;&nbsp;';

			$sH .= $sComment.'<br />';

		} else $sH .= $sComment;

	} else {

		if ($bShow_navblock) {

			if ($C["imgview"]["viewer"] == 'popup') {

				if (isset($_SESSION["user"]) && isset($_SESSION["aSearchresults"])) $sH .= '<a href="javascript:PSS_relocate(\''.$aFile["fil_path"].'\', \''.$aFile["fil_name"].'\');">['.$T["image_admin_gotoimage"].']</a><br />';

			} elseif ($C["imgview"]["position_navi"] == 'both' || $C["imgview"]["position_navi"] == 'bottom') $sH .= $sNavi;

		}

	}

	if ($C["imgview"]["viewer"] == 'popup') $PSS["hide_footer"] = true;

	if ($bShow_details) {

		if ($bShow_navblock && $C["imgview"]["viewer"] == 'popup') $sH .= '<br />';

		if ($bResized) {

			if ($C["imgview"]["show_link"]) $sLinkresized = 'http://'.$_SERVER["HTTP_HOST"].$aThisimage["path"].$PSS["dir_resize"].$aThisimage["name"];

			if ($C["imgview"]["show_oimage"]) $sH .= '<table border="0" cellspacing="0" cellpadding="0"><tr><td>';

			$sH .= '<span class="pss_dir"><strong>'.$T["image_info_resized_head"].'</strong><br />';

			if ($C["imgview"]["show_name"]) $sH .= $T["image_info_name"].' '.$aThisimage["name"].'<br />';

			if ($C["imgview"]["show_dimensions"]) {

				$sH .= $T["image_info_width"].' '.$aImagedataresized["twidth"].'px<br />';
				$sH .= $T["image_info_height"].' '.$aImagedataresized["theight"].'px<br />';

			}

			if ($C["imgview"]["show_type"]) $sH .= $T["image_info_type"].' '.$sType.'<br />';
			if ($C["imgview"]["show_size"]) $sH .= $T["image_info_size_1"].' '.number_format(filesize(urldecode($sPath.$PSS["dir_resize"].$aThisimage["name"])), 0, ',', '.').' '.$T["image_info_size_2"].'<br />';
			if ($C["imgview"]["show_date"]) $sH .= $T["image_info_date"].' '.$sFiledate.'<br />';
			if ($C["imgview"]["show_link"]) $sH .= $T["image_info_link"].' '.urldecode($sLinkresized);

			$sH .= '</span>';

			if ($C["imgview"]["show_oimage"]) {

				$sH .= '</td><td></td>';
				$sH .= '<td>';
				$sH .= '<span class="pss_dir"><strong>'.$T["image_info_oimage_head"].'</strong><br />';

			}

		} else {

			$sH .= '<span class="pss_dir"><strong>'.$T["image_info_head"].'</strong><br />';

		}

		if (!$bResized || ($bResized && $C["imgview"]["show_oimage"])) {

			if ($C["imgview"]["show_name"]) $sH .= $T["image_info_name"].' '.$aThisimage["name"].'<br />';

			if ($C["imgview"]["show_dimensions"]) {

				$sH .= $T["image_info_width"].' '.$aImagedata[0].'px<br />';
				$sH .= $T["image_info_height"].' '.$aImagedata[1].'px<br />';

			}

			if ($C["imgview"]["show_type"]) $sH .= $T["image_info_type"].' '.$sType.'<br />';

		}

		if ($bResized) {

			if ($C["imgview"]["show_oimage"]) {

				if ($C["imgview"]["show_size"]) $sH .= $T["image_info_size_1"].' '.number_format(filesize(urldecode($sPath.$aThisimage["name"])), 0, ',', '.').' '.$T["image_info_size_2"].'<br />';
				if ($C["imgview"]["show_date"]) $sH .= $T["image_info_date"].' '.$sFiledate.'<br />';
				if ($C["imgview"]["show_link"]) $sH .= $T["image_info_link"].' '.urldecode('http://'.$_SERVER["HTTP_HOST"].$aThisimage["path"].$aThisimage["name"]);

				$sH .= '</span>';
				$sH .= '</td>';
				$sH .= '</td></tr></table>';

			}

		} else {

			if ($C["imgview"]["show_size"]) $sH .= $T["image_info_size_1"].' '.number_format(filesize(urldecode($sPath.$aThisimage["name"])), 0, ',', '.').' '.$T["image_info_size_2"].'<br />';
			if ($C["imgview"]["show_date"]) $sH .= $T["image_info_date"].' '.$sFiledate.'<br />';
			if ($C["imgview"]["show_link"]) $sH .= $T["image_info_link"].' '.urldecode('http://'.$_SERVER["HTTP_HOST"].$aThisimage["path"].$aThisimage["name"]);
			$sH .= '</span>';

		}

	}

	$sH .= '</div>';

	return $sH;

}

function PSS_resize_popup($aImagesize, $aFile) {
	global $C;

	$sH = '';

	$aWindowsize = array(
		'width' => $aImagesize["width"] + $C["popup"]["auto_resize_width"],
		'height' => $aImagesize["height"] + $C["popup"]["auto_resize_height"],
	);

	if (isset($aFile["comment"]) && $C["imgview"]["comment_position"] == 'right') {

		$aWindowsize["width"] += 15 + $C["imgview"]["comment_width"];

	}

	if (isset($_SESSION["user"]) && $_SESSION["user"]["usr_class"] <= 1) {

		$aWindowsize["height"] += 40;

		if (!isset($_SESSION["aSearchresults"])) $aWindowsize["width"] += 330;

	}

	if ($aWindowsize["width"] < 240) $aWindowsize["width"] = 240;
	if ($aWindowsize["height"] < 80) $aWindowsize["width"] = 80;

	$sH .= "\n".'<script language="JavaScript" type="text/JavaScript">'."\n";
	$sH .= '<!--'."\n";
	$sH .= '	window.resizeTo('.$aWindowsize["width"].', '.$aWindowsize["height"].');'."\n";
	$sH .= '//-->'."\n";
	$sH .= '</script>'."\n";

	// echo debug($aWindowsize);

	return $sH;

}

?>