<?php

/** 
Non-recursive copy of files from one directory to another. 
If destination directory does not exists it is created.

\example
copyToDir('./test/foo/*.txt', './test/bar'); // copies all txt files
\endexample
*/
function copyToDir($source_pattern, $dst_dir)
{
    $ok = true;
    if (!file_exists($dst_dir)) {
        mkdir($dst_dir);
    }
    foreach (glob($source_pattern) as $file) {
        if(!is_dir($file) && is_readable($file)) {
            $dest = realpath($dst_dir) . DIRECTORY_SEPARATOR . basename($file);
            $cp_ok = copy($file, $dest);
            $ok = $ok && $cp_ok;
        }
    }
    return $ok;
}



/** Recursively delete a directory. If directory does not exists the function will do nothing and return true.
*/
function deleteDirectory($dir)
{
    if (!file_exists($dir)) return true;
    $result = false;
    if ($handle = opendir("$dir")){
        $result = true;
        while ((($file=readdir($handle))!==false) && ($result)){
            if ($file!='.' && $file!='..'){
                if (is_dir("$dir/$file")){
                    $result = deleteDirectory("$dir/$file");
                } else {
                    $result = unlink("$dir/$file");
                }
            }
        }
        closedir($handle);
        if ($result){
            $result = rmdir($dir);
        }
    }
    return $result;
}


/** Delete a file. If file does not exists the function will do nothing and return true.
*/
function deleteFile($file_path)
{
    if (!file_exists($file_path)) return true;
    return unlink($file_path);
}

/** Create a zip file from a directory. Command works recursively. */
function zipDirectory($dir_to_zip)
{
    $zip_file_path = $dir_to_zip . '.zip';
    $zip_basename = basename($dir_to_zip);
    $parent_dir = dirname($dir_to_zip);
    $cmd = "cd $parent_dir && zip -r $zip_basename.zip $zip_basename && cd -";
    printf ("ML_DBG, CMD:\n$cmd\n");
    exec($cmd);
    printf ("ML_DBG, zip_file_path:$zip_file_path\n");
    return file_exists($zip_file_path);
}


/** Launch an executable/script and just forget about it. I.e. don't wait for the launched 
program to finish, but continue with php script. */
function launchProcess ( $fullCmdLine )
{
    exec("{$fullCmdLine} >Crawler.out 2>&1 &");
}

/** Force kill a process. */
function processForceKill ( $processID )
{
    $ret = shell_exec("/bin/kill -9 ${processID} >/dev/null 2>&1");
    return $ret;
}


/** Test if process with ID \a $processID is runnning. */
function processRunning ( $processID )
{
    $ret = shell_exec("./processIDRunning.sh ${processID}");
    if ( $ret == 0 )    return false;
    else                return true;
}

/** Get computer-/hostname. */
function hostname ()
{
    $ret = shell_exec("hostname");
    //$ret = "vaio";
    return trim($ret);
}


/** Get computer-/hostname. */
function systemHostname ()
{
    $ret = shell_exec("hostname");
    //$ret = "vaio";
    return trim($ret);
}

/** Execute a command in directory. */
function shellExecute ( $cmd, $dir )
{
    $cmds = "cd $dir && $cmd >/tmp/shellExecute_output.txt 2>&1";
//    $ret = shell_exec($cmds);
    $output = array();
    $exit_code;
    exec ( $cmds ,$output , $exit_code );
    return (int)$exit_code == 0;
}


/** Converts a simple one level deep xml string to an array. */
function simple_xml_string_to_array ( $sXml )
{
    $a = simplexml_load_string( $sXml );

    $aXml = array();
    foreach ( $a as $key => $val ) {
        $aXml[$key] = $val;
    }
    return $aXml;
}


/** Remove designated directory.
*/
function removeDirectory($dir_path)
{
    if (!file_exists($dir_path)) return true;
    $cmd = "rm -rf $dir_path";
    return shellExecute ( $cmd, ".");
}


/** Download file to designated directory.
\return true if download was successfull.
*/
function downloadFile($file_url, $dst_dir)
{
    $cmd = "wget $file_url";
    return shellExecute ( $cmd, $dst_dir );
}


/** Unzip file.
\return Path to directory containing the unpacked files if successfull, otherwise false.
*/
function unzipFile($file_path)
{
    $retval = false;
    $path_parts = pathinfo($file_path);
    $leaf_filename = $path_parts['basename'];
    $leaf_barename = $path_parts['filename'];
    $dir = $path_parts['dirname'];

    $cmd = "unzip -o $leaf_filename";
    $ok = shellExecute ( $cmd, $dir );
    if ($ok) $retval =  "$dir/$leaf_barename";

    return $retval;
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

/** Convert xml to array. Not that atributes will be lost, so only simple xmls will work. */
function xmlToArray ( $xml_object, $out = array () )
{
    foreach ( (array) $xml_object as $index => $node ) {
        $out[$index] = ( is_object ( $node ) ) ? xmlToArray( $node ) : $node;
    }

    return $out;
}

function loadSimpleXmlFileToArray($xmlfile_path)
{
    $xml_object = simplexml_load_file( $xmlfile_path );
    return xmlToArray($xml_object);
}


/** Convert xml to array. Not that atributes will be lost, so only simple xmls will work. */
function arrayToXmlString ( $array, $xml_out = "" )
{
    foreach ( $array as $key => $val ) {
        if (is_array($val)) $xml_out = arrayToXmlString ($val);
        $xml_out .= "<$key>$val</$key>\n";
    }
    return $xml_out;
}

function writeArrayToXml($array, $xmlfile_path)
{
    $xml_out = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    $xml_out .= "<root>\n";
    $xml_out .= arrayToXmlString( $array );
    $xml_out .= "</root>\n";
    return file_put_contents($xmlfile_path, $xml_out);
}
