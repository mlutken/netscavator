<?php
require_once('string_utils.php');


class ReferenceManualGeneratorPlainHtml
{
    // ----------------------------------------------
    // --- Constructor and private init functions ---
    // ----------------------------------------------
    public  function __construct ( $aAllInOrigOrder, $sBaseDir = "." )
    {
        if(!is_dir($sBaseDir)){
            mkdir($sBaseDir, 0755);
        }        
        $sBaseDir = realpath($sBaseDir);
        $this->m_sBaseDir = $sBaseDir;
        $this->m_aAllInOrigOrder = $aAllInOrigOrder;
        
        $this->m_allInMap = [];
		foreach($this->m_aAllInOrigOrder as $entry) {
			$this->m_allInMap[$entry['name']] = $entry;
		}
        
        
        $this->addNodePaths();
        $this->add__All_Functions();
        printf("basedir: %s\n", $this->m_sBaseDir);
        printf("content-dir: %s\n", $this->m_sContentDir );
    }

    
    
    private function addNodePaths()
    {
         foreach ($this->m_allInMap as $key => &$entry) {
            $path = mb_strtolower( $entry["name"], 'UTF-8' );
            $path = str_replace  ( " " , "-" , $path );
            $entry["path"] = $this->m_sPathPrefix . $path . $this->m_sPathPostfix;
         }
    }

    /// Add all functions to the "All functions" entry if present
    private function add__All_Functions()
    {
		$allFunctions = [];
		foreach($this->m_allInMap as $key => &$entry) {
			if ($entry['type'] == 'function') {
  				$allFunctions[] = $entry;
			}
		}
		
		arrayToJsonFile($allFunctions, "/tmp/_allFunctions.json", true);
		$this->m_allInMap['All functions']['functions'] = $allFunctions;
		
		
    }
    
    
    public function writeFile( $f )
    {
        $fullPath = $this->m_sBaseDir . $this->m_sContentDir . $f["path"];
        //@mkdir( $path, 0755, true ); // The @ suppresses php warnings. Here we particularly want to         
//		file_put_contents ( $fileName , $line, FILE_APPEND );

        printf("ML: WRITE name: '%s': %s\n", $f["name"], $fullPath );
        $s = $this->getHtmlForFiles($f);
		file_put_contents ( $fullPath , $s );
		if (!array_key_exists('path', $f)) {
			print_r($f);
        }
        //printf("HTML:\n%s\n\n", $s);
      
    }
    
    public function writeFiles()
    {
        @mkdir( $this->m_sBaseDir, 0755, true ); // The @ suppresses php warnings. 
        @mkdir( $this->m_sBaseDir . $this->m_sContentDir, 0755, true ); // The @ suppresses php warnings. 
        
        foreach ($this->m_allInMap as $key => $entry) {
            $this->writeFile( $entry );
        }
    }
    
    public function getSyntax( $f )
    {
        $s = "";
        if  ( array_key_exists( "syntax", $f ) ) {
            foreach ( $f['syntax'] as $e ) {
                $s .= "<pre>\n{$e}\n</pre>\n"; 
            }
        }
        return $s;
    }

    public function getGroup( $f )
    {
        $s = "";
        if  ( array_key_exists( "group", $f ) ) {
            $s .= "<strong>Group: </strong>"; 
            $s .= "<div>" . $this->t($f["group"]) . "</div><br />\n"; 
        }
        return $s;
    }

    public function getFunctionsTable( $entry )
    {
        $s = "";
        if  ( array_key_exists( "functions", $entry ) && count($entry['functions']) > 0 ) {
            $s .= "<table border=1 >\n";
            foreach ( $entry['functions'] as $e ) {
				$desc = $e['desc'];
				$pos = strpos($desc, '.', 0);
				if ($pos !== false)
					$desc = substr($desc, 0, $pos);
                $s .= "    <tr>\n";
                $s .= "    <td>{$e['name']}</td>\n"; 
                $s .= "    <td>{$desc}</td>\n"; 
                $s .= "    <td>{$e['syntax'][0]}</td>\n"; 
                $s .= "    </tr>\n";
            }
            $s .= "</table>\n";
        }
        return $s;
    }
    
    public function getParameters( $f )
    {
        $s = "";
        if  ( array_key_exists( "params", $f ) && count($f['params']) > 0 ) {
            $s .= "<table border=1 >\n";
            foreach ( $f['params'] as $e ) {
                $s .= "    <tr>\n";
                $s .= "    <td>{$e[1]}</td>\n"; 
                $s .= "    <td>{$e[0]}</td>\n"; 
                $s .= "    <td>" . $this->t($e[2]) . "</td>\n"; 
                $s .= "    </tr>\n";
            }
            $s .= "</table>\n";
        }
        return $s;
    }


    public function getDescription( $f )
    {
        $s = "";
        if  ( array_key_exists( "desc", $f ) ) {
            $s .= "<strong>Description: </strong><br />\n"; 
            $s .= "<p>" . $this->t($f["desc"]) . "</p>\n"; 
        }
        return $s;
    }


    public function getSeeAlso( $f )
    {
        $s = "";
        if  ( array_key_exists( "seealso", $f ) ) {
            $s .= "<strong>See also: </strong><br />\n"; 
            $s .= "<p>" . $this->t($f["seealso"]) . "</p>\n"; 
        }
        return $s;
    }


    public function getExamples( $f )
    {
        $s = "";
        if  ( array_key_exists( "examples", $f ) && count($f['examples']) > 0 ) {
            $s .= "<strong>Examples: </strong><br />\n"; 
            $s .= "<table border=1 >\n";
            foreach ( $f['examples'] as $e ) {
                $s .= "    <tr>\n";
                $s .= "    <td><pre>{$e}</pre></td>\n"; 
                $s .= "    </tr>\n";
            }
            $s .= "</table>\n";
        }
        return $s;
    }

    public function getHtml( $f )
    {
        $s = "";
        $s .= $this->getSyntax($f);
        $s .= $this->getGroup($f);
        $s .= $this->getParameters($f);
        $s .= $this->getDescription($f);
        $s .= $this->getSeeAlso($f);
        $s .= $this->getFunctionsTable($f);
        $s .= $this->getExamples($f);
        
        return $s;
    }
    
    public function getHtmlForDrupal( $f )
    {
		return $this->getHtml($f);
    }
    
    public function getHtmlForFiles( $f )
    {
		$s = $this->getHtmlHeader();
		$s .= $this->getHtml($f);
		$s .= $this->getHtmlFooter();
		return $s;
    }
    
    public function getHtmlHeader()
    {
		$s =
<<<TEXT
<html xmlns='http://www.w3.org/1999/xhtml'>
<head>
	<meta http-equiv='content-type' content='text/html; charset=utf-8'/>
</head>
<body>
TEXT;
		return $s;
    }
    
    public function getHtmlFooter()
    {
		$s =
<<<TEXT
</body>
</html>
TEXT;
		return $s;
    }

    public function dbgPrint()
    {
         foreach ( $this->m_aAllInOrigOrder as $f ) {
//            printf("Name: %s, Path: %s\n", $f["name"], $f["path"]);
            printf("*** %s ***\n-----------\n%s-------\n\n", $f["name"], $this->getHtml($f) );
         }
    }

    public function dbgPrintJson()
    {
		print json_encode($this->m_allInMap, JSON_NUMERIC_CHECK | JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE | JSON_UNESCAPED_SLASHES) . "\n";
    }

    public function allInOrigOrder()
    {
		return $this->m_aAllInOrigOrder;
    }
    
    
    private function t($s)
    {
        return $s;
    }
    

    private     $m_sBaseDir;
    private     $m_sContentDir = "/content/";
    private     $m_sPathPrefix = "reference-";
    private     $m_sPathPostfix = ".html";   // Like eg. '.html' for testing
    private     $m_aAllInOrigOrder = null;  // All items in original order.
}
