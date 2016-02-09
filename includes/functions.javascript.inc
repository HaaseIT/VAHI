<?php
// $Id: functions.javascript.inc,v 1.2 2007/05/22 12:26:34 mhaase Exp $
// -----------------------------------------------------------------------------
//                                                                            --
// Pryde Site Suite                                                           --
// functions.javascript.inc                                                   --
//                                                                            --
// copyright: Marcus Haase (mail@marcus.haase.name)                           --
// The use of this Script is only allowed with the author's authorisation     --
// Any modification of the sources is strictly forbidden                      --
//                                                                            --
// -----------------------------------------------------------------------------

function openScript() {
	global $bScriptopen;
	
	if (!$bScriptopen) {
		
		$sTag  = '<script language="JavaScript" type="text/JavaScript">'."\n";
		$sTag .= '<!--'."\n\n";
		$bScriptopen = true;
		
		return $sTag;
		
	}
	
}

function showOpenpopup() {
	global $PSS;
	
	$sTag  = 'function openPopup(fileName,winName,left,top,width,height,isResizable,hasScrollBars,hasMenuBar,hasLocationBar,hasStatusBar)	{'."\n";
	$sTag .= '  var str = "";'."\n";
	$sTag .= '  str +=  "width=" + ((width) ? width : 100);'."\n";
	$sTag .= '  str +=  ",height=" + ((height) ? height : 100);'."\n";
	$sTag .= '  str +=  ",resizable=" + ((isResizable) ? "yes" : "no");'."\n";
	$sTag .= '  str +=  ",status=" + ((hasStatusBar) ? "yes" : "no");'."\n";
	$sTag .= '  str +=  ",locationbar=" + ((hasLocationBar) ? "yes" : "no");'."\n";
	$sTag .= '  str +=  ",scrollbars=" + ((hasScrollBars) ? "yes" : "no");'."\n";
	$sTag .= '  str +=  ",menubar=" + ((hasMenuBar) ? "yes" : "no");'."\n";
	// $sTag .= '  if (is.ns) {'."\n";
	// $sTag .= '    str += ",screenX=" + ((left) ? left : 100);'."\n";
	// $sTag .= '    str += ",screenY=" + ((top) ? top : 100);'."\n";
	// $sTag .= '  }'."\n\n";
	$sTag .= '  popup = window.open(fileName + "&'.session_name().'='.session_id();
	
	if ($PSS["textcat_autodetect"]) $sTag .= '&l='.$PSS["l"];
	
	$sTag .= '",winName,str);'."\n\n";
	// $sTag .= '  if (is.ie) popup.moveTo(left,top);'."\n";
	$sTag .= '  popup.focus();'."\n";
	$sTag .= '}'."\n\n";
	
	return $sTag;
	
}

?>