<?php 
require_once ('../examples_common.php');
echo headerGet("'DoSearch', Actions and 'click next' links", "ExDoSearchActionsAndClickNext", "[6,7,11,12,16,17,21,22]", "[15,16,21,31,42,43,44,53,82,83,84,85,86,87]", "http://netscavator.com/content/example-do-search-actions-and-click-next" );
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
