<?php
require_once ('utils/ESClient.php');

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of Log
 *
 * @author ml
 */
class Log {
    // ------------------------
    // --- Constructor init ---
    // ------------------------
    public function __construct($es_client=null)
    {
        if ($es_client == null) {
            $es_client = getElasticSearch();
        }
        $this->m_es = $es_client;
        if (!$this->m_es->indexExists('logs')) {
            $this->m_es->createIndexWithDefaultData('logs');
        }
    }

    public function info($msg)
    {
        $this->doLog('info', $msg);
    }

    public function warn($msg)
    {
        $this->doLog('warning', $msg);
    }

    public function err($msg)
    {
        $this->doLog('error', $msg);
    }

    public static function I()
    {
        if (Log::$m_instance == null) {
            Log::$m_instance = new Log();
        }
        return Log::$m_instance;
    }


    // ---------------------------------
    // --- PRIVATE: Helper functions ---
    // ---------------------------------
    private function doLog($lvl, $msg)
    {
        $lvl_uppercase = strtoupper($lvl);
        if ($this->m_do_print_to_stdout) {
            printf("[$lvl_uppercase] : $msg\n");
        }

        $ts_now = time();
        $date = date("Y_m_d", $ts_now);
        $params = array(
            'index' => 'logs'
            , 'type' => "{$date}__{$lvl}"
            , 'ttl' => '30d'
            , 'body' => array(    'date' => $date
                                , 'time' => date("H:i:s", $ts_now)
                                , 'lvl' => $lvl_uppercase
                                , 'msg' => $msg )
        );
        $this->m_es->index($params);
    }


    // ---------------------
    // --- PRIVATE: Data ---
    // ---------------------
    private static $m_instance = null;
    private $m_es = null;
    private $m_do_print_to_stdout = true;

}
