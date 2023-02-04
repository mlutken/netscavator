<?php 
require_once ('../examples_common.php');
$searchListingPage = $_GET['page'];
$pageNumberShow = (int)$searchListingPage +1;

$items                  = lookupType( $_GET['clothes_type'] );
$d                      = getItemsForPage( $items, $searchListingPage );
$nextSearchListingPage  = getNextPageNumber( $items, $searchListingPage );

echo headerGet("Navigator: External file input with php filter function", "ExNavigatorFileInputFilter", 
    "[9]", "[26,27,37,38,39,40,41,42,43,44,45,46,47,52]", "http://netscavator.com/content/example-navigator-external-file-input-filter" );
?>
        <A href="dosearch.php" >Back to search page</A><BR> 
        <?php 
        if ( count($items) == 0 ) {
            echo "<H2>You MUST type 'dress', 'tie' or 'jacket' (case sensitive) in the input field</H2>";
            exit(0);
        }
        echo "<br />";
        echo "<H3>Product listing $pageNumberShow</H3>";
        ?>
        <DIV class="product" >
        <?php
            $i = 0;
            echo "<DIV style=\"color:green;float:left\" >" . $d[$i]['clothes_type'] . ": </DIV>";
            echo "<DIV style=\"color:black;float:left\" >&nbsp;(" . $d[$i]['fabric_type'] . ")&nbsp;</DIV>";
            echo "<DIV style=\"float:left\" class=\"class2\">" . $d[$i]['price'] . " EUR</DIV><BR />";
            echo "<A href=# >" . $d[$i]['color'] . " " . $d[$i]['clothes_type'] . ". View and buy - click here </A>";
        ?>    
        </DIV>
        <DIV class="product" >
        <?php
            $i = 1;
            echo "<DIV style=\"color:green;float:left\" >" . $d[$i]['clothes_type'] . ":  </DIV>";
            echo "<DIV style=\"color:black;float:left\" >&nbsp;(" . $d[$i]['fabric_type'] . ")&nbsp;</DIV>";
            echo "<DIV style=\"float:left\" class=\"class2\">" . $d[$i]['price'] . " EUR</DIV><BR />";
            echo "<A href=# >" . $d[$i]['color'] . " " . $d[$i]['clothes_type'] . ". View and buy - click here </A>";
        ?>    
        </DIV>
        <?php 
            if ( null != $nextSearchListingPage ) {
                echo "<A href=\"searchlisting.php?clothes_type={$_GET['clothes_type']}&page={$nextSearchListingPage}\" style=\"font-size:20px\" >Next</A>";
            }
        ?>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockStartGet("[]"); ?>
        <H3>Product listing 1</H3>
        <DIV class="product" >
        <DIV style="color:green;float:left" >dress: </DIV>
        <DIV style="float:left" class="class2">45.5 EUR</DIV><BR>
        <A href=# >white dress. View and buy - click here </A>    
        </DIV>
        <DIV class="product" >
        <DIV style="color:green;float:left" >dress:  </DIV>
        <DIV style="float:left" class="class2">55.5 EUR</DIV>
        <BR><A href=# >green dress. View and buy - click here </A>    
        </DIV>
        <A href="searchlisting.php?clothes_type=dress&fabric_type=wool&page=1" style="font-size:20px" >Next</A>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockEndGet(); ?>
<?php echo footerGet(); ?>
