<?php 
require_once ('../examples_common.php');
echo headerGet("Navigator: DomPosClick, radio buttons, dom sequences with parameters", "ExNavigatorDomClickPos", 
    "[6,8,9,10,11]", "[23,24,26,27,31,33,34,35,37,38,39]", "http://netscavator.com/content/example-navigator-domposclick-radio-buttons" );
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
