<?php

global $g_baseName;
$g_baseName= "";


function headerGet( $title, $baseName, $highLightXML, $highLightScript, $linkToExampleDocs, $highLightTemplate = null )
{    
$str = <<<MY_DELIMITER
<HTML>
    <HEAD>
        <TITLE>__TITLE__</TITLE>
        <META http-equiv="Content-Type" content="text/html; charset=utf8" > 
        <SCRIPT src="../codeedit.js" type="text/javascript"></SCRIPT>
        <SCRIPT src="../jquery-1.6.2.min.js"></SCRIPT>
        <SCRIPT type="text/javascript" src="../syntaxhighlighter_3.0.83/scripts/shCore.js"></SCRIPT>
        <SCRIPT type="text/javascript" src="../syntaxhighlighter_3.0.83/scripts/shBrushJScript.js"></SCRIPT>
        <SCRIPT type="text/javascript" src="../syntaxhighlighter_3.0.83/scripts/shBrushPhp.js"></SCRIPT>
        <SCRIPT type="text/javascript" src="../syntaxhighlighter_3.0.83/scripts/shBrushXml.js"></SCRIPT>
        <SCRIPT src="../examples_utils.js" type="text/javascript"></SCRIPT>
        <LINK type="text/css" rel="stylesheet" href="../syntaxhighlighter_3.0.83/styles/shCoreDefault.css"/>
        <LINK type="text/css" rel="stylesheet" href="../examples.css"/>
        <SCRIPT>
            var g_baseName = '__BASE_NAME__';
            SyntaxHighlighter.all();
        </SCRIPT>
    </HEAD>
    <BODY class="class1" onLoad="onPageLoad('__BASE_NAME__', '$highLightXML', '$highLightScript', '$highLightTemplate');" >
    <H2>Example: __TITLE__</H2>
    <span><strong>Back to: </strong><a href=/sites >Examples sites</a></span><strong>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Example documentation: </strong><a href='$linkToExampleDocs' >$linkToExampleDocs</a><br>
MY_DELIMITER;

    global $g_baseName;
    $g_baseName = $baseName;
    return str_replace(array("__TITLE__", "__BASE_NAME__"), array($title, $baseName), $str);
}


function sourceBlockStartGet($highLightHtml, $bIsTemplateExample = false )
{    
$str = <<<MY_DELIMITER2
        <TABLE>
            <tr><td><strong>XML output for this example:<strong></td>
                <td><a href=# onclick="$('#xmloutput').toggle('fast');" >Show/Hide</a></td></tr>
        </TABLE>
        <TABLE id=xmloutput style="display:none;background-color:lightgrey" >
            <tr><td><div id=xmloutput_code ></div></td></tr>
        </TABLE>

        <TABLE>
            <tr><td><strong>Script source code for this example:<strong></td>
                <td><a href=# onclick="$('#scriptsrc').toggle('fast');" >Show/Hide</a></td></tr>
        </TABLE>
        <TABLE id=scriptsrc style="display:none;background-color:lightgrey" >
            <tr><td><div id=scriptsrc_code ></div></td></tr>
        </TABLE>
MY_DELIMITER2;
    if ($bIsTemplateExample) {
$str .= <<<MY_DELIMITER2
        <TABLE>
            <tr><td><strong>Template source code for this example:<strong></td>
                <td><a href=# onclick="$('#templatesrc').toggle('fast');" >Show/Hide</a></td></tr>
        </TABLE>
        <TABLE id=templatesrc style="display:none;background-color:lightgrey" >
            <tr><td><div id=templatesrc_code ></div></td></tr>
        </TABLE>
MY_DELIMITER2;
    }

$str .= <<<MY_DELIMITER2
        <TABLE><tr>
            <td><strong>Html source for this page:<strong></td>
            <td><a href=# onclick="$('#htmlsrc').toggle('fast');" >Show/Hide</a></td>
            </tr>
        </TABLE>
        <TABLE id=htmlsrc style="display:none;background-color:lightgrey" >
            <tr><td>
            <script type="syntaxhighlighter" class="brush: html; highlight: $highLightHtml"><![CDATA[
MY_DELIMITER2;

    global $g_baseName;
    return  $str;
}


function sourceBlockEndGet()
{    
$str = <<<MY_DELIMITER3
            ]]></script>
            </td></tr>
        </TABLE>
MY_DELIMITER3;

    global $g_baseName;
    return  $str;
}


function footerGet( $bIsTemplateExample = false)
{    
$str = <<<MY_DELIMITER1
    <BR>
        <script>
        function onPageLoad( baseName, highLightXML, highLightScript, highLightTemplate) {
            loadCode(   "../../code/" + baseName + "/" + baseName + ".xml"
                        , "xmloutput_code", "xml", "highlight: " + highLightXML );
            loadCode(   "../../code/" + baseName + "/" + baseName + ".php"
                        , "scriptsrc_code", "php", "highlight: " + highLightScript );
MY_DELIMITER1;
    if ($bIsTemplateExample) {
$str .= <<<MY_DELIMITER1
            loadCode(   "../../code/templates/" + baseName + ".tpl.php"
                        , "templatesrc_code", "php", "highlight: " + highLightTemplate );
MY_DELIMITER1;
    }


$str .= <<<MY_DELIMITER1
         }

    </script>

    </BODY>
</HTML>
MY_DELIMITER1;

    global $g_baseName;
    return  $str;
}


// --------------------------
// --- Clothes store data ---
// --------------------------
$g_itemsPerSearchListingPage = (int)2;


$g_data = array();
$g_data[] = array ( 'id' =>  0, 'price' => 45.50  , 'color' => 'white'   , 'brand' => 'Dior' , 'clothes_type' => 'dress' , 'fabric_type' => 'wool'  ) ;
$g_data[] = array ( 'id' =>  1, 'price' => 55.50  , 'color' => 'green'   , 'brand' => 'CK'   , 'clothes_type' => 'dress' , 'fabric_type' => 'wool'  ) ;
$g_data[] = array ( 'id' =>  2, 'price' => 35.75  , 'color' => 'green'   , 'brand' => 'Boss' , 'clothes_type' => 'dress' , 'fabric_type' => 'wool'  ) ;
$g_data[] = array ( 'id' =>  3, 'price' => 67.25  , 'color' => 'blue'    , 'brand' => 'CK'   , 'clothes_type' => 'dress' , 'fabric_type' => 'wool'  ) ;

$g_data[] = array ( 'id' =>  4, 'price' => 55.50  , 'color' => 'green'   , 'brand' => 'Dior' , 'clothes_type' => 'dress' , 'fabric_type' => 'cotton'  ) ;
$g_data[] = array ( 'id' =>  5, 'price' => 65.50  , 'color' => 'white'   , 'brand' => 'CK'   , 'clothes_type' => 'dress' , 'fabric_type' => 'cotton'  ) ;
$g_data[] = array ( 'id' =>  6, 'price' => 45.75  , 'color' => 'blue'    , 'brand' => 'Boss' , 'clothes_type' => 'dress' , 'fabric_type' => 'cotton'  ) ;
$g_data[] = array ( 'id' =>  7, 'price' => 77.25  , 'color' => 'white'   , 'brand' => 'Boss' , 'clothes_type' => 'dress' , 'fabric_type' => 'cotton'  ) ;

$g_data[] = array ( 'id' =>  8, 'price' => 25.50  , 'color' => 'green'   , 'brand' => 'Dior' , 'clothes_type' => 'tie' , 'fabric_type' => 'wool'  ) ;
$g_data[] = array ( 'id' =>  9, 'price' => 35.50  , 'color' => 'blue'    , 'brand' => 'Dior' , 'clothes_type' => 'tie' , 'fabric_type' => 'wool'  ) ;
$g_data[] = array ( 'id' => 10, 'price' => 25.75  , 'color' => 'blue'    , 'brand' => 'Boss' , 'clothes_type' => 'tie' , 'fabric_type' => 'wool'  ) ;
$g_data[] = array ( 'id' => 11, 'price' => 47.25  , 'color' => 'white'   , 'brand' => 'CK'   , 'clothes_type' => 'tie' , 'fabric_type' => 'wool'  ) ;

$g_data[] = array ( 'id' => 12, 'price' => 35.50  , 'color' => 'green'   , 'brand' => 'Dior' , 'clothes_type' => 'tie' , 'fabric_type' => 'cotton'  ) ;
$g_data[] = array ( 'id' => 13, 'price' => 45.50  , 'color' => 'white'   , 'brand' => 'CK'   , 'clothes_type' => 'tie' , 'fabric_type' => 'cotton'  ) ;
$g_data[] = array ( 'id' => 14, 'price' => 25.75  , 'color' => 'blue'    , 'brand' => 'Boss' , 'clothes_type' => 'tie' , 'fabric_type' => 'cotton'  ) ;
$g_data[] = array ( 'id' => 15, 'price' => 57.25  , 'color' => 'green'   , 'brand' => 'CK'   , 'clothes_type' => 'tie' , 'fabric_type' => 'cotton'  ) ;

$g_data[] = array ( 'id' => 16, 'price' => 83.50  , 'color' => 'blue'    , 'brand' => 'Dior' , 'clothes_type' => 'jacket' , 'fabric_type' => 'wool'  ) ;
$g_data[] = array ( 'id' => 17, 'price' => 76.50  , 'color' => 'white'   , 'brand' => 'CK'   , 'clothes_type' => 'jacket' , 'fabric_type' => 'wool'  ) ;
$g_data[] = array ( 'id' => 18, 'price' => 63.75  , 'color' => 'blue'    , 'brand' => 'Boss' , 'clothes_type' => 'jacket' , 'fabric_type' => 'wool'  ) ;
$g_data[] = array ( 'id' => 19, 'price' => 58.25  , 'color' => 'green'   , 'brand' => 'CK'   , 'clothes_type' => 'jacket' , 'fabric_type' => 'wool'  ) ;

$g_data[] = array ( 'id' => 20, 'price' => 65.50  , 'color' => 'green'   , 'brand' => 'Dior' , 'clothes_type' => 'jacket' , 'fabric_type' => 'cotton'  ) ;
$g_data[] = array ( 'id' => 21, 'price' => 79.50  , 'color' => 'white'   , 'brand' => 'CK'   , 'clothes_type' => 'jacket' , 'fabric_type' => 'cotton'  ) ;
$g_data[] = array ( 'id' => 22, 'price' => 51.75  , 'color' => 'blue'    , 'brand' => 'Boss' , 'clothes_type' => 'jacket' , 'fabric_type' => 'cotton'  ) ;
$g_data[] = array ( 'id' => 23, 'price' => 82.25  , 'color' => 'white'   , 'brand' => 'CK'   , 'clothes_type' => 'jacket' , 'fabric_type' => 'cotton'  ) ;

function lookupTypeFabric( $clothes_type, $fabric_type )
{
    global $g_data;
    
    $aRet = array();
    foreach ( $g_data as $item ) {
        if ( $item['clothes_type'] == $clothes_type && $item['fabric_type'] == $fabric_type ) {
            $aRet[] = $item;
        }
    }
    return $aRet;
}

function lookupType( $clothes_type )
{
    global $g_data;
    
    $aRet = array();
    foreach ( $g_data as $item ) {
        if ( $item['clothes_type'] == $clothes_type ) {
            $aRet[] = $item;
        }
    }
    return $aRet;
}


function lookupID( $id )
{
    global $g_data;
    
    $ret = null;
    foreach ( $g_data as $item ) {
        if ( $item['id'] == $id ) {
            $ret = $item;
        }
    }
    return $ret;
}


function getItemsForPage( $aItems, $searchListingPage )
{
    global $g_itemsPerSearchListingPage;
    
    $startItem  = $searchListingPage * $g_itemsPerSearchListingPage;
    $endItem    = $startItem + $g_itemsPerSearchListingPage;
    
    
    $aRet = array();
    $i = 0;
    
    foreach ( $aItems as $item ) {
       if ( $i >= $startItem && $i < $endItem  ) {
            $aRet[] = $item;
        }
        $i++;
    }
    return $aRet;
}


function getNextPageNumber( $aItems, $searchListingPage )
{
    global $g_itemsPerSearchListingPage;
    
    $startItem  = $searchListingPage * $g_itemsPerSearchListingPage;
    $endItem    = $startItem + $g_itemsPerSearchListingPage;
    
    
    $iNextSearchListingPage = null;
    if ( count($aItems) > $endItem ) {
        $iNextSearchListingPage = $searchListingPage +1;
    }

    return $iNextSearchListingPage;
}



?>

