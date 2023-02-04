<?php 
require_once ('../examples_common.php');


$searchListingPage = $_GET['page'];
$pageNumberShow = (int)$searchListingPage +1;

$items                  = lookupTypeFabric( $_GET['clothes_type'], $_GET['fabric_type'] );
$d                      = getItemsForPage( $items, $searchListingPage );
$nextSearchListingPage  = getNextPageNumber( $items, $searchListingPage );

echo headerGet("Navigator: DomPosClick, radio buttons, dom sequences with parameters", "ExNavigatorDomClickPos", 
    "[6,8,9,10,11]", "[23,24,26,27,31,33,34,35,37,38,39]", "http://netscavator.com/content/example-navigator-domposclick-radio-buttons" );
?>
        <A href="dosearch.php" >Back to search page</A><BR> 
        <?php 
        if ( count($items) == 0 ) {
            echo "<H2>You need to select something in both drop down's. </H2>";
            exit(0);
        }
        echo "<br />";
        echo "<H1>Product listing $pageNumberShow</H1>";
        ?>
        <DIV class="product" >
        <?php
            $i = 0;
            echo "<DIV style=\"color:green;float:left\" >" . $d[$i]['clothes_type'] . ": </DIV>";
            echo "<DIV style=\"float:left\" class=\"class2\">" . $d[$i]['price'] . " EUR</DIV><BR />";
            echo "<A href=# >" . $d[$i]['color'] . " " . $d[$i]['clothes_type'] . ". View and buy - click here </A>";
        ?>    
        </DIV>
        <DIV class="product" >
        <?php
            $i = 1;
            echo "<DIV style=\"color:green;float:left\" >" . $d[$i]['clothes_type'] . ":  </DIV>";
            echo "<DIV style=\"float:left\" class=\"class2\">" . $d[$i]['price'] . " EUR</DIV><BR />";
            echo "<A href=# >" . $d[$i]['color'] . " " . $d[$i]['clothes_type'] . ". View and buy - click here </A>";
        ?>    
        </DIV>
        <?php 
            if ( null != $nextSearchListingPage ) {
                echo "<A href=\"searchlisting.php?clothes_type={$_GET['clothes_type']}&fabric_type={$_GET['fabric_type']}&page={$nextSearchListingPage}\" style=\"font-size:20px\" >Next</A>";
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
