<?php 
require_once ('../examples_common.php');
echo headerGet("Template SearchListing", "ExTemplateSearchListing", 
    "[]", "[]", 
    "http://netscavator.com/content/example-template-searchlisting", "[]" );
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
<?php echo sourceBlockStartGet("[2,3,4,5,6,8,9,10,11]", true); ?>
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
<?php echo footerGet(true); ?>
