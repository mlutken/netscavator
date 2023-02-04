<?php

require_once "utils/system_utils.php";
require_once "RobotJobHandler.php";
require_once "RobotClientConnectionHttp.php";


// ssh -i ~/.ssh/robot -t sleipner@www.airplaymusic.dk
//  scp -i ~/.ssh/robot /home/ml/temp/ExNavigatorAndSelects.xml.gz  sleipner@www.airplaymusic.dk:/home/sleipner/temp
/**

  \important This is the 'new' and actively maintained version of 'CrawlerRobot', which is now only used in AirplayMusic.
  This class MinerRobot is the one we are using (february 2015).

"Robot Actions":
 * "get-task"
 * ""

 */
class MinerRobot {
    // -------------------------
    // --- PUBLIC: Functions ---	
    // -------------------------

    /** Construct MinerRobot from a job_handler (RobotJobHandlerBase) and a connection 
      (RobotClientConnectionBase).
      \sa MinerRobot::createDefault() */
    function __construct($job_handler, $connection) {
        $this->m_job_handler = $job_handler;
        $this->m_connection = $connection;

//        $this->readStatusFile();
    }

    /** Create default MinerRobot for use with a real server in the other end. 
      Alternatively, one can call createForUnitTest for unit test uses. */
    static function createDefault($robots_base_dir, $robot_name, $kill_timeout_in_seconds, $max_continues, $crawler_exe_path, $server_url) {
        $job_handler    = new RobotJobHandler($robots_base_dir, $robot_name, $kill_timeout_in_seconds, $max_continues, $crawler_exe_path);
        $connection     = new RobotClientConnectionHttp($robot_name, $server_url);
        $miner_robot    = new MinerRobot($job_handler, $connection);
        return $miner_robot;
    }

    
    public function run() 
    {
        $status = $this->getRobotStatus();
        $this->handleRobotStatus($status["robot_status"]);
        return $status;
    }

    public function getRobotStatus() 
    {
        $status = $this->updateFromStatusFile();
        $status["robot_status"] = $this->getJobStatus($status);
        $server_response = $this->sendStatusGetCommand($status);
        //echo "OUT: robot status:\n";print_r($status);
        $status = $this->updateRobotStatusWithServerResponse($status, $server_response);
        return $status;
    }
    

    /** Get job status as a string. */
    public function getJobStatus($crawler_status) 
    {
        $can_continue = $this->m_job_handler->canContinue();
        $robot_status = "statusUnknownE";
        
        // -----------------------------------------
        // --- Job IS running. (has status file) ---
        // -----------------------------------------
        if ($this->m_job_handler->jobRunning()) {
            if ($this->m_job_handler->timeOutReached() ) {
                $robot_status = "killTimeOutReachedE";
            }
            else $robot_status = "runningNormallyE";
            return $robot_status;
        }

        // ---------------------------
        // --- Job is NOT running! ---
        // ---------------------------

        // No status file or no robot directory
        if (!$this->m_job_handler->haveStatusFile()) {
            $robot_status = "newJobE";
            if ($this->m_job_handler->haveRobotDirectory()) {
                $job_params = $this->m_job_handler->loadJobCmdParams();
                if ($job_params != false) {
                    $robot_status = "restartJobE";
                }
            }
            return $robot_status;
        }
        else {
            // HAS status file
            $mining_done_enum = (int)$crawler_status['mining_done'];

            // Normal exit or crashed/killed!
            if ($this->m_job_handler->jobCrashed()) {
                if ($can_continue)  $robot_status = "crashedContinueE";
                else                $robot_status = "crashedNewJobE";
            }
            else if (MiningStatusEnum::miningDoneScriptDoneE() == $mining_done_enum) {
                $robot_status = "miningDoneScriptDoneE";
            }
            else if (MiningStatusEnum::miningDoneMaxPageLoadsReachedE() == $mining_done_enum) {
                $robot_status = "miningDoneMaxPageLoadsReachedE";
            }
            else if (MiningStatusEnum::miningDoneUserExitE() == $mining_done_enum) {
                $robot_status = "miningDoneUserExitE";
            }
            else if (MiningStatusEnum::miningDoneUserStopE() == $mining_done_enum) {
                $robot_status = "miningDoneUserStopE";
            }
        }
        return $robot_status;
    }
    
    
    /** Update the locally found robot_status with possible request from server. */
    public function updateRobotStatusWithServerResponse($status, $server_response) 
    {
        if (array_key_exists("task_robot_command", $server_response)) {
            $task_robot_command = $server_response["task_robot_command"];
            if ($task_robot_command != "") $status["robot_status"] = $task_robot_command; // Current possible commands are: '', 'serverForceKillContinueE', 'serverForceRestartE', 'serverForceNewJobE'
        }
        return $status;
    }

    
    
    /** Execute action according to the robot_status.
    Supported server commands: 'serverForceKillContinueE', 'serverForceRestartE', 'serverForceNewJobE'
    */
    public function handleRobotStatus($robot_status) 
    {
        switch ($robot_status)
        {
            case "newJobE":
            case "crashedNewJobE":
                $job_params = $this->m_connection->getNewJob();
                //echo "OUT: job_params:\n";print_r($job_params);
                $file_url = $job_params["file_url"];
                $dst_dir = $this->m_job_handler->robotsBaseDir();
                $job_zip_file = $this->m_connection->downloadFile($file_url, $dst_dir);
                
                $this->m_job_handler->unPackJob($job_zip_file);
                $this->m_job_handler->saveJobCmdParams($job_params); // Save params in case restart from server is requested!
                $this->m_crawler_command = $this->m_job_handler->startNewJobCmd($job_params);
                $this->m_job_handler->runCommand($this->m_crawler_command);
                break;
            case "restartJobE":
                $job_params = $this->m_job_handler->loadJobCmdParams();
                $this->m_crawler_command = $this->m_job_handler->startNewJobCmd($job_params);
                $this->m_job_handler->runCommand($this->m_crawler_command);
                break;
            case "crashedContinueE":
                $this->m_crawler_command = $this->m_job_handler->continueJobCmd();
                $this->m_job_handler->runCommand($this->m_crawler_command);
                break;
            case "killTimeOutReachedE":
            case "serverForceKillContinueE":
                $this->m_job_handler->killJob();
                break;
            case "serverForceRestartE":
                $this->m_job_handler->killJob();
                $this->m_job_handler->deleteStatusFile();
                break;
            case "serverForceNewJobE":
                $this->m_job_handler->killJob();
                $this->m_job_handler->removeRobotDirectory();
                break;
            case "miningDoneScriptDoneE":
            case "miningDoneMaxPageLoadsReachedE":
            case "miningDoneUserExitE":
            case "miningDoneUserStopE":
            case "statusUnknownE":
                $this->m_job_handler->removeRobotDirectory();
                break;

            default:    // runningNormallyE
                break;
        }
        
    }
    public function robotDir                () { return $this->m_job_handler->robotDir(); }
    public function removeRobotDirectory    () { return $this->m_job_handler->removeRobotDirectory(); }
    public function lastCrawlerCommand      () { return $this->m_crawler_command; }
    public function getLatestRequestUrl     () { return $this->m_connection->getLatestRequestUrl(); }
   
    public function updateFromStatusFile()
    {
        $this->m_job_handler->updateStatus();
        $status = $this->m_job_handler->getStatus();
        return $status;
    }


    public function sendStatusGetCommand($status)
    {
        return $this->m_connection->sendStatusGetCommand($status);;
    }
    
    
    // ----------------------------
    // --- PRIVATE: Member data ---	
    // ----------------------------
    private $m_job_handler;
    private $m_connection;
    
    private $m_crawler_command = "";

    // ------------------------
    // --- DEBUG: Functions ---	
    // ------------------------
}
