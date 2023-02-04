<?php
require_once "robot_settings.php";
require_once "utils/system_utils.php";
require_once "RobotJobHandlerBase.php";

/**
Handles and executes the robot jobs.
*/
class RobotJobHandlerTestImpl extends RobotJobHandlerBase
{
    public  $m_job_running = false;
    
    // ----------------------------
    // --- PUBLIC: Functions ---	
    // ----------------------------
    function __construct( $robots_base_dir, $robot_name, $kill_timeout_in_seconds, $max_continues, $crawler_exe_path )
    {
        parent::__construct( $robots_base_dir, $robot_name, $kill_timeout_in_seconds, $max_continues, $crawler_exe_path );
    }

    public function jobRunningSet($job_running)
    {
        $this->m_job_running = $job_running;
    }
		
    // -----------------------------------------------------
    // --- PROTECTED: Abstract functions overridden here ---
    // -----------------------------------------------------

    /** Read miner status (file) and return status as an associative array. */
    public function doGetMinerStatusFile()
    {
        return loadSimpleXmlFileToArray($this->statusFilePath());
    }
        
    /** Run command in specified directory. */
    public function doRunCommand( $cmd )
    {
//         printf ("UNIT_TEST_INFO, doRunCommand: $cmd, %s\n", $this->robotDir() );
    }
        
    /** Kill current miner job. */
    public function doKillJob()
    {
        $this->m_job_running = false;
    }

    /** Check if current job is running. */
    public function doJobRunning()
    {
        return $this->m_job_running;
    }
	
	
	// ----------------------------
	// --- PRIVATE: Member data ---	
	// ----------------------------
	
}


?>

