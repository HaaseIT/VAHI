<?php
// $Id: functions.image.inc,v 1.2 2007/05/22 12:26:34 mhaase Exp $
// -----------------------------------------------------------------------------
//                                                                            --
// Pryde Site Suite                                                           --
// functions.image.inc                                                        --
//                                                                            --
// copyright: Marcus Haase (mail@marcus.haase.name)                           --
// The use of this Script is only allowed with the author's authorisation     --
// Any modification of the sources is strictly forbidden                      --
//                                                                            --
// -----------------------------------------------------------------------------


function PSS_ResizeImage($image, $newimage, $newwidth, $newheight) {
  global $PSS, $iResizes;

	//$image = $image;
	//$newimage = $newimage;

	$aImagedata = GetImageSize($image);

	if ($aImagedata[2] == 1) { // gif

		$img_old = imagecreatefromgif($image);
		$img_new = imagecreate($newwidth, $newheight);
		imagecopyresampled($img_new, $img_old, 0, 0, 0, 0, $newwidth, $newheight, $aImagedata[0], $aImagedata[1]);
		imagedestroy($img_old);
		imagegif($img_new, $newimage);
		imagedestroy($img_new);

	} elseif ($aImagedata[2] == 2) { // jpg

		$img_old = imagecreatefromjpeg($image);
		$img_new = imagecreatetruecolor($newwidth, $newheight);
		imagecopyresampled($img_new, $img_old, 0, 0, 0, 0, $newwidth, $newheight, $aImagedata[0], $aImagedata[1]);
		imagedestroy($img_old);
		imagejpeg($img_new, $newimage, $PSS["image_quality"]);
		imagedestroy($img_new);

	} elseif ($aImagedata[2] == 3) { // png

		$img_old = imagecreatefrompng($image);
		$img_new = imagecreatetruecolor($newwidth, $newheight);
		imagecopyresampled($img_new, $img_old, 0, 0, 0, 0, $newwidth, $newheight, $aImagedata[0], $aImagedata[1]);
		imagedestroy($img_old);
		imagepng($img_new, $newimage);
		imagedestroy($img_new);

	}

	if(!isset($iResizes)) $iResizes = 1;
	else $iResizes++;

	if ($PSS["linux_chmod_generated"] && (!isset($_ENV["OS"]) || strtolower(substr($_ENV["OS"], 0, 3)) != 'win')) chmod($newimage, 0777);

  return file_exists($newimage);

}

?>