<?php 
require_once ('../examples_common.php');
echo headerGet("Product page mining - 'full scan'", "ExProductPageMining", 
    "[6,11,12]", "[20,24,25,26,27,28,29,30,91,96,107,108,109,124,125,126,127,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,147]"
    , "http://netscavator.com/content/example-product-page-mining");
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
