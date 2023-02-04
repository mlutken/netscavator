<?php 
require_once ('../examples_common.php');
echo headerGet("Template ProductPage", "ExTemplateProductPage", 
    "[]", "[]", 
    "http://netscavator.com/content/example-template-productpage", "[]" );
?>
        <A href="dosearch.php" >Please proceed to the search page by clicking this link.</A>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockStartGet("[]", true); ?>
        <A href="dosearch.php" >Please proceed to the search page by clicking this link.</A>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockEndGet(); ?>
<?php echo footerGet(true); ?>
