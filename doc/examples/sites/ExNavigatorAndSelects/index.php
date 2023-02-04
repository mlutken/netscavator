<?php 
require_once ('../examples_common.php');
echo headerGet("Navigator: Introduction and drop down SELECT's", "ExNavigatorAndSelects", 
    "[6,8,9,11,12]", "[17,23,24,29,30,31,32,33,34,35,36,37,74,75,106,108,109,111,112,123,124,125,126]", "http://netscavator.com/content/example-navigator-introduction-and-drop-down-selects" );
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
