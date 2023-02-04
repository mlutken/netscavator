<?php 
require_once ('../examples_common.php');
echo headerGet("Automatic test 1", "TestAuto1", 
    "[6,11,12]", "[20,24,25,26,27,28,29,30,101,102,113,114,130,134,142,143,144,145,146,147,148,149,158,159,162,163,164,165]" );
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
