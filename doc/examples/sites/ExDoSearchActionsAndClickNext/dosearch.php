<?php 
require_once ('../examples_common.php');
echo headerGet("'DoSearch', Actions and 'click next' links", "ExDoSearchActionsAndClickNext", "[6,7,11,12,16,17,21,22]", "[15,16,21,31,42,43,44,53,82,83,84,85,86,87]", "http://netscavator.com/content/example-do-search-actions-and-click-next" );
?>
        <FORM name="dosearch" action="searchlisting1.php" method="get">
        Product type: <INPUT name=producttype type="text" size="25" value="" /> (tip: You MUST type 'all' )
        <BR><INPUT value="Search" type="submit" /><BR>
        </DIV>
        </FORM>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockStartGet("[2,3]"); ?>
        <FORM name="dosearch" action="searchlisting1.php" method="get">
        Product type: <INPUT name=producttype type="text" size="25" value="" /> (tip: You MUST type 'all' )
        <BR><INPUT value="Search" type="submit" /><BR>
        </DIV>
        </FORM>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockEndGet(); ?>
<?php echo footerGet(); ?>
