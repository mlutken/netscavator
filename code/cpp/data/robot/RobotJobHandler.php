<?php
require_once "robot_settings.php";
require_once "utils/system_utils.php";
require_once "RobotJobHandlerBase.php";

/**
Handles and executes the robot jobs.
*/
class RobotJobHandler extends RobotJobHandlerBase
{
	// ----------------------------
	// --- PUBLIC: Functions ---	
	// ----------------------------
	function __construct( $robots_base_dir, $robot_name, $kill_timeout_in_seconds, $max_continues, $crawler_exe_path )
	{
        parent::__construct( $robots_base_dir, $robot_name, $kill_timeout_in_seconds, $max_continues, $crawler_exe_path );
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
        return shellExecute ( $cmd, $this->robotDir() );
    }
        
    /** Kill current miner job. */
    public function doKillJob()
    {
        return processForceKill( $this->m_status["process_id"] );
    }

    /** Check if current job is running. */
    public function doJobRunning()
    {
        $running = false;
        if ( $this->haveStatusFile() ) {
            $running = processRunning( $this->m_status["process_id"] );
        }
        return $running;
    }
	
	
	// ----------------------------
	// --- PRIVATE: Member data ---	
	// ----------------------------
	
}


?>

