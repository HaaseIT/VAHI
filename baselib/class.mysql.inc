<?php
// $Id: class.mysql.inc,v 1.2 2007/05/22 12:28:00 mhaase Exp $
// -----------------------------------------------------------------------------
//                                                                            --
// Pryde Site Suite                                                           --
// class MySql                                                                --
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
		$this->con = mysql_connect($PSS["db_server"], $PSS["db_user"], $PSS["db_password"]); 
	}
	
	function selectDB($sString) {
		mysql_select_db($sString, $this->con);
	}
	
	function query($sString) {
		return mysql_query($sString, $this->con);
	}
	
	function fetchArray($sel) {
		return mysql_fetch_array($sel);
	}
	
	function freeResult($sel) {
		mysql_free_result($sel);
	}
	
	function commit() {
		return true;
	}
	
	function getLastInsertID()	{
		return mysql_insert_id($this->con);
	}
	
	function numRows($sel) {
		return mysql_num_rows($sel);
	}
	
	function error() {
		return mysql_error($this->con);
	}
	
	function close()	{
		@mysql_close($this->con);
		$this->con =	NULL;
	}
}



?>
