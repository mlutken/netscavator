<?php 
require_once ('../examples_common.php');
echo headerGet("Navigator: External file input", "ExNavigatorFileInput", 
    "[]", "[26,27]", "http://netscavator.com/content/example-navigator-external-file-input" );
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
