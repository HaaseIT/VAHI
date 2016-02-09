<?php
// $Id: functions.search.inc,v 1.8 2007/09/03 10:16:22 mhaase Exp $
// -----------------------------------------------------------------------------
//                                                                            --
// Pryde Site Suite                                                           --
// functions.search.inc                                                       --
//                                                                            --
// copyright: Marcus Haase (mail@marcus.haase.name)                           --
// The use of this Script is only allowed with the author's authorisation     --
// Any modification of the sources is strictly forbidden                      --
//                                                                            --
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// --                            module_search                                --
// -----------------------------------------------------------------------------

// Cleanup dead files and matches missing!!
// uncategorized keywords?

function prepareCategories($bAdminform = false) {
	global $DB, $PSS;

	$sQuery = "SELECT * FROM $PSS[db_table_categories] ORDER BY cat_order";

	$hResult = $DB->query($sQuery);

	while ($aRow = $DB->fetchArray($hResult)) {

		$aCategories[$aRow["cat_id"]]["name"] = getCategoryString($aRow["cat_id"]);
		$aCategories[$aRow["cat_id"]]["advsearch"] = $aRow["cat_advsearch"];
		$aCategories[$aRow["cat_id"]]["selectwidth"] = $aRow["cat_selectwidth"];

	}

	$DB->freeResult($hResult);

	$sQuery = "SELECT key_id, key_category FROM $PSS[db_table_keywords]";

	$hResult = $DB->query($sQuery);

	while ($aRow = $DB->fetchArray($hResult)) {

		if(isset($aCategories[$aRow["key_category"]])) {

			if ($bAdminform) {

				$aCategories[$aRow["key_category"]]["keywords"][] = array(
					"id" => $aRow["key_id"],
					"name" => getKeywordString($aRow["key_id"]),
				);

			} else {

				$sQuery = "SELECT mat_kid FROM $PSS[db_table_matches] WHERE mat_kid = '$aRow[key_id]'";
				//echo $sQuery.'<br>';
				$hSubresult = $DB->query($sQuery);

				if ($DB->numRows($hSubresult) != 0) {

					$aCategories[$aRow["key_category"]]["keywords"][] = array(
						"id" => $aRow["key_id"],
						"name" => getKeywordString($aRow["key_id"]),
					);

				} // endif numrows != 0

			} // endif bAdminform

		} // endif

	} // endwhile

  //echo debug($aCategories);

	if (isset($aCategories)) return $aCategories;

}

function prepareCategoriestree() {
	global $DB, $T, $PSS;

  if (!isset($PSS["aCategories"])) $PSS["aCategories"] = prepareCategories();

	if (is_array($PSS["aCategories"])) {

		$aCategoriestree[0] = array(
			'id' => 'all',
			'name' => $T["search_string_all"],
		);

		$aCategoriestree[0]["keywords"][] = array('id' => 'all', 'name' => $T["search_string_all"]);

		if (isset($PSS["aCategories"][3]) && count($PSS["aCategories"][3]) && isset($PSS["aCategories"][3]["keywords"]) && count($PSS["aCategories"][3]["keywords"])) {

			$aCategoriestree[0]["keywords"][0]["keywords"][0] = array('id' => 'all', 'name' => $T["search_string_all"]);

			foreach ($PSS["aCategories"][3]["keywords"] as $aValues) {

				$aCategoriestree[0]["keywords"][0]["keywords"][] = array(
					'id' => $aValues["id"],
					'name' => $aValues["name"],
				);

			}

		}

		$i = 1;
		foreach ($PSS["aCategories"][2]["keywords"] as $aValues) {

			$aCategoriestree[0]["keywords"][$i] = array(
				'id' => $aValues["id"],
				'name' => $aValues["name"],
			);

			if (isset($PSS["aCategories"][3]) && count($PSS["aCategories"][3]) && isset($PSS["aCategories"][3]["keywords"]) && count($PSS["aCategories"][3]["keywords"])) {

				$aCategoriestree[0]["keywords"][$i]["keywords"][0] = array('id' => 'all', 'name' => $T["search_string_all"]);

				foreach ($PSS["aCategories"][3]["keywords"] as $aValues1) {

			    $sQuery = "SELECT files.fil_path, files.fil_name, matches_1.mat_fid ";
			    $sQuery .= "FROM files ";
			    $sQuery .= "INNER JOIN matches AS matches_1 ON files.fil_id = matches_1.mat_fid ";
					$sQuery .= "INNER JOIN matches AS matches_2 ON matches_1.mat_fid = matches_2.mat_fid AND matches_1.mat_kid = ".$aValues["id"]." AND matches_2.mat_kid = ".$aValues1["id"]." ";
					$sQuery .= "LIMIT 0,1";
					//echo $DB->error();
					//echo '<br>'.$sQuery;
					$hResult = $DB->query($sQuery);

					if ($DB->numRows($hResult) != 0) {

						$aCategoriestree[0]["keywords"][$i]["keywords"][] = array(
							'id' => $aValues1["id"],
							'name' => $aValues1["name"],
						);

					}

				}

			}

			$i++;

		}

		//echo debug($PSS["aCategories"][1]);

		$i = 1;
		foreach ($PSS["aCategories"][1]["keywords"] as $aValues1) {
			//echo $aValues1["id"].'<br>';
			$aCategoriestree[$i] = array(
				'id' => $aValues1["id"],
				'name' => $aValues1["name"],
			);

			if (isset($PSS["aCategories"][2]) && count($PSS["aCategories"][2])) {

				$aCategoriestree[$i]["keywords"][0] = array('id' => 'all', 'name' => $T["search_string_all"]);

				if (isset($PSS["aCategories"][3]) && count($PSS["aCategories"][3]) && isset($PSS["aCategories"][3]["keywords"]) && count($PSS["aCategories"][3]["keywords"])) {

					$aCategoriestree[$i]["keywords"][0]["keywords"][0] = array('id' => 'all', 'name' => $T["search_string_all"]);
					//echo debug($aValues2);
					foreach ($PSS["aCategories"][3]["keywords"] as $aValues3) {
						//echo debug($aValues3);
				    $sQuery = "SELECT files.fil_path, files.fil_name, matches_1.mat_fid ";
				    $sQuery .= "FROM files ";
				    $sQuery .= "INNER JOIN matches AS matches_1 ON files.fil_id = matches_1.mat_fid ";
						$sQuery .= "INNER JOIN matches AS matches_2 ON matches_1.mat_fid = matches_2.mat_fid AND matches_1.mat_kid = ".$aValues1["id"]." AND matches_2.mat_kid = ".$aValues3["id"]." ";
						$sQuery .= "LIMIT 0,1";
						//echo $DB->error();
						//echo '<br>'.$sQuery;
						//echo '1: '.$aValues1["id"].' / 2: '.$aValues3["id"].'<br>';

						$hResult = $DB->query($sQuery);

						if ($DB->numRows($hResult) != 0) {

							$aCategoriestree[$i]["keywords"][0]["keywords"][] = array(
								'id' => $aValues3["id"],
								'name' => $aValues3["name"],
							);

						}

					}

				}

				$ii = 1;
				foreach ($PSS["aCategories"][2]["keywords"] as $aValues2) {

			    $sQuery = "SELECT files.fil_path, files.fil_name, matches_1.mat_fid ";
			    $sQuery .= "FROM files ";
			    $sQuery .= "INNER JOIN matches AS matches_1 ON files.fil_id = matches_1.mat_fid ";
					$sQuery .= "INNER JOIN matches AS matches_2 ON matches_1.mat_fid = matches_2.mat_fid AND matches_1.mat_kid = ".$aValues1["id"]." AND matches_2.mat_kid = ".$aValues2["id"]." ";
					$sQuery .= "LIMIT 0,1";
					//echo $sQuery.'<br>';
					$hResult = $DB->query($sQuery);

					if ($DB->numRows($hResult) != 0) {

						$aCategoriestree[$i]["keywords"][$ii] = array(
							'id' => $aValues2["id"],
							'name' => $aValues2["name"],
						);


						if (isset($PSS["aCategories"][3]) && count($PSS["aCategories"][3]) && isset($PSS["aCategories"][3]["keywords"]) && count($PSS["aCategories"][3]["keywords"])) {

							$aCategoriestree[$i]["keywords"][$ii]["keywords"][0] = array('id' => 'all', 'name' => $T["search_string_all"]);

							$iii = 1;
							foreach ($PSS["aCategories"][3]["keywords"] as $aValues4) {

						    $sQuery = "SELECT files.fil_path, files.fil_name, matches_1.mat_fid ";
						    $sQuery .= "FROM files ";
						    $sQuery .= "INNER JOIN matches AS matches_1 ON files.fil_id = matches_1.mat_fid ";
								$sQuery .= "INNER JOIN matches AS matches_2 ON matches_1.mat_fid = matches_2.mat_fid AND matches_1.mat_kid = ".$aValues1["id"]." AND matches_2.mat_kid = ".$aValues2["id"]." ";
								$sQuery .= "INNER JOIN matches AS matches_3 ON matches_1.mat_fid = matches_3.mat_fid AND matches_3.mat_kid = ".$aValues4["id"]." ";
								$sQuery .= "LIMIT 0,1";

								//echo $sQuery.'<br><br>';

								$hResult = $DB->query($sQuery);

								if ($DB->numRows($hResult) != 0) {

									$aCategoriestree[$i]["keywords"][$ii]["keywords"][$iii] = array(
										'id' => $aValues4["id"],
										'name' => $aValues4["name"],
									);

									$iii++;

								}

							}

						}

						$ii++;

					}

				}

			}

			$i++;

		}

		//echo debug($aCategoriestree);
		return $aCategoriestree;

	} else {

		return false;

	}

}

function getSelectedbytree($aCategoriestree) {

	$sKey0 = ((isset($_REQUEST["key0"])) ? $_REQUEST["key0"] : $_SESSION["aKeyword"][0]);
	$sKey1 = ((isset($_REQUEST["key1"])) ? $_REQUEST["key1"] : $_SESSION["aKeyword"][1]);

	foreach ($aCategoriestree as $aThis) {

		if ($aThis["id"] == $sKey0) {

			$i = 0;
			foreach ($aThis["keywords"] as $aSubthis) {

				if ($aSubthis["id"] == $sKey1) {

					return $i;

				} else {

					$i++;

				} // endif

			} // endforeach

		} // endif

	} // endforeach

}

function prepareJSCategoriesarray($aCategoriestree) {
	global $PSS;

  if (!isset($PSS["aCategories"])) $PSS["aCategories"] = prepareCategories();

	$sTag = '';
	$sSTag = '';

	foreach ($aCategoriestree as $aThis) {

		$sTag .= 'var children_'.$aThis["id"].' = new Array();'."\n";

		$i = 0;
		foreach ($aThis["keywords"] as $aSubthis) {

			$sTag .= 'children_'.$aThis["id"].'['.$i.'] = new list("'.$aSubthis["id"].'", "'.$aSubthis["name"].'");'."\n";

			if (isset($aSubthis["keywords"]) && count($aSubthis["keywords"]) > 1) {

				//echo 'la';

				$ii = 0;
				foreach ($aSubthis["keywords"] as $aSubsubthis) {

					$sTag .= 'children_'.$aThis["id"].'['.$i.']['.$ii.'] = new list("'.$aSubsubthis["id"].'", "'.$aSubsubthis["name"].'");'."\n";

					$ii++;

				}

			}

			$i++;

		}

		$sTag .= "\n";

	}

	return $sTag;

}

function showSearchform() {
	global $PSS, $DB, $T, $C;
	$oForm = new Form();
	$oForm->bUsestyle = true;

	if ($PSS["run_mode"] == 'embeded') {

		$oForm->sFormaction = '';

	} else {

		$oForm->sFormaction = $PSS["request"]["path"];

	}

	$oForm->sFormmethod = 'GET';

	// echo debug($_SESSION);

	$sTag = $oForm->openForm('form_search');

	if ($PSS["run_mode"] == 'embeded') {

		$sTag .= $oForm->makeHidden('pss_a', 'search');
		$sTag .= $oForm->makeHidden('pss_sid', session_id());
		$sTag .= $oForm->makeHidden('pss_d', $PSS["PSS_DIR"]);

	} else {

		$sTag .= $oForm->makeHidden('a', 'search');

	}

	$sTag .= '<table border="0" cellspacing="0" cellpadding="0"><tr>';

	$bSelectsexist = false;

  if (!isset($PSS["aCategories"])) $PSS["aCategories"] = prepareCategories();

	if ($PSS["search_byuser"]) {

		$sQuery = "SELECT usr_id, usr_name FROM $PSS[db_table_users] WHERE usr_visibility = '1'";

		$hResult = $DB->query($sQuery);

		$aUsers[] = 'all|'.$T["search_string_all"];

		while ($aRow = $DB->fetchArray($hResult)) {

			$sQuery = "SELECT * FROM $PSS[db_table_files] WHERE fil_user = '$aRow[usr_id]' LIMIT 0, 1";

			$hUserresult = $DB->query($sQuery);

			// echo debug($DB->fetchArray($hUserresult));

			if ($DB->numRows($hUserresult)) $aUsers[] = $aRow["usr_id"].'|'.$aRow["usr_name"];

		}

		$sUsersearchtag = '';

		if (count($aUsers) > 2) {

			$sUsersearchtag .= '<td class="pss_main">'.$T["search_byuser_string"].':<br>';
			$sUsersearchtag .= $oForm->makeSelect('user', $aUsers, @$_REQUEST["user"], $PSS["search_byuser_selectwidth"]);
			$sUsersearchtag .= '</td>';

			$bSelectsexist = true;

		}

		if ($PSS["search_byuser_position"] == 'left') {

			$sTag .= $sUsersearchtag;

		}

	}

	if (isset($PSS["aCategories"])) {

		$i = 0;
		foreach ($PSS["aCategories"] as $iKey => $aThiscategory) {

			if (!isset($aThiscategory["keywords"])) continue;

			$sTag .= '<td class="pss_main">'.$aThiscategory["name"].':<br>';

			$aOptions[] = 'all|'.$T["search_string_all"];

			// wenn keine keywords vorhanden FEHLERMELDUNG - muss entfernt werden!!
			foreach ($aThiscategory["keywords"] as $aKeyword) {

				$aOptions[] = $aKeyword["id"].'|'.$aKeyword["name"];

			} // endforeach (inner)

			if (isset($_REQUEST["key".$i])) $sSelected = $_REQUEST["key".$i];
			elseif (isset($_SESSION["aKeyword"][$i])) $sSelected = $_SESSION["aKeyword"][$i];
			else $sSelected = '';

			if ($iKey == 1) {

				if ($PSS["run_mode"] == 'embeded') {

					$sTag .= $oForm->makeSelect('pss_k'.$i, $aOptions, $sSelected, $aThiscategory["selectwidth"], 1, false, ' onChange="populateSelect();"');

				} else {

					$sTag .= $oForm->makeSelect('key'.$i, $aOptions, $sSelected, $aThiscategory["selectwidth"], 1, false, ' onChange="populateSelect();"');

				}

			} else {

				if ($PSS["run_mode"] == 'embeded') {

					$sTag .= $oForm->makeSelect('pss_k'.$i, $aOptions, $sSelected, $aThiscategory["selectwidth"]);

				} else {

					$sTag .= $oForm->makeSelect('key'.$i, $aOptions, $sSelected, $aThiscategory["selectwidth"]);

				}

			}

			$bSelectsexist = true;

			unset($aOptions, $sSelected);

			$sTag .= '&nbsp;</td>';

			$i++;

		} // endforeach (outer)

	} // endif isset categories

	if ($PSS["search_byuser"] && $PSS["search_byuser_position"] == 'right') {

		$sTag .= $sUsersearchtag;

	}

	$sTag .= '<td valign="bottom">'.$oForm->makeSubmit('', $T["search_submittext"], 100, 's').'</td>';

	$sTag .= '</tr>';

	if (isset($PSS["searchresults"]) && !$PSS["searchresults"]) {

		$sTag .= '<tr><td class="pss_large" colspan="3">';
		$sTag .= '<span style="color:red;"><strong>'.$T["search_noresults"].'</strong></span>';
		$sTag .= '</td></tr>';

	}

	if ($PSS["run_mode"] == 'embeded' && !isset($_GET["view"]) && isset($PSS["aCategories"])) $sTag .= '<script language="JavaScript" type="text/JavaScript"><!--'."\n".'populateSelect(true);'."\n".'//--></script>';

	$sTag .= $oForm->closeForm();
	$sTag .= '</table>';
	$sTag .= $C["global"]["hr"];

	if ($bSelectsexist) return $sTag;
}

function doSearchquery() {
	global $PSS, $iClauses, $DB;

	$bShowall = true;

	// echo debug($_SESSION["aKeyword"]);

	if (isset($_SESSION["aKeyword"])) {

		foreach ($_SESSION["aKeyword"] as $sKeyword) {

			if ($sKeyword != 'all') {

				$bShowall = false;
        $aKeywords[] = $sKeyword;

			} // endif

		} // endforeach

	} // endif isset _session akeyword

	$bOwnersearch = false;
	$sOwnerquery = '';

	if ($PSS["search_byuser"] && isset($_REQUEST["user"]) && $_REQUEST["user"] != 'all') {

		$sOwnerquery .= "WHERE fil_user = '$_REQUEST[user]' ";

		$bOwnersearch = true;

	}

	if ($bShowall) {

		$sQuery = "SELECT fil_id, fil_path, fil_name FROM $PSS[db_table_files] ";
		$sQuery .= $sOwnerquery;

	} else {

    $sQuery = "SELECT files.fil_path, files.fil_name, matches_1.mat_fid ";
    $sQuery .= "FROM files ";
    $sQuery .= "INNER JOIN matches AS matches_1 ON files.fil_id = matches_1.mat_fid ";

    $iKeywords = count($aKeywords);

    if ($iKeywords == 1) {

      $sQuery .= "WHERE matches_1.mat_kid = '".$aKeywords[0]."'";

    } else {

			$sQuery .= "INNER JOIN matches AS matches_2 ON matches_1.mat_fid = matches_2.mat_fid AND matches_1.mat_kid = ".$aKeywords[0]." AND matches_2.mat_kid = ".$aKeywords[1]." ";

      if ($iKeywords > 2) {

        for ($i = 2;$i < $iKeywords;$i++) {

          $sQuery .= "INNER JOIN matches AS matches_".($i + 1)." ON matches_1.mat_fid = matches_".($i + 1).".mat_fid AND matches_".($i + 1).".mat_kid = ".$aKeywords[$i]." ";

        }

      }

    }

  }

  //echo $sQuery;

//$sQuery .= "INNER JOIN matches AS matches_2 ON matches_1.mat_fid = matches_2.mat_fid AND matches_1.mat_kid = 19 AND matches_2.mat_kid = 5";
//$sQuery .= "INNER JOIN matches AS matches_3 ON matches_1.mat_fid = matches_3.mat_fid AND matches_3.mat_kid = 1";

  /*
		$sQuery = "SELECT ".$PSS["db_table_files"].".fil_id, ".$PSS["db_table_files"].".fil_path, ";
		$sQuery .= $PSS["db_table_files"].".fil_name, ".$PSS["db_table_keywords"].".key_id FROM ".$PSS["db_table_files"]." ";
		$sQuery .= "INNER JOIN ".$PSS["db_table_matches"]." ON ".$PSS["db_table_files"].".fil_id = ".$PSS["db_table_matches"].".mat_fid ";
		$sQuery .= "INNER JOIN ".$PSS["db_table_keywords"]." ON ".$PSS["db_table_matches"].".mat_kid = ".$PSS["db_table_keywords"].".key_id ";
		$sQuery .= $sOwnerquery;

		$iClauses = 0;

		if (!$bShowall) {

			if ($bOwnersearch) {

				$sQuery .= "AND ";

			} else {

				$sQuery .= "WHERE ";

			}

			foreach ($_SESSION["aKeyword"] as $sKeyword) {

				if ($sKeyword != 'all') {

					$sQuery .= $PSS["db_table_keywords"].".key_id = '".$sKeyword."' OR ";

					$iClauses++;

				} // endif

			} // endforeach

			$sQuery = cutStringend($sQuery, 4);

		} // endif !$bShowall

	}
	*/
	// echo debug($sQuery);

	$hResult = $DB->query($sQuery.' ORDER BY fil_name');
	//echo '<br>'.$DB->numRows($hResult);
	return $hResult;

}

function prepareSearchresults($hResult) {
	global $DB, $iClauses;

	while ($aRow = $DB->fetchArray($hResult)) {

		$aSearchresults[] = array(
			"path" => $aRow["fil_path"],
			"name" => $aRow["fil_name"],
			"id" => ((isset($aRow["mat_fid"])) ? $aRow["mat_fid"] : $aRow["fil_id"]),
		);

	} // endwhile

	if (isset($aSearchresults)) {

		$PSS["searchresults"] = true;
		unset($_SESSION["aSearchresults"]);
		$_SESSION["aSearchresults"] = $aSearchresults;
		//echo "lala";
		//debug($_SESSION);

	} else {

		$PSS["searchresults"] = false;
		unset($_SESSION["aSearchresults"]);

	}

// echo debug($aSearchresults);

	return $PSS["searchresults"];
}

?>