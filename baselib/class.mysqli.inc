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
		$this->con = mysqli_connect($PSS["db_server"], $PSS["db_user"], $PSS["db_password"]); 
	}
	
	function selectDB($sString) {
		mysqli_select_db($this->con, $sString);
	}
	
	function query($sString) {
		return mysqli_query($this->con, $sString);
	}
	
	function fetchArray($sel) {
		return mysqli_fetch_array($sel);
	}
	
	function freeResult($sel) {
		mysqli_free_result($sel);
	}
	
	function commit() {
		return true;
	}
	
	function getLastInsertID()	{
		return mysqli_insert_id($this->con);
	}
	
	function numRows($sel) {
		return mysqli_num_rows($sel);
	}
	
	function error() {
		return mysqli_error($this->con);
	}
	
	function close()	{
		@mysqli_close($this->con);
		$this->con =	NULL;
	}
}



?>
