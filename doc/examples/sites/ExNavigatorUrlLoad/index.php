<?php 
require_once ('../examples_common.php');
echo headerGet("Navigator: Url load", "ExNavigatorUrlLoad", 
    "[11]", "[25,26,27,28,29,30,31,32]", "http://netscavator.com/content/example-navigator-url-load" );
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
