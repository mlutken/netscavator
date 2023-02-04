<?php 
require_once ('../examples_common.php');
echo headerGet("Navigator: Text input and custom trim function", "ExNavigatorTextInput", 
    "[6,11]", "[16,23,26,27,28,29,30,40,41,42,43,44,45,97]", "http://netscavator.com/content/example-navigator-text-input-and-custom-trim" );
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
