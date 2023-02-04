<?php 
require_once ('../examples_common.php');
echo headerGet("'DoSearch', Actions and 'click next' links", "ExDoSearchActionsAndClickNext", "[6,7,11,12,16,17,21,22]", "[15,16,21,31,42,43,44,53,82,83,84,85,86,87]", "http://netscavator.com/content/example-do-search-actions-and-click-next" );
?>
        <A href="dosearch.php" >Back to search page</A><BR> 
        <H3>Product listing 2</H3>
        <DIV class="product" >
            <DIV style="color:green;float:left" >Trousers: </DIV>
            <DIV style="float:left" class="class2">35.50 EUR</DIV><BR />
            <A href=# >Green trousers. View and buy - click here </A>
        </DIV>
        <DIV class="product" >
            <DIV style="color:green;float:left" >Jacket: </DIV><DIV style="float:left" class="class2">50.25 EUR</DIV><BR />
            <A href=# >Marine jacket. View and buy - click here </A>
        </DIV>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockStartGet("[]"); ?>
        <A href="dosearch.php" >Back to search page</A><BR> 
        <H3>Product listing 2</H3>
        <DIV class="product" >
            <DIV style="color:green;float:left" >Trousers: </DIV>
            <DIV style="float:left" class="class2">35.50 EUR</DIV><BR />
            <A href=# >Green trousers. View and buy - click here </A>
        </DIV>
        <DIV class="product" >
            <DIV style="color:green;float:left" >Jacket: </DIV><DIV style="float:left" class="class2">50.25 EUR</DIV><BR />
            <A href=# >Marine jacket. View and buy - click here </A>
        </DIV>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockEndGet(); ?>
<?php echo footerGet(); ?>
