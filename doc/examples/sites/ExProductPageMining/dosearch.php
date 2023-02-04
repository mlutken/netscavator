<?php 
require_once ('../examples_common.php');
echo headerGet("Product page mining - 'full scan'", "ExProductPageMining", 
    "[6,11,12]", "[20,24,25,26,27,28,29,30,91,96,107,108,109,124,125,126,127,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,147]"
    , "http://netscavator.com/content/example-product-page-mining");
?>
        <FORM name="dosearch" action="searchlisting.php" method="get">
        <SELECT name="clothes_type" >
        <OPTION value="none">Select clothes category</OPTION>
        <OPTION value="dress">Dresses</OPTION>
        <OPTION value="tie">Ties</OPTION>
        <OPTION value="jacket">Jackets</OPTION>
        </SELECT>
        <SELECT name="fabric_type" >
        <OPTION value="none">Select fabric</OPTION>
        <OPTION value="wool">Wool</OPTION>
        <OPTION value="cotton">Cotton</OPTION>
        </SELECT>
        <INPUT name="page" value=0 type="hidden" />
        <BR><INPUT value="Search" type="submit" /><BR>
        </DIV>
        </FORM>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockStartGet("[]"); ?>
        <FORM name="dosearch" action="searchlisting.php" method="get">
        <SELECT name="clothes_type" >
        <OPTION value="none">Select clothes category</OPTION>
        <OPTION value="dress">Dresses</OPTION>
        <OPTION value="tie">Ties</OPTION>
        <OPTION value="jacket">Jackets</OPTION>
        </SELECT>
        <SELECT name="fabric_type" >
        <OPTION value="none">Select fabric</OPTION>
        <OPTION value="wool">Wool</OPTION>
        <OPTION value="cotton">Cotton</OPTION>
        </SELECT>
        <INPUT name="page" value=0 type="hidden" />
        <BR><INPUT value="Search" type="submit" /><BR>
        </DIV>
        </FORM>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockEndGet(); ?>
<?php echo footerGet(); ?>
