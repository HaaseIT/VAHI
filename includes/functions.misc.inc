<?php
// $Id: functions.misc.inc,v 1.9 2007/11/19 10:07:19 mhaase Exp $
// -----------------------------------------------------------------------------
//                                                                            --
// Pryde Site Suite                                                           --
// functions.misc.inc                                                         --
//                                                                            --
// copyright: Marcus Haase (mail@marcus.haase.name)                           --
// The use of this Script is only allowed with the author's authorisation     --
// Any modification of the sources is strictly forbidden                      --
//                                                                            --
// -----------------------------------------------------------------------------

function T($sString = '') {
	global $T;

	if ($T[$sString] != '') return $T[$sString];

}

function PSS_buildInsertQuery($aData, $sTable) {

	$sFields = '';
	$sValues = '';
	foreach ($aData as $sKey => $sValue) {

		$sFields .= $sKey.', ';
		$sValues .= "'".$sValue."', ";

	}

	$sQ = "INSERT INTO ".$sTable." (";
	$sQ .= cutStringend($sFields, 2);
	$sQ .= ") VALUES (";
	$sQ .= cutStringend($sValues, 2);
	$sQ .= ")";

	return $sQ;

}

function PSS_buildUpdateQuery($aData, $sTable, $sPKey, $sPValue) {

	$sQ = "UPDATE ".$sTable." SET ";

	foreach ($aData as $sKey => $sValue) $sQ .= $sKey." = '".$sValue."', ";

	$sQ = cutStringend($sQ, 2);

	$sQ .= " WHERE ".$sPKey." = '".$sPValue."'";

	return $sQ;

}

function PSS_showClienttime() {

	$sH = '<script type="text/javascript">
<!--
		var Jetzt = new Date();
		var Tag = Jetzt.getDate();
		var Monat = Jetzt.getMonth() + 1;
		var Jahr = Jetzt.getYear();
		var Stunden = Jetzt.getHours();
		var Minuten = Jetzt.getMinutes();
		var NachVoll  = ((Minuten < 10) ? ":0" : ":");
		if (Jahr<2000) Jahr=Jahr+1900;
		document.write(Tag + "." + Monat + "." + Jahr + "  "
		+ Stunden + NachVoll + Minuten);
//-->
</script>';

	return $sH;

}

function prepareLangselect() {
	global $T, $PSS;

	foreach ($PSS["admin_comment_languages"] as $sValue) $aLangs[] = $sValue.'|'.$T["language_".$sValue];

	return $aLangs;

}

function cropFileextension($sFilename) {

	$aFilename = explode('.', $sFilename);

	$iParts = count($aFilename);

	$sFilename = '';

	foreach ($aFilename as $iKey => $sValue) {

		if ($iKey != ($iParts - 1)) $sFilename .= $sValue.'.';

	}

	return substr($sFilename, 0, strlen($sFilename) - 1);

}

function checkModule($sModule = '') {
	global $PSS;

	if ($PSS["show_msg"]) return false;

	if ($PSS["show_cp"]) return false;

	if ($PSS["show_ucp"]) return false;

	if ($PSS["show_image"]) return false;

	/*
	if ($sModule == 'login') {
	} elseif ($sModule == 'la') {
	}
	*/

	return true;

}

function uEncode($sString) {
		global $C;

		if ($C["imgview"]["viewer"] != 'highslide') {

			$sString = str_replace(' ', '{20}', $sString);
			$sString = str_replace('&', '{26}', $sString);
			$sString = str_replace('+', '{2B}', $sString);
			$sString = str_replace('ä', '{E4}', $sString);
			$sString = str_replace('ö', '{F6}', $sString);
			$sString = str_replace('ü', '{FC}', $sString);
			$sString = str_replace('Ä', '{C4}', $sString);
			$sString = str_replace('Ö', '{DE}', $sString);
			$sString = str_replace('Ü', '{DC}', $sString);

		}

	return $sString;

}

function uDecode($sString) {

	$sString = str_replace('{20}', ' ', $sString);
	$sString = str_replace('{26}', '&', $sString);
	$sString = str_replace('{2B}', '+', $sString);
	$sString = str_replace('{E4}', 'ä', $sString);
	$sString = str_replace('{F6}', 'ö', $sString);
	$sString = str_replace('{FC}', 'ü', $sString);
	$sString = str_replace('{C4}', 'Ä', $sString);
	$sString = str_replace('{DE}', 'Ö', $sString);
	$sString = str_replace('{DC}', 'Ü', $sString);

	return $sString;

}

function href($sDir = '', $aGetvars = array(), $sClass = '', $sEvents = '',  $sTarget = '') {
	global $PSS;

	$aGetkeys = array(
			'view' => 'pss_v',
			'page' => 'pss_p',
			'osize' => 'pss_o',
			'a' => 'pss_a',
			'key0' => 'pss_k0',
			'key1' => 'pss_k1',
			'pss_sid' => 'pss_sid',
	);

	// Fix for session trans sid
	$aGetvars["pss_sid"] = session_id();

	$sTag = '<a href="';

	if ($PSS["run_mode"] == 'embeded') {

		if ($sDir != '') $sTag .= '?pss_d='.$sDir.'&amp;';
		else $sTag .= '?';

	} else $sTag .= $sDir.'?';

	if (count($aGetvars)) {

		foreach ($aGetvars as $sKey => $sValue) {

			if ($PSS["run_mode"] == 'embeded') $sTag .= $aGetkeys[$sKey].'='.$sValue;
			else $sTag .= $sKey.'='.$sValue;

			$sTag .= '&amp;';

		}

		$sTag = substr($sTag, 0, strlen($sTag) - 5);

	} else $sTag = substr($sTag, 0, strlen($sTag) - 1);

	//if ($sDir != '' && is_array($aGetvars)) $sTag = substr($sTag, 0, strlen($sTag) - 1); // removed in 2.2.d7, now located 4 lines above without if clause

	$sTag .= '"';

	if ($sClass != '') $sTag .= ' class="'.$sClass.'"';
	if ($sEvents != '') $sTag .= ' '.$sEvents;
	if ($sTarget != '') $sTag .= ' target="'.$sTarget.'"';

	$sTag .= '>';

	return $sTag;

}

function getLanguage() {
	global $PSS;

	$sLang = $PSS["textcat_file"];

	// Text-cat selection
	if ($PSS["textcat_autodetect"]) {

		if (isset($_GET["l"])) {

			$sLang = strtolower($_GET["l"]);

			if (!isset($_COOKIE["l"]) || $_COOKIE["l"] != $_GET["l"]) {

				setcookie('l', strtolower($_GET["l"]), 0, '/');

			}

			//echo $_GET["l"];

		} elseif (isset($_COOKIE["l"])) {

			$sLang = $_COOKIE["l"];

		} else {

			if (isset($_SERVER["HTTP_ACCEPT_LANGUAGE"])) {

				$sLang = substr($_SERVER["HTTP_ACCEPT_LANGUAGE"], 0, 2);

			}

		}

		if (is_file($PSS["path_textcats"].$PSS["textcat_prefix"].$sLang.'.cat')) {

			$sInclude = $PSS["path_textcats"].$PSS["textcat_prefix"].$sLang.'.cat';

		} elseif ($PSS["textcat_fallback"] && is_file($PSS["path_textcats"].$sLang.'.cat')) {

			$sInclude = $PSS["path_textcats"].$sLang.'.cat';

		} elseif (is_file($PSS["path_textcats"].'en.cat')) { // last fallback to hardcoded default value

			$sInclude = $PSS["path_textcats"].'en.cat';
			$sLang = 'en';

		} else {

			die('<br>PSS startup error:<br>The text-catalog could not be loaded.');

		}

	} else {

		if (is_file($PSS["path_textcats"].$PSS["textcat_prefix"].$sLang.'.cat')) {

			$sInclude = $PSS["path_textcats"].$PSS["textcat_prefix"].$sLang.'.cat';

		} else {

			die('<br>PSS startup error:<br>The file: <em>'.$PSS["path_textcats"].$PSS["textcat_prefix"].$sLang.'.cat</em> could not be loaded.');

		}

	}

	$PSS["l"] = $sLang;

	return $sInclude;

}

function verifyRequest($aRequest) {
	global $PSS, $T;

	// permit direct acces to script file
	if ($_SERVER["REQUEST_URI"] == $_SERVER["SCRIPT_NAME"]) PSS_quit($T["error_403"]);

	// don't show thumbs-dir / resizes
	$sPath = urldecode($_SERVER["DOCUMENT_ROOT"].$aRequest["path"]);

	if((substr($sPath, -(strlen($PSS["dir_thumbs"]) + 1)) == '/'.$PSS["dir_thumbs"]) || (substr($sPath, -(strlen($PSS["dir_resize"]) + 1)) == '/'.$PSS["dir_resize"])) PSS_quit($T["error_403"]);

}

function getCheckbox($sKey, $sBoxvalue) {

		if(isset($_REQUEST[$sKey]) && $_REQUEST[$sKey] == $sBoxvalue) return true;
	else return false;

}

function getFormfield($sKey, $sDefault = '') {

		if(isset($_REQUEST[$sKey]) && $_REQUEST[$sKey] != '') $sValue = $_REQUEST[$sKey];
	else $sValue = $sDefault;

	return $sValue;

}

function cutStringend($sString, $iLength) {

		$sString = substr($sString, 0, strlen($sString) - $iLength);

	return $sString;

}

function calculateImagesize($sImage) {
		global $C, $PSS;

		$aImagedata = GetImageSize($sImage);

		$bResize = false;

		if(isset($_GET["view"]) && isset($PSS["view"][0]) && isset($PSS["view"][1]) && is_file($_SERVER["DOCUMENT_ROOT"].$PSS["view"][0].$PSS["view"][1])) {
			$iMaxwidth = ($C["imgview"]["maxwidth"] * 1);
			$iMaxheight = ($C["imgview"]["maxheight"] * 1);
		} else {
			$iMaxwidth = ($C["thumbs"]["maxwidth"] * 1);
			$iMaxheight = ($C["thumbs"]["maxheight"] * 1);
		}

		if($aImagedata[0] > $iMaxwidth && $aImagedata[1] > $iMaxheight) {
			$iWidth = $iMaxwidth;
			$iHeight = $aImagedata[1] / $aImagedata[0] * $iMaxwidth;

			if($iHeight > $iMaxheight) {
				$iHeight = $iMaxheight;
				$iWidth = $aImagedata[0] / $aImagedata[1] * $iMaxheight;
			}
		} elseif($aImagedata[0] > $iMaxwidth) {
			$iWidth = $iMaxwidth;
			$iHeight = $aImagedata[1] / $aImagedata[0] * $iMaxwidth;
		} elseif($aImagedata[1] > $iMaxheight) {
			$iHeight = $iMaxheight;
			$iWidth = $aImagedata[0] / $aImagedata[1] * $iMaxheight;
		} elseif($aImagedata[0] <= $iMaxwidth && $aImagedata[1] <= $iMaxheight) {
			$iWidth = $aImagedata[0];
			$iHeight = $aImagedata[1];
		}

		$aData = array(
			'width' => $aImagedata[0],
			'height' => $aImagedata[1],
			'twidth' => round($iWidth),
			'theight' => round($iHeight),
		);

		if($aData["width"] != $aData["twidth"]) $aData["resize"] = true;
		else $aData["resize"] = false;

		return $aData;
}

function write_ini_file($path, $assoc_array) {

	foreach ($assoc_array as $key => $item) {

		if (is_array($item)) {

			$content .= "\n[$key]\n";

			foreach ($item as $key2 => $item2) $content .= "$key2 = \"$item2\"\n";

		} else $content .= "$key = \"$item\"\n";

	}

	if (!$handle = fopen($path, 'w')) return false;

	if (!fwrite($handle, $content)) return false;

	fclose($handle);

	return true;

}

?>