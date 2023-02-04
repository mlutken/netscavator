<?php 
require_once ('../examples_common.php');
echo headerGet("Navigator: Text input and custom trim function", "ExNavigatorTextInput", 
    "[6,11]", "[16,23,26,27,28,29,30,40,41,42,43,44,45,97]", "http://netscavator.com/content/example-navigator-text-input-and-custom-trim" );
?>
        <A href="dosearch.php" >Please proceed to the search page by clicking this link.</A>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockStartGet("[]"); ?>
        <A href="dosearch.php" >Please proceed to the search page by clicking this link.</A>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockEndGet(); ?>
<?php echo footerGet(); ?>
