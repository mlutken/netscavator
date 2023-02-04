<?php 
require_once ('../examples_common.php');
echo headerGet("Automatic test 1", "TestAuto1", 
    "[6,11,12]", "[20,24,25,26,27,28,29,30,101,102,113,114,130,134,142,143,144,145,146,147,148,149,158,159,162,163,164,165]" );
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
        <p> Hello you! <b>bold</b> and now in <i>italics</i>, more ?
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockEndGet(); ?>
<?php echo footerGet(); ?>
