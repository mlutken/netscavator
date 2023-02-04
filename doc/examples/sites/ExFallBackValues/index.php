<?php 
require_once ('../examples_common.php');
echo headerGet("Fallback values", "ExFallBackValues", 
    "[]", "[26,27,32,95,105,106,108,141]", "http://netscavator.com/content/example-fallback-values" );
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
