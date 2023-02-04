<?php 
require_once ('../examples_common.php');
echo headerGet("Navigator: External file input", "ExNavigatorFileInput", 
    "[]", "[26,27]", "http://netscavator.com/content/example-navigator-external-file-input" );
?>
        <FORM name="dosearch" action="searchlisting.php" method="get">
        Input clothes category: <INPUT name=clothes_type size="25" value="" type="text" /> (tip: You MUST type <b>dress</b>, <b>tie</b> or <b>jacket</b> (case sensitive))
        <BR>
        <INPUT name="page" value=0 type="hidden" />
        <INPUT value="Search" type="submit" /><BR>
        </DIV>
        </FORM>
        <HR>
        <BR>
        <HR>
<?php echo sourceBlockStartGet("[5]"); ?>
        <FORM name="dosearch" action="searchlisting.php" method="get">
        Input clothes category: <INPUT name=clothes_type size="25" value="" type="text" /> (tip: You MUST type <b>dress</b>, <b>tie</b> or <b>jacket</b> (case sensitive))
        <BR>
        <INPUT name="page" value=0 type="hidden" />
        <INPUT value="Search" type="submit" /><BR>
        </DIV>
        </FORM>
        <HR>
        <BR>
        <HR>
<?php echo sourceBlockEndGet(); ?>
<?php echo footerGet(); ?>
