<?php
// $Id: session.inc,v 1.2.1 2011/05/18 08:46:35 mhaase Exp $
// -----------------------------------------------------------------------------
//                                                                            --
// Pryde Site Suite                                                           --
// session.inc                                                                --
//                                                                            --
// copyright: Marcus Haase (mail@marcus.haase.name)                           --
// The use of this Script is only allowed with the author's authorisation     --
// Any modification of the sources is strictly forbidden                      --
//                                                                            --
// -----------------------------------------------------------------------------

// Session handling
session_name('pss_sid');
//echo session_name()."\n";

// session.use_trans_sid wenn nötig aktivieren
// muss noch getestet werden
if(ini_get('session.use_trans_sid') == 1) {
  ini_set('session.use_trans_sid', 0);
}

// register_globals wenn nötig deaktivieren
// muss noch getestet werden / scheint nicht zu funktionieren.
if(ini_get('register_globals') == 1) {
  ini_set('register_globals', 0);
}

// Session wenn nötig starten
if (isset($PSS["admin_enable"]) && $PSS["admin_enable"] = true) {

  if (isset($_GET["pss_sid"]) && trim ($_GET["pss_sid"]) != '') {

    session_id($_GET["pss_sid"]);
    //echo $_GET["pss_sid"]."\n";

  }

  session_start();

}

//echo session_id();

//debug($_SESSION);

?>