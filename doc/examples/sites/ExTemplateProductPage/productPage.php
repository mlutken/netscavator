<?php 
require_once ('../examples_common.php');

$product_id             = $_GET['product_id'];
$item                   = lookupID( $product_id );

echo headerGet("Template ProductPage", "ExTemplateProductPage", 
    "[]", "[]", 
    "http://netscavator.com/content/example-template-productpage", "[]" );
?>
        <A href="dosearch.php" >Back to search page</A><BR> 
        <?php 
        echo "<H3>Show product {$item['clothes_type']}</H3>";
        ?>
        <?php
            echo "<TABLE>\n";
            echo "    <TR>\n";
            echo "        <TD>Type: </TD><TD>{$item['clothes_type']}</TD>\n";
            echo "    <TR>\n";
            echo "    <TR>\n";
            echo "        <TD>Price: </TD><TD>{$item['price']}</TD>\n";
            echo "    <TR>\n";
            echo "    <TR>\n";
            echo "        <TD>Color: </TD><TD>{$item['color']}</TD>\n";
            echo "    <TR>\n";
            echo "    <TR>\n";
            echo "        <TD>Fabric: </TD><TD>{$item['fabric_type']}</TD>\n";
            echo "    <TR>\n";
            echo "    <TR>\n";
            echo "        <TD>Brand: </TD><TD>{$item['brand']}</TD>\n";
            echo "    <TR>\n";
            echo "    <TR>\n";
            echo "        <TD>Product ID: </TD><TD>$product_id</TD>\n";
            echo "    <TR>\n";
            echo "</TABLE>\n";
        ?>    
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockStartGet("[]", true); ?>
        <H3>Show product dress</H3>
        <TABLE>
            <TR>
                <TD>Type: </TD><TD>dress</TD>
            <TR>
            <TR>
                <TD>Price: </TD><TD>65.5</TD>
            <TR>
            <TR>
                <TD>Color: </TD><TD>white</TD>
            <TR>
            <TR>
                <TD>Fabric: </TD><TD>cotton</TD>
            <TR>
            <TR>
                <TD>Brand: </TD><TD>CK</TD>
            <TR>
            <TR>
                <TD>Product ID: </TD><TD>5</TD>
            <TR>
        </TABLE>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockEndGet(); ?>
<?php echo footerGet(true); ?>
