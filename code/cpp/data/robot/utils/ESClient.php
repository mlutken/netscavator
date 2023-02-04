<?php
require_once ( __DIR__ . '/../php_fix_include_path.php' );
require_once ('utils/general_utils.php');


class ESClient extends Elasticsearch\Client
{
    public function __construct($params = array())
    {
        parent::__construct( $params );
        $this->m_aIndicesPresent = array();
    }

    public function indexExists($index)
    {
        $params = array();
        $params['index'] = $index;
        $params['type']  = '';
        $params['id'] = '';
        return $this->exists($params);
    }

    public function typeExists($params)
    {
        $parm = $params;
        $parm['id'] = '';
        return $this->exists($parm);
    }

    public function indexExistsCached($index)
    {
        if (array_key_exists($index, $this->m_aIndicesPresent) ) return true;
        $exists = $this->indexExists($index);
        if ($exists) $this->m_aIndicesPresent[$index] = 1;
        return $exists;
    }

    /** Delete document if it exists. */
    public function deleteSafe($params)
    {
        if ( $this->exists($params)) {
            $this->delete($params);
        }
    }

    /** Delete index if it exists. */
    public function deleteIndexSafe($index)
    {
        if ( $this->indexExists($index)) {
            $this->indices()->delete(array('index'=> $index));
        }
    }

    public function getHostAndPort()
    {
        return array('host' => 'localhost', 'port' => 9200);
    }

    /** Create index in ElasticSearch, using the $json argument as settings and mappings.
    For example the json could be:
    \code
    {
        "settings" : {
        },
        "mappings" : {
            "_default_":{
                "_timestamp" : {
                    "enabled" : true,
                    "store" : true
                },
                "_ttl" : {
                    "enabled" : true,
                    "store" : true
                }
            }
        }
    }
    \endcode
    */
    public function createIndex($index, $create_defaults_json)
    {
        $params['index'] = $index;
        $params['body'] = $create_defaults_json;
        $this->indices()->create($params);
    }

    private 	$m_aIndicesPresent;

}


class SleipnerESClient extends ESClient
{
    public function __construct($params = array())
    {
        parent::__construct( $params );
    }


    /** Run cURL command against ElasticSearch.
    \param $cmd Command to execute XGET, XPUT, XPOST ... etc
    \param $url Url to acces. eg. /movies/price/...

    \return Array containing the lines from the output.*/
    public function runCurl($cmd,$url,$json)
    {
        $data = $json != '' ? " -d '{$json}'" : '';

        $aHost = $this->getHostAndPort();
        $cmdLine =
<<<RAW
curl -{$cmd} 'http://{$aHost['host']}:{$aHost['port']}{$url}'{$data} 2>/dev/null
RAW;
        $output = array();
        exec ( $cmdLine, $output );
        return $output;
    }


    /** Add mapping to ElasticSearch.
    \return Array containing the lines from the output.*/
    public function addMapping($url, $mappingJson)
    {
        $cmd = "XPOST";
        return $this->runCurl($cmd,$url,$mappingJson);
    }


    /** Create index in ElasticSearch.
    Create index with settings from a json file.
    Looks in thehive/php/datagetter/indices_data/ for a json file with the same name as
    the index specified in params. If found and the index needs to be created, it will use
    the json file for the index settings and mappings.
    */
    public function createIndexWithDefaultData($index)
    {
        $index_json_file = __DIR__ . '/../datagetter/indices_data/' . $index . '.json';
        if (file_exists($index_json_file)) {
            $create_defaults_json = file_get_contents($index_json_file);
            $this->createIndex($index, $create_defaults_json);
        }
    }

    /**

    Index a document, but create index with settings from a json file if index does not exist.
    Looks in thehive/php/datagetter/indices_data/ for a json file with the same name as
    the index specified in params. If found and the index needs to be created, it will use
    the json file for the index settings and mappings.
    */
    public function indexAndCreate($params)
    {
        $index = $params['index'];
        $index_exists = $this->indexExistsCached($index);
        if (!$index_exists) {
            $this->createIndexWithDefaultData($index);
        }
        parent::index($params);
    }




}



/** get default Elastic Search client object.*/
function getElasticSearch()
{
    return new SleipnerESClient();
}




?>
