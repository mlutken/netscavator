<?php 
require_once ('../examples_common.php');

$product_id             = $_GET['product_id'];
$item                   = lookupID( $product_id );

echo headerGet("Fallback values", "ExFallBackValues", 
    "[]", "[26,27,32,95,105,106,108,141]", "http://netscavator.com/content/example-fallback-values" );
?>
        <A href="dosearch.php" >Back to search page</A><BR> 
        <?php 
        echo "<H3>Show product {$item['clothes_type']}</H3>";
        ?>
        <?php
            echo "<TABLE>\n";
            echo "    <TR>\n";
            echo "        <TD>Type: </TD><TD>{$item['clothes_type']}</TD>\n";
            echo "    <TR>\n";
            echo "    <TR>\n";
            echo "        <TD>Price: </TD><TD>{$item['price']}</TD>\n";
            echo "    <TR>\n";
            echo "    <TR>\n";
            echo "        <TD>Color: </TD><TD>{$item['color']}</TD>\n";
            echo "    <TR>\n";
            echo "    <TR>\n";
            echo "        <TD>Fabric: </TD><TD>{$item['fabric_type']}</TD>\n";
            echo "    <TR>\n";
            echo "    <TR>\n";
            echo "        <TD>Brand: </TD><TD>{$item['brand']}</TD>\n";
            echo "    <TR>\n";
            echo "    <TR>\n";
            echo "        <TD>Product ID: </TD><TD>$product_id</TD>\n";
            echo "    <TR>\n";
            echo "</TABLE>\n";
        ?>    
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockStartGetNoScript("[4,7,10,13,16,19]"); ?>
        <H3>Show product dress</H3>
        <TABLE>
            <TR>
                <TD>Type: </TD><TD>dress</TD>
            <TR>
            <TR>
                <TD>Price: </TD><TD>65.5</TD>
            <TR>
            <TR>
                <TD>Color: </TD><TD>white</TD>
            <TR>
            <TR>
                <TD>Fabric: </TD><TD>cotton</TD>
            <TR>
            <TR>
                <TD>Brand: </TD><TD>CK</TD>
            <TR>
            <TR>
                <TD>Product ID: </TD><TD>5</TD>
            <TR>
        </TABLE>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockEndGet(); ?>
<?php echo footerGetNoScript(); ?>

<?php
function sourceBlockStartGetNoScript($highLightHtml, $bIsTemplateExample = false )
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
            <tr><td><strong>Note: Script source code for this example is left out intentionally.</strong><br> 
            It's inclusion on the page makes the fallback examples fail due to domFind/outputValueFindNext falsely finding.<br><br>
            <strong>Explanation:</strong> <br>
            The source code is loaded 
            upon page load and is part of the dom tree for this page. When we make a 
            <b>outputValueFindNext(1, "MyProductProperty_FIND", "my_property");</b> and the dom sequence MyProductProperty_FIND is not 
            defined the crawler will create a a sequence that look for any node that contains the string 'MyProductProperty_FIND'. In essence 
            it is the same as if you defined the sequence like: <b>domSeqCreate("MyProductProperty_FIND", "MyProductProperty_FIND", "contains" );</b> 
            So with the script loaded this string will always be present on the page. 
            <br>
            Long explanation, but this is only a 'problem' on the special example sites, not a real world problem.
            </td></tr>
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


function footerGetNoScript( $bIsTemplateExample = false)
{    
$str = <<<MY_DELIMITER1
    <BR>
        <script>
        function onPageLoad( baseName, highLightXML, highLightScript, highLightTemplate) {
            loadCode(   "../../code/" + baseName + "/" + baseName + ".xml"
                        , "xmloutput_code", "xml", "highlight: " + highLightXML );
MY_DELIMITER1;


$str .= <<<MY_DELIMITER1
         }

    </script>

    </BODY>
</HTML>
MY_DELIMITER1;

    global $g_baseName;
    return  $str;
}

?>
