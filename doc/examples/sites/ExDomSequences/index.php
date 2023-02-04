<?php 
require_once ('../examples_common.php');
echo headerGet("Dom sequences", "ExDomSequences", "[5,6,7,8,9,10,11,12]", "[14,15,16,33,34,35,38,40]", "http://netscavator.com/content/example-dom-sequences" );
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
<?php echo sourceBlockStartGet("[2,3,4,8,9,10]"); ?>
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
