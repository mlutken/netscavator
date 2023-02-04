<?php 
require_once ('../examples_common.php');
$searchListingPage = $_GET['page'];
$pageNumberShow = (int)$searchListingPage +1;

$items                  = lookupTypeFabric( $_GET['clothes_type'], $_GET['fabric_type'] );
$d                      = getItemsForPage( $items, $searchListingPage );
$nextSearchListingPage  = getNextPageNumber( $items, $searchListingPage );


echo headerGet("Navigator: Introduction and drop down SELECT's", "ExNavigatorAndSelects", 
    "[6,8,9,11,12]", "[17,23,24,29,30,31,32,33,34,35,36,37,74,75,106,108,109,111,112,123,124,125,126]", "http://netscavator.com/content/example-navigator-introduction-and-drop-down-selects" );
?>
        <A href="dosearch.php" >Back to search page</A><BR> 
        <?php 
        if ( count($items) == 0 ) {
            echo "<H2>You need to select something in both drop down's. </H2>";
            exit(0);
        }
        echo "<br />";
        echo "<H3>Product listing $pageNumberShow</H3>";
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
