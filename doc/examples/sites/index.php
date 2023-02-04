
<?php 
require_once ('examples_common.php');
$aAllExamples[] = array("Minimal", "ExMinimal", "Simplest posible working miner, which simply displays a page." );
$aAllExamples[] = array("Simple data mining", "ExSimpleDataMining", "Very basic mining of data." );
$aAllExamples[] = array("Dom sequences", "ExDomSequences", "Search for sequences of elements like <strong>domFind ( 1, 'DIV, class, product', 'equals' ).</strong>" );
$aAllExamples[] = array("Output trimming", "ExOutputTrimming", "Trimming output values. For example to get rid of for an unwanted ':' or '$' char." );
$aAllExamples[] = array("Typical data mining", "ExTypicalDataMining", "Typical cookbook example of how we would normally mine data from a single page" );
$aAllExamples[] = array("Do search, actions and click next", "ExDoSearchActionsAndClickNext", "Example showing a DoSearch page and several SearchListing pages with next links." );
$aAllExamples[] = array("Navigator introduction and drop down SELECTs", "ExNavigatorAndSelects", "Introducing the navigator. Here we use the navigator to traverse all combinations of two drop-down/combo selects." );
$aAllExamples[] = array("Navigator url load", "ExNavigatorUrlLoad", "Using the navigator to load URLs directly." );
$aAllExamples[] = array("Navigator DomPosClick, radio buttons", "ExNavigatorDomClickPos", "How to handle clicking of dom positions (radio buttons) using the navigator." );
$aAllExamples[] = array("Navigator text input and custom trim", "ExNavigatorTextInput", "Input search strings to an INPUT field using the navigator. Example also shows howto to do custom output trimming using a simple PHP function." );
$aAllExamples[] = array("Navigator external file input", "ExNavigatorFileInput", "Reading the searchs strings from a file. Usefull if you need to search fo thousands or even millions of terms." );
$aAllExamples[] = array("Navigator external file input filter", "ExNavigatorFileInputFilter", "Filtering each of the strings read from the file using a simple custom PHP function." );
$aAllExamples[] = array("Product page mining", "ExProductPageMining", "Complete example showing how to do the whole DoSearch, SearchListing, ProductPage trio." );
$aAllExamples[] = array("Fallback values", "ExFallBackValues", "If an outputValueFind function on the ProductPage fails it can instead fall-back on a value mined from the SearchListing page or set directly using settingSet()." );
$aAllExamples[] = array("Template simple", "ExTemplateSimple", "Very simple template example. It builds upon the 'Typical data mining' example." );
$aAllExamples[] = array("Template SearchListing", "ExTemplateSearchListing", "Template for search list page mining. A real world useable template, but still relatively simple. It builds upon the 'Navigator introduction and drop down SELECTs' example." );
$aAllExamples[] = array("Template ProductPage", "ExTemplateProductPage", "Template for product page mining. A more comples template supporting also product page mining. It builds upon the 'Product page mining' example." );

?>
<HTML>
    <HEAD>
        <TITLE>Sleipner example sites</TITLE>
        <SCRIPT src="codeedit.js" type="text/javascript"></SCRIPT>
        <SCRIPT src="jquery-1.6.2.min.js"></SCRIPT>
        <SCRIPT src="examples_utils.js" type="text/javascript"></SCRIPT>
        <LINK type="text/css" rel="stylesheet" href="examples.css"/>
    </HEAD>
    <BODY class="class1 largeText" >
    <H2>Sleipner examples</H2>
    <p>
    The examples are intended to show the vast majority of Sleipners features in a simple tutorial like way. This means the examples build upon each other and are suited to read/try out in sequence. 
    From within the MinerCreator you should be able to easily load each of the examples from the welcome screen (tab examples).
    We use the same very primitive clothing shop throughout the examples. Each example has a lengthy explaning text found here: 
    <a href=http://netscavator.com/content/examples >http://netscavator.com/content/examples</a>. There is also a ling to the explaning text on 
    top of each of the example site pages.
    </p>
    <?php 
        echo "<table border=1 class=largeTextTable >\n";
        $i = 0;
        foreach ( $aAllExamples as $e ) {
            $i++;
            echo "<tr>\n";
            echo "<td>$i</a></td>\n"; 
            echo "<td><a href={$e[1]} >{$e[0]}</a></td>\n"; 
            echo "<td>{$e[2]}</td>\n"; 
            echo "</tr>\n";
        }
        echo "</table>\n";

    ?>
    <h2>XML, PHP and HTML on the example sites</h2>
    <p>
    If you point your browser to an example you will notice 3 expandable links, which when clicked will expand the XML output, 
    the PHP script code or the example relevant HTML respectively for the current example. 
    These are particularily usefull if you just want read/browse the example and actually try them out.
    </p>
    <p>
    Note that certain lines in the XML, PHP and HTML will be highlighted. These will be the lines that are of 
    particular interest to this specific example. If you go through the examples in order only a few new things 
    will be introduced in each "step" and the highlighted lines help you focus on the parts that are different 
    compared to the previous example(s).    
    </p>

    </BODY>
</HTML>