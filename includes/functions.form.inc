<?php
// $Id: functions.form.inc,v 1.7 2007/05/24 11:14:02 mhaase Exp $
// -----------------------------------------------------------------------------
//                                                                            --
// Pryde Site Suite                                                           --
// functions.form.inc                                                         --
//                                                                            --
// copyright: Marcus Haase (mail@marcus.haase.name)                           --
// The use of this Script is only allowed with the author's authorisation     --
// Any modification of the sources is strictly forbidden                      --
//                                                                            --
// -----------------------------------------------------------------------------

function showEditKeywordForm($aKeyword, $aCategories) {

	$oForm = new Form();
	$oForm->bUsestyle = true;
	$oForm->sFormaction = $_SERVER["REQUEST_URI"];

	$sH = $oForm->openForm();
	$sH .= $oForm->makeHidden('chosen', 'true');
	$sH .= $oForm->makeHidden('doedit', 'true');
	$sH .= $oForm->makeHidden('keyid', $_REQUEST["keyid"]);

	$sH .= '<div class="pss_main" style="font-weight:bold;">Category:</div>';
	$sH .= $oForm->makeSelect('category', $aCategories, $aKeyword["key_category"], 200).'<br>';
	$sH .= '<div class="pss_main" style="padding-top:10px; font-weight:bold;">Keyword name:</div>';
	$sH .= $oForm->makeText('keyword_name', $aKeyword["key_name"], 200).'<br>';

	$sH .= $oForm->makeSubmit('', 'edit', 200);
	$sH .= $oForm->closeForm();

	return $sH;

}

function showSelectKeywordToEditForm($aKeywords, $sGetvars) {

	$oForm = new Form();
	$oForm->bUsestyle = true;
	$oForm->sFormaction = $sGetvars;

	$sH = '';

	foreach ($aKeywords as $sKey => $aValues) {

    $iSelectheight = count($aValues);
    if ($iSelectheight > 12) $iSelectheight = 12;

		$sH = $oForm->openForm();
		$sH .= '<div class="pss_main" style="padding-bottom:5px; font-weight:bold;">Category: '.$sKey.'</div>';
		$sH .= $oForm->makeHidden('chosen', 'true');
		$sH .= $oForm->makeSelect('keyid', $aValues, '', 200, $iSelectheight).'<br>';
		$sH .= $oForm->makeSubmit('', 'next step', 200);
		$sH .= $oForm->closeForm();

	}

	return $sH;

}

function showAddKeywordForm($aOptions) {

	$oForm = new Form();
	$oForm->bUsestyle = true;
	$oForm->sFormaction = $_SERVER["REQUEST_URI"];

	$sH = '<div class="pss_main">';
  $sH .= $oForm->openForm();
  $sH .= $oForm->makeHidden('add', 'true');
  //$sH .= $oForm->makeHidden('language', 'en'); // TODO: Multiple languages
	$sH .= '<div class="pss_main"><strong>Add keyword</strong></div>';
	$sH .= '<div style="margin-top:5px;">Select the category:<br>';
	$sH .= $oForm->makeSelect('category', $aOptions, (isset($_REQUEST["category"]) ? $_REQUEST["category"] : ''), 200);
	$sH .= '</div><div style="margin-top:5px; margin-bottom:5px;">';
	$sH .= 'Enter the keyword:<br>';
	$sH .= $oForm->makeText('keyword', '', 200);
	$sH .= '</div>';
	$sH .= $oForm->makeSubmit('submit', 'Submit', 200);
	$sH .= $oForm->closeForm();
	$sH .= '</div><br />';

	return $sH;

}

function showPasschangeform() {

	$oForm = new Form();
	$oForm->bUsestyle = true;
	$oForm->sFormaction = $_SERVER["REQUEST_URI"];

	$sH = '<div class="pss_main">';
  $sH .= $oForm->openForm();
  $sH .= $oForm->makeHidden('change', 'true');
	$sH .= '<span class="pss_main"><strong>Change password</strong></span><br />';
	$sH .= 'Enter current password here:<br>';
	$sH .= $oForm->makePassword('psspwc', '', 256, 64);
  $sH .= '<br />';
	$sH .= 'Enter new password here:<br>';
	$sH .= $oForm->makePassword('psspwn', '', 256, 64);
	$sH .= '<br />';
	$sH .= 'Confirm new password here:<br>';
	$sH .= $oForm->makePassword('psspwnc', '', 256);
  $sH .= '<br />';
	$sH .= $oForm->makeSubmit('submit', 'Submit', 256);
	$sH .= $oForm->closeForm();
	$sH .= '</div><br />';

	return $sH;

}

function showLoginform() {
	global $T, $C;

	$oForm = new Form();
	$oForm->bUsestyle = true;
	$oForm->sFormaction = $_SERVER["REQUEST_URI"];

	$sH = '<div class="pss_dir">';
  $sH .= $oForm->openForm();
  $sH .= $oForm->makeHidden('login', 'true');
	$sH .= '<span class="pss_main">'.$T["login_formhead"].'</span><br />';
	$sH .= $oForm->makeText('pssu', '', 256, 64);
  $sH .= '<br />';
	$sH .= $oForm->makePassword('pssp', '', 256);
  $sH .= '<br />';
	$sH .= $oForm->makeSubmit('submit', $T["login_submittext"], 256);
	$sH .= $oForm->closeForm();
	$sH .= '</div>';

	return $sH;

}

?>