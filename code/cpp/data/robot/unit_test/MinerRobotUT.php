<?php

require_once ('unit_test/UnitTestBase.php');
require_once "MinerRobot.php";
require_once 'utils/system_utils.php';
require_once 'unit_test/RobotClientConnectionTestImpl.php';
require_once 'unit_test/RobotJobHandlerTestImpl.php';

global $robots_base_dir, $robot_dir, $robot_name, $kill_timeout_in_seconds, $max_continues, $crawler_exe_path, $server_url;

$robots_base_dir = __DIR__ . "/robots_base";
$robot_name = hostname() . "_1";
$robot_dir = $robots_base_dir . "/" . $robot_name;
$kill_timeout_in_seconds = 30; // NOTE: For real robots (not unit testing) we want something much larger like 1/2 - 1 hour likely.
$max_continues = 4; // NOTE: For real robots (not unit testing) we want something larger, like 30 or so.
$crawler_exe_path = __DIR__ . "/../../../build_cbs/make_release_static/crawler/crawler";
$server_url = "http://robots.mysite.com";

function tsToIsoTime($timestamp)
{
    return date("Ymd\THis", $timestamp);
}


function newJobReferenceUrl()
{
    global $robot_name, $server_url;
    $host_name = hostname();
    $url ="{$server_url}/jobs.php?request=get-task&host_name={$host_name}&robot_name={$robot_name}";
//    echo "ML_DBG, request: $url\n";
    return $url;
}

function getCommandReferenceUrl($robot_status, $crawler_status)
{
    global $robot_name, $server_url;
    $host_name = hostname();

    $crawler_status_part = ""; 
    foreach ($crawler_status as $key => $value) {
        $crawler_status_part .= "&{$key}={$value}";
    }
    
    $url ="{$server_url}/jobs.php?request=get-command&host_name={$host_name}&robot_name={$robot_name}{$crawler_status_part}&robot_status={$robot_status}";
//    echo "ML_DBG, request: $url\n";
    return $url;
}


class MinerRobotUT extends UnitTestBase
{
    // ------------------------
    // --- Constructor init --- 
    // ------------------------
    public function __construct()
    {
        parent::__construct('MinerRobotUT'); 
        
         
        
    }
    
    public function run()
    {
        $this->test1();
//        $this->testNewjob(); // Just for checking the unpacked files after a new job manually. This test is included in test1() also!!
    }
    
    
    public function test1()
    {
        global $robot_dir, $robot_name, $kill_timeout_in_seconds, $max_continues, $crawler_exe_path;
        // -------------
        // --- Setup ---
        // -------------
        $job_name = "mysite.com";

        $new_job_server_response = array(
            "file_url" => __DIR__ . "/{$job_name}.zip",
            "job_name" => "{$job_name}",
            "task_id" => "myproject_somesite.com_7",
            "crawler_params" => "--upload-handler uploadFileHttpPost",
            "script_params" => "scanMode=full"
            );


        printf ("UNIT_TEST_INFO robot_dir: '%s'\n", $robot_dir);
        removeDirectory($robot_dir);

        // -----------------------------------
        // --- Robot dir empty : 'newJobE' ---
        // -----------------------------------
        $this->subTestNameSet('newJobE');
        removeDirectory($robot_dir);
        $mr = $this->createMinerRobot();
        $this->m_connection->setEmptyServerResponse();
        $status = $mr->getRobotStatus();
        $this->checkEqual('newJobE', $status['robot_status']);
        $this->checkEqual(getCommandReferenceUrl('newJobE', array()), $mr->getLatestRequestUrl());
        $this->m_connection->m_server_response = $new_job_server_response;
        $mr->handleRobotStatus($status["robot_status"]);
        $this->checkEqual(newJobReferenceUrl(), $mr->getLatestRequestUrl());
        $robot_dir_ok = file_exists($robot_dir . "/crawler.php" );
        $this->checkEqual($robot_dir_ok, true);
        $crawler_command = "{$crawler_exe_path} --job-name mysite.com --task-id myproject_somesite.com_7 --upload-handler uploadFileHttpPost crawler.php scanMode=full";
        $this->checkEqual($crawler_command, $mr->lastCrawlerCommand());
        
        // ------------------------------------------------------------
        // --- Robot dir exists, but no status file : 'restartJobE' ---
        // ------------------------------------------------------------
        $this->subTestNameSet('restartJobE');
        $mr = $this->createMinerRobot();
        $this->m_connection->setEmptyServerResponse();
        $status = $mr->getRobotStatus();
        $this->checkEqual('restartJobE', $status['robot_status']);
        $this->checkEqual(getCommandReferenceUrl('restartJobE', array()), $mr->getLatestRequestUrl());
        $mr->handleRobotStatus($status["robot_status"]);
        $crawler_command = "{$crawler_exe_path} --job-name mysite.com --task-id myproject_somesite.com_7 --upload-handler uploadFileHttpPost crawler.php scanMode=full";
        $this->checkEqual($crawler_command, $mr->lastCrawlerCommand());
        
        // ------------------------------------------------------------------
        // --- Robot dir exists, and we can continue : 'crashedContinueE' ---
        // ------------------------------------------------------------------
        $this->subTestNameSet('crashedContinueE');
        $mr = $this->createMinerRobot();
        $status_file = array(
            'mining_done' => 0,
            'continue_counter' => 1
            );
        $this->writeStatusFile ($status_file);
        $this->m_job_handler->jobRunningSet(false);
        $this->m_connection->setEmptyServerResponse();
        $status = $mr->getRobotStatus();
        $this->checkEqual('crashedContinueE', $status['robot_status']);
        $this->checkEqual(getCommandReferenceUrl('crashedContinueE', $status_file), $mr->getLatestRequestUrl());
        $mr->handleRobotStatus($status["robot_status"]);
        $crawler_command = "{$crawler_exe_path} --continue";
        $this->checkEqual($crawler_command, $mr->lastCrawlerCommand());

        
        // --------------------------------------------------------------------
        // --- Robot dir exists, and we can NOT continue : 'crashedNewJobE' ---
        // --------------------------------------------------------------------
        $this->subTestNameSet('crashedNewJobE');
        $mr = $this->createMinerRobot();
        $status_file = array(
            'mining_done' => 0,
            'continue_counter' => $max_continues+1
            );
        $this->writeStatusFile ($status_file);
        $this->m_job_handler->jobRunningSet(false);
        $this->m_connection->setEmptyServerResponse();
        $status = $mr->getRobotStatus();
        $this->checkEqual('crashedNewJobE', $status['robot_status']);
        $this->checkEqual(getCommandReferenceUrl('crashedNewJobE', $status_file), $mr->getLatestRequestUrl());
        $this->m_connection->m_server_response = $new_job_server_response;
        $mr->handleRobotStatus($status["robot_status"]);
        $this->checkEqual(newJobReferenceUrl(), $mr->getLatestRequestUrl());
        $crawler_command = "{$crawler_exe_path} --job-name mysite.com --task-id myproject_somesite.com_7 --upload-handler uploadFileHttpPost crawler.php scanMode=full";
        $this->checkEqual($crawler_command, $mr->lastCrawlerCommand());

        // -------------------------------------------------------------------------
        // --- Robot running normally ( NO timeout reached) : 'runningNormallyE' ---
        // -------------------------------------------------------------------------
        $this->subTestNameSet('runningNormallyE');
        $ts = time();
        $mr = $this->createMinerRobot();
        $status_file = array(
            'task_id' => "myproject_somesite.com_7",
            'mining_done' => 0,
            'continue_counter' => 0,
            'latest_loaded_time_iso' => tsToIsoTime($ts),
            'job_name' => 'wallmart.com'
            );
        $this->writeStatusFile ($status_file);
        $this->m_job_handler->jobRunningSet(true);
        $this->m_connection->setEmptyServerResponse();
        $status = $mr->getRobotStatus();
        $this->checkEqual('runningNormallyE', $status['robot_status']);
        $this->checkEqual(getCommandReferenceUrl('runningNormallyE', $status_file), $mr->getLatestRequestUrl());
        $this->checkEqual('', $mr->lastCrawlerCommand());
        
        // --------------------------------------------------------------------------------
        // --- Robot running but not updating (timeout reached) : 'killTimeOutReachedE' ---
        // --------------------------------------------------------------------------------
        $this->subTestNameSet('killTimeOutReachedE');
        $ts = time() - $kill_timeout_in_seconds -1; // Simulate timeout condition - timeout is 30s
        
        $mr = $this->createMinerRobot();
        $status_file = array(
            'mining_done' => 0,
            'continue_counter' => 0,
            'latest_loaded_time_iso' => tsToIsoTime($ts)
            );
        $this->writeStatusFile ($status_file);
        $this->m_job_handler->jobRunningSet(true);
        $this->m_connection->setEmptyServerResponse();
        $status = $mr->getRobotStatus();
        $this->checkEqual('killTimeOutReachedE', $status['robot_status']);
        $this->checkEqual(getCommandReferenceUrl('killTimeOutReachedE', $status_file), $mr->getLatestRequestUrl());
        $this->checkEqual('', $mr->lastCrawlerCommand());

        // ----------------------------------------------------------------------------------------------
        // --- Robot running normally, but server requests kill-continue : 'serverForceKillContinueE' ---
        // ----------------------------------------------------------------------------------------------
        $this->subTestNameSet('serverForceKillContinueE');
        $ts = time();
        $mr = $this->createMinerRobot();
        $status_file = array(
            'mining_done' => 0,
            'continue_counter' => 0,
            'latest_loaded_time_iso' => tsToIsoTime($ts)
            );
        $this->writeStatusFile ($status_file);
        $this->m_job_handler->jobRunningSet(true);
        $this->m_connection->m_server_response = array('task_robot_command' => 'serverForceKillContinueE');
        $status = $mr->getRobotStatus();
        $this->checkEqual('serverForceKillContinueE', $status['robot_status']);
        $this->checkEqual(getCommandReferenceUrl('runningNormallyE', $status_file), $mr->getLatestRequestUrl());
        $mr->handleRobotStatus($status["robot_status"]);
        $this->checkEqual('', $mr->lastCrawlerCommand());
        // --- Verify that we then get a 'crashedContinueE' in next round ---
        $mr = $this->createMinerRobot();
        $this->m_job_handler->jobRunningSet(false);
        $this->m_connection->setEmptyServerResponse();
        $status = $mr->getRobotStatus();
        $this->checkEqual('crashedContinueE', $status['robot_status']);
        $mr->handleRobotStatus($status["robot_status"]);
        $crawler_command = "{$crawler_exe_path} --continue";
        $this->checkEqual($crawler_command, $mr->lastCrawlerCommand());
        
        // ----------------------------------------------------------------------------------------
        // --- Robot running normally, but server requests kill-restart : 'serverForceRestartE' ---
        // ----------------------------------------------------------------------------------------
        $this->subTestNameSet('serverForceRestartE');
        $ts = time();
        $mr = $this->createMinerRobot();
        $status_file = array(
            'mining_done' => 0,
            'continue_counter' => 0,
            'latest_loaded_time_iso' => tsToIsoTime($ts)
            );
        $this->writeStatusFile ($status_file);
        $this->m_job_handler->jobRunningSet(true);
        $this->m_connection->m_server_response = array('task_robot_command' => 'serverForceRestartE');
        $status = $mr->getRobotStatus();
        $this->checkEqual('serverForceRestartE', $status['robot_status']);
        $this->checkEqual(getCommandReferenceUrl('runningNormallyE', $status_file), $mr->getLatestRequestUrl());
        $mr->handleRobotStatus($status["robot_status"]);
        $this->checkEqual('', $mr->lastCrawlerCommand());
        // --- Verify that we then get a 'restartJobE' in next round ---
        $mr = $this->createMinerRobot();
        $this->m_job_handler->jobRunningSet(false);
        $this->m_connection->setEmptyServerResponse();
        $status = $mr->getRobotStatus();
        $this->checkEqual('restartJobE', $status['robot_status']);
        $mr->handleRobotStatus($status["robot_status"]);
        $crawler_command = "{$crawler_exe_path} --job-name mysite.com --task-id myproject_somesite.com_7 --upload-handler uploadFileHttpPost crawler.php scanMode=full";
        $this->checkEqual($crawler_command, $mr->lastCrawlerCommand());
    
        // --------------------------------------------------------------------------------------
        // --- Robot running normally, but server requests kill-newjob : 'serverForceNewJobE' ---
        // --------------------------------------------------------------------------------------
        $this->subTestNameSet('serverForceNewJobE');
        $ts = time();
        $mr = $this->createMinerRobot();
        $status_file = array(
            'mining_done' => 0,
            'continue_counter' => 0,
            'latest_loaded_time_iso' => tsToIsoTime($ts)
            );
        $this->writeStatusFile ($status_file);
        $this->m_job_handler->jobRunningSet(true);
        $this->m_connection->m_server_response = array('task_robot_command' => 'serverForceNewJobE');
        $status = $mr->getRobotStatus();
        $this->checkEqual('serverForceNewJobE', $status['robot_status']);
        $this->checkEqual(getCommandReferenceUrl('runningNormallyE', $status_file), $mr->getLatestRequestUrl());
        $mr->handleRobotStatus($status["robot_status"]);
        $this->checkEqual('', $mr->lastCrawlerCommand());
        // --- Verify that we then get a 'newJobE' in next round ---
        $mr = $this->createMinerRobot();
        $this->m_job_handler->jobRunningSet(false);
        $this->m_connection->m_server_response = $new_job_server_response;
        $status = $mr->getRobotStatus();
        $this->checkEqual('newJobE', $status['robot_status']);
        $mr->handleRobotStatus($status["robot_status"]);
        $this->checkEqual(newJobReferenceUrl(), $mr->getLatestRequestUrl());
        $crawler_command = "{$crawler_exe_path} --job-name mysite.com --task-id myproject_somesite.com_7 --upload-handler uploadFileHttpPost crawler.php scanMode=full";
        $this->checkEqual($crawler_command, $mr->lastCrawlerCommand());


        // -----------------------------------------------------------------------
        // --- Miner exited normally with script done: 'miningDoneScriptDoneE' ---
        // -----------------------------------------------------------------------
        $this->subTestNameSet('miningDoneScriptDoneE');
        $mr = $this->createMinerRobot();
        $status_file = array(
            'mining_done' => MiningStatusEnum::miningDoneScriptDoneE(),
            'continue_counter' => 1
            );
        $this->writeStatusFile ($status_file);
        $this->m_job_handler->jobRunningSet(false);
        $this->m_connection->setEmptyServerResponse();
        $status = $mr->getRobotStatus();
        $this->checkEqual('miningDoneScriptDoneE', $status['robot_status']);
        $this->checkEqual(getCommandReferenceUrl('miningDoneScriptDoneE', $status_file), $mr->getLatestRequestUrl());
        $mr->handleRobotStatus($status["robot_status"]);
        $this->checkEqual("", $mr->lastCrawlerCommand());
        $this->checkEqual(false, $this->m_job_handler->haveRobotDirectory() );

        // ---------------------------------------------------------------
        // --- Miner exited normally: 'miningDoneMaxPageLoadsReachedE' ---
        // ---------------------------------------------------------------
        // --- We first need to create a new job since the current robot dir is deleted : 'newJobE' ---
        $this->subTestNameSet('miningDoneMaxPageLoadsReachedE prepare');
        $mr = $this->createMinerRobot();
        $this->m_connection->m_server_response = $new_job_server_response;
        $mr->handleRobotStatus('newJobE');
        $this->checkEqual(true, $this->m_job_handler->haveRobotDirectory() );
        
        $this->subTestNameSet('miningDoneMaxPageLoadsReachedE');
        $mr = $this->createMinerRobot();
        $status_file = array(
            'mining_done' => MiningStatusEnum::miningDoneMaxPageLoadsReachedE(),
            'continue_counter' => 1
            );
        $this->writeStatusFile ($status_file);
        $this->m_job_handler->jobRunningSet(false);
        $this->m_connection->setEmptyServerResponse();
        $status = $mr->getRobotStatus();
        $this->checkEqual('miningDoneMaxPageLoadsReachedE', $status['robot_status']);
        $this->checkEqual(getCommandReferenceUrl('miningDoneMaxPageLoadsReachedE', $status_file), $mr->getLatestRequestUrl());
        $mr->handleRobotStatus($status["robot_status"]);
        $this->checkEqual("", $mr->lastCrawlerCommand());
        $this->checkEqual(false, $this->m_job_handler->haveRobotDirectory() );
        
    }

    /////////////
    public function testNewjob()
    {
        global $robot_dir, $robot_name, $kill_timeout_in_seconds, $max_continues, $crawler_exe_path;
        // -------------
        // --- Setup ---
        // -------------
        $job_name = "mysite.com";

        $new_job_server_response = array(
            "file_url" => __DIR__ . "/{$job_name}.zip",
            "job_name" => "{$job_name}",
            "task_id" => "myproject_somesite.com_7",
            "crawler_params" => "--upload-handler uploadFileHttpPost",
            "script_params" => "scanMode=full"
            );


        printf ("UNIT_TEST_INFO robot_dir: '%s'\n", $robot_dir);
        removeDirectory($robot_dir);

        // -----------------------------------
        // --- Robot dir empty : 'newJobE' ---
        // -----------------------------------
        $this->subTestNameSet('newJobE');
        removeDirectory($robot_dir);
        $mr = $this->createMinerRobot();
        $this->m_connection->setEmptyServerResponse();
        $status = $mr->getRobotStatus();
        $this->checkEqual('newJobE', $status['robot_status']);
        $this->checkEqual(getCommandReferenceUrl('newJobE', array()), $mr->getLatestRequestUrl());
        $this->m_connection->m_server_response = $new_job_server_response;
        $mr->handleRobotStatus($status["robot_status"]);
        $this->checkEqual(newJobReferenceUrl(), $mr->getLatestRequestUrl());
        $robot_dir_ok = file_exists($robot_dir . "/crawler.php" );
        $this->checkEqual($robot_dir_ok, true);
        $crawler_command = "{$crawler_exe_path} --job-name mysite.com --task-id myproject_somesite.com_7 --upload-handler uploadFileHttpPost crawler.php scanMode=full";
        $this->checkEqual($crawler_command, $mr->lastCrawlerCommand());
        
    }
    
    
    ///////////
    
    
    private function createMinerRobot()
    {
        global $robots_base_dir, $robot_name, $kill_timeout_in_seconds, $max_continues, $crawler_exe_path, $server_url;
        $this->m_job_handler = new RobotJobHandlerTestImpl($robots_base_dir, $robot_name, $kill_timeout_in_seconds, $max_continues, $crawler_exe_path);
        $this->m_job_handler->killSleepTimeSet(0); // For unit testing we don't need to wait for job to finish since there is no real crawer job running.
        
        $this->m_connection = new RobotClientConnectionTestImpl($robot_name, $server_url);
        return new MinerRobot($this->m_job_handler, $this->m_connection);
    }

    private function writeStatusFile($crawler_status)
    {
        global $robot_dir;
        $path = "{$robot_dir}/Crawler.status"; 
        writeArrayToXml($crawler_status, $path);
    }

    
    
//    private $m_miner_robot;
    private $m_job_handler;
    private $m_connection;
}
