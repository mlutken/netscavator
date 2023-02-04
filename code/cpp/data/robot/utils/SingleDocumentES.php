<?php

require_once ('utils/data_string_utils.php');
require_once ('utils/ESClient.php');
require_once ('utils/Log.php');

/**
  Class to handle a single ES document.
 */
abstract class SingleDocumentES {

    // ------------------------
    // --- Constructor init ---
    // ------------------------
    public function __construct($elasticSearchClient, $params) {
        $this->m_es = $elasticSearchClient;
        $this->init($params);
    }

    public function __destruct() {
        if ($this->m_unit_test_mode) {
            $this->m_es->deleteSafe($this->m_es_params);
        }
    }

    public function initForUnitTest($index_prefix = 'ut_')
    {
        $params = null;
        if (is_string($index_prefix)) {
            $params = $this->m_es_params;
            $params['index'] = $index_prefix . $params['index'];
        }
        else { // Assume that $index_prefix is a complete $params array
            $params = $index_prefix;
        }
        $this->init($params);
        $this->m_unit_test_mode = true;
    }

    // ---Functions that must/can be overridden ---

    /** Return array with default document data. */
    abstract protected function createDefaultData();

    /** You might need to overide this, but most cases you don't. */
    protected function init($params)
    {
        $this->m_es_params = $params;
        $data_exists = $this->m_es->exists($this->m_es_params);

        if (!$data_exists) {
            $this->m_data = $this->createDefaultData();
            $params = $this->m_es_params;
            $params['body'] = $this->m_data;
            $aResponse = $this->m_es->indexAndCreate($params);
        }
        $this->readData();
    }



    /** Read data from ES. */
    public function readData() {
        $params = $this->m_es_params;
        $params['fields'] = array('_source','_timestamp','_ttl');
        $data_raw = $this->m_es->get($params);
        $this->m_data = $data_raw['_source'];
        $this->m_version = $data_raw['_version'];
        if (isset($data_raw['fields']['_timestamp']) === true) {
            $this->m_timestamp = $data_raw['fields']['_timestamp'];
        }
        if (isset($data_raw['fields']['_ttl']) === true) {
            $this->m_ttl = $data_raw['fields']['_ttl'];
        }
    }

    /** Try write data to ES, using lates retrieved version. If version in ES has changed
        the write wil fail.
    @see writeAlways
    @return  true if write went ok. */
    public function writeData()
    {
        $write_ok = true;
        $params = $this->m_es_params;
        $params['body'] = $this->m_data;
        $version = $this->version();
        $params['version'] = $version;
        $response = null;
        try {
            $response = $this->m_es->indexAndCreate($params);
        }
        catch (Exception $e) {
//            print_r($e);
            $write_ok = false;
        }
        if ($write_ok) {
            $this->m_version++;
        }
        return $write_ok;
    }

    /** Write unconditionally to ES regardless of document version.
    @see writeData
    @return  true if write went ok.    */
    public function writeAlways() {
        $write_ok = true;
        $params = $this->m_es_params;
        $params['body'] = $this->m_data;
        $response = null;
        try {
            $response = $this->m_es->indexAndCreate($params);
        } catch (Exception $e) {
            $write_ok = false;
        }
        return $write_ok;
    }

    public function params()
    {
        return $this->m_es_params;
    }

    public function value($key)
    {
        return @$this->m_data[$key];
    }

    public function valueSet($key, $value)
    {
        $this->m_data[$key] = $value;
    }

    public function data()
    {
        return $this->m_data;
    }

    /** Include _timestamp, _version and _ttl in data.*/
    public function dataAll()
    {
        $data = $this->m_data;
        $data['_version']   = $this->m_version;
        $data['_timestamp'] = $this->m_timestamp;
        $data['_ttl']       = $this->m_ttl;
        return $data;
    }

    public function debugString()
    {
        $data = $this->m_data;
        $data['_version'] = $this->m_version;
        return jsonEncodePretty($data);
    }

    public function debugPrint()
    {
        print "<pre>\n" . $this->debugString() . "\n</pre>\n";
    }

    /** Mostly for debugging and unit test use! */
    public function forceValue($key, $val)
    {
        $this->m_data[$key] = $val;
    }

    public function timestamp   () {   return $this->m_timestamp; }
    public function ttl         () {   return $this->m_ttl; }

    public function version()
    {
        return $this->m_forced_version ? $this->m_forced_version : $this->m_version;
    }

    /// For unit test/debug.
    public function forceVersion($version) {
        $this->m_forced_version = $version;
    }

    public function resetForcedVersion() {
        $this->m_forced_version = 0;
    }

    public function logName()
    {
        return $this->m_log_name;
    }

    /// For unit test/debug.
    public function logNameSet($log_name)
    {
        $this->m_log_name = $log_name;
    }

    // ---------------------
    // --- PRIVATE: Data ---
    // ---------------------
    private $m_forced_version = 0;
    protected $m_timestamp = 0;
    protected $m_ttl = 0;
    protected $m_version = 0;
    protected $m_data = array();
    protected $m_es = null;
    protected $m_es_params = null;
    protected $m_unit_test_mode = false;
    protected $m_log_name = '';

}

?>
