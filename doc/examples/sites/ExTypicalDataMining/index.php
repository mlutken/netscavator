<?php 
require_once ('../examples_common.php');
echo headerGet("Typical data mining", "ExTypicalDataMining", "[6,7,11,12]", "[13,14,15,32,33,34,35,44,45]", "http://netscavator.com/content/example-typical-data-mining" );
?>
    <H3>Product listing</H3>
        <DIV class="product" >
            <DIV style="color:green;float:left" >Shirt: </DIV>
            <DIV style="float:left" class="class2">12.75 EUR</DIV><BR />
            <A href=# >White shirt. View and buy - click here </A>
        </DIV>
        <BR />
        <DIV class="product" >
            <DIV style="color:green;float:left" >Socks: </DIV>
            <DIV style="float:left" class="class2">2.75 EUR</DIV><BR />
            <A href=# >Black socks. View and buy - click here </A>
        </DIV>
        <A href=# style="font-size:20px" >Next</A>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockStartGet("[3,4,9,10]"); ?>
                <H3>Product listing</H3>
                    <DIV class="product" >
                        <DIV style="color:green;float:left" >Shirt: </DIV>
                        <DIV style="float:left" class="class2">12.75 EUR</DIV><BR />
                        <A href=# >White shirt. View and buy - click here </A>
                    </DIV>
                    <BR />
                    <DIV class="product" >
                        <DIV style="color:green;float:left" >Socks: </DIV>
                        <DIV style="float:left" class="class2">2.75 EUR</DIV><BR />
                        <A href=# >Black socks. View and buy - click here </A>
                    </DIV>
                    <A href=# style="font-size:20px" >Next</A>
                    <BR>
                    <BR>
                    <HR>
<?php echo sourceBlockEndGet(); ?>
<?php echo footerGet(); ?>
