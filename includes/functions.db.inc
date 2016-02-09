<?php
// $Id: functions.db.inc,v 1.7 2007/11/19 13:06:00 mhaase Exp $
// -----------------------------------------------------------------------------
//                                                                            --
// Pryde Site Suite                                                           --
// functions.db.inc                                                           --
//                                                                            --
// copyright: Marcus Haase (mail@marcus.haase.name)                           --
// The use of this Script is only allowed with the author's authorisation     --
// Any modification of the sources is strictly forbidden                      --
//                                                                            --
// -----------------------------------------------------------------------------

function getKeywordString($iId) {
	global $DB, $PSS;

	if (isset($PSS["keyword_lang_string"][$iId])) return $PSS["keyword_lang_string"][$iId];

  $sQuery = "SELECT kl_string, kl_lang FROM keywords_lang WHERE kl_kid = '".$iId."' ORDER BY kl_lang";
  $hResult = $DB->query($sQuery);
  //echo $sQuery;
  while($aRow = $DB->fetchArray($hResult)) $aKeywords[$aRow["kl_lang"]] = $aRow["kl_string"];

	if (isset($aKeywords[$PSS["l"]])) $sKlString = $aKeywords[$PSS["l"]];
	else $sKlString = $aKeywords["en"];

	$PSS["keyword_lang_string"][$iId] = $sKlString;

	return $sKlString;

}

function getCategoryString($iId) {
	global $DB, $PSS;

	$sQuery = "SELECT cl_string FROM categories_lang WHERE cl_cid = '".$iId."' AND cl_lang = '".$PSS["l"]."'";
	$hResult = $DB->query($sQuery);

	if ($DB->numRows($hResult)) {

		$aRow = $DB->fetchArray($hResult);

		return $aRow["cl_string"];

	}

	if ($PSS["textcat_file"] != $PSS["l"]) {

		$sQuery = "SELECT cl_string FROM categories_lang WHERE cl_cid = '".$iId."' AND cl_lang = '".$PSS["textcat_file"]."'";
		$hResult = $DB->query($sQuery);

		if ($DB->numRows($hResult)) {

			$aRow = $DB->fetchArray($hResult);

			return $aRow["cl_string"];

		}

	}

	$sQuery = "SELECT cl_string FROM categories_lang WHERE cl_cid = '".$iId."' AND cl_lang = 'en'";
	$hResult = $DB->query($sQuery);

	if ($DB->numRows($hResult)) {

		$aRow = $DB->fetchArray($hResult);

		return $aRow["cl_string"];

	}

}

function getFormatedKeywordsbyFile($iId) {
	global $DB, $PSS;

	$sH = '';

	$sQuery = "SELECT key_id FROM ".$PSS["db_table_matches"]." INNER JOIN ".$PSS["db_table_keywords"]." ON ";
	$sQuery .= $PSS["db_table_matches"].".mat_kid = ".$PSS["db_table_keywords"].".key_id";
	$sQuery .= " WHERE mat_fid = '".$iId."'";

	$hResult = $DB->query($sQuery);

	while ($aRow = $DB->fetchArray($hResult)) $sH .= getKeywordString($aRow["key_id"]).', ';

	$sH = cutStringend($sH, 2);

	return $sH;

}

function getFiledata($sPath, $sName) {
	global $DB, $PSS;

	if (!$PSS["admin_enable"]) return '';

	// Get file-data from DB
	$sQuery = "SELECT fil_id, fil_path, fil_name, fil_user FROM $PSS[db_table_files] WHERE ";
	$sQuery .= "fil_path = '$sPath' AND fil_name = '$sName'";

	$hResult_fil = $DB->query($sQuery);

	if ($DB->numRows($hResult_fil) != 1) return '';

	$aFile = $DB->fetchArray($hResult_fil);

	$sQuery = "SELECT com_lang, com_html FROM $PSS[db_table_comments] WHERE com_fid = '$aFile[fil_id]' AND ";

	if (isset($_REQUEST["sCommentlang"]) && in_array($_REQUEST["sCommentlang"], $PSS["admin_comment_languages"])) {

		$sQuery .= " com_lang = '".$_REQUEST["sCommentlang"]."'";

	} elseif (in_array($PSS["l"], $PSS["admin_comment_languages"])) {

		$sQuery .= " com_lang = '".$PSS["l"]."'";

	} else {

		$sQuery .= " com_lang = '".current($PSS["admin_comment_languages"])."'";

		reset($PSS["admin_comment_languages"]);

	}

	$hResult_com = $DB->query($sQuery);

	if ($DB->numRows($hResult_com) == 0 && !isset($_SESSION["user"])) {

		$sQuery = "SELECT com_lang, com_html FROM $PSS[db_table_comments] WHERE com_fid = '$aFile[fil_id]' ";
		$sQuery .= "AND com_lang = '".$PSS["l"]."'";

		$hResult_com = $DB->query($sQuery);

		if ($DB->numRows($hResult_com) == 0 && !isset($_SESSION["user"])) {

			$sQuery = "SELECT com_lang, com_html FROM $PSS[db_table_comments] WHERE com_fid = '$aFile[fil_id]' ";
			$sQuery .= "AND com_lang = '".$PSS["admin_comment_languages"][0]."'";

			$hResult_com = $DB->query($sQuery);

			if ($PSS["admin_comment_languages"][0] != 'en' && $DB->numRows($hResult_com) == 0 && !isset($_SESSION["user"])) {

				$sQuery = "SELECT com_lang, com_html FROM $PSS[db_table_comments] WHERE com_fid = '$aFile[fil_id]' ";
				$sQuery .= "AND com_lang = 'en'";

				$hResult_com = $DB->query($sQuery);

			}

		}

	}

	$aRow = $DB->fetchArray($hResult_com);

	$aFile["comment"] = $aRow["com_html"];

	return $aFile;

}

function doUserquery($sMethod) {
	global $DB, $PSS;

	$sQuery = "SELECT * FROM ";
	$sQuery .= "$PSS[db_table_users] WHERE ";

	if ($sMethod == 'login') $sQuery .= "usr_login = '$_REQUEST[pssu]' AND usr_password = md5('$_REQUEST[pssp]')";
	elseif ($sMethod == 'refresh') $sQuery .= "usr_id = '".$_SESSION["user"]["usr_id"]."'";
	else PSS_quit('Script error.');

	return $DB->query($sQuery);

}

?>