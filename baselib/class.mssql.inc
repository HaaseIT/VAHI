<?php
// $Id: class.mssql.inc,v 1.2 2007/05/22 12:28:00 mhaase Exp $
// -----------------------------------------------------------------------------
//                                                                            --
// Pryde Site Suite                                                           --
// class MSSql                                                                --
//                                                                            --
// copyright: Marcus Haase (mail@marcus.haase.name)                           --
// The use of this Script is only allowed with the author's authorisation     --
// Any modification of the sources is strictly forbidden                      --
//                                                                            --
// -----------------------------------------------------------------------------


// Abgewandelte version für PSS!!

class DB {
	
	var $con;
	
	function DB() {
		global $PSS;
		$this->con = mssql_connect($PSS["db_server"], $PSS["db_user"], $PSS["db_password"]); 
	}
	
	function selectDB($sString) {
		mssql_select_db($sString, $this->con);
	}
	
	function query($sString) {
		return mssql_query($sString, $this->con);
	}
	
	function fetchArray($sel) {
		return mssql_fetch_array($sel);
	}
	
	function freeResult($sel) {
		mssql_free_result($sel);
	}
	
	function commit() {
		return true;
	}
	
	function getLastInsertID()	{
		$hId = $this->query("SELECT @@identity as 'last_new_id'");
		$rId = $this->fetchArray($hId);
		$iId = $rId["last_new_id"];
		
		return $iId;
	}
	
	function numRows($sel) {
		return mssql_num_rows($sel);
	}
	
	function error() {
		return true;
	}
	
	function close()	{
		@mssql_close($this->con);
		$this->con = NULL;
	}
}



?>
