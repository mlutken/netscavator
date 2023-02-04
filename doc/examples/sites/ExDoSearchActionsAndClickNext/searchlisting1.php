<?php 
require_once ('../examples_common.php');
echo headerGet("'DoSearch', Actions and 'click next' links", "ExDoSearchActionsAndClickNext", "[6,7,11,12,16,17,21,22]", "[15,16,21,31,42,43,44,53,82,83,84,85,86,87]", "http://netscavator.com/content/example-do-search-actions-and-click-next" );
?>
        <A href="dosearch.php" >Back to search page</A><BR> 
        You searched for:  
        <?php 
        echo $_GET['producttype']; 
        if ( $_GET['producttype'] != 'all' ) {
            echo "<H2>You need to enter 'all' in the search form, please go back. </H2>";
            exit(0);
        }
        ?>
        <br />
<!--        <A href="searchlisting2.php" id="testTarget" onclick="alert('I was clicked!');" >Simulate a click here</A><br>
        <button id="runTest1" onclick="simulatedClick(document.getElementById('testTarget'), {});" >Simulate click on above button 1</button><br>
        <button id="runTest2" onclick="document.getElementById('testTarget').click();" >Simulate click on above button 2</button><br>
        <button id="runTest3" onclick="simulatedClick2(document.getElementById('testTarget'));" >Simulate click on above button 3</button><br>-->
        <H3>Product listing 1</H3>
        <DIV class="product" >
            <DIV style="color:green;float:left" >Shirt: </DIV>
            <DIV style="float:left" class="class2">12.75 EUR</DIV><BR />
            <A href=# >White shirt. View and buy - click here </A>
        </DIV>
        <DIV class="product" >
            <DIV style="color:green;float:left" >Socks: </DIV>
            <DIV style="float:left" class="class2">2.75 EUR</DIV><BR />
            <A href=# >Black socks. View and buy - click here </A>
        </DIV>
        <A href="searchlisting2.php" style="font-size:20px" >Next</A>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockStartGet("[12]"); ?>
        <H3>Product listing 1</H3>
        <DIV class="product" >
            <DIV style="color:green;float:left" >Shirt: </DIV>
            <DIV style="float:left" class="class2">12.75 EUR</DIV><BR />
            <A href=# >White shirt. View and buy - click here </A>
        </DIV>
        <DIV class="product" >
            <DIV style="color:green;float:left" >Socks: </DIV>
            <DIV style="float:left" class="class2">2.75 EUR</DIV><BR />
            <A href=# >Black socks. View and buy - click here </A>
        </DIV>
        <A href="searchlisting2.php" style="font-size:20px" >Next</A>
        <BR>
        <BR>
        <HR>
<?php echo sourceBlockEndGet(); ?>
<?php echo footerGet(); ?>
