<?php 
require_once ('../examples_common.php');
echo headerGet("Navigator: External file input with php filter function", "ExNavigatorFileInputFilter", 
    "[9]", "[26,27,37,38,39,40,41,42,43,44,45,46,47,52]", "http://netscavator.com/content/example-navigator-external-file-input-filter" );
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
