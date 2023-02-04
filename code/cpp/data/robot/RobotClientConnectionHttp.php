<?php
require_once "robot_settings.php";
require_once "utils/system_utils.php";
require_once "RobotClientConnectionBase.php";

// ssh -i ~/.ssh/robot -t sleipner@www.airplaymusic.dk
//  scp -i ~/.ssh/robot /home/ml/temp/ExNavigatorAndSelects.xml.gz  sleipner@www.airplaymusic.dk:/home/sleipner/temp
/**

The client endpoint of a job scheduler connection. 

This class communication with the job server getting and sending the commands and status info. 
*/
class RobotClientConnectionHttp extends RobotClientConnectionBase
{
    // ----------------------------
    // --- PUBLIC: Functions ---	
    // ----------------------------
    function __construct($robot_name, $server_url)
    {
        parent::__construct($robot_name, $server_url);
    }

    // -----------------------------------------------------
    // --- PROTECTED: Abstract functions overridden here ---
    // -----------------------------------------------------
	
    /** Send data to server as params_array and get array back as response. Argument is an array of key=>value pairs.
    \return Command array from server. If all is ok return_array['error'] == ''.
    */
    protected function doSendGetFromServer($request_url)
    {
        $json = file_get_contents( $request_url );
        return json_decode ($json, true); // assoc = true
    }

    /** Download file to designated directory.
    \return true id download was successfull.
    */
    function doDownloadFile($file_url, $dst_dir)
    {
        return downloadFile($file_url, $dst_dir);
    }

		
	// ----------------------------
	// --- PRIVATE: Functions ---	
	// ----------------------------
	

	// ----------------------------
	// --- PRIVATE: Member data ---	
	// ----------------------------
	
}


?>

