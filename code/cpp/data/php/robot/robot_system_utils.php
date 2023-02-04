<?php

/** Launch an executable/script and just forget about it. I.e. don't wait for the launched 
program to finish, but continue with php script. */
function launchProcess ( $fullCmdLine )
{

}

/**
POST file to server. 
\param $sUploadedFileName Should contain the name the file should have on 
the server in the $_FILES[$sUploadedFileName] variable. 
\param $sLocalFileToUpload Full path of the actual local file to upload.
*/
function curlPostFile( $serverUrl, $sUploadedFileName, $sLocalFileToUpload  )
{
	$ch = curl_init( $serverUrl );  
	curl_setopt($ch, CURLOPT_POSTFIELDS, array($sUploadedFileName=>"@$sLocalFileToUpload"));
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	$postResult = curl_exec($ch);
	curl_close($ch);
}

?>

