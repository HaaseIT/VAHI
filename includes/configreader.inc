<?php
// $Id: configreader.inc,v 1.2 2007/05/22 12:26:34 mhaase Exp $

function getConf() {
	global $PSS;

	$aIni[0] = parse_ini_file($PSS["path_includes"].$PSS["file_conf"], true);

	$sTag = '';

	$aRequest = parse_url($_SERVER["REQUEST_URI"]);

	if (isset($_REQUEST["view"])) {

		$aTemp = explode('|', $_REQUEST["view"]);

		$aRequest["path"] = udecode($aTemp[0]);

		unset($aTemp);

	} else {

		$aRequest["path"] = urldecode($aRequest["path"]);

	}

	$iDepth = substr_count($aRequest["path"], '/');

	if (is_file($_SERVER["DOCUMENT_ROOT"].$aRequest["path"].$PSS["file_conf"])) $aIni_thisdir = parse_ini_file($_SERVER["DOCUMENT_ROOT"].$aRequest["path"].$PSS["file_conf"], true);

	$sPathmod = '';
	for ($i = $iDepth; $i >= 1; $i--) {

		if (is_file($_SERVER["DOCUMENT_ROOT"].$aRequest["path"].$sPathmod.$PSS["file_conf"])) {

			$aIni[$i] = parse_ini_file($_SERVER["DOCUMENT_ROOT"].$aRequest["path"].$sPathmod.$PSS["file_conf"], true);

		}

		$sPathmod .= '../';

		ksort($aIni);

	}

	if (count($aIni) > 1) {

		$sMerge = '$aIni_merged = array_merge_recursive(';
		foreach ($aIni as $iKey => $aThis) {

			$sMerge .= '$aIni['.$iKey.'], ';

		}

		$sMerge = substr($sMerge, 0, strlen($sMerge) - 2);

		$sMerge .= ');';

		eval($sMerge);

		$aIni_master = array();
		foreach ($aIni_merged as $sKey => $aThis) {

			$aIni_master[$sKey] = array();

			foreach ($aThis as $sSubkey => $aSubthis) {

				$iChildren = count($aSubthis);

				if ($iChildren > 1) {

					// config override set_parent_link if inherit_parentlink is false and not defined in this
					// dirs config file, not needed if only 1 child
					if (!$PSS["inherit_parentlink"] && $sKey == 'directory' && $sSubkey == 'show_parent_link'
							&& (!is_file($_SERVER["DOCUMENT_ROOT"].$aRequest["path"].$PSS["file_conf"])
							|| (is_file($_SERVER["DOCUMENT_ROOT"].$aRequest["path"].$PSS["file_conf"])
							&& (!isset($aIni_thisdir["directory"]["show_parent_link"])
							|| $aIni_thisdir["directory"]["show_parent_link"])))) {

						$aIni_master["directory"]["show_parent_link"] = true;

					} else {

						$aIni_master[$sKey][$sSubkey] = $aSubthis[$iChildren - 1];

					}

				} else {

					$aIni_master[$sKey][$sSubkey] = $aSubthis;

				}

			}

		}

	} else {

		$aIni_master = $aIni[0];

	}

	return $aIni_master;

}

$C = getConf();

?>