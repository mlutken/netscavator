<?php
require_once "robot_system_utils.php";

class CrawlerRobot
{
	// ----------------------------
	// --- PUBLIC: Functions ---	
	// ----------------------------
	function __construct( $sRobotsBaseDir, $sRobotName, $sServerUrl )
	{
		$this->m_sRobotsBaseDir = $sRobotsBaseDir;
		$this->m_sRobotName		= $sRobotName;
		$this->m_sRobotDir		= $this->m_sRobotsBaseDir . "/" . $this->m_sRobotName;
		$this->m_sServerUrl 		= $sServerUrl;
		
	}

	public function run()
	{
		$this->readStatusFile();
		var_dump( $this->m_oStatus);
	}
	
	// ----------------------------
	// --- PRIVATE: Functions ---	
	// ----------------------------
	private function readStatusFile()
	{
		$sStatus = file_get_contents( $this->m_sRobotDir . "/Crawler.status" );
		$this->m_oStatus = json_decode( $sStatus );
	}
	
	// ----------------------------
	// --- PRIVATE: Member data ---	
	// ----------------------------
	private		$m_sRobotsBaseDir;
	private		$m_sRobotName;
	private		$m_sRobotDir;
	private		$m_oStatus;
	
	private		$m_sScriptBaseName;
	private		$m_iKillScriptTimeOut;
	
	
	
	// ------------------------
	// --- DEBUG: Functions ---	
	// ------------------------
	
}


?>

