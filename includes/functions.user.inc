<?php
// $Id: functions.user.inc,v 1.15 2007/11/19 13:07:19 mhaase Exp $
// -----------------------------------------------------------------------------
//                                                                            --
// Pryde Site Suite                                                           --
// functions.admin.inc                                                        --
//                                                                            --
// copyright: Marcus Haase (mail@marcus.haase.name)                           --
// The use of this Script is only allowed with the author's authorisation     --
// Any modification of the sources is strictly forbidden                      --
//                                                                            --
// -----------------------------------------------------------------------------

function handlePWchange() {
	global $T;

	$sH = '';

	if (isset($_REQUEST["change"]) && $_REQUEST["change"] == "true") {
		$sErr = '';

		if (md5($_REQUEST["psspwc"]) != $_SESSION["user"]["usr_password"]) {

			$sErr .= 'Your current password was not entered correctly, please retry:<br />';

		} else {

			if ($_REQUEST["psspwn"] != $_REQUEST["psspwnc"]) {

				$sErr .= 'The new passwords don\'t match, please retry:<br />';

			} else {

				if (strlen($_REQUEST["psspwn"]) < 5) {

					$sErr .= 'The entered password is too short, please enter at least 5 characters:<br />';

				} else {

					global $DB;

					$sQuery = "UPDATE users SET usr_password = md5('".$_REQUEST["psspwn"]."') ";
					$sQuery .= "WHERE usr_id = '".$_SESSION["user"]["usr_id"]."'";

					$DB->query($sQuery);

					$hResult = doUserquery('refresh');

					$_SESSION["user"] = $DB->fetchArray($hResult);

				}

			}

		}

		if ($sErr == '') $sH .= '<div class="pss_main">Your password has been changed.<br /><br /><a href="?cp">'.$T["continue"].'</a></div>';
		else $sH .= '<div class="pss_main"><strong>'.$sErr.'</strong></div><br />'.showPasschangeform();

	} else {

		$sH .= showPasschangeform();

	}

	return $sH;

}

function showUCP($sMsg) {

	$sH = '';

	$sH .= '<div class="pss_main">';
	$sH .= '<strong>Welcome to the user control-panel</strong><br />';
	$sH .= $sMsg;
	$sH .= '<br />';

	$sH .= '<strong>User Settings/Overrides:</strong>';
	$sH .= '<div style="margin-top: 5px;">';
	$sH .= 'thumbs-listing is: '.(($_SESSION["user"]["usr_pref_showallimages"] == 1) ? 'full' : 'splitted').' <a href="./?ucp&chlisting='.(($_SESSION["user"]["usr_pref_showallimages"] == 1) ? 'off' : 'on').'">[change]</a>';
	$sH .= '</div>';

	$sH .= '<div style="margin-top: 5px;">';
	$sH .= 'override rows/cols in thumbs-listing: '.(($_SESSION["user"]["usr_pref_override_rowscols"] == 1) ? 'on' : 'off').' <a href="./?ucp&choverriderowscols='.(($_SESSION["user"]["usr_pref_override_rowscols"] == 1) ? 'off' : 'on').'">[change]</a>';
	$sH .= '</div>';

	$oForm = new Form();
	$oForm->bUsestyle = true;
	$oForm->sFormmethod = 'GET';
	$oForm->sFormaction = './';

	$sH .= $oForm->openForm();
	$sH .= $oForm->makeHidden('ucp');
	$sH .= '<div style="margin-top: 5px;">';
	$sH .= 'if rows/cols are overridden display: '.$oForm->makeText('chcols', $_SESSION["user"]["usr_pref_thumbscols"], 23, 2).' cols and '.$oForm->makeText('chrows', $_SESSION["user"]["usr_pref_thumbsrows"], 23, 2).' rows '.$oForm->makeSubmit('', 'submit', 65);
	$sH .= $oForm->closeForm();
	$sH .= '</div>';

	$sH .= '<div style="margin-top: 5px;">';
	$sH .= 'dir-mgmnt-menu is on: '.(($_SESSION["user"]["usr_pref_adminposition"] == 1) ? 'bottom' : 'top').' <a href="./?ucp&chmenuposition='.(($_SESSION["user"]["usr_pref_adminposition"] == 1) ? 'off' : 'on').'">[change]</a>';
	$sH .= '</div>';

	$sH .= '<div style="margin-top: 5px;">';
	$sH .= 'show navigation: '.(($_SESSION["user"]["usr_pref_shownav"] == 1) ? 'on' : 'off').' <a href="./?ucp&chshownav='.(($_SESSION["user"]["usr_pref_shownav"] == 1) ? 'off' : 'on').'">[change]</a>';
	$sH .= '</div>';

	$sH .= '<div style="margin-top: 5px;">';
	$sH .= 'show files: '.(($_SESSION["user"]["usr_pref_showfiles"] == 1) ? 'on' : 'off').' <a href="./?ucp&chshowfiles='.(($_SESSION["user"]["usr_pref_showfiles"] == 1) ? 'off' : 'on').'">[change]</a>';

	$sH .= '<div style="margin-top: 5px;">';
	$sH .= 'show hidden files/dirs: '.(($_SESSION["user"]["usr_pref_showhidden"] == 1) ? 'on' : 'off').' <a href="./?ucp&chshowhidden='.(($_SESSION["user"]["usr_pref_showhidden"] == 1) ? 'off' : 'on').'">[change]</a>';

	$sH .= '<div style="margin-top: 5px;">';
	$sH .= 'show date on thumbs: '.(($_SESSION["user"]["usr_pref_showdate"] == 1) ? 'on' : 'off').' <a href="./?ucp&chshowdate='.(($_SESSION["user"]["usr_pref_showdate"] == 1) ? 'off' : 'on').'">[change]</a>';

	$sH .= '<div style="margin-top: 5px;">';
	$sH .= 'show dimensions on thumbs: '.(($_SESSION["user"]["usr_pref_showdimensions"] == 1) ? 'on' : 'off').' <a href="./?ucp&chshowdimensions='.(($_SESSION["user"]["usr_pref_showdimensions"] == 1) ? 'off' : 'on').'">[change]</a>';

	$sH .= '<div style="margin-top: 5px;">';
	$sH .= 'show filesize on thumbs: '.(($_SESSION["user"]["usr_pref_showfilesize"] == 1) ? 'on' : 'off').' <a href="./?ucp&chshowfilesize='.(($_SESSION["user"]["usr_pref_showfilesize"] == 1) ? 'off' : 'on').'">[change]</a>';

	$sH .= '<div style="margin-top: 5px;">';
	$sH .= 'show directory-admin for thumbs: '.(($_SESSION["user"]["usr_pref_showdiradmin"] == 1) ? 'on' : 'off').' <a href="./?ucp&chshowdiradmin='.(($_SESSION["user"]["usr_pref_showdiradmin"] == 1) ? 'off' : 'on').'">[change]</a>';

	$sH .= '</div><br />';

	$sH .= '<strong>Profile:</strong>';
	$sH .= '<br />';
	$sH .= '<div style="margin-top: 5px;"><a href="'.$_SERVER["REQUEST_URI"].'&ucppw">';
	$sH .= '[ Change password ]';
	$sH .= '</a></div>';

	$sH .= '</div>';

	return $sH;

}

function handleUCP() {
	global $T;

	$sH = '';
	$sMsg = '';
	$bShowucp = true;

  if (isset($_REQUEST["ucppw"])) {

		$sH .= handlePWchange();
		$bShowucp = false;

	} elseif (isset($_REQUEST["chlisting"]) &&
			($_REQUEST["chlisting"] == 'on' || $_REQUEST["chlisting"] == 'off')) {

		changeUPref('usr_pref_showallimages', 'chlisting');

		// change adminmenu-position if wished
	} elseif (isset($_REQUEST["choverriderowscols"]) &&
						($_REQUEST["choverriderowscols"] == 'on' || $_REQUEST["choverriderowscols"] == 'off')) {

		changeUPref('usr_pref_override_rowscols', 'choverriderowscols');

	}  elseif (isset($_REQUEST["chrows"]) && isset($_REQUEST["chcols"]) &&
						($_REQUEST["chrows"] != '' || $_REQUEST["chcols"] != '')) {

		changeUPref('usr_pref_thumbsrows', 'chrows', 'int');
		changeUPref('usr_pref_thumbscols', 'chcols', 'int');

	} elseif (isset($_REQUEST["chmenuposition"]) &&
						($_REQUEST["chmenuposition"] == 'on' || $_REQUEST["chmenuposition"] == 'off')) {

		changeUPref('usr_pref_adminposition', 'chmenuposition');

	} elseif (isset($_REQUEST["chshownav"]) &&
						($_REQUEST["chshownav"] == 'on' || $_REQUEST["chshownav"] == 'off')) {

		changeUPref('usr_pref_shownav', 'chshownav');

	} elseif (isset($_REQUEST["chshowfiles"]) &&
						($_REQUEST["chshowfiles"] == 'on' || $_REQUEST["chshowfiles"] == 'off')) {

		changeUPref('usr_pref_showfiles', 'chshowfiles');

	} elseif (isset($_REQUEST["chshowhidden"]) &&
						($_REQUEST["chshowhidden"] == 'on' || $_REQUEST["chshowhidden"] == 'off')) {

		changeUPref('usr_pref_showhidden', 'chshowhidden');

	} elseif (isset($_REQUEST["chshowdate"]) &&
						($_REQUEST["chshowdate"] == 'on' || $_REQUEST["chshowdate"] == 'off')) {

		changeUPref('usr_pref_showdate', 'chshowdate');

	} elseif (isset($_REQUEST["chshowdimensions"]) &&
						($_REQUEST["chshowdimensions"] == 'on' || $_REQUEST["chshowdimensions"] == 'off')) {

		changeUPref('usr_pref_showdimensions', 'chshowdimensions');

	} elseif (isset($_REQUEST["chshowfilesize"]) &&
						($_REQUEST["chshowfilesize"] == 'on' || $_REQUEST["chshowfilesize"] == 'off')) {

		changeUPref('usr_pref_showfilesize', 'chshowfilesize');

	} elseif (isset($_REQUEST["chshowdiradmin"]) &&
						($_REQUEST["chshowdiradmin"] == 'on' || $_REQUEST["chshowdiradmin"] == 'off')) {

		changeUPref('usr_pref_showdiradmin', 'chshowdiradmin');

	}

	if ($bShowucp) $sH .= showUCP($sMsg);
	else $sH .= '<div class="pss_main"><a href="?ucp">&lt;&lt; Back to user cp</a></div>';

	return $sH;

}

function showCP($sMsg) {

	$sH = '';

  $sH .= '<div class="pss_main">';
	$sH .= '<strong>Welcome to the control-panel</strong><br />';
	$sH .= $sMsg;
	$sH .= '<br />';

	if ($_SESSION["user"]["usr_class"] == 0) {

		$sH .= '<strong>Search managment:</strong>';
		$sH .= '<div style="margin-top: 5px;">[ edit search categories ]</div>';
		$sH .= '<div style="margin-top: 5px;"><a href="'.$_SERVER["REQUEST_URI"].'&cpaddkeyword">[ add keyword ]</a></div>';
		$sH .= '<div style="margin-top: 5px;"><a href="'.$_SERVER["REQUEST_URI"].'&cpeditkeyword">[ edit keyword ]</a></div>';
		$sH .= '<div style="margin-top: 5px;"><a href="'.$_SERVER["REQUEST_URI"].'&cpdelkeyword">[ remove keyword ]</a></div>';
		$sH .= '<br />';
		$sH .= '<strong>Maintance:</strong>';
		$sH .= '<div style="margin-top: 5px;">[ remove orphans in database ]</div>';
		$sH .= '<br />';
		$sH .= '<strong>Statistics:</strong>';
		$sH .= '<div style="margin-top: 5px;"><a href="'.$_SERVER["REQUEST_URI"].'&cpdbstats">[ view database statistics ]</a></div>';
		$sH .= '<div style="margin-top: 5px;"><a href="'.$_SERVER["REQUEST_URI"].'&cpkeywordstats">[ view keyword statistics ]</a></div>';

	}

  $sH .= '</div>';

	return $sH;

}

function showDBStats() {
	global $DB, $PSS, $T;

	$sH = '';

	$sQuery = "SELECT fil_id from ".$PSS["db_table_files"];
	$hResult = $DB->query($sQuery);

	$aStats["files"] = $DB->numRows($hResult);

	$sQuery = "SELECT mat_fid from ".$PSS["db_table_matches"];
	$hResult = $DB->query($sQuery);

	$aStats["matches"] = $DB->numRows($hResult);

	$sQuery = "SELECT com_id from ".$PSS["db_table_comments"];
	$hResult = $DB->query($sQuery);

	$aStats["comments"] = $DB->numRows($hResult);

	$sH .= '<div class="pss_main"><strong>Database Statistics:</strong><br />';
	$sH .= 'Files linked: '.$aStats["files"];
	$sH .= '<br />';
	$sH .= 'Comments given: '.$aStats["comments"];
	$sH .= '<br />';
	$sH .= 'Keywords matches: '.$aStats["matches"];
	$sH .= '</div>';
	$sH .= '<br />';

	return $sH;

}

function handleAddKeyword() {
	global $DB, $PSS, $T;

	$bShowform = true;
	$sH = '';
	$sErr = '';

	if (isset($_REQUEST["add"]) && $_REQUEST["add"] == "true") {

		if (strlen($_REQUEST["keyword"]) < 3) $sErr .= 'The keyword is too short (min 3)<br />';

		if ($sErr == '') {

			$sQ = "SELECT kl_id FROM ".$PSS["db_table_keywords"];
      $sQ .= " INNER JOIN ".$PSS["db_table_keywords_lang"]." ON ";
      $sQ .= $PSS["db_table_keywords"].".key_id = ".$PSS["db_table_keywords_lang"].".kl_kid";
      $sQ .= " WHERE kl_string = '".$_REQUEST["keyword"]."' AND kl_lang = 'en'";

      //debug($sQ);

			$hResult = $DB->query($sQ);
			$iRows = $DB->numRows($hResult);

			if ($iRows == 0) {

        //$DB->query("SET AUTOCOMMIT = 0;");
        $DB->query("START TRANSACTION;");

				// INSERT QUERY HERE
        $aData = array(
          //'key_name' => $_REQUEST["keyword"],
          'key_category' => $_REQUEST["category"],
        );

        $sQ = PSS_buildInsertQuery($aData, $PSS["db_table_keywords"]);

        //debug($sQuery);

        $DB->query($sQ);

        $sDBErr = $DB->error();
        if ($sDBErr != '') $aDBErr[] = $sDBErr;

        $iIID = $DB->getLastInsertID();

        $aData = array(
          'kl_kid' => $iIID,
          'kl_lang' => 'en',
          'kl_string' => $_REQUEST["keyword"],
        );

        $sQ = PSS_buildInsertQuery($aData, $PSS["db_table_keywords_lang"]);

        //debug($sQuery);

        $DB->query($sQ);

        $sDBErr = $DB->error();
        if ($sDBErr != '') $aDBErr[] = $sDBErr;

				if (!isset($aDBErr) || count($aDBErr) == 0) {

          $DB->query("COMMIT;");
					$sH .= '<div class="pss_main">The keyword has been added.<br /><br /><a href="./?cp&cpaddkeyword&category='.$_REQUEST["category"].'">Click here to add another keyword</a></div><br />';
					$bShowform = false;

				} else {

          $DB->query("ROLLBACK;");
          $sErr .= 'The following database error has occured: ';

          foreach ($aDBErr as $sValue) $sErr .= '"'.$sValue.'", ';

          $sErr = cutStringEnd($sErr, 2);

        }

			} else $sErr .= 'This keyword already exists<br />';

		}

	}

	if ($bShowform) {

		$sQuery = "SELECT * FROM ".$PSS["db_table_categories"]." ORDER BY cat_order";

		$hResult = $DB->query($sQuery);

		while ($aRow = $DB->fetchArray($hResult)) $aOptions[] = $aRow["cat_id"].'|'.getCategoryString($aRow["cat_id"]);

		if ($sErr != '') $sH .= '<div class="pss_main" style="font-weight:bold; color:red;">'.$sErr.'</div><br />';

		$sH .= showAddKeywordForm($aOptions);

	}

	return $sH;

}

function showKeywordStats() {
	global $DB, $PSS, $T;

	$sH = '';

	$sQuery = "SELECT * FROM ".$PSS["db_table_categories"]." LEFT OUTER JOIN categories_lang ON categories.cat_id = categories_lang.cl_cid WHERE cl_lang = 'en' ORDER BY cat_order";
	$hResult = $DB->query($sQuery);



	while ($aRow = $DB->fetchArray($hResult)) {

		$sSubQuery = "SELECT * from ".$PSS["db_table_keywords"]." LEFT OUTER JOIN keywords_lang ON keywords.key_id = keywords_lang.kl_kid WHERE key_category = '".$aRow["cat_id"]."' ORDER BY kl_string";
		$hSubResult = $DB->query($sSubQuery);

		while ($aSubRow = $DB->fetchArray($hSubResult)) {

			$sSubSubQuery = "SELECT mat_kid FROM ".$PSS["db_table_matches"]." WHERE mat_kid = '".$aSubRow["key_id"]."'";

			$hSubSubResult = $DB->query($sSubSubQuery);
			$iMatches = $DB->numRows($hSubSubResult);

			$aKeywords[$aRow["cl_string"]][$aSubRow["kl_kid"].' '.$aSubRow["kl_string"]] = $iMatches;

		}

	}

  //echo $DB->error();

	$sH .= '<div class="pss_main" style="margin-bottom:10px;"><strong>Keyword Statistics:</strong></div>';

	foreach ($aKeywords as $sKey => $aValue) {

		$sH .= '<div class="pss_main" style="padding-bottom:5px; font-weight:bold;">Category: '.$sKey.'</div>';
		$sH .= '<table border="0" cellspacing="0" cellpadding="0">';
		$sH .= '<tr><td class="pss_main" width="120" style="border-bottom:1px solid;">Keyword</td><td class="pss_main" style="border-bottom:1px solid;">Matches&nbsp;</td></tr>';

		foreach ($aValue as $sSubKey => $sSubvalue) {

			$sH .= '<tr><td class="pss_main"'.(($sSubvalue == 0) ? ' style="text-decoration: underline overline;"' : '').'>'.$sSubKey.'</td>';
			$sH .= '<td class="pss_main">'.$sSubvalue.'</td></tr>';

		}

		$sH .= '</table><br />';


	}

	//$sH .= debug($aKeywords);

	return $sH;

}

function handleEditKeyword() {
	global $DB, $PSS, $T;

	$sH = '';
	$sErr = '';

	if (isset($_REQUEST["chosen"]) && $_REQUEST["chosen"] == true && isset($_REQUEST["keyid"])) {

		if (isset($_REQUEST["doedit"]) && $_REQUEST["doedit"] == true) {

			if (strlen($_REQUEST["keyword_name"]) < 3) {

				$sErr .= 'The keyword is too short (min 3).<br />';

			} else {

				$sQuery = "SELECT * FROM ".$PSS["db_table_keywords"]." WHERE key_name = '".$_REQUEST["keyword_name"]."' AND key_id != ".$_REQUEST["keyid"]."";

				$hResult = $DB->query($sQuery);
				$iRows = $DB->numRows($hResult);

				if ($iRows == 0) {

					$aData = array(

						'key_category' => $_REQUEST["category"],
						'key_name' => $_REQUEST["keyword_name"],

					);

					$sQuery = PSS_buildUpdateQuery($aData, $PSS["db_table_keywords"], 'key_id', $_REQUEST["keyid"]);

					//$sH .= $sQuery;

					$DB->query($sQuery);

					$sDBErr = $DB->error();

					if ($sDBErr == '') {

						$sH .= '<div class="pss_main">The keyword has been changed - '.PSS_showClienttime().'</div><br />';
						$bShowform = false;

					} else {

						$sErr .= 'The following database error has occured: "'.$sDBErr.'"';

					}

				} else {

					$sErr .= 'This keyword already exists<br />';

				}

			}

			if ($sErr != '') $sH .= '<div class="pss_main" style="font-weight:bold; color:red;">'.$sErr.'Your input has been reset</div><br />';

		}

		$sQuery = "SELECT * FROM ".$PSS["db_table_categories"]." ORDER BY cat_order";
		$hResult = $DB->query($sQuery);

		while ($aRow = $DB->fetchArray($hResult)) {

			$aCategories[] = $aRow["cat_id"].'|'.$aRow["cat_name"];

		}

		$sQuery = "SELECT * FROM ".$PSS["db_table_keywords"]." WHERE key_id = '".$_REQUEST["keyid"]."'";
		$hResult = $DB->query($sQuery);
		$aKeyword = $DB->fetchArray($hResult);

		//$sH .= debug($aCategories);
		//$sH .= debug($aKeyword);

		$sH .= showEditKeywordForm($aKeyword, $aCategories);

		$sH .= '<div class="pss_main"><a href="?cp&cpeditkeyword">&lt;&lt; Back to step 1</a></div><br />';

	} else {

		$sQuery = "SELECT * FROM ".$PSS["db_table_categories"]." ORDER BY cat_order";
		$hResult = $DB->query($sQuery);

		while ($aRow = $DB->fetchArray($hResult)) {

			$sSubQuery = "SELECT * from ".$PSS["db_table_keywords"]." WHERE key_category = '".$aRow["cat_id"]."'";
			$hSubResult = $DB->query($sSubQuery);

			while ($aSubRow = $DB->fetchArray($hSubResult)) {

				$aKeywords[getCategoryString($aRow["cat_id"])][] = $aSubRow["key_id"].'|'.getKeywordString($aSubRow["key_id"])." - ".$PSS["keyword_lang_string"][$aSubRow["key_id"]]["langsavailable"];

			}

		}

		$sH .= '<div class="pss_main" style="margin-bottom:10px;"><strong>Please choose the Keyword to edit:</strong></div>';

		$sH .= showSelectKeywordToEditForm($aKeywords, '?cp&cpeditkeyword');

	}

	return $sH;

}

function handleDelKeyword() {
	global $DB, $PSS, $T;

	$sH = '';
	$bShowSelect = true;

	if (isset($_REQUEST["chosen"]) && $_REQUEST["chosen"] == true && isset($_REQUEST["keyid"])) {

		if (isset($_REQUEST["deletematches"])) {

			$sQuery = "DELETE FROM ".$PSS["db_table_matches"]." WHERE mat_kid = '".$_REQUEST["keyid"]."'";
			$DB->query($sQuery);

		}

		$sQuery = "SELECT mat_kid FROM ".$PSS["db_table_matches"]." WHERE mat_kid = '".$_REQUEST["keyid"]."'";
		$hResult = $DB->query($sQuery);
		$iMatches = $DB->numRows($hResult);

		if ($iMatches != 0) {

			$sH .= '<div class="pss_main">There are '.$iMatches.' matches linked to this keyword.<br />Those have to be deleted first.<br /><br /><a href="./?cp&cpdelkeyword&chosen=true&keyid='.$_REQUEST["keyid"].'&deletematches" onClick="return confirm(\'Are you sure?\');">Click here to delete them</a><br /><br /><a href="./?cp&cpdelkeyword">&lt;&lt; Back to step 1</a></div><br />';
			$bShowSelect = false;

		} else {

			if (isset($_REQUEST["deletekeyword"])) {

				$sQuery = "DELETE FROM ".$PSS["db_table_keywords"]." WHERE key_id = '".$_REQUEST["keyid"]."'";
				$DB->query($sQuery);

				$sH .= '<div class="pss_main">The keyword has been deleted.</div><br />';

			} else {

				$sQuery = "SELECT key_name, key_id FROM ".$PSS["db_table_keywords"]." WHERE key_id = '".$_REQUEST["keyid"]."'";
				$hResult = $DB->query($sQuery);
				$aRow = $DB->fetchArray($hResult);

				$sH .= '<div class="pss_main">';

				if (isset($_REQUEST["deletematches"])) $sH .= 'The matches linked to the keyword have been deleted.<br /><br />';

				$sH .= 'You want to delete the keyword: <strong>'.$aRow["key_name"].'</strong>.<br /><br /><a href="./?cp&cpdelkeyword&chosen=true&keyid='.$_REQUEST["keyid"].'&deletekeyword" onClick="return confirm(\'Are you sure?\');">Click here to delete it</a><br /><br /><a href="./?cp&cpdelkeyword">&lt;&lt; Back to step 1</a></div><br />';
				$bShowSelect = false;

			}

		}

	}

	if ($bShowSelect) {

		$sQuery = "SELECT * FROM ".$PSS["db_table_categories"]." ORDER BY cat_order";
		$hResult = $DB->query($sQuery);

		while ($aRow = $DB->fetchArray($hResult)) {

			$sSubQuery = "SELECT * from ".$PSS["db_table_keywords"]." WHERE key_category = '".$aRow["cat_id"]."' ORDER BY key_name";
			$hSubResult = $DB->query($sSubQuery);

			while ($aSubRow = $DB->fetchArray($hSubResult)) {

				$aKeywords[$aRow["cat_name"]][] = $aSubRow["key_id"].'|'.$aSubRow["key_name"];

			}

		}

		$sH .= '<div class="pss_main" style="margin-bottom:10px;"><strong>Pick the keyword to delete:</strong></div>';

		$sH .= showSelectKeywordToEditForm($aKeywords, '?cp&cpdelkeyword');

	}

	return $sH;

}

function handleCP() {
	global $T;

	$sH = '';
	$sMsg = '';
	$bShowcp = true;

	if (isset($_REQUEST["cpdbstats"])) {

		$sH .= showDBStats();
		$bShowcp = false;

	} elseif (isset($_REQUEST["cpaddkeyword"])) {

		$sH .= handleAddKeyword();
		$bShowcp = false;

	} elseif (isset($_REQUEST["cpkeywordstats"])) {

		$sH .= showKeywordStats();
		$bShowcp = false;

	} elseif (isset($_REQUEST["cpeditkeyword"])) {

		$sH .= handleEditKeyword();
		$bShowcp = false;

	} elseif (isset($_REQUEST["cpdelkeyword"])) {

		$sH .= handleDelKeyword();
		$bShowcp = false;

	}


	if ($bShowcp) $sH .= showCP($sMsg);
	else $sH .= '<div class="pss_main"><a href="?cp">&lt;&lt; Back to control panel</a></div>';

	return $sH;

}

function changeUPref($sField, $sReqvar, $sType = 'switch') {
	global $DB, $PSS;

	$sQuery = "UPDATE $PSS[db_table_users] SET ";
	$sQuery .= $sField." = '";

	if ($sType == 'switch') {

		if ($_REQUEST[$sReqvar] == 'on') $sQuery .= "1";
		elseif ($_REQUEST[$sReqvar] == 'off') $sQuery .= "0";

	} elseif ($sType == 'int') {

		$iRequest = $_REQUEST[$sReqvar] * 1;

		if ($iRequest == 0) $iRequest = 1;

		$sQuery .= $iRequest;

	} else return false;

	$sQuery .= "' WHERE usr_id = '".$_SESSION["user"]["usr_id"]."'";

	$DB->query($sQuery);

	$hResult = doUserquery('refresh');

	$_SESSION["user"] = $DB->fetchArray($hResult);

}

function doFileoperations() {
	global $DB, $PSS, $T, $C;

	// File operations when logged in
	if (isset($_SESSION["user"]) && isset($_REQUEST["a"]) && ($_REQUEST["a"] != '' && $_REQUEST["a"] != 'search')) {

		$sQuery = "SELECT fil_id, fil_name, fil_path FROM $PSS[db_table_files] ";
		$sQuery .= "WHERE fil_path = '".$PSS["request"]["path"]."' ORDER BY fil_name";

		$hResult = $DB->query($sQuery);

		while ($aRow = $DB->fetchArray($hResult)) $aLinkedfiles[$aRow["fil_id"]] = $aRow["fil_name"];

		if ($_REQUEST["a"] == 'link' || $_REQUEST["a"] == 'addkey' ||
				$_REQUEST["a"] == 'chown' || $_REQUEST["a"] == 'comment') {

			$sFiles = '';
			$sKeywordfiles = '';

			if (isset($_REQUEST["aFiles"])) {

				foreach ($_REQUEST["aFiles"] as $aThis) {

					$aTemp = explode('|', $aThis);
					$sThis = uDecode($aTemp[1]);

					if (!@array_search($sThis, $aLinkedfiles)) {

						$sQuery = "INSERT INTO $PSS[db_table_files] ";
						$sQuery .= "(fil_name, fil_path, fil_user) VALUES ('$sThis', '".$PSS["request"]["path"]."', '{$_SESSION['user']['usr_id']}')";

						$DB->query($sQuery);

						$sFiles .= $sThis.', ';

					} // endif

				} // endforeach

				if ($_REQUEST["a"] == 'addkey') {

					foreach ($_REQUEST["aFiles"] as $aThis) {

						$aTemp = explode('|', $aThis);
						$sThis = uDecode($aTemp[1]);

						$sQuery = "SELECT fil_id FROM $PSS[db_table_files] WHERE ";
						$sQuery .= "fil_path = '".$PSS["request"]["path"]."' AND ";
						$sQuery .= "fil_name = '$sThis'";

						$hResult = $DB->query($sQuery);

						$aRow = $DB->fetchArray($hResult);

						$sQuery = "SELECT * FROM $PSS[db_table_matches] WHERE ";
						$sQuery .= "mat_fid = '$aRow[fil_id]' AND ";
						$sQuery .= "mat_kid = '$_REQUEST[iKeyword]'";

						$hResult = $DB->query($sQuery);

						if ($DB->numRows($hResult) == 0) {

							$sQuery = "INSERT INTO $PSS[db_table_matches] ";
							$sQuery .= "(mat_fid, mat_kid) VALUES ('$aRow[fil_id]', '$_REQUEST[iKeyword]')";

							$DB->query($sQuery);

							$sKeywordfiles .= $sThis.', ';

						}

					}

				} elseif ($_REQUEST["a"] == 'chown') {

					foreach ($_REQUEST["aFiles"] as $aThis) {

						$aTemp = explode('|', $aThis);
						$sThis = uDecode($aTemp[1]);

						$sQuery = "SELECT fil_id FROM $PSS[db_table_files] WHERE ";
						$sQuery .= "fil_path = '".$PSS["request"]["path"]."' AND ";
						$sQuery .= "fil_name = '$sThis'";

						$hResult = $DB->query($sQuery);

						$aRow = $DB->fetchArray($hResult);

						$sQuery = "UPDATE $PSS[db_table_files] SET fil_user = '$_REQUEST[iUser]' WHERE fil_id = '$aRow[fil_id]'";

						$DB->query($sQuery);

					}

				} elseif ($_REQUEST["a"] == 'comment') {

					foreach ($_REQUEST["aFiles"] as $aThis) {

						$aTemp = explode('|', $aThis);
						$sThis = uDecode($aTemp[1]);

						$sQuery = "SELECT fil_id FROM $PSS[db_table_files] WHERE ";
						$sQuery .= "fil_path = '".$PSS["request"]["path"]."' AND ";
						$sQuery .= "fil_name = '$sThis'";

						$hResult = $DB->query($sQuery);

						$aRow = $DB->fetchArray($hResult);

						if (isset($_REQUEST["sCommentlang"])) {

							$TMP_L = $_REQUEST["sCommentlang"];

						} else {

							$TMP_L = current($PSS["admin_comment_languages"]);
							reset($PSS["admin_comment_languages"]);

						}

						$sQuery = "SELECT com_id FROM $PSS[db_table_comments] WHERE com_fid = '$aRow[fil_id]' && com_lang = '".$TMP_L."'";

						$hResult = $DB->query($sQuery);

						if ($DB->numRows($hResult)) {

							$sQuery = "UPDATE $PSS[db_table_comments] SET COM_HTML = '$_REQUEST[sComment]' WHERE com_fid = '$aRow[fil_id]' AND com_lang = '".$TMP_L."'";

						} else {

							$sQuery = "INSERT INTO $PSS[db_table_comments] (com_fid, com_lang, com_html) VALUES ('$aRow[fil_id]', '".$TMP_L."', '$_REQUEST[sComment]')";

						}

						$DB->query($sQuery);

						unset($TMP_L);

					}

				}

			} // endif isset files

			if (!isset($_GET["view"])) {

				$PSS["show_msg"] = true;

				$sH .= '<div class="pss_main">';

				if ($sFiles != '') {

					$sH .= '<br /><span class="pss_main" style="color:green;"><strong>'.$T["actions_link_1"].cutStringend($sFiles, 2).$T["actions_link_2"].'</strong></span><br />';

				}

				if ($sKeywordfiles != '') {

					$sH .= '<br /><span class="pss_main" style="color:green;"><strong>'.$T["actions_keyword_1"].cutStringend($sKeywordfiles, 2).$T["actions_keyword_2"].'"</strong></span><br />';

				}

				if ($_REQUEST["a"] == 'chown') $sH .= '<br /><strong>'.$T["actions_owner"].'</strong><br />';

				if ($_REQUEST["a"] == 'comment') $sH .= '<br /><strong>'.$T["actions_comment"].'</strong><br />';

				if ($sFiles = '' && $sKeywordfiles = '') {

					$sH .= '<br /><strong>'.$T["actions_none"].'</strong><br />';

				}

				$sH .= '<br /><a href="./';

				if (isset($_REQUEST["page"])) $sH .= '?page='.$_REQUEST["page"];

				$sH .= '">'.$T["continue"].'</a><br />';
				$sH .= '</div>';

				//echo debug($_REQUEST["aFiles"]);
				//echo $DB->error();

			}

		} elseif ($_REQUEST["a"] == 'delkey') {

			$sFiles = '';

			if (isset($_REQUEST["aFiles"])) {

				foreach ($_REQUEST["aFiles"] as $aThis) {

					$aTemp = explode('|', $aThis);
					$sThis = uDecode($aTemp[1]);

					$sQuery = "SELECT fil_id FROM $PSS[db_table_files] WHERE ";
					$sQuery .= "fil_path = '".$PSS["request"]["path"]."' AND ";
					$sQuery .= "fil_name = '$sThis'";

					$hResult = $DB->query($sQuery);

					if ($DB->numRows($hResult) != 0) {

						$aRow = $DB->fetchArray($hResult);

						$sQuery = "DELETE FROM $PSS[db_table_matches] WHERE ";
						$sQuery .= "mat_fid = '$aRow[fil_id]' AND ";
						$sQuery .= "mat_kid = '$_REQUEST[iKeyword]'";

						$DB->query($sQuery);

					} // endif

				} // endforeach

			}

			if (!isset($_GET["view"])) {

				$PSS["show_msg"] = true;

				$sH .= '<div class="pss_main">';

				$sH .= '<br /><span class="pss_main" style="color:green;"><strong>'.$T["actions_keyword_remove"].'</strong></span><br />';

				$sH .= '<br /><a href="./';

				if (isset($_REQUEST["page"])) $sH .= '?page='.$_REQUEST["page"];

				$sH .= '">'.$T["continue"].'</a><br />';
				$sH .= '</div>';

				//echo debug($_REQUEST["aFiles"]);
				//echo $DB->error();

			}

		} elseif ($_REQUEST["a"] == 'unlink') {

			$sFiles = '';

			if (isset($_REQUEST["aFiles"])) {

				foreach ($_REQUEST["aFiles"] as $aThis) {

					$aTemp = explode('|', $aThis);
					$sThis = uDecode($aTemp[1]);

					$sQuery = "SELECT fil_id FROM $PSS[db_table_files] WHERE ";
					$sQuery .= "fil_path = '".$PSS["request"]["path"]."' AND ";
					$sQuery .= "fil_name = '$sThis'";

					$hResult = $DB->query($sQuery);

					if ($DB->numRows($hResult) != 0) {

						$aRow = $DB->fetchArray($hResult);

						$sQuery = "DELETE FROM $PSS[db_table_matches] WHERE ";
						$sQuery .= "mat_fid = '$aRow[fil_id]'";

						$DB->query($sQuery);

						$sQuery = "DELETE FROM $PSS[db_table_comments] WHERE ";
						$sQuery .= "com_fid = '$aRow[fil_id]'";

						$DB->query($sQuery);

						$sQuery = "DELETE FROM $PSS[db_table_files] WHERE ";
						$sQuery .= "fil_id = '$aRow[fil_id]'";

						$DB->query($sQuery);

						$sFiles .= $sThis.', ';

					} // endif

				} // endforeach

			}

			if (!isset($_GET["view"])) {

				$PSS["show_msg"] = true;

				$sH .= '<div class="pss_main">';

				if ($sFiles != '') {

					$sH .= '<br /><span class="pss_main" style="color:green;"><strong>'.$T["actions_unlink_1"].cutStringend($sFiles, 2).$T["actions_unlink_2"].'</strong></span><br />';

				} else {

					$sH .= '<br /><strong>'.$T["actions_none"].'</strong><br />';

				}

				$sH .= '<br /><a href="./';

				if (isset($_REQUEST["page"])) $sH .= '?page='.$_REQUEST["page"];

				$sH .= '">'.$T["continue"].'</a><br />';
				$sH .= '</div>';

				//echo debug($_REQUEST["aFiles"]);
				//echo $DB->error();

			}

		} elseif ($_REQUEST["a"] == 'null' && !isset($_GET["view"])) {

			$PSS["show_msg"] = true;

			$sH .= '<div class="pss_main">';
			$sH .= '<br /><strong>'.$T["actions_none"].'</strong><br />';
			$sH .= '<br /><a href="./';

			if (isset($_REQUEST["page"])) $sH .= '?page='.$_REQUEST["page"];

			$sH .= '">'.$T["continue"].'</a><br />';
			$sH .= '</div>';

		}

	}


	if (isset($sH)) return $sH;

}

function handleLogin() {
	global $C, $T, $DB;

	$sH = '';

	if (!$_REQUEST["login"]) $sH .= showLoginform();
	else {

		$sH .= '<div class="pss_main">';

		$hResult = doUserquery('login');

		if($DB->numRows($hResult) == 1) {

			$_SESSION["user"] = $DB->fetchArray($hResult);

		} else {

			if (isset($_SESSION["user"])) unset($_SESSION["user"]);

		}

		if (isset($_SESSION["user"])) {

			$sH .= '<span class="pss_main" style="color:green;"><strong>'.$T["login_success"].'</strong></span><br /><br />';
			$sH .= '<a href="./">'.$T["continue"].'</a><br />';

		} else {

			$sH .= '<br /><span class="pss_main" style="color:#ff0000;"><strong>'.$T["login_fail"].'</strong></span><br /><br />';
			$sH .= '<a href="./?login">'.$T["back"].'</a><br />';

		}

		$sH .= '</div>';

//		echo debug($_SESSION);

	}

	return $sH;

}

function handleLogout() {
	global $C, $T;

	$sH = '';

	if (isset($_SESSION["user"])) {

		unset($_SESSION["user"]);

		$sH .= '<div class="pss_main">';
		$sH .= '<br /><strong>'.$T["login_logout"].'</strong><br /><br />';
		$sH .= '<span class="pss_main"><a href="./';

		if (isset($_REQUEST["page"])) $sH .= '?page='.$_REQUEST["page"];

		$sH .= '">'.$T["continue"].'</a></span><br />';
		$sH .= '</div>';

	} else {

		$sH .= '<div class="pss_main">';
		$sH .= '<br /><strong>'.$T["actions_none"].'</strong><br /><br />';
		$sH .= '<span class="pss_main"><a href="./';

		if (isset($_REQUEST["page"])) $sH .= '?page='.$_REQUEST["page"];

		$sH .= '">'.$T["continue"].'</a></span><br />';
		$sH .= '</div>';

	}

	return $sH;

}

function generateUsermenu() {
	global $C, $T, $PSS;

  $sH = '';

	// Logged in message and usermenu
	if (isset($_SESSION["user"])) {

		$sH .= '<div class="pss_main">';

		if ($C["imgview"]["viewer"] != 'popup' || !isset($_GET["view"])) {

			$sH .= $T["unav_head"].'&nbsp;&nbsp;';

			if (!isset($_GET["view"])) {

				if (isset($PSS["debug_enable"]) && $PSS["debug_enable"] == true) $sH .= '<a href="./?reload">[reload userdata]</a>&nbsp;-&nbsp;';

				if ($_SESSION["user"]["usr_class"] <= 1 && isset($_REQUEST["ucp"])) {

					$sH .= '<a href="./">[leave user cp]</a>&nbsp;-&nbsp;';

				} elseif ($_SESSION["user"]["usr_class"] <= 1 && !isset($_REQUEST["ucp"])) {

					$sH .= '<a href="./?ucp">[user cp]</a>&nbsp;-&nbsp;';

				}

				if (isset($_REQUEST["cp"])) {

					$sH .= '<a href="./">['.$T["unav_cp_leave"].']</a>&nbsp;-&nbsp;';

				} elseif ($_SESSION["user"]["usr_class"] <= 1 && !isset($_REQUEST["cp"])) {

					$sH .= '<a href="./?cp">['.$T["unav_cp"].']</a>&nbsp;-&nbsp;';

				}

			}

			$sH .= '<a href="./?logout';

			// Page mitschleifen, soger bei logout
			if (isset($_REQUEST["page"])) $sH .= '&page='.$_REQUEST["page"];

			$sH .= '">['.$T["unav_logout"].']</a>&nbsp;-&nbsp;';

			$sH .= 'Switch language to: ';

			foreach ($PSS["admin_comment_languages"] as $sValue) {

				$sH .= '<a href="./?l='.$sValue;
				// Page mitschleifen
				if (isset($_REQUEST["page"])) $sH .= '&page='.$_REQUEST["page"];
				$sH .= '">['.$sValue.']</a>';

			}

			$sH .= '<br />';

		}

		$sH .= '<br />'.$T["unav_whoami_1"].$_SESSION["user"]["usr_login"].$T["unav_whoami_2"].'</div>';

		if (isset($_GET["view"]) && $C["imgview"]["viewer"] != 'popup' || !isset($_GET["view"])) $sH .= $C["global"]["hr"];

	} else $sH = '';

	return $sH;

}

?>