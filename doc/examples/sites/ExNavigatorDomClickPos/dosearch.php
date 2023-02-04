<?php 
require_once ('../examples_common.php');
echo headerGet("Navigator: DomPosClick, radio buttons, dom sequences with parameters", "ExNavigatorDomClickPos", 
    "[6,8,9,10,11]", "[23,24,26,27,31,33,34,35,37,38,39]", "http://netscavator.com/content/example-navigator-domposclick-radio-buttons" );
?>
        <FORM name="dosearch" action="searchlisting.php" method="get">
        <H3>Select clothes type</H3>
        <INPUT name="clothes_type" value="dress" type="radio" >Dresses<BR>
        <INPUT name="clothes_type" value="tie" type="radio" >Ties<BR>
        <INPUT name="clothes_type" value="jacket" type="radio" >Jackets<BR>
        <HR>
        <H3>Select fabric type</H3>
        <INPUT name="fabric_type" value="wool" type="radio" >Wool<BR>
        <INPUT name="fabric_type" value="cotton" type="radio" >Cotton<BR>
        <INPUT name="page" value=0 type="hidden" />
        <BR><INPUT value="Search" type="submit" /><BR>
        </DIV>
        </FORM>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockStartGet("[3,4,5,8,9,10]"); ?>
        <FORM name="dosearch" action="searchlisting.php" method="get">
        <H3>Select clothes type</H3>
        <INPUT name="clothes_type" value="dress" type="radio" >Dresses<BR>
        <INPUT name="clothes_type" value="tie" type="radio" >Ties<BR>
        <INPUT name="clothes_type" value="jacket" type="radio" >Jackets<BR>
        <HR>
        <H3>Select fabric type</H3>
        <INPUT name="fabric_type" value="wool" type="radio" >Wool<BR>
        <INPUT name="fabric_type" value="cotton" type="radio" >Cotton<BR>
        <INPUT name="page" value=0 type="hidden" />
        <BR><INPUT value="Search" type="submit" /><BR>
        </DIV>
        </FORM>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockEndGet(); ?>
<?php echo footerGet(); ?>
