<?php

// -----------------------------------------------------------------------------
//                                                                            --
// Pryde Site Suite                                                           --
// pss_embed.php                                                              --
//                                                                            --
// copyright: Marcus Haase (mail@marcus.haase.name)                           --
// The use of this Script is only allowed with the author's authorisation     --
//                                                                            --
// -----------------------------------------------------------------------------

/*

To embed the pss into a site use the following calls:
(replace "string language" with the language to use (eg. de / en)
or leave empty)

include_once($_SERVER["DOCUMENT_ROOT"].'/../pss/pss_embed.php');
$sTag .= pss_embed([string language], [string user], [string password]);

*/

function pss_embed($PSS_LANG = '', $sUser = '', $sPassword = '', $sBasedir = '') {

	ini_set('user_agent', 'pss_embed');

	$sURI = 'http://';

	if ($sUser != '' && $sPassword != '') $sURI .= $sUser.':'.$sPassword.'@';

	$sURI .= $_SERVER["HTTP_HOST"].'/content/';

	if ($sBasedir != '' && $sBasedir != substr($_REQUEST["pss_d"], 0, strlen($sBasedir))) $sURI .= $sBasedir;

	if (isset($_REQUEST["pss_d"])) $sURI .= str_replace("%2F", "/", rawurlencode($_REQUEST["pss_d"]));

	$sURI .= '?';

	if ($PSS_LANG != '') $sURI .= 'l='.$PSS_LANG.'&';
	if (isset($_REQUEST["pss_sid"])) $sURI .= 'pss_sid='.$_REQUEST["pss_sid"].'&';
	if (isset($_REQUEST["pss_p"])) $sURI .= 'page='.$_REQUEST["pss_p"].'&';
	if (isset($_REQUEST["pss_o"])) $sURI .= 'osize='.$_REQUEST["pss_o"].'&';

	if (isset($_REQUEST["pss_a"])) $sURI .= 'a='.$_REQUEST["pss_a"].'&';
	if (isset($_REQUEST["pss_k0"])) $sURI .= 'key0='.$_REQUEST["pss_k0"].'&';
	if (isset($_REQUEST["pss_k1"])) $sURI .= 'key1='.$_REQUEST["pss_k1"].'&';


	if (isset($_REQUEST["pss_v"])) {

		$aTemp = explode('|', $_REQUEST["pss_v"]);

		$aTemp[0] = str_replace("%2F", "/", rawurlencode($aTemp[0]));

		$sURI .= 'view='.$aTemp[0].'|'.urlencode($aTemp[1]).'&';

		unset($aTemp);

	}

	$sURI = substr($sURI, 0, strlen($sURI) - 1);

	if ($sTag = @file_get_contents($sURI)) {

		return $sTag;

	} elseif ($sUser == '' && $sPassword == '') {

		return 'The requested page is not available.';

	} else {

		return false;

	}

}

?>
