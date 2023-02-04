<?php
require_once "robot_settings.php";
require_once "utils/system_utils.php";

// ssh -i ~/.ssh/robot -t sleipner@www.airplaymusic.dk
//  scp -i ~/.ssh/robot /home/ml/temp/ExNavigatorAndSelects.xml.gz  sleipner@www.airplaymusic.dk:/home/sleipner/temp

/** Poor mans php enum with C++ crawler status codes. Corresponds the values written from c++ crawler to 
the crawler status file. */
class MiningStatusEnum
{
    public static function miningActiveE                    () { return (int)0; }
    public static function miningDoneScriptDoneE            () { return (int)1; }
    public static function miningDoneMaxPageLoadsReachedE   () { return (int)2; }
    public static function miningDoneUserExitE              () { return (int)3; }
    public static function miningDoneCrawlerKilledE         () { return (int)4; }
    public static function miningDoneCrawlerCrashedE        () { return (int)5; }
    public static function miningDoneUserStopE              () { return (int)6; }
    public static function miningContinueE                  () { return (int)7; }
    public static function miningContinueCrashedE           () { return (int)8; }
    public static function miningContinueKilledE            () { return (int)9; }
}


/**
Base class for handling the execution and status file reading of a robot.
*/
abstract class RobotJobHandlerBase
{

    // -------------------------
    // --- PUBLIC: Functions ---	
    // -------------------------
    function __construct($robots_base_dir, $robot_name, $kill_timeout_in_seconds, $max_continues, $crawler_exe_path) {
        $this->m_robots_base_dir = $robots_base_dir;
        $this->m_robot_name = $robot_name;
        $this->m_kill_timeout_in_seconds = $kill_timeout_in_seconds;
        $this->m_max_continues = $max_continues;
        $this->m_crawler_exe_path = $crawler_exe_path;
        $this->m_robot_dir = $this->m_robots_base_dir . "/" . $this->m_robot_name;
        $this->m_status_file_path = $this->robotDir() . "/Crawler.status";
        $this->m_job_params_file_path = $this->robotDir() . "/job_params.json";

        // Ensure our working directory exists
        if (!file_exists($this->m_robots_base_dir)) {
            mkdir($this->m_robots_base_dir, 0777, true);
        }
    }

    /** Read status and update/set $this->m_status array. You MUST call this function before calling any other functions. 
        It is by design that we do not call it from the constructor. The MinerRobot class, which uses this one needs to control this.     */
    public function updateStatus()
    {
        $this->m_status = $this->getStatusFile();
//        $this->m_status['job_name'] = $this->jobName(); // Ensure jobname is correct even if we just unpacked a new source TODO: xxx
    }
    
    public function robotsBaseDir   () { return $this->m_robots_base_dir; }
    public function robotName       () { return $this->m_robot_name; }
    public function robotDir        () { return $this->m_robot_dir; }
    public function statusFilePath  () { return $this->m_status_file_path; }
    public function crawlerExePath  () { return $this->m_crawler_exe_path; }
    
    
    /** Get value from the current status. Returns false if value is not found */
    public function statusValue($key)
    {
        if (array_key_exists($key , $this->m_status )) return $this->m_status[$key];
        return false;
    }
    
    public function jobName () 
    { 
        // Use job_name from status file if present. Only if we just unpacked a new job zip file
        // will we need to get the job_name from the string saved from unPackJob.
        if ($this->haveStatusFile()) {
            $this->m_status['job_name'];
        }
        return $this->m_job_name; 
    }
	
    /** Unpack a job (zip) archive file in robotsBaseDir().
    First we delete the exsiting robotsBaseDir()/robotName() then we unpack the 
    archive in robotsBaseDir().
    The zip file is deleted afterwards.
    The resulting subdirectory is the job_name (for example wallmart.com), which 
    can be obtained afterwards with jobName()
    and rename the resulting subdirectory to robotName(). 
    
    the resulting subdirectory. */
    public function unPackJob($job_zip_file)
    {
        $this->removeRobotDirectory();
        $unpacked_dir = unzipFile($job_zip_file);
        deleteFile($job_zip_file);
        $path_parts = pathinfo($unpacked_dir);
        $this->m_job_name = $path_parts['basename'];
        rename( $unpacked_dir, $this->robotDir() ); 
    }

    /** Return true if we have robot directory. 
     * I.e. if the directory robotsBaseDir()/robotName() exists. */
    public function haveRobotDirectory()
    {
        return file_exists($this->robotDir());
    }
    
     /** Completely remove the robot directory. 
      * Robot directory is the: robotsBaseDir()/robotName() path. */
    public function removeRobotDirectory()    
    {
        $this->m_status = array();
        removeDirectory($this->robotDir());
    }
   
    
    /** Return true if we have a valid status (file). */
    public function haveStatusFile()
    {
        return file_exists($this->statusFilePath());
    }

    /** Delete miner status (file). */
    public function deleteStatusFile()    
    {
        $this->m_status = array();
        unlink($this->statusFilePath());
    }
    
    
    /** Read status (file) and return status as an associative array. */
    public function getStatusFile()
    {
        $status = array();
        $status["robot_name"] = $this->robotName();
        $status["host_name"] = hostname();
        if ($this->haveStatusFile()) {
            $status = $this->doGetMinerStatusFile();
        }
        return $status;
    }

    public function getStatus()
    {
        return $this->m_status;
    }
    

    /** Run command in robot directory. */
    public function runCommand( $cmd )
    {
        if (!$cmd) return false;
        return $this->doRunCommand($cmd);
    }

    /** Save command for start or restart of current job from scratch. 
    \param $params associative array with 'job_name', 'task_id', 'crawler_params', 'script_params'     */
    public function saveJobCmdParams($params)    
    {
        $parms = array();
        $parms["job_name"] = $params["job_name"];
        $parms["task_id"] = $params["task_id"];
        $parms["crawler_params"] = $params["crawler_params"];
        $parms["script_params"] = $params["script_params"];
        $json = json_encode($parms, JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE | JSON_UNESCAPED_SLASHES);
        file_put_contents($this->m_job_params_file_path, $json);
    }

    /** Load command for start or restart of current job from scratch. 
    \return Associative array with 'job_name', 'task_id', 'crawler_params', 'script_params' or
     * false if command parameters could not be loaded.  */
    public function loadJobCmdParams()    
    {
        $params = false;
        if (file_exists($this->m_job_params_file_path)) {
           $json = file_get_contents($this->m_job_params_file_path);
           $params = json_decode($json, true); // assoc = true
        }
        return $params;
    }
    
    /** Get command for start or restart of current job from scratch. 
    \param $params associative array with 'job_name', 'task_id', 'crawler_params', 'script_params'     */
    public function startNewJobCmd($params)    
    {
        $job_name = $params["job_name"];
        $task_id = $params["task_id"];
        $crawler_params = $params["crawler_params"];
        $script_params = $params["script_params"];
        
        $cmd = $this->crawlerExePath();
        $cmd .= " --job-name $job_name --task-id $task_id";
        $cmd .= " $crawler_params";
        $cmd .= " crawler.php";
        $cmd .= " $script_params";
        return $cmd;
    }

        
    /** Get command for continuing (start with --continue) current miner job. */
    public function continueJobCmd()    
    {
        if (!$this->haveStatusFile()) return false;
        $cmd = $this->crawlerExePath();
        $cmd .= " --continue";
        return $cmd;
    }

    /** Kill current miner job. 
    return true if job was killed or if there was no job to kill. */
    public function killJob()
    {
        if (!$this->haveStatusFile()) return true;
        $running = $this->jobRunning();
        for ($n = 0 ; $n < 3; $n++ ) {
            if ($running) {
                $this->doKillJob();
                sleep($this->m_kill_sleep_in_seconds);
                $running = $this->jobRunning();
            }
            else break;
        }
        
        return !$running;
    }

    public function jobRunning()
    {
        if (!$this->haveStatusFile()) return false;
        return $this->doJobRunning();
    }
    
    //----
    
    public function secondsSinceLastPageLoad()
    {
        if ( !$this->haveStatusFile() ) return 10000000; // Some large numer

        date_default_timezone_set('UTC');

        $sTime = $this->m_status["latest_loaded_time_iso"];
        
        $imestamp = 0;
        if (($timestamp = strtotime($sTime)) !== false) {
            
        }
        ////echo "$sTime == " . date('l dS \o\f F Y h:i:s A', $timestamp) . "\n";

        return time() - $timestamp;
    }
    
    /** Returns true if timeout is reached and script process is still running.
        The timeout is how many seconds has passes since last full page load completed. */
    public function timeOutReached()
    {
        if (!$this->jobRunning()) return false;
        $timeout_reached = false;
        if ( $this->secondsSinceLastPageLoad() > $this->m_kill_timeout_in_seconds ) {
            $timeout_reached = true;
        }
        return $timeout_reached;
    }
 
    public function jobCrashed()
    {
        $crashed = false;
        if ( !$this->jobRunning() && $this->haveStatusFile() ) {
            $crashed = $this->m_status["mining_done"] == MiningStatusEnum::miningActiveE();
        }
        return $crashed;
    }
    
    public function canContinue()
    {
        $can_continue = false;
        $continue_counter = $this->statusValue('continue_counter');
        if ( $continue_counter !== false ) {
            $can_continue = $continue_counter <= $this->m_max_continues;
        }
        return $can_continue;
    }
 
    // --- Protected abstract functions to override in derived classes.

    /** Read miner status (file) and return status as an associative array. */
    abstract protected function doGetMinerStatusFile();
    
    /** Run command in specified directory. */
    abstract protected function doRunCommand( $cmd );

    /** Kill current miner job. */
    abstract protected function doKillJob();
        
    /** Check if current job is running. */
    abstract protected function doJobRunning();
        
        
    public function killSleepTimeSet($kill_sleep_in_seconds) 
    {
        $this->m_kill_sleep_in_seconds = $kill_sleep_in_seconds;
    }
    
    // ------------------------------
    // --- PROTECTED: Member data ---	
    // ------------------------------
    protected $m_robots_base_dir;
    protected $m_robot_name;
    protected $m_robot_dir;
    protected $m_status_file_path;
    protected $m_status = array();
    // --- PRIVATE: Member data ---
    private $m_job_name = "";
    private $m_job_params_file_path;
    private $m_kill_sleep_in_seconds = 2;

    // ------------------------
    // --- DEBUG: Functions ---	
    // ------------------------
}


?>

