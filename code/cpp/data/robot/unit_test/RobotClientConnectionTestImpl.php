<?php
require_once "robot_settings.php";
require_once "utils/system_utils.php";
require_once "RobotClientConnectionBase.php";

/**

For unit test of robot.
*/
class RobotClientConnectionTestImpl extends RobotClientConnectionBase
{
    // ---------------------------
    // --- PUBLIC: Member data ---	
    // ---------------------------
    public  $m_server_response = array(); // Array with server response
    //
    // ----------------------------
    // --- PUBLIC: Functions ---	
    // ----------------------------
    function __construct($robot_name, $server_url)
    {
        parent::__construct($robot_name, $server_url);
    }
    
    public function setEmptyServerResponse()
    {
        $this->m_server_response = array();
    }

    // -----------------------------------------------------
    // --- PROTECTED: Abstract functions overridden here ---
    // -----------------------------------------------------
	
    /** Send data to server as params_array and get array back as response. Argument is an array of key=>value pairs.
    \return Command array from server. If all is ok return_array['error'] == ''.
    */
    protected function doSendGetFromServer($request_url)
    {
//        echo "ML_DBG, request_url: " . $request_url . "\n";
        return $this->m_server_response; 
    }

    /** Download file to designated directory.
    \return true id download was successfull.
    */
    function doDownloadFile($file_url, $dst_dir)
    {
        return copyToDir($file_url, $dst_dir);
    }

		
	// ----------------------------
	// --- PRIVATE: Functions ---	
	// ----------------------------
	

	
}


?>

