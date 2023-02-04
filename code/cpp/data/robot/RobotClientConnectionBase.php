<?php
require_once "robot_settings.php";
require_once "utils/system_utils.php";

// ssh -i ~/.ssh/robot -t sleipner@www.airplaymusic.dk
//  scp -i ~/.ssh/robot /home/ml/temp/ExNavigatorAndSelects.xml.gz  sleipner@www.airplaymusic.dk:/home/sleipner/temp
/**

The client endpoint of a job scheduler connection. The real used one is implemented in 
RobotClientConnectionHttp and a ClientConnection for unit testing/debugging is found in 
RobotClientConnectionLocalTest

This class (or a derived) handles communication with the job server getting and sending the commands and status info. 
*/
abstract class RobotClientConnectionBase
{
	// ----------------------------
	// --- PUBLIC: Functions ---	
	// ----------------------------
	function __construct($robot_name, $server_url)
	{
		$this->m_robot_name			= $robot_name;
		$this->m_server_url			= $server_url;
		$this->m_latest_request_url	= "";
	}

	// --- Public interface functions ---

    /** Send status to server. Argument is an array of key=>value pairs with status.
    \return Command response array from server. If all is ok return_array['error'] == ''.
    */
    public function sendStatusGetCommand($params_array)
    {
		$params = array();
        $params['request'] = 'get-command';
        $params['host_name'] = hostname();
        $params['robot_name'] = $this->m_robot_name;
		foreach ( $params_array as $key => $val ) {
            if ( RobotClientConnectionBase::includeStatusField($key)) {
//             if ( RobotClientConnectionBase::includeStatusField($key) && $val != "" ) { TODO: Should we use like this instead ?
				$params[$key] = $val; 
			}
		}
       
        $request_url = $this->getRequestUrl($params);
        //urlencode
        
        $this->m_latest_request_url = $request_url;
//        echo "ML_DBG, request_url: " . $this->m_latest_request_url . "\n";
        
        return $this->doSendGetFromServer($request_url);
    }
	
    /** Get new job from server. The array returned will contain a job_zip_url, where 
    the actual zip file containing the scripts and it's helper files can be downloaded from.
     * It will also contain a leat these fields in the returned array:
     * 'job_name', 'task_id', 'crawler_params', 'script_params'
    \return New job description array from server. If all is ok return_array['error'] == ''.
    */
    public function getNewJob()
    {
        $params['request'] = 'get-task';
        $params['host_name'] = hostname();
        $params['robot_name'] = $this->m_robot_name;
        $request_url = $this->getRequestUrl($params);
        $this->m_latest_request_url = $request_url;
//        echo "ML_DBG, request_url: " . $this->m_latest_request_url . "\n";
        return $this->doSendGetFromServer($request_url);
    }
	
    /** Download (zip) file to designated directory.
    \return Path to downloaded file or emty string if failed.
    */
    public function downloadFile($file_url, $dst_dir)
    {
 //       printf("ML_DBG, RobotClientConnectionBase::downloadFile ('$file_url', '$dst_dir')\n");
        if (!$this->doDownloadFile($file_url, $dst_dir)) {
            return "";
        }
        return $dst_dir . "/" . basename($file_url);
    }
	
    public function getLatestRequestUrl()
    {
        return $this->m_latest_request_url;
    }

    	// --- Protected abstract functions to override in derived classes.
	
    /** Send data to server as params_array and get array back as response. Argument is an array of key=>value pairs.
    \return Command array from server. If all is ok return_array['error'] == ''.
    */
    abstract protected function doSendGetFromServer($params_array);

    /** Download file to designated directory.
    \return true id download was successfull.
    */
    abstract protected function doDownloadFile($file_url, $dst_dir);
	// ----------------------------
	// --- PRIVATE: Functions ---	
	// ----------------------------
	private function getRequestUrl($params_array)
	{
        // Create URL
        $request_url = $this->m_server_url . "/jobs.php?" ;
        $i = 0;
        foreach ( $params_array as $key => $val ) {
                if ( $i > 0 ) $request_url .= "&"; 
                $request_url .= $key . "=" . urlencode($val);
                $i = $i + 1;
        }
        return $request_url;
	}
	
	
	/** Should we include a status field from status message to server? 
	List of fields that we currently do NOT exclude:
	job_name, task_id, host_name, robot_name, process_id, script_name, 
	- mining_done, nav_current_state_indices, nav_current_state_string
	- nav_current_state_index, nav_num_states, nav_last_state_index
	- total_pages_loaded, mining_started_time_iso, mining_started_time_ext_iso
	- current_url, latest_loaded_url, latest_loaded_time_iso, latest_loaded_time_ext_iso
	- continue_counter
	NOTE: The reason we are not just making a positive list of the fields we want is 
	that the script (typically the template) could add extra fields that this generic 
	Robot script can not possibly know about. We do not want these script/template added 
	status fields to not be sent.	
	*/
	private static function includeStatusField( $field )
	{
		static $aExcludeFields = array(
			  "script_path", "script_params", "cfg-path", "run-mode"
			, "php-ini-path", "resource-dir", "exit-when-done", "upload-handler"
			, "no-net-activity-timeout", "no-net-activity-handling"
            , "show-output", "output-name", "max-pageloads"
			, "win-width", "win-height"
		);
		
		if ( in_array( $field, $aExcludeFields) ) return false;
		return true;
	}
	
	// ----------------------------
	// --- PRIVATE: Member data ---	
	// ----------------------------
	private	$m_robot_name;
	private $m_server_url;
    private $m_latest_request_url;
}


?>

