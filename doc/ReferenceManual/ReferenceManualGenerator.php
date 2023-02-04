<?php

function str_replace_first($str_pattern, $str_replacement, $string)
{
    $occurrence = strpos($string, $str_pattern);      
    if ($occurrence !== false){
        return substr_replace($string, $str_replacement, $occurrence, strlen($str_pattern));
    }
    return $string;
}

function strStartsWith($haystack,$needle,$case=true)
{
   if($case)
       return strpos($haystack, $needle, 0) === 0;

   return stripos($haystack, $needle, 0) === 0;
}

function strEndsWith($haystack,$needle,$case=true)
{
  $expectedPosition = strlen($haystack) - strlen($needle);

  if($case)
      return strrpos($haystack, $needle, 0) === $expectedPosition;

  return strripos($haystack, $needle, 0) === $expectedPosition;
}

class ReferenceManualGenerator
{
    // ----------------------------------------------
    // --- Constructor and private init functions ---
    // ----------------------------------------------
    public  function __construct ( &$aAllInOrigOrder, $sBaseDir = "." )
    {
        $sBaseDir = realpath($sBaseDir);
        $this->m_aAllInOrigOrder = $aAllInOrigOrder;
        
        $this->addGeneratedData();
    }

    private function addGeneratedData()
    {
        $this->m_dNameToItem = array();
        foreach ( $this->m_aAllInOrigOrder as &$f ) {
            $f["path"] = $this->m_sPathPrefix . urlAliasFromTitle($f["name"]) . $this->m_sPathPostfix;
            $f["summary"] = $this->getSummary( $f["desc"]);
            $f["parse_name"] = $f["name"];
            if ( false !== stripos( $f["parse_name"], " ") ) {
                $f["parse_name"] = urlLeafFromTitle( $f["name"] );
            }
            $this->m_dNameToItem[ $f["parse_name"] ] = &$f;
            if ( $f["parse_name"] != $f["name"] ) {
                $this->m_dNameToItem[ $f["name"] ] = &$f;
            }
            if ( $f["name"] == "All functions" ) {
                $this->addAllFunctions($f);
            }
            if ( $f["type"] == "group" ) {
                $this->addGroupFunctions($f);
            }
        }
// //         $fA = $this->lookupItem("all-functions");
// //         var_dump($fA);
// //         foreach ( $fA['functions'] as $n) {
// //             printf("A: $n\n");
// //         }
    }

    public function addGroupFunctions( &$fG )
    {
        foreach ( $this->m_aAllInOrigOrder as $f ) {
            if ( ( $f["type"] == "function" || $f["type"] == "operator" ) && $f["group"] == $fG["name"]) {
                $fG["functions"][] = $f["name"];
            }
        }
        if ( is_array($fG["functions"]) ) sort($fG["functions"]);
    }
    
    
    public function addAllFunctions( &$fAllFunctions)
    {
        foreach ( $this->m_aAllInOrigOrder as $f ) {
            if ( $f["type"] == "function" || $f["type"] == "operator" ) {
                $fAllFunctions["functions"][] = $f["name"];
            }
        }
        sort($fAllFunctions["functions"]);
    }
    
    
    public function writeFile( $f )
    {
		if ( $f["name"] == "" ) return;
        printf("ML: %s: %s\n", $f["parse_name"], $f["path"] );
        $s = $this->getHtmlForDrupal($f);

        $node = prepareNode( $f["name"] );
		$node->body[$node->language][0]['value'] = $s;
		$node->body[$node->language][0]['summary'] = $f["summary"];
		$node = node_submit($node); // Prepare node for a submit
		node_save($node); // After this call we'll get a nid

    }
    
    public function writeFiles()
    {
        //return;
        foreach ( $this->m_aAllInOrigOrder as &$f ) {
            $this->writeFile( $f );
        }
    }
    
    // ------------------------------
    // --- Display/Html functions ---
    // ------------------------------
    
    public function getSyntax( $f )
    {
        if  ( !array_key_exists( "syntax", $f ) || count($f['syntax']) == 0 ) return "";
        $s  = $this->sectionHeadline("Syntax"); 
        foreach ( $f['syntax'] as $e ) {
            $s .= "<pre>\n{$e}\n</pre>\n"; 
        }
        return $s;
    }

    public function getGroup( $f )
    {
        $s = "";
        if  ( array_key_exists( "group", $f ) ) {
            $fG= $this->lookupItem( $f["group"] );
            $s .= "<div><strong>Group:&nbsp;</strong>"; 
            $s .= $this->parseText( $fG["parse_name"] ) . "&nbsp;(&nbsp;"; 
            $s .= $this->t($f["type"]) . "&nbsp;)</div><br />\n"; 
        }
        return $s;
    }

    public function getEnumValues( $f )
    {
        if  ( !array_key_exists( "values", $f ) || count($f['values']) == 0 ) return "";
        $s  = $this->sectionHeadline("Values"); 
        $s .= "<table border=1 >\n";
        foreach ( $f['values'] as $e ) {
            $s .= "    <tr>\n";
            $s .= "    <td>{$e[0]}</td>\n"; 
            $s .= "    <td>" . $this->parseText($e[1]) . "</td>\n"; 
            $s .= "    </tr>\n";
        }
        $s .= "</table>\n";
        return $s;
    }

    
    public function getFunctionList( $f, $sHeadLine, $bSmallHeadLine )
    {
        if  ( !array_key_exists( "functions", $f ) || count($f['functions']) == 0 ) return "";
        if ( $bSmallHeadLine )  $s = $this->smallHeadline( $sHeadLine);
        else                    $s = $this->sectionHeadline( $sHeadLine);
        $s .= "<table border=1 >\n";
        foreach ( $f['functions'] as $name ) {
            $fF = $this->lookupItem($name);
            $s .= "    <tr>\n";
            $s .= "    <td>" . $this->parseText($name) . "</td>\n"; 
            $s .= "    <td>" . $this->parseText($fF["summary"]) . "</td>\n"; 
            $s .= "    </tr>\n";
        }
        $s .= "</table>\n";
        return $s;
    }

    public function getFunctionGroupsList( $f )
    {
        if  ( $f["name"] != "All function groups" ) return "";
        $s  = $this->sectionHeadline("Function groups"); 
        $s .= "<table border=1 >\n";
        foreach ( $this->m_aAllInOrigOrder as $f ) {
            if ( $f["type"] != "group" ) continue;
            $s .= "    <tr>\n";
            $s .= "    <td>" . $this->parseText($f["parse_name"]) . "</td>\n"; 
            $s .= "    <td>" . $this->parseText($f["summary"]) . "</td>\n"; 
            $s .= "    </tr>\n";
        }
        $s .= "</table><br>\n";
        $s .= $this->sectionHeadline("All functions by group"); 

        foreach ( $this->m_aAllInOrigOrder as $f ) {
            if ( $f["type"] != "group" ) continue;
            $s .= $this->getFunctionList( $f, $f["name"], true ) . "<br>";
        }
        
        return $s;
    }
    
    public function getParameters( $f )
    {
        if  ( !array_key_exists( "params", $f ) || count($f['params']) == 0 ) return "";
        $s  = $this->sectionHeadline("Parameters"); 
        $s .= "<table border=1 >\n";
        foreach ( $f['params'] as $e ) {
            $s .= "    <tr>\n";
            $s .= "    <td><i>{$e[1]}</i></td>\n"; 
            $s .= "    <td>{$e[0]}</td>\n"; 
            $s .= "    <td>" . $this->parseText($e[2]) . "</td>\n"; 
            $s .= "    </tr>\n";
        }
        $s .= "</table>\n";
        return $s;
    }


    public function getDescription( $f )
    {
        if  ( !array_key_exists( "desc", $f ) ) return "";
        $s  = $this->sectionHeadline("Description"); 
        $desc = $this->parseText($f["desc"]);
        $s .= "<p>{$desc}</p>\n"; 
        return $s;
    }


    public function getSeeAlso( $f )
    {
		if  ( !array_key_exists( "seealso", $f ) ) return "";
        $a = explode (",", $f["seealso"] );
        $s  = $this->sectionHeadline("See also"); 
		$s .= "<ul>";
		foreach ( $a as $word ) {
			$word = trim($word);
			if ( $word == "" ) continue;
			$link = $this->getDisplayString($word);

			$summary = "";
			$f = $this->lookupItem($word);
			if ($f) $summary = $f['summary'];
			$s .= "<li>{$link}:&nbsp;{$summary}</li>"; 
		}
		$s .= "</ul>";
        return $s;
    }


    public function getExamples( $f )
    {
        if  ( !array_key_exists( "examples", $f ) || count($f['examples']) == 0 ) return "";
		$s = $this->sectionHeadline("Examples"); 
        foreach ( $f['examples'] as $e ) {
            $s .= "<br><pre>{$e}</pre>"; 
        }
        return $s;
    }

    public function getSummary( $desc )
    {
		$summary = stristr( $desc, '.', true) . ".";
		if ( $summary == "" ) $summary = "No summary.";
		return $summary;
    }
    
    public function parseText( $text )
    {
		$s = "";
        $text = str_replace("'", " ' ", $text);        
        $text = str_ireplace("<PRE>", " <PRE> ", $text);        
        $text = str_ireplace("</PRE>", " </PRE> ", $text);        
		$a = explode ( " ", $text );
		foreach ( $a as $word ) {
			$s .= $this->getDisplayString(trim($word)) . " ";
		}
        return $s;
    }
    
    public function getDisplayString( $word )
    {
        $s = $word;
        if ( $this->m_bIn_CODE_section || $this->m_bIn_PRE_section) {
            $s = str_replace("<", "&lt;", $s);        
            $s = str_replace(">", "&gt;", $s);        
        }
        $f = $this->lookupItem( $word );
        
        // --- Temporarely remove a trailing full stop, comma, colon. ---
        // The char is inserted again later
        $c = "";
        if ( $f == null ) {
            $c = $word[strlen($word)-1];
////            if ( $c == '.' || $c == "." || $c == ":" || $c == "," ) {
            if ( $c == "." || $c == ":" || $c == "," ) {
                $w = str_replace ( "$c", "", $word);
                $f = $this->lookupItem( $w );
            }
            else $c = "";
        }

        if      ( $word == "<PRE>" )    $this->m_bIn_PRE_section = true;
        elseif  ( $word == "</PRE>" )   $this->m_bIn_PRE_section = false;
        
        $pos = strpos( $s, "'");
        while ( $pos !== false ) {
            $this->toggle_CODE_section();
            $repl = $this->m_bIn_CODE_section ? "<code>" : "</code>";
            $s = str_replace_first("'", $repl, $s);        
            $pos = strpos( $s, "'");
        }
        
        if  ( $f != null ) {
            $s = linkLocalFromTitle( $f["name"] ) . $c;
        }
//        printf("ML s: %s\n", $s);
        return $s;
    }   

    public function &lookupItem( $word )
    {
        $f = null;
        $word = trim($word);
        if  ( array_key_exists( $word, $this->m_dNameToItem ) ) {
            $f = $this->m_dNameToItem[$word];
        }
        return $f;
    }

    public function toggle_CODE_section()
    {
        $this->m_bIn_CODE_section = !$this->m_bIn_CODE_section;
        return $this->m_bIn_CODE_section;
    }

    public function toggle_PRE_section()
    {
        $this->m_bIn_PRE_section = !$this->m_bIn_PRE_section;
        return $this->m_bIn_PRE_section;
    }
    
    public function sectionHeadline($headLine)
    {
        return "<h4>{$headLine}: </h4>";
    }

    public function smallHeadline($headLine)
    {
        return "<strong>{$headLine}: </strong>";
    }
    
    public function getHtml( $f )
    {
		$this->m_bIn_CODE_section = false;
        $s = "";
        $s .= $this->getGroup($f);
        $s .= $this->getDescription($f);
        $s .= $this->getSyntax($f);
        $s .= $this->getEnumValues($f);
        $s .= $this->getParameters($f);
        $s .= $this->getFunctionList($f, "Functions", false );
        $s .= $this->getFunctionGroupsList($f);
        $s .= $this->getSeeAlso($f);
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

    public function test()
    {
		$this->getDisplayString("'domFindPos");
		$this->getDisplayString("hejsa");
        $this->getDisplayString("'");
        $this->getDisplayString("(mySeq)'");
    }

    
    private function t($s)
    {
        return $s;
    }
    

    private     $m_sContentDir = "/content/";
    private     $m_sPathPrefix = "";
    private     $m_sPathPostfix = "";   // Like eg. '.html' for testing
    private     $m_aAllInOrigOrder 	= null;  // All items in original order.
    private		$m_dNameToItem		= null;  // Dictionary: lookupup item (function, group, enum, constant ...) based on name
    private     $m_bIn_CODE_section = false;    // True if we have found beginning of a CODE section, which means the first apostrophe (') char. The second one closes the CODE/PRE again
    private     $m_bIn_PRE_section  = false;    // True if we have found beginning of a PRE section: <PRE>, </PRE>
}



?>

