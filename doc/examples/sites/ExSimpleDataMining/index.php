<?php 
require_once ('../examples_common.php');
echo headerGet("Simple data mining", "ExSimpleDataMining", "[5,6]", "[25,26,27,30,31]", "http://netscavator.com/content/example-simple-data-mining" );
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
<?php echo sourceBlockStartGet("[3,4]"); ?>
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
